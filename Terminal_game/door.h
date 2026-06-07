#pragma once

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
	Door(int xPos, int yPos, int targetId, bool isLocked = false, int puzzleNum = 0);

	int getX() const;
	int getY() const;
	bool isLocked() const;
	void unlock();
	int getTargetLocationId() const;
	int getPuzzleNumber() const;
	void setPuzzleNumber(int num);
    // ¬ыполн€ет взаимодействие с дверью: если закрыта Ч задаЄт пазл через ввод и
	// при успешном ответе разблокирует дверь. ¬озвращает true, если дверь теперь открыта.
	bool interact();
};