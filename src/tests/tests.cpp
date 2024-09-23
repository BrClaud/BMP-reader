#include "../bmp_reader.h"
// #include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// здесь будут тесты

using namespace std;

TEST(NotFormatImage, color_image_24_bit){
    try
    {
        BMP_reader bmr("/home/dorothyz/project/c++/BMP-reader/materials/test_img/test1.bmp");
    }
    catch(const string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: BMP файл имееет цвета отличные от черного или белого\n");
    }
}
TEST(NotFormatImage, notFoundImage){
    try
    {
        BMP_reader bmr("/home/dorothyz/project/c++/BMP-reader/materials/test_img/test");
    }
    catch(const string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: не удалось открыть файл\n");
    }
}
TEST(NotFormatImage, not_bmp){
    try
    {
        BMP_reader bmr("/home/dorothyz/project/c++/BMP-reader/materials/test_img/abc");
    }
    catch(const string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: это не BMP файл\n");
    }
}

TEST(NotFormatImage, color_image_32_bit){
    try
    {
        BMP_reader bmr("/home/dorothyz/project/c++/BMP-reader/materials/test_img/test4.bmp");
    }
    catch(const string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: BMP файл имееет цвета отличные от черного или белого\n");
    }
}

TEST(NotOpenImage, diplayInfo){
    try
    {
        BMP_reader bmr;
        bmr.displayInfoBMP();

    }
    catch(const std::string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: файл не открыт\n");
    }
}
TEST(NotOpenImage, diplayBMP){
    try
    {
        BMP_reader bmr;
        bmr.displayBMP();

    }
    catch(const std::string& e)
    {
        EXPECT_STREQ(e.c_str(), "\nОшибка: файл не открыт\n");
    }
}

TEST(display, test_1){
    BMP_reader bmr("/home/dorothyz/project/c++/BMP-reader/materials/test_img/test2.bmp");
    // Перенаправляем стандартный вывод в stringstream
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    // Вызываем функцию
    bmr.displayInfoBMP();

    // Восстанавливаем стандартный вывод
    std::cout.rdbuf(oldCoutBuffer);

    // Проверяем вывод
    std::string output = buffer.str();
    EXPECT_EQ(output, "pixels:\n0\t0\t0\t0\t0\t0\tff\tff\tff\t\nff\tff\tff\tff\tff\tff\t0\t0\t0\t\n");

// 0\t0\t0\t0\t0\t0\tff      ff      ff
// ff      ff      ff      ff      ff      ff      0\t0\t0
}


int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}