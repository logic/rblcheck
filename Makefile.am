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

# We don't include README.ALPHA or bootstrap here, so we don't include them
# in a "make distcheck". Since all tests are shell scripts, we're including
# the full list verbatim.
EXTRA_DIST = \
	config/install-sh		\
	config/missing			\
	config/mkinstalldirs		\
	config/rblcheck.spec		\
	config/rblcheck.spec.in		\
	config/pkginfo.in		\
	utils/README			\
	utils/test_origip.sh		\
	utils/test_rblcheck.sh		\
	utils/dns/Makefile		\
	utils/dns/dump.c		\
	utils/qmail/Makefile		\
	utils/qmail/origip.awk		\
	utils/qmail/origip.c		\
	utils/sendmail/origip.pl	\
	$(TESTS)

SUBDIRS = docs .

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure config.in stamp-h.in \
	$(AUX_DIST)

DISTCLEANFILES = config/rblcheck.spec config/pkginfo

CLEANFILES = config/Prototype

ACLOCAL = aclocal -I $(auxdir)

# Build a Solaris package.
solarispkg: $(bin_PROGRAMS)
	test -x /usr/bin/pkgproto
	test -x /usr/bin/pkgmk
	$(MAKE) DESTDIR=`pwd`/$(distdir) install
	echo 'i configinfo' > config/Prototype
	pkgproto $(distdir)/usr \
		| sed -e "s, $(distdir), ," >> config/Prototype
	pkgmk -d config -f config/Prototype -r $(distdir)
	pkgtrans config $(distdir).pkg rblcheck
	rm -rf $(distdir) config/rblcheck
