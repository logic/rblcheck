# Makefile for origip.
#
# $Id$
#
# $Log$
# Revision 1.5  2000/04/21 15:22:54  logic
# Update to alpha release 19990221.
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
