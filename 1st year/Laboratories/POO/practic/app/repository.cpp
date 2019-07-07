#include "repository.h"

#include <fstream>

Repository::Repository()
{
    repoFile = "repo.txt";
    loadFromFile();
    reorder();
}

void Repository::add(Task task)
{
    items.push_back(task);
    dumpToFile();
    reorder();
}

std::vector<Task> Repository::getAll()
{
    return items;
}

void Repository::reorder()
{
    std::sort(items.begin(), items.end(), [](Task a, Task b) { return a.getState() < b.getState(); });
}

void Repository::dumpToFile()
{
    std::ofstream file(repoFile);
    for (auto t : items)
    {
        file << t.getId() << std::endl;
        file << t.getDescription() << std::endl;
        for (auto p : t.getProgrammers())
        {
            file << p << " ";
        }
        file << std::endl;
        file << t.getState() << std::endl;
    }
    file.close();
}

void Repository::loadFromFile()
{
    std::ifstream file(repoFile);
    while (!file.eof())
    {
        std::string idBuffer;
        std::getline(file, idBuffer);
        if (idBuffer.empty()) break;
        std::string descriptionBuffer;
        std::getline(file, descriptionBuffer);
        std::string programmersBuffer;
        std::getline(file, programmersBuffer);
        std::string stateBuffer;
        std::getline(file, stateBuffer);
        std::vector<std::string> programmers;
        while (!programmersBuffer.empty())
        {
            std::string programmer = programmersBuffer.substr(0, programmersBuffer.find(' '));
            programmersBuffer.replace(
                        programmersBuffer.begin(),
                        programmersBuffer.begin() + int(programmer.size()) + 1,
                        "");
            programmers.push_back(programmer);
        }
        items.push_back(Task(std::stoi(idBuffer), stateBuffer, descriptionBuffer, programmers));
    }
    file.close();
}
