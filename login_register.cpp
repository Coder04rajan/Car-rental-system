#include"read_write_display_funcs.cpp"

int usernameExists(const string& username, const string& filename) {
    int y;
    y=readfile(filename);
    if(y==0) return 0;
    int x=content.size();
    for(int i=0;i<x;i++){
        if(content[i][1]==username) return -1;
    }
    return stoi(content[x-1][0]);
}

void registerUser(const string& username, const string& password,const string& email,const string& DL, const string& filename,int id) {
    ofstream file(filename, ios::app);
    string a=to_string(id+1);
    string c;
    file <<a<<","<< username << "," << password<<","<<email<<",3.5,0,0,0,0,0,0,0,C,"<<DL<<endl;
    file.close();
    std::cout << "Registration successful!" << endl;
}

bool login(const string& username, const string& password, const string& filename) {
    int i=readfile(filename);
    if(i==0) return false;
    int flag=0;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==username && content[i][2]==password){
            content.clear();
            return true;
        }
    }
    content.clear();
    return false;
}

void Master_register(string filename){
    string username,password,email,DL,temp;
    std::cout << "Enter username: "<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return;
    }
    username=j;
    int id;
    id=usernameExists(username,filename);
    if (id==-1) {
    std::cout << "Username already exists!" << endl;
    } 
    else {
    std::cout << "Enter password: "<<endl;
     std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return;
    }
    password=j;
    std::cout << "Re-enter password: "<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return;
    }
    temp=j;
    if(temp!=password){
        std::cout<<"passwords don't match\n redirecting back to home page"<<endl;
        return;
    }
    std::cout<<"Enter email: "<<endl;
     std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return;
    }
    if(!isValidEmail(j)){
        std::cout<<"Invalid email id"<<endl;
        return;
    }
    email=j;
    std::cout<<"Enter Driving Lisence Number: "<<endl;
     std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return;
    }
    DL=j;
    registerUser(username, password,email,DL,filename,id);
    }
}

string Master_login(string filename){
    string username,password;
    std::cout << "Enter username: ";
     std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return "-1";
    }
    username=j;
    std::cout << "Enter password: ";
     std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
        return "-1";
    }
    password=j;
    if (login(username, password,filename)) {
        std::cout << "Login successful!" << endl;
        return username;
    } 
    else {
        std::cout << "Invalid username or password!" << endl;
        return "-1";
    }
}