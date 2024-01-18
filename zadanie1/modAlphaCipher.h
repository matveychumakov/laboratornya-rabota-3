#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>

class modAlphaCipher {
    private:
        std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
        std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
        std::vector <int> key; //ключ
        std::vector<int> convert(const std::wstring& s); //преобразование строка-вектор
        std::wstring convert(const std::vector<int>& v); //преобразование вектор-строка
        std::wstring getValidKey(const std::wstring & s); //проверка ключа      
        std::wstring getValidOpenText(const std::wstring & s); //провека входного текста
        std::wstring getValidCipherText(const std::wstring & s); //проверка зашифр-нного текста
    public:
        modAlphaCipher()=delete; //запретим конструктор без параметров
        modAlphaCipher(const std::wstring& skey); //конструктор для установки ключа
        std::wstring encrypt(const std::wstring& open_text); //зашифрование
        std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
};
class cipher_error: public std::invalid_argument {
    public:
        explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
        explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
//обработчик ошибок, принимающий строки
