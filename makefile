CXX = g++
CXXFLAGS = -Wall -std=c++14

main: main.o log.o struct.o simplelog.o lecture.o stats.o
	$(CXX) main.o log.o struct.o lecture.o simplelog.o stats.o -o test_log

lecture.o : lecture.cpp lecture.h
	$(CXX) $(CXXFLAGS) -c lecture.cpp

log.o: log.cpp log.h struct.h
	$(CXX) $(CXXFLAGS) -c log.cpp

main.o: main.cpp simplelog.h struct.h
	$(CXX) $(CXXFLAGS) -c main.cpp

struct.o: struct.cpp struct.h
	$(CXX) $(CXXFLAGS) -c struct.cpp

simplelog.o : simplelog.cpp simplelog.h log.h
	$(CXX) $(CXXFLAGS) -c simplelog.cpp

Stats.o : Stats.cpp Stats.h simplelog.h
	$(CXX) -c Stats.cpp

clean:
	rm -f main main.o log.o struct.o simplelog.o lecture.o Stats.o
