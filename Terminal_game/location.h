#pragma once
#pragma once
#include "map.h"
#include <string>
#include <vector>

class Location
{
private:
	int locationId;
	std::string locationName;
	Map map;
public:
	Location(int id);
	void init();

	int getId() const;

    // Возвращает список доступных действий в текущей локации
	std::vector<std::string> getActions();

	// Обрабатывает выбранное действие (1-based индекс).
	// Возвращает:
	//  >=0 : id следующей локации (переход)
	//  -1  : переход не состоялся (например, неправильный ответ)
	//  -2  : выход из игры
	int handleAction(int choice);

	// Добавляет дверь в эту локацию в указанных координатах
	void addDoorAt(int x, int y, int targetId, bool isLocked, int puzzleNum);

	// Если в локации есть дверь, ведущая в sourceId, разблокирует её и вернёт true.
	// Иначе вернёт false.
    // Если в локации есть дверь, ведущая в sourceId, разблокирует её и вернёт true.
	// Если заданы matchX/matchY — сначала попытается найти дверь по координатам,
	// ведущую в sourceId (чтобы разблокировать именно ту дверь, через которую пришли).
	// Иначе вернёт false.
	bool unlockDoorToLocation(int sourceId, int matchX = -1, int matchY = -1);
};