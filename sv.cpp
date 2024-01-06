#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

class Person
{

public:
	enum Role
	{
		Student,
		Teacher,
		Parent
	};
	string id;
	string name;
	string usename;
	string password;
	int role;

	virtual void write(std::ostream& os)const {
		os << id << "|" << name << "|" << usename << "|" << password << "|" << role;
	}

	virtual	void read(std::istream& is) {
		getline(is, id, '|');
		getline(is, name, '|');
		getline(is, usename, '|');
		getline(is, password, '|');
		is >> role;
	}
};

class Student :public Person
{
public:
	Student() {
		role = Person::Student;
	}
	string className;
	string phone;
	float gpa = 0.0f;

	void write(std::ostream& os) const override {
		Person::write(os);
		os << "|" << className << "|" << phone << "|" << gpa;
	}

	void read(std::istream& is)  override {
		Person::read(is);

		getline(is, className, '|');
		getline(is, className, '|');
		getline(is, phone, '|');
		is >> gpa;
	}
	void insertInformation();
	void displayInfo();
	void update();
};


template <typename T>
class Manager
{
protected:
	vector<T*> datas;
	string filename;
public:
	T* login(string username, string password);
	bool isExistUsename(string username);
	vector<T*>getAll();
	void  add(T* value);
	T* searchById(string id);
	vector<T*> searchByName(string name);
	void update(T* value, T* newValue);
	void remove(T* value);
	virtual	void readFile();
	void writeFile();
};


class StudentManagement : public Manager<Student>
{
private:
public:
	vector<string> menuItems = { "Xem thong tin ca nhan", "Cap nhat thong tin", "Thoat" };
	StudentManagement() {
		filename = "Students.dat";
		Manager::readFile();
	}

	void sortGpaDecrease() {
		int count = datas.size();
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = i + 1; j < count; j++) {
				if (datas[i]->gpa < datas[j]->gpa) {
					auto temp = datas[i];
					datas[i] = datas[j];
					datas[j] = temp;

				}
			}
		}
		writeFile();
	}
	void sortGpaAscending() {
		int count = datas.size();
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = i + 1; j < count; j++) {
				if (datas[i]->gpa > datas[j]->gpa) {
					auto temp = datas[i];
					datas[i] = datas[j];
					datas[j] = temp;

				}
			}
		}
		writeFile();
	}

};

class TeacherManagement :public Manager<Person>
{
private:

public:
	vector<string> menuItems = { "Them sinh vien", "Danh sach sinh vien","Tim kiem sinh vien", "Xem thong tin sinh vien","Nhap diem cho sinh vien", "Xoa sinh vien", "Sap xep SV theo diem(tang dan)", "Sap xep SV theo diem(giam dan)",  "Thoat" };

	TeacherManagement() {
		filename = "Teachers.dat";
		Manager::readFile();
		if (datas.size() == 0) {
			Person* gv = new Person();
			gv->id = "gv001";
			gv->name = "Giao vien 1";
			gv->usename = "gv001";
			gv->password = "12345";
			gv->role = Person::Teacher;
			add(gv);
		}
	}
};

class ParentManagement : public Manager<Person>
{
private:

public:
	vector<string> menuItems = { "Xem thong tin sinh vien", "Thoat" };

	ParentManagement() {
		filename = "Parents.dat";
		Manager::readFile();
		if (datas.size() == 0) {
			Person* pa = new Person();
			pa->id = "ph001";
			pa->name = "Phu huynh 1";
			pa->usename = "ph001";
			pa->password = "12345";
			pa->role = Person::Parent;
			add(pa);
		}
	}
};


template<typename T>
T* Manager<T>::login(string username, string password)
{
	for (Person* person : datas)
	{
		if (person->usename == username && person->password == password) {
			return (T*)person;
		}
	}
	return nullptr;
}

template<typename T>
bool Manager<T>::isExistUsename(string username)
{
	for (Person* person : datas) {
		if (person->usename == username) return true;
	}
	return false;
}

template<typename T>
inline vector<T*> Manager<T>::getAll()
{
	return datas;
}

template<typename T>
void Manager<T>::add(T* value)
{
	datas.push_back(value);
	writeFile();
}

template<typename T>
T* Manager<T>::searchById(string id)
{
	for (Person* person : datas) {
		if (person->id == id) return (T*)person;
	}
	return nullptr;
}


template<typename T>
vector<T*> Manager<T>::searchByName(string name)
{
	vector<T*> result;
	for (Person* person : datas) {
		if (person->name.find(name) != std::string::npos) {
			result.push_back((T*)person);
		}
	}
	return result;
}

template<typename T>
void Manager<T>::remove(T* value)
{
	for (auto it = datas.begin(); it != datas.end(); ++it)
	{
		if ((*it)->id == value->id) {
			datas.erase(it);
			break;
		}

	}
	delete value;
	writeFile();
}

template<typename T>
void Manager<T>::update(T* value, T* newValue)
{
	auto data = searchById(((Person*)value)->id);
	data = newValue;
	writeFile();
}

template<typename T>
void Manager<T>::readFile()
{
	ifstream infile(filename);
	string objectType;
	if (!infile.is_open()) return;

	if (infile.peek() == std::ifstream::traits_type::eof()) {
		return;
	}
	while (!infile.eof())
	{
		T* person = new T();
		person->read(infile);
		datas.push_back((T*)person);
	}
	infile.close();
}

template<typename T>
void Manager<T>::writeFile()
{
	ofstream file(filename);
	for (Person* person : datas) {
		person->write(file);
	}
	file.close();
}

class GlobalVariable {
public:
	static StudentManagement* studentM;
	static ParentManagement* parentM;
	static TeacherManagement* teacherM;
};

StudentManagement* GlobalVariable::studentM = new StudentManagement();
TeacherManagement* GlobalVariable::teacherM = new TeacherManagement();
ParentManagement* GlobalVariable::parentM = new ParentManagement();


void Student::insertInformation()
{

	cout << "Nhap ma sinh vien: ";
	std::cin.ignore();
	getline(cin, id);

	while (GlobalVariable::studentM->searchById(id) != nullptr)
	{
		cout << "Ma sinh vien da ton tai!\n";
		cout << "Nhap lai ma sinh vien: ";
		getline(cin, id);

	}

	cout << "Nhap ten sinh vien: ";
	getline(cin, name);

	cout << "Nhap ten tai khoan: ";
	getline(cin, usename);


	while (GlobalVariable::studentM->isExistUsename(usename))
	{
		cout << "Tai khoan da ton tai!\n";
		cout << "Nhap lai ten tai khoan: ";
		getline(cin, usename);

	}
	cout << "Nhap mat khau: ";
	getline(cin, password);

	cout << "Nhap ten lop: ";
	getline(cin, className);

	cout << "Nhap so dien thoai: ";
	getline(cin, phone);

}

void Student::displayInfo()
{
	string line = "========================================";
	cout << line << "\n\n";
	cout << " Thong tin sinh vien" << "\n\n";
	cout << line << "\n\n";

	cout << "Ma sinh vien: " << id << endl;
	cout << "Ho ten: " << name << endl;
	cout << "Lop: " << className << endl;
	cout << "So dien thoai: " << phone << endl;
	cout << "Diem trung binh: " << gpa << "\n\n";
	cout << line << "\n\n";
}

void Student::update()
{
	string line = "========================================";
	cout << line << "\n\n";
	cout << " Cap nhat thong tin" << "\n\n";
	cout << line << "\n\n";

	cout << " 1. Ho ten: " << name << endl;
	cout << " 2. Lop: " << className << endl;
	cout << " 3. So dien thoai: " << phone << endl;
	cout << " 4. Thoat\n\n";
	cout << line << "\n\n";
	int choose;
	cout << endl << "Nhap lua chon: ";
	cin >> choose;
	while (choose < 1 || choose > 4)
	{
		cout << "Chon sai, vui long chon lai";
		cin >> choose;
	}


	switch (choose)
	{
	case 1:
		cout << "Nhap ten moi: ";
		fflush(stdin);
		cin >> name;
		break;
	case 2:
		cout << "Nhap lop moi: ";
		fflush(stdin);
		cin >> className;
		break;
	case 3:
		cout << "Nhap so dien thoai moi: ";
		fflush(stdin);
		cin >> phone;
		break;
	case 4:
		return;
	}

	GlobalVariable::studentM->writeFile();
	cout << "\n\nCap nhat thong tin thanh cong!\n";

}


Person* login(string usename, string password);
int menu(string title, vector<string> menuItems);

void showListStudent(vector<Student*> students);
void pressAnyKeyToContinue();

int main()
{
	string line = "========================================";
	Person* person = nullptr;
	cout << line << endl << endl;
	cout << " Dang nhap" << endl << endl;
	cout << line << endl << endl;
	string usename, password;
	do {
		cout << "Nhap tai khoan: ";
		fflush(stdin);
		cin >> usename;

		cout << "Nhap mat khau: ";
		fflush(stdin);
		cin >> password;

		person = login(usename, password);
		if (person == nullptr) {
			cout << "TAI KHOAN hoac MAT KHAU khong chinh xac!!!" << endl;
			cout << "Bam phim bat ki de thu lai...";
			_getch();
			cout << endl << endl;
		}
	} while (person == nullptr);
	cout << "\n\n\n";
	int choose = 0;
	switch (person->role)
	{
	case Person::Student:
	{
		Student* student = (Student*)person;
		do
		{
			choose = menu("Quan li sinh vien", GlobalVariable::studentM->menuItems);
			switch (choose)
			{
			case 1:// xem thong tin
				student->displayInfo();
				pressAnyKeyToContinue();
				break;
			case 2:// cap nhat thong tin
				student->update();
				pressAnyKeyToContinue();
				break;
			}
		} while (choose != GlobalVariable::studentM->menuItems.size());
	}
	break;
	case Person::Teacher:
		do
		{
			choose = menu("Quan li sinh vien", GlobalVariable::teacherM->menuItems);
			switch (choose)
			{
			case 1: //them sv
			{
				Student* student = new Student();
				student->insertInformation();
				GlobalVariable::studentM->add(student);
				cout << "\nThem sinh vien thanh cong!\n";
				pressAnyKeyToContinue();
				break;
			}
			case 2: // danh sach sinh vien
			{
				auto students = GlobalVariable::studentM->getAll();
				if (students.size() > 0) {
					showListStudent(students);
				}
				else {
					cout << "Khong tim thay sinh vien!\n";
				}
				pressAnyKeyToContinue();
				break;
			}

			case 3:
			{
				string name;
				cout << "Nhap ten sinh vien: ";
				fflush(stdin);
				cin >> name;

				auto students = GlobalVariable::studentM->searchByName(name);
				if (students.size() > 0) {
					showListStudent(students);
				}
				else {
					cout << "Khong tim thay sinh vien!\n";
				}
				pressAnyKeyToContinue();
				break;
			}
			case 4:// xem thong tin sinh vien
			{
				string id;
				cout << "Nhap ma sinh vien: ";
				fflush(stdin);
				cin >> id;

				auto student = GlobalVariable::studentM->searchById(id);
				if (student != nullptr) {
					student->displayInfo();
				}
				else {
					cout << "Ma sinh vien khong ton tai!\n";
				}
				pressAnyKeyToContinue();
				break;
			}
			case 5:// nhap diem
			{
				string id;
				cout << "Nhap ma sinh vien: ";
				fflush(stdin);
				cin >> id;
				auto student = GlobalVariable::studentM->searchById(id);
				if (student != nullptr) {
					cout << "Nhap diem: ";
					fflush(stdin);
					cin >> student->gpa;
					GlobalVariable::studentM->writeFile();
				}
				else {
					cout << "Ma sinh vien khong ton tai!\n";
				}
				pressAnyKeyToContinue();
				break;
			}

			case 6: // xoa sinh vien
			{
				cout << "Nhap ma sinh vien can xoa: ";
				string id;
				fflush(stdin);
				cin >> id;
				auto student = GlobalVariable::studentM->searchById(id);
				if (student != nullptr) {
					GlobalVariable::studentM->remove(student);
					cout << "\nXoa thanh cong!\n";
				}
				else {
					cout << "Sinh vien khong ton tai!\n";
				}
				pressAnyKeyToContinue();
				break;
			}
			case 7: // sap xep tang dan
			{
				GlobalVariable::studentM->sortGpaAscending();
				auto students = GlobalVariable::studentM->getAll();
				if (students.size() > 0) {
					showListStudent(students);
				}
				else {
					cout << "Khong tim thay sinh vien!\n";
				}
				pressAnyKeyToContinue();
				break;
			}
			case 8: // sap xem giam dan
			{
				GlobalVariable::studentM->sortGpaDecrease();
				auto students = GlobalVariable::studentM->getAll();
				if (students.size() > 0) {
					showListStudent(students);
				}
				else {
					cout << "Khong tim thay sinh vien!\n";
				}
				pressAnyKeyToContinue();
				break;
			}
			}
		} while (choose != GlobalVariable::teacherM->menuItems.size());

		break;

	case Person::Parent:
		do
		{
			choose = menu("Quan li sinh vien", GlobalVariable::parentM->menuItems);
			switch (choose)
			{
			case 1: //xem thong tin sinh vien
			{
				string id;
				cout << "Nhap ma sinh vien: ";
				fflush(stdin);
				cin >> id;
				auto student = GlobalVariable::studentM->searchById(id);
				if (student != nullptr) {
					student->displayInfo();
				}
				else {
					cout << "Ma sinh vien khong ton tai!\n";
				}
				pressAnyKeyToContinue();
			}
			break;
			}
		} while (choose != GlobalVariable::parentM->menuItems.size());


		break;
	}

	return 0;
}




int menu(string title, vector<string> menuItems)
{
	string line = "========================================";
	cout << line << endl << endl;
	cout << " " << title << endl << endl;
	cout << line << "\n\n";
	int i = 1;
	for (auto item : menuItems)
	{
		cout << " " << i++ << ". " << item << endl;
	}
	cout << endl << line << endl;
	int choose = 0;
	cout << endl << "Nhap lua chon: ";
	fflush(stdin);
	cin >> choose;

	while (choose <1 || choose > menuItems.size()) {
		cout << "Nhap sai, vui long nhap lai: ";
		fflush(stdin);
		cin >> choose;
	}
	return choose;
}

void pressAnyKeyToContinue()
{
	cout << "Bam phim bat ki de tiep tuc...";
	_getch();
	cout << "\n\n";
}

void showListStudent(vector<Student*> students) {
	string line = "========================================================================================";
	cout << line << endl << endl;
	cout << " Danh sach sinh vien" << endl << endl;
	cout << line << endl;

	cout << "| " << std::setw(15) << std::left << "Ma sv" << " | ";
	cout << std::setw(20) << std::left << "Ho ten" << " | ";
	cout << std::setw(15) << std::left << "Lop" << " | ";
	cout << std::setw(15) << std::left << "So dien thoai" << " | ";
	cout << std::setw(7) << std::left << "Diem TB" << " |\n";
	for (auto student : students) {
		cout << "| " << std::setw(15) << std::left << student->id << " | ";
		cout << std::setw(20) << std::left << student->name << " | ";
		cout << std::setw(15) << std::left << student->className << " | ";
		cout << std::setw(15) << std::left << student->phone << " | ";
		cout << std::setw(7) << std::left << student->gpa << " |\n";
	}
	cout << line << endl << endl;

}

Person* login(string usename, string password)
{
	Person* person = GlobalVariable::teacherM->login(usename, password);
	if (person != nullptr) {
		return person;
	}
	person = GlobalVariable::parentM->login(usename, password);
	if (person != nullptr) {
		return person;
	}
	person = GlobalVariable::studentM->login(usename, password);
	return person;
}


