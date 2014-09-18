#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cmath>
using namespace std;

#define START_TIME 1407170715.44


unsigned long int epoch_seconds(tm datetime) {
  unsigned long int epoch_seconds = 
    static_cast<unsigned long int> (mktime(&datetime));
  return epoch_seconds;
}

struct AnswerRemainder {
  int answer;
  int remainder;
};

AnswerRemainder divmod(long int a, long int b) {
  AnswerRemainder result;
  result.answer = a / b;
  result.remainder = a % b;
  return result;
}

float score_rate(int score, long int seconds) {
  AnswerRemainder minutes_seconds, hours_minutes;
  long int minutes, hours;

  minutes_seconds = divmod(seconds, 60);
  minutes = minutes_seconds.answer;
  hours_minutes = divmod(minutes, 60);
  hours = hours_minutes.answer;
  minutes = hours_minutes.remainder;

  float rate;
  hours != 0
    ? rate = score / hours
    : rate = 0;
  return rate;
}

double round(double value, int nth) {
  return floor(value*10*nth + 0.5)/(10*nth);
}

float hot(int score, tm created, int comments) {
  float log_score;
  score == 0
    ? log_score = log10(abs(score))
    : log_score = score;
  int sign;
  if (score > 0) {
    sign = 1;
  }
  else if (score < 0) {
    sign = -1;
  }
  else {
    sign = 0;
  }
  long int seconds = epoch_seconds(created) - START_TIME;
  float result = log_score * sign * 5000 +
    seconds + comments + score_rate(score, seconds);
  return round(result, 5);
}

int main() {
  time_t time_now;
  // Creating some random time
  tm some_time;
  some_time.tm_sec = 50;
  some_time.tm_min = 50;
  some_time.tm_hour = 20;
  some_time.tm_mday = 20;
  some_time.tm_mon = 10;
  some_time.tm_year = 150;
  some_time.tm_wday = 1;
  some_time.tm_yday = 50;
  some_time.tm_isdst = 5;

  // Calculating post's hot_score
  float hot_score = hot(60, some_time, 5);
  cout << hot_score << endl;
  return 0;
}