#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
#include "Matrix44.h"
#include "Sprite.h"

class DebugText 
{
private:
	static const int kMaxCharCount = 512;
	static const int kFontWidth = 9;
	static const int kFontHeight = 18;
	static const int kFontLineCount = 14;
	static const std::string kTexturePath;
	static const Vector2 kDefultSize;

private:
	unsigned int m_textureHandle = 0;
	Sprite* m_sprites[kMaxCharCount] = {};
	size_t m_spriteIndex = 0;

	Vector2 m_pos;
	float m_scale = 1.0f;

	Matrix44 projMat;

public:
	static DebugText* GetInstance();

	void Initalize(float windowWidth = 1280.0f, float windowHeight = 720.0f);

	template<typename ... Args>
	void Printf(const Vector2& pos, float scale, const std::string& fmt, Args ... args);
	template<typename ... Args>
	void Printf(const std::string& fmt, Args ... args);

	void SetPos(const Vector2& pos) { m_pos = pos; }
	void SetScale(float scale) { m_scale = scale; }

private:
	DebugText();
	~DebugText();
	DebugText(const DebugText&) = delete;
	const DebugText& operator=(const DebugText&) = delete;
	void SetSprite(const std::string& str);
};

template<typename ... Args>
void DebugText::Printf(const std::string& fmt, Args ... args) {

	size_t len = fmt.length();
	std::vector<char> buf(len + 1);
	sprintf_s(&buf[0], len + 1, fmt.c_str(), args ...);
	std::string fmtStr(&buf[0], &buf[0] + len);

	for () {
		
	}

}