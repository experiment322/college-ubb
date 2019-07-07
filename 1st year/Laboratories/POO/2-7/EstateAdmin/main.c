#ifdef RUN_TESTS
#include "test/misc_test.h"
#include "test/list_test.h"
#include "test/invoice_test.h"
#include "test/invoice_repository_test.h"
#include "test/invoice_controller_test.h"

// Driver for running tests
static void run(void) {
    run_misc_tests();
    run_list_tests();
    run_invoice_tests();
    run_invoice_repository_tests();
    run_invoice_controller_tests();
}
#else
#include "ui/invoice_ui.h"
#include "repository/invoice_repository.h"
#include "controller/invoice_controller.h"

// Driver for the main program
static void run(void) {
    InvoiceController * controller = create_invoice_controller(create_invoice_repository());
    run_invoice_ui(controller);
    destroy_invoice_repository(destroy_invoice_controller(controller));
}
#endif

// Compile with -DRUN_TESTS to run the tests
int main(void) {
    run();
    return 0;
}
