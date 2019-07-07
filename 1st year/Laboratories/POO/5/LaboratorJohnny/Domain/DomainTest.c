#include "DomainTest.h"
#include "Medicine/MedicineValidator.h"
#include <string.h>

void testCreateMedicine() {
    char name[] = "hello";

    Medicine* medicine = createMedicine(1, name, 2, 10);

    assert(medicine != NULL);
    assert(strcmp(getMedicineName(medicine), name) == 0);
    assert(getMedicineQuantity(medicine) == 10);
    destroyMedicine(medicine);
}


void testUpdateNameMedicine() {
    char name[] = "hello";
    char name2[] = "other name";

    Medicine* medicine = createMedicine(1, name, 2, 10);

    assert(strcmp(getMedicineName(medicine), name) == 0);

    setMedicineName(medicine, name2);
	assert(getMedicineId(medicine) == 1);
    assert(strcmp(getMedicineName(medicine), name) != 0);
    assert(strcmp(getMedicineName(medicine), name2) == 0);

    destroyMedicine(medicine);
}

void testUpdateQuantityMedicine() {
    char name[] = "hello";
    Medicine* medicine = createMedicine(1, name, 2, 10);

    assert(getMedicineQuantity(medicine) == 10);

    setMedicineQuantity(medicine, 3);

    assert(getMedicineQuantity(medicine) == 3);

    destroyMedicine(medicine);
}

void testValidation() {
    char name1[] = "";
    char name2[] = "dsadsa";
    Medicine* medicine1 = createMedicine(1, name1, 2, 10);
    Medicine* medicine2 = createMedicine(1, name2, 2, -10);
    Medicine* medicine3 = createMedicine(1, name2, 500, 10);
    Medicine* medicine4 = createMedicine(1, name1, 500, -10);
    assert(validateMedicine(medicine1) == EMPTY_NAME);
    assert(validateMedicine(medicine2) == NEGATIVE_QUANTITY);
    assert(validateMedicine(medicine3) == CONCENTRATION_OUT_OF_BOUNDS);
    assert(validateMedicineConcentration(-30) == CONCENTRATION_OUT_OF_BOUNDS);
    assert(validateMedicine(medicine4) == 7);

    destroyMedicine(medicine1);
    destroyMedicine(medicine2);
    destroyMedicine(medicine3);
    destroyMedicine(medicine4);

}

void testDeepCopy() {
	Medicine* medicine1 = createMedicine(1, "Hello here is a text!", 2, 10);
	Medicine* medicine2 = deepCopyMedicine(medicine1);

	setMedicineName(medicine1, "abc");
	assert(strcmp(getMedicineName(medicine1), "abc") == 0);
	assert(strcmp(getMedicineName(medicine2), "Hello here is a text!") == 0);
	assert(medicine1 != medicine2);

	destroyMedicine(medicine1);
	destroyMedicine(medicine2);

}

void runDomainTests() {
    testValidation();
	testDeepCopy();
    testCreateMedicine();
    testUpdateNameMedicine();
    testUpdateQuantityMedicine();
}

