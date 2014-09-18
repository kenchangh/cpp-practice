#include <Python.h>
#include <datetime.h>
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

float score_rate(int score, long int seconds) {
  long int minutes, hours;

  minutes = seconds / 60;
  hours = minutes / 60;
  minutes = minutes % 60;

  float rate;
  hours != 0
    ? rate = score / hours
    : rate = 0;
  return rate;
}

double round(double value, int nth) {
  return floor(value*10*nth + 0.5)/(10*nth);
}

tm py_datetime2tm(PyObject *py_datetime) {
  tm c_datetime;
  c_datetime.tm_sec = PyDateTime_DATE_GET_SECOND(py_datetime);
  c_datetime.tm_min = PyDateTime_DATE_GET_MINUTE(py_datetime);
  c_datetime.tm_hour = PyDateTime_DATE_GET_HOUR(py_datetime);
  c_datetime.tm_mday = PyDateTime_GET_DAY(py_datetime);
  c_datetime.tm_mon = PyDateTime_GET_MONTH(py_datetime);
  c_datetime.tm_year = PyDateTime_GET_YEAR(py_datetime) - 1990;
  return c_datetime;
}

static PyObject* hot_score(PyObject *self, PyObject *args) {
  int score, comments;
  PyObject *created;

  if (!PyArg_ParseTuple(args, "iOi", &score, &created, &comments)) {
    return NULL;
  }

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
  unsigned long int seconds =
    epoch_seconds(py_datetime2tm(created)) - START_TIME;
  float result = log_score * sign * 5000 +
    seconds + comments + score_rate(score, seconds);
  return Py_BuildValue("f", round(result, 5));
}

// Defining the functions
static PyMethodDef module_methods[] = {
  {"hot", (PyCFunction)hot_score, METH_VARARGS,
   "Calculates a post's hot score."},
  {NULL, NULL, 0, NULL}
};

// Initializing hot_score module with functions
PyMODINIT_FUNC inithot_score(void) {
  (void) Py_InitModule("hot_score", module_methods);
}

/*int main(int argc, char *argv[]) {
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  inithot();
  return 0;
}*/
