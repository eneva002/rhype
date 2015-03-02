FLAGS = -ansi -lcurl
STD = -std=c++11 
all: bin rhyped

rhyped:
	g++ $(STD) src/rhyped.cpp -o bin/rhyped $(FLAGS)

bin:
	mkdir bin

clean:
	rm -r bin
