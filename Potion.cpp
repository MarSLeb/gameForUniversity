#include "Potion.h"

Potion::Potion() {}

Potion::Potion(shared_ptr<RenderWindow> window, shared_ptr<Book> book, Pickup pickup):
window(window), book(book), pickup(pickup){
    texture.loadFromFile("foto/potion/tablePotion.png");
    for(int i = 0; i < 7; i++) {upTexture[i].loadFromFile("foto/potion/table" + to_string(i) + ".png");}
    curTexture = 0;

    pickup == Pickup::Book 
        ? keyTexture.loadFromFile("foto/potion/key.png")
        : keyTexture.loadFromFile("foto/potion/keyNoBook.png");
    
}

void Potion::drawList(){
    window->draw(listKey);
    window->draw(list);
    window->display();
    while (window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased && ev.key.code == Keyboard::F){
                return;
            }
        }
    }
    
}

void Potion::drawKey(){
    if(pickup != Pickup::Note) {return;}
    window->draw(listKey);
}

void Potion::right(){
    if(curTexture < 6) {curTexture++; upground.setTexture(&upTexture[curTexture]);}
}

void Potion::left(){
    if(curTexture > 0) {curTexture--; upground.setTexture(&upTexture[curTexture]);}
}

int Potion::run(bool havingList){
    if(havingList && pickup != Pickup::Book) { pickup = Pickup::Note; }
    if(pickup == Pickup::Note){
        listKeyTexture.loadFromFile("foto/potion/listKey.png"); 
        listTexture.loadFromFile("foto/potion/listLikeBook.png");
        list.setTexture(&listTexture);
        listKey.setTexture(&listKeyTexture);
    }

    key.setTexture(&keyTexture);
    ground.setTexture(&texture);
    upground.setTexture(&upTexture[curTexture]);

    window->clear();
    window->draw(ground);
    window->draw(upground);
    window->draw(key);
    drawKey();
    window->display();

    Clock clock;
    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::F){
                    if(pickup == Pickup::Book) { book->run(); }
                    else if(pickup == Pickup::Note) { drawList(); }
                }
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
        drawKey();
        window->display();  
    }
    return 8;
}