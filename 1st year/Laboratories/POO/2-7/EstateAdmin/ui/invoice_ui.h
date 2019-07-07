#ifndef INVOICE_UI_H
#define INVOICE_UI_H

#include "controller/invoice_controller.h"

/*
 * Run the invoice ui on the controller passed as parameter.
 * Prompt the user with options and call necessary controller functions to produce the desired outcome.
 */
void run_invoice_ui(InvoiceController * controller);

#endif // INVOICE_UI_H
