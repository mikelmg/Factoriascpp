#pragma once
#include <raylib.h>
#include <vector>

//Possible types of item
typedef enum {
    IRON,
    ALUMINUM,
    COPPER,
    SILVER,
    PLATINUM,
    ZINC,
    NICKEL,
    TIN,
    TITANIUM,
    LEAD,
    MAGNESIUM,
    COBALT,
}ItemsType;

const int ITEM_SIZE =10;

class Item //Declaration forward
{
protected:
    ItemsType type;                         // Type of the Item
public:                            
    Item(ItemsType type);      
    //TODO Add Non static, no pos and type method           
    void Draw(float upSize);                                                    // Draws this Item with a given current upsize                        
    static void Draw(float upSize, Vector2 position, ItemsType type);           // Draws any Item with a given coordinates, type and current upsize

};