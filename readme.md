# Program to calculate the day of the week for a given date

This is a program that calculates the day of the week for a given date, written in C++ and uses Zeller's congruence.

## Functions
- `HWNDToString`: Convert `HWND` input to string.
- `getDayOfWeek`: Get the day of the week from a date using Zeller's congruence.
- `manageInput`: Manage input from the user.

## Implementation Details
The program has three main functions:
- `HWNDToString` takes a Handle Window (HWND) as input and converts it to a string.
- `getDayOfWeek` takes an array of integers containing the date (day, month, year) and calculates the day of the week using Zeller's congruence formula. The calculation is done by initializing variables for the day, month, last two digits of year, and first two digits of year. If the month is January or February, the month is increased by 12 and the year is decreased by 1 because Zeller's congruence only works for months March through December (m = 3, 4, ..., 12). The formula for Zeller's congruence is then applied to calculate the day of the week. The result of the calculation is returned as a string.
- `manageInput` takes a Handle Window (HWND) as input, converts it to a string, checks if the input is in the correct format, and calls `getDayOfWeek` if the input is in the correct format.

## Zeller's congruence

Zeller's congruence is an algorithm used to calculate the day of the week for any given date. It is a well-known method used in many programming applications to determine the day of the week for a given date.

In the code provided, Zeller's congruence is used to determine the day of the week for a date represented by the variables q, m, k, and j. Here's a detailed explanation of how the algorithm works:

The day of the week is calculated using the formula:
  ```cpp
  h = (q + (int) floor((13 * (m + 1)) / 5) + k + (int) floor(k / 4) + (int) floor(j / 4) - 2 * j) % 7
   ``` 
 - The value of `q` represents the day of the month (1 to 31).
 - The value of `m` represents the month of the year (1 to 12).
 - The value of `k` represents the last two digits of the year (0 to 99).
 - The value of `j` represents the first two digits of the year (0 to 99).
 - If the month is January or February `(m < 3)`, then the value of `m` is added to 12, and the value of `k` is decremented by 1. This is done because the algorithm only works for months March through December `(m = 3, 4, ..., 12)`.
 - The value of `h` is calculated using the formula, which is a combination of integer operations and the floor function, which returns the largest integer that is less than or equal to the input value.
 - Finally, the value of `h` is taken modulo 7, and the resulting value will be an integer from 0 to 6. The values of 0, 1, 2, 3, 4, 5, and 6 correspond to Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, and Friday respectively.

## License
This program is licensed under the MIT License.

## Author
Leon Burghardt

## Date
02/02/2023
