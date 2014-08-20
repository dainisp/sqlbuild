#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T03:56:29
#
#-------------------------------------------------

QT       += core gui xml



FLEXSOURCES = scn2.l
BISONSOURCES = sql2.y

OTHER_FILES +=  \
    $$FLEXSOURCES \
    $$BISONSOURCES

flexsource.input = FLEXSOURCES
flexsource.output = ${QMAKE_FILE_BASE}.c
flexsource.commands = flex --header-file=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.c ${QMAKE_FILE_IN}
flexsource.variable_out = SOURCES
flexsource.name = Flex Sources ${QMAKE_FILE_IN}
flexsource.CONFIG += target_predeps

#win32: SOURCES += scn2.c sql2.c

win32:RC_FILE = sqlbuild.rc

QMAKE_EXTRA_COMPILERS += flexsource

flexheader.input = FLEXSOURCES
flexheader.output = ${QMAKE_FILE_BASE}.h
flexheader.commands = @true
flexheader.variable_out = HEADERS
flexheader.name = Flex Headers ${QMAKE_FILE_IN}
flexheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += flexheader

bisonsource.input = BISONSOURCES
bisonsource.output = ${QMAKE_FILE_BASE}.c
bisonsource.commands = bison -t -d --defines=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.c ${QMAKE_FILE_IN}
bisonsource.variable_out = SOURCES
bisonsource.name = Bison Sources ${QMAKE_FILE_IN}
bisonsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += bisonsource

bisonheader.input = BISONSOURCES
bisonheader.output = ${QMAKE_FILE_BASE}.h
bisonheader.commands = @true
bisonheader.variable_out = HEADERS
bisonheader.name = Bison Headers ${QMAKE_FILE_IN}
bisonheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += bisonheader




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlbuild
TEMPLATE = app

win32: LIBS += -LC:/MinGW/msys/1.0/lib

LIBS += -ly -lfl -lfl_pic

INCLUDEPATH += /home/dainis/boost-trunk
SOURCES += main.cpp\
        mainwindow.cpp \
    cview.cpp \
    cscene.cpp \
    dialog.cpp \
    equ_dialog.cpp \
    sqlparser.cpp \
    cexpritem.cpp \
    expr_dialog.cpp \
    catable.cpp \
    calink.cpp \
    crtableitem.cpp \
    ctable.cpp

HEADERS  += mainwindow.h \
    cview.h \
    cscene.h \
    dialog.h \
    equ_dialog.h \
    cexpritem.h \
    expr_dialog.h \
    catable.h \
    calink.h \
    defaultdefs.h \
    crtableitem.h \
    ctable.h

FORMS    += mainwindow.ui \
    settings.ui \
    equ_dialog.ui \
    expr_dialog.ui

OTHER_FILES += \
    scn2.l \
    sql2.y

RESOURCES += \
    sqlbuild.qrc
