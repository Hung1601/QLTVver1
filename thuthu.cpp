#include"book.h"
#include"person.h"
#include"book.cpp"
#include"person.cpp"
#include"file.cpp"

void Register(Staff& s, string &username, string &password) {
    int i = 0;
    for(i=0;i<sizeof(sf);i++){  // Ki?m tra tài kho?n dã t?n t?i hay chua
        if(sf[i].Getaccount() == username){
            cout << "Tai khoan da ton tai " << endl;
            return;
        }
    }
    s.setAccount(username);
    s.setPassword(password);
    cout << "Dang ki thanh cong" << endl;
    s.set_info();
    sf.push_back(s);
    updateFile3(sf);
}

bool Login(const string username, string password){
    for(auto& staff : sf ){  // Ki?m tra tài kho?n, m?t kh?u 
        if(staff.Getaccount() == username && staff.Getpassword() == password){
            return true;
            break;
        }
    }
    cout << "Tai khoan hoac mat khau sai" << endl;
    return false;
}

void changePassword(Staff* &s, string username, string currentPassword, string newPassword) { // Ð?i m?t kh?u
    if (s->Getpassword() == currentPassword) { // Ki?m tra tài kho?n, m?t kh?u 
        for(auto& staff : hs ){  // C?p nh?t trong vector
            if(staff.Getaccount() == username ){
                staff.setPassword(newPassword);
            }
        }
        cout << "Doi mat khau thanh cong!" << endl;
        updateFile3(sf);
    } else {
        cout << "Sai mat khau hien tai! Khong the doi mat khau." << endl;
    }
}

int main(){

    Staff myStaff;
    Staff *myStaffPtr = new Staff;
    int choice;
    string username, password, currentPassword, newPassword;
    docfile1(hs, sach);
    docfile2(sf);
    bool isLoggedIn = false; // Bi?n xác d?nh dang trong dang nh?p 
    bool isSearch = false; // Bi?n xác d?nh dang trong quá trình ch?nh s?a

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
                Register(myStaff, username, password);
                break;
                
            case 2:
                
                cout << "Nhap ten dang nhap: ";
                cin >> username;
                cout << "Nhap mat khau: ";
                cin >> password;
                if(Login(username,password)){
                    isLoggedIn = true;

                    for (auto& staff : sf) { // Xác d?nh d?i tu?ng dang s? d?ng
                        if (staff.Getaccount() == username && staff.Getpassword() == password) {
                        myStaffPtr = &staff;
                        break;
                        }
                    }

                    cout << "Ban dang nhap voi tu cach admin" << endl << endl;
                    while(isLoggedIn){
                        cout << "1. Chinh sua thong tin" << endl;
                        cout << "2. Quan li sach" << endl;
                        cout << "3. Thong ke" <<  endl;
                        cout << "4. Tim kiem sinh vien" << endl;
                        cout << "5. Dang xuat" << endl;
                        cout << "Nhap lua chon tiep theo: \n";
                        cin >> choice;
                        switch (choice){
                        case 1:
                            myStaffPtr -> print_info(sach);
                            myStaffPtr -> editInfor();
                            break;
                        case 2:
                            myStaffPtr->bookManager(sach);
                            updateFile2(sach);
                            break;
                        case 3:
                            myStaffPtr->Statistical(sach, hs);
                            break;
                        case 4:
                            if(myStaff.searchUser(hs)){
                                isSearch = true;
                                while(isSearch){
                                    cout << "1. Xem thong tin chi tiet nguoi dung" << endl;
                                    cout << "2. Xoa tai khoan" << endl;
                                    cout << "3. Quay lai trang chu" << endl;
                                    cout << "Nhap lua chon tiep theo cua ban: \n";
                                    cin >> choice;
                                    switch (choice)
                                    {
                                    case 1:
                                        myStaffPtr -> print_infoUser(hs, sach); 
                                    break;
                                    case 2:
                                        myStaffPtr -> deleteUser(hs, sach); 
                                        updateFile1(hs);
                                    break;
                                    case 3: 
                                        isSearch = false;
                                    break;
                                    default:
                                        cout << "Lua chon khong hop le! " << endl;
                                    break;
                                    }
                                }
                            }
                            break;
                        case 5:
                            isLoggedIn = false;
                            break;
                        default:
                            cout << "Lua chon khong hop le!" << endl;
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
    delete myStaffPtr;
    return 0;
}