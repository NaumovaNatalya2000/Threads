#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>


class Logger
{
private:
	std::wfstream file; //файловый поток
	std::shared_mutex mtx; //мьютекс
	std::streampos readPos; //позиция чтения
	//метод синхронизации записи
	void SyncForWrite();
	//метод синхронизации чтения
	void SyncForRead();
public:
	//конструктор создания
	Logger(const std::wstring& filename);
	//деструктор
	~Logger();
	//запрещаем конструктор копирования и присваивания
	Logger& operator = (const Logger&) = delete;
	Logger(const Logger&) = delete;
	//функция записи
	void WriteLine(const std::wstring& text);
	//функция чтения одной строки
	bool ReadLine(std::wstring& outLine);
	//функция сбросить позицию чтения
	void ReadPosReset();
};

