/**
 * @file main.cpp
 * @brief This is a program that calculates the day of the week for a given date
 * @details This program takes a date in the format dd/mm/yyyy and calculates the day of the week
 * @author Leon Burghardt
 * @date 02/02/2023
 */

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <iomanip>

using namespace std;

/**
* @brief Convert HWND to string
* @param input HWND input to be converted
* @return converted string
*/
string HWNDToString(HWND input) {

    // declare output string and get length of input
    string output;
    size_t sizeTBuffer = GetWindowTextLength(input) + 1; // +1 for null terminator

    if (sizeTBuffer > 0) {
        output.resize(sizeTBuffer); // resize output to fit input
        sizeTBuffer = GetWindowText(input, &output[0], sizeTBuffer); // get input
    }

    return output; // return output
}


/**
* @brief Get day of the week from a date using Zeller's congruence
* @param dates date in array form (day, month, year)
* @return string containing date and the day of the week
*/
string getDayOfWeek(int *dates) {
    // Initialize variables for the day, month, last two digits of year, and first two digits of year
    int q = dates[0]; // day
    int m = dates[1]; // month
    int k = dates[2] % 100; // last two digits of year (years in the century ex. 2021 -> 21)
    int j = dates[2] / 100; // first two digits of year (century ex. 2021 -> 20)

    // If the month is January or February, add 12 to the month and subtract 1 from the year
    // This is because the algorithm only works for months March through December (m = 3, 4, ..., 12)
    if (m < 3) {
        m += 12;
        k--;
    }

    // Calculate h using Zeller's congruence formula
    int h = (q + (int) floor((13 * (m + 1)) / 5) + k +
             (int) floor(k / 4) +
             (int) floor(j / 4) - 2 * j) % 7;

    // more info on Zeller's congruence: https://en.wikipedia.org/wiki/Zeller%27s_congruence


    // Initialize string to store the day of the week
    string day_of_week;

    // Assign the day of the week based on the value of h
    switch (h) {
        case 0:
            day_of_week = "Saturday";
            break;
        case 1:
            day_of_week = "Sunday";
            break;
        case 2:
            day_of_week = "Monday";
            break;
        case 3:
            day_of_week = "Tuesday";
            break;
        case 4:
            day_of_week = "Wednesday";
            break;
        case 5:
            day_of_week = "Thursday";
            break;
        case 6:
            day_of_week = "Friday";
            break;
        default:
            day_of_week = "Unknown";
            break;
    }

    // Return the date and day of the week in a formatted string
    return to_string(dates[0]) + "/" + to_string(dates[1]) + "/" + to_string(dates[2]) + " was on a " +
           day_of_week;
}


/**
* @brief Manage input from user
* @param input input from user in the form of HWND
* @return string containing date and the day of the week
*/
string manageInput(HWND input) {
    // Convert the input Handle Window (HWND) to a string
    string inputString = HWNDToString(input);

    // Check if the input string is empty and display an error message if it is
    if (inputString.empty()) {
        MessageBox(nullptr, "Invalid input", "Error", MB_ICONEXCLAMATION);
        return "Error";
    }

    // Check if the input string has the right format (dd/mm/yyy)
    // input string has to be 11 characters long and has to have '/' characters at positions 2 and 5
    if (inputString.length() != 11 || inputString[2] != '/' || inputString[5] != '/') {
        MessageBox(nullptr, "Invalid input", "Error", MB_ICONEXCLAMATION);
        return "Error";
    }

    // Check if all characters in the input string are digits, excluding the '/' characters
    // excluding 10. character because it is the last character and can be a digit
    for (int i = 0; i < inputString.length(); ++i) {
        if (i == 2 || i == 5 || i == 10) continue;
        if (!isdigit(inputString[i])) {
            MessageBox(nullptr, "Invalid input", "Error", MB_ICONEXCLAMATION);
            return "Error";
        }
    }

    // Create an array to store the day, month, and year values from the input string
    int dates[3];

    // Use a string stream to extract the day, month, and year values from the input string
    int day, month, year;
    char delimiter1, delimiter2; // delimiters for the day, month, and year values

    stringstream ss(inputString); // create a string stream from the input string
    ss >> setw(2) >> setfill('0') >> day
       >> delimiter1 // set the width of the day value to 2 and fill the empty spaces with 0
       >> setw(2) >> setfill('0') >> month
       >> delimiter2 // set the width of the month value to 2 and fill the empty spaces with 0
       >> setw(4) >> setfill('0') >> year; // set the width of the year value to 4 and fill the empty spaces with 0

    // Store the extracted values in the dates array
    dates[0] = day;
    dates[1] = month;
    dates[2] = year;

    // Call the getDayOfWeek function with the dates array and return the result
    return getDayOfWeek(dates);
}


/**
 * @brief Create window and handle callbacks
 * @param hwnd
 * @param msg
 * @param wParam
 * @param lParam
 * @return
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: // A message to close the window
            DestroyWindow(hwnd); // Destroys the specified window
            break;
        case WM_DESTROY: // A message to destroy the window
            PostQuitMessage(0); // Posts a quit message to the message queue of the current thread
            break;
        case WM_COMMAND: // A message sent by a control
            if (LOWORD(wParam) == 2) { // Check if the control ID is 2
                HWND inputBar = GetDlgItem(hwnd, 1); // Get the handle of the control with ID 1
                string output = manageInput(inputBar); // Call the manageInput function and get the output
                if (output != "Error") { // If the output is not "Error"
                    MessageBox(nullptr, output.c_str(), "Date has been calculated",
                               MB_OK); // Display a message box with the output
                }
            }
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam,
                                 lParam); // Call the default window procedure to handle other messages
    }
    return 0;
}

/**
 * @brief Create window
 * @return
 */
int CreateWindowExample() {
    // Initialize the WNDCLASSEX structure
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = "DayOfTheWeekCalculator";
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    // Register the window class
    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }


    // Create the main window
    HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "DayOfTheWeekCalculator", "DayOfTheWeekCalculator",
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 480, 480, nullptr,
                               nullptr, wc.hInstance, nullptr);

    if (hwnd == nullptr) {
        MessageBox(nullptr, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create input bar
    HWND inputBar = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 10, 10, 200, 20, hwnd, (HMENU) 1,
                                 wc.hInstance, nullptr);
    SetWindowText(inputBar, "MM/DD/YYYY");
    if (inputBar == nullptr) {
        MessageBox(nullptr, "Input bar creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create submit button
    HWND button = CreateWindow("BUTTON", "Calculate", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 40,
                               100, 24, hwnd, (HMENU) 2, wc.hInstance, nullptr);
    if (button == nullptr) {
        MessageBox(nullptr, "Button creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Show the main window
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);


    MSG msg;
    // Handle the messages from the Windows Operating System
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


/**
 * @brief Main function
 * @return
 */
int main() {
    CreateWindowExample();
}