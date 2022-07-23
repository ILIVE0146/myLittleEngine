#include "Keyboard.h"

Keyboard::Keyboard()
{
	this->keyStates.fill(false);
}

KeyboardEvent Keyboard::ReadKey()
{
	if (this->keybuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = this->keybuffer.front();
		this->keybuffer.pop();
		return e;
	}
}

unsigned char Keyboard::ReadChar()
{
	if (this->charbuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = this->charbuffer.front();
		this->charbuffer.pop();
		return e;
	}
}

void Keyboard::onKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keybuffer.push(KeyboardEvent(KeyboardEvent::Pressed, key));
}

void Keyboard::onKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keybuffer.push(KeyboardEvent(KeyboardEvent::EventType::Released, key));
}
