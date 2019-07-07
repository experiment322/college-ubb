#include "MainWindow.h"
#include "Validator.h"
#include "SubjectRepo.h"
#include "SubjectManager.h"
#include "ContractManager.h"
#include <QApplication>

void adaugaCateva(SubjectManager& ctr) {
    ctr.addSubject("sport", "type1", "prof1", 10);
    ctr.addSubject("fizica", "type2", "prof2", 25);
    ctr.addSubject("mate", "type4", "prof4", 40);
    ctr.addSubject("geometrie", "type3", "prof3", 30);
}

void testAll() {
    testeRepo();
    testCtr();
}

int main(int argc, char** argv) {
    //    testAll();

    // Initialize backend
    SubjectRepo repository;
    SubjectValidator validator;
    SubjectManager service{ repository, validator };
    ContractManager manager{ service };
    adaugaCateva(service);

    // Initialize frontend
    QApplication a{ argc, argv };
    MainWindow w{ manager, service };
    w.show();

    // Run the GUI
    return a.exec();
}
