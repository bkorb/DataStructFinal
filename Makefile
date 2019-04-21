CC = g++

Tester: Tester.o Inventory.o
	$(CC) -ggdb -O0 Tester.o Inventory.o -o Tester

Tester.o: Tester.cpp Inventory.hpp
	$(CC) -c -ggdb -O0 Inventory.hpp Tester.cpp Trie.hpp

Inventory.o: Inventory.cpp Inventory.hpp Database.hpp priorityQueue.hpp Trie.hpp
	$(CC) -c -ggdb -O0 Inventory.cpp Inventory.hpp Database.hpp priorityQueue.hpp Trie.hpp

clean:
	rm *.o
