#ifndef _WIN32
extern void (*glXGetProcAddress(const unsigned char *))(void);
static inline void *LoadProcAddress(const char *name) { return glXGetProcAddress((const unsigned char *)name); }
#include <stdio.h>
#else
#include <windows.h>
#include <wingdi.h>
#include <stdio.h>
static PROC LoadProcAddress(const char *name) {
	PROC addr = wglGetProcAddress((LPCSTR)name);
	if (addr) return addr;
	else return (PROC)GetProcAddress(GetModuleHandleA("OpenGL32.dll"), (LPCSTR)name);
}
#endif
#define GLPLATFORM_GLX_VERSION 14
#define GLPLATFORM_ENABLE_GLX_3DFX_multisample
#define GLPLATFORM_ENABLE_GLX_AMD_gpu_association
#define GLPLATFORM_ENABLE_GLX_ARB_context_flush_control
#define GLPLATFORM_ENABLE_GLX_ARB_create_context
#define GLPLATFORM_ENABLE_GLX_ARB_create_context_profile
#define GLPLATFORM_ENABLE_GLX_ARB_create_context_robustness
#define GLPLATFORM_ENABLE_GLX_ARB_fbconfig_float
#define GLPLATFORM_ENABLE_GLX_ARB_framebuffer_sRGB
#define GLPLATFORM_ENABLE_GLX_ARB_get_proc_address
#define GLPLATFORM_ENABLE_GLX_ARB_multisample
#define GLPLATFORM_ENABLE_GLX_ARB_robustness_application_isolation
#define GLPLATFORM_ENABLE_GLX_ARB_robustness_share_group_isolation
#define GLPLATFORM_ENABLE_GLX_ARB_vertex_buffer_object
#define GLPLATFORM_ENABLE_GLX_EXT_buffer_age
#define GLPLATFORM_ENABLE_GLX_EXT_create_context_es2_profile
#define GLPLATFORM_ENABLE_GLX_EXT_create_context_es_profile
#define GLPLATFORM_ENABLE_GLX_EXT_fbconfig_packed_float
#define GLPLATFORM_ENABLE_GLX_EXT_framebuffer_sRGB
#define GLPLATFORM_ENABLE_GLX_EXT_import_context
#define GLPLATFORM_ENABLE_GLX_EXT_stereo_tree
#define GLPLATFORM_ENABLE_GLX_EXT_swap_control
#define GLPLATFORM_ENABLE_GLX_EXT_swap_control_tear
#define GLPLATFORM_ENABLE_GLX_EXT_texture_from_pixmap
#define GLPLATFORM_ENABLE_GLX_EXT_visual_info
#define GLPLATFORM_ENABLE_GLX_EXT_visual_rating
#define GLPLATFORM_ENABLE_GLX_INTEL_swap_event
#define GLPLATFORM_ENABLE_GLX_MESA_agp_offset
#define GLPLATFORM_ENABLE_GLX_MESA_copy_sub_buffer
#define GLPLATFORM_ENABLE_GLX_MESA_pixmap_colormap
#define GLPLATFORM_ENABLE_GLX_MESA_query_renderer
#define GLPLATFORM_ENABLE_GLX_MESA_release_buffers
#define GLPLATFORM_ENABLE_GLX_MESA_set_3dfx_mode
#define GLPLATFORM_ENABLE_GLX_NV_copy_buffer
#define GLPLATFORM_ENABLE_GLX_NV_copy_image
#define GLPLATFORM_ENABLE_GLX_NV_delay_before_swap
#define GLPLATFORM_ENABLE_GLX_NV_float_buffer
#define GLPLATFORM_ENABLE_GLX_NV_multisample_coverage
#define GLPLATFORM_ENABLE_GLX_NV_present_video
#define GLPLATFORM_ENABLE_GLX_NV_swap_group
#define GLPLATFORM_ENABLE_GLX_NV_video_capture
#define GLPLATFORM_ENABLE_GLX_NV_video_out
#define GLPLATFORM_ENABLE_GLX_OML_swap_method
#define GLPLATFORM_ENABLE_GLX_OML_sync_control
#define GLPLATFORM_ENABLE_GLX_SGI_swap_control
#define GLPLATFORM_ENABLE_GLX_SUN_get_transparent_index
#include "glplatform-glx.h"

Bool (*glXBindSwapBarrierNV)(Display *, GLuint, GLuint) = NULL;
void (*glXBindTexImageEXT)(Display *, GLXDrawable, int , const int *) = NULL;
int (*glXBindVideoCaptureDeviceNV)(Display *, unsigned int , GLXVideoCaptureDeviceNV) = NULL;
int (*glXBindVideoDeviceNV)(Display *, unsigned int , unsigned int , const int *) = NULL;
int (*glXBindVideoImageNV)(Display *, GLXVideoDeviceNV, GLXPbuffer, int ) = NULL;
void (*glXBlitContextFramebufferAMD)(GLXContext, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = NULL;
GLXFBConfig * (*glXChooseFBConfig)(Display *, int , const int *, int *) = NULL;
XVisualInfo * (*glXChooseVisual)(Display *, int , int *) = NULL;
void (*glXCopyBufferSubDataNV)(Display *, GLXContext, GLXContext, GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) = NULL;
void (*glXCopyContext)(Display *, GLXContext, GLXContext, unsigned long ) = NULL;
void (*glXCopyImageSubDataNV)(Display *, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = NULL;
void (*glXCopySubBufferMESA)(Display *, GLXDrawable, int , int , int , int ) = NULL;
GLXContext (*glXCreateAssociatedContextAMD)(unsigned int , GLXContext) = NULL;
GLXContext (*glXCreateAssociatedContextAttribsAMD)(unsigned int , GLXContext, const int *) = NULL;
GLXContext (*glXCreateContext)(Display *, XVisualInfo *, GLXContext, Bool) = NULL;
GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, const int *) = NULL;
GLXPixmap (*glXCreateGLXPixmap)(Display *, XVisualInfo *, Pixmap) = NULL;
GLXPixmap (*glXCreateGLXPixmapMESA)(Display *, XVisualInfo *, Pixmap, Colormap) = NULL;
GLXContext (*glXCreateNewContext)(Display *, GLXFBConfig, int , GLXContext, Bool) = NULL;
GLXPbuffer (*glXCreatePbuffer)(Display *, GLXFBConfig, const int *) = NULL;
GLXPixmap (*glXCreatePixmap)(Display *, GLXFBConfig, Pixmap, const int *) = NULL;
GLXWindow (*glXCreateWindow)(Display *, GLXFBConfig, Window, const int *) = NULL;
Bool (*glXDelayBeforeSwapNV)(Display *, GLXDrawable, GLfloat) = NULL;
Bool (*glXDeleteAssociatedContextAMD)(GLXContext) = NULL;
void (*glXDestroyContext)(Display *, GLXContext) = NULL;
void (*glXDestroyGLXPixmap)(Display *, GLXPixmap) = NULL;
void (*glXDestroyPbuffer)(Display *, GLXPbuffer) = NULL;
void (*glXDestroyPixmap)(Display *, GLXPixmap) = NULL;
void (*glXDestroyWindow)(Display *, GLXWindow) = NULL;
GLXVideoCaptureDeviceNV * (*glXEnumerateVideoCaptureDevicesNV)(Display *, int , int *) = NULL;
unsigned int * (*glXEnumerateVideoDevicesNV)(Display *, int , int *) = NULL;
void (*glXFreeContextEXT)(Display *, GLXContext) = NULL;
unsigned int (*glXGetAGPOffsetMESA)(const void *) = NULL;
const char * (*glXGetClientString)(Display *, int ) = NULL;
int (*glXGetConfig)(Display *, XVisualInfo *, int , int *) = NULL;
unsigned int (*glXGetContextGPUIDAMD)(GLXContext) = NULL;
GLXContextID (*glXGetContextIDEXT)(const GLXContext) = NULL;
GLXContext (*glXGetCurrentAssociatedContextAMD)() = NULL;
GLXContext (*glXGetCurrentContext)() = NULL;
Display * (*glXGetCurrentDisplay)() = NULL;
Display * (*glXGetCurrentDisplayEXT)() = NULL;
GLXDrawable (*glXGetCurrentDrawable)() = NULL;
GLXDrawable (*glXGetCurrentReadDrawable)() = NULL;
int (*glXGetFBConfigAttrib)(Display *, GLXFBConfig, int , int *) = NULL;
GLXFBConfig * (*glXGetFBConfigs)(Display *, int , int *) = NULL;
unsigned int (*glXGetGPUIDsAMD)(unsigned int , unsigned int *) = NULL;
int (*glXGetGPUInfoAMD)(unsigned int , int , GLenum, unsigned int , void *) = NULL;
Bool (*glXGetMscRateOML)(Display *, GLXDrawable, int32_t *, int32_t *) = NULL;
__GLXextFuncPtr (*glXGetProcAddress)(const GLubyte *) = NULL;
__GLXextFuncPtr (*glXGetProcAddressARB)(const GLubyte *) = NULL;
void (*glXGetSelectedEvent)(Display *, GLXDrawable, unsigned long *) = NULL;
Bool (*glXGetSyncValuesOML)(Display *, GLXDrawable, int64_t *, int64_t *, int64_t *) = NULL;
Status (*glXGetTransparentIndexSUN)(Display *, Window, Window, long *) = NULL;
int (*glXGetVideoDeviceNV)(Display *, int , int , GLXVideoDeviceNV *) = NULL;
int (*glXGetVideoInfoNV)(Display *, int , GLXVideoDeviceNV, unsigned long *, unsigned long *) = NULL;
XVisualInfo * (*glXGetVisualFromFBConfig)(Display *, GLXFBConfig) = NULL;
GLXContext (*glXImportContextEXT)(Display *, GLXContextID) = NULL;
Bool (*glXIsDirect)(Display *, GLXContext) = NULL;
Bool (*glXJoinSwapGroupNV)(Display *, GLXDrawable, GLuint) = NULL;
void (*glXLockVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV) = NULL;
Bool (*glXMakeAssociatedContextCurrentAMD)(GLXContext) = NULL;
Bool (*glXMakeContextCurrent)(Display *, GLXDrawable, GLXDrawable, GLXContext) = NULL;
Bool (*glXMakeCurrent)(Display *, GLXDrawable, GLXContext) = NULL;
void (*glXNamedCopyBufferSubDataNV)(Display *, GLXContext, GLXContext, GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) = NULL;
int (*glXQueryContext)(Display *, GLXContext, int , int *) = NULL;
int (*glXQueryContextInfoEXT)(Display *, GLXContext, int , int *) = NULL;
Bool (*glXQueryCurrentRendererIntegerMESA)(int , unsigned int *) = NULL;
const char * (*glXQueryCurrentRendererStringMESA)(int ) = NULL;
void (*glXQueryDrawable)(Display *, GLXDrawable, int , unsigned int *) = NULL;
Bool (*glXQueryExtension)(Display *, int *, int *) = NULL;
const char * (*glXQueryExtensionsString)(Display *, int ) = NULL;
Bool (*glXQueryFrameCountNV)(Display *, int , GLuint *) = NULL;
Bool (*glXQueryMaxSwapGroupsNV)(Display *, int , GLuint *, GLuint *) = NULL;
Bool (*glXQueryRendererIntegerMESA)(Display *, int , int , int , unsigned int *) = NULL;
const char * (*glXQueryRendererStringMESA)(Display *, int , int , int ) = NULL;
const char * (*glXQueryServerString)(Display *, int , int ) = NULL;
Bool (*glXQuerySwapGroupNV)(Display *, GLXDrawable, GLuint *, GLuint *) = NULL;
Bool (*glXQueryVersion)(Display *, int *, int *) = NULL;
int (*glXQueryVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV, int , int *) = NULL;
Bool (*glXReleaseBuffersMESA)(Display *, GLXDrawable) = NULL;
void (*glXReleaseTexImageEXT)(Display *, GLXDrawable, int ) = NULL;
void (*glXReleaseVideoCaptureDeviceNV)(Display *, GLXVideoCaptureDeviceNV) = NULL;
int (*glXReleaseVideoDeviceNV)(Display *, int , GLXVideoDeviceNV) = NULL;
int (*glXReleaseVideoImageNV)(Display *, GLXPbuffer) = NULL;
Bool (*glXResetFrameCountNV)(Display *, int ) = NULL;
void (*glXSelectEvent)(Display *, GLXDrawable, unsigned long ) = NULL;
int (*glXSendPbufferToVideoNV)(Display *, GLXPbuffer, int , unsigned long *, GLboolean) = NULL;
Bool (*glXSet3DfxModeMESA)(int ) = NULL;
void (*glXSwapBuffers)(Display *, GLXDrawable) = NULL;
int64_t (*glXSwapBuffersMscOML)(Display *, GLXDrawable, int64_t, int64_t, int64_t) = NULL;
void (*glXSwapIntervalEXT)(Display *, GLXDrawable, int ) = NULL;
int (*glXSwapIntervalSGI)(int ) = NULL;
void (*glXUseXFont)(Font, int , int , int ) = NULL;
Bool (*glXWaitForMscOML)(Display *, GLXDrawable, int64_t, int64_t, int64_t, int64_t *, int64_t *, int64_t *) = NULL;
Bool (*glXWaitForSbcOML)(Display *, GLXDrawable, int64_t, int64_t *, int64_t *, int64_t *) = NULL;
void (*glXWaitGL)() = NULL;
void (*glXWaitX)() = NULL;

bool GLPLATFORM_GLX_3DFX_multisample = false;
bool GLPLATFORM_GLX_AMD_gpu_association = false;
bool GLPLATFORM_GLX_ARB_context_flush_control = false;
bool GLPLATFORM_GLX_ARB_create_context = false;
bool GLPLATFORM_GLX_ARB_create_context_profile = false;
bool GLPLATFORM_GLX_ARB_create_context_robustness = false;
bool GLPLATFORM_GLX_ARB_fbconfig_float = false;
bool GLPLATFORM_GLX_ARB_framebuffer_sRGB = false;
bool GLPLATFORM_GLX_ARB_get_proc_address = false;
bool GLPLATFORM_GLX_ARB_multisample = false;
bool GLPLATFORM_GLX_ARB_robustness_application_isolation = false;
bool GLPLATFORM_GLX_ARB_robustness_share_group_isolation = false;
bool GLPLATFORM_GLX_ARB_vertex_buffer_object = false;
bool GLPLATFORM_GLX_EXT_buffer_age = false;
bool GLPLATFORM_GLX_EXT_create_context_es2_profile = false;
bool GLPLATFORM_GLX_EXT_create_context_es_profile = false;
bool GLPLATFORM_GLX_EXT_fbconfig_packed_float = false;
bool GLPLATFORM_GLX_EXT_framebuffer_sRGB = false;
bool GLPLATFORM_GLX_EXT_import_context = false;
bool GLPLATFORM_GLX_EXT_stereo_tree = false;
bool GLPLATFORM_GLX_EXT_swap_control = false;
bool GLPLATFORM_GLX_EXT_swap_control_tear = false;
bool GLPLATFORM_GLX_EXT_texture_from_pixmap = false;
bool GLPLATFORM_GLX_EXT_visual_info = false;
bool GLPLATFORM_GLX_EXT_visual_rating = false;
bool GLPLATFORM_GLX_INTEL_swap_event = false;
bool GLPLATFORM_GLX_MESA_agp_offset = false;
bool GLPLATFORM_GLX_MESA_copy_sub_buffer = false;
bool GLPLATFORM_GLX_MESA_pixmap_colormap = false;
bool GLPLATFORM_GLX_MESA_query_renderer = false;
bool GLPLATFORM_GLX_MESA_release_buffers = false;
bool GLPLATFORM_GLX_MESA_set_3dfx_mode = false;
bool GLPLATFORM_GLX_NV_copy_buffer = false;
bool GLPLATFORM_GLX_NV_copy_image = false;
bool GLPLATFORM_GLX_NV_delay_before_swap = false;
bool GLPLATFORM_GLX_NV_float_buffer = false;
bool GLPLATFORM_GLX_NV_multisample_coverage = false;
bool GLPLATFORM_GLX_NV_present_video = false;
bool GLPLATFORM_GLX_NV_swap_group = false;
bool GLPLATFORM_GLX_NV_video_capture = false;
bool GLPLATFORM_GLX_NV_video_out = false;
bool GLPLATFORM_GLX_OML_swap_method = false;
bool GLPLATFORM_GLX_OML_sync_control = false;
bool GLPLATFORM_GLX_SGI_swap_control = false;
bool GLPLATFORM_GLX_SUN_get_transparent_index = false;

bool glplatform_glx_init(int maj, int min)
{
	int req_version = maj * 10 + min;
	if (req_version < 14) return false;
	if (req_version > 14) return false;
	glXBindSwapBarrierNV = (Bool (*)(Display *, GLuint, GLuint) ) LoadProcAddress("glXBindSwapBarrierNV");
	glXBindTexImageEXT = (void (*)(Display *, GLXDrawable, int , const int *) ) LoadProcAddress("glXBindTexImageEXT");
	glXBindVideoCaptureDeviceNV = (int (*)(Display *, unsigned int , GLXVideoCaptureDeviceNV) ) LoadProcAddress("glXBindVideoCaptureDeviceNV");
	glXBindVideoDeviceNV = (int (*)(Display *, unsigned int , unsigned int , const int *) ) LoadProcAddress("glXBindVideoDeviceNV");
	glXBindVideoImageNV = (int (*)(Display *, GLXVideoDeviceNV, GLXPbuffer, int ) ) LoadProcAddress("glXBindVideoImageNV");
	glXBlitContextFramebufferAMD = (void (*)(GLXContext, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) ) LoadProcAddress("glXBlitContextFramebufferAMD");
	glXChooseFBConfig = (GLXFBConfig * (*)(Display *, int , const int *, int *) ) LoadProcAddress("glXChooseFBConfig");
	glXChooseVisual = (XVisualInfo * (*)(Display *, int , int *) ) LoadProcAddress("glXChooseVisual");
	glXCopyBufferSubDataNV = (void (*)(Display *, GLXContext, GLXContext, GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) ) LoadProcAddress("glXCopyBufferSubDataNV");
	glXCopyContext = (void (*)(Display *, GLXContext, GLXContext, unsigned long ) ) LoadProcAddress("glXCopyContext");
	glXCopyImageSubDataNV = (void (*)(Display *, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLXContext, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glXCopyImageSubDataNV");
	glXCopySubBufferMESA = (void (*)(Display *, GLXDrawable, int , int , int , int ) ) LoadProcAddress("glXCopySubBufferMESA");
	glXCreateAssociatedContextAMD = (GLXContext (*)(unsigned int , GLXContext) ) LoadProcAddress("glXCreateAssociatedContextAMD");
	glXCreateAssociatedContextAttribsAMD = (GLXContext (*)(unsigned int , GLXContext, const int *) ) LoadProcAddress("glXCreateAssociatedContextAttribsAMD");
	glXCreateContext = (GLXContext (*)(Display *, XVisualInfo *, GLXContext, Bool) ) LoadProcAddress("glXCreateContext");
	glXCreateContextAttribsARB = (GLXContext (*)(Display *, GLXFBConfig, GLXContext, Bool, const int *) ) LoadProcAddress("glXCreateContextAttribsARB");
	glXCreateGLXPixmap = (GLXPixmap (*)(Display *, XVisualInfo *, Pixmap) ) LoadProcAddress("glXCreateGLXPixmap");
	glXCreateGLXPixmapMESA = (GLXPixmap (*)(Display *, XVisualInfo *, Pixmap, Colormap) ) LoadProcAddress("glXCreateGLXPixmapMESA");
	glXCreateNewContext = (GLXContext (*)(Display *, GLXFBConfig, int , GLXContext, Bool) ) LoadProcAddress("glXCreateNewContext");
	glXCreatePbuffer = (GLXPbuffer (*)(Display *, GLXFBConfig, const int *) ) LoadProcAddress("glXCreatePbuffer");
	glXCreatePixmap = (GLXPixmap (*)(Display *, GLXFBConfig, Pixmap, const int *) ) LoadProcAddress("glXCreatePixmap");
	glXCreateWindow = (GLXWindow (*)(Display *, GLXFBConfig, Window, const int *) ) LoadProcAddress("glXCreateWindow");
	glXDelayBeforeSwapNV = (Bool (*)(Display *, GLXDrawable, GLfloat) ) LoadProcAddress("glXDelayBeforeSwapNV");
	glXDeleteAssociatedContextAMD = (Bool (*)(GLXContext) ) LoadProcAddress("glXDeleteAssociatedContextAMD");
	glXDestroyContext = (void (*)(Display *, GLXContext) ) LoadProcAddress("glXDestroyContext");
	glXDestroyGLXPixmap = (void (*)(Display *, GLXPixmap) ) LoadProcAddress("glXDestroyGLXPixmap");
	glXDestroyPbuffer = (void (*)(Display *, GLXPbuffer) ) LoadProcAddress("glXDestroyPbuffer");
	glXDestroyPixmap = (void (*)(Display *, GLXPixmap) ) LoadProcAddress("glXDestroyPixmap");
	glXDestroyWindow = (void (*)(Display *, GLXWindow) ) LoadProcAddress("glXDestroyWindow");
	glXEnumerateVideoCaptureDevicesNV = (GLXVideoCaptureDeviceNV * (*)(Display *, int , int *) ) LoadProcAddress("glXEnumerateVideoCaptureDevicesNV");
	glXEnumerateVideoDevicesNV = (unsigned int * (*)(Display *, int , int *) ) LoadProcAddress("glXEnumerateVideoDevicesNV");
	glXFreeContextEXT = (void (*)(Display *, GLXContext) ) LoadProcAddress("glXFreeContextEXT");
	glXGetAGPOffsetMESA = (unsigned int (*)(const void *) ) LoadProcAddress("glXGetAGPOffsetMESA");
	glXGetClientString = (const char * (*)(Display *, int ) ) LoadProcAddress("glXGetClientString");
	glXGetConfig = (int (*)(Display *, XVisualInfo *, int , int *) ) LoadProcAddress("glXGetConfig");
	glXGetContextGPUIDAMD = (unsigned int (*)(GLXContext) ) LoadProcAddress("glXGetContextGPUIDAMD");
	glXGetContextIDEXT = (GLXContextID (*)(const GLXContext) ) LoadProcAddress("glXGetContextIDEXT");
	glXGetCurrentAssociatedContextAMD = (GLXContext (*)() ) LoadProcAddress("glXGetCurrentAssociatedContextAMD");
	glXGetCurrentContext = (GLXContext (*)() ) LoadProcAddress("glXGetCurrentContext");
	glXGetCurrentDisplay = (Display * (*)() ) LoadProcAddress("glXGetCurrentDisplay");
	glXGetCurrentDisplayEXT = (Display * (*)() ) LoadProcAddress("glXGetCurrentDisplayEXT");
	glXGetCurrentDrawable = (GLXDrawable (*)() ) LoadProcAddress("glXGetCurrentDrawable");
	glXGetCurrentReadDrawable = (GLXDrawable (*)() ) LoadProcAddress("glXGetCurrentReadDrawable");
	glXGetFBConfigAttrib = (int (*)(Display *, GLXFBConfig, int , int *) ) LoadProcAddress("glXGetFBConfigAttrib");
	glXGetFBConfigs = (GLXFBConfig * (*)(Display *, int , int *) ) LoadProcAddress("glXGetFBConfigs");
	glXGetGPUIDsAMD = (unsigned int (*)(unsigned int , unsigned int *) ) LoadProcAddress("glXGetGPUIDsAMD");
	glXGetGPUInfoAMD = (int (*)(unsigned int , int , GLenum, unsigned int , void *) ) LoadProcAddress("glXGetGPUInfoAMD");
	glXGetMscRateOML = (Bool (*)(Display *, GLXDrawable, int32_t *, int32_t *) ) LoadProcAddress("glXGetMscRateOML");
	glXGetProcAddress = (__GLXextFuncPtr (*)(const GLubyte *) ) LoadProcAddress("glXGetProcAddress");
	glXGetProcAddressARB = (__GLXextFuncPtr (*)(const GLubyte *) ) LoadProcAddress("glXGetProcAddressARB");
	glXGetSelectedEvent = (void (*)(Display *, GLXDrawable, unsigned long *) ) LoadProcAddress("glXGetSelectedEvent");
	glXGetSyncValuesOML = (Bool (*)(Display *, GLXDrawable, int64_t *, int64_t *, int64_t *) ) LoadProcAddress("glXGetSyncValuesOML");
	glXGetTransparentIndexSUN = (Status (*)(Display *, Window, Window, long *) ) LoadProcAddress("glXGetTransparentIndexSUN");
	glXGetVideoDeviceNV = (int (*)(Display *, int , int , GLXVideoDeviceNV *) ) LoadProcAddress("glXGetVideoDeviceNV");
	glXGetVideoInfoNV = (int (*)(Display *, int , GLXVideoDeviceNV, unsigned long *, unsigned long *) ) LoadProcAddress("glXGetVideoInfoNV");
	glXGetVisualFromFBConfig = (XVisualInfo * (*)(Display *, GLXFBConfig) ) LoadProcAddress("glXGetVisualFromFBConfig");
	glXImportContextEXT = (GLXContext (*)(Display *, GLXContextID) ) LoadProcAddress("glXImportContextEXT");
	glXIsDirect = (Bool (*)(Display *, GLXContext) ) LoadProcAddress("glXIsDirect");
	glXJoinSwapGroupNV = (Bool (*)(Display *, GLXDrawable, GLuint) ) LoadProcAddress("glXJoinSwapGroupNV");
	glXLockVideoCaptureDeviceNV = (void (*)(Display *, GLXVideoCaptureDeviceNV) ) LoadProcAddress("glXLockVideoCaptureDeviceNV");
	glXMakeAssociatedContextCurrentAMD = (Bool (*)(GLXContext) ) LoadProcAddress("glXMakeAssociatedContextCurrentAMD");
	glXMakeContextCurrent = (Bool (*)(Display *, GLXDrawable, GLXDrawable, GLXContext) ) LoadProcAddress("glXMakeContextCurrent");
	glXMakeCurrent = (Bool (*)(Display *, GLXDrawable, GLXContext) ) LoadProcAddress("glXMakeCurrent");
	glXNamedCopyBufferSubDataNV = (void (*)(Display *, GLXContext, GLXContext, GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) ) LoadProcAddress("glXNamedCopyBufferSubDataNV");
	glXQueryContext = (int (*)(Display *, GLXContext, int , int *) ) LoadProcAddress("glXQueryContext");
	glXQueryContextInfoEXT = (int (*)(Display *, GLXContext, int , int *) ) LoadProcAddress("glXQueryContextInfoEXT");
	glXQueryCurrentRendererIntegerMESA = (Bool (*)(int , unsigned int *) ) LoadProcAddress("glXQueryCurrentRendererIntegerMESA");
	glXQueryCurrentRendererStringMESA = (const char * (*)(int ) ) LoadProcAddress("glXQueryCurrentRendererStringMESA");
	glXQueryDrawable = (void (*)(Display *, GLXDrawable, int , unsigned int *) ) LoadProcAddress("glXQueryDrawable");
	glXQueryExtension = (Bool (*)(Display *, int *, int *) ) LoadProcAddress("glXQueryExtension");
	glXQueryExtensionsString = (const char * (*)(Display *, int ) ) LoadProcAddress("glXQueryExtensionsString");
	glXQueryFrameCountNV = (Bool (*)(Display *, int , GLuint *) ) LoadProcAddress("glXQueryFrameCountNV");
	glXQueryMaxSwapGroupsNV = (Bool (*)(Display *, int , GLuint *, GLuint *) ) LoadProcAddress("glXQueryMaxSwapGroupsNV");
	glXQueryRendererIntegerMESA = (Bool (*)(Display *, int , int , int , unsigned int *) ) LoadProcAddress("glXQueryRendererIntegerMESA");
	glXQueryRendererStringMESA = (const char * (*)(Display *, int , int , int ) ) LoadProcAddress("glXQueryRendererStringMESA");
	glXQueryServerString = (const char * (*)(Display *, int , int ) ) LoadProcAddress("glXQueryServerString");
	glXQuerySwapGroupNV = (Bool (*)(Display *, GLXDrawable, GLuint *, GLuint *) ) LoadProcAddress("glXQuerySwapGroupNV");
	glXQueryVersion = (Bool (*)(Display *, int *, int *) ) LoadProcAddress("glXQueryVersion");
	glXQueryVideoCaptureDeviceNV = (int (*)(Display *, GLXVideoCaptureDeviceNV, int , int *) ) LoadProcAddress("glXQueryVideoCaptureDeviceNV");
	glXReleaseBuffersMESA = (Bool (*)(Display *, GLXDrawable) ) LoadProcAddress("glXReleaseBuffersMESA");
	glXReleaseTexImageEXT = (void (*)(Display *, GLXDrawable, int ) ) LoadProcAddress("glXReleaseTexImageEXT");
	glXReleaseVideoCaptureDeviceNV = (void (*)(Display *, GLXVideoCaptureDeviceNV) ) LoadProcAddress("glXReleaseVideoCaptureDeviceNV");
	glXReleaseVideoDeviceNV = (int (*)(Display *, int , GLXVideoDeviceNV) ) LoadProcAddress("glXReleaseVideoDeviceNV");
	glXReleaseVideoImageNV = (int (*)(Display *, GLXPbuffer) ) LoadProcAddress("glXReleaseVideoImageNV");
	glXResetFrameCountNV = (Bool (*)(Display *, int ) ) LoadProcAddress("glXResetFrameCountNV");
	glXSelectEvent = (void (*)(Display *, GLXDrawable, unsigned long ) ) LoadProcAddress("glXSelectEvent");
	glXSendPbufferToVideoNV = (int (*)(Display *, GLXPbuffer, int , unsigned long *, GLboolean) ) LoadProcAddress("glXSendPbufferToVideoNV");
	glXSet3DfxModeMESA = (Bool (*)(int ) ) LoadProcAddress("glXSet3DfxModeMESA");
	glXSwapBuffers = (void (*)(Display *, GLXDrawable) ) LoadProcAddress("glXSwapBuffers");
	glXSwapBuffersMscOML = (int64_t (*)(Display *, GLXDrawable, int64_t, int64_t, int64_t) ) LoadProcAddress("glXSwapBuffersMscOML");
	glXSwapIntervalEXT = (void (*)(Display *, GLXDrawable, int ) ) LoadProcAddress("glXSwapIntervalEXT");
	glXSwapIntervalSGI = (int (*)(int ) ) LoadProcAddress("glXSwapIntervalSGI");
	glXUseXFont = (void (*)(Font, int , int , int ) ) LoadProcAddress("glXUseXFont");
	glXWaitForMscOML = (Bool (*)(Display *, GLXDrawable, int64_t, int64_t, int64_t, int64_t *, int64_t *, int64_t *) ) LoadProcAddress("glXWaitForMscOML");
	glXWaitForSbcOML = (Bool (*)(Display *, GLXDrawable, int64_t, int64_t *, int64_t *, int64_t *) ) LoadProcAddress("glXWaitForSbcOML");
	glXWaitGL = (void (*)() ) LoadProcAddress("glXWaitGL");
	glXWaitX = (void (*)() ) LoadProcAddress("glXWaitX");
	
	GLPLATFORM_GLX_AMD_gpu_association = GLPLATFORM_GLX_AMD_gpu_association && glXBlitContextFramebufferAMD && glXCreateAssociatedContextAMD
		 && glXCreateAssociatedContextAttribsAMD && glXDeleteAssociatedContextAMD && glXGetContextGPUIDAMD
		 && glXGetCurrentAssociatedContextAMD && glXGetGPUIDsAMD && glXGetGPUInfoAMD
		 && glXMakeAssociatedContextCurrentAMD;
	
	GLPLATFORM_GLX_ARB_create_context = GLPLATFORM_GLX_ARB_create_context && glXCreateContextAttribsARB;
	
	GLPLATFORM_GLX_ARB_get_proc_address = GLPLATFORM_GLX_ARB_get_proc_address && glXGetProcAddressARB;
	
	GLPLATFORM_GLX_EXT_import_context = GLPLATFORM_GLX_EXT_import_context && glXFreeContextEXT && glXGetContextIDEXT
		 && glXGetCurrentDisplayEXT && glXImportContextEXT && glXQueryContextInfoEXT;
	
	GLPLATFORM_GLX_EXT_swap_control = GLPLATFORM_GLX_EXT_swap_control && glXSwapIntervalEXT;
	
	GLPLATFORM_GLX_EXT_texture_from_pixmap = GLPLATFORM_GLX_EXT_texture_from_pixmap && glXBindTexImageEXT && glXReleaseTexImageEXT;
	
	GLPLATFORM_GLX_MESA_agp_offset = GLPLATFORM_GLX_MESA_agp_offset && glXGetAGPOffsetMESA;
	
	GLPLATFORM_GLX_MESA_copy_sub_buffer = GLPLATFORM_GLX_MESA_copy_sub_buffer && glXCopySubBufferMESA;
	
	GLPLATFORM_GLX_MESA_pixmap_colormap = GLPLATFORM_GLX_MESA_pixmap_colormap && glXCreateGLXPixmapMESA;
	
	GLPLATFORM_GLX_MESA_query_renderer = GLPLATFORM_GLX_MESA_query_renderer && glXQueryCurrentRendererIntegerMESA && glXQueryCurrentRendererStringMESA
		 && glXQueryRendererIntegerMESA && glXQueryRendererStringMESA;
	
	GLPLATFORM_GLX_MESA_release_buffers = GLPLATFORM_GLX_MESA_release_buffers && glXReleaseBuffersMESA;
	
	GLPLATFORM_GLX_MESA_set_3dfx_mode = GLPLATFORM_GLX_MESA_set_3dfx_mode && glXSet3DfxModeMESA;
	
	GLPLATFORM_GLX_NV_copy_buffer = GLPLATFORM_GLX_NV_copy_buffer && glXCopyBufferSubDataNV && glXNamedCopyBufferSubDataNV;
	
	GLPLATFORM_GLX_NV_copy_image = GLPLATFORM_GLX_NV_copy_image && glXCopyImageSubDataNV;
	
	GLPLATFORM_GLX_NV_delay_before_swap = GLPLATFORM_GLX_NV_delay_before_swap && glXDelayBeforeSwapNV;
	
	GLPLATFORM_GLX_NV_present_video = GLPLATFORM_GLX_NV_present_video && glXBindVideoDeviceNV && glXEnumerateVideoDevicesNV;
	
	GLPLATFORM_GLX_NV_swap_group = GLPLATFORM_GLX_NV_swap_group && glXBindSwapBarrierNV && glXJoinSwapGroupNV
		 && glXQueryFrameCountNV && glXQueryMaxSwapGroupsNV && glXQuerySwapGroupNV
		 && glXResetFrameCountNV;
	
	GLPLATFORM_GLX_NV_video_capture = GLPLATFORM_GLX_NV_video_capture && glXBindVideoCaptureDeviceNV && glXEnumerateVideoCaptureDevicesNV
		 && glXLockVideoCaptureDeviceNV && glXQueryVideoCaptureDeviceNV && glXReleaseVideoCaptureDeviceNV;
	
	GLPLATFORM_GLX_NV_video_out = GLPLATFORM_GLX_NV_video_out && glXBindVideoImageNV && glXGetVideoDeviceNV
		 && glXGetVideoInfoNV && glXReleaseVideoDeviceNV && glXReleaseVideoImageNV
		 && glXSendPbufferToVideoNV;
	
	GLPLATFORM_GLX_OML_sync_control = GLPLATFORM_GLX_OML_sync_control && glXGetMscRateOML && glXGetSyncValuesOML
		 && glXSwapBuffersMscOML && glXWaitForMscOML && glXWaitForSbcOML;
	
	GLPLATFORM_GLX_SGI_swap_control = GLPLATFORM_GLX_SGI_swap_control && glXSwapIntervalSGI;
	
	GLPLATFORM_GLX_SUN_get_transparent_index = GLPLATFORM_GLX_SUN_get_transparent_index && glXGetTransparentIndexSUN;
	
	return glXChooseFBConfig && glXChooseVisual
	 && glXCopyContext && glXCreateContext && glXCreateGLXPixmap
	 && glXCreateNewContext && glXCreatePbuffer && glXCreatePixmap
	 && glXCreateWindow && glXDestroyContext && glXDestroyGLXPixmap
	 && glXDestroyPbuffer && glXDestroyPixmap && glXDestroyWindow
	 && glXGetClientString && glXGetConfig && glXGetCurrentContext
	 && glXGetCurrentDisplay && glXGetCurrentDrawable && glXGetCurrentReadDrawable
	 && glXGetFBConfigAttrib && glXGetFBConfigs && glXGetProcAddress
	 && glXGetSelectedEvent && glXGetVisualFromFBConfig && glXIsDirect
	 && glXMakeContextCurrent && glXMakeCurrent && glXQueryContext
	 && glXQueryDrawable && glXQueryExtension && glXQueryExtensionsString
	 && glXQueryServerString && glXQueryVersion && glXSelectEvent
	 && glXSwapBuffers && glXUseXFont && glXWaitGL
	 && glXWaitX;
}
