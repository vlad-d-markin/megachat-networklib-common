#include <eventmanager.h>


EventManager::EventManager()
{
    m_is_running = false;
}



void EventManager::registerClient(IPollingClient *client)
{
    m_polling_clients.insert(std::pair<int, IPollingClient *>(client->getSocket(), client));
}



void EventManager::unregisterClient(IPollingClient *client)
{
    m_polling_clients.erase(client->getSocket());
}



void EventManager::execute()
{
    m_is_running = true;

    while(m_is_running) {

    }
}



void EventManager::terminate()
{
    m_is_running = false;
}
