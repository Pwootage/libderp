#include <iostream>
#include <logvisor/logvisor.hpp>
#include <libderp/IBinarySerializable.hpp>
#include <libderp/FileDataStream.hpp>
#include <libderp/prime1/MREA.hpp>

using namespace std;
using namespace libderp;

int main(int argc, char **argv) {
  logvisor::RegisterConsoleLogger();
  logvisor::RegisterStandardExceptions();

  cout << "Testing main" << endl;

  FileDataStream fds("b2701146.MREA");

  prime1::MREA mrea;
  mrea.readFrom(fds);

  if (fds.state() != DataStreamState::ok) {
    cout << "Failed to parse MREA" << endl;
    return 1;
  }

  return 0;
}