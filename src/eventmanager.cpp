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
        int i = 0;
        for(auto it = m_polling_clients.begin(); it != m_polling_clients.end(); it++) {
            IPollingClient * client = it->second;

            fds[i].fd = client->getSocket();
            fds[i].events = POLLIN | POLLERR;

            if(client->isPollingOut())
                fds[i].events = fds[i].events | POLLOUT;

            i++;
        }

        // Poll
        int result = poll(fds, m_polling_clients.size(), POLL_TIMEOUT);

        // Timeout
        if(result == 0) {
            continue;
        }

        if(result < 0) {
            throw EventManagerException("Poll failed", errno);
        }

        // Dispatch events
        for(i = 0; i < m_polling_clients.size(); i++) {
            // No events
            if(fds[i].revents == 0)
                continue;

            // onIn
            if(fds[i].revents & POLLIN) {
                m_polling_clients[fds[i].fd]->onIn();
            }
            // onOut
            if(fds[i].revents & POLLOUT) {
                m_polling_clients[fds[i].fd]->onOut();
            }
            // onError
            if(fds[i].revents & POLLERR) {
                m_polling_clients[fds[i].fd]->onError();
            }
        }
    }
}



void EventManager::terminate()
{
    m_is_running = false;
}
