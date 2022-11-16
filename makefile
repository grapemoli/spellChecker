dict: main.o table.o 
	g++ -g main.cpp table.o -o dict

main.o: main.cpp    
	g++ -c -g main.cpp

table.o: table.h TimeInterval.h table.cpp 
	g++ -c -g TimeInterval.h table.cpp 

run: dict
	./dict

clean:
	rm *.o
	rm *.gch
	rm dict

debug: dict
	gdb dict

val:
	valgrind --leak-check=full ./dict
