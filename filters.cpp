#include <Python.h>
#include <datetime.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <dt_extra.h>
using namespace std;


/*static PyObject *relative_delta = NULL;

static PyObject *
set_relative_delta(PyObject *self, PyObject *args) {
  PyObject *result = NULL;
  PyObject *temp;

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }
    Py_XINCREF(temp);         // Add a reference to new callback
    Py_XDECREF(relative_delta);  // Dispose of previous callback
    relative_delta = temp;       // Remember new callback
    Py_INCREF(Py_None);
    result = Py_None;
  }
  return result;
}*/

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

static PyObject *dt2relative(PyObject *self, PyObject *args) {
	PyObject *py_dt;
	if (!PyArg_ParseTuple(args, "O", &py_dt)) {
    return NULL;
  }
  tm dt = py_datetime2tm(py_dt);
  time_t input_time = mktime(&dt);
  time_t time_now = time(NULL); 
  double delta = difftime(time_now, input_time)
  return Py_BuildValue("s", "yolo");
}

// Defining the functions
static PyMethodDef module_methods[] = {
  {"dt2relative", (PyCFunction)dt2relative, METH_VARARGS,
   "Returns a relative datetime string"},
  {NULL, NULL, 0, NULL}
};

// Initializing hot_score module with functions
PyMODINIT_FUNC initfilters(void) {
  (void) Py_InitModule("filters", module_methods);
}
