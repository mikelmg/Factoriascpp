#pragma once
#include <raylib.h>
#include "selectable.h"
#include <deque>
#include <utility>
#include "item.h"

const int ITEM_VELOCITY = 70;
const float ITEM_SPEED = 0.2f;

struct ItemsPosition{
    float position;
    Item* item;
};

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
    void UpdateControl();
    Selectable* GetOrigin();
    Selectable* GetTarget();

protected:
    Selectable* origin;
    Selectable* target;
    std::deque<ItemsPosition> items;
    bool selected;
    ItemsType type;
    Vector2 controlO, controlT;
    //TODO: Connections must be able to stuck if endpoint at max capacity
};