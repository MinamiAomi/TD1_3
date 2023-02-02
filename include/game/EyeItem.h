#pragma once
#include "Item.h"

class EyeItem :
    public Item
{
private:

public:
    EyeItem() {}
    ~EyeItem() {}

    void Initalize();
    void Update();
    void Draw();
    void Draw2D();

    void OnCollision();

    TypeId typeId() const override { return kItemTypeEye; }
};

