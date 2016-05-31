#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <iostream>
#include <sys/poll.h>

#include <interfaces/ipollingclient.h>
#include <exceptions/eventmanagerexception.h>


#define POLL_SIZE 230
#define POLL_TIMEOUT 2000

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
