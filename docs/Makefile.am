docdir = $(datadir)/docs

EXTRA_DIST = rblcheck.sgml
DISTCLEANFILES = rblcheck.ps rblcheck.rtf html/*.html
MAINTAINERCLEANFILES = Makefile.in

html/index.html: rblcheck.sgml
	-srcdir=`cd $(srcdir) && pwd`; \
	db2html $$srcdir/rblcheck.sgml
	-mv rblcheck html

rblcheck.ps: rblcheck.sgml
	-srcdir=`cd $(srcdir) && pwd`; \
	db2ps $$srcdir/rblcheck.sgml

rblcheck.rtf: rblcheck.sgml
	-srcdir=`cd $(srcdir) && pwd`; \
	db2rtf $$srcdir/rblcheck.sgml

dist-hook: html/index.html rblcheck.ps rblcheck.rtf
	-$(mkinstalldirs) $(distdir)/html
	-cp $(srcdir)/html/*.html $(distdir)/html
	-cp $(srcdir)/rblcheck.ps $(distdir)/rblcheck.ps
	-cp $(srcdir)/rblcheck.rtf $(distdir)/rblcheck.rtf

distclean-local:
	-rmdir html

install-data-local: rblcheck.html rblcheck.ps rblcheck.rtf
	-for file in $(srcdir)/*.html; do \
		basefile=`echo $$file | sed -e 's,^.*/,,'`; \
		$(INSTALL_DATA) $$file $(DESTDIR)$(docdir)/$$basefile; \
	done
	-$(INSTALL_DATA) $(srcdir)/rblcheck.ps $(DESTDIR)$(docdir)/rblcheck.ps
	-$(INSTALL_DATA) $(srcdir)/rblcheck.rtf $(DESTDIR)$(docdir)/rblcheck.rtf

uninstall-local:
	-for file in $(srcdir)/html/*.html; do \
		basefile=`echo $$file | sed -e 's,^.*/,,'`; \
		rm -f $(docdir)/html/$$basefile; \
	done
	-rm -f $(docdir)rblcheck.rtf
	-rm -f $(docdir)rblcheck.ps
	-rm -f $(docdir)rblcheck.sgml
	-rmdir $(docdir)/html
