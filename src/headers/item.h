#pragma once
#include <raylib.h>
#include <vector>

// 
const int ITEM_VELOCITY = 70;

class Item //Declaration forward
{
public:
    Item();
    Item(int x, int y, Color color);
    Vector2 GetPosition();
    void Selected();
    void Update(float dt);
    void Draw(float upSize);
protected:
    Vector2 position;
    bool selected;
    Color color;
};