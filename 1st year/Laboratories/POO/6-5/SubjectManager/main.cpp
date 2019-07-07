#include "Console.h"
#include "SubjectManager.h"
#include "SubjectRepo.h"
#include "Validator.h"

void adaugaCateva(SubjectManager& ctr) {
    ctr.addSubject("a", "zz", "yy", 10);
    ctr.addSubject("b", "aa", "dd", 40);
    ctr.addSubject("z", "cc", "ll", 25);
    ctr.addSubject("c", "bb", "ll", 30);
}

void testAll() {
    testeRepo();
    testCtr();
}

int main() {
//    testAll();

    SubjectRepo rep;
    SubjectValidator val;
    SubjectManager ctr{ rep,val };
    adaugaCateva(ctr);//adaug cateva animale
    ConsoleUI ui{ ctr };
    ui.start();
}
