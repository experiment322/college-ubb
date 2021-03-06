#pragma once
#include <string>
#include <iostream>

using namespace std;

class Subject {
    string name;
    string type;
    string professor;
    int hperw;

public:
    Subject(const string n, const string t, const string p, const int h):name{n},type{t},professor{p},hperw{h}{}

    string getName() const {
        return name;
    }

    string getType() const {
        return type;
    }
    string getProfessor() const {
        return professor;
    }

    int getHperw() const {
        return hperw;
    }
};

// /*
//Compara dupa nume
//returneaza true daca p1.nume e mai mic decat p2.nume
//*/
//bool cmpName(const Subject& p1, const Subject& p2);

/*
Compara dupa tip
returneaza true daca p1.tip e mai mic decat p2.tip
*/
bool cmpType(const Subject& p1, const Subject& p2);

/*
Compara dupa profesor
returneaza true daca p1.professor e mai mic decat p2.professor
*/
bool cmpProfessor(const Subject& p1, const Subject& p2);

// /*
//Compara dupa ore pe saptamana
//returneaza true daca p1.hperw e mai mic decat p2.hperw
//*/
//bool cmpHperw(const Subject& p1, const Subject& p2);
