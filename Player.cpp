#include "Player.h"

Player::Player(std::shared_ptr<RenderWindow> window, int x, int y): window(window){
    heroSprites.loadFromFile("foto/sprite.png");
    hero.setTexture(heroSprites);
    hero.setTextureRect(IntRect(100, 0, 100, 100));
    hero.setPosition(x, y);
}   

void Player::setPosition(int x, int y){
    hero.setPosition(x, y);
}

void Player::goRightSprite(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 200, 100, 100));
}

void Player::goLeftSprite(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 100, 100, 100));
}

void Player::goLeft(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 100, 100, 100));
    
    if(hero.getPosition().x > 0){
        hero.move(-0.1 * time, 0);
    }
}

void Player::goRight(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 200, 100, 100));
    if(hero.getPosition().x < 860) {
        hero.move(0.1 * time, 0);
    }
}

void Player::goUp(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 300, 100, 100));

    if(hero.getPosition().y > 0){
        hero.move(0, -0.1 * time);
    }
}

void Player::goDown(float time){
    current += 0.005 * time;
    if(current > 3) current -= 3;
    hero.setTextureRect(IntRect(100 * int(current), 0, 100, 100));

    if(hero.getPosition().y < 440){
        hero.move(0, 0.1 * time);
    }
}
int Player::getX(){
    return hero.getPosition().x;
}

int Player::getY(){
    return hero.getPosition().y;
}

void Player::draw(){
    window->draw(hero);
}

FloatRect Player::getGlobal(){
    return hero.getGlobalBounds();
}