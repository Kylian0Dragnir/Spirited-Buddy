#include "Window.h"
#include "Drawable.h"
#include "AssetManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string>

Window::Window()
{
    m_width = 0;
    m_height = 0;
    m_isOpen = true;

    m_window = nullptr;
    m_renderer = nullptr;
}

Window::~Window()
{
    TTF_Quit();
}

void Window::Create(const std::string& _title, int _w, int _h)
{
    m_width = _w;
    m_height = _h;

    m_window = SDL_CreateWindow(_title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_width,
        m_height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Surface* icon = IMG_Load("../../Assets/SpiritedBuddy_logo.png");

    SDL_SetWindowIcon(m_window, icon);
        
    AssetManager::Get().SetWindow(this);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    m_renderTarget = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        VIRTUAL_WIDTH,
        VIRTUAL_HEIGHT
    );

    TTF_Init();
}

bool Window::GetIsOpen()
{
    return m_isOpen;
}

void Window::SetIsOpen(bool _isOpen)
{
    m_isOpen = _isOpen;
}

void Window::ClearWindow()
{
    SDL_SetRenderTarget(m_renderer, m_renderTarget);

    SDL_SetRenderDrawColor(m_renderer, 0, 64, 100, 255);
    SDL_RenderClear(m_renderer);
}

void Window::Draw(Drawable* p)
{
    p->Draw(this);
}

void Window::Display()
{
    SDL_SetRenderTarget(m_renderer, nullptr);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    int screenW, screenH;
    SDL_GetWindowSize(m_window, &screenW, &screenH);

    float scaleX = screenW / (float)VIRTUAL_WIDTH;
    float scaleY = screenH / (float)VIRTUAL_HEIGHT;

    float scale = std::min(scaleX, scaleY);

    int newW = VIRTUAL_WIDTH * scale;
    int newH = VIRTUAL_HEIGHT * scale;

    SDL_Rect dst;
    dst.w = newW;
    dst.h = newH;
    dst.x = (screenW - newW) / 2;
    dst.y = (screenH - newH) / 2;

    SDL_RenderCopy(m_renderer, m_renderTarget, nullptr, &dst);

    SDL_RenderPresent(m_renderer);
}
