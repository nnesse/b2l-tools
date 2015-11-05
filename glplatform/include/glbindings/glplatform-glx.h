#ifndef GL_BINDIFY_glx_H
#define GL_BINDIFY_glx_H
#ifdef __cplusplus
extern "C" {
#endif
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define GLX_EXTENSION_NAME "GLX"
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
#ifndef GLPLATFORM_GLX_VERSION
#define GLPLATFORM_GLX_VERSION 14
#endif
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_Font
#define GLPLATFORM_TYPE_Font

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif
#ifndef GLPLATFORM_TYPE_GLXFBConfig
#define GLPLATFORM_TYPE_GLXFBConfig
typedef struct __GLXFBConfigRec *GLXFBConfig;
#endif
#ifndef GLPLATFORM_TYPE_GLXPbuffer
#define GLPLATFORM_TYPE_GLXPbuffer
typedef XID GLXPbuffer;
#endif
#ifndef GLPLATFORM_TYPE_GLXPixmap
#define GLPLATFORM_TYPE_GLXPixmap
typedef XID GLXPixmap;
#endif
#ifndef GLPLATFORM_TYPE_GLXWindow
#define GLPLATFORM_TYPE_GLXWindow
typedef XID GLXWindow;
#endif
#ifndef GLPLATFORM_TYPE_Pixmap
#define GLPLATFORM_TYPE_Pixmap

#endif
#ifndef GLPLATFORM_TYPE_Window
#define GLPLATFORM_TYPE_Window

#endif
#ifndef GLPLATFORM_TYPE_XVisualInfo
#define GLPLATFORM_TYPE_XVisualInfo

#endif
#ifndef GLPLATFORM_TYPE___GLXextFuncPtr
#define GLPLATFORM_TYPE___GLXextFuncPtr
typedef void ( *__GLXextFuncPtr)(void);
#endif

#define GLX_ACCUM_ALPHA_SIZE 0x11
#define GLX_ACCUM_BLUE_SIZE 0x10
#define GLX_ACCUM_BUFFER_BIT 0x80
#define GLX_ACCUM_GREEN_SIZE 0xf
#define GLX_ACCUM_RED_SIZE 0xe
#define GLX_ALPHA_SIZE 0xb
#define GLX_AUX_BUFFERS 0x7
#define GLX_AUX_BUFFERS_BIT 0x10
#define GLX_BACK_LEFT_BUFFER_BIT 0x4
#define GLX_BACK_RIGHT_BUFFER_BIT 0x8
#define GLX_BAD_ATTRIBUTE 0x2
#define GLX_BAD_CONTEXT 0x5
#define GLX_BAD_ENUM 0x7
#define GLX_BAD_SCREEN 0x1
#define GLX_BAD_VALUE 0x6
#define GLX_BAD_VISUAL 0x4
#define GLX_BLUE_SIZE 0xa
#define GLX_BUFFER_SIZE 0x2
#define GLX_BufferSwapComplete 0x1
#define GLX_COLOR_INDEX_BIT 0x2
#define GLX_COLOR_INDEX_TYPE 0x8015
#define GLX_CONFIG_CAVEAT 0x20
#define GLX_DAMAGED 0x8020
#define GLX_DEPTH_BUFFER_BIT 0x20
#define GLX_DEPTH_SIZE 0xc
#define GLX_DIRECT_COLOR 0x8003
#define GLX_DONT_CARE 0xffffffff
#define GLX_DOUBLEBUFFER 0x5
#define GLX_DRAWABLE_TYPE 0x8010
#define GLX_EVENT_MASK 0x801f
#define GLX_EXTENSIONS 0x3
#define GLX_FBCONFIG_ID 0x8013
#define GLX_FRONT_LEFT_BUFFER_BIT 0x1
#define GLX_FRONT_RIGHT_BUFFER_BIT 0x2
#define GLX_GRAY_SCALE 0x8006
#define GLX_GREEN_SIZE 0x9
#define GLX_HEIGHT 0x801e
#define GLX_LARGEST_PBUFFER 0x801c
#define GLX_LEVEL 0x3
#define GLX_MAX_PBUFFER_HEIGHT 0x8017
#define GLX_MAX_PBUFFER_PIXELS 0x8018
#define GLX_MAX_PBUFFER_WIDTH 0x8016
#define GLX_NONE 0x8000
#define GLX_NON_CONFORMANT_CONFIG 0x800d
#define GLX_NO_EXTENSION 0x3
#define GLX_PBUFFER 0x8023
#define GLX_PBUFFER_BIT 0x4
#define GLX_PBUFFER_CLOBBER_MASK 0x8000000
#define GLX_PBUFFER_HEIGHT 0x8040
#define GLX_PBUFFER_WIDTH 0x8041
#define GLX_PIXMAP_BIT 0x2
#define GLX_PRESERVED_CONTENTS 0x801b
#define GLX_PSEUDO_COLOR 0x8004
#define GLX_PbufferClobber 0x0
#define GLX_RED_SIZE 0x8
#define GLX_RENDER_TYPE 0x8011
#define GLX_RGBA 0x4
#define GLX_RGBA_BIT 0x1
#define GLX_RGBA_TYPE 0x8014
#define GLX_SAMPLES 0x186a1
#define GLX_SAMPLE_BUFFERS 0x186a0
#define GLX_SAVED 0x8021
#define GLX_SCREEN 0x800c
#define GLX_SLOW_CONFIG 0x8001
#define GLX_STATIC_COLOR 0x8005
#define GLX_STATIC_GRAY 0x8007
#define GLX_STENCIL_BUFFER_BIT 0x40
#define GLX_STENCIL_SIZE 0xd
#define GLX_STEREO 0x6
#define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#define GLX_TRANSPARENT_BLUE_VALUE 0x27
#define GLX_TRANSPARENT_GREEN_VALUE 0x26
#define GLX_TRANSPARENT_INDEX 0x8009
#define GLX_TRANSPARENT_INDEX_VALUE 0x24
#define GLX_TRANSPARENT_RED_VALUE 0x25
#define GLX_TRANSPARENT_RGB 0x8008
#define GLX_TRANSPARENT_TYPE 0x23
#define GLX_TRUE_COLOR 0x8002
#define GLX_USE_GL 0x1
#define GLX_VENDOR 0x1
#define GLX_VERSION 0x2
#define GLX_VISUAL_ID 0x800b
#define GLX_WIDTH 0x801d
#define GLX_WINDOW 0x8022
#define GLX_WINDOW_BIT 0x1
#define GLX_X_RENDERABLE 0x8012
#define GLX_X_VISUAL_TYPE 0x22

#define glXChooseFBConfig _glplatform_glXChooseFBConfig
extern GLXFBConfig * (*glXChooseFBConfig)(Display *, int , const int *, int *);
#define glXChooseVisual _glplatform_glXChooseVisual
extern XVisualInfo * (*glXChooseVisual)(Display *, int , int *);
#define glXCopyContext _glplatform_glXCopyContext
extern void (*glXCopyContext)(Display *, GLXContext, GLXContext, unsigned long );
#define glXCreateContext _glplatform_glXCreateContext
extern GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool);
#define glXCreateGLXPixmap _glplatform_glXCreateGLXPixmap
extern GLXPixmap (*glXCreateGLXPixmap)(Display *, XVisualInfo *, Pixmap);
#define glXCreateNewContext _glplatform_glXCreateNewContext
extern GLXContext (*glXCreateNewContext)(Display *, GLXFBConfig, int , GLXContext, Bool);
#define glXCreatePbuffer _glplatform_glXCreatePbuffer
extern GLXPbuffer (*glXCreatePbuffer)(Display *, GLXFBConfig, const int *);
#define glXCreatePixmap _glplatform_glXCreatePixmap
extern GLXPixmap (*glXCreatePixmap)(Display *, GLXFBConfig, Pixmap, const int *);
#define glXCreateWindow _glplatform_glXCreateWindow
extern GLXWindow (*glXCreateWindow)(Display *, GLXFBConfig, Window, const int *);
#define glXDestroyContext _glplatform_glXDestroyContext
extern void (*glXDestroyContext)(Display *, GLXContext);
#define glXDestroyGLXPixmap _glplatform_glXDestroyGLXPixmap
extern void (*glXDestroyGLXPixmap)(Display *, GLXPixmap);
#define glXDestroyPbuffer _glplatform_glXDestroyPbuffer
extern void (*glXDestroyPbuffer)(Display *, GLXPbuffer);
#define glXDestroyPixmap _glplatform_glXDestroyPixmap
extern void (*glXDestroyPixmap)(Display *, GLXPixmap);
#define glXDestroyWindow _glplatform_glXDestroyWindow
extern void (*glXDestroyWindow)(Display *, GLXWindow);
#define glXGetClientString _glplatform_glXGetClientString
extern const char * (*glXGetClientString)(Display *, int );
#define glXGetConfig _glplatform_glXGetConfig
extern int (*glXGetConfig)(Display *, XVisualInfo *, int , int *);
#define glXGetCurrentContext _glplatform_glXGetCurrentContext
extern GLXContext (*glXGetCurrentContext)();
#define glXGetCurrentDisplay _glplatform_glXGetCurrentDisplay
extern Display * (*glXGetCurrentDisplay)();
#define glXGetCurrentDrawable _glplatform_glXGetCurrentDrawable
extern GLXDrawable (*glXGetCurrentDrawable)();
#define glXGetCurrentReadDrawable _glplatform_glXGetCurrentReadDrawable
extern GLXDrawable (*glXGetCurrentReadDrawable)();
#define glXGetFBConfigAttrib _glplatform_glXGetFBConfigAttrib
extern int (*glXGetFBConfigAttrib)(Display *, GLXFBConfig, int , int *);
#define glXGetFBConfigs _glplatform_glXGetFBConfigs
extern GLXFBConfig * (*glXGetFBConfigs)(Display *, int , int *);
#define glXGetProcAddress _glplatform_glXGetProcAddress
extern __GLXextFuncPtr (*glXGetProcAddress)(const GLubyte *);
#define glXGetSelectedEvent _glplatform_glXGetSelectedEvent
extern void (*glXGetSelectedEvent)(Display *, GLXDrawable, unsigned long *);
#define glXGetVisualFromFBConfig _glplatform_glXGetVisualFromFBConfig
extern XVisualInfo * (*glXGetVisualFromFBConfig)(Display *, GLXFBConfig);
#define glXIsDirect _glplatform_glXIsDirect
extern Bool (*glXIsDirect)(Display *, GLXContext);
#define glXMakeContextCurrent _glplatform_glXMakeContextCurrent
extern Bool (*glXMakeContextCurrent)(Display *, GLXDrawable, GLXDrawable, GLXContext);
#define glXMakeCurrent _glplatform_glXMakeCurrent
extern Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext);
#define glXQueryContext _glplatform_glXQueryContext
extern int (*glXQueryContext)(Display *, GLXContext, int , int *);
#define glXQueryDrawable _glplatform_glXQueryDrawable
extern void (*glXQueryDrawable)(Display *, GLXDrawable, int , unsigned int *);
#define glXQueryExtension _glplatform_glXQueryExtension
extern Bool (*glXQueryExtension)(Display *, int *, int *);
#define glXQueryExtensionsString _glplatform_glXQueryExtensionsString
extern const char * (*glXQueryExtensionsString)(Display *, int );
#define glXQueryServerString _glplatform_glXQueryServerString
extern const char * (*glXQueryServerString)(Display *, int , int );
#define glXQueryVersion _glplatform_glXQueryVersion
extern Bool (*glXQueryVersion)(Display *, int *, int *);
#define glXSelectEvent _glplatform_glXSelectEvent
extern void (*glXSelectEvent)(Display *, GLXDrawable, unsigned long );
#define glXSwapBuffers _glplatform_glXSwapBuffers
extern void (*glXSwapBuffers)(Display *, GLXDrawable);
#define glXUseXFont _glplatform_glXUseXFont
extern void (*glXUseXFont)(Font, int , int , int );
#define glXWaitGL _glplatform_glXWaitGL
extern void (*glXWaitGL)();
#define glXWaitX _glplatform_glXWaitX
extern void (*glXWaitX)();


#if defined(GLPLATFORM_ENABLE_GLX_3DFX_multisample)
extern bool GLPLATFORM_GLX_3DFX_multisample;

#define GLX_SAMPLES_3DFX 0x8051
#define GLX_SAMPLE_BUFFERS_3DFX 0x8050

#endif

#if defined(GLPLATFORM_ENABLE_GLX_AMD_gpu_association)
extern bool GLPLATFORM_GLX_AMD_gpu_association;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif

#define GLX_GPU_CLOCK_AMD 0x21a4
#define GLX_GPU_FASTEST_TARGET_GPUS_AMD 0x21a2
#define GLX_GPU_NUM_PIPES_AMD 0x21a5
#define GLX_GPU_NUM_RB_AMD 0x21a7
#define GLX_GPU_NUM_SIMD_AMD 0x21a6
#define GLX_GPU_NUM_SPI_AMD 0x21a8
#define GLX_GPU_OPENGL_VERSION_STRING_AMD 0x1f02
#define GLX_GPU_RAM_AMD 0x21a3
#define GLX_GPU_RENDERER_STRING_AMD 0x1f01
#define GLX_GPU_VENDOR_AMD 0x1f00

#define glXBlitContextFramebufferAMD _glplatform_glXBlitContextFramebufferAMD
extern void (*glXBlitContextFramebufferAMD)(GLXContext, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glXCreateAssociatedContextAMD _glplatform_glXCreateAssociatedContextAMD
extern GLXContext (*glXCreateAssociatedContextAMD)(unsigned int , GLXContext);
#define glXCreateAssociatedContextAttribsAMD _glplatform_glXCreateAssociatedContextAttribsAMD
extern GLXContext (*glXCreateAssociatedContextAttribsAMD)(unsigned int , GLXContext, const int *);
#define glXDeleteAssociatedContextAMD _glplatform_glXDeleteAssociatedContextAMD
extern Bool (*glXDeleteAssociatedContextAMD)(GLXContext);
#define glXGetContextGPUIDAMD _glplatform_glXGetContextGPUIDAMD
extern unsigned int (*glXGetContextGPUIDAMD)(GLXContext);
#define glXGetCurrentAssociatedContextAMD _glplatform_glXGetCurrentAssociatedContextAMD
extern GLXContext (*glXGetCurrentAssociatedContextAMD)();
#define glXGetGPUIDsAMD _glplatform_glXGetGPUIDsAMD
extern unsigned int (*glXGetGPUIDsAMD)(unsigned int , unsigned int *);
#define glXGetGPUInfoAMD _glplatform_glXGetGPUInfoAMD
extern int (*glXGetGPUInfoAMD)(unsigned int , int , GLenum, unsigned int , void *);
#define glXMakeAssociatedContextCurrentAMD _glplatform_glXMakeAssociatedContextCurrentAMD
extern Bool (*glXMakeAssociatedContextCurrentAMD)(GLXContext);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_context_flush_control)
extern bool GLPLATFORM_GLX_ARB_context_flush_control;

#define GLX_CONTEXT_RELEASE_BEHAVIOR_ARB 0x2097
#define GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#define GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB 0x0

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_create_context)
extern bool GLPLATFORM_GLX_ARB_create_context;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif
#ifndef GLPLATFORM_TYPE_GLXFBConfig
#define GLPLATFORM_TYPE_GLXFBConfig
typedef struct __GLXFBConfigRec *GLXFBConfig;
#endif

#define GLX_CONTEXT_DEBUG_BIT_ARB 0x1
#define GLX_CONTEXT_FLAGS_ARB 0x2094
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x2
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

#define glXCreateContextAttribsARB _glplatform_glXCreateContextAttribsARB
extern GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_create_context_profile)
extern bool GLPLATFORM_GLX_ARB_create_context_profile;

#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x2
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x1
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_create_context_robustness)
extern bool GLPLATFORM_GLX_ARB_create_context_robustness;

#define GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x4
#define GLX_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define GLX_NO_RESET_NOTIFICATION_ARB 0x8261

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_fbconfig_float)
extern bool GLPLATFORM_GLX_ARB_fbconfig_float;

#define GLX_RGBA_FLOAT_BIT_ARB 0x4
#define GLX_RGBA_FLOAT_TYPE_ARB 0x20b9

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_framebuffer_sRGB)
extern bool GLPLATFORM_GLX_ARB_framebuffer_sRGB;

#define GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20b2

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_get_proc_address)
extern bool GLPLATFORM_GLX_ARB_get_proc_address;
#ifndef GLPLATFORM_TYPE___GLXextFuncPtr
#define GLPLATFORM_TYPE___GLXextFuncPtr
typedef void ( *__GLXextFuncPtr)(void);
#endif


#define glXGetProcAddressARB _glplatform_glXGetProcAddressARB
extern __GLXextFuncPtr (*glXGetProcAddressARB)(const GLubyte *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_multisample)
extern bool GLPLATFORM_GLX_ARB_multisample;

#define GLX_SAMPLES_ARB 0x186a1
#define GLX_SAMPLE_BUFFERS_ARB 0x186a0

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_robustness_application_isolation)
extern bool GLPLATFORM_GLX_ARB_robustness_application_isolation;

#define GLX_CONTEXT_RESET_ISOLATION_BIT_ARB 0x8

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_robustness_share_group_isolation)
extern bool GLPLATFORM_GLX_ARB_robustness_share_group_isolation;

#define GLX_CONTEXT_RESET_ISOLATION_BIT_ARB 0x8

#endif

#if defined(GLPLATFORM_ENABLE_GLX_ARB_vertex_buffer_object)
extern bool GLPLATFORM_GLX_ARB_vertex_buffer_object;

#define GLX_CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB 0x2095

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_buffer_age)
extern bool GLPLATFORM_GLX_EXT_buffer_age;

#define GLX_BACK_BUFFER_AGE_EXT 0x20f4

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_create_context_es2_profile)
extern bool GLPLATFORM_GLX_EXT_create_context_es2_profile;

#define GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x4

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_create_context_es_profile)
extern bool GLPLATFORM_GLX_EXT_create_context_es_profile;

#define GLX_CONTEXT_ES_PROFILE_BIT_EXT 0x4

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_fbconfig_packed_float)
extern bool GLPLATFORM_GLX_EXT_fbconfig_packed_float;

#define GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT 0x8
#define GLX_RGBA_UNSIGNED_FLOAT_TYPE_EXT 0x20b1

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_framebuffer_sRGB)
extern bool GLPLATFORM_GLX_EXT_framebuffer_sRGB;

#define GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x20b2

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_import_context)
extern bool GLPLATFORM_GLX_EXT_import_context;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif
#ifndef GLPLATFORM_TYPE_GLXContextID
#define GLPLATFORM_TYPE_GLXContextID
typedef XID GLXContextID;
#endif

#define GLX_SCREEN_EXT 0x800c
#define GLX_SHARE_CONTEXT_EXT 0x800a
#define GLX_VISUAL_ID_EXT 0x800b

#define glXFreeContextEXT _glplatform_glXFreeContextEXT
extern void (*glXFreeContextEXT)(Display *, GLXContext);
#define glXGetContextIDEXT _glplatform_glXGetContextIDEXT
extern GLXContextID (*glXGetContextIDEXT)(const GLXContext);
#define glXGetCurrentDisplayEXT _glplatform_glXGetCurrentDisplayEXT
extern Display * (*glXGetCurrentDisplayEXT)();
#define glXImportContextEXT _glplatform_glXImportContextEXT
extern GLXContext (*glXImportContextEXT)(Display *, GLXContextID);
#define glXQueryContextInfoEXT _glplatform_glXQueryContextInfoEXT
extern int (*glXQueryContextInfoEXT)(Display *, GLXContext, int , int *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_stereo_tree)
extern bool GLPLATFORM_GLX_EXT_stereo_tree;

#define GLX_STEREO_NOTIFY_EXT 0x0
#define GLX_STEREO_NOTIFY_MASK_EXT 0x1
#define GLX_STEREO_TREE_EXT 0x20f5

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_swap_control)
extern bool GLPLATFORM_GLX_EXT_swap_control;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif

#define GLX_MAX_SWAP_INTERVAL_EXT 0x20f2
#define GLX_SWAP_INTERVAL_EXT 0x20f1

#define glXSwapIntervalEXT _glplatform_glXSwapIntervalEXT
extern void (*glXSwapIntervalEXT)(Display *, GLXDrawable, int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_swap_control_tear)
extern bool GLPLATFORM_GLX_EXT_swap_control_tear;

#define GLX_LATE_SWAPS_TEAR_EXT 0x20f3

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_texture_from_pixmap)
extern bool GLPLATFORM_GLX_EXT_texture_from_pixmap;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif

#define GLX_AUX0_EXT 0x20e2
#define GLX_AUX1_EXT 0x20e3
#define GLX_AUX2_EXT 0x20e4
#define GLX_AUX3_EXT 0x20e5
#define GLX_AUX4_EXT 0x20e6
#define GLX_AUX5_EXT 0x20e7
#define GLX_AUX6_EXT 0x20e8
#define GLX_AUX7_EXT 0x20e9
#define GLX_AUX8_EXT 0x20ea
#define GLX_AUX9_EXT 0x20eb
#define GLX_BACK_EXT 0x20e0
#define GLX_BACK_LEFT_EXT 0x20e0
#define GLX_BACK_RIGHT_EXT 0x20e1
#define GLX_BIND_TO_MIPMAP_TEXTURE_EXT 0x20d2
#define GLX_BIND_TO_TEXTURE_RGBA_EXT 0x20d1
#define GLX_BIND_TO_TEXTURE_RGB_EXT 0x20d0
#define GLX_BIND_TO_TEXTURE_TARGETS_EXT 0x20d3
#define GLX_FRONT_EXT 0x20de
#define GLX_FRONT_LEFT_EXT 0x20de
#define GLX_FRONT_RIGHT_EXT 0x20df
#define GLX_MIPMAP_TEXTURE_EXT 0x20d7
#define GLX_TEXTURE_1D_BIT_EXT 0x1
#define GLX_TEXTURE_1D_EXT 0x20db
#define GLX_TEXTURE_2D_BIT_EXT 0x2
#define GLX_TEXTURE_2D_EXT 0x20dc
#define GLX_TEXTURE_FORMAT_EXT 0x20d5
#define GLX_TEXTURE_FORMAT_NONE_EXT 0x20d8
#define GLX_TEXTURE_FORMAT_RGBA_EXT 0x20da
#define GLX_TEXTURE_FORMAT_RGB_EXT 0x20d9
#define GLX_TEXTURE_RECTANGLE_BIT_EXT 0x4
#define GLX_TEXTURE_RECTANGLE_EXT 0x20dd
#define GLX_TEXTURE_TARGET_EXT 0x20d6
#define GLX_Y_INVERTED_EXT 0x20d4

#define glXBindTexImageEXT _glplatform_glXBindTexImageEXT
extern void (*glXBindTexImageEXT)(Display *, GLXDrawable, int , const int *);
#define glXReleaseTexImageEXT _glplatform_glXReleaseTexImageEXT
extern void (*glXReleaseTexImageEXT)(Display *, GLXDrawable, int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_visual_info)
extern bool GLPLATFORM_GLX_EXT_visual_info;

#define GLX_DIRECT_COLOR_EXT 0x8003
#define GLX_GRAY_SCALE_EXT 0x8006
#define GLX_NONE_EXT 0x8000
#define GLX_PSEUDO_COLOR_EXT 0x8004
#define GLX_STATIC_COLOR_EXT 0x8005
#define GLX_STATIC_GRAY_EXT 0x8007
#define GLX_TRANSPARENT_ALPHA_VALUE_EXT 0x28
#define GLX_TRANSPARENT_BLUE_VALUE_EXT 0x27
#define GLX_TRANSPARENT_GREEN_VALUE_EXT 0x26
#define GLX_TRANSPARENT_INDEX_EXT 0x8009
#define GLX_TRANSPARENT_INDEX_VALUE_EXT 0x24
#define GLX_TRANSPARENT_RED_VALUE_EXT 0x25
#define GLX_TRANSPARENT_RGB_EXT 0x8008
#define GLX_TRANSPARENT_TYPE_EXT 0x23
#define GLX_TRUE_COLOR_EXT 0x8002
#define GLX_X_VISUAL_TYPE_EXT 0x22

#endif

#if defined(GLPLATFORM_ENABLE_GLX_EXT_visual_rating)
extern bool GLPLATFORM_GLX_EXT_visual_rating;

#define GLX_NONE_EXT 0x8000
#define GLX_NON_CONFORMANT_VISUAL_EXT 0x800d
#define GLX_SLOW_VISUAL_EXT 0x8001
#define GLX_VISUAL_CAVEAT_EXT 0x20

#endif

#if defined(GLPLATFORM_ENABLE_GLX_INTEL_swap_event)
extern bool GLPLATFORM_GLX_INTEL_swap_event;

#define GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK 0x4000000
#define GLX_COPY_COMPLETE_INTEL 0x8181
#define GLX_EXCHANGE_COMPLETE_INTEL 0x8180
#define GLX_FLIP_COMPLETE_INTEL 0x8182

#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_agp_offset)
extern bool GLPLATFORM_GLX_MESA_agp_offset;


#define glXGetAGPOffsetMESA _glplatform_glXGetAGPOffsetMESA
extern unsigned int (*glXGetAGPOffsetMESA)(const void *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_copy_sub_buffer)
extern bool GLPLATFORM_GLX_MESA_copy_sub_buffer;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif


#define glXCopySubBufferMESA _glplatform_glXCopySubBufferMESA
extern void (*glXCopySubBufferMESA)(Display *, GLXDrawable, int , int , int , int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_pixmap_colormap)
extern bool GLPLATFORM_GLX_MESA_pixmap_colormap;
#ifndef GLPLATFORM_TYPE_Colormap
#define GLPLATFORM_TYPE_Colormap

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXPixmap
#define GLPLATFORM_TYPE_GLXPixmap
typedef XID GLXPixmap;
#endif
#ifndef GLPLATFORM_TYPE_Pixmap
#define GLPLATFORM_TYPE_Pixmap

#endif
#ifndef GLPLATFORM_TYPE_XVisualInfo
#define GLPLATFORM_TYPE_XVisualInfo

#endif


#define glXCreateGLXPixmapMESA _glplatform_glXCreateGLXPixmapMESA
extern GLXPixmap (*glXCreateGLXPixmapMESA)(Display *, XVisualInfo *, Pixmap, Colormap);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_query_renderer)
extern bool GLPLATFORM_GLX_MESA_query_renderer;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif

#define GLX_RENDERER_ACCELERATED_MESA 0x8186
#define GLX_RENDERER_DEVICE_ID_MESA 0x8184
#define GLX_RENDERER_ID_MESA 0x818e
#define GLX_RENDERER_OPENGL_COMPATIBILITY_PROFILE_VERSION_MESA 0x818b
#define GLX_RENDERER_OPENGL_CORE_PROFILE_VERSION_MESA 0x818a
#define GLX_RENDERER_OPENGL_ES2_PROFILE_VERSION_MESA 0x818d
#define GLX_RENDERER_OPENGL_ES_PROFILE_VERSION_MESA 0x818c
#define GLX_RENDERER_PREFERRED_PROFILE_MESA 0x8189
#define GLX_RENDERER_UNIFIED_MEMORY_ARCHITECTURE_MESA 0x8188
#define GLX_RENDERER_VENDOR_ID_MESA 0x8183
#define GLX_RENDERER_VERSION_MESA 0x8185
#define GLX_RENDERER_VIDEO_MEMORY_MESA 0x8187

#define glXQueryCurrentRendererIntegerMESA _glplatform_glXQueryCurrentRendererIntegerMESA
extern Bool (*glXQueryCurrentRendererIntegerMESA)(int , unsigned int *);
#define glXQueryCurrentRendererStringMESA _glplatform_glXQueryCurrentRendererStringMESA
extern const char * (*glXQueryCurrentRendererStringMESA)(int );
#define glXQueryRendererIntegerMESA _glplatform_glXQueryRendererIntegerMESA
extern Bool (*glXQueryRendererIntegerMESA)(Display *, int , int , int , unsigned int *);
#define glXQueryRendererStringMESA _glplatform_glXQueryRendererStringMESA
extern const char * (*glXQueryRendererStringMESA)(Display *, int , int , int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_release_buffers)
extern bool GLPLATFORM_GLX_MESA_release_buffers;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif


#define glXReleaseBuffersMESA _glplatform_glXReleaseBuffersMESA
extern Bool (*glXReleaseBuffersMESA)(Display *, GLXDrawable);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_MESA_set_3dfx_mode)
extern bool GLPLATFORM_GLX_MESA_set_3dfx_mode;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif

#define GLX_3DFX_FULLSCREEN_MODE_MESA 0x2
#define GLX_3DFX_WINDOW_MODE_MESA 0x1

#define glXSet3DfxModeMESA _glplatform_glXSet3DfxModeMESA
extern Bool (*glXSet3DfxModeMESA)(int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_copy_buffer)
extern bool GLPLATFORM_GLX_NV_copy_buffer;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif


#define glXCopyBufferSubDataNV _glplatform_glXCopyBufferSubDataNV
extern void (*glXCopyBufferSubDataNV)(Display *, GLXContext, GLXContext, GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
#define glXNamedCopyBufferSubDataNV _glplatform_glXNamedCopyBufferSubDataNV
extern void (*glXNamedCopyBufferSubDataNV)(Display *, GLXContext, GLXContext, GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_copy_image)
extern bool GLPLATFORM_GLX_NV_copy_image;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXContext
#define GLPLATFORM_TYPE_GLXContext
typedef struct __GLXcontextRec *GLXContext;
#endif


#define glXCopyImageSubDataNV _glplatform_glXCopyImageSubDataNV
extern void (*glXCopyImageSubDataNV)(Display *, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_delay_before_swap)
extern bool GLPLATFORM_GLX_NV_delay_before_swap;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif


#define glXDelayBeforeSwapNV _glplatform_glXDelayBeforeSwapNV
extern Bool (*glXDelayBeforeSwapNV)(Display *, GLXDrawable, GLfloat);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_float_buffer)
extern bool GLPLATFORM_GLX_NV_float_buffer;

#define GLX_FLOAT_COMPONENTS_NV 0x20b0

#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_multisample_coverage)
extern bool GLPLATFORM_GLX_NV_multisample_coverage;

#define GLX_COLOR_SAMPLES_NV 0x20b3
#define GLX_COVERAGE_SAMPLES_NV 0x186a1

#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_present_video)
extern bool GLPLATFORM_GLX_NV_present_video;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif

#define GLX_NUM_VIDEO_SLOTS_NV 0x20f0

#define glXBindVideoDeviceNV _glplatform_glXBindVideoDeviceNV
extern int (*glXBindVideoDeviceNV)(Display *, unsigned int , unsigned int , const int *);
#define glXEnumerateVideoDevicesNV _glplatform_glXEnumerateVideoDevicesNV
extern unsigned int * (*glXEnumerateVideoDevicesNV)(Display *, int , int *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_swap_group)
extern bool GLPLATFORM_GLX_NV_swap_group;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif


#define glXBindSwapBarrierNV _glplatform_glXBindSwapBarrierNV
extern Bool (*glXBindSwapBarrierNV)(Display *, GLuint, GLuint);
#define glXJoinSwapGroupNV _glplatform_glXJoinSwapGroupNV
extern Bool (*glXJoinSwapGroupNV)(Display *, GLXDrawable, GLuint);
#define glXQueryFrameCountNV _glplatform_glXQueryFrameCountNV
extern Bool (*glXQueryFrameCountNV)(Display *, int , GLuint *);
#define glXQueryMaxSwapGroupsNV _glplatform_glXQueryMaxSwapGroupsNV
extern Bool (*glXQueryMaxSwapGroupsNV)(Display *, int , GLuint *, GLuint *);
#define glXQuerySwapGroupNV _glplatform_glXQuerySwapGroupNV
extern Bool (*glXQuerySwapGroupNV)(Display *, GLXDrawable, GLuint *, GLuint *);
#define glXResetFrameCountNV _glplatform_glXResetFrameCountNV
extern Bool (*glXResetFrameCountNV)(Display *, int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_video_capture)
extern bool GLPLATFORM_GLX_NV_video_capture;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXVideoCaptureDeviceNV
#define GLPLATFORM_TYPE_GLXVideoCaptureDeviceNV
typedef XID GLXVideoCaptureDeviceNV;
#endif

#define GLX_DEVICE_ID_NV 0x20cd
#define GLX_NUM_VIDEO_CAPTURE_SLOTS_NV 0x20cf
#define GLX_UNIQUE_ID_NV 0x20ce

#define glXBindVideoCaptureDeviceNV _glplatform_glXBindVideoCaptureDeviceNV
extern int (*glXBindVideoCaptureDeviceNV)(Display *, unsigned int , GLXVideoCaptureDeviceNV);
#define glXEnumerateVideoCaptureDevicesNV _glplatform_glXEnumerateVideoCaptureDevicesNV
extern GLXVideoCaptureDeviceNV * (*glXEnumerateVideoCaptureDevicesNV)(Display *, int , int *);
#define glXLockVideoCaptureDeviceNV _glplatform_glXLockVideoCaptureDeviceNV
extern void (*glXLockVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV);
#define glXQueryVideoCaptureDeviceNV _glplatform_glXQueryVideoCaptureDeviceNV
extern int (*glXQueryVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV, int , int *);
#define glXReleaseVideoCaptureDeviceNV _glplatform_glXReleaseVideoCaptureDeviceNV
extern void (*glXReleaseVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_NV_video_out)
extern bool GLPLATFORM_GLX_NV_video_out;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXPbuffer
#define GLPLATFORM_TYPE_GLXPbuffer
typedef XID GLXPbuffer;
#endif
#ifndef GLPLATFORM_TYPE_GLXVideoDeviceNV
#define GLPLATFORM_TYPE_GLXVideoDeviceNV
typedef unsigned int GLXVideoDeviceNV;
#endif

#define GLX_VIDEO_OUT_ALPHA_NV 0x20c4
#define GLX_VIDEO_OUT_COLOR_AND_ALPHA_NV 0x20c6
#define GLX_VIDEO_OUT_COLOR_AND_DEPTH_NV 0x20c7
#define GLX_VIDEO_OUT_COLOR_NV 0x20c3
#define GLX_VIDEO_OUT_DEPTH_NV 0x20c5
#define GLX_VIDEO_OUT_FIELD_1_NV 0x20c9
#define GLX_VIDEO_OUT_FIELD_2_NV 0x20ca
#define GLX_VIDEO_OUT_FRAME_NV 0x20c8
#define GLX_VIDEO_OUT_STACKED_FIELDS_1_2_NV 0x20cb
#define GLX_VIDEO_OUT_STACKED_FIELDS_2_1_NV 0x20cc

#define glXBindVideoImageNV _glplatform_glXBindVideoImageNV
extern int (*glXBindVideoImageNV)(Display *, GLXVideoDeviceNV, GLXPbuffer, int );
#define glXGetVideoDeviceNV _glplatform_glXGetVideoDeviceNV
extern int (*glXGetVideoDeviceNV)(Display *, int , int , GLXVideoDeviceNV *);
#define glXGetVideoInfoNV _glplatform_glXGetVideoInfoNV
extern int (*glXGetVideoInfoNV)(Display *, int , GLXVideoDeviceNV, unsigned long *, unsigned long *);
#define glXReleaseVideoDeviceNV _glplatform_glXReleaseVideoDeviceNV
extern int (*glXReleaseVideoDeviceNV)(Display *, int , GLXVideoDeviceNV);
#define glXReleaseVideoImageNV _glplatform_glXReleaseVideoImageNV
extern int (*glXReleaseVideoImageNV)(Display *, GLXPbuffer);
#define glXSendPbufferToVideoNV _glplatform_glXSendPbufferToVideoNV
extern int (*glXSendPbufferToVideoNV)(Display *, GLXPbuffer, int , unsigned long *, GLboolean);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_OML_swap_method)
extern bool GLPLATFORM_GLX_OML_swap_method;

#define GLX_SWAP_COPY_OML 0x8062
#define GLX_SWAP_EXCHANGE_OML 0x8061
#define GLX_SWAP_METHOD_OML 0x8060
#define GLX_SWAP_UNDEFINED_OML 0x8063

#endif

#if defined(GLPLATFORM_ENABLE_GLX_OML_sync_control)
extern bool GLPLATFORM_GLX_OML_sync_control;
#ifndef GLPLATFORM_TYPE_Bool
#define GLPLATFORM_TYPE_Bool

#endif
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_GLXDrawable
#define GLPLATFORM_TYPE_GLXDrawable
typedef XID GLXDrawable;
#endif
#ifndef GLPLATFORM_TYPE_int32_t
#define GLPLATFORM_TYPE_int32_t

#endif
#ifndef GLPLATFORM_TYPE_int64_t
#define GLPLATFORM_TYPE_int64_t

#endif


#define glXGetMscRateOML _glplatform_glXGetMscRateOML
extern Bool (*glXGetMscRateOML)(Display *, GLXDrawable, int32_t *, int32_t *);
#define glXGetSyncValuesOML _glplatform_glXGetSyncValuesOML
extern Bool (*glXGetSyncValuesOML)(Display *, GLXDrawable, int64_t *, int64_t *, int64_t *);
#define glXSwapBuffersMscOML _glplatform_glXSwapBuffersMscOML
extern int64_t (*glXSwapBuffersMscOML)(Display *, GLXDrawable, int64_t, int64_t, int64_t);
#define glXWaitForMscOML _glplatform_glXWaitForMscOML
extern Bool (*glXWaitForMscOML)(Display *, GLXDrawable, int64_t, int64_t, int64_t, int64_t *, int64_t *, int64_t *);
#define glXWaitForSbcOML _glplatform_glXWaitForSbcOML
extern Bool (*glXWaitForSbcOML)(Display *, GLXDrawable, int64_t, int64_t *, int64_t *, int64_t *);
#endif

#if defined(GLPLATFORM_ENABLE_GLX_SGI_swap_control)
extern bool GLPLATFORM_GLX_SGI_swap_control;


#define glXSwapIntervalSGI _glplatform_glXSwapIntervalSGI
extern int (*glXSwapIntervalSGI)(int );
#endif

#if defined(GLPLATFORM_ENABLE_GLX_SUN_get_transparent_index)
extern bool GLPLATFORM_GLX_SUN_get_transparent_index;
#ifndef GLPLATFORM_TYPE_Display
#define GLPLATFORM_TYPE_Display

#endif
#ifndef GLPLATFORM_TYPE_Status
#define GLPLATFORM_TYPE_Status

#endif
#ifndef GLPLATFORM_TYPE_Window
#define GLPLATFORM_TYPE_Window

#endif


#define glXGetTransparentIndexSUN _glplatform_glXGetTransparentIndexSUN
extern Status (*glXGetTransparentIndexSUN)(Display *, Window, Window, long *);
#endif

bool glplatform_glx_init(int maj, int min);

#ifdef __cplusplus
}
#endif
#endif
