#include "Sprite.h"
#include "Texture.h"	
#include "Window.h"
#include "SDL.h"

Sprite::Sprite() : Transformable({0, 0})
{
	m_texture = nullptr;

	m_frameWidth = 0;
	m_frameHeight = 0;
	m_frameX = 0;
	m_frameY = 0;
}

Sprite::~Sprite()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

bool Sprite::Load(const std::string& _filePath)
{
	if (m_texture == nullptr)
		m_texture = new Texture();

	if (m_texture->Load(_filePath) == false)
		return false;

	int w, h;
	SDL_QueryTexture((SDL_Texture*)m_texture->GetDataPtr(), NULL, NULL, &w, &h);

	m_frameWidth = w;
	m_frameHeight = h;

	return true;
}

void Sprite::SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY)
{
	m_frameWidth = _frameWidth;
	m_frameHeight = _frameHeight;
	m_frameX = _frameX;
	m_frameY = _frameY;
}

void Sprite::SetOpacity(uint8_t _opacity)
{
	SDL_Texture* texture = (SDL_Texture*)m_texture->GetDataPtr();

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, _opacity);
}

void Sprite::Draw(Window* _window)
{
	float scaledW = m_frameWidth * m_scale;
	float scaledH = m_frameHeight * m_scale;

	SDL_Rect dst{ m_pos.GetX(), m_pos.GetY(), scaledW, scaledH };
	SDL_Rect src{ m_frameX, m_frameY, m_frameWidth, m_frameHeight };

	SDL_Point rotCenter{m_rotationCenter.GetX(), m_rotationCenter.GetY()};

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	switch (m_flip)
	{
	case Flip::FLIP_NONE:
		flip = SDL_FLIP_NONE;
		break;

	case Flip::FLIP_HORIZONTAL:
		flip = SDL_FLIP_HORIZONTAL;
		break;

	case Flip::FLIP_VERTICAL:
		flip = SDL_FLIP_VERTICAL;
		break;
	}

	

	SDL_RenderCopyEx(_window->m_renderer, (SDL_Texture*)m_texture->GetDataPtr(), &src, &dst, m_angle, &rotCenter, flip);
}

Texture* Sprite::GetTexture()
{
	return m_texture;
}

int Sprite::GetWidth()
{
	return m_frameWidth;
}

int Sprite::GetHeight()
{
	return m_frameHeight;
}