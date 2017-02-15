#include <QImage>
#include <QRect>

class Paddle {

public:
    // Constructs Paddle object. Initializes image and Qt objects
    Paddle();
    // Dereferences Paddle Object
    ~Paddle();

public:
    // Resets Paddle to original x and y coords
    void resetState();
    // Moves Paddle
    void move();
    // Sets vx
    void setvx(int);
    // Gets vx
    int getvx();
    // Gets Qt rect
    QRect getRectangle();
    // Gets Qt image
    QImage & getImage();

private:
    QImage image;
    QRect rectangle;
    int vx;
    static const int Initial_X = 135;
    static const int Initial_Y = 380;
};
