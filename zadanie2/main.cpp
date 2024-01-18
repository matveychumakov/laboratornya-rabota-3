#include "RouteCipher.h"

void check(const string& text, const string& key)
{
    try {
        string cipherText; 
        string decryptedText;
        int keyInt = std::stoi(key); //ключ в число
        try {
            RouteCipher cipher(keyInt); 
            cipherText = cipher.encrypt(text); // шифруем текст 
            decryptedText = cipher.decrypt(cipherText); //расшифруем текст 
            cout<<"key:"<<key<<endl;
            cout<<"text:"<<text<<endl;
            cout<<"encrypted text: "<<cipherText<<endl;
            cout<<"decrypted text: "<<decryptedText<<endl;
        } catch (const invalid_argument& e) { //вывод ошибки если неверный аргумент
            cerr << "error: " << e.what() << '\n';
        }
    } catch (const cipher_error & e) { //вывод ошибки если че то не так с шифрованием
        cerr<<"error: "<<e.what()<<endl;
    }
    cout<<""<<endl;
}



int main()
{
    check("MOLOKO","-1");
	cout << "-------------" << endl;
    check("СКАЧАТЬОБОИ","3");
	cout << "-------------" << endl;
    check("MOLOKO","3");
	cout << "-------------" << endl;
    check("82923{{ооз43щ!)","3");
	cout << "-------------" << endl;
	check("","3");
	cout << "-------------" << endl;
    return 0;
}
