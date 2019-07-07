#include "SubjectManager.h"
#include <functional>
#include <algorithm>
#include <assert.h>

using namespace std;

SubjectManager::~SubjectManager() {}

List<Subject> SubjectManager::generalSort(MaiMicF maiMicF) const {
    List<Subject> v{ rep.getAll() }; //fac o copie
    //sort(v.begin(), v.end(), maiMicF);
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {
                //interschimbam
                v.swap(i, j);
            }
        }
    }
    return v;
}

/*
Adauga un nou subject
arunca exceptie daca: nu se poate salva, nu este valid
*/
void SubjectManager::addSubject(const string& name, const string& type, const string& professor, int hperw) {
    Subject p{ name,type,professor,hperw };
    val.validate(p);
    rep.store(p);
    Notify();
}

/*
Modifica o disciplina existenta
arunca exceptie daca: nu exista, nu este valida
*/
void SubjectManager::updateSubject(const string& name, const string& type, const string& professor, int hperw) {
    Subject& p = rep.find(name);
    val.validate({name, type, professor, hperw});
    p.setType(type);
    p.setHperw(hperw);
    p.setProfessor(professor);
    Notify();
}

/*
Sterge o disciplina
arunca exceptie daca: nu exista
*/
void SubjectManager::removeSubject(const string& name) {
    rep.remove(name);
    Notify();
}

/*
Sorteaza dupa nume
 */
List<Subject> SubjectManager::sortByName() const {
    return generalSort(cmpName);
}

/*
Sorteaza dupa tip
*/
List<Subject> SubjectManager::sortByType()const {
    return generalSort(cmpType);
}

/*
Sorteaza dupa profesor
*/
List<Subject> SubjectManager::sortByProfessor()const {
    return generalSort(cmpProfessor);
}

/*
Sorteaza dupa hours/week
*/
List<Subject> SubjectManager::sortByHperw() const {
    return generalSort(cmpHperw);
}

/*
Sorteaza dupa profesor+tip
*/
List<Subject> SubjectManager::sortByProfessorType() const {
    return generalSort([](const Subject&p1, const Subject&p2) {
        if (p1.getProfessor() == p2.getProfessor()) {
            return p1.getType() < p2.getType();
        }
        return p1.getProfessor() < p2.getProfessor();
    });
}

List<Subject> SubjectManager::filtreaza(function<bool(const Subject&)> fct) const {
    List<Subject> rez;
    for (const Subject& subject : rep.getAll()) {
        if (fct(subject)) {
            rez.push_back(subject);
        }
    }
    return rez;
}

List<Subject> SubjectManager::filtrareHperw(int hperw) const {
    return filtreaza([hperw](const Subject& subject) noexcept {
        return subject.getHperw() < hperw;
    });
}

List<Subject> SubjectManager::filtrareProfessor(const string& professor) const {
    return filtreaza([professor](const Subject& subject) noexcept {
        return subject.getProfessor() == professor;
    });
}


void testAdaugaCtr() {
    bool didCatch;
    SubjectRepo rep;
    SubjectValidator val;
    SubjectManager ctr{ rep,val };
    ctr.addSubject("a", "b", "c", 6);
    assert(ctr.getAll().size() == 1);

    //adaug ceva invalid
    try {
        didCatch = false;
        ctr.addSubject("", "", "", -1);
    }
    catch (ValidateException&) {
        didCatch = true;
    }
    assert(didCatch);
    //incerc sa adaug ceva ce existadeja
    try {
        didCatch = false;
        ctr.addSubject("a", "c", "b", -1);
    }
    catch (ValidateException&) {
        didCatch = true;
    }
    assert(didCatch);
}

void testFiltrare() {
    SubjectRepo rep;
    SubjectValidator val;
    SubjectManager ctr{ rep,val };
    ctr.addSubject("a", "a", "a", 6);
    ctr.addSubject("b", "a", "a", 30);
    ctr.addSubject("c", "a", "a", 60);
    assert(ctr.filtrareHperw(60).size() == 2);
    assert(ctr.filtrareHperw(7).size() == 1);
    assert(ctr.filtrareHperw(6).size() == 0);
}

void testSortare() {
    SubjectRepo rep;
    SubjectValidator val;
    SubjectManager ctr{ rep,val };
    ctr.addSubject("y", "y", "z", 6);
    ctr.addSubject("z", "z", "z", 6);
    ctr.addSubject("b", "a", "d", 30);
    ctr.addSubject("c", "a", "e", 60);

    auto firstP = ctr.sortByType()[0];
    assert(firstP.getType() == "a");

    firstP = ctr.sortByProfessor()[0];
    assert(firstP.getProfessor() == "d");

    firstP = ctr.sortByProfessorType()[0];
    assert(firstP.getProfessor() == "d");

}

void testCtr() {
    testAdaugaCtr();
    testFiltrare();
    testSortare();
    cout << ValidateException{{"testing exception printer", "for validator"}} << "\n";
}
