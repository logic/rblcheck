# rblcheck Makefile.
#
# $Id$
#
# $Log$
# Revision 1.2  2000/04/21 15:22:46  logic
# Update to version 1.2.
#
# Revision 1.4  1998/01/28 22:11:31  emarshal
# More portability stuff, and upgrade to version 1.2.
#
# Revision 1.3  1998/01/28 21:32:15  emarshal
# Fixes for compilation on ANSI-unfriendly systems (SunOS) and a Makefile
# change for HP/UX 10.x.
#
# Revision 1.2  1998/01/23 22:05:26  emarshal
# Some quick changes.
#
# Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
# Initial import into CVS.
#

# Do you need the resolver library? If you get some errors about
# missing symbols, uncomment this. Linux/glibc and Solaris definitely
# need this.
#RESOLV=-lresolv


# Generic GCC. This is probably your best bet on most systems, but see
# below for an entry for your system.
CC=gcc
CFLAGS=-O -Wall
LDFLAGS=-s

# Solaris w/Sun cc
#CC=cc
#CFLAGS=-O
#LDFLAGS=-s

# SunOS w/Sun cc
#CC=cc
#CFLAGS=-O
#LDFLAGS=$(LDFLAGS) -n -Bdynamic

# HP 10.x
#CC=cc
#CFLAGS=-O -Ae -D_XOPEN_SOURCE_EXTENDED
#LDFLAGS=-s


LDFLAGS += $(RESOLV)

all: rblcheck

clean:
	-rm rblcheck
