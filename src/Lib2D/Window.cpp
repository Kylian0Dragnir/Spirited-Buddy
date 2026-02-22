#include "Window.h"
#include "Drawable.h"
#include "AssetManager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string>

Window::Window()
{
    m_width = 0;
    m_height = 0;
    m_x = 0;
    m_y = 0;
    m_isOpen = true;

    m_window = nullptr;
    m_renderer = nullptr;
}

Window::~Window()
{
    TTF_Quit();
}

void Window::Create(const std::string& _title, int _w, int _h, int _x, int _y)
{
    m_width = _w;
    m_height = _h;
    m_x = _x;
    m_y = _y;

    m_window = SDL_CreateWindow(_title.c_str(),
        m_x, m_y, 
        m_width,
        m_height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    AssetManager::Get().SetWindow(this);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

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
    SDL_SetRenderDrawColor(m_renderer, 0, 64, 100, 255);
    SDL_RenderClear(m_renderer);
}

void Window::Draw(Drawable* p)
{
    p->Draw(this);
}

void Window::Display()
{
    SDL_RenderPresent(m_renderer);
}
