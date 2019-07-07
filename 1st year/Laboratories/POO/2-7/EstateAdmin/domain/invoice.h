#ifndef INVOICE_H
#define INVOICE_H

/*
 * Macros used to automate and synchronize the generation of InvoiceCategory and INVOICE_CATEGORY_STRING.
 * Any new category should be added here by using CATEGORY(c) as seen below.
 */
#define FOREACH_CATEGORY(CATEGORY) \
    CATEGORY(GAS) \
    CATEGORY(WATER) \
    CATEGORY(SEWAGE) \
    CATEGORY(HEATING) \

#define GENERATE_ENUM(ITEM) ITEM, \

#define GENERATE_STRING(ITEM) #ITEM, \

extern char * INVOICE_CATEGORY_STRING[];

extern unsigned INVOICE_CATEGORY_COUNT;

typedef enum _InvoiceCategory {
    FOREACH_CATEGORY(GENERATE_ENUM)
} InvoiceCategory;

typedef struct _Invoice Invoice;

/*
 * Create a new invoice with the given parameters and return a pointer to it.
 */
Invoice * create_invoice(int sum, int apartment_number, InvoiceCategory category);

/*
 * Clone existing invoice and copy it's properties.
 * Return a pointer to the newly created invoice.
 */
Invoice * clone_invoice(Invoice * invoice);

/*
 * Destroy a previously created/cloned invoice.
 * If NULL is given as parameter nothing will be done.
 */
void destroy_invoice(Invoice * invoice);

// START OF OOP-ISH FUNCTIONS FOR INVOICE MANIPULATION

void invoice_set_sum(Invoice * invoice, int sum);

int invoice_get_sum(Invoice * invoice);

void invoice_set_appartment_number(Invoice * invoice, int appartment_number);

int invoice_get_appartment_number(Invoice * invoice);

void invoice_set_category(Invoice * invoice, InvoiceCategory category);

InvoiceCategory invoice_get_category(Invoice * invoice);

// END OF OOP-ISH FUNCTIONS FOR INVOICE MANIPULATION

#endif // INVOICE_H
