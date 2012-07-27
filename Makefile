package = algo.c
version = 0.0.2
tarname = $(package)
distdir = $(tarname)-$(version)

all:
	cd src && $(MAKE) $@

test:
	cd src && $(MAKE) $@

clean:
	-rm *~ *.log test/*
	cd src && $(MAKE) $@

distclean: clean FORCE
	-rm -rf lib test
	cd src && $(MAKE) $@


dist: $(distdir).tar.gz

$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)

$(distdir): FORCE distclean
	mkdir -p lib
	mkdir -p $(distdir)
	cp -r lib $(distdir)
	cp -r src $(distdir)
	cp  Makefile $(distdir)
	cp  algorithms.* $(distdir)

distcheck: $(distdir).tar.gz
	gzip -cd $(distdir).tar.gz | tar xvf -
	cd $(distdir) && $(MAKE) all
	cd $(distdir) && $(MAKE) clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution."

install:
	cp lib/lib$(package).a /usr/local/lib
	cp headers /usr/local/include/$(package)

FORCE:
	-rm $(distdir).tar.gz > /dev/null 2>&1
	-rm -rf $(distdir) > /dev/null 2>&1


.PHONY: FORCE all clean dist
