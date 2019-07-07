#pragma once
#include "Subject.h"
#include <string>
#include <vector>

using namespace std;

class ValidateException {
    vector<string> msgs;
public:
    ValidateException(const vector<string>& errors) : msgs{ errors } {}
    const vector<string>& getErrors() const { return msgs; }
    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class SubjectValidator {
public:
    void validate(const Subject& p);
};
