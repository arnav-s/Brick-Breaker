#include <QWidget>
#include <QKeyEvent>
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class Game : public QWidget {
Q_OBJECT
public:
    // Contructor for Game object. Initializes global varbiables
    Game(QWidget *parent = 0);
    // Deconstructs Game object
    ~Game();

protected:
    // called on Qt paint event
    void paintEvent(QPaintEvent *);
    // called on Qt timer event
    void timerEvent(QTimerEvent *);
    // called on Qt key press event. Left and right arrow keys move paddle, space starts
    // and pauses game, esc quits game
    void keyPressEvent(QKeyEvent *);
    // called on Qt key release event
    void keyReleaseEvent(QKeyEvent *);
    // calls painter to draw Qt objects on screen
    void drawObjects(QPainter *);
    // sets up Qt end game message
    void endGame(QPainter *, QString);
    // handles game end
    void endGame();
    // calls object move methods
    void moveObjects();
    // handles game start
    void startGame();
    // handles game pause (initiated by space key press)
    void pauseGame();
    // handles game win
    void Win();
    // handles game physics
    void Physics();

private:
    int x;
    int timer;
    int score;
    int lives;
    static const int noBricks = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[noBricks];
    bool gameEnded;
    bool gameWon;
    bool gameStarted;
    bool paused;
};
