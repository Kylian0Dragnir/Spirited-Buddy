#include "SpriteRenderer.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Window.h"
#include <TagComponent.h>

SpriteRenderer::SpriteRenderer()
{
	m_sprite = new Sprite();
    m_isVisible = true;
    m_offset = { 0,0 };
}

SpriteRenderer::~SpriteRenderer()
{
	if (m_sprite)
		delete m_sprite;
}

void SpriteRenderer::Draw(Window* _window)
{
    if (m_isVisible == false)
        return;

    TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

    Vector2f entityPos = transform->GetPos();
    Vector2f scale = transform->GetScale();

    m_sprite->SetScale(scale);
    m_sprite->SetFlip(transform->GetFlip());
    m_sprite->SetRotation(transform->GetAngle());
    m_sprite->SetRotationCenter(transform->GetRotationCenter());

    float tileW = m_sprite->GetWidth() * scale.GetX();
    float tileH = m_sprite->GetHeight() * scale.GetY();

    Vector2f baseDrawPos = entityPos - Vector2f(tileW, tileH) * 0.5f;

    if (m_tiledSize.Length() <= 0)
    {
        m_sprite->SetPos(baseDrawPos + m_offset);
        m_sprite->Draw(_window);
    }
    else
    {
        int countX = (int)ceil(m_tiledSize.GetX() / tileW);
        int countY = (int)ceil(m_tiledSize.GetY() / tileH);

        float totalWidth = countX * tileW;
        float totalHeight = countY * tileH;

        baseDrawPos = entityPos - Vector2f(totalWidth, totalHeight) * 0.5f;

        for (int y = 0; y < countY; y++)
        {
            for (int x = 0; x < countX; x++)
            {
                Vector2f tileOffset = { x * tileW, y * tileH };
                m_sprite->SetPos(baseDrawPos + tileOffset + m_offset);
                m_sprite->Draw(_window);
            }
        }
    }

    if (m_owner->GetComponent<TagComponent>()->Is("WORLD_WRAP"))
    {
        m_sprite->SetPos(baseDrawPos + m_offset + Vector2f{ (float)_window->GetWidth(), 0 });
        m_sprite->Draw(_window);

        m_sprite->SetPos(baseDrawPos + m_offset - Vector2f{ (float)_window->GetWidth(), 0 });
        m_sprite->Draw(_window);

        m_sprite->SetPos(baseDrawPos + m_offset + Vector2f{ 0, (float)_window->GetHeight() });
        m_sprite->Draw(_window);

        m_sprite->SetPos(baseDrawPos + m_offset - Vector2f{ 0, (float)_window->GetHeight() });
        m_sprite->Draw(_window);
    }

}

void SpriteRenderer::Load(const std::string& _filePath)
{
	m_sprite->Load(_filePath);
}

void SpriteRenderer::SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY)
{
	m_sprite->SetFrame(_frameWidth, _frameHeight, _frameX, _frameY);
}

void SpriteRenderer::SetOpacity(uint8_t _opacity)
{
	m_sprite->SetOpacity(_opacity);
}