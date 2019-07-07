#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "process.h"
#include "orderedlist.h"

OrderedList<Process> remove_finished_processes(OrderedList<Process>& process_list)
{
    // find the shortest life of a process in the given process list
    int min_run_time = INT_MAX;
    for (auto it = process_list.iterator(); it.valid(); it.next())
    {
        Process process = it.element();
        if (process.run_time < min_run_time)
        {
            min_run_time = process.run_time;
        }
    }

    // create two lists, one with the finished processes
    // and one with the remaining processes and with their updated run time
    OrderedList<Process> finished_processes(process_list.length());
    OrderedList<Process> unfinished_processes(process_list.length());
    for (auto it = process_list.iterator(); it.valid(); it.next())
    {
        Process process = it.element();
        if (process.run_time > min_run_time)
        {
            process.run_time -= min_run_time;
            unfinished_processes.insert(process);
        }
        else
        {
            finished_processes.insert(process);
        }
    }

    // empty the old process list
    while (!process_list.empty())
    {
        process_list.remove(0);
    }

    // then insert the remaining processes with their remaining run time
    for (auto it = unfinished_processes.iterator(); it.valid(); it.next())
    {
        Process process = it.element();
        process_list.insert(process);
    }

    // return the list of the finished processes
    return finished_processes;
}

void update_system_status(OrderedList<Process>& finished_processes, int& run_time, int& cpu_usage)
{
    // update the cpu usage after process removal
    int total_cpu_usage = 0;
    for (auto it = finished_processes.iterator(); it.valid(); it.next())
    {
        Process process = it.element();
        total_cpu_usage += process.cpu_usage;
    }
    cpu_usage -= total_cpu_usage;

    // update the running time of the system
    int min_run_time = finished_processes.at(0).run_time;
    run_time += min_run_time;
}

int main()
{
    int run_time = 0;
    int cpu_usage = 0;
    std::string target_process_name = "";
    OrderedList<Process> process_list(100);
    OrderedList<Process> process_queue(1024);

    // read processes from file
    std::ifstream infile("processes.txt");
    infile >> target_process_name;
    while (!infile.eof() && process_queue.length() != 1024)
    {
        Process process;
        infile >> process;
        process_queue.insert(process);
    }
    infile.close();

    // simulate the execution of the processes
    while (process_queue.length())
    {
        Process process = process_queue.remove(0);
        while (cpu_usage + process.cpu_usage > 100)
        {
            OrderedList<Process> finished_processes = remove_finished_processes(process_list);
            update_system_status(finished_processes, run_time, cpu_usage);
        }
        if (process.name != target_process_name)
        {
            process_list.insert(process);
            cpu_usage += process.cpu_usage;
        }
        else
        {
            break; // the target process was found
        }
    }

    // print the result
    std::cout
            << "The process '"
            << target_process_name
            << "' began execution after "
            << run_time
            << " units of time."
            << std::endl;

    OrderedList<int> test(10);
    test.insert(4);
    test.insert(1);
    test.insert(3);
    test.insert(2);
    test.insert(5);

    std::cout << std::endl;
    auto it1 = test.iterator();
    while (it1.valid())
    {
        std::cout << it1.element() << std::endl;
        if (it1.element() == 3)
        {
            it1.remove();
        }
        it1.next();
    }

    std::cout << std::endl;
    auto it2 = test.iterator();
    while (it2.valid())
    {
        std::cout << it2.element() << std::endl;
        it2.next();
    }

    return 0;

}
