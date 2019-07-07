#include <stdio.h>
#include <string.h>
#include "invoice_controller.h"
#include "repository/invoice_repository.h"
#include "domain/invoice.h"
#include "util/misc.h"
#include "util/list.h"

typedef struct _InvoiceController {
    InvoiceRepository * repository;
} InvoiceController;

// START OF INTERNAL FUNCTIONS

/*
 * Parse the data, check for valid input and return a new invoice, otherwise return NULL.
 */
static Invoice * data_to_invoice(char * data) {
    char temp_category[16];
    InvoiceCategory category;
    int sum, apartment_number;
    if (sscanf(data, "%i %i %15s", &apartment_number, &sum, temp_category) != 3) {
        return NULL;
    }
    if (sum < 0 || apartment_number < 1) {
        return NULL;
    }
    for (category = 0; category < INVOICE_CATEGORY_COUNT; ++category) {
        if (strcmp(temp_category, INVOICE_CATEGORY_STRING[category]) == 0) {
            return create_invoice(sum, apartment_number, category);
        }
    }
    return NULL;
}

/*
 * Parse data as an int and return 0 on failure.
 */
static int data_to_apartment_number(char * data) {
    int apartment_number;
    if (sscanf(data, "%i", &apartment_number) != 1) {
        return 0;
    }
    return apartment_number;
}

// START OF FILTERING PREDICATORS

static int are_sums_equal(Invoice * i1, Invoice * i2) {
    return invoice_get_sum(i1) == invoice_get_sum(i2);
}

static int are_apartment_numbers_equal(Invoice * i1, Invoice * i2) {
    return invoice_get_appartment_number(i1) == invoice_get_appartment_number(i2);
}

static int are_categories_equal(Invoice * i1, Invoice * i2) {
    return invoice_get_category(i1) == invoice_get_category(i2);
}

//END OF FILTERING PREDICATORS

// START OF SORTING COMPARATORS

static int compare_sum_ascending(Invoice * i1, Invoice * i2) {
    return invoice_get_sum(i1) - invoice_get_sum(i2);
}

static int compare_sum_descending(Invoice * i1, Invoice * i2) {
    return invoice_get_sum(i2) - invoice_get_sum(i1);
}

static int compare_category_ascending(Invoice * i1, Invoice * i2) {
    return invoice_get_category(i1) - invoice_get_category(i2);
}

static int compare_category_descending(Invoice * i1, Invoice * i2) {
    return invoice_get_category(i2) - invoice_get_category(i1);
}

// END OF SORTING COMPARATORS

/*
 * Filter the list in place by calling predicator on the model and every invoice in the list.
 * If the predicator returns !0 the invoice is popped from the list and destroyed.
 */
static void filter_result(List * list, Invoice * model, int (* predicator)(Invoice * model, Invoice * invoice)) {
    int i;
    for (i = 0; i < list_size(list); ++i) {
        if (!predicator(model, list_get(list, i))) {
            destroy_invoice(list_pop(list, i));
            i -= 1;
        }
    }
}

/*
 * Sort the list in place using bubble sort by calling the given comparator function.
 */
static void sort_result(List * list, int (* comparator)(Invoice * i1, Invoice * i2)) {
    int i, sorting = 1;
    while (sorting) {
        sorting = 0;
        for (i = 0; i < list_size(list) - 1; ++i) {
            if (comparator(list_get(list, i), list_get(list, i + 1)) > 0) {
                list_set(list, i, list_set(list, i + 1, list_get(list, i)));
                sorting = 1;
            }
        }
    }
}

// END OF INTERNAL FUNCTIONS

InvoiceController * create_invoice_controller(InvoiceRepository * repository) {
    InvoiceController * controller = safe_malloc(sizeof (*controller));
    controller->repository = repository;
    return controller;
}

InvoiceRepository * destroy_invoice_controller(InvoiceController * controller) {
    if (controller == NULL) {
        return NULL;
    }
    InvoiceRepository * repository = controller->repository;
    safe_free(controller);
    return repository;
}

int controller_add_invoice(InvoiceController * controller, char * data) {
    int result;
    Invoice * invoice = data_to_invoice(data);
    if (invoice == NULL) {
        return FAILURE;
    }
    result = repository_add_invoice(controller->repository, invoice);
    if (result == FAILURE) {
        destroy_invoice(invoice);
    }
    return result;
}

int controller_mod_invoice(InvoiceController * controller, char * data) {
    int result;
    Invoice * invoice = data_to_invoice(data);
    if (invoice == NULL) {
        return FAILURE;
    }
    result = repository_mod_invoice(controller->repository, invoice);
    destroy_invoice(invoice);
    return result;
}

int controller_del_invoice(InvoiceController * controller, char * data) {
    int apartment_number = data_to_apartment_number(data);
    return repository_del_invoice(controller->repository, apartment_number);
}

List * controller_sort_invoices(InvoiceController * controller, SortType sort_type, int ascending) {
    List * result = repository_get_invoices(controller->repository);
    switch (sort_type) {
    case SORT_SUM:
        ascending
                ? sort_result(result, compare_sum_ascending)
                : sort_result(result, compare_sum_descending);
        break;
    case SORT_CATEGORY:
        ascending
                ? sort_result(result, compare_category_ascending)
                : sort_result(result, compare_category_descending);
        break;
    }
    return result;
}

List * controller_filter_invoices(InvoiceController * controller, char * data, FilterType filter_type) {
    List * result = repository_get_invoices(controller->repository);
    Invoice * model = data_to_invoice(data);
    if (model == NULL) {
        destroy_list(result);
        return NULL;
    }
    switch (filter_type) {
    case FILTER_SUM:
        filter_result(result, model, are_sums_equal);
        break;
    case FILTER_APARTMENT_NUMBER:
        filter_result(result, model, are_apartment_numbers_equal);
        break;
    case FILTER_CATEGORY:
        filter_result(result, model, are_categories_equal);
        break;
    }
    destroy_invoice(model);
    return result;
}
