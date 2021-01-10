#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "DACRenderer.h"
#include "driver/dac.h"

void DACRenderer::start()
{
  printf("Enabled dac output");
  dac_output_enable(DAC_CHANNEL_1);
  dac_output_enable(DAC_CHANNEL_2);
  Renderer::start();
}

void DACRenderer::stop()
{
  Renderer::stop();
  printf("Disabling dac output");
  dac_output_disable(DAC_CHANNEL_1);
  dac_output_disable(DAC_CHANNEL_2);
}

DACRenderer::DACRenderer(float world_size)
{
  render_buffer = new RenderBuffer(
      0, 255,
      0, 255,
      128,
      128,
      128.0f / world_size);
}

void IRAM_ATTR DACRenderer::trigger_draw()
{
  // no need to do anything special just draw straight away
  draw();
}

void IRAM_ATTR DACRenderer::draw_sample(const DrawInstruction_t &instruction)
{
  gpio_set_level(PIN_NUM_LASER, instruction.laser ? 1 : 0);
  uint8_t output_x = instruction.x;
  uint8_t output_y = instruction.y;
  dac_output_voltage(DAC_CHANNEL_1, output_x);
  dac_output_voltage(DAC_CHANNEL_2, output_y);
  send_success++;
  output_calls++;
}
