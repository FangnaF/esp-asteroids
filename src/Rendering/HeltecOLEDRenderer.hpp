#ifndef _heltec_hpp_
#define _heltec_hpp_

#include "Renderer.h"

typedef void *TaskHandle_t;

class HeltecOLEDRenderer : public Renderer
{
private:
  TaskHandle_t _draw_task_handle;

public:
  HeltecOLEDRenderer(float world_size);
  void start();
  void stop();

  void trigger_draw(){};
  void draw_sample(const DrawInstruction_t &instruction);
  friend void oled_draw_task(void *param);
};

#endif