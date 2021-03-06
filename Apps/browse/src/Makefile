#############################################################################
# Makefile for building browse
# Created with BruceLee's SDK version: 2011/08/31
# Generated by tmake at 16:46, 2011/11/22
#     Project: browse
#    Template: app
#############################################################################

####### Compiler, tools and options

CC		=	$(SDK_CC)
CXX		=	$(SDK_CXX)
CFLAGS	=	-pipe -Wall -W -O2 -mcpu=iwmmxt -mtune=iwmmxt -DNO_DEBUG
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -Wno-deprecated -O2 -mcpu=iwmmxt -mtune=iwmmxt -DNO_DEBUG
INCPATH	=	-I$(QTDIR)/include -I$(QTDIR)/include/qt -I$(QTDIR)/include/ezx -I$(QTDIR)/include/tapi -I$(QTDIR)/include/qt-ext
LINK	=	$(SDK_CXX)
LFLAGS	=	
LIBS	=	$(SUBLIBS) -L$(SDK_EZX_LIB_DIR) -lipp-jp -lipp-miscGen -lezxappbase -lqte-mt -lezxjpeg -lezxpm -lezxam -ldmnative -lezxsound -lezxphone -lezxdrmsp -lezxdrmcipher -lezx-cmseccert -lezxtapi -lezxssl -lezxdrmsecuretime -lcipci
STRIP	=	$(SDK_STRIP)
MOC		=	$(QTDIR)/bin/moc
UIC		=	$(QTDIR)/bin/uic

TAR		=	tar -cf
GZIP	=	gzip -9f

####### Files

HEADERS =	app.h \
		filebrowser.h \
		fileview.h
SOURCES =	app.cpp \
		filebrowser.cpp \
		fileview.cpp \
		main.cpp
OBJECTS =	app.o \
		filebrowser.o \
		fileview.o \
		main.o
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_app.cpp \
		moc_filebrowser.cpp \
		moc_fileview.cpp
OBJMOC	=	moc_app.o \
		moc_filebrowser.o \
		moc_fileview.o
DIST	=	
TARGET	=	browse
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules


all: help

lib: lib-shared
	
lib-shared: $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(CC) -shared -o lib$(TARGET).so $(OBJECTS) $(OBJMOC) -lc

lib-static: $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(AR) rcs lib$(TARGET).a $(OBJECTS) $(OBJMOC)
	
bin: $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET).unstripped $(OBJECTS) $(OBJMOC) $(LIBS)
	-cp -u $(TARGET).unstripped $(TARGET)
	$(STRIP) $(TARGET)

moc: $(SRCMOC)

tmake: Makefile

Makefile: browse.pro
	tmake browse.pro -o Makefile

dist:
	$(TAR) browse-src[EZX].tar browse.pro Makefile $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) browse-src[EZX].tar

almostclean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET).unstripped
	-rm -f *~ core

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET).unstripped $(TARGET) lib$(TARGET).so lib$(TARGET).a $(TARGET)-src[EZX].tar.gz
	-rm -f *~ core
	
help:
	@printf "\n * Syntax: make bin | lib | lib-shared | lib-static | dist | clean | almostclean | help\n\n"

####### Sub-libraries


###### Combined headers


####### Compile

app.o: app.cpp

filebrowser.o: filebrowser.cpp \
		filebrowser.h \
		app.h \
		fileview.h

fileview.o: fileview.cpp \
		fileview.h

main.o: main.cpp \
		app.h \
		filebrowser.h \
		fileview.h

moc_app.o: moc_app.cpp \
		app.h \
		filebrowser.h \
		app.h \
		fileview.h

moc_filebrowser.o: moc_filebrowser.cpp \
		filebrowser.h \
		app.h \
		filebrowser.h \
		fileview.h

moc_fileview.o: moc_fileview.cpp \
		fileview.h

moc_app.cpp: app.h
	$(MOC) app.h -o moc_app.cpp

moc_filebrowser.cpp: filebrowser.h
	$(MOC) filebrowser.h -o moc_filebrowser.cpp

moc_fileview.cpp: fileview.h
	$(MOC) fileview.h -o moc_fileview.cpp

