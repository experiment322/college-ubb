#include "SubjectManager.h"
#include <functional>
#include <algorithm>
#include <assert.h>

using namespace std;

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


//    return generalSort([](const Subject&p1, const Subject&p2) {
//        return p1.getProfessor() < p2.getProfessor();
//    });
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

List<Subject> SubjectManager::filtrareHperwMaiMic(int hperw) const {
    return filtreaza([hperw](const Subject& p)noexcept {
        return p.getHperw() < hperw;
    });
}

List<Subject> SubjectManager::filtrareHperw(int hperwMin, int hperwMax)const {

    return filtreaza([=](const Subject& subject) noexcept {
        return subject.getHperw() >= hperwMin && subject.getHperw() <= hperwMax;
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
    assert(ctr.filtrareHperw(6, 70).size() == 3);
    assert(ctr.filtrareHperw(6, 50).size() == 2);
    assert(ctr.filtrareHperwMaiMic(60).size() == 2);
    assert(ctr.filtrareHperwMaiMic(7).size() == 1);
    assert(ctr.filtrareHperwMaiMic(6).size() == 0);
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
