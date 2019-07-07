//
// Created by ionut on 15.03.2018.
//

#include "MedicineValidator.h"
#include <string.h>

int validateMedicine(Medicine* medicine) {
    int errors = 0;

    if(strcmp(getMedicineName(medicine), "") == 0) errors |= EMPTY_NAME;
    if(getMedicineQuantity(medicine) < 0) errors |= NEGATIVE_QUANTITY;
    if(getMedicineConcentration(medicine) < 0 || getMedicineConcentration(medicine)>100) errors |= CONCENTRATION_OUT_OF_BOUNDS;

    return errors;
}

int validateMedicineConcentration(int concentration) {
    if(concentration < 0 || concentration>100) return CONCENTRATION_OUT_OF_BOUNDS;
    return 0;
}