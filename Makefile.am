## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = 1.4

SUBDIRS = .

bin_PROGRAMS = rblcheck
rblcheck_SOURCES = rblcheck.c

EXTRA_DIST = \
	README.ALPHA			\
	sites.h				\
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

.PHONY: files release sanity snapshot

files:
	@files=`ls $(DISTFILES) 2> /dev/null `; for p in $$files; do \
	  echo $$p; \
	done

release:
	rm -rf .deps */.deps
	$(MAKE) distcheck

snapshot:
	$(MAKE) dist distdir=$(PACKAGE)-`date +"%y%m%d"`
