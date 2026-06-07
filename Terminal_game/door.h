#pragma once

class Door
{
private:
	int x;
	int y;
	bool locked;
	int puzzleNumber;
	int targetLocationId;

public:
	Door(int targetId, bool isLocked = false);

	bool isLocked() const;
	void unlock();
	int getTargetLocationId() const;
};