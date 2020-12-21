all:
	g++ -std=c++14 -o solution main.cpp

clean:
	rm -rf solution *.o