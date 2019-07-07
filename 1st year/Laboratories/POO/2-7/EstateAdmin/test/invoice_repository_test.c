#include <stdio.h>
#include <assert.h>
#include "invoice_repository_test.h"
#include "util/list.h"
#include "util/misc.h"
#include "domain/invoice.h"
#include "repository/invoice_repository.h"

static void test_invoice_repository_add_invoice(void) {
    List * list;
    Invoice * invoice;
    InvoiceRepository * repository = create_invoice_repository();
    list = repository_get_invoices(repository);
    assert(list_size(list) == 0);
    destroy_list(list);
    assert(repository_add_invoice(repository, create_invoice(100, 1, GAS)) == SUCCESS);
    list = repository_get_invoices(repository);
    assert(list_size(list) == 1);
    destroy_list(list);
    invoice = create_invoice(200, 1, WATER);
    assert(repository_add_invoice(repository, invoice) == FAILURE);
    destroy_invoice(invoice);
    list = repository_get_invoices(repository);
    assert(list_size(list) == 1);
    destroy_list(list);
    destroy_invoice_repository(repository);
}

static void test_invoice_repository_mod_invoice(void) {
    List * list;
    Invoice * invoice;
    InvoiceRepository * repository = create_invoice_repository();
    assert(repository_add_invoice(repository, create_invoice(100, 1, GAS)) == SUCCESS);
    invoice = create_invoice(200, 1, WATER);
    assert(repository_mod_invoice(repository, invoice) == SUCCESS);
    destroy_invoice(invoice);
    list = repository_get_invoices(repository);
    invoice = list_get(list, 0);
    assert(invoice_get_sum(invoice) == 200);
    assert(invoice_get_category(invoice) == WATER);
    destroy_list(list);
    invoice = create_invoice(200, 2, SEWAGE);
    assert(repository_mod_invoice(repository, invoice) == FAILURE);
    destroy_invoice(invoice);
    destroy_invoice_repository(repository);
}

static void test_invoice_repository_del_invoice(void) {
    InvoiceRepository * repository = create_invoice_repository();
    assert(repository_del_invoice(repository, 1) == FAILURE);
    assert(repository_add_invoice(repository, create_invoice(100, 1, GAS)) == SUCCESS);
    assert(repository_del_invoice(repository, 1) == SUCCESS);
    assert(repository_del_invoice(repository, 1) == FAILURE);
    destroy_invoice_repository(repository);
}

void run_invoice_repository_tests(void) {
    printf("invoice_repository_test\n");
    test_invoice_repository_add_invoice(); printf("test_invoice_repository_add_invoice() -> OK\n");
    test_invoice_repository_mod_invoice(); printf("test_invoice_repository_mod_invoice() -> OK\n");
    test_invoice_repository_del_invoice(); printf("test_invoice_repository_del_invoice() -> OK\n");
    destroy_invoice_repository(NULL); // for code coverage
    printf("\n");
}
