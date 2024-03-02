#include"login_register.cpp"
#include"date_time.cpp"
#include"checks.cpp"

void User::update_self(){
    std::cout<<"updating profile"<<endl;
    char choice;
    string temp;
    int index;
    int y;
    if(this->type=="C") y=readfile("cust.csv");
    else y=readfile("employees.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(to_string(this->user_id)==content[i][0]){
            index=i;
            break;
        }
    }
    int flag=0;
    int foo;
    while(1){
        flag=0;
        std::cout<<"---------------------------------------------------------------------------------------------"<<endl;
        std::cout<<"1.change pwd\n2.email_id\n3.name\n4.DL\n5.exit\n";
        std::getline(std::cin, j);
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        choice=j[0];
        switch(choice){
            case '1':
                std::cout<<"Enter new password"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    return;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    return;
                }
                temp=j;
                this->update_pwd(temp);
                content[index][2]=temp;
                break;
            case '2':
                std::cout<<"Enter new email_id"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidEmail(j)){
                    std::cout<<"Invalid email"<<endl;
                    continue;
                }
                temp=j;
                this->email=temp;
                content[index][3]=temp;
                break;
            case '3':
                std::cout<<"Enter new name"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    return;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    return;
                }
                temp=j;
                foo=0;
                for(int i=0;i<content.size();i++){
                    if(content[i][1]==temp){
                        foo=1;
                        std::cout<<"Name already exists"<<endl;
                        break;
                    }
                }
                if(foo==1) break;
                this->name=temp;
                content[index][1]=temp;
                break;
            case '4':
                std::cout<<"Enter new DL"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    return;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    return;
                }
                temp=j;
                this->DL=temp;
                content[index][13]=temp;
                break;
            case '5':
                flag=1;
                break;
            default:
                std::cout<<"Invalid input"<<endl;
                break;
        }
        if(flag==1) break;
    }
    if(this->type=="C") writefile(content,"cust.csv");
    else writefile(content,"employees.csv");
    std::cout<<"redirecting to user menu"<<endl;
}

bool User::delete_self(){
    int y;
    if(this->count!=0){
        std::cout<<"Can't delete as has rented cars. Try again after returning the cars"<<endl;
        return false;
    }
    if(this->dues!=0){
        std::cout<<"Can't delete as has outstanding dues. Try again after clearing them"<<endl;
        return false;
    }
    std::cout<<"You can delete your account. This action is irreversible.\n Do you still want to delete your account.\n Press y to do so."<<endl;
    string temp;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return false;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return false;
    }
    temp=j;
    if(temp!="y"){
        std::cout<<"Cancelling delete"<<endl;
        return false;
    }
    if(this->type=="C") y=readfile("cust.csv");
    else y=readfile("employees.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]==to_string(this->user_id)){
            content.erase(content.begin()+i);
            break;
        }
    }
    if(this->type=="C") writefile(content,"cust.csv");
    else writefile(content,"employees.csv");
    return true;
}

void User::update_pwd(string New){
    this->pwd=New;
}

void User:: view_self(){
    std::cout<<"Your data is:"<<endl;
    int y;
    if(this->type=="C"){
        y=readfile("cust.csv");
        if(y==0) return;
    }
    else{
        y=readfile("employees.csv");
        if(y==0) return;
    }
    for(int i=0;i<content.size();i++){
        if(content[i][0]==to_string(this->user_id)){
            disp.push_back(content[i]);
            std::cout<<"------------------------------------------------------"<<endl;
            Table(disp,head_user);
            std::cout<<"------------------------------------------------------"<<endl;
            disp.clear();
            break;
        }
    }
    std::cout<<"redirecting to user menu"<<endl;
}

void User::view_cars(){
    std::cout<<"printing all cars"<<endl;
    string c;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    std::cout<<"------------------------------------------------------"<<endl;
    Table(content,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    content.clear();
    std::cout<<"Do you want to book a car. Press y if yes"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    c=j;
    if(c=="y") this->gen_book(this);
    else  std::cout<<"redirecting to user menu"<<endl;
}

void User:: view_cars_available(){
    std::cout<<"printing all available cars"<<endl;
    int y;
    string o;
    y=readfile("cars.csv");
    if(y==0) return;
    int c=1;
    for(int i=0;i<content.size();i++){
        if(content[i][7]=="0") disp.push_back(content[i]);
    }
    std::cout<<"------------------------------------------------------"<<endl;
    Table(disp,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    disp.clear();
    std::cout<<"Do you want to book a car (y/n)"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    o=j[0];
    if(o=="y") this->gen_book(this);
    else  std::cout<<"redirecting to user menu"<<endl;
}

void User::search_car_par(){
    std::cout<<"searching for cars enter D in the fields not needed"<<endl<<"Enter the transmission required: "<<endl;
    string trans,fuel;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    trans=j;
    std::cout<<"Enter the fuel type required: "<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    fuel=j;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    int c=1;
    for(int i=0;i<content.size();i++){
        if((trans=="D"?true:content[i][8]==trans)&&(fuel=="D"?true:content[i][9]==fuel)){
            c=0;
            disp.push_back(content[i]);
        }
    }
    std::cout<<"------------------------------------------------------"<<endl;
    Table(disp,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    disp.clear();
    if(c==1) std::cout<<"No such model found"<<endl;
    std::cout<<"Redirecting to user menu"<<endl;
}

void User::search_car_model(){
    std::cout<<"searching for cars"<<endl<<"Enter the model: "<<endl;
    string temp;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    int c=1;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==temp){
            c=0;
            disp.push_back(content[i]);
        }
    }
    std::cout<<"------------------------------------------------------"<<endl;
    Table(disp,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    disp.clear();
    if(c==1) std::cout<<"No such model found"<<endl;
    std::cout<<"Redirecting to user menu"<<endl;
}

//The user pays a fine equal to day rent of car per unit damage while returning it with a damage of less than the orginal damage

void User::return_car(){
    if(this->count==0){
         std::cout<<"You have no cars currently rented"<<endl;
         std::cout<<"redirecting to user menu"<<endl;
         return;
    }
    string emp_name,emp_pwd;
    std::cout<<"returning car"<<endl;
    std::cout<<"enter employee name for verification"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_name=j;
    if(emp_name==this->name){
        std::cout<<"enter different employee's name"<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"enter employee pwd for return"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_pwd=j;
    int f=0;
    int y;
    y=readfile("employees.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==emp_name && content[i][2]==emp_pwd){
            std::cout<<"employee verification done"<<endl;
            f=1;
            break;
        }
    }
    if(f==0){
        std::cout<<"incorrect emp_name or password. Try again "<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"Enter the car_id of the car returning"<<endl;
    string car_id,condition,due_date,curr;
    int delay;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    car_id=j;
    std::cout<<"Enter the date of returning"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    curr=j;
    if(!isValidDate(curr)){
        std::cout<<"Invalid date try again"<<endl;
        return;
    }
    y=readfile("cars.csv");
    if(y==0) return;
    std::cout<<"enter condition score of the car from 1-5"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidInteger(j)){
        std::cout<<"invalid integer number"<<endl;
        return;
    }
    condition=j;
    if(stoi(condition)>=5||stoi(condition)<=0){
        std::cout<<"invalid condition entered"<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    int flag=0;
    int index;
    for(int i=0;i<4;i++){
        if(this->rented_cars[i]==car_id){
            this->rented_cars[i]="0";
            this->count--;
            int x;
            for(int i=0;i<content.size();i++){
                if(content[i][0]==car_id){
                    due_date=content[i][2];
                    delay=dateDifferenceInDays(curr,due_date);
                    if(delay==-1){
                        std::cout<<"You are returning the car in prior"<<endl;
                        delay=0;
                    }
                    x=stoi(content[i][4])*delay;
                    if(stoi(condition)<stoi(content[i][6])){
                        x-=stoi(content[i][3])*(stoi(condition)-stoi(content[i][6]));
                        if(this->elig>0) this->elig+=0.2*(stoi(condition)-stoi(content[i][6]));
                    }
                    content[i][6]=condition;
                    if(this->elig>0) this->elig-=0.1*delay;
                    std::cout<<"Your fine is "<<x<<endl;
                    this->dues+=x;
                    std::cout<<"The car is returned"<<endl;
                    content[i][5]="0";
                    content[i][7]="0";
                    content[i][2]="0";
                }
            }
            writefile(content,"cars.csv");
            content.clear();
            flag=1;
            index=i;
            break;
        }
    }
    if(flag==0){
        std::cout<<"Invalid car_id"<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    else{
         if(this->type=="E"){
            y=readfile("employees.csv");
            if(y==0) return;
         }
         else if (this->type=="C"){
            y=readfile("cust.csv");
            if(y==0) return;
         }
         for(int i=0;i<content.size();i++){
            if(content[i][0]==to_string(this->user_id)){
                if(content[i][4]==to_string(this->elig)){
                    if(this->elig<5) this->elig+=0.02;
                }
                content[i][index+7]="0";
                content[i][6]=to_string(this->count);
                content[i][4]=to_string(this->elig);
                content[i][5]=to_string(this->dues);
                break;
            }
        }
        if(this->type=="E") writefile(content,"employees.csv");
        else if (this->type=="C") writefile(content,"cust.csv");
    }
    std::cout<<"redirecting to user menu"<<endl;
}

void User::clear_dues(){
    std::cout<<"Dues are "<<this->dues<<endl;
    int y;
    string emp_name,emp_pwd;
    std::cout<<"enter employee name for verification"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_name=j;
    if(emp_name==this->name){
        std::cout<<"enter different employee's name"<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"enter employee pwd for return"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_pwd=j;
    int f=0;
    y=readfile("employees.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==emp_name && content[i][2]==emp_pwd){
            std::cout<<"employee verification done"<<endl;
            f=1;
            break;
        }
    }
    if(f==0){
        std::cout<<"incorrect emp_name or password. Try again "<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    while(1){
        std::cout<<"Do you want to clear them (y/n)?"<<endl;
        string c;
        std::getline(std::cin, j);
        if(hasSpaces_or_empty(j)){
            std::cout<<"Input has spaces or is empty. Invalid"<<endl;
            return;
        }
        c=j;
        if(c=="y"){
            this->dues=0;
            if(this->type=="C"){
                y=readfile("cust.csv");
                if(y==0) return;
                for(int i=0;i<content.size();i++){
                    if(content[i][0]==to_string(this->user_id)){
                        content[i][5]="0";
                        break;
                    }
                }
                writefile(content,"cust.csv");
            }
            else if(this->type=="E"){
                y=readfile("employees.csv");
                if(y==0) return;
                for(int i=0;i<content.size();i++){
                    if(content[i][0]==to_string(this->user_id)){
                        content[i][5]="0";
                        break;
                    }
                }
                writefile(content,"employees.csv");
            }
            std::cout<<"Dues are cleared"<<endl;
            break;
        }
        else if(c=="n"){
            std::cout<<"Refused to clear"<<endl;
            break;
        }
        else std::cout<<"invalid input"<<endl;
    }
    std::cout<<"redirecting to user menu"<<endl;
}

void User::view_cars_rented(){
    std::cout<<"Rented cars are"<<endl;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][5]==this->type+to_string(this->user_id)) disp.push_back(content[i]);
    }
    std::cout<<"------------------------------------------------------"<<endl;
    Table(disp,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    disp.clear();
    std::cout<<"redirecting to user menu"<<endl;
}

void User::gen_book(User*ptr){
    string emp_name,emp_pwd;
    std::cout<<"enter employee name for verification"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_name=j;
    if(emp_name==this->name){
        std::cout<<"enter different employee's name"<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"enter employee pwd for return"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    emp_pwd=j;
    int f=0;
    int y;
    y=readfile("employees.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==emp_name && content[i][2]==emp_pwd){
            std::cout<<"employee verification done"<<endl;
            f=1;
            break;
        }
    }
    if(f==0){
        std::cout<<"incorrect emp_name or password. Try again "<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    if(ptr->type=="C"){
        Customer C;
        C.book_car(ptr);
    }
    else{
        Employee E;
        E.book_car(ptr);
    }
}

void Customer::book_car(User*ptr){
    if(ptr->count>=int(ptr->elig)||ptr->count>4){
        std::cout<<"You are ineligible to buy a car.\n Contact the manager"<<endl;
        std::cout<<"You can only rent a maximum of\t"<<int(ptr->elig)<<"cars"<<"Your elig score is\t"<<ptr->elig<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"Enter the car_id of the car you want to book"<<endl;
    string temp,date,curr;
    int num_days;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    std::cout<<"Enter due date in DD/MM/YYYY format "<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    date=j;
    if(date==getCurrentDateAsString()){
        std::cout<<"Date same as present date error"<<endl;
        return;
    }
    if(isValidDate(date)){
        curr=getCurrentDateAsString();
        num_days=dateDifferenceInDays(date,curr);
    }
    else{
        std::cout<<"Invalid date"<<endl;
        return;
    }
    int cost;
    int flag=0;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==temp){
            flag=1;
            if(content[i][7]=="1"){
                std::cout<<"Car is booked"<<endl;
                break;
            }
            std::cout<<"the price is: "<<stoi(content[i][3])*num_days<<endl;
            while(1){
                std::cout<<"enter 1 to pay 0 to exit"<<endl;
                char c;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    return;
                }
                c=j[0];
                if(c=='0'){
                    std::cout<<"Payment failed"<<endl;
                    break;
                }
                else if(c=='1'){
                    std::cout<<"payment done"<<endl;
                    content[i][7]="1";
                    content[i][5]="C"+to_string(ptr->user_id);
                    content[i][2]=date;
                    writefile(content,"cars.csv");
                    content.clear();
                    for(int i=0;i<5;i++){
                        if(ptr->rented_cars[i]=="0"){
                            ptr->rented_cars[i]=temp;
                            break;
                        }
                    }
                    ptr->count++;
                    y=readfile("cust.csv");
                    if(y==0) return;
                    for(int j=0;j<content.size();j++){
                        if(content[j][0]==to_string(ptr->user_id)){
                            for(int k=7;k<=11;k++){
                                if(content[j][k]=="0"){
                                    content[j][k]=temp;
                                    break;
                                }
                            }
                            content[j][6]=to_string(ptr->count);
                            break;
                        }
                    }
                    writefile(content,"cust.csv");
                    break;
                }
                else{
                    std::cout<<"Invalid input"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0){
        std::cout<<"car not found"<<endl;
    }
    std::cout<<"redirecting to user menu"<<endl;
}

void Employee::book_car(User*ptr){
    if(ptr->count>=int(ptr->elig)||ptr->count>4){
        std::cout<<"You are ineligible to buy a car. Contact the manager"<<endl;
        std::cout<<"You can only rent a maximum of\t"<<int(ptr->elig)<<"cars"<<"Your elig score is\t"<<ptr->elig<<endl;
        std::cout<<"redirecting to user menu"<<endl;
        return;
    }
    std::cout<<"Enter the car_id of the car you want to book"<<endl;
    string temp,date,curr;
    int num_days;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    std::cout<<"Enter due date in DD/MM/YYYY format"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    date=j;
    if(date==getCurrentDateAsString()){
        std::cout<<"Date same as present date error"<<endl;
        return;
    }
    if(isValidDate(date)){
        curr=getCurrentDateAsString();
        num_days=dateDifferenceInDays(date,curr);
    }
    else{
        std::cout<<"Invalid date"<<endl;
        return;
    }
    int cost;
    int flag=0;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==temp){
            flag=1;
            if(content[i][7]=="1"){
                std::cout<<"Car is booked"<<endl;
                break;
            }
            std::cout<<"the price with discount is: "<<stoi(content[i][3])*num_days*0.85<<endl;
            while(1){
                std::cout<<"enter 1 to pay 0 to exit"<<endl;
                char c;
                std::getline(std::cin, j);
                c=j[0];
                if(c=='0'){
                    std::cout<<"Payment failed"<<endl;
                    break;
                }
                else if(c=='1'){
                    std::cout<<"payment done"<<endl;
                    content[i][7]="1";
                    content[i][5]="E"+to_string(ptr->user_id);
                    content[i][2]=date;
                    writefile(content,"cars.csv");
                    content.clear();
                    for(int i=0;i<5;i++){
                        if(ptr->rented_cars[i]=="0"){
                            ptr->rented_cars[i]=temp;
                            break;
                        }
                    }
                    ptr->count++;
                    y=readfile("employees.csv");
                    if(y==0) return;
                    for(int j=0;j<content.size();j++){
                        if(content[j][0]==to_string(ptr->user_id)){
                            for(int k=7;k<=11;k++){
                                if(content[j][k]=="0"){
                                    content[j][k]=temp;
                                    break;
                                }
                            }
                            content[j][6]=to_string(stoi(content[j][6])+1);
                            break;
                        }
                    }
                    writefile(content,"employees.csv");
                    break;
                }
                else{
                    std::cout<<"Invalid input"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0){
        std::cout<<"car not found"<<endl;
    }
    std::cout<<"redirecting to user menu"<<endl;
}

void User::user_menu(){
    while(1){
        int flag=0;
        std::cout<<"Welcome"<<endl;
        std::cout<<"Read the following choices and type the one needed"<<endl;
        std::cout<<"--------------------------------------------------------------------------------------------"<<endl;
        std::cout<<"1.View cars\n2.View available cars\n3.View rented cars\n4.Search for a car on its model\n5.Return a car\n6.Clear Dues\n7.Show dues\n8.Show self data\n9.Book car\nv.view cars based on parameters\nu.update self\nd.delete account\nl.Logout"<<endl;
        char c;
        std::getline(std::cin, j);
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        c=j[0];
        switch(c){
            case '1':
                this->view_cars();
                break;
            case '2':
                this->view_cars_available();
                break;
            case '3':
                this->view_cars_rented();
                break;
            case '4':
                this->search_car_model();
                break;
            case '5':
                this->return_car();
                break;
            case '6':
                this->clear_dues();
                break;
            case '7':
                std::cout<<"The dues are\t"<<this->dues<<endl;
                break;
            case '8':
                this->view_self();
                break;
            case 'v':
                this->search_car_par();
                break;
            case 'u':
                this->update_self();
                break;
            case 'd':
                if(this->delete_self()==false) break;
                std::cout<<"deleted your account"<<endl;
                flag=1;
                break;
            case 'l':
                std::cout<<"Logging out!!"<<endl;
                flag=1;
                break;
            case '9':
                this->gen_book(this);
                break;
            default:
                std::cout<<"Invalid input";
                break;
        }
        if(flag==1) break;
    }
    std::cout<<"Logged out"<<endl;
}

void Manager::view_users(){
    std::cout<<"Enter E to view employees and C to view customers"<<endl;
    string c;
    int y;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    c=j;
     if(c=="E"){ 
        y=readfile("employees.csv");
        if(y==0) return;
    }
    else if(c=="C"){ 
        y=readfile("cust.csv");
        if(y==0) return;
    }
    else{
        std::cout<<"Invalid input"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    std::cout<<"--------------------------------------------------------------------------------------"<<endl;
    Table(content,head_user);
    std::cout<<"--------------------------------------------------------------------------------------"<<endl;
    std::cout<<"Going back to menu"<<endl;
}

void Manager:: search_users(){
    std::cout<<"Enter E to view employees and C to view customers"<<endl;
    char c;
    int y;
    string temp;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()!=1){
        std::cout<<"Invalid input for char"<<endl;
        return;
    }
    c=j[0];
    std::cout<<"Enter name to search"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
     if(c=='E'){ 
        y=readfile("employees.csv");
        if(y==0) return;
    }
    else if(c=='C'){ 
        y=readfile("cust.csv");
        if(y==0) return;
    }
    else{
        std::cout<<"Invalid input"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    int flag=0;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==temp){
            flag=1;
            disp.push_back(content[i]);
            std::cout<<"------------------------------------------------------"<<endl;
            Table(disp,head_user);
            std::cout<<"------------------------------------------------------"<<endl;
            disp.clear();
            std::cout<<endl;
            break;
        }
    }
    if(flag==0) std::cout<<"user not found"<<endl;
    std::cout<<"Going back to menu"<<endl;
}

void Manager::update_user(){
    std::cout<<"Enter E to update employees and C to update customers"<<endl;
    char c;
    string temp;
    int val;
    int y;
    float num;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()!=1){
        std::cout<<"Invalid input for char"<<endl;
        return;
    }
    c=j[0];
    std::cout<<"Enter name to update"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    if(c=='E'){ 
        y=readfile("employees.csv");
        if(y==0) return;
    }
    else if(c=='C'){ 
        y=readfile("cust.csv");
        if(y==0) return;
    }
    else{
        std::cout<<"Invalid input"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    int flag=0;
    int index;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==temp){
            flag=1;
            index=i;
        }
    }
    if(flag==0){
        std::cout<<"User not found"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    int f=0;
    while(1){
        f=0;
        std::cout<<"Update menu"<<endl;
        std::cout<<"--------------------------------------------------------------------------"<<endl;
        std::cout<<"1.email\n2.elig_score\n3.fine due\n4.DL number\n5.password\n6.name\n7.exit and write to file\n8.discard changes\n";
        char choice;
        int foo;
        std::getline(std::cin, j);
        if(hasSpaces_or_empty(j)){
            std::cout<<"Input has spaces or is empty. Invalid"<<endl;
            continue;
        }
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        choice=j[0];
        switch(choice){
            case '1':
                std::cout<<"Enter new email"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidEmail(j)){
                    std::cout<<"Invalid email"<<endl;
                    continue;
                }
                temp=j;
                content[index][3]=temp;
                break;
            case '5':
                std::cout<<"Enter new password"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                content[index][2]=temp;
                break;
            case '4':
                std::cout<<"Enter new DL number"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                content[index][13]=temp;
                break;
            case '2':
                std::cout<<"enter new elig_score"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidFloat(j)){
                    std::cout<<"invalid float number"<<endl;
                    continue;
                }
                num=stof(j);
                if(num<=5 && num>=0){
                    content[index][4]=to_string(num);
                }
                break;
            case '3':
                std::cout<<"enter new dues";
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidInteger(j)){
                    std::cout<<"invalid integer number"<<endl;
                    continue;
                }
                val=stoi(j);
                content[index][5]=to_string(val);
                break;
            case '6':
                std::cout<<"Enter new name"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                foo=0;
                for(int i=0;i<content.size();i++){
                    if(content[i][1]==temp){
                        foo=1;
                        std::cout<<"Name already exists"<<endl;
                        break;
                    }
                }
                if(foo==1) break;
                content[index][1]=temp;
                break;
            case '7':
                f=1;
                break;
            case '8':
                std::cout<<"Going back to menu"<<endl;
                return;
            default:
                std::cout<<"Invalid choice"<<endl;
                break;
        }
        if(f==1) break;
    }
    if(c=='E') writefile(content,"employees.csv");
    else if(c=='C') writefile(content,"cust.csv");
    std::cout<<"Going back to menu"<<endl;
}

void Manager::delete_user(){
    std::cout<<"Enter E to delete employees and C to delete customers"<<endl;
    char c;
    int y;
    string temp;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()!=1){
        std::cout<<"Invalid input for char"<<endl;
        return;
    }
    c=j[0];
    std::cout<<"Enter name to delete"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    if(c=='E'){ 
        y=readfile("employees.csv");
        if(y==0) return;
    }
    else if(c=='C'){ 
        y=readfile("cust.csv");
        if(y==0) return;
    }
    else{
        std::cout<<"Invalid input"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    int flag=0;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==temp){
            flag=1;
            content.erase(content.begin()+i);
            std::cout<<"deleted"<<endl;
            break;
        }
    }
    if(flag==0){
        std::cout<<"user not found"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    if(c=='E') writefile(content,"employees.csv");
    else if(c=='C') writefile(content,"cust.csv");
    //updating the cars.csv file if customer has rented any cars at present...
    y=readfile("cars.csv");
    if(y==0){
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    for(int i=0;i<content.size();i++){
        if(content[i][5]==temp){
            content[i][5]="0";
            content[i][2]="0";
            content[i][7]="0";
        }
    }
    writefile(content,"cars.csv");
    std::cout<<"Going back to menu"<<endl;
}

void Manager::delete_car(){
    string temp;
    std::cout<<"Enter car_id to delete"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    int flag=0;
    string name;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==temp){
            flag=1;
            name=content[i][5];
            content.erase(content.begin()+i);
            std::cout<<"deleted"<<endl;
            break;
        }
    }
    writefile(content,"cars.csv");
    if(flag==0){
        std::cout<<"car not found"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    //updating customers or employees who have this car as rented
    int found=0;
    y=readfile("cust.csv");
    if(y!=0){
        for(int i=0;i<content.size();i++){
            if(content[i][1]==name){
                found=1;
                content[i][6]=to_string(stoi(content[i][6])-1);
                for(int j=0;i<5;j++){
                    if(content[i][7+j]==temp) content[i][7+j]="0";
                }
                break;
            }
        }
    }
    writefile(content,"cust.csv");
    if(found==0){
        y=readfile("employees.csv");
        if(y!=0){
            for(int i=0;i<content.size();i++){
                if(content[i][1]==name){
                    found=1;
                    content[i][6]=to_string(stoi(content[i][6])-1);
                    for(int j=0;i<5;j++){
                        if(content[i][7+j]==temp) content[i][7+j]="0";
                    }
                    break;
                }
            }
        }
    }
    writefile(content,"employees.csv");
    std::cout<<"Going back to menu"<<endl;
}

void Manager::update_car(){
    string temp;
    int val;
    std::cout<<"Enter car_id to update"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    int flag=0;
    int index;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==temp){
            flag=1;
            index=i;
        }
    }
    if(flag==0){
        std::cout<<"Car not found"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    int f,foo;
    while(1){
        f=0;
        std::cout<<"Update menu"<<endl;
        std::cout<<"--------------------------------------------------------------------------"<<endl;
        std::cout<<"\n1.model\n2.date of return\n3.Cost\n4.Fine\n5.condition\n6.Car_id\n7.Transmission\n8.Fuel type\n9.exit and write changes\n0.discard changes\n";
        char choice;
        std::getline(std::cin, j);
        if(hasSpaces_or_empty(j)){
            std::cout<<"Input has spaces or is empty. Invalid"<<endl;
            continue;
        }
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        choice=j[0];
        switch(choice){
            case '1':
                std::cout<<"Enter new model"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                content[index][1]=temp;
                break;
            case '2':
                std::cout<<"enter new due date"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                if(!isValidDate(temp)){
                    std::cout<<"Invalid date entered"<<endl;
                    break;
                }
                content[index][2]=temp;
                break;
            case '3':
                std::cout<<"enter new cost"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidInteger(j)){
                    std::cout<<"invalid integer number"<<endl;
                    continue;
                }
                val=stoi(j);
                content[index][3]=to_string(val);
                break;
            case '4':
                std::cout<<"enter new fine"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidInteger(j)){
                    std::cout<<"invalid integer number"<<endl;
                    continue;
                }
                val=stoi(j);
                content[index][4]=to_string(val);
                break;
            case '5':
                std::cout<<"Enter new condition"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                if(!isValidInteger(j)){
                    std::cout<<"invalid integer number"<<endl;
                    continue;
                }
                val=stoi(j);
                if(val<0 || val>5){
                    std::cout<<"invalid input"<<endl;
                    break;
                }
                content[index][6]=to_string(val);
                break;
            case '6':
                std::cout<<"Enter new car_id"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                foo=0;
                for(int i=0;i<content.size();i++){
                    if(content[i][0]==temp){
                        foo=1;
                        std::cout<<"Name already exists"<<endl;
                        break;
                    }
                }
                if(foo==1) break;
                content[index][1]=temp;
                break;
            case '7':
                std::cout<<"Type in the transmission of the car.\n Enter automatic or manual in lower case"<<endl;
                std::getline(std::cin,j);
                if(j!="automatic" && j!="manual"){
                    std::cout<<"invalid input"<<endl;
                    return;
                }
                temp=j;
                content[index][8]=temp;
                break;
            case '8':
                std::cout<<"Type in the fuel type\n Enter petrol or diesel or EV or CNG or hybrid"<<endl;
                std::getline(std::cin,j);
                if(j!="petrol" && j!="diesel" && j!="EV" && j!="CNG" && j!="hybrid"){
                    std::cout<<"invalid input"<<endl;
                    return;
                }
                temp=j;
                content[index][9]=temp;
                break;
            case '9':
                f=1;
                break;
            case '0':
                std::cout<<"Going back to menu"<<endl;
                return;
            default:
                std::cout<<"Invalid choice"<<endl;
                break;
        }
        if(f==1) break;
    }
    writefile(content,"cars.csv");
    std::cout<<"Going back to menu"<<endl;
}

void Manager::add_car(){
    std::cout<<"Adding a car"<<endl;
    string car_id,model,trans,fuel;
    int cost,fine,condition;
    std::cout<<"Enter the car_id"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    car_id=j;
    int y;
    y=readfile("cars.csv");
    if(y==1){
        for(int i=0;i<content.size();i++){
            if(content[i][0]==car_id){
                std::cout<<"Car already exists"<<endl;
                return;
            }
        }
    }
    std::cout<<"Enter the model"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    model=j;
    std::cout<<"Enter the cost"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidInteger(j)){
        std::cout<<"invalid integer number"<<endl;
        return;
    }
    cost=stoi(j);
    std::cout<<"Enter the fine"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidInteger(j)){
        std::cout<<"invalid integer number"<<endl;
        return;
    }
    fine=stoi(j);
    std::cout<<"Enter the condition"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidInteger(j)){
        std::cout<<"invalid integer number"<<endl;
        return;
    }
    condition=stoi(j);
    if(condition<1||condition>5){
        std::cout<<"invalid condition"<<endl;
        return;
    }
    std::cout<<"Type in the transmission of the car.\n Enter automatic or manual in lower case"<<endl;
    std::getline(std::cin,j);
    if(j!="automatic" && j!="manual"){
        std::cout<<"invalid input"<<endl;
        return;
    }
    trans=j;
    std::cout<<"Type in the fuel type\n Enter petrol or diesel or EV or CNG or hybrid"<<endl;
    std::getline(std::cin,j);
    if(j!="petrol" && j!="diesel" && j!="EV" && j!="CNG" && j!="hybrid"){
        std::cout<<"invalid input"<<endl;
        return;
    }
    fuel=j;
    vector<string>par;
    par.push_back(car_id);
    par.push_back(model);
    par.push_back("0");
    par.push_back(to_string(cost));
    par.push_back(to_string(fine));
    par.push_back("0");
    par.push_back(to_string(condition));
    par.push_back("0");
    par.push_back(trans);
    par.push_back(fuel);
    writefileappend(par,"cars.csv");
    std::cout<<"Going back to menu"<<endl;
}

void Manager:: add_user(){
    std::cout<<"Enter E to add employees and C to add customers"<<endl;
    char c;
    int y;
    float elig;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()!=1){
        std::cout<<"Invalid input for char"<<endl;
        return;
    }
    c=j[0];
    if(c=='C') readfile("cust.csv");
    else if(c=='E') readfile("employees.csv");
    else{
        std::cout<<"Invalid input"<<endl;
        std::cout<<"Going back to menu"<<endl;
        return;
    }
    string username,password,email,DL;
    std::cout<<"Enter the name"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    username=j;
    y=readfile("employees.csv");
    if(y==1){
        for(int i=0;i<content.size();i++){
            if(content[i][1]==username){
                std::cout<<"User already exists"<<endl;
                return;
            }
        }
    }
    std::cout<<"Enter the password"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    password=j;
    std::cout<<"Enter the email"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidEmail(j)){
        std::cout<<"Invalid email"<<endl;
        return;
    }
    email=j;
    std::cout<<"Enter the DL"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    DL=j;
    std::cout<<"Enter the elig_score"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    if(!isValidFloat(j)){
        std::cout<<"invalid float number"<<endl;
        return;
    }
    elig=stof(j);
    if(elig<0||elig>5){
        std::cout<<"invalid "<<endl;
        return;
    }
    vector<string>par;
    par.push_back("1");
    par.push_back(username);
    par.push_back(password);
    par.push_back(email);
    par.push_back(to_string(elig));
    par.push_back("0");
    par.push_back("0");
    par.push_back("0");
    par.push_back("0");
    par.push_back("0");
    par.push_back("0");
    par.push_back("0");
    par.push_back("C");
    par.push_back(DL);
    int id=1;
    int x=content.size();
    if(x!=0) id=stoi(content[x-1][0])+1;
    par[0]=to_string(id);
    if(c=='E'){
        par[12]="E";
        writefileappend(par,"employees.csv");
    }
    else writefileappend(par,"cust.csv");
    std::cout<<"written to database"<<endl;
    std::cout<<"Going back to menu"<<endl;
}

void Manager::admin_view_cars(){
    std::cout<<"printing all cars"<<endl;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    std::cout<<"------------------------------------------------------"<<endl;
    Table(content,head_car);
    std::cout<<"------------------------------------------------------"<<endl;
    std::cout<<"redirecting to user menu"<<endl;
}

void Manager::admin_search_car(){
    std::cout<<"searching for cars"<<endl<<"Enter the model: ";
    string temp;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    temp=j;
    int y;
    y=readfile("cars.csv");
    if(y==0) return;
    int c=1;
    int index;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==temp){
            std::cout<<"Your model has been found"<<endl;
            c=0;
            disp.push_back(content[i]);
            std::cout<<"------------------------------------------------------"<<endl;
            Table(disp,head_car);
            std::cout<<"------------------------------------------------------"<<endl;
            disp.clear();
            std::cout<<endl;
            break;
        }
    }
    if(c==1) std::cout<<"No such model found"<<endl;
    std::cout<<"Redirecting to admin menu"<<endl;
}

void Manager::add_admin(){
    string username,password;
    std::cout<<"Enter the name"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    username=j;
    int y;
    y=readfile("manager.csv");
    if(y==1){
        for(int i=0;i<content.size();i++){
            if(content[i][1]==username){
                std::cout<<"User already exists"<<endl;
                return;
            }
        }
    }
    std::cout<<"Enter the password"<<endl;
    std::getline(std::cin, j);
    if(hasSpaces_or_empty(j)){
        std::cout<<"Input has spaces or is empty. Invalid"<<endl;
        return;
    }
    if(j.size()>30){
        std::cout<<"Too long input. Invalid"<<endl;
        return;
    }
    password=j;
    vector<string>par;
    par.push_back(to_string(stoi(content[content.size()-1][0])+1));
    par.push_back(username);
    par.push_back(password);
    std::cout<<"Added admin"<<endl;
    writefileappend(par,"manager.csv");
}

void Manager:: admin_menu(){
    int flag=0;
    while(1){
        flag=0;
        std::cout<<"Welcome to Admin menu"<<endl;
        std::cout<<"Read the following choices and type the one needed"<<endl;
        std::cout<<"--------------------------------------------------------------------------------------------"<<endl;
        std::cout<<"1.View users\n2.Search users\n3.Update users\n4.Delete users\n5.Add users\n6.Update car\n7.Delete car\n8.Add car\n9.show cars\nu.update self\na.add admin\ns.search car\nl.Logout"<<endl;
        char c;
        std::getline(std::cin, j);
        if(hasSpaces_or_empty(j)){
            std::cout<<"Input has spaces or is empty. Invalid"<<endl;
            continue;
        }
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        c=j[0];
        switch(c){
            case '1':
                this->view_users();
                break;
            case '2':
                this->search_users();
                break;
            case '3':
                this->update_user();
                break;
            case '4':
                this->delete_user();
                break;
            case '5':
                this->add_user();
                break;
            case '6':
                this->update_car();
                break;
            case '7':
                this->delete_car();
                break;
            case '8':
                this->add_car();
                break;
            case 'l':
                std::cout<<"Logging out!!"<<endl;
                Clear();
                flag=1;
                break;
            case '9':
                this->admin_view_cars();
                break;
            case 's':
                this->admin_search_car();
                break;
            case 'u':
                this->admin_update_self();
                break;
            case 'a':
                this->add_admin();
                break;
            default:
                std::cout<<"Invalid input";
                break;
        }
        if(flag==1) break;
    }
    std::cout<<"Logged out!!"<<endl;
}

void Manager::admin_update_self(){
    std::cout<<"Updating self"<<endl;
    char c;
    string temp;
    int y,index,flag;
    y=readfile("manager.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][1]==this->name){
            index=i;
            break;
        }
    }
    flag=0;
    while(1){
        std::cout<<"----------------------------------------------------------------------------------------"<<endl;
        std::cout<<"1.Name\n2.password\n3.exit\n";
        std::getline(std::cin,j);
        if(j.size()!=1){
            std::cout<<"Invalid input for char"<<endl;
            continue;
        }
        c=j[0];
        switch(c){
            case '1':
                std::cout<<"Enter the new name"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                for(int i=0;i<content.size();i++){
                if(content[i][1]==temp){
                    std::cout<<"User already exists"<<endl;
                    continue;
                    }
                }
                this->name=temp;
                content[index][1]=temp;
                break;
            case '2':
                std::cout<<"Enter the new password"<<endl;
                std::getline(std::cin, j);
                if(hasSpaces_or_empty(j)){
                    std::cout<<"Input has spaces or is empty. Invalid"<<endl;
                    continue;
                }
                if(j.size()>30){
                    std::cout<<"Too long input. Invalid"<<endl;
                    continue;
                }
                temp=j;
                this->update_pwd(temp);
                content[index][2]=temp;
                break;
            case '3':
                flag=1;
                break;
            default:
                std::cout<<"invalid choice"<<endl;
                break;
        }
        if(flag==1) break;
    }
    writefile(content,"manager.csv");
    std::cout<<"returning to admin menu"<<endl;
}

void Custom(string username){
    Customer C;
    int y;
    y=readfile("cust.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==username){
            C.user_id=stoi(content[i][0]);
            C.name=content[i][1];
            C.update_pwd(content[i][2]);
            C.email=content[i][3];
            C.elig=stof(content[i][4]);
            C.count=stoi(content[i][6]);
            C.dues=stoi(content[i][5]);
            C.rented_cars[0]=content[i][7];
            C.rented_cars[1]=content[i][8];
            C.rented_cars[2]=content[i][9];
            C.rented_cars[3]=content[i][10];
            C.rented_cars[4]=content[i][11];
            C.type=content[i][12];
            C.DL=content[i][13];
        }
    }
    content.clear();
    C.user_menu();
}

void Employe(string username){
    Employee C;
    int y;
    y=readfile("employees.csv");
    if(y==0) return;
    for(int i=0;i<content.size();i++){
        if(content[i][1]==username){
            C.user_id=stoi(content[i][0]);
            C.name=content[i][1];
            C.update_pwd(content[i][2]);
            C.email=content[i][3];
            C.elig=stof(content[i][4]);
            C.count=stoi(content[i][6]);
            C.dues=stoi(content[i][5]);
            C.rented_cars[0]=content[i][7];
            C.rented_cars[1]=content[i][8];
            C.rented_cars[2]=content[i][9];
            C.rented_cars[3]=content[i][10];
            C.rented_cars[4]=content[i][11];
            C.type=content[i][12];
            C.DL=content[i][13];
        }
    }
    C.user_menu();
}

void master(string username){
    Manager user;
    user.name=username;
    int y;
    y=readfile("manager.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]==username){
            user.update_pwd(content[i][1]);
            break;
        }
    }
    user.admin_menu();
}