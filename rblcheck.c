/*
** rblcheck 1.0 - Command-line interface to Paul Vixie's RBL filter.
** Copyright (C) 1997, Edward S. Marshall <emarshal@logic.net>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** 27-Nov-97 [emarshal@logic.net]: Created.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netdb.h>

/* This might actually be needed on other platforms. */
#ifdef linux
#include <getopt.h>
#endif

/* Is this enough? */
#define BUF_SIZE 255

/* "xxx.xxx.xxx.xxx.rbl.maps.vix.com" */
#define DOMAIN_LENGTH 32

char * progname;

void usage()
{
	fprintf( stderr, "Usage: %s <address>\n", progname );
}

int main( int argc, char * argv[] )
{
	u_char answer[ BUF_SIZE ];
	int a, b, c, d;
	int quiet = 0;
	char domain[ DOMAIN_LENGTH ];

	progname = argv[ 0 ];

	while( ( a = getopt( argc, argv, "q?h" ) ) != EOF )
		switch( a )
		{
			case 'q':
				/* Quiet */
				quiet = 1;
				break;
			case '?':
			case 'h':
				/* Help */
				usage();
				return 0;
		}

	if( optind == argc )
	{
		fprintf( stderr, "%s: no IP address specified\n",
		  progname );
		usage();
		return 1;
	}

	if( sscanf( argv[ optind ], "%d.%d.%d.%d", &a, &b, &c, &d ) != 4 ||
	  a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 ||
	  d < 0 || d > 255 )
	{
		fprintf( stderr, "%s: invalid IP address\n", progname );
		usage();	
		return 1;
	}

	/* Create a domain name, in reverse. */
	sprintf( domain, "%d.%d.%d.%d.rbl.maps.vix.com", d, c, b, a );

	/* Here we go... */
	res_init();
	bzero( answer, BUF_SIZE );
	res_query( domain, C_IN, T_A, answer, BUF_SIZE );
	if( h_errno != 0 )
	{
		if( !quiet )
			fprintf( stderr, "not RBL filtered\n" );
		return 0;
	}
	if( !quiet )
		fprintf( stderr, "RBL filtered\n" );
	return 1;
}
