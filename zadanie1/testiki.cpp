#include <UnitTest++/UnitTest++.h> //основаная библиотека для модульных тестов
#include <iostream>
#include <string>
#include <cctype>
#include <UnitTest++/TestReporterStdout.h> //отчеты о выполнении тестов
#include "modAlphaCipher.h"

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter; //для вывода отчетов
    UnitTest::TestRunner runner(reporter); // передаем репортер 
        return runner.RunTestsIf(UnitTest::Test::GetTestList(), //получение всех тестов
                                SuiteName, //имя набора тестов
                                UnitTest::True(),0); //условие выполнения тестов
}

SUITE(KeyTest){
    
    TEST(test1) {
        CHECK(modAlphaCipher(L"ПАКЕТ").encrypt(L"МОЛОКОВПАКЕТЕ")==L"ЬОЦУЭЮВЪЕЭФТП"); //ключ<строки
    }
    TEST(test2) {
        CHECK(modAlphaCipher(L"ПАКЕТПАКЕТПАКЕТ").encrypt(L"МОЛОКОВПАКЕТЕ")==L"ЬОЦУЭЮВЪЕЭФТП"); //ключ>строки
    }
    TEST(test3) {
        CHECK(modAlphaCipher(L"пакет").encrypt(L"МОЛОКОВПАКЕТЕ")==L"ЬОЦУЭЮВЪЕЭФТП"); //ключ в нижнем регистре
    }
    TEST(test4) {
        CHECK_THROW(modAlphaCipher(L"П0"), cipher_error); //ключ с цифрой
    }
    TEST(test5) {
        CHECK_THROW(modAlphaCipher(L"П.АКЕТ"), cipher_error); //ключ со знаком препинания
    }
    TEST(test6) {
        CHECK_THROW(modAlphaCipher(L"ПА КЕТ"), cipher_error); //ключ с пробелом
    }
    TEST(test7) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error); //ключ потерялся
    }
};

struct KeyB_fixture {
	modAlphaCipher * p;
	KeyB_fixture() {
		p = new modAlphaCipher(L"В"); //выделение памяти для ключа 
    }
	~KeyB_fixture() {
		delete p; //освобождение памаяти 
    }
};
//структура для работы с памятью 

SUITE(EncryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ")); //проходит ли шифрование строки в верхнем регистре
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"));//проходит ли шифрование строки в нижнем регистре
        }
    TEST_FIXTURE(KeyB_fixture, WhiteSpace) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИ ЙКЛМНОПРСТУФ ХЦЧШЩЪЫЬЭЮЯ")); //проходит ли шифрование с пробелами
        }
    TEST_FIXTURE(KeyB_fixture, Numbers) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИ871ЙКЛМНОП13РСТУФ66ХЦЧШЩЪЫЬЭЮЯ1337")); //проходит ли шифрование с цифрами
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->encrypt(L""), cipher_error); //проходит шифрование с пустым текстом
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->encrypt(L"123,,5"), cipher_error); //проходит ли шифрование без нужных символов(букв)
        }
    TEST(MaxShiftKey) {
        CHECK(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ" == modAlphaCipher(L"Я").encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ")); //проходит ли шифрование с максимальным сдвигом
        }
};
SUITE(DecryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == p->decrypt(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ")); //проходит ли расшифрование в нормальной строке
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"вгдеёжзийклмнопрстуфхцчшщъыьэюяаб"), cipher_error); //проходит ли расшифрование в строке с нижним регистром
        }
    TEST_FIXTURE(KeyB_fixture, WhiteSpace) {
        CHECK_THROW(p->decrypt(L"АБВГДЕЁЖЗИ ЙКЛМНОПРСТУФ ХЦЧШЩЪЫЬЭЮЯ"), cipher_error);//проходит ли расшифрование в строке с пробелами
        }
    TEST_FIXTURE(KeyB_fixture, Digit) {
        CHECK_THROW(p->decrypt(L"АБВ1ГД2ЕЁ3ЖЗ4И"), cipher_error);//проходит ли расшифрование в строке с цифрами
        }
    TEST_FIXTURE(KeyB_fixture, Punct) {
        CHECK_THROW(p->decrypt(L"АБВ,ГД.ЕЁ/ЖЗ;И"), cipher_error);//проходит ли расшифрование в строке с знаками препинания
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->decrypt(L""), cipher_error);//проходит ли расшифрование строки если ее нет
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->decrypt(L"123,,5"), cipher_error);//проходит ли расшифрование строки без наличия нужных символов(букв)
        }
    TEST(MaxShiftKey) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == modAlphaCipher(L"Я").decrypt(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ"));//проходит ли расшифрование с максимальным сдвигом ключа
        }
};

int main() {
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests(); //запускаем все тесты
}
