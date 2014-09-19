#include <iostream>
#include <ctime>
#include <typeinfo>
#include <string>
#include <sstream>
using namespace std;

string to_str(int i) {
  stringstream s;
  s << i;
  return s.str();
}

string delta_str(double delta) {
  const int SECOND = 1;
  const int MINUTE = 60 * SECOND;
  const int HOUR = 60 * MINUTE;
  const int DAY = 24 * HOUR;
  const int MONTH = 30 * DAY;
  const int YEAR = 365 * MONTH;
  string s;
  // Think about the decimal points
  if (delta < 1 * MINUTE) {
    return delta == 1
      ? s = "1 second ago"
      : s = to_str(delta) + " seconds ago";
  }
  if (delta < 60 * MINUTE) {
    return delta < 2 * MINUTE
      ? s = "1 minute ago"
      : s = to_str(delta/MINUTE) + " minutes ago";
  }
  if (delta < 24 * HOUR) {
    return delta < 2 * HOUR
      ? s = "1 hour ago"
      : s = to_str(delta/HOUR) + " hours ago";
  }
  if (delta < 48 * HOUR) {
    return "yesterday";
  }
  if (delta < 30 * DAY) {
    return delta < 2 * DAY
      ? s = "1 day ago"
      : s = to_str(delta/DAY) + " days ago";
  }
  if (delta < 12 * MONTH) {
    return delta < 2 * MONTH
      ? s = "1 month ago"
      : s = to_str(delta/MONTH) + " months ago";
  }
  else {
    return delta < 2 * YEAR
      ? s = "1 year ago"
      : s = to_str(delta/YEAR) + " years ago"; 
  }
} 

int main() {
  double delta = 6572333;
  time_t input_time = mktime(&dt);
  time_t time_now = time(NULL); 
  double delta = abs(difftime(time_now, input_time));
  cout << delta_str(delta) << endl;
  return 0;
}