#include "modAlphaCipher.h"

inline std::wstring modAlphaCipher::getValidKey(const std::wstring & s){ 
    if (s.empty()){
        throw cipher_error("ключ пустой");
    }
        std::wstring tmp(s);
        for (auto & c:tmp) {
            if (!iswalpha(c))
                throw cipher_error(std::string("неверный ключ"));
            if (iswlower(c))
                c = towupper(c);
        }
    return tmp;
}
//проверка ключа и преобразования 

inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & s)
{ 
    std::wstring tmp;
    for (auto c:s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
            }
}
    if (tmp.empty())
        throw cipher_error("входной текст пустой");
    return tmp;
}
//проверка входного текста на символы + ошибка если текст пустой

inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & s)
{ 
    if (s.empty()){
        throw cipher_error("входной зашифрованный текст пустой");
    }
        for (auto c:s) {
            if (!iswupper(c))
            throw cipher_error(std::string("зашифрованный текст неверен"));
}
return s;
}
//проверка зашифрованного текста на его состав

modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
}
//прохождение по каждому символу и установление из положения с положением алфавита
//+преобразование ключа и его проверка

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
//проверка и преобразование входного текста в вектор + шифрование ключом по каждому символу

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
//проверка и преобразование зашифрованного текста в вектор + расшифрование 

inline std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
//конвертация строки в вектор

inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
//конвертация вектора в строку
