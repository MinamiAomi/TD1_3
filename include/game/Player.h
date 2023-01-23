#pragma once
#include "MathUtility.h"
#include "WorldTransform.h"
#include <array>

class Player
{

private:
	// �v���C���[����������̈�ƂȂ�u���b�N 4��
	std::array<std::unique_ptr<class Block>, 4> m_blocks;
	// �g�����X�t�H�[��
	WorldTransform m_transform;

};

