#include "TilemapRenderer.h"
#include "TransformComponent.h"
#include "Entity.h"

TilemapRenderer::TilemapRenderer(const std::vector<int>& _tiles, int _width, int _height, int _tileSize, const std::string& _tilesetPath)
{
    m_sprite = new Sprite();

    m_tiles = _tiles;
    m_width = _width;
    m_height = _height;
    m_tileSize = _tileSize;

    m_sprite->Load(_tilesetPath);

    m_tilesetColumns = m_sprite->GetWidth() / m_tileSize;
}

TilemapRenderer::~TilemapRenderer()
{
    delete m_sprite;
}

void TilemapRenderer::Draw(Window* window)
{
    TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
    Vector2f origin = transform->GetPos();

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int index = y * m_width + x;
            int id = m_tiles[index];

            if (id == 0)
                continue;

            id -= 1;

            int frameX = (id % m_tilesetColumns) * m_tileSize;
            int frameY = (id / m_tilesetColumns) * m_tileSize;

            m_sprite->SetFrame(m_tileSize, m_tileSize, frameX, frameY);

            Vector2f worldPos = origin + Vector2f(x * m_tileSize + m_tileSize * 0.5f, y * m_tileSize + m_tileSize * 0.5f);

            Vector2f drawPos = worldPos - Vector2f(m_tileSize, m_tileSize) * 0.5f;

            m_sprite->SetPos(drawPos);
            m_sprite->Draw(window);
        }
    }
}
