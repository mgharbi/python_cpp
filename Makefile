CFLAGS=`python3-config --includes`
LDFLAGS=`python3-config --ldflags`

main: bin
	@clang++ -std=c++11 main.cpp ${CFLAGS} -o bin/main ${LDFLAGS}

bin:
	@mkdir -p bin

clean:
	@rm -rf bin
