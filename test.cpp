#include <iostream>
#include <ctime>
#include <typeinfo>
using namespace std;

int main() {
	tm dt;
	dt.tm_sec = 10;
  dt.tm_min = 10;
  dt.tm_hour = 10;
  dt.tm_mday = 10;
  dt.tm_mon = 10;
  dt.tm_year = 100;
  cout << mktime(&dt) << endl;
	return 0;
}