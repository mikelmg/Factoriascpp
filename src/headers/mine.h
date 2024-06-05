#pragma once
#include "selectable.h"
#include "item.h"
#include <raylib.h>

static const int MINE_SIZE = 60;



class Mine: public Selectable{
public:
    Mine();
    Mine(Vector2 position);
    Mine(Vector2 position, ItemsType type);
    ~Mine() override;

    void Draw();
    void DrawSelection();

    void AddItemsToConnection(Connection* con, float position);

    Vector2 GetCenter();
    Rectangle GetRectangle() override;
    int GetSize() override;
    SelectableTypes GetSelectableType() override;


    void Creation(const float &dt);

private:
    float production;
    ItemsType type;
    float spawnTimer;

};