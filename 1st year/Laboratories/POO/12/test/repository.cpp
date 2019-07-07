#include "repository.h"

#include <fstream>
#include <vector>
#include <string>
#include "domain.h"

#define DBFILE "flights.txt"

using namespace std;

FlightRepository::FlightRepository()
{
    ifstream file(DBFILE);
    int id, duration, freeSeats;
    string departureCity, arrivalCity;
    while (!file.eof())
    {
        file >> id >> duration >> freeSeats >> departureCity >> arrivalCity;
        flights.push_back({ id, duration, freeSeats, departureCity, arrivalCity });
    }
    file.close();
}

void FlightRepository::create(Flight flight)
{
    if (flight.getArrivalCity() == flight.getDepartureCity())
        throw FlightRepositoryException("Orasul de pornire si cel de plecare coincid!");
    if (flight.getFreeSeats() < 1)
        throw FlightRepositoryException("Numarul de locuri libere trebuie sa fie cel putin 1!");
    for (auto f : flights)
    {
        if (flight.getId() == f.getId())
            throw FlightRepositoryException("Exista deja un zbor cu acest id!");
    }
    flights.push_back(flight);
    ofstream file(DBFILE, ios_base::app);
    file << flight.toString() << endl;
    file.close();
}

vector<Flight> FlightRepository::read()
{
    return flights;
}

void FlightRepository::remove(int id)
{
    char buffer[256];
    vector<string> lines;
    ifstream ifile(DBFILE);
    for (size_t i = 0; i < flights.size(); ++i)
    {
        ifile.getline(buffer, sizeof(buffer), '\n');
        if (flights[i].getId() == id)
        {
            flights.erase(flights.begin() + int(i));
        }
        else
        {
            lines.push_back(buffer);
        }
    }
    ifile.close();
    ofstream ofile(DBFILE);
    for (auto line : lines)
    {
        ofile << line << endl;
    }
    ofile.close();
}
