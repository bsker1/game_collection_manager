game_collection_manager: main.o
	g++ -std=c++17 main.o -o game_collection_manager

main.o:
	g++ -c -std=c++17 source/main.cpp

run:
	clear
	./game_collection_manager

clean:
	rm *.o game_collection_manager
	clear