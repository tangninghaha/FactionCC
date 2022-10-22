/* header file */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <time.h>

using namespace std;

/* Predefined command */
/* Color */
#define Color_Red 4
#define Color_Blue 9
#define Color_Yellow 6
#define Color_Green 2
#define Color_Grey 8
#define Color_White 7

/* constant definition */
const int kFuncitons_num = 7;
const string kFuncitons_name[7] = {"Import", "Study", "Practice", "Find", "Translate", "Settings", "History"};
const int kMax_word = 10000001;

/* global variable */
string word_english[kMax_word], word_chinese[kMax_word];
int word_num = 0;

/* function declaration */
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

/* function definition */
void ReadWordFile()
{
    ifstream fin(".\\Data\\Word_num.ini");
    fin >> word_num;
    fin.close();
    fin.open(".\\Data\\Word_English.ini");
    for (int i = 1; i <= word_num; i++)
    {
        getline(fin, word_english[i]);
    }
    fin.close();
    fin.open(".\\Data\\Word_Chinese.ini");
    for (int i = 1; i <= word_num; i++)
    {
        getline(fin, word_chinese[i]);
    }
    fin.close();
}

int main()
{
    /* system("mode con cols=50 lines=25"); */
    printf("Start successfully...\n");
    clock_t file_time_start = clock();
    ReadWordFile();
    clock_t file_time_end = clock();
    printf("Read Files successfully\n");
    printf("use time: %lf(s)\n", (double)(file_time_end - file_time_start) / CLOCKS_PER_SEC);
    system("pause");
    Init();
    while (true)
    {
        int ret_num = Menu();
        if (ret_num == -1)
        {
            Init();
            SetColor(Color_Red);
            printf("[AD] Advertising space for rent\n");
            return 0;
        }
        if (!ret_num)
            continue;
        return ret_num;
    }
}

void Init()
{
    system("cls");
    SetColor(Color_Grey);
    printf("Version: v0.0.1\n");
    printf("Welcome to FactionCC!\n\n");
    SetColor(Color_White);
}

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Menu()
{
    Init();
    printf("[0] Exit\n");
    for (int i = 0; i < kFuncitons_num; i++)
    {
        SetColor(Color_White);
        // Print the funcitons name
        printf("[%d] %s\n", i + 1, kFuncitons_name[i].c_str());
    }
    SetColor(Color_Red);
    printf("\nPay Attention! Only Function 0,1,3 can be used!\n\n");
    SetColor(Color_White);
    printf("Please input function number:\n");
    int input_funcitons;
    scanf("%d", &input_funcitons);
    int ret_num = 0;
    switch (input_funcitons)
    {
    case 0:
        ret_num = -1;
        break;
    case 1:
        Import();
        break;
    case 2:
        // Study();
        break;
    case 3:
        Practice();
        break;
    case 4:
        //            Find();
        break;
    case 5:
        //            Translate();
        break;
    case 6:
        //            Settings();
        break;
    case 7:
        //            History();
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

void Import()
{
    Init();
    string temp_english = "", temp_chinese = "";
    printf("Please input Engilsh:\n");
    SetColor(Color_Yellow);
    //    cin>>temp_english;
    getline(cin, temp_english);
    while (temp_english.empty())
    {
        getline(cin, temp_english);
    }
    SetColor(Color_White);
    printf("Please input Chinese:\n");
    SetColor(Color_Yellow);
    //    cin>>temp_chinese;
    getline(cin, temp_chinese);
    while (temp_chinese.empty())
    {
        getline(cin, temp_chinese);
    }
    SetColor(Color_White);
    Mkdir();
    ofstream fout(".\\Data\\Word_num.ini");
    fout << word_num + 1;
    word_num++;
    fout.close();
    fout.open(".\\Data\\Word_English.ini", ios::app);
    fout << temp_english << endl;
    fout.close();
    fout.open(".\\Data\\Word_Chinese.ini", ios::app);
    fout << temp_chinese << endl;
    fout.close();
}

void Mkdir()
{
    string folderPath = ".\\Data";
    if (0 != access(folderPath.c_str(), 0))
    {
        // if this folder not exist, create a new one.
        mkdir(folderPath.c_str());
    }
}

void Practice()
{
    srand(time(0));
    Init();
    SetColor(Color_Grey);
    printf("Input \"***\" to break\n\n");
    SetColor(Color_White);
    int num;
    printf("How many word do you want to practice?:\n");
    scanf("%d", &num);
    int guess_time;
    int t;
    string ans;
    for (int i = 1; i <= num; ++i)
    {
        guess_time = 0;
        SetColor(Color_Grey);
        printf("\nTest %d/%d\n", i, num);
        t = rand() % word_num + 1;
        SetColor(Color_White);
        printf("What \"");
        SetColor(Color_Green);
        printf("%s", word_chinese[t].c_str());
        SetColor(Color_White);
        printf("\" in English?\n");
    Again:
        SetColor(Color_Yellow);
        cin >> ans;
        if (ans == word_english[t])
        {
            SetColor(Color_White);
            printf("You are right\n");
            system("pause");
            getchar();
            continue;
        }
        else
        {
            SetColor(Color_Red);
            printf("You are wrong! Do you need some tips?\n");
            printf("[1] Answer again\n[2] Get some tips\n[3] Get the answer\n");
            SetColor(Color_White);
            int tmp;
            cin >> tmp;
            if (tmp == 1)
            {
                goto Again;
            }
            else if (tmp == 3)
            {
            Answer:
                SetColor(Color_White);
                printf("The answer is: ");
                SetColor(Color_Green);
                printf("%s\n", word_english[t].c_str());
                SetColor(Color_White);
                system("pause");
                getchar();
            }
            else if (tmp == 2)
            {
                ++guess_time;
                if (guess_time >= word_english[t].length())
                {
                    SetColor(Color_White);
                    printf("OK, I'll tell you the answer\n");
                    goto Answer;
                }
                SetColor(Color_White);
                printf("The first %d letters are: ", guess_time);
                SetColor(Color_Green);
                printf("%s\n", word_english[t].substr(0, guess_time).c_str());
                SetColor(Color_White);
                goto Again;
            }
        }
    }
}
