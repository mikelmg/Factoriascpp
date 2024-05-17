#include "headers/connection.h"
#include <raymath.h>

#define middle Vector2Lerp(origin->GetCenter(), target->GetCenter(), 0.5)


Connection::Connection(Selectable *origin, Selectable *target)
{
    this->origin = origin;
    this->target = target;

    //Calculate control points of the curve
    controlO = {(origin->GetCenter().x + target->GetCenter().x)/2, origin->GetCenter().y};
    controlT = {(origin->GetCenter().x + target->GetCenter().x)/2, target->GetCenter().y };
}

void Connection::Selected()
{
}

void Connection::NSelected()
{
}

void Connection::Update(float dt)
{
    //Calculate their new pos in the curve and actualice it
    for (int i = 0; i < items.size(); ++i) {
        //Actualiza la f en relacion a la curva Belzier
        items[i].first+=ITEM_SPEED*dt;
        //Actualiza su posicion 
        //TODO maybe correct their f so it's not a proportion but an absolute distance traveled
        //If reached -> delete
        if(items[i].first > 1){
            delete items[i].second;
            items.pop_back(); 
        }
    }

}

void Connection::Draw(float upSize)
{

    //Draw Spline connecting to buildings
    Vector2 dots[4] = { origin->GetCenter() ,controlO, controlT, target->GetCenter()};
    DrawSplineBezierCubic(dots, 4, 4, RED);

    //Draw Items
    for (int i = 0; i < items.size(); ++i) {
        items[i].second->Draw(upSize, GetSplinePointBezierCubic(origin->GetCenter(), controlO, controlT,
            target->GetCenter(), items[i].first));
    }

}

void Connection::AddItem()
{
    //TODO add any kind of Item
    #define item new Item(COBALT)
    #define pairItem std::pair<float, Item*> (0,item)
    //Add par f, Item to the list
    items.push_front(pairItem);
}

void Connection::UpdateControl()
{
    controlO = {(origin->GetCenter().x + target->GetCenter().x)/2, origin->GetCenter().y};
    controlT = {(origin->GetCenter().x + target->GetCenter().x)/2, target->GetCenter().y };
}