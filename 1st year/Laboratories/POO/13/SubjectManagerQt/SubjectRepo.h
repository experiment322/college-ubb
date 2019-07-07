#pragma once
#include "Subject.h"
#include "List.h"
#include <vector>
#include <string>

using namespace std;

class SubjectRepo {
    List<Subject> all;
    /*
    metoda privata verifica daca exista deja p in repository
    */
    bool exist(const Subject& p);
public:
    SubjectRepo() = default;
    //nu permitem copierea de obiecte
    SubjectRepo(const SubjectRepo& ot) = delete;
    /*
    Salvare disciplina
    arunca exceptie daca mai exista o disciplina cu acelasi nume
    */
    void store(const Subject& p);

    /*
    Stergere disciplina
    arunca exceptie daca nu exista
    */
    void remove(const string& name);

    /*
    Cauta
    arunca exceptie daca nu exista disciplina
    */
    Subject& find(const string& name) const;

    /*
    returneaza toate disciplinele salvate
    */
    List<Subject> getAll() const noexcept;

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class SubjectRepoException {
    string msg;
public:
    SubjectRepoException(string m) :msg{ m } {}
    const string& getError() const { return msg; }
    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const SubjectRepoException& ex);
};

ostream& operator<<(ostream& out, const SubjectRepoException& ex);

void testeRepo();
