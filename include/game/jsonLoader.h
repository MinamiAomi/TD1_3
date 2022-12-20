#pragma once
#include "MathUtility.h"
#include "json.hpp"

struct BlockJsonData {
	int type = {};
	Vector2 position = {};
	float rotation = {};
	float width = 1.0f;
	float height = 1.0f;
};

inline void to_json(nlohmann::json& j, const BlockJsonData& d) {
	j = nlohmann::json{ {d.type,d.position.x,d.position.y,d.rotation,d.width,d.height} };
}

inline void from_json(const nlohmann::json& j, BlockJsonData& d) {
	j.at(0).get_to(d.type);
	j.at(1).get_to(d.position.x);
	j.at(2).get_to(d.position.y);
	j.at(3).get_to(d.rotation);
	j.at(4).get_to(d.width);
	j.at(5).get_to(d.height);
}