all: util iana static publish

static:
	g++ --static -o ./bin/iana-tools ./src/main.cpp ./src/iana.cpp ./src/util.cpp

util:
	g++ -shared -fPIC -o ./lib/libutil.so ./src/util.cpp

iana:
	g++ -shared -fPIC -o ./lib/libiana.so ./src/iana.cpp 

.PHONY: clean publish

clean:
	rm -f ./lib/* ./bin/*

publish: util iana
	rm -f ./include/* ; cp ./src/*.h ./include/

