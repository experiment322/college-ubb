#include "invoice_repository.h"
#include "domain/invoice.h"
#include "util/list.h"
#include "util/misc.h"

typedef struct _InvoiceRepository {
    List * list;
} InvoiceRepository;

static void * clone_invoice_wrapper(void * invoice) {
    return clone_invoice(invoice);
}

static void destroy_invoice_wrapper(void * invoice) {
    destroy_invoice(invoice);
}

InvoiceRepository * create_invoice_repository(void) {
    InvoiceRepository * repository = safe_malloc(sizeof (*repository));
    repository->list = create_list(clone_invoice_wrapper, destroy_invoice_wrapper);
    return repository;
}

void destroy_invoice_repository(InvoiceRepository * repository) {
    if (repository == NULL) {
        return;
    }
    destroy_list(repository->list);
    safe_free(repository);
}

List * repository_get_invoices(InvoiceRepository * repository) {
    return clone_list(repository->list);
}

int repository_add_invoice(InvoiceRepository * repository, Invoice * invoice) {
    int i;
    Invoice * temp_invoice;
    for (i = 0; i < list_size(repository->list); ++i) {
        temp_invoice = list_get(repository->list, i);
        if (invoice_get_appartment_number(temp_invoice) == invoice_get_appartment_number(invoice)) {
            return FAILURE;
        }
    }
    list_add(repository->list, invoice);
    return SUCCESS;
}

int repository_mod_invoice(InvoiceRepository * repository, Invoice * invoice) {
    int i;
    Invoice * old_invoice;
    for (i = 0; i < list_size(repository->list); ++i) {
        old_invoice = list_get(repository->list, i);
        if (invoice_get_appartment_number(old_invoice) == invoice_get_appartment_number(invoice)) {
            invoice_set_sum(old_invoice, invoice_get_sum(invoice));
            invoice_set_category(old_invoice, invoice_get_category(invoice));
            return SUCCESS;
        }
    }
    return FAILURE;
}

int repository_del_invoice(InvoiceRepository * repository, int appartment_number) {
    int i;
    Invoice * invoice;
    for (i = 0; i < list_size(repository->list); ++i) {
        invoice = list_get(repository->list, i);
        if (invoice_get_appartment_number(invoice) == appartment_number) {
            list_pop(repository->list, i);
            destroy_invoice(invoice);
            return SUCCESS;
        }
    }
    return FAILURE;
}
