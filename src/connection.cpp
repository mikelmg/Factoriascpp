#include "headers/connection.h"
#include <raymath.h>

#define middle Vector2Lerp(origin->GetCenter(), target->GetCenter(), 0.5)
#define NUM_SEGMENTS_BEZIER 100

Connection::Connection(Selectable *origin, Selectable *target)
{
    this->origin = origin;
    this->target = target;

    //Calculate control points of the curve
    controlO = {(origin->GetCenter().x + target->GetCenter().x)/2, origin->GetCenter().y};
    controlT = {(origin->GetCenter().x + target->GetCenter().x)/2, target->GetCenter().y };

    UpdateBezierLength();
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
        items[i].position+=ITEM_SPEED*dt;
        //Actualiza su posicion 
        //If reached -> delete
        if(items[i].position >= length){
            delete items[i].item;
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
        items[i].item->Draw(upSize, GetSplinePointBezierCubic(origin->GetCenter(), controlO, controlT,
            target->GetCenter(), items[i].position/length));
    }

}

void Connection::AddItem()
{
    //TODO add any kind of Item
    #define item new Item(COBALT)
    #define pairItem ItemsPosition {0,item}
    //Add par f, Item to the list
    items.push_front(pairItem);
}

void Connection::UpdateControl()
{
    controlO = {(origin->GetCenter().x + target->GetCenter().x)/2, origin->GetCenter().y};
    controlT = {(origin->GetCenter().x + target->GetCenter().x)/2, target->GetCenter().y };
}

Selectable* Connection::GetOrigin(){
    return origin;
}

Selectable* Connection::GetTarget(){
    return target;
}

// Función para calcular la longitud total de la curva de Bézier cúbica
void Connection::UpdateBezierLength() {
    length = 0.0f;
    Vector2 prevPoint = origin->GetCenter();

    // Dividir la curva en numSegments segmentos y sumar las longitudes de estos segmentos
    for (int i = 1; i <= NUM_SEGMENTS_BEZIER; i++) {
        float t = (float)i / (float)NUM_SEGMENTS_BEZIER; // Calcular t para el segmento actual
        Vector2 point = GetSplinePointBezierCubic(target->GetCenter(), controlO, controlT,
            target->GetCenter(), t); // Obtener el punto en la curva
        // Calcular la distancia entre el punto actual y el punto anterior
        length += sqrtf((point.x - prevPoint.x) * (point.x - prevPoint.x) + (point.y - prevPoint.y) * (point.y - prevPoint.y));
        prevPoint = point; // Actualizar el punto anterior
    }
}