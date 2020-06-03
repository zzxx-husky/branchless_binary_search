debug: demo.cpp
	g++ -g demo.cpp -std=c++11 -o demo

release: demo.cpp
	g++ -O3 demo.cpp -std=c++11 -o demo
