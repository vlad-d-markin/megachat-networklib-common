#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>


#include <interfaces/ipollingclient.h>


class EventManager {
private:
    bool m_is_running;
    std::map<int, IPollingClient *> m_polling_clients;

public:
    EventManager();

    void registerClient(IPollingClient * client);


    void unregisterClient(IPollingClient * client);


    void execute();


    void terminate();
};

#endif
