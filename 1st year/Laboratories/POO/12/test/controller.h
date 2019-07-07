#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include "domain.h"
#include "repository.h"

using namespace std;

class FlightController
{
    FlightRepository& repository;
public:
    /**
     * @brief FlightController
     * @param Repository
     */
    FlightController(FlightRepository& Repository) : repository{ Repository } {}

    /**
     * @brief addFlight
     * @param id
     * @param duration
     * @param freeSeats
     * @param departureCity
     * @param arrivalCity
     */
    void addFlight(int id, int duration, int freeSeats, string departureCity, string arrivalCity);

    /**
     * @brief deleteFlightsByDepartureCity
     * @param departureCity
     */
    void deleteFlightsByDepartureCity(string departureCity);

    /**
     * @brief getAllFlightsWithDurationLessThan
     * @param duration
     * @return
     */
    vector<Flight> getAllFlightsWithDurationLessThan(int duration);
};

#endif // CONTROLLER_H
