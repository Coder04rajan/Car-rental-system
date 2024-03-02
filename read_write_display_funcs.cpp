#include"header.hpp"
int readfile(string fname){
    vector<string> row;
    content.clear();
    string line, word;

    fstream file (fname,ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) row.push_back(word);
            content.push_back(row);
        }
        if(content.empty()){
            std::cout<<"It is an empty file\n";
            return 0;
        }
        return 1;
    }
    else std::cout<<"Could not open the file\n";
    return 0;
}
void writefile(vector<vector<string>> par, string fname){  
    fstream fout(fname,ios::out);
    for(auto x:par){
        for(auto y:x){
            fout<<y;
            if(y!=x.back()) fout<<",";
        }
        fout<<"\n";
    }

}
void writefileappend(vector<string> par, string fname){  
    fstream fout(fname,ios::out | ios::app);
    for(auto x:par){
        fout<<x;
        if(x!=par.back()) fout<<",";
    }
    fout<<"\n";
}
void Table(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& headers) {
    if(data.size()==0){
        std::cout<<"No data to display"<<endl;
        return;
    }
    std::vector<size_t> columnWidths(headers.size(), 0);
    for (size_t i = 0; i < headers.size(); ++i) {
        columnWidths[i] = headers[i].size();
    }
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i].size() > columnWidths[i]) {
                columnWidths[i] = row[i].size();
            }
        }
    }
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << std::setw(columnWidths[i] + 2) << std::left << headers[i];
    }
    std::cout << std::endl;
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << std::setw(columnWidths[i] + 2) << std::left << row[i];
        }
        std::cout << std::endl;
    }
}
void Clear()
{
#if defined _WIN32
    system("cls");
    // clrscr(); // including header file : conio.h
#elif defined(_LINUX) || defined(gnu_linux) || defined(linux_)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(_APPLE_)
    system("clear");
#endif
}