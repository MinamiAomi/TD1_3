#pragma once
class GameObject
{
private:
	class Game* m_game = nullptr;

public:
	GameObject() {}
	GameObject(class Game* game) : m_game(game) {}
	virtual ~GameObject() = 0;

	void SetGame(class Game* game) { m_game = game; }
	class Game* GetGame() { return m_game; }
	const class Game* GetGame() const { return m_game; }
};

