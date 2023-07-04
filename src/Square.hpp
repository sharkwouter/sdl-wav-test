#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SDL.h>

class Square {
public:
    Square(int x, int y, int width);
    ~Square();

    void Move();
    void Draw(SDL_Renderer * renderer);

private:
    int x;
    int y;
    int width;
    int speed;
};

#endif // SQUARE_HPP