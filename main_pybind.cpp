#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <iostream>

using std::cout;
using std::endl;

namespace py = pybind11;

int main(int argc, char *argv[])
{
  // Start interpreter, keep it alive
  py::scoped_interpreter guard{};

  cout << "import" << endl;
  py::object torchlib = py::module::import("torchlib");

  cout << "get function" << endl;
  py::object runme = torchlib.attr("runme");

  cout << "run function" << endl;
  py::object result_py = runme();

  double res = result_py.cast<double>();

  cout << "result " <<  res << endl;

  cout << "create dict" << endl;
  py::dict dict;
  cout << "dict created" << endl;
  
  return 0;
}
