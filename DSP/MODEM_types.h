#ifndef MODEM_TYPES_H_INCLUDED_
#define MODEM_TYPES_H_INCLUDED_

// ISO C headers.
#include <float.h>
#include <math.h>

//! @ingroup TYPES
//! @{

//! Signed 8-bit integer.
typedef signed char        MODEM_int8_p;
//! Unsigned 8-bit integer.
typedef unsigned char      MODEM_uint8_p;
//! Signed 16-bit integer.
typedef signed short       MODEM_int16_p;
//! Unsigned 16-bit integer.
typedef unsigned short     MODEM_uint16_p;
//! Signed 32-bit integer.
typedef signed int         MODEM_int32_p;
//! Unsigned 32-bit integer.
typedef unsigned int       MODEM_uint32_p;
//! Signed 64-bit integer.
typedef signed long long   MODEM_int64_p;
//! Unsigned 64-bit integer.
typedef unsigned long long MODEM_uint64_p;

//! Return the maximum of a and b.
#define MODEM_MAX(a, b) (((a) > (b)) ? a : b)
//! Return the minimum of a and b.
#define MODEM_MIN(a, b) (((a) < (b)) ? a : b)

// Do not uncomment next line, use cmake -DMODEM_REAL_SINGLE=1
//#define MODEM_REAL_SINGLE
#if defined(MODEM_REAL_SINGLE)
//! Single precision floating point type.
typedef float MODEM_real_t;
//! Utility macro to append a suffix to a function call.
#  define MODEM_REAL_SUFFIX(a) a ## f
//! Utility macro to append a suffix to a number literal.
#  define MODEM_REAL_CONST(a)  a ## f
//! Format to read real numbers using the scanf family of functions.
#  define MODEM_REAL_FMT       "%f"
//! Smallest number x such that 1.0 + x != 1.0
#  define MODEM_REAL_EPSILON    FLT_EPSILON
#else
//! Double precision floating point type.
typedef double MODEM_real_p;
//! Utility macro to append a suffix to a function call.
#  define MODEM_REAL_SUFFIX(a) a
//! Utility macro to append a suffix to a number literal.
#  define MODEM_REAL_CONST(a)  a
//! Format to read real numbers using the scanf family of functions.
#  define MODEM_REAL_FMT       "%lf"
//! Smallest number x such that 1.0 + x != 1.0
#  define MODEM_REAL_EPSILON   DBL_EPSILON
#endif

#if defined(MODEM_FFTW_SINGLE) || defined(MODEM_REAL_SINGLE)
//! Utility macro to prepend a prefix to a FFTW function call or type.
#  define MODEM_FFTW_PREFIX(a) fftwf_ ## a
#  define MODEM_fftw_real_t float
#else
//! Utility macro to prepend a prefix to a FFTW function call or type.
#  define MODEM_FFTW_PREFIX(a) fftw_ ## a
#  define MODEM_fftw_real_t double
#endif

//#define MODEM_HIPRECISION_SINGLE
#if defined(MODEM_HIPRECISION_SINGLE)
//! Single precision floating point type.
typedef float MODEM_hiprecision_t;
//! Utility macro to append a suffix to a function call.
#  define MODEM_HIPRECISION_SUFFIX(a) a ## f
//! Utility macro to append a suffix to a number literal.
#  define MODEM_HIPRECISION_CONST(a)  a ## f
//! Format to read hi precision numbers using the scanf family of functions.
#  define MODEM_HIPRECISION_FMT       "%f"
#else
//! Double precision floating point type.
typedef double MODEM_hiprecision_p;
//! Utility macro to append a suffix to a function call.
#  define MODEM_HIPRECISION_SUFFIX(a) a
//! Utility macro to append a suffix to a number literal.
#  define MODEM_HIPRECISION_CONST(a)  a
//! Format to read hi precision numbers using the scanf family of functions.
#  define MODEM_HIPRECISION_FMT       "%lf"
#endif

// Microsoft Visual Studio lacks a few ISO C99 functions.
#if __STDC_VERSION__ < 199901L
//! Round v to the nearest integer (double).
// #  define round(v)    floor(v + 0.5) incompatible redefinition
//! Round v to the nearest integer (float).
// #  define roundf(v)   floor(v + 0.5f) floor(v + 0.5) incompatible redefinition
//! Return the maximum of a and b (double).
#  define fmax(a, b)  (((a) > (b)) ? a : b)
//! Return the maximum of a and b (float).
#  define fmaxf(a, b) fmax(a, b)
//! Return the minimum of a and b (double).
#  define fmin(a, b)  (((a) > (b)) ? b : a)
//! Return the minimum of a and b (float).
#  define fminf(a, b) fmin(a, b)
//! Return the logarithm base 2 (double).
#  define log2(a) log(a)/log(2.0)
//! Return the logarithm base 2 (float).
#  define log2f(a) logf(a)/logf(2.0f)
#endif

//! cos() wrapper that uses the configured floating point precision.
#define MODEM_COS(a)     MODEM_REAL_SUFFIX(cos)(a)
//! sin() wrapper that uses the configured floating point precision.
#define MODEM_SIN(a)     MODEM_REAL_SUFFIX(sin)(a)
//! exp() wrapper that uses the configured floating point precision.
#define MODEM_EXP(a)     MODEM_REAL_SUFFIX(exp)(a)
//! fmod() wrapper that uses the configured floating point precision.
#define MODEM_FMOD(a, b) MODEM_REAL_SUFFIX(fmod)(a, b)
//! fmod() wrapper that uses the configured floating point precision.
#define MODEM_MODF(a, b) MODEM_REAL_SUFFIX(modf)(a, b)
//! fabs() wrapper that uses the configured floating point precision.
#define MODEM_FABS(a)    MODEM_REAL_SUFFIX(fabs)(a)
//! fmax() wrapper that uses the configured floating point precision.
#define MODEM_FMAX(a, b) MODEM_REAL_SUFFIX(fmax)(a, b)
//! fmax() wrapper that uses the configured floating point precision.
#define MODEM_FMIM(a, b) MODEM_REAL_SUFFIX(fmin)(a, b)
//! round() wrapper that uses the configured floating point precision.
#define MODEM_ROUND(a)   MODEM_REAL_SUFFIX(round)(a)
//! ceil() wrapper that uses the configured floating point precision.
#define MODEM_CEIL(a)    MODEM_REAL_SUFFIX(ceil)(a)
//! floor() wrapper that uses the configured floating point precision.
#define MODEM_FLOOR(a)   MODEM_REAL_SUFFIX(floor)(a)
//! trunc() wrapper that uses the configured floating point precision.
#define MODEM_TRUNC(a)   MODEM_REAL_SUFFIX(trunc)(a)
//! pow() wrapper that uses the configured floating point precision.
#define MODEM_POW(a, b)  MODEM_REAL_SUFFIX(pow)(a, b)
//! sqrt() wrapper that uses the configured floating point precision.
#define MODEM_SQRT(a)    MODEM_REAL_SUFFIX(sqrt)(a)
//! log2() wrapper that uses the configured floating point precision.
#define MODEM_LOG2(a)    MODEM_REAL_SUFFIX(log2)(a)
//! log() wrapper that uses the configured floating point precision.
#define MODEM_LOG(a)     MODEM_REAL_SUFFIX(log)(a)

//! cos() wrapper that uses the configured floating point precision.
#define MODEM_HP_COS(a)     MODEM_HIPRECISION_SUFFIX(cos)(a)
//! sin() wrapper that uses the configured floating point precision.
#define MODEM_HP_SIN(a)     MODEM_HIPRECISION_SUFFIX(sin)(a)

//! @}

#endif
