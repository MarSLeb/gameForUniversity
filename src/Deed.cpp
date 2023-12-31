#include "Deed.h"

Deed::Deed() {}

Deed::Deed(shared_ptr<RenderWindow> window): window(window){
    music.openFromFile("muziek/youDied.ogg");
    music.setVolume(70);
    texture.loadFromFile("foto/died.png");
}

void Deed::died(bool soundIsPlay){
    ground.setTexture(&texture);
    window->clear();
    window->draw(ground);
    window->display();

    soundIsPlay ? music.setVolume(70) : music.setVolume(0);
    music.play();
    Clock clock;
    while (window->isOpen()){ 
        if(clock.getElapsedTime().asSeconds() >= 5.5) {return;}

        window->clear();
        window->draw(ground);
        window->display();
    }
}