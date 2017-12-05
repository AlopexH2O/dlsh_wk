#############################################################################
# Makefile for building: libwk_dlsh.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.5.3) on: ?? 12? 4 21:34:01 2017
# Project:  wk_dlsh.pro
# Template: lib
# Command: /usr/local/Trolltech/Qt-4.5.3/bin/qmake -unix -o Makefile wk_dlsh.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DSOPHIC_THREAD_8BYTE -DQ4_PLATFORM -DSOPHIC_UNIX -DACE_HAS_EXCEPTIONS -D_LOG -DQT_QT3SUPPORT_LIB -DQT3_SUPPORT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -fpermissive -pipe -g -D_REENTRANT -w -fPIC $(DEFINES)
CXXFLAGS      = -m64 -fpermissive -pipe -g -D_REENTRANT -w -fPIC $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/Qt-4.5.3/mkspecs/linux-g++-64 -I. -I/usr/local/Trolltech/Qt-4.5.3/include/QtCore -I/usr/local/Trolltech/Qt-4.5.3/include/QtGui -I/usr/local/Trolltech/Qt-4.5.3/include/Qt3Support -I/usr/local/Trolltech/Qt-4.5.3/include -I../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/moc -I$(ACE_ROOT)
LINK          = g++
LFLAGS        = -m64 -fpermissive -Wl,-rpath,/usr/local/Trolltech/Qt-4.5.3/lib -shared -Wl,-soname,libwk_dlsh.so
LIBS          = $(SUBLIBS)  -L$(ACE_ROOT)/ace -L/usr/local/Trolltech/Qt-4.5.3/lib -lQt3Support -L/usr/local/Trolltech/Qt-4.5.3/lib -L$(ACE_ROOT)/ace -lQtSql -pthread -pthread -pthread -pthread -lQtXml -pthread -pthread -pthread -pthread -L/usr/X11R6/lib64 -pthread -pthread -pthread -pthread -pthread -pthread -lQtNetwork -pthread -pthread -pthread -pthread -pthread -pthread -lQtGui -pthread -lpng -lfreetype -lgobject-2.0 -lSM -lICE -pthread -pthread -lXrender -lfontconfig -lXext -lX11 -lQtCore -lACE -lz -lm -pthread -lgthread-2.0 -lrt -lglib-2.0 -lpthread -ldl
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/local/Trolltech/Qt-4.5.3/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/

####### Files

SOURCES       = MainLogic.cpp \
		TestCase.cpp \
		test.cpp 
OBJECTS       = ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/MainLogic.o \
		../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/TestCase.o \
		../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/test.o
DIST          = /usr/local/Trolltech/Qt-4.5.3/mkspecs/common/g++.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/warn_off.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/lex.prf \
		wk_dlsh.pro
QMAKE_TARGET  = wk_dlsh
DESTDIR       = ../../../../sophic/deployment/bin/wk/
TARGET        = libwk_dlsh.so
TARGETA       = ../../../../sophic/deployment/bin/wk/libwk_dlsh.a
TARGET0       = libwk_dlsh.so
TARGET1       = libwk_dlsh.so
TARGET2       = libwk_dlsh.so

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  ../../../../sophic/deployment/bin/wk/$(TARGET)

../../../../sophic/deployment/bin/wk/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) ../../../../sophic/deployment/bin/wk/ || $(MKDIR) ../../../../sophic/deployment/bin/wk/ 
	-$(DEL_FILE) $(TARGET)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	
	-$(DEL_FILE) ../../../../sophic/deployment/bin/wk/$(TARGET)
	-$(MOVE) $(TARGET)  ../../../../sophic/deployment/bin/wk/



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

Makefile: wk_dlsh.pro  /usr/local/Trolltech/Qt-4.5.3/mkspecs/linux-g++-64/qmake.conf /usr/local/Trolltech/Qt-4.5.3/mkspecs/common/g++.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/warn_off.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQt3Support.prl \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQtSql.prl \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQtCore.prl \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQtXml.prl \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQtGui.prl \
		/usr/local/Trolltech/Qt-4.5.3/lib/libQtNetwork.prl
	$(QMAKE) -unix -o Makefile wk_dlsh.pro
/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/g++.conf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/unix.conf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/common/linux.conf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/qconfig.pri:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/debug.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/default_post.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/warn_off.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/qt.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/moc.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/resources.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/uic.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/yacc.prf:
/usr/local/Trolltech/Qt-4.5.3/mkspecs/features/lex.prf:
/usr/local/Trolltech/Qt-4.5.3/lib/libQt3Support.prl:
/usr/local/Trolltech/Qt-4.5.3/lib/libQtSql.prl:
/usr/local/Trolltech/Qt-4.5.3/lib/libQtCore.prl:
/usr/local/Trolltech/Qt-4.5.3/lib/libQtXml.prl:
/usr/local/Trolltech/Qt-4.5.3/lib/libQtGui.prl:
/usr/local/Trolltech/Qt-4.5.3/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile wk_dlsh.pro

dist: 
	@$(CHK_DIR_EXISTS) ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0 || $(MKDIR) ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0/ && $(COPY_FILE) --parents systac.h DeviceSet.h DeviceDef.h DevLogic.h ../include/simulator_define.h TestCase.h ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0/ && $(COPY_FILE) --parents MainLogic.cpp TestCase.cpp test.cpp ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0/ && (cd `dirname ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0` && $(TAR) wk_dlsh1.0.0.tar wk_dlsh1.0.0 && $(COMPRESS) wk_dlsh1.0.0.tar) && $(MOVE) `dirname ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0`/wk_dlsh1.0.0.tar.gz . && $(DEL_FILE) -r ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/wk_dlsh1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) ../../../../sophic/deployment/bin/wk/$(TARGET) 
	-$(DEL_FILE) ../../../../sophic/deployment/bin/wk/$(TARGET0) ../../../../sophic/deployment/bin/wk/$(TARGET1) ../../../../sophic/deployment/bin/wk/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/MainLogic.o: MainLogic.cpp systac.h \
		../include/simulator_define.h \
		DevLogic.h \
		DeviceSet.h \
		DeviceDef.h \
		TestCase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/MainLogic.o MainLogic.cpp

../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/TestCase.o: TestCase.cpp TestCase.h \
		DeviceDef.h \
		../include/simulator_define.h \
		systac.h \
		DeviceSet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/TestCase.o TestCase.cpp

../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/test.o: test.cpp ../include/simulator_define.h \
		systac.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ../../../../sophic/source/pcs_ems_application/scada_wk/wk_dlsh/obj/test.o test.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
