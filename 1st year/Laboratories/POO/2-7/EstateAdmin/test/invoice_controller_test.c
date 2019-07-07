#include <stdio.h>
#include <assert.h>
#include "invoice_controller_test.h"
#include "util/list.h"
#include "util/misc.h"
#include "domain/invoice.h"
#include "repository/invoice_repository.h"
#include "controller/invoice_controller.h"

static void test_invoice_controller_add_invoice(void) {
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    assert(controller_add_invoice(controller, "bad") == FAILURE);
    assert(controller_add_invoice(controller, "0 100 WATER") == FAILURE);
    assert(controller_add_invoice(controller, "1 -1 GAS") == FAILURE);
    assert(controller_add_invoice(controller, "1 100 WATE") == FAILURE);
    assert(controller_add_invoice(controller, "1 100 SEWAGE") == SUCCESS);
    assert(controller_add_invoice(controller, "1 200 HEATING") == FAILURE);
    assert(controller_add_invoice(controller, "2 200 HEATING") == SUCCESS);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}

static void test_invoice_controller_mod_invoice(void) {
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    assert(controller_mod_invoice(controller, "bad") == FAILURE);
    assert(controller_mod_invoice(controller, "1 100 GAS") == FAILURE);
    assert(controller_add_invoice(controller, "1 200 WATER") == SUCCESS);
    assert(controller_mod_invoice(controller, "1 100 GAS") == SUCCESS);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}

static void test_invoice_controller_del_invoice(void) {
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    assert(controller_del_invoice(controller, "bad") == FAILURE);
    assert(controller_add_invoice(controller, "1 100 SEWAGE") == SUCCESS);
    assert(controller_del_invoice(controller, "1 dsadas") == SUCCESS);
    assert(controller_del_invoice(controller, "1") == FAILURE);
    assert(controller_add_invoice(controller, "1 100 SEWAGE") == SUCCESS);
    assert(controller_del_invoice(controller, "1") == SUCCESS);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}

static void test_invoice_controller_sort_invoices(void) {
    int i;
    List * sorted_invoices;
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    controller_add_invoice(controller, "2 200 WATER");
    controller_add_invoice(controller, "4 400 HEATING");
    controller_add_invoice(controller, "1 100 GAS");
    controller_add_invoice(controller, "3 300 SEWAGE");
    sorted_invoices = controller_sort_invoices(controller, SORT_SUM, 1);
    for (i = 0; i < list_size(sorted_invoices); ++i) {
        assert(invoice_get_appartment_number(list_get(sorted_invoices, i)) == i + 1);
    }
    destroy_list(sorted_invoices);
    sorted_invoices = controller_sort_invoices(controller, SORT_SUM, 0);
    for (i = 0; i < list_size(sorted_invoices); ++i) {
        assert(invoice_get_appartment_number(list_get(sorted_invoices, i)) == list_size(sorted_invoices) - i);
    }
    destroy_list(sorted_invoices);
    sorted_invoices = controller_sort_invoices(controller, SORT_CATEGORY, 1);
    for (i = 0; i < list_size(sorted_invoices); ++i) {
        assert(invoice_get_appartment_number(list_get(sorted_invoices, i)) == i + 1);
    }
    destroy_list(sorted_invoices);
    sorted_invoices = controller_sort_invoices(controller, SORT_CATEGORY, 0);
    for (i = 0; i < list_size(sorted_invoices); ++i) {
        assert(invoice_get_appartment_number(list_get(sorted_invoices, i)) == list_size(sorted_invoices) - i);
    }
    destroy_list(sorted_invoices);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}

static void test_invoice_controller_filter_invoices(void) {
    List * filtered_invoices;
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    controller_add_invoice(controller, "1 100 GAS");
    controller_add_invoice(controller, "2 100 WATER");
    controller_add_invoice(controller, "3 300 SEWAGE");
    controller_add_invoice(controller, "4 400 SEWAGE");
    assert(controller_filter_invoices(controller, "bad", FILTER_SUM) == NULL);
    filtered_invoices = controller_filter_invoices(controller, "2 0 GAS", FILTER_APARTMENT_NUMBER);
    assert(list_size(filtered_invoices) == 1);
    assert(invoice_get_appartment_number(list_get(filtered_invoices, 0)) == 2);
    destroy_list(filtered_invoices);
    filtered_invoices = controller_filter_invoices(controller, "1 0 SEWAGE", FILTER_CATEGORY);
    assert(list_size(filtered_invoices) == 2);
    assert(invoice_get_appartment_number(list_get(filtered_invoices, 0)) == 3);
    assert(invoice_get_appartment_number(list_get(filtered_invoices, 1)) == 4);
    destroy_list(filtered_invoices);
    filtered_invoices = controller_filter_invoices(controller, "1 100 GAS", FILTER_SUM);
    assert(list_size(filtered_invoices) == 2);
    assert(invoice_get_appartment_number(list_get(filtered_invoices, 0)) == 1);
    assert(invoice_get_appartment_number(list_get(filtered_invoices, 1)) == 2);
    destroy_list(filtered_invoices);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}

void run_invoice_controller_tests(void) {
    printf("invoice_controller_test\n");
    test_invoice_controller_add_invoice(); printf("test_invoice_controller_add_invoice() -> OK\n");
    test_invoice_controller_mod_invoice(); printf("test_invoice_controller_mod_invoice() -> OK\n");
    test_invoice_controller_del_invoice(); printf("test_invoice_controller_del_invoice() -> OK\n");
    test_invoice_controller_sort_invoices(); printf("test_invoice_controller_sort_invoices() -> OK\n");
    test_invoice_controller_filter_invoices(); printf("test_invoice_controller_filter_invoices() -> OK\n");
    destroy_invoice_controller(NULL); // for code coverage
    printf("\n");
}
