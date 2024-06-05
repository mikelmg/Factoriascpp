#pragma once
#include "selectable.h"
#include "item.h"
#include <raylib.h>


class Buffer : public Selectable {
public:
    Buffer(Vector2 position);
    void Draw();
    void DrawSelection();
    void Update(const float& dt);
    Vector2 GetCenter();
    Rectangle GetRectangle() override;
    int GetSize() override;

private:
    ItemsType type;
    int maxItems;
};
