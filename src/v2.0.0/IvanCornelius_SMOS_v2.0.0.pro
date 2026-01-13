TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    EmployeeMobSub.cpp \
        IndividualMobSub.cpp \
    LegalEntityMobSub.cpp \
        MobileSub.cpp \
        main.cpp \

HEADERS += \
    EmployeeMobSub.h \
    IndividualMobSub.h \
    LegalEntityMobSub.h \
    MobileSub.h \
