#include "headers/item.h"

Item::Item(ItemsType type)
{
    this->type = type;
}

// Draws any Item with a given coordinates, type and current upsize
void Item::Draw(float upSize, Vector2 position, ItemsType type)
{
    DrawRectangle(position.x-upSize/2-ITEM_SIZE/2, position.y-upSize/2-ITEM_SIZE/2, ITEM_SIZE+upSize, ITEM_SIZE+upSize, toColor(type));
}

std::string Item::toString(ItemsType type){

    switch (type)
    {
    case IRON:
        return "Iron";
        break;
    
    case COPPER:
        return "Copper";
        break;

    case COBALT:
        return "Cobalt";
        break;
    }

    return "Generic";
}

Color Item::toColor(ItemsType type){

    switch (type)
    {
    case IRON:
        return GRAY;
        break;
    
    case COPPER:
        return ORANGE;
        break;

    case COBALT:
        return BLUE;
        break;
    }

    return WHITE;
}