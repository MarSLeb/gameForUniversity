  #include "SecondLoc.h"
#include <iostream>
#include <string>

SecondLoc::~SecondLoc() {}

SecondLoc::SecondLoc(int save, shared_ptr<RenderWindow> window, shared_ptr<Player> player,
shared_ptr<Book> book, bool havingBook, int listBool):
save(save), window(window), player(player), book(book), havingBook(havingBook){
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

    RectangleShape board;
    board = RectangleShape(Vector2f(260, 230)); // bookcase
    board.setPosition(0, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(375, 185)); // door
    board.setPosition(260, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(350, 245)); // sofa
    board.setPosition(635, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(80, 90)); // table
    board.setPosition(0, 345);
    boards.push_back(board);
    board = RectangleShape(Vector2f(960, 250)); // down bord
    board.setPosition(0, 505);
    boards.push_back(board);

    potionPazzle = Potion(window, book, havingBook ? Pickup::Book : Pickup::None);
    setting = Setting(save, window);
    deed = make_unique<Deed>(window);

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
    return ("2" + to_string(book->getPageTwo()) + " " +
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
        window->draw(background);
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
    background.setTexture(&texture);
    upground.setTexture(&upTexture);
    key.setTexture(&keyTexture);
    player->setPosition(535, 405);
    addNote();

    if(soundIsPlay) {music.play();}

    drawAll(0);

    Clock clock;
    Clock clockForNotice;
    while(window->isOpen()){
        Event ev;
        if(!noticeIsRun) {clockForNotice.restart();}
        while(window->pollEvent(ev)){
            if(ev.type == Event::KeyReleased){
                if(ev.key.code == Keyboard::Escape){
                    drawAll(0);
                    switch (setting.run(createSaveString())){
                        case menuItem::save:
                            return; 
                            break;
                        case menuItem::sound:
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
                        book->setPage(NoteSecond::all); 
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
        player->movePlayer(time, soundIsPlay, boards);
        drawAll(clockForNotice.getElapsedTime().asSeconds());   
    }
}