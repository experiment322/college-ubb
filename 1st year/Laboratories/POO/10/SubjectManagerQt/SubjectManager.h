#pragma once
#include "Subject.h"
#include "SubjectRepo.h"
#include "Validator.h"
#include "List.h"
#include "Observer.h"
#include <string>
#include <vector>
#include <functional>

using namespace std;

typedef bool(*MaiMicF)(const Subject&, const Subject&);

class SubjectManager : public Observable {
    SubjectRepo& rep;
    SubjectValidator& val;

    /**
     * @brief observers
     */
    List<Observer*> observers;

    /*
     Functie de sortare generala
     maiMicF - functie care compara 2 Subject, verifica daca are loc relatia mai mare
              - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
              - poate fi functie lambda (care nu capteaza nimic in capture list)
     returneaza o lista sortata dupa criteriu dat ca paramatru
    */
    List<Subject> generalSort(MaiMicF maiMicF)const;
    /*
    Functie generala de filtrare
    fct - poate fi o functie
    fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
    returneaza doar disciplinele care trec de filtru (fct(subject)==true)
    */
    List<Subject> filtreaza(function<bool(const Subject&)> fct)const;
public:
    SubjectManager(SubjectRepo& rep, SubjectValidator& val) noexcept : rep{ rep }, val{ val } {}

    SubjectManager(const SubjectManager& ot) = delete;

    ~SubjectManager();

    void Attach(Observer* observer) {
        size_t i = 0;
        for (Observer* o : observers) {
            if (o == observer) break;
            ++i;
        }
        if (i != observers.size()) return;
        observers.push_back(observer);
    }

    void Detach(Observer* observer) {
        size_t i = 0;
        for (Observer* o : observers) {
            if (o == observer) break;
            ++i;
        }
        if (i == observers.size()) return;
        observers.swap(i, observers.size() - 1);
        observers.pop_back();
    }

    void Notify() {
        for (Observer* o : observers) {
            o->Update();
        }
    }

    /*
     returneaza toate disciplinele in ordinea in care au fost adaugate
    */
    const List<Subject>& getAll() const noexcept{
        return rep.getAll();
    }

    /*
    Adauga o noua disciplina
    arunca exceptie daca: nu se poate salva, nu este valid
    */
    void addSubject(const string& name, const string& type, const string& professor, int hperw);

    /*
    Modifica o disciplina existenta
    arunca exceptie daca: nu exista, nu este valida
    */
    void updateSubject(const string& name, const string& type, const string& professor, int hperw);

    /*
    Sterge o disciplina
    arunca exceptie daca: nu exista
    */
    void removeSubject(const string& name);

    /*
    Sorteaza dupa nume
     */
    List<Subject> sortByName() const;

    /*
    Sorteaza dupa tip
    */
    List<Subject> sortByType() const;

    /*
    Sorteaza dupa profesor
    */
    List<Subject> sortByProfessor() const;

    /*
    Sorteaza dupa hours/week
    */
    List<Subject> sortByHperw() const;

    /*
    Sorteaza dupa profesor+tip
    */
    List<Subject> sortByProfessorType() const;

    /*
    returneaza doar disciplinele cu hperw mai mic decat cel dat
    */
    List<Subject> filtrareHperw(int hperw) const;

    /*
    returneaza doar disciplinele cu acest profesor
    */
    List<Subject> filtrareProfessor(const string& professor) const;
};

void testCtr();
