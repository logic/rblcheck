# Makefile for origip.
#
# $Id$
#
# $Log$
# Revision 1.3  2000/04/21 15:22:48  logic
# Update to version 1.3.
#
# Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
# Initial import into CVS.
#

CC=gcc
CFLAGS=-O2
LDFLAGS=-s

all: origip

clean:
	-rm origip

test:
	@echo "Testing 'origip'..."
	./test_origip.sh
	@echo "Testing 'rblcheck'..."
	./test_rblcheck.sh
