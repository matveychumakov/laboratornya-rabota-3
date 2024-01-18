#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"


// проверка, чтобы строка состояла только из прописных букв
bool isValid(const std::wstring& s) {
    for(auto c:s)
        if (!iswalpha(c) || !iswupper(c))
            return false;
    return true;
}

void check(const std::wstring& Text, const std::wstring& key)
{ 
    try{
        std::wstring cipherText;
        std::wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text); //шифрование текста
        decryptedText = cipher.decrypt(cipherText); // расшифрование текста
        std::wcout<<"key="<<key<<std::endl;
        std::wcout<<Text<<std::endl;
        std::wcout<<cipherText<<std::endl;
        std::wcout<<decryptedText<<std::endl;
    }
    catch (const cipher_error & e) {
        std::wcerr<<"error: "<<e.what()<<std::endl;
    }
}

int main() {
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    std::wcout << modAlphaCipher(L"").encrypt(L"МОЛОКОВПАКЕТЕ") << std::endl;
    return 0;
}
