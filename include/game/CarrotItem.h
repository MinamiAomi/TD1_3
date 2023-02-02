#pragma once
#include "Item.h"

class CarrotItem :
    public Item
{
private:

public:
    CarrotItem() {}
    ~CarrotItem() {}

    void Initalize();
    void Update();
    void Draw();
    void Draw2D();

    void OnCollision();

    TypeId typeId() const override { return kItemTypeCarrot; }
};

