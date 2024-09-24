#ifndef BMP_READER_H
#define BMP_READER_H

#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BMP_reader {
	typedef struct {
		// Отметка для отличия формата от других (сигнатура
		// формата). Может содержать единственное значение
		// 4D4216/424D16 (little-endian/big-endian)
		unsigned short bfType;
		// 	Размер файла в байтах.
		unsigned int bfSize;
		// Зарезервированы и должны содержать ноль.
		unsigned short bfReserved1;
		// Зарезервированы и должны содержать ноль.
		unsigned short bfReserved2;
		// Положение пиксельных данных относительно
		// начала данной структуры (в байтах).
		unsigned int bfOffBits;
	} BITMAPFILEHEADER;

	typedef struct {
		// Размер данной структуры в байтах, указывающий
		// также на версию структуры
		unsigned int biSize;
		// Ширина растра в пикселях. Указывается целым числом со
		// знаком. Ноль и отрицательные не документированы.
		int biWidth;
		// Целое число со знаком, содержащее два параметра:
		// высота растра в пикселях (абсолютное значение числа) и
		// порядок следования строк в двумерных массивах (знак
		// числа). Нулевое значение не документировано.
		int biHeight;
		// В BMP допустимо только значение 1. Это поле
		// используется в значках и курсорах Windows.
		unsigned short biPlanes;
		// Количество бит на пиксель (список поддерживаемых
		// смотрите в отдельном разделе ниже).
		// Количество бит на пиксель (список поддерживаемых
		// смотрите в отдельном разделе ниже).
		unsigned short biBitCount;
		// Указывает на способ хранения пикселей
		unsigned int biComression;
		// Размер пиксельных данных в байтах. Может
		// быть обнулено если хранение осуществляется
		// двумерным массивом.
		unsigned int biSizeImage;
		// Количество пикселей на метр по горизонтали
		int biXPelsPerMeter;
		// Количество пикселей на метр по вертикали
		int biYPelsPerMeter;
		// Размер таблицы цветов в ячейках.
		unsigned int biClrUsed;
		// Количество ячеек от начала таблицы цветов до
		// последней используемой (включая её саму).
		unsigned int biClrImportant;
	} BITMAPINFOHEADER;

	typedef struct {
		unsigned char rgbBlue;
		unsigned char rgbGreen;
		unsigned char rgbRed;
		unsigned char rgbReserved;
	} RGBQUAD;

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER fileInfoHeader;
	vector<vector<RGBQUAD>> rgb;

	ifstream fs;
	template <typename T>
	void read(ifstream &filePath, T &result, size_t size);

   public:
	// конструкторы
	BMP_reader(){};
	BMP_reader(const string &fileName);

	// деструктор
	~BMP_reader();

	int openBMP(const string &fileName);
	virtual void displayBMP();
	virtual void displayInfoBMP();
	void closeBMP();
};

#endif