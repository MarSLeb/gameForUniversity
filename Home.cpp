#include "Home.h"
#include <iostream>

string Home::createSaveString() {return "h" + to_string(book->getPage()) + to_string(havingBook);}

Home::Home(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player, shared_ptr<Book> book,
bool havingBook, bool soundIsPlay):
save(save), window(window), player(player), book(book), havingBook(havingBook), soundIsPlay(soundIsPlay){
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

    setting = Setting(save, window, texture);

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

void Home::run(){
    if(soundIsPlay) {music.play();}
    else {sound.setVolume(0);}

    player->setPosition(320, 390);

    drawAll();

    Clock clock;
    while (window->isOpen()){
        Event ev;
        while (window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape){
                    switch (setting.run(createSaveString())){
                    case menuItem::save:
                        return; break;
                    case menuItem::sound:
                        sound.getVolume() == 0 ? sound.setVolume(80) : sound.setVolume(0);
                        music.getStatus() == SoundSource::Status::Paused ? music.play() : music.pause();
                        soundIsPlay? soundIsPlay = false : soundIsPlay = true;
                        break;
                    default:
                        break;
                    }
                }
                if(ev.key.code == Keyboard::F){
                    drawAll();
                    book->run();
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