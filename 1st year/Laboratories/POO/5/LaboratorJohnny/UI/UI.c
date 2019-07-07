#include <stdlib.h>
#include <stdio.h>
#include "UI.h"
#include <stdlib.h>
#include <string.h>
#include "../Domain/Medicine/MedicineValidator.h"


UI* createUI(MedicineService* medicineService) {
    UI* ui = (UI*) malloc(sizeof(UI));
    ui->medicineService = medicineService;
    return ui;
}

void destroyUI(UI* ui) {
    destroyMedicineService(ui->medicineService);
    free(ui);
}

int readNumber(char * msg, int* no)  {
    printf("%s", msg);

    int returnValue = scanf("%d", no);
    if (returnValue == 0) {
        while(getchar() != '\n');
        return 1;
    }

    return 0;
}

int readType(char * msg, int* type)  {
    printf("%s", msg);
    int code = scanf("%d", type);
    if(code == 0) {
        while(getchar() != '\n');
        return 1;
    }

    if((*type) == 0 || (*type) == 1) return 0;

    return 1;
}

void readString(char * msg, char* str, int size) {
    char dummy;
    scanf("%c", &dummy);
    printf("%s", msg);
    fgets(str, size, stdin);
    ungetc('\n', stdin);
    str[strcspn(str, "\n")] = 0;
}

void readChar(char * msg, char* chr) {
    printf("%s", msg);
    // keep the space, it deletes rogue whitespace in buffer
    scanf(" %c", chr);
}

void printValidationErrors(int errors) {
    if(errors & CONCENTRATION_OUT_OF_BOUNDS) {
        printf("Eroare! Concentratia trebuie sa fie intre 0 si 100!\n");
    }
    if(errors & EMPTY_NAME) {
        printf("Eroare! Numele nu poate sa fie go! \n");
    }
    if(errors & NEGATIVE_QUANTITY) {
        printf("Eroare! Cantitatea nu poate fi negativa! \n");
    }
}

void printMedicine(Medicine* medicine) {
    printf("{ Id: %d, Nume: '%s', Concentratie: %d%%, Cantitate: %d }",
           getMedicineId(medicine),
           getMedicineName(medicine),
           getMedicineConcentration(medicine),
           getMedicineQuantity(medicine)
    );
}

void printMedicineList(List* list) {
    Medicine* medicine;
    for(int i=0; i < getListSize(list); i++) {
        medicine = getAtListIndex(list, i);
        printMedicine(medicine);
        printf(",");
    }
    printf("\n");
}

void addMedicineUI(UI* ui) {
    int id, concentration, quantity;
    char name[100];

    int errId = readNumber("Introduceti id-ul:", &id);
    if(errId) {
        printf("Id-ul nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    readString("Introduceti numele:", name, 100 * sizeof(char));

    int errConcentration = readNumber("Introduceti concentratia ca un numar intre 0 si 100:", &concentration);

    if(errConcentration) {
        printf("Concentratia nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    int errQuantity = readNumber("Introduceti cantitatea ca un numar pozitiv:", &quantity);

    if(errQuantity) {
        printf("Cantitatea nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }

    int created = addMedicineService(ui->medicineService, id, name, concentration, quantity);

    if(created < 0) {
        printf("Medicamentul a fost creat!");
    } else if(created == 0) {
        printf("Un produs cu id-ul dat exista deja! Cantitatea lui a fost actualizata!");
    } else if(created > 0) {
        //validation errors
        printValidationErrors(created);
    }
}

void updateMedicineUI(UI* ui) {
    int id, concentration;
    char name[100];

    int errId = readNumber("Introduceti id-ul:", &id);
    if(errId) {
        printf("Id-ul nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    readString("Introduceti numele:", name, 100*sizeof(char));

    int errConcentration = readNumber("Introduceti concentratia ca un numar intre 0 si 100:", &concentration);
    if(errConcentration) {
        printf("Concentratia nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }

    int updated = updateMedicineService(ui->medicineService, id, name, concentration);

    if(updated < 0) {
        printf("Medicamentul a fost actualizat cu succes!");
    } else if(updated == 0) {
        printf("Nu exista un produs cu id-ul dat!");
    } else {
        // validation errors
        printValidationErrors(updated);
    }
}

void deleteStockUI(UI* ui) {
    int id;
    int errQuantity = readNumber("Introduceti id-ul medicamentului asupra caruia se sterge stock-ul:", &id);
    if(errQuantity) {
        printf("Cantitatea nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    int erased = eraseQuantityForMedicineService(ui->medicineService, id);
    if(erased) {
        printf("Stocul a fost sters!");
    } else {
        printf("Nu exista un produs cu id-ul dat!");
    }

}

void viewSortedByQuantity(UI* ui) {
    int type = 0;
    int errType = readType("Introduceti tipul sortarii: asc - 0 sau desc - 1:", &type);
    if(errType) {
        printf("Se accepta doar valorile de 0 (asc) si 1 (desc)!\n");
        return;
    }
    List* list = getAllMedicineSortedByQuantityService(ui->medicineService, type);

    if(getListSize(list) == 0) {
        printf("Nu exista date!");
    } else {
        printMedicineList(list);
    }

    destroyList(list);
}

void viewSortedByName(UI* ui) {
    int type = 0;
    int errType = readType("Introduceti tipul sortarii: asc - 0 sau desc - 1:", &type);
    if(errType) {
        printf("Se accepta doar valorile de 0 (asc) si 1 (desc)!\n");
        return;
    }
    List* list = getAllMedicineSortedByNameService(ui->medicineService, type);

    if(getListSize(list) == 0) {
        printf("Nu exista date!");
    } else {
        printMedicineList(list);
    }

    destroyList(list);
}

void viewFiltredByQuantity(UI* ui) {
    int quantity = 0;
    int errQuantity = readNumber("Introduceti cantitatea sub care se arata medicamentele:", &quantity);
    if(errQuantity) {
        printf("Cantitatea nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    List* list = getAllMedicineFiltredByQuantityService(ui->medicineService, quantity);

    if(getListSize(list) == 0) {
        printf("Nu exista date dupa filtrare!");
    } else {
        printMedicineList(list);
    }
    destroyList(list);
}

void viewFilteredByFirstLetter(UI* ui) {
    char firstLetter;
    readChar("Introduceti litera dupa care se va face filtrarea:", &firstLetter);
    List* list = getAllMedicineFiltredByNameService(ui->medicineService, firstLetter);

    if(getListSize(list) == 0) {
        printf("\nNu exista date dupa filtrare!");
    } else {
        printMedicineList(list);
    }

    destroyList(list);
}

void viewFiltredByContainedString(UI* ui) {
    char string[100];
    readString("Introduceti stringul care se va cauta in nume:", string, sizeof(char)*100);
    List* list = getAllMedicineWhichContainsString(ui->medicineService, string);

    if(getListSize(list) == 0) {
        printf("Nu exista date dupa filtrare!");
    } else {
        printMedicineList(list);
    }

    destroyList(list);
}

void viewFiltredByConcentration(UI* ui) {
    int concentration = 0;
    int errQuantity = readNumber("Introduceti concentratia sub care se arata medicamentele:", &concentration);
    if(errQuantity) {
        printf("Concentratia nu s-a putut converti la un numar! Reluati comanda!\n");
        return;
    }
    List* list = getAllMedicineFilteredByConcentration(ui->medicineService, concentration);

    if(getListSize(list) == 0) {
        printf("Nu exista date dupa filtrare!");
    } else {
        printMedicineList(list);
    }
    destroyList(list);
}

void undo(UI * ui) {
    if (undoMedicineService(ui->medicineService)) {
        printf("Undo realizat cu succes.");
    } else {
        printf("Nu s-a putut efectua undo.");
    }
}

void redo(UI * ui) {
    if(redoMedicineService(ui->medicineService)) {
        printf("Redo realizat cu succes.");
    } else {
        printf("Nu s-a putut efectua redo.");
    }
}

void printAll(UI * ui) {
    List * list = getAllMedicineWhichContainsString(ui->medicineService, "");
    printMedicineList(list);
    destroyList(list);
}

void runUI(UI* ui) {
    int command;

    while(1) {
        printf("\n\n0. Iesire\n1.Adauga medicament\n2.Actualizeaza medicament\n3.Sterge stoc\n");
        printf("4. Visualizare sortat dupa cantiate(asc/desc)\n5. Vizualizare sortat dupa nume (asc/desc)\n");
        printf("6. Filtru dupa cantitate\n7. Filtru dupa prima litera\n8. Filtreaza dupa un string continut de nume\n");
        printf("9. Filtru dupa concentratie\n10. Undo\n11. Redo\n12. Print all\n\n");
        int error = readNumber("\nIntroduceti comanda:", &command);
        if(error) {
            printf("Nu s-a putut face conversia. Incercati din nou.\n");
            continue;
        }
        if (command == 0) {
            break;
        } else if(command == 1) {
            addMedicineUI(ui);
        } else if(command == 2) {
            updateMedicineUI(ui);
        } else if(command == 3) {
            deleteStockUI(ui);
        } else if(command == 4) {
            viewSortedByQuantity(ui);
        } else if(command == 5) {
            viewSortedByName(ui);
        } else if(command == 6) {
            viewFiltredByQuantity(ui);
        } else if(command == 7) {
            viewFilteredByFirstLetter(ui);
        } else if(command == 8) {
            viewFiltredByContainedString(ui);
        } else if(command == 9) {
            viewFiltredByConcentration(ui);
        } else if (command == 10) {
            undo(ui);
        } else if (command == 11) {
            redo(ui);
        } else if (command == 12) {
            printAll(ui);
        }
        else {
            printf("Comanda necunoscuta ...\n");
        }
    }
}
