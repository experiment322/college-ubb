
#include "MedicineRepository.h"
#include <stdlib.h>

static void handleRepositoryChange(MedicineRepository * repository) {
    addToList(repository->undoList, deepCopyList(repository->list, (DeepCopyElementFunc)deepCopyMedicine));
    destroyList(repository->redoList);
    repository->redoList = createList((DestructFunc)destroyList, sizeof (List *));
}

MedicineRepository* createMedicineRepository() {
    MedicineRepository* medicineRepository = (MedicineRepository*) malloc(sizeof(MedicineRepository));
    medicineRepository->list = createList((DestructFunc)destroyMedicine, getSizeOfMedicinePointer());
    medicineRepository->undoList = createList((DestructFunc)destroyList, sizeof (List *));
    medicineRepository->redoList = createList((DestructFunc)destroyList, sizeof (List *));
    return medicineRepository;
}

void addMedicineRepository(MedicineRepository* repository, Medicine* medicine) {
    handleRepositoryChange(repository);
    addToList(repository->list, medicine);
}

void updateMedicineRepository(MedicineRepository * repository, Medicine* medicine, char* name, int concentration) {
    handleRepositoryChange(repository);
    setMedicineName(medicine, name);
    setMedicineConcentration(medicine, concentration);
}

Medicine* findMedicineRepository(MedicineRepository* repository, int id) {
    Medicine* medicine;
   for(int i = 0; i < getMedicineRepositorySize(repository); i++) {
        medicine = getAtListIndex(repository->list, i);
        if (id == medicine->id) {
            return getAtListIndex(repository->list, i);
        }

   }

    return NULL;
}

int getMedicineRepositorySize(MedicineRepository* medicineRepository) {
    return getListSize(medicineRepository->list);
}

void destroyMedicineRepository(MedicineRepository* medicineRepository) {
    destroyList(medicineRepository->list);
    destroyList(medicineRepository->undoList);
    destroyList(medicineRepository->redoList);
    free(medicineRepository);
}

List* getAllMedicineRepository(MedicineRepository* medicineRepository) {
    return deepCopyList(medicineRepository->list, (DeepCopyElementFunc)deepCopyMedicine);
}

int undoRepository(MedicineRepository * repository) {
    if (getListSize(repository->undoList) > 0) {
        addToList(repository->redoList, repository->list);
        repository->list = popAtListIndex(repository->undoList, getListSize(repository->undoList) - 1);
        return 1;
    }
    return 0;
}

int redoRepository(MedicineRepository * repository) {
    if (getListSize(repository->redoList) > 0) {
        addToList(repository->undoList, repository->list);
        repository->list = popAtListIndex(repository->redoList, getListSize(repository->redoList) - 1);
        return 1;
    }
    return 0;
}
