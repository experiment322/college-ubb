#include "service.h"

#include <algorithm>

Service::Service(Repository& repository) : repository(repository)
{
}

std::vector<Task> Service::getAll()
{
    return repository.getAll();
}

std::string Service::add(int id, std::string description, std::string state, std::string programmersBuffer)
{
    for (auto t : repository.getAll())
        if (t.getId() == id) return "Tasks exists!";
    if (!description.size()) return "Empty description!";
    if (state != "open" && state != "inprogress" && state != "closed") return "Invalid state!";
    if (!programmersBuffer.size()) return "No programmers!";
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
    if (programmers.size() > 4) return "Too many programmers!";
    repository.add(Task(id, state, description, programmers));
    return "";
}
