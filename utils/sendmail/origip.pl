#!/usr/bin/perl

# Specifically for pulling the remote IP address out of Sendmail
# Received: headers. Supplied by Ophir Ronen <ophir@internap.com>,
# ever-so-slightly modified by Edward S. Marshall <emarshal@logic.net>.
#
# $Id$
#
# $Log$
# Revision 1.2  2000/04/21 15:22:46  logic
# Update to version 1.2.
#
# Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
# Initial import into CVS.
#

@msg = <STDIN>;

foreach $line ( @msg )
{
	chop $line;

	if( $line =~ /.*\[(\d+.*)\]/ )
	{
		$REMOTEIP = $1;
		last;
	}
}
print STDOUT ( $REMOTEIP );
