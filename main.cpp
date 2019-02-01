/*
Namn: Robar Zangana
Datum: 09/01/19
Kurs: Introduktion till programmering i C++
Labboration: Examination kontaktbok
*/
#include "metod.h"
//g++ -o run main.cpp metod.cpp
int main(){
    //Main menu-------------------------------------------------------
    string choice;
    bool bfail = false;
    do{
        cout << "1. Add contact" << endl << "2. Delete contact" << endl << "3. Search for contact" << endl << "4. Exit program" << endl;
        getline(cin, choice);
        //Se till att stringen "choice" bara har 1 i length, får inte vara fler än två siffror.
        if(choice.length() == 1){
            switch(choice.at(0)){
                case '1':
                    add();
                    break;
                case '2':
                    del();
                    break;
                case '3':
                    find();
                    break;
                case '4':
                    cout << "Bye bye!" << endl;
                    exit(0);
                    break;
                default:
                    cout << "Please enter menu number 1-4" << endl;
                    break;
            }
        }
        else
            cout << "Please enter menu number 1-4" << endl;
    }while(bfail == false);
    return 0;
}