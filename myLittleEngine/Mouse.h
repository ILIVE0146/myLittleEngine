#pragma once

#include "MouseEvent.h"
#include <queue>
class Mouse
{
public:
	void onLeftPressed(Vector2i pos);
	void onLeftReleased(Vector2i pos);
	void onRightPressed(Vector2i pos);
	void onRightReleased(Vector2i pos);
	void onMiddlePressed(Vector2i pos);
	void onMiddleReleased(Vector2i pos);
	void onWheelUp(Vector2i pos);
	void onWheelDown(Vector2i pos);
	void onMouseMove(Vector2i pos);

	inline bool isLeftPressed() const { return leftKey; }
	inline bool isRightPressed() const { return rightKey; }
	inline bool isMiddlePressed() const { return middleKey; }
	
	inline Vector2i getPosition() const { return this->position; }
	inline int getPosX() const { return this->position.x; }
	inline int getPosY() const { return this->position.y; }

	bool isEventBufferEmpty() const { return this->eventBuffer.empty(); }
	MouseEvent readEvent();

private:
	std::queue<MouseEvent> eventBuffer;
	Vector2i position = Vector2i(0, 0);
	bool leftKey = false;
	bool rightKey = false;
	bool middleKey = false;
};