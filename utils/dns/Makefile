# DNS Utilities Makefile.
#
# $Id$
#
# $Log$
# Revision 1.1  2000/04/21 15:22:43  logic
# Update to version 1.1.
#
# Revision 1.1  1998/01/27 02:10:33  emarshal
# Added dump.c, a quick utility for dumping an RR (sort of);
# suitable for hexdumping.
#

# Linux/glibc, Solaris
#CC=cc
#CFLAGS=-O
#LDFLAGS=-s -lresolv

# Linux/libc5, NeXT
CC=cc
CFLAGS=-g -Wall
LDFLAGS=-s

all: dump

clean:
	-rm dump
