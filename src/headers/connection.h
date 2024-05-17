#pragma once
#include <raylib.h>
#include "selectable.h"
#include <deque>
#include <utility>
#include "item.h"

const int ITEM_VELOCITY = 70;


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

protected:
    Selectable* origin;
    Selectable* target;
    std::deque<std::pair<float, Item*>> items;
    bool selected;
    ItemsType type;
};