#pragma once
#include "Item.h"

class BucketItem :
    public Item
{
private:

public:
    BucketItem() {}
    ~BucketItem() {}

    void Initalize();
    void Update();
    void Draw();
    void Draw2D();

    void OnCollision();

    TypeId typeId() const override { return kItemTypeBucket; }
};


