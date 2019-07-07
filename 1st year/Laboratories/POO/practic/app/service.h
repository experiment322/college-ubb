#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include <string>
#include "repository.h"
#include "domain.h"

class Service
{

public:
    Service(Repository& repository);

    std::vector<Task> getAll();

    std::string add(int id, std::string description, std::string state, std::string programmers);

private:
    Repository& repository;
};

#endif // SERVICE_H
