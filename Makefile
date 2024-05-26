#!make -f

CXX=clang
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
CODE_SOURCES=Graph.cpp Algorithms.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: demo
	./$^

demo: Demo.o Graph.o Algorithms.o 
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm

tidy:
	clang-tidy $(CODE_SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


Test.o: Test.cpp doctest.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


Algorithms.o: Algorithms.cpp Algorithms.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test
