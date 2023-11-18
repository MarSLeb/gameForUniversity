#include "Cow.h"
#include <iostream>

void Cow::setAnswer(string newAnswer) {answer = newAnswer;}

string Cow::getAnswer() {return answer;}

Cow::Cow(shared_ptr<RenderWindow> window, shared_ptr<RectangleShape> background, shared_ptr<Book> book)
: window(window), background(background), book(book)
{
    texture.loadFromFile("foto/cow/cowStart.png");
    keyTexture.loadFromFile("foto/cow/key.png");
    font.loadFromFile("font/number.TTF");
    // цифры
    for(int i = 0, x = 130; i < 4; i++, x += 195){
        for(int j = 0; j < 10; j++){
            if(j == 1) {setText(number[i][j], " 1", x, 110);}
            else {setText(number[i][j], to_string(j), x, 110);}
        }
        setText(number[i][10], "_", x, 110);
        select[i] = 10;
    }
    

    //для подчёркивания выбранной секции
    sel.setString("_");
    sel.setFont(font);
    sel.setCharacterSize(130);
    sel.setFillColor(Color::Red);
    sel.setOutlineColor(Color::Red);
    selX = 130;
    sel.setPosition(selX, 110);
    cur = 0;


    //текстурки для вывода быков и коров
    for(int i = 0; i < 2; i++){
        textureForAnswer[i].loadFromFile("foto/cow/0.png");
        upTexture[i] = RectangleShape(Vector2f(960, 540));
        upTexture[i].setTexture(&textureForAnswer[i]);
    }
    
    //random answer
    random_device rd;  // a seed source for the random number engine
    mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, 9);
    for(int i = 0; i < 4; i++){
        string newNum = to_string(distrib(gen));
        while(answer.find(newNum) != string::npos) {newNum = to_string(distrib(gen));}
        answer += newNum;
    }
}

void Cow::drawNum(){
    for(int i = 0; i < 4; i++){
        window->draw(number[i][select[i]]);
    }
    window->draw(sel);
}

void Cow::moveUp(){
    if(select[cur] >= 9) {select[cur] = 0;}
    else {select[cur]++;}
}

void Cow::moveDown(){
    if(select[cur] == 0 || select[cur] == 10) {select[cur] = 9;}
    else {select[cur]--;}
}

void Cow::moveRight(){
    if(cur != 3) {
        cur++;
        selX += 195;
        sel.setPosition(selX, 110);
    }
}

void Cow::moveLeft(){
    if(cur != 0) {
        cur--;
        selX -= 195;
        sel.setPosition(selX, 110);
    }
}

bool Cow::isSpace(){
    for(int i = 0; i < 4; i++){
        if(number[i][select[i]].getString() == "_") {return true;}
    }
    return false;
}

pair<int, int> Cow::check(){
    string playerAnswer = "";
    for(int i = 0; i < 4; i++){
        playerAnswer += number[i][select[i]].getString() == " 1" ? "1" : number[i][select[i]].getString();
        if(number[i][select[i]].getString() == "_") {return make_pair(-1, -1);}
    }
    int cow = 0;
    int bull = 0;
    string ostAnsw = "";
    string ostPlayer = "";
    for(int i = 0; i < 4; i++){
        if(answer[i] == playerAnswer[i]) {cow += 1;}
        else {
            ostAnsw += answer[i];
            ostPlayer += playerAnswer[i];
        }
    }
    for(int i = 0; i < ostPlayer.size(); i++){
        if(ostAnsw.find(ostPlayer[i]) != string::npos){
            bull += 1;
            ostAnsw.erase(ostAnsw.find(ostPlayer[i]), 1);
        }
    }
    return make_pair(cow, bull);
}

void Cow::getColor(pair<int, int> cowBull){
    if(cowBull.second == -1) {return;}

    cowBull.first == 0 ? textureForAnswer[0].loadFromFile("foto/cow/0.png") :
        textureForAnswer[0].loadFromFile("foto/cow/o" + to_string(cowBull.first) + ".png");
    cowBull.second == 0 ? textureForAnswer[1].loadFromFile("foto/cow/0.png") :  
        textureForAnswer[1].loadFromFile("foto/cow/b" + to_string(cowBull.second) + ".png");
}

void Cow::drawAnswer(){
    for(int i = 0; i < 2; i++) {window->draw(upTexture[i]);}
}

bool Cow::run(){
    background->setTexture(&texture);
    key.setTexture(&keyTexture);
    window->clear();

    window->draw(*background);
    drawAnswer();
    drawNum();
    window->draw(key);
    window->display();

    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if (ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape) {
                    cur = 0;
                    selX = 130;
                    sel.setPosition(selX, 110);
                    return false;
                }
                if(ev.key.code == Keyboard::A) {moveLeft();}
                if(ev.key.code == Keyboard::S) {moveRight();}
                if(ev.key.code == Keyboard::W) {moveUp();}
                if(ev.key.code == Keyboard::R) {moveDown();}
                if(ev.key.code == Keyboard::F) {book->setLocTexture(5); book->run();}
                if(ev.key.code == Keyboard::T) {
                    auto checkRes = check();
                    if(checkRes.first == 4 && checkRes.second == 0) {return true;}
                    getColor(checkRes);

                    if(!isSpace()){
                        cur = 0;
                        selX = 130;
                        sel.setPosition(selX, 110);
                        for(int i = 0; i < 4; i++) {select[i] = 10;}
                    }
                }
                if(ev.key.code == Keyboard::I) {return true;}
            }
        }
        window->clear();
        window->draw(*background);
        drawAnswer();
        drawNum();
        window->draw(key);
        window->display();
    }
    return false;
}

void Cow::setText(Text& text, String str, float xpos, float ypos){
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setString(str);    
    text.setCharacterSize(130);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(Color::Black);
}