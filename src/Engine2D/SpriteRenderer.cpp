#include "SpriteRenderer.h"
#include "Entity.h"
#include "TransformComponent.h"

SpriteRenderer::SpriteRenderer()
{
	m_sprite = new Sprite();
    m_isVisible = true;
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
    float scale = transform->GetScale();
    Vector2f spriteSize{ (float)m_sprite->GetWidth() * scale, (float)m_sprite->GetHeight() * scale };
    Vector2f drawPos = entityPos - spriteSize * 0.5f;

    m_sprite->SetScale(transform->GetScale());
    m_sprite->SetFlip(transform->GetFlip());
    m_sprite->SetRotation(transform->GetAngle());
    m_sprite->SetRotationCenter(transform->GetRotationCenter());

    m_sprite->SetPos(drawPos);
    m_sprite->Draw(_window);
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
