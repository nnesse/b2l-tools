#ifndef GL_BINDIFY_gl_H
#define GL_BINDIFY_gl_H
#ifdef __cplusplus
extern "C" {
#endif
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
#ifndef GLPLATFORM_GL_VERSION
#define GLPLATFORM_GL_VERSION 32
#endif
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif
#ifndef GLPLATFORM_TYPE_GLsync
#define GLPLATFORM_TYPE_GLsync
typedef struct __GLsync *GLsync;
#endif
#ifndef GLPLATFORM_TYPE_GLuint64
#define GLPLATFORM_TYPE_GLuint64
typedef uint64_t GLuint64;
#endif

#define GL_ACTIVE_ATTRIBUTES 0x8b89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8b8a
#define GL_ACTIVE_TEXTURE 0x84e0
#define GL_ACTIVE_UNIFORMS 0x8b86
#define GL_ACTIVE_UNIFORM_BLOCKS 0x8a36
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8a35
#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8b87
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846e
#define GL_ALPHA 0x1906
#define GL_ALREADY_SIGNALED 0x911a
#define GL_ALWAYS 0x207
#define GL_AND 0x1501
#define GL_AND_INVERTED 0x1504
#define GL_AND_REVERSE 0x1502
#define GL_ARRAY_BUFFER 0x8892
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_ATTACHED_SHADERS 0x8b85
#define GL_BACK 0x405
#define GL_BACK_LEFT 0x402
#define GL_BACK_RIGHT 0x403
#define GL_BGR 0x80e0
#define GL_BGRA 0x80e1
#define GL_BGRA_INTEGER 0x8d9b
#define GL_BGR_INTEGER 0x8d9a
#define GL_BLEND 0xbe2
#define GL_BLEND_DST 0xbe0
#define GL_BLEND_DST_ALPHA 0x80ca
#define GL_BLEND_DST_RGB 0x80c8
#define GL_BLEND_EQUATION_ALPHA 0x883d
#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_BLEND_SRC 0xbe1
#define GL_BLEND_SRC_ALPHA 0x80cb
#define GL_BLEND_SRC_RGB 0x80c9
#define GL_BLUE 0x1905
#define GL_BLUE_INTEGER 0x8d96
#define GL_BOOL 0x8b56
#define GL_BOOL_VEC2 0x8b57
#define GL_BOOL_VEC3 0x8b58
#define GL_BOOL_VEC4 0x8b59
#define GL_BUFFER_ACCESS 0x88bb
#define GL_BUFFER_ACCESS_FLAGS 0x911f
#define GL_BUFFER_MAPPED 0x88bc
#define GL_BUFFER_MAP_LENGTH 0x9120
#define GL_BUFFER_MAP_OFFSET 0x9121
#define GL_BUFFER_MAP_POINTER 0x88bd
#define GL_BUFFER_SIZE 0x8764
#define GL_BUFFER_USAGE 0x8765
#define GL_BYTE 0x1400
#define GL_CCW 0x901
#define GL_CLAMP_READ_COLOR 0x891c
#define GL_CLAMP_TO_BORDER 0x812d
#define GL_CLAMP_TO_EDGE 0x812f
#define GL_CLEAR 0x1500
#define GL_CLIP_DISTANCE0 0x3000
#define GL_CLIP_DISTANCE1 0x3001
#define GL_CLIP_DISTANCE2 0x3002
#define GL_CLIP_DISTANCE3 0x3003
#define GL_CLIP_DISTANCE4 0x3004
#define GL_CLIP_DISTANCE5 0x3005
#define GL_CLIP_DISTANCE6 0x3006
#define GL_CLIP_DISTANCE7 0x3007
#define GL_COLOR 0x1800
#define GL_COLOR_ATTACHMENT0 0x8ce0
#define GL_COLOR_ATTACHMENT1 0x8ce1
#define GL_COLOR_ATTACHMENT10 0x8cea
#define GL_COLOR_ATTACHMENT11 0x8ceb
#define GL_COLOR_ATTACHMENT12 0x8cec
#define GL_COLOR_ATTACHMENT13 0x8ced
#define GL_COLOR_ATTACHMENT14 0x8cee
#define GL_COLOR_ATTACHMENT15 0x8cef
#define GL_COLOR_ATTACHMENT16 0x8cf0
#define GL_COLOR_ATTACHMENT17 0x8cf1
#define GL_COLOR_ATTACHMENT18 0x8cf2
#define GL_COLOR_ATTACHMENT19 0x8cf3
#define GL_COLOR_ATTACHMENT2 0x8ce2
#define GL_COLOR_ATTACHMENT20 0x8cf4
#define GL_COLOR_ATTACHMENT21 0x8cf5
#define GL_COLOR_ATTACHMENT22 0x8cf6
#define GL_COLOR_ATTACHMENT23 0x8cf7
#define GL_COLOR_ATTACHMENT24 0x8cf8
#define GL_COLOR_ATTACHMENT25 0x8cf9
#define GL_COLOR_ATTACHMENT26 0x8cfa
#define GL_COLOR_ATTACHMENT27 0x8cfb
#define GL_COLOR_ATTACHMENT28 0x8cfc
#define GL_COLOR_ATTACHMENT29 0x8cfd
#define GL_COLOR_ATTACHMENT3 0x8ce3
#define GL_COLOR_ATTACHMENT30 0x8cfe
#define GL_COLOR_ATTACHMENT31 0x8cff
#define GL_COLOR_ATTACHMENT4 0x8ce4
#define GL_COLOR_ATTACHMENT5 0x8ce5
#define GL_COLOR_ATTACHMENT6 0x8ce6
#define GL_COLOR_ATTACHMENT7 0x8ce7
#define GL_COLOR_ATTACHMENT8 0x8ce8
#define GL_COLOR_ATTACHMENT9 0x8ce9
#define GL_COLOR_BUFFER_BIT 0x4000
#define GL_COLOR_CLEAR_VALUE 0xc22
#define GL_COLOR_LOGIC_OP 0xbf2
#define GL_COLOR_WRITEMASK 0xc23
#define GL_COMPARE_REF_TO_TEXTURE 0x884e
#define GL_COMPILE_STATUS 0x8b81
#define GL_COMPRESSED_RED 0x8225
#define GL_COMPRESSED_RED_RGTC1 0x8dbb
#define GL_COMPRESSED_RG 0x8226
#define GL_COMPRESSED_RGB 0x84ed
#define GL_COMPRESSED_RGBA 0x84ee
#define GL_COMPRESSED_RG_RGTC2 0x8dbd
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8dbc
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8dbe
#define GL_COMPRESSED_SRGB 0x8c48
#define GL_COMPRESSED_SRGB_ALPHA 0x8c49
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86a3
#define GL_CONDITION_SATISFIED 0x911c
#define GL_CONSTANT_ALPHA 0x8003
#define GL_CONSTANT_COLOR 0x8001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x2
#define GL_CONTEXT_CORE_PROFILE_BIT 0x1
#define GL_CONTEXT_FLAGS 0x821e
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x1
#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_COPY 0x1503
#define GL_COPY_INVERTED 0x150c
#define GL_COPY_READ_BUFFER 0x8f36
#define GL_COPY_WRITE_BUFFER 0x8f37
#define GL_CULL_FACE 0xb44
#define GL_CULL_FACE_MODE 0xb45
#define GL_CURRENT_PROGRAM 0x8b8d
#define GL_CURRENT_QUERY 0x8865
#define GL_CURRENT_VERTEX_ATTRIB 0x8626
#define GL_CW 0x900
#define GL_DECR 0x1e03
#define GL_DECR_WRAP 0x8508
#define GL_DELETE_STATUS 0x8b80
#define GL_DEPTH 0x1801
#define GL_DEPTH24_STENCIL8 0x88f0
#define GL_DEPTH32F_STENCIL8 0x8cad
#define GL_DEPTH_ATTACHMENT 0x8d00
#define GL_DEPTH_BUFFER_BIT 0x100
#define GL_DEPTH_CLAMP 0x864f
#define GL_DEPTH_CLEAR_VALUE 0xb73
#define GL_DEPTH_COMPONENT 0x1902
#define GL_DEPTH_COMPONENT16 0x81a5
#define GL_DEPTH_COMPONENT24 0x81a6
#define GL_DEPTH_COMPONENT32 0x81a7
#define GL_DEPTH_COMPONENT32F 0x8cac
#define GL_DEPTH_FUNC 0xb74
#define GL_DEPTH_RANGE 0xb70
#define GL_DEPTH_STENCIL 0x84f9
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821a
#define GL_DEPTH_TEST 0xb71
#define GL_DEPTH_WRITEMASK 0xb72
#define GL_DITHER 0xbd0
#define GL_DONT_CARE 0x1100
#define GL_DOUBLE 0x140a
#define GL_DOUBLEBUFFER 0xc32
#define GL_DRAW_BUFFER 0xc01
#define GL_DRAW_BUFFER0 0x8825
#define GL_DRAW_BUFFER1 0x8826
#define GL_DRAW_BUFFER10 0x882f
#define GL_DRAW_BUFFER11 0x8830
#define GL_DRAW_BUFFER12 0x8831
#define GL_DRAW_BUFFER13 0x8832
#define GL_DRAW_BUFFER14 0x8833
#define GL_DRAW_BUFFER15 0x8834
#define GL_DRAW_BUFFER2 0x8827
#define GL_DRAW_BUFFER3 0x8828
#define GL_DRAW_BUFFER4 0x8829
#define GL_DRAW_BUFFER5 0x882a
#define GL_DRAW_BUFFER6 0x882b
#define GL_DRAW_BUFFER7 0x882c
#define GL_DRAW_BUFFER8 0x882d
#define GL_DRAW_BUFFER9 0x882e
#define GL_DRAW_FRAMEBUFFER 0x8ca9
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8ca6
#define GL_DST_ALPHA 0x304
#define GL_DST_COLOR 0x306
#define GL_DYNAMIC_COPY 0x88ea
#define GL_DYNAMIC_DRAW 0x88e8
#define GL_DYNAMIC_READ 0x88e9
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_EQUAL 0x202
#define GL_EQUIV 0x1509
#define GL_EXTENSIONS 0x1f03
#define GL_FALSE 0x0
#define GL_FASTEST 0x1101
#define GL_FILL 0x1b02
#define GL_FIRST_VERTEX_CONVENTION 0x8e4d
#define GL_FIXED_ONLY 0x891d
#define GL_FLOAT 0x1406
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8dad
#define GL_FLOAT_MAT2 0x8b5a
#define GL_FLOAT_MAT2x3 0x8b65
#define GL_FLOAT_MAT2x4 0x8b66
#define GL_FLOAT_MAT3 0x8b5b
#define GL_FLOAT_MAT3x2 0x8b67
#define GL_FLOAT_MAT3x4 0x8b68
#define GL_FLOAT_MAT4 0x8b5c
#define GL_FLOAT_MAT4x2 0x8b69
#define GL_FLOAT_MAT4x3 0x8b6a
#define GL_FLOAT_VEC2 0x8b50
#define GL_FLOAT_VEC3 0x8b51
#define GL_FLOAT_VEC4 0x8b52
#define GL_FRAGMENT_SHADER 0x8b30
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8b8b
#define GL_FRAMEBUFFER 0x8d40
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8da7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8cd1
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8cd0
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8cd3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8cd4
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8cd2
#define GL_FRAMEBUFFER_BINDING 0x8ca6
#define GL_FRAMEBUFFER_COMPLETE 0x8cd5
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8cd6
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8cdb
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8da8
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8cd7
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8d56
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8cdc
#define GL_FRAMEBUFFER_SRGB 0x8db9
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8cdd
#define GL_FRONT 0x404
#define GL_FRONT_AND_BACK 0x408
#define GL_FRONT_FACE 0xb46
#define GL_FRONT_LEFT 0x400
#define GL_FRONT_RIGHT 0x401
#define GL_FUNC_ADD 0x8006
#define GL_FUNC_REVERSE_SUBTRACT 0x800b
#define GL_FUNC_SUBTRACT 0x800a
#define GL_GEOMETRY_INPUT_TYPE 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#define GL_GEOMETRY_SHADER 0x8dd9
#define GL_GEOMETRY_VERTICES_OUT 0x8916
#define GL_GEQUAL 0x206
#define GL_GREATER 0x204
#define GL_GREEN 0x1904
#define GL_GREEN_INTEGER 0x8d95
#define GL_HALF_FLOAT 0x140b
#define GL_INCR 0x1e02
#define GL_INCR_WRAP 0x8507
#define GL_INFO_LOG_LENGTH 0x8b84
#define GL_INT 0x1404
#define GL_INTERLEAVED_ATTRIBS 0x8c8c
#define GL_INT_SAMPLER_1D 0x8dc9
#define GL_INT_SAMPLER_1D_ARRAY 0x8dce
#define GL_INT_SAMPLER_2D 0x8dca
#define GL_INT_SAMPLER_2D_ARRAY 0x8dcf
#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910c
#define GL_INT_SAMPLER_2D_RECT 0x8dcd
#define GL_INT_SAMPLER_3D 0x8dcb
#define GL_INT_SAMPLER_BUFFER 0x8dd0
#define GL_INT_SAMPLER_CUBE 0x8dcc
#define GL_INT_VEC2 0x8b53
#define GL_INT_VEC3 0x8b54
#define GL_INT_VEC4 0x8b55
#define GL_INVALID_ENUM 0x500
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x506
#define GL_INVALID_INDEX 0xffffffff
#define GL_INVALID_OPERATION 0x502
#define GL_INVALID_VALUE 0x501
#define GL_INVERT 0x150a
#define GL_KEEP 0x1e00
#define GL_LAST_VERTEX_CONVENTION 0x8e4e
#define GL_LEFT 0x406
#define GL_LEQUAL 0x203
#define GL_LESS 0x201
#define GL_LINE 0x1b01
#define GL_LINEAR 0x2601
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINES 0x1
#define GL_LINES_ADJACENCY 0xa
#define GL_LINE_LOOP 0x2
#define GL_LINE_SMOOTH 0xb20
#define GL_LINE_SMOOTH_HINT 0xc52
#define GL_LINE_STRIP 0x3
#define GL_LINE_STRIP_ADJACENCY 0xb
#define GL_LINE_WIDTH 0xb21
#define GL_LINE_WIDTH_GRANULARITY 0xb23
#define GL_LINE_WIDTH_RANGE 0xb22
#define GL_LINK_STATUS 0x8b82
#define GL_LOGIC_OP_MODE 0xbf0
#define GL_LOWER_LEFT 0x8ca1
#define GL_MAJOR_VERSION 0x821b
#define GL_MAP_FLUSH_EXPLICIT_BIT 0x10
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x8
#define GL_MAP_INVALIDATE_RANGE_BIT 0x4
#define GL_MAP_READ_BIT 0x1
#define GL_MAP_UNSYNCHRONIZED_BIT 0x20
#define GL_MAP_WRITE_BIT 0x2
#define GL_MAX 0x8008
#define GL_MAX_3D_TEXTURE_SIZE 0x8073
#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88ff
#define GL_MAX_CLIP_DISTANCES 0xd32
#define GL_MAX_COLOR_ATTACHMENTS 0x8cdf
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910e
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8a33
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8a32
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8b4d
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8a2e
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8a31
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851c
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910f
#define GL_MAX_DRAW_BUFFERS 0x8824
#define GL_MAX_ELEMENTS_INDICES 0x80e9
#define GL_MAX_ELEMENTS_VERTICES 0x80e8
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8a2d
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8b49
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8de0
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8c29
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8de1
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8a2c
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8ddf
#define GL_MAX_INTEGER_SAMPLES 0x9110
#define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#define GL_MAX_RECTANGLE_TEXTURE_SIZE 0x84f8
#define GL_MAX_RENDERBUFFER_SIZE 0x84e8
#define GL_MAX_SAMPLES 0x8d57
#define GL_MAX_SAMPLE_MASK_WORDS 0x8e59
#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_MAX_TEXTURE_BUFFER_SIZE 0x8c2b
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_MAX_TEXTURE_LOD_BIAS 0x84fd
#define GL_MAX_TEXTURE_SIZE 0xd33
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8c8a
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8c8b
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8c80
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8a30
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8a2f
#define GL_MAX_VARYING_COMPONENTS 0x8b4b
#define GL_MAX_VARYING_FLOATS 0x8b4b
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8b4c
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8a2b
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8b4a
#define GL_MAX_VIEWPORT_DIMS 0xd3a
#define GL_MIN 0x8007
#define GL_MINOR_VERSION 0x821c
#define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#define GL_MIRRORED_REPEAT 0x8370
#define GL_MULTISAMPLE 0x809d
#define GL_NAND 0x150e
#define GL_NEAREST 0x2600
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_NEVER 0x200
#define GL_NICEST 0x1102
#define GL_NONE 0x0
#define GL_NOOP 0x1505
#define GL_NOR 0x1508
#define GL_NOTEQUAL 0x205
#define GL_NO_ERROR 0x0
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86a2
#define GL_NUM_EXTENSIONS 0x821d
#define GL_OBJECT_TYPE 0x9112
#define GL_ONE 0x1
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_ONE_MINUS_DST_ALPHA 0x305
#define GL_ONE_MINUS_DST_COLOR 0x307
#define GL_ONE_MINUS_SRC_ALPHA 0x303
#define GL_ONE_MINUS_SRC_COLOR 0x301
#define GL_OR 0x1507
#define GL_OR_INVERTED 0x150d
#define GL_OR_REVERSE 0x150b
#define GL_OUT_OF_MEMORY 0x505
#define GL_PACK_ALIGNMENT 0xd05
#define GL_PACK_IMAGE_HEIGHT 0x806c
#define GL_PACK_LSB_FIRST 0xd01
#define GL_PACK_ROW_LENGTH 0xd02
#define GL_PACK_SKIP_IMAGES 0x806b
#define GL_PACK_SKIP_PIXELS 0xd04
#define GL_PACK_SKIP_ROWS 0xd03
#define GL_PACK_SWAP_BYTES 0xd00
#define GL_PIXEL_PACK_BUFFER 0x88eb
#define GL_PIXEL_PACK_BUFFER_BINDING 0x88ed
#define GL_PIXEL_UNPACK_BUFFER 0x88ec
#define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88ef
#define GL_POINT 0x1b00
#define GL_POINTS 0x0
#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#define GL_POINT_SIZE 0xb11
#define GL_POINT_SIZE_GRANULARITY 0xb13
#define GL_POINT_SIZE_RANGE 0xb12
#define GL_POINT_SPRITE_COORD_ORIGIN 0x8ca0
#define GL_POLYGON_MODE 0xb40
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_POLYGON_OFFSET_LINE 0x2a02
#define GL_POLYGON_OFFSET_POINT 0x2a01
#define GL_POLYGON_OFFSET_UNITS 0x2a00
#define GL_POLYGON_SMOOTH 0xb41
#define GL_POLYGON_SMOOTH_HINT 0xc53
#define GL_PRIMITIVES_GENERATED 0x8c87
#define GL_PRIMITIVE_RESTART 0x8f9d
#define GL_PRIMITIVE_RESTART_INDEX 0x8f9e
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_PROVOKING_VERTEX 0x8e4f
#define GL_PROXY_TEXTURE_1D 0x8063
#define GL_PROXY_TEXTURE_1D_ARRAY 0x8c19
#define GL_PROXY_TEXTURE_2D 0x8064
#define GL_PROXY_TEXTURE_2D_ARRAY 0x8c1b
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_PROXY_TEXTURE_3D 0x8070
#define GL_PROXY_TEXTURE_CUBE_MAP 0x851b
#define GL_PROXY_TEXTURE_RECTANGLE 0x84f7
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8e4c
#define GL_QUERY_BY_REGION_NO_WAIT 0x8e16
#define GL_QUERY_BY_REGION_WAIT 0x8e15
#define GL_QUERY_COUNTER_BITS 0x8864
#define GL_QUERY_NO_WAIT 0x8e14
#define GL_QUERY_RESULT 0x8866
#define GL_QUERY_RESULT_AVAILABLE 0x8867
#define GL_QUERY_WAIT 0x8e13
#define GL_R11F_G11F_B10F 0x8c3a
#define GL_R16 0x822a
#define GL_R16F 0x822d
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R16_SNORM 0x8f98
#define GL_R32F 0x822e
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_R3_G3_B2 0x2a10
#define GL_R8 0x8229
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R8_SNORM 0x8f94
#define GL_RASTERIZER_DISCARD 0x8c89
#define GL_READ_BUFFER 0xc02
#define GL_READ_FRAMEBUFFER 0x8ca8
#define GL_READ_FRAMEBUFFER_BINDING 0x8caa
#define GL_READ_ONLY 0x88b8
#define GL_READ_WRITE 0x88ba
#define GL_RED 0x1903
#define GL_RED_INTEGER 0x8d94
#define GL_RENDERBUFFER 0x8d41
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8d53
#define GL_RENDERBUFFER_BINDING 0x8ca7
#define GL_RENDERBUFFER_BLUE_SIZE 0x8d52
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8d54
#define GL_RENDERBUFFER_GREEN_SIZE 0x8d51
#define GL_RENDERBUFFER_HEIGHT 0x8d43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8d44
#define GL_RENDERBUFFER_RED_SIZE 0x8d50
#define GL_RENDERBUFFER_SAMPLES 0x8cab
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8d55
#define GL_RENDERBUFFER_WIDTH 0x8d42
#define GL_RENDERER 0x1f01
#define GL_REPEAT 0x2901
#define GL_REPLACE 0x1e01
#define GL_RG 0x8227
#define GL_RG16 0x822c
#define GL_RG16F 0x822f
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823a
#define GL_RG16_SNORM 0x8f99
#define GL_RG32F 0x8230
#define GL_RG32I 0x823b
#define GL_RG32UI 0x823c
#define GL_RG8 0x822b
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG8_SNORM 0x8f95
#define GL_RGB 0x1907
#define GL_RGB10 0x8052
#define GL_RGB10_A2 0x8059
#define GL_RGB12 0x8053
#define GL_RGB16 0x8054
#define GL_RGB16F 0x881b
#define GL_RGB16I 0x8d89
#define GL_RGB16UI 0x8d77
#define GL_RGB16_SNORM 0x8f9a
#define GL_RGB32F 0x8815
#define GL_RGB32I 0x8d83
#define GL_RGB32UI 0x8d71
#define GL_RGB4 0x804f
#define GL_RGB5 0x8050
#define GL_RGB5_A1 0x8057
#define GL_RGB8 0x8051
#define GL_RGB8I 0x8d8f
#define GL_RGB8UI 0x8d7d
#define GL_RGB8_SNORM 0x8f96
#define GL_RGB9_E5 0x8c3d
#define GL_RGBA 0x1908
#define GL_RGBA12 0x805a
#define GL_RGBA16 0x805b
#define GL_RGBA16F 0x881a
#define GL_RGBA16I 0x8d88
#define GL_RGBA16UI 0x8d76
#define GL_RGBA16_SNORM 0x8f9b
#define GL_RGBA2 0x8055
#define GL_RGBA32F 0x8814
#define GL_RGBA32I 0x8d82
#define GL_RGBA32UI 0x8d70
#define GL_RGBA4 0x8056
#define GL_RGBA8 0x8058
#define GL_RGBA8I 0x8d8e
#define GL_RGBA8UI 0x8d7c
#define GL_RGBA8_SNORM 0x8f97
#define GL_RGBA_INTEGER 0x8d99
#define GL_RGB_INTEGER 0x8d98
#define GL_RG_INTEGER 0x8228
#define GL_RIGHT 0x407
#define GL_SAMPLER_1D 0x8b5d
#define GL_SAMPLER_1D_ARRAY 0x8dc0
#define GL_SAMPLER_1D_ARRAY_SHADOW 0x8dc3
#define GL_SAMPLER_1D_SHADOW 0x8b61
#define GL_SAMPLER_2D 0x8b5e
#define GL_SAMPLER_2D_ARRAY 0x8dc1
#define GL_SAMPLER_2D_ARRAY_SHADOW 0x8dc4
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910b
#define GL_SAMPLER_2D_RECT 0x8b63
#define GL_SAMPLER_2D_RECT_SHADOW 0x8b64
#define GL_SAMPLER_2D_SHADOW 0x8b62
#define GL_SAMPLER_3D 0x8b5f
#define GL_SAMPLER_BUFFER 0x8dc2
#define GL_SAMPLER_CUBE 0x8b60
#define GL_SAMPLER_CUBE_SHADOW 0x8dc5
#define GL_SAMPLES 0x80a9
#define GL_SAMPLES_PASSED 0x8914
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809e
#define GL_SAMPLE_ALPHA_TO_ONE 0x809f
#define GL_SAMPLE_BUFFERS 0x80a8
#define GL_SAMPLE_COVERAGE 0x80a0
#define GL_SAMPLE_COVERAGE_INVERT 0x80ab
#define GL_SAMPLE_COVERAGE_VALUE 0x80aa
#define GL_SAMPLE_MASK 0x8e51
#define GL_SAMPLE_MASK_VALUE 0x8e52
#define GL_SAMPLE_POSITION 0x8e50
#define GL_SCISSOR_BOX 0xc10
#define GL_SCISSOR_TEST 0xc11
#define GL_SEPARATE_ATTRIBS 0x8c8d
#define GL_SET 0x150f
#define GL_SHADER_SOURCE_LENGTH 0x8b88
#define GL_SHADER_TYPE 0x8b4f
#define GL_SHADING_LANGUAGE_VERSION 0x8b8c
#define GL_SHORT 0x1402
#define GL_SIGNALED 0x9119
#define GL_SIGNED_NORMALIZED 0x8f9c
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0xb23
#define GL_SMOOTH_LINE_WIDTH_RANGE 0xb22
#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0xb13
#define GL_SMOOTH_POINT_SIZE_RANGE 0xb12
#define GL_SRC1_ALPHA 0x8589
#define GL_SRC_ALPHA 0x302
#define GL_SRC_ALPHA_SATURATE 0x308
#define GL_SRC_COLOR 0x300
#define GL_SRGB 0x8c40
#define GL_SRGB8 0x8c41
#define GL_SRGB8_ALPHA8 0x8c43
#define GL_SRGB_ALPHA 0x8c42
#define GL_STATIC_COPY 0x88e6
#define GL_STATIC_DRAW 0x88e4
#define GL_STATIC_READ 0x88e5
#define GL_STENCIL 0x1802
#define GL_STENCIL_ATTACHMENT 0x8d20
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_STENCIL_BACK_REF 0x8ca3
#define GL_STENCIL_BACK_VALUE_MASK 0x8ca4
#define GL_STENCIL_BACK_WRITEMASK 0x8ca5
#define GL_STENCIL_BUFFER_BIT 0x400
#define GL_STENCIL_CLEAR_VALUE 0xb91
#define GL_STENCIL_FAIL 0xb94
#define GL_STENCIL_FUNC 0xb92
#define GL_STENCIL_INDEX 0x1901
#define GL_STENCIL_INDEX1 0x8d46
#define GL_STENCIL_INDEX16 0x8d49
#define GL_STENCIL_INDEX4 0x8d47
#define GL_STENCIL_INDEX8 0x8d48
#define GL_STENCIL_PASS_DEPTH_FAIL 0xb95
#define GL_STENCIL_PASS_DEPTH_PASS 0xb96
#define GL_STENCIL_REF 0xb97
#define GL_STENCIL_TEST 0xb90
#define GL_STENCIL_VALUE_MASK 0xb93
#define GL_STENCIL_WRITEMASK 0xb98
#define GL_STEREO 0xc33
#define GL_STREAM_COPY 0x88e2
#define GL_STREAM_DRAW 0x88e0
#define GL_STREAM_READ 0x88e1
#define GL_SUBPIXEL_BITS 0xd50
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x1
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_SYNC_STATUS 0x9114
#define GL_TEXTURE 0x1702
#define GL_TEXTURE0 0x84c0
#define GL_TEXTURE1 0x84c1
#define GL_TEXTURE10 0x84ca
#define GL_TEXTURE11 0x84cb
#define GL_TEXTURE12 0x84cc
#define GL_TEXTURE13 0x84cd
#define GL_TEXTURE14 0x84ce
#define GL_TEXTURE15 0x84cf
#define GL_TEXTURE16 0x84d0
#define GL_TEXTURE17 0x84d1
#define GL_TEXTURE18 0x84d2
#define GL_TEXTURE19 0x84d3
#define GL_TEXTURE2 0x84c2
#define GL_TEXTURE20 0x84d4
#define GL_TEXTURE21 0x84d5
#define GL_TEXTURE22 0x84d6
#define GL_TEXTURE23 0x84d7
#define GL_TEXTURE24 0x84d8
#define GL_TEXTURE25 0x84d9
#define GL_TEXTURE26 0x84da
#define GL_TEXTURE27 0x84db
#define GL_TEXTURE28 0x84dc
#define GL_TEXTURE29 0x84dd
#define GL_TEXTURE3 0x84c3
#define GL_TEXTURE30 0x84de
#define GL_TEXTURE31 0x84df
#define GL_TEXTURE4 0x84c4
#define GL_TEXTURE5 0x84c5
#define GL_TEXTURE6 0x84c6
#define GL_TEXTURE7 0x84c7
#define GL_TEXTURE8 0x84c8
#define GL_TEXTURE9 0x84c9
#define GL_TEXTURE_1D 0xde0
#define GL_TEXTURE_1D_ARRAY 0x8c18
#define GL_TEXTURE_2D 0xde1
#define GL_TEXTURE_2D_ARRAY 0x8c1a
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_TEXTURE_3D 0x806f
#define GL_TEXTURE_ALPHA_SIZE 0x805f
#define GL_TEXTURE_ALPHA_TYPE 0x8c13
#define GL_TEXTURE_BASE_LEVEL 0x813c
#define GL_TEXTURE_BINDING_1D 0x8068
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8c1c
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8c1d
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_BINDING_3D 0x806a
#define GL_TEXTURE_BINDING_BUFFER 0x8c2c
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_BINDING_RECTANGLE 0x84f6
#define GL_TEXTURE_BLUE_SIZE 0x805e
#define GL_TEXTURE_BLUE_TYPE 0x8c12
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_TEXTURE_BUFFER 0x8c2a
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8c2d
#define GL_TEXTURE_COMPARE_FUNC 0x884d
#define GL_TEXTURE_COMPARE_MODE 0x884c
#define GL_TEXTURE_COMPRESSED 0x86a1
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86a0
#define GL_TEXTURE_COMPRESSION_HINT 0x84ef
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851a
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884f
#define GL_TEXTURE_DEPTH 0x8071
#define GL_TEXTURE_DEPTH_SIZE 0x884a
#define GL_TEXTURE_DEPTH_TYPE 0x8c16
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_TEXTURE_GREEN_SIZE 0x805d
#define GL_TEXTURE_GREEN_TYPE 0x8c11
#define GL_TEXTURE_HEIGHT 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#define GL_TEXTURE_LOD_BIAS 0x8501
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MAX_LEVEL 0x813d
#define GL_TEXTURE_MAX_LOD 0x813b
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MIN_LOD 0x813a
#define GL_TEXTURE_RECTANGLE 0x84f5
#define GL_TEXTURE_RED_SIZE 0x805c
#define GL_TEXTURE_RED_TYPE 0x8c10
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_TEXTURE_SHARED_SIZE 0x8c3f
#define GL_TEXTURE_STENCIL_SIZE 0x88f1
#define GL_TEXTURE_WIDTH 0x1000
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TIMEOUT_EXPIRED 0x911b
#define GL_TIMEOUT_IGNORED 0xffffffff
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8c8e
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8c8f
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8c7f
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8c85
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8c84
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8c88
#define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8c83
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8c76
#define GL_TRIANGLES 0x4
#define GL_TRIANGLES_ADJACENCY 0xc
#define GL_TRIANGLE_FAN 0x6
#define GL_TRIANGLE_STRIP 0x5
#define GL_TRIANGLE_STRIP_ADJACENCY 0xd
#define GL_TRUE 0x1
#define GL_UNIFORM_ARRAY_STRIDE 0x8a3c
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8a42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8a43
#define GL_UNIFORM_BLOCK_BINDING 0x8a3f
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8a40
#define GL_UNIFORM_BLOCK_INDEX 0x8a3a
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8a41
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8a46
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8a45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8a44
#define GL_UNIFORM_BUFFER 0x8a11
#define GL_UNIFORM_BUFFER_BINDING 0x8a28
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8a34
#define GL_UNIFORM_BUFFER_SIZE 0x8a2a
#define GL_UNIFORM_BUFFER_START 0x8a29
#define GL_UNIFORM_IS_ROW_MAJOR 0x8a3e
#define GL_UNIFORM_MATRIX_STRIDE 0x8a3d
#define GL_UNIFORM_NAME_LENGTH 0x8a39
#define GL_UNIFORM_OFFSET 0x8a3b
#define GL_UNIFORM_SIZE 0x8a38
#define GL_UNIFORM_TYPE 0x8a37
#define GL_UNPACK_ALIGNMENT 0xcf5
#define GL_UNPACK_IMAGE_HEIGHT 0x806e
#define GL_UNPACK_LSB_FIRST 0xcf1
#define GL_UNPACK_ROW_LENGTH 0xcf2
#define GL_UNPACK_SKIP_IMAGES 0x806d
#define GL_UNPACK_SKIP_PIXELS 0xcf4
#define GL_UNPACK_SKIP_ROWS 0xcf3
#define GL_UNPACK_SWAP_BYTES 0xcf0
#define GL_UNSIGNALED 0x9118
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8c3b
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#define GL_UNSIGNED_INT_24_8 0x84fa
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_UNSIGNED_INT_5_9_9_9_REV 0x8c3e
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#define GL_UNSIGNED_INT_SAMPLER_1D 0x8dd1
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8dd6
#define GL_UNSIGNED_INT_SAMPLER_2D 0x8dd2
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8dd7
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910a
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910d
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8dd5
#define GL_UNSIGNED_INT_SAMPLER_3D 0x8dd3
#define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8dd8
#define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8dd4
#define GL_UNSIGNED_INT_VEC2 0x8dc6
#define GL_UNSIGNED_INT_VEC3 0x8dc7
#define GL_UNSIGNED_INT_VEC4 0x8dc8
#define GL_UNSIGNED_NORMALIZED 0x8c17
#define GL_UNSIGNED_SHORT 0x1403
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#define GL_UPPER_LEFT 0x8ca2
#define GL_VALIDATE_STATUS 0x8b83
#define GL_VENDOR 0x1f00
#define GL_VERSION 0x1f02
#define GL_VERTEX_ARRAY_BINDING 0x85b5
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889f
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88fd
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886a
#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#define GL_VERTEX_SHADER 0x8b31
#define GL_VIEWPORT 0xba2
#define GL_WAIT_FAILED 0x911d
#define GL_WRITE_ONLY 0x88b9
#define GL_XOR 0x1506
#define GL_ZERO 0x0

#define glActiveTexture _glplatform_glActiveTexture
extern void (*glActiveTexture)(GLenum);
#define glAttachShader _glplatform_glAttachShader
extern void (*glAttachShader)(GLuint, GLuint);
#define glBeginConditionalRender _glplatform_glBeginConditionalRender
extern void (*glBeginConditionalRender)(GLuint, GLenum);
#define glBeginQuery _glplatform_glBeginQuery
extern void (*glBeginQuery)(GLenum, GLuint);
#define glBeginTransformFeedback _glplatform_glBeginTransformFeedback
extern void (*glBeginTransformFeedback)(GLenum);
#define glBindAttribLocation _glplatform_glBindAttribLocation
extern void (*glBindAttribLocation)(GLuint, GLuint, const GLchar *);
#define glBindBuffer _glplatform_glBindBuffer
extern void (*glBindBuffer)(GLenum, GLuint);
#define glBindBufferBase _glplatform_glBindBufferBase
extern void (*glBindBufferBase)(GLenum, GLuint, GLuint);
#define glBindBufferRange _glplatform_glBindBufferRange
extern void (*glBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glBindFragDataLocation _glplatform_glBindFragDataLocation
extern void (*glBindFragDataLocation)(GLuint, GLuint, const GLchar *);
#define glBindFramebuffer _glplatform_glBindFramebuffer
extern void (*glBindFramebuffer)(GLenum, GLuint);
#define glBindRenderbuffer _glplatform_glBindRenderbuffer
extern void (*glBindRenderbuffer)(GLenum, GLuint);
#define glBindTexture _glplatform_glBindTexture
extern void (*glBindTexture)(GLenum, GLuint);
#define glBindVertexArray _glplatform_glBindVertexArray
extern void (*glBindVertexArray)(GLuint);
#define glBlendColor _glplatform_glBlendColor
extern void (*glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat);
#define glBlendEquation _glplatform_glBlendEquation
extern void (*glBlendEquation)(GLenum);
#define glBlendEquationSeparate _glplatform_glBlendEquationSeparate
extern void (*glBlendEquationSeparate)(GLenum, GLenum);
#define glBlendFunc _glplatform_glBlendFunc
extern void (*glBlendFunc)(GLenum, GLenum);
#define glBlendFuncSeparate _glplatform_glBlendFuncSeparate
extern void (*glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum);
#define glBlitFramebuffer _glplatform_glBlitFramebuffer
extern void (*glBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glBufferData _glplatform_glBufferData
extern void (*glBufferData)(GLenum, GLsizeiptr, const void *, GLenum);
#define glBufferSubData _glplatform_glBufferSubData
extern void (*glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *);
#define glCheckFramebufferStatus _glplatform_glCheckFramebufferStatus
extern GLenum (*glCheckFramebufferStatus)(GLenum);
#define glClampColor _glplatform_glClampColor
extern void (*glClampColor)(GLenum, GLenum);
#define glClear _glplatform_glClear
extern void (*glClear)(GLbitfield);
#define glClearBufferfi _glplatform_glClearBufferfi
extern void (*glClearBufferfi)(GLenum, GLint, GLfloat, GLint);
#define glClearBufferfv _glplatform_glClearBufferfv
extern void (*glClearBufferfv)(GLenum, GLint, const GLfloat *);
#define glClearBufferiv _glplatform_glClearBufferiv
extern void (*glClearBufferiv)(GLenum, GLint, const GLint *);
#define glClearBufferuiv _glplatform_glClearBufferuiv
extern void (*glClearBufferuiv)(GLenum, GLint, const GLuint *);
#define glClearColor _glplatform_glClearColor
extern void (*glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
#define glClearDepth _glplatform_glClearDepth
extern void (*glClearDepth)(GLdouble);
#define glClearStencil _glplatform_glClearStencil
extern void (*glClearStencil)(GLint);
#define glClientWaitSync _glplatform_glClientWaitSync
extern GLenum (*glClientWaitSync)(GLsync, GLbitfield, GLuint64);
#define glColorMask _glplatform_glColorMask
extern void (*glColorMask)(GLboolean, GLboolean, GLboolean, GLboolean);
#define glColorMaski _glplatform_glColorMaski
extern void (*glColorMaski)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
#define glCompileShader _glplatform_glCompileShader
extern void (*glCompileShader)(GLuint);
#define glCompressedTexImage1D _glplatform_glCompressedTexImage1D
extern void (*glCompressedTexImage1D)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexImage2D _glplatform_glCompressedTexImage2D
extern void (*glCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexImage3D _glplatform_glCompressedTexImage3D
extern void (*glCompressedTexImage3D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
#define glCompressedTexSubImage1D _glplatform_glCompressedTexSubImage1D
extern void (*glCompressedTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTexSubImage2D _glplatform_glCompressedTexSubImage2D
extern void (*glCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTexSubImage3D _glplatform_glCompressedTexSubImage3D
extern void (*glCompressedTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCopyBufferSubData _glplatform_glCopyBufferSubData
extern void (*glCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
#define glCopyTexImage1D _glplatform_glCopyTexImage1D
extern void (*glCopyTexImage1D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
#define glCopyTexImage2D _glplatform_glCopyTexImage2D
extern void (*glCopyTexImage2D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
#define glCopyTexSubImage1D _glplatform_glCopyTexSubImage1D
extern void (*glCopyTexSubImage1D)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
#define glCopyTexSubImage2D _glplatform_glCopyTexSubImage2D
extern void (*glCopyTexSubImage2D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTexSubImage3D _glplatform_glCopyTexSubImage3D
extern void (*glCopyTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCreateProgram _glplatform_glCreateProgram
extern GLuint (*glCreateProgram)();
#define glCreateShader _glplatform_glCreateShader
extern GLuint (*glCreateShader)(GLenum);
#define glCullFace _glplatform_glCullFace
extern void (*glCullFace)(GLenum);
#define glDeleteBuffers _glplatform_glDeleteBuffers
extern void (*glDeleteBuffers)(GLsizei, const GLuint *);
#define glDeleteFramebuffers _glplatform_glDeleteFramebuffers
extern void (*glDeleteFramebuffers)(GLsizei, const GLuint *);
#define glDeleteProgram _glplatform_glDeleteProgram
extern void (*glDeleteProgram)(GLuint);
#define glDeleteQueries _glplatform_glDeleteQueries
extern void (*glDeleteQueries)(GLsizei, const GLuint *);
#define glDeleteRenderbuffers _glplatform_glDeleteRenderbuffers
extern void (*glDeleteRenderbuffers)(GLsizei, const GLuint *);
#define glDeleteShader _glplatform_glDeleteShader
extern void (*glDeleteShader)(GLuint);
#define glDeleteSync _glplatform_glDeleteSync
extern void (*glDeleteSync)(GLsync);
#define glDeleteTextures _glplatform_glDeleteTextures
extern void (*glDeleteTextures)(GLsizei, const GLuint *);
#define glDeleteVertexArrays _glplatform_glDeleteVertexArrays
extern void (*glDeleteVertexArrays)(GLsizei, const GLuint *);
#define glDepthFunc _glplatform_glDepthFunc
extern void (*glDepthFunc)(GLenum);
#define glDepthMask _glplatform_glDepthMask
extern void (*glDepthMask)(GLboolean);
#define glDepthRange _glplatform_glDepthRange
extern void (*glDepthRange)(GLdouble, GLdouble);
#define glDetachShader _glplatform_glDetachShader
extern void (*glDetachShader)(GLuint, GLuint);
#define glDisable _glplatform_glDisable
extern void (*glDisable)(GLenum);
#define glDisableVertexAttribArray _glplatform_glDisableVertexAttribArray
extern void (*glDisableVertexAttribArray)(GLuint);
#define glDisablei _glplatform_glDisablei
extern void (*glDisablei)(GLenum, GLuint);
#define glDrawArrays _glplatform_glDrawArrays
extern void (*glDrawArrays)(GLenum, GLint, GLsizei);
#define glDrawArraysInstanced _glplatform_glDrawArraysInstanced
extern void (*glDrawArraysInstanced)(GLenum, GLint, GLsizei, GLsizei);
#define glDrawBuffer _glplatform_glDrawBuffer
extern void (*glDrawBuffer)(GLenum);
#define glDrawBuffers _glplatform_glDrawBuffers
extern void (*glDrawBuffers)(GLsizei, const GLenum *);
#define glDrawElements _glplatform_glDrawElements
extern void (*glDrawElements)(GLenum, GLsizei, GLenum, const void *);
#define glDrawElementsBaseVertex _glplatform_glDrawElementsBaseVertex
extern void (*glDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint);
#define glDrawElementsInstanced _glplatform_glDrawElementsInstanced
extern void (*glDrawElementsInstanced)(GLenum, GLsizei, GLenum, const void *, GLsizei);
#define glDrawElementsInstancedBaseVertex _glplatform_glDrawElementsInstancedBaseVertex
extern void (*glDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
#define glDrawRangeElements _glplatform_glDrawRangeElements
extern void (*glDrawRangeElements)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
#define glDrawRangeElementsBaseVertex _glplatform_glDrawRangeElementsBaseVertex
extern void (*glDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
#define glEnable _glplatform_glEnable
extern void (*glEnable)(GLenum);
#define glEnableVertexAttribArray _glplatform_glEnableVertexAttribArray
extern void (*glEnableVertexAttribArray)(GLuint);
#define glEnablei _glplatform_glEnablei
extern void (*glEnablei)(GLenum, GLuint);
#define glEndConditionalRender _glplatform_glEndConditionalRender
extern void (*glEndConditionalRender)();
#define glEndQuery _glplatform_glEndQuery
extern void (*glEndQuery)(GLenum);
#define glEndTransformFeedback _glplatform_glEndTransformFeedback
extern void (*glEndTransformFeedback)();
#define glFenceSync _glplatform_glFenceSync
extern GLsync (*glFenceSync)(GLenum, GLbitfield);
#define glFinish _glplatform_glFinish
extern void (*glFinish)();
#define glFlush _glplatform_glFlush
extern void (*glFlush)();
#define glFlushMappedBufferRange _glplatform_glFlushMappedBufferRange
extern void (*glFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr);
#define glFramebufferRenderbuffer _glplatform_glFramebufferRenderbuffer
extern void (*glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint);
#define glFramebufferTexture _glplatform_glFramebufferTexture
extern void (*glFramebufferTexture)(GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture1D _glplatform_glFramebufferTexture1D
extern void (*glFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture2D _glplatform_glFramebufferTexture2D
extern void (*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture3D _glplatform_glFramebufferTexture3D
extern void (*glFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
#define glFramebufferTextureLayer _glplatform_glFramebufferTextureLayer
extern void (*glFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint);
#define glFrontFace _glplatform_glFrontFace
extern void (*glFrontFace)(GLenum);
#define glGenBuffers _glplatform_glGenBuffers
extern void (*glGenBuffers)(GLsizei, GLuint *);
#define glGenFramebuffers _glplatform_glGenFramebuffers
extern void (*glGenFramebuffers)(GLsizei, GLuint *);
#define glGenQueries _glplatform_glGenQueries
extern void (*glGenQueries)(GLsizei, GLuint *);
#define glGenRenderbuffers _glplatform_glGenRenderbuffers
extern void (*glGenRenderbuffers)(GLsizei, GLuint *);
#define glGenTextures _glplatform_glGenTextures
extern void (*glGenTextures)(GLsizei, GLuint *);
#define glGenVertexArrays _glplatform_glGenVertexArrays
extern void (*glGenVertexArrays)(GLsizei, GLuint *);
#define glGenerateMipmap _glplatform_glGenerateMipmap
extern void (*glGenerateMipmap)(GLenum);
#define glGetActiveAttrib _glplatform_glGetActiveAttrib
extern void (*glGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
#define glGetActiveUniform _glplatform_glGetActiveUniform
extern void (*glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
#define glGetActiveUniformBlockName _glplatform_glGetActiveUniformBlockName
extern void (*glGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformBlockiv _glplatform_glGetActiveUniformBlockiv
extern void (*glGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *);
#define glGetActiveUniformName _glplatform_glGetActiveUniformName
extern void (*glGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformsiv _glplatform_glGetActiveUniformsiv
extern void (*glGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
#define glGetAttachedShaders _glplatform_glGetAttachedShaders
extern void (*glGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *);
#define glGetAttribLocation _glplatform_glGetAttribLocation
extern GLint (*glGetAttribLocation)(GLuint, const GLchar *);
#define glGetBooleani_v _glplatform_glGetBooleani_v
extern void (*glGetBooleani_v)(GLenum, GLuint, GLboolean *);
#define glGetBooleanv _glplatform_glGetBooleanv
extern void (*glGetBooleanv)(GLenum, GLboolean *);
#define glGetBufferParameteri64v _glplatform_glGetBufferParameteri64v
extern void (*glGetBufferParameteri64v)(GLenum, GLenum, GLint64 *);
#define glGetBufferParameteriv _glplatform_glGetBufferParameteriv
extern void (*glGetBufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetBufferPointerv _glplatform_glGetBufferPointerv
extern void (*glGetBufferPointerv)(GLenum, GLenum, void **);
#define glGetBufferSubData _glplatform_glGetBufferSubData
extern void (*glGetBufferSubData)(GLenum, GLintptr, GLsizeiptr, void *);
#define glGetCompressedTexImage _glplatform_glGetCompressedTexImage
extern void (*glGetCompressedTexImage)(GLenum, GLint, void *);
#define glGetDoublev _glplatform_glGetDoublev
extern void (*glGetDoublev)(GLenum, GLdouble *);
#define glGetError _glplatform_glGetError
extern GLenum (*glGetError)();
#define glGetFloatv _glplatform_glGetFloatv
extern void (*glGetFloatv)(GLenum, GLfloat *);
#define glGetFragDataLocation _glplatform_glGetFragDataLocation
extern GLint (*glGetFragDataLocation)(GLuint, const GLchar *);
#define glGetFramebufferAttachmentParameteriv _glplatform_glGetFramebufferAttachmentParameteriv
extern void (*glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *);
#define glGetInteger64i_v _glplatform_glGetInteger64i_v
extern void (*glGetInteger64i_v)(GLenum, GLuint, GLint64 *);
#define glGetInteger64v _glplatform_glGetInteger64v
extern void (*glGetInteger64v)(GLenum, GLint64 *);
#define glGetIntegeri_v _glplatform_glGetIntegeri_v
extern void (*glGetIntegeri_v)(GLenum, GLuint, GLint *);
#define glGetIntegerv _glplatform_glGetIntegerv
extern void (*glGetIntegerv)(GLenum, GLint *);
#define glGetMultisamplefv _glplatform_glGetMultisamplefv
extern void (*glGetMultisamplefv)(GLenum, GLuint, GLfloat *);
#define glGetProgramInfoLog _glplatform_glGetProgramInfoLog
extern void (*glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramiv _glplatform_glGetProgramiv
extern void (*glGetProgramiv)(GLuint, GLenum, GLint *);
#define glGetQueryObjectiv _glplatform_glGetQueryObjectiv
extern void (*glGetQueryObjectiv)(GLuint, GLenum, GLint *);
#define glGetQueryObjectuiv _glplatform_glGetQueryObjectuiv
extern void (*glGetQueryObjectuiv)(GLuint, GLenum, GLuint *);
#define glGetQueryiv _glplatform_glGetQueryiv
extern void (*glGetQueryiv)(GLenum, GLenum, GLint *);
#define glGetRenderbufferParameteriv _glplatform_glGetRenderbufferParameteriv
extern void (*glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetShaderInfoLog _glplatform_glGetShaderInfoLog
extern void (*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetShaderSource _glplatform_glGetShaderSource
extern void (*glGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetShaderiv _glplatform_glGetShaderiv
extern void (*glGetShaderiv)(GLuint, GLenum, GLint *);
#define glGetString _glplatform_glGetString
extern const GLubyte * (*glGetString)(GLenum);
#define glGetStringi _glplatform_glGetStringi
extern const GLubyte * (*glGetStringi)(GLenum, GLuint);
#define glGetSynciv _glplatform_glGetSynciv
extern void (*glGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
#define glGetTexImage _glplatform_glGetTexImage
extern void (*glGetTexImage)(GLenum, GLint, GLenum, GLenum, void *);
#define glGetTexLevelParameterfv _glplatform_glGetTexLevelParameterfv
extern void (*glGetTexLevelParameterfv)(GLenum, GLint, GLenum, GLfloat *);
#define glGetTexLevelParameteriv _glplatform_glGetTexLevelParameteriv
extern void (*glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint *);
#define glGetTexParameterIiv _glplatform_glGetTexParameterIiv
extern void (*glGetTexParameterIiv)(GLenum, GLenum, GLint *);
#define glGetTexParameterIuiv _glplatform_glGetTexParameterIuiv
extern void (*glGetTexParameterIuiv)(GLenum, GLenum, GLuint *);
#define glGetTexParameterfv _glplatform_glGetTexParameterfv
extern void (*glGetTexParameterfv)(GLenum, GLenum, GLfloat *);
#define glGetTexParameteriv _glplatform_glGetTexParameteriv
extern void (*glGetTexParameteriv)(GLenum, GLenum, GLint *);
#define glGetTransformFeedbackVarying _glplatform_glGetTransformFeedbackVarying
extern void (*glGetTransformFeedbackVarying)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
#define glGetUniformBlockIndex _glplatform_glGetUniformBlockIndex
extern GLuint (*glGetUniformBlockIndex)(GLuint, const GLchar *);
#define glGetUniformIndices _glplatform_glGetUniformIndices
extern void (*glGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *);
#define glGetUniformLocation _glplatform_glGetUniformLocation
extern GLint (*glGetUniformLocation)(GLuint, const GLchar *);
#define glGetUniformfv _glplatform_glGetUniformfv
extern void (*glGetUniformfv)(GLuint, GLint, GLfloat *);
#define glGetUniformiv _glplatform_glGetUniformiv
extern void (*glGetUniformiv)(GLuint, GLint, GLint *);
#define glGetUniformuiv _glplatform_glGetUniformuiv
extern void (*glGetUniformuiv)(GLuint, GLint, GLuint *);
#define glGetVertexAttribIiv _glplatform_glGetVertexAttribIiv
extern void (*glGetVertexAttribIiv)(GLuint, GLenum, GLint *);
#define glGetVertexAttribIuiv _glplatform_glGetVertexAttribIuiv
extern void (*glGetVertexAttribIuiv)(GLuint, GLenum, GLuint *);
#define glGetVertexAttribPointerv _glplatform_glGetVertexAttribPointerv
extern void (*glGetVertexAttribPointerv)(GLuint, GLenum, void **);
#define glGetVertexAttribdv _glplatform_glGetVertexAttribdv
extern void (*glGetVertexAttribdv)(GLuint, GLenum, GLdouble *);
#define glGetVertexAttribfv _glplatform_glGetVertexAttribfv
extern void (*glGetVertexAttribfv)(GLuint, GLenum, GLfloat *);
#define glGetVertexAttribiv _glplatform_glGetVertexAttribiv
extern void (*glGetVertexAttribiv)(GLuint, GLenum, GLint *);
#define glHint _glplatform_glHint
extern void (*glHint)(GLenum, GLenum);
#define glIsBuffer _glplatform_glIsBuffer
extern GLboolean (*glIsBuffer)(GLuint);
#define glIsEnabled _glplatform_glIsEnabled
extern GLboolean (*glIsEnabled)(GLenum);
#define glIsEnabledi _glplatform_glIsEnabledi
extern GLboolean (*glIsEnabledi)(GLenum, GLuint);
#define glIsFramebuffer _glplatform_glIsFramebuffer
extern GLboolean (*glIsFramebuffer)(GLuint);
#define glIsProgram _glplatform_glIsProgram
extern GLboolean (*glIsProgram)(GLuint);
#define glIsQuery _glplatform_glIsQuery
extern GLboolean (*glIsQuery)(GLuint);
#define glIsRenderbuffer _glplatform_glIsRenderbuffer
extern GLboolean (*glIsRenderbuffer)(GLuint);
#define glIsShader _glplatform_glIsShader
extern GLboolean (*glIsShader)(GLuint);
#define glIsSync _glplatform_glIsSync
extern GLboolean (*glIsSync)(GLsync);
#define glIsTexture _glplatform_glIsTexture
extern GLboolean (*glIsTexture)(GLuint);
#define glIsVertexArray _glplatform_glIsVertexArray
extern GLboolean (*glIsVertexArray)(GLuint);
#define glLineWidth _glplatform_glLineWidth
extern void (*glLineWidth)(GLfloat);
#define glLinkProgram _glplatform_glLinkProgram
extern void (*glLinkProgram)(GLuint);
#define glLogicOp _glplatform_glLogicOp
extern void (*glLogicOp)(GLenum);
#define glMapBuffer _glplatform_glMapBuffer
extern void * (*glMapBuffer)(GLenum, GLenum);
#define glMapBufferRange _glplatform_glMapBufferRange
extern void * (*glMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
#define glMultiDrawArrays _glplatform_glMultiDrawArrays
extern void (*glMultiDrawArrays)(GLenum, const GLint *, const GLsizei *, GLsizei);
#define glMultiDrawElements _glplatform_glMultiDrawElements
extern void (*glMultiDrawElements)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
#define glMultiDrawElementsBaseVertex _glplatform_glMultiDrawElementsBaseVertex
extern void (*glMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
#define glPixelStoref _glplatform_glPixelStoref
extern void (*glPixelStoref)(GLenum, GLfloat);
#define glPixelStorei _glplatform_glPixelStorei
extern void (*glPixelStorei)(GLenum, GLint);
#define glPointParameterf _glplatform_glPointParameterf
extern void (*glPointParameterf)(GLenum, GLfloat);
#define glPointParameterfv _glplatform_glPointParameterfv
extern void (*glPointParameterfv)(GLenum, const GLfloat *);
#define glPointParameteri _glplatform_glPointParameteri
extern void (*glPointParameteri)(GLenum, GLint);
#define glPointParameteriv _glplatform_glPointParameteriv
extern void (*glPointParameteriv)(GLenum, const GLint *);
#define glPointSize _glplatform_glPointSize
extern void (*glPointSize)(GLfloat);
#define glPolygonMode _glplatform_glPolygonMode
extern void (*glPolygonMode)(GLenum, GLenum);
#define glPolygonOffset _glplatform_glPolygonOffset
extern void (*glPolygonOffset)(GLfloat, GLfloat);
#define glPrimitiveRestartIndex _glplatform_glPrimitiveRestartIndex
extern void (*glPrimitiveRestartIndex)(GLuint);
#define glProvokingVertex _glplatform_glProvokingVertex
extern void (*glProvokingVertex)(GLenum);
#define glReadBuffer _glplatform_glReadBuffer
extern void (*glReadBuffer)(GLenum);
#define glReadPixels _glplatform_glReadPixels
extern void (*glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
#define glRenderbufferStorage _glplatform_glRenderbufferStorage
extern void (*glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei);
#define glRenderbufferStorageMultisample _glplatform_glRenderbufferStorageMultisample
extern void (*glRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#define glSampleCoverage _glplatform_glSampleCoverage
extern void (*glSampleCoverage)(GLfloat, GLboolean);
#define glSampleMaski _glplatform_glSampleMaski
extern void (*glSampleMaski)(GLuint, GLbitfield);
#define glScissor _glplatform_glScissor
extern void (*glScissor)(GLint, GLint, GLsizei, GLsizei);
#define glShaderSource _glplatform_glShaderSource
extern void (*glShaderSource)(GLuint, GLsizei, const GLchar *const*, const GLint *);
#define glStencilFunc _glplatform_glStencilFunc
extern void (*glStencilFunc)(GLenum, GLint, GLuint);
#define glStencilFuncSeparate _glplatform_glStencilFuncSeparate
extern void (*glStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint);
#define glStencilMask _glplatform_glStencilMask
extern void (*glStencilMask)(GLuint);
#define glStencilMaskSeparate _glplatform_glStencilMaskSeparate
extern void (*glStencilMaskSeparate)(GLenum, GLuint);
#define glStencilOp _glplatform_glStencilOp
extern void (*glStencilOp)(GLenum, GLenum, GLenum);
#define glStencilOpSeparate _glplatform_glStencilOpSeparate
extern void (*glStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum);
#define glTexBuffer _glplatform_glTexBuffer
extern void (*glTexBuffer)(GLenum, GLenum, GLuint);
#define glTexImage1D _glplatform_glTexImage1D
extern void (*glTexImage1D)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
#define glTexImage2D _glplatform_glTexImage2D
extern void (*glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
#define glTexImage2DMultisample _glplatform_glTexImage2DMultisample
extern void (*glTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexImage3D _glplatform_glTexImage3D
extern void (*glTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
#define glTexImage3DMultisample _glplatform_glTexImage3DMultisample
extern void (*glTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTexParameterIiv _glplatform_glTexParameterIiv
extern void (*glTexParameterIiv)(GLenum, GLenum, const GLint *);
#define glTexParameterIuiv _glplatform_glTexParameterIuiv
extern void (*glTexParameterIuiv)(GLenum, GLenum, const GLuint *);
#define glTexParameterf _glplatform_glTexParameterf
extern void (*glTexParameterf)(GLenum, GLenum, GLfloat);
#define glTexParameterfv _glplatform_glTexParameterfv
extern void (*glTexParameterfv)(GLenum, GLenum, const GLfloat *);
#define glTexParameteri _glplatform_glTexParameteri
extern void (*glTexParameteri)(GLenum, GLenum, GLint);
#define glTexParameteriv _glplatform_glTexParameteriv
extern void (*glTexParameteriv)(GLenum, GLenum, const GLint *);
#define glTexSubImage1D _glplatform_glTexSubImage1D
extern void (*glTexSubImage1D)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
#define glTexSubImage2D _glplatform_glTexSubImage2D
extern void (*glTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTexSubImage3D _glplatform_glTexSubImage3D
extern void (*glTexSubImage3D)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTransformFeedbackVaryings _glplatform_glTransformFeedbackVaryings
extern void (*glTransformFeedbackVaryings)(GLuint, GLsizei, const GLchar *const*, GLenum);
#define glUniform1f _glplatform_glUniform1f
extern void (*glUniform1f)(GLint, GLfloat);
#define glUniform1fv _glplatform_glUniform1fv
extern void (*glUniform1fv)(GLint, GLsizei, const GLfloat *);
#define glUniform1i _glplatform_glUniform1i
extern void (*glUniform1i)(GLint, GLint);
#define glUniform1iv _glplatform_glUniform1iv
extern void (*glUniform1iv)(GLint, GLsizei, const GLint *);
#define glUniform1ui _glplatform_glUniform1ui
extern void (*glUniform1ui)(GLint, GLuint);
#define glUniform1uiv _glplatform_glUniform1uiv
extern void (*glUniform1uiv)(GLint, GLsizei, const GLuint *);
#define glUniform2f _glplatform_glUniform2f
extern void (*glUniform2f)(GLint, GLfloat, GLfloat);
#define glUniform2fv _glplatform_glUniform2fv
extern void (*glUniform2fv)(GLint, GLsizei, const GLfloat *);
#define glUniform2i _glplatform_glUniform2i
extern void (*glUniform2i)(GLint, GLint, GLint);
#define glUniform2iv _glplatform_glUniform2iv
extern void (*glUniform2iv)(GLint, GLsizei, const GLint *);
#define glUniform2ui _glplatform_glUniform2ui
extern void (*glUniform2ui)(GLint, GLuint, GLuint);
#define glUniform2uiv _glplatform_glUniform2uiv
extern void (*glUniform2uiv)(GLint, GLsizei, const GLuint *);
#define glUniform3f _glplatform_glUniform3f
extern void (*glUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
#define glUniform3fv _glplatform_glUniform3fv
extern void (*glUniform3fv)(GLint, GLsizei, const GLfloat *);
#define glUniform3i _glplatform_glUniform3i
extern void (*glUniform3i)(GLint, GLint, GLint, GLint);
#define glUniform3iv _glplatform_glUniform3iv
extern void (*glUniform3iv)(GLint, GLsizei, const GLint *);
#define glUniform3ui _glplatform_glUniform3ui
extern void (*glUniform3ui)(GLint, GLuint, GLuint, GLuint);
#define glUniform3uiv _glplatform_glUniform3uiv
extern void (*glUniform3uiv)(GLint, GLsizei, const GLuint *);
#define glUniform4f _glplatform_glUniform4f
extern void (*glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glUniform4fv _glplatform_glUniform4fv
extern void (*glUniform4fv)(GLint, GLsizei, const GLfloat *);
#define glUniform4i _glplatform_glUniform4i
extern void (*glUniform4i)(GLint, GLint, GLint, GLint, GLint);
#define glUniform4iv _glplatform_glUniform4iv
extern void (*glUniform4iv)(GLint, GLsizei, const GLint *);
#define glUniform4ui _glplatform_glUniform4ui
extern void (*glUniform4ui)(GLint, GLuint, GLuint, GLuint, GLuint);
#define glUniform4uiv _glplatform_glUniform4uiv
extern void (*glUniform4uiv)(GLint, GLsizei, const GLuint *);
#define glUniformBlockBinding _glplatform_glUniformBlockBinding
extern void (*glUniformBlockBinding)(GLuint, GLuint, GLuint);
#define glUniformMatrix2fv _glplatform_glUniformMatrix2fv
extern void (*glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix2x3fv _glplatform_glUniformMatrix2x3fv
extern void (*glUniformMatrix2x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix2x4fv _glplatform_glUniformMatrix2x4fv
extern void (*glUniformMatrix2x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3fv _glplatform_glUniformMatrix3fv
extern void (*glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3x2fv _glplatform_glUniformMatrix3x2fv
extern void (*glUniformMatrix3x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix3x4fv _glplatform_glUniformMatrix3x4fv
extern void (*glUniformMatrix3x4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4fv _glplatform_glUniformMatrix4fv
extern void (*glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4x2fv _glplatform_glUniformMatrix4x2fv
extern void (*glUniformMatrix4x2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUniformMatrix4x3fv _glplatform_glUniformMatrix4x3fv
extern void (*glUniformMatrix4x3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
#define glUnmapBuffer _glplatform_glUnmapBuffer
extern GLboolean (*glUnmapBuffer)(GLenum);
#define glUseProgram _glplatform_glUseProgram
extern void (*glUseProgram)(GLuint);
#define glValidateProgram _glplatform_glValidateProgram
extern void (*glValidateProgram)(GLuint);
#define glVertexAttrib1d _glplatform_glVertexAttrib1d
extern void (*glVertexAttrib1d)(GLuint, GLdouble);
#define glVertexAttrib1dv _glplatform_glVertexAttrib1dv
extern void (*glVertexAttrib1dv)(GLuint, const GLdouble *);
#define glVertexAttrib1f _glplatform_glVertexAttrib1f
extern void (*glVertexAttrib1f)(GLuint, GLfloat);
#define glVertexAttrib1fv _glplatform_glVertexAttrib1fv
extern void (*glVertexAttrib1fv)(GLuint, const GLfloat *);
#define glVertexAttrib1s _glplatform_glVertexAttrib1s
extern void (*glVertexAttrib1s)(GLuint, GLshort);
#define glVertexAttrib1sv _glplatform_glVertexAttrib1sv
extern void (*glVertexAttrib1sv)(GLuint, const GLshort *);
#define glVertexAttrib2d _glplatform_glVertexAttrib2d
extern void (*glVertexAttrib2d)(GLuint, GLdouble, GLdouble);
#define glVertexAttrib2dv _glplatform_glVertexAttrib2dv
extern void (*glVertexAttrib2dv)(GLuint, const GLdouble *);
#define glVertexAttrib2f _glplatform_glVertexAttrib2f
extern void (*glVertexAttrib2f)(GLuint, GLfloat, GLfloat);
#define glVertexAttrib2fv _glplatform_glVertexAttrib2fv
extern void (*glVertexAttrib2fv)(GLuint, const GLfloat *);
#define glVertexAttrib2s _glplatform_glVertexAttrib2s
extern void (*glVertexAttrib2s)(GLuint, GLshort, GLshort);
#define glVertexAttrib2sv _glplatform_glVertexAttrib2sv
extern void (*glVertexAttrib2sv)(GLuint, const GLshort *);
#define glVertexAttrib3d _glplatform_glVertexAttrib3d
extern void (*glVertexAttrib3d)(GLuint, GLdouble, GLdouble, GLdouble);
#define glVertexAttrib3dv _glplatform_glVertexAttrib3dv
extern void (*glVertexAttrib3dv)(GLuint, const GLdouble *);
#define glVertexAttrib3f _glplatform_glVertexAttrib3f
extern void (*glVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat);
#define glVertexAttrib3fv _glplatform_glVertexAttrib3fv
extern void (*glVertexAttrib3fv)(GLuint, const GLfloat *);
#define glVertexAttrib3s _glplatform_glVertexAttrib3s
extern void (*glVertexAttrib3s)(GLuint, GLshort, GLshort, GLshort);
#define glVertexAttrib3sv _glplatform_glVertexAttrib3sv
extern void (*glVertexAttrib3sv)(GLuint, const GLshort *);
#define glVertexAttrib4Nbv _glplatform_glVertexAttrib4Nbv
extern void (*glVertexAttrib4Nbv)(GLuint, const GLbyte *);
#define glVertexAttrib4Niv _glplatform_glVertexAttrib4Niv
extern void (*glVertexAttrib4Niv)(GLuint, const GLint *);
#define glVertexAttrib4Nsv _glplatform_glVertexAttrib4Nsv
extern void (*glVertexAttrib4Nsv)(GLuint, const GLshort *);
#define glVertexAttrib4Nub _glplatform_glVertexAttrib4Nub
extern void (*glVertexAttrib4Nub)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
#define glVertexAttrib4Nubv _glplatform_glVertexAttrib4Nubv
extern void (*glVertexAttrib4Nubv)(GLuint, const GLubyte *);
#define glVertexAttrib4Nuiv _glplatform_glVertexAttrib4Nuiv
extern void (*glVertexAttrib4Nuiv)(GLuint, const GLuint *);
#define glVertexAttrib4Nusv _glplatform_glVertexAttrib4Nusv
extern void (*glVertexAttrib4Nusv)(GLuint, const GLushort *);
#define glVertexAttrib4bv _glplatform_glVertexAttrib4bv
extern void (*glVertexAttrib4bv)(GLuint, const GLbyte *);
#define glVertexAttrib4d _glplatform_glVertexAttrib4d
extern void (*glVertexAttrib4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glVertexAttrib4dv _glplatform_glVertexAttrib4dv
extern void (*glVertexAttrib4dv)(GLuint, const GLdouble *);
#define glVertexAttrib4f _glplatform_glVertexAttrib4f
extern void (*glVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glVertexAttrib4fv _glplatform_glVertexAttrib4fv
extern void (*glVertexAttrib4fv)(GLuint, const GLfloat *);
#define glVertexAttrib4iv _glplatform_glVertexAttrib4iv
extern void (*glVertexAttrib4iv)(GLuint, const GLint *);
#define glVertexAttrib4s _glplatform_glVertexAttrib4s
extern void (*glVertexAttrib4s)(GLuint, GLshort, GLshort, GLshort, GLshort);
#define glVertexAttrib4sv _glplatform_glVertexAttrib4sv
extern void (*glVertexAttrib4sv)(GLuint, const GLshort *);
#define glVertexAttrib4ubv _glplatform_glVertexAttrib4ubv
extern void (*glVertexAttrib4ubv)(GLuint, const GLubyte *);
#define glVertexAttrib4uiv _glplatform_glVertexAttrib4uiv
extern void (*glVertexAttrib4uiv)(GLuint, const GLuint *);
#define glVertexAttrib4usv _glplatform_glVertexAttrib4usv
extern void (*glVertexAttrib4usv)(GLuint, const GLushort *);
#define glVertexAttribI1i _glplatform_glVertexAttribI1i
extern void (*glVertexAttribI1i)(GLuint, GLint);
#define glVertexAttribI1iv _glplatform_glVertexAttribI1iv
extern void (*glVertexAttribI1iv)(GLuint, const GLint *);
#define glVertexAttribI1ui _glplatform_glVertexAttribI1ui
extern void (*glVertexAttribI1ui)(GLuint, GLuint);
#define glVertexAttribI1uiv _glplatform_glVertexAttribI1uiv
extern void (*glVertexAttribI1uiv)(GLuint, const GLuint *);
#define glVertexAttribI2i _glplatform_glVertexAttribI2i
extern void (*glVertexAttribI2i)(GLuint, GLint, GLint);
#define glVertexAttribI2iv _glplatform_glVertexAttribI2iv
extern void (*glVertexAttribI2iv)(GLuint, const GLint *);
#define glVertexAttribI2ui _glplatform_glVertexAttribI2ui
extern void (*glVertexAttribI2ui)(GLuint, GLuint, GLuint);
#define glVertexAttribI2uiv _glplatform_glVertexAttribI2uiv
extern void (*glVertexAttribI2uiv)(GLuint, const GLuint *);
#define glVertexAttribI3i _glplatform_glVertexAttribI3i
extern void (*glVertexAttribI3i)(GLuint, GLint, GLint, GLint);
#define glVertexAttribI3iv _glplatform_glVertexAttribI3iv
extern void (*glVertexAttribI3iv)(GLuint, const GLint *);
#define glVertexAttribI3ui _glplatform_glVertexAttribI3ui
extern void (*glVertexAttribI3ui)(GLuint, GLuint, GLuint, GLuint);
#define glVertexAttribI3uiv _glplatform_glVertexAttribI3uiv
extern void (*glVertexAttribI3uiv)(GLuint, const GLuint *);
#define glVertexAttribI4bv _glplatform_glVertexAttribI4bv
extern void (*glVertexAttribI4bv)(GLuint, const GLbyte *);
#define glVertexAttribI4i _glplatform_glVertexAttribI4i
extern void (*glVertexAttribI4i)(GLuint, GLint, GLint, GLint, GLint);
#define glVertexAttribI4iv _glplatform_glVertexAttribI4iv
extern void (*glVertexAttribI4iv)(GLuint, const GLint *);
#define glVertexAttribI4sv _glplatform_glVertexAttribI4sv
extern void (*glVertexAttribI4sv)(GLuint, const GLshort *);
#define glVertexAttribI4ubv _glplatform_glVertexAttribI4ubv
extern void (*glVertexAttribI4ubv)(GLuint, const GLubyte *);
#define glVertexAttribI4ui _glplatform_glVertexAttribI4ui
extern void (*glVertexAttribI4ui)(GLuint, GLuint, GLuint, GLuint, GLuint);
#define glVertexAttribI4uiv _glplatform_glVertexAttribI4uiv
extern void (*glVertexAttribI4uiv)(GLuint, const GLuint *);
#define glVertexAttribI4usv _glplatform_glVertexAttribI4usv
extern void (*glVertexAttribI4usv)(GLuint, const GLushort *);
#define glVertexAttribIPointer _glplatform_glVertexAttribIPointer
extern void (*glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
#define glVertexAttribPointer _glplatform_glVertexAttribPointer
extern void (*glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
#define glViewport _glplatform_glViewport
extern void (*glViewport)(GLint, GLint, GLsizei, GLsizei);
#define glWaitSync _glplatform_glWaitSync
extern void (*glWaitSync)(GLsync, GLbitfield, GLuint64);

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 33

#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif
#ifndef GLPLATFORM_TYPE_GLuint64
#define GLPLATFORM_TYPE_GLuint64
typedef uint64_t GLuint64;
#endif

#define GL_ANY_SAMPLES_PASSED 0x8c2f
#define GL_INT_2_10_10_10_REV 0x8d9f
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88fc
#define GL_ONE_MINUS_SRC1_ALPHA 0x88fb
#define GL_ONE_MINUS_SRC1_COLOR 0x88fa
#define GL_RGB10_A2UI 0x906f
#define GL_SAMPLER_BINDING 0x8919
#define GL_SRC1_COLOR 0x88f9
#define GL_TEXTURE_SWIZZLE_A 0x8e45
#define GL_TEXTURE_SWIZZLE_B 0x8e44
#define GL_TEXTURE_SWIZZLE_G 0x8e43
#define GL_TEXTURE_SWIZZLE_R 0x8e42
#define GL_TEXTURE_SWIZZLE_RGBA 0x8e46
#define GL_TIMESTAMP 0x8e28
#define GL_TIME_ELAPSED 0x88bf
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR 0x88fe

#define glBindFragDataLocationIndexed _glplatform_glBindFragDataLocationIndexed
extern void (*glBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *);
#define glBindSampler _glplatform_glBindSampler
extern void (*glBindSampler)(GLuint, GLuint);
#define glDeleteSamplers _glplatform_glDeleteSamplers
extern void (*glDeleteSamplers)(GLsizei, const GLuint *);
#define glGenSamplers _glplatform_glGenSamplers
extern void (*glGenSamplers)(GLsizei, GLuint *);
#define glGetFragDataIndex _glplatform_glGetFragDataIndex
extern GLint (*glGetFragDataIndex)(GLuint, const GLchar *);
#define glGetQueryObjecti64v _glplatform_glGetQueryObjecti64v
extern void (*glGetQueryObjecti64v)(GLuint, GLenum, GLint64 *);
#define glGetQueryObjectui64v _glplatform_glGetQueryObjectui64v
extern void (*glGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *);
#define glGetSamplerParameterIiv _glplatform_glGetSamplerParameterIiv
extern void (*glGetSamplerParameterIiv)(GLuint, GLenum, GLint *);
#define glGetSamplerParameterIuiv _glplatform_glGetSamplerParameterIuiv
extern void (*glGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetSamplerParameterfv _glplatform_glGetSamplerParameterfv
extern void (*glGetSamplerParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetSamplerParameteriv _glplatform_glGetSamplerParameteriv
extern void (*glGetSamplerParameteriv)(GLuint, GLenum, GLint *);
#define glIsSampler _glplatform_glIsSampler
extern GLboolean (*glIsSampler)(GLuint);
#define glQueryCounter _glplatform_glQueryCounter
extern void (*glQueryCounter)(GLuint, GLenum);
#define glSamplerParameterIiv _glplatform_glSamplerParameterIiv
extern void (*glSamplerParameterIiv)(GLuint, GLenum, const GLint *);
#define glSamplerParameterIuiv _glplatform_glSamplerParameterIuiv
extern void (*glSamplerParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glSamplerParameterf _glplatform_glSamplerParameterf
extern void (*glSamplerParameterf)(GLuint, GLenum, GLfloat);
#define glSamplerParameterfv _glplatform_glSamplerParameterfv
extern void (*glSamplerParameterfv)(GLuint, GLenum, const GLfloat *);
#define glSamplerParameteri _glplatform_glSamplerParameteri
extern void (*glSamplerParameteri)(GLuint, GLenum, GLint);
#define glSamplerParameteriv _glplatform_glSamplerParameteriv
extern void (*glSamplerParameteriv)(GLuint, GLenum, const GLint *);
#define glVertexAttribDivisor _glplatform_glVertexAttribDivisor
extern void (*glVertexAttribDivisor)(GLuint, GLuint);
#define glVertexAttribP1ui _glplatform_glVertexAttribP1ui
extern void (*glVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP1uiv _glplatform_glVertexAttribP1uiv
extern void (*glVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP2ui _glplatform_glVertexAttribP2ui
extern void (*glVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP2uiv _glplatform_glVertexAttribP2uiv
extern void (*glVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP3ui _glplatform_glVertexAttribP3ui
extern void (*glVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP3uiv _glplatform_glVertexAttribP3uiv
extern void (*glVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP4ui _glplatform_glVertexAttribP4ui
extern void (*glVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP4uiv _glplatform_glVertexAttribP4uiv
extern void (*glVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 40

#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_SUBROUTINES 0x8de5
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH 0x8e48
#define GL_ACTIVE_SUBROUTINE_UNIFORMS 0x8de6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8e47
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8e49
#define GL_COMPATIBLE_SUBROUTINES 0x8e4b
#define GL_DOUBLE_MAT2 0x8f46
#define GL_DOUBLE_MAT2x3 0x8f49
#define GL_DOUBLE_MAT2x4 0x8f4a
#define GL_DOUBLE_MAT3 0x8f47
#define GL_DOUBLE_MAT3x2 0x8f4b
#define GL_DOUBLE_MAT3x4 0x8f4c
#define GL_DOUBLE_MAT4 0x8f48
#define GL_DOUBLE_MAT4x2 0x8f4d
#define GL_DOUBLE_MAT4x3 0x8f4e
#define GL_DOUBLE_VEC2 0x8ffc
#define GL_DOUBLE_VEC3 0x8ffd
#define GL_DOUBLE_VEC4 0x8ffe
#define GL_DRAW_INDIRECT_BUFFER 0x8f3f
#define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8f43
#define GL_FRACTIONAL_EVEN 0x8e7c
#define GL_FRACTIONAL_ODD 0x8e7b
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8e5d
#define GL_GEOMETRY_SHADER_INVOCATIONS 0x887f
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900e
#define GL_ISOLINES 0x8e7a
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e1e
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e1f
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8e5c
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8e5a
#define GL_MAX_PATCH_VERTICES 0x8e7d
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8e5f
#define GL_MAX_SUBROUTINES 0x8de7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8de8
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886c
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8e83
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8e81
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8e85
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8e89
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e7f
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886d
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8e86
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8e82
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8e8a
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e80
#define GL_MAX_TESS_GEN_LEVEL 0x8e7e
#define GL_MAX_TESS_PATCH_COMPONENTS 0x8e84
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8e70
#define GL_MAX_VERTEX_STREAMS 0x8e71
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8e5b
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8e5e
#define GL_MIN_SAMPLE_SHADING_VALUE 0x8c37
#define GL_NUM_COMPATIBLE_SUBROUTINES 0x8e4a
#define GL_PATCHES 0xe
#define GL_PATCH_DEFAULT_INNER_LEVEL 0x8e73
#define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8e74
#define GL_PATCH_VERTICES 0x8e72
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 0x900b
#define GL_QUADS 0x7
#define GL_SAMPLER_CUBE_MAP_ARRAY 0x900c
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900d
#define GL_SAMPLE_SHADING 0x8c36
#define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8e75
#define GL_TESS_CONTROL_SHADER 0x8e88
#define GL_TESS_EVALUATION_SHADER 0x8e87
#define GL_TESS_GEN_MODE 0x8e76
#define GL_TESS_GEN_POINT_MODE 0x8e79
#define GL_TESS_GEN_SPACING 0x8e77
#define GL_TESS_GEN_VERTEX_ORDER 0x8e78
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900a
#define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#define GL_TRANSFORM_FEEDBACK 0x8e22
#define GL_TRANSFORM_FEEDBACK_BINDING 0x8e25
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8e24
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8e23
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84f0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84f1
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900f

#define glBeginQueryIndexed _glplatform_glBeginQueryIndexed
extern void (*glBeginQueryIndexed)(GLenum, GLuint, GLuint);
#define glBindTransformFeedback _glplatform_glBindTransformFeedback
extern void (*glBindTransformFeedback)(GLenum, GLuint);
#define glBlendEquationSeparatei _glplatform_glBlendEquationSeparatei
extern void (*glBlendEquationSeparatei)(GLuint, GLenum, GLenum);
#define glBlendEquationi _glplatform_glBlendEquationi
extern void (*glBlendEquationi)(GLuint, GLenum);
#define glBlendFuncSeparatei _glplatform_glBlendFuncSeparatei
extern void (*glBlendFuncSeparatei)(GLuint, GLenum, GLenum, GLenum, GLenum);
#define glBlendFunci _glplatform_glBlendFunci
extern void (*glBlendFunci)(GLuint, GLenum, GLenum);
#define glDeleteTransformFeedbacks _glplatform_glDeleteTransformFeedbacks
extern void (*glDeleteTransformFeedbacks)(GLsizei, const GLuint *);
#define glDrawArraysIndirect _glplatform_glDrawArraysIndirect
extern void (*glDrawArraysIndirect)(GLenum, const void *);
#define glDrawElementsIndirect _glplatform_glDrawElementsIndirect
extern void (*glDrawElementsIndirect)(GLenum, GLenum, const void *);
#define glDrawTransformFeedback _glplatform_glDrawTransformFeedback
extern void (*glDrawTransformFeedback)(GLenum, GLuint);
#define glDrawTransformFeedbackStream _glplatform_glDrawTransformFeedbackStream
extern void (*glDrawTransformFeedbackStream)(GLenum, GLuint, GLuint);
#define glEndQueryIndexed _glplatform_glEndQueryIndexed
extern void (*glEndQueryIndexed)(GLenum, GLuint);
#define glGenTransformFeedbacks _glplatform_glGenTransformFeedbacks
extern void (*glGenTransformFeedbacks)(GLsizei, GLuint *);
#define glGetActiveSubroutineName _glplatform_glGetActiveSubroutineName
extern void (*glGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineUniformName _glplatform_glGetActiveSubroutineUniformName
extern void (*glGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineUniformiv _glplatform_glGetActiveSubroutineUniformiv
extern void (*glGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *);
#define glGetProgramStageiv _glplatform_glGetProgramStageiv
extern void (*glGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetQueryIndexediv _glplatform_glGetQueryIndexediv
extern void (*glGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *);
#define glGetSubroutineIndex _glplatform_glGetSubroutineIndex
extern GLuint (*glGetSubroutineIndex)(GLuint, GLenum, const GLchar *);
#define glGetSubroutineUniformLocation _glplatform_glGetSubroutineUniformLocation
extern GLint (*glGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *);
#define glGetUniformSubroutineuiv _glplatform_glGetUniformSubroutineuiv
extern void (*glGetUniformSubroutineuiv)(GLenum, GLint, GLuint *);
#define glGetUniformdv _glplatform_glGetUniformdv
extern void (*glGetUniformdv)(GLuint, GLint, GLdouble *);
#define glIsTransformFeedback _glplatform_glIsTransformFeedback
extern GLboolean (*glIsTransformFeedback)(GLuint);
#define glMinSampleShading _glplatform_glMinSampleShading
extern void (*glMinSampleShading)(GLfloat);
#define glPatchParameterfv _glplatform_glPatchParameterfv
extern void (*glPatchParameterfv)(GLenum, const GLfloat *);
#define glPatchParameteri _glplatform_glPatchParameteri
extern void (*glPatchParameteri)(GLenum, GLint);
#define glPauseTransformFeedback _glplatform_glPauseTransformFeedback
extern void (*glPauseTransformFeedback)();
#define glResumeTransformFeedback _glplatform_glResumeTransformFeedback
extern void (*glResumeTransformFeedback)();
#define glUniform1d _glplatform_glUniform1d
extern void (*glUniform1d)(GLint, GLdouble);
#define glUniform1dv _glplatform_glUniform1dv
extern void (*glUniform1dv)(GLint, GLsizei, const GLdouble *);
#define glUniform2d _glplatform_glUniform2d
extern void (*glUniform2d)(GLint, GLdouble, GLdouble);
#define glUniform2dv _glplatform_glUniform2dv
extern void (*glUniform2dv)(GLint, GLsizei, const GLdouble *);
#define glUniform3d _glplatform_glUniform3d
extern void (*glUniform3d)(GLint, GLdouble, GLdouble, GLdouble);
#define glUniform3dv _glplatform_glUniform3dv
extern void (*glUniform3dv)(GLint, GLsizei, const GLdouble *);
#define glUniform4d _glplatform_glUniform4d
extern void (*glUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glUniform4dv _glplatform_glUniform4dv
extern void (*glUniform4dv)(GLint, GLsizei, const GLdouble *);
#define glUniformMatrix2dv _glplatform_glUniformMatrix2dv
extern void (*glUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x3dv _glplatform_glUniformMatrix2x3dv
extern void (*glUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x4dv _glplatform_glUniformMatrix2x4dv
extern void (*glUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3dv _glplatform_glUniformMatrix3dv
extern void (*glUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x2dv _glplatform_glUniformMatrix3x2dv
extern void (*glUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x4dv _glplatform_glUniformMatrix3x4dv
extern void (*glUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4dv _glplatform_glUniformMatrix4dv
extern void (*glUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x2dv _glplatform_glUniformMatrix4x2dv
extern void (*glUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x3dv _glplatform_glUniformMatrix4x3dv
extern void (*glUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformSubroutinesuiv _glplatform_glUniformSubroutinesuiv
extern void (*glUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 41

#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_PROGRAM 0x8259
#define GL_ALL_SHADER_BITS 0xffffffff
#define GL_FIXED 0x140c
#define GL_FRAGMENT_SHADER_BIT 0x2
#define GL_GEOMETRY_SHADER_BIT 0x4
#define GL_HIGH_FLOAT 0x8df2
#define GL_HIGH_INT 0x8df5
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8b9b
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8b9a
#define GL_LAYER_PROVOKING_VERTEX 0x825e
#define GL_LOW_FLOAT 0x8df0
#define GL_LOW_INT 0x8df3
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8dfd
#define GL_MAX_VARYING_VECTORS 0x8dfc
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8dfb
#define GL_MAX_VIEWPORTS 0x825b
#define GL_MEDIUM_FLOAT 0x8df1
#define GL_MEDIUM_INT 0x8df4
#define GL_NUM_PROGRAM_BINARY_FORMATS 0x87fe
#define GL_NUM_SHADER_BINARY_FORMATS 0x8df9
#define GL_PROGRAM_BINARY_FORMATS 0x87ff
#define GL_PROGRAM_BINARY_LENGTH 0x8741
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_PIPELINE_BINDING 0x825a
#define GL_PROGRAM_SEPARABLE 0x8258
#define GL_RGB565 0x8d62
#define GL_SHADER_BINARY_FORMATS 0x8df8
#define GL_SHADER_COMPILER 0x8dfa
#define GL_TESS_CONTROL_SHADER_BIT 0x8
#define GL_TESS_EVALUATION_SHADER_BIT 0x10
#define GL_UNDEFINED_VERTEX 0x8260
#define GL_VERTEX_SHADER_BIT 0x1
#define GL_VIEWPORT_BOUNDS_RANGE 0x825d
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825f
#define GL_VIEWPORT_SUBPIXEL_BITS 0x825c

#define glActiveShaderProgram _glplatform_glActiveShaderProgram
extern void (*glActiveShaderProgram)(GLuint, GLuint);
#define glBindProgramPipeline _glplatform_glBindProgramPipeline
extern void (*glBindProgramPipeline)(GLuint);
#define glClearDepthf _glplatform_glClearDepthf
extern void (*glClearDepthf)(GLfloat);
#define glCreateShaderProgramv _glplatform_glCreateShaderProgramv
extern GLuint (*glCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*);
#define glDeleteProgramPipelines _glplatform_glDeleteProgramPipelines
extern void (*glDeleteProgramPipelines)(GLsizei, const GLuint *);
#define glDepthRangeArrayv _glplatform_glDepthRangeArrayv
extern void (*glDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *);
#define glDepthRangeIndexed _glplatform_glDepthRangeIndexed
extern void (*glDepthRangeIndexed)(GLuint, GLdouble, GLdouble);
#define glDepthRangef _glplatform_glDepthRangef
extern void (*glDepthRangef)(GLfloat, GLfloat);
#define glGenProgramPipelines _glplatform_glGenProgramPipelines
extern void (*glGenProgramPipelines)(GLsizei, GLuint *);
#define glGetDoublei_v _glplatform_glGetDoublei_v
extern void (*glGetDoublei_v)(GLenum, GLuint, GLdouble *);
#define glGetFloati_v _glplatform_glGetFloati_v
extern void (*glGetFloati_v)(GLenum, GLuint, GLfloat *);
#define glGetProgramBinary _glplatform_glGetProgramBinary
extern void (*glGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
#define glGetProgramPipelineInfoLog _glplatform_glGetProgramPipelineInfoLog
extern void (*glGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramPipelineiv _glplatform_glGetProgramPipelineiv
extern void (*glGetProgramPipelineiv)(GLuint, GLenum, GLint *);
#define glGetShaderPrecisionFormat _glplatform_glGetShaderPrecisionFormat
extern void (*glGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *);
#define glGetVertexAttribLdv _glplatform_glGetVertexAttribLdv
extern void (*glGetVertexAttribLdv)(GLuint, GLenum, GLdouble *);
#define glIsProgramPipeline _glplatform_glIsProgramPipeline
extern GLboolean (*glIsProgramPipeline)(GLuint);
#define glProgramBinary _glplatform_glProgramBinary
extern void (*glProgramBinary)(GLuint, GLenum, const void *, GLsizei);
#define glProgramParameteri _glplatform_glProgramParameteri
extern void (*glProgramParameteri)(GLuint, GLenum, GLint);
#define glProgramUniform1d _glplatform_glProgramUniform1d
extern void (*glProgramUniform1d)(GLuint, GLint, GLdouble);
#define glProgramUniform1dv _glplatform_glProgramUniform1dv
extern void (*glProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform1f _glplatform_glProgramUniform1f
extern void (*glProgramUniform1f)(GLuint, GLint, GLfloat);
#define glProgramUniform1fv _glplatform_glProgramUniform1fv
extern void (*glProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform1i _glplatform_glProgramUniform1i
extern void (*glProgramUniform1i)(GLuint, GLint, GLint);
#define glProgramUniform1iv _glplatform_glProgramUniform1iv
extern void (*glProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform1ui _glplatform_glProgramUniform1ui
extern void (*glProgramUniform1ui)(GLuint, GLint, GLuint);
#define glProgramUniform1uiv _glplatform_glProgramUniform1uiv
extern void (*glProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform2d _glplatform_glProgramUniform2d
extern void (*glProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble);
#define glProgramUniform2dv _glplatform_glProgramUniform2dv
extern void (*glProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform2f _glplatform_glProgramUniform2f
extern void (*glProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat);
#define glProgramUniform2fv _glplatform_glProgramUniform2fv
extern void (*glProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform2i _glplatform_glProgramUniform2i
extern void (*glProgramUniform2i)(GLuint, GLint, GLint, GLint);
#define glProgramUniform2iv _glplatform_glProgramUniform2iv
extern void (*glProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform2ui _glplatform_glProgramUniform2ui
extern void (*glProgramUniform2ui)(GLuint, GLint, GLuint, GLuint);
#define glProgramUniform2uiv _glplatform_glProgramUniform2uiv
extern void (*glProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform3d _glplatform_glProgramUniform3d
extern void (*glProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
#define glProgramUniform3dv _glplatform_glProgramUniform3dv
extern void (*glProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform3f _glplatform_glProgramUniform3f
extern void (*glProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
#define glProgramUniform3fv _glplatform_glProgramUniform3fv
extern void (*glProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform3i _glplatform_glProgramUniform3i
extern void (*glProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint);
#define glProgramUniform3iv _glplatform_glProgramUniform3iv
extern void (*glProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform3ui _glplatform_glProgramUniform3ui
extern void (*glProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint);
#define glProgramUniform3uiv _glplatform_glProgramUniform3uiv
extern void (*glProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform4d _glplatform_glProgramUniform4d
extern void (*glProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glProgramUniform4dv _glplatform_glProgramUniform4dv
extern void (*glProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform4f _glplatform_glProgramUniform4f
extern void (*glProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glProgramUniform4fv _glplatform_glProgramUniform4fv
extern void (*glProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform4i _glplatform_glProgramUniform4i
extern void (*glProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint);
#define glProgramUniform4iv _glplatform_glProgramUniform4iv
extern void (*glProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform4ui _glplatform_glProgramUniform4ui
extern void (*glProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
#define glProgramUniform4uiv _glplatform_glProgramUniform4uiv
extern void (*glProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniformMatrix2dv _glplatform_glProgramUniformMatrix2dv
extern void (*glProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2fv _glplatform_glProgramUniformMatrix2fv
extern void (*glProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x3dv _glplatform_glProgramUniformMatrix2x3dv
extern void (*glProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x3fv _glplatform_glProgramUniformMatrix2x3fv
extern void (*glProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x4dv _glplatform_glProgramUniformMatrix2x4dv
extern void (*glProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x4fv _glplatform_glProgramUniformMatrix2x4fv
extern void (*glProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3dv _glplatform_glProgramUniformMatrix3dv
extern void (*glProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3fv _glplatform_glProgramUniformMatrix3fv
extern void (*glProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x2dv _glplatform_glProgramUniformMatrix3x2dv
extern void (*glProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x2fv _glplatform_glProgramUniformMatrix3x2fv
extern void (*glProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x4dv _glplatform_glProgramUniformMatrix3x4dv
extern void (*glProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x4fv _glplatform_glProgramUniformMatrix3x4fv
extern void (*glProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4dv _glplatform_glProgramUniformMatrix4dv
extern void (*glProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4fv _glplatform_glProgramUniformMatrix4fv
extern void (*glProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x2dv _glplatform_glProgramUniformMatrix4x2dv
extern void (*glProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x2fv _glplatform_glProgramUniformMatrix4x2fv
extern void (*glProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x3dv _glplatform_glProgramUniformMatrix4x3dv
extern void (*glProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x3fv _glplatform_glProgramUniformMatrix4x3fv
extern void (*glProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glReleaseShaderCompiler _glplatform_glReleaseShaderCompiler
extern void (*glReleaseShaderCompiler)();
#define glScissorArrayv _glplatform_glScissorArrayv
extern void (*glScissorArrayv)(GLuint, GLsizei, const GLint *);
#define glScissorIndexed _glplatform_glScissorIndexed
extern void (*glScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei);
#define glScissorIndexedv _glplatform_glScissorIndexedv
extern void (*glScissorIndexedv)(GLuint, const GLint *);
#define glShaderBinary _glplatform_glShaderBinary
extern void (*glShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
#define glUseProgramStages _glplatform_glUseProgramStages
extern void (*glUseProgramStages)(GLuint, GLbitfield, GLuint);
#define glValidateProgramPipeline _glplatform_glValidateProgramPipeline
extern void (*glValidateProgramPipeline)(GLuint);
#define glVertexAttribL1d _glplatform_glVertexAttribL1d
extern void (*glVertexAttribL1d)(GLuint, GLdouble);
#define glVertexAttribL1dv _glplatform_glVertexAttribL1dv
extern void (*glVertexAttribL1dv)(GLuint, const GLdouble *);
#define glVertexAttribL2d _glplatform_glVertexAttribL2d
extern void (*glVertexAttribL2d)(GLuint, GLdouble, GLdouble);
#define glVertexAttribL2dv _glplatform_glVertexAttribL2dv
extern void (*glVertexAttribL2dv)(GLuint, const GLdouble *);
#define glVertexAttribL3d _glplatform_glVertexAttribL3d
extern void (*glVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL3dv _glplatform_glVertexAttribL3dv
extern void (*glVertexAttribL3dv)(GLuint, const GLdouble *);
#define glVertexAttribL4d _glplatform_glVertexAttribL4d
extern void (*glVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL4dv _glplatform_glVertexAttribL4dv
extern void (*glVertexAttribL4dv)(GLuint, const GLdouble *);
#define glVertexAttribLPointer _glplatform_glVertexAttribLPointer
extern void (*glVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
#define glViewportArrayv _glplatform_glViewportArrayv
extern void (*glViewportArrayv)(GLuint, GLsizei, const GLfloat *);
#define glViewportIndexedf _glplatform_glViewportIndexedf
extern void (*glViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glViewportIndexedfv _glplatform_glViewportIndexedfv
extern void (*glViewportIndexedfv)(GLuint, const GLfloat *);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 42


#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92d9
#define GL_ALL_BARRIER_BITS 0xffffffff
#define GL_ATOMIC_COUNTER_BARRIER_BIT 0x1000
#define GL_ATOMIC_COUNTER_BUFFER 0x92c0
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92c5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92c6
#define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92c1
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92c4
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92cb
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92ca
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92c8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92c9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92c7
#define GL_ATOMIC_COUNTER_BUFFER_SIZE 0x92c3
#define GL_ATOMIC_COUNTER_BUFFER_START 0x92c2
#define GL_BUFFER_UPDATE_BARRIER_BIT 0x200
#define GL_COMMAND_BARRIER_BIT 0x40
#define GL_COMPRESSED_RGBA_BPTC_UNORM 0x8e8c
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8e8e
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8e8f
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8e8d
#define GL_COPY_READ_BUFFER_BINDING 0x8f36
#define GL_COPY_WRITE_BUFFER_BINDING 0x8f37
#define GL_ELEMENT_ARRAY_BARRIER_BIT 0x2
#define GL_FRAMEBUFFER_BARRIER_BIT 0x400
#define GL_IMAGE_1D 0x904c
#define GL_IMAGE_1D_ARRAY 0x9052
#define GL_IMAGE_2D 0x904d
#define GL_IMAGE_2D_ARRAY 0x9053
#define GL_IMAGE_2D_MULTISAMPLE 0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY 0x9056
#define GL_IMAGE_2D_RECT 0x904f
#define GL_IMAGE_3D 0x904e
#define GL_IMAGE_BINDING_ACCESS 0x8f3e
#define GL_IMAGE_BINDING_FORMAT 0x906e
#define GL_IMAGE_BINDING_LAYER 0x8f3d
#define GL_IMAGE_BINDING_LAYERED 0x8f3c
#define GL_IMAGE_BINDING_LEVEL 0x8f3b
#define GL_IMAGE_BINDING_NAME 0x8f3a
#define GL_IMAGE_BUFFER 0x9051
#define GL_IMAGE_CUBE 0x9050
#define GL_IMAGE_CUBE_MAP_ARRAY 0x9054
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90c9
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90c8
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90c7
#define GL_INT_IMAGE_1D 0x9057
#define GL_INT_IMAGE_1D_ARRAY 0x905d
#define GL_INT_IMAGE_2D 0x9058
#define GL_INT_IMAGE_2D_ARRAY 0x905e
#define GL_INT_IMAGE_2D_MULTISAMPLE 0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_INT_IMAGE_2D_RECT 0x905a
#define GL_INT_IMAGE_3D 0x9059
#define GL_INT_IMAGE_BUFFER 0x905c
#define GL_INT_IMAGE_CUBE 0x905b
#define GL_INT_IMAGE_CUBE_MAP_ARRAY 0x905f
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92dc
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92d8
#define GL_MAX_COMBINED_ATOMIC_COUNTERS 0x92d7
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92d1
#define GL_MAX_COMBINED_IMAGE_UNIFORMS 0x90cf
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8f39
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS 0x92d6
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92d0
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS 0x90ce
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS 0x92d5
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92cf
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS 0x90cd
#define GL_MAX_IMAGE_SAMPLES 0x906d
#define GL_MAX_IMAGE_UNITS 0x8f38
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92d3
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92cd
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90cb
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92d4
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92ce
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90cc
#define GL_MAX_VERTEX_ATOMIC_COUNTERS 0x92d2
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92cc
#define GL_MAX_VERTEX_IMAGE_UNIFORMS 0x90ca
#define GL_MIN_MAP_BUFFER_ALIGNMENT 0x90bc
#define GL_NUM_SAMPLE_COUNTS 0x9380
#define GL_PACK_COMPRESSED_BLOCK_DEPTH 0x912d
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT 0x912c
#define GL_PACK_COMPRESSED_BLOCK_SIZE 0x912e
#define GL_PACK_COMPRESSED_BLOCK_WIDTH 0x912b
#define GL_PIXEL_BUFFER_BARRIER_BIT 0x80
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x20
#define GL_TEXTURE_FETCH_BARRIER_BIT 0x8
#define GL_TEXTURE_IMMUTABLE_FORMAT 0x912f
#define GL_TEXTURE_UPDATE_BARRIER_BIT 0x100
#define GL_TRANSFORM_FEEDBACK_ACTIVE 0x8e24
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x800
#define GL_TRANSFORM_FEEDBACK_PAUSED 0x8e23
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92da
#define GL_UNIFORM_BARRIER_BIT 0x4
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH 0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE 0x912a
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH 0x9127
#define GL_UNSIGNED_INT_ATOMIC_COUNTER 0x92db
#define GL_UNSIGNED_INT_IMAGE_1D 0x9062
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY 0x9068
#define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY 0x9069
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906b
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906c
#define GL_UNSIGNED_INT_IMAGE_2D_RECT 0x9065
#define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#define GL_UNSIGNED_INT_IMAGE_BUFFER 0x9067
#define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906a
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x1

#define glBindImageTexture _glplatform_glBindImageTexture
extern void (*glBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
#define glDrawArraysInstancedBaseInstance _glplatform_glDrawArraysInstancedBaseInstance
extern void (*glDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint);
#define glDrawElementsInstancedBaseInstance _glplatform_glDrawElementsInstancedBaseInstance
extern void (*glDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
#define glDrawElementsInstancedBaseVertexBaseInstance _glplatform_glDrawElementsInstancedBaseVertexBaseInstance
extern void (*glDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
#define glDrawTransformFeedbackInstanced _glplatform_glDrawTransformFeedbackInstanced
extern void (*glDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei);
#define glDrawTransformFeedbackStreamInstanced _glplatform_glDrawTransformFeedbackStreamInstanced
extern void (*glDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei);
#define glGetActiveAtomicCounterBufferiv _glplatform_glGetActiveAtomicCounterBufferiv
extern void (*glGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *);
#define glGetInternalformativ _glplatform_glGetInternalformativ
extern void (*glGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *);
#define glMemoryBarrier _glplatform_glMemoryBarrier
extern void (*glMemoryBarrier)(GLbitfield);
#define glTexStorage1D _glplatform_glTexStorage1D
extern void (*glTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei);
#define glTexStorage2D _glplatform_glTexStorage2D
extern void (*glTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#define glTexStorage3D _glplatform_glTexStorage3D
extern void (*glTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 43

#ifndef GLPLATFORM_TYPE_GLDEBUGPROC
#define GLPLATFORM_TYPE_GLDEBUGPROC
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif

#define GL_ACTIVE_RESOURCES 0x92f5
#define GL_ACTIVE_VARIABLES 0x9305
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8d6a
#define GL_ARRAY_SIZE 0x92fb
#define GL_ARRAY_STRIDE 0x92fe
#define GL_ATOMIC_COUNTER_BUFFER_INDEX 0x9301
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ed
#define GL_AUTO_GENERATE_MIPMAP 0x8295
#define GL_BLOCK_INDEX 0x92fd
#define GL_BUFFER 0x82e0
#define GL_BUFFER_BINDING 0x9302
#define GL_BUFFER_DATA_SIZE 0x9303
#define GL_BUFFER_VARIABLE 0x92e5
#define GL_CAVEAT_SUPPORT 0x82b8
#define GL_CLEAR_BUFFER 0x82b4
#define GL_COLOR_COMPONENTS 0x8283
#define GL_COLOR_ENCODING 0x8296
#define GL_COLOR_RENDERABLE 0x8286
#define GL_COMPRESSED_R11_EAC 0x9270
#define GL_COMPRESSED_RG11_EAC 0x9272
#define GL_COMPRESSED_RGB8_ETC2 0x9274
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#define GL_COMPRESSED_SIGNED_R11_EAC 0x9271
#define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_SRGB8_ETC2 0x9275
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPUTE_SHADER 0x91b9
#define GL_COMPUTE_SHADER_BIT 0x20
#define GL_COMPUTE_SUBROUTINE 0x92ed
#define GL_COMPUTE_SUBROUTINE_UNIFORM 0x92f3
#define GL_COMPUTE_TEXTURE 0x82a0
#define GL_COMPUTE_WORK_GROUP_SIZE 0x8267
#define GL_CONTEXT_FLAG_DEBUG_BIT 0x2
#define GL_DEBUG_CALLBACK_FUNCTION 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM 0x8245
#define GL_DEBUG_GROUP_STACK_DEPTH 0x826d
#define GL_DEBUG_LOGGED_MESSAGES 0x9145
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_OUTPUT 0x92e0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_LOW 0x9148
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826b
#define GL_DEBUG_SOURCE_API 0x8246
#define GL_DEBUG_SOURCE_APPLICATION 0x824a
#define GL_DEBUG_SOURCE_OTHER 0x824b
#define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824d
#define GL_DEBUG_TYPE_ERROR 0x824c
#define GL_DEBUG_TYPE_MARKER 0x8268
#define GL_DEBUG_TYPE_OTHER 0x8251
#define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#define GL_DEBUG_TYPE_POP_GROUP 0x826a
#define GL_DEBUG_TYPE_PORTABILITY 0x824f
#define GL_DEBUG_TYPE_PUSH_GROUP 0x8269
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824e
#define GL_DEPTH_COMPONENTS 0x8284
#define GL_DEPTH_RENDERABLE 0x8287
#define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90ea
#define GL_DISPATCH_INDIRECT_BUFFER 0x90ee
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90ef
#define GL_FILTER 0x829a
#define GL_FRAGMENT_SUBROUTINE 0x92ec
#define GL_FRAGMENT_SUBROUTINE_UNIFORM 0x92f2
#define GL_FRAGMENT_TEXTURE 0x829f
#define GL_FRAMEBUFFER_BLEND 0x828b
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT 0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS 0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES 0x9313
#define GL_FRAMEBUFFER_DEFAULT_WIDTH 0x9310
#define GL_FRAMEBUFFER_RENDERABLE 0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828a
#define GL_FULL_SUPPORT 0x82b7
#define GL_GEOMETRY_SUBROUTINE 0x92eb
#define GL_GEOMETRY_SUBROUTINE_UNIFORM 0x92f1
#define GL_GEOMETRY_TEXTURE 0x829e
#define GL_GET_TEXTURE_IMAGE_FORMAT 0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE 0x8292
#define GL_IMAGE_CLASS_10_10_10_2 0x82c3
#define GL_IMAGE_CLASS_11_11_10 0x82c2
#define GL_IMAGE_CLASS_1_X_16 0x82be
#define GL_IMAGE_CLASS_1_X_32 0x82bb
#define GL_IMAGE_CLASS_1_X_8 0x82c1
#define GL_IMAGE_CLASS_2_X_16 0x82bd
#define GL_IMAGE_CLASS_2_X_32 0x82ba
#define GL_IMAGE_CLASS_2_X_8 0x82c0
#define GL_IMAGE_CLASS_4_X_16 0x82bc
#define GL_IMAGE_CLASS_4_X_32 0x82b9
#define GL_IMAGE_CLASS_4_X_8 0x82bf
#define GL_IMAGE_COMPATIBILITY_CLASS 0x82a8
#define GL_IMAGE_PIXEL_FORMAT 0x82a9
#define GL_IMAGE_PIXEL_TYPE 0x82aa
#define GL_IMAGE_TEXEL_SIZE 0x82a7
#define GL_INTERNALFORMAT_ALPHA_SIZE 0x8274
#define GL_INTERNALFORMAT_ALPHA_TYPE 0x827b
#define GL_INTERNALFORMAT_BLUE_SIZE 0x8273
#define GL_INTERNALFORMAT_BLUE_TYPE 0x827a
#define GL_INTERNALFORMAT_DEPTH_SIZE 0x8275
#define GL_INTERNALFORMAT_DEPTH_TYPE 0x827c
#define GL_INTERNALFORMAT_GREEN_SIZE 0x8272
#define GL_INTERNALFORMAT_GREEN_TYPE 0x8279
#define GL_INTERNALFORMAT_PREFERRED 0x8270
#define GL_INTERNALFORMAT_RED_SIZE 0x8271
#define GL_INTERNALFORMAT_RED_TYPE 0x8278
#define GL_INTERNALFORMAT_SHARED_SIZE 0x8277
#define GL_INTERNALFORMAT_STENCIL_SIZE 0x8276
#define GL_INTERNALFORMAT_STENCIL_TYPE 0x827d
#define GL_INTERNALFORMAT_SUPPORTED 0x826f
#define GL_IS_PER_PATCH 0x92e7
#define GL_IS_ROW_MAJOR 0x9300
#define GL_LOCATION 0x930e
#define GL_LOCATION_INDEX 0x930f
#define GL_MANUAL_GENERATE_MIPMAP 0x8294
#define GL_MATRIX_STRIDE 0x92ff
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMBINED_DIMENSIONS 0x8282
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8f39
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90dc
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91bd
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90db
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91bc
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91bb
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91be
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90eb
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91bf
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH 0x826c
#define GL_MAX_DEBUG_LOGGED_MESSAGES 0x9144
#define GL_MAX_DEBUG_MESSAGE_LENGTH 0x9143
#define GL_MAX_DEPTH 0x8280
#define GL_MAX_ELEMENT_INDEX 0x8d6b
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90da
#define GL_MAX_FRAMEBUFFER_HEIGHT 0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS 0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES 0x9318
#define GL_MAX_FRAMEBUFFER_WIDTH 0x9315
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90d7
#define GL_MAX_HEIGHT 0x827f
#define GL_MAX_LABEL_LENGTH 0x82e8
#define GL_MAX_LAYERS 0x8281
#define GL_MAX_NAME_LENGTH 0x92f6
#define GL_MAX_NUM_ACTIVE_VARIABLES 0x92f7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92f8
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE 0x90de
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90dd
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90d8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90d9
#define GL_MAX_UNIFORM_LOCATIONS 0x826e
#define GL_MAX_VERTEX_ATTRIB_BINDINGS 0x82da
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d9
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90d6
#define GL_MAX_WIDTH 0x827e
#define GL_MIPMAP 0x8293
#define GL_NAME_LENGTH 0x92f9
#define GL_NUM_ACTIVE_VARIABLES 0x9304
#define GL_NUM_SHADING_LANGUAGE_VERSIONS 0x82e9
#define GL_OFFSET 0x92fc
#define GL_PRIMITIVE_RESTART_FIXED_INDEX 0x8d69
#define GL_PROGRAM 0x82e2
#define GL_PROGRAM_INPUT 0x92e3
#define GL_PROGRAM_OUTPUT 0x92e4
#define GL_PROGRAM_PIPELINE 0x82e4
#define GL_QUERY 0x82e3
#define GL_READ_PIXELS 0x828c
#define GL_READ_PIXELS_FORMAT 0x828d
#define GL_READ_PIXELS_TYPE 0x828e
#define GL_REFERENCED_BY_COMPUTE_SHADER 0x930b
#define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930a
#define GL_REFERENCED_BY_GEOMETRY_SHADER 0x9309
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_VERTEX_SHADER 0x9306
#define GL_SAMPLER 0x82e6
#define GL_SHADER 0x82e1
#define GL_SHADER_IMAGE_ATOMIC 0x82a6
#define GL_SHADER_IMAGE_LOAD 0x82a4
#define GL_SHADER_IMAGE_STORE 0x82a5
#define GL_SHADER_STORAGE_BARRIER_BIT 0x2000
#define GL_SHADER_STORAGE_BLOCK 0x92e6
#define GL_SHADER_STORAGE_BUFFER 0x90d2
#define GL_SHADER_STORAGE_BUFFER_BINDING 0x90d3
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90df
#define GL_SHADER_STORAGE_BUFFER_SIZE 0x90d5
#define GL_SHADER_STORAGE_BUFFER_START 0x90d4
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82ac
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82ae
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82ad
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82af
#define GL_SRGB_READ 0x8297
#define GL_SRGB_WRITE 0x8298
#define GL_STACK_OVERFLOW 0x503
#define GL_STACK_UNDERFLOW 0x504
#define GL_STENCIL_COMPONENTS 0x8285
#define GL_STENCIL_RENDERABLE 0x8288
#define GL_TESS_CONTROL_SUBROUTINE 0x92e9
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92ef
#define GL_TESS_CONTROL_TEXTURE 0x829c
#define GL_TESS_EVALUATION_SUBROUTINE 0x92ea
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92f0
#define GL_TESS_EVALUATION_TEXTURE 0x829d
#define GL_TEXTURE_BUFFER_OFFSET 0x919d
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919f
#define GL_TEXTURE_BUFFER_SIZE 0x919e
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82b2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE 0x82b3
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82b1
#define GL_TEXTURE_GATHER 0x82a2
#define GL_TEXTURE_GATHER_SHADOW 0x82a3
#define GL_TEXTURE_IMAGE_FORMAT 0x828f
#define GL_TEXTURE_IMAGE_TYPE 0x8290
#define GL_TEXTURE_IMMUTABLE_LEVELS 0x82df
#define GL_TEXTURE_SHADOW 0x82a1
#define GL_TEXTURE_VIEW 0x82b5
#define GL_TEXTURE_VIEW_MIN_LAYER 0x82dd
#define GL_TEXTURE_VIEW_MIN_LEVEL 0x82db
#define GL_TEXTURE_VIEW_NUM_LAYERS 0x82de
#define GL_TEXTURE_VIEW_NUM_LEVELS 0x82dc
#define GL_TOP_LEVEL_ARRAY_SIZE 0x930c
#define GL_TOP_LEVEL_ARRAY_STRIDE 0x930d
#define GL_TRANSFORM_FEEDBACK_VARYING 0x92f4
#define GL_TYPE 0x92fa
#define GL_UNIFORM 0x92e1
#define GL_UNIFORM_BLOCK 0x92e2
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90ec
#define GL_VERTEX_ARRAY 0x8074
#define GL_VERTEX_ATTRIB_ARRAY_LONG 0x874e
#define GL_VERTEX_ATTRIB_BINDING 0x82d4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d5
#define GL_VERTEX_BINDING_BUFFER 0x8f4f
#define GL_VERTEX_BINDING_DIVISOR 0x82d6
#define GL_VERTEX_BINDING_OFFSET 0x82d7
#define GL_VERTEX_BINDING_STRIDE 0x82d8
#define GL_VERTEX_SUBROUTINE 0x92e8
#define GL_VERTEX_SUBROUTINE_UNIFORM 0x92ee
#define GL_VERTEX_TEXTURE 0x829b
#define GL_VIEW_CLASS_128_BITS 0x82c4
#define GL_VIEW_CLASS_16_BITS 0x82ca
#define GL_VIEW_CLASS_24_BITS 0x82c9
#define GL_VIEW_CLASS_32_BITS 0x82c8
#define GL_VIEW_CLASS_48_BITS 0x82c7
#define GL_VIEW_CLASS_64_BITS 0x82c6
#define GL_VIEW_CLASS_8_BITS 0x82cb
#define GL_VIEW_CLASS_96_BITS 0x82c5
#define GL_VIEW_CLASS_BPTC_FLOAT 0x82d3
#define GL_VIEW_CLASS_BPTC_UNORM 0x82d2
#define GL_VIEW_CLASS_RGTC1_RED 0x82d0
#define GL_VIEW_CLASS_RGTC2_RG 0x82d1
#define GL_VIEW_CLASS_S3TC_DXT1_RGB 0x82cc
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA 0x82cd
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA 0x82ce
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA 0x82cf
#define GL_VIEW_COMPATIBILITY_CLASS 0x82b6

#define glBindVertexBuffer _glplatform_glBindVertexBuffer
extern void (*glBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei);
#define glClearBufferData _glplatform_glClearBufferData
extern void (*glClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *);
#define glClearBufferSubData _glplatform_glClearBufferSubData
extern void (*glClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#define glCopyImageSubData _glplatform_glCopyImageSubData
extern void (*glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#define glDebugMessageCallback _glplatform_glDebugMessageCallback
extern void (*glDebugMessageCallback)(GLDEBUGPROC, const void *);
#define glDebugMessageControl _glplatform_glDebugMessageControl
extern void (*glDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
#define glDebugMessageInsert _glplatform_glDebugMessageInsert
extern void (*glDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
#define glDispatchCompute _glplatform_glDispatchCompute
extern void (*glDispatchCompute)(GLuint, GLuint, GLuint);
#define glDispatchComputeIndirect _glplatform_glDispatchComputeIndirect
extern void (*glDispatchComputeIndirect)(GLintptr);
#define glFramebufferParameteri _glplatform_glFramebufferParameteri
extern void (*glFramebufferParameteri)(GLenum, GLenum, GLint);
#define glGetDebugMessageLog _glplatform_glGetDebugMessageLog
extern GLuint (*glGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
#define glGetFramebufferParameteriv _glplatform_glGetFramebufferParameteriv
extern void (*glGetFramebufferParameteriv)(GLenum, GLenum, GLint *);
#define glGetInternalformati64v _glplatform_glGetInternalformati64v
extern void (*glGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
#define glGetObjectLabel _glplatform_glGetObjectLabel
extern void (*glGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetObjectPtrLabel _glplatform_glGetObjectPtrLabel
extern void (*glGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *);
#define glGetPointerv _glplatform_glGetPointerv
extern void (*glGetPointerv)(GLenum, void **);
#define glGetProgramInterfaceiv _glplatform_glGetProgramInterfaceiv
extern void (*glGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetProgramResourceIndex _glplatform_glGetProgramResourceIndex
extern GLuint (*glGetProgramResourceIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocation _glplatform_glGetProgramResourceLocation
extern GLint (*glGetProgramResourceLocation)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocationIndex _glplatform_glGetProgramResourceLocationIndex
extern GLint (*glGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceName _glplatform_glGetProgramResourceName
extern void (*glGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramResourceiv _glplatform_glGetProgramResourceiv
extern void (*glGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
#define glInvalidateBufferData _glplatform_glInvalidateBufferData
extern void (*glInvalidateBufferData)(GLuint);
#define glInvalidateBufferSubData _glplatform_glInvalidateBufferSubData
extern void (*glInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr);
#define glInvalidateFramebuffer _glplatform_glInvalidateFramebuffer
extern void (*glInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *);
#define glInvalidateSubFramebuffer _glplatform_glInvalidateSubFramebuffer
extern void (*glInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glInvalidateTexImage _glplatform_glInvalidateTexImage
extern void (*glInvalidateTexImage)(GLuint, GLint);
#define glInvalidateTexSubImage _glplatform_glInvalidateTexSubImage
extern void (*glInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#define glMultiDrawArraysIndirect _glplatform_glMultiDrawArraysIndirect
extern void (*glMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei);
#define glMultiDrawElementsIndirect _glplatform_glMultiDrawElementsIndirect
extern void (*glMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei);
#define glObjectLabel _glplatform_glObjectLabel
extern void (*glObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *);
#define glObjectPtrLabel _glplatform_glObjectPtrLabel
extern void (*glObjectPtrLabel)(const void *, GLsizei, const GLchar *);
#define glPopDebugGroup _glplatform_glPopDebugGroup
extern void (*glPopDebugGroup)();
#define glPushDebugGroup _glplatform_glPushDebugGroup
extern void (*glPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *);
#define glShaderStorageBlockBinding _glplatform_glShaderStorageBlockBinding
extern void (*glShaderStorageBlockBinding)(GLuint, GLuint, GLuint);
#define glTexBufferRange _glplatform_glTexBufferRange
extern void (*glTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
#define glTexStorage2DMultisample _glplatform_glTexStorage2DMultisample
extern void (*glTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexStorage3DMultisample _glplatform_glTexStorage3DMultisample
extern void (*glTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTextureView _glplatform_glTextureView
extern void (*glTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
#define glVertexAttribBinding _glplatform_glVertexAttribBinding
extern void (*glVertexAttribBinding)(GLuint, GLuint);
#define glVertexAttribFormat _glplatform_glVertexAttribFormat
extern void (*glVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexAttribIFormat _glplatform_glVertexAttribIFormat
extern void (*glVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexAttribLFormat _glplatform_glVertexAttribLFormat
extern void (*glVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexBindingDivisor _glplatform_glVertexBindingDivisor
extern void (*glVertexBindingDivisor)(GLuint, GLuint);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 44


#define GL_BUFFER_IMMUTABLE_STORAGE 0x821f
#define GL_BUFFER_STORAGE_FLAGS 0x8220
#define GL_CLEAR_TEXTURE 0x9365
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x4000
#define GL_CLIENT_STORAGE_BIT 0x200
#define GL_DYNAMIC_STORAGE_BIT 0x100
#define GL_LOCATION_COMPONENT 0x934a
#define GL_MAP_COHERENT_BIT 0x80
#define GL_MAP_PERSISTENT_BIT 0x40
#define GL_MAP_READ_BIT 0x1
#define GL_MAP_WRITE_BIT 0x2
#define GL_MAX_VERTEX_ATTRIB_STRIDE 0x82e5
#define GL_MIRROR_CLAMP_TO_EDGE 0x8743
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_QUERY_BUFFER 0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT 0x8000
#define GL_QUERY_BUFFER_BINDING 0x9193
#define GL_QUERY_RESULT_NO_WAIT 0x9194
#define GL_STENCIL_INDEX 0x1901
#define GL_STENCIL_INDEX8 0x8d48
#define GL_TEXTURE_BUFFER_BINDING 0x8c2a
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8c8e
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934b
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934c
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8c3b

#define glBindBuffersBase _glplatform_glBindBuffersBase
extern void (*glBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *);
#define glBindBuffersRange _glplatform_glBindBuffersRange
extern void (*glBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
#define glBindImageTextures _glplatform_glBindImageTextures
extern void (*glBindImageTextures)(GLuint, GLsizei, const GLuint *);
#define glBindSamplers _glplatform_glBindSamplers
extern void (*glBindSamplers)(GLuint, GLsizei, const GLuint *);
#define glBindTextures _glplatform_glBindTextures
extern void (*glBindTextures)(GLuint, GLsizei, const GLuint *);
#define glBindVertexBuffers _glplatform_glBindVertexBuffers
extern void (*glBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#define glBufferStorage _glplatform_glBufferStorage
extern void (*glBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield);
#define glClearTexImage _glplatform_glClearTexImage
extern void (*glClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *);
#define glClearTexSubImage _glplatform_glClearTexSubImage
extern void (*glClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#endif

#if defined(GLPLATFORM_GL_VERSION) && GLPLATFORM_GL_VERSION >= 45

#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif

#define GL_BACK 0x405
#define GL_CLIP_DEPTH_MODE 0x935d
#define GL_CLIP_ORIGIN 0x935c
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x4
#define GL_CONTEXT_LOST 0x507
#define GL_CONTEXT_RELEASE_BEHAVIOR 0x82fb
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82fc
#define GL_GUILTY_CONTEXT_RESET 0x8253
#define GL_INNOCENT_CONTEXT_RESET 0x8254
#define GL_LOSE_CONTEXT_ON_RESET 0x8252
#define GL_LOWER_LEFT 0x8ca1
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82fa
#define GL_MAX_CULL_DISTANCES 0x82f9
#define GL_NEGATIVE_ONE_TO_ONE 0x935e
#define GL_NONE 0x0
#define GL_NO_ERROR 0x0
#define GL_NO_RESET_NOTIFICATION 0x8261
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8e1a
#define GL_QUERY_BY_REGION_WAIT_INVERTED 0x8e19
#define GL_QUERY_NO_WAIT_INVERTED 0x8e18
#define GL_QUERY_TARGET 0x82ea
#define GL_QUERY_WAIT_INVERTED 0x8e17
#define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#define GL_TEXTURE_BINDING_1D 0x8068
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8c1c
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8c1d
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_BINDING_3D 0x806a
#define GL_TEXTURE_BINDING_BUFFER 0x8c2c
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900a
#define GL_TEXTURE_BINDING_RECTANGLE 0x84f6
#define GL_TEXTURE_TARGET 0x1006
#define GL_UNKNOWN_CONTEXT_RESET 0x8255
#define GL_UPPER_LEFT 0x8ca2
#define GL_ZERO_TO_ONE 0x935f

#define glBindTextureUnit _glplatform_glBindTextureUnit
extern void (*glBindTextureUnit)(GLuint, GLuint);
#define glBlitNamedFramebuffer _glplatform_glBlitNamedFramebuffer
extern void (*glBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glCheckNamedFramebufferStatus _glplatform_glCheckNamedFramebufferStatus
extern GLenum (*glCheckNamedFramebufferStatus)(GLuint, GLenum);
#define glClearNamedBufferData _glplatform_glClearNamedBufferData
extern void (*glClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *);
#define glClearNamedBufferSubData _glplatform_glClearNamedBufferSubData
extern void (*glClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#define glClearNamedFramebufferfi _glplatform_glClearNamedFramebufferfi
extern void (*glClearNamedFramebufferfi)(GLuint, GLenum, const GLfloat, GLint);
#define glClearNamedFramebufferfv _glplatform_glClearNamedFramebufferfv
extern void (*glClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *);
#define glClearNamedFramebufferiv _glplatform_glClearNamedFramebufferiv
extern void (*glClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *);
#define glClearNamedFramebufferuiv _glplatform_glClearNamedFramebufferuiv
extern void (*glClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *);
#define glClipControl _glplatform_glClipControl
extern void (*glClipControl)(GLenum, GLenum);
#define glCompressedTextureSubImage1D _glplatform_glCompressedTextureSubImage1D
extern void (*glCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage2D _glplatform_glCompressedTextureSubImage2D
extern void (*glCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage3D _glplatform_glCompressedTextureSubImage3D
extern void (*glCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCopyNamedBufferSubData _glplatform_glCopyNamedBufferSubData
extern void (*glCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
#define glCopyTextureSubImage1D _glplatform_glCopyTextureSubImage1D
extern void (*glCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint, GLint, GLsizei);
#define glCopyTextureSubImage2D _glplatform_glCopyTextureSubImage2D
extern void (*glCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTextureSubImage3D _glplatform_glCopyTextureSubImage3D
extern void (*glCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCreateBuffers _glplatform_glCreateBuffers
extern void (*glCreateBuffers)(GLsizei, GLuint *);
#define glCreateFramebuffers _glplatform_glCreateFramebuffers
extern void (*glCreateFramebuffers)(GLsizei, GLuint *);
#define glCreateProgramPipelines _glplatform_glCreateProgramPipelines
extern void (*glCreateProgramPipelines)(GLsizei, GLuint *);
#define glCreateQueries _glplatform_glCreateQueries
extern void (*glCreateQueries)(GLenum, GLsizei, GLuint *);
#define glCreateRenderbuffers _glplatform_glCreateRenderbuffers
extern void (*glCreateRenderbuffers)(GLsizei, GLuint *);
#define glCreateSamplers _glplatform_glCreateSamplers
extern void (*glCreateSamplers)(GLsizei, GLuint *);
#define glCreateTextures _glplatform_glCreateTextures
extern void (*glCreateTextures)(GLenum, GLsizei, GLuint *);
#define glCreateTransformFeedbacks _glplatform_glCreateTransformFeedbacks
extern void (*glCreateTransformFeedbacks)(GLsizei, GLuint *);
#define glCreateVertexArrays _glplatform_glCreateVertexArrays
extern void (*glCreateVertexArrays)(GLsizei, GLuint *);
#define glDisableVertexArrayAttrib _glplatform_glDisableVertexArrayAttrib
extern void (*glDisableVertexArrayAttrib)(GLuint, GLuint);
#define glEnableVertexArrayAttrib _glplatform_glEnableVertexArrayAttrib
extern void (*glEnableVertexArrayAttrib)(GLuint, GLuint);
#define glFlushMappedNamedBufferRange _glplatform_glFlushMappedNamedBufferRange
extern void (*glFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr);
#define glGenerateTextureMipmap _glplatform_glGenerateTextureMipmap
extern void (*glGenerateTextureMipmap)(GLuint);
#define glGetCompressedTextureImage _glplatform_glGetCompressedTextureImage
extern void (*glGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *);
#define glGetCompressedTextureSubImage _glplatform_glGetCompressedTextureSubImage
extern void (*glGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
#define glGetGraphicsResetStatus _glplatform_glGetGraphicsResetStatus
extern GLenum (*glGetGraphicsResetStatus)();
#define glGetNamedBufferParameteri64v _glplatform_glGetNamedBufferParameteri64v
extern void (*glGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *);
#define glGetNamedBufferParameteriv _glplatform_glGetNamedBufferParameteriv
extern void (*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedBufferPointerv _glplatform_glGetNamedBufferPointerv
extern void (*glGetNamedBufferPointerv)(GLuint, GLenum, void **);
#define glGetNamedBufferSubData _glplatform_glGetNamedBufferSubData
extern void (*glGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *);
#define glGetNamedFramebufferAttachmentParameteriv _glplatform_glGetNamedFramebufferAttachmentParameteriv
extern void (*glGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *);
#define glGetNamedFramebufferParameteriv _glplatform_glGetNamedFramebufferParameteriv
extern void (*glGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedRenderbufferParameteriv _glplatform_glGetNamedRenderbufferParameteriv
extern void (*glGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetQueryBufferObjecti64v _glplatform_glGetQueryBufferObjecti64v
extern void (*glGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectiv _glplatform_glGetQueryBufferObjectiv
extern void (*glGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectui64v _glplatform_glGetQueryBufferObjectui64v
extern void (*glGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectuiv _glplatform_glGetQueryBufferObjectuiv
extern void (*glGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetTextureImage _glplatform_glGetTextureImage
extern void (*glGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetTextureLevelParameterfv _glplatform_glGetTextureLevelParameterfv
extern void (*glGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *);
#define glGetTextureLevelParameteriv _glplatform_glGetTextureLevelParameteriv
extern void (*glGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *);
#define glGetTextureParameterIiv _glplatform_glGetTextureParameterIiv
extern void (*glGetTextureParameterIiv)(GLuint, GLenum, GLint *);
#define glGetTextureParameterIuiv _glplatform_glGetTextureParameterIuiv
extern void (*glGetTextureParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetTextureParameterfv _glplatform_glGetTextureParameterfv
extern void (*glGetTextureParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetTextureParameteriv _glplatform_glGetTextureParameteriv
extern void (*glGetTextureParameteriv)(GLuint, GLenum, GLint *);
#define glGetTextureSubImage _glplatform_glGetTextureSubImage
extern void (*glGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#define glGetTransformFeedbacki64_v _glplatform_glGetTransformFeedbacki64_v
extern void (*glGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *);
#define glGetTransformFeedbacki_v _glplatform_glGetTransformFeedbacki_v
extern void (*glGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *);
#define glGetTransformFeedbackiv _glplatform_glGetTransformFeedbackiv
extern void (*glGetTransformFeedbackiv)(GLuint, GLenum, GLint *);
#define glGetVertexArrayIndexed64iv _glplatform_glGetVertexArrayIndexed64iv
extern void (*glGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *);
#define glGetVertexArrayIndexediv _glplatform_glGetVertexArrayIndexediv
extern void (*glGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *);
#define glGetVertexArrayiv _glplatform_glGetVertexArrayiv
extern void (*glGetVertexArrayiv)(GLuint, GLenum, GLint *);
#define glGetnCompressedTexImage _glplatform_glGetnCompressedTexImage
extern void (*glGetnCompressedTexImage)(GLenum, GLint, GLsizei, void *);
#define glGetnTexImage _glplatform_glGetnTexImage
extern void (*glGetnTexImage)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetnUniformdv _glplatform_glGetnUniformdv
extern void (*glGetnUniformdv)(GLuint, GLint, GLsizei, GLdouble *);
#define glGetnUniformfv _glplatform_glGetnUniformfv
extern void (*glGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *);
#define glGetnUniformiv _glplatform_glGetnUniformiv
extern void (*glGetnUniformiv)(GLuint, GLint, GLsizei, GLint *);
#define glGetnUniformuiv _glplatform_glGetnUniformuiv
extern void (*glGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *);
#define glInvalidateNamedFramebufferData _glplatform_glInvalidateNamedFramebufferData
extern void (*glInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *);
#define glInvalidateNamedFramebufferSubData _glplatform_glInvalidateNamedFramebufferSubData
extern void (*glInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glMapNamedBuffer _glplatform_glMapNamedBuffer
extern void * (*glMapNamedBuffer)(GLuint, GLenum);
#define glMapNamedBufferRange _glplatform_glMapNamedBufferRange
extern void * (*glMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
#define glMemoryBarrierByRegion _glplatform_glMemoryBarrierByRegion
extern void (*glMemoryBarrierByRegion)(GLbitfield);
#define glNamedBufferData _glplatform_glNamedBufferData
extern void (*glNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum);
#define glNamedBufferStorage _glplatform_glNamedBufferStorage
extern void (*glNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield);
#define glNamedBufferSubData _glplatform_glNamedBufferSubData
extern void (*glNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *);
#define glNamedFramebufferDrawBuffer _glplatform_glNamedFramebufferDrawBuffer
extern void (*glNamedFramebufferDrawBuffer)(GLuint, GLenum);
#define glNamedFramebufferDrawBuffers _glplatform_glNamedFramebufferDrawBuffers
extern void (*glNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *);
#define glNamedFramebufferParameteri _glplatform_glNamedFramebufferParameteri
extern void (*glNamedFramebufferParameteri)(GLuint, GLenum, GLint);
#define glNamedFramebufferReadBuffer _glplatform_glNamedFramebufferReadBuffer
extern void (*glNamedFramebufferReadBuffer)(GLuint, GLenum);
#define glNamedFramebufferRenderbuffer _glplatform_glNamedFramebufferRenderbuffer
extern void (*glNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint);
#define glNamedFramebufferTexture _glplatform_glNamedFramebufferTexture
extern void (*glNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint);
#define glNamedFramebufferTextureLayer _glplatform_glNamedFramebufferTextureLayer
extern void (*glNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint);
#define glNamedRenderbufferStorage _glplatform_glNamedRenderbufferStorage
extern void (*glNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei);
#define glNamedRenderbufferStorageMultisample _glplatform_glNamedRenderbufferStorageMultisample
extern void (*glNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glReadnPixels _glplatform_glReadnPixels
extern void (*glReadnPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#define glTextureBarrier _glplatform_glTextureBarrier
extern void (*glTextureBarrier)();
#define glTextureBuffer _glplatform_glTextureBuffer
extern void (*glTextureBuffer)(GLuint, GLenum, GLuint);
#define glTextureBufferRange _glplatform_glTextureBufferRange
extern void (*glTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
#define glTextureParameterIiv _glplatform_glTextureParameterIiv
extern void (*glTextureParameterIiv)(GLuint, GLenum, const GLint *);
#define glTextureParameterIuiv _glplatform_glTextureParameterIuiv
extern void (*glTextureParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glTextureParameterf _glplatform_glTextureParameterf
extern void (*glTextureParameterf)(GLuint, GLenum, GLfloat);
#define glTextureParameterfv _glplatform_glTextureParameterfv
extern void (*glTextureParameterfv)(GLuint, GLenum, const GLfloat *);
#define glTextureParameteri _glplatform_glTextureParameteri
extern void (*glTextureParameteri)(GLuint, GLenum, GLint);
#define glTextureParameteriv _glplatform_glTextureParameteriv
extern void (*glTextureParameteriv)(GLuint, GLenum, const GLint *);
#define glTextureStorage1D _glplatform_glTextureStorage1D
extern void (*glTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei);
#define glTextureStorage2D _glplatform_glTextureStorage2D
extern void (*glTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glTextureStorage2DMultisample _glplatform_glTextureStorage2DMultisample
extern void (*glTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTextureStorage3D _glplatform_glTextureStorage3D
extern void (*glTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#define glTextureStorage3DMultisample _glplatform_glTextureStorage3DMultisample
extern void (*glTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTextureSubImage1D _glplatform_glTextureSubImage1D
extern void (*glTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage2D _glplatform_glTextureSubImage2D
extern void (*glTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage3D _glplatform_glTextureSubImage3D
extern void (*glTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTransformFeedbackBufferBase _glplatform_glTransformFeedbackBufferBase
extern void (*glTransformFeedbackBufferBase)(GLuint, GLuint, GLuint);
#define glTransformFeedbackBufferRange _glplatform_glTransformFeedbackBufferRange
extern void (*glTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glUnmapNamedBuffer _glplatform_glUnmapNamedBuffer
extern GLboolean (*glUnmapNamedBuffer)(GLuint);
#define glVertexArrayAttribBinding _glplatform_glVertexArrayAttribBinding
extern void (*glVertexArrayAttribBinding)(GLuint, GLuint, GLuint);
#define glVertexArrayAttribFormat _glplatform_glVertexArrayAttribFormat
extern void (*glVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexArrayAttribIFormat _glplatform_glVertexArrayAttribIFormat
extern void (*glVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayAttribLFormat _glplatform_glVertexArrayAttribLFormat
extern void (*glVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayBindingDivisor _glplatform_glVertexArrayBindingDivisor
extern void (*glVertexArrayBindingDivisor)(GLuint, GLuint, GLuint);
#define glVertexArrayElementBuffer _glplatform_glVertexArrayElementBuffer
extern void (*glVertexArrayElementBuffer)(GLuint, GLuint);
#define glVertexArrayVertexBuffer _glplatform_glVertexArrayVertexBuffer
extern void (*glVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
#define glVertexArrayVertexBuffers _glplatform_glVertexArrayVertexBuffers
extern void (*glVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#endif


#if defined(GLPLATFORM_ENABLE_GL_ARB_ES2_compatibility)
extern bool GLPLATFORM_GL_ARB_ES2_compatibility;

#define GL_FIXED 0x140c
#define GL_HIGH_FLOAT 0x8df2
#define GL_HIGH_INT 0x8df5
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8b9b
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8b9a
#define GL_LOW_FLOAT 0x8df0
#define GL_LOW_INT 0x8df3
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8dfd
#define GL_MAX_VARYING_VECTORS 0x8dfc
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8dfb
#define GL_MEDIUM_FLOAT 0x8df1
#define GL_MEDIUM_INT 0x8df4
#define GL_NUM_SHADER_BINARY_FORMATS 0x8df9
#define GL_RGB565 0x8d62
#define GL_SHADER_BINARY_FORMATS 0x8df8
#define GL_SHADER_COMPILER 0x8dfa

#define glClearDepthf _glplatform_glClearDepthf
extern void (*glClearDepthf)(GLfloat);
#define glDepthRangef _glplatform_glDepthRangef
extern void (*glDepthRangef)(GLfloat, GLfloat);
#define glGetShaderPrecisionFormat _glplatform_glGetShaderPrecisionFormat
extern void (*glGetShaderPrecisionFormat)(GLenum, GLenum, GLint *, GLint *);
#define glReleaseShaderCompiler _glplatform_glReleaseShaderCompiler
extern void (*glReleaseShaderCompiler)();
#define glShaderBinary _glplatform_glShaderBinary
extern void (*glShaderBinary)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_ES3_1_compatibility)
extern bool GLPLATFORM_GL_ARB_ES3_1_compatibility;

#define GL_BACK 0x405

#define glMemoryBarrierByRegion _glplatform_glMemoryBarrierByRegion
extern void (*glMemoryBarrierByRegion)(GLbitfield);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_ES3_compatibility)
extern bool GLPLATFORM_GL_ARB_ES3_compatibility;

#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8d6a
#define GL_COMPRESSED_R11_EAC 0x9270
#define GL_COMPRESSED_RG11_EAC 0x9272
#define GL_COMPRESSED_RGB8_ETC2 0x9274
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#define GL_COMPRESSED_SIGNED_R11_EAC 0x9271
#define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_SRGB8_ETC2 0x9275
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_MAX_ELEMENT_INDEX 0x8d6b
#define GL_PRIMITIVE_RESTART_FIXED_INDEX 0x8d69

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_arrays_of_arrays)
extern bool GLPLATFORM_GL_ARB_arrays_of_arrays;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_base_instance)
extern bool GLPLATFORM_GL_ARB_base_instance;


#define glDrawArraysInstancedBaseInstance _glplatform_glDrawArraysInstancedBaseInstance
extern void (*glDrawArraysInstancedBaseInstance)(GLenum, GLint, GLsizei, GLsizei, GLuint);
#define glDrawElementsInstancedBaseInstance _glplatform_glDrawElementsInstancedBaseInstance
extern void (*glDrawElementsInstancedBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
#define glDrawElementsInstancedBaseVertexBaseInstance _glplatform_glDrawElementsInstancedBaseVertexBaseInstance
extern void (*glDrawElementsInstancedBaseVertexBaseInstance)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_bindless_texture)
extern bool GLPLATFORM_GL_ARB_bindless_texture;
#ifndef GLPLATFORM_TYPE_GLuint64
#define GLPLATFORM_TYPE_GLuint64
typedef uint64_t GLuint64;
#endif
#ifndef GLPLATFORM_TYPE_GLuint64EXT
#define GLPLATFORM_TYPE_GLuint64EXT
typedef uint64_t GLuint64EXT;
#endif

#define GL_UNSIGNED_INT64_ARB 0x140f

#define glGetImageHandleARB _glplatform_glGetImageHandleARB
extern GLuint64 (*glGetImageHandleARB)(GLuint, GLint, GLboolean, GLint, GLenum);
#define glGetTextureHandleARB _glplatform_glGetTextureHandleARB
extern GLuint64 (*glGetTextureHandleARB)(GLuint);
#define glGetTextureSamplerHandleARB _glplatform_glGetTextureSamplerHandleARB
extern GLuint64 (*glGetTextureSamplerHandleARB)(GLuint, GLuint);
#define glGetVertexAttribLui64vARB _glplatform_glGetVertexAttribLui64vARB
extern void (*glGetVertexAttribLui64vARB)(GLuint, GLenum, GLuint64EXT *);
#define glIsImageHandleResidentARB _glplatform_glIsImageHandleResidentARB
extern GLboolean (*glIsImageHandleResidentARB)(GLuint64);
#define glIsTextureHandleResidentARB _glplatform_glIsTextureHandleResidentARB
extern GLboolean (*glIsTextureHandleResidentARB)(GLuint64);
#define glMakeImageHandleNonResidentARB _glplatform_glMakeImageHandleNonResidentARB
extern void (*glMakeImageHandleNonResidentARB)(GLuint64);
#define glMakeImageHandleResidentARB _glplatform_glMakeImageHandleResidentARB
extern void (*glMakeImageHandleResidentARB)(GLuint64, GLenum);
#define glMakeTextureHandleNonResidentARB _glplatform_glMakeTextureHandleNonResidentARB
extern void (*glMakeTextureHandleNonResidentARB)(GLuint64);
#define glMakeTextureHandleResidentARB _glplatform_glMakeTextureHandleResidentARB
extern void (*glMakeTextureHandleResidentARB)(GLuint64);
#define glProgramUniformHandleui64ARB _glplatform_glProgramUniformHandleui64ARB
extern void (*glProgramUniformHandleui64ARB)(GLuint, GLint, GLuint64);
#define glProgramUniformHandleui64vARB _glplatform_glProgramUniformHandleui64vARB
extern void (*glProgramUniformHandleui64vARB)(GLuint, GLint, GLsizei, const GLuint64 *);
#define glUniformHandleui64ARB _glplatform_glUniformHandleui64ARB
extern void (*glUniformHandleui64ARB)(GLint, GLuint64);
#define glUniformHandleui64vARB _glplatform_glUniformHandleui64vARB
extern void (*glUniformHandleui64vARB)(GLint, GLsizei, const GLuint64 *);
#define glVertexAttribL1ui64ARB _glplatform_glVertexAttribL1ui64ARB
extern void (*glVertexAttribL1ui64ARB)(GLuint, GLuint64EXT);
#define glVertexAttribL1ui64vARB _glplatform_glVertexAttribL1ui64vARB
extern void (*glVertexAttribL1ui64vARB)(GLuint, const GLuint64EXT *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_blend_func_extended)
extern bool GLPLATFORM_GL_ARB_blend_func_extended;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88fc
#define GL_ONE_MINUS_SRC1_ALPHA 0x88fb
#define GL_ONE_MINUS_SRC1_COLOR 0x88fa
#define GL_SRC1_ALPHA 0x8589
#define GL_SRC1_COLOR 0x88f9

#define glBindFragDataLocationIndexed _glplatform_glBindFragDataLocationIndexed
extern void (*glBindFragDataLocationIndexed)(GLuint, GLuint, GLuint, const GLchar *);
#define glGetFragDataIndex _glplatform_glGetFragDataIndex
extern GLint (*glGetFragDataIndex)(GLuint, const GLchar *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_buffer_storage)
extern bool GLPLATFORM_GL_ARB_buffer_storage;

#define GL_BUFFER_IMMUTABLE_STORAGE 0x821f
#define GL_BUFFER_STORAGE_FLAGS 0x8220
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x4000
#define GL_CLIENT_STORAGE_BIT 0x200
#define GL_DYNAMIC_STORAGE_BIT 0x100
#define GL_MAP_COHERENT_BIT 0x80
#define GL_MAP_PERSISTENT_BIT 0x40
#define GL_MAP_READ_BIT 0x1
#define GL_MAP_WRITE_BIT 0x2

#define glBufferStorage _glplatform_glBufferStorage
extern void (*glBufferStorage)(GLenum, GLsizeiptr, const void *, GLbitfield);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_cl_event)
extern bool GLPLATFORM_GL_ARB_cl_event;
#ifndef GLPLATFORM_TYPE_GLsync
#define GLPLATFORM_TYPE_GLsync
typedef struct __GLsync *GLsync;
#endif
#ifndef GLPLATFORM_TYPE_struct__cl_context
#define GLPLATFORM_TYPE_struct__cl_context
struct _cl_context;
#endif
#ifndef GLPLATFORM_TYPE_struct__cl_event
#define GLPLATFORM_TYPE_struct__cl_event
struct _cl_event;
#endif

#define GL_SYNC_CL_EVENT_ARB 0x8240
#define GL_SYNC_CL_EVENT_COMPLETE_ARB 0x8241

#define glCreateSyncFromCLeventARB _glplatform_glCreateSyncFromCLeventARB
extern GLsync (*glCreateSyncFromCLeventARB)(struct _cl_context *, struct _cl_event *, GLbitfield);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_clear_buffer_object)
extern bool GLPLATFORM_GL_ARB_clear_buffer_object;


#define glClearBufferData _glplatform_glClearBufferData
extern void (*glClearBufferData)(GLenum, GLenum, GLenum, GLenum, const void *);
#define glClearBufferSubData _glplatform_glClearBufferSubData
extern void (*glClearBufferSubData)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_clear_texture)
extern bool GLPLATFORM_GL_ARB_clear_texture;

#define GL_CLEAR_TEXTURE 0x9365

#define glClearTexImage _glplatform_glClearTexImage
extern void (*glClearTexImage)(GLuint, GLint, GLenum, GLenum, const void *);
#define glClearTexSubImage _glplatform_glClearTexSubImage
extern void (*glClearTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_clip_control)
extern bool GLPLATFORM_GL_ARB_clip_control;

#define GL_CLIP_DEPTH_MODE 0x935d
#define GL_CLIP_ORIGIN 0x935c
#define GL_LOWER_LEFT 0x8ca1
#define GL_NEGATIVE_ONE_TO_ONE 0x935e
#define GL_UPPER_LEFT 0x8ca2
#define GL_ZERO_TO_ONE 0x935f

#define glClipControl _glplatform_glClipControl
extern void (*glClipControl)(GLenum, GLenum);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_compressed_texture_pixel_storage)
extern bool GLPLATFORM_GL_ARB_compressed_texture_pixel_storage;

#define GL_PACK_COMPRESSED_BLOCK_DEPTH 0x912d
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT 0x912c
#define GL_PACK_COMPRESSED_BLOCK_SIZE 0x912e
#define GL_PACK_COMPRESSED_BLOCK_WIDTH 0x912b
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH 0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE 0x912a
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH 0x9127

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_compute_shader)
extern bool GLPLATFORM_GL_ARB_compute_shader;

#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ed
#define GL_COMPUTE_SHADER 0x91b9
#define GL_COMPUTE_SHADER_BIT 0x20
#define GL_COMPUTE_WORK_GROUP_SIZE 0x8267
#define GL_DISPATCH_INDIRECT_BUFFER 0x90ee
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90ef
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91bd
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91bc
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91bb
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91be
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90eb
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91bf
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90ec

#define glDispatchCompute _glplatform_glDispatchCompute
extern void (*glDispatchCompute)(GLuint, GLuint, GLuint);
#define glDispatchComputeIndirect _glplatform_glDispatchComputeIndirect
extern void (*glDispatchComputeIndirect)(GLintptr);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_compute_variable_group_size)
extern bool GLPLATFORM_GL_ARB_compute_variable_group_size;

#define GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB 0x90eb
#define GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB 0x91bf
#define GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB 0x9344
#define GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB 0x9345

#define glDispatchComputeGroupSizeARB _glplatform_glDispatchComputeGroupSizeARB
extern void (*glDispatchComputeGroupSizeARB)(GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_conditional_render_inverted)
extern bool GLPLATFORM_GL_ARB_conditional_render_inverted;

#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8e1a
#define GL_QUERY_BY_REGION_WAIT_INVERTED 0x8e19
#define GL_QUERY_NO_WAIT_INVERTED 0x8e18
#define GL_QUERY_WAIT_INVERTED 0x8e17

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_conservative_depth)
extern bool GLPLATFORM_GL_ARB_conservative_depth;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_copy_buffer)
extern bool GLPLATFORM_GL_ARB_copy_buffer;

#define GL_COPY_READ_BUFFER 0x8f36
#define GL_COPY_WRITE_BUFFER 0x8f37

#define glCopyBufferSubData _glplatform_glCopyBufferSubData
extern void (*glCopyBufferSubData)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_copy_image)
extern bool GLPLATFORM_GL_ARB_copy_image;


#define glCopyImageSubData _glplatform_glCopyImageSubData
extern void (*glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_cull_distance)
extern bool GLPLATFORM_GL_ARB_cull_distance;

#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82fa
#define GL_MAX_CULL_DISTANCES 0x82f9

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_debug_output)
extern bool GLPLATFORM_GL_ARB_debug_output;
#ifndef GLPLATFORM_TYPE_GLDEBUGPROCARB
#define GLPLATFORM_TYPE_GLDEBUGPROCARB
typedef void ( *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_DEBUG_CALLBACK_FUNCTION_ARB 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB 0x8245
#define GL_DEBUG_LOGGED_MESSAGES_ARB 0x9145
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB 0x8242
#define GL_DEBUG_SEVERITY_HIGH_ARB 0x9146
#define GL_DEBUG_SEVERITY_LOW_ARB 0x9148
#define GL_DEBUG_SEVERITY_MEDIUM_ARB 0x9147
#define GL_DEBUG_SOURCE_API_ARB 0x8246
#define GL_DEBUG_SOURCE_APPLICATION_ARB 0x824a
#define GL_DEBUG_SOURCE_OTHER_ARB 0x824b
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB 0x8249
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824d
#define GL_DEBUG_TYPE_ERROR_ARB 0x824c
#define GL_DEBUG_TYPE_OTHER_ARB 0x8251
#define GL_DEBUG_TYPE_PERFORMANCE_ARB 0x8250
#define GL_DEBUG_TYPE_PORTABILITY_ARB 0x824f
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824e
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB 0x9144
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB 0x9143

#define glDebugMessageCallbackARB _glplatform_glDebugMessageCallbackARB
extern void (*glDebugMessageCallbackARB)(GLDEBUGPROCARB, const void *);
#define glDebugMessageControlARB _glplatform_glDebugMessageControlARB
extern void (*glDebugMessageControlARB)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
#define glDebugMessageInsertARB _glplatform_glDebugMessageInsertARB
extern void (*glDebugMessageInsertARB)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
#define glGetDebugMessageLogARB _glplatform_glGetDebugMessageLogARB
extern GLuint (*glGetDebugMessageLogARB)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_depth_buffer_float)
extern bool GLPLATFORM_GL_ARB_depth_buffer_float;

#define GL_DEPTH32F_STENCIL8 0x8cad
#define GL_DEPTH_COMPONENT32F 0x8cac
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8dad

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_depth_clamp)
extern bool GLPLATFORM_GL_ARB_depth_clamp;

#define GL_DEPTH_CLAMP 0x864f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_derivative_control)
extern bool GLPLATFORM_GL_ARB_derivative_control;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_direct_state_access)
extern bool GLPLATFORM_GL_ARB_direct_state_access;
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif

#define GL_QUERY_TARGET 0x82ea
#define GL_TEXTURE_BINDING_1D 0x8068
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8c1c
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8c1d
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_BINDING_3D 0x806a
#define GL_TEXTURE_BINDING_BUFFER 0x8c2c
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900a
#define GL_TEXTURE_BINDING_RECTANGLE 0x84f6
#define GL_TEXTURE_TARGET 0x1006

#define glBindTextureUnit _glplatform_glBindTextureUnit
extern void (*glBindTextureUnit)(GLuint, GLuint);
#define glBlitNamedFramebuffer _glplatform_glBlitNamedFramebuffer
extern void (*glBlitNamedFramebuffer)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glCheckNamedFramebufferStatus _glplatform_glCheckNamedFramebufferStatus
extern GLenum (*glCheckNamedFramebufferStatus)(GLuint, GLenum);
#define glClearNamedBufferData _glplatform_glClearNamedBufferData
extern void (*glClearNamedBufferData)(GLuint, GLenum, GLenum, GLenum, const void *);
#define glClearNamedBufferSubData _glplatform_glClearNamedBufferSubData
extern void (*glClearNamedBufferSubData)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
#define glClearNamedFramebufferfi _glplatform_glClearNamedFramebufferfi
extern void (*glClearNamedFramebufferfi)(GLuint, GLenum, const GLfloat, GLint);
#define glClearNamedFramebufferfv _glplatform_glClearNamedFramebufferfv
extern void (*glClearNamedFramebufferfv)(GLuint, GLenum, GLint, const GLfloat *);
#define glClearNamedFramebufferiv _glplatform_glClearNamedFramebufferiv
extern void (*glClearNamedFramebufferiv)(GLuint, GLenum, GLint, const GLint *);
#define glClearNamedFramebufferuiv _glplatform_glClearNamedFramebufferuiv
extern void (*glClearNamedFramebufferuiv)(GLuint, GLenum, GLint, const GLuint *);
#define glCompressedTextureSubImage1D _glplatform_glCompressedTextureSubImage1D
extern void (*glCompressedTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage2D _glplatform_glCompressedTextureSubImage2D
extern void (*glCompressedTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCompressedTextureSubImage3D _glplatform_glCompressedTextureSubImage3D
extern void (*glCompressedTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
#define glCopyNamedBufferSubData _glplatform_glCopyNamedBufferSubData
extern void (*glCopyNamedBufferSubData)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
#define glCopyTextureSubImage1D _glplatform_glCopyTextureSubImage1D
extern void (*glCopyTextureSubImage1D)(GLuint, GLint, GLint, GLint, GLint, GLsizei);
#define glCopyTextureSubImage2D _glplatform_glCopyTextureSubImage2D
extern void (*glCopyTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCopyTextureSubImage3D _glplatform_glCopyTextureSubImage3D
extern void (*glCopyTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
#define glCreateBuffers _glplatform_glCreateBuffers
extern void (*glCreateBuffers)(GLsizei, GLuint *);
#define glCreateFramebuffers _glplatform_glCreateFramebuffers
extern void (*glCreateFramebuffers)(GLsizei, GLuint *);
#define glCreateProgramPipelines _glplatform_glCreateProgramPipelines
extern void (*glCreateProgramPipelines)(GLsizei, GLuint *);
#define glCreateQueries _glplatform_glCreateQueries
extern void (*glCreateQueries)(GLenum, GLsizei, GLuint *);
#define glCreateRenderbuffers _glplatform_glCreateRenderbuffers
extern void (*glCreateRenderbuffers)(GLsizei, GLuint *);
#define glCreateSamplers _glplatform_glCreateSamplers
extern void (*glCreateSamplers)(GLsizei, GLuint *);
#define glCreateTextures _glplatform_glCreateTextures
extern void (*glCreateTextures)(GLenum, GLsizei, GLuint *);
#define glCreateTransformFeedbacks _glplatform_glCreateTransformFeedbacks
extern void (*glCreateTransformFeedbacks)(GLsizei, GLuint *);
#define glCreateVertexArrays _glplatform_glCreateVertexArrays
extern void (*glCreateVertexArrays)(GLsizei, GLuint *);
#define glDisableVertexArrayAttrib _glplatform_glDisableVertexArrayAttrib
extern void (*glDisableVertexArrayAttrib)(GLuint, GLuint);
#define glEnableVertexArrayAttrib _glplatform_glEnableVertexArrayAttrib
extern void (*glEnableVertexArrayAttrib)(GLuint, GLuint);
#define glFlushMappedNamedBufferRange _glplatform_glFlushMappedNamedBufferRange
extern void (*glFlushMappedNamedBufferRange)(GLuint, GLintptr, GLsizeiptr);
#define glGenerateTextureMipmap _glplatform_glGenerateTextureMipmap
extern void (*glGenerateTextureMipmap)(GLuint);
#define glGetCompressedTextureImage _glplatform_glGetCompressedTextureImage
extern void (*glGetCompressedTextureImage)(GLuint, GLint, GLsizei, void *);
#define glGetNamedBufferParameteri64v _glplatform_glGetNamedBufferParameteri64v
extern void (*glGetNamedBufferParameteri64v)(GLuint, GLenum, GLint64 *);
#define glGetNamedBufferParameteriv _glplatform_glGetNamedBufferParameteriv
extern void (*glGetNamedBufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedBufferPointerv _glplatform_glGetNamedBufferPointerv
extern void (*glGetNamedBufferPointerv)(GLuint, GLenum, void **);
#define glGetNamedBufferSubData _glplatform_glGetNamedBufferSubData
extern void (*glGetNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, void *);
#define glGetNamedFramebufferAttachmentParameteriv _glplatform_glGetNamedFramebufferAttachmentParameteriv
extern void (*glGetNamedFramebufferAttachmentParameteriv)(GLuint, GLenum, GLenum, GLint *);
#define glGetNamedFramebufferParameteriv _glplatform_glGetNamedFramebufferParameteriv
extern void (*glGetNamedFramebufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetNamedRenderbufferParameteriv _glplatform_glGetNamedRenderbufferParameteriv
extern void (*glGetNamedRenderbufferParameteriv)(GLuint, GLenum, GLint *);
#define glGetQueryBufferObjecti64v _glplatform_glGetQueryBufferObjecti64v
extern void (*glGetQueryBufferObjecti64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectiv _glplatform_glGetQueryBufferObjectiv
extern void (*glGetQueryBufferObjectiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectui64v _glplatform_glGetQueryBufferObjectui64v
extern void (*glGetQueryBufferObjectui64v)(GLuint, GLuint, GLenum, GLintptr);
#define glGetQueryBufferObjectuiv _glplatform_glGetQueryBufferObjectuiv
extern void (*glGetQueryBufferObjectuiv)(GLuint, GLuint, GLenum, GLintptr);
#define glGetTextureImage _glplatform_glGetTextureImage
extern void (*glGetTextureImage)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetTextureLevelParameterfv _glplatform_glGetTextureLevelParameterfv
extern void (*glGetTextureLevelParameterfv)(GLuint, GLint, GLenum, GLfloat *);
#define glGetTextureLevelParameteriv _glplatform_glGetTextureLevelParameteriv
extern void (*glGetTextureLevelParameteriv)(GLuint, GLint, GLenum, GLint *);
#define glGetTextureParameterIiv _glplatform_glGetTextureParameterIiv
extern void (*glGetTextureParameterIiv)(GLuint, GLenum, GLint *);
#define glGetTextureParameterIuiv _glplatform_glGetTextureParameterIuiv
extern void (*glGetTextureParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetTextureParameterfv _glplatform_glGetTextureParameterfv
extern void (*glGetTextureParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetTextureParameteriv _glplatform_glGetTextureParameteriv
extern void (*glGetTextureParameteriv)(GLuint, GLenum, GLint *);
#define glGetTransformFeedbacki64_v _glplatform_glGetTransformFeedbacki64_v
extern void (*glGetTransformFeedbacki64_v)(GLuint, GLenum, GLuint, GLint64 *);
#define glGetTransformFeedbacki_v _glplatform_glGetTransformFeedbacki_v
extern void (*glGetTransformFeedbacki_v)(GLuint, GLenum, GLuint, GLint *);
#define glGetTransformFeedbackiv _glplatform_glGetTransformFeedbackiv
extern void (*glGetTransformFeedbackiv)(GLuint, GLenum, GLint *);
#define glGetVertexArrayIndexed64iv _glplatform_glGetVertexArrayIndexed64iv
extern void (*glGetVertexArrayIndexed64iv)(GLuint, GLuint, GLenum, GLint64 *);
#define glGetVertexArrayIndexediv _glplatform_glGetVertexArrayIndexediv
extern void (*glGetVertexArrayIndexediv)(GLuint, GLuint, GLenum, GLint *);
#define glGetVertexArrayiv _glplatform_glGetVertexArrayiv
extern void (*glGetVertexArrayiv)(GLuint, GLenum, GLint *);
#define glInvalidateNamedFramebufferData _glplatform_glInvalidateNamedFramebufferData
extern void (*glInvalidateNamedFramebufferData)(GLuint, GLsizei, const GLenum *);
#define glInvalidateNamedFramebufferSubData _glplatform_glInvalidateNamedFramebufferSubData
extern void (*glInvalidateNamedFramebufferSubData)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glMapNamedBuffer _glplatform_glMapNamedBuffer
extern void * (*glMapNamedBuffer)(GLuint, GLenum);
#define glMapNamedBufferRange _glplatform_glMapNamedBufferRange
extern void * (*glMapNamedBufferRange)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
#define glNamedBufferData _glplatform_glNamedBufferData
extern void (*glNamedBufferData)(GLuint, GLsizeiptr, const void *, GLenum);
#define glNamedBufferStorage _glplatform_glNamedBufferStorage
extern void (*glNamedBufferStorage)(GLuint, GLsizeiptr, const void *, GLbitfield);
#define glNamedBufferSubData _glplatform_glNamedBufferSubData
extern void (*glNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void *);
#define glNamedFramebufferDrawBuffer _glplatform_glNamedFramebufferDrawBuffer
extern void (*glNamedFramebufferDrawBuffer)(GLuint, GLenum);
#define glNamedFramebufferDrawBuffers _glplatform_glNamedFramebufferDrawBuffers
extern void (*glNamedFramebufferDrawBuffers)(GLuint, GLsizei, const GLenum *);
#define glNamedFramebufferParameteri _glplatform_glNamedFramebufferParameteri
extern void (*glNamedFramebufferParameteri)(GLuint, GLenum, GLint);
#define glNamedFramebufferReadBuffer _glplatform_glNamedFramebufferReadBuffer
extern void (*glNamedFramebufferReadBuffer)(GLuint, GLenum);
#define glNamedFramebufferRenderbuffer _glplatform_glNamedFramebufferRenderbuffer
extern void (*glNamedFramebufferRenderbuffer)(GLuint, GLenum, GLenum, GLuint);
#define glNamedFramebufferTexture _glplatform_glNamedFramebufferTexture
extern void (*glNamedFramebufferTexture)(GLuint, GLenum, GLuint, GLint);
#define glNamedFramebufferTextureLayer _glplatform_glNamedFramebufferTextureLayer
extern void (*glNamedFramebufferTextureLayer)(GLuint, GLenum, GLuint, GLint, GLint);
#define glNamedRenderbufferStorage _glplatform_glNamedRenderbufferStorage
extern void (*glNamedRenderbufferStorage)(GLuint, GLenum, GLsizei, GLsizei);
#define glNamedRenderbufferStorageMultisample _glplatform_glNamedRenderbufferStorageMultisample
extern void (*glNamedRenderbufferStorageMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glTextureBuffer _glplatform_glTextureBuffer
extern void (*glTextureBuffer)(GLuint, GLenum, GLuint);
#define glTextureBufferRange _glplatform_glTextureBufferRange
extern void (*glTextureBufferRange)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
#define glTextureParameterIiv _glplatform_glTextureParameterIiv
extern void (*glTextureParameterIiv)(GLuint, GLenum, const GLint *);
#define glTextureParameterIuiv _glplatform_glTextureParameterIuiv
extern void (*glTextureParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glTextureParameterf _glplatform_glTextureParameterf
extern void (*glTextureParameterf)(GLuint, GLenum, GLfloat);
#define glTextureParameterfv _glplatform_glTextureParameterfv
extern void (*glTextureParameterfv)(GLuint, GLenum, const GLfloat *);
#define glTextureParameteri _glplatform_glTextureParameteri
extern void (*glTextureParameteri)(GLuint, GLenum, GLint);
#define glTextureParameteriv _glplatform_glTextureParameteriv
extern void (*glTextureParameteriv)(GLuint, GLenum, const GLint *);
#define glTextureStorage1D _glplatform_glTextureStorage1D
extern void (*glTextureStorage1D)(GLuint, GLsizei, GLenum, GLsizei);
#define glTextureStorage2D _glplatform_glTextureStorage2D
extern void (*glTextureStorage2D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
#define glTextureStorage2DMultisample _glplatform_glTextureStorage2DMultisample
extern void (*glTextureStorage2DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTextureStorage3D _glplatform_glTextureStorage3D
extern void (*glTextureStorage3D)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#define glTextureStorage3DMultisample _glplatform_glTextureStorage3DMultisample
extern void (*glTextureStorage3DMultisample)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#define glTextureSubImage1D _glplatform_glTextureSubImage1D
extern void (*glTextureSubImage1D)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage2D _glplatform_glTextureSubImage2D
extern void (*glTextureSubImage2D)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTextureSubImage3D _glplatform_glTextureSubImage3D
extern void (*glTextureSubImage3D)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
#define glTransformFeedbackBufferBase _glplatform_glTransformFeedbackBufferBase
extern void (*glTransformFeedbackBufferBase)(GLuint, GLuint, GLuint);
#define glTransformFeedbackBufferRange _glplatform_glTransformFeedbackBufferRange
extern void (*glTransformFeedbackBufferRange)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glUnmapNamedBuffer _glplatform_glUnmapNamedBuffer
extern GLboolean (*glUnmapNamedBuffer)(GLuint);
#define glVertexArrayAttribBinding _glplatform_glVertexArrayAttribBinding
extern void (*glVertexArrayAttribBinding)(GLuint, GLuint, GLuint);
#define glVertexArrayAttribFormat _glplatform_glVertexArrayAttribFormat
extern void (*glVertexArrayAttribFormat)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexArrayAttribIFormat _glplatform_glVertexArrayAttribIFormat
extern void (*glVertexArrayAttribIFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayAttribLFormat _glplatform_glVertexArrayAttribLFormat
extern void (*glVertexArrayAttribLFormat)(GLuint, GLuint, GLint, GLenum, GLuint);
#define glVertexArrayBindingDivisor _glplatform_glVertexArrayBindingDivisor
extern void (*glVertexArrayBindingDivisor)(GLuint, GLuint, GLuint);
#define glVertexArrayElementBuffer _glplatform_glVertexArrayElementBuffer
extern void (*glVertexArrayElementBuffer)(GLuint, GLuint);
#define glVertexArrayVertexBuffer _glplatform_glVertexArrayVertexBuffer
extern void (*glVertexArrayVertexBuffer)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
#define glVertexArrayVertexBuffers _glplatform_glVertexArrayVertexBuffers
extern void (*glVertexArrayVertexBuffers)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_draw_buffers_blend)
extern bool GLPLATFORM_GL_ARB_draw_buffers_blend;


#define glBlendEquationSeparateiARB _glplatform_glBlendEquationSeparateiARB
extern void (*glBlendEquationSeparateiARB)(GLuint, GLenum, GLenum);
#define glBlendEquationiARB _glplatform_glBlendEquationiARB
extern void (*glBlendEquationiARB)(GLuint, GLenum);
#define glBlendFuncSeparateiARB _glplatform_glBlendFuncSeparateiARB
extern void (*glBlendFuncSeparateiARB)(GLuint, GLenum, GLenum, GLenum, GLenum);
#define glBlendFunciARB _glplatform_glBlendFunciARB
extern void (*glBlendFunciARB)(GLuint, GLenum, GLenum);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_draw_elements_base_vertex)
extern bool GLPLATFORM_GL_ARB_draw_elements_base_vertex;


#define glDrawElementsBaseVertex _glplatform_glDrawElementsBaseVertex
extern void (*glDrawElementsBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLint);
#define glDrawElementsInstancedBaseVertex _glplatform_glDrawElementsInstancedBaseVertex
extern void (*glDrawElementsInstancedBaseVertex)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
#define glDrawRangeElementsBaseVertex _glplatform_glDrawRangeElementsBaseVertex
extern void (*glDrawRangeElementsBaseVertex)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
#define glMultiDrawElementsBaseVertex _glplatform_glMultiDrawElementsBaseVertex
extern void (*glMultiDrawElementsBaseVertex)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_draw_indirect)
extern bool GLPLATFORM_GL_ARB_draw_indirect;

#define GL_DRAW_INDIRECT_BUFFER 0x8f3f
#define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8f43

#define glDrawArraysIndirect _glplatform_glDrawArraysIndirect
extern void (*glDrawArraysIndirect)(GLenum, const void *);
#define glDrawElementsIndirect _glplatform_glDrawElementsIndirect
extern void (*glDrawElementsIndirect)(GLenum, GLenum, const void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_enhanced_layouts)
extern bool GLPLATFORM_GL_ARB_enhanced_layouts;

#define GL_LOCATION_COMPONENT 0x934a
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8c8e
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934b
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934c

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_explicit_attrib_location)
extern bool GLPLATFORM_GL_ARB_explicit_attrib_location;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_explicit_uniform_location)
extern bool GLPLATFORM_GL_ARB_explicit_uniform_location;

#define GL_MAX_UNIFORM_LOCATIONS 0x826e

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_fragment_coord_conventions)
extern bool GLPLATFORM_GL_ARB_fragment_coord_conventions;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_fragment_layer_viewport)
extern bool GLPLATFORM_GL_ARB_fragment_layer_viewport;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_framebuffer_no_attachments)
extern bool GLPLATFORM_GL_ARB_framebuffer_no_attachments;

#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT 0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS 0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES 0x9313
#define GL_FRAMEBUFFER_DEFAULT_WIDTH 0x9310
#define GL_MAX_FRAMEBUFFER_HEIGHT 0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS 0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES 0x9318
#define GL_MAX_FRAMEBUFFER_WIDTH 0x9315

#define glFramebufferParameteri _glplatform_glFramebufferParameteri
extern void (*glFramebufferParameteri)(GLenum, GLenum, GLint);
#define glGetFramebufferParameteriv _glplatform_glGetFramebufferParameteriv
extern void (*glGetFramebufferParameteriv)(GLenum, GLenum, GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_framebuffer_object)
extern bool GLPLATFORM_GL_ARB_framebuffer_object;

#define GL_COLOR_ATTACHMENT0 0x8ce0
#define GL_COLOR_ATTACHMENT1 0x8ce1
#define GL_COLOR_ATTACHMENT10 0x8cea
#define GL_COLOR_ATTACHMENT11 0x8ceb
#define GL_COLOR_ATTACHMENT12 0x8cec
#define GL_COLOR_ATTACHMENT13 0x8ced
#define GL_COLOR_ATTACHMENT14 0x8cee
#define GL_COLOR_ATTACHMENT15 0x8cef
#define GL_COLOR_ATTACHMENT2 0x8ce2
#define GL_COLOR_ATTACHMENT3 0x8ce3
#define GL_COLOR_ATTACHMENT4 0x8ce4
#define GL_COLOR_ATTACHMENT5 0x8ce5
#define GL_COLOR_ATTACHMENT6 0x8ce6
#define GL_COLOR_ATTACHMENT7 0x8ce7
#define GL_COLOR_ATTACHMENT8 0x8ce8
#define GL_COLOR_ATTACHMENT9 0x8ce9
#define GL_DEPTH24_STENCIL8 0x88f0
#define GL_DEPTH_ATTACHMENT 0x8d00
#define GL_DEPTH_STENCIL 0x84f9
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821a
#define GL_DRAW_FRAMEBUFFER 0x8ca9
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8ca6
#define GL_FRAMEBUFFER 0x8d40
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8cd1
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8cd0
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8cd3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8cd4
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8cd2
#define GL_FRAMEBUFFER_BINDING 0x8ca6
#define GL_FRAMEBUFFER_COMPLETE 0x8cd5
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8cd6
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8cdb
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8cd7
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8d56
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8cdc
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8cdd
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x506
#define GL_MAX_COLOR_ATTACHMENTS 0x8cdf
#define GL_MAX_RENDERBUFFER_SIZE 0x84e8
#define GL_MAX_SAMPLES 0x8d57
#define GL_READ_FRAMEBUFFER 0x8ca8
#define GL_READ_FRAMEBUFFER_BINDING 0x8caa
#define GL_RENDERBUFFER 0x8d41
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8d53
#define GL_RENDERBUFFER_BINDING 0x8ca7
#define GL_RENDERBUFFER_BLUE_SIZE 0x8d52
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8d54
#define GL_RENDERBUFFER_GREEN_SIZE 0x8d51
#define GL_RENDERBUFFER_HEIGHT 0x8d43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8d44
#define GL_RENDERBUFFER_RED_SIZE 0x8d50
#define GL_RENDERBUFFER_SAMPLES 0x8cab
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8d55
#define GL_RENDERBUFFER_WIDTH 0x8d42
#define GL_STENCIL_ATTACHMENT 0x8d20
#define GL_STENCIL_INDEX1 0x8d46
#define GL_STENCIL_INDEX16 0x8d49
#define GL_STENCIL_INDEX4 0x8d47
#define GL_STENCIL_INDEX8 0x8d48
#define GL_TEXTURE_STENCIL_SIZE 0x88f1
#define GL_UNSIGNED_INT_24_8 0x84fa
#define GL_UNSIGNED_NORMALIZED 0x8c17

#define glBindFramebuffer _glplatform_glBindFramebuffer
extern void (*glBindFramebuffer)(GLenum, GLuint);
#define glBindRenderbuffer _glplatform_glBindRenderbuffer
extern void (*glBindRenderbuffer)(GLenum, GLuint);
#define glBlitFramebuffer _glplatform_glBlitFramebuffer
extern void (*glBlitFramebuffer)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
#define glCheckFramebufferStatus _glplatform_glCheckFramebufferStatus
extern GLenum (*glCheckFramebufferStatus)(GLenum);
#define glDeleteFramebuffers _glplatform_glDeleteFramebuffers
extern void (*glDeleteFramebuffers)(GLsizei, const GLuint *);
#define glDeleteRenderbuffers _glplatform_glDeleteRenderbuffers
extern void (*glDeleteRenderbuffers)(GLsizei, const GLuint *);
#define glFramebufferRenderbuffer _glplatform_glFramebufferRenderbuffer
extern void (*glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint);
#define glFramebufferTexture1D _glplatform_glFramebufferTexture1D
extern void (*glFramebufferTexture1D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture2D _glplatform_glFramebufferTexture2D
extern void (*glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
#define glFramebufferTexture3D _glplatform_glFramebufferTexture3D
extern void (*glFramebufferTexture3D)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
#define glFramebufferTextureLayer _glplatform_glFramebufferTextureLayer
extern void (*glFramebufferTextureLayer)(GLenum, GLenum, GLuint, GLint, GLint);
#define glGenFramebuffers _glplatform_glGenFramebuffers
extern void (*glGenFramebuffers)(GLsizei, GLuint *);
#define glGenRenderbuffers _glplatform_glGenRenderbuffers
extern void (*glGenRenderbuffers)(GLsizei, GLuint *);
#define glGenerateMipmap _glplatform_glGenerateMipmap
extern void (*glGenerateMipmap)(GLenum);
#define glGetFramebufferAttachmentParameteriv _glplatform_glGetFramebufferAttachmentParameteriv
extern void (*glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *);
#define glGetRenderbufferParameteriv _glplatform_glGetRenderbufferParameteriv
extern void (*glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *);
#define glIsFramebuffer _glplatform_glIsFramebuffer
extern GLboolean (*glIsFramebuffer)(GLuint);
#define glIsRenderbuffer _glplatform_glIsRenderbuffer
extern GLboolean (*glIsRenderbuffer)(GLuint);
#define glRenderbufferStorage _glplatform_glRenderbufferStorage
extern void (*glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei);
#define glRenderbufferStorageMultisample _glplatform_glRenderbufferStorageMultisample
extern void (*glRenderbufferStorageMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_framebuffer_sRGB)
extern bool GLPLATFORM_GL_ARB_framebuffer_sRGB;

#define GL_FRAMEBUFFER_SRGB 0x8db9

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_get_program_binary)
extern bool GLPLATFORM_GL_ARB_get_program_binary;

#define GL_NUM_PROGRAM_BINARY_FORMATS 0x87fe
#define GL_PROGRAM_BINARY_FORMATS 0x87ff
#define GL_PROGRAM_BINARY_LENGTH 0x8741
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257

#define glGetProgramBinary _glplatform_glGetProgramBinary
extern void (*glGetProgramBinary)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
#define glProgramBinary _glplatform_glProgramBinary
extern void (*glProgramBinary)(GLuint, GLenum, const void *, GLsizei);
#define glProgramParameteri _glplatform_glProgramParameteri
extern void (*glProgramParameteri)(GLuint, GLenum, GLint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_get_texture_sub_image)
extern bool GLPLATFORM_GL_ARB_get_texture_sub_image;


#define glGetCompressedTextureSubImage _glplatform_glGetCompressedTextureSubImage
extern void (*glGetCompressedTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
#define glGetTextureSubImage _glplatform_glGetTextureSubImage
extern void (*glGetTextureSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_gpu_shader5)
extern bool GLPLATFORM_GL_ARB_gpu_shader5;

#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8e5d
#define GL_GEOMETRY_SHADER_INVOCATIONS 0x887f
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8e5c
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8e5a
#define GL_MAX_VERTEX_STREAMS 0x8e71
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8e5b

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_gpu_shader_fp64)
extern bool GLPLATFORM_GL_ARB_gpu_shader_fp64;

#define GL_DOUBLE 0x140a
#define GL_DOUBLE_MAT2 0x8f46
#define GL_DOUBLE_MAT2x3 0x8f49
#define GL_DOUBLE_MAT2x4 0x8f4a
#define GL_DOUBLE_MAT3 0x8f47
#define GL_DOUBLE_MAT3x2 0x8f4b
#define GL_DOUBLE_MAT3x4 0x8f4c
#define GL_DOUBLE_MAT4 0x8f48
#define GL_DOUBLE_MAT4x2 0x8f4d
#define GL_DOUBLE_MAT4x3 0x8f4e
#define GL_DOUBLE_VEC2 0x8ffc
#define GL_DOUBLE_VEC3 0x8ffd
#define GL_DOUBLE_VEC4 0x8ffe

#define glGetUniformdv _glplatform_glGetUniformdv
extern void (*glGetUniformdv)(GLuint, GLint, GLdouble *);
#define glUniform1d _glplatform_glUniform1d
extern void (*glUniform1d)(GLint, GLdouble);
#define glUniform1dv _glplatform_glUniform1dv
extern void (*glUniform1dv)(GLint, GLsizei, const GLdouble *);
#define glUniform2d _glplatform_glUniform2d
extern void (*glUniform2d)(GLint, GLdouble, GLdouble);
#define glUniform2dv _glplatform_glUniform2dv
extern void (*glUniform2dv)(GLint, GLsizei, const GLdouble *);
#define glUniform3d _glplatform_glUniform3d
extern void (*glUniform3d)(GLint, GLdouble, GLdouble, GLdouble);
#define glUniform3dv _glplatform_glUniform3dv
extern void (*glUniform3dv)(GLint, GLsizei, const GLdouble *);
#define glUniform4d _glplatform_glUniform4d
extern void (*glUniform4d)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glUniform4dv _glplatform_glUniform4dv
extern void (*glUniform4dv)(GLint, GLsizei, const GLdouble *);
#define glUniformMatrix2dv _glplatform_glUniformMatrix2dv
extern void (*glUniformMatrix2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x3dv _glplatform_glUniformMatrix2x3dv
extern void (*glUniformMatrix2x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix2x4dv _glplatform_glUniformMatrix2x4dv
extern void (*glUniformMatrix2x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3dv _glplatform_glUniformMatrix3dv
extern void (*glUniformMatrix3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x2dv _glplatform_glUniformMatrix3x2dv
extern void (*glUniformMatrix3x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix3x4dv _glplatform_glUniformMatrix3x4dv
extern void (*glUniformMatrix3x4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4dv _glplatform_glUniformMatrix4dv
extern void (*glUniformMatrix4dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x2dv _glplatform_glUniformMatrix4x2dv
extern void (*glUniformMatrix4x2dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#define glUniformMatrix4x3dv _glplatform_glUniformMatrix4x3dv
extern void (*glUniformMatrix4x3dv)(GLint, GLsizei, GLboolean, const GLdouble *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_half_float_vertex)
extern bool GLPLATFORM_GL_ARB_half_float_vertex;

#define GL_HALF_FLOAT 0x140b

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_imaging)
extern bool GLPLATFORM_GL_ARB_imaging;

#define GL_BLEND_COLOR 0x8005
#define GL_BLEND_EQUATION 0x8009
#define GL_CONSTANT_ALPHA 0x8003
#define GL_CONSTANT_COLOR 0x8001
#define GL_FUNC_ADD 0x8006
#define GL_FUNC_REVERSE_SUBTRACT 0x800b
#define GL_FUNC_SUBTRACT 0x800a
#define GL_MAX 0x8008
#define GL_MIN 0x8007
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002

#define glBlendColor _glplatform_glBlendColor
extern void (*glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat);
#define glBlendEquation _glplatform_glBlendEquation
extern void (*glBlendEquation)(GLenum);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_indirect_parameters)
extern bool GLPLATFORM_GL_ARB_indirect_parameters;

#define GL_PARAMETER_BUFFER_ARB 0x80ee
#define GL_PARAMETER_BUFFER_BINDING_ARB 0x80ef

#define glMultiDrawArraysIndirectCountARB _glplatform_glMultiDrawArraysIndirectCountARB
extern void (*glMultiDrawArraysIndirectCountARB)(GLenum, GLintptr, GLintptr, GLsizei, GLsizei);
#define glMultiDrawElementsIndirectCountARB _glplatform_glMultiDrawElementsIndirectCountARB
extern void (*glMultiDrawElementsIndirectCountARB)(GLenum, GLenum, GLintptr, GLintptr, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_internalformat_query)
extern bool GLPLATFORM_GL_ARB_internalformat_query;

#define GL_NUM_SAMPLE_COUNTS 0x9380

#define glGetInternalformativ _glplatform_glGetInternalformativ
extern void (*glGetInternalformativ)(GLenum, GLenum, GLenum, GLsizei, GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_internalformat_query2)
extern bool GLPLATFORM_GL_ARB_internalformat_query2;
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif

#define GL_AUTO_GENERATE_MIPMAP 0x8295
#define GL_CAVEAT_SUPPORT 0x82b8
#define GL_CLEAR_BUFFER 0x82b4
#define GL_COLOR_COMPONENTS 0x8283
#define GL_COLOR_ENCODING 0x8296
#define GL_COLOR_RENDERABLE 0x8286
#define GL_COMPUTE_TEXTURE 0x82a0
#define GL_DEPTH_COMPONENTS 0x8284
#define GL_DEPTH_RENDERABLE 0x8287
#define GL_FILTER 0x829a
#define GL_FRAGMENT_TEXTURE 0x829f
#define GL_FRAMEBUFFER_BLEND 0x828b
#define GL_FRAMEBUFFER_RENDERABLE 0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828a
#define GL_FULL_SUPPORT 0x82b7
#define GL_GEOMETRY_TEXTURE 0x829e
#define GL_GET_TEXTURE_IMAGE_FORMAT 0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE 0x8292
#define GL_IMAGE_CLASS_10_10_10_2 0x82c3
#define GL_IMAGE_CLASS_11_11_10 0x82c2
#define GL_IMAGE_CLASS_1_X_16 0x82be
#define GL_IMAGE_CLASS_1_X_32 0x82bb
#define GL_IMAGE_CLASS_1_X_8 0x82c1
#define GL_IMAGE_CLASS_2_X_16 0x82bd
#define GL_IMAGE_CLASS_2_X_32 0x82ba
#define GL_IMAGE_CLASS_2_X_8 0x82c0
#define GL_IMAGE_CLASS_4_X_16 0x82bc
#define GL_IMAGE_CLASS_4_X_32 0x82b9
#define GL_IMAGE_CLASS_4_X_8 0x82bf
#define GL_IMAGE_COMPATIBILITY_CLASS 0x82a8
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90c7
#define GL_IMAGE_PIXEL_FORMAT 0x82a9
#define GL_IMAGE_PIXEL_TYPE 0x82aa
#define GL_IMAGE_TEXEL_SIZE 0x82a7
#define GL_INTERNALFORMAT_ALPHA_SIZE 0x8274
#define GL_INTERNALFORMAT_ALPHA_TYPE 0x827b
#define GL_INTERNALFORMAT_BLUE_SIZE 0x8273
#define GL_INTERNALFORMAT_BLUE_TYPE 0x827a
#define GL_INTERNALFORMAT_DEPTH_SIZE 0x8275
#define GL_INTERNALFORMAT_DEPTH_TYPE 0x827c
#define GL_INTERNALFORMAT_GREEN_SIZE 0x8272
#define GL_INTERNALFORMAT_GREEN_TYPE 0x8279
#define GL_INTERNALFORMAT_PREFERRED 0x8270
#define GL_INTERNALFORMAT_RED_SIZE 0x8271
#define GL_INTERNALFORMAT_RED_TYPE 0x8278
#define GL_INTERNALFORMAT_SHARED_SIZE 0x8277
#define GL_INTERNALFORMAT_STENCIL_SIZE 0x8276
#define GL_INTERNALFORMAT_STENCIL_TYPE 0x827d
#define GL_INTERNALFORMAT_SUPPORTED 0x826f
#define GL_MANUAL_GENERATE_MIPMAP 0x8294
#define GL_MAX_COMBINED_DIMENSIONS 0x8282
#define GL_MAX_DEPTH 0x8280
#define GL_MAX_HEIGHT 0x827f
#define GL_MAX_LAYERS 0x8281
#define GL_MAX_WIDTH 0x827e
#define GL_MIPMAP 0x8293
#define GL_NUM_SAMPLE_COUNTS 0x9380
#define GL_READ_PIXELS 0x828c
#define GL_READ_PIXELS_FORMAT 0x828d
#define GL_READ_PIXELS_TYPE 0x828e
#define GL_RENDERBUFFER 0x8d41
#define GL_SAMPLES 0x80a9
#define GL_SHADER_IMAGE_ATOMIC 0x82a6
#define GL_SHADER_IMAGE_LOAD 0x82a4
#define GL_SHADER_IMAGE_STORE 0x82a5
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82ac
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82ae
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82ad
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82af
#define GL_SRGB_DECODE_ARB 0x8299
#define GL_SRGB_READ 0x8297
#define GL_SRGB_WRITE 0x8298
#define GL_STENCIL_COMPONENTS 0x8285
#define GL_STENCIL_RENDERABLE 0x8288
#define GL_TESS_CONTROL_TEXTURE 0x829c
#define GL_TESS_EVALUATION_TEXTURE 0x829d
#define GL_TEXTURE_1D 0xde0
#define GL_TEXTURE_1D_ARRAY 0x8c18
#define GL_TEXTURE_2D 0xde1
#define GL_TEXTURE_2D_ARRAY 0x8c1a
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_TEXTURE_3D 0x806f
#define GL_TEXTURE_BUFFER 0x8c2a
#define GL_TEXTURE_COMPRESSED 0x86a1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82b2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE 0x82b3
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82b1
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#define GL_TEXTURE_GATHER 0x82a2
#define GL_TEXTURE_GATHER_SHADOW 0x82a3
#define GL_TEXTURE_IMAGE_FORMAT 0x828f
#define GL_TEXTURE_IMAGE_TYPE 0x8290
#define GL_TEXTURE_RECTANGLE 0x84f5
#define GL_TEXTURE_SHADOW 0x82a1
#define GL_TEXTURE_VIEW 0x82b5
#define GL_VERTEX_TEXTURE 0x829b
#define GL_VIEW_CLASS_128_BITS 0x82c4
#define GL_VIEW_CLASS_16_BITS 0x82ca
#define GL_VIEW_CLASS_24_BITS 0x82c9
#define GL_VIEW_CLASS_32_BITS 0x82c8
#define GL_VIEW_CLASS_48_BITS 0x82c7
#define GL_VIEW_CLASS_64_BITS 0x82c6
#define GL_VIEW_CLASS_8_BITS 0x82cb
#define GL_VIEW_CLASS_96_BITS 0x82c5
#define GL_VIEW_CLASS_BPTC_FLOAT 0x82d3
#define GL_VIEW_CLASS_BPTC_UNORM 0x82d2
#define GL_VIEW_CLASS_RGTC1_RED 0x82d0
#define GL_VIEW_CLASS_RGTC2_RG 0x82d1
#define GL_VIEW_CLASS_S3TC_DXT1_RGB 0x82cc
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA 0x82cd
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA 0x82ce
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA 0x82cf
#define GL_VIEW_COMPATIBILITY_CLASS 0x82b6

#define glGetInternalformati64v _glplatform_glGetInternalformati64v
extern void (*glGetInternalformati64v)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_invalidate_subdata)
extern bool GLPLATFORM_GL_ARB_invalidate_subdata;


#define glInvalidateBufferData _glplatform_glInvalidateBufferData
extern void (*glInvalidateBufferData)(GLuint);
#define glInvalidateBufferSubData _glplatform_glInvalidateBufferSubData
extern void (*glInvalidateBufferSubData)(GLuint, GLintptr, GLsizeiptr);
#define glInvalidateFramebuffer _glplatform_glInvalidateFramebuffer
extern void (*glInvalidateFramebuffer)(GLenum, GLsizei, const GLenum *);
#define glInvalidateSubFramebuffer _glplatform_glInvalidateSubFramebuffer
extern void (*glInvalidateSubFramebuffer)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
#define glInvalidateTexImage _glplatform_glInvalidateTexImage
extern void (*glInvalidateTexImage)(GLuint, GLint);
#define glInvalidateTexSubImage _glplatform_glInvalidateTexSubImage
extern void (*glInvalidateTexSubImage)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_map_buffer_alignment)
extern bool GLPLATFORM_GL_ARB_map_buffer_alignment;

#define GL_MIN_MAP_BUFFER_ALIGNMENT 0x90bc

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_map_buffer_range)
extern bool GLPLATFORM_GL_ARB_map_buffer_range;

#define GL_MAP_FLUSH_EXPLICIT_BIT 0x10
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x8
#define GL_MAP_INVALIDATE_RANGE_BIT 0x4
#define GL_MAP_READ_BIT 0x1
#define GL_MAP_UNSYNCHRONIZED_BIT 0x20
#define GL_MAP_WRITE_BIT 0x2

#define glFlushMappedBufferRange _glplatform_glFlushMappedBufferRange
extern void (*glFlushMappedBufferRange)(GLenum, GLintptr, GLsizeiptr);
#define glMapBufferRange _glplatform_glMapBufferRange
extern void * (*glMapBufferRange)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_multi_bind)
extern bool GLPLATFORM_GL_ARB_multi_bind;


#define glBindBuffersBase _glplatform_glBindBuffersBase
extern void (*glBindBuffersBase)(GLenum, GLuint, GLsizei, const GLuint *);
#define glBindBuffersRange _glplatform_glBindBuffersRange
extern void (*glBindBuffersRange)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
#define glBindImageTextures _glplatform_glBindImageTextures
extern void (*glBindImageTextures)(GLuint, GLsizei, const GLuint *);
#define glBindSamplers _glplatform_glBindSamplers
extern void (*glBindSamplers)(GLuint, GLsizei, const GLuint *);
#define glBindTextures _glplatform_glBindTextures
extern void (*glBindTextures)(GLuint, GLsizei, const GLuint *);
#define glBindVertexBuffers _glplatform_glBindVertexBuffers
extern void (*glBindVertexBuffers)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_multi_draw_indirect)
extern bool GLPLATFORM_GL_ARB_multi_draw_indirect;


#define glMultiDrawArraysIndirect _glplatform_glMultiDrawArraysIndirect
extern void (*glMultiDrawArraysIndirect)(GLenum, const void *, GLsizei, GLsizei);
#define glMultiDrawElementsIndirect _glplatform_glMultiDrawElementsIndirect
extern void (*glMultiDrawElementsIndirect)(GLenum, GLenum, const void *, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_occlusion_query2)
extern bool GLPLATFORM_GL_ARB_occlusion_query2;

#define GL_ANY_SAMPLES_PASSED 0x8c2f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_pipeline_statistics_query)
extern bool GLPLATFORM_GL_ARB_pipeline_statistics_query;

#define GL_CLIPPING_INPUT_PRIMITIVES_ARB 0x82f6
#define GL_CLIPPING_OUTPUT_PRIMITIVES_ARB 0x82f7
#define GL_COMPUTE_SHADER_INVOCATIONS_ARB 0x82f5
#define GL_FRAGMENT_SHADER_INVOCATIONS_ARB 0x82f4
#define GL_GEOMETRY_SHADER_INVOCATIONS 0x887f
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB 0x82f3
#define GL_PRIMITIVES_SUBMITTED_ARB 0x82ef
#define GL_TESS_CONTROL_SHADER_PATCHES_ARB 0x82f1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB 0x82f2
#define GL_VERTEX_SHADER_INVOCATIONS_ARB 0x82f0
#define GL_VERTICES_SUBMITTED_ARB 0x82ee

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_program_interface_query)
extern bool GLPLATFORM_GL_ARB_program_interface_query;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_RESOURCES 0x92f5
#define GL_ACTIVE_VARIABLES 0x9305
#define GL_ARRAY_SIZE 0x92fb
#define GL_ARRAY_STRIDE 0x92fe
#define GL_ATOMIC_COUNTER_BUFFER 0x92c0
#define GL_ATOMIC_COUNTER_BUFFER_INDEX 0x9301
#define GL_BLOCK_INDEX 0x92fd
#define GL_BUFFER_BINDING 0x9302
#define GL_BUFFER_DATA_SIZE 0x9303
#define GL_BUFFER_VARIABLE 0x92e5
#define GL_COMPATIBLE_SUBROUTINES 0x8e4b
#define GL_COMPUTE_SUBROUTINE 0x92ed
#define GL_COMPUTE_SUBROUTINE_UNIFORM 0x92f3
#define GL_FRAGMENT_SUBROUTINE 0x92ec
#define GL_FRAGMENT_SUBROUTINE_UNIFORM 0x92f2
#define GL_GEOMETRY_SUBROUTINE 0x92eb
#define GL_GEOMETRY_SUBROUTINE_UNIFORM 0x92f1
#define GL_IS_PER_PATCH 0x92e7
#define GL_IS_ROW_MAJOR 0x9300
#define GL_LOCATION 0x930e
#define GL_LOCATION_INDEX 0x930f
#define GL_MATRIX_STRIDE 0x92ff
#define GL_MAX_NAME_LENGTH 0x92f6
#define GL_MAX_NUM_ACTIVE_VARIABLES 0x92f7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92f8
#define GL_NAME_LENGTH 0x92f9
#define GL_NUM_ACTIVE_VARIABLES 0x9304
#define GL_NUM_COMPATIBLE_SUBROUTINES 0x8e4a
#define GL_OFFSET 0x92fc
#define GL_PROGRAM_INPUT 0x92e3
#define GL_PROGRAM_OUTPUT 0x92e4
#define GL_REFERENCED_BY_COMPUTE_SHADER 0x930b
#define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930a
#define GL_REFERENCED_BY_GEOMETRY_SHADER 0x9309
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_VERTEX_SHADER 0x9306
#define GL_SHADER_STORAGE_BLOCK 0x92e6
#define GL_TESS_CONTROL_SUBROUTINE 0x92e9
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92ef
#define GL_TESS_EVALUATION_SUBROUTINE 0x92ea
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92f0
#define GL_TOP_LEVEL_ARRAY_SIZE 0x930c
#define GL_TOP_LEVEL_ARRAY_STRIDE 0x930d
#define GL_TRANSFORM_FEEDBACK_VARYING 0x92f4
#define GL_TYPE 0x92fa
#define GL_UNIFORM 0x92e1
#define GL_UNIFORM_BLOCK 0x92e2
#define GL_VERTEX_SUBROUTINE 0x92e8
#define GL_VERTEX_SUBROUTINE_UNIFORM 0x92ee

#define glGetProgramInterfaceiv _glplatform_glGetProgramInterfaceiv
extern void (*glGetProgramInterfaceiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetProgramResourceIndex _glplatform_glGetProgramResourceIndex
extern GLuint (*glGetProgramResourceIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocation _glplatform_glGetProgramResourceLocation
extern GLint (*glGetProgramResourceLocation)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceLocationIndex _glplatform_glGetProgramResourceLocationIndex
extern GLint (*glGetProgramResourceLocationIndex)(GLuint, GLenum, const GLchar *);
#define glGetProgramResourceName _glplatform_glGetProgramResourceName
extern void (*glGetProgramResourceName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramResourceiv _glplatform_glGetProgramResourceiv
extern void (*glGetProgramResourceiv)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_provoking_vertex)
extern bool GLPLATFORM_GL_ARB_provoking_vertex;

#define GL_FIRST_VERTEX_CONVENTION 0x8e4d
#define GL_LAST_VERTEX_CONVENTION 0x8e4e
#define GL_PROVOKING_VERTEX 0x8e4f
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8e4c

#define glProvokingVertex _glplatform_glProvokingVertex
extern void (*glProvokingVertex)(GLenum);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_query_buffer_object)
extern bool GLPLATFORM_GL_ARB_query_buffer_object;

#define GL_QUERY_BUFFER 0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT 0x8000
#define GL_QUERY_BUFFER_BINDING 0x9193
#define GL_QUERY_RESULT_NO_WAIT 0x9194

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_robust_buffer_access_behavior)
extern bool GLPLATFORM_GL_ARB_robust_buffer_access_behavior;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_robustness)
extern bool GLPLATFORM_GL_ARB_robustness;

#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB 0x4
#define GL_GUILTY_CONTEXT_RESET_ARB 0x8253
#define GL_INNOCENT_CONTEXT_RESET_ARB 0x8254
#define GL_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define GL_NO_ERROR 0x0
#define GL_NO_RESET_NOTIFICATION_ARB 0x8261
#define GL_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GL_UNKNOWN_CONTEXT_RESET_ARB 0x8255

#define glGetGraphicsResetStatusARB _glplatform_glGetGraphicsResetStatusARB
extern GLenum (*glGetGraphicsResetStatusARB)();
#define glGetnCompressedTexImageARB _glplatform_glGetnCompressedTexImageARB
extern void (*glGetnCompressedTexImageARB)(GLenum, GLint, GLsizei, void *);
#define glGetnTexImageARB _glplatform_glGetnTexImageARB
extern void (*glGetnTexImageARB)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
#define glGetnUniformdvARB _glplatform_glGetnUniformdvARB
extern void (*glGetnUniformdvARB)(GLuint, GLint, GLsizei, GLdouble *);
#define glGetnUniformfvARB _glplatform_glGetnUniformfvARB
extern void (*glGetnUniformfvARB)(GLuint, GLint, GLsizei, GLfloat *);
#define glGetnUniformivARB _glplatform_glGetnUniformivARB
extern void (*glGetnUniformivARB)(GLuint, GLint, GLsizei, GLint *);
#define glGetnUniformuivARB _glplatform_glGetnUniformuivARB
extern void (*glGetnUniformuivARB)(GLuint, GLint, GLsizei, GLuint *);
#define glReadnPixelsARB _glplatform_glReadnPixelsARB
extern void (*glReadnPixelsARB)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_robustness_isolation)
extern bool GLPLATFORM_GL_ARB_robustness_isolation;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_sample_shading)
extern bool GLPLATFORM_GL_ARB_sample_shading;

#define GL_MIN_SAMPLE_SHADING_VALUE_ARB 0x8c37
#define GL_SAMPLE_SHADING_ARB 0x8c36

#define glMinSampleShadingARB _glplatform_glMinSampleShadingARB
extern void (*glMinSampleShadingARB)(GLfloat);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_sampler_objects)
extern bool GLPLATFORM_GL_ARB_sampler_objects;

#define GL_SAMPLER_BINDING 0x8919

#define glBindSampler _glplatform_glBindSampler
extern void (*glBindSampler)(GLuint, GLuint);
#define glDeleteSamplers _glplatform_glDeleteSamplers
extern void (*glDeleteSamplers)(GLsizei, const GLuint *);
#define glGenSamplers _glplatform_glGenSamplers
extern void (*glGenSamplers)(GLsizei, GLuint *);
#define glGetSamplerParameterIiv _glplatform_glGetSamplerParameterIiv
extern void (*glGetSamplerParameterIiv)(GLuint, GLenum, GLint *);
#define glGetSamplerParameterIuiv _glplatform_glGetSamplerParameterIuiv
extern void (*glGetSamplerParameterIuiv)(GLuint, GLenum, GLuint *);
#define glGetSamplerParameterfv _glplatform_glGetSamplerParameterfv
extern void (*glGetSamplerParameterfv)(GLuint, GLenum, GLfloat *);
#define glGetSamplerParameteriv _glplatform_glGetSamplerParameteriv
extern void (*glGetSamplerParameteriv)(GLuint, GLenum, GLint *);
#define glIsSampler _glplatform_glIsSampler
extern GLboolean (*glIsSampler)(GLuint);
#define glSamplerParameterIiv _glplatform_glSamplerParameterIiv
extern void (*glSamplerParameterIiv)(GLuint, GLenum, const GLint *);
#define glSamplerParameterIuiv _glplatform_glSamplerParameterIuiv
extern void (*glSamplerParameterIuiv)(GLuint, GLenum, const GLuint *);
#define glSamplerParameterf _glplatform_glSamplerParameterf
extern void (*glSamplerParameterf)(GLuint, GLenum, GLfloat);
#define glSamplerParameterfv _glplatform_glSamplerParameterfv
extern void (*glSamplerParameterfv)(GLuint, GLenum, const GLfloat *);
#define glSamplerParameteri _glplatform_glSamplerParameteri
extern void (*glSamplerParameteri)(GLuint, GLenum, GLint);
#define glSamplerParameteriv _glplatform_glSamplerParameteriv
extern void (*glSamplerParameteriv)(GLuint, GLenum, const GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_seamless_cube_map)
extern bool GLPLATFORM_GL_ARB_seamless_cube_map;

#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_seamless_cubemap_per_texture)
extern bool GLPLATFORM_GL_ARB_seamless_cubemap_per_texture;

#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_separate_shader_objects)
extern bool GLPLATFORM_GL_ARB_separate_shader_objects;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_PROGRAM 0x8259
#define GL_ALL_SHADER_BITS 0xffffffff
#define GL_FRAGMENT_SHADER_BIT 0x2
#define GL_GEOMETRY_SHADER_BIT 0x4
#define GL_PROGRAM_PIPELINE_BINDING 0x825a
#define GL_PROGRAM_SEPARABLE 0x8258
#define GL_TESS_CONTROL_SHADER_BIT 0x8
#define GL_TESS_EVALUATION_SHADER_BIT 0x10
#define GL_VERTEX_SHADER_BIT 0x1

#define glActiveShaderProgram _glplatform_glActiveShaderProgram
extern void (*glActiveShaderProgram)(GLuint, GLuint);
#define glBindProgramPipeline _glplatform_glBindProgramPipeline
extern void (*glBindProgramPipeline)(GLuint);
#define glCreateShaderProgramv _glplatform_glCreateShaderProgramv
extern GLuint (*glCreateShaderProgramv)(GLenum, GLsizei, const GLchar *const*);
#define glDeleteProgramPipelines _glplatform_glDeleteProgramPipelines
extern void (*glDeleteProgramPipelines)(GLsizei, const GLuint *);
#define glGenProgramPipelines _glplatform_glGenProgramPipelines
extern void (*glGenProgramPipelines)(GLsizei, GLuint *);
#define glGetProgramPipelineInfoLog _glplatform_glGetProgramPipelineInfoLog
extern void (*glGetProgramPipelineInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetProgramPipelineiv _glplatform_glGetProgramPipelineiv
extern void (*glGetProgramPipelineiv)(GLuint, GLenum, GLint *);
#define glIsProgramPipeline _glplatform_glIsProgramPipeline
extern GLboolean (*glIsProgramPipeline)(GLuint);
#define glProgramUniform1d _glplatform_glProgramUniform1d
extern void (*glProgramUniform1d)(GLuint, GLint, GLdouble);
#define glProgramUniform1dv _glplatform_glProgramUniform1dv
extern void (*glProgramUniform1dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform1f _glplatform_glProgramUniform1f
extern void (*glProgramUniform1f)(GLuint, GLint, GLfloat);
#define glProgramUniform1fv _glplatform_glProgramUniform1fv
extern void (*glProgramUniform1fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform1i _glplatform_glProgramUniform1i
extern void (*glProgramUniform1i)(GLuint, GLint, GLint);
#define glProgramUniform1iv _glplatform_glProgramUniform1iv
extern void (*glProgramUniform1iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform1ui _glplatform_glProgramUniform1ui
extern void (*glProgramUniform1ui)(GLuint, GLint, GLuint);
#define glProgramUniform1uiv _glplatform_glProgramUniform1uiv
extern void (*glProgramUniform1uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform2d _glplatform_glProgramUniform2d
extern void (*glProgramUniform2d)(GLuint, GLint, GLdouble, GLdouble);
#define glProgramUniform2dv _glplatform_glProgramUniform2dv
extern void (*glProgramUniform2dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform2f _glplatform_glProgramUniform2f
extern void (*glProgramUniform2f)(GLuint, GLint, GLfloat, GLfloat);
#define glProgramUniform2fv _glplatform_glProgramUniform2fv
extern void (*glProgramUniform2fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform2i _glplatform_glProgramUniform2i
extern void (*glProgramUniform2i)(GLuint, GLint, GLint, GLint);
#define glProgramUniform2iv _glplatform_glProgramUniform2iv
extern void (*glProgramUniform2iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform2ui _glplatform_glProgramUniform2ui
extern void (*glProgramUniform2ui)(GLuint, GLint, GLuint, GLuint);
#define glProgramUniform2uiv _glplatform_glProgramUniform2uiv
extern void (*glProgramUniform2uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform3d _glplatform_glProgramUniform3d
extern void (*glProgramUniform3d)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
#define glProgramUniform3dv _glplatform_glProgramUniform3dv
extern void (*glProgramUniform3dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform3f _glplatform_glProgramUniform3f
extern void (*glProgramUniform3f)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
#define glProgramUniform3fv _glplatform_glProgramUniform3fv
extern void (*glProgramUniform3fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform3i _glplatform_glProgramUniform3i
extern void (*glProgramUniform3i)(GLuint, GLint, GLint, GLint, GLint);
#define glProgramUniform3iv _glplatform_glProgramUniform3iv
extern void (*glProgramUniform3iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform3ui _glplatform_glProgramUniform3ui
extern void (*glProgramUniform3ui)(GLuint, GLint, GLuint, GLuint, GLuint);
#define glProgramUniform3uiv _glplatform_glProgramUniform3uiv
extern void (*glProgramUniform3uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniform4d _glplatform_glProgramUniform4d
extern void (*glProgramUniform4d)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glProgramUniform4dv _glplatform_glProgramUniform4dv
extern void (*glProgramUniform4dv)(GLuint, GLint, GLsizei, const GLdouble *);
#define glProgramUniform4f _glplatform_glProgramUniform4f
extern void (*glProgramUniform4f)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glProgramUniform4fv _glplatform_glProgramUniform4fv
extern void (*glProgramUniform4fv)(GLuint, GLint, GLsizei, const GLfloat *);
#define glProgramUniform4i _glplatform_glProgramUniform4i
extern void (*glProgramUniform4i)(GLuint, GLint, GLint, GLint, GLint, GLint);
#define glProgramUniform4iv _glplatform_glProgramUniform4iv
extern void (*glProgramUniform4iv)(GLuint, GLint, GLsizei, const GLint *);
#define glProgramUniform4ui _glplatform_glProgramUniform4ui
extern void (*glProgramUniform4ui)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
#define glProgramUniform4uiv _glplatform_glProgramUniform4uiv
extern void (*glProgramUniform4uiv)(GLuint, GLint, GLsizei, const GLuint *);
#define glProgramUniformMatrix2dv _glplatform_glProgramUniformMatrix2dv
extern void (*glProgramUniformMatrix2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2fv _glplatform_glProgramUniformMatrix2fv
extern void (*glProgramUniformMatrix2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x3dv _glplatform_glProgramUniformMatrix2x3dv
extern void (*glProgramUniformMatrix2x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x3fv _glplatform_glProgramUniformMatrix2x3fv
extern void (*glProgramUniformMatrix2x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix2x4dv _glplatform_glProgramUniformMatrix2x4dv
extern void (*glProgramUniformMatrix2x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix2x4fv _glplatform_glProgramUniformMatrix2x4fv
extern void (*glProgramUniformMatrix2x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3dv _glplatform_glProgramUniformMatrix3dv
extern void (*glProgramUniformMatrix3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3fv _glplatform_glProgramUniformMatrix3fv
extern void (*glProgramUniformMatrix3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x2dv _glplatform_glProgramUniformMatrix3x2dv
extern void (*glProgramUniformMatrix3x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x2fv _glplatform_glProgramUniformMatrix3x2fv
extern void (*glProgramUniformMatrix3x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix3x4dv _glplatform_glProgramUniformMatrix3x4dv
extern void (*glProgramUniformMatrix3x4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix3x4fv _glplatform_glProgramUniformMatrix3x4fv
extern void (*glProgramUniformMatrix3x4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4dv _glplatform_glProgramUniformMatrix4dv
extern void (*glProgramUniformMatrix4dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4fv _glplatform_glProgramUniformMatrix4fv
extern void (*glProgramUniformMatrix4fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x2dv _glplatform_glProgramUniformMatrix4x2dv
extern void (*glProgramUniformMatrix4x2dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x2fv _glplatform_glProgramUniformMatrix4x2fv
extern void (*glProgramUniformMatrix4x2fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glProgramUniformMatrix4x3dv _glplatform_glProgramUniformMatrix4x3dv
extern void (*glProgramUniformMatrix4x3dv)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
#define glProgramUniformMatrix4x3fv _glplatform_glProgramUniformMatrix4x3fv
extern void (*glProgramUniformMatrix4x3fv)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
#define glUseProgramStages _glplatform_glUseProgramStages
extern void (*glUseProgramStages)(GLuint, GLbitfield, GLuint);
#define glValidateProgramPipeline _glplatform_glValidateProgramPipeline
extern void (*glValidateProgramPipeline)(GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_atomic_counters)
extern bool GLPLATFORM_GL_ARB_shader_atomic_counters;

#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92d9
#define GL_ATOMIC_COUNTER_BUFFER 0x92c0
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92c5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92c6
#define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92c1
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92c4
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92cb
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92ca
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92c8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92c9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92c7
#define GL_ATOMIC_COUNTER_BUFFER_SIZE 0x92c3
#define GL_ATOMIC_COUNTER_BUFFER_START 0x92c2
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92dc
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92d8
#define GL_MAX_COMBINED_ATOMIC_COUNTERS 0x92d7
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92d1
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS 0x92d6
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92d0
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS 0x92d5
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92cf
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92d3
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92cd
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92d4
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92ce
#define GL_MAX_VERTEX_ATOMIC_COUNTERS 0x92d2
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92cc
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92da
#define GL_UNSIGNED_INT_ATOMIC_COUNTER 0x92db

#define glGetActiveAtomicCounterBufferiv _glplatform_glGetActiveAtomicCounterBufferiv
extern void (*glGetActiveAtomicCounterBufferiv)(GLuint, GLuint, GLenum, GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_bit_encoding)
extern bool GLPLATFORM_GL_ARB_shader_bit_encoding;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_draw_parameters)
extern bool GLPLATFORM_GL_ARB_shader_draw_parameters;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_group_vote)
extern bool GLPLATFORM_GL_ARB_shader_group_vote;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_image_load_store)
extern bool GLPLATFORM_GL_ARB_shader_image_load_store;

#define GL_ALL_BARRIER_BITS 0xffffffff
#define GL_ATOMIC_COUNTER_BARRIER_BIT 0x1000
#define GL_BUFFER_UPDATE_BARRIER_BIT 0x200
#define GL_COMMAND_BARRIER_BIT 0x40
#define GL_ELEMENT_ARRAY_BARRIER_BIT 0x2
#define GL_FRAMEBUFFER_BARRIER_BIT 0x400
#define GL_IMAGE_1D 0x904c
#define GL_IMAGE_1D_ARRAY 0x9052
#define GL_IMAGE_2D 0x904d
#define GL_IMAGE_2D_ARRAY 0x9053
#define GL_IMAGE_2D_MULTISAMPLE 0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY 0x9056
#define GL_IMAGE_2D_RECT 0x904f
#define GL_IMAGE_3D 0x904e
#define GL_IMAGE_BINDING_ACCESS 0x8f3e
#define GL_IMAGE_BINDING_FORMAT 0x906e
#define GL_IMAGE_BINDING_LAYER 0x8f3d
#define GL_IMAGE_BINDING_LAYERED 0x8f3c
#define GL_IMAGE_BINDING_LEVEL 0x8f3b
#define GL_IMAGE_BINDING_NAME 0x8f3a
#define GL_IMAGE_BUFFER 0x9051
#define GL_IMAGE_CUBE 0x9050
#define GL_IMAGE_CUBE_MAP_ARRAY 0x9054
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90c9
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90c8
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90c7
#define GL_INT_IMAGE_1D 0x9057
#define GL_INT_IMAGE_1D_ARRAY 0x905d
#define GL_INT_IMAGE_2D 0x9058
#define GL_INT_IMAGE_2D_ARRAY 0x905e
#define GL_INT_IMAGE_2D_MULTISAMPLE 0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_INT_IMAGE_2D_RECT 0x905a
#define GL_INT_IMAGE_3D 0x9059
#define GL_INT_IMAGE_BUFFER 0x905c
#define GL_INT_IMAGE_CUBE 0x905b
#define GL_INT_IMAGE_CUBE_MAP_ARRAY 0x905f
#define GL_MAX_COMBINED_IMAGE_UNIFORMS 0x90cf
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8f39
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS 0x90ce
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS 0x90cd
#define GL_MAX_IMAGE_SAMPLES 0x906d
#define GL_MAX_IMAGE_UNITS 0x8f38
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90cb
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90cc
#define GL_MAX_VERTEX_IMAGE_UNIFORMS 0x90ca
#define GL_PIXEL_BUFFER_BARRIER_BIT 0x80
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x20
#define GL_TEXTURE_FETCH_BARRIER_BIT 0x8
#define GL_TEXTURE_UPDATE_BARRIER_BIT 0x100
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x800
#define GL_UNIFORM_BARRIER_BIT 0x4
#define GL_UNSIGNED_INT_IMAGE_1D 0x9062
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY 0x9068
#define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY 0x9069
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906b
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906c
#define GL_UNSIGNED_INT_IMAGE_2D_RECT 0x9065
#define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#define GL_UNSIGNED_INT_IMAGE_BUFFER 0x9067
#define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906a
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x1

#define glBindImageTexture _glplatform_glBindImageTexture
extern void (*glBindImageTexture)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
#define glMemoryBarrier _glplatform_glMemoryBarrier
extern void (*glMemoryBarrier)(GLbitfield);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_image_size)
extern bool GLPLATFORM_GL_ARB_shader_image_size;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_precision)
extern bool GLPLATFORM_GL_ARB_shader_precision;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_stencil_export)
extern bool GLPLATFORM_GL_ARB_shader_stencil_export;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_storage_buffer_object)
extern bool GLPLATFORM_GL_ARB_shader_storage_buffer_object;

#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8f39
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8f39
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90dc
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90db
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90da
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90d7
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE 0x90de
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90dd
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90d8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90d9
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90d6
#define GL_SHADER_STORAGE_BARRIER_BIT 0x2000
#define GL_SHADER_STORAGE_BUFFER 0x90d2
#define GL_SHADER_STORAGE_BUFFER_BINDING 0x90d3
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90df
#define GL_SHADER_STORAGE_BUFFER_SIZE 0x90d5
#define GL_SHADER_STORAGE_BUFFER_START 0x90d4

#define glShaderStorageBlockBinding _glplatform_glShaderStorageBlockBinding
extern void (*glShaderStorageBlockBinding)(GLuint, GLuint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_subroutine)
extern bool GLPLATFORM_GL_ARB_shader_subroutine;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_SUBROUTINES 0x8de5
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH 0x8e48
#define GL_ACTIVE_SUBROUTINE_UNIFORMS 0x8de6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8e47
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8e49
#define GL_COMPATIBLE_SUBROUTINES 0x8e4b
#define GL_MAX_SUBROUTINES 0x8de7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8de8
#define GL_NUM_COMPATIBLE_SUBROUTINES 0x8e4a
#define GL_UNIFORM_NAME_LENGTH 0x8a39
#define GL_UNIFORM_SIZE 0x8a38

#define glGetActiveSubroutineName _glplatform_glGetActiveSubroutineName
extern void (*glGetActiveSubroutineName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineUniformName _glplatform_glGetActiveSubroutineUniformName
extern void (*glGetActiveSubroutineUniformName)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveSubroutineUniformiv _glplatform_glGetActiveSubroutineUniformiv
extern void (*glGetActiveSubroutineUniformiv)(GLuint, GLenum, GLuint, GLenum, GLint *);
#define glGetProgramStageiv _glplatform_glGetProgramStageiv
extern void (*glGetProgramStageiv)(GLuint, GLenum, GLenum, GLint *);
#define glGetSubroutineIndex _glplatform_glGetSubroutineIndex
extern GLuint (*glGetSubroutineIndex)(GLuint, GLenum, const GLchar *);
#define glGetSubroutineUniformLocation _glplatform_glGetSubroutineUniformLocation
extern GLint (*glGetSubroutineUniformLocation)(GLuint, GLenum, const GLchar *);
#define glGetUniformSubroutineuiv _glplatform_glGetUniformSubroutineuiv
extern void (*glGetUniformSubroutineuiv)(GLenum, GLint, GLuint *);
#define glUniformSubroutinesuiv _glplatform_glUniformSubroutinesuiv
extern void (*glUniformSubroutinesuiv)(GLenum, GLsizei, const GLuint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shader_texture_image_samples)
extern bool GLPLATFORM_GL_ARB_shader_texture_image_samples;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shading_language_420pack)
extern bool GLPLATFORM_GL_ARB_shading_language_420pack;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shading_language_include)
extern bool GLPLATFORM_GL_ARB_shading_language_include;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_NAMED_STRING_LENGTH_ARB 0x8de9
#define GL_NAMED_STRING_TYPE_ARB 0x8dea
#define GL_SHADER_INCLUDE_ARB 0x8dae

#define glCompileShaderIncludeARB _glplatform_glCompileShaderIncludeARB
extern void (*glCompileShaderIncludeARB)(GLuint, GLsizei, const GLchar *const*, const GLint *);
#define glDeleteNamedStringARB _glplatform_glDeleteNamedStringARB
extern void (*glDeleteNamedStringARB)(GLint, const GLchar *);
#define glGetNamedStringARB _glplatform_glGetNamedStringARB
extern void (*glGetNamedStringARB)(GLint, const GLchar *, GLsizei, GLint *, GLchar *);
#define glGetNamedStringivARB _glplatform_glGetNamedStringivARB
extern void (*glGetNamedStringivARB)(GLint, const GLchar *, GLenum, GLint *);
#define glIsNamedStringARB _glplatform_glIsNamedStringARB
extern GLboolean (*glIsNamedStringARB)(GLint, const GLchar *);
#define glNamedStringARB _glplatform_glNamedStringARB
extern void (*glNamedStringARB)(GLenum, GLint, const GLchar *, GLint, const GLchar *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_shading_language_packing)
extern bool GLPLATFORM_GL_ARB_shading_language_packing;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_sparse_buffer)
extern bool GLPLATFORM_GL_ARB_sparse_buffer;

#define GL_SPARSE_BUFFER_PAGE_SIZE_ARB 0x82f8
#define GL_SPARSE_STORAGE_BIT_ARB 0x400

#define glBufferPageCommitmentARB _glplatform_glBufferPageCommitmentARB
extern void (*glBufferPageCommitmentARB)(GLenum, GLintptr, GLsizeiptr, GLboolean);
#define glNamedBufferPageCommitmentARB _glplatform_glNamedBufferPageCommitmentARB
extern void (*glNamedBufferPageCommitmentARB)(GLuint, GLintptr, GLsizeiptr, GLboolean);
#define glNamedBufferPageCommitmentEXT _glplatform_glNamedBufferPageCommitmentEXT
extern void (*glNamedBufferPageCommitmentEXT)(GLuint, GLintptr, GLsizeiptr, GLboolean);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_sparse_texture)
extern bool GLPLATFORM_GL_ARB_sparse_texture;

#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB 0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_ARB 0x919a
#define GL_MAX_SPARSE_TEXTURE_SIZE_ARB 0x9198
#define GL_NUM_SPARSE_LEVELS_ARB 0x91aa
#define GL_NUM_VIRTUAL_PAGE_SIZES_ARB 0x91a8
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_ARB 0x91a9
#define GL_TEXTURE_SPARSE_ARB 0x91a6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_ARB 0x91a7
#define GL_VIRTUAL_PAGE_SIZE_X_ARB 0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_ARB 0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_ARB 0x9197

#define glTexPageCommitmentARB _glplatform_glTexPageCommitmentARB
extern void (*glTexPageCommitmentARB)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_stencil_texturing)
extern bool GLPLATFORM_GL_ARB_stencil_texturing;

#define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90ea

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_sync)
extern bool GLPLATFORM_GL_ARB_sync;
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif
#ifndef GLPLATFORM_TYPE_GLsync
#define GLPLATFORM_TYPE_GLsync
typedef struct __GLsync *GLsync;
#endif
#ifndef GLPLATFORM_TYPE_GLuint64
#define GLPLATFORM_TYPE_GLuint64
typedef uint64_t GLuint64;
#endif

#define GL_ALREADY_SIGNALED 0x911a
#define GL_CONDITION_SATISFIED 0x911c
#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_OBJECT_TYPE 0x9112
#define GL_SIGNALED 0x9119
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x1
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_SYNC_STATUS 0x9114
#define GL_TIMEOUT_EXPIRED 0x911b
#define GL_TIMEOUT_IGNORED 0xffffffff
#define GL_UNSIGNALED 0x9118
#define GL_WAIT_FAILED 0x911d

#define glClientWaitSync _glplatform_glClientWaitSync
extern GLenum (*glClientWaitSync)(GLsync, GLbitfield, GLuint64);
#define glDeleteSync _glplatform_glDeleteSync
extern void (*glDeleteSync)(GLsync);
#define glFenceSync _glplatform_glFenceSync
extern GLsync (*glFenceSync)(GLenum, GLbitfield);
#define glGetInteger64v _glplatform_glGetInteger64v
extern void (*glGetInteger64v)(GLenum, GLint64 *);
#define glGetSynciv _glplatform_glGetSynciv
extern void (*glGetSynciv)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
#define glIsSync _glplatform_glIsSync
extern GLboolean (*glIsSync)(GLsync);
#define glWaitSync _glplatform_glWaitSync
extern void (*glWaitSync)(GLsync, GLbitfield, GLuint64);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_tessellation_shader)
extern bool GLPLATFORM_GL_ARB_tessellation_shader;

#define GL_CCW 0x901
#define GL_CW 0x900
#define GL_EQUAL 0x202
#define GL_FRACTIONAL_EVEN 0x8e7c
#define GL_FRACTIONAL_ODD 0x8e7b
#define GL_ISOLINES 0x8e7a
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e1e
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e1f
#define GL_MAX_PATCH_VERTICES 0x8e7d
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886c
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8e83
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8e81
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8e85
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8e89
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8e7f
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886d
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8e86
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8e82
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8e8a
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8e80
#define GL_MAX_TESS_GEN_LEVEL 0x8e7e
#define GL_MAX_TESS_PATCH_COMPONENTS 0x8e84
#define GL_PATCHES 0xe
#define GL_PATCH_DEFAULT_INNER_LEVEL 0x8e73
#define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8e74
#define GL_PATCH_VERTICES 0x8e72
#define GL_QUADS 0x7
#define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8e75
#define GL_TESS_CONTROL_SHADER 0x8e88
#define GL_TESS_EVALUATION_SHADER 0x8e87
#define GL_TESS_GEN_MODE 0x8e76
#define GL_TESS_GEN_POINT_MODE 0x8e79
#define GL_TESS_GEN_SPACING 0x8e77
#define GL_TESS_GEN_VERTEX_ORDER 0x8e78
#define GL_TRIANGLES 0x4
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84f0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84f1

#define glPatchParameterfv _glplatform_glPatchParameterfv
extern void (*glPatchParameterfv)(GLenum, const GLfloat *);
#define glPatchParameteri _glplatform_glPatchParameteri
extern void (*glPatchParameteri)(GLenum, GLint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_barrier)
extern bool GLPLATFORM_GL_ARB_texture_barrier;


#define glTextureBarrier _glplatform_glTextureBarrier
extern void (*glTextureBarrier)();
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_buffer_object_rgb32)
extern bool GLPLATFORM_GL_ARB_texture_buffer_object_rgb32;

#define GL_RGB32F 0x8815
#define GL_RGB32I 0x8d83
#define GL_RGB32UI 0x8d71

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_buffer_range)
extern bool GLPLATFORM_GL_ARB_texture_buffer_range;

#define GL_TEXTURE_BUFFER_OFFSET 0x919d
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919f
#define GL_TEXTURE_BUFFER_SIZE 0x919e

#define glTexBufferRange _glplatform_glTexBufferRange
extern void (*glTexBufferRange)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_compression_bptc)
extern bool GLPLATFORM_GL_ARB_texture_compression_bptc;

#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8e8c
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8e8e
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8e8f
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8e8d

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_compression_rgtc)
extern bool GLPLATFORM_GL_ARB_texture_compression_rgtc;

#define GL_COMPRESSED_RED_RGTC1 0x8dbb
#define GL_COMPRESSED_RG_RGTC2 0x8dbd
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8dbc
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8dbe

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_cube_map_array)
extern bool GLPLATFORM_GL_ARB_texture_cube_map_array;

#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900e
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB 0x900b
#define GL_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900c
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB 0x900d
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB 0x900a
#define GL_TEXTURE_CUBE_MAP_ARRAY_ARB 0x9009
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_gather)
extern bool GLPLATFORM_GL_ARB_texture_gather;

#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB 0x8f9f
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8e5f
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8e5e

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_mirror_clamp_to_edge)
extern bool GLPLATFORM_GL_ARB_texture_mirror_clamp_to_edge;

#define GL_MIRROR_CLAMP_TO_EDGE 0x8743

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_multisample)
extern bool GLPLATFORM_GL_ARB_texture_multisample;

#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910c
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910e
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910f
#define GL_MAX_INTEGER_SAMPLES 0x9110
#define GL_MAX_SAMPLE_MASK_WORDS 0x8e59
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910b
#define GL_SAMPLE_MASK 0x8e51
#define GL_SAMPLE_MASK_VALUE 0x8e52
#define GL_SAMPLE_POSITION 0x8e50
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910a
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910d

#define glGetMultisamplefv _glplatform_glGetMultisamplefv
extern void (*glGetMultisamplefv)(GLenum, GLuint, GLfloat *);
#define glSampleMaski _glplatform_glSampleMaski
extern void (*glSampleMaski)(GLuint, GLbitfield);
#define glTexImage2DMultisample _glplatform_glTexImage2DMultisample
extern void (*glTexImage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexImage3DMultisample _glplatform_glTexImage3DMultisample
extern void (*glTexImage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_query_levels)
extern bool GLPLATFORM_GL_ARB_texture_query_levels;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_query_lod)
extern bool GLPLATFORM_GL_ARB_texture_query_lod;


#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_rg)
extern bool GLPLATFORM_GL_ARB_texture_rg;

#define GL_R16 0x822a
#define GL_R16F 0x822d
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32F 0x822e
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_R8 0x8229
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_RG 0x8227
#define GL_RG16 0x822c
#define GL_RG16F 0x822f
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823a
#define GL_RG32F 0x8230
#define GL_RG32I 0x823b
#define GL_RG32UI 0x823c
#define GL_RG8 0x822b
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG_INTEGER 0x8228

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_rgb10_a2ui)
extern bool GLPLATFORM_GL_ARB_texture_rgb10_a2ui;

#define GL_RGB10_A2UI 0x906f

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_stencil8)
extern bool GLPLATFORM_GL_ARB_texture_stencil8;

#define GL_STENCIL_INDEX 0x1901
#define GL_STENCIL_INDEX8 0x8d48

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_storage)
extern bool GLPLATFORM_GL_ARB_texture_storage;

#define GL_TEXTURE_IMMUTABLE_FORMAT 0x912f

#define glTexStorage1D _glplatform_glTexStorage1D
extern void (*glTexStorage1D)(GLenum, GLsizei, GLenum, GLsizei);
#define glTexStorage2D _glplatform_glTexStorage2D
extern void (*glTexStorage2D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
#define glTexStorage3D _glplatform_glTexStorage3D
extern void (*glTexStorage3D)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_storage_multisample)
extern bool GLPLATFORM_GL_ARB_texture_storage_multisample;


#define glTexStorage2DMultisample _glplatform_glTexStorage2DMultisample
extern void (*glTexStorage2DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
#define glTexStorage3DMultisample _glplatform_glTexStorage3DMultisample
extern void (*glTexStorage3DMultisample)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_swizzle)
extern bool GLPLATFORM_GL_ARB_texture_swizzle;

#define GL_TEXTURE_SWIZZLE_A 0x8e45
#define GL_TEXTURE_SWIZZLE_B 0x8e44
#define GL_TEXTURE_SWIZZLE_G 0x8e43
#define GL_TEXTURE_SWIZZLE_R 0x8e42
#define GL_TEXTURE_SWIZZLE_RGBA 0x8e46

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_texture_view)
extern bool GLPLATFORM_GL_ARB_texture_view;

#define GL_TEXTURE_IMMUTABLE_LEVELS 0x82df
#define GL_TEXTURE_VIEW_MIN_LAYER 0x82dd
#define GL_TEXTURE_VIEW_MIN_LEVEL 0x82db
#define GL_TEXTURE_VIEW_NUM_LAYERS 0x82de
#define GL_TEXTURE_VIEW_NUM_LEVELS 0x82dc

#define glTextureView _glplatform_glTextureView
extern void (*glTextureView)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_timer_query)
extern bool GLPLATFORM_GL_ARB_timer_query;
#ifndef GLPLATFORM_TYPE_GLint64
#define GLPLATFORM_TYPE_GLint64
typedef int64_t GLint64;
#endif
#ifndef GLPLATFORM_TYPE_GLuint64
#define GLPLATFORM_TYPE_GLuint64
typedef uint64_t GLuint64;
#endif

#define GL_TIMESTAMP 0x8e28
#define GL_TIME_ELAPSED 0x88bf

#define glGetQueryObjecti64v _glplatform_glGetQueryObjecti64v
extern void (*glGetQueryObjecti64v)(GLuint, GLenum, GLint64 *);
#define glGetQueryObjectui64v _glplatform_glGetQueryObjectui64v
extern void (*glGetQueryObjectui64v)(GLuint, GLenum, GLuint64 *);
#define glQueryCounter _glplatform_glQueryCounter
extern void (*glQueryCounter)(GLuint, GLenum);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_transform_feedback2)
extern bool GLPLATFORM_GL_ARB_transform_feedback2;

#define GL_TRANSFORM_FEEDBACK 0x8e22
#define GL_TRANSFORM_FEEDBACK_BINDING 0x8e25
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8e24
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8e23

#define glBindTransformFeedback _glplatform_glBindTransformFeedback
extern void (*glBindTransformFeedback)(GLenum, GLuint);
#define glDeleteTransformFeedbacks _glplatform_glDeleteTransformFeedbacks
extern void (*glDeleteTransformFeedbacks)(GLsizei, const GLuint *);
#define glDrawTransformFeedback _glplatform_glDrawTransformFeedback
extern void (*glDrawTransformFeedback)(GLenum, GLuint);
#define glGenTransformFeedbacks _glplatform_glGenTransformFeedbacks
extern void (*glGenTransformFeedbacks)(GLsizei, GLuint *);
#define glIsTransformFeedback _glplatform_glIsTransformFeedback
extern GLboolean (*glIsTransformFeedback)(GLuint);
#define glPauseTransformFeedback _glplatform_glPauseTransformFeedback
extern void (*glPauseTransformFeedback)();
#define glResumeTransformFeedback _glplatform_glResumeTransformFeedback
extern void (*glResumeTransformFeedback)();
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_transform_feedback3)
extern bool GLPLATFORM_GL_ARB_transform_feedback3;

#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8e70
#define GL_MAX_VERTEX_STREAMS 0x8e71

#define glBeginQueryIndexed _glplatform_glBeginQueryIndexed
extern void (*glBeginQueryIndexed)(GLenum, GLuint, GLuint);
#define glDrawTransformFeedbackStream _glplatform_glDrawTransformFeedbackStream
extern void (*glDrawTransformFeedbackStream)(GLenum, GLuint, GLuint);
#define glEndQueryIndexed _glplatform_glEndQueryIndexed
extern void (*glEndQueryIndexed)(GLenum, GLuint);
#define glGetQueryIndexediv _glplatform_glGetQueryIndexediv
extern void (*glGetQueryIndexediv)(GLenum, GLuint, GLenum, GLint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_transform_feedback_instanced)
extern bool GLPLATFORM_GL_ARB_transform_feedback_instanced;


#define glDrawTransformFeedbackInstanced _glplatform_glDrawTransformFeedbackInstanced
extern void (*glDrawTransformFeedbackInstanced)(GLenum, GLuint, GLsizei);
#define glDrawTransformFeedbackStreamInstanced _glplatform_glDrawTransformFeedbackStreamInstanced
extern void (*glDrawTransformFeedbackStreamInstanced)(GLenum, GLuint, GLuint, GLsizei);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_transform_feedback_overflow_query)
extern bool GLPLATFORM_GL_ARB_transform_feedback_overflow_query;

#define GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB 0x82ec
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB 0x82ed

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_uniform_buffer_object)
extern bool GLPLATFORM_GL_ARB_uniform_buffer_object;
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_ACTIVE_UNIFORM_BLOCKS 0x8a36
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8a35
#define GL_INVALID_INDEX 0xffffffff
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8a33
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8a32
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8a2e
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8a31
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8a2d
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8a2c
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8a30
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8a2f
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8a2b
#define GL_UNIFORM_ARRAY_STRIDE 0x8a3c
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8a42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8a43
#define GL_UNIFORM_BLOCK_BINDING 0x8a3f
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8a40
#define GL_UNIFORM_BLOCK_INDEX 0x8a3a
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8a41
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8a46
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8a45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8a44
#define GL_UNIFORM_BUFFER 0x8a11
#define GL_UNIFORM_BUFFER_BINDING 0x8a28
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8a34
#define GL_UNIFORM_BUFFER_SIZE 0x8a2a
#define GL_UNIFORM_BUFFER_START 0x8a29
#define GL_UNIFORM_IS_ROW_MAJOR 0x8a3e
#define GL_UNIFORM_MATRIX_STRIDE 0x8a3d
#define GL_UNIFORM_NAME_LENGTH 0x8a39
#define GL_UNIFORM_OFFSET 0x8a3b
#define GL_UNIFORM_SIZE 0x8a38
#define GL_UNIFORM_TYPE 0x8a37

#define glBindBufferBase _glplatform_glBindBufferBase
extern void (*glBindBufferBase)(GLenum, GLuint, GLuint);
#define glBindBufferRange _glplatform_glBindBufferRange
extern void (*glBindBufferRange)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
#define glGetActiveUniformBlockName _glplatform_glGetActiveUniformBlockName
extern void (*glGetActiveUniformBlockName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformBlockiv _glplatform_glGetActiveUniformBlockiv
extern void (*glGetActiveUniformBlockiv)(GLuint, GLuint, GLenum, GLint *);
#define glGetActiveUniformName _glplatform_glGetActiveUniformName
extern void (*glGetActiveUniformName)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetActiveUniformsiv _glplatform_glGetActiveUniformsiv
extern void (*glGetActiveUniformsiv)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
#define glGetIntegeri_v _glplatform_glGetIntegeri_v
extern void (*glGetIntegeri_v)(GLenum, GLuint, GLint *);
#define glGetUniformBlockIndex _glplatform_glGetUniformBlockIndex
extern GLuint (*glGetUniformBlockIndex)(GLuint, const GLchar *);
#define glGetUniformIndices _glplatform_glGetUniformIndices
extern void (*glGetUniformIndices)(GLuint, GLsizei, const GLchar *const*, GLuint *);
#define glUniformBlockBinding _glplatform_glUniformBlockBinding
extern void (*glUniformBlockBinding)(GLuint, GLuint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_array_bgra)
extern bool GLPLATFORM_GL_ARB_vertex_array_bgra;

#define GL_BGRA 0x80e1

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_array_object)
extern bool GLPLATFORM_GL_ARB_vertex_array_object;

#define GL_VERTEX_ARRAY_BINDING 0x85b5

#define glBindVertexArray _glplatform_glBindVertexArray
extern void (*glBindVertexArray)(GLuint);
#define glDeleteVertexArrays _glplatform_glDeleteVertexArrays
extern void (*glDeleteVertexArrays)(GLsizei, const GLuint *);
#define glGenVertexArrays _glplatform_glGenVertexArrays
extern void (*glGenVertexArrays)(GLsizei, GLuint *);
#define glIsVertexArray _glplatform_glIsVertexArray
extern GLboolean (*glIsVertexArray)(GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_64bit)
extern bool GLPLATFORM_GL_ARB_vertex_attrib_64bit;

#define GL_DOUBLE_MAT2 0x8f46
#define GL_DOUBLE_MAT2x3 0x8f49
#define GL_DOUBLE_MAT2x4 0x8f4a
#define GL_DOUBLE_MAT3 0x8f47
#define GL_DOUBLE_MAT3x2 0x8f4b
#define GL_DOUBLE_MAT3x4 0x8f4c
#define GL_DOUBLE_MAT4 0x8f48
#define GL_DOUBLE_MAT4x2 0x8f4d
#define GL_DOUBLE_MAT4x3 0x8f4e
#define GL_DOUBLE_VEC2 0x8ffc
#define GL_DOUBLE_VEC3 0x8ffd
#define GL_DOUBLE_VEC4 0x8ffe
#define GL_RGB32I 0x8d83

#define glGetVertexAttribLdv _glplatform_glGetVertexAttribLdv
extern void (*glGetVertexAttribLdv)(GLuint, GLenum, GLdouble *);
#define glVertexAttribL1d _glplatform_glVertexAttribL1d
extern void (*glVertexAttribL1d)(GLuint, GLdouble);
#define glVertexAttribL1dv _glplatform_glVertexAttribL1dv
extern void (*glVertexAttribL1dv)(GLuint, const GLdouble *);
#define glVertexAttribL2d _glplatform_glVertexAttribL2d
extern void (*glVertexAttribL2d)(GLuint, GLdouble, GLdouble);
#define glVertexAttribL2dv _glplatform_glVertexAttribL2dv
extern void (*glVertexAttribL2dv)(GLuint, const GLdouble *);
#define glVertexAttribL3d _glplatform_glVertexAttribL3d
extern void (*glVertexAttribL3d)(GLuint, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL3dv _glplatform_glVertexAttribL3dv
extern void (*glVertexAttribL3dv)(GLuint, const GLdouble *);
#define glVertexAttribL4d _glplatform_glVertexAttribL4d
extern void (*glVertexAttribL4d)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
#define glVertexAttribL4dv _glplatform_glVertexAttribL4dv
extern void (*glVertexAttribL4dv)(GLuint, const GLdouble *);
#define glVertexAttribLPointer _glplatform_glVertexAttribLPointer
extern void (*glVertexAttribLPointer)(GLuint, GLint, GLenum, GLsizei, const void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding)
extern bool GLPLATFORM_GL_ARB_vertex_attrib_binding;

#define GL_MAX_VERTEX_ATTRIB_BINDINGS 0x82da
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d9
#define GL_VERTEX_ATTRIB_BINDING 0x82d4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82d5
#define GL_VERTEX_BINDING_DIVISOR 0x82d6
#define GL_VERTEX_BINDING_OFFSET 0x82d7
#define GL_VERTEX_BINDING_STRIDE 0x82d8

#define glBindVertexBuffer _glplatform_glBindVertexBuffer
extern void (*glBindVertexBuffer)(GLuint, GLuint, GLintptr, GLsizei);
#define glVertexAttribBinding _glplatform_glVertexAttribBinding
extern void (*glVertexAttribBinding)(GLuint, GLuint);
#define glVertexAttribFormat _glplatform_glVertexAttribFormat
extern void (*glVertexAttribFormat)(GLuint, GLint, GLenum, GLboolean, GLuint);
#define glVertexAttribIFormat _glplatform_glVertexAttribIFormat
extern void (*glVertexAttribIFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexAttribLFormat _glplatform_glVertexAttribLFormat
extern void (*glVertexAttribLFormat)(GLuint, GLint, GLenum, GLuint);
#define glVertexBindingDivisor _glplatform_glVertexBindingDivisor
extern void (*glVertexBindingDivisor)(GLuint, GLuint);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_type_10f_11f_11f_rev)
extern bool GLPLATFORM_GL_ARB_vertex_type_10f_11f_11f_rev;

#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8c3b

#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_vertex_type_2_10_10_10_rev)
extern bool GLPLATFORM_GL_ARB_vertex_type_2_10_10_10_rev;

#define GL_INT_2_10_10_10_REV 0x8d9f
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368

#define glVertexAttribP1ui _glplatform_glVertexAttribP1ui
extern void (*glVertexAttribP1ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP1uiv _glplatform_glVertexAttribP1uiv
extern void (*glVertexAttribP1uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP2ui _glplatform_glVertexAttribP2ui
extern void (*glVertexAttribP2ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP2uiv _glplatform_glVertexAttribP2uiv
extern void (*glVertexAttribP2uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP3ui _glplatform_glVertexAttribP3ui
extern void (*glVertexAttribP3ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP3uiv _glplatform_glVertexAttribP3uiv
extern void (*glVertexAttribP3uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#define glVertexAttribP4ui _glplatform_glVertexAttribP4ui
extern void (*glVertexAttribP4ui)(GLuint, GLenum, GLboolean, GLuint);
#define glVertexAttribP4uiv _glplatform_glVertexAttribP4uiv
extern void (*glVertexAttribP4uiv)(GLuint, GLenum, GLboolean, const GLuint *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_ARB_viewport_array)
extern bool GLPLATFORM_GL_ARB_viewport_array;

#define GL_DEPTH_RANGE 0xb70
#define GL_FIRST_VERTEX_CONVENTION 0x8e4d
#define GL_LAST_VERTEX_CONVENTION 0x8e4e
#define GL_LAYER_PROVOKING_VERTEX 0x825e
#define GL_MAX_VIEWPORTS 0x825b
#define GL_PROVOKING_VERTEX 0x8e4f
#define GL_SCISSOR_BOX 0xc10
#define GL_SCISSOR_TEST 0xc11
#define GL_UNDEFINED_VERTEX 0x8260
#define GL_VIEWPORT 0xba2
#define GL_VIEWPORT_BOUNDS_RANGE 0x825d
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825f
#define GL_VIEWPORT_SUBPIXEL_BITS 0x825c

#define glDepthRangeArrayv _glplatform_glDepthRangeArrayv
extern void (*glDepthRangeArrayv)(GLuint, GLsizei, const GLdouble *);
#define glDepthRangeIndexed _glplatform_glDepthRangeIndexed
extern void (*glDepthRangeIndexed)(GLuint, GLdouble, GLdouble);
#define glGetDoublei_v _glplatform_glGetDoublei_v
extern void (*glGetDoublei_v)(GLenum, GLuint, GLdouble *);
#define glGetFloati_v _glplatform_glGetFloati_v
extern void (*glGetFloati_v)(GLenum, GLuint, GLfloat *);
#define glScissorArrayv _glplatform_glScissorArrayv
extern void (*glScissorArrayv)(GLuint, GLsizei, const GLint *);
#define glScissorIndexed _glplatform_glScissorIndexed
extern void (*glScissorIndexed)(GLuint, GLint, GLint, GLsizei, GLsizei);
#define glScissorIndexedv _glplatform_glScissorIndexedv
extern void (*glScissorIndexedv)(GLuint, const GLint *);
#define glViewportArrayv _glplatform_glViewportArrayv
extern void (*glViewportArrayv)(GLuint, GLsizei, const GLfloat *);
#define glViewportIndexedf _glplatform_glViewportIndexedf
extern void (*glViewportIndexedf)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
#define glViewportIndexedfv _glplatform_glViewportIndexedfv
extern void (*glViewportIndexedfv)(GLuint, const GLfloat *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_context_flush_control)
extern bool GLPLATFORM_GL_KHR_context_flush_control;

#define GL_CONTEXT_RELEASE_BEHAVIOR 0x82fb
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82fc
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82fc
#define GL_CONTEXT_RELEASE_BEHAVIOR_KHR 0x82fb
#define GL_NONE 0x0

#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_debug)
extern bool GLPLATFORM_GL_KHR_debug;
#ifndef GLPLATFORM_TYPE_GLDEBUGPROC
#define GLPLATFORM_TYPE_GLDEBUGPROC
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif
#ifndef GLPLATFORM_TYPE_GLDEBUGPROCKHR
#define GLPLATFORM_TYPE_GLDEBUGPROCKHR
typedef void ( *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif
#ifndef GLPLATFORM_TYPE_GLchar
#define GLPLATFORM_TYPE_GLchar
typedef char GLchar;
#endif

#define GL_BUFFER 0x82e0
#define GL_BUFFER_KHR 0x82e0
#define GL_CONTEXT_FLAG_DEBUG_BIT 0x2
#define GL_CONTEXT_FLAG_DEBUG_BIT_KHR 0x2
#define GL_DEBUG_CALLBACK_FUNCTION 0x8244
#define GL_DEBUG_CALLBACK_FUNCTION_KHR 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM 0x8245
#define GL_DEBUG_CALLBACK_USER_PARAM_KHR 0x8245
#define GL_DEBUG_GROUP_STACK_DEPTH 0x826d
#define GL_DEBUG_GROUP_STACK_DEPTH_KHR 0x826d
#define GL_DEBUG_LOGGED_MESSAGES 0x9145
#define GL_DEBUG_LOGGED_MESSAGES_KHR 0x9145
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR 0x8243
#define GL_DEBUG_OUTPUT 0x92e0
#define GL_DEBUG_OUTPUT_KHR 0x92e0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR 0x8242
#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_HIGH_KHR 0x9146
#define GL_DEBUG_SEVERITY_LOW 0x9148
#define GL_DEBUG_SEVERITY_LOW_KHR 0x9148
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_DEBUG_SEVERITY_MEDIUM_KHR 0x9147
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826b
#define GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826b
#define GL_DEBUG_SOURCE_API 0x8246
#define GL_DEBUG_SOURCE_API_KHR 0x8246
#define GL_DEBUG_SOURCE_APPLICATION 0x824a
#define GL_DEBUG_SOURCE_APPLICATION_KHR 0x824a
#define GL_DEBUG_SOURCE_OTHER 0x824b
#define GL_DEBUG_SOURCE_OTHER_KHR 0x824b
#define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#define GL_DEBUG_SOURCE_SHADER_COMPILER_KHR 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#define GL_DEBUG_SOURCE_THIRD_PARTY_KHR 0x8249
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR 0x8247
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824d
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824d
#define GL_DEBUG_TYPE_ERROR 0x824c
#define GL_DEBUG_TYPE_ERROR_KHR 0x824c
#define GL_DEBUG_TYPE_MARKER 0x8268
#define GL_DEBUG_TYPE_MARKER_KHR 0x8268
#define GL_DEBUG_TYPE_OTHER 0x8251
#define GL_DEBUG_TYPE_OTHER_KHR 0x8251
#define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#define GL_DEBUG_TYPE_PERFORMANCE_KHR 0x8250
#define GL_DEBUG_TYPE_POP_GROUP 0x826a
#define GL_DEBUG_TYPE_POP_GROUP_KHR 0x826a
#define GL_DEBUG_TYPE_PORTABILITY 0x824f
#define GL_DEBUG_TYPE_PORTABILITY_KHR 0x824f
#define GL_DEBUG_TYPE_PUSH_GROUP 0x8269
#define GL_DEBUG_TYPE_PUSH_GROUP_KHR 0x8269
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824e
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824e
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH 0x826c
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR 0x826c
#define GL_MAX_DEBUG_LOGGED_MESSAGES 0x9144
#define GL_MAX_DEBUG_LOGGED_MESSAGES_KHR 0x9144
#define GL_MAX_DEBUG_MESSAGE_LENGTH 0x9143
#define GL_MAX_DEBUG_MESSAGE_LENGTH_KHR 0x9143
#define GL_MAX_LABEL_LENGTH 0x82e8
#define GL_MAX_LABEL_LENGTH_KHR 0x82e8
#define GL_PROGRAM 0x82e2
#define GL_PROGRAM_KHR 0x82e2
#define GL_PROGRAM_PIPELINE 0x82e4
#define GL_PROGRAM_PIPELINE_KHR 0x82e4
#define GL_QUERY 0x82e3
#define GL_QUERY_KHR 0x82e3
#define GL_SAMPLER 0x82e6
#define GL_SAMPLER_KHR 0x82e6
#define GL_SHADER 0x82e1
#define GL_SHADER_KHR 0x82e1
#define GL_STACK_OVERFLOW 0x503
#define GL_STACK_OVERFLOW_KHR 0x503
#define GL_STACK_UNDERFLOW 0x504
#define GL_STACK_UNDERFLOW_KHR 0x504
#define GL_VERTEX_ARRAY 0x8074
#define GL_VERTEX_ARRAY_KHR 0x8074

#define glDebugMessageCallback _glplatform_glDebugMessageCallback
extern void (*glDebugMessageCallback)(GLDEBUGPROC, const void *);
#define glDebugMessageCallbackKHR _glplatform_glDebugMessageCallbackKHR
extern void (*glDebugMessageCallbackKHR)(GLDEBUGPROCKHR, const void *);
#define glDebugMessageControl _glplatform_glDebugMessageControl
extern void (*glDebugMessageControl)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
#define glDebugMessageControlKHR _glplatform_glDebugMessageControlKHR
extern void (*glDebugMessageControlKHR)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
#define glDebugMessageInsert _glplatform_glDebugMessageInsert
extern void (*glDebugMessageInsert)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
#define glDebugMessageInsertKHR _glplatform_glDebugMessageInsertKHR
extern void (*glDebugMessageInsertKHR)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
#define glGetDebugMessageLog _glplatform_glGetDebugMessageLog
extern GLuint (*glGetDebugMessageLog)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
#define glGetDebugMessageLogKHR _glplatform_glGetDebugMessageLogKHR
extern GLuint (*glGetDebugMessageLogKHR)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
#define glGetObjectLabel _glplatform_glGetObjectLabel
extern void (*glGetObjectLabel)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetObjectLabelKHR _glplatform_glGetObjectLabelKHR
extern void (*glGetObjectLabelKHR)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
#define glGetObjectPtrLabel _glplatform_glGetObjectPtrLabel
extern void (*glGetObjectPtrLabel)(const void *, GLsizei, GLsizei *, GLchar *);
#define glGetObjectPtrLabelKHR _glplatform_glGetObjectPtrLabelKHR
extern void (*glGetObjectPtrLabelKHR)(const void *, GLsizei, GLsizei *, GLchar *);
#define glGetPointerv _glplatform_glGetPointerv
extern void (*glGetPointerv)(GLenum, void **);
#define glGetPointervKHR _glplatform_glGetPointervKHR
extern void (*glGetPointervKHR)(GLenum, void **);
#define glObjectLabel _glplatform_glObjectLabel
extern void (*glObjectLabel)(GLenum, GLuint, GLsizei, const GLchar *);
#define glObjectLabelKHR _glplatform_glObjectLabelKHR
extern void (*glObjectLabelKHR)(GLenum, GLuint, GLsizei, const GLchar *);
#define glObjectPtrLabel _glplatform_glObjectPtrLabel
extern void (*glObjectPtrLabel)(const void *, GLsizei, const GLchar *);
#define glObjectPtrLabelKHR _glplatform_glObjectPtrLabelKHR
extern void (*glObjectPtrLabelKHR)(const void *, GLsizei, const GLchar *);
#define glPopDebugGroup _glplatform_glPopDebugGroup
extern void (*glPopDebugGroup)();
#define glPopDebugGroupKHR _glplatform_glPopDebugGroupKHR
extern void (*glPopDebugGroupKHR)();
#define glPushDebugGroup _glplatform_glPushDebugGroup
extern void (*glPushDebugGroup)(GLenum, GLuint, GLsizei, const GLchar *);
#define glPushDebugGroupKHR _glplatform_glPushDebugGroupKHR
extern void (*glPushDebugGroupKHR)(GLenum, GLuint, GLsizei, const GLchar *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_no_error)
extern bool GLPLATFORM_GL_KHR_no_error;

#define GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR 0x8

#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_robust_buffer_access_behavior)
extern bool GLPLATFORM_GL_KHR_robust_buffer_access_behavior;


#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_robustness)
extern bool GLPLATFORM_GL_KHR_robustness;

#define GL_CONTEXT_LOST 0x507
#define GL_CONTEXT_LOST_KHR 0x507
#define GL_CONTEXT_ROBUST_ACCESS 0x90f3
#define GL_CONTEXT_ROBUST_ACCESS_KHR 0x90f3
#define GL_GUILTY_CONTEXT_RESET 0x8253
#define GL_GUILTY_CONTEXT_RESET_KHR 0x8253
#define GL_INNOCENT_CONTEXT_RESET 0x8254
#define GL_INNOCENT_CONTEXT_RESET_KHR 0x8254
#define GL_LOSE_CONTEXT_ON_RESET 0x8252
#define GL_LOSE_CONTEXT_ON_RESET_KHR 0x8252
#define GL_NO_ERROR 0x0
#define GL_NO_RESET_NOTIFICATION 0x8261
#define GL_NO_RESET_NOTIFICATION_KHR 0x8261
#define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#define GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#define GL_UNKNOWN_CONTEXT_RESET 0x8255
#define GL_UNKNOWN_CONTEXT_RESET_KHR 0x8255

#define glGetGraphicsResetStatus _glplatform_glGetGraphicsResetStatus
extern GLenum (*glGetGraphicsResetStatus)();
#define glGetGraphicsResetStatusKHR _glplatform_glGetGraphicsResetStatusKHR
extern GLenum (*glGetGraphicsResetStatusKHR)();
#define glGetnUniformfv _glplatform_glGetnUniformfv
extern void (*glGetnUniformfv)(GLuint, GLint, GLsizei, GLfloat *);
#define glGetnUniformfvKHR _glplatform_glGetnUniformfvKHR
extern void (*glGetnUniformfvKHR)(GLuint, GLint, GLsizei, GLfloat *);
#define glGetnUniformiv _glplatform_glGetnUniformiv
extern void (*glGetnUniformiv)(GLuint, GLint, GLsizei, GLint *);
#define glGetnUniformivKHR _glplatform_glGetnUniformivKHR
extern void (*glGetnUniformivKHR)(GLuint, GLint, GLsizei, GLint *);
#define glGetnUniformuiv _glplatform_glGetnUniformuiv
extern void (*glGetnUniformuiv)(GLuint, GLint, GLsizei, GLuint *);
#define glGetnUniformuivKHR _glplatform_glGetnUniformuivKHR
extern void (*glGetnUniformuivKHR)(GLuint, GLint, GLsizei, GLuint *);
#define glReadnPixels _glplatform_glReadnPixels
extern void (*glReadnPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#define glReadnPixelsKHR _glplatform_glReadnPixelsKHR
extern void (*glReadnPixelsKHR)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_texture_compression_astc_hdr)
extern bool GLPLATFORM_GL_KHR_texture_compression_astc_hdr;

#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93bb
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR 0x93b8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR 0x93b9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR 0x93ba
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93bc
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93bd
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR 0x93b0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR 0x93b1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR 0x93b2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR 0x93b3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR 0x93b4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR 0x93b5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR 0x93b6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR 0x93b7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93db
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93d8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93d9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93da
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93dc
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93dd
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93d0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93d1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93d2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93d3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93d4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93d5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93d6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93d7

#endif

#if defined(GLPLATFORM_ENABLE_GL_KHR_texture_compression_astc_ldr)
extern bool GLPLATFORM_GL_KHR_texture_compression_astc_ldr;

#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93bb
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR 0x93b8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR 0x93b9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR 0x93ba
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93bc
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93bd
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR 0x93b0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR 0x93b1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR 0x93b2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR 0x93b3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR 0x93b4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR 0x93b5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR 0x93b6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR 0x93b7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93db
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93d8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93d9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93da
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93dc
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93dd
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93d0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93d1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93d2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93d3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93d4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93d5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93d6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93d7

#endif

bool glplatform_glcore_init(int maj, int min);

#ifdef __cplusplus
}
#endif
#endif
