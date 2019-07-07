#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>

using namespace std;

class Flight
{
    int id;
    int duration;
    int freeSeats;
    string departureCity;
    string arrivalCity;
public:
    Flight(int Id, int Duration, int FreeSeats, string DepartureCity, string ArrivalCity)
        : id{ Id },
          duration{ Duration },
          freeSeats{ FreeSeats },
          departureCity{ DepartureCity },
          arrivalCity{ ArrivalCity }
    {}

    int getId() { return id; }
    void setId(int Id) { id = Id; }

    int getDuration() { return duration; }
    void setDuration(int Duration) { duration = Duration; }

    int getFreeSeats() { return freeSeats; }
    void setFreeSeats(int FreeSeats) { freeSeats = FreeSeats; }

    string getDepartureCity() { return departureCity; }
    void setDepartureCity(string DepartureCity) { departureCity = DepartureCity; }

    string getArrivalCity() { return arrivalCity; }
    void setArrivalCity(string ArrivalCity) { arrivalCity = ArrivalCity; }

    string toString();
};

#endif // DOMAIN_H
