#pragma once
#include "MathUtility.h"
#include "WorldTransform.h"
#include <array>

class Player
{

private:
	// プレイヤーが動かせる領域となるブロック 4辺
	std::array<std::unique_ptr<class Block>, 4> m_blocks;
	// トランスフォーム
	WorldTransform m_transform;

};

