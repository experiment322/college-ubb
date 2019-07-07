#include "SubjectRepo.h"
#include <assert.h>

void SubjectRepo::store(const Subject& p)
{
    if (exist(p)) {
        throw SubjectRepoException("Exista deja disciplina: " + p.getName());
    }
    all.push_back(p);
}

bool SubjectRepo::exist(const Subject& p) {
    try {
        find(p.getName());
        return true;
    }
    catch (SubjectRepoException& ) {
        return false;
    }
}
/*
Cauta
arunca exceptie daca nu exista disciplina
*/
Subject SubjectRepo::find(const string& name) const{
    for (const Subject& p : all) {
        if (p.getName() == name) {
            return p;
        }
    }
    //daca nu exista arunc o exceptie
    throw SubjectRepoException("Nu exista disciplina tip: " + name);
}

/*
returneaza toate disciplinele salvate
*/
const List<Subject>& SubjectRepo::getAll() const noexcept{
    return all;
}


ostream& operator<<(ostream& out, const SubjectRepoException& ex) {
    out << ex.msg;
    return out;
}




void testAdauga() {
    bool didCatch;
    SubjectRepo rep;
    rep.store(Subject{ "a","b","c",4 });
    assert(rep.getAll().size() == 1);
    assert(rep.find("a").getName() == "a");

    rep.store(Subject{ "aa","bb","cc",4 });
    assert(rep.getAll().size() == 2);

    //nu pot adauga 2 cu acelasi nume
    try {
        didCatch = false;
        rep.store(Subject{ "a","a","a",4 });
    }
    catch (SubjectRepoException&) {
        didCatch = true;
    }
    assert(didCatch);
}

void testCauta() {
    bool didCatch;
    SubjectRepo rep;
    rep.store(Subject{ "a","b","c",4 });
    rep.store(Subject{ "aa","bb","cc",4 });

    auto p = rep.find("a");
    assert(p.getName() == "a");

    //arunca exceptie daca nu gaseste
    try {
        didCatch = false;
        rep.find("aaa");
    }
    catch (SubjectRepoException&) {
        didCatch = true;
    }
    assert(didCatch);
}

void testeRepo() {
    testAdauga();
    testCauta();
    cout << SubjectRepoException{"testing exception printer"} << "\n";
}
