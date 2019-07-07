#include "Medicine.h"
#include <string.h>
#include <stdlib.h>

int getSizeOfMedicinePointer() {
    return sizeof(Medicine*);
}

Medicine* createMedicine(int id, char *name, int concentration, int quantity) {
    Medicine* medicine = (Medicine*) malloc(sizeof(Medicine));
    medicine->id = id;
    medicine->quantity = quantity;
    medicine->name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(medicine->name, name);
    medicine->concentration = concentration;

    return medicine;
}

Medicine* deepCopyMedicine(Medicine* medicine) {
    return createMedicine(
        getMedicineId(medicine),
        getMedicineName(medicine),
        getMedicineConcentration(medicine),
        getMedicineQuantity(medicine)
    );
}

void destroyMedicine(Medicine* medicine) {
    free(medicine->name);
    free(medicine);
}


int getMedicineId(Medicine* medicine) {
    return medicine->id;
}

int getMedicineConcentration(Medicine* medicine) {
    return medicine->concentration;
}

char* getMedicineName(Medicine* medicine) {
    return medicine->name;
}

int getMedicineQuantity(Medicine* medicine)  {
    return medicine->quantity;
}

void setMedicineName(Medicine * medicine,  char * name) {
    free(medicine->name);
    medicine->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(medicine->name, name);
}

void setMedicineConcentration(Medicine * medicine, int concentration) {
    medicine->concentration = concentration;
}

void setMedicineQuantity(Medicine * medicine, int quantity) {
    medicine->quantity = quantity;
}
