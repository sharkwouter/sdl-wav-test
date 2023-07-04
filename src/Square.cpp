#include "Square.hpp"

Square::Square(int x, int y, int width): x(x), y(y), width(width)  {
    this->speed = 1;
}

Square::~Square() {

}

void Square::Move() {
    if (this->x <= 0) {
        this->speed = 1;
    }
    if ((this->x + this->width) >= 480) {
        this->speed = -1;
    }
    this->x += this->speed;
}

void Square::Draw(SDL_Renderer * renderer) {
    SDL_Rect rect = {this->x, this->y, this->width, this->width};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}