#include <stdio.h>
#include <vector>
#include <thread>

#include "opc_client.h"
#include "timer.hpp"

const unsigned int desired_fps = 60;

int main(int argc, char* argv[]) {
  OPCClient opc_client;
  std::vector<uint8_t> framebuffer;
  int frameBytes = 4096 * 3;
  Timer frame_time;
  
  fprintf(stderr, "connecting to: %s\n\n", argv[1]);

  opc_client.resolve(argv[1]);
  framebuffer.resize(sizeof(OPCClient::Header) + frameBytes);

  fprintf(stderr, "frameBytes: %d\n", frameBytes);
  OPCClient::Header::view(framebuffer).init(0, opc_client.SET_PIXEL_COLORS, frameBytes);

  unsigned char count = 0;
  while(true) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

    frame_time.start();
    uint8_t* colors = (uint8_t*)OPCClient::Header::view(framebuffer).data();
    memset(colors, count, frameBytes);


    if (!opc_client.write(framebuffer))
      exit(1);

    frame_time.end();


    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> time_duration = now - start_time;


    float target = 1.0f/desired_fps;
    float remainder = target - time_duration.count();

    if (remainder > 0)
    {
      std::this_thread::sleep_for(std::chrono::duration<float>(remainder));
    }
    
    fprintf(stderr, "Frame Time: % 2.2fms, count: %3d\n", frame_time.duration(), count);
    count++;
  }
}