#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;


string getDayOfWeek(int* dates){
    int q = dates[0];
    int m = dates[1];
    int k = dates[2] % 100;
    int j = dates[2] / 100;

    int h = (q + static_cast<int>(floor((13 * (m + 1)) / 5)) + k +
             static_cast<int>(floor(k / 4)) +
             static_cast<int>(floor(j / 4)) - 2 * j) % 7;

    string day_of_week;
    switch (h) {
        case 0: day_of_week = "Saturday"; break;
        case 1: day_of_week = "Sunday"; break;
        case 2: day_of_week = "Monday"; break;
        case 3: day_of_week = "Tuesday"; break;
        case 4: day_of_week = "Wednesday"; break;
        case 5: day_of_week = "Thursday"; break;
        case 6: day_of_week = "Friday"; break;
        default: day_of_week = "Unknown"; break;
    }
    return to_string(dates[0]) + "/" + to_string(dates[1]) + "/" + to_string(dates[2]) + " was on a " + day_of_week;

}

int* manageInput(){
    int day, month, year;
    string input;
    cout << "Enter date (dd/mm/yyyy): ";
    getline(cin, input);

    stringstream ss(input);
    ss >> day;
    if(ss.fail() or day < 1 or day > 31) {
        cout << "Invalid day" << endl;
        return reinterpret_cast<int *>(1);
    }
    ss.ignore();
    ss >> month;
    if(ss.fail() or month < 1 or month > 12) {
        cout << "Invalid month" << endl;
        return reinterpret_cast<int *>(1);
    }
    ss.ignore();
    ss >> year;
    if(ss.fail() or year < 0) {
        cout << "Invalid year" << endl;
        return reinterpret_cast<int *>(1);
    }

    if (month == 1 || month == 2) {
        year--;
        month += 12;
    }

    return new int[]{day, month, year};
}


int main() {

    cout << getDayOfWeek(manageInput()) << endl;
    main();
}
