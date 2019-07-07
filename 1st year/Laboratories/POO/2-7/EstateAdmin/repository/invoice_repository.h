#ifndef INVOICE_REPOSITORY_H
#define INVOICE_REPOSITORY_H

#include "domain/invoice.h"
#include "util/list.h"

typedef struct _InvoiceRepository InvoiceRepository;

/*
 * Create a new invoice repository and return a pointer to it.
 */
InvoiceRepository * create_invoice_repository(void);

/*
 * Destroy a previous created invoice repository.
 * If NULL is given as parameter do nothing.
 */
void destroy_invoice_repository(InvoiceRepository * repository);

/*
 * Return a pointer to a copy of the internal invoice list.
 * The copy should be destroyed by the developer when it isn't needed anymore.
 * Any modification to the copy will not affect the repository's internal list.
 */
List * repository_get_invoices(InvoiceRepository * repository);

/*
 * Add the invoice to the internal list of the repository.
 * If there is already an invoice with the same apartment_number the invoice will not be added to the repository.
 * In this case return FAILURE, otherwise return SUCCESS. In both cases the invoice is not destroyed/cloned.
 * In case of SUCCESS the invoice is not cloned and should not be destroyed by the developer to avoid dangling pointers.
 */
int repository_add_invoice(InvoiceRepository * repository, Invoice * invoice);

/*
 * Modify the invoice in the repository with the same apartment_number as the one given as parameter.
 * The modification is done by copying the other properties from the new one, thus the developer should destroy it after.
 * If an invoice with the same apartment_number is not found return FAILURE, otherwise return SUCCESS.
 */
int repository_mod_invoice(InvoiceRepository * repository, Invoice * invoice);

/*
 * Destroy the invoice with the apartment_number given as parameter by calling destroy_invoice.
 * If an invoice with the same apartment_number is not found return FAILURE, otherwise return SUCCESS.
 */
int repository_del_invoice(InvoiceRepository * repository, int appartment_number);

#endif // INVOICE_REPOSITORY_H
