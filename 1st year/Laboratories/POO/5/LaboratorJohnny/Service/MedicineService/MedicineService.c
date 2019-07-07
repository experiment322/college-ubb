#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MedicineService.h"
#include "../../Utils/Utils.h"
#include "../../Domain/Medicine/MedicineValidator.h"

#define ASC 0
#define DESC 1

MedicineService* createMedicineService(MedicineRepository * repository) {
    MedicineService* medicineService = (MedicineService*) malloc(sizeof(MedicineService));
    medicineService->repository = repository;

    return medicineService;
}

int addMedicineService(MedicineService* service, int id, char* name, int concentration, int quantity) {
    Medicine* medicine = createMedicine(id, name, concentration, quantity);
    Medicine* findMedicine = findMedicineService(service, id);


    int validation = validateMedicine(medicine);
    if (validation != 0) {
        destroyMedicine(medicine);
        return validation;
    }

    // medicine already exists, update it
    if (findMedicine != NULL) {
        setMedicineQuantity(findMedicine, quantity);
        destroyMedicine(medicine);
        return 0;
    }
    addMedicineRepository(service->repository, medicine);
    return -1; // true - created

}

void destroyMedicineService(MedicineService* medicineService) {
    destroyMedicineRepository(medicineService->repository);
    free(medicineService);
}

int updateMedicineService(MedicineService* service, int medicineId, char* name, int concentration) {
    Medicine* medicine = findMedicineService(service, medicineId);

    if(medicine != NULL) {
        int validation = validateMedicineConcentration(concentration);
        if(validation != 0) return validation;
        // if valid, update
        updateMedicineRepository(service->repository, medicine, name, concentration);
        return -1; // true, we found a medicine to update
    }

    return 0; // false

}

int getMedicineServiceSize(MedicineService* service) {
    return getMedicineRepositorySize(service->repository);
}

Medicine* findMedicineService(MedicineService* service, int id) {
    return findMedicineRepository(service->repository, id);
}

int eraseQuantityForMedicineService(MedicineService* service, int medicineId) {
    Medicine* medicine = findMedicineService(service, medicineId);

    if(medicine != NULL) {
        setMedicineQuantity(medicine, 0);
        return 1; // true, we found a medicine to reset quantity
    }

    return 0; // false
}

static int compareByQuantityAscending(void *item1, void *item2) {
    Medicine* medicine1 = (Medicine*)item1;
    Medicine* medicine2 = (Medicine*)item2;

    return getMedicineQuantity(medicine1) - getMedicineQuantity(medicine2);

}

static int compareByQuantityDescending(void *item1, void *item2) {
    Medicine* medicine1 = (Medicine*)item1;
    Medicine* medicine2 = (Medicine*)item2;
    return getMedicineQuantity(medicine2) - getMedicineQuantity(medicine1);

}

static int compareByNameAscending(void *item1, void *item2) {
    Medicine* medicine1 = (Medicine*)item1;
    Medicine* medicine2 = (Medicine*)item2;

    return strcmp(getMedicineName(medicine1), getMedicineName(medicine2));
}

static int compareByNameDescending(void *item1, void *item2) {
    Medicine* medicine1 = (Medicine*)item1;
    Medicine* medicine2 = (Medicine*)item2;
    return strcmp(getMedicineName(medicine2), getMedicineName(medicine1));
}

List* getAllMedicineSortedByQuantityService(MedicineService* service, int type) {
    List* medicineList = getAllMedicineRepository(service->repository);

    // 0 - ascending
    if(type == ASC) {
        selectionSort(medicineList, (CompareFunc)compareByQuantityAscending);
    // 1 - descending
    } else {
        selectionSort(medicineList, (CompareFunc)compareByQuantityDescending);
    }

    return medicineList;
}

List* getAllMedicineSortedByNameService(MedicineService* service, int type) {
    List* medicineList = getAllMedicineRepository(service->repository);

    // 0 - ascending
    if(type == ASC) {
        selectionSort(medicineList, (CompareFunc)compareByNameAscending);
        // 1 - descending
    } else {
        selectionSort(medicineList, (CompareFunc)compareByNameDescending);
    }

    return medicineList;
}

List* getAllMedicineFiltredByNameService(MedicineService* service, char letter) {
    List* medicineList = getAllMedicineRepository(service->repository);
    List* filteredList = createList((DestructFunc)destroyMedicine, getSizeOfMedicinePointer());
    Medicine* medicine;

    for(int i=0; i< getListSize(medicineList); i++) {
        medicine = getAtListIndex(medicineList, i);
        if(getMedicineName(medicine)[0] == letter) {
            addToList(filteredList, deepCopyMedicine(medicine));
        }
    }
    destroyList(medicineList);
    return filteredList;
}

List* getAllMedicineFiltredByQuantityService(MedicineService* service, int quantity) {
    List* medicineList = getAllMedicineRepository(service->repository);
    List* filteredList = createList((DestructFunc)destroyMedicine, getSizeOfMedicinePointer());
    Medicine* medicine;

    for(int i=0; i < getListSize(medicineList); i++) {
        medicine = getAtListIndex(medicineList, i);
        if(getMedicineQuantity(medicine) < quantity) {
            addToList(filteredList, deepCopyMedicine(medicine));
        }
    }
    destroyList(medicineList);
    return filteredList;
}

List* getAllMedicineWhichContainsString(MedicineService* medicineService, char* string) {
    List* medicineList = getAllMedicineRepository(medicineService->repository);
    List* filteredList = createList((DestructFunc)destroyMedicine, getSizeOfMedicinePointer());
    Medicine* medicine;
    char* name;

    for(int i=0; i < getListSize(medicineList); i++) {
        medicine = getAtListIndex(medicineList, i);
        name = getMedicineName(medicine);
        if(strstr(name, string) != NULL) {
            addToList(filteredList, deepCopyMedicine(medicine));
        }
    }
    destroyList(medicineList);
    return filteredList;
}

List * getAllMedicineFilteredByConcentration(MedicineService * service, int concentration) {
    List* medicineList = getAllMedicineRepository(service->repository);
    List* filteredList = createList((DestructFunc)destroyMedicine, getSizeOfMedicinePointer());
    Medicine* medicine;

    for(int i=0; i < getListSize(medicineList); i++) {
        medicine = getAtListIndex(medicineList, i);
        if(getMedicineConcentration(medicine) < concentration) {
            addToList(filteredList, deepCopyMedicine(medicine));
        }
    }
    destroyList(medicineList);
    return filteredList;
}

int undoMedicineService(MedicineService * service) {
    return undoRepository(service->repository);
}

int redoMedicineService(MedicineService * service) {
    return redoRepository(service->repository);
}
