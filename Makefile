CC = g++

Tester: Tester.o Inventory.o
	$(CC) -ggdb -O0 Tester.o Inventory.o -o Tester

Tester.o: Inventory.cpp Inventory.hpp Tester.cpp
	$(CC) -c -ggdb -O0 Inventory.hpp Tester.cpp

Inventory.o: Inventory.cpp Inventory.hpp Database.hpp
	$(CC) -c -ggdb -O0 Inventory.cpp Inventory.hpp Database.hpp

clean:
	rm *.o
