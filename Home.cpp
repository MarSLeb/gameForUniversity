#include "Home.h"
#include <iostream>

string Home::createSaveString() {return "h" + to_string(book->getPageTwo()) + to_string(havingBook) + to_string((int)hasNote);}

Home::Home(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, shared_ptr<Book> book,
bool havingBook, bool soundIsPlay):
save(save), window(window), player(player), book(book), havingBook(havingBook), soundIsPlay(soundIsPlay),
    secondBoard(SecondBoard(window))
    {
    texture.loadFromFile("foto/home.png");
    havingBook == true ? keyTexture.loadFromFile("foto/key.png") :
                         keyTexture.loadFromFile("foto/keyNoBook.png");

    ground.setTexture(texture);
    ground.setTextureRect(IntRect(0, 0, 1920, 540));
    ground.setPosition(0, 0);
    key.setTexture(&keyTexture);

    buffer.loadFromFile("muziek/step.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);
    music.openFromFile("muziek/2.ogg");
    music.setVolume(10);
    music.setLoop(true);

    setting = Setting(save, window);
    firstBoard = FirstBoard(window);
    deed = make_unique<Deed>(window);

    vector<lines> upLine;
    upLine.push_back(lines(310, 335, 0, 290));
    upLine.push_back(lines(335, 430, 0, 190));
    upLine.push_back(lines(430, 750, 0, 290));
    upLine.push_back(lines(750, 1000, 0, 310));
    upLine.push_back(lines(1000, 1290, 0, 290));
    upLine.push_back(lines(1290, 1540, 0, 310));
    upLine.push_back(lines(1540, 1920, 0, 290));
    upBord = Borders(upLine);

    vector<lines> downLines;
    downLines.push_back(lines(0, 1920, 385, 540));
    downBord = Borders(downLines);

    vector<lines> leftLines;
    leftLines.push_back(lines(030, 310, 290, 385));
    leftLines.push_back(lines(325, 335, 190, 290));
    leftLines.push_back(lines(990, 1000, 0, 310));
    leftLines.push_back(lines(1530, 1540, 0, 310));
    leftBord = Borders(leftLines);

    vector<lines> rightLines;
    rightLines.push_back(lines(430, 440, 190, 290));
    rightLines.push_back(lines(750, 760, 0, 310));
    rightLines.push_back(lines(1290, 1300, 0, 310));
    rightBord = Borders(rightLines);
}

void Home::setCountHasNote(NoteFourth note) { hasNote = note; }

void Home::setValume(bool flag) { soundIsPlay = flag; }

void Home::died(){
    music.pause();
    setting.died();
    deed->died(soundIsPlay);
}

void Home::goRight(float time){
    if(xForTexture < 960 && player->getX() >= 450 && player->getX() <= 480){
        xForTexture += 0.15 * time;
        ground.setTextureRect(IntRect(int(xForTexture), 0, 960, 540));
        player->goRightSprite(time);
    }
    else {player->goRight(time);}
}

void Home::goLeft(float time){
    if(xForTexture > 0 && player->getX() >= 450 && player->getX() <= 480){
        xForTexture -= 0.15 * time;
        ground.setTextureRect(IntRect(int(xForTexture), 0, 960, 540));
        player->goLeftSprite(time);
    }
    else {player->goLeft(time);}
}

void Home::drawAll(){
    window->clear();
    window->draw(ground);
    player->draw();
    window->draw(key);
    window->display();
}

bool Home::runSetting(){
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

void Home::run(){
    book->setPage((NoteFourth)hasNote);
    if(soundIsPlay) {music.play();}
    else {sound.setVolume(0);}

    player->setPosition(320, 390);

    drawAll();

    Clock clock;
    while (window->isOpen()){
        Event ev;
        while (window->pollEvent(ev)){
            if(ev.type == Event::LostFocus) { if(!runSetting()) { return; } }
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape) { if(!runSetting()) { return; } }
                if(ev.key.code == Keyboard::F){
                    drawAll();
                    book->run();
                }
                if(ev.key.code == Keyboard::T){
                    int x = player->getX() + xForTexture;
                    if(x > 740 && x < 1010 && player->getY() < 320) { runFirstBoard(); }
                    else if(x > 1280 && x < 1530 && player->getY() < 320) { runSecondBoard();  }
                    else if(x > 610 && x < 710 && player->getY() < 300) { died(); return; }
                    else if(x > 1695 && x < 1789 && player->getY() < 300) { died(); return; }
                    else if(x > 1120 && x < 1220 && player->getY() < 300){ 
                        music.pause();
                        setting.died();
                        return;
                    }
                }
            }   
        }
        float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); 
	    time = time / 800;

        if(Keyboard::isKeyPressed(Keyboard::S)){
            if(!rightBord.getContact(player->getX() + xForTexture, player->getY())){
                goRight(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goRight(0);}
        }
        else if(Keyboard::isKeyPressed(Keyboard::A)){
            if(!leftBord.getContact(player->getX() + xForTexture, player->getY())){
                goLeft(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goLeft(0);}
        } 
        else if(Keyboard::isKeyPressed(Keyboard::W)){
            if(!upBord.getContact(player->getX() + xForTexture, player->getY())){
                player->goUp(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goUp(0);}
        }
        else if(Keyboard::isKeyPressed(Keyboard::R)){
            if(!downBord.getContact(player->getX() + xForTexture, player->getY())){
                player->goDown(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goDown(0);}
        }

        drawAll();
    }
}

bool Home::runFirstBoard(){
    firstBoard.setFinishFlag(hasNote == NoteFourth::first || hasNote == NoteFourth::all);
    firstBoard.setSoundPlaying(soundIsPlay);
    if(firstBoard.run()){
        if(hasNote == NoteFourth::none || hasNote == NoteFourth::first){
            hasNote = NoteFourth::first;
        }
        else { hasNote = NoteFourth::all; }
        book->setPage((NoteFourth)hasNote);
    }
}

bool Home::runSecondBoard(){
    secondBoard.setFinishFlag(hasNote == NoteFourth::second || hasNote == NoteFourth::all);
    secondBoard.setSoundPlaying(soundIsPlay);
    if(secondBoard.run()){
        if(hasNote == NoteFourth::none || hasNote == NoteFourth::second){
            hasNote = NoteFourth::second;
        }
        else { hasNote = NoteFourth::all; }
        book->setPage((NoteFourth)hasNote);
    }
}