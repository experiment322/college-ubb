#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>

class Task
{

public:
    Task(int id, std::string state, std::string description, std::vector<std::string> programmers);

    void setId(int id);
    int getId();

    void setState(std::string state);
    std::string getState();

    void setDescription(std::string description);
    std::string getDescription();

    void setProgrammers(std::vector<std::string> programmers);
    std::vector<std::string> getProgrammers();

private:
    int id;
    std::string state;
    std::string description;
    std::vector<std::string> programmers;
};

#endif // DOMAIN_H
