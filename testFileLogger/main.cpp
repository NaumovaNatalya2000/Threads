#include <iostream>
#include <thread>
#include <vector>
#include "Logger.h"
#include "FunctionsSystem.h"


int main() {
	setlocale(LC_ALL, "");
	std::wstring filename = L"log.txt";
	Logger logger(filename);
	std::vector<std::thread> threads; //вектор потоков
	std::wstring message;

	wchar_t menu{ L'a' };
	while (menu != 'q' && menu != 'Q') {
		std::wcout
			<< L"[Основное меню] === Программа для тестирования потоков ===\n"
			<< L"[1] - Ввести сообщение\n"
			<< L"[2] - Вывести строку из файла логов (строки выводятся по очереди)\n"
			<< L"[3] - Сбросить позицию чтения\n"
			<< L"[q] - Выход из программы"
			<< std::endl;
		menu = NotEmptyChar();
		switch (menu) {
		case L'1':
		{
			message = NotEmptyString(L"Введите сообщение:");
			threads.push_back(std::thread(
				[&logger, message]() {
				logger.WriteLine(message);
				}));
			break;
		}
		case L'2':
		{
			std::thread t(
				[&logger]() {
					std::wstring line;
					if (logger.ReadLine(line)) {
						std::wcout << L"[Чтение] " << line << std::endl;
					}
					else {
						std::wcout << L"Вы дошли до конца файла! Строк больше нет" << std::endl;
					}
				});
			if (t.joinable()) {
				t.join();
			}
			break;
		}
		case L'3':
		{
			logger.ReadPosReset();
			break;
		}
		default: break;
		}
		pause();
		clearScreen();
	}

	//ждем выполнения всех потоков
	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
}