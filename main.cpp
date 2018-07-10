#include <Python.h>
#include <iostream>
#include "timer.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }
  Py_SetProgramName(program);

  Timer t;
  Py_Initialize();
  cout << "Python initialized in " << t.elapsed() << "ms\n";

  t.reset();
  PyObject *module_name = PyUnicode_DecodeFSDefault("torchlib");
  PyObject *module = PyImport_Import(module_name);
  Py_DECREF(module_name);
  cout << "Module imported in " << t.elapsed() << "ms\n";

  t.reset();
  if (module) {
    PyObject *func = PyObject_GetAttrString(module, "runme");

    if (func && PyCallable_Check(func)) {
      PyObject *py_arguments = PyTuple_New(0);
      PyObject *output = PyObject_CallObject(func, py_arguments);
      Py_DECREF(py_arguments);

      if (output) {
        double result = PyFloat_AsDouble(output);
        cout << "Python execution took " << t.elapsed() << "ms, result " << result << " \n";
      } else {
        Py_DECREF(func);
        Py_DECREF(module);
        PyErr_Print();
        fprintf(stderr, "Function call failed\n");
      }
    } else {
      if (PyErr_Occurred())
        PyErr_Print();
      fprintf(stderr, "Function not found\n");
    }
    Py_XDECREF(func);
    Py_DECREF(module);
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to load the module.\n");
    return 1;
  }


  // t.reset();
  // PyRun_SimpleString("from time import time,ctime\n"
  //     "print('Today is', ctime(time()))\n");
  // cout << "Python run " << t.elapsed() << "ms\n";
  
  t.reset();
  if (Py_FinalizeEx() < 0) {
    exit(120);
  }
  cout << "Python closed in " << t.elapsed() << "ms\n";

  // PyMem_RawFree(program);

  return 0;
}
