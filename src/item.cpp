#include "headers/item.h"

Item::Item()
{
    position.x   = 100;
    position.y = 100;
    color = {20, 160, 133, 255};
}

Item::Item(Vector2 position, ItemsType type)
{
    this->position = position;

    this->type = type;

    switch (type)
    {
    case IRON:
        color = GRAY;
        break;
    
    case COPPER:
        color = ORANGE;
        break;

    case COBALT:
        color = BLUE;
        break;

    }
}

Vector2 Item::GetPosition(){
    return position;
}

void Item::SetPosition(Vector2 newPosition)
{
    position = newPosition;
}
void Item::Update(float dt)
{
    // position.x += ITEM_VELOCITY*dt;

}

void Item::Draw(float upSize)
{
    DrawRectangle(position.x-upSize/2, position.y-upSize/2, 20+upSize, 20+upSize, color);
}