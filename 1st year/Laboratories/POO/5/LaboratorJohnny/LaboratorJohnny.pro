TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Domain/Medicine/Medicine.c \
    Domain/Medicine/MedicineValidator.c \
    Domain/DomainTest.c \
    Repository/MedicineRepository/MedicineRepository.c \
    Repository/RepositoryTest.c \
    Service/MedicineService/MedicineService.c \
    Service/MedicineServiceTests.c \
    UI/UI.c \
    Utils/List.c \
    Utils/Utils.c \
    ListTest.c \
    main.c \
    UtilsTest.c

HEADERS += \
    Domain/Medicine/Medicine.h \
    Domain/Medicine/MedicineValidator.h \
    Domain/DomainTest.h \
    Repository/MedicineRepository/MedicineRepository.h \
    Repository/RepositoryTest.h \
    Service/MedicineService/MedicineService.h \
    Service/MedicineServiceTests.h \
    UI/UI.h \
    Utils/List.h \
    Utils/Utils.h \
    ListTest.h \
    UtilsTest.h
