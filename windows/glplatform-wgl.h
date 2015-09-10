#ifndef GL_BINDIFY_wgl_H
#define GL_BINDIFY_wgl_H
#ifdef __cplusplus
extern "C" {
#endif
#include <windows.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#ifndef GLBINDIFY_COMMON_GL_TYPEDEFS
#define GLBINDIFY_COMMON_GL_TYPEDEFS
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef double GLdouble;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif
#ifndef GLPLATFORM_WGL_VERSION
#define GLPLATFORM_WGL_VERSION 10
#endif
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_COLORREF
#define GLPLATFORM_TYPE_COLORREF

#endif
#ifndef GLPLATFORM_TYPE_DWORD
#define GLPLATFORM_TYPE_DWORD

#endif
#ifndef GLPLATFORM_TYPE_FLOAT
#define GLPLATFORM_TYPE_FLOAT

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif
#ifndef GLPLATFORM_TYPE_LAYERPLANEDESCRIPTOR
#define GLPLATFORM_TYPE_LAYERPLANEDESCRIPTOR

#endif
#ifndef GLPLATFORM_TYPE_LPCSTR
#define GLPLATFORM_TYPE_LPCSTR

#endif
#ifndef GLPLATFORM_TYPE_LPGLYPHMETRICSFLOAT
#define GLPLATFORM_TYPE_LPGLYPHMETRICSFLOAT

#endif
#ifndef GLPLATFORM_TYPE_PROC
#define GLPLATFORM_TYPE_PROC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_FONT_LINES 0x0
#define WGL_FONT_POLYGONS 0x1
#define WGL_SWAP_MAIN_PLANE 0x1
#define WGL_SWAP_OVERLAY1 0x2
#define WGL_SWAP_OVERLAY10 0x400
#define WGL_SWAP_OVERLAY11 0x800
#define WGL_SWAP_OVERLAY12 0x1000
#define WGL_SWAP_OVERLAY13 0x2000
#define WGL_SWAP_OVERLAY14 0x4000
#define WGL_SWAP_OVERLAY15 0x8000
#define WGL_SWAP_OVERLAY2 0x4
#define WGL_SWAP_OVERLAY3 0x8
#define WGL_SWAP_OVERLAY4 0x10
#define WGL_SWAP_OVERLAY5 0x20
#define WGL_SWAP_OVERLAY6 0x40
#define WGL_SWAP_OVERLAY7 0x80
#define WGL_SWAP_OVERLAY8 0x100
#define WGL_SWAP_OVERLAY9 0x200
#define WGL_SWAP_UNDERLAY1 0x10000
#define WGL_SWAP_UNDERLAY10 0x2000000
#define WGL_SWAP_UNDERLAY11 0x4000000
#define WGL_SWAP_UNDERLAY12 0x8000000
#define WGL_SWAP_UNDERLAY13 0x10000000
#define WGL_SWAP_UNDERLAY14 0x20000000
#define WGL_SWAP_UNDERLAY15 0x40000000
#define WGL_SWAP_UNDERLAY2 0x20000
#define WGL_SWAP_UNDERLAY3 0x40000
#define WGL_SWAP_UNDERLAY4 0x80000
#define WGL_SWAP_UNDERLAY5 0x100000
#define WGL_SWAP_UNDERLAY6 0x200000
#define WGL_SWAP_UNDERLAY7 0x400000
#define WGL_SWAP_UNDERLAY8 0x800000
#define WGL_SWAP_UNDERLAY9 0x1000000

#define wglCopyContext _glplatform_wglCopyContext
extern BOOL (*wglCopyContext)(HGLRC, HGLRC, UINT);
#define wglCreateContext _glplatform_wglCreateContext
extern HGLRC (*wglCreateContext)(HDC);
#define wglCreateLayerContext _glplatform_wglCreateLayerContext
extern HGLRC (*wglCreateLayerContext)(HDC, int );
#define wglDeleteContext _glplatform_wglDeleteContext
extern BOOL (*wglDeleteContext)(HGLRC);
#define wglDescribeLayerPlane _glplatform_wglDescribeLayerPlane
extern BOOL (*wglDescribeLayerPlane)(HDC, int , int , UINT, const LAYERPLANEDESCRIPTOR *);
#define wglGetCurrentContext _glplatform_wglGetCurrentContext
extern HGLRC (*wglGetCurrentContext)();
#define wglGetCurrentDC _glplatform_wglGetCurrentDC
extern HDC (*wglGetCurrentDC)();
#define wglGetLayerPaletteEntries _glplatform_wglGetLayerPaletteEntries
extern int (*wglGetLayerPaletteEntries)(HDC, int , int , int , const COLORREF *);
#define wglGetProcAddress _glplatform_wglGetProcAddress
extern PROC (*wglGetProcAddress)(LPCSTR);
#define wglMakeCurrent _glplatform_wglMakeCurrent
extern BOOL (*wglMakeCurrent)(HDC, HGLRC);
#define wglRealizeLayerPalette _glplatform_wglRealizeLayerPalette
extern BOOL (*wglRealizeLayerPalette)(HDC, int , BOOL);
#define wglSetLayerPaletteEntries _glplatform_wglSetLayerPaletteEntries
extern int (*wglSetLayerPaletteEntries)(HDC, int , int , int , const COLORREF *);
#define wglShareLists _glplatform_wglShareLists
extern BOOL (*wglShareLists)(HGLRC, HGLRC);
#define wglSwapLayerBuffers _glplatform_wglSwapLayerBuffers
extern BOOL (*wglSwapLayerBuffers)(HDC, UINT);
#define wglUseFontBitmaps _glplatform_wglUseFontBitmaps
extern BOOL (*wglUseFontBitmaps)(HDC, DWORD, DWORD, DWORD);
#define wglUseFontBitmapsA _glplatform_wglUseFontBitmapsA
extern BOOL (*wglUseFontBitmapsA)(HDC, DWORD, DWORD, DWORD);
#define wglUseFontBitmapsW _glplatform_wglUseFontBitmapsW
extern BOOL (*wglUseFontBitmapsW)(HDC, DWORD, DWORD, DWORD);
#define wglUseFontOutlines _glplatform_wglUseFontOutlines
extern BOOL (*wglUseFontOutlines)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT);
#define wglUseFontOutlinesA _glplatform_wglUseFontOutlinesA
extern BOOL (*wglUseFontOutlinesA)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT);
#define wglUseFontOutlinesW _glplatform_wglUseFontOutlinesW
extern BOOL (*wglUseFontOutlinesW)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT);


#if defined(GLPLATFORM_ENABLE_WGL_3DFX_multisample)
extern bool GLPLATFORM_WGL_3DFX_multisample;

#define WGL_SAMPLES_3DFX 0x2061
#define WGL_SAMPLE_BUFFERS_3DFX 0x2060

#endif

#if defined(GLPLATFORM_ENABLE_WGL_3DL_stereo_control)
extern bool GLPLATFORM_WGL_3DL_stereo_control;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_STEREO_EMITTER_DISABLE_3DL 0x2056
#define WGL_STEREO_EMITTER_ENABLE_3DL 0x2055
#define WGL_STEREO_POLARITY_INVERT_3DL 0x2058
#define WGL_STEREO_POLARITY_NORMAL_3DL 0x2057

#define wglSetStereoEmitterState3DL _glplatform_wglSetStereoEmitterState3DL
extern BOOL (*wglSetStereoEmitterState3DL)(HDC, UINT);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_AMD_gpu_association)
extern bool GLPLATFORM_WGL_AMD_gpu_association;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif
#ifndef GLPLATFORM_TYPE_INT
#define GLPLATFORM_TYPE_INT

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif
#ifndef GLPLATFORM_TYPE_VOID
#define GLPLATFORM_TYPE_VOID

#endif

#define WGL_GPU_CLOCK_AMD 0x21a4
#define WGL_GPU_FASTEST_TARGET_GPUS_AMD 0x21a2
#define WGL_GPU_NUM_PIPES_AMD 0x21a5
#define WGL_GPU_NUM_RB_AMD 0x21a7
#define WGL_GPU_NUM_SIMD_AMD 0x21a6
#define WGL_GPU_NUM_SPI_AMD 0x21a8
#define WGL_GPU_OPENGL_VERSION_STRING_AMD 0x1f02
#define WGL_GPU_RAM_AMD 0x21a3
#define WGL_GPU_RENDERER_STRING_AMD 0x1f01
#define WGL_GPU_VENDOR_AMD 0x1f00

#define wglBlitContextFramebufferAMD _glplatform_wglBlitContextFramebufferAMD
extern VOID (*wglBlitContextFramebufferAMD)(HGLRC, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define wglCreateAssociatedContextAMD _glplatform_wglCreateAssociatedContextAMD
extern HGLRC (*wglCreateAssociatedContextAMD)(UINT);
#define wglCreateAssociatedContextAttribsAMD _glplatform_wglCreateAssociatedContextAttribsAMD
extern HGLRC (*wglCreateAssociatedContextAttribsAMD)(UINT, HGLRC, const int *);
#define wglDeleteAssociatedContextAMD _glplatform_wglDeleteAssociatedContextAMD
extern BOOL (*wglDeleteAssociatedContextAMD)(HGLRC);
#define wglGetContextGPUIDAMD _glplatform_wglGetContextGPUIDAMD
extern UINT (*wglGetContextGPUIDAMD)(HGLRC);
#define wglGetCurrentAssociatedContextAMD _glplatform_wglGetCurrentAssociatedContextAMD
extern HGLRC (*wglGetCurrentAssociatedContextAMD)();
#define wglGetGPUIDsAMD _glplatform_wglGetGPUIDsAMD
extern UINT (*wglGetGPUIDsAMD)(UINT, UINT *);
#define wglGetGPUInfoAMD _glplatform_wglGetGPUInfoAMD
extern INT (*wglGetGPUInfoAMD)(UINT, int , GLenum, UINT, void *);
#define wglMakeAssociatedContextCurrentAMD _glplatform_wglMakeAssociatedContextCurrentAMD
extern BOOL (*wglMakeAssociatedContextCurrentAMD)(HGLRC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_buffer_region)
extern bool GLPLATFORM_WGL_ARB_buffer_region;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HANDLE
#define GLPLATFORM_TYPE_HANDLE

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif
#ifndef GLPLATFORM_TYPE_VOID
#define GLPLATFORM_TYPE_VOID

#endif

#define WGL_BACK_COLOR_BUFFER_BIT_ARB 0x2
#define WGL_DEPTH_BUFFER_BIT_ARB 0x4
#define WGL_FRONT_COLOR_BUFFER_BIT_ARB 0x1
#define WGL_STENCIL_BUFFER_BIT_ARB 0x8

#define wglCreateBufferRegionARB _glplatform_wglCreateBufferRegionARB
extern HANDLE (*wglCreateBufferRegionARB)(HDC, int , UINT);
#define wglDeleteBufferRegionARB _glplatform_wglDeleteBufferRegionARB
extern VOID (*wglDeleteBufferRegionARB)(HANDLE);
#define wglRestoreBufferRegionARB _glplatform_wglRestoreBufferRegionARB
extern BOOL (*wglRestoreBufferRegionARB)(HANDLE, int , int , int , int , int , int );
#define wglSaveBufferRegionARB _glplatform_wglSaveBufferRegionARB
extern BOOL (*wglSaveBufferRegionARB)(HANDLE, int , int , int , int );
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_context_flush_control)
extern bool GLPLATFORM_WGL_ARB_context_flush_control;

#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB 0x2097
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB 0x0

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_create_context)
extern bool GLPLATFORM_WGL_ARB_create_context;
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x1
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x2
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092

#define wglCreateContextAttribsARB _glplatform_wglCreateContextAttribsARB
extern HGLRC (*wglCreateContextAttribsARB)(HDC, HGLRC, const int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_create_context_profile)
extern bool GLPLATFORM_WGL_ARB_create_context_profile;

#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x2
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x1
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_create_context_robustness)
extern bool GLPLATFORM_WGL_ARB_create_context_robustness;

#define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x4
#define WGL_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define WGL_NO_RESET_NOTIFICATION_ARB 0x8261

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_extensions_string)
extern bool GLPLATFORM_WGL_ARB_extensions_string;
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif


#define wglGetExtensionsStringARB _glplatform_wglGetExtensionsStringARB
extern const char * (*wglGetExtensionsStringARB)(HDC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_framebuffer_sRGB)
extern bool GLPLATFORM_WGL_ARB_framebuffer_sRGB;

#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20a9

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_make_current_read)
extern bool GLPLATFORM_WGL_ARB_make_current_read;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif


#define wglGetCurrentReadDCARB _glplatform_wglGetCurrentReadDCARB
extern HDC (*wglGetCurrentReadDCARB)();
#define wglMakeContextCurrentARB _glplatform_wglMakeContextCurrentARB
extern BOOL (*wglMakeContextCurrentARB)(HDC, HDC, HGLRC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_multisample)
extern bool GLPLATFORM_WGL_ARB_multisample;

#define WGL_SAMPLES_ARB 0x2042
#define WGL_SAMPLE_BUFFERS_ARB 0x2041

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_pbuffer)
extern bool GLPLATFORM_WGL_ARB_pbuffer;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HPBUFFERARB
#define GLPLATFORM_TYPE_HPBUFFERARB
DECLARE_HANDLE(HPBUFFERARB);
#endif

#define WGL_DRAW_TO_PBUFFER_ARB 0x202d
#define WGL_MAX_PBUFFER_HEIGHT_ARB 0x2030
#define WGL_MAX_PBUFFER_PIXELS_ARB 0x202e
#define WGL_MAX_PBUFFER_WIDTH_ARB 0x202f
#define WGL_PBUFFER_HEIGHT_ARB 0x2035
#define WGL_PBUFFER_LARGEST_ARB 0x2033
#define WGL_PBUFFER_LOST_ARB 0x2036
#define WGL_PBUFFER_WIDTH_ARB 0x2034

#define wglCreatePbufferARB _glplatform_wglCreatePbufferARB
extern HPBUFFERARB (*wglCreatePbufferARB)(HDC, int , int , int , const int *);
#define wglDestroyPbufferARB _glplatform_wglDestroyPbufferARB
extern BOOL (*wglDestroyPbufferARB)(HPBUFFERARB);
#define wglGetPbufferDCARB _glplatform_wglGetPbufferDCARB
extern HDC (*wglGetPbufferDCARB)(HPBUFFERARB);
#define wglQueryPbufferARB _glplatform_wglQueryPbufferARB
extern BOOL (*wglQueryPbufferARB)(HPBUFFERARB, int , int *);
#define wglReleasePbufferDCARB _glplatform_wglReleasePbufferDCARB
extern int (*wglReleasePbufferDCARB)(HPBUFFERARB, HDC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_pixel_format)
extern bool GLPLATFORM_WGL_ARB_pixel_format;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_FLOAT
#define GLPLATFORM_TYPE_FLOAT

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_ACCELERATION_ARB 0x2003
#define WGL_ACCUM_ALPHA_BITS_ARB 0x2021
#define WGL_ACCUM_BITS_ARB 0x201d
#define WGL_ACCUM_BLUE_BITS_ARB 0x2020
#define WGL_ACCUM_GREEN_BITS_ARB 0x201f
#define WGL_ACCUM_RED_BITS_ARB 0x201e
#define WGL_ALPHA_BITS_ARB 0x201b
#define WGL_ALPHA_SHIFT_ARB 0x201c
#define WGL_AUX_BUFFERS_ARB 0x2024
#define WGL_BLUE_BITS_ARB 0x2019
#define WGL_BLUE_SHIFT_ARB 0x201a
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_DRAW_TO_BITMAP_ARB 0x2002
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_FULL_ACCELERATION_ARB 0x2027
#define WGL_GENERIC_ACCELERATION_ARB 0x2026
#define WGL_GREEN_BITS_ARB 0x2017
#define WGL_GREEN_SHIFT_ARB 0x2018
#define WGL_NEED_PALETTE_ARB 0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB 0x2005
#define WGL_NO_ACCELERATION_ARB 0x2025
#define WGL_NUMBER_OVERLAYS_ARB 0x2008
#define WGL_NUMBER_PIXEL_FORMATS_ARB 0x2000
#define WGL_NUMBER_UNDERLAYS_ARB 0x2009
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_RED_BITS_ARB 0x2015
#define WGL_RED_SHIFT_ARB 0x2016
#define WGL_SHARE_ACCUM_ARB 0x200e
#define WGL_SHARE_DEPTH_ARB 0x200c
#define WGL_SHARE_STENCIL_ARB 0x200d
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_STEREO_ARB 0x2012
#define WGL_SUPPORT_GDI_ARB 0x200f
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_SWAP_COPY_ARB 0x2029
#define WGL_SWAP_EXCHANGE_ARB 0x2028
#define WGL_SWAP_LAYER_BUFFERS_ARB 0x2006
#define WGL_SWAP_METHOD_ARB 0x2007
#define WGL_SWAP_UNDEFINED_ARB 0x202a
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB 0x203a
#define WGL_TRANSPARENT_ARB 0x200a
#define WGL_TRANSPARENT_BLUE_VALUE_ARB 0x2039
#define WGL_TRANSPARENT_GREEN_VALUE_ARB 0x2038
#define WGL_TRANSPARENT_INDEX_VALUE_ARB 0x203b
#define WGL_TRANSPARENT_RED_VALUE_ARB 0x2037
#define WGL_TYPE_COLORINDEX_ARB 0x202c
#define WGL_TYPE_RGBA_ARB 0x202b

#define wglChoosePixelFormatARB _glplatform_wglChoosePixelFormatARB
extern BOOL (*wglChoosePixelFormatARB)(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
#define wglGetPixelFormatAttribfvARB _glplatform_wglGetPixelFormatAttribfvARB
extern BOOL (*wglGetPixelFormatAttribfvARB)(HDC, int , int , UINT, const int *, FLOAT *);
#define wglGetPixelFormatAttribivARB _glplatform_wglGetPixelFormatAttribivARB
extern BOOL (*wglGetPixelFormatAttribivARB)(HDC, int , int , UINT, const int *, int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_pixel_format_float)
extern bool GLPLATFORM_WGL_ARB_pixel_format_float;

#define WGL_TYPE_RGBA_FLOAT_ARB 0x21a0

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_render_texture)
extern bool GLPLATFORM_WGL_ARB_render_texture;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HPBUFFERARB
#define GLPLATFORM_TYPE_HPBUFFERARB
DECLARE_HANDLE(HPBUFFERARB);
#endif

#define WGL_AUX0_ARB 0x2087
#define WGL_AUX1_ARB 0x2088
#define WGL_AUX2_ARB 0x2089
#define WGL_AUX3_ARB 0x208a
#define WGL_AUX4_ARB 0x208b
#define WGL_AUX5_ARB 0x208c
#define WGL_AUX6_ARB 0x208d
#define WGL_AUX7_ARB 0x208e
#define WGL_AUX8_ARB 0x208f
#define WGL_AUX9_ARB 0x2090
#define WGL_BACK_LEFT_ARB 0x2085
#define WGL_BACK_RIGHT_ARB 0x2086
#define WGL_BIND_TO_TEXTURE_RGBA_ARB 0x2071
#define WGL_BIND_TO_TEXTURE_RGB_ARB 0x2070
#define WGL_CUBE_MAP_FACE_ARB 0x207c
#define WGL_FRONT_LEFT_ARB 0x2083
#define WGL_FRONT_RIGHT_ARB 0x2084
#define WGL_MIPMAP_LEVEL_ARB 0x207b
#define WGL_MIPMAP_TEXTURE_ARB 0x2074
#define WGL_NO_TEXTURE_ARB 0x2077
#define WGL_TEXTURE_1D_ARB 0x2079
#define WGL_TEXTURE_2D_ARB 0x207a
#define WGL_TEXTURE_CUBE_MAP_ARB 0x2078
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x207e
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x2080
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x2082
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x207d
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x207f
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x2081
#define WGL_TEXTURE_FORMAT_ARB 0x2072
#define WGL_TEXTURE_RGBA_ARB 0x2076
#define WGL_TEXTURE_RGB_ARB 0x2075
#define WGL_TEXTURE_TARGET_ARB 0x2073

#define wglBindTexImageARB _glplatform_wglBindTexImageARB
extern BOOL (*wglBindTexImageARB)(HPBUFFERARB, int );
#define wglReleaseTexImageARB _glplatform_wglReleaseTexImageARB
extern BOOL (*wglReleaseTexImageARB)(HPBUFFERARB, int );
#define wglSetPbufferAttribARB _glplatform_wglSetPbufferAttribARB
extern BOOL (*wglSetPbufferAttribARB)(HPBUFFERARB, const int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_robustness_application_isolation)
extern bool GLPLATFORM_WGL_ARB_robustness_application_isolation;

#define WGL_CONTEXT_RESET_ISOLATION_BIT_ARB 0x8

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ARB_robustness_share_group_isolation)
extern bool GLPLATFORM_WGL_ARB_robustness_share_group_isolation;

#define WGL_CONTEXT_RESET_ISOLATION_BIT_ARB 0x8

#endif

#if defined(GLPLATFORM_ENABLE_WGL_ATI_pixel_format_float)
extern bool GLPLATFORM_WGL_ATI_pixel_format_float;

#define WGL_TYPE_RGBA_FLOAT_ATI 0x21a0

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_create_context_es2_profile)
extern bool GLPLATFORM_WGL_EXT_create_context_es2_profile;

#define WGL_CONTEXT_ES2_PROFILE_BIT_EXT 0x4

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_create_context_es_profile)
extern bool GLPLATFORM_WGL_EXT_create_context_es_profile;

#define WGL_CONTEXT_ES_PROFILE_BIT_EXT 0x4

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_depth_float)
extern bool GLPLATFORM_WGL_EXT_depth_float;

#define WGL_DEPTH_FLOAT_EXT 0x2040

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_display_color_table)
extern bool GLPLATFORM_WGL_EXT_display_color_table;
#ifndef GLPLATFORM_TYPE_VOID
#define GLPLATFORM_TYPE_VOID

#endif


#define wglBindDisplayColorTableEXT _glplatform_wglBindDisplayColorTableEXT
extern GLboolean (*wglBindDisplayColorTableEXT)(GLushort);
#define wglCreateDisplayColorTableEXT _glplatform_wglCreateDisplayColorTableEXT
extern GLboolean (*wglCreateDisplayColorTableEXT)(GLushort);
#define wglDestroyDisplayColorTableEXT _glplatform_wglDestroyDisplayColorTableEXT
extern VOID (*wglDestroyDisplayColorTableEXT)(GLushort);
#define wglLoadDisplayColorTableEXT _glplatform_wglLoadDisplayColorTableEXT
extern GLboolean (*wglLoadDisplayColorTableEXT)(const GLushort *, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_extensions_string)
extern bool GLPLATFORM_WGL_EXT_extensions_string;


#define wglGetExtensionsStringEXT _glplatform_wglGetExtensionsStringEXT
extern const char * (*wglGetExtensionsStringEXT)();
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_framebuffer_sRGB)
extern bool GLPLATFORM_WGL_EXT_framebuffer_sRGB;

#define WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x20a9

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_make_current_read)
extern bool GLPLATFORM_WGL_EXT_make_current_read;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif


#define wglGetCurrentReadDCEXT _glplatform_wglGetCurrentReadDCEXT
extern HDC (*wglGetCurrentReadDCEXT)();
#define wglMakeContextCurrentEXT _glplatform_wglMakeContextCurrentEXT
extern BOOL (*wglMakeContextCurrentEXT)(HDC, HDC, HGLRC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_multisample)
extern bool GLPLATFORM_WGL_EXT_multisample;

#define WGL_SAMPLES_EXT 0x2042
#define WGL_SAMPLE_BUFFERS_EXT 0x2041

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_pbuffer)
extern bool GLPLATFORM_WGL_EXT_pbuffer;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HPBUFFEREXT
#define GLPLATFORM_TYPE_HPBUFFEREXT
DECLARE_HANDLE(HPBUFFEREXT);
#endif

#define WGL_DRAW_TO_PBUFFER_EXT 0x202d
#define WGL_MAX_PBUFFER_HEIGHT_EXT 0x2030
#define WGL_MAX_PBUFFER_PIXELS_EXT 0x202e
#define WGL_MAX_PBUFFER_WIDTH_EXT 0x202f
#define WGL_OPTIMAL_PBUFFER_HEIGHT_EXT 0x2032
#define WGL_OPTIMAL_PBUFFER_WIDTH_EXT 0x2031
#define WGL_PBUFFER_HEIGHT_EXT 0x2035
#define WGL_PBUFFER_LARGEST_EXT 0x2033
#define WGL_PBUFFER_WIDTH_EXT 0x2034

#define wglCreatePbufferEXT _glplatform_wglCreatePbufferEXT
extern HPBUFFEREXT (*wglCreatePbufferEXT)(HDC, int , int , int , const int *);
#define wglDestroyPbufferEXT _glplatform_wglDestroyPbufferEXT
extern BOOL (*wglDestroyPbufferEXT)(HPBUFFEREXT);
#define wglGetPbufferDCEXT _glplatform_wglGetPbufferDCEXT
extern HDC (*wglGetPbufferDCEXT)(HPBUFFEREXT);
#define wglQueryPbufferEXT _glplatform_wglQueryPbufferEXT
extern BOOL (*wglQueryPbufferEXT)(HPBUFFEREXT, int , int *);
#define wglReleasePbufferDCEXT _glplatform_wglReleasePbufferDCEXT
extern int (*wglReleasePbufferDCEXT)(HPBUFFEREXT, HDC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_pixel_format)
extern bool GLPLATFORM_WGL_EXT_pixel_format;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_FLOAT
#define GLPLATFORM_TYPE_FLOAT

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_ACCELERATION_EXT 0x2003
#define WGL_ACCUM_ALPHA_BITS_EXT 0x2021
#define WGL_ACCUM_BITS_EXT 0x201d
#define WGL_ACCUM_BLUE_BITS_EXT 0x2020
#define WGL_ACCUM_GREEN_BITS_EXT 0x201f
#define WGL_ACCUM_RED_BITS_EXT 0x201e
#define WGL_ALPHA_BITS_EXT 0x201b
#define WGL_ALPHA_SHIFT_EXT 0x201c
#define WGL_AUX_BUFFERS_EXT 0x2024
#define WGL_BLUE_BITS_EXT 0x2019
#define WGL_BLUE_SHIFT_EXT 0x201a
#define WGL_COLOR_BITS_EXT 0x2014
#define WGL_DEPTH_BITS_EXT 0x2022
#define WGL_DOUBLE_BUFFER_EXT 0x2011
#define WGL_DRAW_TO_BITMAP_EXT 0x2002
#define WGL_DRAW_TO_WINDOW_EXT 0x2001
#define WGL_FULL_ACCELERATION_EXT 0x2027
#define WGL_GENERIC_ACCELERATION_EXT 0x2026
#define WGL_GREEN_BITS_EXT 0x2017
#define WGL_GREEN_SHIFT_EXT 0x2018
#define WGL_NEED_PALETTE_EXT 0x2004
#define WGL_NEED_SYSTEM_PALETTE_EXT 0x2005
#define WGL_NO_ACCELERATION_EXT 0x2025
#define WGL_NUMBER_OVERLAYS_EXT 0x2008
#define WGL_NUMBER_PIXEL_FORMATS_EXT 0x2000
#define WGL_NUMBER_UNDERLAYS_EXT 0x2009
#define WGL_PIXEL_TYPE_EXT 0x2013
#define WGL_RED_BITS_EXT 0x2015
#define WGL_RED_SHIFT_EXT 0x2016
#define WGL_SHARE_ACCUM_EXT 0x200e
#define WGL_SHARE_DEPTH_EXT 0x200c
#define WGL_SHARE_STENCIL_EXT 0x200d
#define WGL_STENCIL_BITS_EXT 0x2023
#define WGL_STEREO_EXT 0x2012
#define WGL_SUPPORT_GDI_EXT 0x200f
#define WGL_SUPPORT_OPENGL_EXT 0x2010
#define WGL_SWAP_COPY_EXT 0x2029
#define WGL_SWAP_EXCHANGE_EXT 0x2028
#define WGL_SWAP_LAYER_BUFFERS_EXT 0x2006
#define WGL_SWAP_METHOD_EXT 0x2007
#define WGL_SWAP_UNDEFINED_EXT 0x202a
#define WGL_TRANSPARENT_EXT 0x200a
#define WGL_TRANSPARENT_VALUE_EXT 0x200b
#define WGL_TYPE_COLORINDEX_EXT 0x202c
#define WGL_TYPE_RGBA_EXT 0x202b

#define wglChoosePixelFormatEXT _glplatform_wglChoosePixelFormatEXT
extern BOOL (*wglChoosePixelFormatEXT)(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
#define wglGetPixelFormatAttribfvEXT _glplatform_wglGetPixelFormatAttribfvEXT
extern BOOL (*wglGetPixelFormatAttribfvEXT)(HDC, int , int , UINT, int *, FLOAT *);
#define wglGetPixelFormatAttribivEXT _glplatform_wglGetPixelFormatAttribivEXT
extern BOOL (*wglGetPixelFormatAttribivEXT)(HDC, int , int , UINT, int *, int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_pixel_format_packed_float)
extern bool GLPLATFORM_WGL_EXT_pixel_format_packed_float;

#define WGL_TYPE_RGBA_UNSIGNED_FLOAT_EXT 0x20a8

#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_swap_control)
extern bool GLPLATFORM_WGL_EXT_swap_control;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif


#define wglGetSwapIntervalEXT _glplatform_wglGetSwapIntervalEXT
extern int (*wglGetSwapIntervalEXT)();
#define wglSwapIntervalEXT _glplatform_wglSwapIntervalEXT
extern BOOL (*wglSwapIntervalEXT)(int );
#endif

#if defined(GLPLATFORM_ENABLE_WGL_EXT_swap_control_tear)
extern bool GLPLATFORM_WGL_EXT_swap_control_tear;


#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_digital_video_control)
extern bool GLPLATFORM_WGL_I3D_digital_video_control;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif

#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D 0x2050
#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D 0x2051
#define WGL_DIGITAL_VIDEO_CURSOR_INCLUDED_I3D 0x2052
#define WGL_DIGITAL_VIDEO_GAMMA_CORRECTED_I3D 0x2053

#define wglGetDigitalVideoParametersI3D _glplatform_wglGetDigitalVideoParametersI3D
extern BOOL (*wglGetDigitalVideoParametersI3D)(HDC, int , int *);
#define wglSetDigitalVideoParametersI3D _glplatform_wglSetDigitalVideoParametersI3D
extern BOOL (*wglSetDigitalVideoParametersI3D)(HDC, int , const int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_gamma)
extern bool GLPLATFORM_WGL_I3D_gamma;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_USHORT
#define GLPLATFORM_TYPE_USHORT

#endif

#define WGL_GAMMA_EXCLUDE_DESKTOP_I3D 0x204f
#define WGL_GAMMA_TABLE_SIZE_I3D 0x204e

#define wglGetGammaTableI3D _glplatform_wglGetGammaTableI3D
extern BOOL (*wglGetGammaTableI3D)(HDC, int , USHORT *, USHORT *, USHORT *);
#define wglGetGammaTableParametersI3D _glplatform_wglGetGammaTableParametersI3D
extern BOOL (*wglGetGammaTableParametersI3D)(HDC, int , int *);
#define wglSetGammaTableI3D _glplatform_wglSetGammaTableI3D
extern BOOL (*wglSetGammaTableI3D)(HDC, int , const USHORT *, const USHORT *, const USHORT *);
#define wglSetGammaTableParametersI3D _glplatform_wglSetGammaTableParametersI3D
extern BOOL (*wglSetGammaTableParametersI3D)(HDC, int , const int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_genlock)
extern bool GLPLATFORM_WGL_I3D_genlock;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_GENLOCK_SOURCE_DIGITAL_FIELD_I3D 0x2049
#define WGL_GENLOCK_SOURCE_DIGITAL_SYNC_I3D 0x2048
#define WGL_GENLOCK_SOURCE_EDGE_BOTH_I3D 0x204c
#define WGL_GENLOCK_SOURCE_EDGE_FALLING_I3D 0x204a
#define WGL_GENLOCK_SOURCE_EDGE_RISING_I3D 0x204b
#define WGL_GENLOCK_SOURCE_EXTERNAL_FIELD_I3D 0x2046
#define WGL_GENLOCK_SOURCE_EXTERNAL_SYNC_I3D 0x2045
#define WGL_GENLOCK_SOURCE_EXTERNAL_TTL_I3D 0x2047
#define WGL_GENLOCK_SOURCE_MULTIVIEW_I3D 0x2044

#define wglDisableGenlockI3D _glplatform_wglDisableGenlockI3D
extern BOOL (*wglDisableGenlockI3D)(HDC);
#define wglEnableGenlockI3D _glplatform_wglEnableGenlockI3D
extern BOOL (*wglEnableGenlockI3D)(HDC);
#define wglGenlockSampleRateI3D _glplatform_wglGenlockSampleRateI3D
extern BOOL (*wglGenlockSampleRateI3D)(HDC, UINT);
#define wglGenlockSourceDelayI3D _glplatform_wglGenlockSourceDelayI3D
extern BOOL (*wglGenlockSourceDelayI3D)(HDC, UINT);
#define wglGenlockSourceEdgeI3D _glplatform_wglGenlockSourceEdgeI3D
extern BOOL (*wglGenlockSourceEdgeI3D)(HDC, UINT);
#define wglGenlockSourceI3D _glplatform_wglGenlockSourceI3D
extern BOOL (*wglGenlockSourceI3D)(HDC, UINT);
#define wglGetGenlockSampleRateI3D _glplatform_wglGetGenlockSampleRateI3D
extern BOOL (*wglGetGenlockSampleRateI3D)(HDC, UINT *);
#define wglGetGenlockSourceDelayI3D _glplatform_wglGetGenlockSourceDelayI3D
extern BOOL (*wglGetGenlockSourceDelayI3D)(HDC, UINT *);
#define wglGetGenlockSourceEdgeI3D _glplatform_wglGetGenlockSourceEdgeI3D
extern BOOL (*wglGetGenlockSourceEdgeI3D)(HDC, UINT *);
#define wglGetGenlockSourceI3D _glplatform_wglGetGenlockSourceI3D
extern BOOL (*wglGetGenlockSourceI3D)(HDC, UINT *);
#define wglIsEnabledGenlockI3D _glplatform_wglIsEnabledGenlockI3D
extern BOOL (*wglIsEnabledGenlockI3D)(HDC, BOOL *);
#define wglQueryGenlockMaxSourceDelayI3D _glplatform_wglQueryGenlockMaxSourceDelayI3D
extern BOOL (*wglQueryGenlockMaxSourceDelayI3D)(HDC, UINT *, UINT *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_image_buffer)
extern bool GLPLATFORM_WGL_I3D_image_buffer;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_DWORD
#define GLPLATFORM_TYPE_DWORD

#endif
#ifndef GLPLATFORM_TYPE_HANDLE
#define GLPLATFORM_TYPE_HANDLE

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_LPVOID
#define GLPLATFORM_TYPE_LPVOID

#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_IMAGE_BUFFER_LOCK_I3D 0x2
#define WGL_IMAGE_BUFFER_MIN_ACCESS_I3D 0x1

#define wglAssociateImageBufferEventsI3D _glplatform_wglAssociateImageBufferEventsI3D
extern BOOL (*wglAssociateImageBufferEventsI3D)(HDC, const HANDLE *, const LPVOID *, const DWORD *, UINT);
#define wglCreateImageBufferI3D _glplatform_wglCreateImageBufferI3D
extern LPVOID (*wglCreateImageBufferI3D)(HDC, DWORD, UINT);
#define wglDestroyImageBufferI3D _glplatform_wglDestroyImageBufferI3D
extern BOOL (*wglDestroyImageBufferI3D)(HDC, LPVOID);
#define wglReleaseImageBufferEventsI3D _glplatform_wglReleaseImageBufferEventsI3D
extern BOOL (*wglReleaseImageBufferEventsI3D)(HDC, const LPVOID *, UINT);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_swap_frame_lock)
extern bool GLPLATFORM_WGL_I3D_swap_frame_lock;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif


#define wglDisableFrameLockI3D _glplatform_wglDisableFrameLockI3D
extern BOOL (*wglDisableFrameLockI3D)();
#define wglEnableFrameLockI3D _glplatform_wglEnableFrameLockI3D
extern BOOL (*wglEnableFrameLockI3D)();
#define wglIsEnabledFrameLockI3D _glplatform_wglIsEnabledFrameLockI3D
extern BOOL (*wglIsEnabledFrameLockI3D)(BOOL *);
#define wglQueryFrameLockMasterI3D _glplatform_wglQueryFrameLockMasterI3D
extern BOOL (*wglQueryFrameLockMasterI3D)(BOOL *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_I3D_swap_frame_usage)
extern bool GLPLATFORM_WGL_I3D_swap_frame_usage;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_DWORD
#define GLPLATFORM_TYPE_DWORD

#endif


#define wglBeginFrameTrackingI3D _glplatform_wglBeginFrameTrackingI3D
extern BOOL (*wglBeginFrameTrackingI3D)();
#define wglEndFrameTrackingI3D _glplatform_wglEndFrameTrackingI3D
extern BOOL (*wglEndFrameTrackingI3D)();
#define wglGetFrameUsageI3D _glplatform_wglGetFrameUsageI3D
extern BOOL (*wglGetFrameUsageI3D)(float *);
#define wglQueryFrameTrackingI3D _glplatform_wglQueryFrameTrackingI3D
extern BOOL (*wglQueryFrameTrackingI3D)(DWORD *, DWORD *, float *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_DX_interop)
extern bool GLPLATFORM_WGL_NV_DX_interop;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HANDLE
#define GLPLATFORM_TYPE_HANDLE

#endif

#define WGL_ACCESS_READ_ONLY_NV 0x0
#define WGL_ACCESS_READ_WRITE_NV 0x1
#define WGL_ACCESS_WRITE_DISCARD_NV 0x2

#define wglDXCloseDeviceNV _glplatform_wglDXCloseDeviceNV
extern BOOL (*wglDXCloseDeviceNV)(HANDLE);
#define wglDXLockObjectsNV _glplatform_wglDXLockObjectsNV
extern BOOL (*wglDXLockObjectsNV)(HANDLE, GLint, HANDLE *);
#define wglDXObjectAccessNV _glplatform_wglDXObjectAccessNV
extern BOOL (*wglDXObjectAccessNV)(HANDLE, GLenum);
#define wglDXOpenDeviceNV _glplatform_wglDXOpenDeviceNV
extern HANDLE (*wglDXOpenDeviceNV)(void *);
#define wglDXRegisterObjectNV _glplatform_wglDXRegisterObjectNV
extern HANDLE (*wglDXRegisterObjectNV)(HANDLE, void *, GLuint, GLenum, GLenum);
#define wglDXSetResourceShareHandleNV _glplatform_wglDXSetResourceShareHandleNV
extern BOOL (*wglDXSetResourceShareHandleNV)(void *, HANDLE);
#define wglDXUnlockObjectsNV _glplatform_wglDXUnlockObjectsNV
extern BOOL (*wglDXUnlockObjectsNV)(HANDLE, GLint, HANDLE *);
#define wglDXUnregisterObjectNV _glplatform_wglDXUnregisterObjectNV
extern BOOL (*wglDXUnregisterObjectNV)(HANDLE, HANDLE);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_DX_interop2)
extern bool GLPLATFORM_WGL_NV_DX_interop2;


#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_copy_image)
extern bool GLPLATFORM_WGL_NV_copy_image;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HGLRC
#define GLPLATFORM_TYPE_HGLRC

#endif


#define wglCopyImageSubDataNV _glplatform_wglCopyImageSubDataNV
extern BOOL (*wglCopyImageSubDataNV)(HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_delay_before_swap)
extern bool GLPLATFORM_WGL_NV_delay_before_swap;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif


#define wglDelayBeforeSwapNV _glplatform_wglDelayBeforeSwapNV
extern BOOL (*wglDelayBeforeSwapNV)(HDC, GLfloat);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_float_buffer)
extern bool GLPLATFORM_WGL_NV_float_buffer;

#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV 0x20b4
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV 0x20b3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV 0x20b2
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV 0x20b1
#define WGL_FLOAT_COMPONENTS_NV 0x20b0
#define WGL_TEXTURE_FLOAT_RGBA_NV 0x20b8
#define WGL_TEXTURE_FLOAT_RGB_NV 0x20b7
#define WGL_TEXTURE_FLOAT_RG_NV 0x20b6
#define WGL_TEXTURE_FLOAT_R_NV 0x20b5

#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_gpu_affinity)
extern bool GLPLATFORM_WGL_NV_gpu_affinity;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HGPUNV
#define GLPLATFORM_TYPE_HGPUNV
DECLARE_HANDLE(HGPUNV);
#endif
#ifndef GLPLATFORM_TYPE_PGPU_DEVICE
#define GLPLATFORM_TYPE_PGPU_DEVICE
typedef struct _GPU_DEVICE *PGPU_DEVICE;
#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif


#define wglCreateAffinityDCNV _glplatform_wglCreateAffinityDCNV
extern HDC (*wglCreateAffinityDCNV)(const HGPUNV *);
#define wglDeleteDCNV _glplatform_wglDeleteDCNV
extern BOOL (*wglDeleteDCNV)(HDC);
#define wglEnumGpuDevicesNV _glplatform_wglEnumGpuDevicesNV
extern BOOL (*wglEnumGpuDevicesNV)(HGPUNV, UINT, PGPU_DEVICE);
#define wglEnumGpusFromAffinityDCNV _glplatform_wglEnumGpusFromAffinityDCNV
extern BOOL (*wglEnumGpusFromAffinityDCNV)(HDC, UINT, HGPUNV *);
#define wglEnumGpusNV _glplatform_wglEnumGpusNV
extern BOOL (*wglEnumGpusNV)(UINT, HGPUNV *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_multisample_coverage)
extern bool GLPLATFORM_WGL_NV_multisample_coverage;

#define WGL_COLOR_SAMPLES_NV 0x20b9
#define WGL_COVERAGE_SAMPLES_NV 0x2042

#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_present_video)
extern bool GLPLATFORM_WGL_NV_present_video;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HVIDEOOUTPUTDEVICENV
#define GLPLATFORM_TYPE_HVIDEOOUTPUTDEVICENV
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
#endif

#define WGL_NUM_VIDEO_SLOTS_NV 0x20f0

#define wglBindVideoDeviceNV _glplatform_wglBindVideoDeviceNV
extern BOOL (*wglBindVideoDeviceNV)(HDC, unsigned int , HVIDEOOUTPUTDEVICENV, const int *);
#define wglEnumerateVideoDevicesNV _glplatform_wglEnumerateVideoDevicesNV
extern int (*wglEnumerateVideoDevicesNV)(HDC, HVIDEOOUTPUTDEVICENV *);
#define wglQueryCurrentContextNV _glplatform_wglQueryCurrentContextNV
extern BOOL (*wglQueryCurrentContextNV)(int , int *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_render_depth_texture)
extern bool GLPLATFORM_WGL_NV_render_depth_texture;

#define WGL_BIND_TO_TEXTURE_DEPTH_NV 0x20a3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV 0x20a4
#define WGL_DEPTH_COMPONENT_NV 0x20a7
#define WGL_DEPTH_TEXTURE_FORMAT_NV 0x20a5
#define WGL_TEXTURE_DEPTH_COMPONENT_NV 0x20a6

#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_render_texture_rectangle)
extern bool GLPLATFORM_WGL_NV_render_texture_rectangle;

#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV 0x20a1
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV 0x20a0
#define WGL_TEXTURE_RECTANGLE_NV 0x20a2

#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_swap_group)
extern bool GLPLATFORM_WGL_NV_swap_group;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif


#define wglBindSwapBarrierNV _glplatform_wglBindSwapBarrierNV
extern BOOL (*wglBindSwapBarrierNV)(GLuint, GLuint);
#define wglJoinSwapGroupNV _glplatform_wglJoinSwapGroupNV
extern BOOL (*wglJoinSwapGroupNV)(HDC, GLuint);
#define wglQueryFrameCountNV _glplatform_wglQueryFrameCountNV
extern BOOL (*wglQueryFrameCountNV)(HDC, GLuint *);
#define wglQueryMaxSwapGroupsNV _glplatform_wglQueryMaxSwapGroupsNV
extern BOOL (*wglQueryMaxSwapGroupsNV)(HDC, GLuint *, GLuint *);
#define wglQuerySwapGroupNV _glplatform_wglQuerySwapGroupNV
extern BOOL (*wglQuerySwapGroupNV)(HDC, GLuint *, GLuint *);
#define wglResetFrameCountNV _glplatform_wglResetFrameCountNV
extern BOOL (*wglResetFrameCountNV)(HDC);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_vertex_array_range)
extern bool GLPLATFORM_WGL_NV_vertex_array_range;


#define wglAllocateMemoryNV _glplatform_wglAllocateMemoryNV
extern void * (*wglAllocateMemoryNV)(GLsizei, GLfloat, GLfloat, GLfloat);
#define wglFreeMemoryNV _glplatform_wglFreeMemoryNV
extern void (*wglFreeMemoryNV)(void *);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_video_capture)
extern bool GLPLATFORM_WGL_NV_video_capture;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HVIDEOINPUTDEVICENV
#define GLPLATFORM_TYPE_HVIDEOINPUTDEVICENV
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
#endif
#ifndef GLPLATFORM_TYPE_UINT
#define GLPLATFORM_TYPE_UINT

#endif

#define WGL_NUM_VIDEO_CAPTURE_SLOTS_NV 0x20cf
#define WGL_UNIQUE_ID_NV 0x20ce

#define wglBindVideoCaptureDeviceNV _glplatform_wglBindVideoCaptureDeviceNV
extern BOOL (*wglBindVideoCaptureDeviceNV)(UINT, HVIDEOINPUTDEVICENV);
#define wglEnumerateVideoCaptureDevicesNV _glplatform_wglEnumerateVideoCaptureDevicesNV
extern UINT (*wglEnumerateVideoCaptureDevicesNV)(HDC, HVIDEOINPUTDEVICENV *);
#define wglLockVideoCaptureDeviceNV _glplatform_wglLockVideoCaptureDeviceNV
extern BOOL (*wglLockVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV);
#define wglQueryVideoCaptureDeviceNV _glplatform_wglQueryVideoCaptureDeviceNV
extern BOOL (*wglQueryVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV, int , int *);
#define wglReleaseVideoCaptureDeviceNV _glplatform_wglReleaseVideoCaptureDeviceNV
extern BOOL (*wglReleaseVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_NV_video_output)
extern bool GLPLATFORM_WGL_NV_video_output;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_HPBUFFERARB
#define GLPLATFORM_TYPE_HPBUFFERARB
DECLARE_HANDLE(HPBUFFERARB);
#endif
#ifndef GLPLATFORM_TYPE_HPVIDEODEV
#define GLPLATFORM_TYPE_HPVIDEODEV
DECLARE_HANDLE(HPVIDEODEV);
#endif

#define WGL_BIND_TO_VIDEO_RGBA_NV 0x20c1
#define WGL_BIND_TO_VIDEO_RGB_AND_DEPTH_NV 0x20c2
#define WGL_BIND_TO_VIDEO_RGB_NV 0x20c0
#define WGL_VIDEO_OUT_ALPHA_NV 0x20c4
#define WGL_VIDEO_OUT_COLOR_AND_ALPHA_NV 0x20c6
#define WGL_VIDEO_OUT_COLOR_AND_DEPTH_NV 0x20c7
#define WGL_VIDEO_OUT_COLOR_NV 0x20c3
#define WGL_VIDEO_OUT_DEPTH_NV 0x20c5
#define WGL_VIDEO_OUT_FIELD_1 0x20c9
#define WGL_VIDEO_OUT_FIELD_2 0x20ca
#define WGL_VIDEO_OUT_FRAME 0x20c8
#define WGL_VIDEO_OUT_STACKED_FIELDS_1_2 0x20cb
#define WGL_VIDEO_OUT_STACKED_FIELDS_2_1 0x20cc

#define wglBindVideoImageNV _glplatform_wglBindVideoImageNV
extern BOOL (*wglBindVideoImageNV)(HPVIDEODEV, HPBUFFERARB, int );
#define wglGetVideoDeviceNV _glplatform_wglGetVideoDeviceNV
extern BOOL (*wglGetVideoDeviceNV)(HDC, int , HPVIDEODEV *);
#define wglGetVideoInfoNV _glplatform_wglGetVideoInfoNV
extern BOOL (*wglGetVideoInfoNV)(HPVIDEODEV, unsigned long *, unsigned long *);
#define wglReleaseVideoDeviceNV _glplatform_wglReleaseVideoDeviceNV
extern BOOL (*wglReleaseVideoDeviceNV)(HPVIDEODEV);
#define wglReleaseVideoImageNV _glplatform_wglReleaseVideoImageNV
extern BOOL (*wglReleaseVideoImageNV)(HPBUFFERARB, int );
#define wglSendPbufferToVideoNV _glplatform_wglSendPbufferToVideoNV
extern BOOL (*wglSendPbufferToVideoNV)(HPBUFFERARB, int , unsigned long *, BOOL);
#endif

#if defined(GLPLATFORM_ENABLE_WGL_OML_sync_control)
extern bool GLPLATFORM_WGL_OML_sync_control;
#ifndef GLPLATFORM_TYPE_BOOL
#define GLPLATFORM_TYPE_BOOL

#endif
#ifndef GLPLATFORM_TYPE_HDC
#define GLPLATFORM_TYPE_HDC

#endif
#ifndef GLPLATFORM_TYPE_INT32
#define GLPLATFORM_TYPE_INT32

#endif
#ifndef GLPLATFORM_TYPE_INT64
#define GLPLATFORM_TYPE_INT64

#endif


#define wglGetMscRateOML _glplatform_wglGetMscRateOML
extern BOOL (*wglGetMscRateOML)(HDC, INT32 *, INT32 *);
#define wglGetSyncValuesOML _glplatform_wglGetSyncValuesOML
extern BOOL (*wglGetSyncValuesOML)(HDC, INT64 *, INT64 *, INT64 *);
#define wglSwapBuffersMscOML _glplatform_wglSwapBuffersMscOML
extern INT64 (*wglSwapBuffersMscOML)(HDC, INT64, INT64, INT64);
#define wglSwapLayerBuffersMscOML _glplatform_wglSwapLayerBuffersMscOML
extern INT64 (*wglSwapLayerBuffersMscOML)(HDC, int , INT64, INT64, INT64);
#define wglWaitForMscOML _glplatform_wglWaitForMscOML
extern BOOL (*wglWaitForMscOML)(HDC, INT64, INT64, INT64, INT64 *, INT64 *, INT64 *);
#define wglWaitForSbcOML _glplatform_wglWaitForSbcOML
extern BOOL (*wglWaitForSbcOML)(HDC, INT64, INT64 *, INT64 *, INT64 *);
#endif

bool glplatform_wgl_init(int maj, int min);

#ifdef __cplusplus
}
#endif
#endif
