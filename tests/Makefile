
tests:
	../src/subnet_merge -f example-c.txt | diff expected-c.txt -
	../src/subnet_merge -f example-n.txt | diff expected-c.txt -
	../src/subnet_merge -m N -f example-n.txt | diff expected-n.txt -
	../src/subnet_merge -m C -f expected-c.txt | diff expected-c.txt -
	../src/subnet_merge -m N -f expected-n.txt | diff expected-n.txt -

.PHONEY:	tests
