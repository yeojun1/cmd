#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <regex>

using namespace std;

bool isValidDateFormat(const string& dateStr) {
    regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    return regex_match(dateStr, pattern);
}

int daysBetween(const std::string& dateStr) {
    tm inputDate = {};
    istringstream ss(dateStr);
    ss >> get_time(&inputDate, "%Y-%m-%d");
    if (ss.fail()) {
        cerr << "Failed to parse entered date" << endl;
        return 0;
    }

    inputDate.tm_isdst = -1; // No Summer time

    time_t nowTime = time(nullptr);
    tm* nowTm = localtime(&nowTime);
    nowTm->tm_hour = 0;
    nowTm->tm_min = 0;
    nowTm->tm_sec = 0;
    nowTm->tm_isdst = -1;

    time_t inputTime = mktime(&inputDate);
    time_t currentTime = mktime(nowTm);

    double diffSeconds = difftime(currentTime, inputTime);
    int diffDays = static_cast<int>(diffSeconds / (60 * 60 * 24));

    return diffDays;
}

int main() {
    string enteredDate;
    cout << "Enter a date (YYYY-MM-DD): ";
    cin >> enteredDate;

    if (!isValidDateFormat(enteredDate)) {
        cout << "Invalid date format entered" << endl;
        return 1;
    }

    int diff = daysBetween(enteredDate);
    if (diff == 0) {
        cout << "D-Day" << endl;
    } else if (diff >= 0) {
        cout << "D+" << diff << endl;
    } else {
        cout << "D" << diff << endl;
    }

    return 0;
}
