#include "Console.h"
#include <iostream>
#include <string>

using namespace std;

void ConsoleUI::tipareste(const List<Subject>& subjects) {
    cout << "Discipline:\n";
    for (const Subject& s : subjects) {
        cout << s.getName() << ' ' << s.getType() << ' ' << s.getProfessor() << ' ' << s.getHperw() << '\n';
    }
    cout << "Sfarsit lista discipline\n";
}

void ConsoleUI::adaugaUI() {
    string name, ty, pf;
    int hperw;
    cout << "Dati nume:";
    cin >> name;
    cout << "Dati tip:";
    cin >> ty;
    cout << "Dati profesor:";
    cin >> pf;
    cout << "Dati ore pe saptamana:";
    cin >> hperw;
    ctr.addSubject(name, ty, pf, hperw);
    cout << "Adaugat cu succes\n";
}

void ConsoleUI::start() {
    while (true) {
        cout << "Meniu:\n";
        cout << "1 adauga\n2 tipareste\n3 sort by type\n4 sort by professor\n5 sort by professor+type\n6 filtrare ore pe saptamana\n7 Filtrare ore pe saptamana min max\n0 Iesire\nDati comanda:";
        int cmd;
        cin >> cmd;
        try {
            switch (cmd) {
            case 1:
                adaugaUI();
                break;
            case 2:
                tipareste(ctr.getAll());
                break;
            case 3:
                tipareste(ctr.sortByType());
                break;
            case 4:
                tipareste(ctr.sortByProfessor());
                break;
            case 5:
                tipareste(ctr.sortByProfessorType());
                break;
            case 6:
                cout << "Dati ore pe saptamana maxim:";
                int hperw;
                cin >> hperw;
                tipareste(ctr.filtrareHperwMaiMic(hperw));
                break;
            case 7:
                cout << "Dati ore pe saptamana minim:";
                int hperwMin;
                cin >> hperwMin;
                cout << "Dati ore pe saptamana maxim:";
                int hperwMax;
                cin >> hperwMax;
                tipareste(ctr.filtrareHperw(hperwMin,hperwMax));
                break;
            case 0:
                return;
            default:
                cout << "Comanda invalida\n";
            }
        }
        catch (SubjectRepoException& ex) {
            cout << ex <<'\n';
        }
        catch (ValidateException& ex) {
            cout << ex << '\n';
        }
    }
}
