#pragma once
#include <raylib.h>
#include <vector>
#include "selectable.h"
#include "connection.h"


static const std::vector<Color> LVLCOLORS = {
    RAYWHITE,
    BEIGE,
    WHITE,
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    LIME,
    BLUE,
    SKYBLUE,
    PURPLE,
    VIOLET,
    DARKPURPLE,
    MAROON,
    DARKGREEN,
    DARKBLUE,
    DARKBROWN,
    DARKGRAY,
    LIGHTGRAY
};
const int BUILDING_SIZE = 40;

class Building: public Selectable //Declaration forward
{
public:
    Building();
    Building(int x, int y, int level);
    void Update(float dt);
    void Draw();
    Vector2 GetCenter();
    void UpdateConnections();
    void AddInConnection(Connection* con);
    void AddOutConnection(Connection* con);
    void DeleteInConnection(Connection* con);
    void DeleteOutConnection(Connection* con);    
    //TODO Make Buildings create Items at speed proportinal to their lvl

private:
    // Vector2 position;
    // bool selected;

    int level;
    Color color;
    std::vector<Connection*> inConnections;
    std::vector<Connection*> outConnections;


};