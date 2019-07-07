#pragma once

#include "Medicine.h"

#define CONCENTRATION_OUT_OF_BOUNDS 1 << 0
#define NEGATIVE_QUANTITY 1 << 1
#define EMPTY_NAME 1 << 2

/**
 * Functia valideaza un medicament. Verifica daca concentratia se afla in intervalul 0-100, daca cantitatea e negativa
 * sau daca numele e gol
 * Erorile sunt returnate drept puteri ale lui 2 pentru a le putea combina
 * @param medicine
 * @return un numar ce are pe biti erorile in modul urmator:
 * bitul 0 setat daca concentratia nu se afla in invervalul potrivit, bitul 1 daca cantitatea e negativa, bitul 2 daca numele e null
 * , 0 daca nu exista eroare
 */
int validateMedicine(Medicine* medicine);

/**
 * Functia valideaza concentratia unui medicament. Verifica daca concentratia se afla in intervalul 0-100.
 * @param concentration
 * @return 1 daca concentratia nu e valida, 0 in caz contrar
 */
int validateMedicineConcentration(int concentration);