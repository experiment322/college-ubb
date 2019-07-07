#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual ~Observer();
    virtual void Update() = 0;
};

class Observable
{
public:
    virtual ~Observable();
    virtual void Notify() = 0;
    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
};

#endif // OBSERVER_H
