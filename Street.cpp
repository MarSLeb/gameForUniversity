#include "Street.h"
#include <iostream>

Street::Street(int save, shared_ptr<RenderWindow> window, shared_ptr<Book> book, shared_ptr<Player> player, bool havingBook):
save(save), window(window), book(book), player(player), havingBook(havingBook){
    texture.loadFromFile("foto/street.png");
    upSprite.loadFromFile("foto/street/sprite.png");
    upHalf.loadFromFile("foto/street/half.png");
    havingBook == true ? keyTexture.loadFromFile("foto/key.png") :
                         keyTexture.loadFromFile("foto/keyNoBook.png");

    background.setTexture(&texture);
    sprite.setTexture(&upSprite);
    half.setTexture(&upHalf);
    key.setTexture(&keyTexture);

    setting = Setting(save, window);
    deed = make_unique<Deed>(window);

    buffer.loadFromFile("muziek/step.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);
    music.openFromFile("muziek/street.ogg");
    music.setVolume(5);
    music.setLoop(true);

    RectangleShape board;
    board = RectangleShape(Vector2f(350, 50)); // tree l
    board.setPosition(0, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(430, 50)); // tree r
    board.setPosition(530, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(960, 300)); // road
    board.setPosition(0, 500);
    boards.push_back(board);
    board = RectangleShape(Vector2f(290, 5)); // bus stop l
    board.setPosition(0, 385);
    boards.push_back(board);
    board = RectangleShape(Vector2f(290, 5)); // bus stop r
    board.setPosition(685, 385);
    boards.push_back(board);
    board = RectangleShape(Vector2f(30, 5)); // mari
    board.setPosition(170, 150);
    boards.push_back(board);
    board = RectangleShape(Vector2f(50, 50)); // bazil
    board.setPosition(705, 50);
    boards.push_back(board);
    board = RectangleShape(Vector2f(30, 5)); // kim
    board.setPosition(545, 340);
    boards.push_back(board);
}

string Street::createSaveString() {return ("s" + to_string(book->getPageTwo()) + to_string(havingBook));}

void Street::setPageInBook(int num) {book->setPage((NoteSecond)num);}

void Street::drawUp(){
    int x = player->getX();
    int y = player->getY();
    if(x >= 60 && x <= 200 && y <= 80) {window->draw(sprite);}
    else if(x >= 450 && x <= 560 && y >= 200 && y <= 280) {window->draw(sprite);}
    else if(x >= 585 && y >= 140 && y <= 295) {window->draw(half);}
    else if(x <= 270 && y >= 140 && y <= 295) {window->draw(half);}
}

bool Street::drawRepl(){
    int x = player->getX();
    int y = player->getY();
    Texture say;
    RectangleShape sayText = RectangleShape(Vector2f(960, 540));
    if(x >= 50 && x <= 200 && y >= 50 && y <= 170) {say.loadFromFile("foto/street/mari.png");}
    else if(x >= 600 && x <= 760 && y <= 110) {say.loadFromFile("foto/street/bazil.png");}
    else if(x >= 430 && x < 580 && y >= 210 && y <= 360) {say.loadFromFile("foto/street/kim.png");}
    else if(x <= 280 && y >= 270 && y <= 400) {music.pause(); setting.died(); deed->died(soundIsPlay); return false;}
    else if(x >= 580 && y >= 270 && y <= 400){
        Home home = Home(save, window, player, book, soundIsPlay, havingBook);
        sound.pause();
        music.pause();
        home.setValume(soundIsPlay);
        home.run();
        return false;
    }
    //переход в локу на правой
    else {return true;}

    Sound talking;
    SoundBuffer buf;
    buf.loadFromFile("muziek/talking.ogg");
    talking.setBuffer(buf);
    if(soundIsPlay) {talking.setVolume(10);}
    else {talking.setVolume(0);}
    
    sayText.setTexture(&say);
    window->clear();
    window->draw(background);
    player->draw();
    drawUp();
    window->draw(sayText);

    Clock clock;
    talking.play();
    while(window->isOpen()){
        Event ev;
        float time = clock.getElapsedTime().asMilliseconds();
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::T) {return true;}
            }
        }
        if(time < 4 && talking.getStatus() == SoundSource::Status::Stopped) {talking.play();}
        window->clear();
        window->draw(background);
        player->draw();
        drawUp();
        window->draw(sayText);
        window->display();
    }
}

void Street::drawAll(){
    window->clear();
    window->draw(background);
    player->draw();
    drawUp();
    window->draw(key);
    window->display();
}

void Street::setValue(bool flag) {soundIsPlay = flag;}

bool Street::runSetting(){
    drawAll();
    switch (setting.run(createSaveString())){
        case menuItem::save:
            return false;
            break;
        case menuItem::sound:
            music.getStatus() == SoundSource::Status::Paused ? music.play() : music.pause();
            soundIsPlay ? soundIsPlay = false : soundIsPlay = true;
            break;
    }
    return true;
}

void Street::run(int num){
    player->setPosition(390, 30);
    if(num != 4) {
        setting.died();
        deed->died(soundIsPlay);
        return;
    }

    if(soundIsPlay) {music.play();}
    else {sound.setVolume(0); music.play(); music.pause();}

    drawAll();

    Clock clock;
    while(window->isOpen()){
        Event event;
        while (window->pollEvent(event)){
            if(event.type == Event::LostFocus) { if(!runSetting()) {return;} }
            if(event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::Escape) { if(!runSetting()) {return;} }
                if(event.key.code == Keyboard::F && havingBook){
                    drawAll();
                    book->run();
                }
                if(event.key.code == Keyboard::T) {if(!drawRepl()) {return;}}
            }
        }

        float time = clock.getElapsedTime().asMicroseconds(); 
	    clock.restart(); 
	    time = time / 800; 
        player->movePlayer(time, soundIsPlay, boards);
        drawAll();
    }
}