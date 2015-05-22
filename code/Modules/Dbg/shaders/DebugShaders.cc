//-----------------------------------------------------------------------------
// #version:19# machine generated, do not edit!
//-----------------------------------------------------------------------------
#include "Pre.h"
#include "DebugShaders.h"

namespace Oryol {
namespace Shaders {
#if ORYOL_OPENGL
const char* vsDbgText_glsl100_src = 
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform vec2 glyphSize;\n"
"attribute vec4 position;\n"
"attribute vec4 color0;\n"
"varying vec2 uv;\n"
"varying vec4 color;\n"
"void main() {\n"
"vec2 screenPos = position.xy * glyphSize;\n"
"screenPos.x -= 1.0;\n"
"screenPos.y = 1.0 - screenPos.y;\n"
"_POSITION = vec4(screenPos, 0.0, 1.0);\n"
"uv = position.zw * vec2(8.0 / 1024.0, 1.0);\n"
"color = color0;\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fsDbgText_glsl100_src = 
"precision mediump float;\n"
"#define mul(v,m) (m * v)\n"
"#define _TEXTURE2D texture2D\n"
"#define _COLOR gl_FragColor\n"
"uniform sampler2D tex;\n"
"varying vec2 uv;\n"
"varying vec4 color;\n"
"void main() {\n"
"_COLOR = _TEXTURE2D(tex, uv).xxxx * color;\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* vsDbgText_glsl120_src = 
"#version 120\n"
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform vec2 glyphSize;\n"
"attribute vec4 position;\n"
"attribute vec4 color0;\n"
"varying vec2 uv;\n"
"varying vec4 color;\n"
"void main() {\n"
"vec2 screenPos = position.xy * glyphSize;\n"
"screenPos.x -= 1.0;\n"
"screenPos.y = 1.0 - screenPos.y;\n"
"_POSITION = vec4(screenPos, 0.0, 1.0);\n"
"uv = position.zw * vec2(8.0 / 1024.0, 1.0);\n"
"color = color0;\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fsDbgText_glsl120_src = 
"#version 120\n"
"#define mul(v,m) (m * v)\n"
"#define _TEXTURE2D texture2D\n"
"#define _COLOR gl_FragColor\n"
"uniform sampler2D tex;\n"
"varying vec2 uv;\n"
"varying vec4 color;\n"
"void main() {\n"
"_COLOR = _TEXTURE2D(tex, uv).xxxx * color;\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* vsDbgText_glsl150_src = 
"#version 150\n"
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform vec2 glyphSize;\n"
"in vec4 position;\n"
"in vec4 color0;\n"
"out vec2 uv;\n"
"out vec4 color;\n"
"void main() {\n"
"vec2 screenPos = position.xy * glyphSize;\n"
"screenPos.x -= 1.0;\n"
"screenPos.y = 1.0 - screenPos.y;\n"
"_POSITION = vec4(screenPos, 0.0, 1.0);\n"
"uv = position.zw * vec2(8.0 / 1024.0, 1.0);\n"
"color = color0;\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fsDbgText_glsl150_src = 
"#version 150\n"
"#define mul(v,m) (m * v)\n"
"#define _TEXTURE2D texture\n"
"#define _COLOR _FragColor\n"
"uniform sampler2D tex;\n"
"in vec2 uv;\n"
"in vec4 color;\n"
"out vec4 _FragColor;\n"
"void main() {\n"
"_COLOR = _TEXTURE2D(tex, uv).xxxx * color;\n"
"}\n"
;
#endif
#if ORYOL_D3D11
const char* vsDbgText_hlsl5_src = 
"#define _POSITION _oPosition\n"
"#define mat4 float4x4\n"
"#define mat2 float2x2\n"
"#define mat3 float3x3\n"
"#define vec4 float4\n"
"#define vec2 float2\n"
"#define vec3 float3\n"
"vec2 glyphSize;\n"
"void main(\n"
"in vec4 position : position,\n"
"in vec4 color0 : color0,\n"
"out vec2 uv : uv,\n"
"out vec4 color : color,\n"
"out vec4 _oPosition : SV_POSITION) {\n"
"vec2 screenPos = position.xy * glyphSize;\n"
"screenPos.x -= 1.0;\n"
"screenPos.y = 1.0 - screenPos.y;\n"
"_POSITION = vec4(screenPos, 0.0, 1.0);\n"
"uv = position.zw * vec2(8.0 / 1024.0, 1.0);\n"
"color = color0;\n"
"}\n"
;
#endif
#if ORYOL_D3D11
const char* fsDbgText_hlsl5_src = 
"#define _TEXTURE2D FIXME_TEXTURE2D\n"
"#define _COLOR _oColor\n"
"#define mat4 float4x4\n"
"#define mat2 float2x2\n"
"#define mat3 float3x3\n"
"#define vec4 float4\n"
"#define vec2 float2\n"
"#define vec3 float3\n"
"sampler2D tex;\n"
"void main(\n"
"in vec2 uv : uv,\n"
"in vec4 color : color,\n"
"out vec4 _oColor : SV_TARGET) {\n"
"_COLOR = _TEXTURE2D(tex, uv).xxxx * color;\n"
"}\n"
;
#endif
ProgramBundleSetup TextShader::CreateSetup() {
    ProgramBundleSetup setup("TextShader");
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL100, vsDbgText_glsl100_src, fsDbgText_glsl100_src);
    #endif
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL120, vsDbgText_glsl120_src, fsDbgText_glsl120_src);
    #endif
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL150, vsDbgText_glsl150_src, fsDbgText_glsl150_src);
    #endif
    #if ORYOL_D3D11
    setup.AddProgramFromSources(0, ShaderLang::HLSL5, vsDbgText_hlsl5_src, fsDbgText_hlsl5_src);
    #endif
    setup.AddUniform("glyphSize", GlyphSize);
    setup.AddTextureUniform("tex", Texture);
    return setup;
}
}
}

