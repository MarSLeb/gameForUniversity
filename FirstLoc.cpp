#include "FirstLoc.h"
#include <iostream>

FirstLoc::~FirstLoc() {}

void FirstLoc::setAnswer(string answer){
    cow->setAnswer(answer);
}

string FirstLoc::createSaveString() {
    string b = bookInLoc ? "1" : "0";
    return ("10" + cow->getAnswer() + b);
}

FirstLoc::FirstLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, shared_ptr<Book> book):
window(window), player(player), book(book), save(save){
    keyTexture.loadFromFile("foto/keyNoBook.png");
    texture.loadFromFile("foto/first.png");
    upTexture.loadFromFile("foto/firstUp.png");
    bookTexture.loadFromFile("foto/book.png");
    bookSprite.setTexture(&bookTexture);

    player->setPosition(700, 200);

    vector<lines> upLine;
    upLine.push_back(lines(0, 95, 375, 385));
    upLine.push_back(lines(96, 210, 275, 285));
    upLine.push_back(lines(96, 300, 202, 212));
    upLine.push_back(lines(301, 468, 193, 203));
    upLine.push_back(lines(469, 596, 141, 151));
    upLine.push_back(lines(597, 960, 175, 180));
    upLine.push_back(lines(643, 960, 415, 425));
    upBord = Borders(upLine);

    vector<lines> downLine;
    downLine.push_back(lines(643, 960, 205, 215));
    downBord = Borders(downLine);

    vector<lines> leftLine;
    leftLine.push_back(lines(295, 305, 198, 207));
    leftLine.push_back(lines(205, 210, 207, 280));
    leftLine.push_back(lines(90, 100, 280, 380));
    leftLine.push_back(lines(463, 468, 146, 198));
    leftBord = Borders(leftLine);

    vector<lines> rightLine;
    rightLine.push_back(lines(591, 600, 146, 180));
    rightLine.push_back(lines(630, 643, 214, 420));
    rightBord = Borders(rightLine);

    cow = make_unique<Cow>(window, book);
    setting = Setting(save, window);

    sound.setVolume(80);
    music.setVolume(40);

    buffer.loadFromFile("muziek/step.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);
    music.openFromFile("muziek/muzik.ogg");
    music.setVolume(20);
    music.setLoop(true);
}

void FirstLoc::drawBook(){
    if(bookInLoc) {window->draw(bookSprite);}
}

void FirstLoc::setBookInLoc(bool flag) {
    if(!flag){
        bookInLoc = flag;
        keyTexture.loadFromFile("foto/key.png");
        key.setTexture(&keyTexture);
    }
}

void FirstLoc::setPageInBook(int num) {book->setPage((NoteSecond)num);}

void FirstLoc::drawAll(){
    window->clear();
    window->draw(background);
    player->draw();
    window->draw(upground);
    drawBook();
    window->draw(key);
    window->display();
}

void FirstLoc::run(){
    music.play();
    background.setTexture(&texture);
    upground.setTexture(&upTexture);
    key.setTexture(&keyTexture);
    
    drawAll();

    Clock clock;
    while(window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape){
                    drawAll();
                    switch (setting.run(createSaveString())){
                       case menuItem::save:
                            return; break;
                        case menuItem::sound:
                            sound.getVolume() == 0 ? sound.setVolume(80) : sound.setVolume(0);
                            music.getStatus() == SoundSource::Status::Paused ? music.play() : music.pause();
                            soundIsPlay ? soundIsPlay = false : soundIsPlay = true;
                            break;
                    }
                }
                if(ev.key.code == Keyboard::F && !bookInLoc){
                    drawAll();
                    book->run();
                }
                if(ev.key.code == Keyboard::T){
                    if (player->getX() >= 469 && player->getX() <= 596 && player->getY() >= 141 && player->getY() <= 151){
                        if(cow->run(!bookInLoc)){
                            SecondLoc loc = SecondLoc(save, window, player, book, !bookInLoc);
                            loc.setCurPotion(8);
                            music.pause();
                            loc.setValue(soundIsPlay); 
                            loc.run(); 
                            return;
                        }
                        background.setTexture(&texture);
                    }
                    if(bookInLoc && player->getY() >= 250 && player->getY() <= 350 && player->getX() >= 620){
                        bookInLoc = false;
                        keyTexture.loadFromFile("foto/key.png");
                        key.setTexture(&keyTexture);
                    }
                }
            }
        }

        float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); 
	    time = time / 800; 

        if(Keyboard::isKeyPressed(Keyboard::S)){
            if(!rightBord.getContact(player->getX(), player->getY())){
                player->goRight(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goRight(0);}
        }
        else if(Keyboard::isKeyPressed(Keyboard::A)){
            if(!leftBord.getContact(player->getX(), player->getY())){
                player->goLeft(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goLeft(0);}
        } 
        else if(Keyboard::isKeyPressed(Keyboard::W)){
            if(!upBord.getContact(player->getX(), player->getY())){
                player->goUp(time);
                if (sound.getStatus() != sf::SoundSource::Status::Playing){
                    sound.play();
                }
            }
            else {player->goUp(0);}
        }
        else if(Keyboard::isKeyPressed(Keyboard::R)){
            if(!downBord.getContact(player->getX(), player->getY())){
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