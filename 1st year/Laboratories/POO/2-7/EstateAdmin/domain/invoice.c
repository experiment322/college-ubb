#include "invoice.h"
#include "util/misc.h"

char * INVOICE_CATEGORY_STRING[] = {
    FOREACH_CATEGORY(GENERATE_STRING)
};

unsigned INVOICE_CATEGORY_COUNT = sizeof (INVOICE_CATEGORY_STRING) / sizeof (*INVOICE_CATEGORY_STRING);

typedef struct _Invoice {
    int sum;
    int apartment_number;
    InvoiceCategory category;
} Invoice;

Invoice * create_invoice(int sum, int apartment_number, InvoiceCategory category) {
    Invoice * invoice = safe_malloc(sizeof (*invoice));
    invoice->sum = sum;
    invoice->apartment_number = apartment_number;
    invoice->category = category;
    return invoice;
}

Invoice * clone_invoice(Invoice * invoice) {
    Invoice * clone = safe_malloc(sizeof (*invoice));
    clone->sum = invoice->sum;
    clone->apartment_number = invoice->apartment_number;
    clone->category = invoice->category;
    return clone;
}

void destroy_invoice(Invoice * invoice) {
    if (invoice == NULL) {
        return;
    }
    safe_free(invoice);
}

void invoice_set_sum(Invoice * invoice, int sum) {
    invoice->sum = sum;
}

int invoice_get_sum(Invoice * invoice) {
    return invoice->sum;
}

void invoice_set_appartment_number(Invoice * invoice, int appartment_number) {
    invoice->apartment_number = appartment_number;
}

int invoice_get_appartment_number(Invoice * invoice) {
    return invoice->apartment_number;
}

void invoice_set_category(Invoice * invoice, InvoiceCategory category) {
    invoice->category = category;
}

InvoiceCategory invoice_get_category(Invoice * invoice) {
    return invoice->category;
}
