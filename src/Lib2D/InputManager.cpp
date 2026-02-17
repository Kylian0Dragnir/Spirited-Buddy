#include <SDL.h>
#include <iostream>
#include "InputManager.h"

InputManager::InputManager()
{
	m_keyboardState = SDL_GetKeyboardState(NULL);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

InputManager& InputManager::Get()
{
	static InputManager Instance;
	return Instance;
}

void InputManager::Update(float _dt)
{
	memcpy(m_prevKeyboardState, m_keyboardState, KEY_NUM_SCANCODES * sizeof(Uint8));
	SDL_Event event;

	Vector2f allDelta = { 0.f, 0.f };

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEMOTION)
		{
			allDelta = allDelta + Vector2f((float)event.motion.xrel, (float)event.motion.yrel);
		}
	}

	float maxSpeed = 700.f;              
	float maxFrameDelta = maxSpeed * _dt; 

	if (allDelta.Length() > maxFrameDelta)
		allDelta = allDelta.Normalize() * maxFrameDelta;

	m_virtualMousePos = m_virtualMousePos + allDelta;

	m_prevMouseState = m_mouseState;
	m_mouseState = SDL_GetMouseState(NULL, NULL);
}

Vector2f InputManager::GetMousePosition()
{
	return m_virtualMousePos;
}

void InputManager::SetMousePosition(Vector2f pos)
{
	m_virtualMousePos = pos;
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
