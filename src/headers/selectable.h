#pragma once
#include <raylib.h>
#include <vector>


class Selectable //Declaration forward
{
public:
    Vector2 GetPosition();
    void SetPosition(Vector2 position);
    void Selected();
    void NSelected();
    bool GetSelected();
    virtual void Draw() = 0;
    virtual void DrawSelection()= 0;
    virtual Vector2 GetCenter() = 0;
    void CenterPosition();
    static Color ApplyBlueFilter(Color originalColor);
    void StoreInitialPosition();
    Vector2 GetSelectedPosition();

protected:
    Vector2 selectedPosition;
    Vector2 position;

    bool selected;
};