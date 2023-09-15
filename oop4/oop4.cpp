
/**************************************************************
*                КАФЕДРА № 302 2 КУРС ПЯВУ  CPP               *
*-------------------------------------------------------------*
* Project Type  : Win32 Console Application                   *
* Project Name  : Diamand Cards                               *
* File Name     : oop4.cpp                                    *
* Language      : C/C++ MS VS ver 2015 and above              *
* Programmer(s) : Карпиков Р.С.                               *
* Created       : 17/05/22                                    *
* Last Revision : 13/12/22                                    *
**************************************************************/
#include <Windows.h>
#include "Header4.h"  // Объявление классов

#define START_X_CARD 400
#define START_Y_CARD 370
#define START_PRINT_X1 200
#define START_PRINT_X2 400
#define START_PRINT_X3 600
#define START_PRINT_Y 600
#define TABLE_HIGHT 200
#define COLOR_COUNT 4
#define MARK_COUNT 3
#define SPEED 6

// Макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*------------------------------------------------------------*/
/*------------------Основная программа------------------------*/
/*------------------------------------------------------------*/

int main() {

	HWND hwnd = GetConsoleWindow(); // Получаем дескриптор консольного окна
	hdc = GetWindowDC(hwnd);        // Получаем контекст устройства консольного окна

	Card* card;                     // Указатель на карту
	Marked_Card* Mcard;             // Указатель на помеченую карту

	card = new Card(START_X_CARD, START_Y_CARD, 1);   // Создаем стартовую карту
	card->Show();                   // Отображаем стартовую карту

	Card* matrix[COLOR_COUNT][MARK_COUNT] = {          // Матрица значений
		{new Marked_Card(START_X_CARD, START_Y_CARD, 1, 1), new Marked_Card(START_X_CARD, START_Y_CARD, 1, 2), new Marked_Card(START_X_CARD, START_Y_CARD, 1, 3)},
		{new Marked_Card(START_X_CARD, START_Y_CARD, 2, 1), new Marked_Card(START_X_CARD, START_Y_CARD, 2, 2), new Marked_Card(START_X_CARD, START_Y_CARD, 2, 3)},
		{new Marked_Card(START_X_CARD, START_Y_CARD, 3, 1), new Marked_Card(START_X_CARD, START_Y_CARD, 3, 2), new Marked_Card(START_X_CARD, START_Y_CARD, 3, 3)},
		{new Marked_Card(START_X_CARD, START_Y_CARD, 4, 1), new Marked_Card(START_X_CARD, START_Y_CARD, 4, 2), new Marked_Card(START_X_CARD, START_Y_CARD, 4, 3)},
	};
	

	SignPrinter Q_printer(START_PRINT_X1, START_PRINT_Y, 1); // Создаем принтеры
	SignPrinter K_printer(START_PRINT_X2, START_PRINT_Y, 2);
	SignPrinter T_printer(START_PRINT_X3, START_PRINT_Y, 3);

	Q_printer.Show();                     // Показываем принтеры
	K_printer.Show();
	T_printer.Show();

	Card* pBase = card;                   // Задаем рабочий указатель

	pBase = new Marked_Card(START_X_CARD, START_Y_CARD, 1, 4);

	while (1) {
		if (KEY_DOWN(87)) {     // Клавиша 'W'
			pBase->Drag(0, -SPEED); // Перемещение вверх
		}
		if (KEY_DOWN(83)) {     // Клавиша 'S'
			pBase->Drag(0, SPEED);  // Перемещение вниз
		}
		if (KEY_DOWN(65)) {     // Клавиша 'A'
			pBase->Drag(-SPEED, 0); // Перемещение вправо
		}
		if (KEY_DOWN(68)) {     // Клавиша 'D'
			pBase->Drag(SPEED, 0);  // Перемещение влево
		}

		if (KEY_DOWN(67)) {     // Клавиша 'С'
			pBase->Hide();
			pBase = new Card(START_X_CARD, START_Y_CARD, 1);
			pBase->Show();      // Красная карта
		}

		if (KEY_DOWN(86)) {     // Клавиша 'V'
			pBase->Hide();
			pBase = new Card(START_X_CARD, START_Y_CARD, 4);
			pBase->Show();      // Красная карта
		}

		if (KEY_DOWN(90)) {     // Клавиша 'Z'
			pBase->Hide();
			pBase = new Card(START_X_CARD, START_Y_CARD, 2);
			pBase->Show();      // Зеленая карта
		}

		if (KEY_DOWN(88)) {     // Клавиша 'X'
			pBase->Hide();
			pBase = new Card(START_X_CARD, START_Y_CARD, 3);
			pBase->Show();		// Синяя карта
		}

		if (Q_printer.IsContact(pBase->GetX(), pBase->GetY())) {
			// При контакте с Q принтером:
			pBase->MoveTo(START_X_CARD, START_Y_CARD);
			pBase->Hide();                          // Скрыть карту
			pBase = matrix[pBase->GetColorId()][Q_printer.GetSignId()]; // Установить новый указатель
		}
		if (K_printer.IsContact(pBase->GetX(), pBase->GetY())) {
			// При контакте с K принтером:
			pBase->MoveTo(START_X_CARD, START_Y_CARD);
			pBase->Hide();                          // Скрыть карту
			pBase = matrix[pBase->GetColorId()][K_printer.GetSignId()]; // Установить новый указатель
		}
		if (T_printer.IsContact(pBase->GetX(), pBase->GetY())) {
			// При контакте с T принтером:
			pBase->MoveTo(START_X_CARD, START_Y_CARD);
			pBase->Hide();                          // Скрыть карту
			pBase = matrix[pBase->GetColorId()][T_printer.GetSignId()]; // Установить новый указатель
		}
		
		if (KEY_DOWN(49))            // При нажатии '1'
			break;                   // Выход из программы

		Q_printer.Show();            
		K_printer.Show();            // Показать принтеры
		T_printer.Show();
		pBase->Show();               // Показать рабочую карту
		Sleep(60);                   // Пауза
	}
} // main