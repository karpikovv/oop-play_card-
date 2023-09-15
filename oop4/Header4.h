/**************************************************************
*                КАФЕДРА № 302 2 КУРС ПЯВУ  CPP               *
*-------------------------------------------------------------*
* Project Type  : Win32 Console Application                   *
* Project Name  : Взаимодействие классов                      *
* File Name     : Header4.h                                   *
* Language      : C/C++ MS VS ver 2015 and above              *
* Programmer(s) : Карпиков Р.С.                               *
* Created       : 12/04/22                                    *
* Last Revision : 20/03/23                                    *
* Comment(s)    : Взятие карты со стола, перевернутая карта   *
**************************************************************/

/*Иерархия классов
*				           Location
*					          |
					        Point
					          |
					        Figure
               /              |      \       \                \
	      Sign               Mark    Form   Conflict           Card
*      /    |   \             |                |                 |
* K_Sign Q_Sign T_Sign    DiamandRed       Sign_Printer     Marked_Card
*                         DiamandBlue
*                         DiamandGreen
*                         NewSign
*/

using namespace std;
HDC hdc;

#include <Windows.h>
#include <iostream>
#include <conio.h>

class Location {
protected:
	int X;        // Координаты Х и У 
	int Y;        // Открытые для потомков
public:
	int GetX() {  // Геттер Х
		return X;
	}
	int GetY() {  // Геттер У
		return Y;
	}
};
/*---------------------------------------------------------------*/
/*--------------------------Класс точка--------------------------*/
/*---------------------------------------------------------------*/
class Point : public Location {// Класс точка
	// Интерфейс
public:
	virtual void Show() = 0;
	// Отобразить
	virtual void Hide() = 0;
	// Скрыть
	virtual void SetValues(int x, int y) = 0;
	// Установить новые значения
	virtual void MoveTo(int NewX, int NewY) = 0;
	// Переместить на новые координаты
	virtual void Drag(int Nx, int Ny) = 0;
	// Передвинуть с шагом

};//Point
/*---------------------------------------------------------------*/
/*-------------------------Класс фигура--------------------------*/
/*---------------------------------------------------------------*/

class Figure : public Point { // Класс фигура 
protected:
	HPEN PenBlack; // Черная кисть 
	HPEN White1;   // Пустая кисть
	HPEN White2;   // Белая кисть
	HPEN PenRed;   // Красная кисть
	HPEN PenGreen; // Зеленая кисть
	HPEN PenBlue;  // Синяя кисть
	HBRUSH BrBlack;// Зеленая заливка
	HBRUSH White3; // Белая заливка
	HBRUSH Brown;  // Коричневая заливка

public:
	Figure(int InitX, int InitY) {                          // Конструктор класса
		PenBlack = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));    // Черная кисть
		White1 = CreatePen(PS_NULL, 2, RGB(255, 255, 255)); // Прозрачная кисть
		White2 = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));// Белая кисть для фона
		PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));    // Красная кисть
		PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));  // Красная кисть
		PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));   // Красная кисть
		BrBlack = CreateSolidBrush(RGB(0, 120, 10));        // Заливка для карты
		White3 = CreateSolidBrush(RGB(255, 255, 255));      // Заливка фона
		Brown = CreateSolidBrush(RGB(61, 36, 13));          // Стол
		X = InitX;
		Y = InitY;
	}

	void SetValues(int nX, int nY) {    // Установить значения
		X = nX;
		Y = nY;
	}

	void MoveTo(int NewX, int NewY) { // Перемещение фигуры
		Hide();                       // Скрыть 
		X = NewX;
		Y = NewY;                     // Обновить координаты
		Show();                       // Показать
	}

	void Drag(int Nx, int Ny) {       // Буксировка фигуры
		Hide();                       // Скрыть
		X = X + Nx;                   // Изменить координаты
		Y = Y + Ny;
		Show();                       // Показать
	}

};//Figure

/*---------------------------------------------------------------*/
/*---------------------------Класс Масть-------------------------*/
/*---------------------------------------------------------------*/

class Mark : public Figure { //Ромб
protected:
	int Side;                // Сторона ромба
	int Mark_id;

public:
	Mark(int InitX = 20, int InitY = 20, int InitSide = 5) :Figure(InitX, InitY) {
		Side = InitSide;     // Сторона ромба 
	}                        // Конструктор класса

	void SetValues(int NewX, int NewY, int NewSide) {
		X = NewX;         // Установить координаты
		Y = NewY;
		Side = NewSide;   // И размер 
	}

	int GetColorId() {
		return Mark_id - 1;     // Получить цвет
	}
};//Mark

class NewMark : public Mark { //Ромб
public:
	NewMark(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // Сторона ромба 
		Mark_id = 4;

	}
	void Show() {
		SelectObject(hdc, White1);      // Пустая кисть
		LineTo(hdc, X - Side, Y);       // Перемещение в начальную точку

		SelectObject(hdc, PenBlack);    // Красная кисть
		LineTo(hdc, X + Side, Y);

		SelectObject(hdc, White1);       // Пустая кисть
		LineTo(hdc, X, Y - 1.5 * Side);  // Ребра ромба

		SelectObject(hdc, PenBlack);      // Красная кисть
		LineTo(hdc, X, Y + 1.5 * Side);
	}

	void Hide() {
		SelectObject(hdc, White1);      // Пустая кисть
		LineTo(hdc, X - Side, Y);       // Перемещение в начальную точку

		SelectObject(hdc, White2);      // Красная кисть
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y - 1.5 * Side);  // Ребра ромба
		LineTo(hdc, X, Y + 1.5 * Side);
	}
};//DiamandRed

class DiamandRed : public Mark { //Ромб
public:
	DiamandRed(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // Сторона ромба 
		Mark_id = 1;

	}                       
	void Show() {
		SelectObject(hdc, White1);      // Пустая кисть
		LineTo(hdc, X - Side, Y);       // Перемещение в начальную точку
		SelectObject(hdc, PenRed);      // Красная кисть

		LineTo(hdc, X, Y - 1.5 * Side); // Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // Перемещение в начальную точку
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // Кисть цвета фона

		LineTo(hdc, X, Y - 1.5 * Side);// Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandRed

class DiamandBlue : public Mark { //Ромб
public:
	DiamandBlue(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // Сторона ромба 
		Mark_id = 2;

	}
	void Show() {
		SelectObject(hdc, White1);      // Пустая кисть
		LineTo(hdc, X - Side, Y);       // Перемещение в начальную точку
		SelectObject(hdc, PenBlue);      // Красная кисть

		LineTo(hdc, X, Y - 1.5 * Side); // Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // Перемещение в начальную точку
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // Кисть цвета фона

		LineTo(hdc, X, Y - 1.5 * Side);// Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandBlue

class DiamandGreen : public Mark { //Ромб
public:
	DiamandGreen(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // Сторона ромба 
		Mark_id = 3;

	}
	void Show() {
		SelectObject(hdc, White1);      // Пустая кисть
		LineTo(hdc, X - Side, Y);       // Перемещение в начальную точку
		SelectObject(hdc, PenGreen);      // Красная кисть

		LineTo(hdc, X, Y - 1.5 * Side); // Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // Перемещение в начальную точку
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // Кисть цвета фона

		LineTo(hdc, X, Y - 1.5 * Side);// Ребра ромба
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandGreen

/*---------------------------------------------------------------*/
/*---------------------------Класс знак -------------------------*/
/*---------------------------------------------------------------*/
class Sign : public Figure {
protected:
	int size;     //размер
	bool Reverse; //флаг переворот
public:
	Sign(int InitX = 20, int InitY = 20, bool reverse = false) :Figure(InitX, InitY) {
		size = 14;
		Reverse = reverse;
	}                              // Конструктор класса

	void SetValues(int InitX, int InitY, bool reverse = false) {
		X = InitX;                 // Установить координаты
		Y = InitY;                 // И Положение
		Reverse = reverse;
	}
};//Sign

/*---------------------------------------------------------------*/
/*---------------------------Класс знак Т------------------------*/
/*---------------------------------------------------------------*/
class T_sign : public Sign { //Буква 'Т'
public:
	void Show() {                    // Отобразить
		SelectObject(hdc, White1);   // Пустая кисть
		LineTo(hdc, X, Y - size);    // Переместиться в начаную точу
		SelectObject(hdc, PenBlack); // Черная кисть
		LineTo(hdc, X, Y + size);    // Ножка 'Т' 

		SelectObject(hdc, White1);   // Пустая кисть
		if (Reverse) {               // Шляпка если перевернутая
			LineTo(hdc, X - size, Y + size);
			SelectObject(hdc, PenBlack);
			LineTo(hdc, X + size, Y + size);
		}
		else {                       // Шляпка если прямая
			LineTo(hdc, X - size, Y - size);
			SelectObject(hdc, PenBlack);
			LineTo(hdc, X + size, Y - size);
		}
	}

	void Hide() {                    // Скрыть
		SelectObject(hdc, White2);   // Переместиться в начаную точу
		LineTo(hdc, X, Y - size);    // Ножка
		LineTo(hdc, X, Y + size);
		if (Reverse) {               // Шляпка
			LineTo(hdc, X - size, Y + size);
			LineTo(hdc, X + size, Y + size);
		}
		else {
			LineTo(hdc, X - size, Y - size);
			LineTo(hdc, X + size, Y - size);
		}
	}

};// T_Sign
/*---------------------------------------------------------------*/
/*---------------------------Класс знак К------------------------*/
/*---------------------------------------------------------------*/

class K_sign : public Sign { //Буква К
public:
	void Show() {                    // Отобразить
		SelectObject(hdc, White1);   // Пустая кисть

		if (Reverse) {               // Перевернутая
			LineTo(hdc, X - size / 2, Y + size);// Начальная точка
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X + size / 2, Y);       // Верхняя диагональ
			LineTo(hdc, X - size / 2, Y - size);// Нижняя диагональ
			SelectObject(hdc, White1);          // Пустая кисть
			LineTo(hdc, X + size / 2, Y + size);// Начало вертикальной прямой
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X + size / 2, Y - size);// Конец вертикальной прямой
		}
		else {                                  // Без поворота
			LineTo(hdc, X + size / 2, Y - size);// Начальная точка
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X - size / 2, Y);       // Верхняя диагональ
			LineTo(hdc, X + size / 2, Y + size);// Нижняя диагональ
			SelectObject(hdc, White1);          // Пустая кисть
			LineTo(hdc, X - size / 2, Y - size);// Начало вертикальной прямой
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X - size / 2, Y + size);// Конец вертикальной прямой
		}
	}

	void Hide() {                               //Скрыть
		SelectObject(hdc, White2);              // Аналогично с отображением
		if (Reverse) {
			LineTo(hdc, X - size / 2, Y + size);
			LineTo(hdc, X + size / 2, Y);
			LineTo(hdc, X - size / 2, Y - size);
			LineTo(hdc, X + size / 2, Y + size);
			LineTo(hdc, X + size / 2, Y - size);
		}
		else {
			LineTo(hdc, X + size / 2, Y - size);
			LineTo(hdc, X - size / 2, Y);
			LineTo(hdc, X + size / 2, Y + size);
			LineTo(hdc, X - size / 2, Y - size);
			LineTo(hdc, X - size / 2, Y + size);
		}
	}
};// K_Sign

/*---------------------------------------------------------------*/
/*---------------------------Класс знак Q------------------------*/
/*---------------------------------------------------------------*/
class Q_sign : public Sign { //Буква Q
public:
	void Show() {            // Отобразить
		SelectObject(hdc, White1);  // Пустая кисть
		LineTo(hdc, X, Y);          // Переместиться в начальную точку

		SelectObject(hdc, PenBlack);// Черная кисть
		if (Reverse) {              // Если перевернута
			Ellipse(hdc, X - size, Y - size, X + size, Y + 1.5 * size);
			// Овал и черта
			LineTo(hdc, X + size, Y - size);
		}
		else {                      // Если без поворота
			Ellipse(hdc, X - size, Y - 1.5 * size, X + size, Y + size);
			// Овал и черта
			LineTo(hdc, X + size, Y + size);
		}
	}
	void Hide() {                   //Скрыть
		SelectObject(hdc, White1);  // Аналогично с отображением
		LineTo(hdc, X, Y);
		SelectObject(hdc, White3);
		SelectObject(hdc, White2);
		if (Reverse) {
			Ellipse(hdc, X - size, Y - size, X + size, Y + 1.5 * size);
			LineTo(hdc, X + size, Y - size);
		}
		else {
			Ellipse(hdc, X - size, Y - 1.5 * size, X + size, Y + size);
			LineTo(hdc, X + size, Y + size);
		}
	}
};// Q_Sign

class J_sign : public Sign { //Буква К
public:
	void Show() {                    // Отобразить
		SelectObject(hdc, White1);   // Пустая кисть

		if (Reverse) {               // Перевернутая
			LineTo(hdc, X + size / 2, Y);// Начальная точка
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X - size / 2, Y - size);       // Верхняя диагональ
			LineTo(hdc, X - size / 2, Y + size);// Нижняя диагональ
			LineTo(hdc, X, Y + size);// Начало вертикальной прямой
		}
		else {                                  // Без поворота
			LineTo(hdc, X - size/2, Y);// Начальная точка
			SelectObject(hdc, PenBlack);        // Черная кисть
			LineTo(hdc, X + size/2, Y + size);       // Верхняя диагональ
			LineTo(hdc, X + size/2, Y - size);// Нижняя диагональ
			LineTo(hdc, X, Y - size);// Начало вертикальной прямой
		}
	}

	void Hide() {                               //Скрыть
		SelectObject(hdc, White2);              // Аналогично с отображением
		if (Reverse) {
			LineTo(hdc, X - size / 2, Y + size);
			LineTo(hdc, X + size / 2, Y);
			LineTo(hdc, X - size / 2, Y - size);
			LineTo(hdc, X + size / 2, Y + size);
			LineTo(hdc, X + size / 2, Y - size);
		}
		else {
			LineTo(hdc, X + size / 2, Y - size);
			LineTo(hdc, X - size / 2, Y);
			LineTo(hdc, X + size / 2, Y + size);
			LineTo(hdc, X - size / 2, Y - size);
			LineTo(hdc, X - size / 2, Y + size);
		}
	}
};// K_Sign


/*---------------------------------------------------------------*/
/*----------------------Класс форма карты------------------------*/
/*---------------------------------------------------------------*/

class Form :public Figure {        // Форма карты
protected:
	int Size;                      // Размер
public:
	Form(int InitX = 20, int InitY = 20, int size = 100) :Figure(InitX, InitY) {
		Size = size;               // Размер
	}// Конструктор класса

	void Show() { // Отобразить
		SelectObject(hdc, White3);                  // Фон
		SelectObject(hdc, White1);                  // Пустая кисть
		LineTo(hdc, X - Size, Y - 1.5 * Size + 10); // Начало
		Rectangle(hdc, X - Size, Y - 1.5 * Size, X + Size, Y + 1.5 * Size);
		// Заливка фона
		SelectObject(hdc, PenBlack);                // Черная кисть
		// Стороны карты, с закругленными краями
		LineTo(hdc, X - Size, Y + 1.5 * Size - 10);
		ArcTo(hdc, X - Size, Y + 1.5 * Size - 20, X - Size + 20, Y + 1.5 * Size, X - Size, Y + 1.5 * Size - 10, X - Size + 10, Y + 1.5 * Size);
		LineTo(hdc, X + Size - 10, Y + 1.5 * Size);
		ArcTo(hdc, X + Size - 20, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 20, X + Size - 10, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 10);
		LineTo(hdc, X + Size, Y - 1.5 * Size + 10);
		ArcTo(hdc, X + Size, Y - 1.5 * Size + 20, X + Size - 20, Y - 1.5 * Size, X + Size, Y - 1.5 * Size + 10, X + Size - 10, Y - 1.5 * Size);
		LineTo(hdc, X - Size + 10, Y - 1.5 * Size);
		ArcTo(hdc, X - Size + 20, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 20, X - Size + 10, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 10);
	}

	void Hide() { // Скрыть
		SelectObject(hdc, White1);   // Аналогично с отображением
		LineTo(hdc, X - Size, Y - 1.5 * Size + 10);
		SelectObject(hdc, White2);
		LineTo(hdc, X - Size, Y + 1.5 * Size - 10);
		ArcTo(hdc, X - Size, Y + 1.5 * Size - 20, X - Size + 20, Y + 1.5 * Size, X - Size, Y + 1.5 * Size - 10, X - Size + 10, Y + 1.5 * Size);
		LineTo(hdc, X + Size - 10, Y + 1.5 * Size);
		ArcTo(hdc, X + Size - 20, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 20, X + Size - 10, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 10);
		LineTo(hdc, X + Size, Y - 1.5 * Size + 10);
		ArcTo(hdc, X + Size, Y - 1.5 * Size + 20, X + Size - 20, Y - 1.5 * Size, X + Size, Y - 1.5 * Size + 10, X + Size - 10, Y - 1.5 * Size);
		LineTo(hdc, X - Size + 10, Y - 1.5 * Size);
		ArcTo(hdc, X - Size + 20, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 20, X - Size + 10, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 10);
	}

	void SetValues(int NewX = 0, int NewY = 0, int NewSize = 100) {
		X = NewX;  // Установить значения координат
		Y = NewY;  // И размер
		Size = NewSize;
	}
};// Form
/*---------------------------------------------------------------*/
/*----------------- Конфликтующий класс -------------------------*/
/*---------------------------------------------------------------*/

class Conflict : public Figure {
	//Абстрактный класс конфликтующих объектов
public:
	Conflict(int InitX, int InitY) : Figure(InitX, InitY) {
		// Конструктор наследуется от Figure
	}

	virtual bool IsContact(int x, int y) = 0;
	// Чисто виртуальная функция проверки взаимодействия

};//Conflict
/*---------------------------------------------------------------*/
/*----------------------- Класс Принтер -------------------------*/
/*---------------------------------------------------------------*/

class SignPrinter : public Conflict { // Принтер
private:
	int mark_id;       // Символ для печати
	int Size;          // Размер принтера
	Sign* Mark;        // Указатель на Символ

public:
	SignPrinter(int InitX = 0, int InitY = 0, int sign_id = 1) :Conflict(InitX, InitY) {
		mark_id = sign_id;     // Символ для печати
		Size = 30;             // Размер принтера
		if (mark_id == 1) {    // Дама
			Mark = new Q_sign; // Указатель на даму
		}
		if (mark_id == 2) {    // Король
			Mark = new K_sign; // Указать на короля
		}
		if (mark_id == 3) {    // Туз
			Mark = new T_sign; // Указать на туза
		}
		Mark->SetValues(X, Y); // Установка значений 
	}// Конструктор класса

	bool IsContact(int x, int y) {  // Проверка прикосновения
		if (x > X - 20 and x < X + 20 and y > Y - 180 and y < Y - 160)
			// Совпадение координат с погрешностью
			return true;            // Совпадают
		else
			return false;           // Не совпадают
	}
	void Show() {                   // Отобразить
		SelectObject(hdc, BrBlack); // Фон (Зеленый)
		SelectObject(hdc, PenBlack);// Обводка (Черный)
		Rectangle(hdc, X - Size, Y - Size, X + Size, Y + Size);
		// Форма принтера
		Mark->Show();               // Знак принтера
	}
	void Hide() {                   // Скрыть
		SelectObject(hdc, White3);  // Аналогично с отображением
		Rectangle(hdc, X - Size, Y - Size, X + Size, Y + Size);
		Mark->Hide();
	}
	int GetSignId() {
		return mark_id - 1;
	}
};
/*---------------------------------------------------------------*/
/*---------------Класс неопределенная карта----------------------*/
/*---------------------------------------------------------------*/

class Card : public Figure { // Игральная карта
protected:
	int Size;      // Размер
	Mark* Mark1;    // Масть - Ромб(верх)
	Mark* Mark2;    // Масть - Ромб(низ)
	Mark* MarkMain; // Масть - Ромб(середина)
	Form form;     // Форма карты

public:
	bool is_reverse = false;   // Стартовое значение
	Card(int InitX = 0, int InitY = 0, int color_id = 2) :Figure(InitX, InitY) {
		Size = 100;                   // Размер
		if (color_id == 1) {           // Дама
			Mark1    = new DiamandRed; // Указатели на дам
			Mark2    = new DiamandRed;
			MarkMain = new DiamandRed;
		}
		if (color_id == 2) {           // Дама
			Mark1    = new DiamandBlue; // Указатели на дам
			Mark2    = new DiamandBlue;
			MarkMain = new DiamandBlue;
		}
		if (color_id == 3) {           // Дама
			Mark1    = new DiamandGreen; // Указатели на дам
			Mark2    = new DiamandGreen;
			MarkMain = new DiamandGreen;
		}
		if (color_id == 4) {           // Дама
			Mark1    = new NewMark; // Указатели на дам
			Mark2    = new NewMark;
			MarkMain = new NewMark;
		}
		SetValues();                  // Связать элеметы карты
	}

	void SetValues() {// Связать элеметы карты
		Mark1->SetValues(X - 3 * Size / 4, Y - 5 * Size / 6, Size / 8);
		// Верхний ромб
		Mark2->SetValues(X + 3 * Size / 4, Y + 5 * Size / 6, Size / 8);
		// Нижний ромб
		MarkMain->SetValues(X, Y, Size / 3);
		// Центральный ромб
		form.SetValues(X, Y, Size);
		// Форма карты
	}

	void Show() {       // Отобразить
		SetValues();    // Обновить привязку фигур
		form.Show();    // Отобразить фому
		Mark1->Show();   // Отобразить 1 ромб
		Mark2->Show();   // Отобразить 2 ромб
		MarkMain->Show();// Отобразить Главный ромб
	}

	void Hide() {       // Скрыть
		form.Hide();    // Аналогично с отображением  
		Mark1->Hide();
		Mark2->Hide();
		MarkMain->Hide();
	}

	int GetColorId() {
		return MarkMain->GetColorId();  // Получить цвет 
	}

};//Card
/*---------------------------------------------------------------*/
/*-----------------Класс определенная карта----------------------*/
/*---------------------------------------------------------------*/

class Marked_Card : public Card { // Игральная карта
protected:
	Sign* Sign1;                  // Указатели на знак карты
	Sign* Sign2;

public:
	Marked_Card(int InitX, int InitY, int color_id, int s = 1) :Card(InitX, InitY, color_id) {
		Size = 100;
		if (s == 1) {           // Дама
			Sign1 = new Q_sign; // Указатели на дам
			Sign2 = new Q_sign;
		}
		if (s == 2) {           // Король
			Sign1 = new K_sign; // Указатели на королей
			Sign2 = new K_sign;
		}
		if (s == 3) {           // Туз
			Sign1 = new T_sign; // Указатели на тузов
			Sign2 = new T_sign;
		}
		if (s == 4) {           // Туз
			Sign1 = new J_sign; // Указатели на тузов
			Sign2 = new J_sign;
		}
		//Mark1.SetColorId(color_id);   // Установить цвет 
		//Mark2.SetColorId(color_id);   // Установить цвет 
		//MarkMain.SetColorId(color_id);// Установить цвет 
		SetValues();                  // Связать элеметы карты
	}

	void SetValues() {// Связать элеметы карты
		Card::SetValues();      // Связать элементы предка
		Sign1->SetValues(X - 3 * Size / 4, Y - 15 * Size / 12, false);
		// Связать знаки
		Sign2->SetValues(X + 3 * Size / 4, Y + 15 * Size / 12, true);
	}

	void Show() { // Отобразить
		SelectObject(hdc, White3); // Цвет карты (Белый)
		SetValues();               // Обновить привязку фигур
		Card::Show();          // Отобразить карту
		Sign1->Show();         // Отобразить знаки
		Sign2->Show();

	}

	void Hide() { //Скрыть
		Card::Hide();
		Sign1->Hide();
		Sign2->Hide();
		
	}
};//Marked_Card

