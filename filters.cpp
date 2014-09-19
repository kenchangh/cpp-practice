#include <Python.h>
#include <datetime.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;


string to_str(int i) {
  stringstream s;
  s << i;
  return s.str();
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

string delta_str(double delta) {
  const int SECOND = 1;
  const int MINUTE = 60 * SECOND;
  const int HOUR = 60 * MINUTE;
  const int DAY = 24 * HOUR;
  const int MONTH = 30 * DAY;
  const int YEAR = 365 * MONTH;

  string s;
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

static PyObject *dt2relative(PyObject *self, PyObject *args) {
	PyObject *py_dt;

	if (!PyArg_ParseTuple(args, "O", &py_dt)) {
    return NULL;
  }
  tm dt = py_datetime2tm(py_dt);
  time_t input_time = mktime(&dt);
  time_t time_now = time(NULL); 
  double delta = abs(difftime(time_now, input_time));
  string s = delta_str(delta);
  return Py_BuildValue("s", s.c_str());
}

// Defining the functions
static PyMethodDef module_methods[] = {
  {"dt2relative", (PyCFunction)dt2relative, METH_VARARGS,
   "Returns a relative datetime string"},
  {NULL, NULL, 0, NULL}
};

// Initializing hot_score module with functions
PyMODINIT_FUNC initdt2relative(void) {
  (void) Py_InitModule("dt2relative", module_methods);
}
