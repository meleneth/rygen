#include <iostream>
#include <unistd.h>

#include "rygen_types.hpp"

#include "video.hpp"
#include "demo.hpp"
#include "console.hpp"

using namespace std;
using namespace Rygen;

int main(int argc, char *argv[]) {
  console.print_logs = 1;
  auto video = Video(1024, 768);
  video.setup();

  auto demo = Demo(video);

  demo.render_frame(video);

  cout << "rygen: rygen\n";
  sleep(5);
  return 0;
}
