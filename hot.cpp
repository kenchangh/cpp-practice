#include <Python.h>
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

static PyObject* hot_score(PyObject *self, PyObject *args) {
  int score, comments;
  float created;

  if (!PyArg_ParseTuple(args, "ifi", &score, &created, &comments)) {
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
  long int seconds = created - START_TIME;
  float result = log_score * sign * 5000 +
    seconds + comments + score_rate(score, seconds);
  return Py_BuildValue("f", round(result, 5));
}

static PyMethodDef module_methods[] = {
  {"hot", (PyCFunction)hot_score, METH_VARARGS,
   "Calculates a post's hot score."},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC inithot_score(void) {
  (void) Py_InitModule("hot_score", module_methods);
}

/*int main(int argc, char *argv[]) {
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  inithot();
  return 0;
}*/
