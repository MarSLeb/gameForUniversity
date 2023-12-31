#include "Book.h"

using namespace std;

Book::Book(shared_ptr<RenderWindow> window): window(window){
    keyTexture.loadFromFile("foto/keyForBook.png");
    pages = {};
    for(int i = 1; i <= count; i++){
        pages[i - 1].loadFromFile("foto/pages/" + to_string(i) + ".png");
    }
    current = 0;
}

void Book::nextPage(){
    if(current < count - 1){
        current += 1;
    }
    background.setTexture(&pages[current]);
}

void Book::lastPage(){
    if(current > 0){
        current -= 1;
    }
    background.setTexture(&pages[current]);
}

void Book::setPage(NoteSecond note){
    if(note == NoteSecond::all) {pages[1].loadFromFile("foto/pages/2.1.png"); hasNoteForSecondLoc = NoteSecond::all;}   
    else {pages[1].loadFromFile("foto/pages/2.png"); hasNoteForSecondLoc = NoteSecond::none;}
}

void Book::setPage(NoteFourth note){
    hasNoteForFourthLoc = note;
    if(hasNoteForFourthLoc == NoteFourth::none) { pages[4].loadFromFile("foto/pages/5.png"); }
    else if(hasNoteForFourthLoc == NoteFourth::first) { pages[4].loadFromFile("foto/pages/5.1.png"); }
    else if(hasNoteForFourthLoc == NoteFourth::second) { pages[4].loadFromFile("foto/pages/5.2.png"); }
    else { pages[4].loadFromFile("foto/pages/5.3.png"); }
}

int Book::getPageTwo() { return (int)hasNoteForSecondLoc; }

int Book::getPageFive() { return (int)hasNoteForFourthLoc; }

void Book::run(){
    current = 0;
    background.setTexture(&pages[current]);
    key.setTexture(&keyTexture);

    window->draw(background);
    window->draw(key);
    window->display();

    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::F) {return;} 
                if(event.key.code == Keyboard::S) {nextPage();}
                if(event.key.code == Keyboard::A) {lastPage();}
            }
        }
        window->draw(background);
        window->draw(key);
        window->display();
    }
}
