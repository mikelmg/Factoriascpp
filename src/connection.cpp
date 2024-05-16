#include "headers/connection.h"
#include <raymath.h>

#define middle Vector2Lerp(origin->GetCenter(), target->GetCenter(), 0.5)


Connection::Connection(Selectable *origin, Selectable *target)
{
    this->origin = origin;
    this->target = target;
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
        items[i].first+=0.2f*dt;
        //Actualiza su posicion 
        items[i].second->SetPosition(GetSplinePointBezierQuad(origin->GetPosition(), middle, 
        target->GetPosition(), items[i].first));

        //If reached -> delete
        if(items[i].first > 1){
            items.erase(items.begin() + i); 
        }
    }

}

void Connection::Draw(float upSize)
{
    //Draw Spline connecting to buildings
    Vector2 dots[3] = {origin->GetCenter(), middle, target->GetCenter()};
    DrawSplineBezierQuadratic(dots, 3, 4, RED);

    //Draw Items
    for (int i = 0; i < items.size(); ++i) {
        items[i].second->Draw(upSize);
    }

}

void Connection::AddItem()
{
    #define item new Item(origin->GetCenter(), COBALT)
    #define pairItem std::pair<float, Item*> (0,item)
    //Add par f, Item to the list
    items.push_back(pairItem);
}
