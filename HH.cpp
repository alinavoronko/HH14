/*
HH12

Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksts ar struktūru: atslēga (int), vērtība (nepārsniedz 30 simbolus). 
Failu komponentes sakārtotas atslēgu pieaugšanas secībā. Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3  tā,
lai arī f3 komponentes būtu atslēgu pieaugšanas secībā  (failos  nedrīkst parādīties 2 komponentes ar vienādu atslēgu vērtību).
Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā uz ekrāna faila saturu.*/



#include<iostream>
#include<fstream>
#include <cstring>
#include<string>
#include<map>
using namespace std;
const int wLen = 30; //vārda maks. garums


/*funkcija, kas izveido failus f1 un f2*/
void izveidot()
{

map<int, string>::iterator itr1;
map<int, string> vardnica1;


// izveidojam vārdnīcu, ar kuru aizpildīsim pirmo failu
vardnica1.insert(pair<int, string>(50, "HH"));
vardnica1.insert(pair<int, string>(46, "task"));
vardnica1.insert(pair<int, string>(36, "of"));
vardnica1.insert(pair<int, string>(35, "a test"));
vardnica1.insert(pair<int, string>(34, "is"));
vardnica1.insert(pair<int, string>(21, "this"));
vardnica1.insert(pair<int, string>(20, "!"));
vardnica1.insert(pair<int, string>(11, "world"));
vardnica1.insert(pair<int, string>(1, "hello"));

map<int, string>::iterator itr2;
map<int, string> vardnica2;

//-||- otro failu
vardnica2.insert(pair<int, string>(51, "fine"));
vardnica2.insert(pair<int, string>(44, "just"));
vardnica2.insert(pair<int, string>(33, "work"));
vardnica2.insert(pair<int, string>(21, "should"));
vardnica2.insert(pair<int, string>(8, "it"));


fstream f1("f1", ios::out | ios::binary);
fstream f2("f2", ios::out | ios::binary);


cout << "f1 faila saturs: " << endl;
for (map<int, string>::iterator it = vardnica1.begin(); it != vardnica1.end(); it++)
{

    std::cout << it->first << " => " << it->second << '\n';
    int num1 = it->first;
    string n1 = it->second;
    char char_n1[wLen + 1];
    strcpy_s(char_n1, n1.c_str());

    f1.write((char*)&num1, sizeof(num1));
    f1.write(char_n1, wLen + 1);



}

cout << "\nf2 faila saturs: " << endl;

for (map<int, string>::iterator it = vardnica2.begin(); it != vardnica2.end(); it++)
{

    std::cout << it->first << " => " << it->second << '\n';
    int num1 = it->first;
    string n1 = it->second;
    char char_n1[wLen + 1];
    strcpy_s(char_n1, n1.c_str());

    f2.write((char*)&num1, sizeof(num1));
    f2.write(char_n1, wLen + 1);
}
f1.close();
f2.close();

}

void joinDesc(fstream& f1, fstream& f2, fstream& f3)
{


    int n1;
    int n2;
    char word1[wLen + 1]; //vārda maksimālais garums + beigu simbols
    char word2[wLen + 1];

    f1.read((char*)&n1, sizeof(n1));
    f1.read(word1, sizeof(word1));
    f2.read((char*)&n2, sizeof(n2));
    f2.read(word2, sizeof(word2));

    do
    {
        if (n1 < n2)
        {
            do {
              
                f3.write((char*)&n1, sizeof(n1));
                f3.write(word1, sizeof(word1));
                f1.read((char*)&n1, sizeof(n1));
                f1.read(word1, sizeof(word1));
            } while (n1 < n2 && f1 && f2);
            /*Papildu pārbaude, vai nav sasniegtas failu beigas.*/
            if (n1 != n2) { /*ja gadījumā pēdējā nolasītā n1 vērtība nesakrīt ar n2*/
                f3.write((char*)&n2, sizeof(n2));
                f3.write(word2, sizeof(word2));
                f2.read((char*)&n2, sizeof(n2));
                f2.read(word2, sizeof(word2));
            }
        }
        else if (n2 < n1)
        {
            do {
                f3.write((char*)&n2, sizeof(n2));
                f3.write(word2, sizeof(word2));
                f2.read((char*)&n2, sizeof(n2));
                f2.read(word2, sizeof(word2));
            } while (n2 < n1 && f1 && f2);
            if (n1 != n2) {
                f3.write((char*)&n1, sizeof(n1));
                f3.write(word1, sizeof(word1));
                f1.read((char*)&n1, sizeof(n1));
                f1.read(word1, sizeof(word1));
            }
        }
        else if (n1 == n2) {

            f1.read((char*)&n1, sizeof(n1));
            f1.read(word1, sizeof(word1));
            f2.read((char*)&n2, sizeof(n2));
            f2.read(word2, sizeof(word2));
        }
    } while (f1 && f2);

    //gadījumā ja viens fails ir garāks par otru
    while (!f1.eof()) {
        f1.read((char*)&n1, sizeof(n1));
        f1.read(word1, sizeof(word1));
        f3.write((char*)&n1, sizeof(n1));
        f3.write(word1, sizeof(word1));
    }

    while (!f2.eof()) {
        f2.read((char*)&n2, sizeof(n2));
        f2.read(word2, sizeof(word2));
        f3.write((char*)&n2, sizeof(n2));
        f3.write(word2, sizeof(word2));
    }

    f1.close();
    f2.close();
    f3.close();
}


int main()
{
    izveidot();
    fstream f1("f1", ios::in | ios::binary);
    fstream f2("f2", ios::in | ios::binary);
    fstream f3("f3", ios::out | ios::binary);
    joinDesc(f1, f2, f3);
    int n3;
    char word3[wLen + 1];

    /*sagaidāmais rezultāts:
1 hello
8 it
11 world
20 !
33 work
34 is
35 a test
36 of
44 just
46 task
50 HH
51 fine */

    cout << "\nf3 faila saturs: " << endl;
    f3.open("f3", ios::in | ios::binary);
    f3.read((char*)&n3, sizeof(n3));
    f3.read(word3, sizeof(word3));
    while (f3)
    {
        cout << n3 << " " << word3 << endl;
        f3.read((char*)&n3, sizeof(n3));
        f3.read(word3, sizeof(word3));
    }
    return 0;
}