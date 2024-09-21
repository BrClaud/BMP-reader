#include <ncurses.h>

#include <fstream>
#include <string>

#include "bmp_reader.h"

using namespace std;

typedef struct {
	int a;
	int b;
} test;

void displayBytes(const string &path);
void test_bytes_to_int();

int main(int argc, char *argv[]) {
	if (argc == 2) {
		BMP_reader bmr;
		try {
			bmr.openBMP(argv[1]);
		} catch (const string &e) {
			std::cerr << e << '\n';
			exit(0);
		}
		// bmr.displayInfoBMP();
		bmr.displayBMP();

	} else {
		cout << "Не введен путь к файлу";
	}
	return 0;
}

void test_bytes_to_int() {
	ofstream of("/home/dorothyz/project/c++/BMP-reader/materials/test.bin",
				ios::in | ios::binary | ios::trunc);
	unsigned char ch1 = '\0';
	unsigned char ch2 = '\xff';
	unsigned char ch3 = '\xe0';
	of.write((char *)&ch1, sizeof(ch1));
	of.write((char *)&ch2, sizeof(ch2));
	of.write((char *)&ch3, sizeof(ch3));
	of.close();

	ifstream in("/home/dorothyz/project/c++/BMP-reader/materials/test.bin",
				ios::out | ios::binary);
	in.seekg(0, ios::end);
	int size = in.tellg();
	in.seekg(0, ios::beg);

	// vector<unsigned char> arr(size);
	int clr = 0;
	//.data передает указатель на начало массива, а arr передает обьект класса
	// vector
	in.read(reinterpret_cast<char *>(&clr), size);
	in.close();

	cout << "start\n";
	cout << hex << clr << endl;
	// for(unsigned char byte : arr){
	// 	cout<< hex << static_cast<int>(byte)<<' ';
	// }
	cout << "\nend\n";
}

void displayBytes(const string &path) {
	ofstream of(path, ios::in | ios::binary | ios::trunc);
	string str;
	cin >> str;
	of.write((char *)str.c_str(), str.size());
	of.close();

	ifstream in(path, ios::out | ios::binary);
	in.seekg(0, ios::end);
	int size = in.tellg();
	in.seekg(0, ios::beg);

	vector<unsigned char> arr(size);
	//.data передает указатель на начало массива, а arr передает обьект класса
	// vector
	in.read(reinterpret_cast<char *>(arr.data()), size);
	in.close();

	cout << "start\n";
	for (unsigned char byte : arr) {
		cout << hex << static_cast<int>(byte) << ' ';
	}
	cout << "\nend\n";
}