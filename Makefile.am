## Process this file with automake to produce Makefile.in

auxdir = @ac_aux_dir@
AUX_DIST = $(auxdir)/install-sh $(auxdir)/missing $(auxdir)/mkinstalldirs

noinst_HEADERS = sites.h

bin_PROGRAMS = rblcheck
rblcheck_SOURCES = rblcheck.c

EXTRA_DIST = \
	README.ALPHA			\
	config/install-sh		\
	config/missing			\
	config/mkinstalldirs		\
	docs/BUGS			\
	docs/CREDITS			\
	docs/INSTALL			\
	docs/NOT-TODO			\
	docs/PLATFORMS			\
	docs/TODO			\
	utils/README			\
	utils/test_origip.sh		\
	utils/test_rblcheck.sh		\
	utils/dns/Makefile		\
	utils/dns/dump.c		\
	utils/qmail/Makefile		\
	utils/qmail/origip.awk		\
	utils/qmail/origip.c		\
	utils/sendmail/origip.pl

SUBDIRS = .

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure config.in stamp-h.in \
	$(AUX_DIST)

ACLOCAL = aclocal -I $(auxdir)
