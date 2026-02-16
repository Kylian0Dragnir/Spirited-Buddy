#pragma once
#include "Transformable.h"
#include "Drawable.h"
#include <string>

class Texture;

class Sprite : public Transformable, public Drawable
{
	Texture* m_texture;
	int m_frameWidth;
	int m_frameHeight;
	int m_frameX;
	int m_frameY;

public:

	Sprite();
	~Sprite();

	bool Load(const std::string& _filePath);
	void SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY);
	void SetOpacity(uint8_t _opacity);

	void Draw(Window* _window) override;

	Texture* GetTexture();
	int GetWidth();
	int GetHeight();
};