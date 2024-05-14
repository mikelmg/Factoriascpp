#pragma once
#include <raylib.h>


class ItemA //Declaration forward
{
public:
    ItemA();
    ItemA(int x, int y, Color color);
    void Update(float dt);
    void Draw(float upSize);

private:
    float x;
    float y;
    Color color;
    int upSize = 0;
};