#include "headers/item.h"


Item::Item()
{
    position.x = 100;
    position.y = 100;
    this->color = {20, 160, 133, 255};
}

Item::Item(int x, int y, Color color)
{
    position.x = x;
    position.y = y;

    this->color = color;
}

Vector2 Item::GetPosition(){
    return position;
}


void Item::Update(float dt)
{
    position.x += ITEM_VELOCITY*dt;
}

void Item::Draw(float upSize)
{
    DrawRectangle(position.x-upSize/2, position.y-upSize/2, 20+upSize, 20+upSize, color);
}