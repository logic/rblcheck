/*
   rblcheck RBL Systems

   Add new sites to this listing in the format:

       SITE("site.domain.com")

   Do not add any extra whitespace, and make sure you place quotes
   around the address. Use C comments in this file if you want to
   add comments about each site. Uncomment the sites you want to use
   by default. The listings are checked in the order they are listed
   here.

   These listings are provided as a convenience, and examples of how to
   add new listings. I'll try to keep them updated if at all possible,
   but you should not rely blindly on these values being correct, nor
   should you rely on someone else's judgement about the "goodness" of
   a particular list; test them, and see if their policies suit your
   tastes. RBL-style systems tend to move around a bit, so you should
   check the service websites regularly for updates.

   In other words, if you use one of these, and the world ends, don't
   blame me. You're using them at your own risk. If they break, you get
   to keep both pieces.

   For more up-to-date information on current RBL-style listings, see:

       http://www.iki.fi/era/rbl/rbl.html
*/

/* dev.null.dk
   http://dev.null.dk/ (Maybe?) */
/* SITE("dev.null.dk") */

/* MAPS RBL: Mail Abuse Protection System Realtime Blackhole List
   http://mail-abuse.org/rbl/ */
/* SITE("blackholes.mail-abuse.org") */

/* MAPS RSS: Mail Abuse Protection System Relay Spam Stopper
   http://mail-abuse.org/rss/ */
/* SITE("relays.mail-abuse.org") */

/* MAPS DUL: Mail Abuse Protection System Dial-up User List
   http://mail-abuse.org/dul/ */
/* SITE("dialups.mail-abuse.org") */

/* MBL: Mike's Black List
   http://groups.google.com/groups?ic=1&th=26aaeffd51692527,1
   Please note: This URL seems to change frequently. See era's list above
   for more current information. */
/* SITE("3y.spam.mrs.kithrup.com") */

/* ORBL: Open Relay Black List
   http://www.orbl.org/ */
/* SITE("or.orbl.org") */

/* ORBZ: Open Relay Block Zone
   http://www.orbz.gst-group.co.uk/orbs/ */
/* SITE("orbz.gst-group.co.uk") */
/* SITE("manual.orbz.gst-group.co.uk") */

/* ORDB: Open Relay DataBase
   http://www.ordb.org/ */
/* SITE("relays.ordb.org") */
