#pragma once

#include "../../Domain/Medicine/Medicine.h"
#include "../../Utils/List.h"

typedef struct {
    List* list;
    List* undoList;
    List* redoList;
} MedicineRepository;

/**
 * Functia creaza un medicineRepository si returneaza un pointer catre heap
 * Dealocarea memoriei se face prin apelarea functie destroyMedicineRepository de catre cel care
 * creaza un repository
 * @return a pointer to a MedicineRepository
 */
MedicineRepository* createMedicineRepository();


/**
 * Functia elibereaza memoria utilizata de un repository creat cu createMedicineRepository
 * @param medicineRepository - un repository a carui memorie va fi eliberata
 *
 * Preconditii: medicineRepository a fost creat cu createMedicineRepository
 */
void destroyMedicineRepository(MedicineRepository* medicineRepository);

/**
 * Functia returneaza marimea repository-ului
 * @param medicineRepository
 * @return marimea repository-ului
 */
int getMedicineRepositorySize(MedicineRepository* medicineRepository);

/**
 * Functia adauga un medicament in repository
 * @param repository - repository-ul in care se adauga medicamentul
 * @param medicine - obiectul de adaugat
 */
void addMedicineRepository(MedicineRepository* repository, Medicine* medicine);

/**
 * Functia actualizeaza numele si cantitatea unui medicament dat
 * Preconditii: medicine e un obiect luat din repository
 * @param repository
 * @param medicine - obiect luat din repository
 * @param name - numele nou ce va fi atribuit medicamentului
 * @param quantity - cantitatea noua de medicament ce se va salva in medicament
 */
void updateMedicineRepository(MedicineRepository * repository, Medicine* medicine, char* name, int quantity);

/**
 * Functia cauta un medicament in repository dupa un id dat
 * @param repository
 * @param id - id-ul medicamentului care se va cauta
 * @return NULL daca obiectul nu exista in repository, un pointer la Medicine daca exista
 */
Medicine* findMedicineRepository(MedicineRepository* repository, int id);

/**
 * Functia returneaza o lista cu toate medicamentele dintr-un repository medicineRepository
 * Postconditii: spatiul alocat unui MedicineList va fi delocat de apelant; NU se vor dealoca
 * spatiile de memorii ale structurilor Medicine
 * @param medicineRepository
 * @return un pointer la MedicineList
 */
List* getAllMedicineRepository(MedicineRepository* medicineRepository);

/**
 * @brief undoRepository restituie repository-ul la o versiune anterioara.
 * @param repository
 * @return 1 daca s-a realizat restituirea, 0 altfel
 */
int undoRepository(MedicineRepository * repository);

/**
 * @brief redoRepository anuleaza ultimele undo-uri daca nu a avut loc nicio modificare
 * intre acestea, altfel anularea lor nu va mai fi posibila.
 * @param repository
 * @return 1 daca s-a realizat anularea, 0 altfel
 */
int redoRepository(MedicineRepository * repository);
