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

class Item //Declaration forward
{
public:
    Item();
    Item(Vector2 position, ItemsType type);
    Vector2 GetPosition();
    void SetPosition(Vector2 newPosition);
    void Selected();
    void Update(float dt);
    void Draw(float upSize);
protected:
    Vector2 position;
    bool selected;
    ItemsType type;
    Color color;
};