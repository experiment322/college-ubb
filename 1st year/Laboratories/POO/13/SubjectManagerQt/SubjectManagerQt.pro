#-------------------------------------------------
#
# Project created by QtCreator 2018-05-05T16:19:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubjectManagerQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Dialog.cpp \
    main.cpp \
    MainWindow.cpp \
    Subject.cpp \
    SubjectManager.cpp \
    SubjectRepo.cpp \
    Validator.cpp \
    Observer.cpp \
    ContractManager.cpp \
    ContractCRUDGUI.cpp \
    ContractReadOnlyGUI.cpp

HEADERS += \
    Dialog.h \
    List.h \
    MainWindow.h \
    Subject.h \
    SubjectManager.h \
    SubjectRepo.h \
    Validator.h \
    Ui_Dialog.h \
    Ui_MainWindow.h \
    Observer.h \
    ContractManager.h \
    ContractCRUDGUI.h \
    Ui_ContractCRUDGUI.h \
    ContractReadOnlyGUI.h \
    Ui_ContractReadOnlyGUI.h

FORMS +=

RESOURCES += \
    resources.qrc
