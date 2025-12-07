#include "FunctionsSystem.h"

void clearScreen()
{
	std::wcout << L"\033[2J\033[H" << std::flush;
}
void pause()
{
	std::wcout << L"Нажмите Enter для продолжения...";
	std::wcin.clear(); // Очищаем флаги ошибок
	std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
}

std::wstring NotEmptyString(const std::wstring& prompt)
{
	std::wstring input;
	do {
		std::wcout << prompt << std::endl;
		std::getline(std::wcin, input);
	} while (input.empty());
	return input;
}

wchar_t NotEmptyChar()
{
	std::wstring input;
	std::getline(std::wcin, input); //ввод данных до первого enter
	if (!input.empty()) {
		return input[0]; //считывание первого символа из потока
	}
	else {
		return L'a';
	}
}