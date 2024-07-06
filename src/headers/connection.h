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
    ~Connection();
    
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
    void ChangeType(ItemsType type);


protected:
    Selectable* origin;                                 //Where the items are coming from
    Selectable* target;                                 //Where the items are going
    std::deque<float> items;                            //Items in the connection
    bool selected;                                      //Is the connection selected/Does it need to update curve or length
    ItemsType type;                                     //Type of the Items in the connection
    Vector2 controlO, controlT;                         //Bezier control points
    float length;                                       //Length of the curve           

    //TODO: Connections must be able to stuck if endpoint at max capacity
};