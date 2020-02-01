#include "wrapper.h"

#include <glslang/Include/glslang_c_interface.h>
#include <GlslangToSpv.h>
#include <Logger.h>
#include <SpvTools.h>
#include <StandAlone/DirStackFileIncluder.h>
#include <StandAlone/ResourceLimits.h>
#include <glslang/Include/ShHandle.h>
#include <glslang/Include/ResourceLimits.h>
#include <glslang/MachineIndependent/Versions.h>


// #include <glslang_c_shader_types.h>
// #include <SPIRV/GlslangToSpv.h>
// #include <glslang/Public/ShaderLang.h>
#include <stdio.h>
#include <string>


int glsl_to_spirv(char *source, uint32_t length) {
  // glslang_initialize_process()
  // glslang::TShader *shader = new glslang::TShader(
  //   // From: ShaderLang.h
  //   EShLangVertex
  // );

  // if (!glslang::InitializeProcess()) {
  //    return 0;
  // }

  std::string a("hello world");

  int init_result = glslang_initialize_process();
  printf("FROM C: hello (init: %i) %s\n", init_result, a.c_str());
  return 1;
}
