FLAGS = -ansi -lpython2.7
PY=-I/usr/include/python2.7
STD = -std=c++11 
all: bin rhyped rhype tmp pyfile 

rhyped:
	g++ $(STD) $(PY) src/rhyped.cpp -o bin/rhyped $(FLAGS)

rhype:
	g++ $(STD) src/rhype.cpp -o bin/rhype $(FLAGS)

pyfile:
	cp src/hyped.py $(HOME)/rhype/hyped.py
 
bin:
	mkdir bin

tmp:
	rm -rf  $(HOME)/rhype && mkdir $(HOME)/rhype 

clean:
	rm -rf bin $(HOME)/rhype
