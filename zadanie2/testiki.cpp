#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <UnitTest++/TestReporterStdout.h>
#include "RouteCipher.h"

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

std::string t;
SUITE(encrypt){
    TEST(test1){
        t = "MOLOKO"; 
        CHECK_EQUAL(RouteCipher(3).encrypt(t), "MKOOOL"); //шифрование строки с прописными буквами
    }
    TEST(test2){
        t = "MOL OKO"; 
        CHECK_THROW(RouteCipher(3).encrypt(RouteCipher(3).getValidText(t)), cipher_error); //шифрование строки с пробелами 
    }
    TEST(test3){
        t = "%%MOLO@#KO"; 
        CHECK_THROW(RouteCipher(3).encrypt(RouteCipher(3).getValidText(t)), cipher_error);//шифрование строки с различными символами 
    }
    TEST(test4){
        t = "moloko"; 
        CHECK_EQUAL(RouteCipher(3).encrypt(t), "mkoool");//шифрование строки с буквами в нижнем регистре 
    }
    TEST(test5){
        t = " "; 
        CHECK_THROW(RouteCipher(3).encrypt(RouteCipher(3).getValidText(t)), cipher_error); //шифрование строки с отсутствием в ней букв
    }    
}
SUITE(decrypt){
    TEST(t_1){
        t = "MKOOOL"; 
        CHECK_EQUAL(RouteCipher(3).decrypt(t), "MOLOKO"); //расшифрование строки с прописными буквами 
    }
    TEST(t_2){
        t = "MKO OOL"; 
        CHECK_THROW(RouteCipher(3).decrypt(RouteCipher(3).getValidText(t)), cipher_error);//расшифрование строки с пробелами 
    }
    TEST(t_3){
        t = "9MOL#OKO|^%]"; 
        CHECK_THROW(RouteCipher(3).decrypt(RouteCipher(3).getValidText(t)), cipher_error);//расшифрование строки с различными сиволами 
    }
    TEST(t_4){
        t = " ";
        CHECK_THROW(RouteCipher(3).decrypt(RouteCipher(3).getValidText(t)), cipher_error);//расшифрование строки с отсутствием в ней букв
    }
    TEST(t_5){
        t = "1-2-3-4-5"; 
        CHECK_THROW(RouteCipher(3).decrypt(RouteCipher(3).getValidText(t)), cipher_error); //расшифрование строки с отсутствием в ней нужных символов(букв)
    }    
}
SUITE(KeyTest) {
    TEST(InvalidKey) {
    CHECK_THROW(RouteCipher(0), std::invalid_argument); 
    }
    TEST(NonKey) {
    CHECK_THROW(RouteCipher(-1), std::invalid_argument);
    //тесты на правильность ключа 
}
}

SUITE(KeyLengthTest) {
    TEST(KeyGreaterThanTextLength) {
        CHECK_THROW(RouteCipher(10).getValidText("mlk"), cipher_error);
    }
    //тест на сравнение ключа с строкой
}
int main() {
    return UnitTest::RunAllTests();
}  
