#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

enum class NoteFourth{
    none,
    first, 
    second, 
    all
};

enum class NoteSecond{
    none, 
    all
};

class Book{
    private:
        array<Texture, 5> pages;
        int count = 5;
        int current;
        shared_ptr<RenderWindow> window;
        RectangleShape background = RectangleShape(Vector2f(960, 540));
        Texture keyTexture;
        RectangleShape key = RectangleShape(Vector2f(960, 540));
        NoteSecond hasNoteForSecondLoc = NoteSecond::none;
        NoteFourth hasNoteForFourthLoc = NoteFourth::none;

        void nextPage();
        void lastPage();

    public:
        int getPageTwo();
        int getPageFive();
        Book(shared_ptr<RenderWindow> window);
        void setPage(NoteSecond note);
        void setPage(NoteFourth note);
        void run();
};