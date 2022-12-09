gcm: main.o
	g++ -std=c++17 main.o -o gcm

main.o:
	g++ -c -std=c++17 source/main.cpp

run:
	clear
	./gcm

clean:
	rm *.o gcm
	clear