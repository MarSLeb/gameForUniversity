#include "FirstBoard.h"
#include <iostream>

FirstBoard::FirstBoard() {}

FirstBoard::FirstBoard(shared_ptr<RenderWindow> window): window(window){
    font.loadFromFile("font/number.TTF");
    textureNote.loadFromFile("foto/home/first/end.png");
    texturePuzzle.loadFromFile("foto/home/first/0.png");
    buffer.loadFromFile("muziek/miss.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(100);
}

void FirstBoard::setFinishFlag(bool flag) { finish = flag; }

void FirstBoard::setSoundPlaying(bool flag) { soundIsPlay = flag; }

void FirstBoard::left(){
    if(finish) { return; }
    if(current == 0) { return; }
    current--;
    texturePuzzle.loadFromFile("foto/home/first/" + to_string(current) + ".png");
    groundPuzzle.setTexture(&texturePuzzle);
}

void FirstBoard::right(){
    if(finish) { return; }
    if(current == 3) { return; }
    current++;
    texturePuzzle.loadFromFile("foto/home/first/" + to_string(current) + ".png");
    groundPuzzle.setTexture(&texturePuzzle);
}

bool FirstBoard::run(){
    groundNote.setTexture(&textureNote);
    groundPuzzle.setTexture(&texturePuzzle);
    draw();
    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape) { return finish; }
                if(ev.key.code == Keyboard::T) { checkCurrentAnswer(); }
                if(ev.key.code == Keyboard::A) { left(); }
                if(ev.key.code == Keyboard::S) { right(); }
            }
        }
        draw();
    }
}

void FirstBoard::checkCurrentAnswer(){
    if(current == 3) { finish = true; return; }
    if(soundIsPlay) { sound.play(); }
}

void FirstBoard::draw(){
    window->clear();
    window->draw(groundPuzzle);
    if(finish) { window->draw(groundNote); }
    window->display();
}