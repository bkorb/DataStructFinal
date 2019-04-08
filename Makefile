Tester: Tester.o
	g++ Tester.o -o Tester

Tester.o: Database.hpp Tester.cpp
	g++ -c Database.hpp Tester.cpp

clean:
	rm *.o
