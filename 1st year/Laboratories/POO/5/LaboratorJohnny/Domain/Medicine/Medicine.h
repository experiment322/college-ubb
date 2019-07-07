#pragma once

typedef struct {
    int id;
    char* name;
    int concentration;
    int quantity;
} Medicine;

/**
  Functia reaturneaza marimea unui pointer la Medicine
  Procedura e menita sa fie folosita pentru a calcula dimensiuni in cadrul unei liste
  Marimea pointerului difera de arhitectura si zona de memorie unde se salveaza
*/
int getSizeOfMedicinePointer();

/**
 * Functia encapsuleaza operatie de creere
 * @param id - id-ul medicamentului creat
 * @param name - numele medicamentului creat
 * @param concentration - concentratia medicamentului sub forma unui numar intre 0 si 100
 * @param quantity - stocul unui medicament
 * @return pointer pe heap la un struct Medicine
 *
 * Post conditii: memoria va fi dealocata de cel care apeleaza functia prin apelarea destroyMedicine
 */
Medicine* createMedicine(int id, char * name, int concentration, int quantity);

/**
* Functia encapsuleaza operatie de deepCopy
* @param medicine - pointer la entitatea caruia i se copiaza proprietatile
  Functia returneaza un pointer la un nou medicine
*
* Post conditii: memoria va fi dealocata de cel care apeleaza functia prin apelarea destroyMedicine
*/
Medicine* deepCopyMedicine(Medicine* medicine);

/**
 * Functia elibereaza memoria folosita de un medicament
 * @param medicine - un medicament
 *
 * Pre conditii: medicine a fost creat folosind functia createMedicine
 */
void destroyMedicine(Medicine* medicine);

/**
 * Functia returneaza adresa unui sirului de caractere ce reprezinta numele unui medicament
 * @param medicine - pointer la un struct medicine
 * @return un sir de caractere
 */
char* getMedicineName(Medicine* medicine);

/**
 *
 * Functia returneaza un numar ce reprezinta cantitatea unui medicament
 * @param medicine - pointer la un struct medicine
 * @return un int mai mare ca 0
 */
int getMedicineQuantity(Medicine* medicine);

/**
 * Functia schimba numele unui medicament
 * @param medicine - pointer la un struct medicine
 * @param name noul nume ce se va atribui entitatii
 */
void setMedicineName(Medicine * medicine,  char * name);

/**
 * Functia schimba cantitatea unui medicament
 * @param medicine - pointer la un struct medicine
 * @param name noua cantitate ce se va atribui entitatii
 */
void setMedicineQuantity(Medicine * medicine, int quantity);

/**
 * Functia schimba concentratia unui medicament
 * @param medicine - pointer la un struct medicine
 * @param name noua cantitate ce se va atribui entitatii
 */
void setMedicineConcentration(Medicine * medicine, int concentration);

/**
 *
 * Functia returneaza un int ce reprezinta id-ul unui medicament
 * @param medicine - pointer la un struct medicine
 * @return un int, id-ul medicamentului
 */
int getMedicineId(Medicine* medicine);

/**
 *
 * Functia returneaza concentratia unui medicament ca un numar intre 0 si 100
 * @param medicine - pointer la un struct medicine
 * @return un sir de caractere
 */
int getMedicineConcentration(Medicine* medicine);

/**
 * Elibereaza memoria alocata cu create sau cu deepCopyMedicine
 * @param medicine
 */
void destroyMedicine(Medicine* medicine);