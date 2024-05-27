#include "headers/item.h"

Item::Item(ItemsType type)
{
    this->type = type;
}

// Draws any Item with a given coordinates, type and current upsize
void Item::Draw(float upSize, Vector2 position, ItemsType type)
{
    Color color;

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

    DrawRectangle(position.x-upSize/2-ITEM_SIZE/2, position.y-upSize/2-ITEM_SIZE/2, ITEM_SIZE+upSize, ITEM_SIZE+upSize, color);
}