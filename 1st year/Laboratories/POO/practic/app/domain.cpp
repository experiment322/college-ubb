#include "domain.h"

Task::Task(int id, std::string state, std::string description, std::vector<std::string> programmers)
    : id(id), state(state), description(description), programmers(programmers)
{
}

void Task::setId(int id)
{
    this->id = id;
}

int Task::getId()
{
    return id;
}

void Task::setState(std::string state)
{
    this->state = state;
}

std::string Task::getState()
{
    return state;
}

void Task::setDescription(std::string description)
{
    this->description = description;
}

std::string Task::getDescription()
{
    return description;
}

void Task::setProgrammers(std::vector<std::string> programmers)
{
    this->programmers = programmers;
}

std::vector<std::string> Task::getProgrammers()
{
    return programmers;
}
