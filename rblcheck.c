/*
** rblcheck 1.2 - Command-line interface to Paul Vixie's RBL filter.
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
** $Id$
**
** Revision history:
**
** 27-Nov-97 [emarshal@logic.net]: Created.
** 08-Dec-97 [emarshal@logic.net]: Patched to properly use res_query()
**     responses, instead of just hoping for the best with a packet
**     size.
**
** $Log$
** Revision 1.2  2000/04/21 15:22:46  logic
** Update to version 1.2.
**
** Revision 1.7  1998/01/28 22:11:31  emarshal
** More portability stuff, and upgrade to version 1.2.
**
** Revision 1.6  1998/01/28 21:44:06  emarshal
** Fixed compilation for systems without getshort() provided by the resolver
** header files (NeXTSTEP).
**
** Revision 1.5  1998/01/28 21:32:15  emarshal
** Fixes for compilation on ANSI-unfriendly systems (SunOS) and a Makefile
** change for HP/UX 10.x.
**
** Revision 1.4  1998/01/27 23:42:21  emarshal
** Version update.
**
** Revision 1.3  1998/01/27 02:09:56  emarshal
** Added support for returning TXT records associated with
** RBL-filtered addresses.
**
** Revision 1.2  1998/01/23 22:05:27  emarshal
** Some quick changes.
**
** Revision 1.1.1.1  1998/01/09 20:42:50  emarshal
** Initial import into CVS.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netdb.h>

#define VERSION "1.2"
#define DOMAIN_LENGTH 32            /* "xxx.xxx.xxx.xxx.rbl.maps.vix.com" */
#define RBLSITE "rbl.maps.vix.com"  /* What is the RBL root domain? */

/*
** PORTABILITY STUFF.
** I'll happily take patches relating to this section, if you find a
** platform that this doesn't compile on.
*/

/* Unabashedly borrowed from the bind 8.1.1 sources, just in case, since
   bind 4.x defines these differently, and some don't even have this. */

#ifndef NS_INT16SZ
#define NS_INT16SZ 2
#endif

#ifndef NS_INT32SZ
#define NS_INT32SZ 4
#endif

#ifndef NS_GET16
#define NS_GET16(s, cp) { \
	register unsigned char *t_cp = (unsigned char *)(cp); \
	(s) = ((unsigned short)t_cp[0] << 8) \
	    | ((unsigned short)t_cp[1]) \
	    ; \
	(cp) += NS_INT16SZ; \
}
#endif

/* This might actually be needed on other platforms. */
#if defined(linux)
#include <getopt.h>
#endif

/* NeXT puts optind's declaration in libc.h. */
#ifdef NeXT
#include <libc.h>
#endif

/* Some compilers dont understand 'const'. */
#ifndef __STDC__
#define const
#endif

const char * progname;

void version()
{
	fprintf( stderr,
	  "rblcheck %s, Copyright (C) 1997, 1998 Edward S. Marshall\n",
	  VERSION );
}

void usage()
{
	version();
	fprintf( stderr, "Usage: %s [-q] [-t] [-v] [-h|-?] <address>\n\n\
    -q        Quiet mode; no output\n\
    -t        Print a TXT record, if any\n\
    -h, -?    Display this help message\n\
    -v        Display version information\n", progname );
}

int main( argc, argv )
	int argc;
	char **argv;
{
	extern int optind;
	u_char answer[ PACKETSZ ];
	int a, b, c, d;
	int quiet = 0;
	int txt = 0;
	char domain[ DOMAIN_LENGTH ];
	const u_char * cp;
	const u_char * end;

	progname = argv[ 0 ];

	while( ( a = getopt( argc, argv, "qt?hv" ) ) != EOF )
		switch( a )
		{
			case 'q':
				/* Quiet */
				quiet = 1;
				break;
			case 't':
				/* Display TXT */
				txt = 1;
				break;
			case '?':
			case 'h':
				/* Help */
				usage();
				return 0;
			case 'v':
				/* Verision */
				version();
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
	sprintf( domain, "%d.%d.%d.%d.%s", d, c, b, a, RBLSITE );

	/* Make our DNS query. */
	res_init();
	res_query( domain, C_IN, txt ? T_TXT : T_A, answer, PACKETSZ );

	/* Was there a problem? */
	if( h_errno != 0 )
	{
		if( !quiet )
			fprintf( stderr, "not RBL filtered\n" );
		return 0;
	}

	if( !quiet )
		fprintf( stderr, "RBL filtered\n" );

	/* Did the user ask for the TXT record? */
	if( txt )
	{
		/* Skip the header and the address we queried. */
		cp = answer + sizeof( HEADER );
		while( *cp != '\0' )
		{
			a = *cp++;
			while( a-- )
				cp++;
		}

		/* This seems to be a bit of magic data that we need to
		   skip. I wish there were good online documentation
		   for programming for libresolv, so I'd know what I'm
		   skipping here. Anyone reading this, feel free to
		   enlighten me. */
		cp += 1 + NS_INT16SZ + NS_INT32SZ;

		/* Skip the type, class and ttl. */
		cp += ( NS_INT16SZ * 2 ) + NS_INT32SZ;

		/* Get the length and end of the buffer. */
		NS_GET16( c, cp );
		end = cp + c;

		/* Iterate over any multiple answers we might have. In
		   this context, it's unlikely, but anyway. */
		while( cp < end )
		{
			a = *cp++;
			if( a != 0 )
				for( b = a; b > 0 && cp < end ; b-- )
				{
					if( *cp == '\n' || *cp == '"' ||
					  *cp == '\\' )
						putc( '\\', stdout );
					putc( *cp, stdout );
					cp++;
				}
		}
		putc( '\n', stdout );
	}
	return 1;
}
