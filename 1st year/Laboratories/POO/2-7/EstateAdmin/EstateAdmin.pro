TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    controller/invoice_controller.c \
    domain/invoice.c \
    repository/invoice_repository.c \
    test/invoice_controller_test.c \
    test/invoice_repository_test.c \
    test/invoice_test.c \
    test/list_test.c \
    test/misc_test.c \
    ui/invoice_ui.c \
    util/list.c \
    util/misc.c \
    main.c

HEADERS += \
    controller/invoice_controller.h \
    domain/invoice.h \
    repository/invoice_repository.h \
    test/invoice_controller_test.h \
    test/invoice_repository_test.h \
    test/invoice_test.h \
    test/list_test.h \
    test/misc_test.h \
    ui/invoice_ui.h \
    util/list.h \
    util/misc.h

SUBDIRS +=

DISTFILES +=
