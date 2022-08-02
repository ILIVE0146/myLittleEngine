#include "Mouse.h"

void Mouse::onLeftPressed(Vector2i pos)
{
	this->leftKey = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, pos));
}

void Mouse::onLeftReleased(Vector2i pos)
{
	this->leftKey = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, pos));
}

void Mouse::onRightPressed(Vector2i pos)
{
	this->rightKey = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, pos));
}

void Mouse::onRightReleased(Vector2i pos)
{
	this->rightKey = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, pos));
}

void Mouse::onMiddlePressed(Vector2i pos)
{
	this->middleKey = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, pos));
}

void Mouse::onMiddleReleased(Vector2i pos)
{
	this->middleKey = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, pos));
}

void Mouse::onWheelUp(Vector2i pos)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, pos));
}
void Mouse::onWheelDown(Vector2i pos)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, pos));
}
void Mouse::onMouseMove(Vector2i pos)
{
	this->position = pos;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, pos));
}

void Mouse::onMouseMoveRaw(Vector2i pos)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, pos));
}

MouseEvent Mouse::readEvent()
{
	if (this->eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent event = this->eventBuffer.front();
		this->eventBuffer.pop();

		return event;
	}
}
