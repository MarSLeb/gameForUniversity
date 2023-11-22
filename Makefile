run: Engine.o GameMenu.o Book.o Player.o FirstLoc.o Borders.o Cow.o SecondLoc.o Save.o Setting.o Potion.o Deed.o Street.o Animation.o Home.o FirstBoard.o
	g++ -c main.cpp 
	g++ main.o Engine.o GameMenu.o Book.o Player.o FirstLoc.o Borders.o Cow.o SecondLoc.o Save.o Setting.o Potion.o Deed.o Street.o  Animation.o Home.o FirstBoard.o -o out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./out

Engine.o: Engine.cpp
	g++ -c Engine.cpp

GameMenu.o: GameMenu.cpp
	g++ -c GameMenu.cpp

Book.o: Book.cpp
	g++ -c Book.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

FirstLoc.o: FirstLoc.cpp
	g++ -c FirstLoc.cpp

Borders.o: Borders.cpp
	g++ -c Borders.cpp

Cow.o: Cow.cpp
	g++ -c Cow.cpp

SecondLoc.o: SecondLoc.cpp
	g++ -c SecondLoc.cpp

Save.o: Save.cpp
	g++ -c Save.cpp

Setting.o: Setting.cpp
	g++ -c Setting.cpp

Potion.o: Potion.cpp
	g++ -c Potion.cpp

Deed.o: Deed.cpp
	g++ -c Deed.cpp

Street.o: Street.cpp
	g++ -c Street.cpp

Animation.o: Animation.cpp
	g++ -c Animation.cpp

Home.o: Home.cpp
	g++ -c Home.cpp

FirstBoard.o: FirstBoard.cpp
	g++ -c FirstBoard.cpp

clean:
	rm *.o
	rm out