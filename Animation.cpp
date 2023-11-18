#include "Animation.h"
#include <iostream>

Animation::Animation(shared_ptr<RenderWindow> window, Anim numberOfAnimation): window(window){
    if(numberOfAnimation == Anim::start){
        countTexture = 30;
        for(int i = 0; i < countTexture; i++){
            texture[i].loadFromFile("animation/start/" + to_string(i) + ".PNG");
        }
    }
    else{
        countTexture = 40;
        for(int i = 0; i < countTexture; i++){
            texture[i].loadFromFile("animation/end/" + to_string(i) + ".png");
        }
    }
    background.setTexture(&texture[0]);
    curTexture = 0;
}

void Animation::run(){
    curTexture = 0;
    background.setTexture(&texture[curTexture]);
    window->clear();
    window->draw(background);
    window->display();
    Clock clock;
    while(window->isOpen()){
        float time = clock.getElapsedTime().asMilliseconds();
        if(time >= 250){
            clock.restart();
            if(curTexture == countTexture - 1) {return;}
            curTexture++;
            background.setTexture(&texture[curTexture]);
            
            window->clear();
            window->draw(background);
            window->display();
        }
    }
}