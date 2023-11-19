#include "Street.h"
#include <iostream>

Street::Street(int save, shared_ptr<RenderWindow> window, shared_ptr<Book> book, shared_ptr<Player> player, bool havingBook):
window(window), book(book), player(player), havingBook(havingBook){
    texture.loadFromFile("foto/street.png");
    upSprite.loadFromFile("foto/street/sprite.png");
    upHalf.loadFromFile("foto/street/half.png");
    havingBook == true ? keyTexture.loadFromFile("foto/key.png") :
                         keyTexture.loadFromFile("foto/keyNoBook.png");

    background.setTexture(&texture);
    sprite.setTexture(&upSprite);
    half.setTexture(&upHalf);
    key.setTexture(&keyTexture);

    setting = Setting(save, window, texture);
    deed = make_unique<Deed>(window);

    buffer.loadFromFile("muziek/step.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);
    music.openFromFile("muziek/street.ogg");
    music.setVolume(5);
    music.setLoop(true);

    vector<lines> upLines;
    upLines.push_back(lines(0, 300, 40, 45));
    upLines.push_back(lines(460, 960, 40, 45));
    upLines.push_back(lines(0, 260, 365, 370));
    upLines.push_back(lines(595, 960, 365, 370));
    upLines.push_back(lines(80, 180, 120, 125));
    upLines.push_back(lines(460, 545, 307, 312));
    upLines.push_back(lines(620, 740, 70, 75)); //
    upBord = Borders(upLines);

    vector<lines> downLines;
    downLines.push_back(lines(0, 960, 395, 400));
    downLines.push_back(lines(595, 960, 295, 300));
    downLines.push_back(lines(0, 260, 295, 300));
    downLines.push_back(lines(80, 180, 80, 85));
    downLines.push_back(lines(460, 545, 280, 285));
    downBord = Borders(downLines);

    vector<lines> leftLines;
    leftLines.push_back(lines(300, 305, 0, 45));
    leftLines.push_back(lines(180, 185, 80, 120));
    leftLines.push_back(lines(260, 265, 295, 365));
    leftLines.push_back(lines(545, 560, 280, 307));
    leftLines.push_back(lines(740, 745, 0, 70)); //
    leftBord = Borders(leftLines);

    vector<lines> rightLines;
    rightLines.push_back(lines(595, 600, 295, 365));
    rightLines.push_back(lines(460, 465, 280, 307)); 
    rightLines.push_back(lines(620, 625, 0, 70)); //
    rightLines.push_back(lines(80, 85, 80, 120));
    rightLines.push_back(lines(460, 485, 0, 45));
    rightBord = Borders(rightLines);
}

string Street::createSaveString() {return ("s" + to_string(book->getPage()) + to_string(havingBook));}

void Street::setPageInBook(int num) {book->setPage(num);}

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
    if(x >= 50 && x <= 200 && y >= 50 && y <= 150) {say.loadFromFile("foto/street/mari.png");}
    else if(x >= 600 && x <= 760 && y <= 110) {say.loadFromFile("foto/street/bazil.png");}
    else if(x >= 450 && x <= 560 && y >= 210 && y <= 360) {say.loadFromFile("foto/street/kim.png");}
    else if(x <= 280 && y >= 270 && y <= 400) {music.pause(); setting.died(); deed->died(soundIsPlay); return false;}
    else if(x >= 580 && y >= 270 && y <= 400){
        Home home = Home(save, window, player, book, soundIsPlay, havingBook);
        sound.pause();
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
            if(event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::Escape){
                    switch (setting.run(createSaveString())){
                    case menuItem::save:
                        return; break;
                    case menuItem::sound:
                        sound.getVolume() == 0 ? sound.setVolume(80) : sound.setVolume(0);
                        music.getStatus() == SoundSource::Status::Paused ? music.play() : music.pause();
                        soundIsPlay == true ? soundIsPlay = false : soundIsPlay = true;
                        break;
                    default:
                        break;
                    }
                }
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