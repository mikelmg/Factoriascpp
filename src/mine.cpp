#include "headers/mine.h"
#include <raymath.h>

Mine::Mine(){
    position.x = 20;
    position.y = 20;
}

Mine::Mine(Vector2 position){

    this->position.x = position.x;
    this->position.y = position.y;
    
    type = COBALT;

    spawnTimer = 0;
    selected = false;
}

Mine::Mine(Vector2 position, ItemsType type){

    this->position.x = position.x;
    this->position.y = position.y;
    
    this->type = type;

    spawnTimer = 0;
    selected = false;

    production = 0.4f;
}



void Mine::Creation(const float &dt){
        
    spawnTimer += dt;
    int amountProduced = spawnTimer / production;

    if(spawnTimer >= production){
        for(Connection* con: outConnections){//Every Conn
            for(int i = 1; i <= amountProduced; i++)//In case of lag
                AddItemsToConnection(con, spawnTimer-production*i);//Is this order right?
        }
        spawnTimer=0;
    }
}


void Mine::Draw()
{
    
    for (auto const& [key, val] : inventary){
        std::string text = Item::toString(key);

        text.append(": ");
        text.append(std::to_string(val));

        DrawText(text.data(), position.x, position.y -20, 20, GREEN);
    }

    Color color = Item::toColor(type);
    if (selected){
        DrawSelection();
        color = ApplyBlueFilter(color);
    }
    DrawRectangle(position.x, position.y, MINE_SIZE, MINE_SIZE, color);
}

Vector2 Mine::GetCenter()
{
    return Vector2(Vector2AddValue(position, MINE_SIZE/2) );
}

void Mine::DrawSelection(){
    #define rectangle Rectangle{position.x-2, position.y-2, MINE_SIZE+2, MINE_SIZE+2}
    DrawRectangleRoundedLines(rectangle, 0.5, 4, 1, RED);
}

Rectangle Mine::GetRectangle(){
    return Rectangle{position.x, position.y, MINE_SIZE, MINE_SIZE};
}

int Mine::GetSize() {
    return MINE_SIZE;
}