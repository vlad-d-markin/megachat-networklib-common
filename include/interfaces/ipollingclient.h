#ifndef IPOLLINGCLIENT_H
#define IPOLLINGCLIENT_H

class IPollingClient {
public:
    virtual void onIn() = 0;


    virtual void onOut() = 0;


    virtual void onError() = 0;


    virtual int getSocket() = 0;


    virtual bool isPollingOut() = 0;
};

#endif
