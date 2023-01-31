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

    void OnCollision();

    TypeId typeId() const override { return kItemTypeCarrot; }
};

