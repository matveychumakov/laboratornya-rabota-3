#include "RouteCipher.h"

RouteCipher::RouteCipher(int k) {
    if (k < 2)
        throw std::invalid_argument("неверный ключ");
    key = k;
}
//конструктор класса и проверка на ключ 

string RouteCipher::encrypt(const string& text) {
	string valid_text = getValidText(text); //получаем текст 
    int row = key, col = valid_text.length(); // инициализируем ряд как ключ, столбики как длину текста 
    vector<vector<char>> matrix(row, vector<char>(col, ' ')); //создаем матрицу row x col, пустую

    int direction = 0;
    int row_index = 0, col_index = 0;

    for (int i = 0; i < col; i++) {
        if (row_index == 0 || row_index == row - 1)
            direction = 1 - direction; //если индекс ряда в начале или конце -> меняем направление 
        matrix[row_index][col_index++] = text[i]; // записываем символ в матрицу 
        if (direction) //смотрим направление и идем 'вправо' или "влево"
            row_index++;
        else
            row_index--;
    }

    string cipher_text;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (matrix[i][j] != ' ')
                cipher_text += matrix[i][j];

    return cipher_text;
    //считываем каждый элемент матрицы и смотрим, если нет пробела, добавляем к cipher_text
}
//функция для шифрования
 
string RouteCipher::decrypt(const string& cipher_text) {
    int row = key, col = cipher_text.length(); //инициализируем ряд как ключ, столбики как длину шифрованного текста 
    vector<vector<char>> matrix(row, vector<char>(col, ' '));//создаем матрицу row x col, пустую

    int direction;
    int row_index = 0, col_index = 0;

    for (int i = 0; i < col; i++) {
        if (row_index == 0)
            direction = 1; //если вначале стоим, идем вниз
        if (row_index == row - 1)
            direction = 0; //если стоим в конце, идем вверх 
        matrix[row_index][col_index++] = '*'; //записываем символ * что прошли ячейку и увеличием индекс столбца 
        if (direction) // в зависимости от направления уменьшаем/увеличиваем индекс строки
            row_index++; 
        else
            row_index--;
    }

    int index = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (matrix[i][j] == '*' && index < col) //проверка если ячейка содержит * и индекс меньше длины зашифрованного текста 
                matrix[i][j] = cipher_text[index++]; //записывем символ из зашированного текст в ячейку

    string text;
    row_index = 0, col_index = 0;
    for (int i = 0; i < col; i++) { //проверяем символы и смотрим, какой текущий индекс ряда
        if (row_index == 0)
            direction = 1;
        if (row_index == row - 1)
            direction = 0;
        if (matrix[row_index][col_index] != '*') //если в ячейке нет символа * то
            text += matrix[row_index][col_index++]; // добавляем символ из матрицы к расшифрованному текску и идем дальше 
        if (direction)
            row_index++;
        else
            row_index--;
    }

    return text;
}
//функция для расшифрования 

string RouteCipher::getValidText(const std::string & text) {
    if (text.empty()) {
        throw cipher_error("введеный текст пуст");
    }
	if (static_cast<long unsigned int>(key) >= text.length()) {
        throw cipher_error("ключ не может быть больше длины строки");
    }

    for (char c : text) {
        if (!isalpha(c)) {
            throw cipher_error("введеный текст содержит некорректные символы");
        }
    }
    return text;
} //проверка входного текста на пустоту/если длина ключа >= длине текста/в тексте есть символы которые не буквы 
