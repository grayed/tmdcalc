#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T18:29:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TMDCalc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWindow.cpp \
    gui/PDFsDialog.cpp \
    lib/common/SM.cpp \
    lib/common/utils.cpp \
    gui/ScopeDialog.cpp \
    open-beauty/open-beauty-PhaseSpaceDialog.cpp \
    open-beauty/open-beauty-aux.cpp \
    open-beauty/open-beauty-OutputDialog.cpp \
    lib/common/histogram.cpp \
    lib/common/HEPVector4.cpp \
    lib/pdfs/pdf.cpp \
    lib/pdfs/grv94.cpp \
    lib/extern/ct11pdf.cc \
    lib/extern/mstwpdf.cc \
    lib/extern/dgauss.cpp \
    open-beauty/open-beauty-gg.cpp \
    lib/common/frames.cpp \
    lib/extern/vegas.c \
    lib/tmdpdfs/tmdpdf.cpp \
    lib/amplitudes/gg2qq.cpp

HEADERS  += MainWindow.h \
    gui/PDFsDialog.h \
    lib/common/SM.h \
    lib/common/utils.h \
    gui/ScopeDialog.h \
    open-beauty/open-beauty-PhaseSpaceDialog.h \
    open-beauty/open-beauty-OutputDialog.h \
    lib/common/histogram.h \
    lib/common/HEPVector4.h \
    lib/pdfs/pdf.h \
    lib/pdfs/grv94.h \
    lib/extern/ct11pdf.h \
    lib/extern/mstwpdf.h \
    lib/extern/dgauss.h \
    lib/common/frames.h \
    lib/extern/vegas.h \
    lib/tmdpdfs/tmdpdf.h \
    lib/extern/nrutil.h

FORMS    += MainWindow.ui \
    gui/PDFsDialog.ui \
    gui/ScopeDialog.ui \
    open-beauty/open-beauty-PhaseSpaceDialog.ui \
    open-beauty/open-beauty-OutputDialog.ui
