#include "Logger.h"

Logger::Logger(const std::wstring& filename){
	//открываем поток для чтения и записи, записи будут идти в конец файла
	file.open( filename, std::ios::in | std::ios::out | std::ios::app );
	//если файла нет - создаем его
	if (!file.is_open()) {
		//создаем файл если отсутствует
		std::wofstream temp(filename, std::ios::out);
		temp.close();
		file.open(filename, std::ios::in | std::ios::out | std::ios::app);
	}
	readPos = 0;
}

Logger::~Logger()
{
	//блокируем мьютекс на время удаления
	std::unique_lock<std::shared_mutex> lock(mtx);
	if (file.is_open()) {
		file.close();
	}
}

void Logger::SyncForWrite()
{
	//очищаем флаги ошибок и eof
	file.clear();
	//писать всегда в конец
	file.seekp(0, std::ios::end);
}

void Logger::SyncForRead()
{
	//очищаем флаги ошибок и eof
	file.clear();
	//устанавливаем позицию чтения
	file.seekg(readPos);
}

void Logger::WriteLine(const std::wstring& text) {
	std::unique_lock<std::shared_mutex> lock(mtx);
	SyncForWrite();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	file << text << L"\n";
	file.flush();
}

bool Logger::ReadLine(std::wstring& outLine) {
	std::shared_lock<std::shared_mutex> lock(mtx); // разделяемая блокировка
	SyncForRead();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	if (std::getline(file, outLine)) {
		readPos = file.tellg(); // обновляем позицию
		return true;
	}
	return false; // новых строк нет
}

void Logger::ReadPosReset()
{
	readPos = 0;
}
