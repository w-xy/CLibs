#ifndef _CTYPE_H
#define _CTYPE_H

#include <stddef.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef int s32;

typedef unsigned short u16;
typedef short s16;

typedef unsigned char u8;
typedef char s8;

typedef struct
{
    s16 re;
    s16 im;
} cmpl16;

typedef union
{
    u16 value;
    struct
    {
        u16 sign: 1;
        u16 exp: 5;
        u16 mantissa: 10;
    };
} fp16;

typedef union
{
    u16 value;
    struct
    {
        u16 sign: 1;
        u16 exp: 8;
        u16 mantissa: 7;
    };
} bf16;

typedef union
{
    u8 value;
    struct
    {
        u8 sign: 1;
        u8 exp: 4;
        u8 mantissa: 3;
    };
} fp8e4m3;

typedef union
{
    u8 value;
    struct
    {
        u8 sign: 1;
        u8 exp: 5;
        u8 mantissa: 2;
    };
} fp8e5m2;


typedef struct
{
    union
    {
        u32 i;
        cmpl16 x;
        float f;
        void *p;
    };
} uni_t;

#define CTYPE_BASE_INT 0
#define CTYPE_BASE_FLOAT 1
#define CTYPE_BASE_PTR 2

#define CTYPE_VINT_S8 0
#define CTYPE_VINT_U8 1
#define CTYPE_VINT_S16 2
#define CTYPE_VINT_U16 3
#define CTYPE_VINT_S32 4
#define CTYPE_VINT_U32 5
#define CTYPE_VINT_CMPL16 6

#define CTYPE_VFLOAT_FP32 0
#define CTYPE_VFLOAT_FP16 1
#define CTYPE_VFLOAT_BF16 2
#define CTYPE_VFLOAT_FP8E4M3 3
#define CTYPE_VFLOAT_FP8E5M2 4

#define CTYPE_VPTR_PTR 0
#define CTYPE_VPTR_STR 1
#define CTYPE_VPTR_FUNC 2


typedef union
{
    u8 value[1];
    struct
    {
        u8 is_array: 1;
        u8 base_type: 2;
        u8 vtype: 3;
        u8 rsvd: 2;
    };
} uni_type;

#define UNI_TYPE(is_array, base_type, vtype) ((uni_type){.is_array = is_array, .base_type = base_type, .vtype = vtype})

typedef struct
{
    uni_type type;
    u16      size;
} uni_meta;



#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr)-offsetof(type, member)))

#define CLIBS_STATIC_CHECK_2POW(n) \
    ((void)sizeof(char[((n < 2) || (n & (n-1))) ? -1 : n]))



#endif