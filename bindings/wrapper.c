#include "wrapper.h"

#include <stdio.h>

int glsl_to_spirv(char *source, uint32_t length) {
  printf("FROM C: hello\n");
  return 1;
}
