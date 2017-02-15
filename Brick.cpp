#include "Brick.hpp"
#include <iostream>

Brick::Brick(int x, int y) {
    image.load("brick.png");
    destroyed = false;
    rectangle = image.rect();
    rectangle.translate(x, y);
}

Brick::~Brick() {
}

QRect Brick::getRectangle() {
    return rectangle;
}

void Brick::setRectangle(QRect rectangle) {
    Brick::rectangle = rectangle;
}

QImage & Brick::getImage() {
    return image;
}

bool Brick::isDestroyed() {
    return destroyed;
}

void Brick::setDestroyed(bool destroyed) {
    Brick::destroyed = destroyed;
}
