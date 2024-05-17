#include "headers/item.h"

Item::Item()
{
    color = {20, 160, 133, 255};
}

Item::Item(ItemsType type)
{

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


void Item::Draw(float upSize, Vector2 position)
{
    DrawRectangle(position.x-upSize/2-ITEM_SIZE/2, position.y-upSize/2-ITEM_SIZE/2, 15+upSize, 15+upSize, color);
}