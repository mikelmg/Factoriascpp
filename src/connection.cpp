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
    Vector2 controlO {(origin->GetCenter().x + target->GetCenter().x)/2, 
        origin->GetCenter().y };
    Vector2 control1 {(origin->GetCenter().x + target->GetCenter().x)/2, 
        target->GetCenter().y };

    //Calculate their new pos in the curve and actualice it
    for (int i = 0; i < items.size(); ++i) {
        //Actualiza la f en relacion a la curva Belzier
        items[i].first+=0.2f*dt;
        //Actualiza su posicion 
        //TODO Items don't need position now and their pos should be corrected
        //TODO maybe correct their f so it's not a proportion but an absolute distance traveled
        items[i].second->SetPosition(GetSplinePointBezierCubic(origin->GetCenter(), controlO, control1,
            target->GetCenter(), items[i].first));

        //If reached -> delete
        if(items[i].first > 1){
            delete items[i].second;
            items.pop_back(); 
        }
    }

}

void Connection::Draw(float upSize)
{
    //#TODO Change the calculation of control points to only refresh when changed and store them as attributes
    Vector2 controlO {(origin->GetCenter().x + target->GetCenter().x)/2, 
        origin->GetCenter().y };
    Vector2 control1 {(origin->GetCenter().x + target->GetCenter().x)/2, 
        target->GetCenter().y };


    //Draw Spline connecting to buildings
    Vector2 dots[4] = { origin->GetCenter() ,controlO, control1, target->GetCenter()};
    DrawSplineBezierCubic(dots, 4, 4, RED);

    //Draw Items
    for (int i = 0; i < items.size(); ++i) {
        items[i].second->Draw(upSize);
    }

}

void Connection::AddItem()
{
    //TODO add any kind of Item
    #define item new Item(origin->GetCenter(), COBALT)
    #define pairItem std::pair<float, Item*> (0,item)
    //Add par f, Item to the list
    items.push_front(pairItem);
}
