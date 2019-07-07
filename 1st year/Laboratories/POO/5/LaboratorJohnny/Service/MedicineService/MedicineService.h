#pragma once

#include "../../Domain/Medicine/Medicine.h"
#include "../../Repository/MedicineRepository/MedicineRepository.h"

typedef struct {
    MedicineRepository* repository;
} MedicineService;

/**
 * Functia creaza un medicineService si returneaza un pointer catre heap
 * Dealocarea memoriei se face prin apelarea functie destroyMedicineService de catre cel care
 * creaza un service
 * @param repository - MedicineService e dependent de un medicineRepository
 * @return a pointer to a MedicineService
 *
 */
MedicineService* createMedicineService(MedicineRepository * repository);

/**
 * Functia elibereaza memoria utilizata de un service creat cu createMedicineService
 * @param medicineService - un service a carui memorie va fi eliberata
 *
 * Preconditii: medicineService a fost creat cu createMedicineService
 */
void destroyMedicineService(MedicineService* medicineService);

/**
 * Functia adauga un nou medicament in service. Daca id-ul exista deja in service atunci
 *  la medicamentul existent se va updata cantitatea cu cantitatea data ca parametru
 * @param service
 * @param id - id-ul noului medicament
 * @param name - numele noului medicament
 * @param concentration - concentratia noului medicament
 * @param quantity - cantitatea noului medicament
 * @return - daca un medicament cu id-ul dat nu exista return -1, daca exista return 0, daca valoare de return este positiva
 * a aparut o eroare de validare (a se vedea MedicineValidator)
 */
int addMedicineService(MedicineService* service, int id, char* name, int concentration, int quantity);

/**
 * Functia face update la un medicament din service daca el exista, in caz contrar nu face decat sa returneze esecul
 * @param service
 * @param medicineId - id-ul medicamentului cautat
 * @param name - noul nume al medicamentului
 * @param concentration - noua concentratie a medicamentului data ca un numar intre 0 si 100
 *
 * @return 0 daca nu exista un medicament sa fie updatat, -1 daca exista, daca exista return 0, daca valoare de return este positiva
 * a aparut o eroare de validare (a se vedea MedicineValidator)
 */
int updateMedicineService(MedicineService* service,int medicineId, char* name, int concentration);

/**
 * Functia cauta un obiect in service dupa id-ul dat
 * @param service
 * @param id
 * @return Se retureaza un poiner la struct-ul cautat daca medicamentul exista, daca nu returneaza NULL
 */
Medicine* findMedicineService(MedicineService* service, int id);

/**
 * Functia sterge stocul unui medicament cu id-ul dat
 * @param service
 * @param medicineId
 * @return 1 daca exista un medicament cu id-ul dat si stergerea s-a efectuat cu succes si 0 in caz contrar
 */
int eraseQuantityForMedicineService(MedicineService* service, int medicineId);


/**
 * Functia returneaza marimea service-ului
 * @param service
 * @return marimea service-ului
 */
int getMedicineServiceSize(MedicineService* service);

/**
 * Functia returneaza o lista ce contine pointer la Medicine, struct-uri sortate dupa cantitate, in ordinea data
 * de parametrul type
 * @param service
 * @param type - 0 sau 1, 0 pentru sortare ascendenta (lexicografica) si 1 pentru sortare descendenta (invers lexicografica)
 * Postconditii: spatiul alocat unui MedicineList va fi delocat de apelant; NU se vor dealoca
 * spatiile de memorii ale structurilor Medicine
 * @return o medicineList, lista ce contine pointeri la structuri din service
 */
List* getAllMedicineSortedByQuantityService(MedicineService* service, int type);

/**
 * Functia returneaza o lista ce contine pointer la Medicine, struct-uri sortate dupa nume, in ordinea data
 * de parametrul type
 * @param service
 * @param type - 0 sau 1, 0 pentru sortare ascendenta (lexicografica) si 1 pentru sortare descendenta (invers lexicografica)
 * Postconditii: spatiul alocat unui MedicineList va fi delocat de apelant; NU se vor dealoca
 * spatiile de memorii ale structurilor Medicine
 * @return o medicineList, lista ce contine pointeri la structuri din service
 */
List* getAllMedicineSortedByNameService(MedicineService* service, int type);

/**
 * Functia returneaza o lista ce contine pointer la Medicine, structuri ale caror campuri name incep cu litera data
 * @param service
 * @param letter
 * Postconditii: spatiul alocat unui MedicineList va fi delocat de apelant; NU se vor dealoca
 * spatiile de memorii ale structurilor Medicine
 * @return o medicineList, lista ce contine pointeri la structuri din service
 */
List* getAllMedicineFiltredByNameService(MedicineService* service, char letter);

/**
 * Functia returneaza o lista ce contine pointer la Medicine, structuri ale caror campuri quantity au valorea strict mai mica
 * decat valoarea data
 * @param service
 * @param quantity
 * Postconditii: spatiul alocat unui MedicineList va fi delocat de apelant; NU se vor dealoca
 * spatiile de memorii ale structurilor Medicine
 * @return o medicineList, lista ce contine pointeri la structuri din repository
 */
List* getAllMedicineFiltredByQuantityService(MedicineService* service, int quantity);

/**
 * Functia returneaza toate medicamentele ale caror nume contin un string dat
 * @param medicineService
 * @param string
 * @return lista cu medicamente
 * Postconditie: Memoria listei trebuie dealocata manual
 */
List* getAllMedicineWhichContainsString(MedicineService* medicineService, char* string);

List * getAllMedicineFilteredByConcentration(MedicineService * service, int concentration);

int undoMedicineService(MedicineService * service);

int redoMedicineService(MedicineService * service);

