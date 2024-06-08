#include "headers/buffer.h"

//TODO buffer class
    Buffer::Buffer(Vector2 position) {

    }

    void Buffer::Draw() {

    }

    void Buffer::DrawSelection() {

    }

    void Buffer::Update(const float& dt) {}

    Vector2 Buffer::GetCenter() {
        return Vector2{ 0,0 };
    }

    Rectangle Buffer::GetRectangle()  { 
        return Rectangle{};
    }

    int Buffer::GetSize() { return 0; }

SelectableTypes Buffer::GetSelectableType() {
    return BUFFER;
}
