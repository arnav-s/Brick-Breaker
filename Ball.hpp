#include <QImage>
#include <QRect>

class Ball {
public:
    // Constructor for Ball object. Sets Ball image, Qt attributes, and
    // initial trajectory
    Ball();
    // Dereferences Ball object
    ~Ball();

public:
    // Sets object position to initial x and y coords
    void resetState();
    // Called whenever frame is refreshed. Translates Qt rect
    void ballMove();
    // Sets x coord
    void setX(int);
    // Sets y coord
    void setY(int);
    // Gets x coord
    int getX();
    // Gets x coord
    int getY();
    // Gets Qt rect
    QRect getRectangle();
    // Gets Qt image
    QImage & getImage();

private:
    int xCoord;
    int yCoord;
    QImage image;
    QRect rectangle;
    // coordinate values
    static const int Initial_X = 155;
    static const int Initial_Y = 375;
    static const int Right_Wall = 300;
    static const int Left_Wall = 0; 
    static const int Top_Wall = 0;
};
