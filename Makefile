CFLAGS=`python3-config --cflags` -fno-lto -g
LDFLAGS=`python3-config --ldflags`

PYBIND=`python3 -m pybind11 --includes`

main_pybind: bin
	@g++-6 -std=c++14 main_pybind.cpp ${PYBIND} ${CFLAGS} -o bin/main_pybind ${LDFLAGS}

main: bin
	@g++-6 -std=c++11 main.cpp ${CFLAGS} -o bin/main ${LDFLAGS}

bin:
	@mkdir -p bin

clean:
	@rm -rf bin
