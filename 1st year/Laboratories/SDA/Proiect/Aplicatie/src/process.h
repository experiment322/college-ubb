#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

struct Process
{
    // Fields
    std::string name;
    int cpu_usage;
    int run_time;

    // Methods
    bool operator==(const Process& other) const { return name == other.name; }

    bool operator!=(const Process& other) const { return !operator==(other); }

    bool operator<(const Process& other) const { return cpu_usage < other.cpu_usage; }

    bool operator>=(const Process& other) const { return !operator<(other); }

    bool operator>(const Process& other) const { return cpu_usage > other.cpu_usage; }

    bool operator<=(const Process& other) const { return !operator>(other); }
};

// overload >> for reading from file
std::istream& operator>>(std::istream& stream, Process& process)
{
    stream >> process.name >> process.cpu_usage >> process.run_time;
    return stream;
}

#endif // PROCESS_H
