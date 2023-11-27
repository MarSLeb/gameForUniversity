#include "SecondBoard.h"
#include <iostream>

const int Y = 345;
const int X = 550;
const int STEP = 115;
Color COLOR = Color::Black;
const int YFORCURSOR = Y + 20;
const vector<string> CHESSCOLUMN = {"A", "B", "C", "D", "E", "F", "G", "H"};

SecondBoard::SecondBoard(shared_ptr<RenderWindow> window): window(window){
    texturePuzzle.loadFromFile("foto/home/second/secondBoard.png");
    textureNote.loadFromFile("foto/home/second/end.png");

    font.loadFromFile("font/menu.ttf");
    
    buffer.loadFromFile("muziek/miss.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);

    setText(chessPieces[0], "K", X, Y, COLOR);
    setText(chessPieces[1], "e", X, Y, COLOR);
    setText(chessPieces[2], "N", X, Y, COLOR);
    setText(chessPieces[3], "R", X, Y, COLOR);
    setText(chessPieces[4], "Q", X, Y, COLOR);
    currentInSector[0] = 0;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 8; j++){
            if(i == 0){
                setText(chessCoordinates[i][j], CHESSCOLUMN[j], X + STEP, Y, COLOR); 
            }
            else{
                setText(chessCoordinates[i][j], to_string(j + 1), X + (2 * STEP), Y, COLOR); 
            }
        }
        currentInSector[i + 1] = 0;
    }

    setText(select, "_",  X, YFORCURSOR, Color::Red);
    currentSector = 0;
}

void SecondBoard::setFinishFlag(bool flag) { finish = flag; }

void SecondBoard::setSoundPlaying(bool flag) {soundIsPlay = flag;}

bool SecondBoard::checkAnswer(){
    string answer =  "";
    answer += chessPieces[currentInSector[0]].getString();
    for(int i = 1; i < 3; i++){
        answer += chessCoordinates[i - 1][currentInSector[i]].getString();
    }
    return answer == "RA7";
}

void SecondBoard::right(){
    if(currentSector == 2) { return; }
    currentSector++;
    select.setPosition(select.getPosition().x + STEP, YFORCURSOR);
}

void SecondBoard::left(){
    if(currentSector == 0) { return; }
    currentSector--;
    select.setPosition(select.getPosition().x - STEP, YFORCURSOR);
}

void SecondBoard::down(){
    if(currentInSector[currentSector] <= 0) { return; }
    currentInSector[currentSector]--;
}

void SecondBoard::up(){
    if(currentSector == 0){
        if(currentInSector[currentSector] == 4) { return; }
        currentInSector[currentSector]++;
    }
    else{
        if(currentInSector[currentSector] == 7) { return; }
        currentInSector[currentSector]++;
    }
}

void SecondBoard::draw(){
    window->clear();
    window->draw(groundPuzzle);
    window->draw(select);
    window->draw(chessPieces[currentInSector[0]]);
    for(int i = 1; i < 3; i++){
        window->draw(chessCoordinates[i - 1][currentInSector[i]]);
    }
    if(finish) { window->draw(groundNote); }
    window->display();
}

bool SecondBoard::run(){
    groundNote.setTexture(&textureNote);
    groundPuzzle.setTexture(&texturePuzzle);

    draw();

    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape) { return finish; }
                if(ev.key.code == Keyboard::T) { finish = checkAnswer();}
                if(!finish){
                    if(ev.key.code == Keyboard::W) { up(); }
                    if(ev.key.code == Keyboard::R) { down(); }
                    if(ev.key.code == Keyboard::A) { left(); }
                    if(ev.key.code == Keyboard::S) { right(); }
                }
            }
        }

        draw();
    }
}

void SecondBoard::setText(Text& text, String str, float xpos, float ypos, Color color){
    text.setFont(font);
    text.setFillColor(color);
    text.setString(str);    
    text.setCharacterSize(70);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(color);
}