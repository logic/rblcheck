# rblcheck Makefile.
#
# $Id$
#
# $Log$
# Revision 1.1  2000/04/21 15:22:43  logic
# Update to version 1.1.
#
# Revision 1.2  1998/01/23 22:05:26  emarshal
# Some quick changes.
#
# Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
# Initial import into CVS.
#

# Linux/glibc, Solaris
#CC=cc
#CFLAGS=-O
#LDFLAGS=-s -lresolv

# Linux/libc5, NeXT
CC=cc
CFLAGS=-O
LDFLAGS=-s

all: rblcheck

clean:
	-rm rblcheck
