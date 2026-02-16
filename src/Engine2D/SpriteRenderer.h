#pragma once
#include "Component.h"
#include "Lib2D/Drawable.h"
#include "Lib2D/Sprite.h"

class Sprite;

class SpriteRenderer : public Component, public Drawable
{

	Sprite* m_sprite;

public:

	SpriteRenderer();
	~SpriteRenderer();
	void Draw(Window* _window) override;
	void Load(const std::string& _filePath);
	void SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY);
	void SetOpacity(uint8_t _opacity);
};

