#include "wrapper.h"

// #include <glslang/Include/glslang_c_interface.h>
// #include <GlslangToSpv.h>
// #include <Logger.h>
// #include <SpvTools.h>
// #include <StandAlone/DirStackFileIncluder.h>
// #include <StandAlone/ResourceLimits.h>
// #include <glslang/Include/ShHandle.h>
#include <Standalone/ResourceLimits.h>
// #include <glslang/MachineIndependent/Versions.h>


// #include <glslang_c_shader_types.h>
#include <SPIRV/GlslangToSpv.h>
#include <SPIRV/SpvTools.h>
#include <SPIRV/disassemble.h>
#include <glslang/Public/ShaderLang.h>
#include <stdio.h>
#include <string>
#include <fstream>

int glslang_init() {
  return (int)glslang::InitializeProcess();
}

int glslang_compile(
  const char *source,
  int32_t length,
  uint32_t stage
) {

  if (stage > EShLangCount) {
    printf("glslang_compile: provided stage (%u) was larger than max stage (%i)\n",
      stage,
      EShLangCount
    );
    return -1;
  }

  EShLanguage selected_stage = (EShLanguage)stage;

  glslang::TShader shader(selected_stage);
  shader.setStringsWithLengths(
    (const char * const *)&source,
    (int *)&length,
    1
  );

  shader.setEnvInput(
    glslang::EShSourceGlsl,
    selected_stage,
    glslang::EShClientOpenGL,
    450
  );

  shader.setEnvClient(
    glslang::EShClientOpenGL,
    glslang::EShTargetOpenGL_450
  );

  shader.setEnvTarget(
    glslang::EShTargetSpv,
    glslang::EShTargetSpv_1_3
  );

  shader.setEntryPoint("main");

  int r = shader.parse(
    &glslang::DefaultTBuiltInResource,
    450,
    false,
    EShMsgRelaxedErrors
  );

  if (!r) {
    printf("glslang: failed to parse shader\nLOG: %s",
      shader.getInfoLog()
    );
  }

  glslang::TProgram program;
  program.addShader(&shader);
  if (!program.link(EShMsgDefault)) {
    printf("glslang: unable to link\nLOG:%s\n",
      program.getInfoLog()
    );
    return -1;
  }

  // program.mapIO();


  std::vector<uint32_t> spirv;// = compilation_output_data;
  glslang::SpvOptions options;
  // options.generateDebugInfo = generate_debug_info_;
  options.disableOptimizer = true;
  options.optimizeSize = false;
  // Note the call to GlslangToSpv also populates compilation_output_data.
  glslang::GlslangToSpv(*program.getIntermediate(selected_stage), spirv,
                        &options);

  spv::Disassemble(std::cout, spirv);

  std::ofstream output;
  output.open("E:\\out2.spv", std::ios::binary);
  output.write((char *)spirv.data(), sizeof(unsigned int) * spirv.size());
  output.close();

  // glslang_initialize_process()
  // glslang::TShader *shader = new glslang::TShader(
  //   // From: ShaderLang.h
  //   EShLangVertex
  // );

  // if (!glslang::InitializeProcess()) {
  //    return 0;
  // }

  // std::string src(" \
  //   layout(location=0) out vec4 colorOut; \
  //   void main(){ \
  //     colorOut = vec4(1.0, 0.0, 0.0, 1.0); \
  //   } \
  // ");
  //
  // glslang_input_t input;
  // input.language = GLSLANG_SOURCE_GLSL;
  // input.stage = GLSLANG_STAGE_FRAGMENT;
  // input.client = GLSLANG_CLIENT_OPENGL;
  // input.client_version = GLSLANG_TARGET_OPENGL_450;
  // input.target_language = GLSLANG_TARGET_NONE;
  // input.target_language_version = GLSLANG_TARGET_SPV_1_1;
  // input.code = src.c_str();
  // input.default_version = 450;
  // input.default_profile = GLSLANG_CORE_PROFILE;
  // input.force_default_version_and_profile = false;
  // input.forward_compatible = true;
  // input.messages = GLSLANG_MSG_DEFAULT_BIT;
  //
  //
  // if (!glslang_initialize_process()) {
  //   printf("glslang: failed to initialize\n");
  //   return -1;
  // }
  //
  // glslang_shader_t* shader = glslang_shader_create( &input );
  //
  // if ( !glslang_shader_preprocess(shader, &input)) {
  //   printf("glslang: failed to preprocess shader\n");
  //   // return -1;
  // }
  //
  // const char* newsrc = glslang_shader_get_preprocessed_code(shader);
  // printf("new src: %s\n", newsrc);
  //
  // if ( !glslang_shader_parse(shader, &input) ) {
  //   printf("glslang: failed to parse shader\nLOG: %s", glslang_shader_get_info_log(shader));
  //   return -1;
  // }
  //
  // glslang_program_t* program = glslang_program_create();
  // glslang_program_add_shader( program, shader );
  // if (!glslang_program_link(program, GLSLANG_MSG_RELAXED_ERRORS_BIT)) {
  //   printf("glslang: failed to link program\nLOG: %s\n", glslang_program_get_info_log(program));
  //   return -1;
  // }
  //
  // glslang_program_SPIRV_generate(program, input.stage);
  //
  // glslang_program_SPIRV_get_messages(program);
  // printf("glslang: SPIRV messages: %s", glslang_program_SPIRV_get_messages(program));
  //
  // size_t len = glslang_program_SPIRV_get_size(program);
  // unsigned int *buf = glslang_program_SPIRV_get_ptr(program);
  //
  // std::ofstream output;
  // output.open("E:\\out.spv", std::ios::binary);
  // output.write((char *)buf, sizeof(unsigned int) * len);
  // output.close();
  //
  // glslang_shader_delete(shader);
  // glslang_finalize_process();

  return 1;
}
