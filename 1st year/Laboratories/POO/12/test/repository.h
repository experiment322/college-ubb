#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "domain.h"

using namespace std;

class FlightRepository
{
    vector<Flight> flights;
public:
    /**
     * @brief FlightRepository
     */
    FlightRepository();

    /**
     * @brief create
     * @param flight
     */
    void create(Flight flight);

    /**
     * @brief read
     * @return
     */
    vector<Flight> read();

    /**
     * @brief remove
     * @param id
     */
    void remove(int id);
};

class FlightRepositoryException
{
    string message;
public:
    /**
     * @brief FlightRepositoryException
     * @param Message
     */
    FlightRepositoryException(string Message) : message{ Message } {}

    /**
     * @brief getMessage
     * @return
     */
    string getMessage() { return message; }
};

#endif // REPOSITORY_H
