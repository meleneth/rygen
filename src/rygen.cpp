#include <iostream>
#include <unistd.h>

#include "video.hpp"

using namespace std;
using namespace Rygen;

int main(int argc, char *argv[])
{
  auto video =  Video(1024, 768);
  cout << "rygen: rygen\n";
  sleep(5);
  return 0;
}



