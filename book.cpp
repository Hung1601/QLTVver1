#include"book.h"

string book:: getName(){
    return name;
}

string book:: getAuthor(){
    return author;
}

string book:: getType(){
    return type;
}
    
string book:: getPublisher(){
    return publisher;
}

int book:: getYearPublished(){
    return yearPublished;
}

int book:: getNumber(){
    return number;
}

int book:: getID(){
    return ID;
}

void book:: setName(string &nameBook){
    name = nameBook;
}

void book:: setAuthor(string &nameAuthor){
    author = nameAuthor;
}

void book:: setType(string &nameType){
    type = nameType;
}

void book:: setPublisher(string &namePublisher){
    publisher = namePublisher;
}

void book:: setYearpublisher(int &YearPublished){
    yearPublished = YearPublished;
}

void book:: setID(int &id){
    ID = id;
}

void book:: setNumber(int &Number){
    number = Number;
}

void book:: display(){
    cout << left << setw(8) << ID << setw(40) << name << setw(20) << type << setw(25) << author << setw(20) << number << endl;
}

void book:: showBookInformation(){
    cout << "Thong tin sach la: "<< endl;
    cout << "ID: " << ID << endl;
    cout << "Ten sach: " << name << endl;
    cout << "Tac gia: " << author << endl;
    cout << "Nha xuat ban: " << publisher << endl;
    cout << "Nam xuat ban: " << yearPublished << endl;
    cout << "So luong sach: " << number << endl;
} 
        
void book:: addBook(){
    cout << "Nhap thong tin sach muon them! "<< endl;
    cin.ignore();
    cout << "Ten sach: ";
    getline(cin,name);
    cout << "Tac gia: ";
    getline(cin,author);
    cout << "The loai: ";
    getline(cin,type);
    cout << "Nha xuat ban: ";
    getline(cin,publisher);
    cout << "Nam xuat ban ";
    cin >> yearPublished;
    cout << "So luong sach: ";
    cin >> number;
    cout << endl;
}