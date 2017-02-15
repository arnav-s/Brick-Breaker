#include <QImage>
#include <QRect>

class Brick {
public:
    // Default constructor for a Brick object. Sets initial state to
    // not destroyed and its Qt rectangle and image.
    Brick(int x, int y);
    // Dereferences brick object
    ~Brick();

public:
    // Returns whether or not Brick object is destroyed
    bool isDestroyed();
    // Sets Brick destroyed
    void setDestroyed(bool);
    // Gets Qt rect
    QRect getRectangle();
    // Sets Qt rect
    void setRectangle(QRect);
    // Gets Qt image
    QImage & getImage();

private:
    QImage image;
    QRect rectangle;
    bool destroyed;
};
