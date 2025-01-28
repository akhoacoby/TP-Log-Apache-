CXX = g++
CXXFLAGS = -Wall -std=c++11

main: main.o log.o struct.o
	$(CXX) main.o log.o struct.o -o test_log

log.o: log.cpp log.h struct.h
	$(CXX) $(CXXFLAGS) -c log.cpp

main.o: main.cpp log.h struct.h
	$(CXX) $(CXXFLAGS) -c main.cpp

struct.o: struct.cpp struct.h
	$(CXX) $(CXXFLAGS) -c struct.cpp

clean:
	rm -f main main.o log.o struct.o
