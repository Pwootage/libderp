#include <iostream>
#include <logvisor/logvisor.hpp>
#include "libderp/libderp.hpp"

using namespace std;

int main(int argc, char **argv) {
  logvisor::RegisterConsoleLogger();
  logvisor::RegisterStandardExceptions();

  cout << "Testing main" << endl;
}