.PHONY: run clean

SFMLFLAG = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJECTS = FirstLoc.o SecondLoc.o Home.o Street.o \
Cow.o Potion.o FirstBoard.o SecondBoard.o \
Engine.o GameMenu.o Book.o Player.o Borders.o Save.o Setting.o Deed.o Animation.o main.o 

run:  $(OBJECTS)
	g++ $(OBJECTS) -o out $(SFMLFLAG)
	./out


main.o: src/main.cpp
	g++ -c src/main.cpp 

Engine.o: src/Engine.cpp
	g++ -c src/Engine.cpp

GameMenu.o: src/GameMenu.cpp
	g++ -c src/GameMenu.cpp

Book.o: src/Book.cpp
	g++ -c src/Book.cpp

Player.o: src/Player.cpp
	g++ -c src/Player.cpp

Borders.o: src/Borders.cpp
	g++ -c src/Borders.cpp

Save.o: src/Save.cpp
	g++ -c src/Save.cpp

Setting.o: src/Setting.cpp
	g++ -c src/Setting.cpp

Deed.o: src/Deed.cpp
	g++ -c src/Deed.cpp

Animation.o: src/Animation.cpp
	g++ -c src/Animation.cpp


Cow.o: src/puzzle/Cow.cpp
	g++ -c src/puzzle/Cow.cpp

Potion.o: src/puzzle/Potion.cpp
	g++ -c src/puzzle/Potion.cpp

FirstBoard.o: src/puzzle/FirstBoard.cpp
	g++ -c src/puzzle/FirstBoard.cpp

SecondBoard.o: src/puzzle/SecondBoard.cpp
	g++ -c src/puzzle/SecondBoard.cpp


FirstLoc.o: src/levl/FirstLoc.cpp 
	g++ -c src/levl/FirstLoc.cpp

SecondLoc.o: src/levl/SecondLoc.cpp 
	g++ -c src/levl/SecondLoc.cpp

Street.o: src/levl/Street.cpp 
	g++ -c src/levl/Street.cpp

Home.o: src/levl/Home.cpp
	g++ -c src/levl/Home.cpp


clean:
	rm *.o out