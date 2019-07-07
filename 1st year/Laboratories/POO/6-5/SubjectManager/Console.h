#pragma once
#include "List.h"
#include "Subject.h"
#include "SubjectManager.h"

class ConsoleUI {
    SubjectManager& ctr;
    /*
    Citeste datele de la tastatura si adauga Subject
    arunca exceptie daca: nu se poate salva, nu e valid
    */
    void adaugaUI();
    /*
    Tipareste o lista de discipline la consola
    */
    void tipareste(const List<Subject>& subjects);
public:
    ConsoleUI(SubjectManager& ctr) noexcept:ctr{ ctr } {
    }
    //nu permitem copierea obiectelor
    ConsoleUI(const ConsoleUI& ot) = delete;

    void start();
};
