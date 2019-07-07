#include "Validator.h"

void SubjectValidator::validate(const Subject& p) {
    vector<string> msgs;
    if (p.getHperw() < 0) msgs.push_back("Ore pe saptamana negativ!!!");
    if (p.getHperw() > 60) msgs.push_back("Ore pe saptamana inuman!!!");
    if (p.getType().size() == 0) msgs.push_back("Tip vid!!!");
    if (p.getName().size() == 0) msgs.push_back("Nume vid!!!");
    if (p.getProfessor().size() == 0) msgs.push_back("Profesor vid!!!");
    if (msgs.size() > 0) {
        throw ValidateException(msgs);
    }
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
    for (const auto& msg : ex.msgs) {
        out << msg<< " ";
    }
    return out;
}
