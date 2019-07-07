#include "controller.h"

#include <string>
#include <vector>
#include "domain.h"

using namespace std;

void FlightController::addFlight(int id, int duration, int freeSeats, string departureCity, string arrivalCity)
{
    repository.create({ id, duration, freeSeats, departureCity, arrivalCity });
}

void FlightController::deleteFlightsByDepartureCity(string departureCity)
{
    vector<Flight> flights = repository.read();
    for (auto f : flights)
    {
        if (f.getDepartureCity() == departureCity)
        {
            repository.remove(f.getId());
        }
    }
}

vector<Flight> FlightController::getAllFlightsWithDurationLessThan(int duration)
{
    vector<Flight> result;
    vector<Flight> flights = repository.read();
    for (auto f : flights)
    {
        if (f.getDuration() < duration)
        {
            result.push_back(f);
        }
    }
    return result;
}
