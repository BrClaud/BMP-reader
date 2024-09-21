#include "bmp_reader.h"

BMP_reader::BMP_reader(const string &fileName) { openBMP(fileName); }

BMP_reader::~BMP_reader() { closeBMP(); }

template <typename T>
void BMP_reader::read(ifstream &filePath, T &result, size_t size) {
	filePath.read(reinterpret_cast<char *>(&result), size);
}

/**
 * @brief открывает BMP файл и считывает информацию
 * @return 1 - ошибка
 * @return 0 - успешно
 */
int BMP_reader::openBMP(const string &fileName) {
	// начало открытия файла
	fs.open(fileName, ios::binary);
	if (!fs.is_open()) {
		cout << "ошибка открытия\n";
		// TODO throw
		return 1;
	}

	// читаем заголовок
	read(fs, fileHeader.bfType, sizeof(fileHeader.bfType));
	read(fs, fileHeader.bfSize, sizeof(fileHeader.bfSize));
	read(fs, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
	read(fs, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved2));
	read(fs, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));

	// проверка на то что это BMP файл, начинается с "BM"
	if (fileHeader.bfType != 0x4D42) {
		cout << "ошибка: это не BMP файл\n";
		return 1;
	}

	// читаем информацию
	read(fs, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));
	read(fs, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
	read(fs, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
	read(fs, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
	read(fs, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
	read(fs, fileInfoHeader.biComression, sizeof(fileInfoHeader.biComression));
	read(fs, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
	read(fs, fileInfoHeader.biXPelsPerMeter,
		 sizeof(fileInfoHeader.biXPelsPerMeter));
	read(fs, fileInfoHeader.biYPelsPerMeter,
		 sizeof(fileInfoHeader.biYPelsPerMeter));
	read(fs, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
	read(fs, fileInfoHeader.biClrImportant,
		 sizeof(fileInfoHeader.biClrImportant));

	// читаем цвета по пикселям
	for (int i = 0; i < fileInfoHeader.biHeight; ++i) {
		rgb.push_back(vector<RGBQUAD>(fileInfoHeader.biWidth));
	}
	int bytesPerPixel = fileInfoHeader.biBitCount / 8;
	int rowSize = fileInfoHeader.biWidth * (bytesPerPixel);
	int padding = (4 - (rowSize % 4)) % 4;
	// создаем вектор строку

	// ищем сдвиг по байтам
	fs.seekg(fileHeader.bfOffBits, ios::beg);
	for (int i = 0; i < fileInfoHeader.biHeight; ++i) {
		// читаем строку битов
		vector<unsigned char> row(padding + rowSize);
		vector<unsigned char>::iterator it;
		fs.read(reinterpret_cast<char *>(row.data()), row.size());
		it = row.begin();
		// идем по байтам строки и записываем их в каждый пиксель
		for (int j = 0; j < fileInfoHeader.biWidth; ++j) {
			rgb[i][j].rgbBlue = *it++;
			rgb[i][j].rgbGreen = *it++;
			rgb[i][j].rgbRed = *it++;
			if (bytesPerPixel == 3) {
				rgb[i][j].rgbReserved = 0;
			} else {
				rgb[i][j].rgbReserved = (*it)++;
			}
		}
	}
	// развернем вектор чтобы строки были в правильном порядке
	reverse(rgb.begin(), rgb.end());
	return 0;
}

void BMP_reader::closeBMP() { fs.close(); }

void BMP_reader::displayInfoBMP() {
	// printf потому что так проще выводить много переменных и форматировать их
	printf(
		"bfType: %d\nbfSize: %d\nbfReserved1: %d\nbfReserved2: %d\nbfOffBits: "
		"%d",
		fileHeader.bfType, fileHeader.bfSize, fileHeader.bfReserved1,
		fileHeader.bfReserved2, fileHeader.bfOffBits);
	printf(
		"biSize: %d\nbiWidth: %d\nbiHeight: %d\nbiPlanes: %d\nbiBitCount: "
		"%d\nbiCommpression: %d\nbiSizeImage: %d\nbiXPerMetr: %d\nbiYPerMetr: "
		"%d\nbibiClrUsed: %d\nbiClrImportant: %d\n",
		fileInfoHeader.biSize, fileInfoHeader.biWidth, fileInfoHeader.biHeight,
		fileInfoHeader.biPlanes, fileInfoHeader.biBitCount,
		fileInfoHeader.biComression, fileInfoHeader.biSizeImage,
		fileInfoHeader.biXPelsPerMeter, fileInfoHeader.biYPelsPerMeter,
		fileInfoHeader.biClrUsed, fileInfoHeader.biClrImportant);
	cout << "вывод байтов пикселей:\n";
	for (int i = 0; i < fileInfoHeader.biHeight; ++i) {
		for (int j = 0; j < fileInfoHeader.biWidth; ++j) {
			cout << hex << static_cast<int>(rgb[i][j].rgbRed) << '\t';
			cout << hex << static_cast<int>(rgb[i][j].rgbGreen) << '\t';
			cout << hex << static_cast<int>(rgb[i][j].rgbBlue) << '\t';
			if (fileInfoHeader.biBitCount / 8 == 4)
				cout << hex << static_cast<int>(rgb[i][j].rgbReserved) << '\t';
		}
		cout << '\n';
	}
}
