#include "Subject.h"

bool cmpName(const Subject& p1, const Subject& p2) {
    return p1.getName() < p2.getName();
}

bool cmpType(const Subject& p1, const Subject& p2) {
    return p1.getType() < p2.getType();
}

bool cmpProfessor(const Subject& p1, const Subject& p2) {
    return p1.getProfessor() < p2.getProfessor();
}

bool cmpHperw(const Subject& p1, const Subject& p2) {
    return p1.getHperw() < p2.getHperw();
}
