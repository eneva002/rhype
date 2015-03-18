FLAGS = -ansi -lpython2.7
PY=-I/usr/include/python2.7
STD = -std=c++11 
all: bin rhyped rhype pyfile

rhyped:
	g++ $(STD) $(PY) src/rhyped.cpp -o bin/rhyped $(FLAGS)

rhype:
	g++ $(STD) src/rhype.cpp -o bin/rhype $(FLAGS)

pyfile:
	cp src/hyped.py bin/hyped.py
 
bin:
	mkdir bin

clean:
	rm -rf bin
