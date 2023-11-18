#include "Potion.h"

Potion::Potion() {}

Potion::Potion(shared_ptr<RenderWindow> window, shared_ptr<Book> book): window(window), book(book){
    texture.loadFromFile("foto/potion/tablePotion.png");
    for(int i = 0; i < 7; i++) {upTexture[i].loadFromFile("foto/potion/table" + to_string(i) + ".png");}
    curTexture = 0;
    keyTexture.loadFromFile("foto/potion/key.png");
}

void Potion::right(){
    if(curTexture < 6) {curTexture++; upground.setTexture(&upTexture[curTexture]);}
}

void Potion::left(){
    if(curTexture > 0) {curTexture--; upground.setTexture(&upTexture[curTexture]);}
}

int Potion::run(){
    book->setLocTexture(6);
    key.setTexture(&keyTexture);
    ground.setTexture(&texture);
    upground.setTexture(&upTexture[curTexture]);

    window->clear();
    window->draw(ground);
    window->draw(upground);
    window->draw(key);
    window->display();

    Clock clock;
    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::F) {book->run();}
                if(ev.key.code == Keyboard::Escape) {return 8;}
                if(ev.key.code == Keyboard::T) {
                    return 6 - curTexture;
                }
                if(ev.key.code == Keyboard::S) {right();}
                if(ev.key.code == Keyboard::A) {left();}
            }  
        }

        window->clear();
        window->draw(ground);
        window->draw(upground);
        window->draw(key);
        window->display();  
    }
    return 8;
}