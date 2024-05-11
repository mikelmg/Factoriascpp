#include "headers/selectable.h"

Vector2 Selectable::GetPosition(){
    return position;
}

void Selectable::SetPosition(Vector2 position){
    this->position.x = position.x;
    this->position.y = position.y;
}

void Selectable::Selected(){
    selected = true;
}

void Selectable::NSelected(){
    selected = false;
}

bool Selectable::GetSelected(){
    return selected; 
}