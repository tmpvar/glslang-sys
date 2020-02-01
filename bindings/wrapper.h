#include <stdint.h>
extern "C" {
  int glslang_init();
  int glslang_compile(const char *source, int32_t length, uint32_t stage);
}
