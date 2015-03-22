FLAGS = -ansi -lpython2.7
PY=-I/usr/include/python2.7
STD = -std=c++11 
rhypedir = $(HOME)/rhypefiles
all: bin rhyped rhype tmp pyfile 

rhyped:
	g++ $(STD) $(PY) src/rhyped.cpp -o bin/rhyped $(FLAGS)

rhype:
	g++ $(STD) src/rhype.cpp -o bin/rhype $(FLAGS)

pyfile:
	cp src/hyped.py $(rhypedir)/hyped.py
 
bin:
	mkdir bin

tmp:
	rm -rf  $(rhypedir) && mkdir $(rhypedir)

clean:
	rm -rf bin $(rhypedir)
