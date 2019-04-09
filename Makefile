Tester: Tester.o Inventory.o
	g++ Tester.o Inventory.o -o Tester

Tester.o: Inventory.cpp Inventory.hpp Tester.cpp
	g++ -c Inventory.hpp Tester.cpp

Inventory.o: Inventory.cpp Inventory.hpp Database.hpp
	g++ -c Inventory.cpp Inventory.hpp Database.hpp

clean:
	rm *.o
