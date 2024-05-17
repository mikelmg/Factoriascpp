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
    void Draw(float upSize, Vector2 position);
protected:
    ItemsType type;
    Color color;
};