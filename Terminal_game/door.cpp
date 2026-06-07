#include "door.h"

Door::Door(int targetId, bool isLocked)
	: x(0),
	y(0),
	locked(isLocked),
	puzzleNumber(0),
	targetLocationId(targetId)
{
}

bool Door::isLocked() const
{
	return locked;
}

void Door::unlock()
{
	locked = false;
}

int Door::getTargetLocationId() const
{
	return targetLocationId;
}