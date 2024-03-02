#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<regex>
using namespace std;

vector<vector<string>> content;
vector<string> toupdate;
std::string j;
vector<vector<string>> disp;
vector<string> head_user= {"user_id","username","password","email","elig_score","dues","number of cars","car 1","car 2","car 3","car 4","car 5","type","DL"};
vector<string> head_car={"Vehicle number","Make","Date","Cost_per_day","fine_per_day","current_user","condition","rental_status","transmission","fuel_type"};

bool hasSpaces_or_empty(const std::string& str);
bool isValidEmail(const std::string& email);
bool isValidFloat(const std::string& str);
bool isValidInteger(const std::string& str);
bool isLeapYear(int year);
bool isValidDate(const std::string& dateStr);
std::time_t stringToTime(const std::string& dateStr);
int dateDifferenceInDays(const std::string& date1Str, const std::string& date2Str);
std::string getCurrentDateAsString();
void Clear();
void Table(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& headers);
int readfile(string fname);
void writefile(vector<vector<string>> par, string fname);
void writefileappend(vector<string> par, string fname);
int usernameExists(const string& username, const string& filename);
void registerUser(const string& username, const string& password,const string& email,const string& DL, const string& filename,int id);
bool login(const string& username, const string& password, const string& filename);
void Master_register(string filename);
string Master_login(string filename);
void Custom(string username);
void Employe(string username);
void master(string username);

class User{
    protected:
        string pwd;
    public:
        string type;
        int user_id;
        float elig;
        int count;
        int dues;
        string DL;
        string rented_cars[5];
        string name;
        string email;
        void update_pwd(string New);
        void update_self();
        void view_self();
        void view_cars();
        void view_cars_available();
        void view_cars_rented();
        void search_car_model();
        void search_car_par();
        void return_car();
        void clear_dues();
        void user_menu();
        bool delete_self();
        void gen_book(User*ptr);
};
class Customer: public User{
    public:
        void book_car(User*ptr);
};
class Employee: public User{
    public:
        void book_car(User*ptr);
};
class Manager: public User{
    public:
        void admin_menu();
        void view_users();//emp or cust list of usernames
        void search_users();//find user and gives the data of that user
        void update_user();//update menu for different parameters
        void delete_user();//finds type and username and deletes the user
        void update_car();//updates the car characteristics
        void delete_car();
        void add_car();
        void add_user();
        void admin_view_cars();
        void admin_search_car();
        void admin_update_self();
        void add_admin();
};