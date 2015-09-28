###############################################################################
# Makefile.  Generated from Makefile.in by configure.
# Makefile for the DMalloc library.
# $Id: Makefile.in,v 1.3 2010-05-07 15:12:37 gray Exp $
###############################################################################

# default root installation directory
prefix = /usr/local
exec_prefix = ${prefix}

srcdir = .


libdir = ${exec_prefix}/lib
includedir = ${prefix}/include

# default c-compiler
CC = gcc

DEFS = $(DEFINES)
INCS = -I. -I$(srcdir) $(INCLUDES)
LIBS = -L. 
A_OUT = aout

MODULE	= md5
LIBRARY	= lib$(MODULE).a

# now construct our build and install targets
BUILD_ALL = $(LIBRARY)
INSTALL_LIB = $(LIBRARY)

CCFLAGS = -g -O2 -fPIC
LDFLAGS = 

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

PORTFLS	= Makefile.in configure.ac configure README.txt md5.[ch] md5_loc.h md5_t.c rfc1321.txt conf.h.in \
	install-sh mkinstalldirs

###############################################################################
# End of system configuration section.
###############################################################################

SHELL = /bin/sh

HFLS = md5.h conf.h
OBJS = md5.o

CFLAGS = $(CCFLAGS)
TEST = $(MODULE)_t

all : $(BUILD_ALL)

clean :
	rm -f $(A_OUT) core *.o *.t
	rm -f $(LIBRARY) $(TEST)

realclean : clean

distclean : clean
	rm -f confdefs.h config.status config.log config.cache conf.h
	rm -f configure.lineno
	rm -rf autom4te.cache
	rm -f Makefile

installdirs :
	$(srcdir)/mkinstalldirs $(includedir) $(libdir) $(bindir)

installincs : $(HFLS)
	$(srcdir)/mkinstalldirs $(includedir)
	$(INSTALL_DATA) $(HFLS) $(includedir)

installlib : $(INSTALL_LIB)
	$(srcdir)/mkinstalldirs $(libdir)
	$(INSTALL_DATA) $(LIBRARY) $(libdir)
	ranlib $(libdir)/$(LIBRARY)

install : installincs installlib

$(LIBRARY) : $(OBJS) $(NORMAL_OBJS)
	ar cr $@ $?
	ranlib $@

tests : $(TEST)
	./$(TEST)

$(TEST) : $(TEST).o $(LIBRARY)
	rm -f $@
	$(CC) $(LDFLAGS) -o $(A_OUT) $(TEST).o $(LIBRARY)
	mv $(A_OUT) $@

.c.o :
	rm -f $@
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) $(INCS) -c $< -o ./$@

port :: $(PORTFLS)
	rm -rf $@
	mkdir $@
	cp $(PORTFLS) $@
	@ echo ''
	@ echo 'Please rename $@ to md5-version and tar up file'

###############################################################################
#
# These dependencies are automatically generated.  Do not edit by hand.
#

md5.o: md5.c conf.h md5.h md5_loc.h
md5_t.o: md5_t.c md5.h
