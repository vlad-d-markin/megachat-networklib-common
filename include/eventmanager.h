#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <iostream>
#include <sys/poll.h>


#include "interfaces/ipollingclient.h"
#include "exceptions/eventmanagerexception.h"


#define POLL_SIZE 230
#define POLL_TIMEOUT 2000



/**
 * @brief Event dispatcher
 */
class EventManager {
private:
    bool m_is_running;                                  ///< Event loop is running
    std::map<int, IPollingClient *> m_polling_clients;  ///< Objects to dispatch I/O events

public:
    EventManager();


    /**
     * @brief registerClient
     * @param client
     */
    void registerClient(IPollingClient * client);


    /**
     * @brief Remove PollingClient
     * @param client
     */
    void unregisterClient(IPollingClient * client);



    /**
     * @brief Run event loop
     */
    void execute();



    /**
     * @brief Terminate event loop
     */
    void terminate();
};

#endif
