#ifndef INVOICE_CONTROLLER_H
#define INVOICE_CONTROLLER_H

#include "util/list.h"
#include "repository/invoice_repository.h"

typedef enum _FilterType {
    FILTER_SUM,
    FILTER_APARTMENT_NUMBER,
    FILTER_CATEGORY
} FilterType;

typedef enum _SortType {
    SORT_SUM,
    SORT_CATEGORY
} SortType;

typedef struct _InvoiceController InvoiceController;

/*
 * Create a new invoice controller which operates on the given repository and return a pointer to it.
 */
InvoiceController * create_invoice_controller(InvoiceRepository * repository);

/*
 * Destroy a previously created controller and return the repository on which it operated.
 */
InvoiceRepository * destroy_invoice_controller(InvoiceController * controller);

/*
 * Convert data to an invoice and add it to the internal repository.
 * In case of conversion failure or repository failure return FAILURE, otherwise return SUCCESS.
 * data should be a string of the form "APNO SUM CAT".
 * Constraints: APNO >= 1, SUM >= 0 and CAT is an existent case-sensitive category.
 */
int controller_add_invoice(InvoiceController * controller, char * data);

/*
 * Convert data to an invoice and update the invoice in repository with mathcing apartment_number.
 * In case of conversion failure or repository failure return FAILURE, otherwise return SUCCESS.
 * data should be a string of the form "APNO SUM CAT".
 * Constraints: APNO >= 1, SUM >= 0 and CAT is an existent case-sensitive category.
 */
int controller_mod_invoice(InvoiceController * controller, char * data);

/*
 * Convert data to an int representing the apartment_number and delete the invoice matching from repository.
 * In case of conversion failure or repository failure return FAILURE, otherwise return SUCCESS.
 * data should be a string of the form "APNO", where APNO is an integer.
 */
int controller_del_invoice(InvoiceController * controller, char * data);

/*
 * Sort a copy of the list of invoices from the repository in place and return it.
 * Sorting criteria is specified by a value from SortType and is done descending if ascending is 0, otherwise ascending.
 * It is the responsability of the developer to destroy the list later.
 */
List * controller_sort_invoices(InvoiceController * controller, SortType sort_type, int ascending);

/*
 * Filter a copy of the list of invoices from the repository in place and return it.
 * Filter criteria is specified by a value from FilterType and only that property from the invoice is used in filtering.
 * The invoice is obtained by parsing the data and converting it, where data is a string of the form "APNO SUM CAT".
 * Constraints: APNO >= 1, SUM >= 0 and CAT is an existent case-sensitive category.
 * Even if only one field is used all must appear in the string and be valid.
 * If the conversion fails the function returns NULL, otherwise return the filtered list.
 * It is the responsability of the developer to destroy the list later.
 */
List * controller_filter_invoices(InvoiceController * controller, char * data, FilterType filter_type);

#endif // INVOICE_CONTROLLER_H
