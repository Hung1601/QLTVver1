#include"book.h"
#include"person.h"
#include"book.cpp"
#include"person.cpp"
#include"file.cpp"
#include<conio.h>

void Register(Student& st, string &username, string &password) {
    int i = 0;
    for(i=0;i<size(hs);i++){  // Kiểm tra tài khoản đã tồn tại hay chưa
        if(hs[i].Getaccount() == username){
            cout << "Tai khoan da ton tai! " << endl;
            return;
        }
    }
    st.setAccount(username);
    st.setPassword(password);
    cout << "Dang ki thanh cong!" << endl;
    int newId = hs.back().GetID() + 1;
    st.setID(newId);
    st.set_info();
    hs.push_back(st);
    updateFile1(hs);
}

bool Login(const string username, string password){
    for(auto& student : hs ){  // Kiểm tra tài khoản, mật khẩu 
        if(student.Getaccount() == username && student.Getpassword() == password){
            return true;
            break;
        }
    }
    cout << "Tai khoan hoac mat khau sai" << endl;
    return false;
}

void changePassword(Student* &st, string username, string currentPassword, string newPassword) { // Đổi mật khẩu
    if (st->Getpassword() == currentPassword) { // Kiểm tra tài khoản, mật khẩu 
        for(auto& student : hs ){  // Cập nhật trong vector
            if(student.Getaccount() == username ){
                student.setPassword(newPassword);
            }
        }
        cout << "Doi mat khau thanh cong!" << endl;
        updateFile1(hs);
    } else {
        cout << "Sai mat khau hien tai! Khong the doi mat khau." << endl;
    }
}

void displayMenu1(char choice) {
    system("cls"); 
    std::cout << "Library System:" << std::endl;
    if (choice == '1') {
        std::cout << "\033[1;31m"; 
    }
    std::cout << "1. Dang ky tai khoan" << std::endl;
    std::cout << "\033[0m"; 

    if (choice == '2') {
        std::cout << "\033[1;32m";
    }
    std::cout << "2. Dang nhap " << std::endl;
    std::cout << "\033[0m"; 

    if (choice == '3') {
        std::cout << "\033[1;34m"; 
    }
    std::cout << "3. Thoat" << std::endl;
    std::cout << "\033[0m";

}

void displayMenuCustom1(char choice)
{
	system("cls"); 
    if (choice == '1') {
        std::cout << "\033[1;31m"; 
    }
    std::cout << "1. Tra cuu sach" << std::endl;
    std::cout << "\033[0m"; 

    if (choice == '2') {
        std::cout << "\033[1;32m";
    }
    std::cout << "2. Thong tin nguoi dung" << std::endl;
    std::cout << "\033[0m"; 

    if (choice == '3') {
        std::cout << "\033[1;33m"; 
    }
    std::cout << "3. Doi mat khau" << std::endl;
    std::cout << "\033[0m";
    
    if (choice == '4') {
        std::cout << "\033[1;34m"; 
    }
    std::cout << "4. Dang xuat" << std::endl;
    std::cout << "\033[0m";

}

int main()
{
    
    string username, password, currentPassword, newPassword;
    Student myStudent;
    Student* myStudentPtr = new Student;
    docfile1(hs, sach);
    docfile2(sf);
    bool isLoggedIn = false; // Biến xác định đang trong đăng nhập 
    bool isEdit = false; // Biến xác định đang trong quá trình chỉnh sửa
    
    char choice = '1';
    char keyPressed;

    while (true) 
    {
        displayMenu1(choice);
        keyPressed = _getch(); 
        switch (keyPressed) 
        {
            case 72: 
                choice = (choice == '1') ? '3' : static_cast<char>(choice - 1);
                break;
            case 80:
                choice = (choice == '3') ? '1' : static_cast<char>(choice + 1);
                break;
            case 13:
                switch(choice)
            {
            case '1':{
                system("cls");
                std::string username, password;
                std::cout << "Nhap ten dang nhap: ";
                std::cin >> username;
                std::cout << "Nhap mat khau: ";
                std::cin >> password;
                Register(myStudent, username, password);
                break;
                }
            case '2':
                system("cls");
                cout << "Nhap ten dang nhap: ";
                cin >> username;
                cout << "Nhap mat khau: ";
                cin >> password;

                if (Login(username, password)) 
                    {
                    isLoggedIn = true;
                    for (auto& student : hs) { // Xác định đối tượng đang sử dụng
                        if (student.Getaccount() == username && student.Getpassword() == password) 
                        {
                        myStudentPtr = &student;
                        break;
                        }
                    }
                

                    while(isLoggedIn)
                    {
							displayMenuCustom1(choice);
						    
					        keyPressed = _getch();
					        switch (keyPressed) 
							{
					            case 72: 
					                choice = (choice == '1') ? '4' : static_cast<char>(choice - 1);
					                break;
					            case 80:
					                choice = (choice == '4') ? '1' : static_cast<char>(choice + 1);
					                break;
                                case 13: 
                                    switch (choice)
                                    {
                                           case '1':
                                                  system("cls");
                                                  cout << "Cac sach hien co : " << endl; // Phần này học sau
                                                  cout << left << setw(8) << "ID"<< setw(41) << "Ten" << setw(24) << "The loai" << setw(25) << "Tac gia" << setw(25) << "So luong" << endl;
                                                  cout << setfill('-') << setw(99) << "-" << setfill(' ') << endl;

                                                  for (book& b : sach) {
                                                  b.display();
                                                  }
                                                  if(myStudentPtr->searchBook(sach)){
                                                  myStudentPtr->borrowBook(sach);
                                                  updateFile1(hs);
                                                  updateFile2(sach); 
                                                    }else{
                                                 break;
                                                    }            
                                                 break;

                                            case '2':
                                                 system("cls");
                                                 cout << "Thong tin hien tai nguoi dung: \n";
                                                 myStudentPtr->print_info(sach);
                                                 isEdit = true;
                                                 while(isEdit){
                                                 cout << "1. Chinh sua thong tin" << endl;
                                                 cout << "2. Tra sach" << endl;
                                                 cout << "3. Quay tro lai trang chu" << endl;
                                                 cin >> choice;
                                                 switch (choice)
                                               {
                                                 case 1:
                                                 myStudentPtr->editInformation();
                                                 updateFile1(hs);
                                                 updateFile2(sach);
                                                 break;
                                                 case 2:
                                                 myStudentPtr->returnBook(sach);
                                                 updateFile1(hs);
                                                 updateFile2(sach);
                                                 case 3:
                                                 isEdit = false;
                                                 break;
                                                default:
                                                cout << "Lua chon khong hop le!" << endl;
                                                break;
                                               }
                                            }
                                             break;
                        case '3': 
                            system("cls");
                            cout << "Nhap mat khau hien tai: ";
                            cin >> currentPassword;
                            cout << "Nhap mat khau moi: ";
                            cin >> newPassword;
                            changePassword(myStudentPtr, username, currentPassword, newPassword);
                            break;

                        case '4': 
                            isLoggedIn = false;
                            break;
                        default:
                            cout << "Lua chon khong hop le!\n";
                            break;
                            }
                    
                        }
                    }
            break; 
            case 3:
                return 0;
            default:
                cout << "Lua chon khong hop le!" << endl;
                break;
            }
        }
    }
    }
    delete myStudentPtr;
    return 0;
}    
        