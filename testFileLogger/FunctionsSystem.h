#pragma once
#include<iostream>
#include <string>

//функция очистки экрана
void clearScreen();
	//функция паузы
void pause();

//функция ввода строки с проверкой на пустоту
std::wstring NotEmptyString(const std::wstring& prompt);
//функция проверки потока ввода на пустоту
wchar_t NotEmptyChar();

