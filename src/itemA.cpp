#include "headers/itemA.h"

ItemA::ItemA()
{
    this->x = 100;
    this->y = 100;
    this->color = {20, 160, 133, 255};
}

ItemA::ItemA(int x, int y, Color color)
{
    this->x = x;
    this->y = y;

    this->color = color;
}

void ItemA::Update(float dt)
{
    this->x += ITEM_VELOCITY*dt;
}

void ItemA::Draw(float upSize)
{

    DrawRectangle(this->x-upSize/2, this->y-upSize/2, 20+upSize, 20+upSize, this->color);
}