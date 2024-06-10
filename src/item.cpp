#include "headers/item.h"
#include <algorithm>

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

ItemsType Item::toItemsType(std::string type){

    std::transform(type.begin(), type.end(), type.begin(), ::toupper);

    if(type == "IRON")
        return IRON;
    else if(type == "COPPER")
        return COPPER;
    else if(type == "COBALT")
        return COBALT;
    else if (type == "SILVER")
        return SILVER;
    else if (type == "PLATINUM")
        return PLATINUM;
    else if (type == "ZINC")
        return ZINC;
    else if (type == "NICKEL")
        return NICKEL;
    else if (type == "TIN")
        return TIN;
    else if (type == "TITANIUM")
        return TITANIUM;
    else if (type == "LEAD")
        return LEAD;
    else if (type == "MAGNESIUM")
        return MAGNESIUM;
    else if (type == "ALUMINUM")
        return ALUMINUM;
    else
        return TIN;
    
    return TIN;
}

std::vector<ItemsType> Item::toItemsTypeV(std::vector <std::string> types){
    std::vector<ItemsType> result;

    for(auto it = types.begin(); it != types.end(); ++it){
        result.push_back( toItemsType(*it));
    }
    return result;
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