/*
   rblcheck RBL Systems

   Add new sites to this listing in the format:

       SITE("site.domain.com")

   Do not add any extra whitespace, and make sure you place quotes
   around the address. Use C comments in this file if you want to
   add comments about each site. Uncomment the sites you want to use
   by default. The listings are checked in the order they are listed
   here.

   These listings are provided to you as a convenience; as I find more
   listings, I'll add them here, but I neither operate nor recommend
   any of these particular systems. You should make your own decision
   as to which listings to support by default. Also, RBL-style systems
   (aside from the MAPS RBL) have a tendancy to move around a bit, so
   you should check the service websites from time to time to make
   sure nothing has changed.

   In other words, if you use one of these, and the world ends, don't
   blame me. You're using them at your own risk.

   You should also visit era eriksson's fine page listing the currently
   available RBL-alike systems, which will have far more up-to-date
   information than this file:

       http://www.iki.fi/era/rbl/rbl.html
*/


/* MAPS RBL: Mail Abuse Protection System Realtime Blackhole List
   http://maps.vix.com/rbl/

   This listing is human-operated, and is one of the most popular
   blacklists of spam-originating systems. Originallys started by
   Paul Vixie, this is the original RBL system. */
/* SITE("rbl.maps.vix.com") */


/* ORBS: Open Relay Behaviour-modification System
   http://www.orbs.org/

   This is an automated listing of IP addresses that have been tested
   to host an SMTP server that will transmit at least one message to
   any system for anyone (an "open email relay"). Mechanisms are also
   available to remove systems that have closed the relay. */
/* SITE("relays.orbs.org") */


/* IMRSS: The Internet Mail Relay Services Survey
   http://www.imrss.org/

   This list appears to be similar in scope to ORBS, in that it
   catalogues open mail relays. */
/* SITE("mr-out.imrss.org") */


/* RRSS: The Radparker Relay Spam Stopper
   http://relays.radparker.com/

   Like ORBS and IMRSS, this system is a listing of open relays, but
   the maintainer manually handles addition of relays, and only after
   evidence of spam from that server has been presented. */
/* SITE("relays.radparker.com") */


/* MAPS DUL: Mail Abuse Protection System Dial-up User List
   http://maps.vix.com/dul/

   This list was started from a list compiled by "Afterburner" (the
   head-honcho abuse guy at Erols Internet), and extended to be easily
   added to over time. This service was originally called the ORCA DUL,
   and was operated at "dul.orca.bc.ca"; the MAPS project invited Al
   Iverson, the DUL maintainer, to host it on their systems. */
/* SITE("dul.maps.vix.com") */


/* DSSL: The Direct Spam Sources List
   http://www.imrss.org/dssl/

   This list is similar in intent to the MAPS DUL, but uses a unique
   scheme of matching patterns to dialup IP naming conventions. The
   server looks up the IP you pass it, "compresses" the name, and
   matches it against a series of patterns, returning true or false
   based on a successful or failed match. */
/* SITE("dssl.imrss.org") */

/* The Shub-Internet Blackholes
   http://www.shub-inter.net/

   These listing is human-operated, and is much more aggressive than
   the MAPS list. If a system appears on either RBL, DUL, or ORBS, it
   is removed from the listings, and so these should be checked last.
   The first list (relayips) is a listing of open email relays, and
   the second (spamips) is a listing of hand-picked spam sources. */
/* SITE("relayips.shub-inter.net") */
/* SITE("spamips.shub-inter.net") */
