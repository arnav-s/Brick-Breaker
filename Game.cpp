#include <QPainter>
#include <QApplication>
#include "Game.hpp"
#include <iostream>

Game::Game(QWidget *parent) : QWidget(parent) {
    // init game variables
    x = 0;
    lives = 3;
    gameEnded = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    ball = new Ball();
    paddle = new Paddle();
    score = 0;
    int numBricks = 0;

    // initialize game with 30 bricks
    for (int i=0; i<5; i++) {
        for (int j=0; j<6; j++) {
            bricks[numBricks] = new Brick(j*40+30, i*10+50);
            numBricks++;
        }
    }
}

Game::~Game() {
    delete ball;
    delete paddle;

    for (int i=0; i<noBricks; i++) {
        delete bricks[i];
    }
}

void Game::paintEvent(QPaintEvent *evnt) {
    Q_UNUSED(evnt);

    QPainter painter(this);

    if (gameEnded) {
        endGame(&painter, "You Lost");
    } else if(gameWon) {
        endGame(&painter, "You Won");
    }

    else {
        drawObjects(&painter);
    }
}


void Game::drawObjects(QPainter *painter) {
    painter->drawImage(ball->getRectangle(), ball->getImage());

    painter->drawImage(paddle->getRectangle(), paddle->getImage());

    QFont font("Arial", 9, QFont::DemiBold);

    painter->setFont(font);

    QString score_msg= "Score: " + QString::number(score);

    QString lives_msg= "Lives: " + QString::number(lives);

    painter->drawText(1, 405, score_msg);

    painter->drawText(240, 405, lives_msg);

    for (int i=0; i<noBricks; i++) {
        if (!bricks[i]->isDestroyed()) {
            painter->drawImage(bricks[i]->getRectangle(), bricks[i]->getImage());
        }
    } 
}

void Game::timerEvent(QTimerEvent *evnt) {
    Q_UNUSED(evnt);
    // continually account for physics, painting, and moving objects
    moveObjects();
    Physics();
    repaint();
}

void Game::moveObjects() {
    ball->ballMove();
    paddle->move();
}

void Game::keyReleaseEvent(QKeyEvent *evnt) {
    int vx = 0;

    switch (evnt->key()) {
        // stop paddle left move
        case Qt::Key_Left:
            paddle->setvx(vx);
            break;
        // stop paddle right move
        case Qt::Key_Right:
            paddle->setvx(vx);
            break;
    }
}

void Game::keyPressEvent(QKeyEvent *evnt) {
    int vx = 0;

    switch (evnt->key()) {
        // move paddle left
        case Qt::Key_Left:
            vx = -1;
            paddle->setvx(vx);
            break;
        // move paddle right
        case Qt::Key_Right:
            vx = 1;
            paddle->setvx(vx);
            break;
        // pause/start game
        case Qt::Key_Space:
            if(!gameStarted) {
                startGame();
            }
            else {
                pauseGame();
            }
            break;
        // exit game
        case Qt::Key_Escape:
            qApp->exit();
            break;
        default:
            QWidget::keyPressEvent(evnt);
    }
}

void Game::Physics() {
    // lost game
    if (ball->getRectangle().bottom() > BOTTOM_EDGE && lives==0) {
        endGame();
    }
    // lost a life
    else if (ball->getRectangle().bottom() > BOTTOM_EDGE && lives>0){
        lives--;
        paddle->resetState();
        ball->resetState();
        pauseGame();
    }
    score = 0;
    for (int i=0; i<noBricks; i++) {
        // update score on brick destroy
        if (bricks[i]->isDestroyed()) {
            score++;
        }
        // all bricks destroyed
        if (score == noBricks) {
            Win();
        }
    }

    // ball hit paddle
    if ((ball->getRectangle()).intersects(paddle->getRectangle()))
    {
        ball->setX(ball->getX()+paddle->getvx());
        ball->setY(-1*ball->getY());
    }
    
    // get ball rect boundaries
    int ballLeft = ball->getRectangle().left();
    int ballHeight = ball->getRectangle().height();
    int ballWidth = ball->getRectangle().width();
    int ballTop = ball->getRectangle().top();

    QPoint topRight(ballLeft + ballWidth + 1, ballTop - 1);
    QPoint topLeft(ballLeft - 1, ballTop - 1);
    QPoint bottomLeft(ballLeft - 1, ballTop + ballHeight + 1);
    QPoint bottomRight(ballLeft + ballWidth + 1, ballTop + ballHeight + 1);

    for (int i=0; i<noBricks; i++)
    {
        if (!bricks[i]->isDestroyed() &&
                (ball->getRectangle()).intersects(bricks[i]->getRectangle())) {

            bool flag = false;
            if(bricks[i]->getRectangle().contains(topLeft)
                    && bricks[i]->getRectangle().contains(bottomLeft)){
                ball->setX(-1*ball->getX());
                flag = true;
            }

            if(bricks[i]->getRectangle().contains(bottomLeft) &&
                    bricks[i]->getRectangle().contains(bottomRight)) {
                ball->setY(-1*ball->getY());
                flag = true;
            }

            if(bricks[i]->getRectangle().contains(topLeft)&&
                    bricks[i]->getRectangle().contains(topRight)) {
                ball->setY(-1*ball->getY());
                flag = true;
            }

            if(bricks[i]->getRectangle().contains(bottomRight) &&
                    bricks[i]->getRectangle().contains(topRight)) {
                ball->setX(-1*ball->getX());
                flag = true;
            }

            if (!flag) {
                if(bricks[i]->getRectangle().contains(bottomRight)) {
                    if (ball->getX() >= 0 && ball->getY() < 0) {
                        ball->setX(-1 * ball->getX());
                    }
                    else if (ball->getX() <= 0 && ball->getY() > 0) {
                        ball->setY(-1 * ball->getX());
                    }
                    else if (ball->getX() >= 0 && ball->getY() > 0) {
                        ball->setX(-1 * ball->getX());
                        ball->setY(-1 * ball->getY());
                    }
                } else if(bricks[i]->getRectangle().contains(topRight)) {
                    if (ball->getY() < 0) {
                        ball->setY(-1 * ball->getY());
                    }
                    else if (ball->getX() >= 0 && ball->getY() > 0) {
                        ball->setX(-1 * ball->getX());
                    }
                }
                else if(bricks[i]->getRectangle().contains(bottomLeft)) {
                    if (ball->getX() <= 0 && ball->getY() > 0) {
                        ball->setX(-1 * ball->getX());
                        ball->setY(-1*ball->getY());
                    }
                    else if (ball->getX() <= 0 && ball->getY() < 0) {
                        ball->setX(-1 * ball->getX());
                    }
                    else if (ball->getX() >= 0 && ball->getY() > 0) {
                        ball->setY(-1 * ball->getY());
                    }
                }
                else if(bricks[i]->getRectangle().contains(topLeft)) {
                    if ( ball->getY() < 0) {
                        ball->setY(-1 * ball->getY());
                    }
                    else if (ball->getX() <= 0 && ball->getY() > 0) {
                        ball->setX(-1 * ball->getX());
                    }

                }

            }
            bricks[i]->setDestroyed(true);
        }
    }
}

void Game::startGame() {
    // setup initial state of game
    if (!gameStarted) {
        ball->resetState();
        paddle->resetState();

        for (int i=0; i<noBricks; i++) {
            bricks[i]->setDestroyed(false);
        }

        gameEnded = false;
        gameWon = false; 
        gameStarted = true;
        lives=3;
        timer = startTimer(DELAY);
    } 
}

void Game::pauseGame() {
    if (paused) {
        timer = startTimer(DELAY);
        paused = false;
    } else {
        paused = true;
        killTimer(timer);
    } 
}

void Game::endGame() {
    killTimer(timer);
    gameEnded = true;
    gameStarted = false;

}
void Game::endGame(QPainter *painter, QString msg) {
    QFont font("Arial", 12, QFont::Bold);
    QFontMetrics f(font);
    int textWidth = f.width(msg);

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2));
    painter->drawText(-textWidth/2, 0, msg);
}

void Game::Win() {
    killTimer(timer);
    gameWon = true;
    gameStarted = false;
}
