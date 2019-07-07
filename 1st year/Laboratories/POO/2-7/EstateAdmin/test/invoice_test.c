#include <stdio.h>
#include <assert.h>
#include "invoice_test.h"
#include "domain/invoice.h"

static void test_invoice_sum(void) {
    Invoice * invoice = create_invoice(0, 0, GAS);
    invoice_set_sum(invoice, 10);
    assert(invoice_get_sum(invoice) == 10);
    destroy_invoice(invoice);
}

static void test_invoice_apartment_number(void) {
    Invoice * invoice = create_invoice(0, 0, GAS);
    invoice_set_appartment_number(invoice, 1);
    assert(invoice_get_appartment_number(invoice) == 1);
    destroy_invoice(invoice);
}

static void test_invoice_category(void) {
    Invoice * invoice = create_invoice(0, 0, GAS);
    invoice_set_category(invoice, WATER);
    assert(invoice_get_category(invoice) == WATER);
    destroy_invoice(invoice);
}

static void test_clone_invoice(void) {
    Invoice * invoice = create_invoice(100, 1, SEWAGE);
    Invoice * clone = clone_invoice(invoice);
    assert(invoice_get_sum(invoice) == invoice_get_sum(clone));
    assert(invoice_get_appartment_number(invoice) == invoice_get_appartment_number(clone));
    assert(invoice_get_category(invoice) == invoice_get_category(clone));
    destroy_invoice(invoice);
    destroy_invoice(clone);
}

void run_invoice_tests(void) {
    printf("invoice_test\n");
    test_invoice_sum(); printf("test_invoice_sum() -> OK\n");
    test_invoice_apartment_number(); printf("test_invoice_apartment_number() -> OK\n");
    test_invoice_category(); printf("test_invoice_category() -> OK\n");
    test_clone_invoice(); printf("test_clone_invoice() -> OK\n");
    destroy_invoice(NULL); // for code coverage
    printf("\n");
}
