#ifndef CONTRACTMANAGER_H
#define CONTRACTMANAGER_H

#include <string>
#include <ctime>
#include <cstdlib>

#include "List.h"
#include "Observer.h"
#include "Subject.h"
#include "SubjectManager.h"

class ContractManager : public Observable
{
    friend class SubjectListModel;
private:
    List<Subject> subjects;
    SubjectManager& service;
    List<Observer*> observers;
public:
    ContractManager(SubjectManager& service) : service{ service }
    {
        srand(unsigned(time(nullptr)));
    }

    ~ContractManager();

    List<Subject> getSubjects();

    bool addSubject(std::string name);

    bool removeSubject(std::string name);

    void generateContract(size_t subjectCount);

    // Observable interface implementation
    void Attach(Observer* observer)
    {
        for (Observer* o : observers)
        {
            if (o == observer)
            {
                return;
            }
        }
        observers.push_back(observer);
    }

    void Detach(Observer* observer)
    {
        size_t i = 0;
        for (Observer* o : observers)
        {
            if (o == observer)
            {
                observers.swap(i, observers.size() - 1);
                observers.pop_back();
                return;
            }
            ++i;
        }
    }

    void Notify()
    {
        for (Observer* o : observers)
        {
            o->Update();
        }
    }
};

#endif // CONTRACTMANAGER_H
