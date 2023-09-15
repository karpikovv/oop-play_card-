/**************************************************************
*                ������� � 302 2 ���� ����  CPP               *
*-------------------------------------------------------------*
* Project Type  : Win32 Console Application                   *
* Project Name  : �������������� �������                      *
* File Name     : Header4.h                                   *
* Language      : C/C++ MS VS ver 2015 and above              *
* Programmer(s) : �������� �.�.                               *
* Created       : 12/04/22                                    *
* Last Revision : 20/03/23                                    *
* Comment(s)    : ������ ����� �� �����, ������������ �����   *
**************************************************************/

/*�������� �������
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
	int X;        // ���������� � � � 
	int Y;        // �������� ��� ��������
public:
	int GetX() {  // ������ �
		return X;
	}
	int GetY() {  // ������ �
		return Y;
	}
};
/*---------------------------------------------------------------*/
/*--------------------------����� �����--------------------------*/
/*---------------------------------------------------------------*/
class Point : public Location {// ����� �����
	// ���������
public:
	virtual void Show() = 0;
	// ����������
	virtual void Hide() = 0;
	// ������
	virtual void SetValues(int x, int y) = 0;
	// ���������� ����� ��������
	virtual void MoveTo(int NewX, int NewY) = 0;
	// ����������� �� ����� ����������
	virtual void Drag(int Nx, int Ny) = 0;
	// ����������� � �����

};//Point
/*---------------------------------------------------------------*/
/*-------------------------����� ������--------------------------*/
/*---------------------------------------------------------------*/

class Figure : public Point { // ����� ������ 
protected:
	HPEN PenBlack; // ������ ����� 
	HPEN White1;   // ������ �����
	HPEN White2;   // ����� �����
	HPEN PenRed;   // ������� �����
	HPEN PenGreen; // ������� �����
	HPEN PenBlue;  // ����� �����
	HBRUSH BrBlack;// ������� �������
	HBRUSH White3; // ����� �������
	HBRUSH Brown;  // ���������� �������

public:
	Figure(int InitX, int InitY) {                          // ����������� ������
		PenBlack = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));    // ������ �����
		White1 = CreatePen(PS_NULL, 2, RGB(255, 255, 255)); // ���������� �����
		White2 = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));// ����� ����� ��� ����
		PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));    // ������� �����
		PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));  // ������� �����
		PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));   // ������� �����
		BrBlack = CreateSolidBrush(RGB(0, 120, 10));        // ������� ��� �����
		White3 = CreateSolidBrush(RGB(255, 255, 255));      // ������� ����
		Brown = CreateSolidBrush(RGB(61, 36, 13));          // ����
		X = InitX;
		Y = InitY;
	}

	void SetValues(int nX, int nY) {    // ���������� ��������
		X = nX;
		Y = nY;
	}

	void MoveTo(int NewX, int NewY) { // ����������� ������
		Hide();                       // ������ 
		X = NewX;
		Y = NewY;                     // �������� ����������
		Show();                       // ��������
	}

	void Drag(int Nx, int Ny) {       // ���������� ������
		Hide();                       // ������
		X = X + Nx;                   // �������� ����������
		Y = Y + Ny;
		Show();                       // ��������
	}

};//Figure

/*---------------------------------------------------------------*/
/*---------------------------����� �����-------------------------*/
/*---------------------------------------------------------------*/

class Mark : public Figure { //����
protected:
	int Side;                // ������� �����
	int Mark_id;

public:
	Mark(int InitX = 20, int InitY = 20, int InitSide = 5) :Figure(InitX, InitY) {
		Side = InitSide;     // ������� ����� 
	}                        // ����������� ������

	void SetValues(int NewX, int NewY, int NewSide) {
		X = NewX;         // ���������� ����������
		Y = NewY;
		Side = NewSide;   // � ������ 
	}

	int GetColorId() {
		return Mark_id - 1;     // �������� ����
	}
};//Mark

class NewMark : public Mark { //����
public:
	NewMark(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // ������� ����� 
		Mark_id = 4;

	}
	void Show() {
		SelectObject(hdc, White1);      // ������ �����
		LineTo(hdc, X - Side, Y);       // ����������� � ��������� �����

		SelectObject(hdc, PenBlack);    // ������� �����
		LineTo(hdc, X + Side, Y);

		SelectObject(hdc, White1);       // ������ �����
		LineTo(hdc, X, Y - 1.5 * Side);  // ����� �����

		SelectObject(hdc, PenBlack);      // ������� �����
		LineTo(hdc, X, Y + 1.5 * Side);
	}

	void Hide() {
		SelectObject(hdc, White1);      // ������ �����
		LineTo(hdc, X - Side, Y);       // ����������� � ��������� �����

		SelectObject(hdc, White2);      // ������� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y - 1.5 * Side);  // ����� �����
		LineTo(hdc, X, Y + 1.5 * Side);
	}
};//DiamandRed

class DiamandRed : public Mark { //����
public:
	DiamandRed(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // ������� ����� 
		Mark_id = 1;

	}                       
	void Show() {
		SelectObject(hdc, White1);      // ������ �����
		LineTo(hdc, X - Side, Y);       // ����������� � ��������� �����
		SelectObject(hdc, PenRed);      // ������� �����

		LineTo(hdc, X, Y - 1.5 * Side); // ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // ����������� � ��������� �����
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // ����� ����� ����

		LineTo(hdc, X, Y - 1.5 * Side);// ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandRed

class DiamandBlue : public Mark { //����
public:
	DiamandBlue(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // ������� ����� 
		Mark_id = 2;

	}
	void Show() {
		SelectObject(hdc, White1);      // ������ �����
		LineTo(hdc, X - Side, Y);       // ����������� � ��������� �����
		SelectObject(hdc, PenBlue);      // ������� �����

		LineTo(hdc, X, Y - 1.5 * Side); // ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // ����������� � ��������� �����
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // ����� ����� ����

		LineTo(hdc, X, Y - 1.5 * Side);// ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandBlue

class DiamandGreen : public Mark { //����
public:
	DiamandGreen(int InitX = 20, int InitY = 20, int InitSide = 5) :Mark(InitX, InitY, InitSide) {
		Side = InitSide;     // ������� ����� 
		Mark_id = 3;

	}
	void Show() {
		SelectObject(hdc, White1);      // ������ �����
		LineTo(hdc, X - Side, Y);       // ����������� � ��������� �����
		SelectObject(hdc, PenGreen);      // ������� �����

		LineTo(hdc, X, Y - 1.5 * Side); // ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}

	void Hide() {
		SelectObject(hdc, White1);     // ����������� � ��������� �����
		LineTo(hdc, X - Side, Y);
		SelectObject(hdc, White2);     // ����� ����� ����

		LineTo(hdc, X, Y - 1.5 * Side);// ����� �����
		LineTo(hdc, X + Side, Y);
		LineTo(hdc, X, Y + 1.5 * Side);
		LineTo(hdc, X - Side, Y);
	}
};//DiamandGreen

/*---------------------------------------------------------------*/
/*---------------------------����� ���� -------------------------*/
/*---------------------------------------------------------------*/
class Sign : public Figure {
protected:
	int size;     //������
	bool Reverse; //���� ���������
public:
	Sign(int InitX = 20, int InitY = 20, bool reverse = false) :Figure(InitX, InitY) {
		size = 14;
		Reverse = reverse;
	}                              // ����������� ������

	void SetValues(int InitX, int InitY, bool reverse = false) {
		X = InitX;                 // ���������� ����������
		Y = InitY;                 // � ���������
		Reverse = reverse;
	}
};//Sign

/*---------------------------------------------------------------*/
/*---------------------------����� ���� �------------------------*/
/*---------------------------------------------------------------*/
class T_sign : public Sign { //����� '�'
public:
	void Show() {                    // ����������
		SelectObject(hdc, White1);   // ������ �����
		LineTo(hdc, X, Y - size);    // ������������� � ������� ����
		SelectObject(hdc, PenBlack); // ������ �����
		LineTo(hdc, X, Y + size);    // ����� '�' 

		SelectObject(hdc, White1);   // ������ �����
		if (Reverse) {               // ������ ���� ������������
			LineTo(hdc, X - size, Y + size);
			SelectObject(hdc, PenBlack);
			LineTo(hdc, X + size, Y + size);
		}
		else {                       // ������ ���� ������
			LineTo(hdc, X - size, Y - size);
			SelectObject(hdc, PenBlack);
			LineTo(hdc, X + size, Y - size);
		}
	}

	void Hide() {                    // ������
		SelectObject(hdc, White2);   // ������������� � ������� ����
		LineTo(hdc, X, Y - size);    // �����
		LineTo(hdc, X, Y + size);
		if (Reverse) {               // ������
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
/*---------------------------����� ���� �------------------------*/
/*---------------------------------------------------------------*/

class K_sign : public Sign { //����� �
public:
	void Show() {                    // ����������
		SelectObject(hdc, White1);   // ������ �����

		if (Reverse) {               // ������������
			LineTo(hdc, X - size / 2, Y + size);// ��������� �����
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X + size / 2, Y);       // ������� ���������
			LineTo(hdc, X - size / 2, Y - size);// ������ ���������
			SelectObject(hdc, White1);          // ������ �����
			LineTo(hdc, X + size / 2, Y + size);// ������ ������������ ������
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X + size / 2, Y - size);// ����� ������������ ������
		}
		else {                                  // ��� ��������
			LineTo(hdc, X + size / 2, Y - size);// ��������� �����
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X - size / 2, Y);       // ������� ���������
			LineTo(hdc, X + size / 2, Y + size);// ������ ���������
			SelectObject(hdc, White1);          // ������ �����
			LineTo(hdc, X - size / 2, Y - size);// ������ ������������ ������
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X - size / 2, Y + size);// ����� ������������ ������
		}
	}

	void Hide() {                               //������
		SelectObject(hdc, White2);              // ���������� � ������������
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
/*---------------------------����� ���� Q------------------------*/
/*---------------------------------------------------------------*/
class Q_sign : public Sign { //����� Q
public:
	void Show() {            // ����������
		SelectObject(hdc, White1);  // ������ �����
		LineTo(hdc, X, Y);          // ������������� � ��������� �����

		SelectObject(hdc, PenBlack);// ������ �����
		if (Reverse) {              // ���� �����������
			Ellipse(hdc, X - size, Y - size, X + size, Y + 1.5 * size);
			// ���� � �����
			LineTo(hdc, X + size, Y - size);
		}
		else {                      // ���� ��� ��������
			Ellipse(hdc, X - size, Y - 1.5 * size, X + size, Y + size);
			// ���� � �����
			LineTo(hdc, X + size, Y + size);
		}
	}
	void Hide() {                   //������
		SelectObject(hdc, White1);  // ���������� � ������������
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

class J_sign : public Sign { //����� �
public:
	void Show() {                    // ����������
		SelectObject(hdc, White1);   // ������ �����

		if (Reverse) {               // ������������
			LineTo(hdc, X + size / 2, Y);// ��������� �����
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X - size / 2, Y - size);       // ������� ���������
			LineTo(hdc, X - size / 2, Y + size);// ������ ���������
			LineTo(hdc, X, Y + size);// ������ ������������ ������
		}
		else {                                  // ��� ��������
			LineTo(hdc, X - size/2, Y);// ��������� �����
			SelectObject(hdc, PenBlack);        // ������ �����
			LineTo(hdc, X + size/2, Y + size);       // ������� ���������
			LineTo(hdc, X + size/2, Y - size);// ������ ���������
			LineTo(hdc, X, Y - size);// ������ ������������ ������
		}
	}

	void Hide() {                               //������
		SelectObject(hdc, White2);              // ���������� � ������������
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
/*----------------------����� ����� �����------------------------*/
/*---------------------------------------------------------------*/

class Form :public Figure {        // ����� �����
protected:
	int Size;                      // ������
public:
	Form(int InitX = 20, int InitY = 20, int size = 100) :Figure(InitX, InitY) {
		Size = size;               // ������
	}// ����������� ������

	void Show() { // ����������
		SelectObject(hdc, White3);                  // ���
		SelectObject(hdc, White1);                  // ������ �����
		LineTo(hdc, X - Size, Y - 1.5 * Size + 10); // ������
		Rectangle(hdc, X - Size, Y - 1.5 * Size, X + Size, Y + 1.5 * Size);
		// ������� ����
		SelectObject(hdc, PenBlack);                // ������ �����
		// ������� �����, � ������������� ������
		LineTo(hdc, X - Size, Y + 1.5 * Size - 10);
		ArcTo(hdc, X - Size, Y + 1.5 * Size - 20, X - Size + 20, Y + 1.5 * Size, X - Size, Y + 1.5 * Size - 10, X - Size + 10, Y + 1.5 * Size);
		LineTo(hdc, X + Size - 10, Y + 1.5 * Size);
		ArcTo(hdc, X + Size - 20, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 20, X + Size - 10, Y + 1.5 * Size, X + Size, Y + 1.5 * Size - 10);
		LineTo(hdc, X + Size, Y - 1.5 * Size + 10);
		ArcTo(hdc, X + Size, Y - 1.5 * Size + 20, X + Size - 20, Y - 1.5 * Size, X + Size, Y - 1.5 * Size + 10, X + Size - 10, Y - 1.5 * Size);
		LineTo(hdc, X - Size + 10, Y - 1.5 * Size);
		ArcTo(hdc, X - Size + 20, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 20, X - Size + 10, Y - 1.5 * Size, X - Size, Y - 1.5 * Size + 10);
	}

	void Hide() { // ������
		SelectObject(hdc, White1);   // ���������� � ������������
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
		X = NewX;  // ���������� �������� ���������
		Y = NewY;  // � ������
		Size = NewSize;
	}
};// Form
/*---------------------------------------------------------------*/
/*----------------- ������������� ����� -------------------------*/
/*---------------------------------------------------------------*/

class Conflict : public Figure {
	//����������� ����� ������������� ��������
public:
	Conflict(int InitX, int InitY) : Figure(InitX, InitY) {
		// ����������� ����������� �� Figure
	}

	virtual bool IsContact(int x, int y) = 0;
	// ����� ����������� ������� �������� ��������������

};//Conflict
/*---------------------------------------------------------------*/
/*----------------------- ����� ������� -------------------------*/
/*---------------------------------------------------------------*/

class SignPrinter : public Conflict { // �������
private:
	int mark_id;       // ������ ��� ������
	int Size;          // ������ ��������
	Sign* Mark;        // ��������� �� ������

public:
	SignPrinter(int InitX = 0, int InitY = 0, int sign_id = 1) :Conflict(InitX, InitY) {
		mark_id = sign_id;     // ������ ��� ������
		Size = 30;             // ������ ��������
		if (mark_id == 1) {    // ����
			Mark = new Q_sign; // ��������� �� ����
		}
		if (mark_id == 2) {    // ������
			Mark = new K_sign; // ������� �� ������
		}
		if (mark_id == 3) {    // ���
			Mark = new T_sign; // ������� �� ����
		}
		Mark->SetValues(X, Y); // ��������� �������� 
	}// ����������� ������

	bool IsContact(int x, int y) {  // �������� �������������
		if (x > X - 20 and x < X + 20 and y > Y - 180 and y < Y - 160)
			// ���������� ��������� � ������������
			return true;            // ���������
		else
			return false;           // �� ���������
	}
	void Show() {                   // ����������
		SelectObject(hdc, BrBlack); // ��� (�������)
		SelectObject(hdc, PenBlack);// ������� (������)
		Rectangle(hdc, X - Size, Y - Size, X + Size, Y + Size);
		// ����� ��������
		Mark->Show();               // ���� ��������
	}
	void Hide() {                   // ������
		SelectObject(hdc, White3);  // ���������� � ������������
		Rectangle(hdc, X - Size, Y - Size, X + Size, Y + Size);
		Mark->Hide();
	}
	int GetSignId() {
		return mark_id - 1;
	}
};
/*---------------------------------------------------------------*/
/*---------------����� �������������� �����----------------------*/
/*---------------------------------------------------------------*/

class Card : public Figure { // ��������� �����
protected:
	int Size;      // ������
	Mark* Mark1;    // ����� - ����(����)
	Mark* Mark2;    // ����� - ����(���)
	Mark* MarkMain; // ����� - ����(��������)
	Form form;     // ����� �����

public:
	bool is_reverse = false;   // ��������� ��������
	Card(int InitX = 0, int InitY = 0, int color_id = 2) :Figure(InitX, InitY) {
		Size = 100;                   // ������
		if (color_id == 1) {           // ����
			Mark1    = new DiamandRed; // ��������� �� ���
			Mark2    = new DiamandRed;
			MarkMain = new DiamandRed;
		}
		if (color_id == 2) {           // ����
			Mark1    = new DiamandBlue; // ��������� �� ���
			Mark2    = new DiamandBlue;
			MarkMain = new DiamandBlue;
		}
		if (color_id == 3) {           // ����
			Mark1    = new DiamandGreen; // ��������� �� ���
			Mark2    = new DiamandGreen;
			MarkMain = new DiamandGreen;
		}
		if (color_id == 4) {           // ����
			Mark1    = new NewMark; // ��������� �� ���
			Mark2    = new NewMark;
			MarkMain = new NewMark;
		}
		SetValues();                  // ������� ������� �����
	}

	void SetValues() {// ������� ������� �����
		Mark1->SetValues(X - 3 * Size / 4, Y - 5 * Size / 6, Size / 8);
		// ������� ����
		Mark2->SetValues(X + 3 * Size / 4, Y + 5 * Size / 6, Size / 8);
		// ������ ����
		MarkMain->SetValues(X, Y, Size / 3);
		// ����������� ����
		form.SetValues(X, Y, Size);
		// ����� �����
	}

	void Show() {       // ����������
		SetValues();    // �������� �������� �����
		form.Show();    // ���������� ����
		Mark1->Show();   // ���������� 1 ����
		Mark2->Show();   // ���������� 2 ����
		MarkMain->Show();// ���������� ������� ����
	}

	void Hide() {       // ������
		form.Hide();    // ���������� � ������������  
		Mark1->Hide();
		Mark2->Hide();
		MarkMain->Hide();
	}

	int GetColorId() {
		return MarkMain->GetColorId();  // �������� ���� 
	}

};//Card
/*---------------------------------------------------------------*/
/*-----------------����� ������������ �����----------------------*/
/*---------------------------------------------------------------*/

class Marked_Card : public Card { // ��������� �����
protected:
	Sign* Sign1;                  // ��������� �� ���� �����
	Sign* Sign2;

public:
	Marked_Card(int InitX, int InitY, int color_id, int s = 1) :Card(InitX, InitY, color_id) {
		Size = 100;
		if (s == 1) {           // ����
			Sign1 = new Q_sign; // ��������� �� ���
			Sign2 = new Q_sign;
		}
		if (s == 2) {           // ������
			Sign1 = new K_sign; // ��������� �� �������
			Sign2 = new K_sign;
		}
		if (s == 3) {           // ���
			Sign1 = new T_sign; // ��������� �� �����
			Sign2 = new T_sign;
		}
		if (s == 4) {           // ���
			Sign1 = new J_sign; // ��������� �� �����
			Sign2 = new J_sign;
		}
		//Mark1.SetColorId(color_id);   // ���������� ���� 
		//Mark2.SetColorId(color_id);   // ���������� ���� 
		//MarkMain.SetColorId(color_id);// ���������� ���� 
		SetValues();                  // ������� ������� �����
	}

	void SetValues() {// ������� ������� �����
		Card::SetValues();      // ������� �������� ������
		Sign1->SetValues(X - 3 * Size / 4, Y - 15 * Size / 12, false);
		// ������� �����
		Sign2->SetValues(X + 3 * Size / 4, Y + 15 * Size / 12, true);
	}

	void Show() { // ����������
		SelectObject(hdc, White3); // ���� ����� (�����)
		SetValues();               // �������� �������� �����
		Card::Show();          // ���������� �����
		Sign1->Show();         // ���������� �����
		Sign2->Show();

	}

	void Hide() { //������
		Card::Hide();
		Sign1->Hide();
		Sign2->Hide();
		
	}
};//Marked_Card

