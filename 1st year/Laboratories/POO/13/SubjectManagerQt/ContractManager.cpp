#include "ContractManager.h"

ContractManager::~ContractManager()
{
    // dummy
}

List<Subject> ContractManager::getSubjects()
{
    return subjects;
}

bool ContractManager::addSubject(std::string name)
{
    for (auto s : service.getAll())
    {
        if (name == s.getName())
        {
            subjects.push_back(s);
            Notify();
            return true;
        }
    }
    return false;
}

bool ContractManager::removeSubject(std::string name)
{
    size_t index = 0;
    for (auto s : subjects)
    {
        if (name == s.getName())
        {
            subjects.swap(index, subjects.size() - 1);
            subjects.pop_back();
            Notify();
            return true;
        }
        ++index;
    }
    return false;
}

void ContractManager::generateContract(size_t subjectCount)
{
    List<Subject> pool = service.getAll();
    while (subjects.size() != 0)
    {
        subjects.pop_back();
    }
    while (subjectCount)
    {
        size_t index = size_t(rand()) % pool.size();
        subjects.push_back(pool[index]);
        --subjectCount;
    }
    Notify();
}
