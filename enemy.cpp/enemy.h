#include "Enemy.h"
#include "Player.h"

void Enemy::onStomped(Player& p) {
    alive_ = false;
    p.addScore(100);
    p.bounce();
}

void Enemy::onTouch(Player& p) {
    p.hurt({(p.center().x < center().x ? -300.f : 300.f), -300.f});
}
