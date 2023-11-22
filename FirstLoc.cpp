#include "FirstLoc.h"
#include <iostream>

FirstLoc::~FirstLoc() {}

void FirstLoc::setAnswer(string answer){ cow->setAnswer(answer); }

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
    cow = make_unique<Cow>(window, book);
    setting = Setting(save, window);

    RectangleShape board;
    board = RectangleShape(Vector2f(115, 380)); // left table
    board.setPosition(0, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(140, 280)); // chair
    board.setPosition(115, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(70, 207)); // up table
    board.setPosition(255, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(178, 183)); // wardrobe
    board.setPosition(325, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(173, 146)); // door
    board.setPosition(503, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(300, 180)); // vending machine
    board.setPosition(676, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(230, 120)); // sofa
    board.setPosition(715, 300);
    boards.push_back(board);
    board = RectangleShape(Vector2f(42, 600)); // left board
    board.setPosition(0, 0);
    boards.push_back(board);
    board = RectangleShape(Vector2f(50, 600)); // right board
    board.setPosition(930, 0);
    boards.push_back(board);
    
    music.openFromFile("muziek/muzik.ogg");
    music.setLoop(true);
    music.setVolume(20);
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
        player->movePlayer(time, soundIsPlay, boards);
        drawAll();
    }
}



