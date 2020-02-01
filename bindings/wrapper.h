#include <stdint.h>
extern "C" {
  int glsl_to_spirv(char *source, uint32_t length);
}
