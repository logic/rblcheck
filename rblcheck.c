/*
** rblcheck 1.5 - Command-line interface to RBL-style filters.
** Copyright (C) 1997, 1998, 1999, 2000, 2001,
** Edward S. Marshall <esm@logic.net>
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
*/

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <netdb.h>

/*-- PORTABILITY ------------------------------------------------------------*/

#ifdef STDC_HEADERS
#include <stdlib.h>
#endif

/* getopt() handling, for Linux (and probably others) */
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

/* NeXT puts optind's declaration in libc.h. */
#ifdef HAVE_LIBC_H
#include <libc.h>
#endif

/* FreeBSD 3.x needs this. */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

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

#ifndef T_TXT
#define T_TXT 16
#endif

#ifndef PACKETSZ
#define PACKETSZ 512
#endif

/*-- LOCAL DEFINITIONS ------------------------------------------------------*/

#define RESULT_SIZE 4096 /* What is the longest result text we support? */

/*-- GLOBAL VARIABLES -------------------------------------------------------*/

/* Simple linked list to hold the sites we support. See sites.h. */
struct rbl
{
	char * site;
	struct rbl * next;
};
struct rbl * rblsites = NULL;

/* Name the program was invoked as. */
const char * progname;

/* Global options. */
int quiet = 0;
int txt = 0;
int firstmatch = 0;

/*-- FUNCTIONS --------------------------------------------------------------*/

/* version()
 * Display the version of this program back to the user. */
void version()
{
	fprintf( stderr,
	  "%s %s\nCopyright (C) 1997, 1998, 1999, 2000, 2001 Edward S. Marshall\n",
	  PACKAGE, VERSION );
}

/* usage()
 * Display how to use this program back to the user. */
void usage()
{
	version();
	fprintf( stderr,
	  "Usage: %s [-qtlcvh?] [-s <service>] <address> [ <address> ... ]\n\
\n\
    -q           Quiet mode; no output\n\
    -t           Print a TXT record, if any\n\
    -m           Stop checking after first address match in any list\n\
    -l           List default RBL services to check\n\
    -c           Clear the current list of RBL services\n\
    -s <service> Add a new service to the RBL services list\n\
    -h, -?       Display this help message\n\
    -v           Display version information\n\
    <address>    An IP address to look up; specify `-' to read multiple\n\
                 addresses from standard input.\n", progname );
}

/* togglesite()
 * This function takes the name of the site, and either adds it to the
 * list of sites to check, or removes it if it already exists. */
struct rbl * togglesite( char * sitename, struct rbl * sites )
{
	struct rbl * ptr;
	struct rbl * last = NULL;
	int sitelen;

	sitelen = strlen( sitename );

	for( ptr = sites; ptr != NULL; last = ptr, ptr = ptr->next )
	{
		if( ( strlen( ptr->site ) == sitelen ) &&
		  ( ! strcmp( ptr->site, sitename ) ) )
		{
			if( last )
				last->next = ptr->next;
			else
				sites = ptr->next;
			free( ptr->site );
			free( ptr );
			return sites;
		}
	}
	if( ! ( ptr = ( struct rbl * )malloc( sizeof( struct rbl ) ) ) )
	{
		perror( "malloc failed" );
		exit( 1 );
	}
	if( last )
		last->next = ptr;
	else
		sites = ptr;
	if( ( ptr->site = ( char * )malloc( sitelen + 1 ) ) )
		strcpy( ptr->site, sitename );
	else
	{
		perror( "malloc failed" );
		exit( 1 );
	}
	ptr->next = NULL;
	return sites;
}

/* rblcheck()
 * Checks the specified dotted-quad address against the provided RBL
 * domain. If "txt" is non-zero, we perform a TXT record lookup. We
 * return the text returned from a TXT match, or an empty string, on
 * a successful match, or NULL on an unsuccessful match. */
char * rblcheck( int a, int b, int c, int d, char * rbldomain, int txt )
{
	char * domain;
	char * result = NULL;
	u_char fixedans[ PACKETSZ ];
	u_char * answer;
	const u_char * cp;
	u_char * rp;
	const u_char * cend;
	const u_char * rend;
	int len;

	/* 16 characters max in a dotted-quad address, plus 1 for null */
	domain = ( char * )malloc( 17 + strlen( rbldomain ) );

	/* Create a domain name, in reverse. */
	sprintf( domain, "%d.%d.%d.%d.%s", d, c, b, a, rbldomain );

	/* Make our DNS query. */
	res_init();
	answer = fixedans;
	len = res_query( domain, C_IN, T_A, answer, PACKETSZ );

	/* Was there a problem? If so, the domain doesn't exist. */
	if( len == -1 )
		return result;

	if( len > PACKETSZ )
	{
		answer = malloc( len );
		len = res_query( domain, C_IN, T_A, answer, len );
		if( len == -1 )
			return result;
	}

	result = ( char * )malloc( RESULT_SIZE );
	result[ 0 ] = '\0';
	if( !txt )
	{
		return result;
	}

	/* Make another DNS query for textual data; this shouldn't
	   be a performance hit, since it'll now be cached at the
	   nameserver we're using. */
	res_init();
	len = res_query( domain, C_IN, T_TXT, answer, PACKETSZ );

	/* Just in case there's no TXT record... */
	if( len == -1 )
	{
		return result;
	}

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
	cend = cp + c;

	/* Iterate over any multiple answers we might have. In
	   this context, it's unlikely, but anyway. */
	rp = result;
	rend = result + RESULT_SIZE - 1;
	while( cp < cend && rp < rend )
	{
		a = *cp++;
		if( a != 0 )
			for( b = a; b > 0 && cp < cend && rp < rend;
			  b-- )
			{
				if( *cp == '\n' || *cp == '"' ||
				  *cp == '\\' )
				{
					*rp++ = '\\';
				}
				*rp++ = *cp++;
			}
	}
	*rp = '\0';
	return result;
}

/* full_rblcheck
 * Takes an IP address, and feeds it to rblcheck() for each defined
 * RBL listing, handling output of results if necessary. */
int full_rblcheck( char * addr )
{
	int a, b, c, d;
	int count = 0;
	char * response;
	struct rbl * ptr;

	for( ptr = rblsites; ptr != NULL; ptr = ptr->next )
	{
		if( sscanf( addr, "%d.%d.%d.%d", &a, &b, &c, &d ) != 4
		  || a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255
		  || d < 0 || d > 255 )
		{
			fprintf( stderr, "%s: warning: invalid address `%s'\n",
			  progname, addr );
			return 0;
		}
		response = rblcheck( a, b, c, d, ptr->site, txt );
		if( !quiet || response )
			printf( "%s %s%s%s%s%s%s", addr,
			  ( !quiet && !response ? "not " : "" ),
			  ( !quiet ? "RBL filtered by " : "" ),
			  ( !quiet ? ptr->site : "" ),
			  ( txt && response && strlen( response ) && !quiet ?
			    ": " : "" ),
			  ( txt && response ? response : "" ),
			  ( quiet && ( !txt || ( response &&
			    !strlen( response ) ) ) ? "" : "\n" ) );
		if( response )
		{
			count++;
			free( response );
		}
		if( firstmatch && count )
			return count;
	}
	return count;
}

/*-- MAINLINE ---------------------------------------------------------------*/

int main( int argc, char ** argv )
{
	int a;
	struct rbl * ptr;
	int rblfiltered = 0;
	char inbuf[ RESULT_SIZE ];

/* Hack to handle the easy addition of sites at compile time. */
#define SITE(x) rblsites = togglesite( (x), rblsites );
#include "sites.h"
#undef SITE

	progname = argv[ 0 ];

	while( ( a = getopt( argc, argv, "qtlms:c?hv" ) ) != EOF )
		switch( a )
		{
			case 'q':
				/* Quiet mode. */
				quiet = 1;
				break;
			case 't':
				/* Display TXT record. */
				txt = 1;
				break;
			case 'm':
				/* Stop after first successful match. */
				firstmatch = 1;
				break;
			case 'l':
				/* Display supported RBL systems. */
				for( ptr = rblsites; ptr != NULL;
				  ptr = ptr->next )
					printf( "%s\n", ptr->site );
				return 0;
			case 's':
				/* Toggle a particular zone. */
				rblsites = togglesite( optarg, rblsites );
				break;
			case 'c':
				/* Clear the rbl zones. */
				ptr = rblsites;
				while( ptr != NULL )
				{
					rblsites = ptr->next;
					free( ptr->site );
					free( ptr );
					ptr = rblsites;
				}
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

	/* Did they tell us to check anything? */
	if( optind == argc )
	{
		fprintf( stderr, "%s: no IP address(es) specified\n",
		  progname );
		usage();
		return -1;
	}

	/* Do we have any listings to search? */
	if( !rblsites )
	{
		fprintf( stderr,
		  "%s: no rbl listing(s) specified (need `-s <zone>'?)\n",
		  progname );
		return 0;
	}

	/* Loop through the command line. */
	while( optind < argc )
	{
		/* Handle addresses from stdin. */
		if( argv[ optind ][ 0 ] == '-' && argv[ optind ][ 1 ] == '\0' )
			while( fgets( inbuf, RESULT_SIZE - 1, stdin ) != NULL )
			{
				inbuf[ strlen( inbuf ) - 1 ] = '\0';
				rblfiltered += full_rblcheck( inbuf );
				if( firstmatch && rblfiltered )
					return rblfiltered;
			}
		else
			rblfiltered += full_rblcheck( argv[ optind ] );
		if( firstmatch && rblfiltered )
			return rblfiltered;
		optind++;
	}

	return rblfiltered;
}

/* EOF */
