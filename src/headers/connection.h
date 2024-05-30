#pragma once
#include <raylib.h>
#include "selectable.h"
#include <deque>
#include <utility>
#include "item.h"

const int ITEM_VELOCITY = 70;
const float ITEM_SPEED = 120.f;

class Selectable;

class Connection //Declaration forward
{
public:
    Connection();
    Connection(Selectable* x, Selectable* y);
    void Selected();
    void NSelected();
    void Update(float dt);
    void Draw(float upSize);
    void AddItem();
    void AddItem(float position);
    void UpdateControl();
    Selectable* GetOrigin();
    Selectable* GetTarget();
    void UpdateBezierLength();


protected:
    Selectable* origin;
    Selectable* target;
    std::deque<float> items;
    bool selected;
    ItemsType type;
    Vector2 controlO, controlT;
    float length;

    //TODO: Connections must be able to stuck if endpoint at max capacity
};