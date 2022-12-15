gcm: main.o Game.o save.o utils.o
	g++ -std=c++17 main.o Game.o save.o utils.o -o gcm

main.o:
	g++ -c -std=c++17 source/main.cpp

Game.o:
	g++ -c -std=c++17 source/Game.cpp

save.o:
	g++ -c -std=c++17 source/save.cpp

utils.o:
	g++ -c -std=c++17 source/utils.cpp

run:
	clear
	./gcm

clean:
	rm *.o gcm
	clear