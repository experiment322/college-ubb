TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Console.h \
    List.h \
    Subject.h \
    SubjectManager.h \
    SubjectRepo.h \
    Validator.h

SOURCES += \
    Console.cpp \
    main.cpp \
    Subject.cpp \
    SubjectManager.cpp \
    SubjectRepo.cpp \
    Validator.cpp

