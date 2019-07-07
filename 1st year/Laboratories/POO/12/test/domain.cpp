#include "domain.h"

#include <string>

using namespace std;

string Flight::toString()
{
    return std::to_string(id) + " "
            + std::to_string(duration) + " "
            + std::to_string(freeSeats) + " "
            + departureCity + " " + arrivalCity;
}
