#!/bin/sh

# Quick test script to try the messages in a Maildir for a successful
# retrieval of the sending IP address from the message. On a failure,
# we're told about it. Good for testing for failures in the code.
#
# $Id$
#
# $Log$
# Revision 1.4  2000/04/21 15:22:51  logic
# Update to version 1.4.
#
# Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
# Initial import into CVS.
#


#MAILDIR=$HOME/Maildir

#for i in $MAILDIR/cur/* $MAILDIR/new/*
for i in /u/staff/emarshal/mail/inboxes/*/*/*
do
	x="`cat $i | ./origip`"
	if [ -z "$x" ]
	then
		echo "failure: $i"
	fi
done
