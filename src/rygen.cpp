#include <iostream>
#include <unistd.h>

#include "video.hpp"
#include "demo.hpp"

using namespace std;
using namespace Rygen;

int main(int argc, char *argv[])
{
  auto video =  Video(1024, 768);
  video.setup();

  auto demo = Demo(video);

  demo.render_frame();

  cout << "rygen: rygen\n";
  sleep(5);
  return 0;
}



