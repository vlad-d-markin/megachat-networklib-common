#include <eventmanager.h>


EventManager::EventManager()
{
    m_is_running = false;
}



void EventManager::registerClient(IPollingClient *client)
{
    if(m_polling_clients.size() + 1 >= POLL_SIZE)
        throw EventManagerException("Too many polling clients");

    m_polling_clients.insert(std::pair<int, IPollingClient *>(client->getSocket(), client));
}



void EventManager::unregisterClient(IPollingClient *client)
{
    m_polling_clients.erase(client->getSocket());
}



void EventManager::execute()
{
    m_is_running = true;

    struct pollfd fds[POLL_SIZE];

    while(m_is_running) {
        // Register set for poll
        for(int i = 0; i < m_polling_clients.size(); i++) {
            fds[i].fd = m_polling_clients[i]->getSocket();

            // Set events to wait for
            fds[i].events = 0;
            fds[i].events = POLLIN | POLLERR;
            if(m_polling_clients[i]->isPollingOut())
                fds[i].events |= POLLOUT;
        }

        // Poll
        int result = poll(fds, m_polling_clients.size(), POLL_TIMEOUT);

        // Timeout
        if(result == 0)
            continue;

        if(result < 0)
            throw EventManagerException("Poll failed", errno);

        // Dispatch events
        for(int i = 0; i < m_polling_clients.size(); i++) {
            // No events
            if(fds[i].revents == 0)
                continue;

            // onIn
            if(fds[i].revents & POLLIN) {
                std::cout << "onIn" << std::endl;
                m_polling_clients[i]->onIn();
            }
            // onOut
            if(fds[i].revents & POLLOUT) {
                std::cout << "onOut" << std::endl;
                m_polling_clients[i]->onOut();
            }
            // onError
            if(fds[i].revents & POLLERR) {
                std::cout << "onErr" << std::endl;
                m_polling_clients[i]->onError();
            }
        }
    }
}



void EventManager::terminate()
{
    m_is_running = false;
}
