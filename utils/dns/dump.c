/*
** dump.c
**
** This little utility pulls in a DNS query, and dumps it, suitable for
** a hexdumper. :-) Just a little tool I find handy in a pinch.
**
** $Id$
**
** $Log$
** Revision 1.6  2000/04/21 15:22:57  logic
** Update to current cvs tree.
**
** Revision 1.1  1998/01/27 02:10:34  emarshal
** Added dump.c, a quick utility for dumping an RR (sort of);
** suitable for hexdumping.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netdb.h>
#include <getopt.h>

int main( int argc, char * argv[] )
{
	int i;
	char domain[] = "2.0.0.127.rbl.maps.vix.com";
	u_char buf[ PACKETSZ ];

	/* Here we go... */
	res_init();
	res_query( domain, C_IN, T_TXT, buf, PACKETSZ );

	/* Was there a problem? */
	if( h_errno != 0 )
		return 0;

	for( i = 0; i < PACKETSZ; i++ )
		putc( buf[ i ], stdout );

	return 0;
}
