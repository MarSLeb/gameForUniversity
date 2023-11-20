  #include "SecondLoc.h"
#include <iostream>
#include <string>

SecondLoc::~SecondLoc() {}

SecondLoc::SecondLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<RectangleShape> background, shared_ptr<Player> player,
shared_ptr<Book> book, bool havingBook, int listBool):
save(save), window(window), background(background), player(player), book(book), havingBook(havingBook){
    hasNote = listBool == 1;
    
    for(int i = 0; i < 3; i++) {potionTexture[i].loadFromFile("foto/potion/" + to_string(i + 1) + ".png");}
    potion[0].setTexture(potionTexture[0]);
    potion[1].setTexture(potionTexture[2]);
    potion[2].setTexture(potionTexture[2]);
    potion[3].setTexture(potionTexture[1]);
    potion[4].setTexture(potionTexture[1]);
    potion[5].setTexture(potionTexture[0]);
    potion[6].setTexture(potionTexture[2]);
    for(int i = 0, y = 320; i < 7; i++, y+= 15) {potion[i].setPosition(30, y);}
    curPotion = 8;
    finishPotioin = false;

    texture.loadFromFile("foto/second.png");
    listTexture.loadFromFile("foto/potion/list.png");
    havingBook == true ? keyTexture.loadFromFile("foto/key.png") :
                         keyTexture.loadFromFile("foto/keyNoBook.png");
    upTexture.loadFromFile("foto/secondUp.png");
    list.setTexture(&listTexture);
    noticeTexture.loadFromFile("foto/notion.png");
    notice.setTexture(&noticeTexture);

    vector<lines> upLine;
    upLine.push_back(lines(245, 560, 185, 190));
    upLine.push_back(lines(0, 245, 230, 232));
    upLine.push_back(lines(560, 960, 245, 250));
    upBord = Borders(upLine);

    vector<lines> downLines;
    downLines.push_back(lines(0, 960, 403, 405));
    downLines.push_back(lines(0, 60, 240, 243));
    downBord = Borders(downLines);

    vector<lines> leftLines;
    leftLines.push_back(lines(60, 63, 240, 403));
    leftLines.push_back(lines(240, 245, 185, 230));
    leftBord = Borders(leftLines);

    vector<lines> rightLines;
    rightLines.push_back(lines(555, 560, 185, 245));
    rightBord = Borders(rightLines);

    potionPazzle = Potion(window, book, havingBook ? Pickup::Book : Pickup::None);
    setting = Setting(save, window, texture);
    deed = make_unique<Deed>(window);

    buffer.loadFromFile("muziek/step.ogg");
    sound.setBuffer(buffer);
    sound.setVolume(80);
    bufferForNotion.loadFromFile("muziek/notion.ogg");
    notionSound.setBuffer(bufferForNotion);
    notionSound.setVolume(40);
    music.openFromFile("muziek/2.ogg");
    music.setVolume(10);
    music.setLoop(true);
}

void SecondLoc::setCurPotion(int num) {num == 8 ? curPotion = 8 : curPotion = num; finishPotioin = (num != 8);}

void SecondLoc::drawPotion(){
    for(int i = 0; i < 7; i++){
        if(i != curPotion) {window->draw(potion[i]);}
    }
}

string SecondLoc::createSaveString(){
    return ("2" + to_string(book->getPage()) + " " +
            to_string(hasNote == true) + to_string(curPotion) + to_string(havingBook));
}

void SecondLoc::drawList(){
    if(hasNote) {return;}
    window->draw(list);
}

void SecondLoc::died(){
    setting.died();
    deed->died(soundIsPlay);
}

void SecondLoc::setValue(bool flag) {soundIsPlay = flag;}

void SecondLoc::drawAll(float time){
    window->clear();
        window->draw(*background);
        drawList();
        player->draw();
        window->draw(upground); 
        drawPotion();
        window->draw(key);
        if(hasNote && !havingBook) { window->draw(listKey); }
        if(noticeIsRun && time < 2.5) {window->draw(notice);}
        window->display();
}

void SecondLoc::addNote(){
    if(!havingBook && hasNote){
        listKeyTexture.loadFromFile("foto/potion/listKey.png");
        listKey.setTexture(&listKeyTexture);
        noteTexture.loadFromFile("foto/potion/listLikeBook.png");
        note.setTexture(&noteTexture);
    }
}

void SecondLoc::drawNote(){
    window->draw(listKey);
    window->draw(note);
    window->display();

    while (window->isOpen()){
        Event ev;
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased && ev.key.code == Keyboard::F){
                return;
            }
        }
    }
   
}

void SecondLoc::run(){
    background->setTexture(&texture);
    upground.setTexture(&upTexture);
    key.setTexture(&keyTexture);
    player->setPosition(535, 405);
    addNote();

    if(soundIsPlay) {music.play();}
    else {sound.setVolume(0);}

    drawAll(0);

    Clock clock;
    Clock clockForNotice;
    while(window->isOpen()){
        Event ev;
        if(!noticeIsRun) {clockForNotice.restart();}
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape){
                    switch (setting.run(createSaveString())){
                    case menuItem::save:
                        return; 
                        break;
                    case menuItem::sound:
                        sound.getVolume() == 0 ? sound.setVolume(80) : sound.setVolume(0);
                        music.getStatus() == SoundSource::Status::Paused ? music.play() : music.pause();
                        notionSound.getVolume() == 0 ? notionSound.setVolume(80) : notionSound.setVolume(0);
                        soundIsPlay? soundIsPlay = false : soundIsPlay = true;
                        break;
                    default:
                        break;
                    }
                }
                if(ev.key.code == Keyboard::F){
                    drawAll(clockForNotice.getElapsedTime().asSeconds());
                    if(havingBook){
                        book->run();
                    }
                    else if(hasNote){
                        drawNote();
                    }
                    
                }
                if(ev.key.code == Keyboard::T){
                    if(!noticeIsRun && player->getX() >= 800 && player->getX() <= 960 && player->getY() >= 240){
                        hasNote = true;
                        book->setPage(1); 
                        addNote();
                        noticeIsRun = true; 
                        if(soundIsPlay) {notionSound.play();}
                    }
                    if(player->getY() >= 250 && player->getX() <= 70 && !finishPotioin){
                        curPotion = potionPazzle.run(hasNote);
                        if(curPotion != 8) {finishPotioin = true;}
                        if(curPotion == 6 || curPotion == 3 || curPotion == 2) {music.pause(); died(); return;}
                    }
                    if(player->getX() >= 330 && player->getX() <= 440 && player->getY() <= 195){
                        Street loc = Street(save, window, book, player, havingBook);
                        music.pause(); 
                        loc.setValue(soundIsPlay); 
                        loc.run(curPotion); 
                        return;
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
        drawAll(clockForNotice.getElapsedTime().asSeconds());   
    }
}