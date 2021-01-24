#include "MenuItem.h"

MenuItem::MenuItem(int newX, int newY, string text) : x(newX), y(newY), text(text)
{

}

int MenuItem::GetX() { return this->x; }
int MenuItem::GetY() { return this->y; }
string MenuItem::GetText() { return this->text; }