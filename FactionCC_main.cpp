//header file

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <direct.h>

using namespace std;


//Predefined command
//Color
#define Color_Red 4
#define Color_Blue 9
#define Color_Yellow 6
#define Color_Green 2
#define Color_Grey 8
#define Color_White 7


//constant definition
const int kFuncitons_num = 7;
const string kFuncitons_name[7] = {"Import", "Study", "Practice", "Find", "Translate", "Settings", "History"};
const int kMax_word = 100001;


//global variable
string word_english[kMax_word], word_chinese[kMax_word];
int word_num = 0, no_study_num = 0;
bool is_study[kMax_word];


//function declaration
int main();
void Init();
void SetColor(int);
int Menu();

void Import();
void Study();
void Practice();
void Find();
void Translate();
void Settings();
void History();

void ReadWordFile();
void Mkdir();


//function definition
void ReadWordFile() {
    ifstream fin(".\\Data\\Word_num.ini");
    fin>>word_num;
    fin.open(".\\Data\\Word_English.ini");
    for(int i = 1; i <= word_num; i++) {
        getline(fin, word_english[i]);
    }
    fin.close();
    fin.open(".\\Data\\Word_Chinese.ini");
    for(int i = 1; i <= word_num; i++) {
        getline(fin, word_chinese[i]);
    }
    fin.close();
    fin.open(".\\Data\\Word_study.ini");
    fin>>no_study_num;
    for(int i = 1; i <= word_num; i++) {
        fin>>is_study[i];
    }
}

int main() {
    system("mode con cols=50 lines=25");
    ReadWordFile();
    Init();
    while(true) {
        int ret_num = Menu();
        if(ret_num == -1) return 0;
        if(!ret_num) continue;
        return ret_num;
    }
}

void Init() {
    system("cls");
    SetColor(Color_Grey);
    printf("Welcome to FactionCC!\n\n");
    SetColor(Color_White);
}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Menu() {
    Init();
    printf("[0] Exit\n");
    for(int i = 0; i < kFuncitons_num; i++) {
        SetColor(Color_White);
        //Print the funcitons name
        printf("[%d] %s\n", i + 1, kFuncitons_name[i].c_str());
    }
    printf("Please input function number:\n");
    int input_funcitons;
    scanf("%d", &input_funcitons);
    int ret_num = 0;
    switch(input_funcitons) {
        case 0:
            ret_num = -1;
            break;
        case 1 :
            Import();
            break;
        case 2:
            Study();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            SetColor(Color_Red);
            printf("Error input!\n");
            SetColor(Color_White);
            Sleep(1000);
            ret_num = 0;
            break;
    }
    return ret_num;
}

void Import() {
    Init();
    string temp_english = "", temp_chinese = "";
    printf("Please input Engilsh:\n");
    SetColor(Color_Yellow);
//    cin>>temp_english;
    getline(cin, temp_english);
    if(temp_english.empty()) {
        getline(cin, temp_english);
    }
    SetColor(Color_White);
    printf("Please input Chinese:\n");
    SetColor(Color_Yellow);
//    cin>>temp_chinese;
    getline(cin, temp_chinese);
    SetColor(Color_White); 
    Mkdir();
    ofstream fout(".\\Data\\Word_num.ini");
    fout<<word_num + 1;
    word_num++;
    fout.close();
    fout.open(".\\Data\\Word_English.ini", ios::app);
    fout<<temp_english<<endl;
    fout.close();
    fout.open(".\\Data\\Word_Chinese.ini", ios::app);
    fout<<temp_chinese<<endl;
    fout.close();
}

void Mkdir() {
    string folderPath = ".\\Data";
    if (0 != access(folderPath.c_str(), 0)) {
        // if this folder not exist, create a new one.
        mkdir(folderPath.c_str());
    }
}

void Study() {
    Init();
    if(!word_num) {
       SetColor(Color_Red);
       printf("There is no word in the files!\n");
       SetColor(Color_White);
       Sleep(1000);
       return;
    }
    if(!no_study_num) {
        SetColor(Color_Red);
        printf("No not learn words!\n");
        SetColor(Color_White);
        Sleep(1000);
        return;
    }
    
}
