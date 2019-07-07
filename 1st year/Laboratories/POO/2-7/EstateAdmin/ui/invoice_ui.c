#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "controller/invoice_controller.h"
#include "domain/invoice.h"
#include "util/misc.h"
#include "util/list.h"

// START OF INTERNAL FUNCTIONS

/*
 * Read a nonnegative int from data buffer.
 * Return -1 if operation did not succed.
 */
static int parse_option(char * data) {
    char * endptr;
    long long_result = strtol(data, &endptr, 10);
    if (endptr == data || *endptr != '\n' || long_result < 0 || long_result > INT_MAX) {
        return -1;
    }
    return (int)long_result;
}

/*
 * Utility function to pretty print an invoice.
 */
static void print_invoice(Invoice * invoice) {
    int sum = invoice_get_sum(invoice);
    int apartment_number = invoice_get_appartment_number(invoice);
    char * category = INVOICE_CATEGORY_STRING[invoice_get_category(invoice)];
    printf("# %16i # %16i # %16s #\n", apartment_number, sum, category);
}

/*
 * Utility function to pretty print a list of invoices with headers and then destroy the list.
 * If the list is NULL it means there was an error in the controller and FAILED will be printed.
 */
static void print_and_destroy_invoice_list(List * list) {
    int i;
    if (list == NULL) {
        printf("FAILED\n");
        return;
    }
    if (list_size(list) > 0) {
        printf("# %16s # %16s # %16s #\n", "APARTMENT", "SUM", "CATEGORY");
        for (i = 0; i < list_size(list); ++i) {
            print_invoice(list_get(list, i));
        }
    }
    printf("DONE\n");
    destroy_list(list);
}

// END OF INTERNAL FUNCTIONS

void run_invoice_ui(InvoiceController * controller) {
    int opt;
    char data[256];
    while (1) {
        printf("[ESTATE ADMIN MENU]\n");
        printf("  0 - Add invoice\n");
        printf("  1 - Modify invoice\n");
        printf("  2 - Delete invoice\n");
        printf("  3 - Show invoices filtered by sum\n");
        printf("  4 - Show invoices filtered by apartment number\n");
        printf("  5 - Show invoices filtered by category\n");
        printf("  6 - Show invoices sorted ascending by sum\n");
        printf("  7 - Show invoices sorted descending by sum\n");
        printf("  8 - Show invoices sorted ascending by category\n");
        printf("  9 - Show invoices sorted descending by category\n");
        printf(" 10 - Quit\n");
        printf(">>> ");
        fgets(data, 256, stdin);
        opt = parse_option(data);
        switch (opt) {
        case 0:
            printf("INVOICE[APARTMENT SUM CATEGORY] >>> ");
            fgets(data, 256, stdin);
            printf("%s\n", controller_add_invoice(controller, data) == SUCCESS ? "DONE" : "FAILED");
            break;
        case 1:
            printf("INVOICE[APARTMENT SUM CATEGORY] >>> ");
            fgets(data, 256, stdin);
            printf("%s\n", controller_mod_invoice(controller, data) == SUCCESS ? "DONE" : "FAILED");
            break;
        case 2:
            printf("INVOICE[APARTMENT] >>> ");
            fgets(data, 256, stdin);
            printf("%s\n", controller_del_invoice(controller, data) == SUCCESS ? "DONE" : "FAILED");
            break;
        case 3:
            printf("INVOICE[APARTMENT? SUM CATEGORY?] >>> ");
            fgets(data, 256, stdin);
            print_and_destroy_invoice_list(controller_filter_invoices(controller, data, FILTER_SUM));
            break;
        case 4:
            printf("INVOICE[APARTMENT SUM? CATEGORY?] >>> ");
            fgets(data, 256, stdin);
            print_and_destroy_invoice_list(controller_filter_invoices(controller, data, FILTER_APARTMENT_NUMBER));
            break;
        case 5:
            printf("INVOICE[APARTMENT? SUM? CATEGORY] >>> ");
            fgets(data, 256, stdin);
            print_and_destroy_invoice_list(controller_filter_invoices(controller, data, FILTER_CATEGORY));
            break;
        case 6:
            print_and_destroy_invoice_list(controller_sort_invoices(controller, SORT_SUM, 1));
            break;
        case 7:
            print_and_destroy_invoice_list(controller_sort_invoices(controller, SORT_SUM, 0));
            break;
        case 8:
            print_and_destroy_invoice_list(controller_sort_invoices(controller, SORT_CATEGORY, 1));
            break;
        case 9:
            print_and_destroy_invoice_list(controller_sort_invoices(controller, SORT_CATEGORY, 0));
            break;
        case 10:
            return;
        default:
            printf("Invalid command\n");
        }
        printf("\n");
    }
}
