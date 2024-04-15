#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <sstream>
using namespace std;

struct Date {
  int day, month, year;

  Date(int d, int m, int y) : day(d), month(m), year(y) {}

  bool isValidDate() {
    if (year < 0)
      return false;
    if (month < 0 || month > 11)
      return false;
    if (day < 1 || day > daysInMonth(month, year))
      return false;
    return true;
  }

  void newDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
  }

  // void printDate() {
  //   static const string months[] = {
  //       "January", "February", "March", "April", "May", "June", "July",
  //       "August", "September", "October", "November", "December"
  //   };
  //   cout << day << " " << months[month] << ", " << year << endl;
  // }

  string printDate() {
    // used static to run it faster. It is not going to be initialized each time
    static const string months[] = {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"
    };
    stringstream ss;
    ss << day << " " << months[month] << " " << year;
    return ss.str();
  }

  // The first const before Date& other indicates that the other parameter is passed as a reference to a constant and will not be changed inside the method. The second const used after the parentheses indicates that this method does not change the state of the current Date object for which it is called
  bool operator<(const Date& other) const {
    if (year != other.year)
      return year < other.year;
    if (month != other.month)
      return month < other.month;
    return day < other.day;
  }

  int daysInMonth(int month, int year) {
    switch (month) {
      case 0: 
      case 2: 
      case 4: 
      case 6:
      case 7: 
      case 9: 
      case 11:
        return 31;
      case 3: 
      case 5: 
      case 8: 
      case 10:
        return 30;
      case 1:
        return (isLeapYear(year)) ? 29 : 28;
      default:
        throw std::logic_error("Invalid month");
    }
  }
  bool isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }

  int getDayOfWeek() {
    int d = day, m = month, y = year;
    if (m < 3) {
      m += 12;
      y--;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (d + (13 * (m+1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    // h = 0 corresponds to Saturday, 1 to Sunday, and so on
    return (h + 5) % 7;
  }

  int calculateDifference(const Date& other) const {
    // Convert both dates to days since a reference date (e.g., January 1, 0 AD)
    int days1 = day + 31 * (month - 1) + 365 * (year);
    for (int i = 0; i < year; i++) {
      if (isLeapYear(i))
        days1++;
    }

    int days2 = other.day + 31 * (other.month - 1) + 365 * (other.year);
    for (int i = 0; i < other.year; i++) {
      if (other.isLeapYear(i))
        days2++;
    }

    // Calculate the difference in days
    return abs(days2 - days1);
  }
};

int main() {
  string daysOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
  Date d1(13, 3, 2024);
  Date d2(26, 7, 2024);
  Date d3(29, 1, 2024);
  Date d4(12, 6, 2012);

  d2.newDate(25, 7, 2024);

  cout << d2.printDate() << " is " << daysOfWeek[d2.getDayOfWeek() - 2] << endl;
  cout << d1.calculateDifference(d2) << " days between " << d1.printDate() << " and " << d2.printDate() << endl;

  vector<Date> dates = {d1, d2, d3, d4};

  sort(dates.begin(), dates.end());

  cout << "Sorted dates:" << endl;
  for (auto date : dates) {
    cout << date.printDate() << endl;
  }

  return 0;
}