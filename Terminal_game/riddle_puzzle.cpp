#include "riddle_puzzle.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <locale>
#include "logger.h"

RiddlePuzzle::RiddlePuzzle()
	: Puzzle("Riddle")
{
    std::srand((unsigned)time(nullptr));

	// Единый набор вопросов — должен совпадать с тем, что используется в solve()
	std::vector<std::string> questions =
	{
		"Что всегда идёт, но никогда не приходит?",
		"Сколько месяцев в году имеют 28 дней?",
		"Что можно поймать, но нельзя бросить?",
		"Что принадлежит вам, но другие используют его чаще, чем вы?",
		"Что растёт вниз, а не вверх?"
	};

	int index = rand() % static_cast<int>(questions.size());
	question = questions[index];
	// Сохраняем эталонный ответ (первый вариант) для совместимости
	std::vector<std::vector<std::string>> poolAnswers =
	{
		{"завтра", "tomorrow"},
		{"12", "двенадцать", "twelve"},
		{"простуда", "cold"},
		{"имя", "name"},
		{"борода", "beard"}
	};
	if (index >= 0 && index < static_cast<int>(poolAnswers.size()))
		answer = poolAnswers[index][0];
}

void RiddlePuzzle::start()
{
	std::cout << "ЗАГАДКА\n\n";
	std::cout << question << "\n\n";

	Logger::instance().log(std::string("Riddle presented: ") + question);
}

bool RiddlePuzzle::solve()
{
    std::string input;
	std::cin >> input;

    // Нормализуем ввод с учётом локали (чтобы работать и с кириллицей)
	std::locale loc("");
	std::string lower;
	lower.reserve(input.size());
	for (unsigned char c : input)
		lower.push_back(std::tolower(static_cast<char>(c), loc));

	// Подготовим ту же таблицу ответов, что был создан в конструкторе.
	// Дублируем список тут (не идеал), чтобы маппинг вопросов->ответов был простым.
	std::vector<std::vector<std::string>> poolAnswers =
	{
		{"завтра", "tomorrow"},
		{"12", "двенадцать", "twelve"},
		{"простуда", "cold"},
		{"имя", "name"},
		{"борода", "beard"}
	};

	// Определим индекс текущего вопроса по полю question
	std::vector<std::string> questions =
	{
		"Что всегда идёт, но никогда не приходит?",
		"Сколько месяцев в году имеют 28 дней?",
		"Что можно поймать, но нельзя бросить?",
		"Что принадлежит вам, но другие используют его чаще, чем вы?",
		"Что растёт вниз, а не вверх?"
	};

	int qidx = -1;
	for (size_t i = 0; i < questions.size(); ++i)
	{
		if (questions[i] == question)
		{
			qidx = static_cast<int>(i);
			break;
		}
	}

    if (qidx == -1)
	{
		Logger::instance().log(std::string("Riddle question not recognized: ") + question);
		return false;
	}

	for (auto &opt : poolAnswers[qidx])
	{
        std::string o = opt;
		std::string ol;
		ol.reserve(o.size());
		for (unsigned char c : o)
			ol.push_back(std::tolower(static_cast<char>(c), loc));
        if (lower == ol)
		{
			Logger::instance().log(std::string("Riddle answered correctly: input=") + input + " question=" + question);
			return true;
		}
	}

	Logger::instance().log(std::string("Riddle answered incorrectly: input=") + input + " question=" + question);
	return false;
}

bool RiddlePuzzle::play()
{
	start();

	bool result = solve();
	setCompleted(result);

	return result;
}