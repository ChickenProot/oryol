//-----------------------------------------------------------------------------
// #version:19# machine generated, do not edit!
//-----------------------------------------------------------------------------
#include "Pre.h"
#include "shaders.h"

namespace Oryol {
namespace Shaders {
#if ORYOL_OPENGL
const char* vs_glsl100_src = 
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform mat4 modelViewProj;\n"
"uniform mat4 modelView;\n"
"attribute vec4 position;\n"
"attribute vec3 normal;\n"
"varying vec3 viewSpacePos;\n"
"varying vec3 viewSpaceNormal;\n"
"void main() {\n"
"_POSITION = modelViewProj * position;\n"
"viewSpacePos = vec3(modelView * position);\n"
"viewSpaceNormal = vec3(modelView * vec4(normal, 0.0));\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fs_glsl100_src = 
"precision mediump float;\n"
"#define mul(v,m) (m * v)\n"
"#define _COLOR gl_FragColor\n"
"uniform vec3 lightVec;\n"
"varying vec3 viewSpacePos;\n"
"varying vec3 viewSpaceNormal;\n"
"const float PI = 3.14159265358979323846;\n"
"const float c = 0.4;\n"
"float square(float x) {\n"
"return x * x;\n"
"}\n"
"float TrowbridgeReitz(float c, float n_dot_h) {\n"
"float cSquared = c * c;\n"
"return square(cSquared / (n_dot_h*n_dot_h*(cSquared - 1.0) + 1.0));\n"
"}\n"
"vec3\n"
"D_TrowbridgeReitz(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = TrowbridgeReitz(c, dot(N, H));\n"
"D *= 1.0 / (c*c*PI);\n"
"return vec3(D);\n"
"}\n"
"float GGX(float c, float cosThetaM) {\n"
"float cosSquared = cosThetaM * cosThetaM;\n"
"float tanSquared = (1.0 - cosSquared) / cosSquared;\n"
"return (1.0 / PI) * square(c / (cosSquared * (c * c + tanSquared)));\n"
"}\n"
"vec3 D_GGX(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = GGX(c, dot(N, H));\n"
"return vec3(D);\n"
"}\n"
"const float m = 0.25;\n"
"float Gsch(float v, float m) {\n"
"float k = sqrt(2.0 * m * m / PI);\n"
"return v > 0.0 ? v / (v - k * v + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_Schlick(vec3 L, vec3 V, vec3 N) {\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gsch(n_dot_l, m) * Gsch(n_dot_v, m);\n"
"return vec3(G);\n"
"}\n"
"float Gue4(float v, float k) {\n"
"return v > 0.0 ? v / (v * (1.0 - k) + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_UE4(vec3 L, vec3 V, vec3 N) {\n"
"float k = ((c + 1.0) * (c + 1.0)) / 8.0;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gue4(n_dot_l, k) * Gue4(n_dot_v, k);\n"
"return vec3(G);\n"
"}\n"
"vec4 gamma(vec4 c) {\n"
"return vec4(pow(c.xyz, vec3(1.0/2.2)), c.w);\n"
"}\n"
"void main() {\n"
"const vec3 eyePos = vec3(0.0, 0.0, 0.0);\n"
"vec3 N = normalize(viewSpaceNormal);\n"
"vec3 V = normalize(eyePos - viewSpacePos);\n"
"vec3 L = lightVec.xyz;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"vec3 D = D_GGX(L, V, N);\n"
"vec3 G = G_UE4(L, V, N);\n"
"vec3 spec = D * G;\n"
"vec3 c = spec;\n"
"_COLOR = gamma(vec4(c, 1.0));\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* vs_glsl120_src = 
"#version 120\n"
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform mat4 modelViewProj;\n"
"uniform mat4 modelView;\n"
"attribute vec4 position;\n"
"attribute vec3 normal;\n"
"varying vec3 viewSpacePos;\n"
"varying vec3 viewSpaceNormal;\n"
"void main() {\n"
"_POSITION = modelViewProj * position;\n"
"viewSpacePos = vec3(modelView * position);\n"
"viewSpaceNormal = vec3(modelView * vec4(normal, 0.0));\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fs_glsl120_src = 
"#version 120\n"
"#define mul(v,m) (m * v)\n"
"#define _COLOR gl_FragColor\n"
"uniform vec3 lightVec;\n"
"varying vec3 viewSpacePos;\n"
"varying vec3 viewSpaceNormal;\n"
"const float PI = 3.14159265358979323846;\n"
"const float c = 0.4;\n"
"float square(float x) {\n"
"return x * x;\n"
"}\n"
"float TrowbridgeReitz(float c, float n_dot_h) {\n"
"float cSquared = c * c;\n"
"return square(cSquared / (n_dot_h*n_dot_h*(cSquared - 1.0) + 1.0));\n"
"}\n"
"vec3\n"
"D_TrowbridgeReitz(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = TrowbridgeReitz(c, dot(N, H));\n"
"D *= 1.0 / (c*c*PI);\n"
"return vec3(D);\n"
"}\n"
"float GGX(float c, float cosThetaM) {\n"
"float cosSquared = cosThetaM * cosThetaM;\n"
"float tanSquared = (1.0 - cosSquared) / cosSquared;\n"
"return (1.0 / PI) * square(c / (cosSquared * (c * c + tanSquared)));\n"
"}\n"
"vec3 D_GGX(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = GGX(c, dot(N, H));\n"
"return vec3(D);\n"
"}\n"
"const float m = 0.25;\n"
"float Gsch(float v, float m) {\n"
"float k = sqrt(2.0 * m * m / PI);\n"
"return v > 0.0 ? v / (v - k * v + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_Schlick(vec3 L, vec3 V, vec3 N) {\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gsch(n_dot_l, m) * Gsch(n_dot_v, m);\n"
"return vec3(G);\n"
"}\n"
"float Gue4(float v, float k) {\n"
"return v > 0.0 ? v / (v * (1.0 - k) + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_UE4(vec3 L, vec3 V, vec3 N) {\n"
"float k = ((c + 1.0) * (c + 1.0)) / 8.0;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gue4(n_dot_l, k) * Gue4(n_dot_v, k);\n"
"return vec3(G);\n"
"}\n"
"vec4 gamma(vec4 c) {\n"
"return vec4(pow(c.xyz, vec3(1.0/2.2)), c.w);\n"
"}\n"
"void main() {\n"
"const vec3 eyePos = vec3(0.0, 0.0, 0.0);\n"
"vec3 N = normalize(viewSpaceNormal);\n"
"vec3 V = normalize(eyePos - viewSpacePos);\n"
"vec3 L = lightVec.xyz;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"vec3 D = D_GGX(L, V, N);\n"
"vec3 G = G_UE4(L, V, N);\n"
"vec3 spec = D * G;\n"
"vec3 c = spec;\n"
"_COLOR = gamma(vec4(c, 1.0));\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* vs_glsl150_src = 
"#version 150\n"
"#define mul(v,m) (m * v)\n"
"#define _POSITION gl_Position\n"
"uniform mat4 modelViewProj;\n"
"uniform mat4 modelView;\n"
"in vec4 position;\n"
"in vec3 normal;\n"
"out vec3 viewSpacePos;\n"
"out vec3 viewSpaceNormal;\n"
"void main() {\n"
"_POSITION = modelViewProj * position;\n"
"viewSpacePos = vec3(modelView * position);\n"
"viewSpaceNormal = vec3(modelView * vec4(normal, 0.0));\n"
"}\n"
;
#endif
#if ORYOL_OPENGL
const char* fs_glsl150_src = 
"#version 150\n"
"#define mul(v,m) (m * v)\n"
"#define _COLOR _FragColor\n"
"uniform vec3 lightVec;\n"
"in vec3 viewSpacePos;\n"
"in vec3 viewSpaceNormal;\n"
"out vec4 _FragColor;\n"
"const float PI = 3.14159265358979323846;\n"
"const float c = 0.4;\n"
"float square(float x) {\n"
"return x * x;\n"
"}\n"
"float TrowbridgeReitz(float c, float n_dot_h) {\n"
"float cSquared = c * c;\n"
"return square(cSquared / (n_dot_h*n_dot_h*(cSquared - 1.0) + 1.0));\n"
"}\n"
"vec3\n"
"D_TrowbridgeReitz(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = TrowbridgeReitz(c, dot(N, H));\n"
"D *= 1.0 / (c*c*PI);\n"
"return vec3(D);\n"
"}\n"
"float GGX(float c, float cosThetaM) {\n"
"float cosSquared = cosThetaM * cosThetaM;\n"
"float tanSquared = (1.0 - cosSquared) / cosSquared;\n"
"return (1.0 / PI) * square(c / (cosSquared * (c * c + tanSquared)));\n"
"}\n"
"vec3 D_GGX(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = GGX(c, dot(N, H));\n"
"return vec3(D);\n"
"}\n"
"const float m = 0.25;\n"
"float Gsch(float v, float m) {\n"
"float k = sqrt(2.0 * m * m / PI);\n"
"return v > 0.0 ? v / (v - k * v + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_Schlick(vec3 L, vec3 V, vec3 N) {\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gsch(n_dot_l, m) * Gsch(n_dot_v, m);\n"
"return vec3(G);\n"
"}\n"
"float Gue4(float v, float k) {\n"
"return v > 0.0 ? v / (v * (1.0 - k) + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_UE4(vec3 L, vec3 V, vec3 N) {\n"
"float k = ((c + 1.0) * (c + 1.0)) / 8.0;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gue4(n_dot_l, k) * Gue4(n_dot_v, k);\n"
"return vec3(G);\n"
"}\n"
"vec4 gamma(vec4 c) {\n"
"return vec4(pow(c.xyz, vec3(1.0/2.2)), c.w);\n"
"}\n"
"void main() {\n"
"const vec3 eyePos = vec3(0.0, 0.0, 0.0);\n"
"vec3 N = normalize(viewSpaceNormal);\n"
"vec3 V = normalize(eyePos - viewSpacePos);\n"
"vec3 L = lightVec.xyz;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"vec3 D = D_GGX(L, V, N);\n"
"vec3 G = G_UE4(L, V, N);\n"
"vec3 spec = D * G;\n"
"vec3 c = spec;\n"
"_COLOR = gamma(vec4(c, 1.0));\n"
"}\n"
;
#endif
#if ORYOL_D3D11
const char* vs_hlsl5_src = 
"#define _POSITION _oPosition\n"
"#define mat4 float4x4\n"
"#define mat2 float2x2\n"
"#define mat3 float3x3\n"
"#define vec4 float4\n"
"#define vec2 float2\n"
"#define vec3 float3\n"
"mat4 modelViewProj;\n"
"mat4 modelView;\n"
"void main(\n"
"in vec4 position : position,\n"
"in vec3 normal : normal,\n"
"out vec3 viewSpacePos : viewSpacePos,\n"
"out vec3 viewSpaceNormal : viewSpaceNormal,\n"
"out vec4 _oPosition : SV_POSITION) {\n"
"_POSITION = modelViewProj * position;\n"
"viewSpacePos = vec3(modelView * position);\n"
"viewSpaceNormal = vec3(modelView * vec4(normal, 0.0));\n"
"}\n"
;
#endif
#if ORYOL_D3D11
const char* fs_hlsl5_src = 
"#define _COLOR _oColor\n"
"#define mat4 float4x4\n"
"#define mat2 float2x2\n"
"#define mat3 float3x3\n"
"#define vec4 float4\n"
"#define vec2 float2\n"
"#define vec3 float3\n"
"vec3 lightVec;\n"
"const float PI = 3.14159265358979323846;\n"
"const float c = 0.4;\n"
"float square(float x) {\n"
"return x * x;\n"
"}\n"
"float TrowbridgeReitz(float c, float n_dot_h) {\n"
"float cSquared = c * c;\n"
"return square(cSquared / (n_dot_h*n_dot_h*(cSquared - 1.0) + 1.0));\n"
"}\n"
"vec3\n"
"D_TrowbridgeReitz(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = TrowbridgeReitz(c, dot(N, H));\n"
"D *= 1.0 / (c*c*PI);\n"
"return vec3(D);\n"
"}\n"
"float GGX(float c, float cosThetaM) {\n"
"float cosSquared = cosThetaM * cosThetaM;\n"
"float tanSquared = (1.0 - cosSquared) / cosSquared;\n"
"return (1.0 / PI) * square(c / (cosSquared * (c * c + tanSquared)));\n"
"}\n"
"vec3 D_GGX(vec3 L, vec3 V, vec3 N) {\n"
"vec3 H = normalize(L + V);\n"
"float D = GGX(c, dot(N, H));\n"
"return vec3(D);\n"
"}\n"
"const float m = 0.25;\n"
"float Gsch(float v, float m) {\n"
"float k = sqrt(2.0 * m * m / PI);\n"
"return v > 0.0 ? v / (v - k * v + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_Schlick(vec3 L, vec3 V, vec3 N) {\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gsch(n_dot_l, m) * Gsch(n_dot_v, m);\n"
"return vec3(G);\n"
"}\n"
"float Gue4(float v, float k) {\n"
"return v > 0.0 ? v / (v * (1.0 - k) + k) : 0.0;\n"
"}\n"
"vec3\n"
"G_UE4(vec3 L, vec3 V, vec3 N) {\n"
"float k = ((c + 1.0) * (c + 1.0)) / 8.0;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"float G = Gue4(n_dot_l, k) * Gue4(n_dot_v, k);\n"
"return vec3(G);\n"
"}\n"
"vec4 gamma(vec4 c) {\n"
"return vec4(pow(c.xyz, vec3(1.0/2.2)), c.w);\n"
"}\n"
"void main(\n"
"in vec3 viewSpacePos : viewSpacePos,\n"
"in vec3 viewSpaceNormal : viewSpaceNormal,\n"
"out vec4 _oColor : SV_TARGET) {\n"
"const vec3 eyePos = vec3(0.0, 0.0, 0.0);\n"
"vec3 N = normalize(viewSpaceNormal);\n"
"vec3 V = normalize(eyePos - viewSpacePos);\n"
"vec3 L = lightVec.xyz;\n"
"float n_dot_l = dot(N, L);\n"
"float n_dot_v = dot(N, V);\n"
"vec3 D = D_GGX(L, V, N);\n"
"vec3 G = G_UE4(L, V, N);\n"
"vec3 spec = D * G;\n"
"vec3 c = spec;\n"
"_COLOR = gamma(vec4(c, 1.0));\n"
"}\n"
;
#endif
ProgramBundleSetup Main::CreateSetup() {
    ProgramBundleSetup setup("Main");
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL100, vs_glsl100_src, fs_glsl100_src);
    #endif
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL120, vs_glsl120_src, fs_glsl120_src);
    #endif
    #if ORYOL_OPENGL
    setup.AddProgramFromSources(0, ShaderLang::GLSL150, vs_glsl150_src, fs_glsl150_src);
    #endif
    #if ORYOL_D3D11
    setup.AddProgramFromSources(0, ShaderLang::HLSL5, vs_hlsl5_src, fs_hlsl5_src);
    #endif
    setup.AddUniform("modelViewProj", ModelViewProj);
    setup.AddUniform("modelView", ModelView);
    setup.AddUniform("lightVec", LightVec);
    return setup;
}
}
}

