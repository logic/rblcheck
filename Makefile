# rblcheck Makefile.

# Solaris
# CC=cc
# CFLAGS=-O
# LDFLAGS=-s -lresolv

# Linux
CC=gcc
CFLAGS=-O2
LDFLAGS=-s

all: rblcheck

clean:
	-rm rblcheck
