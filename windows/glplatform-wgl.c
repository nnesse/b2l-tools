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
#define GLPLATFORM_WGL_VERSION 10
#define GLPLATFORM_ENABLE_WGL_3DFX_multisample
#define GLPLATFORM_ENABLE_WGL_3DL_stereo_control
#define GLPLATFORM_ENABLE_WGL_AMD_gpu_association
#define GLPLATFORM_ENABLE_WGL_ARB_buffer_region
#define GLPLATFORM_ENABLE_WGL_ARB_context_flush_control
#define GLPLATFORM_ENABLE_WGL_ARB_create_context
#define GLPLATFORM_ENABLE_WGL_ARB_create_context_profile
#define GLPLATFORM_ENABLE_WGL_ARB_create_context_robustness
#define GLPLATFORM_ENABLE_WGL_ARB_extensions_string
#define GLPLATFORM_ENABLE_WGL_ARB_framebuffer_sRGB
#define GLPLATFORM_ENABLE_WGL_ARB_make_current_read
#define GLPLATFORM_ENABLE_WGL_ARB_multisample
#define GLPLATFORM_ENABLE_WGL_ARB_pbuffer
#define GLPLATFORM_ENABLE_WGL_ARB_pixel_format
#define GLPLATFORM_ENABLE_WGL_ARB_pixel_format_float
#define GLPLATFORM_ENABLE_WGL_ARB_render_texture
#define GLPLATFORM_ENABLE_WGL_ARB_robustness_application_isolation
#define GLPLATFORM_ENABLE_WGL_ARB_robustness_share_group_isolation
#define GLPLATFORM_ENABLE_WGL_ATI_pixel_format_float
#define GLPLATFORM_ENABLE_WGL_EXT_create_context_es2_profile
#define GLPLATFORM_ENABLE_WGL_EXT_create_context_es_profile
#define GLPLATFORM_ENABLE_WGL_EXT_depth_float
#define GLPLATFORM_ENABLE_WGL_EXT_display_color_table
#define GLPLATFORM_ENABLE_WGL_EXT_extensions_string
#define GLPLATFORM_ENABLE_WGL_EXT_framebuffer_sRGB
#define GLPLATFORM_ENABLE_WGL_EXT_make_current_read
#define GLPLATFORM_ENABLE_WGL_EXT_multisample
#define GLPLATFORM_ENABLE_WGL_EXT_pbuffer
#define GLPLATFORM_ENABLE_WGL_EXT_pixel_format
#define GLPLATFORM_ENABLE_WGL_EXT_pixel_format_packed_float
#define GLPLATFORM_ENABLE_WGL_EXT_swap_control
#define GLPLATFORM_ENABLE_WGL_EXT_swap_control_tear
#define GLPLATFORM_ENABLE_WGL_I3D_digital_video_control
#define GLPLATFORM_ENABLE_WGL_I3D_gamma
#define GLPLATFORM_ENABLE_WGL_I3D_genlock
#define GLPLATFORM_ENABLE_WGL_I3D_image_buffer
#define GLPLATFORM_ENABLE_WGL_I3D_swap_frame_lock
#define GLPLATFORM_ENABLE_WGL_I3D_swap_frame_usage
#define GLPLATFORM_ENABLE_WGL_NV_DX_interop
#define GLPLATFORM_ENABLE_WGL_NV_DX_interop2
#define GLPLATFORM_ENABLE_WGL_NV_copy_image
#define GLPLATFORM_ENABLE_WGL_NV_delay_before_swap
#define GLPLATFORM_ENABLE_WGL_NV_float_buffer
#define GLPLATFORM_ENABLE_WGL_NV_gpu_affinity
#define GLPLATFORM_ENABLE_WGL_NV_multisample_coverage
#define GLPLATFORM_ENABLE_WGL_NV_present_video
#define GLPLATFORM_ENABLE_WGL_NV_render_depth_texture
#define GLPLATFORM_ENABLE_WGL_NV_render_texture_rectangle
#define GLPLATFORM_ENABLE_WGL_NV_swap_group
#define GLPLATFORM_ENABLE_WGL_NV_vertex_array_range
#define GLPLATFORM_ENABLE_WGL_NV_video_capture
#define GLPLATFORM_ENABLE_WGL_NV_video_output
#define GLPLATFORM_ENABLE_WGL_OML_sync_control
#include "glplatform-wgl.h"

void * (*wglAllocateMemoryNV)(GLsizei, GLfloat, GLfloat, GLfloat) = NULL;
BOOL (*wglAssociateImageBufferEventsI3D)(HDC, const HANDLE *, const LPVOID *, const DWORD *, UINT) = NULL;
BOOL (*wglBeginFrameTrackingI3D)() = NULL;
GLboolean (*wglBindDisplayColorTableEXT)(GLushort) = NULL;
BOOL (*wglBindSwapBarrierNV)(GLuint, GLuint) = NULL;
BOOL (*wglBindTexImageARB)(HPBUFFERARB, int ) = NULL;
BOOL (*wglBindVideoCaptureDeviceNV)(UINT, HVIDEOINPUTDEVICENV) = NULL;
BOOL (*wglBindVideoDeviceNV)(HDC, unsigned int , HVIDEOOUTPUTDEVICENV, const int *) = NULL;
BOOL (*wglBindVideoImageNV)(HPVIDEODEV, HPBUFFERARB, int ) = NULL;
VOID (*wglBlitContextFramebufferAMD)(HGLRC, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = NULL;
BOOL (*wglChoosePixelFormatARB)(HDC, const int *, const FLOAT *, UINT, int *, UINT *) = NULL;
BOOL (*wglChoosePixelFormatEXT)(HDC, const int *, const FLOAT *, UINT, int *, UINT *) = NULL;
BOOL (*wglCopyContext)(HGLRC, HGLRC, UINT) = NULL;
BOOL (*wglCopyImageSubDataNV)(HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = NULL;
HDC (*wglCreateAffinityDCNV)(const HGPUNV *) = NULL;
HGLRC (*wglCreateAssociatedContextAMD)(UINT) = NULL;
HGLRC (*wglCreateAssociatedContextAttribsAMD)(UINT, HGLRC, const int *) = NULL;
HANDLE (*wglCreateBufferRegionARB)(HDC, int , UINT) = NULL;
HGLRC (*wglCreateContextAttribsARB)(HDC, HGLRC, const int *) = NULL;
GLboolean (*wglCreateDisplayColorTableEXT)(GLushort) = NULL;
LPVOID (*wglCreateImageBufferI3D)(HDC, DWORD, UINT) = NULL;
HGLRC (*wglCreateLayerContext)(HDC, int ) = NULL;
HPBUFFERARB (*wglCreatePbufferARB)(HDC, int , int , int , const int *) = NULL;
HPBUFFEREXT (*wglCreatePbufferEXT)(HDC, int , int , int , const int *) = NULL;
BOOL (*wglDXCloseDeviceNV)(HANDLE) = NULL;
BOOL (*wglDXLockObjectsNV)(HANDLE, GLint, HANDLE *) = NULL;
BOOL (*wglDXObjectAccessNV)(HANDLE, GLenum) = NULL;
HANDLE (*wglDXOpenDeviceNV)(void *) = NULL;
HANDLE (*wglDXRegisterObjectNV)(HANDLE, void *, GLuint, GLenum, GLenum) = NULL;
BOOL (*wglDXSetResourceShareHandleNV)(void *, HANDLE) = NULL;
BOOL (*wglDXUnlockObjectsNV)(HANDLE, GLint, HANDLE *) = NULL;
BOOL (*wglDXUnregisterObjectNV)(HANDLE, HANDLE) = NULL;
BOOL (*wglDelayBeforeSwapNV)(HDC, GLfloat) = NULL;
BOOL (*wglDeleteAssociatedContextAMD)(HGLRC) = NULL;
VOID (*wglDeleteBufferRegionARB)(HANDLE) = NULL;
BOOL (*wglDeleteContext)(HGLRC) = NULL;
BOOL (*wglDeleteDCNV)(HDC) = NULL;
BOOL (*wglDescribeLayerPlane)(HDC, int , int , UINT, const LAYERPLANEDESCRIPTOR *) = NULL;
VOID (*wglDestroyDisplayColorTableEXT)(GLushort) = NULL;
BOOL (*wglDestroyImageBufferI3D)(HDC, LPVOID) = NULL;
BOOL (*wglDestroyPbufferARB)(HPBUFFERARB) = NULL;
BOOL (*wglDestroyPbufferEXT)(HPBUFFEREXT) = NULL;
BOOL (*wglDisableFrameLockI3D)() = NULL;
BOOL (*wglDisableGenlockI3D)(HDC) = NULL;
BOOL (*wglEnableFrameLockI3D)() = NULL;
BOOL (*wglEnableGenlockI3D)(HDC) = NULL;
BOOL (*wglEndFrameTrackingI3D)() = NULL;
BOOL (*wglEnumGpuDevicesNV)(HGPUNV, UINT, PGPU_DEVICE) = NULL;
BOOL (*wglEnumGpusFromAffinityDCNV)(HDC, UINT, HGPUNV *) = NULL;
BOOL (*wglEnumGpusNV)(UINT, HGPUNV *) = NULL;
UINT (*wglEnumerateVideoCaptureDevicesNV)(HDC, HVIDEOINPUTDEVICENV *) = NULL;
int (*wglEnumerateVideoDevicesNV)(HDC, HVIDEOOUTPUTDEVICENV *) = NULL;
void (*wglFreeMemoryNV)(void *) = NULL;
BOOL (*wglGenlockSampleRateI3D)(HDC, UINT) = NULL;
BOOL (*wglGenlockSourceDelayI3D)(HDC, UINT) = NULL;
BOOL (*wglGenlockSourceEdgeI3D)(HDC, UINT) = NULL;
BOOL (*wglGenlockSourceI3D)(HDC, UINT) = NULL;
UINT (*wglGetContextGPUIDAMD)(HGLRC) = NULL;
HGLRC (*wglGetCurrentAssociatedContextAMD)() = NULL;
HGLRC (*wglGetCurrentContext)() = NULL;
HDC (*wglGetCurrentDC)() = NULL;
HDC (*wglGetCurrentReadDCARB)() = NULL;
HDC (*wglGetCurrentReadDCEXT)() = NULL;
BOOL (*wglGetDigitalVideoParametersI3D)(HDC, int , int *) = NULL;
const char * (*wglGetExtensionsStringARB)(HDC) = NULL;
const char * (*wglGetExtensionsStringEXT)() = NULL;
BOOL (*wglGetFrameUsageI3D)(float *) = NULL;
UINT (*wglGetGPUIDsAMD)(UINT, UINT *) = NULL;
INT (*wglGetGPUInfoAMD)(UINT, int , GLenum, UINT, void *) = NULL;
BOOL (*wglGetGammaTableI3D)(HDC, int , USHORT *, USHORT *, USHORT *) = NULL;
BOOL (*wglGetGammaTableParametersI3D)(HDC, int , int *) = NULL;
BOOL (*wglGetGenlockSampleRateI3D)(HDC, UINT *) = NULL;
BOOL (*wglGetGenlockSourceDelayI3D)(HDC, UINT *) = NULL;
BOOL (*wglGetGenlockSourceEdgeI3D)(HDC, UINT *) = NULL;
BOOL (*wglGetGenlockSourceI3D)(HDC, UINT *) = NULL;
int (*wglGetLayerPaletteEntries)(HDC, int , int , int , const COLORREF *) = NULL;
BOOL (*wglGetMscRateOML)(HDC, INT32 *, INT32 *) = NULL;
HDC (*wglGetPbufferDCARB)(HPBUFFERARB) = NULL;
HDC (*wglGetPbufferDCEXT)(HPBUFFEREXT) = NULL;
BOOL (*wglGetPixelFormatAttribfvARB)(HDC, int , int , UINT, const int *, FLOAT *) = NULL;
BOOL (*wglGetPixelFormatAttribfvEXT)(HDC, int , int , UINT, int *, FLOAT *) = NULL;
BOOL (*wglGetPixelFormatAttribivARB)(HDC, int , int , UINT, const int *, int *) = NULL;
BOOL (*wglGetPixelFormatAttribivEXT)(HDC, int , int , UINT, int *, int *) = NULL;
PROC (*wglGetProcAddress)(LPCSTR) = NULL;
int (*wglGetSwapIntervalEXT)() = NULL;
BOOL (*wglGetSyncValuesOML)(HDC, INT64 *, INT64 *, INT64 *) = NULL;
BOOL (*wglGetVideoDeviceNV)(HDC, int , HPVIDEODEV *) = NULL;
BOOL (*wglGetVideoInfoNV)(HPVIDEODEV, unsigned long *, unsigned long *) = NULL;
BOOL (*wglIsEnabledFrameLockI3D)(BOOL *) = NULL;
BOOL (*wglIsEnabledGenlockI3D)(HDC, BOOL *) = NULL;
BOOL (*wglJoinSwapGroupNV)(HDC, GLuint) = NULL;
GLboolean (*wglLoadDisplayColorTableEXT)(const GLushort *, GLuint) = NULL;
BOOL (*wglLockVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV) = NULL;
BOOL (*wglMakeAssociatedContextCurrentAMD)(HGLRC) = NULL;
BOOL (*wglMakeContextCurrentARB)(HDC, HDC, HGLRC) = NULL;
BOOL (*wglMakeContextCurrentEXT)(HDC, HDC, HGLRC) = NULL;
BOOL (*wglQueryCurrentContextNV)(int , int *) = NULL;
BOOL (*wglQueryFrameCountNV)(HDC, GLuint *) = NULL;
BOOL (*wglQueryFrameLockMasterI3D)(BOOL *) = NULL;
BOOL (*wglQueryFrameTrackingI3D)(DWORD *, DWORD *, float *) = NULL;
BOOL (*wglQueryGenlockMaxSourceDelayI3D)(HDC, UINT *, UINT *) = NULL;
BOOL (*wglQueryMaxSwapGroupsNV)(HDC, GLuint *, GLuint *) = NULL;
BOOL (*wglQueryPbufferARB)(HPBUFFERARB, int , int *) = NULL;
BOOL (*wglQueryPbufferEXT)(HPBUFFEREXT, int , int *) = NULL;
BOOL (*wglQuerySwapGroupNV)(HDC, GLuint *, GLuint *) = NULL;
BOOL (*wglQueryVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV, int , int *) = NULL;
BOOL (*wglRealizeLayerPalette)(HDC, int , BOOL) = NULL;
BOOL (*wglReleaseImageBufferEventsI3D)(HDC, const LPVOID *, UINT) = NULL;
int (*wglReleasePbufferDCARB)(HPBUFFERARB, HDC) = NULL;
int (*wglReleasePbufferDCEXT)(HPBUFFEREXT, HDC) = NULL;
BOOL (*wglReleaseTexImageARB)(HPBUFFERARB, int ) = NULL;
BOOL (*wglReleaseVideoCaptureDeviceNV)(HDC, HVIDEOINPUTDEVICENV) = NULL;
BOOL (*wglReleaseVideoDeviceNV)(HPVIDEODEV) = NULL;
BOOL (*wglReleaseVideoImageNV)(HPBUFFERARB, int ) = NULL;
BOOL (*wglResetFrameCountNV)(HDC) = NULL;
BOOL (*wglRestoreBufferRegionARB)(HANDLE, int , int , int , int , int , int ) = NULL;
BOOL (*wglSaveBufferRegionARB)(HANDLE, int , int , int , int ) = NULL;
BOOL (*wglSendPbufferToVideoNV)(HPBUFFERARB, int , unsigned long *, BOOL) = NULL;
BOOL (*wglSetDigitalVideoParametersI3D)(HDC, int , const int *) = NULL;
BOOL (*wglSetGammaTableI3D)(HDC, int , const USHORT *, const USHORT *, const USHORT *) = NULL;
BOOL (*wglSetGammaTableParametersI3D)(HDC, int , const int *) = NULL;
int (*wglSetLayerPaletteEntries)(HDC, int , int , int , const COLORREF *) = NULL;
BOOL (*wglSetPbufferAttribARB)(HPBUFFERARB, const int *) = NULL;
BOOL (*wglSetStereoEmitterState3DL)(HDC, UINT) = NULL;
BOOL (*wglShareLists)(HGLRC, HGLRC) = NULL;
INT64 (*wglSwapBuffersMscOML)(HDC, INT64, INT64, INT64) = NULL;
BOOL (*wglSwapIntervalEXT)(int ) = NULL;
BOOL (*wglSwapLayerBuffers)(HDC, UINT) = NULL;
INT64 (*wglSwapLayerBuffersMscOML)(HDC, int , INT64, INT64, INT64) = NULL;
BOOL (*wglUseFontBitmaps)(HDC, DWORD, DWORD, DWORD) = NULL;
BOOL (*wglUseFontBitmapsA)(HDC, DWORD, DWORD, DWORD) = NULL;
BOOL (*wglUseFontBitmapsW)(HDC, DWORD, DWORD, DWORD) = NULL;
BOOL (*wglUseFontOutlines)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) = NULL;
BOOL (*wglUseFontOutlinesA)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) = NULL;
BOOL (*wglUseFontOutlinesW)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) = NULL;
BOOL (*wglWaitForMscOML)(HDC, INT64, INT64, INT64, INT64 *, INT64 *, INT64 *) = NULL;
BOOL (*wglWaitForSbcOML)(HDC, INT64, INT64 *, INT64 *, INT64 *) = NULL;

bool GLPLATFORM_WGL_3DFX_multisample = false;
bool GLPLATFORM_WGL_3DL_stereo_control = false;
bool GLPLATFORM_WGL_AMD_gpu_association = false;
bool GLPLATFORM_WGL_ARB_buffer_region = false;
bool GLPLATFORM_WGL_ARB_context_flush_control = false;
bool GLPLATFORM_WGL_ARB_create_context = false;
bool GLPLATFORM_WGL_ARB_create_context_profile = false;
bool GLPLATFORM_WGL_ARB_create_context_robustness = false;
bool GLPLATFORM_WGL_ARB_extensions_string = false;
bool GLPLATFORM_WGL_ARB_framebuffer_sRGB = false;
bool GLPLATFORM_WGL_ARB_make_current_read = false;
bool GLPLATFORM_WGL_ARB_multisample = false;
bool GLPLATFORM_WGL_ARB_pbuffer = false;
bool GLPLATFORM_WGL_ARB_pixel_format = false;
bool GLPLATFORM_WGL_ARB_pixel_format_float = false;
bool GLPLATFORM_WGL_ARB_render_texture = false;
bool GLPLATFORM_WGL_ARB_robustness_application_isolation = false;
bool GLPLATFORM_WGL_ARB_robustness_share_group_isolation = false;
bool GLPLATFORM_WGL_ATI_pixel_format_float = false;
bool GLPLATFORM_WGL_EXT_create_context_es2_profile = false;
bool GLPLATFORM_WGL_EXT_create_context_es_profile = false;
bool GLPLATFORM_WGL_EXT_depth_float = false;
bool GLPLATFORM_WGL_EXT_display_color_table = false;
bool GLPLATFORM_WGL_EXT_extensions_string = false;
bool GLPLATFORM_WGL_EXT_framebuffer_sRGB = false;
bool GLPLATFORM_WGL_EXT_make_current_read = false;
bool GLPLATFORM_WGL_EXT_multisample = false;
bool GLPLATFORM_WGL_EXT_pbuffer = false;
bool GLPLATFORM_WGL_EXT_pixel_format = false;
bool GLPLATFORM_WGL_EXT_pixel_format_packed_float = false;
bool GLPLATFORM_WGL_EXT_swap_control = false;
bool GLPLATFORM_WGL_EXT_swap_control_tear = false;
bool GLPLATFORM_WGL_I3D_digital_video_control = false;
bool GLPLATFORM_WGL_I3D_gamma = false;
bool GLPLATFORM_WGL_I3D_genlock = false;
bool GLPLATFORM_WGL_I3D_image_buffer = false;
bool GLPLATFORM_WGL_I3D_swap_frame_lock = false;
bool GLPLATFORM_WGL_I3D_swap_frame_usage = false;
bool GLPLATFORM_WGL_NV_DX_interop = false;
bool GLPLATFORM_WGL_NV_DX_interop2 = false;
bool GLPLATFORM_WGL_NV_copy_image = false;
bool GLPLATFORM_WGL_NV_delay_before_swap = false;
bool GLPLATFORM_WGL_NV_float_buffer = false;
bool GLPLATFORM_WGL_NV_gpu_affinity = false;
bool GLPLATFORM_WGL_NV_multisample_coverage = false;
bool GLPLATFORM_WGL_NV_present_video = false;
bool GLPLATFORM_WGL_NV_render_depth_texture = false;
bool GLPLATFORM_WGL_NV_render_texture_rectangle = false;
bool GLPLATFORM_WGL_NV_swap_group = false;
bool GLPLATFORM_WGL_NV_vertex_array_range = false;
bool GLPLATFORM_WGL_NV_video_capture = false;
bool GLPLATFORM_WGL_NV_video_output = false;
bool GLPLATFORM_WGL_OML_sync_control = false;

bool glplatform_wgl_init(int maj, int min)
{
	int req_version = maj * 10 + min;
	if (req_version < 10) return false;
	if (req_version > 10) return false;
	wglAllocateMemoryNV = (void * (*)(GLsizei, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("wglAllocateMemoryNV");
	wglAssociateImageBufferEventsI3D = (BOOL (*)(HDC, const HANDLE *, const LPVOID *, const DWORD *, UINT) ) LoadProcAddress("wglAssociateImageBufferEventsI3D");
	wglBeginFrameTrackingI3D = (BOOL (*)() ) LoadProcAddress("wglBeginFrameTrackingI3D");
	wglBindDisplayColorTableEXT = (GLboolean (*)(GLushort) ) LoadProcAddress("wglBindDisplayColorTableEXT");
	wglBindSwapBarrierNV = (BOOL (*)(GLuint, GLuint) ) LoadProcAddress("wglBindSwapBarrierNV");
	wglBindTexImageARB = (BOOL (*)(HPBUFFERARB, int ) ) LoadProcAddress("wglBindTexImageARB");
	wglBindVideoCaptureDeviceNV = (BOOL (*)(UINT, HVIDEOINPUTDEVICENV) ) LoadProcAddress("wglBindVideoCaptureDeviceNV");
	wglBindVideoDeviceNV = (BOOL (*)(HDC, unsigned int , HVIDEOOUTPUTDEVICENV, const int *) ) LoadProcAddress("wglBindVideoDeviceNV");
	wglBindVideoImageNV = (BOOL (*)(HPVIDEODEV, HPBUFFERARB, int ) ) LoadProcAddress("wglBindVideoImageNV");
	wglBlitContextFramebufferAMD = (VOID (*)(HGLRC, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) ) LoadProcAddress("wglBlitContextFramebufferAMD");
	wglChoosePixelFormatARB = (BOOL (*)(HDC, const int *, const FLOAT *, UINT, int *, UINT *) ) LoadProcAddress("wglChoosePixelFormatARB");
	wglChoosePixelFormatEXT = (BOOL (*)(HDC, const int *, const FLOAT *, UINT, int *, UINT *) ) LoadProcAddress("wglChoosePixelFormatEXT");
	wglCopyContext = (BOOL (*)(HGLRC, HGLRC, UINT) ) LoadProcAddress("wglCopyContext");
	wglCopyImageSubDataNV = (BOOL (*)(HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, HGLRC, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("wglCopyImageSubDataNV");
	wglCreateAffinityDCNV = (HDC (*)(const HGPUNV *) ) LoadProcAddress("wglCreateAffinityDCNV");
	wglCreateAssociatedContextAMD = (HGLRC (*)(UINT) ) LoadProcAddress("wglCreateAssociatedContextAMD");
	wglCreateAssociatedContextAttribsAMD = (HGLRC (*)(UINT, HGLRC, const int *) ) LoadProcAddress("wglCreateAssociatedContextAttribsAMD");
	wglCreateBufferRegionARB = (HANDLE (*)(HDC, int , UINT) ) LoadProcAddress("wglCreateBufferRegionARB");
	wglCreateContextAttribsARB = (HGLRC (*)(HDC, HGLRC, const int *) ) LoadProcAddress("wglCreateContextAttribsARB");
	wglCreateDisplayColorTableEXT = (GLboolean (*)(GLushort) ) LoadProcAddress("wglCreateDisplayColorTableEXT");
	wglCreateImageBufferI3D = (LPVOID (*)(HDC, DWORD, UINT) ) LoadProcAddress("wglCreateImageBufferI3D");
	wglCreateLayerContext = (HGLRC (*)(HDC, int ) ) LoadProcAddress("wglCreateLayerContext");
	wglCreatePbufferARB = (HPBUFFERARB (*)(HDC, int , int , int , const int *) ) LoadProcAddress("wglCreatePbufferARB");
	wglCreatePbufferEXT = (HPBUFFEREXT (*)(HDC, int , int , int , const int *) ) LoadProcAddress("wglCreatePbufferEXT");
	wglDXCloseDeviceNV = (BOOL (*)(HANDLE) ) LoadProcAddress("wglDXCloseDeviceNV");
	wglDXLockObjectsNV = (BOOL (*)(HANDLE, GLint, HANDLE *) ) LoadProcAddress("wglDXLockObjectsNV");
	wglDXObjectAccessNV = (BOOL (*)(HANDLE, GLenum) ) LoadProcAddress("wglDXObjectAccessNV");
	wglDXOpenDeviceNV = (HANDLE (*)(void *) ) LoadProcAddress("wglDXOpenDeviceNV");
	wglDXRegisterObjectNV = (HANDLE (*)(HANDLE, void *, GLuint, GLenum, GLenum) ) LoadProcAddress("wglDXRegisterObjectNV");
	wglDXSetResourceShareHandleNV = (BOOL (*)(void *, HANDLE) ) LoadProcAddress("wglDXSetResourceShareHandleNV");
	wglDXUnlockObjectsNV = (BOOL (*)(HANDLE, GLint, HANDLE *) ) LoadProcAddress("wglDXUnlockObjectsNV");
	wglDXUnregisterObjectNV = (BOOL (*)(HANDLE, HANDLE) ) LoadProcAddress("wglDXUnregisterObjectNV");
	wglDelayBeforeSwapNV = (BOOL (*)(HDC, GLfloat) ) LoadProcAddress("wglDelayBeforeSwapNV");
	wglDeleteAssociatedContextAMD = (BOOL (*)(HGLRC) ) LoadProcAddress("wglDeleteAssociatedContextAMD");
	wglDeleteBufferRegionARB = (VOID (*)(HANDLE) ) LoadProcAddress("wglDeleteBufferRegionARB");
	wglDeleteContext = (BOOL (*)(HGLRC) ) LoadProcAddress("wglDeleteContext");
	wglDeleteDCNV = (BOOL (*)(HDC) ) LoadProcAddress("wglDeleteDCNV");
	wglDescribeLayerPlane = (BOOL (*)(HDC, int , int , UINT, const LAYERPLANEDESCRIPTOR *) ) LoadProcAddress("wglDescribeLayerPlane");
	wglDestroyDisplayColorTableEXT = (VOID (*)(GLushort) ) LoadProcAddress("wglDestroyDisplayColorTableEXT");
	wglDestroyImageBufferI3D = (BOOL (*)(HDC, LPVOID) ) LoadProcAddress("wglDestroyImageBufferI3D");
	wglDestroyPbufferARB = (BOOL (*)(HPBUFFERARB) ) LoadProcAddress("wglDestroyPbufferARB");
	wglDestroyPbufferEXT = (BOOL (*)(HPBUFFEREXT) ) LoadProcAddress("wglDestroyPbufferEXT");
	wglDisableFrameLockI3D = (BOOL (*)() ) LoadProcAddress("wglDisableFrameLockI3D");
	wglDisableGenlockI3D = (BOOL (*)(HDC) ) LoadProcAddress("wglDisableGenlockI3D");
	wglEnableFrameLockI3D = (BOOL (*)() ) LoadProcAddress("wglEnableFrameLockI3D");
	wglEnableGenlockI3D = (BOOL (*)(HDC) ) LoadProcAddress("wglEnableGenlockI3D");
	wglEndFrameTrackingI3D = (BOOL (*)() ) LoadProcAddress("wglEndFrameTrackingI3D");
	wglEnumGpuDevicesNV = (BOOL (*)(HGPUNV, UINT, PGPU_DEVICE) ) LoadProcAddress("wglEnumGpuDevicesNV");
	wglEnumGpusFromAffinityDCNV = (BOOL (*)(HDC, UINT, HGPUNV *) ) LoadProcAddress("wglEnumGpusFromAffinityDCNV");
	wglEnumGpusNV = (BOOL (*)(UINT, HGPUNV *) ) LoadProcAddress("wglEnumGpusNV");
	wglEnumerateVideoCaptureDevicesNV = (UINT (*)(HDC, HVIDEOINPUTDEVICENV *) ) LoadProcAddress("wglEnumerateVideoCaptureDevicesNV");
	wglEnumerateVideoDevicesNV = (int (*)(HDC, HVIDEOOUTPUTDEVICENV *) ) LoadProcAddress("wglEnumerateVideoDevicesNV");
	wglFreeMemoryNV = (void (*)(void *) ) LoadProcAddress("wglFreeMemoryNV");
	wglGenlockSampleRateI3D = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglGenlockSampleRateI3D");
	wglGenlockSourceDelayI3D = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglGenlockSourceDelayI3D");
	wglGenlockSourceEdgeI3D = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglGenlockSourceEdgeI3D");
	wglGenlockSourceI3D = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglGenlockSourceI3D");
	wglGetContextGPUIDAMD = (UINT (*)(HGLRC) ) LoadProcAddress("wglGetContextGPUIDAMD");
	wglGetCurrentAssociatedContextAMD = (HGLRC (*)() ) LoadProcAddress("wglGetCurrentAssociatedContextAMD");
	wglGetCurrentContext = (HGLRC (*)() ) LoadProcAddress("wglGetCurrentContext");
	wglGetCurrentDC = (HDC (*)() ) LoadProcAddress("wglGetCurrentDC");
	wglGetCurrentReadDCARB = (HDC (*)() ) LoadProcAddress("wglGetCurrentReadDCARB");
	wglGetCurrentReadDCEXT = (HDC (*)() ) LoadProcAddress("wglGetCurrentReadDCEXT");
	wglGetDigitalVideoParametersI3D = (BOOL (*)(HDC, int , int *) ) LoadProcAddress("wglGetDigitalVideoParametersI3D");
	wglGetExtensionsStringARB = (const char * (*)(HDC) ) LoadProcAddress("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT = (const char * (*)() ) LoadProcAddress("wglGetExtensionsStringEXT");
	wglGetFrameUsageI3D = (BOOL (*)(float *) ) LoadProcAddress("wglGetFrameUsageI3D");
	wglGetGPUIDsAMD = (UINT (*)(UINT, UINT *) ) LoadProcAddress("wglGetGPUIDsAMD");
	wglGetGPUInfoAMD = (INT (*)(UINT, int , GLenum, UINT, void *) ) LoadProcAddress("wglGetGPUInfoAMD");
	wglGetGammaTableI3D = (BOOL (*)(HDC, int , USHORT *, USHORT *, USHORT *) ) LoadProcAddress("wglGetGammaTableI3D");
	wglGetGammaTableParametersI3D = (BOOL (*)(HDC, int , int *) ) LoadProcAddress("wglGetGammaTableParametersI3D");
	wglGetGenlockSampleRateI3D = (BOOL (*)(HDC, UINT *) ) LoadProcAddress("wglGetGenlockSampleRateI3D");
	wglGetGenlockSourceDelayI3D = (BOOL (*)(HDC, UINT *) ) LoadProcAddress("wglGetGenlockSourceDelayI3D");
	wglGetGenlockSourceEdgeI3D = (BOOL (*)(HDC, UINT *) ) LoadProcAddress("wglGetGenlockSourceEdgeI3D");
	wglGetGenlockSourceI3D = (BOOL (*)(HDC, UINT *) ) LoadProcAddress("wglGetGenlockSourceI3D");
	wglGetLayerPaletteEntries = (int (*)(HDC, int , int , int , const COLORREF *) ) LoadProcAddress("wglGetLayerPaletteEntries");
	wglGetMscRateOML = (BOOL (*)(HDC, INT32 *, INT32 *) ) LoadProcAddress("wglGetMscRateOML");
	wglGetPbufferDCARB = (HDC (*)(HPBUFFERARB) ) LoadProcAddress("wglGetPbufferDCARB");
	wglGetPbufferDCEXT = (HDC (*)(HPBUFFEREXT) ) LoadProcAddress("wglGetPbufferDCEXT");
	wglGetPixelFormatAttribfvARB = (BOOL (*)(HDC, int , int , UINT, const int *, FLOAT *) ) LoadProcAddress("wglGetPixelFormatAttribfvARB");
	wglGetPixelFormatAttribfvEXT = (BOOL (*)(HDC, int , int , UINT, int *, FLOAT *) ) LoadProcAddress("wglGetPixelFormatAttribfvEXT");
	wglGetPixelFormatAttribivARB = (BOOL (*)(HDC, int , int , UINT, const int *, int *) ) LoadProcAddress("wglGetPixelFormatAttribivARB");
	wglGetPixelFormatAttribivEXT = (BOOL (*)(HDC, int , int , UINT, int *, int *) ) LoadProcAddress("wglGetPixelFormatAttribivEXT");
	wglGetProcAddress = (PROC (*)(LPCSTR) ) LoadProcAddress("wglGetProcAddress");
	wglGetSwapIntervalEXT = (int (*)() ) LoadProcAddress("wglGetSwapIntervalEXT");
	wglGetSyncValuesOML = (BOOL (*)(HDC, INT64 *, INT64 *, INT64 *) ) LoadProcAddress("wglGetSyncValuesOML");
	wglGetVideoDeviceNV = (BOOL (*)(HDC, int , HPVIDEODEV *) ) LoadProcAddress("wglGetVideoDeviceNV");
	wglGetVideoInfoNV = (BOOL (*)(HPVIDEODEV, unsigned long *, unsigned long *) ) LoadProcAddress("wglGetVideoInfoNV");
	wglIsEnabledFrameLockI3D = (BOOL (*)(BOOL *) ) LoadProcAddress("wglIsEnabledFrameLockI3D");
	wglIsEnabledGenlockI3D = (BOOL (*)(HDC, BOOL *) ) LoadProcAddress("wglIsEnabledGenlockI3D");
	wglJoinSwapGroupNV = (BOOL (*)(HDC, GLuint) ) LoadProcAddress("wglJoinSwapGroupNV");
	wglLoadDisplayColorTableEXT = (GLboolean (*)(const GLushort *, GLuint) ) LoadProcAddress("wglLoadDisplayColorTableEXT");
	wglLockVideoCaptureDeviceNV = (BOOL (*)(HDC, HVIDEOINPUTDEVICENV) ) LoadProcAddress("wglLockVideoCaptureDeviceNV");
	wglMakeAssociatedContextCurrentAMD = (BOOL (*)(HGLRC) ) LoadProcAddress("wglMakeAssociatedContextCurrentAMD");
	wglMakeContextCurrentARB = (BOOL (*)(HDC, HDC, HGLRC) ) LoadProcAddress("wglMakeContextCurrentARB");
	wglMakeContextCurrentEXT = (BOOL (*)(HDC, HDC, HGLRC) ) LoadProcAddress("wglMakeContextCurrentEXT");
	wglQueryCurrentContextNV = (BOOL (*)(int , int *) ) LoadProcAddress("wglQueryCurrentContextNV");
	wglQueryFrameCountNV = (BOOL (*)(HDC, GLuint *) ) LoadProcAddress("wglQueryFrameCountNV");
	wglQueryFrameLockMasterI3D = (BOOL (*)(BOOL *) ) LoadProcAddress("wglQueryFrameLockMasterI3D");
	wglQueryFrameTrackingI3D = (BOOL (*)(DWORD *, DWORD *, float *) ) LoadProcAddress("wglQueryFrameTrackingI3D");
	wglQueryGenlockMaxSourceDelayI3D = (BOOL (*)(HDC, UINT *, UINT *) ) LoadProcAddress("wglQueryGenlockMaxSourceDelayI3D");
	wglQueryMaxSwapGroupsNV = (BOOL (*)(HDC, GLuint *, GLuint *) ) LoadProcAddress("wglQueryMaxSwapGroupsNV");
	wglQueryPbufferARB = (BOOL (*)(HPBUFFERARB, int , int *) ) LoadProcAddress("wglQueryPbufferARB");
	wglQueryPbufferEXT = (BOOL (*)(HPBUFFEREXT, int , int *) ) LoadProcAddress("wglQueryPbufferEXT");
	wglQuerySwapGroupNV = (BOOL (*)(HDC, GLuint *, GLuint *) ) LoadProcAddress("wglQuerySwapGroupNV");
	wglQueryVideoCaptureDeviceNV = (BOOL (*)(HDC, HVIDEOINPUTDEVICENV, int , int *) ) LoadProcAddress("wglQueryVideoCaptureDeviceNV");
	wglRealizeLayerPalette = (BOOL (*)(HDC, int , BOOL) ) LoadProcAddress("wglRealizeLayerPalette");
	wglReleaseImageBufferEventsI3D = (BOOL (*)(HDC, const LPVOID *, UINT) ) LoadProcAddress("wglReleaseImageBufferEventsI3D");
	wglReleasePbufferDCARB = (int (*)(HPBUFFERARB, HDC) ) LoadProcAddress("wglReleasePbufferDCARB");
	wglReleasePbufferDCEXT = (int (*)(HPBUFFEREXT, HDC) ) LoadProcAddress("wglReleasePbufferDCEXT");
	wglReleaseTexImageARB = (BOOL (*)(HPBUFFERARB, int ) ) LoadProcAddress("wglReleaseTexImageARB");
	wglReleaseVideoCaptureDeviceNV = (BOOL (*)(HDC, HVIDEOINPUTDEVICENV) ) LoadProcAddress("wglReleaseVideoCaptureDeviceNV");
	wglReleaseVideoDeviceNV = (BOOL (*)(HPVIDEODEV) ) LoadProcAddress("wglReleaseVideoDeviceNV");
	wglReleaseVideoImageNV = (BOOL (*)(HPBUFFERARB, int ) ) LoadProcAddress("wglReleaseVideoImageNV");
	wglResetFrameCountNV = (BOOL (*)(HDC) ) LoadProcAddress("wglResetFrameCountNV");
	wglRestoreBufferRegionARB = (BOOL (*)(HANDLE, int , int , int , int , int , int ) ) LoadProcAddress("wglRestoreBufferRegionARB");
	wglSaveBufferRegionARB = (BOOL (*)(HANDLE, int , int , int , int ) ) LoadProcAddress("wglSaveBufferRegionARB");
	wglSendPbufferToVideoNV = (BOOL (*)(HPBUFFERARB, int , unsigned long *, BOOL) ) LoadProcAddress("wglSendPbufferToVideoNV");
	wglSetDigitalVideoParametersI3D = (BOOL (*)(HDC, int , const int *) ) LoadProcAddress("wglSetDigitalVideoParametersI3D");
	wglSetGammaTableI3D = (BOOL (*)(HDC, int , const USHORT *, const USHORT *, const USHORT *) ) LoadProcAddress("wglSetGammaTableI3D");
	wglSetGammaTableParametersI3D = (BOOL (*)(HDC, int , const int *) ) LoadProcAddress("wglSetGammaTableParametersI3D");
	wglSetLayerPaletteEntries = (int (*)(HDC, int , int , int , const COLORREF *) ) LoadProcAddress("wglSetLayerPaletteEntries");
	wglSetPbufferAttribARB = (BOOL (*)(HPBUFFERARB, const int *) ) LoadProcAddress("wglSetPbufferAttribARB");
	wglSetStereoEmitterState3DL = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglSetStereoEmitterState3DL");
	wglShareLists = (BOOL (*)(HGLRC, HGLRC) ) LoadProcAddress("wglShareLists");
	wglSwapBuffersMscOML = (INT64 (*)(HDC, INT64, INT64, INT64) ) LoadProcAddress("wglSwapBuffersMscOML");
	wglSwapIntervalEXT = (BOOL (*)(int ) ) LoadProcAddress("wglSwapIntervalEXT");
	wglSwapLayerBuffers = (BOOL (*)(HDC, UINT) ) LoadProcAddress("wglSwapLayerBuffers");
	wglSwapLayerBuffersMscOML = (INT64 (*)(HDC, int , INT64, INT64, INT64) ) LoadProcAddress("wglSwapLayerBuffersMscOML");
	wglUseFontBitmaps = (BOOL (*)(HDC, DWORD, DWORD, DWORD) ) LoadProcAddress("wglUseFontBitmaps");
	wglUseFontBitmapsA = (BOOL (*)(HDC, DWORD, DWORD, DWORD) ) LoadProcAddress("wglUseFontBitmapsA");
	wglUseFontBitmapsW = (BOOL (*)(HDC, DWORD, DWORD, DWORD) ) LoadProcAddress("wglUseFontBitmapsW");
	wglUseFontOutlines = (BOOL (*)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) ) LoadProcAddress("wglUseFontOutlines");
	wglUseFontOutlinesA = (BOOL (*)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) ) LoadProcAddress("wglUseFontOutlinesA");
	wglUseFontOutlinesW = (BOOL (*)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int , LPGLYPHMETRICSFLOAT) ) LoadProcAddress("wglUseFontOutlinesW");
	wglWaitForMscOML = (BOOL (*)(HDC, INT64, INT64, INT64, INT64 *, INT64 *, INT64 *) ) LoadProcAddress("wglWaitForMscOML");
	wglWaitForSbcOML = (BOOL (*)(HDC, INT64, INT64 *, INT64 *, INT64 *) ) LoadProcAddress("wglWaitForSbcOML");
	
	GLPLATFORM_WGL_3DL_stereo_control = GLPLATFORM_WGL_3DL_stereo_control && wglSetStereoEmitterState3DL;
	
	GLPLATFORM_WGL_AMD_gpu_association = GLPLATFORM_WGL_AMD_gpu_association && wglBlitContextFramebufferAMD && wglCreateAssociatedContextAMD
		 && wglCreateAssociatedContextAttribsAMD && wglDeleteAssociatedContextAMD && wglGetContextGPUIDAMD
		 && wglGetCurrentAssociatedContextAMD && wglGetGPUIDsAMD && wglGetGPUInfoAMD
		 && wglMakeAssociatedContextCurrentAMD;
	
	GLPLATFORM_WGL_ARB_buffer_region = GLPLATFORM_WGL_ARB_buffer_region && wglCreateBufferRegionARB && wglDeleteBufferRegionARB
		 && wglRestoreBufferRegionARB && wglSaveBufferRegionARB;
	
	GLPLATFORM_WGL_ARB_create_context = GLPLATFORM_WGL_ARB_create_context && wglCreateContextAttribsARB;
	
	GLPLATFORM_WGL_ARB_extensions_string = GLPLATFORM_WGL_ARB_extensions_string && wglGetExtensionsStringARB;
	
	GLPLATFORM_WGL_ARB_make_current_read = GLPLATFORM_WGL_ARB_make_current_read && wglGetCurrentReadDCARB && wglMakeContextCurrentARB;
	
	GLPLATFORM_WGL_ARB_pbuffer = GLPLATFORM_WGL_ARB_pbuffer && wglCreatePbufferARB && wglDestroyPbufferARB
		 && wglGetPbufferDCARB && wglQueryPbufferARB && wglReleasePbufferDCARB;
	
	GLPLATFORM_WGL_ARB_pixel_format = GLPLATFORM_WGL_ARB_pixel_format && wglChoosePixelFormatARB && wglGetPixelFormatAttribfvARB
		 && wglGetPixelFormatAttribivARB;
	
	GLPLATFORM_WGL_ARB_render_texture = GLPLATFORM_WGL_ARB_render_texture && wglBindTexImageARB && wglReleaseTexImageARB
		 && wglSetPbufferAttribARB;
	
	GLPLATFORM_WGL_EXT_display_color_table = GLPLATFORM_WGL_EXT_display_color_table && wglBindDisplayColorTableEXT && wglCreateDisplayColorTableEXT
		 && wglDestroyDisplayColorTableEXT && wglLoadDisplayColorTableEXT;
	
	GLPLATFORM_WGL_EXT_extensions_string = GLPLATFORM_WGL_EXT_extensions_string && wglGetExtensionsStringEXT;
	
	GLPLATFORM_WGL_EXT_make_current_read = GLPLATFORM_WGL_EXT_make_current_read && wglGetCurrentReadDCEXT && wglMakeContextCurrentEXT;
	
	GLPLATFORM_WGL_EXT_pbuffer = GLPLATFORM_WGL_EXT_pbuffer && wglCreatePbufferEXT && wglDestroyPbufferEXT
		 && wglGetPbufferDCEXT && wglQueryPbufferEXT && wglReleasePbufferDCEXT;
	
	GLPLATFORM_WGL_EXT_pixel_format = GLPLATFORM_WGL_EXT_pixel_format && wglChoosePixelFormatEXT && wglGetPixelFormatAttribfvEXT
		 && wglGetPixelFormatAttribivEXT;
	
	GLPLATFORM_WGL_EXT_swap_control = GLPLATFORM_WGL_EXT_swap_control && wglGetSwapIntervalEXT && wglSwapIntervalEXT;
	
	GLPLATFORM_WGL_I3D_digital_video_control = GLPLATFORM_WGL_I3D_digital_video_control && wglGetDigitalVideoParametersI3D && wglSetDigitalVideoParametersI3D;
	
	GLPLATFORM_WGL_I3D_gamma = GLPLATFORM_WGL_I3D_gamma && wglGetGammaTableI3D && wglGetGammaTableParametersI3D
		 && wglSetGammaTableI3D && wglSetGammaTableParametersI3D;
	
	GLPLATFORM_WGL_I3D_genlock = GLPLATFORM_WGL_I3D_genlock && wglDisableGenlockI3D && wglEnableGenlockI3D
		 && wglGenlockSampleRateI3D && wglGenlockSourceDelayI3D && wglGenlockSourceEdgeI3D
		 && wglGenlockSourceI3D && wglGetGenlockSampleRateI3D && wglGetGenlockSourceDelayI3D
		 && wglGetGenlockSourceEdgeI3D && wglGetGenlockSourceI3D && wglIsEnabledGenlockI3D
		 && wglQueryGenlockMaxSourceDelayI3D;
	
	GLPLATFORM_WGL_I3D_image_buffer = GLPLATFORM_WGL_I3D_image_buffer && wglAssociateImageBufferEventsI3D && wglCreateImageBufferI3D
		 && wglDestroyImageBufferI3D && wglReleaseImageBufferEventsI3D;
	
	GLPLATFORM_WGL_I3D_swap_frame_lock = GLPLATFORM_WGL_I3D_swap_frame_lock && wglDisableFrameLockI3D && wglEnableFrameLockI3D
		 && wglIsEnabledFrameLockI3D && wglQueryFrameLockMasterI3D;
	
	GLPLATFORM_WGL_I3D_swap_frame_usage = GLPLATFORM_WGL_I3D_swap_frame_usage && wglBeginFrameTrackingI3D && wglEndFrameTrackingI3D
		 && wglGetFrameUsageI3D && wglQueryFrameTrackingI3D;
	
	GLPLATFORM_WGL_NV_DX_interop = GLPLATFORM_WGL_NV_DX_interop && wglDXCloseDeviceNV && wglDXLockObjectsNV
		 && wglDXObjectAccessNV && wglDXOpenDeviceNV && wglDXRegisterObjectNV
		 && wglDXSetResourceShareHandleNV && wglDXUnlockObjectsNV && wglDXUnregisterObjectNV;
	
	GLPLATFORM_WGL_NV_copy_image = GLPLATFORM_WGL_NV_copy_image && wglCopyImageSubDataNV;
	
	GLPLATFORM_WGL_NV_delay_before_swap = GLPLATFORM_WGL_NV_delay_before_swap && wglDelayBeforeSwapNV;
	
	GLPLATFORM_WGL_NV_gpu_affinity = GLPLATFORM_WGL_NV_gpu_affinity && wglCreateAffinityDCNV && wglDeleteDCNV
		 && wglEnumGpuDevicesNV && wglEnumGpusFromAffinityDCNV && wglEnumGpusNV;
	
	GLPLATFORM_WGL_NV_present_video = GLPLATFORM_WGL_NV_present_video && wglBindVideoDeviceNV && wglEnumerateVideoDevicesNV
		 && wglQueryCurrentContextNV;
	
	GLPLATFORM_WGL_NV_swap_group = GLPLATFORM_WGL_NV_swap_group && wglBindSwapBarrierNV && wglJoinSwapGroupNV
		 && wglQueryFrameCountNV && wglQueryMaxSwapGroupsNV && wglQuerySwapGroupNV
		 && wglResetFrameCountNV;
	
	GLPLATFORM_WGL_NV_vertex_array_range = GLPLATFORM_WGL_NV_vertex_array_range && wglAllocateMemoryNV && wglFreeMemoryNV;
	
	GLPLATFORM_WGL_NV_video_capture = GLPLATFORM_WGL_NV_video_capture && wglBindVideoCaptureDeviceNV && wglEnumerateVideoCaptureDevicesNV
		 && wglLockVideoCaptureDeviceNV && wglQueryVideoCaptureDeviceNV && wglReleaseVideoCaptureDeviceNV;
	
	GLPLATFORM_WGL_NV_video_output = GLPLATFORM_WGL_NV_video_output && wglBindVideoImageNV && wglGetVideoDeviceNV
		 && wglGetVideoInfoNV && wglReleaseVideoDeviceNV && wglReleaseVideoImageNV
		 && wglSendPbufferToVideoNV;
	
	GLPLATFORM_WGL_OML_sync_control = GLPLATFORM_WGL_OML_sync_control && wglGetMscRateOML && wglGetSyncValuesOML
		 && wglSwapBuffersMscOML && wglSwapLayerBuffersMscOML && wglWaitForMscOML
		 && wglWaitForSbcOML;
	
	return wglCopyContext
	 && wglCreateLayerContext && wglDeleteContext && wglDescribeLayerPlane
	 && wglGetCurrentContext && wglGetCurrentDC && wglGetLayerPaletteEntries
	 && wglGetProcAddress && wglRealizeLayerPalette
	 && wglSetLayerPaletteEntries && wglShareLists && wglSwapLayerBuffers
	 && wglUseFontBitmaps && wglUseFontBitmapsA && wglUseFontBitmapsW
	 && wglUseFontOutlines && wglUseFontOutlinesA && wglUseFontOutlinesW;
}
