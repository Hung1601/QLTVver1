#include"book.h"
#include"person.h"
#include"book.cpp"
#include"person.cpp"
#include"file.cpp"

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


int main(){
    int choice;
    string username, password, currentPassword, newPassword;
    Student myStudent;
    Student* myStudentPtr = new Student;
    docfile1(hs, sach);
    docfile2(sf);
    bool isLoggedIn = false; // Biến xác định đang trong đăng nhập 
    bool isEdit = false; // Biến xác định đang trong quá trình chỉnh sửa
    while (true) {
        cout << "1. Dang ki\n";
        cout << "2. Dang nhap\n";
        cout << "3. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:

                cout << "Nhap ten dang nhap: ";
                cin >> username;
                cout << "Nhap mat khau: ";
                cin >> password;
                Register(myStudent, username, password);
                break;
                
            case 2:
                
                cout << "Nhap ten dang nhap: ";
                cin >> username;
                cout << "Nhap mat khau: ";
                cin >> password;
                if (Login(username, password)) {
                    cout << "Dang nhap thanh cong!" << endl << endl;

                    for (auto& student : hs) { // Xác định đối tượng đang sử dụng
                        if (student.Getaccount() == username && student.Getpassword() == password) {
                        myStudentPtr = &student;
                        break;
                        }
                    }

                    isLoggedIn = true;
                    while(isLoggedIn){
                    cout << "1. Tra cuu sach\n";
                    cout << "2. Thong tin nguoi dung\n";
                    cout << "3. Doi mat khau\n";
                    cout << "4. Dang xuat\n";
                    cout << "Nhap lua chon tiep theo: \n";
                    cin >> choice;
                    switch (choice){
                        case 1:
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

                        case 2:
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
                        
                        case 3: 
                            cout << "Nhap mat khau hien tai: ";
                            cin >> currentPassword;
                            cout << "Nhap mat khau moi: ";
                            cin >> newPassword;
                            changePassword(myStudentPtr, username, currentPassword, newPassword);
                            break;

                        case 4: 
                            isLoggedIn = false;
                            break;
                        default:
                            cout << "Lua chon khong hop le!\n";
                            break;
                        }
                    };
                }
            break; 
            case 3:
                return 0;
            default:
                cout << "Lua chon khong hop le!" << endl;
                break;
        }
    }
    delete myStudentPtr;
    return 0;
}