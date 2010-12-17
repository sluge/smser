#############################################################################
# Makefile for building: smser
# Generated by qmake (2.01a) (Qt 4.6.3) on: Mon Dec 6 11:09:30 2010
# Project:  smser.pro
# Template: subdirs
# Command: /usr/local/qtsdk-2010.04/qt/bin/qmake -spec /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile smser.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/local/qtsdk-2010.04/qt/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-src

src/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src/ || $(MKDIR) src/ 
	cd src/ && $(QMAKE) /home/igor/prj/smser/src/src.pro -spec /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-src-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src/ || $(MKDIR) src/ 
	cd src/ && $(QMAKE) /home/igor/prj/smser/src/src.pro -spec /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o $(MAKEFILE)
sub-src: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE)
sub-src-make_default: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) 
sub-src-make_first: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) first
sub-src-all: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) all
sub-src-clean: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-distclean: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-install_subtargets: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) install
sub-src-uninstall_subtargets: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: smser.pro  /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++/qmake.conf /usr/local/qtsdk-2010.04/qt/mkspecs/common/g++.conf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/common/unix.conf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/common/linux.conf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/qconfig.pri \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt_functions.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt_config.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/exclusive_builds.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/default_pre.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/debug.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/default_post.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/warn_on.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/unix/thread.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/moc.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/resources.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/uic.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/yacc.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/lex.prf \
		/usr/local/qtsdk-2010.04/qt/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile smser.pro
/usr/local/qtsdk-2010.04/qt/mkspecs/common/g++.conf:
/usr/local/qtsdk-2010.04/qt/mkspecs/common/unix.conf:
/usr/local/qtsdk-2010.04/qt/mkspecs/common/linux.conf:
/usr/local/qtsdk-2010.04/qt/mkspecs/qconfig.pri:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt_functions.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt_config.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/exclusive_builds.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/default_pre.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/debug.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/default_post.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/warn_on.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/qt.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/unix/thread.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/moc.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/resources.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/uic.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/yacc.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/lex.prf:
/usr/local/qtsdk-2010.04/qt/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /usr/local/qtsdk-2010.04/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile smser.pro

qmake_all: sub-src-qmake_all FORCE

make_default: sub-src-make_default FORCE
make_first: sub-src-make_first FORCE
all: sub-src-all FORCE
clean: sub-src-clean FORCE
distclean: sub-src-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-src-install_subtargets FORCE
uninstall_subtargets: sub-src-uninstall_subtargets FORCE

sub-src-check: src/$(MAKEFILE)
	cd src/ && $(MAKE) check
check: sub-src-check

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

