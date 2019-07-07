
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "MedicineServiceTests.h"
#include "../Domain/Medicine/Medicine.h"
#include "MedicineService/MedicineService.h"


void runMedicineServiceTests() {
    Medicine* medicine;
    Medicine* medicine1;

    // Create tests
    MedicineService* medicineService = createMedicineService(createMedicineRepository());
    assert(getMedicineServiceSize(medicineService) == 0);

    // Add tests
    addMedicineService(medicineService, 1, "Strepsils", 57, 3);
    assert(getMedicineServiceSize(medicineService) == 1);

    addMedicineService(medicineService, 2, "Nurofen", 30, 10);
    assert(getMedicineServiceSize(medicineService) == 2);

    // Undo/redo tests
    assert(undoMedicineService(medicineService) == 1);
    assert(redoMedicineService(medicineService) == 1);
    assert(redoMedicineService(medicineService) == 0);

    medicine = findMedicineService(medicineService, 1);
    medicine1= findMedicineService(medicineService, 2);

    // New filter test
    List * list = getAllMedicineFilteredByConcentration(medicineService, 50);
    assert(getListSize(list) == 1);
    destroyList(list);

    // unvalid add
    addMedicineService(medicineService, 1, "", -2, -1);

    // if is the same id, just update
    addMedicineService(medicineService, 2, "CC", 2, 2);
    assert(getMedicineServiceSize(medicineService) == 2);
    assert(getMedicineQuantity(medicine1) == 2);
    assert(strcmp(getMedicineName(medicine1), "CC") != 0); // name should not update

    // Find tests
    assert(findMedicineService(medicineService, 3) == NULL);

    // Update tests
    assert(getMedicineQuantity(medicine) == 3);
    assert(strcmp(getMedicineName(medicine), "Strepsils") == 0);

    assert(updateMedicineService(medicineService, 1, "Alt nume", 8) == -1);
    assert(updateMedicineService(medicineService, 443423342, "A", 3) == 0);

    assert(getMedicineConcentration(medicine) == 8);
    assert(strcmp(getMedicineName(medicine), "Alt nume") == 0);

    // erase quantity of medicine
    assert(getMedicineQuantity(medicine) != 0);
    assert(eraseQuantityForMedicineService(medicineService, 1) == 1);
    assert(getMedicineQuantity(medicine) == 0);

    assert(eraseQuantityForMedicineService(medicineService, 100) == 0);
    addMedicineService(medicineService, 3, "Atrepsils2", 57, 3);
     addMedicineService(medicineService, 4, "Nurofen2", 30, 80);
    addMedicineService(medicineService, 5, "Nzzzzz", 30, 2);


    List* l1 = getAllMedicineFiltredByQuantityService(medicineService, 10);
    assert(getListSize(l1) == 4);
    List* l2 = getAllMedicineFiltredByQuantityService(medicineService, 2);
    assert(getListSize(l2) == 1);
    List* l3 = getAllMedicineFiltredByQuantityService(medicineService, 100);
    assert(getListSize(l3) == 5);

    List* l4 = getAllMedicineFiltredByNameService(medicineService, 'N');
    assert(getListSize(l4) == 3);

    List* quantityAscSort = getAllMedicineSortedByQuantityService(medicineService, 0);
    assert(((Medicine*)getAtListIndex(quantityAscSort, 0))->id == findMedicineService(medicineService, 1)->id);

    List* quantityDescSort = getAllMedicineSortedByQuantityService(medicineService, 1);
    assert(((Medicine*)getAtListIndex(quantityDescSort, 0))->id == findMedicineService(medicineService, 4)->id);

    List* nameAscSort = getAllMedicineSortedByNameService(medicineService, 0); // 0 - asc
    assert(((Medicine*)getAtListIndex(nameAscSort, 0))->id == findMedicineService(medicineService, 1)->id);

    List* nameDescSort = getAllMedicineSortedByNameService(medicineService, 1); // 1 - desc
    assert(((Medicine*)getAtListIndex(nameDescSort, 0))->id == findMedicineService(medicineService, 5)->id);

    List* l5 = getAllMedicineWhichContainsString(medicineService, "Alt");
    assert(getListSize(l5) == 1);

    destroyList(quantityAscSort);
    destroyList(quantityDescSort);
    destroyList(nameAscSort);
    destroyList(nameDescSort);

    destroyList(l1);
    destroyList(l2);
    destroyList(l3);
    destroyList(l4);
    destroyList(l5);
    destroyMedicineService(medicineService);
}
