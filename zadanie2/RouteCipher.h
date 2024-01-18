#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cctype>
#include <locale>
#include <codecvt>
using namespace std;
class RouteCipher
{
private:
    int key;
public:
    RouteCipher() = delete; //запретим конструктор без параметров
    RouteCipher(int k); //конструктор для установки ключа
    string getValidText(const std::string & text); //проверяем входной текст
    string encrypt(const string& text); //зашифрование
    string decrypt(const string& cipher_text); //расшифрование
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};//обработчик ошибок, принимающий строки
