#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void OnNotify() = 0; // Pure virtual function for receiving notifications
};

#endif
