all: make-lib util-test

util-test:
	g++ -o util-test util-test.cpp -Wl,-rpath=../lib -L../lib/ -lutil

.PHONY: make-lib clean

make-lib:
	cd ../ && make

clean:
	rm -f *-test

