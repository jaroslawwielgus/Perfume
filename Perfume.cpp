#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

// in the below procedures name of parameters are different than in int main() to show that they don't have to be the same like in int main(), because these variables are local
void show_all(string** array, int rows_no) // procedure takes as a parameter dynamic two-dimensional array of strings (perfume) and number of rows, then it goes / loops through rows and columns and shows perfume
{
    for (int i = 0; i < rows_no; i++) // sizeof(perfume) / sizeof(perfume[0]) - theoretically it shouldn't work, but in reality works
    {
        for (int j = 0; j < 7; j++) // sizeof(perfume[0]) / sizeof(perfume[0][0]) - theoretically it shouldn't work, but in reality works
        {
            cout << array[i][j] + " ";
        }
        cout << endl;
    }
}

void show_of_chosen_gender(string** array, int rows_no, string gender_or_unisex) // procedure takes as a parameter dynamic two-dimensional array of strings (perfume), number of rows and string "m" or "k" or "u"
{
    for (int i = 0; i < rows_no; i++)  // we go / loop through rows
    {
        if (array[i][3] == gender_or_unisex) // when gender in perfume array matches the gender provided by user then we go / loop through all columns and show values in array
        {
            for (int j = 0; j < 7; j++)
            {
                cout << array[i][j] + " ";
            }
            cout << endl;
        }
    }
}

void show_of_chosen_gender_and_price_range(string** array, int rows_no, string gender_or_unisex, string price_range) // procedure takes as a parameter dynamic two-dimensional array of strings (perfume), number or rows, string "m" or "k" or "u" and price range 
{
    for (int i = 0; i < rows_no; i++) // we go / loop through rows
    {
        //string gender_or_unisex_string(1, gender_or_unisex);
        //string budget_string(1, budget);
        if (array[i][3] == gender_or_unisex && array[i][4] == price_range) // when gender and price range in perfume array matches gender and price range which user gave, then we go / loop through all columns and we show values in array (here all variables of the same type are compared so it is string because in price range is a lot of characters)   
        {   
            for (int j = 0; j < 7; j++)
            {
                cout << array[i][j] + " ";
            }
            cout << endl;
        }
    }
}

void show_of_chosen_gender_price_range_and_type(string** array, int rows_no, string gender_or_unisex, string price_range, string type) // analogically but there are also type/category of perfume
{
    for (int i = 0; i < rows_no; i++)
    {
        if (array[i][3] == gender_or_unisex && array[i][4] == price_range && array[i][2] == type)
        {
            for (int j = 0; j < 7; j++)
            {
                cout << array[i][j] + " ";
            }
            cout << endl;
        }
    }
}

void show_of_chosen_gender_price_range_type_and_season(string** array, int rows_no, string gender_or_unisex, string price_range, string type, string season) // analogically but there are also type/category of perfume and season 
{
    for (int i = 0; i < rows_no; i++)
    {
        if (array[i][3] == gender_or_unisex && array[i][4] == price_range && array[i][2] == type && array[i][6] == season) //if (perfume[i][3] == gender_or_unisex_string && perfume[i][4] == range && perfume[i][2] == category && perfume[i][5] == company && perfume[i][6] == period)
        {
            for (int j = 0; j < 7; j++)
            {
                cout << array[i][j] + " ";
            }
            cout << endl;
        }
    }
}

void open_file(ifstream& csv_file) // procedure open_file takes a reference to ifstream (&csv_file) object because it wants to modify state of the object and it wants to have access to original object instead of his copy
{
    csv_file.open("C:\\Users\\Uzytkownik\\Desktop\\perfume.csv", ios::in); // we open file which is located in desktop in program input mode, that is to reading file   
    if (csv_file.good() == false) // if we couldn't find file
    {
        cout << "Nie udalo sie otworzyc pliku!";
        exit(0);  // finish program
    }
}




int main()
{
    string line;
    int lines_no = 0;
    ifstream file; // changed type of variable

    open_file(file); // we open file

    while (getline(file, line)) // we extract lines of text while it is true that lines exist
    {
        // cout << line << endl;
        ++lines_no; // in this while we count number of lines of file
    }

    file.close(); // we close file

    int array_size = lines_no;  // number of rows in array is number of lines in file
    string** perfume = NULL; // perfume is dynamic two-dimensional array of strings (perfume is pointer to pointers chain characters set on NULL initially)
    perfume = new string * [array_size]; // memory allocation for array_size pointers to chains characters

    for (int i = 0; i < array_size; i++)
    {
        perfume[i] = new string[7]; // for each pointer there is allocated strings array which size is 7 (number of columns is 7) 
    }

    lines_no = 0; // we set number of lines to 0 because we will read file once again  
    open_file(file); // we read file once again because we want to go to the its beginning because we came to its end earlier 

    // determination of number of columns on the basis of semicolon number
    getline(file, line); // we catch single line from the file
    int columns_no = 1; // Columns counter starts from 1

    // Counting of number of columns - in columns number there will be included also end semicolons which separate rows
    for (char character : line)
    {
        if (character == ';')
        {
            ++columns_no;
        }
    }

    file.close(); // we close file

    open_file(file); // we open file


    while (getline(file, line))  // this while loop will read and split lines from file
    {
        size_t pos = line.find_last_not_of(";"); // Checking if line ends with ";;;;;;;;;;;;;"
        if (pos != string::npos && pos >= line.length() - 9)
        {
            line = line.substr(0, pos + 1); // line ends with ";;;;;;;;;;;;;"
        }

        istringstream line_stream(line); // Creating stringstream stream to split lines into values

        string* values = new string[columns_no]; // creating array to store values for current line

        for (int i = 0; i < columns_no; i++) // Reading values and adding them to array
        {
            getline(line_stream, values[i], ';');
        }

        perfume[lines_no] = values; // Adding values array to matrix

        ++lines_no;
    }

    file.close(); // we close file

    file.open("C:\\Users\\Uzytkownik\\Desktop\\perfume.csv", ios::in); // we open file
    int col_no = 7; // number of columns is 7

    for (int i = 0; i < lines_no; i++) // this for deletes space from the beginning of the strings, at the beginning we go through rows   
    {
        getline(file, line);
        stringstream ss(line);
        for (int j = 0; j < columns_no; j++) // we go / loop through columns
        {

            getline(ss, perfume[i][j], ';');

            // Delete spaces from the beginning of each string
            size_t start = perfume[i][j].find_first_not_of(' ');
            if (start != string::npos)
            {
                perfume[i][j].erase(0, start);
            }
        }
    }

    file.close(); // we close file


    char gender;
    char gender_or_unisex;
    char show_or_not_1;
    char show_or_not_2;

    cout << "Witaj w perfumerii!" << endl;
    cout << "Czy chcesz wyswietlic wszystkie perfumy(t - tak, n - nie): ";
    cin >> show_or_not_1;
    if (show_or_not_1 == 't')
    {
        cout << endl;
        show_all(perfume, lines_no); // we are calling procedure which will show all perfume
        cout << endl;
    }
    cout << "Podaj plec osoby dla ktorej szukasz perfum (m - mezczyzna, k - kobieta): ";
    cin >> gender;
    switch (gender)
    {
    case 'm':
        cout << "Czy to maja byc perfume meskie czy unisex? Wpisz m dla meskich albo u dla unisex: ";
        break;
    case 'k':
        cout << "Czy to maja byc perfume kobiece czy unisex? Wpisz k dla kobiecych albo u dla unisex: ";
        break;
    }
    cin >> gender_or_unisex;
    string gender_or_unisex_string(1, gender_or_unisex); // from varaiable of type char it changes to type string so there is 1
    cout << "Czy chcesz wyswietlic perfume spelniajace kryterium? (t - tak, n - nie): ";
    cin >> show_or_not_2;
    if (show_or_not_2 == 't')
    {
        cout << endl;
        show_of_chosen_gender(perfume, lines_no, gender_or_unisex_string); // we call function which will show perfume with chosen gender or unisex
        cout << endl;
    }

    char budget;
    char show_or_not_3;
    string range;
    cout << "Podaj swoj budget (a - 0-100zl, b - 100-200zl, c - 200-300zl, d - 300-500zl, e - 500-1000zl, f - 1000-2000zl): ";
    cin >> budget;

    switch (budget)
    {
    case 'a':
        range = "0-100zl";
        break;
    case 'b':
        range = "100-200zl";
        break;
    case 'c':
        range = "200-300zl";
        break;
    case 'd':
        range = "300-500zl";
        break;
    case 'e':
        range = "500-1000zl";
        break;
    case 'f':
        range = "1000-2000zl";
        break;
    }

    cout << "Czy chcesz wyswietlic perfume spelniajace kryterium? (t - tak, n - nie): ";
    cin >> show_or_not_3;
    if (show_or_not_3 == 't')
    {
        cout << endl;
        show_of_chosen_gender_and_price_range(perfume, lines_no, gender_or_unisex_string, range); // we call procedure which will show perfume with chosen gender and price range
        cout << endl;
    }

    char type;
    string category;
    char show_or_not_4;
    cout << "Podaj typ perfum (a - aromatyczno-przyprawowe, b - aromatyczno-wodne, c - bursztynowe, d - cytrusowo-aromatyczne, e - drzewno-aromatyczne, f - drzewno-kwiatowo, g - drzewno-przyprawowe, h - kwiatowo-owocowe, i - kwiatowo-owocowo-gourmand, j - orientalno-drzewne, k - orientalno-fougere, l - orientalno-kwiatowe, m - orientalno-przyprawowe, n - orientalno-waniliowe, o - skorzane, p - szyprowo-kwiatowe, r - szyprowo-owocowe): ";
    cin >> type;
    switch (type)
    {
    case 'a':
        category = "aromatyczno-przyprawowe";
        break;
    case 'b':
        category = "aromatyczno-wodne";
        break;
    case 'c':
        category = "bursztynowe";
        break;
    case 'd':
        category = "cytrusowo-aromatyczne";
        break;
    case 'e':
        category = "drzewno-aromatyczne";
        break;
    case 'f':
        category = "drzewno-kwiatowo";
        break;
    case 'g':
        category = "drzewno-przyprawowe";
        break;
    case 'h':
        category = "kwiatowo-owocowe";
        break;
    case 'i':
        category = "kwiatowo-owocowo-gourmand";
        break;
    case 'j':
        category = "orientalno-drzewne";
        break;
    case 'k':
        category = "orientalno-fougere";
        break;
    case 'l':
        category = "orientalno-kwiatowe";
        break;
    case 'm':
        category = "orientalno-przyprawowe";
        break;
    case 'n':
        category = "orientalno-waniliowe";
        break;
    case 'o':
        category = "skorzane";
        break;
    case 'p':
        category = "szyprowo-kwiatowe";
        break;
    case 'r':
        category = "szyprowo-owocowe";
        break;
    }
    cout << "Czy chcesz wyswietlic perfumy spelniajace kryterium? (t - tak, n - nie): ";
    cin >> show_or_not_4;
    if (show_or_not_4 == 't')
    {
        cout << endl;
        show_of_chosen_gender_price_range_and_type(perfume, lines_no, gender_or_unisex_string, range, category); // we call function which will show perfume with chosen gender, price range and type
        cout << endl;
    }

    char season;
    string period;
    char show_or_not_6;
    cout << "Podaj pore roku (a - zima-jesien, b - wiosna-lato): ";
    cin >> season;
    switch (season)
    {
    case 'a':
        period = "zima-jesien";
        break;
    case 'b':
        period = "wiosna-lato";
        break;
    }

    cout << "Czy chcesz wyswietlic perfumy spelniajace kryterium? (t - tak, n - nie): ";
    cin >> show_or_not_6;
    if (show_or_not_6 == 't')
    {
        cout << endl;
        show_of_chosen_gender_price_range_type_and_season(perfume, lines_no, gender_or_unisex_string, range, category, period); // we call procedure which will perfumes with chosen gender, price range, type and season
        cout << endl;
    }


    return 0;
}

// Test data:
// 1. m, m, d, j, a
// 2. m, u, e, g, a
// 3. k, k, d, l, a

















