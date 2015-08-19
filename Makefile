package		= subnet_merge
version		= 0.2
tarname		= subnet_merge
distdir		= $(tarname)-$(version)

prefix		= /usr/local
exec_prefix	= ${prefix}
bindir		= ${exec_prefix}/bin

all clean:
	cd src && $(MAKE) $@

tests:	
	cd src && $(MAKE) subnet_merge
	cd tests && $(MAKE) tests

dist: $(distdir).tar.gz

$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)

SOURCES=\
	src/bit.c\
	src/bit.h\
	src/constants.h\
	src/Makefile\
	src/netaddr.c\
	src/netaddr.h\
	src/node.c\
	src/node.h\
	src/subnet_merge.c\
	src/tree.c\
	src/tree.h\
	src/util.c\
	src/util.h

TESTS=\
	tests/example-c.txt\
	tests/example-n.txt\
	tests/expected-c.txt\
	tests/expected-n.txt\
	tests/Makefile\
	tests/output-c.txt

$(distdir): FORCE
	mkdir -p $(distdir)/src
	cp $(SOURCES) $(distdir)/src
	mkdir -p $(distdir)/tests
	cp $(TESTS) $(distdir)/tests
	cp Makefile README $(distdir)

FORCE:
	-rm $(distdir).tar.gz >/dev/null 2>&1
	-rm -rf $(distdir) >/dev/null 2>&1


.PHONY: FORCE all clean check dist tests
