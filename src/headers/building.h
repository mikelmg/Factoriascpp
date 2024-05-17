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
    void AddConnection(Connection* con);
    // Vector2 GetPosition();
    // void SetPosition(Vector2 position);
    // void Selected();
    // void NSelected();
    // bool GetSelected();

private:
    // Vector2 position;
    // bool selected;

    int level;
    Color color;
    std::vector<Connection*> connections;

};