#pragma once

#include "../Service/MedicineService/MedicineService.h"

typedef struct {
    MedicineService* medicineService;
} UI;

void runUI(UI* ui);

UI* createUI(MedicineService* medicineService);

void destroyUI(UI* ui);

