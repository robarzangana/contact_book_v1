/*
Namn: Robar Zangana
Datum: 09/01/19
Kurs: Introduktion till programmering i C++
Labboration: Examination kontaktbok
*/
#include "metod.h"

//Add menu-------------------------------------------------------------
void add(){
    string contact, name, ad, em, bir, res, num;
    bool check;
    //cin.ignore();
    
    //Namn
    cout << "Type in the persons name. End by pressing enter" << endl;
    name = only_alpha_check();

    //Adress
    cout << "Type in persons address (optional). End by pressing enter" << endl;
    getline(cin, ad);
    
    //Email
    cout << "Type in persons email. End by pressing enter" << endl;
    getline(cin, em);
    em = mail_check(em);
    
    //Telefonnummer
    cout << "Type in persons phone number. End by pressing enter" << endl;
    num = only_num_check();
    
    //Födelsedag
    cout << "Type in persons birthdate. End by pressing enter" << endl;
    bir = only_num_check();

    //Annat
    cout << "Type in other information about the person (optional). End by pressing enter" << endl;
    getline(cin, res);

    contact = name + " " + ad + " " + em + " " + num + " " + bir + " " + res;
    
    ofstream output;
    output.open("kontaktbok.txt", ios_base::app); //ios_bas::app (append) gör så att den lägger till string på nästa rad av kontaktbok.txt, så den ersätter inte
    output << contact << endl;
    output.close();
    cout << "You have added " << name << " to your contacts" << endl;
    return;
}

//Delete menu------------------------------------------------------
void del(){
    string line, ctxt, txt;
    bool bfail = false;
    int found = 0, row = 0, r = 0;
    //cin.ignore();

    //För in all data från fil in till vectorn "vec"
    vector<string> vec;
    //Kontrollerar om "file" existerar, om inte då kommer den skriva ut error meddelande
    ifstream file("kontaktbok.txt");
    if(file.fail()){
        cout << "No contact book exists, create new one by adding a contact in main menu" << endl;
        return; //Avsluta tillbaka till main().
    }
    while(file.peek() != EOF){
        getline(file, line);
        vec.push_back(line);
    }
    file.close();

    //Skriver ut vektorn
    cout << "Rows: " << endl;
    for(auto a : vec){
        r++;
        cout << r << ". " << a << endl;
    }

    do{
        //Rad som ska raderas från vektorn
        cout << "Which row do you want to delete?" << endl;
        txt = only_num_check();
        row = stoi(txt);
        //cout << "txt: " << txt << endl << "v: " << r << endl << "row: "<< row << endl;
        if(row<=r){
            vec.erase(vec.begin()+(row-1), vec.begin()+row);
            bfail = true;
        }
        else
            //Om rad inte finns
            cout << "That row does not exist, try again." << endl;
    }while(bfail == false);
    
    //Skriv ut vektorn till ny fil som ersätter gamla (samma namn)
    ofstream output;
    output.open("kontaktbok.txt");
    for(auto a : vec){
        output << a << endl;
    }
    cout << "Contact have been deleted" << endl;
    output.close();
    return;
}



//Find menu-----------------------------------------------------------------
void find(){
    string search_word, c_search_word, line;
    int found = 0, exist = 0;
    //cin.ignore();
    
    ifstream file("kontaktbok.txt");
    if(file.fail()){
        cout << "No contact book exists, create new one by adding a contact in main menu" << endl;
        return;
    }

    cout << "Type in the text your searching for:" << endl;
    getline(cin, search_word);
    c_search_word = lower_check(search_word);
   //Kontroll
   //cout << "word: " << search_word << endl << "cword: " << c_search_word << endl;
    
    //Leta efter string
    while(file.peek() != EOF){
        getline(file, line);
        found = lower_check(line).find(c_search_word, 0);

        //Om sökstring existerar i fil, skriv ut hela den raden där den finns och öka "exist" med 1
        if(found >= 0){
            cout << line << endl;
            exist++;
        }

        //Om sökstring inte existerar i fil
        if(file.peek() == EOF && exist == 0)
            cout << endl << "Searched input does not exist in contacts" << endl;
    }
    //Om inga kontakter existerar
    if (file.peek() == EOF && line.size()==0){
            cout << "You have no contacts stored" << endl;
    }
    file.close();
    return;
}

//------------------------METODER-------------------------------------
//Kontrollerar att bara nummer har skrivits in
string only_num_check(){
    bool bfail = false;
    string num, rnum;
    do{
        rnum ="";
        num = "";
        getline(cin, rnum);
        for(int i = 0; i!=rnum.length(); i++){
            switch(rnum.at(i)){
                case '0' : case '1' : case '2' : case '3' : case '4' : case '5' :
                case '6' : case '7' : case '8' : case '9' :
                    num += rnum.at(i);
                    if(num.length() == rnum.length())
                        bfail = true;
                    break;
                default:
                    cout << "Invalid input type, only numbers are allowed. Try again" << endl;
                    //Avbryt forsats genom att i=slutet av for-satsen
                    i = rnum.length()-1;
                    break;
            }
        }
    }while(bfail == false);
    return num;
}

//Kontrollerar att bara bokstäver och mellanslag har skrivits in
string only_alpha_check(){
    string cname, name;
    bool check = false;
    do{
        cname ="";
        name = "";
        getline(cin, name);
        for(int i=0; i!=name.length(); i++){
            if(isalpha(name.at(i)) || name.at(i) == ' ' ||/*å, ä, ö, Å, Ä, Ö*/ name.at(i) == '\x86' || 
            name.at(i) == '\x84' || name.at(i) == '\x94' || name.at(i) == '\x8F' || name.at(i) == '\x8E' || 
            name.at(i) == '\x99'){
                cname += name.at(i);
            }
            else{
                cout << "Invalid input type. May only contain letters" << endl;
                cname ="";
                i=name.length();
                break;
            }
            if(cname.length() == name.length())
                check=true;
        }
    }while(check==false);
    return cname;
}

//Konverterar alla bokstäver till små bokstäver
string lower_check(string a){
    string b;
    for(int i=0; i!=a.length(); i++)
        b += tolower(a.at(i));
    return b;
}

//Kontrollerar att "@" finns med i stringen
string mail_check(string a){
    bool req = false;
    do{
        for(int i=0; i!=a.length(); i++){
            if(a.at(i) == '@'){
                req = true;
                break;
            }
        }
        if(req==false){
            cout << "You need to have a '@' in your mail. Try again" << endl;
            getline(cin, a);
        }
    }while(req == false);
    return a;
}