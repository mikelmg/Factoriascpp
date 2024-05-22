#pragma once
#include <raylib.h>
#include <vector>

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
public:
    Item();
    Item(ItemsType type);
    static void Draw(float upSize, Vector2 position, ItemsType type);
protected:
    ItemsType type;
};