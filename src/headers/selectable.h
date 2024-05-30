#pragma once
#include <raylib.h>
#include <vector>
#include "connection.h"
#include "item.h"
#include <unordered_map>

class Connection;
//TODO add class origin of materials that implements Selectable
class Selectable //Declaration forward
{
protected:
    Vector2 position;                                            // Coordinates in the world (top left corner of the object)
    Vector2 selectedPosition;                                    // Original position when dragged 

    std::vector<Connection*> inConnections;
    std::vector<Connection*> outConnections;

    std::unordered_map<ItemsType, int> inventary;


    bool selected;                                               // The Selectable is currently been selected (to move, act, etc)

public:
    void CenterPosition();                                              // Rounds position of the object to snap to grid
    static Color ApplyBlueFilter(Color originalColor);                  // Given a color, returns it with a blue filter
    void StoreInitialPosition();                                        // Sets selectedPosition to position
    void AddItemsToConnection(Connection* con, float position);
    void AddItemsToInventary(ItemsType type, int amount);

    virtual void Draw() = 0;                                            // Abstract: Draw the object by it's own implementation
    virtual void DrawSelection()= 0;                                    // Abstract: Draws the object selection mark by it's own implementation                     

    void SetPosition(Vector2 position);                                 // Set position to a given Vector2
    void Selected();                                                    // Set selected to true
    void NSelected();                                                   // Set selected to false

    Vector2 GetPosition();                                              // Get Coordinates in the world (top left corner of the object)
    virtual Vector2 GetCenter() = 0;                                    // Abstract: Get the center of the object, calculated from the position and size
    Vector2 GetSelectedPosition();                                      // Get Original position when dragged
    bool GetSelected();                                                 // Get if it is currently been selected (to move, act, etc)
};