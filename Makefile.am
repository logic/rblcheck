## Process this file with automake to produce Makefile.in

auxdir = @ac_aux_dir@
AUX_DIST = $(auxdir)/install-sh $(auxdir)/missing $(auxdir)/mkinstalldirs

noinst_HEADERS = sites.h

bin_PROGRAMS = rblcheck
rblcheck_SOURCES = rblcheck.c

XFAIL_TESTS = \
	tests/maps/rbl/listed tests/maps/rbl/unlisted \
	tests/maps/rss/listed tests/maps/rss/unlisted \
	tests/orbs/inputs/listed tests/orbs/inputs/unlisted \
	tests/orbs/outputs/listed tests/orbs/outputs/unlisted \
	tests/orbs/delayed-outputs/listed tests/orbs/delayed-outputs/unlisted \
	tests/orbs/manual/listed tests/orbs/manual/unlisted \
	tests/orbs/spamsources/listed tests/orbs/spamsources/unlisted \
	tests/orbs/untestable-netblocks/listed tests/orbs/untestable-netblocks/unlisted \
	tests/orbs/spamsource-netblocks/listed tests/orbs/spamsource-netblocks/unlisted
TESTS = tests/clearlist tests/addlisting tests/removelisting $(XFAIL_TESTS)

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
