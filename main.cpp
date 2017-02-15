#include <QApplication>
#include "Game.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::cout << argc << " " << *argv << std::endl;

    Game window;

    window.resize(300, 400);
    window.setWindowTitle("Brick Breaker");
    window.show();

    return app.exec();
}
