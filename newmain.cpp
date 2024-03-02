#include"classes.cpp"

int main() {
    char choice,choice1;
    string username, password;
    std::cout<< "Welcome to the app"<<endl;
    string i;
    int p;
    string temp;
    while(1){
        p=0;
        std::cout << "1. Customer\n2. Employee\n3. Manager\n4. Exit \nEnter your choice: ";
        std::getline(std::cin, j);
        if(hasSpaces_or_empty(j)){
            std::cout<<"Invalid input\n Input has spaces or is empty"<<endl;
            continue;
        }
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        choice1=j[0];
        switch(choice1){
            case '1':
                std::cout<<"Customer"<<endl;
                std::cout << "1. Register\n2. Login\nEnter your choice: ";
                std::getline(std::cin, j);
                if(j.size()!=1){
                std::cout<<"Invalid input for char"<<endl;
                continue;
                }
                choice=j[0];
                switch (choice) {
                    case '1':
                        Master_register("cust.csv");
                        break;
                    case '2':
                        temp=Master_login("cust.csv");
                        if(temp!="-1"){
                            Clear();
                            Custom(temp);
                            Clear();
                        }
                        break;
                    default:
                        std::cout << "Invalid choice!" << endl;
                        break;
                }
                break;
            case '2' :
                temp=Master_login("employees.csv");
                if(temp!="-1"){
                    Clear();
                    Employe(temp);
                    Clear();
                }
                break;
            case '3':
                temp=Master_login("manager.csv");
                if(temp!="-1"){
                    Clear();
                    master(temp);
                    Clear();
                }
                break;
            case '4':
                     p=1;
                     break;   
            default:
                std::cout<<"Invalid choice!"<<endl;
        }
        if(p==1){
            std::cout<<"Exiting"<<endl;
            break;
        }
        std::cout<<"You are logged out"<<endl;
        std::cout<<"Welcome to the app enter 0 to exit any other key to continue"<<endl;
        std::getline(std::cin,i);
        if(i=="0") break;
    }
    Clear();
    std::cout<<"Thank You!!"<<endl;
    return 0;
}