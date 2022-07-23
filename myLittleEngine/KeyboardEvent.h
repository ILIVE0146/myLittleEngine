#pragma once

class KeyboardEvent
{
public:
	enum EventType
	{
		Invalid = -1,
		Pressed,
		Released
	};

	KeyboardEvent() : type(EventType::Invalid), key(0u) {}
	KeyboardEvent(const EventType type, const unsigned char key) : type(type), key(key) {}
	inline bool isPressed() const { return this->type == EventType::Pressed; }
	inline bool isReleased() const { return this->type == EventType::Released; }
	inline bool isValid() const { return this->type == EventType::Invalid; }
	inline unsigned char getKeyCode() const { return this->key; }

private:
	EventType type;
	unsigned char key;
};