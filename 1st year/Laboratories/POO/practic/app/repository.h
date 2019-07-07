#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <algorithm>
#include "domain.h"

class Repository
{

public:
    Repository();

    void add(Task task);

    std::vector<Task> getAll();

private:
    std::string repoFile;
    std::vector<Task> items;

    void reorder();
    void dumpToFile();
    void loadFromFile();
};

#endif // REPOSITORY_H
