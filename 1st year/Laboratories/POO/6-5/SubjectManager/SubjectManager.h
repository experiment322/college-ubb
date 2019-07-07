#pragma once
#include "Subject.h"
#include "SubjectRepo.h"
#include "Validator.h"
#include "List.h"
#include <string>
#include <vector>
#include <functional>

using namespace std;

typedef bool(*MaiMicF)(const Subject&, const Subject&);

class SubjectManager {
    SubjectRepo& rep;
    SubjectValidator& val;

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
    SubjectManager(SubjectRepo& rep, SubjectValidator& val) noexcept:rep{ rep }, val{ val } {
    }
    //nu permitem copierea de obiecte SubjectManager
    SubjectManager(const SubjectManager& ot) = delete;
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
    Sorteaza dupa tip
    */
    List<Subject> sortByType()const;

    /*
    Sorteaza dupa profesor
    */
    List<Subject> sortByProfessor()const;


    /*
    Sorteaza dupa profesor+tip
    */
    List<Subject> sortByProfessorType() const;

    /*
    returneaza doar disciplinele cu hperw mai mic decat cel dat
    */
    List<Subject> filtrareHperwMaiMic(int hperw)const;

    /*
    returneaza doar disciplinele cu hperw intre cele doua valori
    */
    List<Subject> filtrareHperw(int hperwMin, int hperwMax)const;

};
void testCtr();
