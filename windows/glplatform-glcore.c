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
#define GLPLATFORM_GL_VERSION 45
#define GLPLATFORM_ENABLE_GL_ARB_ES2_compatibility
#define GLPLATFORM_ENABLE_GL_ARB_ES3_1_compatibility
#define GLPLATFORM_ENABLE_GL_ARB_ES3_compatibility
#define GLPLATFORM_ENABLE_GL_ARB_arrays_of_arrays
#define GLPLATFORM_ENABLE_GL_ARB_base_instance
#define GLPLATFORM_ENABLE_GL_ARB_bindless_texture
#define GLPLATFORM_ENABLE_GL_ARB_blend_func_extended
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
#define GLPLATFORM_ENABLE_GL_ARB_cl_event
#define GLPLATFORM_ENABLE_GL_ARB_clear_buffer_object
#define GLPLATFORM_ENABLE_GL_ARB_clear_texture
#define GLPLATFORM_ENABLE_GL_ARB_clip_control
#define GLPLATFORM_ENABLE_GL_ARB_compressed_texture_pixel_storage
#define GLPLATFORM_ENABLE_GL_ARB_compute_shader
#define GLPLATFORM_ENABLE_GL_ARB_compute_variable_group_size
#define GLPLATFORM_ENABLE_GL_ARB_conditional_render_inverted
#define GLPLATFORM_ENABLE_GL_ARB_conservative_depth
#define GLPLATFORM_ENABLE_GL_ARB_copy_buffer
#define GLPLATFORM_ENABLE_GL_ARB_copy_image
#define GLPLATFORM_ENABLE_GL_ARB_cull_distance
#define GLPLATFORM_ENABLE_GL_ARB_debug_output
#define GLPLATFORM_ENABLE_GL_ARB_depth_buffer_float
#define GLPLATFORM_ENABLE_GL_ARB_depth_clamp
#define GLPLATFORM_ENABLE_GL_ARB_derivative_control
#define GLPLATFORM_ENABLE_GL_ARB_direct_state_access
#define GLPLATFORM_ENABLE_GL_ARB_draw_buffers_blend
#define GLPLATFORM_ENABLE_GL_ARB_draw_elements_base_vertex
#define GLPLATFORM_ENABLE_GL_ARB_draw_indirect
#define GLPLATFORM_ENABLE_GL_ARB_enhanced_layouts
#define GLPLATFORM_ENABLE_GL_ARB_explicit_attrib_location
#define GLPLATFORM_ENABLE_GL_ARB_explicit_uniform_location
#define GLPLATFORM_ENABLE_GL_ARB_fragment_coord_conventions
#define GLPLATFORM_ENABLE_GL_ARB_fragment_layer_viewport
#define GLPLATFORM_ENABLE_GL_ARB_framebuffer_no_attachments
#define GLPLATFORM_ENABLE_GL_ARB_framebuffer_object
#define GLPLATFORM_ENABLE_GL_ARB_framebuffer_sRGB
#define GLPLATFORM_ENABLE_GL_ARB_get_program_binary
#define GLPLATFORM_ENABLE_GL_ARB_get_texture_sub_image
#define GLPLATFORM_ENABLE_GL_ARB_gpu_shader5
#define GLPLATFORM_ENABLE_GL_ARB_gpu_shader_fp64
#define GLPLATFORM_ENABLE_GL_ARB_half_float_vertex
#define GLPLATFORM_ENABLE_GL_ARB_imaging
#define GLPLATFORM_ENABLE_GL_ARB_indirect_parameters
#define GLPLATFORM_ENABLE_GL_ARB_internalformat_query
#define GLPLATFORM_ENABLE_GL_ARB_internalformat_query2
#define GLPLATFORM_ENABLE_GL_ARB_invalidate_subdata
#define GLPLATFORM_ENABLE_GL_ARB_map_buffer_alignment
#define GLPLATFORM_ENABLE_GL_ARB_map_buffer_range
#define GLPLATFORM_ENABLE_GL_ARB_multi_bind
#define GLPLATFORM_ENABLE_GL_ARB_multi_draw_indirect
#define GLPLATFORM_ENABLE_GL_ARB_occlusion_query2
#define GLPLATFORM_ENABLE_GL_ARB_pipeline_statistics_query
#define GLPLATFORM_ENABLE_GL_ARB_program_interface_query
#define GLPLATFORM_ENABLE_GL_ARB_provoking_vertex
#define GLPLATFORM_ENABLE_GL_ARB_query_buffer_object
#define GLPLATFORM_ENABLE_GL_ARB_robust_buffer_access_behavior
#define GLPLATFORM_ENABLE_GL_ARB_robustness
#define GLPLATFORM_ENABLE_GL_ARB_robustness_isolation
#define GLPLATFORM_ENABLE_GL_ARB_sample_shading
#define GLPLATFORM_ENABLE_GL_ARB_sampler_objects
#define GLPLATFORM_ENABLE_GL_ARB_seamless_cube_map
#define GLPLATFORM_ENABLE_GL_ARB_seamless_cubemap_per_texture
#define GLPLATFORM_ENABLE_GL_ARB_separate_shader_objects
#define GLPLATFORM_ENABLE_GL_ARB_shader_atomic_counters
#define GLPLATFORM_ENABLE_GL_ARB_shader_bit_encoding
#define GLPLATFORM_ENABLE_GL_ARB_shader_draw_parameters
#define GLPLATFORM_ENABLE_GL_ARB_shader_group_vote
#define GLPLATFORM_ENABLE_GL_ARB_shader_image_load_store
#define GLPLATFORM_ENABLE_GL_ARB_shader_image_size
#define GLPLATFORM_ENABLE_GL_ARB_shader_precision
#define GLPLATFORM_ENABLE_GL_ARB_shader_stencil_export
#define GLPLATFORM_ENABLE_GL_ARB_shader_storage_buffer_object
#define GLPLATFORM_ENABLE_GL_ARB_shader_subroutine
#define GLPLATFORM_ENABLE_GL_ARB_shader_texture_image_samples
#define GLPLATFORM_ENABLE_GL_ARB_shading_language_420pack
#define GLPLATFORM_ENABLE_GL_ARB_shading_language_include
#define GLPLATFORM_ENABLE_GL_ARB_shading_language_packing
#define GLPLATFORM_ENABLE_GL_ARB_sparse_buffer
#define GLPLATFORM_ENABLE_GL_ARB_sparse_texture
#define GLPLATFORM_ENABLE_GL_ARB_stencil_texturing
#define GLPLATFORM_ENABLE_GL_ARB_sync
#define GLPLATFORM_ENABLE_GL_ARB_tessellation_shader
#define GLPLATFORM_ENABLE_GL_ARB_texture_barrier
#define GLPLATFORM_ENABLE_GL_ARB_texture_buffer_object_rgb32
#define GLPLATFORM_ENABLE_GL_ARB_texture_buffer_range
#define GLPLATFORM_ENABLE_GL_ARB_texture_compression_bptc
#define GLPLATFORM_ENABLE_GL_ARB_texture_compression_rgtc
#define GLPLATFORM_ENABLE_GL_ARB_texture_cube_map_array
#define GLPLATFORM_ENABLE_GL_ARB_texture_gather
#define GLPLATFORM_ENABLE_GL_ARB_texture_mirror_clamp_to_edge
#define GLPLATFORM_ENABLE_GL_ARB_texture_multisample
#define GLPLATFORM_ENABLE_GL_ARB_texture_query_levels
#define GLPLATFORM_ENABLE_GL_ARB_texture_query_lod
#define GLPLATFORM_ENABLE_GL_ARB_texture_rg
#define GLPLATFORM_ENABLE_GL_ARB_texture_rgb10_a2ui
#define GLPLATFORM_ENABLE_GL_ARB_texture_stencil8
#define GLPLATFORM_ENABLE_GL_ARB_texture_storage
#define GLPLATFORM_ENABLE_GL_ARB_texture_storage_multisample
#define GLPLATFORM_ENABLE_GL_ARB_texture_swizzle
#define GLPLATFORM_ENABLE_GL_ARB_texture_view
#define GLPLATFORM_ENABLE_GL_ARB_timer_query
#define GLPLATFORM_ENABLE_GL_ARB_transform_feedback2
#define GLPLATFORM_ENABLE_GL_ARB_transform_feedback3
#define GLPLATFORM_ENABLE_GL_ARB_transform_feedback_instanced
#define GLPLATFORM_ENABLE_GL_ARB_transform_feedback_overflow_query
#define GLPLATFORM_ENABLE_GL_ARB_uniform_buffer_object
#define GLPLATFORM_ENABLE_GL_ARB_vertex_array_bgra
#define GLPLATFORM_ENABLE_GL_ARB_vertex_array_object
#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_64bit
#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_vertex_type_10f_11f_11f_rev
#define GLPLATFORM_ENABLE_GL_ARB_vertex_type_2_10_10_10_rev
#define GLPLATFORM_ENABLE_GL_ARB_viewport_array
#define GLPLATFORM_ENABLE_GL_EXT_direct_state_access
#define GLPLATFORM_ENABLE_GL_KHR_context_flush_control
#define GLPLATFORM_ENABLE_GL_KHR_debug
#define GLPLATFORM_ENABLE_GL_KHR_robust_buffer_access_behavior
#define GLPLATFORM_ENABLE_GL_KHR_robustness
#define GLPLATFORM_ENABLE_GL_KHR_texture_compression_astc_hdr
#define GLPLATFORM_ENABLE_GL_KHR_texture_compression_astc_ldr
#include "glplatform-glcore.h"

void (*glActiveShaderProgram)(GLuint, GLuint) = NULL;
void (*glActiveTexture)(GLenum) = NULL;
void (*glAttachShader)(GLuint, GLuint) = NULL;
void (*glBeginConditionalRender)(GLuint, GLenum) = NULL;
void (*glBeginQuery)(GLenum, GLuint) = NULL;
void (*glBeginQueryIndexed)(GLenum, GLuint, GLuint) = NULL;
void (*glBeginTransformFeedback)(GLenum) = NULL;
void (*glBindAttribLocation)(GLuint, GLuint, const GLchar *) = NULL;
void (*glBindBuffer)(GLenum, GLuint) = NULL;
void (*glBindBufferBase)(GLenum, GLuint, GLuint) = NULL;
void (*glBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr) = NULL;
void (*glBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *) = NULL;
void (*glBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *) = NULL;
void (*glBindFragDataLocation)(GLuint, GLuint, const GLchar *) = NULL;
void (*glBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *) = NULL;
void (*glBindFramebuffer)(GLenum, GLuint) = NULL;
void (*glBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum) = NULL;
void (*glBindImageTextures)(GLuint, GLsizei, const GLuint *) = NULL;
void (*glBindMultiTextureEXT)(GLenum, GLenum, GLuint) = NULL;
void (*glBindProgramPipeline)(GLuint) = NULL;
void (*glBindRenderbuffer)(GLenum, GLuint) = NULL;
void (*glBindSampler)(GLuint, GLuint) = NULL;
void (*glBindSamplers)(GLuint, GLsizei, const GLuint *) = NULL;
void (*glBindTexture)(GLenum, GLuint) = NULL;
void (*glBindTextureUnit)(GLuint, GLuint) = NULL;
void (*glBindTextures)(GLuint, GLsizei, const GLuint *) = NULL;
void (*glBindTransformFeedback)(GLenum, GLuint) = NULL;
void (*glBindVertexArray)(GLuint) = NULL;
void (*glBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei) = NULL;
void (*glBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = NULL;
void (*glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glBlendEquation)(GLenum) = NULL;
void (*glBlendEquationSeparate)(GLenum, GLenum) = NULL;
void (*glBlendEquationSeparatei)(GLuint, GLenum, GLenum) = NULL;
void (*glBlendEquationSeparateiARB)(GLuint, GLenum, GLenum) = NULL;
void (*glBlendEquationi)(GLuint, GLenum) = NULL;
void (*glBlendEquationiARB)(GLuint, GLenum) = NULL;
void (*glBlendFunc)(GLenum, GLenum) = NULL;
void (*glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum) = NULL;
void (*glBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum) = NULL;
void (*glBlendFuncSeparateiARB)(GLuint, GLenum, GLenum, GLenum, GLenum) = NULL;
void (*glBlendFunci)(GLuint, GLenum, GLenum) = NULL;
void (*glBlendFunciARB)(GLuint, GLenum, GLenum) = NULL;
void (*glBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = NULL;
void (*glBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) = NULL;
void (*glBufferData)(GLenum, GLsizeiptr, const void *, GLenum) = NULL;
void (*glBufferPageCommitmentARB)(GLenum, GLintptr, GLsizeiptr, GLboolean) = NULL;
void (*glBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield) = NULL;
void (*glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *) = NULL;
GLenum (*glCheckFramebufferStatus)(GLenum) = NULL;
GLenum (*glCheckNamedFramebufferStatus)(GLuint, GLenum) = NULL;
GLenum (*glCheckNamedFramebufferStatusEXT)(GLuint, GLenum) = NULL;
void (*glClampColor)(GLenum, GLenum) = NULL;
void (*glClear)(GLbitfield) = NULL;
void (*glClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *) = NULL;
void (*glClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) = NULL;
void (*glClearBufferfi)(GLenum, GLint, GLfloat, GLint) = NULL;
void (*glClearBufferfv)(GLenum, GLint, const GLfloat *) = NULL;
void (*glClearBufferiv)(GLenum, GLint, const GLint *) = NULL;
void (*glClearBufferuiv)(GLenum, GLint, const GLuint *) = NULL;
void (*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glClearDepth)(GLdouble) = NULL;
void (*glClearDepthf)(GLfloat) = NULL;
void (*glClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *) = NULL;
void (*glClearNamedBufferDataEXT)(GLuint, GLenum, GLenum, GLenum, const void *) = NULL;
void (*glClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glClearNamedBufferSubDataEXT)(GLuint, GLenum, GLsizeiptr, GLsizeiptr, GLenum, GLenum, const void *) = NULL;
void (*glClearNamedFramebufferfi)(GLuint, GLenum, const GLfloat, GLint) = NULL;
void (*glClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *) = NULL;
void (*glClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *) = NULL;
void (*glClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *) = NULL;
void (*glClearStencil)(GLint) = NULL;
void (*glClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *) = NULL;
void (*glClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glClientAttribDefaultEXT)(GLbitfield) = NULL;
GLenum (*glClientWaitSync)(GLsync, GLbitfield, GLuint64) = NULL;
void (*glClipControl)(GLenum, GLenum) = NULL;
void (*glColorMask)(GLboolean, GLboolean, GLboolean, GLboolean) = NULL;
void (*glColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean) = NULL;
void (*glCompileShader)(GLuint) = NULL;
void (*glCompileShaderIncludeARB)(GLuint, GLsizei, const GLchar *const*, const GLint *) = NULL;
void (*glCompressedMultiTexImage1DEXT)(GLenum, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedMultiTexImage2DEXT)(GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedMultiTexImage3DEXT)(GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedMultiTexSubImage1DEXT)(GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedMultiTexSubImage2DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedMultiTexSubImage3DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureImage1DEXT)(GLuint, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTextureImage2DEXT)(GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTextureImage3DEXT)(GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage1DEXT)(GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage2DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCompressedTextureSubImage3DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) = NULL;
void (*glCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) = NULL;
void (*glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = NULL;
void (*glCopyMultiTexImage1DEXT)(GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) = NULL;
void (*glCopyMultiTexImage2DEXT)(GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) = NULL;
void (*glCopyMultiTexSubImage1DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei) = NULL;
void (*glCopyMultiTexSubImage2DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyMultiTexSubImage3DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizei) = NULL;
void (*glCopyTexImage1D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) = NULL;
void (*glCopyTexImage2D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) = NULL;
void (*glCopyTexSubImage1D)(GLenum, GLint, GLint, GLint, GLint, GLsizei) = NULL;
void (*glCopyTexSubImage2D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyTextureImage1DEXT)(GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) = NULL;
void (*glCopyTextureImage2DEXT)(GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) = NULL;
void (*glCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint, GLint, GLsizei) = NULL;
void (*glCopyTextureSubImage1DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei) = NULL;
void (*glCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyTextureSubImage2DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCopyTextureSubImage3DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glCreateBuffers)(GLsizei, GLuint *) = NULL;
void (*glCreateFramebuffers)(GLsizei, GLuint *) = NULL;
GLuint (*glCreateProgram)() = NULL;
void (*glCreateProgramPipelines)(GLsizei, GLuint *) = NULL;
void (*glCreateQueries)(GLenum, GLsizei, GLuint *) = NULL;
void (*glCreateRenderbuffers)(GLsizei, GLuint *) = NULL;
void (*glCreateSamplers)(GLsizei, GLuint *) = NULL;
GLuint (*glCreateShader)(GLenum) = NULL;
GLuint (*glCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*) = NULL;
GLsync (*glCreateSyncFromCLeventARB)(struct _cl_context *, struct _cl_event *, GLbitfield) = NULL;
void (*glCreateTextures)(GLenum, GLsizei, GLuint *) = NULL;
void (*glCreateTransformFeedbacks)(GLsizei, GLuint *) = NULL;
void (*glCreateVertexArrays)(GLsizei, GLuint *) = NULL;
void (*glCullFace)(GLenum) = NULL;
void (*glDebugMessageCallback)(GLDEBUGPROC, const void *) = NULL;
void (*glDebugMessageCallbackARB)(GLDEBUGPROCARB, const void *) = NULL;
void (*glDebugMessageCallbackKHR)(GLDEBUGPROCKHR, const void *) = NULL;
void (*glDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) = NULL;
void (*glDebugMessageControlARB)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) = NULL;
void (*glDebugMessageControlKHR)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) = NULL;
void (*glDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) = NULL;
void (*glDebugMessageInsertARB)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) = NULL;
void (*glDebugMessageInsertKHR)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) = NULL;
void (*glDeleteBuffers)(GLsizei, const GLuint *) = NULL;
void (*glDeleteFramebuffers)(GLsizei, const GLuint *) = NULL;
void (*glDeleteNamedStringARB)(GLint, const GLchar *) = NULL;
void (*glDeleteProgram)(GLuint) = NULL;
void (*glDeleteProgramPipelines)(GLsizei, const GLuint *) = NULL;
void (*glDeleteQueries)(GLsizei, const GLuint *) = NULL;
void (*glDeleteRenderbuffers)(GLsizei, const GLuint *) = NULL;
void (*glDeleteSamplers)(GLsizei, const GLuint *) = NULL;
void (*glDeleteShader)(GLuint) = NULL;
void (*glDeleteSync)(GLsync) = NULL;
void (*glDeleteTextures)(GLsizei, const GLuint *) = NULL;
void (*glDeleteTransformFeedbacks)(GLsizei, const GLuint *) = NULL;
void (*glDeleteVertexArrays)(GLsizei, const GLuint *) = NULL;
void (*glDepthFunc)(GLenum) = NULL;
void (*glDepthMask)(GLboolean) = NULL;
void (*glDepthRange)(GLdouble, GLdouble) = NULL;
void (*glDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *) = NULL;
void (*glDepthRangeIndexed)(GLuint, GLdouble, GLdouble) = NULL;
void (*glDepthRangef)(GLfloat, GLfloat) = NULL;
void (*glDetachShader)(GLuint, GLuint) = NULL;
void (*glDisable)(GLenum) = NULL;
void (*glDisableClientStateIndexedEXT)(GLenum, GLuint) = NULL;
void (*glDisableClientStateiEXT)(GLenum, GLuint) = NULL;
void (*glDisableIndexedEXT)(GLenum, GLuint) = NULL;
void (*glDisableVertexArrayAttrib)(GLuint, GLuint) = NULL;
void (*glDisableVertexArrayAttribEXT)(GLuint, GLuint) = NULL;
void (*glDisableVertexArrayEXT)(GLuint, GLenum) = NULL;
void (*glDisableVertexAttribArray)(GLuint) = NULL;
void (*glDisablei)(GLenum, GLuint) = NULL;
void (*glDispatchCompute)(GLuint, GLuint, GLuint) = NULL;
void (*glDispatchComputeGroupSizeARB)(GLuint, GLuint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glDispatchComputeIndirect)(GLintptr) = NULL;
void (*glDrawArrays)(GLenum, GLint, GLsizei) = NULL;
void (*glDrawArraysIndirect)(GLenum, const void *) = NULL;
void (*glDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei) = NULL;
void (*glDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint) = NULL;
void (*glDrawBuffer)(GLenum) = NULL;
void (*glDrawBuffers)(GLsizei, const GLenum *) = NULL;
void (*glDrawElements)(GLenum, GLsizei, GLenum, const void *) = NULL;
void (*glDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint) = NULL;
void (*glDrawElementsIndirect)(GLenum, GLenum, const void *) = NULL;
void (*glDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei) = NULL;
void (*glDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint) = NULL;
void (*glDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint) = NULL;
void (*glDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint) = NULL;
void (*glDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *) = NULL;
void (*glDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint) = NULL;
void (*glDrawTransformFeedback)(GLenum, GLuint) = NULL;
void (*glDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei) = NULL;
void (*glDrawTransformFeedbackStream)(GLenum, GLuint, GLuint) = NULL;
void (*glDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei) = NULL;
void (*glEnable)(GLenum) = NULL;
void (*glEnableClientStateIndexedEXT)(GLenum, GLuint) = NULL;
void (*glEnableClientStateiEXT)(GLenum, GLuint) = NULL;
void (*glEnableIndexedEXT)(GLenum, GLuint) = NULL;
void (*glEnableVertexArrayAttrib)(GLuint, GLuint) = NULL;
void (*glEnableVertexArrayAttribEXT)(GLuint, GLuint) = NULL;
void (*glEnableVertexArrayEXT)(GLuint, GLenum) = NULL;
void (*glEnableVertexAttribArray)(GLuint) = NULL;
void (*glEnablei)(GLenum, GLuint) = NULL;
void (*glEndConditionalRender)() = NULL;
void (*glEndQuery)(GLenum) = NULL;
void (*glEndQueryIndexed)(GLenum, GLuint) = NULL;
void (*glEndTransformFeedback)() = NULL;
GLsync (*glFenceSync)(GLenum, GLbitfield) = NULL;
void (*glFinish)() = NULL;
void (*glFlush)() = NULL;
void (*glFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr) = NULL;
void (*glFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizei) = NULL;
void (*glFlushMappedNamedBufferRangeEXT)(GLuint, GLintptr, GLsizeiptr) = NULL;
void (*glFramebufferDrawBufferEXT)(GLuint, GLenum) = NULL;
void (*glFramebufferDrawBuffersEXT)(GLuint, GLsizei, const GLenum *) = NULL;
void (*glFramebufferParameteri)(GLenum, GLenum, GLint) = NULL;
void (*glFramebufferReadBufferEXT)(GLuint, GLenum) = NULL;
void (*glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint) = NULL;
void (*glFramebufferTexture)(GLenum, GLenum, GLuint, GLint) = NULL;
void (*glFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint) = NULL;
void (*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint) = NULL;
void (*glFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint) = NULL;
void (*glFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint) = NULL;
void (*glFrontFace)(GLenum) = NULL;
void (*glGenBuffers)(GLsizei, GLuint *) = NULL;
void (*glGenFramebuffers)(GLsizei, GLuint *) = NULL;
void (*glGenProgramPipelines)(GLsizei, GLuint *) = NULL;
void (*glGenQueries)(GLsizei, GLuint *) = NULL;
void (*glGenRenderbuffers)(GLsizei, GLuint *) = NULL;
void (*glGenSamplers)(GLsizei, GLuint *) = NULL;
void (*glGenTextures)(GLsizei, GLuint *) = NULL;
void (*glGenTransformFeedbacks)(GLsizei, GLuint *) = NULL;
void (*glGenVertexArrays)(GLsizei, GLuint *) = NULL;
void (*glGenerateMipmap)(GLenum) = NULL;
void (*glGenerateMultiTexMipmapEXT)(GLenum, GLenum) = NULL;
void (*glGenerateTextureMipmap)(GLuint) = NULL;
void (*glGenerateTextureMipmapEXT)(GLuint, GLenum) = NULL;
void (*glGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *) = NULL;
void (*glGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = NULL;
void (*glGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *) = NULL;
void (*glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) = NULL;
void (*glGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *) = NULL;
void (*glGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *) = NULL;
void (*glGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *) = NULL;
GLint (*glGetAttribLocation)(GLuint, const GLchar *) = NULL;
void (*glGetBooleanIndexedvEXT)(GLenum, GLuint, GLboolean *) = NULL;
void (*glGetBooleani_v)(GLenum, GLuint, GLboolean *) = NULL;
void (*glGetBooleanv)(GLenum, GLboolean *) = NULL;
void (*glGetBufferParameteri64v)(GLenum, GLenum, GLint64 *) = NULL;
void (*glGetBufferParameteriv)(GLenum, GLenum, GLint *) = NULL;
void (*glGetBufferPointerv)(GLenum, GLenum, void **) = NULL;
void (*glGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *) = NULL;
void (*glGetCompressedMultiTexImageEXT)(GLenum, GLenum, GLint, void *) = NULL;
void (*glGetCompressedTexImage)(GLenum, GLint, void *) = NULL;
void (*glGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *) = NULL;
void (*glGetCompressedTextureImageEXT)(GLuint, GLenum, GLint, void *) = NULL;
void (*glGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *) = NULL;
GLuint (*glGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) = NULL;
GLuint (*glGetDebugMessageLogARB)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) = NULL;
GLuint (*glGetDebugMessageLogKHR)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) = NULL;
void (*glGetDoubleIndexedvEXT)(GLenum, GLuint, GLdouble *) = NULL;
void (*glGetDoublei_v)(GLenum, GLuint, GLdouble *) = NULL;
void (*glGetDoublei_vEXT)(GLenum, GLuint, GLdouble *) = NULL;
void (*glGetDoublev)(GLenum, GLdouble *) = NULL;
GLenum (*glGetError)() = NULL;
void (*glGetFloatIndexedvEXT)(GLenum, GLuint, GLfloat *) = NULL;
void (*glGetFloati_v)(GLenum, GLuint, GLfloat *) = NULL;
void (*glGetFloati_vEXT)(GLenum, GLuint, GLfloat *) = NULL;
void (*glGetFloatv)(GLenum, GLfloat *) = NULL;
GLint (*glGetFragDataIndex)(GLuint, const GLchar *) = NULL;
GLint (*glGetFragDataLocation)(GLuint, const GLchar *) = NULL;
void (*glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *) = NULL;
void (*glGetFramebufferParameteriv)(GLenum, GLenum, GLint *) = NULL;
void (*glGetFramebufferParameterivEXT)(GLuint, GLenum, GLint *) = NULL;
GLenum (*glGetGraphicsResetStatus)() = NULL;
GLenum (*glGetGraphicsResetStatusARB)() = NULL;
GLenum (*glGetGraphicsResetStatusKHR)() = NULL;
GLuint64 (*glGetImageHandleARB)(GLuint, GLint, GLboolean, GLint, GLenum) = NULL;
void (*glGetInteger64i_v)(GLenum, GLuint, GLint64 *) = NULL;
void (*glGetInteger64v)(GLenum, GLint64 *) = NULL;
void (*glGetIntegerIndexedvEXT)(GLenum, GLuint, GLint *) = NULL;
void (*glGetIntegeri_v)(GLenum, GLuint, GLint *) = NULL;
void (*glGetIntegerv)(GLenum, GLint *) = NULL;
void (*glGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *) = NULL;
void (*glGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *) = NULL;
void (*glGetMultiTexEnvfvEXT)(GLenum, GLenum, GLenum, GLfloat *) = NULL;
void (*glGetMultiTexEnvivEXT)(GLenum, GLenum, GLenum, GLint *) = NULL;
void (*glGetMultiTexGendvEXT)(GLenum, GLenum, GLenum, GLdouble *) = NULL;
void (*glGetMultiTexGenfvEXT)(GLenum, GLenum, GLenum, GLfloat *) = NULL;
void (*glGetMultiTexGenivEXT)(GLenum, GLenum, GLenum, GLint *) = NULL;
void (*glGetMultiTexImageEXT)(GLenum, GLenum, GLint, GLenum, GLenum, void *) = NULL;
void (*glGetMultiTexLevelParameterfvEXT)(GLenum, GLenum, GLint, GLenum, GLfloat *) = NULL;
void (*glGetMultiTexLevelParameterivEXT)(GLenum, GLenum, GLint, GLenum, GLint *) = NULL;
void (*glGetMultiTexParameterIivEXT)(GLenum, GLenum, GLenum, GLint *) = NULL;
void (*glGetMultiTexParameterIuivEXT)(GLenum, GLenum, GLenum, GLuint *) = NULL;
void (*glGetMultiTexParameterfvEXT)(GLenum, GLenum, GLenum, GLfloat *) = NULL;
void (*glGetMultiTexParameterivEXT)(GLenum, GLenum, GLenum, GLint *) = NULL;
void (*glGetMultisamplefv)(GLenum, GLuint, GLfloat *) = NULL;
void (*glGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *) = NULL;
void (*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedBufferParameterivEXT)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedBufferPointerv)(GLuint, GLenum, void **) = NULL;
void (*glGetNamedBufferPointervEXT)(GLuint, GLenum, void **) = NULL;
void (*glGetNamedBufferSubData)(GLuint, GLintptr, GLsizei, void *) = NULL;
void (*glGetNamedBufferSubDataEXT)(GLuint, GLintptr, GLsizeiptr, void *) = NULL;
void (*glGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetNamedFramebufferAttachmentParameterivEXT)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedFramebufferParameterivEXT)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedProgramLocalParameterIivEXT)(GLuint, GLenum, GLuint, GLint *) = NULL;
void (*glGetNamedProgramLocalParameterIuivEXT)(GLuint, GLenum, GLuint, GLuint *) = NULL;
void (*glGetNamedProgramLocalParameterdvEXT)(GLuint, GLenum, GLuint, GLdouble *) = NULL;
void (*glGetNamedProgramLocalParameterfvEXT)(GLuint, GLenum, GLuint, GLfloat *) = NULL;
void (*glGetNamedProgramStringEXT)(GLuint, GLenum, GLenum, void *) = NULL;
void (*glGetNamedProgramivEXT)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedRenderbufferParameterivEXT)(GLuint, GLenum, GLint *) = NULL;
void (*glGetNamedStringARB)(GLint, const GLchar *, GLsizei, GLint *, GLchar *) = NULL;
void (*glGetNamedStringivARB)(GLint, const GLchar *, GLenum, GLint *) = NULL;
void (*glGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetObjectLabelKHR)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetObjectPtrLabelKHR)(const void *, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetPointerIndexedvEXT)(GLenum, GLuint, void **) = NULL;
void (*glGetPointeri_vEXT)(GLenum, GLuint, void **) = NULL;
void (*glGetPointerv)(GLenum, void **) = NULL;
void (*glGetPointervKHR)(GLenum, void **) = NULL;
void (*glGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *) = NULL;
void (*glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetProgramPipelineiv)(GLuint, GLenum, GLint *) = NULL;
GLuint (*glGetProgramResourceIndex)(GLuint, GLenum, const GLchar *) = NULL;
GLint (*glGetProgramResourceLocation)(GLuint, GLenum, const GLchar *) = NULL;
GLint (*glGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *) = NULL;
void (*glGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *) = NULL;
void (*glGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetProgramiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr) = NULL;
void (*glGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr) = NULL;
void (*glGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr) = NULL;
void (*glGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr) = NULL;
void (*glGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *) = NULL;
void (*glGetQueryObjecti64v)(GLuint, GLenum, GLint64 *) = NULL;
void (*glGetQueryObjectiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *) = NULL;
void (*glGetQueryObjectuiv)(GLuint, GLenum, GLuint *) = NULL;
void (*glGetQueryiv)(GLenum, GLenum, GLint *) = NULL;
void (*glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *) = NULL;
void (*glGetSamplerParameterIiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *) = NULL;
void (*glGetSamplerParameterfv)(GLuint, GLenum, GLfloat *) = NULL;
void (*glGetSamplerParameteriv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *) = NULL;
void (*glGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *) = NULL;
void (*glGetShaderiv)(GLuint, GLenum, GLint *) = NULL;
const GLubyte * (*glGetString)(GLenum) = NULL;
const GLubyte * (*glGetStringi)(GLenum, GLuint) = NULL;
GLuint (*glGetSubroutineIndex)(GLuint, GLenum, const GLchar *) = NULL;
GLint (*glGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *) = NULL;
void (*glGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *) = NULL;
void (*glGetTexImage)(GLenum, GLint, GLenum, GLenum, void *) = NULL;
void (*glGetTexLevelParameterfv)(GLenum, GLint, GLenum, GLfloat *) = NULL;
void (*glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint *) = NULL;
void (*glGetTexParameterIiv)(GLenum, GLenum, GLint *) = NULL;
void (*glGetTexParameterIuiv)(GLenum, GLenum, GLuint *) = NULL;
void (*glGetTexParameterfv)(GLenum, GLenum, GLfloat *) = NULL;
void (*glGetTexParameteriv)(GLenum, GLenum, GLint *) = NULL;
GLuint64 (*glGetTextureHandleARB)(GLuint) = NULL;
void (*glGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glGetTextureImageEXT)(GLuint, GLenum, GLint, GLenum, GLenum, void *) = NULL;
void (*glGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *) = NULL;
void (*glGetTextureLevelParameterfvEXT)(GLuint, GLenum, GLint, GLenum, GLfloat *) = NULL;
void (*glGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *) = NULL;
void (*glGetTextureLevelParameterivEXT)(GLuint, GLenum, GLint, GLenum, GLint *) = NULL;
void (*glGetTextureParameterIiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetTextureParameterIivEXT)(GLuint, GLenum, GLenum, GLint *) = NULL;
void (*glGetTextureParameterIuiv)(GLuint, GLenum, GLuint *) = NULL;
void (*glGetTextureParameterIuivEXT)(GLuint, GLenum, GLenum, GLuint *) = NULL;
void (*glGetTextureParameterfv)(GLuint, GLenum, GLfloat *) = NULL;
void (*glGetTextureParameterfvEXT)(GLuint, GLenum, GLenum, GLfloat *) = NULL;
void (*glGetTextureParameteriv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetTextureParameterivEXT)(GLuint, GLenum, GLenum, GLint *) = NULL;
GLuint64 (*glGetTextureSamplerHandleARB)(GLuint, GLuint) = NULL;
void (*glGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *) = NULL;
void (*glGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *) = NULL;
void (*glGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *) = NULL;
void (*glGetTransformFeedbackiv)(GLuint, GLenum, GLint *) = NULL;
GLuint (*glGetUniformBlockIndex)(GLuint, const GLchar *) = NULL;
void (*glGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *) = NULL;
GLint (*glGetUniformLocation)(GLuint, const GLchar *) = NULL;
void (*glGetUniformSubroutineuiv)(GLenum, GLint, GLuint *) = NULL;
void (*glGetUniformdv)(GLuint, GLint, GLdouble *) = NULL;
void (*glGetUniformfv)(GLuint, GLint, GLfloat *) = NULL;
void (*glGetUniformiv)(GLuint, GLint, GLint *) = NULL;
void (*glGetUniformuiv)(GLuint, GLint, GLuint *) = NULL;
void (*glGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *) = NULL;
void (*glGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *) = NULL;
void (*glGetVertexArrayIntegeri_vEXT)(GLuint, GLuint, GLenum, GLint *) = NULL;
void (*glGetVertexArrayIntegervEXT)(GLuint, GLenum, GLint *) = NULL;
void (*glGetVertexArrayPointeri_vEXT)(GLuint, GLuint, GLenum, void **) = NULL;
void (*glGetVertexArrayPointervEXT)(GLuint, GLenum, void **) = NULL;
void (*glGetVertexArrayiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetVertexAttribIiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetVertexAttribIuiv)(GLuint, GLenum, GLuint *) = NULL;
void (*glGetVertexAttribLdv)(GLuint, GLenum, GLdouble *) = NULL;
void (*glGetVertexAttribLui64vARB)(GLuint, GLenum, GLuint64EXT *) = NULL;
void (*glGetVertexAttribPointerv)(GLuint, GLenum, void **) = NULL;
void (*glGetVertexAttribdv)(GLuint, GLenum, GLdouble *) = NULL;
void (*glGetVertexAttribfv)(GLuint, GLenum, GLfloat *) = NULL;
void (*glGetVertexAttribiv)(GLuint, GLenum, GLint *) = NULL;
void (*glGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *) = NULL;
void (*glGetnCompressedTexImageARB)(GLenum, GLint, GLsizei, void *) = NULL;
void (*glGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glGetnTexImageARB)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *) = NULL;
void (*glGetnUniformdvARB)(GLuint, GLint, GLsizei, GLdouble *) = NULL;
void (*glGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *) = NULL;
void (*glGetnUniformfvARB)(GLuint, GLint, GLsizei, GLfloat *) = NULL;
void (*glGetnUniformfvKHR)(GLuint, GLint, GLsizei, GLfloat *) = NULL;
void (*glGetnUniformiv)(GLuint, GLint, GLsizei, GLint *) = NULL;
void (*glGetnUniformivARB)(GLuint, GLint, GLsizei, GLint *) = NULL;
void (*glGetnUniformivKHR)(GLuint, GLint, GLsizei, GLint *) = NULL;
void (*glGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *) = NULL;
void (*glGetnUniformuivARB)(GLuint, GLint, GLsizei, GLuint *) = NULL;
void (*glGetnUniformuivKHR)(GLuint, GLint, GLsizei, GLuint *) = NULL;
void (*glHint)(GLenum, GLenum) = NULL;
void (*glInvalidateBufferData)(GLuint) = NULL;
void (*glInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr) = NULL;
void (*glInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *) = NULL;
void (*glInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *) = NULL;
void (*glInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glInvalidateTexImage)(GLuint, GLint) = NULL;
void (*glInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) = NULL;
GLboolean (*glIsBuffer)(GLuint) = NULL;
GLboolean (*glIsEnabled)(GLenum) = NULL;
GLboolean (*glIsEnabledIndexedEXT)(GLenum, GLuint) = NULL;
GLboolean (*glIsEnabledi)(GLenum, GLuint) = NULL;
GLboolean (*glIsFramebuffer)(GLuint) = NULL;
GLboolean (*glIsImageHandleResidentARB)(GLuint64) = NULL;
GLboolean (*glIsNamedStringARB)(GLint, const GLchar *) = NULL;
GLboolean (*glIsProgram)(GLuint) = NULL;
GLboolean (*glIsProgramPipeline)(GLuint) = NULL;
GLboolean (*glIsQuery)(GLuint) = NULL;
GLboolean (*glIsRenderbuffer)(GLuint) = NULL;
GLboolean (*glIsSampler)(GLuint) = NULL;
GLboolean (*glIsShader)(GLuint) = NULL;
GLboolean (*glIsSync)(GLsync) = NULL;
GLboolean (*glIsTexture)(GLuint) = NULL;
GLboolean (*glIsTextureHandleResidentARB)(GLuint64) = NULL;
GLboolean (*glIsTransformFeedback)(GLuint) = NULL;
GLboolean (*glIsVertexArray)(GLuint) = NULL;
void (*glLineWidth)(GLfloat) = NULL;
void (*glLinkProgram)(GLuint) = NULL;
void (*glLogicOp)(GLenum) = NULL;
void (*glMakeImageHandleNonResidentARB)(GLuint64) = NULL;
void (*glMakeImageHandleResidentARB)(GLuint64, GLenum) = NULL;
void (*glMakeTextureHandleNonResidentARB)(GLuint64) = NULL;
void (*glMakeTextureHandleResidentARB)(GLuint64) = NULL;
void * (*glMapBuffer)(GLenum, GLenum) = NULL;
void * (*glMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield) = NULL;
void * (*glMapNamedBuffer)(GLuint, GLenum) = NULL;
void * (*glMapNamedBufferEXT)(GLuint, GLenum) = NULL;
void * (*glMapNamedBufferRange)(GLuint, GLintptr, GLsizei, GLbitfield) = NULL;
void * (*glMapNamedBufferRangeEXT)(GLuint, GLintptr, GLsizeiptr, GLbitfield) = NULL;
void (*glMatrixFrustumEXT)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glMatrixLoadIdentityEXT)(GLenum) = NULL;
void (*glMatrixLoadTransposedEXT)(GLenum, const GLdouble *) = NULL;
void (*glMatrixLoadTransposefEXT)(GLenum, const GLfloat *) = NULL;
void (*glMatrixLoaddEXT)(GLenum, const GLdouble *) = NULL;
void (*glMatrixLoadfEXT)(GLenum, const GLfloat *) = NULL;
void (*glMatrixMultTransposedEXT)(GLenum, const GLdouble *) = NULL;
void (*glMatrixMultTransposefEXT)(GLenum, const GLfloat *) = NULL;
void (*glMatrixMultdEXT)(GLenum, const GLdouble *) = NULL;
void (*glMatrixMultfEXT)(GLenum, const GLfloat *) = NULL;
void (*glMatrixOrthoEXT)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glMatrixPopEXT)(GLenum) = NULL;
void (*glMatrixPushEXT)(GLenum) = NULL;
void (*glMatrixRotatedEXT)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glMatrixRotatefEXT)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glMatrixScaledEXT)(GLenum, GLdouble, GLdouble, GLdouble) = NULL;
void (*glMatrixScalefEXT)(GLenum, GLfloat, GLfloat, GLfloat) = NULL;
void (*glMatrixTranslatedEXT)(GLenum, GLdouble, GLdouble, GLdouble) = NULL;
void (*glMatrixTranslatefEXT)(GLenum, GLfloat, GLfloat, GLfloat) = NULL;
void (*glMemoryBarrier)(GLbitfield) = NULL;
void (*glMemoryBarrierByRegion)(GLbitfield) = NULL;
void (*glMinSampleShading)(GLfloat) = NULL;
void (*glMinSampleShadingARB)(GLfloat) = NULL;
void (*glMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei) = NULL;
void (*glMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei) = NULL;
void (*glMultiDrawArraysIndirectCountARB)(GLenum, GLintptr, GLintptr, GLsizei, GLsizei) = NULL;
void (*glMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei) = NULL;
void (*glMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *) = NULL;
void (*glMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei) = NULL;
void (*glMultiDrawElementsIndirectCountARB)(GLenum, GLenum, GLintptr, GLintptr, GLsizei, GLsizei) = NULL;
void (*glMultiTexBufferEXT)(GLenum, GLenum, GLenum, GLuint) = NULL;
void (*glMultiTexCoordPointerEXT)(GLenum, GLint, GLenum, GLsizei, const void *) = NULL;
void (*glMultiTexEnvfEXT)(GLenum, GLenum, GLenum, GLfloat) = NULL;
void (*glMultiTexEnvfvEXT)(GLenum, GLenum, GLenum, const GLfloat *) = NULL;
void (*glMultiTexEnviEXT)(GLenum, GLenum, GLenum, GLint) = NULL;
void (*glMultiTexEnvivEXT)(GLenum, GLenum, GLenum, const GLint *) = NULL;
void (*glMultiTexGendEXT)(GLenum, GLenum, GLenum, GLdouble) = NULL;
void (*glMultiTexGendvEXT)(GLenum, GLenum, GLenum, const GLdouble *) = NULL;
void (*glMultiTexGenfEXT)(GLenum, GLenum, GLenum, GLfloat) = NULL;
void (*glMultiTexGenfvEXT)(GLenum, GLenum, GLenum, const GLfloat *) = NULL;
void (*glMultiTexGeniEXT)(GLenum, GLenum, GLenum, GLint) = NULL;
void (*glMultiTexGenivEXT)(GLenum, GLenum, GLenum, const GLint *) = NULL;
void (*glMultiTexImage1DEXT)(GLenum, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glMultiTexImage2DEXT)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glMultiTexImage3DEXT)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glMultiTexParameterIivEXT)(GLenum, GLenum, GLenum, const GLint *) = NULL;
void (*glMultiTexParameterIuivEXT)(GLenum, GLenum, GLenum, const GLuint *) = NULL;
void (*glMultiTexParameterfEXT)(GLenum, GLenum, GLenum, GLfloat) = NULL;
void (*glMultiTexParameterfvEXT)(GLenum, GLenum, GLenum, const GLfloat *) = NULL;
void (*glMultiTexParameteriEXT)(GLenum, GLenum, GLenum, GLint) = NULL;
void (*glMultiTexParameterivEXT)(GLenum, GLenum, GLenum, const GLint *) = NULL;
void (*glMultiTexRenderbufferEXT)(GLenum, GLenum, GLuint) = NULL;
void (*glMultiTexSubImage1DEXT)(GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glMultiTexSubImage2DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glMultiTexSubImage3DEXT)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glNamedBufferData)(GLuint, GLsizei, const void *, GLenum) = NULL;
void (*glNamedBufferDataEXT)(GLuint, GLsizeiptr, const void *, GLenum) = NULL;
void (*glNamedBufferPageCommitmentARB)(GLuint, GLintptr, GLsizeiptr, GLboolean) = NULL;
void (*glNamedBufferPageCommitmentEXT)(GLuint, GLintptr, GLsizeiptr, GLboolean) = NULL;
void (*glNamedBufferStorage)(GLuint, GLsizei, const void *, GLbitfield) = NULL;
void (*glNamedBufferStorageEXT)(GLuint, GLsizeiptr, const void *, GLbitfield) = NULL;
void (*glNamedBufferSubData)(GLuint, GLintptr, GLsizei, const void *) = NULL;
void (*glNamedBufferSubDataEXT)(GLuint, GLintptr, GLsizeiptr, const void *) = NULL;
void (*glNamedCopyBufferSubDataEXT)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) = NULL;
void (*glNamedFramebufferDrawBuffer)(GLuint, GLenum) = NULL;
void (*glNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *) = NULL;
void (*glNamedFramebufferParameteri)(GLuint, GLenum, GLint) = NULL;
void (*glNamedFramebufferParameteriEXT)(GLuint, GLenum, GLint) = NULL;
void (*glNamedFramebufferReadBuffer)(GLuint, GLenum) = NULL;
void (*glNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint) = NULL;
void (*glNamedFramebufferRenderbufferEXT)(GLuint, GLenum, GLenum, GLuint) = NULL;
void (*glNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint) = NULL;
void (*glNamedFramebufferTexture1DEXT)(GLuint, GLenum, GLenum, GLuint, GLint) = NULL;
void (*glNamedFramebufferTexture2DEXT)(GLuint, GLenum, GLenum, GLuint, GLint) = NULL;
void (*glNamedFramebufferTexture3DEXT)(GLuint, GLenum, GLenum, GLuint, GLint, GLint) = NULL;
void (*glNamedFramebufferTextureEXT)(GLuint, GLenum, GLuint, GLint) = NULL;
void (*glNamedFramebufferTextureFaceEXT)(GLuint, GLenum, GLuint, GLint, GLenum) = NULL;
void (*glNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint) = NULL;
void (*glNamedFramebufferTextureLayerEXT)(GLuint, GLenum, GLuint, GLint, GLint) = NULL;
void (*glNamedProgramLocalParameter4dEXT)(GLuint, GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glNamedProgramLocalParameter4dvEXT)(GLuint, GLenum, GLuint, const GLdouble *) = NULL;
void (*glNamedProgramLocalParameter4fEXT)(GLuint, GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glNamedProgramLocalParameter4fvEXT)(GLuint, GLenum, GLuint, const GLfloat *) = NULL;
void (*glNamedProgramLocalParameterI4iEXT)(GLuint, GLenum, GLuint, GLint, GLint, GLint, GLint) = NULL;
void (*glNamedProgramLocalParameterI4ivEXT)(GLuint, GLenum, GLuint, const GLint *) = NULL;
void (*glNamedProgramLocalParameterI4uiEXT)(GLuint, GLenum, GLuint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glNamedProgramLocalParameterI4uivEXT)(GLuint, GLenum, GLuint, const GLuint *) = NULL;
void (*glNamedProgramLocalParameters4fvEXT)(GLuint, GLenum, GLuint, GLsizei, const GLfloat *) = NULL;
void (*glNamedProgramLocalParametersI4ivEXT)(GLuint, GLenum, GLuint, GLsizei, const GLint *) = NULL;
void (*glNamedProgramLocalParametersI4uivEXT)(GLuint, GLenum, GLuint, GLsizei, const GLuint *) = NULL;
void (*glNamedProgramStringEXT)(GLuint, GLenum, GLenum, GLsizei, const void *) = NULL;
void (*glNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei) = NULL;
void (*glNamedRenderbufferStorageEXT)(GLuint, GLenum, GLsizei, GLsizei) = NULL;
void (*glNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glNamedRenderbufferStorageMultisampleCoverageEXT)(GLuint, GLsizei, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glNamedRenderbufferStorageMultisampleEXT)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glNamedStringARB)(GLenum, GLint, const GLchar *, GLint, const GLchar *) = NULL;
void (*glObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *) = NULL;
void (*glObjectLabelKHR)(GLenum, GLuint, GLsizei, const GLchar *) = NULL;
void (*glObjectPtrLabel)(const void *, GLsizei, const GLchar *) = NULL;
void (*glObjectPtrLabelKHR)(const void *, GLsizei, const GLchar *) = NULL;
void (*glPatchParameterfv)(GLenum, const GLfloat *) = NULL;
void (*glPatchParameteri)(GLenum, GLint) = NULL;
void (*glPauseTransformFeedback)() = NULL;
void (*glPixelStoref)(GLenum, GLfloat) = NULL;
void (*glPixelStorei)(GLenum, GLint) = NULL;
void (*glPointParameterf)(GLenum, GLfloat) = NULL;
void (*glPointParameterfv)(GLenum, const GLfloat *) = NULL;
void (*glPointParameteri)(GLenum, GLint) = NULL;
void (*glPointParameteriv)(GLenum, const GLint *) = NULL;
void (*glPointSize)(GLfloat) = NULL;
void (*glPolygonMode)(GLenum, GLenum) = NULL;
void (*glPolygonOffset)(GLfloat, GLfloat) = NULL;
void (*glPopDebugGroup)() = NULL;
void (*glPopDebugGroupKHR)() = NULL;
void (*glPrimitiveRestartIndex)(GLuint) = NULL;
void (*glProgramBinary)(GLuint, GLenum, const void *, GLsizei) = NULL;
void (*glProgramParameteri)(GLuint, GLenum, GLint) = NULL;
void (*glProgramUniform1d)(GLuint, GLint, GLdouble) = NULL;
void (*glProgramUniform1dEXT)(GLuint, GLint, GLdouble) = NULL;
void (*glProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform1dvEXT)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform1f)(GLuint, GLint, GLfloat) = NULL;
void (*glProgramUniform1fEXT)(GLuint, GLint, GLfloat) = NULL;
void (*glProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform1fvEXT)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform1i)(GLuint, GLint, GLint) = NULL;
void (*glProgramUniform1iEXT)(GLuint, GLint, GLint) = NULL;
void (*glProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform1ivEXT)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform1ui)(GLuint, GLint, GLuint) = NULL;
void (*glProgramUniform1uiEXT)(GLuint, GLint, GLuint) = NULL;
void (*glProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform1uivEXT)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble) = NULL;
void (*glProgramUniform2dEXT)(GLuint, GLint, GLdouble, GLdouble) = NULL;
void (*glProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform2dvEXT)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat) = NULL;
void (*glProgramUniform2fEXT)(GLuint, GLint, GLfloat, GLfloat) = NULL;
void (*glProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform2fvEXT)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform2i)(GLuint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform2iEXT)(GLuint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform2ivEXT)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform2ui)(GLuint, GLint, GLuint, GLuint) = NULL;
void (*glProgramUniform2uiEXT)(GLuint, GLint, GLuint, GLuint) = NULL;
void (*glProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform2uivEXT)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble) = NULL;
void (*glProgramUniform3dEXT)(GLuint, GLint, GLdouble, GLdouble, GLdouble) = NULL;
void (*glProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform3dvEXT)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat) = NULL;
void (*glProgramUniform3fEXT)(GLuint, GLint, GLfloat, GLfloat, GLfloat) = NULL;
void (*glProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform3fvEXT)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform3iEXT)(GLuint, GLint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform3ivEXT)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint) = NULL;
void (*glProgramUniform3uiEXT)(GLuint, GLint, GLuint, GLuint, GLuint) = NULL;
void (*glProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform3uivEXT)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glProgramUniform4dEXT)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform4dvEXT)(GLuint, GLint, GLsizei, const GLdouble *) = NULL;
void (*glProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glProgramUniform4fEXT)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform4fvEXT)(GLuint, GLint, GLsizei, const GLfloat *) = NULL;
void (*glProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform4iEXT)(GLuint, GLint, GLint, GLint, GLint, GLint) = NULL;
void (*glProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform4ivEXT)(GLuint, GLint, GLsizei, const GLint *) = NULL;
void (*glProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glProgramUniform4uiEXT)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniform4uivEXT)(GLuint, GLint, GLsizei, const GLuint *) = NULL;
void (*glProgramUniformHandleui64ARB)(GLuint, GLint, GLuint64) = NULL;
void (*glProgramUniformHandleui64vARB)(GLuint, GLint, GLsizei, const GLuint64 *) = NULL;
void (*glProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix2fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2x3dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix2x3fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2x4dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix2x4fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3x2dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3x2fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3x4dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix3x4fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4x2dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4x2fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4x3dvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProgramUniformMatrix4x3fvEXT)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glProvokingVertex)(GLenum) = NULL;
void (*glPushClientAttribDefaultEXT)(GLbitfield) = NULL;
void (*glPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *) = NULL;
void (*glPushDebugGroupKHR)(GLenum, GLuint, GLsizei, const GLchar *) = NULL;
void (*glQueryCounter)(GLuint, GLenum) = NULL;
void (*glReadBuffer)(GLenum) = NULL;
void (*glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *) = NULL;
void (*glReadnPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glReadnPixelsARB)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glReadnPixelsKHR)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) = NULL;
void (*glReleaseShaderCompiler)() = NULL;
void (*glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei) = NULL;
void (*glRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glResumeTransformFeedback)() = NULL;
void (*glSampleCoverage)(GLfloat, GLboolean) = NULL;
void (*glSampleMaski)(GLuint, GLbitfield) = NULL;
void (*glSamplerParameterIiv)(GLuint, GLenum, const GLint *) = NULL;
void (*glSamplerParameterIuiv)(GLuint, GLenum, const GLuint *) = NULL;
void (*glSamplerParameterf)(GLuint, GLenum, GLfloat) = NULL;
void (*glSamplerParameterfv)(GLuint, GLenum, const GLfloat *) = NULL;
void (*glSamplerParameteri)(GLuint, GLenum, GLint) = NULL;
void (*glSamplerParameteriv)(GLuint, GLenum, const GLint *) = NULL;
void (*glScissor)(GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glScissorArrayv)(GLuint, GLsizei, const GLint *) = NULL;
void (*glScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glScissorIndexedv)(GLuint, const GLint *) = NULL;
void (*glShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei) = NULL;
void (*glShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *) = NULL;
void (*glShaderStorageBlockBinding)(GLuint, GLuint, GLuint) = NULL;
void (*glStencilFunc)(GLenum, GLint, GLuint) = NULL;
void (*glStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint) = NULL;
void (*glStencilMask)(GLuint) = NULL;
void (*glStencilMaskSeparate)(GLenum, GLuint) = NULL;
void (*glStencilOp)(GLenum, GLenum, GLenum) = NULL;
void (*glStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum) = NULL;
void (*glTexBuffer)(GLenum, GLenum, GLuint) = NULL;
void (*glTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) = NULL;
void (*glTexImage1D)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTexPageCommitmentARB)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTexParameterIiv)(GLenum, GLenum, const GLint *) = NULL;
void (*glTexParameterIuiv)(GLenum, GLenum, const GLuint *) = NULL;
void (*glTexParameterf)(GLenum, GLenum, GLfloat) = NULL;
void (*glTexParameterfv)(GLenum, GLenum, const GLfloat *) = NULL;
void (*glTexParameteri)(GLenum, GLenum, GLint) = NULL;
void (*glTexParameteriv)(GLenum, GLenum, const GLint *) = NULL;
void (*glTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei) = NULL;
void (*glTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = NULL;
void (*glTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureBarrier)() = NULL;
void (*glTextureBuffer)(GLuint, GLenum, GLuint) = NULL;
void (*glTextureBufferEXT)(GLuint, GLenum, GLenum, GLuint) = NULL;
void (*glTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizei) = NULL;
void (*glTextureBufferRangeEXT)(GLuint, GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) = NULL;
void (*glTextureImage1DEXT)(GLuint, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTextureImage2DEXT)(GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTextureImage3DEXT)(GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) = NULL;
void (*glTexturePageCommitmentEXT)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTextureParameterIiv)(GLuint, GLenum, const GLint *) = NULL;
void (*glTextureParameterIivEXT)(GLuint, GLenum, GLenum, const GLint *) = NULL;
void (*glTextureParameterIuiv)(GLuint, GLenum, const GLuint *) = NULL;
void (*glTextureParameterIuivEXT)(GLuint, GLenum, GLenum, const GLuint *) = NULL;
void (*glTextureParameterf)(GLuint, GLenum, GLfloat) = NULL;
void (*glTextureParameterfEXT)(GLuint, GLenum, GLenum, GLfloat) = NULL;
void (*glTextureParameterfv)(GLuint, GLenum, const GLfloat *) = NULL;
void (*glTextureParameterfvEXT)(GLuint, GLenum, GLenum, const GLfloat *) = NULL;
void (*glTextureParameteri)(GLuint, GLenum, GLint) = NULL;
void (*glTextureParameteriEXT)(GLuint, GLenum, GLenum, GLint) = NULL;
void (*glTextureParameteriv)(GLuint, GLenum, const GLint *) = NULL;
void (*glTextureParameterivEXT)(GLuint, GLenum, GLenum, const GLint *) = NULL;
void (*glTextureRenderbufferEXT)(GLuint, GLenum, GLuint) = NULL;
void (*glTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei) = NULL;
void (*glTextureStorage1DEXT)(GLuint, GLenum, GLsizei, GLenum, GLsizei) = NULL;
void (*glTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glTextureStorage2DEXT)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei) = NULL;
void (*glTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTextureStorage2DMultisampleEXT)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = NULL;
void (*glTextureStorage3DEXT)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) = NULL;
void (*glTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTextureStorage3DMultisampleEXT)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) = NULL;
void (*glTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureSubImage1DEXT)(GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureSubImage2DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureSubImage3DEXT)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) = NULL;
void (*glTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glTransformFeedbackBufferBase)(GLuint, GLuint, GLuint) = NULL;
void (*glTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizei) = NULL;
void (*glTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum) = NULL;
void (*glUniform1d)(GLint, GLdouble) = NULL;
void (*glUniform1dv)(GLint, GLsizei, const GLdouble *) = NULL;
void (*glUniform1f)(GLint, GLfloat) = NULL;
void (*glUniform1fv)(GLint, GLsizei, const GLfloat *) = NULL;
void (*glUniform1i)(GLint, GLint) = NULL;
void (*glUniform1iv)(GLint, GLsizei, const GLint *) = NULL;
void (*glUniform1ui)(GLint, GLuint) = NULL;
void (*glUniform1uiv)(GLint, GLsizei, const GLuint *) = NULL;
void (*glUniform2d)(GLint, GLdouble, GLdouble) = NULL;
void (*glUniform2dv)(GLint, GLsizei, const GLdouble *) = NULL;
void (*glUniform2f)(GLint, GLfloat, GLfloat) = NULL;
void (*glUniform2fv)(GLint, GLsizei, const GLfloat *) = NULL;
void (*glUniform2i)(GLint, GLint, GLint) = NULL;
void (*glUniform2iv)(GLint, GLsizei, const GLint *) = NULL;
void (*glUniform2ui)(GLint, GLuint, GLuint) = NULL;
void (*glUniform2uiv)(GLint, GLsizei, const GLuint *) = NULL;
void (*glUniform3d)(GLint, GLdouble, GLdouble, GLdouble) = NULL;
void (*glUniform3dv)(GLint, GLsizei, const GLdouble *) = NULL;
void (*glUniform3f)(GLint, GLfloat, GLfloat, GLfloat) = NULL;
void (*glUniform3fv)(GLint, GLsizei, const GLfloat *) = NULL;
void (*glUniform3i)(GLint, GLint, GLint, GLint) = NULL;
void (*glUniform3iv)(GLint, GLsizei, const GLint *) = NULL;
void (*glUniform3ui)(GLint, GLuint, GLuint, GLuint) = NULL;
void (*glUniform3uiv)(GLint, GLsizei, const GLuint *) = NULL;
void (*glUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glUniform4dv)(GLint, GLsizei, const GLdouble *) = NULL;
void (*glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glUniform4fv)(GLint, GLsizei, const GLfloat *) = NULL;
void (*glUniform4i)(GLint, GLint, GLint, GLint, GLint) = NULL;
void (*glUniform4iv)(GLint, GLsizei, const GLint *) = NULL;
void (*glUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glUniform4uiv)(GLint, GLsizei, const GLuint *) = NULL;
void (*glUniformBlockBinding)(GLuint, GLuint, GLuint) = NULL;
void (*glUniformHandleui64ARB)(GLint, GLuint64) = NULL;
void (*glUniformHandleui64vARB)(GLint, GLsizei, const GLuint64 *) = NULL;
void (*glUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *) = NULL;
void (*glUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *) = NULL;
void (*glUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *) = NULL;
GLboolean (*glUnmapBuffer)(GLenum) = NULL;
GLboolean (*glUnmapNamedBuffer)(GLuint) = NULL;
GLboolean (*glUnmapNamedBufferEXT)(GLuint) = NULL;
void (*glUseProgram)(GLuint) = NULL;
void (*glUseProgramStages)(GLuint, GLbitfield, GLuint) = NULL;
void (*glValidateProgram)(GLuint) = NULL;
void (*glValidateProgramPipeline)(GLuint) = NULL;
void (*glVertexArrayAttribBinding)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexArrayBindVertexBufferEXT)(GLuint, GLuint, GLuint, GLintptr, GLsizei) = NULL;
void (*glVertexArrayBindingDivisor)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexArrayColorOffsetEXT)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayEdgeFlagOffsetEXT)(GLuint, GLuint, GLsizei, GLintptr) = NULL;
void (*glVertexArrayElementBuffer)(GLuint, GLuint) = NULL;
void (*glVertexArrayFogCoordOffsetEXT)(GLuint, GLuint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayIndexOffsetEXT)(GLuint, GLuint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayMultiTexCoordOffsetEXT)(GLuint, GLuint, GLenum, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayNormalOffsetEXT)(GLuint, GLuint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArraySecondaryColorOffsetEXT)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayTexCoordOffsetEXT)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayVertexAttribBindingEXT)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexArrayVertexAttribDivisorEXT)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexArrayVertexAttribFormatEXT)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexArrayVertexAttribIFormatEXT)(GLuint, GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexArrayVertexAttribIOffsetEXT)(GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayVertexAttribLFormatEXT)(GLuint, GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexArrayVertexAttribLOffsetEXT)(GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexArrayVertexAttribOffsetEXT)(GLuint, GLuint, GLuint, GLint, GLenum, GLboolean, GLsizei, GLintptr) = NULL;
void (*glVertexArrayVertexBindingDivisorEXT)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei) = NULL;
void (*glVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) = NULL;
void (*glVertexArrayVertexOffsetEXT)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) = NULL;
void (*glVertexAttrib1d)(GLuint, GLdouble) = NULL;
void (*glVertexAttrib1dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttrib1f)(GLuint, GLfloat) = NULL;
void (*glVertexAttrib1fv)(GLuint, const GLfloat *) = NULL;
void (*glVertexAttrib1s)(GLuint, GLshort) = NULL;
void (*glVertexAttrib1sv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttrib2d)(GLuint, GLdouble, GLdouble) = NULL;
void (*glVertexAttrib2dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttrib2f)(GLuint, GLfloat, GLfloat) = NULL;
void (*glVertexAttrib2fv)(GLuint, const GLfloat *) = NULL;
void (*glVertexAttrib2s)(GLuint, GLshort, GLshort) = NULL;
void (*glVertexAttrib2sv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble) = NULL;
void (*glVertexAttrib3dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat) = NULL;
void (*glVertexAttrib3fv)(GLuint, const GLfloat *) = NULL;
void (*glVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort) = NULL;
void (*glVertexAttrib3sv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttrib4Nbv)(GLuint, const GLbyte *) = NULL;
void (*glVertexAttrib4Niv)(GLuint, const GLint *) = NULL;
void (*glVertexAttrib4Nsv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte) = NULL;
void (*glVertexAttrib4Nubv)(GLuint, const GLubyte *) = NULL;
void (*glVertexAttrib4Nuiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttrib4Nusv)(GLuint, const GLushort *) = NULL;
void (*glVertexAttrib4bv)(GLuint, const GLbyte *) = NULL;
void (*glVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glVertexAttrib4dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glVertexAttrib4fv)(GLuint, const GLfloat *) = NULL;
void (*glVertexAttrib4iv)(GLuint, const GLint *) = NULL;
void (*glVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort) = NULL;
void (*glVertexAttrib4sv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttrib4ubv)(GLuint, const GLubyte *) = NULL;
void (*glVertexAttrib4uiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttrib4usv)(GLuint, const GLushort *) = NULL;
void (*glVertexAttribBinding)(GLuint, GLuint) = NULL;
void (*glVertexAttribDivisor)(GLuint, GLuint) = NULL;
void (*glVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexAttribI1i)(GLuint, GLint) = NULL;
void (*glVertexAttribI1iv)(GLuint, const GLint *) = NULL;
void (*glVertexAttribI1ui)(GLuint, GLuint) = NULL;
void (*glVertexAttribI1uiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttribI2i)(GLuint, GLint, GLint) = NULL;
void (*glVertexAttribI2iv)(GLuint, const GLint *) = NULL;
void (*glVertexAttribI2ui)(GLuint, GLuint, GLuint) = NULL;
void (*glVertexAttribI2uiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttribI3i)(GLuint, GLint, GLint, GLint) = NULL;
void (*glVertexAttribI3iv)(GLuint, const GLint *) = NULL;
void (*glVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glVertexAttribI3uiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttribI4bv)(GLuint, const GLbyte *) = NULL;
void (*glVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint) = NULL;
void (*glVertexAttribI4iv)(GLuint, const GLint *) = NULL;
void (*glVertexAttribI4sv)(GLuint, const GLshort *) = NULL;
void (*glVertexAttribI4ubv)(GLuint, const GLubyte *) = NULL;
void (*glVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint) = NULL;
void (*glVertexAttribI4uiv)(GLuint, const GLuint *) = NULL;
void (*glVertexAttribI4usv)(GLuint, const GLushort *) = NULL;
void (*glVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = NULL;
void (*glVertexAttribL1d)(GLuint, GLdouble) = NULL;
void (*glVertexAttribL1dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttribL1ui64ARB)(GLuint, GLuint64EXT) = NULL;
void (*glVertexAttribL1ui64vARB)(GLuint, const GLuint64EXT *) = NULL;
void (*glVertexAttribL2d)(GLuint, GLdouble, GLdouble) = NULL;
void (*glVertexAttribL2dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble) = NULL;
void (*glVertexAttribL3dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) = NULL;
void (*glVertexAttribL4dv)(GLuint, const GLdouble *) = NULL;
void (*glVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint) = NULL;
void (*glVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *) = NULL;
void (*glVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *) = NULL;
void (*glVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *) = NULL;
void (*glVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *) = NULL;
void (*glVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint) = NULL;
void (*glVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *) = NULL;
void (*glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *) = NULL;
void (*glVertexBindingDivisor)(GLuint, GLuint) = NULL;
void (*glViewport)(GLint, GLint, GLsizei, GLsizei) = NULL;
void (*glViewportArrayv)(GLuint, GLsizei, const GLfloat *) = NULL;
void (*glViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) = NULL;
void (*glViewportIndexedfv)(GLuint, const GLfloat *) = NULL;
void (*glWaitSync)(GLsync, GLbitfield, GLuint64) = NULL;

bool GLPLATFORM_GL_ARB_ES2_compatibility = false;
bool GLPLATFORM_GL_ARB_ES3_1_compatibility = false;
bool GLPLATFORM_GL_ARB_ES3_compatibility = false;
bool GLPLATFORM_GL_ARB_arrays_of_arrays = false;
bool GLPLATFORM_GL_ARB_base_instance = false;
bool GLPLATFORM_GL_ARB_bindless_texture = false;
bool GLPLATFORM_GL_ARB_blend_func_extended = false;
bool GLPLATFORM_GL_ARB_buffer_storage = false;
bool GLPLATFORM_GL_ARB_cl_event = false;
bool GLPLATFORM_GL_ARB_clear_buffer_object = false;
bool GLPLATFORM_GL_ARB_clear_texture = false;
bool GLPLATFORM_GL_ARB_clip_control = false;
bool GLPLATFORM_GL_ARB_compressed_texture_pixel_storage = false;
bool GLPLATFORM_GL_ARB_compute_shader = false;
bool GLPLATFORM_GL_ARB_compute_variable_group_size = false;
bool GLPLATFORM_GL_ARB_conditional_render_inverted = false;
bool GLPLATFORM_GL_ARB_conservative_depth = false;
bool GLPLATFORM_GL_ARB_copy_buffer = false;
bool GLPLATFORM_GL_ARB_copy_image = false;
bool GLPLATFORM_GL_ARB_cull_distance = false;
bool GLPLATFORM_GL_ARB_debug_output = false;
bool GLPLATFORM_GL_ARB_depth_buffer_float = false;
bool GLPLATFORM_GL_ARB_depth_clamp = false;
bool GLPLATFORM_GL_ARB_derivative_control = false;
bool GLPLATFORM_GL_ARB_direct_state_access = false;
bool GLPLATFORM_GL_ARB_draw_buffers_blend = false;
bool GLPLATFORM_GL_ARB_draw_elements_base_vertex = false;
bool GLPLATFORM_GL_ARB_draw_indirect = false;
bool GLPLATFORM_GL_ARB_enhanced_layouts = false;
bool GLPLATFORM_GL_ARB_explicit_attrib_location = false;
bool GLPLATFORM_GL_ARB_explicit_uniform_location = false;
bool GLPLATFORM_GL_ARB_fragment_coord_conventions = false;
bool GLPLATFORM_GL_ARB_fragment_layer_viewport = false;
bool GLPLATFORM_GL_ARB_framebuffer_no_attachments = false;
bool GLPLATFORM_GL_ARB_framebuffer_object = false;
bool GLPLATFORM_GL_ARB_framebuffer_sRGB = false;
bool GLPLATFORM_GL_ARB_get_program_binary = false;
bool GLPLATFORM_GL_ARB_get_texture_sub_image = false;
bool GLPLATFORM_GL_ARB_gpu_shader5 = false;
bool GLPLATFORM_GL_ARB_gpu_shader_fp64 = false;
bool GLPLATFORM_GL_ARB_half_float_vertex = false;
bool GLPLATFORM_GL_ARB_imaging = false;
bool GLPLATFORM_GL_ARB_indirect_parameters = false;
bool GLPLATFORM_GL_ARB_internalformat_query = false;
bool GLPLATFORM_GL_ARB_internalformat_query2 = false;
bool GLPLATFORM_GL_ARB_invalidate_subdata = false;
bool GLPLATFORM_GL_ARB_map_buffer_alignment = false;
bool GLPLATFORM_GL_ARB_map_buffer_range = false;
bool GLPLATFORM_GL_ARB_multi_bind = false;
bool GLPLATFORM_GL_ARB_multi_draw_indirect = false;
bool GLPLATFORM_GL_ARB_occlusion_query2 = false;
bool GLPLATFORM_GL_ARB_pipeline_statistics_query = false;
bool GLPLATFORM_GL_ARB_program_interface_query = false;
bool GLPLATFORM_GL_ARB_provoking_vertex = false;
bool GLPLATFORM_GL_ARB_query_buffer_object = false;
bool GLPLATFORM_GL_ARB_robust_buffer_access_behavior = false;
bool GLPLATFORM_GL_ARB_robustness = false;
bool GLPLATFORM_GL_ARB_robustness_isolation = false;
bool GLPLATFORM_GL_ARB_sample_shading = false;
bool GLPLATFORM_GL_ARB_sampler_objects = false;
bool GLPLATFORM_GL_ARB_seamless_cube_map = false;
bool GLPLATFORM_GL_ARB_seamless_cubemap_per_texture = false;
bool GLPLATFORM_GL_ARB_separate_shader_objects = false;
bool GLPLATFORM_GL_ARB_shader_atomic_counters = false;
bool GLPLATFORM_GL_ARB_shader_bit_encoding = false;
bool GLPLATFORM_GL_ARB_shader_draw_parameters = false;
bool GLPLATFORM_GL_ARB_shader_group_vote = false;
bool GLPLATFORM_GL_ARB_shader_image_load_store = false;
bool GLPLATFORM_GL_ARB_shader_image_size = false;
bool GLPLATFORM_GL_ARB_shader_precision = false;
bool GLPLATFORM_GL_ARB_shader_stencil_export = false;
bool GLPLATFORM_GL_ARB_shader_storage_buffer_object = false;
bool GLPLATFORM_GL_ARB_shader_subroutine = false;
bool GLPLATFORM_GL_ARB_shader_texture_image_samples = false;
bool GLPLATFORM_GL_ARB_shading_language_420pack = false;
bool GLPLATFORM_GL_ARB_shading_language_include = false;
bool GLPLATFORM_GL_ARB_shading_language_packing = false;
bool GLPLATFORM_GL_ARB_sparse_buffer = false;
bool GLPLATFORM_GL_ARB_sparse_texture = false;
bool GLPLATFORM_GL_ARB_stencil_texturing = false;
bool GLPLATFORM_GL_ARB_sync = false;
bool GLPLATFORM_GL_ARB_tessellation_shader = false;
bool GLPLATFORM_GL_ARB_texture_barrier = false;
bool GLPLATFORM_GL_ARB_texture_buffer_object_rgb32 = false;
bool GLPLATFORM_GL_ARB_texture_buffer_range = false;
bool GLPLATFORM_GL_ARB_texture_compression_bptc = false;
bool GLPLATFORM_GL_ARB_texture_compression_rgtc = false;
bool GLPLATFORM_GL_ARB_texture_cube_map_array = false;
bool GLPLATFORM_GL_ARB_texture_gather = false;
bool GLPLATFORM_GL_ARB_texture_mirror_clamp_to_edge = false;
bool GLPLATFORM_GL_ARB_texture_multisample = false;
bool GLPLATFORM_GL_ARB_texture_query_levels = false;
bool GLPLATFORM_GL_ARB_texture_query_lod = false;
bool GLPLATFORM_GL_ARB_texture_rg = false;
bool GLPLATFORM_GL_ARB_texture_rgb10_a2ui = false;
bool GLPLATFORM_GL_ARB_texture_stencil8 = false;
bool GLPLATFORM_GL_ARB_texture_storage = false;
bool GLPLATFORM_GL_ARB_texture_storage_multisample = false;
bool GLPLATFORM_GL_ARB_texture_swizzle = false;
bool GLPLATFORM_GL_ARB_texture_view = false;
bool GLPLATFORM_GL_ARB_timer_query = false;
bool GLPLATFORM_GL_ARB_transform_feedback2 = false;
bool GLPLATFORM_GL_ARB_transform_feedback3 = false;
bool GLPLATFORM_GL_ARB_transform_feedback_instanced = false;
bool GLPLATFORM_GL_ARB_transform_feedback_overflow_query = false;
bool GLPLATFORM_GL_ARB_uniform_buffer_object = false;
bool GLPLATFORM_GL_ARB_vertex_array_bgra = false;
bool GLPLATFORM_GL_ARB_vertex_array_object = false;
bool GLPLATFORM_GL_ARB_vertex_attrib_64bit = false;
bool GLPLATFORM_GL_ARB_vertex_attrib_binding = false;
bool GLPLATFORM_GL_ARB_vertex_type_10f_11f_11f_rev = false;
bool GLPLATFORM_GL_ARB_vertex_type_2_10_10_10_rev = false;
bool GLPLATFORM_GL_ARB_viewport_array = false;
bool GLPLATFORM_GL_EXT_direct_state_access = false;
bool GLPLATFORM_GL_KHR_context_flush_control = false;
bool GLPLATFORM_GL_KHR_debug = false;
bool GLPLATFORM_GL_KHR_robust_buffer_access_behavior = false;
bool GLPLATFORM_GL_KHR_robustness = false;
bool GLPLATFORM_GL_KHR_texture_compression_astc_hdr = false;
bool GLPLATFORM_GL_KHR_texture_compression_astc_ldr = false;

bool glplatform_glcore_init(int maj, int min)
{
	int req_version = maj * 10 + min;
	int actual_maj, actual_min, actual_version, i;
	int num_extensions;
	if (req_version < 32) return false;
	if (req_version > 45) return false;
	glActiveShaderProgram = (void (*)(GLuint, GLuint) ) LoadProcAddress("glActiveShaderProgram");
	glActiveTexture = (void (*)(GLenum) ) LoadProcAddress("glActiveTexture");
	glAttachShader = (void (*)(GLuint, GLuint) ) LoadProcAddress("glAttachShader");
	glBeginConditionalRender = (void (*)(GLuint, GLenum) ) LoadProcAddress("glBeginConditionalRender");
	glBeginQuery = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBeginQuery");
	glBeginQueryIndexed = (void (*)(GLenum, GLuint, GLuint) ) LoadProcAddress("glBeginQueryIndexed");
	glBeginTransformFeedback = (void (*)(GLenum) ) LoadProcAddress("glBeginTransformFeedback");
	glBindAttribLocation = (void (*)(GLuint, GLuint, const GLchar *) ) LoadProcAddress("glBindAttribLocation");
	glBindBuffer = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBindBuffer");
	glBindBufferBase = (void (*)(GLenum, GLuint, GLuint) ) LoadProcAddress("glBindBufferBase");
	glBindBufferRange = (void (*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr) ) LoadProcAddress("glBindBufferRange");
	glBindBuffersBase = (void (*)(GLenum, GLuint, GLsizei, const GLuint *) ) LoadProcAddress("glBindBuffersBase");
	glBindBuffersRange = (void (*)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *) ) LoadProcAddress("glBindBuffersRange");
	glBindFragDataLocation = (void (*)(GLuint, GLuint, const GLchar *) ) LoadProcAddress("glBindFragDataLocation");
	glBindFragDataLocationIndexed = (void (*)(GLuint, GLuint, GLuint, const GLchar *) ) LoadProcAddress("glBindFragDataLocationIndexed");
	glBindFramebuffer = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBindFramebuffer");
	glBindImageTexture = (void (*)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum) ) LoadProcAddress("glBindImageTexture");
	glBindImageTextures = (void (*)(GLuint, GLsizei, const GLuint *) ) LoadProcAddress("glBindImageTextures");
	glBindMultiTextureEXT = (void (*)(GLenum, GLenum, GLuint) ) LoadProcAddress("glBindMultiTextureEXT");
	glBindProgramPipeline = (void (*)(GLuint) ) LoadProcAddress("glBindProgramPipeline");
	glBindRenderbuffer = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBindRenderbuffer");
	glBindSampler = (void (*)(GLuint, GLuint) ) LoadProcAddress("glBindSampler");
	glBindSamplers = (void (*)(GLuint, GLsizei, const GLuint *) ) LoadProcAddress("glBindSamplers");
	glBindTexture = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBindTexture");
	glBindTextureUnit = (void (*)(GLuint, GLuint) ) LoadProcAddress("glBindTextureUnit");
	glBindTextures = (void (*)(GLuint, GLsizei, const GLuint *) ) LoadProcAddress("glBindTextures");
	glBindTransformFeedback = (void (*)(GLenum, GLuint) ) LoadProcAddress("glBindTransformFeedback");
	glBindVertexArray = (void (*)(GLuint) ) LoadProcAddress("glBindVertexArray");
	glBindVertexBuffer = (void (*)(GLuint, GLuint, GLintptr, GLsizei) ) LoadProcAddress("glBindVertexBuffer");
	glBindVertexBuffers = (void (*)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) ) LoadProcAddress("glBindVertexBuffers");
	glBlendColor = (void (*)(GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glBlendColor");
	glBlendEquation = (void (*)(GLenum) ) LoadProcAddress("glBlendEquation");
	glBlendEquationSeparate = (void (*)(GLenum, GLenum) ) LoadProcAddress("glBlendEquationSeparate");
	glBlendEquationSeparatei = (void (*)(GLuint, GLenum, GLenum) ) LoadProcAddress("glBlendEquationSeparatei");
	glBlendEquationSeparateiARB = (void (*)(GLuint, GLenum, GLenum) ) LoadProcAddress("glBlendEquationSeparateiARB");
	glBlendEquationi = (void (*)(GLuint, GLenum) ) LoadProcAddress("glBlendEquationi");
	glBlendEquationiARB = (void (*)(GLuint, GLenum) ) LoadProcAddress("glBlendEquationiARB");
	glBlendFunc = (void (*)(GLenum, GLenum) ) LoadProcAddress("glBlendFunc");
	glBlendFuncSeparate = (void (*)(GLenum, GLenum, GLenum, GLenum) ) LoadProcAddress("glBlendFuncSeparate");
	glBlendFuncSeparatei = (void (*)(GLuint, GLenum, GLenum, GLenum, GLenum) ) LoadProcAddress("glBlendFuncSeparatei");
	glBlendFuncSeparateiARB = (void (*)(GLuint, GLenum, GLenum, GLenum, GLenum) ) LoadProcAddress("glBlendFuncSeparateiARB");
	glBlendFunci = (void (*)(GLuint, GLenum, GLenum) ) LoadProcAddress("glBlendFunci");
	glBlendFunciARB = (void (*)(GLuint, GLenum, GLenum) ) LoadProcAddress("glBlendFunciARB");
	glBlitFramebuffer = (void (*)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) ) LoadProcAddress("glBlitFramebuffer");
	glBlitNamedFramebuffer = (void (*)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum) ) LoadProcAddress("glBlitNamedFramebuffer");
	glBufferData = (void (*)(GLenum, GLsizeiptr, const void *, GLenum) ) LoadProcAddress("glBufferData");
	glBufferPageCommitmentARB = (void (*)(GLenum, GLintptr, GLsizeiptr, GLboolean) ) LoadProcAddress("glBufferPageCommitmentARB");
	glBufferStorage = (void (*)(GLenum, GLsizeiptr, const void *, GLbitfield) ) LoadProcAddress("glBufferStorage");
	glBufferSubData = (void (*)(GLenum, GLintptr, GLsizeiptr, const void *) ) LoadProcAddress("glBufferSubData");
	glCheckFramebufferStatus = (GLenum (*)(GLenum) ) LoadProcAddress("glCheckFramebufferStatus");
	glCheckNamedFramebufferStatus = (GLenum (*)(GLuint, GLenum) ) LoadProcAddress("glCheckNamedFramebufferStatus");
	glCheckNamedFramebufferStatusEXT = (GLenum (*)(GLuint, GLenum) ) LoadProcAddress("glCheckNamedFramebufferStatusEXT");
	glClampColor = (void (*)(GLenum, GLenum) ) LoadProcAddress("glClampColor");
	glClear = (void (*)(GLbitfield) ) LoadProcAddress("glClear");
	glClearBufferData = (void (*)(GLenum, GLenum, GLenum, GLenum, const void *) ) LoadProcAddress("glClearBufferData");
	glClearBufferSubData = (void (*)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *) ) LoadProcAddress("glClearBufferSubData");
	glClearBufferfi = (void (*)(GLenum, GLint, GLfloat, GLint) ) LoadProcAddress("glClearBufferfi");
	glClearBufferfv = (void (*)(GLenum, GLint, const GLfloat *) ) LoadProcAddress("glClearBufferfv");
	glClearBufferiv = (void (*)(GLenum, GLint, const GLint *) ) LoadProcAddress("glClearBufferiv");
	glClearBufferuiv = (void (*)(GLenum, GLint, const GLuint *) ) LoadProcAddress("glClearBufferuiv");
	glClearColor = (void (*)(GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glClearColor");
	glClearDepth = (void (*)(GLdouble) ) LoadProcAddress("glClearDepth");
	glClearDepthf = (void (*)(GLfloat) ) LoadProcAddress("glClearDepthf");
	glClearNamedBufferData = (void (*)(GLuint, GLenum, GLenum, GLenum, const void *) ) LoadProcAddress("glClearNamedBufferData");
	glClearNamedBufferDataEXT = (void (*)(GLuint, GLenum, GLenum, GLenum, const void *) ) LoadProcAddress("glClearNamedBufferDataEXT");
	glClearNamedBufferSubData = (void (*)(GLuint, GLenum, GLintptr, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glClearNamedBufferSubData");
	glClearNamedBufferSubDataEXT = (void (*)(GLuint, GLenum, GLsizeiptr, GLsizeiptr, GLenum, GLenum, const void *) ) LoadProcAddress("glClearNamedBufferSubDataEXT");
	glClearNamedFramebufferfi = (void (*)(GLuint, GLenum, const GLfloat, GLint) ) LoadProcAddress("glClearNamedFramebufferfi");
	glClearNamedFramebufferfv = (void (*)(GLuint, GLenum, GLint, const GLfloat *) ) LoadProcAddress("glClearNamedFramebufferfv");
	glClearNamedFramebufferiv = (void (*)(GLuint, GLenum, GLint, const GLint *) ) LoadProcAddress("glClearNamedFramebufferiv");
	glClearNamedFramebufferuiv = (void (*)(GLuint, GLenum, GLint, const GLuint *) ) LoadProcAddress("glClearNamedFramebufferuiv");
	glClearStencil = (void (*)(GLint) ) LoadProcAddress("glClearStencil");
	glClearTexImage = (void (*)(GLuint, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glClearTexImage");
	glClearTexSubImage = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glClearTexSubImage");
	glClientAttribDefaultEXT = (void (*)(GLbitfield) ) LoadProcAddress("glClientAttribDefaultEXT");
	glClientWaitSync = (GLenum (*)(GLsync, GLbitfield, GLuint64) ) LoadProcAddress("glClientWaitSync");
	glClipControl = (void (*)(GLenum, GLenum) ) LoadProcAddress("glClipControl");
	glColorMask = (void (*)(GLboolean, GLboolean, GLboolean, GLboolean) ) LoadProcAddress("glColorMask");
	glColorMaski = (void (*)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean) ) LoadProcAddress("glColorMaski");
	glCompileShader = (void (*)(GLuint) ) LoadProcAddress("glCompileShader");
	glCompileShaderIncludeARB = (void (*)(GLuint, GLsizei, const GLchar *const*, const GLint *) ) LoadProcAddress("glCompileShaderIncludeARB");
	glCompressedMultiTexImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexImage1DEXT");
	glCompressedMultiTexImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexImage2DEXT");
	glCompressedMultiTexImage3DEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexImage3DEXT");
	glCompressedMultiTexSubImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexSubImage1DEXT");
	glCompressedMultiTexSubImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexSubImage2DEXT");
	glCompressedMultiTexSubImage3DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedMultiTexSubImage3DEXT");
	glCompressedTexImage1D = (void (*)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTexImage1D");
	glCompressedTexImage2D = (void (*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTexImage2D");
	glCompressedTexImage3D = (void (*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTexImage3D");
	glCompressedTexSubImage1D = (void (*)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTexSubImage1D");
	glCompressedTexSubImage2D = (void (*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTexSubImage2D");
	glCompressedTexSubImage3D = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTexSubImage3D");
	glCompressedTextureImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureImage1DEXT");
	glCompressedTextureImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureImage2DEXT");
	glCompressedTextureImage3DEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureImage3DEXT");
	glCompressedTextureSubImage1D = (void (*)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage1D");
	glCompressedTextureSubImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage1DEXT");
	glCompressedTextureSubImage2D = (void (*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage2D");
	glCompressedTextureSubImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage2DEXT");
	glCompressedTextureSubImage3D = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage3D");
	glCompressedTextureSubImage3DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *) ) LoadProcAddress("glCompressedTextureSubImage3DEXT");
	glCopyBufferSubData = (void (*)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr) ) LoadProcAddress("glCopyBufferSubData");
	glCopyImageSubData = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glCopyImageSubData");
	glCopyMultiTexImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) ) LoadProcAddress("glCopyMultiTexImage1DEXT");
	glCopyMultiTexImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) ) LoadProcAddress("glCopyMultiTexImage2DEXT");
	glCopyMultiTexSubImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei) ) LoadProcAddress("glCopyMultiTexSubImage1DEXT");
	glCopyMultiTexSubImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyMultiTexSubImage2DEXT");
	glCopyMultiTexSubImage3DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyMultiTexSubImage3DEXT");
	glCopyNamedBufferSubData = (void (*)(GLuint, GLuint, GLintptr, GLintptr, GLsizei) ) LoadProcAddress("glCopyNamedBufferSubData");
	glCopyTexImage1D = (void (*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) ) LoadProcAddress("glCopyTexImage1D");
	glCopyTexImage2D = (void (*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) ) LoadProcAddress("glCopyTexImage2D");
	glCopyTexSubImage1D = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLsizei) ) LoadProcAddress("glCopyTexSubImage1D");
	glCopyTexSubImage2D = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTexSubImage2D");
	glCopyTexSubImage3D = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTexSubImage3D");
	glCopyTextureImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint) ) LoadProcAddress("glCopyTextureImage1DEXT");
	glCopyTextureImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint) ) LoadProcAddress("glCopyTextureImage2DEXT");
	glCopyTextureSubImage1D = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei) ) LoadProcAddress("glCopyTextureSubImage1D");
	glCopyTextureSubImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei) ) LoadProcAddress("glCopyTextureSubImage1DEXT");
	glCopyTextureSubImage2D = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTextureSubImage2D");
	glCopyTextureSubImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTextureSubImage2DEXT");
	glCopyTextureSubImage3D = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTextureSubImage3D");
	glCopyTextureSubImage3DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glCopyTextureSubImage3DEXT");
	glCreateBuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateBuffers");
	glCreateFramebuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateFramebuffers");
	glCreateProgram = (GLuint (*)() ) LoadProcAddress("glCreateProgram");
	glCreateProgramPipelines = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateProgramPipelines");
	glCreateQueries = (void (*)(GLenum, GLsizei, GLuint *) ) LoadProcAddress("glCreateQueries");
	glCreateRenderbuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateRenderbuffers");
	glCreateSamplers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateSamplers");
	glCreateShader = (GLuint (*)(GLenum) ) LoadProcAddress("glCreateShader");
	glCreateShaderProgramv = (GLuint (*)(GLenum, GLsizei, const GLchar *const*) ) LoadProcAddress("glCreateShaderProgramv");
	glCreateSyncFromCLeventARB = (GLsync (*)(struct _cl_context *, struct _cl_event *, GLbitfield) ) LoadProcAddress("glCreateSyncFromCLeventARB");
	glCreateTextures = (void (*)(GLenum, GLsizei, GLuint *) ) LoadProcAddress("glCreateTextures");
	glCreateTransformFeedbacks = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateTransformFeedbacks");
	glCreateVertexArrays = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glCreateVertexArrays");
	glCullFace = (void (*)(GLenum) ) LoadProcAddress("glCullFace");
	glDebugMessageCallback = (void (*)(GLDEBUGPROC, const void *) ) LoadProcAddress("glDebugMessageCallback");
	glDebugMessageCallbackARB = (void (*)(GLDEBUGPROCARB, const void *) ) LoadProcAddress("glDebugMessageCallbackARB");
	glDebugMessageCallbackKHR = (void (*)(GLDEBUGPROCKHR, const void *) ) LoadProcAddress("glDebugMessageCallbackKHR");
	glDebugMessageControl = (void (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) ) LoadProcAddress("glDebugMessageControl");
	glDebugMessageControlARB = (void (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) ) LoadProcAddress("glDebugMessageControlARB");
	glDebugMessageControlKHR = (void (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean) ) LoadProcAddress("glDebugMessageControlKHR");
	glDebugMessageInsert = (void (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) ) LoadProcAddress("glDebugMessageInsert");
	glDebugMessageInsertARB = (void (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) ) LoadProcAddress("glDebugMessageInsertARB");
	glDebugMessageInsertKHR = (void (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *) ) LoadProcAddress("glDebugMessageInsertKHR");
	glDeleteBuffers = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteBuffers");
	glDeleteFramebuffers = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteFramebuffers");
	glDeleteNamedStringARB = (void (*)(GLint, const GLchar *) ) LoadProcAddress("glDeleteNamedStringARB");
	glDeleteProgram = (void (*)(GLuint) ) LoadProcAddress("glDeleteProgram");
	glDeleteProgramPipelines = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteProgramPipelines");
	glDeleteQueries = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteQueries");
	glDeleteRenderbuffers = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteRenderbuffers");
	glDeleteSamplers = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteSamplers");
	glDeleteShader = (void (*)(GLuint) ) LoadProcAddress("glDeleteShader");
	glDeleteSync = (void (*)(GLsync) ) LoadProcAddress("glDeleteSync");
	glDeleteTextures = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteTextures");
	glDeleteTransformFeedbacks = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteTransformFeedbacks");
	glDeleteVertexArrays = (void (*)(GLsizei, const GLuint *) ) LoadProcAddress("glDeleteVertexArrays");
	glDepthFunc = (void (*)(GLenum) ) LoadProcAddress("glDepthFunc");
	glDepthMask = (void (*)(GLboolean) ) LoadProcAddress("glDepthMask");
	glDepthRange = (void (*)(GLdouble, GLdouble) ) LoadProcAddress("glDepthRange");
	glDepthRangeArrayv = (void (*)(GLuint, GLsizei, const GLdouble *) ) LoadProcAddress("glDepthRangeArrayv");
	glDepthRangeIndexed = (void (*)(GLuint, GLdouble, GLdouble) ) LoadProcAddress("glDepthRangeIndexed");
	glDepthRangef = (void (*)(GLfloat, GLfloat) ) LoadProcAddress("glDepthRangef");
	glDetachShader = (void (*)(GLuint, GLuint) ) LoadProcAddress("glDetachShader");
	glDisable = (void (*)(GLenum) ) LoadProcAddress("glDisable");
	glDisableClientStateIndexedEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glDisableClientStateIndexedEXT");
	glDisableClientStateiEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glDisableClientStateiEXT");
	glDisableIndexedEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glDisableIndexedEXT");
	glDisableVertexArrayAttrib = (void (*)(GLuint, GLuint) ) LoadProcAddress("glDisableVertexArrayAttrib");
	glDisableVertexArrayAttribEXT = (void (*)(GLuint, GLuint) ) LoadProcAddress("glDisableVertexArrayAttribEXT");
	glDisableVertexArrayEXT = (void (*)(GLuint, GLenum) ) LoadProcAddress("glDisableVertexArrayEXT");
	glDisableVertexAttribArray = (void (*)(GLuint) ) LoadProcAddress("glDisableVertexAttribArray");
	glDisablei = (void (*)(GLenum, GLuint) ) LoadProcAddress("glDisablei");
	glDispatchCompute = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glDispatchCompute");
	glDispatchComputeGroupSizeARB = (void (*)(GLuint, GLuint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glDispatchComputeGroupSizeARB");
	glDispatchComputeIndirect = (void (*)(GLintptr) ) LoadProcAddress("glDispatchComputeIndirect");
	glDrawArrays = (void (*)(GLenum, GLint, GLsizei) ) LoadProcAddress("glDrawArrays");
	glDrawArraysIndirect = (void (*)(GLenum, const void *) ) LoadProcAddress("glDrawArraysIndirect");
	glDrawArraysInstanced = (void (*)(GLenum, GLint, GLsizei, GLsizei) ) LoadProcAddress("glDrawArraysInstanced");
	glDrawArraysInstancedBaseInstance = (void (*)(GLenum, GLint, GLsizei, GLsizei, GLuint) ) LoadProcAddress("glDrawArraysInstancedBaseInstance");
	glDrawBuffer = (void (*)(GLenum) ) LoadProcAddress("glDrawBuffer");
	glDrawBuffers = (void (*)(GLsizei, const GLenum *) ) LoadProcAddress("glDrawBuffers");
	glDrawElements = (void (*)(GLenum, GLsizei, GLenum, const void *) ) LoadProcAddress("glDrawElements");
	glDrawElementsBaseVertex = (void (*)(GLenum, GLsizei, GLenum, const void *, GLint) ) LoadProcAddress("glDrawElementsBaseVertex");
	glDrawElementsIndirect = (void (*)(GLenum, GLenum, const void *) ) LoadProcAddress("glDrawElementsIndirect");
	glDrawElementsInstanced = (void (*)(GLenum, GLsizei, GLenum, const void *, GLsizei) ) LoadProcAddress("glDrawElementsInstanced");
	glDrawElementsInstancedBaseInstance = (void (*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint) ) LoadProcAddress("glDrawElementsInstancedBaseInstance");
	glDrawElementsInstancedBaseVertex = (void (*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint) ) LoadProcAddress("glDrawElementsInstancedBaseVertex");
	glDrawElementsInstancedBaseVertexBaseInstance = (void (*)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint) ) LoadProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
	glDrawRangeElements = (void (*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *) ) LoadProcAddress("glDrawRangeElements");
	glDrawRangeElementsBaseVertex = (void (*)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint) ) LoadProcAddress("glDrawRangeElementsBaseVertex");
	glDrawTransformFeedback = (void (*)(GLenum, GLuint) ) LoadProcAddress("glDrawTransformFeedback");
	glDrawTransformFeedbackInstanced = (void (*)(GLenum, GLuint, GLsizei) ) LoadProcAddress("glDrawTransformFeedbackInstanced");
	glDrawTransformFeedbackStream = (void (*)(GLenum, GLuint, GLuint) ) LoadProcAddress("glDrawTransformFeedbackStream");
	glDrawTransformFeedbackStreamInstanced = (void (*)(GLenum, GLuint, GLuint, GLsizei) ) LoadProcAddress("glDrawTransformFeedbackStreamInstanced");
	glEnable = (void (*)(GLenum) ) LoadProcAddress("glEnable");
	glEnableClientStateIndexedEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glEnableClientStateIndexedEXT");
	glEnableClientStateiEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glEnableClientStateiEXT");
	glEnableIndexedEXT = (void (*)(GLenum, GLuint) ) LoadProcAddress("glEnableIndexedEXT");
	glEnableVertexArrayAttrib = (void (*)(GLuint, GLuint) ) LoadProcAddress("glEnableVertexArrayAttrib");
	glEnableVertexArrayAttribEXT = (void (*)(GLuint, GLuint) ) LoadProcAddress("glEnableVertexArrayAttribEXT");
	glEnableVertexArrayEXT = (void (*)(GLuint, GLenum) ) LoadProcAddress("glEnableVertexArrayEXT");
	glEnableVertexAttribArray = (void (*)(GLuint) ) LoadProcAddress("glEnableVertexAttribArray");
	glEnablei = (void (*)(GLenum, GLuint) ) LoadProcAddress("glEnablei");
	glEndConditionalRender = (void (*)() ) LoadProcAddress("glEndConditionalRender");
	glEndQuery = (void (*)(GLenum) ) LoadProcAddress("glEndQuery");
	glEndQueryIndexed = (void (*)(GLenum, GLuint) ) LoadProcAddress("glEndQueryIndexed");
	glEndTransformFeedback = (void (*)() ) LoadProcAddress("glEndTransformFeedback");
	glFenceSync = (GLsync (*)(GLenum, GLbitfield) ) LoadProcAddress("glFenceSync");
	glFinish = (void (*)() ) LoadProcAddress("glFinish");
	glFlush = (void (*)() ) LoadProcAddress("glFlush");
	glFlushMappedBufferRange = (void (*)(GLenum, GLintptr, GLsizeiptr) ) LoadProcAddress("glFlushMappedBufferRange");
	glFlushMappedNamedBufferRange = (void (*)(GLuint, GLintptr, GLsizei) ) LoadProcAddress("glFlushMappedNamedBufferRange");
	glFlushMappedNamedBufferRangeEXT = (void (*)(GLuint, GLintptr, GLsizeiptr) ) LoadProcAddress("glFlushMappedNamedBufferRangeEXT");
	glFramebufferDrawBufferEXT = (void (*)(GLuint, GLenum) ) LoadProcAddress("glFramebufferDrawBufferEXT");
	glFramebufferDrawBuffersEXT = (void (*)(GLuint, GLsizei, const GLenum *) ) LoadProcAddress("glFramebufferDrawBuffersEXT");
	glFramebufferParameteri = (void (*)(GLenum, GLenum, GLint) ) LoadProcAddress("glFramebufferParameteri");
	glFramebufferReadBufferEXT = (void (*)(GLuint, GLenum) ) LoadProcAddress("glFramebufferReadBufferEXT");
	glFramebufferRenderbuffer = (void (*)(GLenum, GLenum, GLenum, GLuint) ) LoadProcAddress("glFramebufferRenderbuffer");
	glFramebufferTexture = (void (*)(GLenum, GLenum, GLuint, GLint) ) LoadProcAddress("glFramebufferTexture");
	glFramebufferTexture1D = (void (*)(GLenum, GLenum, GLenum, GLuint, GLint) ) LoadProcAddress("glFramebufferTexture1D");
	glFramebufferTexture2D = (void (*)(GLenum, GLenum, GLenum, GLuint, GLint) ) LoadProcAddress("glFramebufferTexture2D");
	glFramebufferTexture3D = (void (*)(GLenum, GLenum, GLenum, GLuint, GLint, GLint) ) LoadProcAddress("glFramebufferTexture3D");
	glFramebufferTextureLayer = (void (*)(GLenum, GLenum, GLuint, GLint, GLint) ) LoadProcAddress("glFramebufferTextureLayer");
	glFrontFace = (void (*)(GLenum) ) LoadProcAddress("glFrontFace");
	glGenBuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenBuffers");
	glGenFramebuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenFramebuffers");
	glGenProgramPipelines = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenProgramPipelines");
	glGenQueries = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenQueries");
	glGenRenderbuffers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenRenderbuffers");
	glGenSamplers = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenSamplers");
	glGenTextures = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenTextures");
	glGenTransformFeedbacks = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenTransformFeedbacks");
	glGenVertexArrays = (void (*)(GLsizei, GLuint *) ) LoadProcAddress("glGenVertexArrays");
	glGenerateMipmap = (void (*)(GLenum) ) LoadProcAddress("glGenerateMipmap");
	glGenerateMultiTexMipmapEXT = (void (*)(GLenum, GLenum) ) LoadProcAddress("glGenerateMultiTexMipmapEXT");
	glGenerateTextureMipmap = (void (*)(GLuint) ) LoadProcAddress("glGenerateTextureMipmap");
	glGenerateTextureMipmapEXT = (void (*)(GLuint, GLenum) ) LoadProcAddress("glGenerateTextureMipmapEXT");
	glGetActiveAtomicCounterBufferiv = (void (*)(GLuint, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetActiveAtomicCounterBufferiv");
	glGetActiveAttrib = (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) ) LoadProcAddress("glGetActiveAttrib");
	glGetActiveSubroutineName = (void (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetActiveSubroutineName");
	glGetActiveSubroutineUniformName = (void (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetActiveSubroutineUniformName");
	glGetActiveSubroutineUniformiv = (void (*)(GLuint, GLenum, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetActiveSubroutineUniformiv");
	glGetActiveUniform = (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *) ) LoadProcAddress("glGetActiveUniform");
	glGetActiveUniformBlockName = (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetActiveUniformBlockName");
	glGetActiveUniformBlockiv = (void (*)(GLuint, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetActiveUniformBlockiv");
	glGetActiveUniformName = (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetActiveUniformName");
	glGetActiveUniformsiv = (void (*)(GLuint, GLsizei, const GLuint *, GLenum, GLint *) ) LoadProcAddress("glGetActiveUniformsiv");
	glGetAttachedShaders = (void (*)(GLuint, GLsizei, GLsizei *, GLuint *) ) LoadProcAddress("glGetAttachedShaders");
	glGetAttribLocation = (GLint (*)(GLuint, const GLchar *) ) LoadProcAddress("glGetAttribLocation");
	glGetBooleanIndexedvEXT = (void (*)(GLenum, GLuint, GLboolean *) ) LoadProcAddress("glGetBooleanIndexedvEXT");
	glGetBooleani_v = (void (*)(GLenum, GLuint, GLboolean *) ) LoadProcAddress("glGetBooleani_v");
	glGetBooleanv = (void (*)(GLenum, GLboolean *) ) LoadProcAddress("glGetBooleanv");
	glGetBufferParameteri64v = (void (*)(GLenum, GLenum, GLint64 *) ) LoadProcAddress("glGetBufferParameteri64v");
	glGetBufferParameteriv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetBufferParameteriv");
	glGetBufferPointerv = (void (*)(GLenum, GLenum, void **) ) LoadProcAddress("glGetBufferPointerv");
	glGetBufferSubData = (void (*)(GLenum, GLintptr, GLsizeiptr, void *) ) LoadProcAddress("glGetBufferSubData");
	glGetCompressedMultiTexImageEXT = (void (*)(GLenum, GLenum, GLint, void *) ) LoadProcAddress("glGetCompressedMultiTexImageEXT");
	glGetCompressedTexImage = (void (*)(GLenum, GLint, void *) ) LoadProcAddress("glGetCompressedTexImage");
	glGetCompressedTextureImage = (void (*)(GLuint, GLint, GLsizei, void *) ) LoadProcAddress("glGetCompressedTextureImage");
	glGetCompressedTextureImageEXT = (void (*)(GLuint, GLenum, GLint, void *) ) LoadProcAddress("glGetCompressedTextureImageEXT");
	glGetCompressedTextureSubImage = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *) ) LoadProcAddress("glGetCompressedTextureSubImage");
	glGetDebugMessageLog = (GLuint (*)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) ) LoadProcAddress("glGetDebugMessageLog");
	glGetDebugMessageLogARB = (GLuint (*)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) ) LoadProcAddress("glGetDebugMessageLogARB");
	glGetDebugMessageLogKHR = (GLuint (*)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *) ) LoadProcAddress("glGetDebugMessageLogKHR");
	glGetDoubleIndexedvEXT = (void (*)(GLenum, GLuint, GLdouble *) ) LoadProcAddress("glGetDoubleIndexedvEXT");
	glGetDoublei_v = (void (*)(GLenum, GLuint, GLdouble *) ) LoadProcAddress("glGetDoublei_v");
	glGetDoublei_vEXT = (void (*)(GLenum, GLuint, GLdouble *) ) LoadProcAddress("glGetDoublei_vEXT");
	glGetDoublev = (void (*)(GLenum, GLdouble *) ) LoadProcAddress("glGetDoublev");
	glGetError = (GLenum (*)() ) LoadProcAddress("glGetError");
	glGetFloatIndexedvEXT = (void (*)(GLenum, GLuint, GLfloat *) ) LoadProcAddress("glGetFloatIndexedvEXT");
	glGetFloati_v = (void (*)(GLenum, GLuint, GLfloat *) ) LoadProcAddress("glGetFloati_v");
	glGetFloati_vEXT = (void (*)(GLenum, GLuint, GLfloat *) ) LoadProcAddress("glGetFloati_vEXT");
	glGetFloatv = (void (*)(GLenum, GLfloat *) ) LoadProcAddress("glGetFloatv");
	glGetFragDataIndex = (GLint (*)(GLuint, const GLchar *) ) LoadProcAddress("glGetFragDataIndex");
	glGetFragDataLocation = (GLint (*)(GLuint, const GLchar *) ) LoadProcAddress("glGetFragDataLocation");
	glGetFramebufferAttachmentParameteriv = (void (*)(GLenum, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetFramebufferAttachmentParameteriv");
	glGetFramebufferParameteriv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetFramebufferParameteriv");
	glGetFramebufferParameterivEXT = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetFramebufferParameterivEXT");
	glGetGraphicsResetStatus = (GLenum (*)() ) LoadProcAddress("glGetGraphicsResetStatus");
	glGetGraphicsResetStatusARB = (GLenum (*)() ) LoadProcAddress("glGetGraphicsResetStatusARB");
	glGetGraphicsResetStatusKHR = (GLenum (*)() ) LoadProcAddress("glGetGraphicsResetStatusKHR");
	glGetImageHandleARB = (GLuint64 (*)(GLuint, GLint, GLboolean, GLint, GLenum) ) LoadProcAddress("glGetImageHandleARB");
	glGetInteger64i_v = (void (*)(GLenum, GLuint, GLint64 *) ) LoadProcAddress("glGetInteger64i_v");
	glGetInteger64v = (void (*)(GLenum, GLint64 *) ) LoadProcAddress("glGetInteger64v");
	glGetIntegerIndexedvEXT = (void (*)(GLenum, GLuint, GLint *) ) LoadProcAddress("glGetIntegerIndexedvEXT");
	glGetIntegeri_v = (void (*)(GLenum, GLuint, GLint *) ) LoadProcAddress("glGetIntegeri_v");
	glGetIntegerv = (void (*)(GLenum, GLint *) ) LoadProcAddress("glGetIntegerv");
	glGetInternalformati64v = (void (*)(GLenum, GLenum, GLenum, GLsizei, GLint64 *) ) LoadProcAddress("glGetInternalformati64v");
	glGetInternalformativ = (void (*)(GLenum, GLenum, GLenum, GLsizei, GLint *) ) LoadProcAddress("glGetInternalformativ");
	glGetMultiTexEnvfvEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat *) ) LoadProcAddress("glGetMultiTexEnvfvEXT");
	glGetMultiTexEnvivEXT = (void (*)(GLenum, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetMultiTexEnvivEXT");
	glGetMultiTexGendvEXT = (void (*)(GLenum, GLenum, GLenum, GLdouble *) ) LoadProcAddress("glGetMultiTexGendvEXT");
	glGetMultiTexGenfvEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat *) ) LoadProcAddress("glGetMultiTexGenfvEXT");
	glGetMultiTexGenivEXT = (void (*)(GLenum, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetMultiTexGenivEXT");
	glGetMultiTexImageEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLenum, void *) ) LoadProcAddress("glGetMultiTexImageEXT");
	glGetMultiTexLevelParameterfvEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLfloat *) ) LoadProcAddress("glGetMultiTexLevelParameterfvEXT");
	glGetMultiTexLevelParameterivEXT = (void (*)(GLenum, GLenum, GLint, GLenum, GLint *) ) LoadProcAddress("glGetMultiTexLevelParameterivEXT");
	glGetMultiTexParameterIivEXT = (void (*)(GLenum, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetMultiTexParameterIivEXT");
	glGetMultiTexParameterIuivEXT = (void (*)(GLenum, GLenum, GLenum, GLuint *) ) LoadProcAddress("glGetMultiTexParameterIuivEXT");
	glGetMultiTexParameterfvEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat *) ) LoadProcAddress("glGetMultiTexParameterfvEXT");
	glGetMultiTexParameterivEXT = (void (*)(GLenum, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetMultiTexParameterivEXT");
	glGetMultisamplefv = (void (*)(GLenum, GLuint, GLfloat *) ) LoadProcAddress("glGetMultisamplefv");
	glGetNamedBufferParameteri64v = (void (*)(GLuint, GLenum, GLint64 *) ) LoadProcAddress("glGetNamedBufferParameteri64v");
	glGetNamedBufferParameteriv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedBufferParameteriv");
	glGetNamedBufferParameterivEXT = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedBufferParameterivEXT");
	glGetNamedBufferPointerv = (void (*)(GLuint, GLenum, void **) ) LoadProcAddress("glGetNamedBufferPointerv");
	glGetNamedBufferPointervEXT = (void (*)(GLuint, GLenum, void **) ) LoadProcAddress("glGetNamedBufferPointervEXT");
	glGetNamedBufferSubData = (void (*)(GLuint, GLintptr, GLsizei, void *) ) LoadProcAddress("glGetNamedBufferSubData");
	glGetNamedBufferSubDataEXT = (void (*)(GLuint, GLintptr, GLsizeiptr, void *) ) LoadProcAddress("glGetNamedBufferSubDataEXT");
	glGetNamedFramebufferAttachmentParameteriv = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetNamedFramebufferAttachmentParameteriv");
	glGetNamedFramebufferAttachmentParameterivEXT = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetNamedFramebufferAttachmentParameterivEXT");
	glGetNamedFramebufferParameteriv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedFramebufferParameteriv");
	glGetNamedFramebufferParameterivEXT = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedFramebufferParameterivEXT");
	glGetNamedProgramLocalParameterIivEXT = (void (*)(GLuint, GLenum, GLuint, GLint *) ) LoadProcAddress("glGetNamedProgramLocalParameterIivEXT");
	glGetNamedProgramLocalParameterIuivEXT = (void (*)(GLuint, GLenum, GLuint, GLuint *) ) LoadProcAddress("glGetNamedProgramLocalParameterIuivEXT");
	glGetNamedProgramLocalParameterdvEXT = (void (*)(GLuint, GLenum, GLuint, GLdouble *) ) LoadProcAddress("glGetNamedProgramLocalParameterdvEXT");
	glGetNamedProgramLocalParameterfvEXT = (void (*)(GLuint, GLenum, GLuint, GLfloat *) ) LoadProcAddress("glGetNamedProgramLocalParameterfvEXT");
	glGetNamedProgramStringEXT = (void (*)(GLuint, GLenum, GLenum, void *) ) LoadProcAddress("glGetNamedProgramStringEXT");
	glGetNamedProgramivEXT = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetNamedProgramivEXT");
	glGetNamedRenderbufferParameteriv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedRenderbufferParameteriv");
	glGetNamedRenderbufferParameterivEXT = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetNamedRenderbufferParameterivEXT");
	glGetNamedStringARB = (void (*)(GLint, const GLchar *, GLsizei, GLint *, GLchar *) ) LoadProcAddress("glGetNamedStringARB");
	glGetNamedStringivARB = (void (*)(GLint, const GLchar *, GLenum, GLint *) ) LoadProcAddress("glGetNamedStringivARB");
	glGetObjectLabel = (void (*)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetObjectLabel");
	glGetObjectLabelKHR = (void (*)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetObjectLabelKHR");
	glGetObjectPtrLabel = (void (*)(const void *, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetObjectPtrLabel");
	glGetObjectPtrLabelKHR = (void (*)(const void *, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetObjectPtrLabelKHR");
	glGetPointerIndexedvEXT = (void (*)(GLenum, GLuint, void **) ) LoadProcAddress("glGetPointerIndexedvEXT");
	glGetPointeri_vEXT = (void (*)(GLenum, GLuint, void **) ) LoadProcAddress("glGetPointeri_vEXT");
	glGetPointerv = (void (*)(GLenum, void **) ) LoadProcAddress("glGetPointerv");
	glGetPointervKHR = (void (*)(GLenum, void **) ) LoadProcAddress("glGetPointervKHR");
	glGetProgramBinary = (void (*)(GLuint, GLsizei, GLsizei *, GLenum *, void *) ) LoadProcAddress("glGetProgramBinary");
	glGetProgramInfoLog = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetProgramInfoLog");
	glGetProgramInterfaceiv = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetProgramInterfaceiv");
	glGetProgramPipelineInfoLog = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetProgramPipelineInfoLog");
	glGetProgramPipelineiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetProgramPipelineiv");
	glGetProgramResourceIndex = (GLuint (*)(GLuint, GLenum, const GLchar *) ) LoadProcAddress("glGetProgramResourceIndex");
	glGetProgramResourceLocation = (GLint (*)(GLuint, GLenum, const GLchar *) ) LoadProcAddress("glGetProgramResourceLocation");
	glGetProgramResourceLocationIndex = (GLint (*)(GLuint, GLenum, const GLchar *) ) LoadProcAddress("glGetProgramResourceLocationIndex");
	glGetProgramResourceName = (void (*)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetProgramResourceName");
	glGetProgramResourceiv = (void (*)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *) ) LoadProcAddress("glGetProgramResourceiv");
	glGetProgramStageiv = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetProgramStageiv");
	glGetProgramiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetProgramiv");
	glGetQueryBufferObjecti64v = (void (*)(GLuint, GLuint, GLenum, GLintptr) ) LoadProcAddress("glGetQueryBufferObjecti64v");
	glGetQueryBufferObjectiv = (void (*)(GLuint, GLuint, GLenum, GLintptr) ) LoadProcAddress("glGetQueryBufferObjectiv");
	glGetQueryBufferObjectui64v = (void (*)(GLuint, GLuint, GLenum, GLintptr) ) LoadProcAddress("glGetQueryBufferObjectui64v");
	glGetQueryBufferObjectuiv = (void (*)(GLuint, GLuint, GLenum, GLintptr) ) LoadProcAddress("glGetQueryBufferObjectuiv");
	glGetQueryIndexediv = (void (*)(GLenum, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetQueryIndexediv");
	glGetQueryObjecti64v = (void (*)(GLuint, GLenum, GLint64 *) ) LoadProcAddress("glGetQueryObjecti64v");
	glGetQueryObjectiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetQueryObjectiv");
	glGetQueryObjectui64v = (void (*)(GLuint, GLenum, GLuint64 *) ) LoadProcAddress("glGetQueryObjectui64v");
	glGetQueryObjectuiv = (void (*)(GLuint, GLenum, GLuint *) ) LoadProcAddress("glGetQueryObjectuiv");
	glGetQueryiv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetQueryiv");
	glGetRenderbufferParameteriv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetRenderbufferParameteriv");
	glGetSamplerParameterIiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetSamplerParameterIiv");
	glGetSamplerParameterIuiv = (void (*)(GLuint, GLenum, GLuint *) ) LoadProcAddress("glGetSamplerParameterIuiv");
	glGetSamplerParameterfv = (void (*)(GLuint, GLenum, GLfloat *) ) LoadProcAddress("glGetSamplerParameterfv");
	glGetSamplerParameteriv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetSamplerParameteriv");
	glGetShaderInfoLog = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetShaderInfoLog");
	glGetShaderPrecisionFormat = (void (*)(GLenum, GLenum, GLint *, GLint *) ) LoadProcAddress("glGetShaderPrecisionFormat");
	glGetShaderSource = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *) ) LoadProcAddress("glGetShaderSource");
	glGetShaderiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetShaderiv");
	glGetString = (const GLubyte * (*)(GLenum) ) LoadProcAddress("glGetString");
	glGetStringi = (const GLubyte * (*)(GLenum, GLuint) ) LoadProcAddress("glGetStringi");
	glGetSubroutineIndex = (GLuint (*)(GLuint, GLenum, const GLchar *) ) LoadProcAddress("glGetSubroutineIndex");
	glGetSubroutineUniformLocation = (GLint (*)(GLuint, GLenum, const GLchar *) ) LoadProcAddress("glGetSubroutineUniformLocation");
	glGetSynciv = (void (*)(GLsync, GLenum, GLsizei, GLsizei *, GLint *) ) LoadProcAddress("glGetSynciv");
	glGetTexImage = (void (*)(GLenum, GLint, GLenum, GLenum, void *) ) LoadProcAddress("glGetTexImage");
	glGetTexLevelParameterfv = (void (*)(GLenum, GLint, GLenum, GLfloat *) ) LoadProcAddress("glGetTexLevelParameterfv");
	glGetTexLevelParameteriv = (void (*)(GLenum, GLint, GLenum, GLint *) ) LoadProcAddress("glGetTexLevelParameteriv");
	glGetTexParameterIiv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetTexParameterIiv");
	glGetTexParameterIuiv = (void (*)(GLenum, GLenum, GLuint *) ) LoadProcAddress("glGetTexParameterIuiv");
	glGetTexParameterfv = (void (*)(GLenum, GLenum, GLfloat *) ) LoadProcAddress("glGetTexParameterfv");
	glGetTexParameteriv = (void (*)(GLenum, GLenum, GLint *) ) LoadProcAddress("glGetTexParameteriv");
	glGetTextureHandleARB = (GLuint64 (*)(GLuint) ) LoadProcAddress("glGetTextureHandleARB");
	glGetTextureImage = (void (*)(GLuint, GLint, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glGetTextureImage");
	glGetTextureImageEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLenum, void *) ) LoadProcAddress("glGetTextureImageEXT");
	glGetTextureLevelParameterfv = (void (*)(GLuint, GLint, GLenum, GLfloat *) ) LoadProcAddress("glGetTextureLevelParameterfv");
	glGetTextureLevelParameterfvEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLfloat *) ) LoadProcAddress("glGetTextureLevelParameterfvEXT");
	glGetTextureLevelParameteriv = (void (*)(GLuint, GLint, GLenum, GLint *) ) LoadProcAddress("glGetTextureLevelParameteriv");
	glGetTextureLevelParameterivEXT = (void (*)(GLuint, GLenum, GLint, GLenum, GLint *) ) LoadProcAddress("glGetTextureLevelParameterivEXT");
	glGetTextureParameterIiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetTextureParameterIiv");
	glGetTextureParameterIivEXT = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetTextureParameterIivEXT");
	glGetTextureParameterIuiv = (void (*)(GLuint, GLenum, GLuint *) ) LoadProcAddress("glGetTextureParameterIuiv");
	glGetTextureParameterIuivEXT = (void (*)(GLuint, GLenum, GLenum, GLuint *) ) LoadProcAddress("glGetTextureParameterIuivEXT");
	glGetTextureParameterfv = (void (*)(GLuint, GLenum, GLfloat *) ) LoadProcAddress("glGetTextureParameterfv");
	glGetTextureParameterfvEXT = (void (*)(GLuint, GLenum, GLenum, GLfloat *) ) LoadProcAddress("glGetTextureParameterfvEXT");
	glGetTextureParameteriv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetTextureParameteriv");
	glGetTextureParameterivEXT = (void (*)(GLuint, GLenum, GLenum, GLint *) ) LoadProcAddress("glGetTextureParameterivEXT");
	glGetTextureSamplerHandleARB = (GLuint64 (*)(GLuint, GLuint) ) LoadProcAddress("glGetTextureSamplerHandleARB");
	glGetTextureSubImage = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glGetTextureSubImage");
	glGetTransformFeedbackVarying = (void (*)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *) ) LoadProcAddress("glGetTransformFeedbackVarying");
	glGetTransformFeedbacki64_v = (void (*)(GLuint, GLenum, GLuint, GLint64 *) ) LoadProcAddress("glGetTransformFeedbacki64_v");
	glGetTransformFeedbacki_v = (void (*)(GLuint, GLenum, GLuint, GLint *) ) LoadProcAddress("glGetTransformFeedbacki_v");
	glGetTransformFeedbackiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetTransformFeedbackiv");
	glGetUniformBlockIndex = (GLuint (*)(GLuint, const GLchar *) ) LoadProcAddress("glGetUniformBlockIndex");
	glGetUniformIndices = (void (*)(GLuint, GLsizei, const GLchar *const*, GLuint *) ) LoadProcAddress("glGetUniformIndices");
	glGetUniformLocation = (GLint (*)(GLuint, const GLchar *) ) LoadProcAddress("glGetUniformLocation");
	glGetUniformSubroutineuiv = (void (*)(GLenum, GLint, GLuint *) ) LoadProcAddress("glGetUniformSubroutineuiv");
	glGetUniformdv = (void (*)(GLuint, GLint, GLdouble *) ) LoadProcAddress("glGetUniformdv");
	glGetUniformfv = (void (*)(GLuint, GLint, GLfloat *) ) LoadProcAddress("glGetUniformfv");
	glGetUniformiv = (void (*)(GLuint, GLint, GLint *) ) LoadProcAddress("glGetUniformiv");
	glGetUniformuiv = (void (*)(GLuint, GLint, GLuint *) ) LoadProcAddress("glGetUniformuiv");
	glGetVertexArrayIndexed64iv = (void (*)(GLuint, GLuint, GLenum, GLint64 *) ) LoadProcAddress("glGetVertexArrayIndexed64iv");
	glGetVertexArrayIndexediv = (void (*)(GLuint, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexArrayIndexediv");
	glGetVertexArrayIntegeri_vEXT = (void (*)(GLuint, GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexArrayIntegeri_vEXT");
	glGetVertexArrayIntegervEXT = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexArrayIntegervEXT");
	glGetVertexArrayPointeri_vEXT = (void (*)(GLuint, GLuint, GLenum, void **) ) LoadProcAddress("glGetVertexArrayPointeri_vEXT");
	glGetVertexArrayPointervEXT = (void (*)(GLuint, GLenum, void **) ) LoadProcAddress("glGetVertexArrayPointervEXT");
	glGetVertexArrayiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexArrayiv");
	glGetVertexAttribIiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexAttribIiv");
	glGetVertexAttribIuiv = (void (*)(GLuint, GLenum, GLuint *) ) LoadProcAddress("glGetVertexAttribIuiv");
	glGetVertexAttribLdv = (void (*)(GLuint, GLenum, GLdouble *) ) LoadProcAddress("glGetVertexAttribLdv");
	glGetVertexAttribLui64vARB = (void (*)(GLuint, GLenum, GLuint64EXT *) ) LoadProcAddress("glGetVertexAttribLui64vARB");
	glGetVertexAttribPointerv = (void (*)(GLuint, GLenum, void **) ) LoadProcAddress("glGetVertexAttribPointerv");
	glGetVertexAttribdv = (void (*)(GLuint, GLenum, GLdouble *) ) LoadProcAddress("glGetVertexAttribdv");
	glGetVertexAttribfv = (void (*)(GLuint, GLenum, GLfloat *) ) LoadProcAddress("glGetVertexAttribfv");
	glGetVertexAttribiv = (void (*)(GLuint, GLenum, GLint *) ) LoadProcAddress("glGetVertexAttribiv");
	glGetnCompressedTexImage = (void (*)(GLenum, GLint, GLsizei, void *) ) LoadProcAddress("glGetnCompressedTexImage");
	glGetnCompressedTexImageARB = (void (*)(GLenum, GLint, GLsizei, void *) ) LoadProcAddress("glGetnCompressedTexImageARB");
	glGetnTexImage = (void (*)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glGetnTexImage");
	glGetnTexImageARB = (void (*)(GLenum, GLint, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glGetnTexImageARB");
	glGetnUniformdv = (void (*)(GLuint, GLint, GLsizei, GLdouble *) ) LoadProcAddress("glGetnUniformdv");
	glGetnUniformdvARB = (void (*)(GLuint, GLint, GLsizei, GLdouble *) ) LoadProcAddress("glGetnUniformdvARB");
	glGetnUniformfv = (void (*)(GLuint, GLint, GLsizei, GLfloat *) ) LoadProcAddress("glGetnUniformfv");
	glGetnUniformfvARB = (void (*)(GLuint, GLint, GLsizei, GLfloat *) ) LoadProcAddress("glGetnUniformfvARB");
	glGetnUniformfvKHR = (void (*)(GLuint, GLint, GLsizei, GLfloat *) ) LoadProcAddress("glGetnUniformfvKHR");
	glGetnUniformiv = (void (*)(GLuint, GLint, GLsizei, GLint *) ) LoadProcAddress("glGetnUniformiv");
	glGetnUniformivARB = (void (*)(GLuint, GLint, GLsizei, GLint *) ) LoadProcAddress("glGetnUniformivARB");
	glGetnUniformivKHR = (void (*)(GLuint, GLint, GLsizei, GLint *) ) LoadProcAddress("glGetnUniformivKHR");
	glGetnUniformuiv = (void (*)(GLuint, GLint, GLsizei, GLuint *) ) LoadProcAddress("glGetnUniformuiv");
	glGetnUniformuivARB = (void (*)(GLuint, GLint, GLsizei, GLuint *) ) LoadProcAddress("glGetnUniformuivARB");
	glGetnUniformuivKHR = (void (*)(GLuint, GLint, GLsizei, GLuint *) ) LoadProcAddress("glGetnUniformuivKHR");
	glHint = (void (*)(GLenum, GLenum) ) LoadProcAddress("glHint");
	glInvalidateBufferData = (void (*)(GLuint) ) LoadProcAddress("glInvalidateBufferData");
	glInvalidateBufferSubData = (void (*)(GLuint, GLintptr, GLsizeiptr) ) LoadProcAddress("glInvalidateBufferSubData");
	glInvalidateFramebuffer = (void (*)(GLenum, GLsizei, const GLenum *) ) LoadProcAddress("glInvalidateFramebuffer");
	glInvalidateNamedFramebufferData = (void (*)(GLuint, GLsizei, const GLenum *) ) LoadProcAddress("glInvalidateNamedFramebufferData");
	glInvalidateNamedFramebufferSubData = (void (*)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glInvalidateNamedFramebufferSubData");
	glInvalidateSubFramebuffer = (void (*)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glInvalidateSubFramebuffer");
	glInvalidateTexImage = (void (*)(GLuint, GLint) ) LoadProcAddress("glInvalidateTexImage");
	glInvalidateTexSubImage = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glInvalidateTexSubImage");
	glIsBuffer = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsBuffer");
	glIsEnabled = (GLboolean (*)(GLenum) ) LoadProcAddress("glIsEnabled");
	glIsEnabledIndexedEXT = (GLboolean (*)(GLenum, GLuint) ) LoadProcAddress("glIsEnabledIndexedEXT");
	glIsEnabledi = (GLboolean (*)(GLenum, GLuint) ) LoadProcAddress("glIsEnabledi");
	glIsFramebuffer = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsFramebuffer");
	glIsImageHandleResidentARB = (GLboolean (*)(GLuint64) ) LoadProcAddress("glIsImageHandleResidentARB");
	glIsNamedStringARB = (GLboolean (*)(GLint, const GLchar *) ) LoadProcAddress("glIsNamedStringARB");
	glIsProgram = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsProgram");
	glIsProgramPipeline = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsProgramPipeline");
	glIsQuery = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsQuery");
	glIsRenderbuffer = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsRenderbuffer");
	glIsSampler = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsSampler");
	glIsShader = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsShader");
	glIsSync = (GLboolean (*)(GLsync) ) LoadProcAddress("glIsSync");
	glIsTexture = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsTexture");
	glIsTextureHandleResidentARB = (GLboolean (*)(GLuint64) ) LoadProcAddress("glIsTextureHandleResidentARB");
	glIsTransformFeedback = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsTransformFeedback");
	glIsVertexArray = (GLboolean (*)(GLuint) ) LoadProcAddress("glIsVertexArray");
	glLineWidth = (void (*)(GLfloat) ) LoadProcAddress("glLineWidth");
	glLinkProgram = (void (*)(GLuint) ) LoadProcAddress("glLinkProgram");
	glLogicOp = (void (*)(GLenum) ) LoadProcAddress("glLogicOp");
	glMakeImageHandleNonResidentARB = (void (*)(GLuint64) ) LoadProcAddress("glMakeImageHandleNonResidentARB");
	glMakeImageHandleResidentARB = (void (*)(GLuint64, GLenum) ) LoadProcAddress("glMakeImageHandleResidentARB");
	glMakeTextureHandleNonResidentARB = (void (*)(GLuint64) ) LoadProcAddress("glMakeTextureHandleNonResidentARB");
	glMakeTextureHandleResidentARB = (void (*)(GLuint64) ) LoadProcAddress("glMakeTextureHandleResidentARB");
	glMapBuffer = (void * (*)(GLenum, GLenum) ) LoadProcAddress("glMapBuffer");
	glMapBufferRange = (void * (*)(GLenum, GLintptr, GLsizeiptr, GLbitfield) ) LoadProcAddress("glMapBufferRange");
	glMapNamedBuffer = (void * (*)(GLuint, GLenum) ) LoadProcAddress("glMapNamedBuffer");
	glMapNamedBufferEXT = (void * (*)(GLuint, GLenum) ) LoadProcAddress("glMapNamedBufferEXT");
	glMapNamedBufferRange = (void * (*)(GLuint, GLintptr, GLsizei, GLbitfield) ) LoadProcAddress("glMapNamedBufferRange");
	glMapNamedBufferRangeEXT = (void * (*)(GLuint, GLintptr, GLsizeiptr, GLbitfield) ) LoadProcAddress("glMapNamedBufferRangeEXT");
	glMatrixFrustumEXT = (void (*)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glMatrixFrustumEXT");
	glMatrixLoadIdentityEXT = (void (*)(GLenum) ) LoadProcAddress("glMatrixLoadIdentityEXT");
	glMatrixLoadTransposedEXT = (void (*)(GLenum, const GLdouble *) ) LoadProcAddress("glMatrixLoadTransposedEXT");
	glMatrixLoadTransposefEXT = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glMatrixLoadTransposefEXT");
	glMatrixLoaddEXT = (void (*)(GLenum, const GLdouble *) ) LoadProcAddress("glMatrixLoaddEXT");
	glMatrixLoadfEXT = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glMatrixLoadfEXT");
	glMatrixMultTransposedEXT = (void (*)(GLenum, const GLdouble *) ) LoadProcAddress("glMatrixMultTransposedEXT");
	glMatrixMultTransposefEXT = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glMatrixMultTransposefEXT");
	glMatrixMultdEXT = (void (*)(GLenum, const GLdouble *) ) LoadProcAddress("glMatrixMultdEXT");
	glMatrixMultfEXT = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glMatrixMultfEXT");
	glMatrixOrthoEXT = (void (*)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glMatrixOrthoEXT");
	glMatrixPopEXT = (void (*)(GLenum) ) LoadProcAddress("glMatrixPopEXT");
	glMatrixPushEXT = (void (*)(GLenum) ) LoadProcAddress("glMatrixPushEXT");
	glMatrixRotatedEXT = (void (*)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glMatrixRotatedEXT");
	glMatrixRotatefEXT = (void (*)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glMatrixRotatefEXT");
	glMatrixScaledEXT = (void (*)(GLenum, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glMatrixScaledEXT");
	glMatrixScalefEXT = (void (*)(GLenum, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glMatrixScalefEXT");
	glMatrixTranslatedEXT = (void (*)(GLenum, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glMatrixTranslatedEXT");
	glMatrixTranslatefEXT = (void (*)(GLenum, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glMatrixTranslatefEXT");
	glMemoryBarrier = (void (*)(GLbitfield) ) LoadProcAddress("glMemoryBarrier");
	glMemoryBarrierByRegion = (void (*)(GLbitfield) ) LoadProcAddress("glMemoryBarrierByRegion");
	glMinSampleShading = (void (*)(GLfloat) ) LoadProcAddress("glMinSampleShading");
	glMinSampleShadingARB = (void (*)(GLfloat) ) LoadProcAddress("glMinSampleShadingARB");
	glMultiDrawArrays = (void (*)(GLenum, const GLint *, const GLsizei *, GLsizei) ) LoadProcAddress("glMultiDrawArrays");
	glMultiDrawArraysIndirect = (void (*)(GLenum, const void *, GLsizei, GLsizei) ) LoadProcAddress("glMultiDrawArraysIndirect");
	glMultiDrawArraysIndirectCountARB = (void (*)(GLenum, GLintptr, GLintptr, GLsizei, GLsizei) ) LoadProcAddress("glMultiDrawArraysIndirectCountARB");
	glMultiDrawElements = (void (*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei) ) LoadProcAddress("glMultiDrawElements");
	glMultiDrawElementsBaseVertex = (void (*)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *) ) LoadProcAddress("glMultiDrawElementsBaseVertex");
	glMultiDrawElementsIndirect = (void (*)(GLenum, GLenum, const void *, GLsizei, GLsizei) ) LoadProcAddress("glMultiDrawElementsIndirect");
	glMultiDrawElementsIndirectCountARB = (void (*)(GLenum, GLenum, GLintptr, GLintptr, GLsizei, GLsizei) ) LoadProcAddress("glMultiDrawElementsIndirectCountARB");
	glMultiTexBufferEXT = (void (*)(GLenum, GLenum, GLenum, GLuint) ) LoadProcAddress("glMultiTexBufferEXT");
	glMultiTexCoordPointerEXT = (void (*)(GLenum, GLint, GLenum, GLsizei, const void *) ) LoadProcAddress("glMultiTexCoordPointerEXT");
	glMultiTexEnvfEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat) ) LoadProcAddress("glMultiTexEnvfEXT");
	glMultiTexEnvfvEXT = (void (*)(GLenum, GLenum, GLenum, const GLfloat *) ) LoadProcAddress("glMultiTexEnvfvEXT");
	glMultiTexEnviEXT = (void (*)(GLenum, GLenum, GLenum, GLint) ) LoadProcAddress("glMultiTexEnviEXT");
	glMultiTexEnvivEXT = (void (*)(GLenum, GLenum, GLenum, const GLint *) ) LoadProcAddress("glMultiTexEnvivEXT");
	glMultiTexGendEXT = (void (*)(GLenum, GLenum, GLenum, GLdouble) ) LoadProcAddress("glMultiTexGendEXT");
	glMultiTexGendvEXT = (void (*)(GLenum, GLenum, GLenum, const GLdouble *) ) LoadProcAddress("glMultiTexGendvEXT");
	glMultiTexGenfEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat) ) LoadProcAddress("glMultiTexGenfEXT");
	glMultiTexGenfvEXT = (void (*)(GLenum, GLenum, GLenum, const GLfloat *) ) LoadProcAddress("glMultiTexGenfvEXT");
	glMultiTexGeniEXT = (void (*)(GLenum, GLenum, GLenum, GLint) ) LoadProcAddress("glMultiTexGeniEXT");
	glMultiTexGenivEXT = (void (*)(GLenum, GLenum, GLenum, const GLint *) ) LoadProcAddress("glMultiTexGenivEXT");
	glMultiTexImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexImage1DEXT");
	glMultiTexImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexImage2DEXT");
	glMultiTexImage3DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexImage3DEXT");
	glMultiTexParameterIivEXT = (void (*)(GLenum, GLenum, GLenum, const GLint *) ) LoadProcAddress("glMultiTexParameterIivEXT");
	glMultiTexParameterIuivEXT = (void (*)(GLenum, GLenum, GLenum, const GLuint *) ) LoadProcAddress("glMultiTexParameterIuivEXT");
	glMultiTexParameterfEXT = (void (*)(GLenum, GLenum, GLenum, GLfloat) ) LoadProcAddress("glMultiTexParameterfEXT");
	glMultiTexParameterfvEXT = (void (*)(GLenum, GLenum, GLenum, const GLfloat *) ) LoadProcAddress("glMultiTexParameterfvEXT");
	glMultiTexParameteriEXT = (void (*)(GLenum, GLenum, GLenum, GLint) ) LoadProcAddress("glMultiTexParameteriEXT");
	glMultiTexParameterivEXT = (void (*)(GLenum, GLenum, GLenum, const GLint *) ) LoadProcAddress("glMultiTexParameterivEXT");
	glMultiTexRenderbufferEXT = (void (*)(GLenum, GLenum, GLuint) ) LoadProcAddress("glMultiTexRenderbufferEXT");
	glMultiTexSubImage1DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexSubImage1DEXT");
	glMultiTexSubImage2DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexSubImage2DEXT");
	glMultiTexSubImage3DEXT = (void (*)(GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glMultiTexSubImage3DEXT");
	glNamedBufferData = (void (*)(GLuint, GLsizei, const void *, GLenum) ) LoadProcAddress("glNamedBufferData");
	glNamedBufferDataEXT = (void (*)(GLuint, GLsizeiptr, const void *, GLenum) ) LoadProcAddress("glNamedBufferDataEXT");
	glNamedBufferPageCommitmentARB = (void (*)(GLuint, GLintptr, GLsizeiptr, GLboolean) ) LoadProcAddress("glNamedBufferPageCommitmentARB");
	glNamedBufferPageCommitmentEXT = (void (*)(GLuint, GLintptr, GLsizeiptr, GLboolean) ) LoadProcAddress("glNamedBufferPageCommitmentEXT");
	glNamedBufferStorage = (void (*)(GLuint, GLsizei, const void *, GLbitfield) ) LoadProcAddress("glNamedBufferStorage");
	glNamedBufferStorageEXT = (void (*)(GLuint, GLsizeiptr, const void *, GLbitfield) ) LoadProcAddress("glNamedBufferStorageEXT");
	glNamedBufferSubData = (void (*)(GLuint, GLintptr, GLsizei, const void *) ) LoadProcAddress("glNamedBufferSubData");
	glNamedBufferSubDataEXT = (void (*)(GLuint, GLintptr, GLsizeiptr, const void *) ) LoadProcAddress("glNamedBufferSubDataEXT");
	glNamedCopyBufferSubDataEXT = (void (*)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr) ) LoadProcAddress("glNamedCopyBufferSubDataEXT");
	glNamedFramebufferDrawBuffer = (void (*)(GLuint, GLenum) ) LoadProcAddress("glNamedFramebufferDrawBuffer");
	glNamedFramebufferDrawBuffers = (void (*)(GLuint, GLsizei, const GLenum *) ) LoadProcAddress("glNamedFramebufferDrawBuffers");
	glNamedFramebufferParameteri = (void (*)(GLuint, GLenum, GLint) ) LoadProcAddress("glNamedFramebufferParameteri");
	glNamedFramebufferParameteriEXT = (void (*)(GLuint, GLenum, GLint) ) LoadProcAddress("glNamedFramebufferParameteriEXT");
	glNamedFramebufferReadBuffer = (void (*)(GLuint, GLenum) ) LoadProcAddress("glNamedFramebufferReadBuffer");
	glNamedFramebufferRenderbuffer = (void (*)(GLuint, GLenum, GLenum, GLuint) ) LoadProcAddress("glNamedFramebufferRenderbuffer");
	glNamedFramebufferRenderbufferEXT = (void (*)(GLuint, GLenum, GLenum, GLuint) ) LoadProcAddress("glNamedFramebufferRenderbufferEXT");
	glNamedFramebufferTexture = (void (*)(GLuint, GLenum, GLuint, GLint) ) LoadProcAddress("glNamedFramebufferTexture");
	glNamedFramebufferTexture1DEXT = (void (*)(GLuint, GLenum, GLenum, GLuint, GLint) ) LoadProcAddress("glNamedFramebufferTexture1DEXT");
	glNamedFramebufferTexture2DEXT = (void (*)(GLuint, GLenum, GLenum, GLuint, GLint) ) LoadProcAddress("glNamedFramebufferTexture2DEXT");
	glNamedFramebufferTexture3DEXT = (void (*)(GLuint, GLenum, GLenum, GLuint, GLint, GLint) ) LoadProcAddress("glNamedFramebufferTexture3DEXT");
	glNamedFramebufferTextureEXT = (void (*)(GLuint, GLenum, GLuint, GLint) ) LoadProcAddress("glNamedFramebufferTextureEXT");
	glNamedFramebufferTextureFaceEXT = (void (*)(GLuint, GLenum, GLuint, GLint, GLenum) ) LoadProcAddress("glNamedFramebufferTextureFaceEXT");
	glNamedFramebufferTextureLayer = (void (*)(GLuint, GLenum, GLuint, GLint, GLint) ) LoadProcAddress("glNamedFramebufferTextureLayer");
	glNamedFramebufferTextureLayerEXT = (void (*)(GLuint, GLenum, GLuint, GLint, GLint) ) LoadProcAddress("glNamedFramebufferTextureLayerEXT");
	glNamedProgramLocalParameter4dEXT = (void (*)(GLuint, GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glNamedProgramLocalParameter4dEXT");
	glNamedProgramLocalParameter4dvEXT = (void (*)(GLuint, GLenum, GLuint, const GLdouble *) ) LoadProcAddress("glNamedProgramLocalParameter4dvEXT");
	glNamedProgramLocalParameter4fEXT = (void (*)(GLuint, GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glNamedProgramLocalParameter4fEXT");
	glNamedProgramLocalParameter4fvEXT = (void (*)(GLuint, GLenum, GLuint, const GLfloat *) ) LoadProcAddress("glNamedProgramLocalParameter4fvEXT");
	glNamedProgramLocalParameterI4iEXT = (void (*)(GLuint, GLenum, GLuint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glNamedProgramLocalParameterI4iEXT");
	glNamedProgramLocalParameterI4ivEXT = (void (*)(GLuint, GLenum, GLuint, const GLint *) ) LoadProcAddress("glNamedProgramLocalParameterI4ivEXT");
	glNamedProgramLocalParameterI4uiEXT = (void (*)(GLuint, GLenum, GLuint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glNamedProgramLocalParameterI4uiEXT");
	glNamedProgramLocalParameterI4uivEXT = (void (*)(GLuint, GLenum, GLuint, const GLuint *) ) LoadProcAddress("glNamedProgramLocalParameterI4uivEXT");
	glNamedProgramLocalParameters4fvEXT = (void (*)(GLuint, GLenum, GLuint, GLsizei, const GLfloat *) ) LoadProcAddress("glNamedProgramLocalParameters4fvEXT");
	glNamedProgramLocalParametersI4ivEXT = (void (*)(GLuint, GLenum, GLuint, GLsizei, const GLint *) ) LoadProcAddress("glNamedProgramLocalParametersI4ivEXT");
	glNamedProgramLocalParametersI4uivEXT = (void (*)(GLuint, GLenum, GLuint, GLsizei, const GLuint *) ) LoadProcAddress("glNamedProgramLocalParametersI4uivEXT");
	glNamedProgramStringEXT = (void (*)(GLuint, GLenum, GLenum, GLsizei, const void *) ) LoadProcAddress("glNamedProgramStringEXT");
	glNamedRenderbufferStorage = (void (*)(GLuint, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glNamedRenderbufferStorage");
	glNamedRenderbufferStorageEXT = (void (*)(GLuint, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glNamedRenderbufferStorageEXT");
	glNamedRenderbufferStorageMultisample = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glNamedRenderbufferStorageMultisample");
	glNamedRenderbufferStorageMultisampleCoverageEXT = (void (*)(GLuint, GLsizei, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glNamedRenderbufferStorageMultisampleCoverageEXT");
	glNamedRenderbufferStorageMultisampleEXT = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glNamedRenderbufferStorageMultisampleEXT");
	glNamedStringARB = (void (*)(GLenum, GLint, const GLchar *, GLint, const GLchar *) ) LoadProcAddress("glNamedStringARB");
	glObjectLabel = (void (*)(GLenum, GLuint, GLsizei, const GLchar *) ) LoadProcAddress("glObjectLabel");
	glObjectLabelKHR = (void (*)(GLenum, GLuint, GLsizei, const GLchar *) ) LoadProcAddress("glObjectLabelKHR");
	glObjectPtrLabel = (void (*)(const void *, GLsizei, const GLchar *) ) LoadProcAddress("glObjectPtrLabel");
	glObjectPtrLabelKHR = (void (*)(const void *, GLsizei, const GLchar *) ) LoadProcAddress("glObjectPtrLabelKHR");
	glPatchParameterfv = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glPatchParameterfv");
	glPatchParameteri = (void (*)(GLenum, GLint) ) LoadProcAddress("glPatchParameteri");
	glPauseTransformFeedback = (void (*)() ) LoadProcAddress("glPauseTransformFeedback");
	glPixelStoref = (void (*)(GLenum, GLfloat) ) LoadProcAddress("glPixelStoref");
	glPixelStorei = (void (*)(GLenum, GLint) ) LoadProcAddress("glPixelStorei");
	glPointParameterf = (void (*)(GLenum, GLfloat) ) LoadProcAddress("glPointParameterf");
	glPointParameterfv = (void (*)(GLenum, const GLfloat *) ) LoadProcAddress("glPointParameterfv");
	glPointParameteri = (void (*)(GLenum, GLint) ) LoadProcAddress("glPointParameteri");
	glPointParameteriv = (void (*)(GLenum, const GLint *) ) LoadProcAddress("glPointParameteriv");
	glPointSize = (void (*)(GLfloat) ) LoadProcAddress("glPointSize");
	glPolygonMode = (void (*)(GLenum, GLenum) ) LoadProcAddress("glPolygonMode");
	glPolygonOffset = (void (*)(GLfloat, GLfloat) ) LoadProcAddress("glPolygonOffset");
	glPopDebugGroup = (void (*)() ) LoadProcAddress("glPopDebugGroup");
	glPopDebugGroupKHR = (void (*)() ) LoadProcAddress("glPopDebugGroupKHR");
	glPrimitiveRestartIndex = (void (*)(GLuint) ) LoadProcAddress("glPrimitiveRestartIndex");
	glProgramBinary = (void (*)(GLuint, GLenum, const void *, GLsizei) ) LoadProcAddress("glProgramBinary");
	glProgramParameteri = (void (*)(GLuint, GLenum, GLint) ) LoadProcAddress("glProgramParameteri");
	glProgramUniform1d = (void (*)(GLuint, GLint, GLdouble) ) LoadProcAddress("glProgramUniform1d");
	glProgramUniform1dEXT = (void (*)(GLuint, GLint, GLdouble) ) LoadProcAddress("glProgramUniform1dEXT");
	glProgramUniform1dv = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform1dv");
	glProgramUniform1dvEXT = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform1dvEXT");
	glProgramUniform1f = (void (*)(GLuint, GLint, GLfloat) ) LoadProcAddress("glProgramUniform1f");
	glProgramUniform1fEXT = (void (*)(GLuint, GLint, GLfloat) ) LoadProcAddress("glProgramUniform1fEXT");
	glProgramUniform1fv = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform1fv");
	glProgramUniform1fvEXT = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform1fvEXT");
	glProgramUniform1i = (void (*)(GLuint, GLint, GLint) ) LoadProcAddress("glProgramUniform1i");
	glProgramUniform1iEXT = (void (*)(GLuint, GLint, GLint) ) LoadProcAddress("glProgramUniform1iEXT");
	glProgramUniform1iv = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform1iv");
	glProgramUniform1ivEXT = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform1ivEXT");
	glProgramUniform1ui = (void (*)(GLuint, GLint, GLuint) ) LoadProcAddress("glProgramUniform1ui");
	glProgramUniform1uiEXT = (void (*)(GLuint, GLint, GLuint) ) LoadProcAddress("glProgramUniform1uiEXT");
	glProgramUniform1uiv = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform1uiv");
	glProgramUniform1uivEXT = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform1uivEXT");
	glProgramUniform2d = (void (*)(GLuint, GLint, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform2d");
	glProgramUniform2dEXT = (void (*)(GLuint, GLint, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform2dEXT");
	glProgramUniform2dv = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform2dv");
	glProgramUniform2dvEXT = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform2dvEXT");
	glProgramUniform2f = (void (*)(GLuint, GLint, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform2f");
	glProgramUniform2fEXT = (void (*)(GLuint, GLint, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform2fEXT");
	glProgramUniform2fv = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform2fv");
	glProgramUniform2fvEXT = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform2fvEXT");
	glProgramUniform2i = (void (*)(GLuint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform2i");
	glProgramUniform2iEXT = (void (*)(GLuint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform2iEXT");
	glProgramUniform2iv = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform2iv");
	glProgramUniform2ivEXT = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform2ivEXT");
	glProgramUniform2ui = (void (*)(GLuint, GLint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform2ui");
	glProgramUniform2uiEXT = (void (*)(GLuint, GLint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform2uiEXT");
	glProgramUniform2uiv = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform2uiv");
	glProgramUniform2uivEXT = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform2uivEXT");
	glProgramUniform3d = (void (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform3d");
	glProgramUniform3dEXT = (void (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform3dEXT");
	glProgramUniform3dv = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform3dv");
	glProgramUniform3dvEXT = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform3dvEXT");
	glProgramUniform3f = (void (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform3f");
	glProgramUniform3fEXT = (void (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform3fEXT");
	glProgramUniform3fv = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform3fv");
	glProgramUniform3fvEXT = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform3fvEXT");
	glProgramUniform3i = (void (*)(GLuint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform3i");
	glProgramUniform3iEXT = (void (*)(GLuint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform3iEXT");
	glProgramUniform3iv = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform3iv");
	glProgramUniform3ivEXT = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform3ivEXT");
	glProgramUniform3ui = (void (*)(GLuint, GLint, GLuint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform3ui");
	glProgramUniform3uiEXT = (void (*)(GLuint, GLint, GLuint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform3uiEXT");
	glProgramUniform3uiv = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform3uiv");
	glProgramUniform3uivEXT = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform3uivEXT");
	glProgramUniform4d = (void (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform4d");
	glProgramUniform4dEXT = (void (*)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glProgramUniform4dEXT");
	glProgramUniform4dv = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform4dv");
	glProgramUniform4dvEXT = (void (*)(GLuint, GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glProgramUniform4dvEXT");
	glProgramUniform4f = (void (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform4f");
	glProgramUniform4fEXT = (void (*)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glProgramUniform4fEXT");
	glProgramUniform4fv = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform4fv");
	glProgramUniform4fvEXT = (void (*)(GLuint, GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glProgramUniform4fvEXT");
	glProgramUniform4i = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform4i");
	glProgramUniform4iEXT = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glProgramUniform4iEXT");
	glProgramUniform4iv = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform4iv");
	glProgramUniform4ivEXT = (void (*)(GLuint, GLint, GLsizei, const GLint *) ) LoadProcAddress("glProgramUniform4ivEXT");
	glProgramUniform4ui = (void (*)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform4ui");
	glProgramUniform4uiEXT = (void (*)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glProgramUniform4uiEXT");
	glProgramUniform4uiv = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform4uiv");
	glProgramUniform4uivEXT = (void (*)(GLuint, GLint, GLsizei, const GLuint *) ) LoadProcAddress("glProgramUniform4uivEXT");
	glProgramUniformHandleui64ARB = (void (*)(GLuint, GLint, GLuint64) ) LoadProcAddress("glProgramUniformHandleui64ARB");
	glProgramUniformHandleui64vARB = (void (*)(GLuint, GLint, GLsizei, const GLuint64 *) ) LoadProcAddress("glProgramUniformHandleui64vARB");
	glProgramUniformMatrix2dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2dv");
	glProgramUniformMatrix2dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2dvEXT");
	glProgramUniformMatrix2fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2fv");
	glProgramUniformMatrix2fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2fvEXT");
	glProgramUniformMatrix2x3dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2x3dv");
	glProgramUniformMatrix2x3dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2x3dvEXT");
	glProgramUniformMatrix2x3fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2x3fv");
	glProgramUniformMatrix2x3fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2x3fvEXT");
	glProgramUniformMatrix2x4dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2x4dv");
	glProgramUniformMatrix2x4dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix2x4dvEXT");
	glProgramUniformMatrix2x4fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2x4fv");
	glProgramUniformMatrix2x4fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix2x4fvEXT");
	glProgramUniformMatrix3dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3dv");
	glProgramUniformMatrix3dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3dvEXT");
	glProgramUniformMatrix3fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3fv");
	glProgramUniformMatrix3fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3fvEXT");
	glProgramUniformMatrix3x2dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3x2dv");
	glProgramUniformMatrix3x2dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3x2dvEXT");
	glProgramUniformMatrix3x2fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3x2fv");
	glProgramUniformMatrix3x2fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3x2fvEXT");
	glProgramUniformMatrix3x4dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3x4dv");
	glProgramUniformMatrix3x4dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix3x4dvEXT");
	glProgramUniformMatrix3x4fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3x4fv");
	glProgramUniformMatrix3x4fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix3x4fvEXT");
	glProgramUniformMatrix4dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4dv");
	glProgramUniformMatrix4dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4dvEXT");
	glProgramUniformMatrix4fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4fv");
	glProgramUniformMatrix4fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4fvEXT");
	glProgramUniformMatrix4x2dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4x2dv");
	glProgramUniformMatrix4x2dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4x2dvEXT");
	glProgramUniformMatrix4x2fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4x2fv");
	glProgramUniformMatrix4x2fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4x2fvEXT");
	glProgramUniformMatrix4x3dv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4x3dv");
	glProgramUniformMatrix4x3dvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glProgramUniformMatrix4x3dvEXT");
	glProgramUniformMatrix4x3fv = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4x3fv");
	glProgramUniformMatrix4x3fvEXT = (void (*)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glProgramUniformMatrix4x3fvEXT");
	glProvokingVertex = (void (*)(GLenum) ) LoadProcAddress("glProvokingVertex");
	glPushClientAttribDefaultEXT = (void (*)(GLbitfield) ) LoadProcAddress("glPushClientAttribDefaultEXT");
	glPushDebugGroup = (void (*)(GLenum, GLuint, GLsizei, const GLchar *) ) LoadProcAddress("glPushDebugGroup");
	glPushDebugGroupKHR = (void (*)(GLenum, GLuint, GLsizei, const GLchar *) ) LoadProcAddress("glPushDebugGroupKHR");
	glQueryCounter = (void (*)(GLuint, GLenum) ) LoadProcAddress("glQueryCounter");
	glReadBuffer = (void (*)(GLenum) ) LoadProcAddress("glReadBuffer");
	glReadPixels = (void (*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *) ) LoadProcAddress("glReadPixels");
	glReadnPixels = (void (*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glReadnPixels");
	glReadnPixelsARB = (void (*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glReadnPixelsARB");
	glReadnPixelsKHR = (void (*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *) ) LoadProcAddress("glReadnPixelsKHR");
	glReleaseShaderCompiler = (void (*)() ) LoadProcAddress("glReleaseShaderCompiler");
	glRenderbufferStorage = (void (*)(GLenum, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glRenderbufferStorage");
	glRenderbufferStorageMultisample = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glRenderbufferStorageMultisample");
	glResumeTransformFeedback = (void (*)() ) LoadProcAddress("glResumeTransformFeedback");
	glSampleCoverage = (void (*)(GLfloat, GLboolean) ) LoadProcAddress("glSampleCoverage");
	glSampleMaski = (void (*)(GLuint, GLbitfield) ) LoadProcAddress("glSampleMaski");
	glSamplerParameterIiv = (void (*)(GLuint, GLenum, const GLint *) ) LoadProcAddress("glSamplerParameterIiv");
	glSamplerParameterIuiv = (void (*)(GLuint, GLenum, const GLuint *) ) LoadProcAddress("glSamplerParameterIuiv");
	glSamplerParameterf = (void (*)(GLuint, GLenum, GLfloat) ) LoadProcAddress("glSamplerParameterf");
	glSamplerParameterfv = (void (*)(GLuint, GLenum, const GLfloat *) ) LoadProcAddress("glSamplerParameterfv");
	glSamplerParameteri = (void (*)(GLuint, GLenum, GLint) ) LoadProcAddress("glSamplerParameteri");
	glSamplerParameteriv = (void (*)(GLuint, GLenum, const GLint *) ) LoadProcAddress("glSamplerParameteriv");
	glScissor = (void (*)(GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glScissor");
	glScissorArrayv = (void (*)(GLuint, GLsizei, const GLint *) ) LoadProcAddress("glScissorArrayv");
	glScissorIndexed = (void (*)(GLuint, GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glScissorIndexed");
	glScissorIndexedv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glScissorIndexedv");
	glShaderBinary = (void (*)(GLsizei, const GLuint *, GLenum, const void *, GLsizei) ) LoadProcAddress("glShaderBinary");
	glShaderSource = (void (*)(GLuint, GLsizei, const GLchar *const*, const GLint *) ) LoadProcAddress("glShaderSource");
	glShaderStorageBlockBinding = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glShaderStorageBlockBinding");
	glStencilFunc = (void (*)(GLenum, GLint, GLuint) ) LoadProcAddress("glStencilFunc");
	glStencilFuncSeparate = (void (*)(GLenum, GLenum, GLint, GLuint) ) LoadProcAddress("glStencilFuncSeparate");
	glStencilMask = (void (*)(GLuint) ) LoadProcAddress("glStencilMask");
	glStencilMaskSeparate = (void (*)(GLenum, GLuint) ) LoadProcAddress("glStencilMaskSeparate");
	glStencilOp = (void (*)(GLenum, GLenum, GLenum) ) LoadProcAddress("glStencilOp");
	glStencilOpSeparate = (void (*)(GLenum, GLenum, GLenum, GLenum) ) LoadProcAddress("glStencilOpSeparate");
	glTexBuffer = (void (*)(GLenum, GLenum, GLuint) ) LoadProcAddress("glTexBuffer");
	glTexBufferRange = (void (*)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) ) LoadProcAddress("glTexBufferRange");
	glTexImage1D = (void (*)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTexImage1D");
	glTexImage2D = (void (*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTexImage2D");
	glTexImage2DMultisample = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexImage2DMultisample");
	glTexImage3D = (void (*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTexImage3D");
	glTexImage3DMultisample = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexImage3DMultisample");
	glTexPageCommitmentARB = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexPageCommitmentARB");
	glTexParameterIiv = (void (*)(GLenum, GLenum, const GLint *) ) LoadProcAddress("glTexParameterIiv");
	glTexParameterIuiv = (void (*)(GLenum, GLenum, const GLuint *) ) LoadProcAddress("glTexParameterIuiv");
	glTexParameterf = (void (*)(GLenum, GLenum, GLfloat) ) LoadProcAddress("glTexParameterf");
	glTexParameterfv = (void (*)(GLenum, GLenum, const GLfloat *) ) LoadProcAddress("glTexParameterfv");
	glTexParameteri = (void (*)(GLenum, GLenum, GLint) ) LoadProcAddress("glTexParameteri");
	glTexParameteriv = (void (*)(GLenum, GLenum, const GLint *) ) LoadProcAddress("glTexParameteriv");
	glTexStorage1D = (void (*)(GLenum, GLsizei, GLenum, GLsizei) ) LoadProcAddress("glTexStorage1D");
	glTexStorage2D = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glTexStorage2D");
	glTexStorage2DMultisample = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexStorage2DMultisample");
	glTexStorage3D = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glTexStorage3D");
	glTexStorage3DMultisample = (void (*)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexStorage3DMultisample");
	glTexSubImage1D = (void (*)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTexSubImage1D");
	glTexSubImage2D = (void (*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTexSubImage2D");
	glTexSubImage3D = (void (*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTexSubImage3D");
	glTextureBarrier = (void (*)() ) LoadProcAddress("glTextureBarrier");
	glTextureBuffer = (void (*)(GLuint, GLenum, GLuint) ) LoadProcAddress("glTextureBuffer");
	glTextureBufferEXT = (void (*)(GLuint, GLenum, GLenum, GLuint) ) LoadProcAddress("glTextureBufferEXT");
	glTextureBufferRange = (void (*)(GLuint, GLenum, GLuint, GLintptr, GLsizei) ) LoadProcAddress("glTextureBufferRange");
	glTextureBufferRangeEXT = (void (*)(GLuint, GLenum, GLenum, GLuint, GLintptr, GLsizeiptr) ) LoadProcAddress("glTextureBufferRangeEXT");
	glTextureImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureImage1DEXT");
	glTextureImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureImage2DEXT");
	glTextureImage3DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureImage3DEXT");
	glTexturePageCommitmentEXT = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTexturePageCommitmentEXT");
	glTextureParameterIiv = (void (*)(GLuint, GLenum, const GLint *) ) LoadProcAddress("glTextureParameterIiv");
	glTextureParameterIivEXT = (void (*)(GLuint, GLenum, GLenum, const GLint *) ) LoadProcAddress("glTextureParameterIivEXT");
	glTextureParameterIuiv = (void (*)(GLuint, GLenum, const GLuint *) ) LoadProcAddress("glTextureParameterIuiv");
	glTextureParameterIuivEXT = (void (*)(GLuint, GLenum, GLenum, const GLuint *) ) LoadProcAddress("glTextureParameterIuivEXT");
	glTextureParameterf = (void (*)(GLuint, GLenum, GLfloat) ) LoadProcAddress("glTextureParameterf");
	glTextureParameterfEXT = (void (*)(GLuint, GLenum, GLenum, GLfloat) ) LoadProcAddress("glTextureParameterfEXT");
	glTextureParameterfv = (void (*)(GLuint, GLenum, const GLfloat *) ) LoadProcAddress("glTextureParameterfv");
	glTextureParameterfvEXT = (void (*)(GLuint, GLenum, GLenum, const GLfloat *) ) LoadProcAddress("glTextureParameterfvEXT");
	glTextureParameteri = (void (*)(GLuint, GLenum, GLint) ) LoadProcAddress("glTextureParameteri");
	glTextureParameteriEXT = (void (*)(GLuint, GLenum, GLenum, GLint) ) LoadProcAddress("glTextureParameteriEXT");
	glTextureParameteriv = (void (*)(GLuint, GLenum, const GLint *) ) LoadProcAddress("glTextureParameteriv");
	glTextureParameterivEXT = (void (*)(GLuint, GLenum, GLenum, const GLint *) ) LoadProcAddress("glTextureParameterivEXT");
	glTextureRenderbufferEXT = (void (*)(GLuint, GLenum, GLuint) ) LoadProcAddress("glTextureRenderbufferEXT");
	glTextureStorage1D = (void (*)(GLuint, GLsizei, GLenum, GLsizei) ) LoadProcAddress("glTextureStorage1D");
	glTextureStorage1DEXT = (void (*)(GLuint, GLenum, GLsizei, GLenum, GLsizei) ) LoadProcAddress("glTextureStorage1DEXT");
	glTextureStorage2D = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glTextureStorage2D");
	glTextureStorage2DEXT = (void (*)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei) ) LoadProcAddress("glTextureStorage2DEXT");
	glTextureStorage2DMultisample = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTextureStorage2DMultisample");
	glTextureStorage2DMultisampleEXT = (void (*)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTextureStorage2DMultisampleEXT");
	glTextureStorage3D = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glTextureStorage3D");
	glTextureStorage3DEXT = (void (*)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei) ) LoadProcAddress("glTextureStorage3DEXT");
	glTextureStorage3DMultisample = (void (*)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTextureStorage3DMultisample");
	glTextureStorage3DMultisampleEXT = (void (*)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean) ) LoadProcAddress("glTextureStorage3DMultisampleEXT");
	glTextureSubImage1D = (void (*)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage1D");
	glTextureSubImage1DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage1DEXT");
	glTextureSubImage2D = (void (*)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage2D");
	glTextureSubImage2DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage2DEXT");
	glTextureSubImage3D = (void (*)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage3D");
	glTextureSubImage3DEXT = (void (*)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *) ) LoadProcAddress("glTextureSubImage3DEXT");
	glTextureView = (void (*)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glTextureView");
	glTransformFeedbackBufferBase = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glTransformFeedbackBufferBase");
	glTransformFeedbackBufferRange = (void (*)(GLuint, GLuint, GLuint, GLintptr, GLsizei) ) LoadProcAddress("glTransformFeedbackBufferRange");
	glTransformFeedbackVaryings = (void (*)(GLuint, GLsizei, const GLchar *const*, GLenum) ) LoadProcAddress("glTransformFeedbackVaryings");
	glUniform1d = (void (*)(GLint, GLdouble) ) LoadProcAddress("glUniform1d");
	glUniform1dv = (void (*)(GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glUniform1dv");
	glUniform1f = (void (*)(GLint, GLfloat) ) LoadProcAddress("glUniform1f");
	glUniform1fv = (void (*)(GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glUniform1fv");
	glUniform1i = (void (*)(GLint, GLint) ) LoadProcAddress("glUniform1i");
	glUniform1iv = (void (*)(GLint, GLsizei, const GLint *) ) LoadProcAddress("glUniform1iv");
	glUniform1ui = (void (*)(GLint, GLuint) ) LoadProcAddress("glUniform1ui");
	glUniform1uiv = (void (*)(GLint, GLsizei, const GLuint *) ) LoadProcAddress("glUniform1uiv");
	glUniform2d = (void (*)(GLint, GLdouble, GLdouble) ) LoadProcAddress("glUniform2d");
	glUniform2dv = (void (*)(GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glUniform2dv");
	glUniform2f = (void (*)(GLint, GLfloat, GLfloat) ) LoadProcAddress("glUniform2f");
	glUniform2fv = (void (*)(GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glUniform2fv");
	glUniform2i = (void (*)(GLint, GLint, GLint) ) LoadProcAddress("glUniform2i");
	glUniform2iv = (void (*)(GLint, GLsizei, const GLint *) ) LoadProcAddress("glUniform2iv");
	glUniform2ui = (void (*)(GLint, GLuint, GLuint) ) LoadProcAddress("glUniform2ui");
	glUniform2uiv = (void (*)(GLint, GLsizei, const GLuint *) ) LoadProcAddress("glUniform2uiv");
	glUniform3d = (void (*)(GLint, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glUniform3d");
	glUniform3dv = (void (*)(GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glUniform3dv");
	glUniform3f = (void (*)(GLint, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glUniform3f");
	glUniform3fv = (void (*)(GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glUniform3fv");
	glUniform3i = (void (*)(GLint, GLint, GLint, GLint) ) LoadProcAddress("glUniform3i");
	glUniform3iv = (void (*)(GLint, GLsizei, const GLint *) ) LoadProcAddress("glUniform3iv");
	glUniform3ui = (void (*)(GLint, GLuint, GLuint, GLuint) ) LoadProcAddress("glUniform3ui");
	glUniform3uiv = (void (*)(GLint, GLsizei, const GLuint *) ) LoadProcAddress("glUniform3uiv");
	glUniform4d = (void (*)(GLint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glUniform4d");
	glUniform4dv = (void (*)(GLint, GLsizei, const GLdouble *) ) LoadProcAddress("glUniform4dv");
	glUniform4f = (void (*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glUniform4f");
	glUniform4fv = (void (*)(GLint, GLsizei, const GLfloat *) ) LoadProcAddress("glUniform4fv");
	glUniform4i = (void (*)(GLint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glUniform4i");
	glUniform4iv = (void (*)(GLint, GLsizei, const GLint *) ) LoadProcAddress("glUniform4iv");
	glUniform4ui = (void (*)(GLint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glUniform4ui");
	glUniform4uiv = (void (*)(GLint, GLsizei, const GLuint *) ) LoadProcAddress("glUniform4uiv");
	glUniformBlockBinding = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glUniformBlockBinding");
	glUniformHandleui64ARB = (void (*)(GLint, GLuint64) ) LoadProcAddress("glUniformHandleui64ARB");
	glUniformHandleui64vARB = (void (*)(GLint, GLsizei, const GLuint64 *) ) LoadProcAddress("glUniformHandleui64vARB");
	glUniformMatrix2dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix2dv");
	glUniformMatrix2fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix2fv");
	glUniformMatrix2x3dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix2x3dv");
	glUniformMatrix2x3fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix2x3fv");
	glUniformMatrix2x4dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix2x4dv");
	glUniformMatrix2x4fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix2x4fv");
	glUniformMatrix3dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix3dv");
	glUniformMatrix3fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix3fv");
	glUniformMatrix3x2dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix3x2dv");
	glUniformMatrix3x2fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix3x2fv");
	glUniformMatrix3x4dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix3x4dv");
	glUniformMatrix3x4fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix3x4fv");
	glUniformMatrix4dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix4dv");
	glUniformMatrix4fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix4fv");
	glUniformMatrix4x2dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix4x2dv");
	glUniformMatrix4x2fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix4x2fv");
	glUniformMatrix4x3dv = (void (*)(GLint, GLsizei, GLboolean, const GLdouble *) ) LoadProcAddress("glUniformMatrix4x3dv");
	glUniformMatrix4x3fv = (void (*)(GLint, GLsizei, GLboolean, const GLfloat *) ) LoadProcAddress("glUniformMatrix4x3fv");
	glUniformSubroutinesuiv = (void (*)(GLenum, GLsizei, const GLuint *) ) LoadProcAddress("glUniformSubroutinesuiv");
	glUnmapBuffer = (GLboolean (*)(GLenum) ) LoadProcAddress("glUnmapBuffer");
	glUnmapNamedBuffer = (GLboolean (*)(GLuint) ) LoadProcAddress("glUnmapNamedBuffer");
	glUnmapNamedBufferEXT = (GLboolean (*)(GLuint) ) LoadProcAddress("glUnmapNamedBufferEXT");
	glUseProgram = (void (*)(GLuint) ) LoadProcAddress("glUseProgram");
	glUseProgramStages = (void (*)(GLuint, GLbitfield, GLuint) ) LoadProcAddress("glUseProgramStages");
	glValidateProgram = (void (*)(GLuint) ) LoadProcAddress("glValidateProgram");
	glValidateProgramPipeline = (void (*)(GLuint) ) LoadProcAddress("glValidateProgramPipeline");
	glVertexArrayAttribBinding = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexArrayAttribBinding");
	glVertexArrayAttribFormat = (void (*)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexArrayAttribFormat");
	glVertexArrayAttribIFormat = (void (*)(GLuint, GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexArrayAttribIFormat");
	glVertexArrayAttribLFormat = (void (*)(GLuint, GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexArrayAttribLFormat");
	glVertexArrayBindVertexBufferEXT = (void (*)(GLuint, GLuint, GLuint, GLintptr, GLsizei) ) LoadProcAddress("glVertexArrayBindVertexBufferEXT");
	glVertexArrayBindingDivisor = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexArrayBindingDivisor");
	glVertexArrayColorOffsetEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayColorOffsetEXT");
	glVertexArrayEdgeFlagOffsetEXT = (void (*)(GLuint, GLuint, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayEdgeFlagOffsetEXT");
	glVertexArrayElementBuffer = (void (*)(GLuint, GLuint) ) LoadProcAddress("glVertexArrayElementBuffer");
	glVertexArrayFogCoordOffsetEXT = (void (*)(GLuint, GLuint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayFogCoordOffsetEXT");
	glVertexArrayIndexOffsetEXT = (void (*)(GLuint, GLuint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayIndexOffsetEXT");
	glVertexArrayMultiTexCoordOffsetEXT = (void (*)(GLuint, GLuint, GLenum, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayMultiTexCoordOffsetEXT");
	glVertexArrayNormalOffsetEXT = (void (*)(GLuint, GLuint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayNormalOffsetEXT");
	glVertexArraySecondaryColorOffsetEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArraySecondaryColorOffsetEXT");
	glVertexArrayTexCoordOffsetEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayTexCoordOffsetEXT");
	glVertexArrayVertexAttribBindingEXT = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexArrayVertexAttribBindingEXT");
	glVertexArrayVertexAttribDivisorEXT = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexArrayVertexAttribDivisorEXT");
	glVertexArrayVertexAttribFormatEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexArrayVertexAttribFormatEXT");
	glVertexArrayVertexAttribIFormatEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexArrayVertexAttribIFormatEXT");
	glVertexArrayVertexAttribIOffsetEXT = (void (*)(GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayVertexAttribIOffsetEXT");
	glVertexArrayVertexAttribLFormatEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexArrayVertexAttribLFormatEXT");
	glVertexArrayVertexAttribLOffsetEXT = (void (*)(GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayVertexAttribLOffsetEXT");
	glVertexArrayVertexAttribOffsetEXT = (void (*)(GLuint, GLuint, GLuint, GLint, GLenum, GLboolean, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayVertexAttribOffsetEXT");
	glVertexArrayVertexBindingDivisorEXT = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexArrayVertexBindingDivisorEXT");
	glVertexArrayVertexBuffer = (void (*)(GLuint, GLuint, GLuint, GLintptr, GLsizei) ) LoadProcAddress("glVertexArrayVertexBuffer");
	glVertexArrayVertexBuffers = (void (*)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *) ) LoadProcAddress("glVertexArrayVertexBuffers");
	glVertexArrayVertexOffsetEXT = (void (*)(GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr) ) LoadProcAddress("glVertexArrayVertexOffsetEXT");
	glVertexAttrib1d = (void (*)(GLuint, GLdouble) ) LoadProcAddress("glVertexAttrib1d");
	glVertexAttrib1dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttrib1dv");
	glVertexAttrib1f = (void (*)(GLuint, GLfloat) ) LoadProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (void (*)(GLuint, const GLfloat *) ) LoadProcAddress("glVertexAttrib1fv");
	glVertexAttrib1s = (void (*)(GLuint, GLshort) ) LoadProcAddress("glVertexAttrib1s");
	glVertexAttrib1sv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttrib1sv");
	glVertexAttrib2d = (void (*)(GLuint, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttrib2d");
	glVertexAttrib2dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttrib2dv");
	glVertexAttrib2f = (void (*)(GLuint, GLfloat, GLfloat) ) LoadProcAddress("glVertexAttrib2f");
	glVertexAttrib2fv = (void (*)(GLuint, const GLfloat *) ) LoadProcAddress("glVertexAttrib2fv");
	glVertexAttrib2s = (void (*)(GLuint, GLshort, GLshort) ) LoadProcAddress("glVertexAttrib2s");
	glVertexAttrib2sv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttrib2sv");
	glVertexAttrib3d = (void (*)(GLuint, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttrib3d");
	glVertexAttrib3dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttrib3dv");
	glVertexAttrib3f = (void (*)(GLuint, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glVertexAttrib3f");
	glVertexAttrib3fv = (void (*)(GLuint, const GLfloat *) ) LoadProcAddress("glVertexAttrib3fv");
	glVertexAttrib3s = (void (*)(GLuint, GLshort, GLshort, GLshort) ) LoadProcAddress("glVertexAttrib3s");
	glVertexAttrib3sv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttrib3sv");
	glVertexAttrib4Nbv = (void (*)(GLuint, const GLbyte *) ) LoadProcAddress("glVertexAttrib4Nbv");
	glVertexAttrib4Niv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttrib4Niv");
	glVertexAttrib4Nsv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttrib4Nsv");
	glVertexAttrib4Nub = (void (*)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte) ) LoadProcAddress("glVertexAttrib4Nub");
	glVertexAttrib4Nubv = (void (*)(GLuint, const GLubyte *) ) LoadProcAddress("glVertexAttrib4Nubv");
	glVertexAttrib4Nuiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttrib4Nuiv");
	glVertexAttrib4Nusv = (void (*)(GLuint, const GLushort *) ) LoadProcAddress("glVertexAttrib4Nusv");
	glVertexAttrib4bv = (void (*)(GLuint, const GLbyte *) ) LoadProcAddress("glVertexAttrib4bv");
	glVertexAttrib4d = (void (*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttrib4d");
	glVertexAttrib4dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttrib4dv");
	glVertexAttrib4f = (void (*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glVertexAttrib4f");
	glVertexAttrib4fv = (void (*)(GLuint, const GLfloat *) ) LoadProcAddress("glVertexAttrib4fv");
	glVertexAttrib4iv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttrib4iv");
	glVertexAttrib4s = (void (*)(GLuint, GLshort, GLshort, GLshort, GLshort) ) LoadProcAddress("glVertexAttrib4s");
	glVertexAttrib4sv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttrib4sv");
	glVertexAttrib4ubv = (void (*)(GLuint, const GLubyte *) ) LoadProcAddress("glVertexAttrib4ubv");
	glVertexAttrib4uiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttrib4uiv");
	glVertexAttrib4usv = (void (*)(GLuint, const GLushort *) ) LoadProcAddress("glVertexAttrib4usv");
	glVertexAttribBinding = (void (*)(GLuint, GLuint) ) LoadProcAddress("glVertexAttribBinding");
	glVertexAttribDivisor = (void (*)(GLuint, GLuint) ) LoadProcAddress("glVertexAttribDivisor");
	glVertexAttribFormat = (void (*)(GLuint, GLint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexAttribFormat");
	glVertexAttribI1i = (void (*)(GLuint, GLint) ) LoadProcAddress("glVertexAttribI1i");
	glVertexAttribI1iv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttribI1iv");
	glVertexAttribI1ui = (void (*)(GLuint, GLuint) ) LoadProcAddress("glVertexAttribI1ui");
	glVertexAttribI1uiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttribI1uiv");
	glVertexAttribI2i = (void (*)(GLuint, GLint, GLint) ) LoadProcAddress("glVertexAttribI2i");
	glVertexAttribI2iv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttribI2iv");
	glVertexAttribI2ui = (void (*)(GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexAttribI2ui");
	glVertexAttribI2uiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttribI2uiv");
	glVertexAttribI3i = (void (*)(GLuint, GLint, GLint, GLint) ) LoadProcAddress("glVertexAttribI3i");
	glVertexAttribI3iv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttribI3iv");
	glVertexAttribI3ui = (void (*)(GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexAttribI3ui");
	glVertexAttribI3uiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttribI3uiv");
	glVertexAttribI4bv = (void (*)(GLuint, const GLbyte *) ) LoadProcAddress("glVertexAttribI4bv");
	glVertexAttribI4i = (void (*)(GLuint, GLint, GLint, GLint, GLint) ) LoadProcAddress("glVertexAttribI4i");
	glVertexAttribI4iv = (void (*)(GLuint, const GLint *) ) LoadProcAddress("glVertexAttribI4iv");
	glVertexAttribI4sv = (void (*)(GLuint, const GLshort *) ) LoadProcAddress("glVertexAttribI4sv");
	glVertexAttribI4ubv = (void (*)(GLuint, const GLubyte *) ) LoadProcAddress("glVertexAttribI4ubv");
	glVertexAttribI4ui = (void (*)(GLuint, GLuint, GLuint, GLuint, GLuint) ) LoadProcAddress("glVertexAttribI4ui");
	glVertexAttribI4uiv = (void (*)(GLuint, const GLuint *) ) LoadProcAddress("glVertexAttribI4uiv");
	glVertexAttribI4usv = (void (*)(GLuint, const GLushort *) ) LoadProcAddress("glVertexAttribI4usv");
	glVertexAttribIFormat = (void (*)(GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexAttribIFormat");
	glVertexAttribIPointer = (void (*)(GLuint, GLint, GLenum, GLsizei, const void *) ) LoadProcAddress("glVertexAttribIPointer");
	glVertexAttribL1d = (void (*)(GLuint, GLdouble) ) LoadProcAddress("glVertexAttribL1d");
	glVertexAttribL1dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttribL1dv");
	glVertexAttribL1ui64ARB = (void (*)(GLuint, GLuint64EXT) ) LoadProcAddress("glVertexAttribL1ui64ARB");
	glVertexAttribL1ui64vARB = (void (*)(GLuint, const GLuint64EXT *) ) LoadProcAddress("glVertexAttribL1ui64vARB");
	glVertexAttribL2d = (void (*)(GLuint, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttribL2d");
	glVertexAttribL2dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttribL2dv");
	glVertexAttribL3d = (void (*)(GLuint, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttribL3d");
	glVertexAttribL3dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttribL3dv");
	glVertexAttribL4d = (void (*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble) ) LoadProcAddress("glVertexAttribL4d");
	glVertexAttribL4dv = (void (*)(GLuint, const GLdouble *) ) LoadProcAddress("glVertexAttribL4dv");
	glVertexAttribLFormat = (void (*)(GLuint, GLint, GLenum, GLuint) ) LoadProcAddress("glVertexAttribLFormat");
	glVertexAttribLPointer = (void (*)(GLuint, GLint, GLenum, GLsizei, const void *) ) LoadProcAddress("glVertexAttribLPointer");
	glVertexAttribP1ui = (void (*)(GLuint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexAttribP1ui");
	glVertexAttribP1uiv = (void (*)(GLuint, GLenum, GLboolean, const GLuint *) ) LoadProcAddress("glVertexAttribP1uiv");
	glVertexAttribP2ui = (void (*)(GLuint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexAttribP2ui");
	glVertexAttribP2uiv = (void (*)(GLuint, GLenum, GLboolean, const GLuint *) ) LoadProcAddress("glVertexAttribP2uiv");
	glVertexAttribP3ui = (void (*)(GLuint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexAttribP3ui");
	glVertexAttribP3uiv = (void (*)(GLuint, GLenum, GLboolean, const GLuint *) ) LoadProcAddress("glVertexAttribP3uiv");
	glVertexAttribP4ui = (void (*)(GLuint, GLenum, GLboolean, GLuint) ) LoadProcAddress("glVertexAttribP4ui");
	glVertexAttribP4uiv = (void (*)(GLuint, GLenum, GLboolean, const GLuint *) ) LoadProcAddress("glVertexAttribP4uiv");
	glVertexAttribPointer = (void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *) ) LoadProcAddress("glVertexAttribPointer");
	glVertexBindingDivisor = (void (*)(GLuint, GLuint) ) LoadProcAddress("glVertexBindingDivisor");
	glViewport = (void (*)(GLint, GLint, GLsizei, GLsizei) ) LoadProcAddress("glViewport");
	glViewportArrayv = (void (*)(GLuint, GLsizei, const GLfloat *) ) LoadProcAddress("glViewportArrayv");
	glViewportIndexedf = (void (*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat) ) LoadProcAddress("glViewportIndexedf");
	glViewportIndexedfv = (void (*)(GLuint, const GLfloat *) ) LoadProcAddress("glViewportIndexedfv");
	glWaitSync = (void (*)(GLsync, GLbitfield, GLuint64) ) LoadProcAddress("glWaitSync");
	
	if (!glGetIntegerv || !glGetStringi) return false;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
	glGetIntegerv(GL_MAJOR_VERSION, &actual_maj);
	glGetIntegerv(GL_MINOR_VERSION, &actual_min);
	actual_version = actual_maj * 10 + actual_min;
	if (actual_version < req_version) return false;
	for (i = 0; i < num_extensions; i++) {
		const char *extname = (const char *)glGetStringi(GL_EXTENSIONS, i);
		if (!strcmp(extname, "GL_ARB_ES2_compatibility")) {
			GLPLATFORM_GL_ARB_ES2_compatibility = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_ES3_1_compatibility")) {
			GLPLATFORM_GL_ARB_ES3_1_compatibility = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_ES3_compatibility")) {
			GLPLATFORM_GL_ARB_ES3_compatibility = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_arrays_of_arrays")) {
			GLPLATFORM_GL_ARB_arrays_of_arrays = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_base_instance")) {
			GLPLATFORM_GL_ARB_base_instance = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_bindless_texture")) {
			GLPLATFORM_GL_ARB_bindless_texture = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_blend_func_extended")) {
			GLPLATFORM_GL_ARB_blend_func_extended = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_buffer_storage")) {
			GLPLATFORM_GL_ARB_buffer_storage = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_cl_event")) {
			GLPLATFORM_GL_ARB_cl_event = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_clear_buffer_object")) {
			GLPLATFORM_GL_ARB_clear_buffer_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_clear_texture")) {
			GLPLATFORM_GL_ARB_clear_texture = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_clip_control")) {
			GLPLATFORM_GL_ARB_clip_control = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_compressed_texture_pixel_storage")) {
			GLPLATFORM_GL_ARB_compressed_texture_pixel_storage = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_compute_shader")) {
			GLPLATFORM_GL_ARB_compute_shader = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_compute_variable_group_size")) {
			GLPLATFORM_GL_ARB_compute_variable_group_size = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_conditional_render_inverted")) {
			GLPLATFORM_GL_ARB_conditional_render_inverted = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_conservative_depth")) {
			GLPLATFORM_GL_ARB_conservative_depth = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_copy_buffer")) {
			GLPLATFORM_GL_ARB_copy_buffer = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_copy_image")) {
			GLPLATFORM_GL_ARB_copy_image = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_cull_distance")) {
			GLPLATFORM_GL_ARB_cull_distance = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_debug_output")) {
			GLPLATFORM_GL_ARB_debug_output = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_depth_buffer_float")) {
			GLPLATFORM_GL_ARB_depth_buffer_float = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_depth_clamp")) {
			GLPLATFORM_GL_ARB_depth_clamp = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_derivative_control")) {
			GLPLATFORM_GL_ARB_derivative_control = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_direct_state_access")) {
			GLPLATFORM_GL_ARB_direct_state_access = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_draw_buffers_blend")) {
			GLPLATFORM_GL_ARB_draw_buffers_blend = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_draw_elements_base_vertex")) {
			GLPLATFORM_GL_ARB_draw_elements_base_vertex = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_draw_indirect")) {
			GLPLATFORM_GL_ARB_draw_indirect = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_enhanced_layouts")) {
			GLPLATFORM_GL_ARB_enhanced_layouts = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_explicit_attrib_location")) {
			GLPLATFORM_GL_ARB_explicit_attrib_location = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_explicit_uniform_location")) {
			GLPLATFORM_GL_ARB_explicit_uniform_location = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_fragment_coord_conventions")) {
			GLPLATFORM_GL_ARB_fragment_coord_conventions = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_fragment_layer_viewport")) {
			GLPLATFORM_GL_ARB_fragment_layer_viewport = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_framebuffer_no_attachments")) {
			GLPLATFORM_GL_ARB_framebuffer_no_attachments = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_framebuffer_object")) {
			GLPLATFORM_GL_ARB_framebuffer_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_framebuffer_sRGB")) {
			GLPLATFORM_GL_ARB_framebuffer_sRGB = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_get_program_binary")) {
			GLPLATFORM_GL_ARB_get_program_binary = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_get_texture_sub_image")) {
			GLPLATFORM_GL_ARB_get_texture_sub_image = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_gpu_shader5")) {
			GLPLATFORM_GL_ARB_gpu_shader5 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_gpu_shader_fp64")) {
			GLPLATFORM_GL_ARB_gpu_shader_fp64 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_half_float_vertex")) {
			GLPLATFORM_GL_ARB_half_float_vertex = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_imaging")) {
			GLPLATFORM_GL_ARB_imaging = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_indirect_parameters")) {
			GLPLATFORM_GL_ARB_indirect_parameters = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_internalformat_query")) {
			GLPLATFORM_GL_ARB_internalformat_query = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_internalformat_query2")) {
			GLPLATFORM_GL_ARB_internalformat_query2 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_invalidate_subdata")) {
			GLPLATFORM_GL_ARB_invalidate_subdata = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_map_buffer_alignment")) {
			GLPLATFORM_GL_ARB_map_buffer_alignment = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_map_buffer_range")) {
			GLPLATFORM_GL_ARB_map_buffer_range = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_multi_bind")) {
			GLPLATFORM_GL_ARB_multi_bind = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_multi_draw_indirect")) {
			GLPLATFORM_GL_ARB_multi_draw_indirect = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_occlusion_query2")) {
			GLPLATFORM_GL_ARB_occlusion_query2 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_pipeline_statistics_query")) {
			GLPLATFORM_GL_ARB_pipeline_statistics_query = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_program_interface_query")) {
			GLPLATFORM_GL_ARB_program_interface_query = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_provoking_vertex")) {
			GLPLATFORM_GL_ARB_provoking_vertex = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_query_buffer_object")) {
			GLPLATFORM_GL_ARB_query_buffer_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_robust_buffer_access_behavior")) {
			GLPLATFORM_GL_ARB_robust_buffer_access_behavior = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_robustness")) {
			GLPLATFORM_GL_ARB_robustness = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_robustness_isolation")) {
			GLPLATFORM_GL_ARB_robustness_isolation = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_sample_shading")) {
			GLPLATFORM_GL_ARB_sample_shading = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_sampler_objects")) {
			GLPLATFORM_GL_ARB_sampler_objects = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_seamless_cube_map")) {
			GLPLATFORM_GL_ARB_seamless_cube_map = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_seamless_cubemap_per_texture")) {
			GLPLATFORM_GL_ARB_seamless_cubemap_per_texture = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_separate_shader_objects")) {
			GLPLATFORM_GL_ARB_separate_shader_objects = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_atomic_counters")) {
			GLPLATFORM_GL_ARB_shader_atomic_counters = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_bit_encoding")) {
			GLPLATFORM_GL_ARB_shader_bit_encoding = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_draw_parameters")) {
			GLPLATFORM_GL_ARB_shader_draw_parameters = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_group_vote")) {
			GLPLATFORM_GL_ARB_shader_group_vote = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_image_load_store")) {
			GLPLATFORM_GL_ARB_shader_image_load_store = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_image_size")) {
			GLPLATFORM_GL_ARB_shader_image_size = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_precision")) {
			GLPLATFORM_GL_ARB_shader_precision = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_stencil_export")) {
			GLPLATFORM_GL_ARB_shader_stencil_export = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_storage_buffer_object")) {
			GLPLATFORM_GL_ARB_shader_storage_buffer_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_subroutine")) {
			GLPLATFORM_GL_ARB_shader_subroutine = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shader_texture_image_samples")) {
			GLPLATFORM_GL_ARB_shader_texture_image_samples = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shading_language_420pack")) {
			GLPLATFORM_GL_ARB_shading_language_420pack = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shading_language_include")) {
			GLPLATFORM_GL_ARB_shading_language_include = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_shading_language_packing")) {
			GLPLATFORM_GL_ARB_shading_language_packing = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_sparse_buffer")) {
			GLPLATFORM_GL_ARB_sparse_buffer = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_sparse_texture")) {
			GLPLATFORM_GL_ARB_sparse_texture = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_stencil_texturing")) {
			GLPLATFORM_GL_ARB_stencil_texturing = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_sync")) {
			GLPLATFORM_GL_ARB_sync = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_tessellation_shader")) {
			GLPLATFORM_GL_ARB_tessellation_shader = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_barrier")) {
			GLPLATFORM_GL_ARB_texture_barrier = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_buffer_object_rgb32")) {
			GLPLATFORM_GL_ARB_texture_buffer_object_rgb32 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_buffer_range")) {
			GLPLATFORM_GL_ARB_texture_buffer_range = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_compression_bptc")) {
			GLPLATFORM_GL_ARB_texture_compression_bptc = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_compression_rgtc")) {
			GLPLATFORM_GL_ARB_texture_compression_rgtc = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_cube_map_array")) {
			GLPLATFORM_GL_ARB_texture_cube_map_array = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_gather")) {
			GLPLATFORM_GL_ARB_texture_gather = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_mirror_clamp_to_edge")) {
			GLPLATFORM_GL_ARB_texture_mirror_clamp_to_edge = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_multisample")) {
			GLPLATFORM_GL_ARB_texture_multisample = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_query_levels")) {
			GLPLATFORM_GL_ARB_texture_query_levels = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_query_lod")) {
			GLPLATFORM_GL_ARB_texture_query_lod = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_rg")) {
			GLPLATFORM_GL_ARB_texture_rg = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_rgb10_a2ui")) {
			GLPLATFORM_GL_ARB_texture_rgb10_a2ui = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_stencil8")) {
			GLPLATFORM_GL_ARB_texture_stencil8 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_storage")) {
			GLPLATFORM_GL_ARB_texture_storage = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_storage_multisample")) {
			GLPLATFORM_GL_ARB_texture_storage_multisample = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_swizzle")) {
			GLPLATFORM_GL_ARB_texture_swizzle = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_texture_view")) {
			GLPLATFORM_GL_ARB_texture_view = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_timer_query")) {
			GLPLATFORM_GL_ARB_timer_query = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_transform_feedback2")) {
			GLPLATFORM_GL_ARB_transform_feedback2 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_transform_feedback3")) {
			GLPLATFORM_GL_ARB_transform_feedback3 = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_transform_feedback_instanced")) {
			GLPLATFORM_GL_ARB_transform_feedback_instanced = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_transform_feedback_overflow_query")) {
			GLPLATFORM_GL_ARB_transform_feedback_overflow_query = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_uniform_buffer_object")) {
			GLPLATFORM_GL_ARB_uniform_buffer_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_array_bgra")) {
			GLPLATFORM_GL_ARB_vertex_array_bgra = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_array_object")) {
			GLPLATFORM_GL_ARB_vertex_array_object = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_attrib_64bit")) {
			GLPLATFORM_GL_ARB_vertex_attrib_64bit = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_attrib_binding")) {
			GLPLATFORM_GL_ARB_vertex_attrib_binding = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_type_10f_11f_11f_rev")) {
			GLPLATFORM_GL_ARB_vertex_type_10f_11f_11f_rev = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_vertex_type_2_10_10_10_rev")) {
			GLPLATFORM_GL_ARB_vertex_type_2_10_10_10_rev = true;
			continue;
		}
		if (!strcmp(extname, "GL_ARB_viewport_array")) {
			GLPLATFORM_GL_ARB_viewport_array = true;
			continue;
		}
		if (!strcmp(extname, "GL_EXT_direct_state_access")) {
			GLPLATFORM_GL_EXT_direct_state_access = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_context_flush_control")) {
			GLPLATFORM_GL_KHR_context_flush_control = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_debug")) {
			GLPLATFORM_GL_KHR_debug = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_robust_buffer_access_behavior")) {
			GLPLATFORM_GL_KHR_robust_buffer_access_behavior = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_robustness")) {
			GLPLATFORM_GL_KHR_robustness = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_texture_compression_astc_hdr")) {
			GLPLATFORM_GL_KHR_texture_compression_astc_hdr = true;
			continue;
		}
		if (!strcmp(extname, "GL_KHR_texture_compression_astc_ldr")) {
			GLPLATFORM_GL_KHR_texture_compression_astc_ldr = true;
			continue;
		}
	}
	
	GLPLATFORM_GL_ARB_ES2_compatibility = GLPLATFORM_GL_ARB_ES2_compatibility && glClearDepthf && glDepthRangef
		 && glGetShaderPrecisionFormat && glReleaseShaderCompiler && glShaderBinary;
	
	GLPLATFORM_GL_ARB_ES3_1_compatibility = GLPLATFORM_GL_ARB_ES3_1_compatibility && glMemoryBarrierByRegion;
	
	GLPLATFORM_GL_ARB_base_instance = GLPLATFORM_GL_ARB_base_instance && glDrawArraysInstancedBaseInstance && glDrawElementsInstancedBaseInstance
		 && glDrawElementsInstancedBaseVertexBaseInstance;
	
	GLPLATFORM_GL_ARB_bindless_texture = GLPLATFORM_GL_ARB_bindless_texture && glGetImageHandleARB && glGetTextureHandleARB
		 && glGetTextureSamplerHandleARB && glGetVertexAttribLui64vARB && glIsImageHandleResidentARB
		 && glIsTextureHandleResidentARB && glMakeImageHandleNonResidentARB && glMakeImageHandleResidentARB
		 && glMakeTextureHandleNonResidentARB && glMakeTextureHandleResidentARB && glProgramUniformHandleui64ARB
		 && glProgramUniformHandleui64vARB && glUniformHandleui64ARB && glUniformHandleui64vARB
		 && glVertexAttribL1ui64ARB && glVertexAttribL1ui64vARB;
	
	GLPLATFORM_GL_ARB_blend_func_extended = GLPLATFORM_GL_ARB_blend_func_extended && glBindFragDataLocationIndexed && glGetFragDataIndex;
	
	GLPLATFORM_GL_ARB_buffer_storage = GLPLATFORM_GL_ARB_buffer_storage && glBufferStorage;
	
	GLPLATFORM_GL_ARB_cl_event = GLPLATFORM_GL_ARB_cl_event && glCreateSyncFromCLeventARB;
	
	GLPLATFORM_GL_ARB_clear_buffer_object = GLPLATFORM_GL_ARB_clear_buffer_object && glClearBufferData && glClearBufferSubData;
	
	GLPLATFORM_GL_ARB_clear_texture = GLPLATFORM_GL_ARB_clear_texture && glClearTexImage && glClearTexSubImage;
	
	GLPLATFORM_GL_ARB_clip_control = GLPLATFORM_GL_ARB_clip_control && glClipControl;
	
	GLPLATFORM_GL_ARB_compute_shader = GLPLATFORM_GL_ARB_compute_shader && glDispatchCompute && glDispatchComputeIndirect;
	
	GLPLATFORM_GL_ARB_compute_variable_group_size = GLPLATFORM_GL_ARB_compute_variable_group_size && glDispatchComputeGroupSizeARB;
	
	GLPLATFORM_GL_ARB_copy_buffer = GLPLATFORM_GL_ARB_copy_buffer && glCopyBufferSubData;
	
	GLPLATFORM_GL_ARB_copy_image = GLPLATFORM_GL_ARB_copy_image && glCopyImageSubData;
	
	GLPLATFORM_GL_ARB_debug_output = GLPLATFORM_GL_ARB_debug_output && glDebugMessageCallbackARB && glDebugMessageControlARB
		 && glDebugMessageInsertARB && glGetDebugMessageLogARB;
	
	GLPLATFORM_GL_ARB_direct_state_access = GLPLATFORM_GL_ARB_direct_state_access && glBindTextureUnit && glBlitNamedFramebuffer
		 && glCheckNamedFramebufferStatus && glClearNamedBufferData && glClearNamedBufferSubData
		 && glClearNamedFramebufferfi && glClearNamedFramebufferfv && glClearNamedFramebufferiv
		 && glClearNamedFramebufferuiv && glCompressedTextureSubImage1D && glCompressedTextureSubImage2D
		 && glCompressedTextureSubImage3D && glCopyNamedBufferSubData && glCopyTextureSubImage1D
		 && glCopyTextureSubImage2D && glCopyTextureSubImage3D && glCreateBuffers
		 && glCreateFramebuffers && glCreateProgramPipelines && glCreateQueries
		 && glCreateRenderbuffers && glCreateSamplers && glCreateTextures
		 && glCreateTransformFeedbacks && glCreateVertexArrays && glDisableVertexArrayAttrib
		 && glEnableVertexArrayAttrib && glFlushMappedNamedBufferRange && glGenerateTextureMipmap
		 && glGetCompressedTextureImage && glGetNamedBufferParameteri64v && glGetNamedBufferParameteriv
		 && glGetNamedBufferPointerv && glGetNamedBufferSubData && glGetNamedFramebufferAttachmentParameteriv
		 && glGetNamedFramebufferParameteriv && glGetNamedRenderbufferParameteriv && glGetQueryBufferObjecti64v
		 && glGetQueryBufferObjectiv && glGetQueryBufferObjectui64v && glGetQueryBufferObjectuiv
		 && glGetTextureImage && glGetTextureLevelParameterfv && glGetTextureLevelParameteriv
		 && glGetTextureParameterIiv && glGetTextureParameterIuiv && glGetTextureParameterfv
		 && glGetTextureParameteriv && glGetTransformFeedbacki64_v && glGetTransformFeedbacki_v
		 && glGetTransformFeedbackiv && glGetVertexArrayIndexed64iv && glGetVertexArrayIndexediv
		 && glGetVertexArrayiv && glInvalidateNamedFramebufferData && glInvalidateNamedFramebufferSubData
		 && glMapNamedBuffer && glMapNamedBufferRange && glNamedBufferData
		 && glNamedBufferStorage && glNamedBufferSubData && glNamedFramebufferDrawBuffer
		 && glNamedFramebufferDrawBuffers && glNamedFramebufferParameteri && glNamedFramebufferReadBuffer
		 && glNamedFramebufferRenderbuffer && glNamedFramebufferTexture && glNamedFramebufferTextureLayer
		 && glNamedRenderbufferStorage && glNamedRenderbufferStorageMultisample && glTextureBuffer
		 && glTextureBufferRange && glTextureParameterIiv && glTextureParameterIuiv
		 && glTextureParameterf && glTextureParameterfv && glTextureParameteri
		 && glTextureParameteriv && glTextureStorage1D && glTextureStorage2D
		 && glTextureStorage2DMultisample && glTextureStorage3D && glTextureStorage3DMultisample
		 && glTextureSubImage1D && glTextureSubImage2D && glTextureSubImage3D
		 && glTransformFeedbackBufferBase && glTransformFeedbackBufferRange && glUnmapNamedBuffer
		 && glVertexArrayAttribBinding && glVertexArrayAttribFormat && glVertexArrayAttribIFormat
		 && glVertexArrayAttribLFormat && glVertexArrayBindingDivisor && glVertexArrayElementBuffer
		 && glVertexArrayVertexBuffer && glVertexArrayVertexBuffers;
	
	GLPLATFORM_GL_ARB_draw_buffers_blend = GLPLATFORM_GL_ARB_draw_buffers_blend && glBlendEquationSeparateiARB && glBlendEquationiARB
		 && glBlendFuncSeparateiARB && glBlendFunciARB;
	
	GLPLATFORM_GL_ARB_draw_elements_base_vertex = GLPLATFORM_GL_ARB_draw_elements_base_vertex && glDrawElementsBaseVertex && glDrawElementsInstancedBaseVertex
		 && glDrawRangeElementsBaseVertex && glMultiDrawElementsBaseVertex;
	
	GLPLATFORM_GL_ARB_draw_indirect = GLPLATFORM_GL_ARB_draw_indirect && glDrawArraysIndirect && glDrawElementsIndirect;
	
	GLPLATFORM_GL_ARB_framebuffer_no_attachments = GLPLATFORM_GL_ARB_framebuffer_no_attachments && glFramebufferParameteri && glGetFramebufferParameteriv;
	
	GLPLATFORM_GL_ARB_framebuffer_object = GLPLATFORM_GL_ARB_framebuffer_object && glBindFramebuffer && glBindRenderbuffer
		 && glBlitFramebuffer && glCheckFramebufferStatus && glDeleteFramebuffers
		 && glDeleteRenderbuffers && glFramebufferRenderbuffer && glFramebufferTexture1D
		 && glFramebufferTexture2D && glFramebufferTexture3D && glFramebufferTextureLayer
		 && glGenFramebuffers && glGenRenderbuffers && glGenerateMipmap
		 && glGetFramebufferAttachmentParameteriv && glGetRenderbufferParameteriv && glIsFramebuffer
		 && glIsRenderbuffer && glRenderbufferStorage && glRenderbufferStorageMultisample;
	
	GLPLATFORM_GL_ARB_get_program_binary = GLPLATFORM_GL_ARB_get_program_binary && glGetProgramBinary && glProgramBinary
		 && glProgramParameteri;
	
	GLPLATFORM_GL_ARB_get_texture_sub_image = GLPLATFORM_GL_ARB_get_texture_sub_image && glGetCompressedTextureSubImage && glGetTextureSubImage;
	
	GLPLATFORM_GL_ARB_gpu_shader_fp64 = GLPLATFORM_GL_ARB_gpu_shader_fp64 && glGetUniformdv && glUniform1d
		 && glUniform1dv && glUniform2d && glUniform2dv
		 && glUniform3d && glUniform3dv && glUniform4d
		 && glUniform4dv && glUniformMatrix2dv && glUniformMatrix2x3dv
		 && glUniformMatrix2x4dv && glUniformMatrix3dv && glUniformMatrix3x2dv
		 && glUniformMatrix3x4dv && glUniformMatrix4dv && glUniformMatrix4x2dv
		 && glUniformMatrix4x3dv;
	
	GLPLATFORM_GL_ARB_imaging = GLPLATFORM_GL_ARB_imaging && glBlendColor && glBlendEquation;
	
	GLPLATFORM_GL_ARB_indirect_parameters = GLPLATFORM_GL_ARB_indirect_parameters && glMultiDrawArraysIndirectCountARB && glMultiDrawElementsIndirectCountARB;
	
	GLPLATFORM_GL_ARB_internalformat_query = GLPLATFORM_GL_ARB_internalformat_query && glGetInternalformativ;
	
	GLPLATFORM_GL_ARB_internalformat_query2 = GLPLATFORM_GL_ARB_internalformat_query2 && glGetInternalformati64v;
	
	GLPLATFORM_GL_ARB_invalidate_subdata = GLPLATFORM_GL_ARB_invalidate_subdata && glInvalidateBufferData && glInvalidateBufferSubData
		 && glInvalidateFramebuffer && glInvalidateSubFramebuffer && glInvalidateTexImage
		 && glInvalidateTexSubImage;
	
	GLPLATFORM_GL_ARB_map_buffer_range = GLPLATFORM_GL_ARB_map_buffer_range && glFlushMappedBufferRange && glMapBufferRange;
	
	GLPLATFORM_GL_ARB_multi_bind = GLPLATFORM_GL_ARB_multi_bind && glBindBuffersBase && glBindBuffersRange
		 && glBindImageTextures && glBindSamplers && glBindTextures
		 && glBindVertexBuffers;
	
	GLPLATFORM_GL_ARB_multi_draw_indirect = GLPLATFORM_GL_ARB_multi_draw_indirect && glMultiDrawArraysIndirect && glMultiDrawElementsIndirect;
	
	GLPLATFORM_GL_ARB_program_interface_query = GLPLATFORM_GL_ARB_program_interface_query && glGetProgramInterfaceiv && glGetProgramResourceIndex
		 && glGetProgramResourceLocation && glGetProgramResourceLocationIndex && glGetProgramResourceName
		 && glGetProgramResourceiv;
	
	GLPLATFORM_GL_ARB_provoking_vertex = GLPLATFORM_GL_ARB_provoking_vertex && glProvokingVertex;
	
	GLPLATFORM_GL_ARB_robustness = GLPLATFORM_GL_ARB_robustness && glGetGraphicsResetStatusARB && glGetnCompressedTexImageARB
		 && glGetnTexImageARB && glGetnUniformdvARB && glGetnUniformfvARB
		 && glGetnUniformivARB && glGetnUniformuivARB && glReadnPixelsARB;
	
	GLPLATFORM_GL_ARB_sample_shading = GLPLATFORM_GL_ARB_sample_shading && glMinSampleShadingARB;
	
	GLPLATFORM_GL_ARB_sampler_objects = GLPLATFORM_GL_ARB_sampler_objects && glBindSampler && glDeleteSamplers
		 && glGenSamplers && glGetSamplerParameterIiv && glGetSamplerParameterIuiv
		 && glGetSamplerParameterfv && glGetSamplerParameteriv && glIsSampler
		 && glSamplerParameterIiv && glSamplerParameterIuiv && glSamplerParameterf
		 && glSamplerParameterfv && glSamplerParameteri && glSamplerParameteriv;
	
	GLPLATFORM_GL_ARB_separate_shader_objects = GLPLATFORM_GL_ARB_separate_shader_objects && glActiveShaderProgram && glBindProgramPipeline
		 && glCreateShaderProgramv && glDeleteProgramPipelines && glGenProgramPipelines
		 && glGetProgramPipelineInfoLog && glGetProgramPipelineiv && glIsProgramPipeline
		 && glProgramUniform1d && glProgramUniform1dv && glProgramUniform1f
		 && glProgramUniform1fv && glProgramUniform1i && glProgramUniform1iv
		 && glProgramUniform1ui && glProgramUniform1uiv && glProgramUniform2d
		 && glProgramUniform2dv && glProgramUniform2f && glProgramUniform2fv
		 && glProgramUniform2i && glProgramUniform2iv && glProgramUniform2ui
		 && glProgramUniform2uiv && glProgramUniform3d && glProgramUniform3dv
		 && glProgramUniform3f && glProgramUniform3fv && glProgramUniform3i
		 && glProgramUniform3iv && glProgramUniform3ui && glProgramUniform3uiv
		 && glProgramUniform4d && glProgramUniform4dv && glProgramUniform4f
		 && glProgramUniform4fv && glProgramUniform4i && glProgramUniform4iv
		 && glProgramUniform4ui && glProgramUniform4uiv && glProgramUniformMatrix2dv
		 && glProgramUniformMatrix2fv && glProgramUniformMatrix2x3dv && glProgramUniformMatrix2x3fv
		 && glProgramUniformMatrix2x4dv && glProgramUniformMatrix2x4fv && glProgramUniformMatrix3dv
		 && glProgramUniformMatrix3fv && glProgramUniformMatrix3x2dv && glProgramUniformMatrix3x2fv
		 && glProgramUniformMatrix3x4dv && glProgramUniformMatrix3x4fv && glProgramUniformMatrix4dv
		 && glProgramUniformMatrix4fv && glProgramUniformMatrix4x2dv && glProgramUniformMatrix4x2fv
		 && glProgramUniformMatrix4x3dv && glProgramUniformMatrix4x3fv && glUseProgramStages
		 && glValidateProgramPipeline;
	
	GLPLATFORM_GL_ARB_shader_atomic_counters = GLPLATFORM_GL_ARB_shader_atomic_counters && glGetActiveAtomicCounterBufferiv;
	
	GLPLATFORM_GL_ARB_shader_image_load_store = GLPLATFORM_GL_ARB_shader_image_load_store && glBindImageTexture && glMemoryBarrier;
	
	GLPLATFORM_GL_ARB_shader_storage_buffer_object = GLPLATFORM_GL_ARB_shader_storage_buffer_object && glShaderStorageBlockBinding;
	
	GLPLATFORM_GL_ARB_shader_subroutine = GLPLATFORM_GL_ARB_shader_subroutine && glGetActiveSubroutineName && glGetActiveSubroutineUniformName
		 && glGetActiveSubroutineUniformiv && glGetProgramStageiv && glGetSubroutineIndex
		 && glGetSubroutineUniformLocation && glGetUniformSubroutineuiv && glUniformSubroutinesuiv;
	
	GLPLATFORM_GL_ARB_shading_language_include = GLPLATFORM_GL_ARB_shading_language_include && glCompileShaderIncludeARB && glDeleteNamedStringARB
		 && glGetNamedStringARB && glGetNamedStringivARB && glIsNamedStringARB
		 && glNamedStringARB;
	
	GLPLATFORM_GL_ARB_sparse_buffer = GLPLATFORM_GL_ARB_sparse_buffer && glBufferPageCommitmentARB && glNamedBufferPageCommitmentARB
		 && glNamedBufferPageCommitmentEXT;
	
	GLPLATFORM_GL_ARB_sparse_texture = GLPLATFORM_GL_ARB_sparse_texture && glTexPageCommitmentARB;
	
	GLPLATFORM_GL_ARB_sync = GLPLATFORM_GL_ARB_sync && glClientWaitSync && glDeleteSync
		 && glFenceSync && glGetInteger64v && glGetSynciv
		 && glIsSync && glWaitSync;
	
	GLPLATFORM_GL_ARB_tessellation_shader = GLPLATFORM_GL_ARB_tessellation_shader && glPatchParameterfv && glPatchParameteri;
	
	GLPLATFORM_GL_ARB_texture_barrier = GLPLATFORM_GL_ARB_texture_barrier && glTextureBarrier;
	
	GLPLATFORM_GL_ARB_texture_buffer_range = GLPLATFORM_GL_ARB_texture_buffer_range && glTexBufferRange;
	
	GLPLATFORM_GL_ARB_texture_multisample = GLPLATFORM_GL_ARB_texture_multisample && glGetMultisamplefv && glSampleMaski
		 && glTexImage2DMultisample && glTexImage3DMultisample;
	
	GLPLATFORM_GL_ARB_texture_storage = GLPLATFORM_GL_ARB_texture_storage && glTexStorage1D && glTexStorage2D
		 && glTexStorage3D;
	
	GLPLATFORM_GL_ARB_texture_storage_multisample = GLPLATFORM_GL_ARB_texture_storage_multisample && glTexStorage2DMultisample && glTexStorage3DMultisample;
	
	GLPLATFORM_GL_ARB_texture_view = GLPLATFORM_GL_ARB_texture_view && glTextureView;
	
	GLPLATFORM_GL_ARB_timer_query = GLPLATFORM_GL_ARB_timer_query && glGetQueryObjecti64v && glGetQueryObjectui64v
		 && glQueryCounter;
	
	GLPLATFORM_GL_ARB_transform_feedback2 = GLPLATFORM_GL_ARB_transform_feedback2 && glBindTransformFeedback && glDeleteTransformFeedbacks
		 && glDrawTransformFeedback && glGenTransformFeedbacks && glIsTransformFeedback
		 && glPauseTransformFeedback && glResumeTransformFeedback;
	
	GLPLATFORM_GL_ARB_transform_feedback3 = GLPLATFORM_GL_ARB_transform_feedback3 && glBeginQueryIndexed && glDrawTransformFeedbackStream
		 && glEndQueryIndexed && glGetQueryIndexediv;
	
	GLPLATFORM_GL_ARB_transform_feedback_instanced = GLPLATFORM_GL_ARB_transform_feedback_instanced && glDrawTransformFeedbackInstanced && glDrawTransformFeedbackStreamInstanced;
	
	GLPLATFORM_GL_ARB_uniform_buffer_object = GLPLATFORM_GL_ARB_uniform_buffer_object && glGetActiveUniformBlockName && glGetActiveUniformBlockiv
		 && glGetActiveUniformName && glGetActiveUniformsiv && glGetUniformBlockIndex
		 && glGetUniformIndices && glUniformBlockBinding;
	
	GLPLATFORM_GL_ARB_vertex_array_object = GLPLATFORM_GL_ARB_vertex_array_object && glBindVertexArray && glDeleteVertexArrays
		 && glGenVertexArrays && glIsVertexArray;
	
	GLPLATFORM_GL_ARB_vertex_attrib_64bit = GLPLATFORM_GL_ARB_vertex_attrib_64bit && glGetVertexAttribLdv && glVertexAttribL1d
		 && glVertexAttribL1dv && glVertexAttribL2d && glVertexAttribL2dv
		 && glVertexAttribL3d && glVertexAttribL3dv && glVertexAttribL4d
		 && glVertexAttribL4dv && glVertexAttribLPointer;
	
	GLPLATFORM_GL_ARB_vertex_attrib_binding = GLPLATFORM_GL_ARB_vertex_attrib_binding && glBindVertexBuffer && glVertexAttribBinding
		 && glVertexAttribFormat && glVertexAttribIFormat && glVertexAttribLFormat
		 && glVertexBindingDivisor;
	
	GLPLATFORM_GL_ARB_vertex_type_2_10_10_10_rev = GLPLATFORM_GL_ARB_vertex_type_2_10_10_10_rev && glVertexAttribP1ui && glVertexAttribP1uiv
		 && glVertexAttribP2ui && glVertexAttribP2uiv && glVertexAttribP3ui
		 && glVertexAttribP3uiv && glVertexAttribP4ui && glVertexAttribP4uiv;
	
	GLPLATFORM_GL_ARB_viewport_array = GLPLATFORM_GL_ARB_viewport_array && glDepthRangeArrayv && glDepthRangeIndexed
		 && glGetDoublei_v && glGetFloati_v && glScissorArrayv
		 && glScissorIndexed && glScissorIndexedv && glViewportArrayv
		 && glViewportIndexedf && glViewportIndexedfv;
	
	GLPLATFORM_GL_EXT_direct_state_access = GLPLATFORM_GL_EXT_direct_state_access && glBindMultiTextureEXT && glCheckNamedFramebufferStatusEXT
		 && glClearNamedBufferDataEXT && glClearNamedBufferSubDataEXT && glClientAttribDefaultEXT
		 && glCompressedMultiTexImage1DEXT && glCompressedMultiTexImage2DEXT && glCompressedMultiTexImage3DEXT
		 && glCompressedMultiTexSubImage1DEXT && glCompressedMultiTexSubImage2DEXT && glCompressedMultiTexSubImage3DEXT
		 && glCompressedTextureImage1DEXT && glCompressedTextureImage2DEXT && glCompressedTextureImage3DEXT
		 && glCompressedTextureSubImage1DEXT && glCompressedTextureSubImage2DEXT && glCompressedTextureSubImage3DEXT
		 && glCopyMultiTexImage1DEXT && glCopyMultiTexImage2DEXT && glCopyMultiTexSubImage1DEXT
		 && glCopyMultiTexSubImage2DEXT && glCopyMultiTexSubImage3DEXT && glCopyTextureImage1DEXT
		 && glCopyTextureImage2DEXT && glCopyTextureSubImage1DEXT && glCopyTextureSubImage2DEXT
		 && glCopyTextureSubImage3DEXT && glDisableClientStateIndexedEXT && glDisableClientStateiEXT
		 && glDisableIndexedEXT && glDisableVertexArrayAttribEXT && glDisableVertexArrayEXT
		 && glEnableClientStateIndexedEXT && glEnableClientStateiEXT && glEnableIndexedEXT
		 && glEnableVertexArrayAttribEXT && glEnableVertexArrayEXT && glFlushMappedNamedBufferRangeEXT
		 && glFramebufferDrawBufferEXT && glFramebufferDrawBuffersEXT && glFramebufferReadBufferEXT
		 && glGenerateMultiTexMipmapEXT && glGenerateTextureMipmapEXT && glGetBooleanIndexedvEXT
		 && glGetCompressedMultiTexImageEXT && glGetCompressedTextureImageEXT && glGetDoubleIndexedvEXT
		 && glGetDoublei_vEXT && glGetFloatIndexedvEXT && glGetFloati_vEXT
		 && glGetFramebufferParameterivEXT && glGetIntegerIndexedvEXT && glGetMultiTexEnvfvEXT
		 && glGetMultiTexEnvivEXT && glGetMultiTexGendvEXT && glGetMultiTexGenfvEXT
		 && glGetMultiTexGenivEXT && glGetMultiTexImageEXT && glGetMultiTexLevelParameterfvEXT
		 && glGetMultiTexLevelParameterivEXT && glGetMultiTexParameterIivEXT && glGetMultiTexParameterIuivEXT
		 && glGetMultiTexParameterfvEXT && glGetMultiTexParameterivEXT && glGetNamedBufferParameterivEXT
		 && glGetNamedBufferPointervEXT && glGetNamedBufferSubDataEXT && glGetNamedFramebufferAttachmentParameterivEXT
		 && glGetNamedFramebufferParameterivEXT && glGetNamedProgramLocalParameterIivEXT && glGetNamedProgramLocalParameterIuivEXT
		 && glGetNamedProgramLocalParameterdvEXT && glGetNamedProgramLocalParameterfvEXT && glGetNamedProgramStringEXT
		 && glGetNamedProgramivEXT && glGetNamedRenderbufferParameterivEXT && glGetPointerIndexedvEXT
		 && glGetPointeri_vEXT && glGetTextureImageEXT && glGetTextureLevelParameterfvEXT
		 && glGetTextureLevelParameterivEXT && glGetTextureParameterIivEXT && glGetTextureParameterIuivEXT
		 && glGetTextureParameterfvEXT && glGetTextureParameterivEXT && glGetVertexArrayIntegeri_vEXT
		 && glGetVertexArrayIntegervEXT && glGetVertexArrayPointeri_vEXT && glGetVertexArrayPointervEXT
		 && glIsEnabledIndexedEXT && glMapNamedBufferEXT && glMapNamedBufferRangeEXT
		 && glMatrixFrustumEXT && glMatrixLoadIdentityEXT && glMatrixLoadTransposedEXT
		 && glMatrixLoadTransposefEXT && glMatrixLoaddEXT && glMatrixLoadfEXT
		 && glMatrixMultTransposedEXT && glMatrixMultTransposefEXT && glMatrixMultdEXT
		 && glMatrixMultfEXT && glMatrixOrthoEXT && glMatrixPopEXT
		 && glMatrixPushEXT && glMatrixRotatedEXT && glMatrixRotatefEXT
		 && glMatrixScaledEXT && glMatrixScalefEXT && glMatrixTranslatedEXT
		 && glMatrixTranslatefEXT && glMultiTexBufferEXT && glMultiTexCoordPointerEXT
		 && glMultiTexEnvfEXT && glMultiTexEnvfvEXT && glMultiTexEnviEXT
		 && glMultiTexEnvivEXT && glMultiTexGendEXT && glMultiTexGendvEXT
		 && glMultiTexGenfEXT && glMultiTexGenfvEXT && glMultiTexGeniEXT
		 && glMultiTexGenivEXT && glMultiTexImage1DEXT && glMultiTexImage2DEXT
		 && glMultiTexImage3DEXT && glMultiTexParameterIivEXT && glMultiTexParameterIuivEXT
		 && glMultiTexParameterfEXT && glMultiTexParameterfvEXT && glMultiTexParameteriEXT
		 && glMultiTexParameterivEXT && glMultiTexRenderbufferEXT && glMultiTexSubImage1DEXT
		 && glMultiTexSubImage2DEXT && glMultiTexSubImage3DEXT && glNamedBufferDataEXT
		 && glNamedBufferStorageEXT && glNamedBufferSubDataEXT && glNamedCopyBufferSubDataEXT
		 && glNamedFramebufferParameteriEXT && glNamedFramebufferRenderbufferEXT && glNamedFramebufferTexture1DEXT
		 && glNamedFramebufferTexture2DEXT && glNamedFramebufferTexture3DEXT && glNamedFramebufferTextureEXT
		 && glNamedFramebufferTextureFaceEXT && glNamedFramebufferTextureLayerEXT && glNamedProgramLocalParameter4dEXT
		 && glNamedProgramLocalParameter4dvEXT && glNamedProgramLocalParameter4fEXT && glNamedProgramLocalParameter4fvEXT
		 && glNamedProgramLocalParameterI4iEXT && glNamedProgramLocalParameterI4ivEXT && glNamedProgramLocalParameterI4uiEXT
		 && glNamedProgramLocalParameterI4uivEXT && glNamedProgramLocalParameters4fvEXT && glNamedProgramLocalParametersI4ivEXT
		 && glNamedProgramLocalParametersI4uivEXT && glNamedProgramStringEXT && glNamedRenderbufferStorageEXT
		 && glNamedRenderbufferStorageMultisampleCoverageEXT && glNamedRenderbufferStorageMultisampleEXT && glProgramUniform1dEXT
		 && glProgramUniform1dvEXT && glProgramUniform1fEXT && glProgramUniform1fvEXT
		 && glProgramUniform1iEXT && glProgramUniform1ivEXT && glProgramUniform1uiEXT
		 && glProgramUniform1uivEXT && glProgramUniform2dEXT && glProgramUniform2dvEXT
		 && glProgramUniform2fEXT && glProgramUniform2fvEXT && glProgramUniform2iEXT
		 && glProgramUniform2ivEXT && glProgramUniform2uiEXT && glProgramUniform2uivEXT
		 && glProgramUniform3dEXT && glProgramUniform3dvEXT && glProgramUniform3fEXT
		 && glProgramUniform3fvEXT && glProgramUniform3iEXT && glProgramUniform3ivEXT
		 && glProgramUniform3uiEXT && glProgramUniform3uivEXT && glProgramUniform4dEXT
		 && glProgramUniform4dvEXT && glProgramUniform4fEXT && glProgramUniform4fvEXT
		 && glProgramUniform4iEXT && glProgramUniform4ivEXT && glProgramUniform4uiEXT
		 && glProgramUniform4uivEXT && glProgramUniformMatrix2dvEXT && glProgramUniformMatrix2fvEXT
		 && glProgramUniformMatrix2x3dvEXT && glProgramUniformMatrix2x3fvEXT && glProgramUniformMatrix2x4dvEXT
		 && glProgramUniformMatrix2x4fvEXT && glProgramUniformMatrix3dvEXT && glProgramUniformMatrix3fvEXT
		 && glProgramUniformMatrix3x2dvEXT && glProgramUniformMatrix3x2fvEXT && glProgramUniformMatrix3x4dvEXT
		 && glProgramUniformMatrix3x4fvEXT && glProgramUniformMatrix4dvEXT && glProgramUniformMatrix4fvEXT
		 && glProgramUniformMatrix4x2dvEXT && glProgramUniformMatrix4x2fvEXT && glProgramUniformMatrix4x3dvEXT
		 && glProgramUniformMatrix4x3fvEXT && glPushClientAttribDefaultEXT && glTextureBufferEXT
		 && glTextureBufferRangeEXT && glTextureImage1DEXT && glTextureImage2DEXT
		 && glTextureImage3DEXT && glTexturePageCommitmentEXT && glTextureParameterIivEXT
		 && glTextureParameterIuivEXT && glTextureParameterfEXT && glTextureParameterfvEXT
		 && glTextureParameteriEXT && glTextureParameterivEXT && glTextureRenderbufferEXT
		 && glTextureStorage1DEXT && glTextureStorage2DEXT && glTextureStorage2DMultisampleEXT
		 && glTextureStorage3DEXT && glTextureStorage3DMultisampleEXT && glTextureSubImage1DEXT
		 && glTextureSubImage2DEXT && glTextureSubImage3DEXT && glUnmapNamedBufferEXT
		 && glVertexArrayBindVertexBufferEXT && glVertexArrayColorOffsetEXT && glVertexArrayEdgeFlagOffsetEXT
		 && glVertexArrayFogCoordOffsetEXT && glVertexArrayIndexOffsetEXT && glVertexArrayMultiTexCoordOffsetEXT
		 && glVertexArrayNormalOffsetEXT && glVertexArraySecondaryColorOffsetEXT && glVertexArrayTexCoordOffsetEXT
		 && glVertexArrayVertexAttribBindingEXT && glVertexArrayVertexAttribDivisorEXT && glVertexArrayVertexAttribFormatEXT
		 && glVertexArrayVertexAttribIFormatEXT && glVertexArrayVertexAttribIOffsetEXT && glVertexArrayVertexAttribLFormatEXT
		 && glVertexArrayVertexAttribLOffsetEXT && glVertexArrayVertexAttribOffsetEXT && glVertexArrayVertexBindingDivisorEXT
		 && glVertexArrayVertexOffsetEXT;
	
	GLPLATFORM_GL_KHR_debug = GLPLATFORM_GL_KHR_debug && glDebugMessageCallback && glDebugMessageCallbackKHR
		 && glDebugMessageControl && glDebugMessageControlKHR && glDebugMessageInsert
		 && glDebugMessageInsertKHR && glGetDebugMessageLog && glGetDebugMessageLogKHR
		 && glGetObjectLabel && glGetObjectLabelKHR && glGetObjectPtrLabel
		 && glGetObjectPtrLabelKHR && glGetPointerv && glGetPointervKHR
		 && glObjectLabel && glObjectLabelKHR && glObjectPtrLabel
		 && glObjectPtrLabelKHR && glPopDebugGroup && glPopDebugGroupKHR
		 && glPushDebugGroup && glPushDebugGroupKHR;
	
	GLPLATFORM_GL_KHR_robustness = GLPLATFORM_GL_KHR_robustness && glGetGraphicsResetStatus && glGetGraphicsResetStatusKHR
		 && glGetnUniformfv && glGetnUniformfvKHR && glGetnUniformiv
		 && glGetnUniformivKHR && glGetnUniformuiv && glGetnUniformuivKHR
		 && glReadnPixels && glReadnPixelsKHR;
	
	return glActiveTexture && glAttachShader
	 && glBeginConditionalRender && glBeginQuery && glBeginTransformFeedback
	 && glBindAttribLocation && glBindBuffer && glBindBufferBase
	 && glBindBufferRange && glBindFragDataLocation && glBindFramebuffer
	 && glBindRenderbuffer && glBindTexture && glBindVertexArray
	 && glBlendColor && glBlendEquation && glBlendEquationSeparate
	 && glBlendFunc && glBlendFuncSeparate && glBlitFramebuffer
	 && glBufferData && glBufferSubData && glCheckFramebufferStatus
	 && glClampColor && glClear && glClearBufferfi
	 && glClearBufferfv && glClearBufferiv && glClearBufferuiv
	 && glClearColor && glClearDepth && glClearStencil
	 && glClientWaitSync && glColorMask && glColorMaski
	 && glCompileShader && glCompressedTexImage1D && glCompressedTexImage2D
	 && glCompressedTexImage3D && glCompressedTexSubImage1D && glCompressedTexSubImage2D
	 && glCompressedTexSubImage3D && glCopyBufferSubData && glCopyTexImage1D
	 && glCopyTexImage2D && glCopyTexSubImage1D && glCopyTexSubImage2D
	 && glCopyTexSubImage3D && glCreateProgram && glCreateShader
	 && glCullFace && glDeleteBuffers && glDeleteFramebuffers
	 && glDeleteProgram && glDeleteQueries && glDeleteRenderbuffers
	 && glDeleteShader && glDeleteSync && glDeleteTextures
	 && glDeleteVertexArrays && glDepthFunc && glDepthMask
	 && glDepthRange && glDetachShader && glDisable
	 && glDisableVertexAttribArray && glDisablei && glDrawArrays
	 && glDrawArraysInstanced && glDrawBuffer && glDrawBuffers
	 && glDrawElements && glDrawElementsBaseVertex && glDrawElementsInstanced
	 && glDrawElementsInstancedBaseVertex && glDrawRangeElements && glDrawRangeElementsBaseVertex
	 && glEnable && glEnableVertexAttribArray && glEnablei
	 && glEndConditionalRender && glEndQuery && glEndTransformFeedback
	 && glFenceSync && glFinish && glFlush
	 && glFlushMappedBufferRange && glFramebufferRenderbuffer && glFramebufferTexture
	 && glFramebufferTexture1D && glFramebufferTexture2D && glFramebufferTexture3D
	 && glFramebufferTextureLayer && glFrontFace && glGenBuffers
	 && glGenFramebuffers && glGenQueries && glGenRenderbuffers
	 && glGenTextures && glGenVertexArrays && glGenerateMipmap
	 && glGetActiveAttrib && glGetActiveUniform && glGetActiveUniformBlockName
	 && glGetActiveUniformBlockiv && glGetActiveUniformName && glGetActiveUniformsiv
	 && glGetAttachedShaders && glGetAttribLocation && glGetBooleani_v
	 && glGetBooleanv && glGetBufferParameteri64v && glGetBufferParameteriv
	 && glGetBufferPointerv && glGetBufferSubData && glGetCompressedTexImage
	 && glGetDoublev && glGetError && glGetFloatv
	 && glGetFragDataLocation && glGetFramebufferAttachmentParameteriv && glGetInteger64i_v
	 && glGetInteger64v && glGetIntegeri_v && glGetIntegerv
	 && glGetMultisamplefv && glGetProgramInfoLog && glGetProgramiv
	 && glGetQueryObjectiv && glGetQueryObjectuiv && glGetQueryiv
	 && glGetRenderbufferParameteriv && glGetShaderInfoLog && glGetShaderSource
	 && glGetShaderiv && glGetString && glGetStringi
	 && glGetSynciv && glGetTexImage && glGetTexLevelParameterfv
	 && glGetTexLevelParameteriv && glGetTexParameterIiv && glGetTexParameterIuiv
	 && glGetTexParameterfv && glGetTexParameteriv && glGetTransformFeedbackVarying
	 && glGetUniformBlockIndex && glGetUniformIndices && glGetUniformLocation
	 && glGetUniformfv && glGetUniformiv && glGetUniformuiv
	 && glGetVertexAttribIiv && glGetVertexAttribIuiv && glGetVertexAttribPointerv
	 && glGetVertexAttribdv && glGetVertexAttribfv && glGetVertexAttribiv
	 && glHint && glIsBuffer && glIsEnabled
	 && glIsEnabledi && glIsFramebuffer && glIsProgram
	 && glIsQuery && glIsRenderbuffer && glIsShader
	 && glIsSync && glIsTexture && glIsVertexArray
	 && glLineWidth && glLinkProgram && glLogicOp
	 && glMapBuffer && glMapBufferRange && glMultiDrawArrays
	 && glMultiDrawElements && glMultiDrawElementsBaseVertex && glPixelStoref
	 && glPixelStorei && glPointParameterf && glPointParameterfv
	 && glPointParameteri && glPointParameteriv && glPointSize
	 && glPolygonMode && glPolygonOffset && glPrimitiveRestartIndex
	 && glProvokingVertex && glReadBuffer && glReadPixels
	 && glRenderbufferStorage && glRenderbufferStorageMultisample && glSampleCoverage
	 && glSampleMaski && glScissor && glShaderSource
	 && glStencilFunc && glStencilFuncSeparate && glStencilMask
	 && glStencilMaskSeparate && glStencilOp && glStencilOpSeparate
	 && glTexBuffer && glTexImage1D && glTexImage2D
	 && glTexImage2DMultisample && glTexImage3D && glTexImage3DMultisample
	 && glTexParameterIiv && glTexParameterIuiv && glTexParameterf
	 && glTexParameterfv && glTexParameteri && glTexParameteriv
	 && glTexSubImage1D && glTexSubImage2D && glTexSubImage3D
	 && glTransformFeedbackVaryings && glUniform1f && glUniform1fv
	 && glUniform1i && glUniform1iv && glUniform1ui
	 && glUniform1uiv && glUniform2f && glUniform2fv
	 && glUniform2i && glUniform2iv && glUniform2ui
	 && glUniform2uiv && glUniform3f && glUniform3fv
	 && glUniform3i && glUniform3iv && glUniform3ui
	 && glUniform3uiv && glUniform4f && glUniform4fv
	 && glUniform4i && glUniform4iv && glUniform4ui
	 && glUniform4uiv && glUniformBlockBinding && glUniformMatrix2fv
	 && glUniformMatrix2x3fv && glUniformMatrix2x4fv && glUniformMatrix3fv
	 && glUniformMatrix3x2fv && glUniformMatrix3x4fv && glUniformMatrix4fv
	 && glUniformMatrix4x2fv && glUniformMatrix4x3fv && glUnmapBuffer
	 && glUseProgram && glValidateProgram && glVertexAttrib1d
	 && glVertexAttrib1dv && glVertexAttrib1f && glVertexAttrib1fv
	 && glVertexAttrib1s && glVertexAttrib1sv && glVertexAttrib2d
	 && glVertexAttrib2dv && glVertexAttrib2f && glVertexAttrib2fv
	 && glVertexAttrib2s && glVertexAttrib2sv && glVertexAttrib3d
	 && glVertexAttrib3dv && glVertexAttrib3f && glVertexAttrib3fv
	 && glVertexAttrib3s && glVertexAttrib3sv && glVertexAttrib4Nbv
	 && glVertexAttrib4Niv && glVertexAttrib4Nsv && glVertexAttrib4Nub
	 && glVertexAttrib4Nubv && glVertexAttrib4Nuiv && glVertexAttrib4Nusv
	 && glVertexAttrib4bv && glVertexAttrib4d && glVertexAttrib4dv
	 && glVertexAttrib4f && glVertexAttrib4fv && glVertexAttrib4iv
	 && glVertexAttrib4s && glVertexAttrib4sv && glVertexAttrib4ubv
	 && glVertexAttrib4uiv && glVertexAttrib4usv && glVertexAttribI1i
	 && glVertexAttribI1iv && glVertexAttribI1ui && glVertexAttribI1uiv
	 && glVertexAttribI2i && glVertexAttribI2iv && glVertexAttribI2ui
	 && glVertexAttribI2uiv && glVertexAttribI3i && glVertexAttribI3iv
	 && glVertexAttribI3ui && glVertexAttribI3uiv && glVertexAttribI4bv
	 && glVertexAttribI4i && glVertexAttribI4iv && glVertexAttribI4sv
	 && glVertexAttribI4ubv && glVertexAttribI4ui && glVertexAttribI4uiv
	 && glVertexAttribI4usv && glVertexAttribIPointer && glVertexAttribPointer
	 && glViewport && glWaitSync
	 && ((req_version < 33) ||
		(glBindFragDataLocationIndexed && glBindSampler
		 && glDeleteSamplers && glGenSamplers && glGetFragDataIndex
		 && glGetQueryObjecti64v && glGetQueryObjectui64v && glGetSamplerParameterIiv
		 && glGetSamplerParameterIuiv && glGetSamplerParameterfv && glGetSamplerParameteriv
		 && glIsSampler && glQueryCounter && glSamplerParameterIiv
		 && glSamplerParameterIuiv && glSamplerParameterf && glSamplerParameterfv
		 && glSamplerParameteri && glSamplerParameteriv && glVertexAttribDivisor
		 && glVertexAttribP1ui && glVertexAttribP1uiv && glVertexAttribP2ui
		 && glVertexAttribP2uiv && glVertexAttribP3ui && glVertexAttribP3uiv
		 && glVertexAttribP4ui && glVertexAttribP4uiv))
	 && ((req_version < 40) ||
		(glBeginQueryIndexed && glBindTransformFeedback
		 && glBlendEquationSeparatei && glBlendEquationi && glBlendFuncSeparatei
		 && glBlendFunci && glDeleteTransformFeedbacks && glDrawArraysIndirect
		 && glDrawElementsIndirect && glDrawTransformFeedback && glDrawTransformFeedbackStream
		 && glEndQueryIndexed && glGenTransformFeedbacks && glGetActiveSubroutineName
		 && glGetActiveSubroutineUniformName && glGetActiveSubroutineUniformiv && glGetProgramStageiv
		 && glGetQueryIndexediv && glGetSubroutineIndex && glGetSubroutineUniformLocation
		 && glGetUniformSubroutineuiv && glGetUniformdv && glIsTransformFeedback
		 && glMinSampleShading && glPatchParameterfv && glPatchParameteri
		 && glPauseTransformFeedback && glResumeTransformFeedback && glUniform1d
		 && glUniform1dv && glUniform2d && glUniform2dv
		 && glUniform3d && glUniform3dv && glUniform4d
		 && glUniform4dv && glUniformMatrix2dv && glUniformMatrix2x3dv
		 && glUniformMatrix2x4dv && glUniformMatrix3dv && glUniformMatrix3x2dv
		 && glUniformMatrix3x4dv && glUniformMatrix4dv && glUniformMatrix4x2dv
		 && glUniformMatrix4x3dv && glUniformSubroutinesuiv))
	 && ((req_version < 41) ||
		(glActiveShaderProgram && glBindProgramPipeline
		 && glClearDepthf && glCreateShaderProgramv && glDeleteProgramPipelines
		 && glDepthRangeArrayv && glDepthRangeIndexed && glDepthRangef
		 && glGenProgramPipelines && glGetDoublei_v && glGetFloati_v
		 && glGetProgramBinary && glGetProgramPipelineInfoLog && glGetProgramPipelineiv
		 && glGetShaderPrecisionFormat && glGetVertexAttribLdv && glIsProgramPipeline
		 && glProgramBinary && glProgramParameteri && glProgramUniform1d
		 && glProgramUniform1dv && glProgramUniform1f && glProgramUniform1fv
		 && glProgramUniform1i && glProgramUniform1iv && glProgramUniform1ui
		 && glProgramUniform1uiv && glProgramUniform2d && glProgramUniform2dv
		 && glProgramUniform2f && glProgramUniform2fv && glProgramUniform2i
		 && glProgramUniform2iv && glProgramUniform2ui && glProgramUniform2uiv
		 && glProgramUniform3d && glProgramUniform3dv && glProgramUniform3f
		 && glProgramUniform3fv && glProgramUniform3i && glProgramUniform3iv
		 && glProgramUniform3ui && glProgramUniform3uiv && glProgramUniform4d
		 && glProgramUniform4dv && glProgramUniform4f && glProgramUniform4fv
		 && glProgramUniform4i && glProgramUniform4iv && glProgramUniform4ui
		 && glProgramUniform4uiv && glProgramUniformMatrix2dv && glProgramUniformMatrix2fv
		 && glProgramUniformMatrix2x3dv && glProgramUniformMatrix2x3fv && glProgramUniformMatrix2x4dv
		 && glProgramUniformMatrix2x4fv && glProgramUniformMatrix3dv && glProgramUniformMatrix3fv
		 && glProgramUniformMatrix3x2dv && glProgramUniformMatrix3x2fv && glProgramUniformMatrix3x4dv
		 && glProgramUniformMatrix3x4fv && glProgramUniformMatrix4dv && glProgramUniformMatrix4fv
		 && glProgramUniformMatrix4x2dv && glProgramUniformMatrix4x2fv && glProgramUniformMatrix4x3dv
		 && glProgramUniformMatrix4x3fv && glReleaseShaderCompiler && glScissorArrayv
		 && glScissorIndexed && glScissorIndexedv && glShaderBinary
		 && glUseProgramStages && glValidateProgramPipeline && glVertexAttribL1d
		 && glVertexAttribL1dv && glVertexAttribL2d && glVertexAttribL2dv
		 && glVertexAttribL3d && glVertexAttribL3dv && glVertexAttribL4d
		 && glVertexAttribL4dv && glVertexAttribLPointer && glViewportArrayv
		 && glViewportIndexedf && glViewportIndexedfv))
	 && ((req_version < 42) ||
		(glBindImageTexture && glDrawArraysInstancedBaseInstance
		 && glDrawElementsInstancedBaseInstance && glDrawElementsInstancedBaseVertexBaseInstance && glDrawTransformFeedbackInstanced
		 && glDrawTransformFeedbackStreamInstanced && glGetActiveAtomicCounterBufferiv && glGetInternalformativ
		 && glMemoryBarrier && glTexStorage1D && glTexStorage2D
		 && glTexStorage3D))
	 && ((req_version < 43) ||
		(glBindVertexBuffer && glClearBufferData
		 && glClearBufferSubData && glCopyImageSubData && glDebugMessageCallback
		 && glDebugMessageControl && glDebugMessageInsert && glDispatchCompute
		 && glDispatchComputeIndirect && glFramebufferParameteri && glGetDebugMessageLog
		 && glGetFramebufferParameteriv && glGetInternalformati64v && glGetObjectLabel
		 && glGetObjectPtrLabel && glGetPointerv && glGetProgramInterfaceiv
		 && glGetProgramResourceIndex && glGetProgramResourceLocation && glGetProgramResourceLocationIndex
		 && glGetProgramResourceName && glGetProgramResourceiv && glInvalidateBufferData
		 && glInvalidateBufferSubData && glInvalidateFramebuffer && glInvalidateSubFramebuffer
		 && glInvalidateTexImage && glInvalidateTexSubImage && glMultiDrawArraysIndirect
		 && glMultiDrawElementsIndirect && glObjectLabel && glObjectPtrLabel
		 && glPopDebugGroup && glPushDebugGroup && glShaderStorageBlockBinding
		 && glTexBufferRange && glTexStorage2DMultisample && glTexStorage3DMultisample
		 && glTextureView && glVertexAttribBinding && glVertexAttribFormat
		 && glVertexAttribIFormat && glVertexAttribLFormat && glVertexBindingDivisor))
	 && ((req_version < 44) ||
		(glBindBuffersBase && glBindBuffersRange
		 && glBindImageTextures && glBindSamplers && glBindTextures
		 && glBindVertexBuffers && glBufferStorage && glClearTexImage
		 && glClearTexSubImage))
	 && ((req_version < 45) ||
		(glBindTextureUnit && glBlitNamedFramebuffer
		 && glCheckNamedFramebufferStatus && glClearNamedBufferData && glClearNamedBufferSubData
		 && glClearNamedFramebufferfi && glClearNamedFramebufferfv && glClearNamedFramebufferiv
		 && glClearNamedFramebufferuiv && glClipControl && glCompressedTextureSubImage1D
		 && glCompressedTextureSubImage2D && glCompressedTextureSubImage3D && glCopyNamedBufferSubData
		 && glCopyTextureSubImage1D && glCopyTextureSubImage2D && glCopyTextureSubImage3D
		 && glCreateBuffers && glCreateFramebuffers && glCreateProgramPipelines
		 && glCreateQueries && glCreateRenderbuffers && glCreateSamplers
		 && glCreateTextures && glCreateTransformFeedbacks && glCreateVertexArrays
		 && glDisableVertexArrayAttrib && glEnableVertexArrayAttrib && glFlushMappedNamedBufferRange
		 && glGenerateTextureMipmap && glGetCompressedTextureImage && glGetCompressedTextureSubImage
		 && glGetGraphicsResetStatus && glGetNamedBufferParameteri64v && glGetNamedBufferParameteriv
		 && glGetNamedBufferPointerv && glGetNamedBufferSubData && glGetNamedFramebufferAttachmentParameteriv
		 && glGetNamedFramebufferParameteriv && glGetNamedRenderbufferParameteriv && glGetQueryBufferObjecti64v
		 && glGetQueryBufferObjectiv && glGetQueryBufferObjectui64v && glGetQueryBufferObjectuiv
		 && glGetTextureImage && glGetTextureLevelParameterfv && glGetTextureLevelParameteriv
		 && glGetTextureParameterIiv && glGetTextureParameterIuiv && glGetTextureParameterfv
		 && glGetTextureParameteriv && glGetTextureSubImage && glGetTransformFeedbacki64_v
		 && glGetTransformFeedbacki_v && glGetTransformFeedbackiv && glGetVertexArrayIndexed64iv
		 && glGetVertexArrayIndexediv && glGetVertexArrayiv && glGetnCompressedTexImage
		 && glGetnTexImage && glGetnUniformdv && glGetnUniformfv
		 && glGetnUniformiv && glGetnUniformuiv && glInvalidateNamedFramebufferData
		 && glInvalidateNamedFramebufferSubData && glMapNamedBuffer && glMapNamedBufferRange
		 && glMemoryBarrierByRegion && glNamedBufferData && glNamedBufferStorage
		 && glNamedBufferSubData && glNamedFramebufferDrawBuffer && glNamedFramebufferDrawBuffers
		 && glNamedFramebufferParameteri && glNamedFramebufferReadBuffer && glNamedFramebufferRenderbuffer
		 && glNamedFramebufferTexture && glNamedFramebufferTextureLayer && glNamedRenderbufferStorage
		 && glNamedRenderbufferStorageMultisample && glReadnPixels && glTextureBarrier
		 && glTextureBuffer && glTextureBufferRange && glTextureParameterIiv
		 && glTextureParameterIuiv && glTextureParameterf && glTextureParameterfv
		 && glTextureParameteri && glTextureParameteriv && glTextureStorage1D
		 && glTextureStorage2D && glTextureStorage2DMultisample && glTextureStorage3D
		 && glTextureStorage3DMultisample && glTextureSubImage1D && glTextureSubImage2D
		 && glTextureSubImage3D && glTransformFeedbackBufferBase && glTransformFeedbackBufferRange
		 && glUnmapNamedBuffer && glVertexArrayAttribBinding && glVertexArrayAttribFormat
		 && glVertexArrayAttribIFormat && glVertexArrayAttribLFormat && glVertexArrayBindingDivisor
		 && glVertexArrayElementBuffer && glVertexArrayVertexBuffer && glVertexArrayVertexBuffers));
}
