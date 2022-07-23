#pragma once

#include "Vector2.h"
class MouseEvent
{
public:
	enum EventType
	{
		Invalid = -1,
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE
	};
private:
	EventType type;
	Vector2i mousePosition;
	
public:
	MouseEvent() : type(EventType::Invalid), mousePosition(0, 0) {}
	MouseEvent(const EventType type, const Vector2i& mousePosition) : type(type), mousePosition(mousePosition) {}
	inline bool isValid() { return this->type == EventType::Invalid; }
	EventType getType() const { return type; }
	inline Vector2i getPosition() const { return this->mousePosition; }
	inline int getPosX() const { return this->mousePosition.x; }
	inline int getPosY() const { return this->mousePosition.y; }
	
};

