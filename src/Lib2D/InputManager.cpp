#include <SDL.h>
#include <iostream>
#include "InputManager.h"

InputManager::InputManager()
{
	m_keyboardState = SDL_GetKeyboardState(NULL);
}

InputManager& InputManager::Get()
{
	static InputManager Instance;
	return Instance;
}

void InputManager::Update()
{
	memcpy(m_prevKeyboardState, m_keyboardState, KEY_NUM_SCANCODES * sizeof(Uint8));
	SDL_PumpEvents();

	m_prevMouseState = m_mouseState;
	m_mouseState = SDL_GetMouseState(NULL, NULL);
}

Vector2f InputManager::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return { (float)x, (float)y };
}

bool InputManager::IsKeyDown(Key _key)
{
	SDL_Scancode scancode = SDL_GetScancodeFromKey(_key);
	return m_prevKeyboardState[scancode] == 0 && m_keyboardState[scancode] == 1;
}

bool InputManager::IsKeyHeld(Key _key)
{
	SDL_Scancode scancode = SDL_GetScancodeFromKey(_key);
	return m_keyboardState[scancode];
}

bool InputManager::IsKeyReleased(Key _key)
{
	SDL_Scancode scancode = SDL_GetScancodeFromKey(_key);
	return m_prevKeyboardState[scancode] == 1 && m_keyboardState[scancode] == 0;
}

bool InputManager::IsMouseDown(MouseButton _button)
{
	return (m_prevMouseState & SDL_BUTTON(_button)) == 0 && (m_mouseState & SDL_BUTTON(_button)) == 1;
}

bool InputManager::IsMouseHeld(MouseButton _button)
{
	return (m_mouseState & SDL_BUTTON(_button)) != 0;
}

bool InputManager::IsMouseReleased(MouseButton button)
{
	return (m_prevMouseState & SDL_BUTTON(button)) == 1 && (m_mouseState & SDL_BUTTON(button)) == 0;
}
