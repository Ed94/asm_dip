// This file was generated automatially by gencpp's singleheader.cpp(See: https://github.com/Ed94/gencpp)

#pragma once

#ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wunused-const-variable"
#	pragma clang diagnostic ignored "-Wunused-but-set-variable"
#	pragma clang diagnostic ignored "-Wswitch"
#	pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#	pragma clang diagnostic ignored "-Wvarargs"
#	pragma clang diagnostic ignored "-Wunused-function"
#endif

#ifdef __GNUC__
#	pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunknown-pragmas"
#	pragma GCC diagnostic ignored "-Wcomment"
#	pragma GCC diagnostic ignored "-Wswitch"
#	pragma GCC diagnostic ignored "-Wunused-variable"
#endif
/*
	gencpp: An attempt at "simple" staged metaprogramming for c/c++.

	See Readme.md for more information from the project repository.

	Public Address:
	https://github.com/Ed94/gencpp

	This is a single header variant of the library.
	Define GEN_IMPLEMENTATION before including this file in a single compilation unit.
*/
#if ! defined(GEN_DONT_ENFORCE_GEN_TIME_GUARD) && ! defined(GEN_TIME)
#	error Gen.hpp : GEN_TIME not defined
#endif

#ifdef GEN_DONT_USE_NAMESPACE
#	define GEN_NS_BEGIN
#	define GEN_NS_END
#else
#	define GEN_NS_BEGIN namespace gen {
#	define GEN_NS_END   }
#endif


//! If its desired to roll your own dependencies, define GEN_ROLL_OWN_DEPENDENCIES before including this file.
// Dependencies are derived from the c-zpl library: https://github.com/zpl-c/zpl
#ifndef GEN_ROLL_OWN_DEPENDENCIES

#pragma region Platform Detection

/* Platform architecture */

#if defined( _WIN64 ) || defined( __x86_64__ ) || defined( _M_X64 ) || defined( __64BIT__ ) || defined( __powerpc64__ ) || defined( __ppc64__ ) || defined( __aarch64__ )
#	ifndef GEN_ARCH_64_BIT
#		define GEN_ARCH_64_BIT 1
#	endif
#else
#	ifndef GEN_ARCH_32_BItxt_StrCaT
#		define GEN_ARCH_32_BIT 1
#	endif
#endif

/* Platform OS */

#if defined( _WIN32 ) || defined( _WIN64 )
#	ifndef GEN_SYSTEM_WINDOWS
#		define GEN_SYSTEM_WINDOWS 1
#	endif
#elif defined( __APPLE__ ) && defined( __MACH__ )
#	ifndef GEN_SYSTEM_OSX
#		define GEN_SYSTEM_OSX 1
#	endif
#	ifndef GEN_SYSTEM_MACOS
#		define GEN_SYSTEM_MACOS 1
#	endif
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
#		ifndef GEN_SYSTEM_IOS
#			define GEN_SYSTEM_IOS 1
#		endif
#	endif
#elif defined( __unix__ )
#	ifndef GEN_SYSTEM_UNIX
#		define GEN_SYSTEM_UNIX 1
#	endif
#	if defined( ANDROID ) || defined( __ANDROID__ )
#		ifndef GEN_SYSTEM_ANDROID
#			define GEN_SYSTEM_ANDROID 1
#		endif
#		ifndef GEN_SYSTEM_LINUX
#			define GEN_SYSTEM_LINUX 1
#		endif
#	elif defined( __linux__ )
#		ifndef GEN_SYSTEM_LINUX
#			define GEN_SYSTEM_LINUX 1
#		endif
#	elif defined( __FreeBSD__ ) || defined( __FreeBSD_kernel__ )
#		ifndef GEN_SYSTEM_FREEBSD
#			define GEN_SYSTEM_FREEBSD 1
#		endif
#	elif defined( __OpenBSD__ )
#		ifndef GEN_SYSTEM_OPENBSD
#			define GEN_SYSTEM_OPENBSD 1
#		endif
#	elif defined( __EMSCRIPTEN__ )
#		ifndef GEN_SYSTEM_EMSCRIPTEN
#			define GEN_SYSTEM_EMSCRIPTEN 1
#		endif
#	elif defined( __CYGWIN__ )
#		ifndef GEN_SYSTEM_CYGWIN
#			define GEN_SYSTEM_CYGWIN 1
#		endif
#	else
#		error This UNIX operating system is not supported
#	endif
#else
#	error This operating system is not supported
#endif

/* Platform compiler */

#if defined( _MSC_VER )
#	define GEN_COMPILER_MSVC 1
#elif defined( __GNUC__ )
#	define GEN_COMPILER_GCC 1
#elif defined( __clang__ )
#	define GEN_COMPILER_CLANG 1
#elif defined( __MINGW32__ )
#	define GEN_COMPILER_MINGW 1
#	error Unknown compiler
#endif

#if defined( __has_attribute )
#	define GEN_HAS_ATTRIBUTE( attribute ) __has_attribute( attribute )
#else
#	define GEN_HAS_ATTRIBUTE( attribute ) ( 0 )
#endif

#if defined(GEN_GCC_VERSION_CHECK)
#  undef GEN_GCC_VERSION_CHECK
#endif
#if defined(GEN_GCC_VERSION)
#  define GEN_GCC_VERSION_CHECK(major,minor,patch) (GEN_GCC_VERSION >= GEN_VERSION_ENCODE(major, minor, patch))
#else
#  define GEN_GCC_VERSION_CHECK(major,minor,patch) (0)
#endif

#pragma endregion Platform Detection

#pragma region Mandatory Includes

#	include <stdarg.h>
#	include <stddef.h>

#	if defined( GEN_SYSTEM_WINDOWS )
#		include <intrin.h>
#	endif

#pragma endregion Mandatory Includes

#ifdef GEN_DONT_USE_NAMESPACE
#	define GEN_NS
#	define GEN_NS_BEGIN
#	define GEN_NS_END
#else
#	define GEN_NS       gen::
#	define GEN_NS_BEGIN namespace gen {
#	define GEN_NS_END   }
#endif

GEN_NS_BEGIN

#pragma region Macros

#ifndef global
#define global        static    // Global variables
#endif
#ifndef internal
#define internal      static    // Internal linkage
#endif
#ifndef local_persist
#define local_persist static    // Local Persisting variables
#endif

#ifndef api_c
#define api_c extern "C"
#endif

#ifndef bit
#define bit( Value )                             ( 1 << Value )
#define bitfield_is_equal( Type, Field, Mask ) ( (Type(Mask) & Type(Field)) == Type(Mask) )
#endif

#ifndef ccast
#define ccast( type, value ) ( const_cast< type >( (value) ) )
#endif
#ifndef pcast
#define pcast( type, value ) ( * reinterpret_cast< type* >( & ( value ) ) )
#endif
#ifndef rcast
#define rcast( type, value ) reinterpret_cast< type >( value )
#endif
#ifndef scast
#define scast( type, value ) static_cast< type >( value )
#endif

#ifndef stringize
#define stringize_va( ... ) #__VA_ARGS__
#define stringize( ... )    stringize_va( __VA_ARGS__ )
#endif

#ifndef do_once
#define do_once( statement ) for ( local_persist b32 once = true; once; once = false, (statement) )

#define do_once_start      \
	do                     \
	{                      \
		local_persist      \
		bool done = false; \
		if ( done )        \
			break;         \
		done = true;

#define do_once_end        \
	}                      \
	while(0);
#endif

#ifndef labeled_scope_start
#define labeled_scope_start if ( false ) {
#define labeled_scope_end   }
#endif

#ifndef         compiler_decorated_func_name
#   ifdef COMPILER_CLANG
#       define  compiler_decorated_func_name __PRETTY_NAME__
#   elif defined(COMPILER_MSVC)
#   	define compiler_decorated_func_name __FUNCDNAME__
#   endif
#endif

#ifndef num_args_impl
#define num_args_impl( _0,                                 \
		_1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10,   \
		_11, _12, _13, _14, _15, _16, _17, _18, _19, _20,  \
		_21, _22, _23, _24, _25, _26, _27, _28, _29, _30,  \
		_31, _32, _33, _34, _35, _36, _37, _38, _39, _40,  \
		_41, _42, _43, _44, _45, _46, _47, _48, _49, _50,  \
		_51, _52, _53, _54, _55, _56, _57, _58, _59, _60,  \
		_61, _62, _63, _64, _65, _66, _67, _68, _69, _70,  \
		_71, _72, _73, _74, _75, _76, _77, _78, _79, _80,  \
		_81, _82, _83, _84, _85, _86, _87, _88, _89, _90,  \
		_91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
		N, ...                                             \
	) N

// ## deletes preceding comma if _VA_ARGS__ is empty (GCC, Clang)
#define num_args(...)                            \
	num_args_impl(_, ## __VA_ARGS__,             \
		100, 99, 98, 97, 96, 95, 94, 93, 92, 91, \
		 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, \
		 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, \
		 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, \
		 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, \
		 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, \
		 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, \
		 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, \
		 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, \
		 10,  9,  8,  7,  6,  5,  4,  3,  2,  1, \
		 0                                       \
	)
#endif

#ifndef clamp
#define clamp( x, lower, upper )      min( max( ( x ), ( lower ) ), ( upper ) )
#endif
#ifndef count_of
#define count_of( x )                 ( ( size_of( x ) / size_of( 0 [ x ] ) ) / ( ( ssize )( ! ( size_of( x ) % size_of( 0 [ x ] ) ) ) ) )
#endif
#ifndef is_between
#define is_between( x, lower, upper ) ( ( ( lower ) <= ( x ) ) && ( ( x ) <= ( upper ) ) )
#endif
#ifndef size_of
#define size_of( x )                  ( ssize )( sizeof( x ) )
#endif

#ifndef max
#define max( a, b ) ( (a > b) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( (a < b) ? (a) : (b) )
#endif

#if defined( _MSC_VER ) || defined( GEN_COMPILER_TINYC )
#	define offset_of( Type, element ) ( ( GEN_NS( ssize ) ) & ( ( ( Type* )0 )->element ) )
#else
#	define offset_of( Type, element ) __builtin_offsetof( Type, element )
#endif

#ifndef        forceinline
#	ifdef GEN_COMPILER_MSVC
#		define forceinline __forceinline
#		define neverinline __declspec( noinline )
#	elif defined(GEN_COMPILER_GCC)
#		define forceinline inline __attribute__((__always_inline__))
#		define neverinline __attribute__( ( __noinline__ ) )
#	elif defined(GEN_COMPILER_CLANG)
#	if __has_attribute(__always_inline__)
#		define forceinline inline __attribute__((__always_inline__))
#		define neverinline __attribute__( ( __noinline__ ) )
#	else
#		define forceinline
#		define neverinline
#	endif
#	else
#		define forceinline
#		define neverinline
#	endif
#endif

#ifndef        neverinline
#	ifdef GEN_COMPILER_MSVC
#		define neverinline __declspec( noinline )
#	elif defined(GEN_COMPILER_GCC)
#		define neverinline __attribute__( ( __noinline__ ) )
#	elif defined(GEN_COMPILER_CLANG)
#	if __has_attribute(__always_inline__)
#		define neverinline __attribute__( ( __noinline__ ) )
#	else
#		define neverinline
#	endif
#	else
#		define neverinline
#	endif
#endif

#pragma endregion Macros

#pragma region Basic Types

#define GEN_U8_MIN 0u
#define GEN_U8_MAX 0xffu
#define GEN_I8_MIN ( -0x7f - 1 )
#define GEN_I8_MAX 0x7f

#define GEN_U16_MIN 0u
#define GEN_U16_MAX 0xffffu
#define GEN_I16_MIN ( -0x7fff - 1 )
#define GEN_I16_MAX 0x7fff

#define GEN_U32_MIN 0u
#define GEN_U32_MAX 0xffffffffu
#define GEN_I32_MIN ( -0x7fffffff - 1 )
#define GEN_I32_MAX 0x7fffffff

#define GEN_U64_MIN 0ull
#define GEN_U64_MAX 0xffffffffffffffffull
#define GEN_I64_MIN ( -0x7fffffffffffffffll - 1 )
#define GEN_I64_MAX 0x7fffffffffffffffll

#if defined( GEN_ARCH_32_BIT )
#	define GEN_USIZE_MIN GEN_U32_MIN
#	define GEN_USIZE_MAX GEN_U32_MAX
#	define GEN_ISIZE_MIN GEN_S32_MIN
#	define GEN_ISIZE_MAX GEN_S32_MAX
#elif defined( GEN_ARCH_64_BIT )
#	define GEN_USIZE_MIN GEN_U64_MIN
#	define GEN_USIZE_MAX GEN_U64_MAX
#	define GEN_ISIZE_MIN GEN_I64_MIN
#	define GEN_ISIZE_MAX GEN_I64_MAX
#else
#	error Unknown architecture size. This library only supports 32 bit and 64 bit architectures.
#endif

#define GEN_F32_MIN 1.17549435e-38f
#define GEN_F32_MAX 3.40282347e+38f
#define GEN_F64_MIN 2.2250738585072014e-308
#define GEN_F64_MAX 1.7976931348623157e+308

#if defined( GEN_COMPILER_MSVC )
#	if _MSC_VER < 1300
typedef unsigned char  u8;
typedef signed   char  s8;
typedef unsigned short u16;
typedef signed   short s16;
typedef unsigned int   u32;
typedef signed   int   s32;
#    else
typedef unsigned __int8  u8;
typedef signed   __int8  s8;
typedef unsigned __int16 u16;
typedef signed   __int16 s16;
typedef unsigned __int32 u32;
typedef signed   __int32 s32;
#    endif
typedef unsigned __int64 u64;
typedef signed   __int64 s64;
#else
#	include <stdint.h>

typedef uint8_t  u8;
typedef int8_t   s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;
#endif

static_assert( sizeof( u8 )  == sizeof( s8 ),  "sizeof(u8) != sizeof(s8)" );
static_assert( sizeof( u16 ) == sizeof( s16 ), "sizeof(u16) != sizeof(s16)" );
static_assert( sizeof( u32 ) == sizeof( s32 ), "sizeof(u32) != sizeof(s32)" );
static_assert( sizeof( u64 ) == sizeof( s64 ), "sizeof(u64) != sizeof(s64)" );

static_assert( sizeof( u8 )  == 1, "sizeof(u8) != 1" );
static_assert( sizeof( u16 ) == 2, "sizeof(u16) != 2" );
static_assert( sizeof( u32 ) == 4, "sizeof(u32) != 4" );
static_assert( sizeof( u64 ) == 8, "sizeof(u64) != 8" );

typedef size_t    usize;
typedef ptrdiff_t ssize;

static_assert( sizeof( usize ) == sizeof( ssize ), "sizeof(usize) != sizeof(ssize)" );

// NOTE: (u)zpl_intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
#if defined( _WIN64 )
typedef signed __int64   sptr;
typedef unsigned __int64 uptr;
#elif defined( _WIN32 )
// NOTE; To mark types changing their size, e.g. zpl_intptr
#	ifndef _W64
#		if ! defined( __midl ) && ( defined( _X86_ ) || defined( _M_IX86 ) ) && _MSC_VER >= 1300
#			define _W64 __w64
#		else
#			define _W64
#		endif
#	endif
typedef _W64 signed int   sptr;
typedef _W64 unsigned int uptr;
#else
typedef uintptr_t uptr;
typedef intptr_t  sptr;
#endif

static_assert( sizeof( uptr ) == sizeof( sptr ), "sizeof(uptr) != sizeof(sptr)" );

typedef float  f32;
typedef double f64;

static_assert( sizeof( f32 ) == 4, "sizeof(f32) != 4" );
static_assert( sizeof( f64 ) == 8, "sizeof(f64) != 8" );

typedef s8  b8;
typedef s16 b16;
typedef s32 b32;

using mem_ptr       = void*;
using mem_ptr_const = void const*;

template<typename Type> uptr to_uptr( Type* ptr ) { return (uptr)ptr; }
template<typename Type> sptr to_sptr( Type* ptr ) { return (sptr)ptr; }

template<typename Type> mem_ptr       to_mem_ptr      ( Type ptr ) { return (mem_ptr)      ptr; }
template<typename Type> mem_ptr_const to_mem_ptr_const( Type ptr ) { return (mem_ptr_const)ptr; }

#pragma endregion Basic Types

#pragma region Debug

#if defined( _MSC_VER )
#	if _MSC_VER < 1300
#		define GEN_DEBUG_TRAP() __asm int 3 /* Trap to debugger! */
#	else
#		define GEN_DEBUG_TRAP() __debugbreak()
#	endif
#elif defined( GEN_COMPILER_TINYC )
#	define GEN_DEBUG_TRAP() process_exit( 1 )
#else
#	define GEN_DEBUG_TRAP() __builtin_trap()
#endif

#define GEN_ASSERT( cond ) GEN_ASSERT_MSG( cond, NULL )

#define GEN_ASSERT_MSG( cond, msg, ... )                                                     \
	do                                                                                       \
	{                                                                                        \
		if ( ! ( cond ) )                                                                    \
		{                                                                                    \
			assert_handler( #cond, __FILE__, scast( s64, __LINE__ ), msg, ##__VA_ARGS__ ); \
			GEN_DEBUG_TRAP();                                                                \
		}                                                                                    \
	} while ( 0 )

#define GEN_ASSERT_NOT_NULL( ptr ) GEN_ASSERT_MSG( ( ptr ) != NULL, #ptr " must not be NULL" )

// NOTE: Things that shouldn't happen with a message!
#define GEN_PANIC( msg, ... ) GEN_ASSERT_MSG( 0, msg, ##__VA_ARGS__ )

#if Build_Debug
	#define GEN_FATAL( ... )                               \
	do                                                     \
	{                                                      \
		local_persist thread_local                         \
		char buf[GEN_PRINTF_MAXLEN] = { 0 };               \
		                                                   \
		str_fmt(buf, GEN_PRINTF_MAXLEN, __VA_ARGS__);      \
		GEN_PANIC(buf);                                    \
	}                                                      \
	while (0)
#else

#	define GEN_FATAL( ... )                  \
	do                                       \
	{                                        \
		str_fmt_out_err( __VA_ARGS__ );      \
		process_exit(1);                     \
	}                                        \
	while (0)
#endif

void assert_handler( char const* condition, char const* file, s32 line, char const* msg, ... );
s32  assert_crash( char const* condition );
void process_exit( u32 code );

#pragma endregion Debug

#pragma region Memory

#define kilobytes( x ) ( ( x ) * ( s64 )( 1024 ) )
#define megabytes( x ) ( kilobytes( x ) * ( s64 )( 1024 ) )
#define gigabytes( x ) ( megabytes( x ) * ( s64 )( 1024 ) )
#define terabytes( x ) ( gigabytes( x ) * ( s64 )( 1024 ) )

#define GEN__ONES          ( scast( GEN_NS usize, - 1) / GEN_U8_MAX )
#define GEN__HIGHS         ( GEN__ONES * ( GEN_U8_MAX / 2 + 1 ) )
#define GEN__HAS_ZERO( x ) ( ( ( x ) - GEN__ONES ) & ~( x ) & GEN__HIGHS )

template< class Type >
void swap( Type& a, Type& b )
{
	Type tmp = a;
	a = b;
	b = tmp;
}

//! Checks if value is power of 2.
b32 is_power_of_two( ssize x );

//! Aligns address to specified alignment.
void* align_forward( void* ptr, ssize alignment );

//! Aligns value to a specified alignment.
s64 align_forward_i64( s64 value, ssize alignment );

//! Moves pointer forward by bytes.
void* pointer_add( void* ptr, ssize bytes );

//! Moves pointer forward by bytes.
void const* pointer_add_const( void const* ptr, ssize bytes );

//! Calculates difference between two addresses.
ssize pointer_diff( void const* begin, void const* end );

//! Copy non-overlapping memory from source to destination.
void* mem_copy( void* dest, void const* source, ssize size );

//! Search for a constant value within the size limit at memory location.
void const* mem_find( void const* data, u8 byte_value, ssize size );

//! Copy memory from source to destination.
void* mem_move( void* dest, void const* source, ssize size );

//! Set constant value at memory location with specified size.
void* mem_set( void* data, u8 byte_value, ssize size );

//! @param ptr Memory location to clear up.
//! @param size The size to clear up with.
void zero_size( void* ptr, ssize size );

//! Clears up an item.
#define zero_item( t ) zero_size( ( t ), size_of( *( t ) ) )    // NOTE: Pass pointer of struct

//! Clears up an array.
#define zero_array( a, count ) zero_size( ( a ), size_of( *( a ) ) * count )

enum AllocType : u8
{
	EAllocation_ALLOC,
	EAllocation_FREE,
	EAllocation_FREE_ALL,
	EAllocation_RESIZE,
};

using AllocatorProc = void* ( void* allocator_data, AllocType type
	, ssize size, ssize alignment
	, void* old_memory, ssize old_size
	, u64 flags );

struct AllocatorInfo
{
	AllocatorProc* Proc;
	void*          Data;
};

enum AllocFlag
{
	ALLOCATOR_FLAG_CLEAR_TO_ZERO = bit( 0 ),
};

#ifndef GEN_DEFAULT_MEMORY_ALIGNMENT
#	define GEN_DEFAULT_MEMORY_ALIGNMENT ( 2 * size_of( void* ) )
#endif

#ifndef GEN_DEFAULT_ALLOCATOR_FLAGS
#	define GEN_DEFAULT_ALLOCATOR_FLAGS ( ALLOCATOR_FLAG_CLEAR_TO_ZERO )
#endif

//! Allocate memory with default alignment.
void* alloc( AllocatorInfo a, ssize size );

//! Allocate memory with specified alignment.
void* alloc_align( AllocatorInfo a, ssize size, ssize alignment );

//! Free allocated memory.
void free( AllocatorInfo a, void* ptr );

//! Free all memory allocated by an allocator.
void free_all( AllocatorInfo a );

//! Resize an allocated memory.
void* resize( AllocatorInfo a, void* ptr, ssize old_size, ssize new_size );

//! Resize an allocated memory with specified alignment.
void* resize_align( AllocatorInfo a, void* ptr, ssize old_size, ssize new_size, ssize alignment );

//! Allocate memory for an item.
#define alloc_item( allocator_, Type ) ( Type* )alloc( allocator_, size_of( Type ) )

//! Allocate memory for an array of items.
#define alloc_array( allocator_, Type, count ) ( Type* )alloc( allocator_, size_of( Type ) * ( count ) )

/* heap memory analysis tools */
/* define GEN_HEAP_ANALYSIS to enable this feature */
/* call zpl_heap_stats_init at the beginning of the entry point */
/* you can call zpl_heap_stats_check near the end of the execution to validate any possible leaks */
void  heap_stats_init( void );
ssize heap_stats_used_memory( void );
ssize heap_stats_alloc_count( void );
void  heap_stats_check( void );

//! Allocate/Resize memory using default options.

//! Use this if you don't need a "fancy" resize allocation
void* default_resize_align( AllocatorInfo a, void* ptr, ssize old_size, ssize new_size, ssize alignment );

void* heap_allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags );

//! The heap allocator backed by operating system's memory manager.
constexpr AllocatorInfo heap( void ) { return { heap_allocator_proc, nullptr }; }

//! Helper to allocate memory using heap allocator.
#define malloc( sz ) alloc( heap(), sz )

//! Helper to free memory allocated by heap allocator.
#define mfree( ptr ) free( heap(), ptr )

struct VirtualMemory
{
	void*  data;
	ssize size;
};

//! Initialize virtual memory from existing data.
VirtualMemory vm_from_memory( void* data, ssize size );

//! Allocate virtual memory at address with size.

//! @param addr The starting address of the region to reserve. If NULL, it lets operating system to decide where to allocate it.
//! @param size The size to serve.
VirtualMemory vm_alloc( void* addr, ssize size );

//! Release the virtual memory.
b32 vm_free( VirtualMemory vm );

//! Trim virtual memory.
VirtualMemory vm_trim( VirtualMemory vm, ssize lead_size, ssize size );

//! Purge virtual memory.
b32 gen_vm_purge( VirtualMemory vm );

//! Retrieve VM's page size and alignment.
ssize gen_virtual_memory_page_size( ssize* alignment_out );

struct Arena
{
	static
	void* allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags );

	static
	Arena init_from_memory( void* start, ssize size )
	{
		return
		{
			{ nullptr, nullptr },
			start,
			size,
			0,
			0
		};
	}

	static
	Arena init_from_allocator( AllocatorInfo backing, ssize size )
	{
		Arena result =
		{
		backing,
		alloc( backing, size),
		size,
		0,
		0
		};
		return result;
	}

	static
	Arena init_sub( Arena& parent, ssize size )
	{
		return init_from_allocator( parent.Backing, size );
	}

	ssize alignment_of( ssize alignment )
	{
		ssize alignment_offset, result_pointer, mask;
		GEN_ASSERT( is_power_of_two( alignment ) );

		alignment_offset = 0;
		result_pointer   = (ssize) PhysicalStart + TotalUsed;
		mask             = alignment - 1;

		if ( result_pointer & mask )
			alignment_offset = alignment - ( result_pointer & mask );

		return alignment_offset;
	}

// This id is defined by Unreal for asserts
#pragma push_macro("check")
#undef check
	void check()
	{
		GEN_ASSERT( TempCount == 0 );
	}
#pragma pop_macro("check")

	void free()
	{
		if ( Backing.Proc )
		{
			gen::free( Backing, PhysicalStart );
			PhysicalStart = nullptr;
		}
	}

	ssize size_remaining( ssize alignment )
	{
		ssize result = TotalSize - ( TotalUsed + alignment_of( alignment ) );
		return result;
	}

	AllocatorInfo Backing;
	void*         PhysicalStart;
	ssize            TotalSize;
	ssize            TotalUsed;
	ssize            TempCount;

	operator AllocatorInfo()
	{
		return { allocator_proc, this };
	}
};

// Just a wrapper around using an arena with memory associated with its scope instead of from an allocator.
// Used for static segment or stack allocations.
template< s32 Size >
struct FixedArena
{
	static
	FixedArena init()
	{
		FixedArena result = { Arena::init_from_memory( result.memory, Size ), {0} };
		return result;
	}

	ssize size_remaining( ssize alignment )
	{
		return arena.size_remaining( alignment );
	}

	operator AllocatorInfo()
	{
		return { Arena::allocator_proc, &arena };
	}

	Arena arena;
	char  memory[ Size ];
};

using Arena_1KB   = FixedArena< kilobytes( 1 ) >;
using Arena_4KB   = FixedArena< kilobytes( 4 ) >;
using Arena_8KB   = FixedArena< kilobytes( 8 ) >;
using Arena_16KB  = FixedArena< kilobytes( 16 ) >;
using Arena_32KB  = FixedArena< kilobytes( 32 ) >;
using Arena_64KB  = FixedArena< kilobytes( 64 ) >;
using Arena_128KB = FixedArena< kilobytes( 128 ) >;
using Arena_256KB = FixedArena< kilobytes( 256 ) >;
using Arena_512KB = FixedArena< kilobytes( 512 ) >;
using Arena_1MB   = FixedArena< megabytes( 1 ) >;
using Arena_2MB   = FixedArena< megabytes( 2 ) >;
using Arena_4MB   = FixedArena< megabytes( 4 ) >;

struct Pool
{
	static
	void* allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags );

	static
	Pool init( AllocatorInfo backing, ssize num_blocks, ssize block_size )
	{
		return init_align( backing, num_blocks, block_size, GEN_DEFAULT_MEMORY_ALIGNMENT );
	}

	static
	Pool init_align( AllocatorInfo backing, ssize num_blocks, ssize block_size, ssize block_align );

	void clear();

	void free()
	{
		if ( Backing.Proc )
		{
			gen::free( Backing, PhysicalStart );
		}
	}

	AllocatorInfo Backing;
	void*         PhysicalStart;
	void*         FreeList;
	ssize         BlockSize;
	ssize         BlockAlign;
	ssize         TotalSize;
	ssize         NumBlocks;

	operator AllocatorInfo()
	{
		return { allocator_proc, this };
	}
};


inline
b32 is_power_of_two( ssize x ) {
	if ( x <= 0 )
		return false;
	return ! ( x & ( x - 1 ) );
}

inline
mem_ptr align_forward( void* ptr, ssize alignment )
{
	GEN_ASSERT( is_power_of_two( alignment ) );
	uptr p       = to_uptr(ptr);
	uptr forward = (p + ( alignment - 1 ) ) & ~( alignment - 1 );

	return to_mem_ptr(forward);
}

inline s64 align_forward_i64( s64 value, ssize alignment ) { return value + ( alignment - value % alignment ) % alignment; }

inline void*       pointer_add      ( void*       ptr, ssize bytes ) { return rcast(void*,       rcast( u8*,        ptr) + bytes ); }
inline void const* pointer_add_const( void const* ptr, ssize bytes ) { return rcast(void const*, rcast( u8 const*,  ptr) + bytes ); }

inline sptr pointer_diff( mem_ptr_const begin, mem_ptr_const end ) {
	return scast( ssize, rcast( u8 const*, end) - rcast(u8 const*, begin) );
}

inline
void* mem_move( void* destination, void const* source, ssize byte_count )
{
	if ( destination == NULL )
	{
		return NULL;
	}

	u8*       dest_ptr = rcast( u8*, destination);
	u8 const* src_ptr  = rcast( u8 const*, source);

	if ( dest_ptr == src_ptr )
		return dest_ptr;

	if ( src_ptr + byte_count <= dest_ptr || dest_ptr + byte_count <= src_ptr )    // NOTE: Non-overlapping
		return mem_copy( dest_ptr, src_ptr, byte_count );

	if ( dest_ptr < src_ptr )
	{
		if ( to_uptr(src_ptr) % size_of( ssize ) == to_uptr(dest_ptr) % size_of( ssize ) )
		{
			while ( pcast( uptr, dest_ptr) % size_of( ssize ) )
			{
				if ( ! byte_count-- )
					return destination;

				*dest_ptr++ = *src_ptr++;
			}
			while ( byte_count >= size_of( ssize ) )
			{
				* rcast(ssize*, dest_ptr)  = * rcast(ssize const*, src_ptr);
				byte_count -= size_of( ssize );
				dest_ptr   += size_of( ssize );
				src_ptr    += size_of( ssize );
			}
		}
		for ( ; byte_count; byte_count-- )
			*dest_ptr++ = *src_ptr++;
	}
	else
	{
		if ( ( to_uptr(src_ptr) % size_of( ssize ) ) == ( to_uptr(dest_ptr) % size_of( ssize ) ) )
		{
			while ( to_uptr( dest_ptr + byte_count ) % size_of( ssize ) )
			{
				if ( ! byte_count-- )
					return destination;

				dest_ptr[ byte_count ] = src_ptr[ byte_count ];
			}
			while ( byte_count >= size_of( ssize ) )
			{
				byte_count                              -= size_of( ssize );
				* rcast(ssize*, dest_ptr + byte_count )  = * rcast( ssize const*, src_ptr + byte_count );
			}
		}
		while ( byte_count )
			byte_count--, dest_ptr[ byte_count ] = src_ptr[ byte_count ];
	}

	return destination;
}

inline
void* mem_set( void* destination, u8 fill_byte, ssize byte_count )
{
	if ( destination == NULL )
	{
		return NULL;
	}

	ssize align_offset;
	u8*   dest_ptr  = rcast( u8*, destination);
	u32   fill_word = ( ( u32 )-1 ) / 255 * fill_byte;

	if ( byte_count == 0 )
		return destination;

	dest_ptr[ 0 ] = dest_ptr[ byte_count - 1 ] = fill_byte;
	if ( byte_count < 3 )
		return destination;

	dest_ptr[ 1 ] = dest_ptr[ byte_count - 2 ] = fill_byte;
	dest_ptr[ 2 ] = dest_ptr[ byte_count - 3 ] = fill_byte;
	if ( byte_count < 7 )
		return destination;

	dest_ptr[ 3 ] = dest_ptr[ byte_count - 4 ] = fill_byte;
	if ( byte_count < 9 )
		return destination;

	align_offset  = -to_sptr( dest_ptr ) & 3;
	dest_ptr     += align_offset;
	byte_count   -= align_offset;
	byte_count   &= -4;

	* rcast( u32*, ( dest_ptr + 0              ) ) = fill_word;
	* rcast( u32*, ( dest_ptr + byte_count - 4 ) ) = fill_word;
	if ( byte_count < 9 )
		return destination;

	* rcast( u32*, dest_ptr + 4 )               = fill_word;
	* rcast( u32*, dest_ptr + 8 )               = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 12 ) = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 8 )  = fill_word;
	if ( byte_count < 25 )
		return destination;

	* rcast( u32*, dest_ptr + 12 )              = fill_word;
	* rcast( u32*, dest_ptr + 16 )              = fill_word;
	* rcast( u32*, dest_ptr + 20 )              = fill_word;
	* rcast( u32*, dest_ptr + 24 )              = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 28 ) = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 24 ) = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 20 ) = fill_word;
	* rcast( u32*, dest_ptr + byte_count - 16 ) = fill_word;

	align_offset  = 24 + to_uptr( dest_ptr ) & 4;
	dest_ptr     += align_offset;
	byte_count   -= align_offset;

	{
		u64 fill_doubleword = ( scast( u64, fill_word) << 32 ) | fill_word;
		while ( byte_count > 31 )
		{
			* rcast( u64*, dest_ptr + 0 )  = fill_doubleword;
			* rcast( u64*, dest_ptr + 8 )  = fill_doubleword;
			* rcast( u64*, dest_ptr + 16 ) = fill_doubleword;
			* rcast( u64*, dest_ptr + 24 ) = fill_doubleword;

			byte_count -= 32;
			dest_ptr += 32;
		}
	}

	return destination;
}

inline
void* alloc_align( AllocatorInfo a, ssize size, ssize alignment ) {
	return a.Proc( a.Data, EAllocation_ALLOC, size, alignment, nullptr, 0, GEN_DEFAULT_ALLOCATOR_FLAGS );
}

inline
void* alloc( AllocatorInfo a, ssize size ) {
	return alloc_align( a, size, GEN_DEFAULT_MEMORY_ALIGNMENT );
}

inline
void free( AllocatorInfo a, void* ptr ) {
	if ( ptr != nullptr )
		a.Proc( a.Data, EAllocation_FREE, 0, 0, ptr, 0, GEN_DEFAULT_ALLOCATOR_FLAGS );
}

inline
void free_all( AllocatorInfo a ) {
	a.Proc( a.Data, EAllocation_FREE_ALL, 0, 0, nullptr, 0, GEN_DEFAULT_ALLOCATOR_FLAGS );
}

inline
void* resize( AllocatorInfo a, void* ptr, ssize old_size, ssize new_size ) {
	return resize_align( a, ptr, old_size, new_size, GEN_DEFAULT_MEMORY_ALIGNMENT );
}

inline
void* resize_align( AllocatorInfo a, void* ptr, ssize old_size, ssize new_size, ssize alignment ) {
	return a.Proc( a.Data, EAllocation_RESIZE, new_size, alignment, ptr, old_size, GEN_DEFAULT_ALLOCATOR_FLAGS );
}

inline
void* default_resize_align( AllocatorInfo a, void* old_memory, ssize old_size, ssize new_size, ssize alignment )
{
	if ( ! old_memory )
		return alloc_align( a, new_size, alignment );

	if ( new_size == 0 )
	{
		free( a, old_memory );
		return nullptr;
	}

	if ( new_size < old_size )
		new_size = old_size;

	if ( old_size == new_size )
	{
		return old_memory;
	}
	else
	{
		void*  new_memory = alloc_align( a, new_size, alignment );
		if ( ! new_memory )
			return nullptr;

		mem_move( new_memory, old_memory, min( new_size, old_size ) );
		free( a, old_memory );
		return new_memory;
	}
}

inline
void zero_size( void* ptr, ssize size ) {
	mem_set( ptr, 0, size );
}

#pragma endregion Memory

#pragma region String Ops

const char* char_first_occurence( const char* str, char c );
constexpr auto str_find = &char_first_occurence;

b32   char_is_alpha( char c );
b32   char_is_alphanumeric( char c );
b32   char_is_digit( char c );
b32   char_is_hex_digit( char c );
b32   char_is_space( char c );
char  char_to_lower( char c );
char  char_to_upper( char c );

s32  digit_to_int( char c );
s32  hex_digit_to_int( char c );

s32         str_compare( const char* s1, const char* s2 );
s32         str_compare( const char* s1, const char* s2, ssize len );
char*       str_copy( char* dest, const char* source, ssize len );
ssize       str_copy_nulpad( char* dest, const char* source, ssize len );
ssize       str_len( const char* str );
ssize       str_len( const char* str, ssize max_len );
char*       str_reverse( char* str );    // NOTE: ASCII only
char const* str_skip( char const* str, char c );
char const* str_skip_any( char const* str, char const* char_list );
char const* str_trim( char const* str, b32 catch_newline );

// NOTE: ASCII only
void str_to_lower( char* str );
void str_to_upper( char* str );

s64  str_to_i64( const char* str, char** end_ptr, s32 base );
void i64_to_str( s64 value, char* string, s32 base );
void u64_to_str( u64 value, char* string, s32 base );
f64  str_to_f64( const char* str, char** end_ptr );

inline
const char* char_first_occurence( const char* s, char c )
{
	char ch = c;
	for ( ; *s != ch; s++ )
	{
		if ( *s == '\0' )
			return NULL;
	}
	return s;
}

inline
b32 char_is_alpha( char c )
{
	if ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) )
		return true;
	return false;
}

inline
b32 char_is_alphanumeric( char c )
{
	return char_is_alpha( c ) || char_is_digit( c );
}

inline
b32 char_is_digit( char c )
{
	if ( c >= '0' && c <= '9' )
		return true;
	return false;
}

inline
b32 char_is_hex_digit( char c )
{
	if ( char_is_digit( c ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ) )
		return true;
	return false;
}

inline
b32 char_is_space( char c )
{
	if ( c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v' )
		return true;
	return false;
}

inline
char char_to_lower( char c )
{
	if ( c >= 'A' && c <= 'Z' )
		return 'a' + ( c - 'A' );
	return c;
}

inline char char_to_upper( char c )
{
	if ( c >= 'a' && c <= 'z' )
		return 'A' + ( c - 'a' );
	return c;
}

inline
s32 digit_to_int( char c )
{
	return char_is_digit( c ) ? c - '0' : c - 'W';
}

inline
s32 hex_digit_to_int( char c )
{
	if ( char_is_digit( c ) )
		return digit_to_int( c );
	else if ( is_between( c, 'a', 'f' ) )
		return c - 'a' + 10;
	else if ( is_between( c, 'A', 'F' ) )
		return c - 'A' + 10;
	return -1;
}

inline
s32 str_compare( const char* s1, const char* s2 )
{
	while ( *s1 && ( *s1 == *s2 ) )
	{
		s1++, s2++;
	}
	return *( u8* )s1 - *( u8* )s2;
}

inline
s32 str_compare( const char* s1, const char* s2, ssize len )
{
	for ( ; len > 0; s1++, s2++, len-- )
	{
		if ( *s1 != *s2 )
			return ( ( s1 < s2 ) ? -1 : +1 );
		else if ( *s1 == '\0' )
			return 0;
	}
	return 0;
}

inline
char* str_copy( char* dest, const char* source, ssize len )
{
	GEN_ASSERT_NOT_NULL( dest );
	if ( source )
	{
		char* str = dest;
		while ( len > 0 && *source )
		{
			*str++ = *source++;
			len--;
		}
		while ( len > 0 )
		{
			*str++ = '\0';
			len--;
		}
	}
	return dest;
}

inline
ssize str_copy_nulpad( char* dest, const char* source, ssize len )
{
	ssize result = 0;
	GEN_ASSERT_NOT_NULL( dest );
	if ( source )
	{
		const char* source_start = source;
		char*       str          = dest;
		while ( len > 0 && *source )
		{
			*str++ = *source++;
			len--;
		}
		while ( len > 0 )
		{
			*str++ = '\0';
			len--;
		}

		result = source - source_start;
	}
	return result;
}

inline
ssize str_len( const char* str )
{
	if ( str == NULL )
	{
		return 0;
	}
	const char* p = str;
	while ( *str )
		str++;
	return str - p;
}

inline
ssize str_len( const char* str, ssize max_len )
{
	const char* end = rcast(const char*, mem_find( str, 0, max_len ));
	if ( end )
		return end - str;
	return max_len;
}

inline
char* str_reverse( char* str )
{
	ssize    len  = str_len( str );
	char* a    = str + 0;
	char* b    = str + len - 1;
	len       /= 2;
	while ( len-- )
	{
		swap( *a, *b );
		a++, b--;
	}
	return str;
}

inline
char const* str_skip( char const* str, char c )
{
	while ( *str && *str != c )
	{
		++str;
	}
	return str;
}

inline
char const* str_skip_any( char const* str, char const* char_list )
{
	char const* closest_ptr     = rcast( char const*, pointer_add_const( rcast(void const*, str), str_len( str ) ));
	ssize       char_list_count = str_len( char_list );
	for ( ssize i = 0; i < char_list_count; i++ )
	{
		char const* p = str_skip( str, char_list[ i ] );
		closest_ptr   = min( closest_ptr, p );
	}
	return closest_ptr;
}

inline
char const* str_trim( char const* str, b32 catch_newline )
{
	while ( *str && char_is_space( *str ) && ( ! catch_newline || ( catch_newline && *str != '\n' ) ) )
	{
		++str;
	}
	return str;
}

inline
void str_to_lower( char* str )
{
	if ( ! str )
		return;
	while ( *str )
	{
		*str = char_to_lower( *str );
		str++;
	}
}

inline
void str_to_upper( char* str )
{
	if ( ! str )
		return;
	while ( *str )
	{
		*str = char_to_upper( *str );
		str++;
	}
}

#pragma endregion String Ops

#pragma region Printing

struct FileInfo;

#ifndef GEN_PRINTF_MAXLEN
#	define GEN_PRINTF_MAXLEN kilobytes(128)
#endif

// NOTE: A locally persisting buffer is used internally
char*  str_fmt_buf       ( char const* fmt, ... );
char*  str_fmt_buf_va    ( char const* fmt, va_list va );
ssize  str_fmt           ( char* str, ssize n, char const* fmt, ... );
ssize  str_fmt_va        ( char* str, ssize n, char const* fmt, va_list va );
ssize  str_fmt_out_va    ( char const* fmt, va_list va );
ssize  str_fmt_out_err   ( char const* fmt, ... );
ssize  str_fmt_out_err_va( char const* fmt, va_list va );
ssize  str_fmt_file      ( FileInfo* f, char const* fmt, ... );
ssize  str_fmt_file_va   ( FileInfo* f, char const* fmt, va_list va );

constexpr
char const* Msg_Invalid_Value = "INVALID VALUE PROVIDED";

inline
ssize log_fmt(char const* fmt, ...)
{
	ssize res;
	va_list va;

	va_start(va, fmt);
	res = str_fmt_out_va(fmt, va);
	va_end(va);

	return res;
}

#pragma endregion Printing

#pragma region Containers

template<class TType>             struct RemoveConst                    { typedef TType Type;       };
template<class TType>             struct RemoveConst<const TType>       { typedef TType Type;       };
template<class TType>             struct RemoveConst<const TType[]>     { typedef TType Type[];     };
template<class TType, usize Size> struct RemoveConst<const TType[Size]> { typedef TType Type[Size]; };

template<class TType>
using TRemoveConst = typename RemoveConst<TType>::Type;

template<class Type>
struct Array
{
	struct Header
	{
		AllocatorInfo Allocator;
		usize            Capacity;
		usize            Num;
	};

	static
	Array init( AllocatorInfo allocator )
	{
		return init_reserve( allocator, grow_formula(0) );
	}

	static
	Array init_reserve( AllocatorInfo allocator, ssize capacity )
	{
		Header* header = rcast( Header*, alloc( allocator, sizeof(Header) + sizeof(Type) * capacity ));

		if ( header == nullptr )
			return { nullptr };

		header->Allocator = allocator;
		header->Capacity  = capacity;
		header->Num       = 0;

		return { rcast( Type*, header + 1) };
	}

	static
	usize grow_formula( usize value )
	{
		return 2 * value + 8;
	}

	bool append( Array other )
	{
		return append( other, other.num() );
	}

	bool append( Type value )
	{
		Header* header = get_header();

		if ( header->Num == header->Capacity )
		{
			if ( ! grow( header->Capacity ))
				return false;

			header = get_header();
		}

		Data[ header->Num ] = value;
		header->Num++;

		return true;
	}

	bool append( Type* items, usize item_num )
	{
		Header* header = get_header();

		if ( header->Num + item_num > header->Capacity )
		{
			if ( ! grow( header->Capacity + item_num ))
				return false;

			header = get_header();
		}

		mem_copy( Data + header->Num, items, item_num * sizeof(Type) );
		header->Num += item_num;

		return true;
	}

	bool append_at( Type item, usize idx )
	{
		Header* header = get_header();

		if ( idx >= header->Num )
			idx = header->Num - 1;

		if ( idx < 0 )
			idx = 0;

		if ( header->Capacity < header->Num + 1 )
		{
			if ( ! grow( header->Capacity + 1 ))
				return false;

			header = get_header();
		}

		Type* target = Data + idx;

		mem_move( target + 1, target, (header->Num - idx) * sizeof(Type) );
		header->Num++;

		return true;
	}

	bool append_at( Type* items, usize item_num, usize idx )
	{
		Header* header = get_header();

		if ( idx >= header->Num )
		{
			return append( items, item_num );
		}

		if ( item_num > header->Capacity )
		{
			if ( ! grow( header->Capacity + item_num ) )
				return false;

			header = get_header();
		}

		Type* target = Data + idx + item_num;
		Type* src    = Data + idx;

		mem_move( target, src, (header->Num - idx) * sizeof(Type) );
		mem_copy( src, items, item_num * sizeof(Type) );
		header->Num += item_num;

		return true;
	}

	Type& back( void )
	{
		Header& header = * get_header();
		return Data[ header.Num - 1 ];
	}

	void clear( void )
	{
		Header& header = * get_header();
		header.Num     = 0;
	}

	bool fill( usize begin, usize end, Type value )
	{
		Header& header = * get_header();

		if ( begin < 0 || end > header.Num )
			return false;

		for ( ssize idx = ssize(begin); idx < ssize(end); idx++ )
		{
			Data[ idx ] = value;
		}

		return true;
	}

	void free( void )
	{
		Header& header = * get_header();
		gen::free( header.Allocator, &header );
		Data = nullptr;
	}

	Header* get_header( void )
	{
		using NonConstType = TRemoveConst< Type >;
		return rcast( Header*, const_cast<NonConstType*>(Data) ) - 1 ;
	}

	bool grow( usize min_capacity )
	{
		Header& header       = * get_header();
		usize      new_capacity = grow_formula( header.Capacity );

		if ( new_capacity < min_capacity )
			new_capacity = min_capacity;

		return set_capacity( new_capacity );
	}

	usize num( void )
	{
		return get_header()->Num;
	}

	void pop( void )
	{
		Header& header = * get_header();

		GEN_ASSERT( header.Num > 0 );
		header.Num--;
	}

	void remove_at( usize idx )
	{
		Header* header = get_header();
		GEN_ASSERT( idx < header->Num );

		mem_move( header + idx, header + idx + 1, sizeof( Type ) * ( header->Num - idx - 1 ) );
		header->Num--;
	}

	bool reserve( usize new_capacity )
	{
		Header& header = * get_header();

		if ( header.Capacity < new_capacity )
			return set_capacity( new_capacity );

		return true;
	}

	bool resize( usize num )
	{
		Header* header = get_header();

		if ( header->Capacity < num )
		{
			if ( ! grow( num ) )
				return false;

			header = get_header();
		}

		header->Num = num;
		return true;
	}

	bool set_capacity( usize new_capacity )
	{
		Header& header = * get_header();

		if ( new_capacity == header.Capacity )
			return true;

		if ( new_capacity < header.Num )
		{
			// Already have the memory, mine as well keep it.
			header.Num = new_capacity;
			return true;
		}

		ssize      size       = sizeof( Header ) + sizeof( Type ) * new_capacity;
		Header* new_header = rcast( Header*, alloc( header.Allocator, size ) );

		if ( new_header == nullptr )
			return false;

		mem_move( new_header, &header, sizeof( Header ) + sizeof( Type ) * header.Num );

		new_header->Capacity = new_capacity;

		gen::free( header.Allocator, &header );

		Data = rcast( Type*, new_header + 1);
		return true;
	}

	Type* Data;

	operator Type*()
	{
		return Data;
	}

	operator Type const*() const
	{
		return Data;
	}

	// For-range based support

	Type* begin()
	{
		return Data;
	}

	Type* end()
	{
		return Data + get_header()->Num;
	}
};

// TODO(Ed) : This thing needs ALOT of work.

template<typename Type>
struct HashTable
{
	struct FindResult
	{
		ssize HashIndex;
		ssize PrevIndex;
		ssize EntryIndex;
	};

	struct Entry
	{
		u64  Key;
		ssize   Next;
		Type Value;
	};

	static constexpr f32 CriticalLoadScale = 0.7f;

	static
	HashTable init( AllocatorInfo allocator )
	{
		HashTable<Type> result = init_reserve(allocator, 8);
		return result;
	}

	static
	HashTable init_reserve( AllocatorInfo allocator, usize num )
	{
		HashTable<Type> result = { { nullptr }, { nullptr } };

		result.Hashes  = Array<ssize>::init_reserve( allocator, num );
		result.Hashes.get_header()->Num = num;
		result.Hashes.resize( num );
		result.Hashes.fill( 0, num, -1);

		result.Entries = Array<Entry>::init_reserve( allocator, num );
		return result;
	}

	void clear( void )
	{
		Entries.clear();
		Hashes.fill( 0, Hashes.num(), -1);
	}

	void destroy( void )
	{
		if ( Hashes && Hashes.get_header()->Capacity )
		{
			Hashes.free();
			Entries.free();
		}
	}

	Type* get( u64 key )
	{
		ssize idx = find( key ).EntryIndex;
		if ( idx >= 0 )
			return & Entries[ idx ].Value;

		return nullptr;
	}

	using MapProc = void (*)( u64 key, Type  value );

	void map( MapProc map_proc )
	{
		GEN_ASSERT_NOT_NULL( map_proc );

		for ( ssize idx = 0; idx < ssize(Entries.num()); ++idx )
		{
			map_proc( Entries[ idx ].Key, Entries[ idx ].Value );
		}
	}

	using MapMutProc = void (*)( u64 key, Type* value );

	void map_mut( MapMutProc map_proc )
	{
		GEN_ASSERT_NOT_NULL( map_proc );

		for ( ssize idx = 0; idx < ssize(Entries.num()); ++idx )
		{
			map_proc( Entries[ idx ].Key, & Entries[ idx ].Value );
		}
	}

	void grow()
	{
		ssize new_num = Array<Entry>::grow_formula( Entries.num() );
		rehash( new_num );
	}

	void rehash( ssize new_num )
	{
		ssize last_added_index;

		HashTable<Type> new_ht = init_reserve( Hashes.get_header()->Allocator, new_num );
		for ( ssize idx = 0; idx < ssize(Entries.num()); ++idx )
		{
			FindResult find_result;

			Entry& entry     = Entries[ idx ];
			find_result      = new_ht.find( entry.Key );
			last_added_index = new_ht.add_entry( entry.Key );

			if ( find_result.PrevIndex < 0 )
				new_ht.Hashes[ find_result.HashIndex ] = last_added_index;
			else
				new_ht.Entries[ find_result.PrevIndex ].Next = last_added_index;

			new_ht.Entries[ last_added_index ].Next  = find_result.EntryIndex;
			new_ht.Entries[ last_added_index ].Value = entry.Value;
		}

		destroy();
		*this = new_ht;
	}

	void rehash_fast()
	{
		ssize idx;

		for ( idx = 0; idx < ssize(Entries.num()); idx++ )
			Entries[ idx ].Next = -1;

		for ( idx = 0; idx < ssize(Hashes.num()); idx++ )
			Hashes[ idx ] = -1;

		for ( idx = 0; idx < ssize(Entries.num()); idx++ )
		{
			Entry*     entry;
			FindResult find_result;

			entry       = & Entries[ idx ];
			find_result = find( entry->Key );

			if ( find_result.PrevIndex < 0 )
				Hashes[ find_result.HashIndex ] = idx;
			else
				Entries[ find_result.PrevIndex ].Next = idx;
		}
	}

	void remove( u64 key )
	{
		FindResult find_result = find( key);

		if ( find_result.EntryIndex >= 0 )
		{
			Entries.remove_at( find_result.EntryIndex );
			rehash_fast();
		}
	}

	void remove_entry( ssize idx )
	{
		Entries.remove_at( idx );
	}

	void set( u64 key, Type value )
	{
		ssize idx;
		FindResult find_result;

		if ( full() )
			grow();

		find_result = find( key );
		if ( find_result.EntryIndex >= 0 )
		{
			idx = find_result.EntryIndex;
		}
		else
		{
			idx = add_entry( key );

			if ( find_result.PrevIndex >= 0 )
			{
				Entries[ find_result.PrevIndex ].Next = idx;
			}
			else
			{
				Hashes[ find_result.HashIndex ] = idx;
			}
		}

		Entries[ idx ].Value = value;

		if ( full() )
			grow();
	}

	ssize slot( u64 key )
	{
		for ( ssize idx = 0; idx < ssize(Hashes.num()); ++idx )
			if ( Hashes[ idx ] == key )
				return idx;

		return -1;
	}

	Array< ssize>    Hashes;
	Array< Entry> Entries;

protected:

	ssize add_entry( u64 key )
	{
		ssize idx;
		Entry entry = { key, -1 };

		idx = Entries.num();
		Entries.append( entry );
		return idx;
	}

	FindResult find( u64 key )
	{
		FindResult result = { -1, -1, -1 };

		if ( Hashes.num() > 0 )
		{
			result.HashIndex    = key % Hashes.num();
			result.EntryIndex  = Hashes[ result.HashIndex ];

			while ( result.EntryIndex >= 0 )
			{
				if ( Entries[ result.EntryIndex ].Key == key )
					break;

				result.PrevIndex  = result.EntryIndex;
				result.EntryIndex = Entries[ result.EntryIndex ].Next;
			}
		}

		return result;
	}

	b32 full()
	{
		usize critical_load = usize( CriticalLoadScale * f32(Hashes.num()) );
		b32 result = Entries.num() > critical_load;
		return result;
	}
};

#pragma endregion Containers

#pragma region Hashing

u32 crc32( void const* data, ssize len );
u64 crc64( void const* data, ssize len );

#pragma endregion Hashing

#pragma region Strings

// Constant string with length.
struct StrC
{
	ssize          Len;
	char const* Ptr;

	operator char const* ()               const { return Ptr; }
	char const& operator[]( ssize index ) const { return Ptr[index]; }
};

#define cast_to_strc( str ) * rcast( StrC*, (str) - sizeof(ssize) )
#define txt( text )         StrC { sizeof( text ) - 1, ( text ) }

inline
StrC to_str( char const* str )
{
	return { str_len( str ), str };
}

// Dynamic String
// This is directly based off the ZPL string api.
// They used a header pattern
// I kept it for simplicty of porting but its not necessary to keep it that way.
struct String
{
	struct Header
	{
		AllocatorInfo Allocator;
		ssize            Capacity;
		ssize            Length;
	};

	static
	usize grow_formula( usize value )
	{
		// Using a very aggressive growth formula to reduce time mem_copying with recursive calls to append in this library.
		return 4 * value + 8;
	}

	static
	String make( AllocatorInfo allocator, char const* str )
	{
		ssize length = str ? str_len( str ) : 0;
		return make_length( allocator, str, length );
	}

	static
	String make( AllocatorInfo allocator, StrC str )
	{
		return make_length( allocator, str.Ptr, str.Len );
	}

	static
	String make_reserve( AllocatorInfo allocator, ssize capacity );

	static
	String make_length( AllocatorInfo allocator, char const* str, ssize length );

	static
	String fmt( AllocatorInfo allocator, char* buf, ssize buf_size, char const* fmt, ... );

	static
	String fmt_buf( AllocatorInfo allocator, char const* fmt, ... );

	static
	String join( AllocatorInfo allocator, char const** parts, ssize num_parts, char const* glue )
	{
		String result = make( allocator, "" );

		for ( ssize idx = 0; idx < num_parts; ++idx )
		{
			result.append( parts[ idx ] );

			if ( idx < num_parts - 1 )
				result.append( glue );
		}

		return result;
	}

	static
	bool are_equal( String lhs, String rhs )
	{
		if ( lhs.length() != rhs.length() )
			return false;

		for ( ssize idx = 0; idx < lhs.length(); ++idx )
			if ( lhs[ idx ] != rhs[ idx ] )
				return false;

		return true;
	}

	static
	bool are_equal( String lhs, StrC rhs )
	{
		if ( lhs.length() != (rhs.Len) )
			return false;

		for ( ssize idx = 0; idx < lhs.length(); ++idx )
			if ( lhs[idx] != rhs[idx] )
				return false;

		return true;
	}

	bool make_space_for( char const* str, ssize add_len );

	bool append( char c )
	{
		return append( & c, 1 );
	}

	bool append( char const* str )
	{
		return append( str, str_len( str ) );
	}

	bool append( char const* str, ssize length )
	{
		if ( sptr(str) > 0 )
		{
			ssize curr_len = this->length();

			if ( ! make_space_for( str, length ) )
				return false;

			Header& header = get_header();

			mem_copy( Data + curr_len, str, length );

			Data[ curr_len + length ] = '\0';

			header.Length = curr_len + length;
		}
		return str != nullptr;
	}

	bool append( StrC str)
	{
		return append( str.Ptr, str.Len );
	}

	bool append( const String other )
	{
		return append( other.Data, other.length() );
	}

	bool append_fmt( char const* fmt, ... );

	ssize avail_space() const
	{
		Header const&
		header = * rcast( Header const*, Data - sizeof( Header ));

		return header.Capacity - header.Length;
	}

	char& back()
	{
		return Data[ length() - 1 ];
	}

	bool contains(StrC substring) const
	{
		Header const& header = * rcast( Header const*, Data - sizeof( Header ));

		if (substring.Len > header.Length)
			return false;

		ssize main_len = header.Length;
		ssize sub_len  = substring.Len;

		for (ssize i = 0; i <= main_len - sub_len; ++i)
		{
			if (str_compare(Data + i, substring.Ptr, sub_len) == 0)
				return true;
		}

		return false;
	}

	bool contains(String const& substring) const
	{
		Header const& header = * rcast( Header const*, Data - sizeof( Header ));

		if (substring.length() > header.Length)
			return false;

		ssize main_len = header.Length;
		ssize sub_len  = substring.length();

		for (ssize i = 0; i <= main_len - sub_len; ++i)
		{
			if (str_compare(Data + i, substring.Data, sub_len) == 0)
				return true;
		}

		return false;
	}

	ssize capacity() const
	{
		Header const&
		header = * rcast( Header const*, Data - sizeof( Header ));

		return header.Capacity;
	}

	void clear()
	{
		get_header().Length = 0;
	}

	String duplicate( AllocatorInfo allocator ) const
	{
		return make_length( allocator, Data, length() );
	}

	void free()
	{
		if ( ! Data )
			return;

		Header& header = get_header();

		gen::free( header.Allocator, & header );
	}

	Header& get_header()
	{
		return *(Header*)(Data - sizeof(Header));
	}

	ssize length() const
	{
		Header const&
		header = * rcast( Header const*, Data - sizeof( Header ));

		return header.Length;
	}

	b32 starts_with( StrC substring ) const
	{
		if (substring.Len > length())
			return false;

		b32 result = str_compare(Data, substring.Ptr, substring.Len ) == 0;
		return result;
	}

	b32 starts_with( String substring ) const
	{
		if (substring.length() > length())
			return false;

		b32 result = str_compare(Data, substring, substring.length() - 1 ) == 0;
		return result;
	}

	void skip_line()
	{
	#define current (*scanner)
		char* scanner = Data;
		while ( current != '\r' && current != '\n' )
		{
			++ scanner;
		}

		s32 new_length = scanner - Data;

		if ( current == '\r' )
		{
			new_length += 1;
		}

		mem_move( Data, scanner, new_length );

		Header* header = & get_header();
		header->Length = new_length;
	#undef current
	}

	void strip_space()
	{
		char* write_pos = Data;
		char* read_pos  = Data;

		while ( * read_pos)
		{
			if ( ! char_is_space( *read_pos ))
			{
				*write_pos = *read_pos;
				write_pos++;
			}
			read_pos++;
		}

		write_pos[0] = '\0';  // Null-terminate the modified string

		// Update the length if needed
		get_header().Length = write_pos - Data;
	}

	void trim( char const* cut_set )
	{
		ssize len = 0;

		char* start_pos = Data;
		char* end_pos   = Data + length() - 1;

		while ( start_pos <= end_pos && char_first_occurence( cut_set, *start_pos ) )
			start_pos++;

		while ( end_pos > start_pos && char_first_occurence( cut_set, *end_pos ) )
			end_pos--;

		len = scast( ssize, ( start_pos > end_pos ) ? 0 : ( ( end_pos - start_pos ) + 1 ) );

		if ( Data != start_pos )
			mem_move( Data, start_pos, len );

		Data[ len ] = '\0';

		get_header().Length = len;
	}

	void trim_space()
	{
		return trim( " \t\r\n\v\f" );
	}

	// Debug function that provides a copy of the string with whitespace characters visualized.
	String visualize_whitespace() const
	{
		Header* header = (Header*)(Data - sizeof(Header));

		String result = make_reserve(header->Allocator, length() * 2); // Assume worst case for space requirements.

		for ( char c : *this )
		{
			switch ( c )
			{
				case ' ':
					result.append( txt("·") );
				break;
				case '\t':
					result.append( txt("→") );
				break;
				case '\n':
					result.append( txt("↵") );
				break;
				case '\r':
					result.append( txt("⏎") );
				break;
				case '\v':
					result.append( txt("⇕") );
				break;
				case '\f':
					result.append( txt("⌂") );
				break;
				default:
					result.append(c);
				break;
			}
		}

		return result;
	}

	// For-range support

	char* begin() const
	{
		return Data;
	}

	char* end() const
	{
		Header const&
		header = * rcast( Header const*, Data - sizeof( Header ));

		return Data + header.Length;
	}

	operator bool()
	{
		return Data != nullptr;
	}

	operator char* ()
	{
		return Data;
	}

	operator char const* () const
	{
		return Data;
	}

	operator StrC() const
	{
		return { length(), Data };
	}

	// Used with cached strings
	// Essentially makes the string a string view.
	String const& operator = ( String const& other ) const
	{
		if ( this == & other )
			return *this;

		String*
		this_ = ccast(String*, this);
		this_->Data = other.Data;

		return *this;
	}

	char& operator [] ( ssize index )
	{
		return Data[ index ];
	}

	char const& operator [] ( ssize index ) const
	{
		return Data[ index ];
	}

	char* Data;
};

struct String_POD
{
	char* Data;
};
static_assert( sizeof( String_POD ) == sizeof( String ), "String is not a POD" );

// Implements basic string interning. Data structure is based off the ZPL Hashtable.
using StringTable = HashTable<String const>;

// Represents strings cached with the string table.
// Should never be modified, if changed string is desired, cache_string( str ) another.
using StringCached = String const;

#pragma endregion Strings

#pragma region File Handling

typedef u32 FileMode;

enum FileModeFlag
{
	EFileMode_READ   = bit( 0 ),
	EFileMode_WRITE  = bit( 1 ),
	EFileMode_APPEND = bit( 2 ),
	EFileMode_RW     = bit( 3 ),
	GEN_FILE_MODES   = EFileMode_READ | EFileMode_WRITE | EFileMode_APPEND | EFileMode_RW,
};

// NOTE: Only used internally and for the file operations
enum SeekWhenceType
{
	ESeekWhence_BEGIN   = 0,
	ESeekWhence_CURRENT = 1,
	ESeekWhence_END     = 2,
};

enum FileError
{
	EFileError_NONE,
	EFileError_INVALID,
	EFileError_INVALID_FILENAME,
	EFileError_EXISTS,
	EFileError_NOT_EXISTS,
	EFileError_PERMISSION,
	EFileError_TRUNCATION_FAILURE,
	EFileError_NOT_EMPTY,
	EFileError_NAME_TOO_LONG,
	EFileError_UNKNOWN,
};

union FileDescriptor
{
	void* p;
	sptr  i;
	uptr  u;
};

typedef struct FileOperations FileOperations;

#define GEN_FILE_OPEN_PROC( name )     FileError name( FileDescriptor* fd, FileOperations* ops, FileMode mode, char const* filename )
#define GEN_FILE_READ_AT_PROC( name )  b32 name( FileDescriptor fd, void* buffer, ssize size, s64 offset, ssize* bytes_read, b32 stop_at_newline )
#define GEN_FILE_WRITE_AT_PROC( name ) b32 name( FileDescriptor fd, void const* buffer, ssize size, s64 offset, ssize* bytes_written )
#define GEN_FILE_SEEK_PROC( name )     b32 name( FileDescriptor fd, s64 offset, SeekWhenceType whence, s64* new_offset )
#define GEN_FILE_CLOSE_PROC( name )    void name( FileDescriptor fd )

typedef GEN_FILE_OPEN_PROC( file_open_proc );
typedef GEN_FILE_READ_AT_PROC( FileReadProc );
typedef GEN_FILE_WRITE_AT_PROC( FileWriteProc );
typedef GEN_FILE_SEEK_PROC( FileSeekProc );
typedef GEN_FILE_CLOSE_PROC( FileCloseProc );

struct FileOperations
{
	FileReadProc*  read_at;
	FileWriteProc* write_at;
	FileSeekProc*  seek;
	FileCloseProc* close;
};

extern FileOperations const default_file_operations;

typedef u64 FileTime;

enum DirType
{
	GEN_DIR_TYPE_FILE,
	GEN_DIR_TYPE_FOLDER,
	GEN_DIR_TYPE_UNKNOWN,
};

struct DirInfo;

struct DirEntry
{
	char const*     filename;
	struct DirInfo* dir_info;
	u8              type;
};

struct DirInfo
{
	char const* fullpath;
	DirEntry*   entries;    // zpl_array

	// Internals
	char** filenames;    // zpl_array
	String buf;
};

struct FileInfo
{
	FileOperations ops;
	FileDescriptor fd;
	b32            is_temp;

	char const* filename;
	FileTime    last_write_time;
	DirEntry*   dir;
};

enum FileStandardType
{
	EFileStandard_INPUT,
	EFileStandard_OUTPUT,
	EFileStandard_ERROR,

	EFileStandard_COUNT,
};

/**
	* Get standard file I/O.
	* @param  std Check zpl_file_standard_type
	* @return     File handle to standard I/O
	*/
FileInfo* file_get_standard( FileStandardType std );

/**
	* Closes the file
	* @param  file
	*/
FileError file_close( FileInfo* file );

/**
	* Returns the currently opened file's name
	* @param  file
	*/
inline
	char const* file_name( FileInfo* file )
{
	return file->filename ? file->filename : "";
}

/**
	* Opens a file
	* @param  file
	* @param  filename
	*/
FileError file_open( FileInfo* file, char const* filename );

/**
	* Opens a file using a specified mode
	* @param  file
	* @param  mode     Access mode to use
	* @param  filename
	*/
FileError file_open_mode( FileInfo* file, FileMode mode, char const* filename );

/**
	* Reads from a file
	* @param  file
	* @param  buffer Buffer to read to
	* @param  size   Size to read
	*/
b32 file_read( FileInfo* file, void* buffer, ssize size );

/**
	* Reads file at a specific offset
	* @param  file
	* @param  buffer     Buffer to read to
	* @param  size       Size to read
	* @param  offset     Offset to read from
	* @param  bytes_read How much data we've actually read
	*/
b32 file_read_at( FileInfo* file, void* buffer, ssize size, s64 offset );

/**
	* Reads file safely
	* @param  file
	* @param  buffer     Buffer to read to
	* @param  size       Size to read
	* @param  offset     Offset to read from
	* @param  bytes_read How much data we've actually read
	*/
b32 file_read_at_check( FileInfo* file, void* buffer, ssize size, s64 offset, ssize* bytes_read );

struct FileContents
{
	AllocatorInfo allocator;
	void*         data;
	ssize            size;
};

constexpr b32 zero_terminate    = true;
constexpr b32 no_zero_terminate = false;

/**
	* Reads the whole file contents
	* @param  a              Allocator to use
	* @param  zero_terminate End the read data with null terminator
	* @param  filepath       Path to the file
	* @return                File contents data
	*/
FileContents file_read_contents( AllocatorInfo a, b32 zero_terminate, char const* filepath );

/**
	* Returns a size of the file
	* @param  file
	* @return      File size
	*/
s64 file_size( FileInfo* file );

/**
	* Seeks the file cursor from the beginning of file to a specific position
	* @param  file
	* @param  offset Offset to seek to
	*/
s64 file_seek( FileInfo* file, s64 offset );

/**
	* Seeks the file cursor to the end of the file
	* @param  file
	*/
s64 file_seek_to_end( FileInfo* file );

/**
	* Returns the length from the beginning of the file we've read so far
	* @param  file
	* @return      Our current position in file
	*/
s64 file_tell( FileInfo* file );

/**
	* Writes to a file
	* @param  file
	* @param  buffer Buffer to read from
	* @param  size   Size to read
	*/
b32 file_write( FileInfo* file, void const* buffer, ssize size );

/**
	* Writes to file at a specific offset
	* @param  file
	* @param  buffer        Buffer to read from
	* @param  size          Size to write
	* @param  offset        Offset to write to
	* @param  bytes_written How much data we've actually written
	*/
b32 file_write_at( FileInfo* file, void const* buffer, ssize size, s64 offset );

/**
	* Writes to file safely
	* @param  file
	* @param  buffer        Buffer to read from
	* @param  size          Size to write
	* @param  offset        Offset to write to
	* @param  bytes_written How much data we've actually written
	*/
b32 file_write_at_check( FileInfo* file, void const* buffer, ssize size, s64 offset, ssize* bytes_written );

enum FileStreamFlags : u32
{
	/* Allows us to write to the buffer directly. Beware: you can not append a new data! */
	EFileStream_WRITABLE = bit( 0 ),

	/* Clones the input buffer so you can write (zpl_file_write*) data into it. */
	/* Since we work with a clone, the buffer size can dynamically grow as well. */
	EFileStream_CLONE_WRITABLE = bit( 1 ),
};

/**
	* Opens a new memory stream
	* @param file
	* @param allocator
	*/
b8 file_stream_new( FileInfo* file, AllocatorInfo allocator );

/**
	* Opens a memory stream over an existing buffer
	* @param  file
	* @param  allocator
	* @param  buffer   Memory to create stream from
	* @param  size     Buffer's size
	* @param  flags
	*/
b8 file_stream_open( FileInfo* file, AllocatorInfo allocator, u8* buffer, ssize size, FileStreamFlags flags );

/**
	* Retrieves the stream's underlying buffer and buffer size.
	* @param file memory stream
	* @param size (Optional) buffer size
	*/
u8* file_stream_buf( FileInfo* file, ssize* size );

extern FileOperations const memory_file_operations;

inline
s64 file_seek( FileInfo* f, s64 offset )
{
	s64 new_offset = 0;

	if ( ! f->ops.read_at )
		f->ops = default_file_operations;

	f->ops.seek( f->fd, offset, ESeekWhence_BEGIN, &new_offset );

	return new_offset;
}

inline
s64 file_seek_to_end( FileInfo* f )
{
	s64 new_offset = 0;

	if ( ! f->ops.read_at )
		f->ops = default_file_operations;

	f->ops.seek( f->fd, 0, ESeekWhence_END, &new_offset );

	return new_offset;
}

inline
s64 file_tell( FileInfo* f )
{
	s64 new_offset = 0;

	if ( ! f->ops.read_at )
		f->ops = default_file_operations;

	f->ops.seek( f->fd, 0, ESeekWhence_CURRENT, &new_offset );

	return new_offset;
}

inline
b32 file_read( FileInfo* f, void* buffer, ssize size )
{
	s64 cur_offset = file_tell( f );
	b32 result     = file_read_at( f, buffer, size, file_tell( f ) );
	file_seek( f, cur_offset + size );
	return result;
}

inline
b32 file_read_at( FileInfo* f, void* buffer, ssize size, s64 offset )
{
	return file_read_at_check( f, buffer, size, offset, NULL );
}

inline
b32 file_read_at_check( FileInfo* f, void* buffer, ssize size, s64 offset, ssize* bytes_read )
{
	if ( ! f->ops.read_at )
		f->ops = default_file_operations;
	return f->ops.read_at( f->fd, buffer, size, offset, bytes_read, false );
}

inline
b32 file_write( FileInfo* f, void const* buffer, ssize size )
{
	s64 cur_offset = file_tell( f );
	b32 result     = file_write_at( f, buffer, size, file_tell( f ) );

	file_seek( f, cur_offset + size );

	return result;
}

inline
b32 file_write_at( FileInfo* f, void const* buffer, ssize size, s64 offset )
{
	return file_write_at_check( f, buffer, size, offset, NULL );
}

inline
b32 file_write_at_check( FileInfo* f, void const* buffer, ssize size, s64 offset, ssize* bytes_written )
{
	if ( ! f->ops.read_at )
		f->ops = default_file_operations;

	return f->ops.write_at( f->fd, buffer, size, offset, bytes_written );
}

#pragma endregion File Handling

#pragma region Timing

#ifdef GEN_BENCHMARK
//! Return CPU timestamp.
u64 read_cpu_time_stamp_counter( void );

//! Return relative time (in seconds) since the application start.
f64 time_rel( void );

//! Return relative time since the application start.
u64 time_rel_ms( void );
#endif

#pragma endregion Timing

#pragma region Parsing

#pragma region ADT

enum ADT_Type : u32
{
	EADT_TYPE_UNINITIALISED, /* node was not initialised, this is a programming error! */
	EADT_TYPE_ARRAY,
	EADT_TYPE_OBJECT,
	EADT_TYPE_STRING,
	EADT_TYPE_MULTISTRING,
	EADT_TYPE_INTEGER,
	EADT_TYPE_REAL,
};

enum ADT_Props : u32
{
	EADT_PROPS_NONE,
	EADT_PROPS_NAN,
	EADT_PROPS_NAN_NEG,
	EADT_PROPS_INFINITY,
	EADT_PROPS_INFINITY_NEG,
	EADT_PROPS_FALSE,
	EADT_PROPS_TRUE,
	EADT_PROPS_NULL,
	EADT_PROPS_IS_EXP,
	EADT_PROPS_IS_HEX,

	// Used internally so that people can fill in real numbers they plan to write.
	EADT_PROPS_IS_PARSED_REAL,
};

enum ADT_NamingStyle : u32
{
	EADT_NAME_STYLE_DOUBLE_QUOTE,
	EADT_NAME_STYLE_SINGLE_QUOTE,
	EADT_NAME_STYLE_NO_QUOTES,
};

enum ADT_AssignStyle : u32
{
	EADT_ASSIGN_STYLE_COLON,
	EADT_ASSIGN_STYLE_EQUALS,
	EADT_ASSIGN_STYLE_LINE,
};

enum ADT_DelimStyle : u32
{
	EADT_DELIM_STYLE_COMMA,
	EADT_DELIM_STYLE_LINE,
	EADT_DELIM_STYLE_NEWLINE,
};

enum ADT_Error : u32
{
	EADT_ERROR_NONE,
	EADT_ERROR_INTERNAL,
	EADT_ERROR_ALREADY_CONVERTED,
	EADT_ERROR_INVALID_TYPE,
	EADT_ERROR_OUT_OF_MEMORY,
};

struct ADT_Node
{
	char const*      name;
	struct ADT_Node* parent;

	/* properties */
	ADT_Type type  : 4;
	u8 props : 4;
#ifndef GEN_PARSER_DISABLE_ANALYSIS
	u8 cfg_mode          : 1;
	u8 name_style        : 2;
	u8 assign_style      : 2;
	u8 delim_style       : 2;
	u8 delim_line_width  : 4;
	u8 assign_line_width : 4;
#endif

	/* adt data */
	union
	{
		char const*     string;
		Array<ADT_Node> nodes;    ///< zpl_array

		struct
		{
			union
			{
				f64 real;
				s64 integer;
			};

#ifndef GEN_PARSER_DISABLE_ANALYSIS
			/* number analysis */
			s32 base;
			s32 base2;
			u8  base2_offset : 4;
			s8  exp          : 4;
			u8  neg_zero     : 1;
			u8  lead_digit   : 1;
#endif
		};
	};
};

/* ADT NODE LIMITS
	* delimiter and assignment segment width is limited to 128 whitespace symbols each.
	* real number limits decimal position to 128 places.
	* real number exponent is limited to 64 digits.
	*/

/**
	* @brief Initialise an ADT object or array
	*
	* @param node
	* @param backing Memory allocator used for descendants
	* @param name Node's name
	* @param is_array
	* @return error code
	*/
u8 adt_make_branch( ADT_Node* node, AllocatorInfo backing, char const* name, b32 is_array );

/**
	* @brief Destroy an ADT branch and its descendants
	*
	* @param node
	* @return error code
	*/
u8 adt_destroy_branch( ADT_Node* node );

/**
	* @brief Initialise an ADT leaf
	*
	* @param node
	* @param name Node's name
	* @param type Node's type (use zpl_adt_make_branch for container nodes)
	* @return error code
	*/
u8 adt_make_leaf( ADT_Node* node, char const* name, ADT_Type type );


/**
	* @brief Fetch a node using provided URI string.
	*
	* This method uses a basic syntax to fetch a node from the ADT. The following features are available
	* to retrieve the data:
	*
	* - "a/b/c" navigates through objects "a" and "b" to get to "c"
	* - "arr/[foo=123]/bar" iterates over "arr" to find any object with param "foo" that matches the value "123", then gets its field called "bar"
	* - "arr/3" retrieves the 4th element in "arr"
	* - "arr/[apple]" retrieves the first element of value "apple" in "arr"
	*
	* @param node ADT node
	* @param uri Locator string as described above
	* @return zpl_adt_node*
	*
	* @see code/apps/examples/json_get.c
	*/
ADT_Node* adt_query( ADT_Node* node, char const* uri );

/**
	* @brief Find a field node within an object by the given name.
	*
	* @param node
	* @param name
	* @param deep_search Perform search recursively
	* @return zpl_adt_node * node
	*/
ADT_Node* adt_find( ADT_Node* node, char const* name, b32 deep_search );

/**
	* @brief Allocate an unitialised node within a container at a specified index.
	*
	* @param parent
	* @param index
	* @return zpl_adt_node * node
	*/
ADT_Node* adt_alloc_at( ADT_Node* parent, ssize index );

/**
	* @brief Allocate an unitialised node within a container.
	*
	* @param parent
	* @return zpl_adt_node * node
	*/
ADT_Node* adt_alloc( ADT_Node* parent );

/**
	* @brief Move an existing node to a new container at a specified index.
	*
	* @param node
	* @param new_parent
	* @param index
	* @return zpl_adt_node * node
	*/
ADT_Node* adt_move_node_at( ADT_Node* node, ADT_Node* new_parent, ssize index );

/**
	* @brief Move an existing node to a new container.
	*
	* @param node
	* @param new_parent
	* @return zpl_adt_node * node
	*/
ADT_Node* adt_move_node( ADT_Node* node, ADT_Node* new_parent );

/**
	* @brief Swap two nodes.
	*
	* @param node
	* @param other_node
	* @return
	*/
void adt_swap_nodes( ADT_Node* node, ADT_Node* other_node );

/**
	* @brief Remove node from container.
	*
	* @param node
	* @return
	*/
void adt_remove_node( ADT_Node* node );

/**
	* @brief Initialise a node as an object
	*
	* @param obj
	* @param name
	* @param backing
	* @return
	*/
b8 adt_set_obj( ADT_Node* obj, char const* name, AllocatorInfo backing );

/**
	* @brief Initialise a node as an array
	*
	* @param obj
	* @param name
	* @param backing
	* @return
	*/
b8 adt_set_arr( ADT_Node* obj, char const* name, AllocatorInfo backing );

/**
	* @brief Initialise a node as a string
	*
	* @param obj
	* @param name
	* @param value
	* @return
	*/
b8 adt_set_str( ADT_Node* obj, char const* name, char const* value );

/**
	* @brief Initialise a node as a float
	*
	* @param obj
	* @param name
	* @param value
	* @return
	*/
b8 adt_set_flt( ADT_Node* obj, char const* name, f64 value );

/**
	* @brief Initialise a node as a signed integer
	*
	* @param obj
	* @param name
	* @param value
	* @return
	*/
b8 adt_set_int( ADT_Node* obj, char const* name, s64 value );

/**
	* @brief Append a new node to a container as an object
	*
	* @param parent
	* @param name
	* @return*
	*/
ADT_Node* adt_append_obj( ADT_Node* parent, char const* name );

/**
	* @brief Append a new node to a container as an array
	*
	* @param parent
	* @param name
	* @return*
	*/
ADT_Node* adt_append_arr( ADT_Node* parent, char const* name );

/**
	* @brief Append a new node to a container as a string
	*
	* @param parent
	* @param name
	* @param value
	* @return*
	*/
ADT_Node* adt_append_str( ADT_Node* parent, char const* name, char const* value );

/**
	* @brief Append a new node to a container as a float
	*
	* @param parent
	* @param name
	* @param value
	* @return*
	*/
ADT_Node* adt_append_flt( ADT_Node* parent, char const* name, f64 value );

/**
	* @brief Append a new node to a container as a signed integer
	*
	* @param parent
	* @param name
	* @param value
	* @return*
	*/
ADT_Node* adt_append_int( ADT_Node* parent, char const* name, s64 value );

/* parser helpers */

/**
	* @brief Parses a text and stores the result into an unitialised node.
	*
	* @param node
	* @param base
	* @return*
	*/
char* adt_parse_number( ADT_Node* node, char* base );

/**
	* @brief Parses a text and stores the result into an unitialised node.
	* This function expects the entire input to be a number.
	*
	* @param node
	* @param base
	* @return*
	*/
char* adt_parse_number_strict( ADT_Node* node, char* base_str );

/**
	* @brief Parses and converts an existing string node into a number.
	*
	* @param node
	* @return
	*/
ADT_Error adt_str_to_number( ADT_Node* node );

/**
	* @brief Parses and converts an existing string node into a number.
	* This function expects the entire input to be a number.
	*
	* @param node
	* @return
	*/
ADT_Error adt_str_to_number_strict( ADT_Node* node );

/**
	* @brief Prints a number into a file stream.
	*
	* The provided file handle can also be a memory mapped stream.
	*
	* @see zpl_file_stream_new
	* @param file
	* @param node
	* @return
	*/
ADT_Error adt_print_number( FileInfo* file, ADT_Node* node );

/**
	* @brief Prints a string into a file stream.
	*
	* The provided file handle can also be a memory mapped stream.
	*
	* @see zpl_file_stream_new
	* @param file
	* @param node
	* @param escaped_chars
	* @param escape_symbol
	* @return
	*/
ADT_Error adt_print_string( FileInfo* file, ADT_Node* node, char const* escaped_chars, char const* escape_symbol );

#pragma endregion ADT

#pragma region CSV

enum CSV_Error : u32
{
	ECSV_Error__NONE,
	ECSV_Error__INTERNAL,
	ECSV_Error__UNEXPECTED_END_OF_INPUT,
	ECSV_Error__MISMATCHED_ROWS,
};

typedef ADT_Node CSV_Object;

u8   csv_parse( CSV_Object* root, char* text, AllocatorInfo allocator, b32 has_header );
u8   csv_parse_delimiter( CSV_Object* root, char* text, AllocatorInfo allocator, b32 has_header, char delim );
void csv_free( CSV_Object* obj );

void   csv_write( FileInfo* file, CSV_Object* obj );
String csv_write_string( AllocatorInfo a, CSV_Object* obj );
void   csv_write_delimiter( FileInfo* file, CSV_Object* obj, char delim );
String csv_write_string_delimiter( AllocatorInfo a, CSV_Object* obj, char delim );

/* inline */

inline
u8 csv_parse( CSV_Object* root, char* text, AllocatorInfo allocator, b32 has_header )
{
	return csv_parse_delimiter( root, text, allocator, has_header, ',' );
}

inline
void csv_write( FileInfo* file, CSV_Object* obj )
{
	csv_write_delimiter( file, obj, ',' );
}

inline
String csv_write_string( AllocatorInfo a, CSV_Object* obj )
{
	return csv_write_string_delimiter( a, obj, ',' );
}

#pragma endregion CSV
#pragma endregion Parsing

GEN_NS_END

// GEN_ROLL_OWN_DEPENDENCIES
#endif

GEN_NS_BEGIN

#pragma region Types

using LogFailType = ssize(*)(char const*, ...);

// By default this library will either crash or exit if an error is detected while generating codes.
// Even if set to not use GEN_FATAL, GEN_FATAL will still be used for memory failures as the library is unusable when they occur.
#ifdef GEN_DONT_USE_FATAL
	#define log_failure log_fmt
#else
	#define log_failure GEN_FATAL
#endif

enum class AccessSpec : u32
{
	Default,
	Private,
	Protected,
	Public,

	Num_AccessSpec,
	Invalid,
};

inline
char const* to_str( AccessSpec type )
{
	local_persist
	char const* lookup[ (u32)AccessSpec::Num_AccessSpec ] = {
		"",
		"private",
		"protected",
		"public",
	};

	if ( type > AccessSpec::Public )
		return "Invalid";

	return lookup[ (u32)type ];
}


enum CodeFlag : u32
{
	None          = 0,
	FunctionType  = bit(0),
	ParamPack     = bit(1),
	Module_Export = bit(2),
	Module_Import = bit(3),
};

// Used to indicate if enum definitoin is an enum class or regular enum.
enum class EnumT : u8
{
	Regular,
	Class
};

constexpr EnumT EnumClass   = EnumT::Class;
constexpr EnumT EnumRegular = EnumT::Regular;

enum class ModuleFlag : u32
{
	None    = 0,
	Export  = bit(0),
	Import  = bit(1),

	Num_ModuleFlags,
	Invalid,
};

inline
StrC to_str( ModuleFlag flag )
{
	local_persist
	StrC lookup[ (u32)ModuleFlag::Num_ModuleFlags ] = {
		{ sizeof("__none__"), "__none__" },
		{ sizeof("export"), "export" },
		{ sizeof("import"), "import" },
	};

	if ( flag > ModuleFlag::Import )
		return { sizeof("invalid"), "invalid" };

	return lookup[ (u32)flag ];
}

inline
ModuleFlag operator|( ModuleFlag A, ModuleFlag B)
{
	return (ModuleFlag)( (u32)A | (u32)B );
}

enum class EPreprocessCond : u32
{
	If,
	IfDef,
	IfNotDef,
	ElIf
};

constexpr EPreprocessCond PreprocessCond_If       = EPreprocessCond::If;
constexpr EPreprocessCond PreprocessCond_IfDef    = EPreprocessCond::IfDef;
constexpr EPreprocessCond PreprocessCond_IfNotDef = EPreprocessCond::IfNotDef;
constexpr EPreprocessCond PreprocessCond_ElIf     = EPreprocessCond::ElIf;

namespace ECode
{
	enum Type : u32
	{
		Invalid,
		Untyped,
		NewLine,
		Comment,
		Access_Private,
		Access_Protected,
		Access_Public,
		PlatformAttributes,
		Class,
		Class_Fwd,
		Class_Body,
		Constructor,
		Constructor_Fwd,
		Destructor,
		Destructor_Fwd,
		Enum,
		Enum_Fwd,
		Enum_Body,
		Enum_Class,
		Enum_Class_Fwd,
		Execution,
		Export_Body,
		Extern_Linkage,
		Extern_Linkage_Body,
		Friend,
		Function,
		Function_Fwd,
		Function_Body,
		Global_Body,
		Module,
		Namespace,
		Namespace_Body,
		Operator,
		Operator_Fwd,
		Operator_Member,
		Operator_Member_Fwd,
		Operator_Cast,
		Operator_Cast_Fwd,
		Parameters,
		Preprocess_Define,
		Preprocess_Include,
		Preprocess_If,
		Preprocess_IfDef,
		Preprocess_IfNotDef,
		Preprocess_ElIf,
		Preprocess_Else,
		Preprocess_EndIf,
		Preprocess_Pragma,
		Specifiers,
		Struct,
		Struct_Fwd,
		Struct_Body,
		Template,
		Typedef,
		Typename,
		Union,
		Union_Body,
		Using,
		Using_Namespace,
		Variable,
		NumTypes
	};

	inline StrC to_str( Type type )
	{
		local_persist StrC lookup[] {
			{ sizeof( "Invalid" ),             "Invalid"             },
			{ sizeof( "Untyped" ),             "Untyped"             },
			{ sizeof( "NewLine" ),             "NewLine"             },
			{ sizeof( "Comment" ),             "Comment"             },
			{ sizeof( "Access_Private" ),      "Access_Private"      },
			{ sizeof( "Access_Protected" ),    "Access_Protected"    },
			{ sizeof( "Access_Public" ),       "Access_Public"       },
			{ sizeof( "PlatformAttributes" ),  "PlatformAttributes"  },
			{ sizeof( "Class" ),               "Class"               },
			{ sizeof( "Class_Fwd" ),           "Class_Fwd"           },
			{ sizeof( "Class_Body" ),          "Class_Body"          },
			{ sizeof( "Constructor" ),         "Constructor"         },
			{ sizeof( "Constructor_Fwd" ),     "Constructor_Fwd"     },
			{ sizeof( "Destructor" ),          "Destructor"          },
			{ sizeof( "Destructor_Fwd" ),      "Destructor_Fwd"      },
			{ sizeof( "Enum" ),                "Enum"                },
			{ sizeof( "Enum_Fwd" ),            "Enum_Fwd"            },
			{ sizeof( "Enum_Body" ),           "Enum_Body"           },
			{ sizeof( "Enum_Class" ),          "Enum_Class"          },
			{ sizeof( "Enum_Class_Fwd" ),      "Enum_Class_Fwd"      },
			{ sizeof( "Execution" ),           "Execution"           },
			{ sizeof( "Export_Body" ),         "Export_Body"         },
			{ sizeof( "Extern_Linkage" ),      "Extern_Linkage"      },
			{ sizeof( "Extern_Linkage_Body" ), "Extern_Linkage_Body" },
			{ sizeof( "Friend" ),              "Friend"              },
			{ sizeof( "Function" ),            "Function"            },
			{ sizeof( "Function_Fwd" ),        "Function_Fwd"        },
			{ sizeof( "Function_Body" ),       "Function_Body"       },
			{ sizeof( "Global_Body" ),         "Global_Body"         },
			{ sizeof( "Module" ),              "Module"              },
			{ sizeof( "Namespace" ),           "Namespace"           },
			{ sizeof( "Namespace_Body" ),      "Namespace_Body"      },
			{ sizeof( "Operator" ),            "Operator"            },
			{ sizeof( "Operator_Fwd" ),        "Operator_Fwd"        },
			{ sizeof( "Operator_Member" ),     "Operator_Member"     },
			{ sizeof( "Operator_Member_Fwd" ), "Operator_Member_Fwd" },
			{ sizeof( "Operator_Cast" ),       "Operator_Cast"       },
			{ sizeof( "Operator_Cast_Fwd" ),   "Operator_Cast_Fwd"   },
			{ sizeof( "Parameters" ),          "Parameters"          },
			{ sizeof( "Preprocess_Define" ),   "Preprocess_Define"   },
			{ sizeof( "Preprocess_Include" ),  "Preprocess_Include"  },
			{ sizeof( "Preprocess_If" ),       "Preprocess_If"       },
			{ sizeof( "Preprocess_IfDef" ),    "Preprocess_IfDef"    },
			{ sizeof( "Preprocess_IfNotDef" ), "Preprocess_IfNotDef" },
			{ sizeof( "Preprocess_ElIf" ),     "Preprocess_ElIf"     },
			{ sizeof( "Preprocess_Else" ),     "Preprocess_Else"     },
			{ sizeof( "Preprocess_EndIf" ),    "Preprocess_EndIf"    },
			{ sizeof( "Preprocess_Pragma" ),   "Preprocess_Pragma"   },
			{ sizeof( "Specifiers" ),          "Specifiers"          },
			{ sizeof( "Struct" ),              "Struct"              },
			{ sizeof( "Struct_Fwd" ),          "Struct_Fwd"          },
			{ sizeof( "Struct_Body" ),         "Struct_Body"         },
			{ sizeof( "Template" ),            "Template"            },
			{ sizeof( "Typedef" ),             "Typedef"             },
			{ sizeof( "Typename" ),            "Typename"            },
			{ sizeof( "Union" ),               "Union"               },
			{ sizeof( "Union_Body" ),          "Union_Body"          },
			{ sizeof( "Using" ),               "Using"               },
			{ sizeof( "Using_Namespace" ),     "Using_Namespace"     },
			{ sizeof( "Variable" ),            "Variable"            },
		};
		return lookup[type];
	}

}    // namespace ECode

using CodeT = ECode::Type;

namespace EOperator
{
	enum Type : u32
	{
		Invalid,
		Assign,
		Assign_Add,
		Assign_Subtract,
		Assign_Multiply,
		Assign_Divide,
		Assign_Modulo,
		Assign_BAnd,
		Assign_BOr,
		Assign_BXOr,
		Assign_LShift,
		Assign_RShift,
		Increment,
		Decrement,
		Unary_Plus,
		Unary_Minus,
		UnaryNot,
		Add,
		Subtract,
		Multiply,
		Divide,
		Modulo,
		BNot,
		BAnd,
		BOr,
		BXOr,
		LShift,
		RShift,
		LAnd,
		LOr,
		LEqual,
		LNot,
		Lesser,
		Greater,
		LesserEqual,
		GreaterEqual,
		Subscript,
		Indirection,
		AddressOf,
		MemberOfPointer,
		PtrToMemOfPtr,
		FunctionCall,
		Comma,
		New,
		NewArray,
		Delete,
		DeleteArray,
		NumOps
	};

	inline StrC to_str( Type op )
	{
		local_persist StrC lookup[] {
			{ sizeof( "INVALID" ),  "INVALID"  },
			{ sizeof( "=" ),        "="        },
			{ sizeof( "+=" ),       "+="       },
			{ sizeof( "-=" ),       "-="       },
			{ sizeof( "*=" ),       "*="       },
			{ sizeof( "/=" ),       "/="       },
			{ sizeof( "%=" ),       "%="       },
			{ sizeof( "&=" ),       "&="       },
			{ sizeof( "|=" ),       "|="       },
			{ sizeof( "^=" ),       "^="       },
			{ sizeof( "<<=" ),      "<<="      },
			{ sizeof( ">>=" ),      ">>="      },
			{ sizeof( "++" ),       "++"       },
			{ sizeof( "--" ),       "--"       },
			{ sizeof( "+" ),        "+"        },
			{ sizeof( "-" ),        "-"        },
			{ sizeof( "!" ),        "!"        },
			{ sizeof( "+" ),        "+"        },
			{ sizeof( "-" ),        "-"        },
			{ sizeof( "*" ),        "*"        },
			{ sizeof( "/" ),        "/"        },
			{ sizeof( "%" ),        "%"        },
			{ sizeof( "~" ),        "~"        },
			{ sizeof( "&" ),        "&"        },
			{ sizeof( "|" ),        "|"        },
			{ sizeof( "^" ),        "^"        },
			{ sizeof( "<<" ),       "<<"       },
			{ sizeof( ">>" ),       ">>"       },
			{ sizeof( "&&" ),       "&&"       },
			{ sizeof( "||" ),       "||"       },
			{ sizeof( "==" ),       "=="       },
			{ sizeof( "!=" ),       "!="       },
			{ sizeof( "<" ),        "<"        },
			{ sizeof( ">" ),        ">"        },
			{ sizeof( "<=" ),       "<="       },
			{ sizeof( ">=" ),       ">="       },
			{ sizeof( "[]" ),       "[]"       },
			{ sizeof( "*" ),        "*"        },
			{ sizeof( "&" ),        "&"        },
			{ sizeof( "->" ),       "->"       },
			{ sizeof( "->*" ),      "->*"      },
			{ sizeof( "()" ),       "()"       },
			{ sizeof( "," ),        ","        },
			{ sizeof( "new" ),      "new"      },
			{ sizeof( "new[]" ),    "new[]"    },
			{ sizeof( "delete" ),   "delete"   },
			{ sizeof( "delete[]" ), "delete[]" },
		};
		return lookup[op];
	}

}    // namespace EOperator

using OperatorT = EOperator::Type;

namespace ESpecifier
{
	enum Type : u32
	{
		Invalid,
		Consteval,
		Constexpr,
		Constinit,
		Explicit,
		External_Linkage,
		ForceInline,
		Global,
		Inline,
		Internal_Linkage,
		Local_Persist,
		Mutable,
		NeverInline,
		Ptr,
		Ref,
		Register,
		RValue,
		Static,
		Thread_Local,
		Virtual,
		Const,
		Final,
		NoExceptions,
		Override,
		Pure,
		Volatile,
		NumSpecifiers
	};

	inline bool is_trailing( Type specifier )
	{
		return specifier > Virtual;
	}

	inline StrC to_str( Type type )
	{
		local_persist StrC lookup[] {
			{ sizeof( "INVALID" ),       "INVALID"       },
			{ sizeof( "consteval" ),     "consteval"     },
			{ sizeof( "constexpr" ),     "constexpr"     },
			{ sizeof( "constinit" ),     "constinit"     },
			{ sizeof( "explicit" ),      "explicit"      },
			{ sizeof( "extern" ),        "extern"        },
			{ sizeof( "forceinline" ),   "forceinline"   },
			{ sizeof( "global" ),        "global"        },
			{ sizeof( "inline" ),        "inline"        },
			{ sizeof( "internal" ),      "internal"      },
			{ sizeof( "local_persist" ), "local_persist" },
			{ sizeof( "mutable" ),       "mutable"       },
			{ sizeof( "neverinline" ),   "neverinline"   },
			{ sizeof( "*" ),             "*"             },
			{ sizeof( "&" ),             "&"             },
			{ sizeof( "register" ),      "register"      },
			{ sizeof( "&&" ),            "&&"            },
			{ sizeof( "static" ),        "static"        },
			{ sizeof( "thread_local" ),  "thread_local"  },
			{ sizeof( "virtual" ),       "virtual"       },
			{ sizeof( "const" ),         "const"         },
			{ sizeof( "final" ),         "final"         },
			{ sizeof( "noexcept" ),      "noexcept"      },
			{ sizeof( "override" ),      "override"      },
			{ sizeof( "= 0" ),           "= 0"           },
			{ sizeof( "volatile" ),      "volatile"      },
		};
		return lookup[type];
	}

	inline Type to_type( StrC str )
	{
		local_persist u32 keymap[NumSpecifiers];
		do_once_start for ( u32 index = 0; index < NumSpecifiers; index++ )
		{
			StrC enum_str = to_str( (Type)index );
			keymap[index] = crc32( enum_str.Ptr, enum_str.Len - 1 );
		}
		do_once_end u32 hash = crc32( str.Ptr, str.Len );
		for ( u32 index = 0; index < NumSpecifiers; index++ )
		{
			if ( keymap[index] == hash )
				return (Type)index;
		}
		return Invalid;
	}

}    // namespace ESpecifier

using SpecifierT = ESpecifier::Type;

#pragma endregion Types

#pragma region AST

struct AST;
struct AST_Body;
struct AST_Attributes;
struct AST_Comment;
struct AST_Constructor;
// struct AST_BaseClass;
struct AST_Class;
struct AST_Define;
struct AST_Destructor;
struct AST_Enum;
struct AST_Exec;
struct AST_Extern;
struct AST_Include;
struct AST_Friend;
struct AST_Fn;
struct AST_Module;
struct AST_NS;
struct AST_Operator;
struct AST_OpCast;
struct AST_Param;
struct AST_Pragma;
struct AST_PreprocessCond;
struct AST_Specifiers;

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct AST_Expr;
struct AST_Expr_Assign;
struct AST_Expr_Alignof;
struct AST_Expr_Binary;
struct AST_Expr_CStyleCast;
struct AST_Expr_FunctionalCast;
struct AST_Expr_CppCast;
struct AST_Expr_ProcCall;
struct AST_Expr_Decltype;
struct AST_Expr_Comma;  // TODO(Ed) : This is a binary op not sure if it needs its own AST...
struct AST_Expr_AMS;    // Access Member Symbol
struct AST_Expr_Sizeof;
struct AST_Expr_Subscript;
struct AST_Expr_Ternary;
struct AST_Expr_UnaryPrefix;
struct AST_Expr_UnaryPostfix;
struct AST_Expr_Element;

struct AST_Stmt;
struct AST_Stmt_Break;
struct AST_Stmt_Case;
struct AST_Stmt_Continue;
struct AST_Stmt_Decl;
struct AST_Stmt_Do;
struct AST_Stmt_Expr;  // TODO(Ed) : Is this distinction needed? (Should it be a flag instead?)
struct AST_Stmt_Else;
struct AST_Stmt_If;
struct AST_Stmt_For;
struct AST_Stmt_Goto;
struct AST_Stmt_Label;
struct AST_Stmt_Switch;
struct AST_Stmt_While;
#endif

struct AST_Struct;
struct AST_Template;
struct AST_Type;
struct AST_Typedef;
struct AST_Union;
struct AST_Using;
struct AST_Var;

struct Code;
struct CodeBody;
// These are to offer ease of use and optionally strong type safety for the AST.
struct CodeAttributes;
// struct CodeBaseClass;
struct CodeComment;
struct CodeClass;
struct CodeConstructor;
struct CodeDefine;
struct CodeDestructor;
struct CodeEnum;
struct CodeExec;
struct CodeExtern;
struct CodeInclude;
struct CodeFriend;
struct CodeFn;
struct CodeModule;
struct CodeNS;
struct CodeOperator;
struct CodeOpCast;
struct CodeParam;
struct CodePreprocessCond;
struct CodePragma;
struct CodeSpecifiers;

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct CodeExpr;
struct CodeExpr_Assign;
struct CodeExpr_Alignof;
struct CodeExpr_Binary;
struct CodeExpr_CStyleCast;
struct CodeExpr_FunctionalCast;
struct CodeExpr_CppCast;
struct CodeExpr_Element;
struct CodeExpr_ProcCall;
struct CodeExpr_Decltype;
struct CodeExpr_Comma;
struct CodeExpr_AMS; // Access Member Symbol
struct CodeExpr_Sizeof;
struct CodeExpr_Subscript;
struct CodeExpr_Ternary;
struct CodeExpr_UnaryPrefix;
struct CodeExpr_UnaryPostfix;

struct CodeStmt;
struct CodeStmt_Break;
struct CodeStmt_Case;
struct CodeStmt_Continue;
struct CodeStmt_Decl;
struct CodeStmt_Do;
struct CodeStmt_Expr;
struct CodeStmt_Else;
struct CodeStmt_If;
struct CodeStmt_For;
struct CodeStmt_Goto;
struct CodeStmt_Label;
struct CodeStmt_Switch;
struct CodeStmt_While;
#endif

struct CodeStruct;
struct CodeTemplate;
struct CodeType;
struct CodeTypedef;
struct CodeUnion;
struct CodeUsing;
struct CodeVar;

namespace parser
{
	struct Token;
}

/*
	AST* wrapper
	- Not constantly have to append the '*' as this is written often..
	- Allows for implicit conversion to any of the ASTs (raw or filtered).
*/
struct Code
{
#	pragma region Statics
	// Used to identify ASTs that should always be duplicated. (Global constant ASTs)
	static Code Global;

	// Used to identify invalid generated code.
	static Code Invalid;
#	pragma endregion Statics

#	define Using_Code( Typename )          \
	char const* debug_str();               \
	Code        duplicate();			   \
	bool        is_equal( Code other );    \
	bool        is_valid();                \
	void        set_global();              \
	String      to_string();               \
	Typename&   operator = ( AST* other ); \
	Typename&   operator = ( Code other ); \
	bool        operator ==( Code other ); \
	bool        operator !=( Code other ); \
	operator bool();

	Using_Code( Code );

	template< class Type >
	forceinline Type cast()
	{
		return * rcast( Type*, this );
	}

	AST* operator ->()
	{
		return ast;
	}
	Code& operator ++();

	// TODO(Ed) : Remove this overload.
	auto& operator*()
	{
		local_persist thread_local
		Code NullRef = { nullptr };

		if ( ast == nullptr )
			return NullRef;

		return *this;
	}

	AST* ast;

#ifdef GEN_ENFORCE_STRONG_CODE_TYPES
#	define operator explicit operator
#endif
	operator CodeBody() const;
	operator CodeAttributes() const;
	// operator CodeBaseClass() const;
	operator CodeComment() const;
	operator CodeClass() const;
	operator CodeConstructor() const;
	operator CodeDefine() const;
	operator CodeDestructor() const;
	operator CodeExec() const;
	operator CodeEnum() const;
	operator CodeExtern() const;
	operator CodeInclude() const;
	operator CodeFriend() const;
	operator CodeFn() const;
	operator CodeModule() const;
	operator CodeNS() const;
	operator CodeOperator() const;
	operator CodeOpCast() const;
	operator CodeParam() const;
	operator CodePragma() const;
	operator CodePreprocessCond() const;
	operator CodeSpecifiers() const;
	operator CodeStruct() const;
	operator CodeTemplate() const;
	operator CodeType() const;
	operator CodeTypedef() const;
	operator CodeUnion() const;
	operator CodeUsing() const;
	operator CodeVar() const;
	#undef operator
};

struct Code_POD
{
	AST* ast;
};

static_assert( sizeof(Code) == sizeof(Code_POD), "ERROR: Code is not POD" );

// Desired width of the AST data structure.
constexpr int const AST_POD_Size = 128;

/*
	Simple AST POD with functionality to seralize into C++ syntax.
*/
struct AST
{
#	pragma region Member Functions
	void        append     ( AST* other );
	char const* debug_str  ();
	AST*        duplicate  ();
	Code&       entry      ( u32 idx );
	bool        has_entries();
	bool        is_equal   ( AST* other );
	char const* type_str();
	bool        validate_body();

	String to_string();

	neverinline
	void to_string( String& result );

	template< class Type >
	forceinline Type cast()
	{
		return * this;
	}

	operator Code();
	operator CodeBody();
	operator CodeAttributes();
	// operator CodeBaseClass();
	operator CodeComment();
	operator CodeConstructor();
	operator CodeDestructor();
	operator CodeClass();
	operator CodeDefine();
	operator CodeEnum();
	operator CodeExec();
	operator CodeExtern();
	operator CodeInclude();
	operator CodeFriend();
	operator CodeFn();
	operator CodeModule();
	operator CodeNS();
	operator CodeOperator();
	operator CodeOpCast();
	operator CodeParam();
	operator CodePragma();
	operator CodePreprocessCond();
	operator CodeSpecifiers();
	operator CodeStruct();
	operator CodeTemplate();
	operator CodeType();
	operator CodeTypedef();
	operator CodeUnion();
	operator CodeUsing();
	operator CodeVar();
#	pragma endregion Member Functions

	constexpr static
	int ArrSpecs_Cap =
	(
			AST_POD_Size
			- sizeof(AST*) * 3
			- sizeof(parser::Token*)
			- sizeof(AST*)
			- sizeof(StringCached)
			- sizeof(CodeT)
			- sizeof(ModuleFlag)
			- sizeof(int)
	)
	/ sizeof(int) - 1; // -1 for 4 extra bytes

	union {
		struct
		{
			AST*      InlineCmt;       // Class, Constructor, Destructor, Enum, Friend, Functon, Operator, OpCast, Struct, Typedef, Using, Variable
			AST*      Attributes;      // Class, Enum, Function, Struct, Typedef, Union, Using, Variable
			AST*      Specs;           // Destructor, Function, Operator, Typename, Variable
			union {
				AST*  InitializerList; // Constructor
				AST*  ParentType;      // Class, Struct, ParentType->Next has a possible list of interfaces.
				AST*  ReturnType;      // Function, Operator, Typename
				AST*  UnderlyingType;  // Enum, Typedef
				AST*  ValueType;       // Parameter, Variable
			};
			union {
				AST*  Macro;           // Parameter
				AST*  BitfieldSize;    // Variable (Class/Struct Data Member)
				AST*  Params;          // Constructor, Function, Operator, Template, Typename
			};
			union {
				AST*  ArrExpr;          // Typename
				AST*  Body;             // Class, Constructor, Destructor, Enum, Friend, Function, Namespace, Struct, Union
				AST*  Declaration;      // Friend, Template
				AST*  Value;            // Parameter, Variable
			};
			union {
				AST*  NextVar;          // Variable; Possible way to handle comma separated variables declarations. ( , NextVar->Specs NextVar->Name NextVar->ArrExpr = NextVar->Value )
				AST*  SuffixSpecs;      // Only used with typenames, to store the function suffix if typename is function signature. ( May not be needed )
				AST*  PostNameMacro;     // Only used with parameters for specifically UE_REQUIRES (Thanks Unreal)
			};
		};
		StringCached  Content;          // Attributes, Comment, Execution, Include
		struct {
			SpecifierT ArrSpecs[ArrSpecs_Cap]; // Specifiers
			AST*       NextSpecs;              // Specifiers; If ArrSpecs is full, then NextSpecs is used.
		};
	};
	union {
		AST* Prev;
		AST* Front;
		AST* Last;
	};
	union {
		AST* Next;
		AST* Back;
	};
	parser::Token*    Token; // Reference to starting token, only avaialble if it was derived from parsing.
	AST*              Parent;
	StringCached      Name;
	CodeT             Type;
//	CodeFlag          CodeFlags;
	ModuleFlag        ModuleFlags;
	union {
		b32           IsFunction;  // Used by typedef to not serialize the name field.
		b32           IsParamPack; // Used by typename to know if type should be considered a parameter pack.
		OperatorT     Op;
		AccessSpec    ParentAccess;
		s32           NumEntries;
		s32           VarConstructorInit; // Used by variables to know that initialization is using a constructor expression instead of an assignment expression.
	};
};

struct AST_POD
{
	union {
		struct
		{
			AST*      InlineCmt;       // Class, Constructor, Destructor, Enum, Friend, Functon, Operator, OpCast, Struct, Typedef, Using, Variable
			AST*      Attributes;      // Class, Enum, Function, Struct, Typedef, Union, Using, Variable
			AST*      Specs;           // Destructor, Function, Operator, Typename, Variable
			union {
				AST*  InitializerList; // Constructor
				AST*  ParentType;      // Class, Struct, ParentType->Next has a possible list of interfaces.
				AST*  ReturnType;      // Function, Operator, Typename
				AST*  UnderlyingType;  // Enum, Typedef
				AST*  ValueType;       // Parameter, Variable
			};
			union {
				AST*  Macro;           // Parameter
				AST*  BitfieldSize;    // Variable (Class/Struct Data Member)
				AST*  Params;          // Constructor, Function, Operator, Template, Typename
			};
			union {
				AST*  ArrExpr;          // Typename
				AST*  Body;             // Class, Constructr, Destructor, Enum, Friend, Function, Namespace, Struct, Union
				AST*  Declaration;      // Friend, Template
				AST*  Value;            // Parameter, Variable
			};
			union {
				AST*  NextVar;          // Variable; Possible way to handle comma separated variables declarations. ( , NextVar->Specs NextVar->Name NextVar->ArrExpr = NextVar->Value )
				AST*  SuffixSpecs;      // Only used with typenames, to store the function suffix if typename is function signature. ( May not be needed )
				AST*  PostNameMacro;    // Only used with parameters for specifically UE_REQUIRES (Thanks Unreal)
			};
		};
		StringCached  Content;          // Attributes, Comment, Execution, Include
		struct {
			SpecifierT ArrSpecs[AST::ArrSpecs_Cap]; // Specifiers
			AST*       NextSpecs;                   // Specifiers; If ArrSpecs is full, then NextSpecs is used.
		};
	};
	union {
		AST* Prev;
		AST* Front;
		AST* Last;
	};
	union {
		AST* Next;
		AST* Back;
	};
	parser::Token*    Token; // Reference to starting token, only avaialble if it was derived from parsing.
	AST*              Parent;
	StringCached      Name;
	CodeT             Type;
	CodeFlag          CodeFlags;
	ModuleFlag        ModuleFlags;
	union {
		b32           IsFunction;  // Used by typedef to not serialize the name field.
		b32           IsParamPack; // Used by typename to know if type should be considered a parameter pack.
		OperatorT     Op;
		AccessSpec    ParentAccess;
		s32           NumEntries;
		s32           VarConstructorInit; // Used by variables to know that initialization is using a constructor expression instead of an assignment expression.
	};
};

struct test {
	SpecifierT ArrSpecs[AST::ArrSpecs_Cap]; // Specifiers
	AST* NextSpecs;                         // Specifiers; If ArrSpecs is full, then NextSpecs is used.
};

constexpr int pls = sizeof(test);

// Its intended for the AST to have equivalent size to its POD.
// All extra functionality within the AST namespace should just be syntatic sugar.
static_assert( sizeof(AST)     == sizeof(AST_POD), "ERROR: AST IS NOT POD" );
static_assert( sizeof(AST_POD) == AST_POD_Size,    "ERROR: AST POD is not size of AST_POD_Size" );

// Used when the its desired when omission is allowed in a definition.
#define NoCode      { nullptr }
#define CodeInvalid (* Code::Invalid.ast) // Uses an implicitly overloaded cast from the AST to the desired code type.

#pragma region Code Types

struct CodeBody
{
	Using_Code( CodeBody );

	void append( Code other )
	{
		raw()->append( other.ast );
	}
	void append( CodeBody body )
	{
		for ( Code entry : body )
		{
			append( entry );
		}
	}
	bool has_entries()
	{
		return rcast( AST*, ast )->has_entries();
	}
	void to_string( String& result );
	void to_string_export( String& result );
	AST* raw()
	{
		return rcast( AST*, ast );
	}
	AST_Body* operator->()
	{
		return ast;
	}
	operator Code()
	{
		return * rcast( Code*, this );
	}
#pragma region Iterator
	Code begin()
	{
		if ( ast )
			return { rcast( AST*, ast)->Front };

		return { nullptr };
	}
	Code end()
	{
		return { rcast(AST*, ast)->Back->Next };
	}
#pragma endregion Iterator

	AST_Body* ast;
};

struct CodeClass
{
	Using_Code( CodeClass );

	void add_interface( CodeType interface );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST* raw()
	{
		return rcast( AST*, ast );
	}
	operator Code()
	{
		return * rcast( Code*, this );
	}
	AST_Class* operator->()
	{
		if ( ast == nullptr )
		{
			log_failure("Attempt to dereference a nullptr");
			return nullptr;
		}
		return ast;
	}
	AST_Class* ast;
};

struct CodeParam
{
	Using_Code( CodeParam );

	void append( CodeParam other );

	CodeParam get( s32 idx );
	bool has_entries();
	void to_string( String& result );
	AST* raw()
	{
		return rcast( AST*, ast );
	}
	AST_Param* operator->()
	{
		if ( ast == nullptr )
		{
			log_failure("Attempt to dereference a nullptr!");
			return nullptr;
		}
		return ast;
	}
	operator Code()
	{
		return { (AST*)ast };
	}
#pragma region Iterator
	CodeParam begin()
	{
		if ( ast )
			return { ast };

		return { nullptr };
	}
	CodeParam end()
	{
		// return { (AST_Param*) rcast( AST*, ast)->Last };
		return { nullptr };
	}
	CodeParam& operator++();
	CodeParam operator*()
	{
		return * this;
	}
#pragma endregion Iterator

	AST_Param* ast;
};

struct CodeSpecifiers
{
	Using_Code( CodeSpecifiers );

	bool append( SpecifierT spec )
	{
		if ( ast == nullptr )
		{
			log_failure("CodeSpecifiers: Attempted to append to a null specifiers AST!");
			return false;
		}

		if ( raw()->NumEntries == AST::ArrSpecs_Cap )
		{
			log_failure("CodeSpecifiers: Attempted to append over %d specifiers to a specifiers AST!", AST::ArrSpecs_Cap );
			return false;
		}

		raw()->ArrSpecs[ raw()->NumEntries ] = spec;
		raw()->NumEntries++;
		return true;
	}
	s32 has( SpecifierT spec )
	{
		for ( s32 idx = 0; idx < raw()->NumEntries; idx++ )
		{
			if ( raw()->ArrSpecs[ idx ] == spec )
				return idx;
		}

		return -1;
	}
	void to_string( String& result );
	AST* raw()
	{
		return rcast( AST*, ast );
	}
	AST_Specifiers* operator->()
	{
		if ( ast == nullptr )
		{
			log_failure("Attempt to dereference a nullptr!");
			return nullptr;
		}
		return ast;
	}
	operator Code()
	{
		return { (AST*) ast };
	}
#pragma region Iterator
	SpecifierT* begin()
	{
		if ( ast )
			return & raw()->ArrSpecs[0];

		return nullptr;
	}
	SpecifierT* end()
	{
		return raw()->ArrSpecs + raw()->NumEntries;
	}
#pragma endregion Iterator

	AST_Specifiers* ast;
};

struct CodeStruct
{
	Using_Code( CodeStruct );

	void add_interface( CodeType interface );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST* raw()
	{
		return rcast( AST*, ast );
	}
	operator Code()
	{
		return * rcast( Code*, this );
	}
	AST_Struct* operator->()
	{
		if ( ast == nullptr )
		{
			log_failure("Attempt to dereference a nullptr");
			return nullptr;
		}
		return ast;
	}
	AST_Struct* ast;
};

#define Define_CodeType( Typename )     \
	struct Code##Typename               \
	{                                   \
		Using_Code( Code ## Typename ); \
		AST*            raw();          \
		operator        Code();         \
		AST_##Typename* operator->();   \
		AST_##Typename* ast;            \
	}

Define_CodeType( Attributes );
// Define_CodeType( BaseClass );
Define_CodeType( Comment );

struct CodeConstructor
{
	Using_Code( CodeConstructor );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST*             raw();
	operator         Code();
	AST_Constructor* operator->();
	AST_Constructor* ast;
};

struct CodeDefine
{
	Using_Code( CodeDefine );

	void to_string( String& result );

	AST*        raw();
	operator    Code();
	AST_Define* operator->();
	AST_Define* ast;
};

struct CodeDestructor
{
	Using_Code( CodeDestructor );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST*             raw();
	operator         Code();
	AST_Destructor* operator->();
	AST_Destructor* ast;
};

struct CodeEnum
{
	Using_Code( CodeEnum );

	void to_string_def( String& result );
	void to_string_fwd( String& result );
	void to_string_class_def( String& result );
	void to_string_class_fwd( String& result );

	AST*      raw();
	operator  Code();
	AST_Enum* operator->();
	AST_Enum* ast;
};

Define_CodeType( Exec );

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct CodeExpr
{
	Using_Code( CodeExpr );

	void to_string( String& result );

	AST*      raw();
	operator  Code();
	AST_Expr* operator->();
	AST_Expr* ast;
};

struct CodeExpr_Assign
{
	Using_Code( CodeExpr_Assign );

	void to_string( String& result );

	AST*             raw();
	operator         Code();
	AST_Expr_Assign* operator->();
	AST_Expr_Assign* ast;
};

struct CodeExpr_Alignof
{
	Using_Code( CodeExpr_Alignof );

	void to_string( String& result );

	AST*              raw();
	operator          Code();
	AST_Expr_Alignof* operator->();
	AST_Expr_Alignof* ast;
};

struct CodeExpr_Binary
{
	Using_Code( CodeExpr_Binary );

	void to_string( String& result );

	AST*             raw();
	operator         Code();
	AST_Expr_Binary* operator->();
	AST_Expr_Binary* ast;
};

struct CodeExpr_CStyleCast
{
	Using_Code( CodeExpr_CStyleCast );

	void to_string( String& result );

	AST*                 raw();
	operator             Code();
	AST_Expr_CStyleCast* operator->();
	AST_Expr_CStyleCast* ast;
};

struct CodeExpr_FunctionalCast
{
	Using_Code( CodeExpr_FunctionalCast );

	void to_string( String& result );

	AST*                     raw();
	operator                 Code();
	AST_Expr_FunctionalCast* operator->();
	AST_Expr_FunctionalCast* ast;
};

struct CodeExpr_CppCast
{
	Using_Code( CodeExpr_CppCast );

	void to_string( String& result );

	AST*              raw();
	operator          Code();
	AST_Expr_CppCast* operator->();
	AST_Expr_CppCast* ast;
};

struct CodeExpr_Element
{
	Using_Code( CodeExpr_Element );

	void to_string( String& result );

	AST*              raw();
	operator          Code();
	AST_Expr_Element* operator->();
	AST_Expr_Element* ast;
};

struct CodeExpr_ProcCall
{
	Using_Code( CodeExpr_ProcCall );

	void to_string( String& result );

	AST*               raw();
	operator           Code();
	AST_Expr_ProcCall* operator->();
	AST_Expr_ProcCall* ast;
};

struct CodeExpr_Decltype
{
	Using_Code( CodeExpr_Decltype );

	void to_string( String& result );

	AST*      raw();
	operator  Code();
	AST_Expr_Decltype* operator->();
	AST_Expr_Decltype* ast;
};

struct CodeExpr_Comma
{
	Using_Code( CodeExpr_Comma );

	void to_string( String& result );

	AST*      raw();
	operator  Code();
	AST_Expr_Comma* operator->();
	AST_Expr_Comma* ast;
};

struct CodeExpr_AMS
{
	Using_Code( CodeExpr_AMS );

	void to_string( String& result );

	AST*          raw();
	operator      Code();
	AST_Expr_AMS* operator->();
	AST_Expr_AMS* ast;
};

struct CodeExpr_Sizeof
{
	Using_Code( CodeExpr_Sizeof );

	void to_string( String& result );

	AST*             raw();
	operator         Code();
	AST_Expr_Sizeof* operator->();
	AST_Expr_Sizeof* ast;
};

struct CodeExpr_Subscript
{
	Using_Code( CodeExpr_Subscript );

	void to_string( String& result );

	AST*                raw();
	operator            Code();
	AST_Expr_Subscript* operator->();
	AST_Expr_Subscript* ast;
};

struct CodeExpr_Ternary
{
	Using_Code( CodeExpr_Ternary );

	void to_string( String& result );

	AST*              raw();
	operator          Code();
	AST_Expr_Ternary* operator->();
	AST_Expr_Ternary* ast;
};

struct CodeExpr_UnaryPrefix
{
	Using_Code( CodeExpr_UnaryPrefix );

	void to_string( String& result );

	AST*                  raw();
	operator              Code();
	AST_Expr_UnaryPrefix* operator->();
	AST_Expr_UnaryPrefix* ast;
};

struct CodeExpr_UnaryPostfix
{
	Using_Code( CodeExpr_UnaryPostfix );

	void to_string( String& result );

	AST*                   raw();
	operator               Code();
	AST_Expr_UnaryPostfix* operator->();
	AST_Expr_UnaryPostfix* ast;
};
#endif

struct CodeExtern
{
	Using_Code( CodeExtern );

	void to_string( String& result );

	AST*        raw();
	operator    Code();
	AST_Extern* operator->();
	AST_Extern* ast;
};

struct CodeInclude
{
	Using_Code( CodeInclude );

	void to_string( String& result );

	AST*         raw();
	operator     Code();
	AST_Include* operator->();
	AST_Include* ast;
};

struct CodeFriend
{
	Using_Code( CodeFriend );

	void to_string( String& result );

	AST*        raw();
	operator    Code();
	AST_Friend* operator->();
	AST_Friend* ast;
};

struct CodeFn
{
	Using_Code( CodeFn );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST*     raw();
	operator Code();
	AST_Fn*  operator->();
	AST_Fn*  ast;
};

struct CodeModule
{
	Using_Code( CodeModule );

	void to_string( String& result );

	AST*        raw();
	operator    Code();
	AST_Module* operator->();
	AST_Module* ast;
};

struct CodeNS
{
	Using_Code( CodeNS );

	void to_string( String& result );

	AST*     raw();
	operator Code();
	AST_NS*  operator->();
	AST_NS*  ast;
};

struct CodeOperator
{
	Using_Code( CodeOperator );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST*          raw();
	operator      Code();
	AST_Operator* operator->();
	AST_Operator* ast;
};

struct CodeOpCast
{
	Using_Code( CodeOpCast );

	void to_string_def( String& result );
	void to_string_fwd( String& result );

	AST*        raw();
	operator    Code();
	AST_OpCast* operator->();
	AST_OpCast* ast;
};

struct CodePragma
{
	Using_Code( CodePragma );

	void to_string( String& result );

	AST*        raw();
	operator    Code();
	AST_Pragma* operator->();
	AST_Pragma* ast;
};

struct CodePreprocessCond
{
	Using_Code( CodePreprocessCond );

	void to_string_if( String& result );
	void to_string_ifdef( String& result );
	void to_string_ifndef( String& result );
	void to_string_elif( String& result );
	void to_string_else( String& result );
	void to_string_endif( String& result );

	AST*                raw();
	operator            Code();
	AST_PreprocessCond* operator->();
	AST_PreprocessCond* ast;
};

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct CodeStmt
{
	Using_Code( CodeStmt );

	void to_string( String& result );

	AST*      raw();
	operator  Code();
	AST_Stmt* operator->();
	AST_Stmt* ast;
};

struct CodeStmt_Break
{
	Using_Code( CodeStmt_Break );

	void to_string( String& result );

	AST*            raw();
	operator        Code();
	AST_Stmt_Break* operator->();
	AST_Stmt_Break* ast;
};

struct CodeStmt_Case
{
	Using_Code( CodeStmt_Case );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Case* operator->();
	AST_Stmt_Case* ast;
};

struct CodeStmt_Continue
{
	Using_Code( CodeStmt_Continue );

	void to_string( String& result );

	AST*               raw();
	operator           Code();
	AST_Stmt_Continue* operator->();
	AST_Stmt_Continue* ast;
};

struct CodeStmt_Decl
{
	Using_Code( CodeStmt_Decl );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Decl* operator->();
	AST_Stmt_Decl* ast;
};

struct CodeStmt_Do
{
	Using_Code( CodeStmt_Do );

	void to_string( String& result );

	AST*         raw();
	operator     Code();
	AST_Stmt_Do* operator->();
	AST_Stmt_Do* ast;
};

struct CodeStmt_Expr
{
	Using_Code( CodeStmt_Expr );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Expr* operator->();
	AST_Stmt_Expr* ast;
};

struct CodeStmt_Else
{
	Using_Code( CodeStmt_Else );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Else* operator->();
	AST_Stmt_Else* ast;
};

struct CodeStmt_If
{
	Using_Code( CodeStmt_If );

	void to_string( String& result );

	AST*         raw();
	operator     Code();
	AST_Stmt_If* operator->();
	AST_Stmt_If* ast;
};

struct CodeStmt_For
{
	Using_Code( CodeStmt_For );

	void to_string( String& result );

	AST*          raw();
	operator      Code();
	AST_Stmt_For* operator->();
	AST_Stmt_For* ast;
};

struct CodeStmt_Goto
{
	Using_Code( CodeStmt_Goto );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Goto* operator->();
	AST_Stmt_Goto* ast;
};

struct CodeStmt_Label
{
	Using_Code( CodeStmt_Label );

	void to_string( String& result );

	AST*            raw();
	operator        Code();
	AST_Stmt_Label* operator->();
	AST_Stmt_Label* ast;
};

struct CodeStmt_Switch
{
	Using_Code( CodeStmt_Switch );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_Switch* operator->();
	AST_Stmt_Switch* ast;
};

struct CodeStmt_While
{
	Using_Code( CodeStmt_While );

	void to_string( String& result );

	AST*           raw();
	operator       Code();
	AST_Stmt_While* operator->();
	AST_Stmt_While* ast;
};
#endif

struct CodeTemplate
{
	Using_Code( CodeTemplate );

	void to_string( String& result );

	AST*          raw();
	operator      Code();
	AST_Template* operator->();
	AST_Template* ast;
};

struct CodeType
{
	Using_Code( CodeType );

	void to_string( String& result );

	AST*      raw();
	operator  Code();
	AST_Type* operator->();
	AST_Type* ast;
};

struct CodeTypedef
{
	Using_Code( CodeTypedef );

	void to_string( String& result );

	AST*         raw();
	operator     Code();
	AST_Typedef* operator->();
	AST_Typedef* ast;
};

struct CodeUnion
{
	Using_Code( CodeUnion );

	void to_string( String& result );

	AST*       raw();
	operator   Code();
	AST_Union* operator->();
	AST_Union* ast;
};

struct CodeUsing
{
	Using_Code( CodeUsing );

	void to_string( String& result );
	void to_string_ns( String& result );

	AST*       raw();
	operator   Code();
	AST_Using* operator->();
	AST_Using* ast;
};

struct CodeVar
{
	Using_Code( CodeVar );

	void to_string( String& result );

	AST*     raw();
	operator Code();
	AST_Var* operator->();
	AST_Var* ast;
};

#undef Define_CodeType
#undef Using_Code

#pragma endregion Code Types

#pragma region AST Types
/*
	Show only relevant members of the AST for its type.
	AST* fields are replaced with Code types.
		- Guards assignemnts to AST* fields to ensure the AST is duplicated if assigned to another parent.
*/

struct AST_Body
{
	char              _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	Code              Front;
	Code              Back;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) ];
	s32 			  NumEntries;
};
static_assert( sizeof(AST_Body) == sizeof(AST), "ERROR: AST_Body is not the same size as AST");

struct AST_Attributes
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Attributes) == sizeof(AST), "ERROR: AST_Attributes is not the same size as AST");

#if 0
struct AST_BaseClass
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_BaseClass) == sizeof(AST), "ERROR: AST_BaseClass is not the same size as AST");
#endif

struct AST_Comment
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Comment) == sizeof(AST), "ERROR: AST_Comment is not the same size as AST");

struct AST_Class
{
	union {
		char                _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment     InlineCmt; // Only supported by forward declarations
			CodeAttributes  Attributes;
			char 	        _PAD_SPECS_ [ sizeof(AST*) ];
			CodeType        ParentType;
			char 	        _PAD_PARAMS_[ sizeof(AST*) ];
			CodeBody        Body;
			char 	        _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	CodeType                Prev;
	CodeType                Next;
	parser::Token*          Tok;
	Code                    Parent;
	StringCached            Name;
	CodeT                   Type;
	ModuleFlag              ModuleFlags;
	AccessSpec              ParentAccess;
};
static_assert( sizeof(AST_Class) == sizeof(AST), "ERROR: AST_Class is not the same size as AST");

struct AST_Constructor
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt; // Only supported by forward declarations
			char           _PAD_PROPERTIES_ [ sizeof(AST*) * 1 ];
			CodeSpecifiers Specs;
			Code           InitializerList;
			CodeParam      Params;
			Code           Body;
			char 		   _PAD_PROPERTIES_2_ [ sizeof(AST*) * 2 ];
		};
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Constructor) == sizeof(AST), "ERROR: AST_Constructor is not the same size as AST");

struct AST_Define
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Define) == sizeof(AST), "ERROR: AST_Define is not the same size as AST");

struct AST_Destructor
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			char           _PAD_PROPERTIES_ [ sizeof(AST*) * 1 ];
			CodeSpecifiers Specs;
			char           _PAD_PROPERTIES_2_ [ sizeof(AST*) * 2 ];
			Code           Body;
			char 		   _PAD_PROPERTIES_3_ [ sizeof(AST*) ];
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	char                   _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Destructor) == sizeof(AST), "ERROR: AST_Destructor is not the same size as AST");

struct AST_Enum
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			CodeAttributes Attributes;
			char           _PAD_SPEC_  [ sizeof(AST*) ];
			CodeType       UnderlyingType;
			char	       _PAD_PARAMS_[ sizeof(AST*) ];
			CodeBody       Body;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	char 			       _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Enum) == sizeof(AST), "ERROR: AST_Enum is not the same size as AST");

struct AST_Exec
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char              _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Exec) == sizeof(AST), "ERROR: AST_Exec is not the same size as AST");

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct AST_Expr
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr) == sizeof(AST), "ERROR: AST_Expr is not the same size as AST");

struct AST_Expr_Assign
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Assign) == sizeof(AST), "ERROR: AST_Expr_Assign is not the same size as AST");

struct AST_Expr_Alignof
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Alignof) == sizeof(AST), "ERROR: AST_Expr_Alignof is not the same size as AST");

struct AST_Expr_Binary
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Binary) == sizeof(AST), "ERROR: AST_Expr_Binary is not the same size as AST");

struct AST_Expr_CStyleCast
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_CStyleCast) == sizeof(AST), "ERROR: AST_Expr_CStyleCast is not the same size as AST");

struct AST_Expr_FunctionalCast
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_FunctionalCast) == sizeof(AST), "ERROR: AST_Expr_FunctionalCast is not the same size as AST");

struct AST_Expr_CppCast
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_CppCast) == sizeof(AST), "ERROR: AST_Expr_CppCast is not the same size as AST");

struct AST_Expr_ProcCall
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_ProcCall) == sizeof(AST), "ERROR: AST_Expr_Identifier is not the same size as AST");

struct AST_Expr_Decltype
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Decltype) == sizeof(AST), "ERROR: AST_Expr_Decltype is not the same size as AST");

struct AST_Expr_Comma
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Comma) == sizeof(AST), "ERROR: AST_Expr_Comma is not the same size as AST");

struct AST_Expr_AMS
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_AMS) == sizeof(AST), "ERROR: AST_Expr_AMS is not the same size as AST");

struct AST_Expr_Sizeof
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Sizeof) == sizeof(AST), "ERROR: AST_Expr_Sizeof is not the same size as AST");

struct AST_Expr_Subscript
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Subscript) == sizeof(AST), "ERROR: AST_Expr_Subscript is not the same size as AST");

struct AST_Expr_Ternary
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Ternary) == sizeof(AST), "ERROR: AST_Expr_Ternary is not the same size as AST");

struct AST_Expr_UnaryPrefix
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_UnaryPrefix) == sizeof(AST), "ERROR: AST_Expr_UnaryPrefix is not the same size as AST");

struct AST_Expr_UnaryPostfix
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_UnaryPostfix) == sizeof(AST), "ERROR: AST_Expr_UnaryPostfix is not the same size as AST");

struct AST_Expr_Element
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Expr_Element) == sizeof(AST), "ERROR: AST_Expr_Element is not the same size as AST");
#endif

struct AST_Extern
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char      _PAD_PROPERTIES_[ sizeof(AST*) * 5 ];
			CodeBody  Body;
			char      _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Extern) == sizeof(AST), "ERROR: AST_Extern is not the same size as AST");

struct AST_Include
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Include) == sizeof(AST), "ERROR: AST_Include is not the same size as AST");

struct AST_Friend
{
	union {
		char            _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment InlineCmt;
			char        _PAD_PROPERTIES_[ sizeof(AST*) * 4 ];
			Code        Declaration;
			char 	    _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Friend) == sizeof(AST), "ERROR: AST_Friend is not the same size as AST");

struct AST_Fn
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment     InlineCmt;
			CodeAttributes  Attributes;
			CodeSpecifiers  Specs;
			CodeType        ReturnType;
			CodeParam 	    Params;
			CodeBody        Body;
			char 	        _PAD_PROPERTIES_ [ sizeof(AST*) ];
		};
	};
	Code                    Prev;
	Code                    Next;
	parser::Token*          Tok;
	Code                    Parent;
	StringCached            Name;
	CodeT                   Type;
	ModuleFlag              ModuleFlags;
	char 			        _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Fn) == sizeof(AST), "ERROR: AST_Fn is not the same size as AST");

struct AST_Module
{
	char              _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	ModuleFlag        ModuleFlags;
	char 			  _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Module) == sizeof(AST), "ERROR: AST_Module is not the same size as AST");

struct AST_NS
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct {
			char 	  _PAD_PROPERTIES_[ sizeof(AST*) * 5 ];
			CodeBody  Body;
			char 	  _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	ModuleFlag        ModuleFlags;
	char 			  _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_NS) == sizeof(AST), "ERROR: AST_NS is not the same size as AST");

struct AST_Operator
{
	union {
		char                _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment     InlineCmt;
			CodeAttributes  Attributes;
			CodeSpecifiers  Specs;
			CodeType        ReturnType;
			CodeParam 	    Params;
			CodeBody        Body;
			char 	        _PAD_PROPERTIES_ [ sizeof(AST*) ];
		};
	};
	Code           Prev;
	Code           Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	ModuleFlag     ModuleFlags;
	OperatorT      Op;
};
static_assert( sizeof(AST_Operator) == sizeof(AST), "ERROR: AST_Operator is not the same size as AST");

struct AST_OpCast
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			char 	       _PAD_PROPERTIES_[ sizeof(AST*)  ];
			CodeSpecifiers Specs;
			CodeType       ValueType;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) ];
			CodeBody       Body;
			char 	       _PAD_PROPERTIES_3_[ sizeof(AST*) ];
		};
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_OpCast) == sizeof(AST), "ERROR: AST_OpCast is not the same size as AST");

struct AST_Param
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char 	  _PAD_PROPERTIES_2_[ sizeof(AST*) * 3 ];
			CodeType  ValueType;
			Code      Macro;
			Code      Value;
			Code     PostNameMacro; // Thanks Unreal
			// char     _PAD_PROPERTIES_3_[sizeof( AST* )];
		};
	};
	CodeParam         Last;
	CodeParam         Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) ];
	s32               NumEntries;
};
static_assert( sizeof(AST_Param) == sizeof(AST), "ERROR: AST_Param is not the same size as AST");

struct AST_Pragma
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Pragma) == sizeof(AST), "ERROR: AST_Pragma is not the same size as AST");

struct AST_PreprocessCond
{
	union {
		char          _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		StringCached  Content;
	};
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_PreprocessCond) == sizeof(AST), "ERROR: AST_PreprocessCond is not the same size as AST");

struct AST_Specifiers
{
	SpecifierT        ArrSpecs[ AST::ArrSpecs_Cap ];
	CodeSpecifiers    NextSpecs;
	Code              Prev;
	Code              Next;
	parser::Token*    Tok;
	Code              Parent;
	StringCached      Name;
	CodeT             Type;
	char 			  _PAD_UNUSED_[ sizeof(ModuleFlag) ];
	s32               NumEntries;
};
static_assert( sizeof(AST_Specifiers) == sizeof(AST), "ERROR: AST_Specifier is not the same size as AST");

#if GEN_EXECUTION_EXPRESSION_SUPPORT
struct AST_Stmt
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt) == sizeof(AST), "ERROR: AST_Stmt is not the same size as AST");

struct AST_Stmt_Break
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Break) == sizeof(AST), "ERROR: AST_Stmt_Break is not the same size as AST");

struct AST_Stmt_Case
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Case) == sizeof(AST), "ERROR: AST_Stmt_Case is not the same size as AST");

struct AST_Stmt_Continue
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Continue) == sizeof(AST), "ERROR: AST_Stmt_Continue is not the same size as AST");

struct AST_Stmt_Decl
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Decl) == sizeof(AST), "ERROR: AST_Stmt_Decl is not the same size as AST");

struct AST_Stmt_Do
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Do) == sizeof(AST), "ERROR: AST_Stmt_Do is not the same size as AST");

struct AST_Stmt_Expr
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Expr) == sizeof(AST), "ERROR: AST_Stmt_Expr is not the same size as AST");

struct AST_Stmt_Else
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Else) == sizeof(AST), "ERROR: AST_Stmt_Else is not the same size as AST");

struct AST_Stmt_If
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_If) == sizeof(AST), "ERROR: AST_Stmt_If is not the same size as AST");

struct AST_Stmt_For
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_For) == sizeof(AST), "ERROR: AST_Stmt_For is not the same size as AST");

struct AST_Stmt_Goto
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Goto) == sizeof(AST), "ERROR: AST_Stmt_Goto is not the same size as AST");

struct AST_Stmt_Label
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Label) == sizeof(AST), "ERROR: AST_Stmt_Label is not the same size as AST");

struct AST_Stmt_Switch
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_Switch) == sizeof(AST), "ERROR: AST_Stmt_Switch is not the same size as AST");

struct AST_Stmt_While
{
	union {
		char _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
	};
	CodeExpr       Prev;
	CodeExpr       Next;
	parser::Token* Tok;
	Code           Parent;
	StringCached   Name;
	CodeT          Type;
	char           _PAD_UNUSED_[ sizeof(ModuleFlag) + sizeof(u32) ];
};
static_assert( sizeof(AST_Stmt_While) == sizeof(AST), "ERROR: AST_Stmt_While is not the same size as AST");
#endif

struct AST_Struct
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			CodeAttributes Attributes;
			char 	       _PAD_SPECS_ [ sizeof(AST*) ];
			CodeType       ParentType;
			char 	       _PAD_PARAMS_[ sizeof(AST*) ];
			CodeBody       Body;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	CodeType               Prev;
	CodeType               Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	AccessSpec             ParentAccess;
};
static_assert( sizeof(AST_Struct) == sizeof(AST), "ERROR: AST_Struct is not the same size as AST");

struct AST_Template
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char 	       _PAD_PROPERTIES_[ sizeof(AST*) * 4 ];
			CodeParam 	   Params;
			Code           Declaration;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	char 			       _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Template) == sizeof(AST), "ERROR: AST_Template is not the same size as AST");

#if 0
// WIP... The type ast is going to become more advanced and lead to a major change to AST design.
struct AST_Type
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char           _PAD_INLINE_CMT_[ sizeof(AST*) ];
			CodeAttributes Attributes;
			CodeSpecifiers Specs;
			Code           QualifierID;
			// CodeType       ReturnType;      // Only used for function signatures
			// CodeParam      Params;          // Only used for function signatures
			Code           ArrExpr;
			// CodeSpecifiers SpecsFuncSuffix; // Only used for function signatures
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	char 			       _PAD_UNUSED_[ sizeof(ModuleFlag) ];
	b32                    IsParamPack;
};
static_assert( sizeof(AST_Type) == sizeof(AST), "ERROR: AST_Type is not the same size as AST");
#endif

struct AST_Type
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char           _PAD_INLINE_CMT_[ sizeof(AST*) ];
			CodeAttributes Attributes;
			CodeSpecifiers Specs;
			CodeType       ReturnType;      // Only used for function signatures
			CodeParam      Params;          // Only used for function signatures
			Code           ArrExpr;
			CodeSpecifiers SpecsFuncSuffix; // Only used for function signatures
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	char 			       _PAD_UNUSED_[ sizeof(ModuleFlag) ];
	b32                    IsParamPack;
};
static_assert( sizeof(AST_Type) == sizeof(AST), "ERROR: AST_Type is not the same size as AST");

struct AST_Typedef
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			char 	       _PAD_PROPERTIES_[ sizeof(AST*) * 2 ];
			Code           UnderlyingType;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) * 3 ];
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	b32                    IsFunction;
};
static_assert( sizeof(AST_Typedef) == sizeof(AST), "ERROR: AST_Typedef is not the same size as AST");

struct AST_Union
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			char           _PAD_INLINE_CMT_[ sizeof(AST*) ];
			CodeAttributes Attributes;
			char 	       _PAD_PROPERTIES_[ sizeof(AST*) * 3 ];
			CodeBody       Body;
			char 	       _PAD_PROPERTIES_2_[ sizeof(AST*) ];
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	char 			       _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Union) == sizeof(AST), "ERROR: AST_Union is not the same size as AST");

struct AST_Using
{
	union {
		char                _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment     InlineCmt;
			CodeAttributes  Attributes;
			char 	        _PAD_SPECS_     [ sizeof(AST*) ];
			CodeType        UnderlyingType;
			char 	        _PAD_PROPERTIES_[ sizeof(AST*) * 3 ];
		};
	};
	Code                    Prev;
	Code                    Next;
	parser::Token*          Tok;
	Code                    Parent;
	StringCached            Name;
	CodeT                   Type;
	ModuleFlag              ModuleFlags;
	char 			        _PAD_UNUSED_[ sizeof(u32) ];
};
static_assert( sizeof(AST_Using) == sizeof(AST), "ERROR: AST_Using is not the same size as AST");

struct AST_Var
{
	union {
		char               _PAD_[ sizeof(SpecifierT) * AST::ArrSpecs_Cap + sizeof(AST*) ];
		struct
		{
			CodeComment    InlineCmt;
			CodeAttributes Attributes;
			CodeSpecifiers Specs;
			CodeType       ValueType;
			Code           BitfieldSize;
			Code           Value;
			CodeVar		   NextVar;
		};
	};
	Code                   Prev;
	Code                   Next;
	parser::Token*         Tok;
	Code                   Parent;
	StringCached           Name;
	CodeT                  Type;
	ModuleFlag             ModuleFlags;
	s32                    VarConstructorInit;
};
static_assert( sizeof(AST_Var) == sizeof(AST), "ERROR: AST_Var is not the same size as AST");

#pragma endregion AST Types

#pragma endregion AST

#pragma region Gen Interface

// Initialize the library.
// This currently just initializes the CodePool.
void init();

// Currently manually free's the arenas, code for checking for leaks.
// However on Windows at least, it doesn't need to occur as the OS will clean up after the process.
void deinit();

// Clears the allocations, but doesn't return to the heap, the calls init() again.
// Ease of use.
void reset();

// Used internally to retrive or make string allocations.
// Strings are stored in a series of string arenas of fixed size (SizePer_StringArena)
StringCached get_cached_string( StrC str );

/*
	This provides a fresh Code AST.
	The gen interface use this as their method from getting a new AST object from the CodePool.
	Use this if you want to make your own API for formatting the supported Code Types.
*/
Code make_code();

// Set these before calling gen's init() procedure.

void set_allocator_data_arrays ( AllocatorInfo data_array_allocator );
void set_allocator_code_pool   ( AllocatorInfo pool_allocator );
void set_allocator_lexer       ( AllocatorInfo lex_allocator );
void set_allocator_string_arena( AllocatorInfo string_allocator );
void set_allocator_string_table( AllocatorInfo string_allocator );
void set_allocator_type_table  ( AllocatorInfo type_reg_allocator );

#pragma region Upfront

CodeAttributes def_attributes( StrC content );
CodeComment    def_comment   ( StrC content );

CodeClass def_class( StrC name
	, Code           body         = NoCode
	, CodeType       parent       = NoCode, AccessSpec access = AccessSpec::Default
	, CodeAttributes attributes   = NoCode
	, ModuleFlag     mflags       = ModuleFlag::None
	, CodeType*      interfaces   = nullptr, s32 num_interfaces = 0 );

CodeConstructor def_constructor( CodeParam params = NoCode, Code initializer_list = NoCode, Code body = NoCode );

CodeDefine def_define( StrC name, StrC content );

CodeDestructor def_destructor( Code body = NoCode, CodeSpecifiers specifiers = NoCode );

CodeEnum def_enum( StrC name
	, Code         body      = NoCode,      CodeType       type       = NoCode
	, EnumT        specifier = EnumRegular, CodeAttributes attributes = NoCode
	, ModuleFlag   mflags    = ModuleFlag::None );

CodeExec   def_execution  ( StrC content );
CodeExtern def_extern_link( StrC name, Code body );
CodeFriend def_friend     ( Code symbol );

CodeFn def_function( StrC name
	, CodeParam      params     = NoCode, CodeType       ret_type   = NoCode, Code body = NoCode
	, CodeSpecifiers specifiers = NoCode, CodeAttributes attributes = NoCode
	, ModuleFlag mflags     = ModuleFlag::None );

CodeInclude   def_include  ( StrC content, bool foreign = false );
CodeModule    def_module   ( StrC name,            ModuleFlag mflags = ModuleFlag::None );
CodeNS        def_namespace( StrC name, Code body, ModuleFlag mflags = ModuleFlag::None );

CodeOperator def_operator( OperatorT op, StrC nspace
	, CodeParam      params     = NoCode, CodeType       ret_type   = NoCode, Code body = NoCode
	, CodeSpecifiers specifiers = NoCode, CodeAttributes attributes = NoCode
	, ModuleFlag     mflags     = ModuleFlag::None );

CodeOpCast def_operator_cast( CodeType type, Code body = NoCode, CodeSpecifiers specs = NoCode );

CodeParam  def_param ( CodeType type, StrC name, Code value = NoCode );
CodePragma def_pragma( StrC directive );

CodePreprocessCond def_preprocess_cond( EPreprocessCond type, StrC content );

CodeSpecifiers def_specifier( SpecifierT specifier );

CodeStruct def_struct( StrC name
	, Code           body       = NoCode
	, CodeType       parent     = NoCode, AccessSpec access = AccessSpec::Default
	, CodeAttributes attributes = NoCode
	, ModuleFlag     mflags     = ModuleFlag::None
	, CodeType*      interfaces = nullptr, s32 num_interfaces = 0 );

CodeTemplate def_template( CodeParam params, Code definition, ModuleFlag mflags = ModuleFlag::None );

CodeType    def_type   ( StrC name, Code arrayexpr = NoCode, CodeSpecifiers specifiers = NoCode, CodeAttributes attributes = NoCode );
CodeTypedef def_typedef( StrC name, Code type, CodeAttributes attributes = NoCode, ModuleFlag mflags = ModuleFlag::None );

CodeUnion def_union( StrC name, Code body, CodeAttributes attributes = NoCode, ModuleFlag mflags = ModuleFlag::None );

CodeUsing def_using( StrC name, CodeType type = NoCode
	, CodeAttributes attributess = NoCode
	, ModuleFlag     mflags      = ModuleFlag::None );

CodeUsing def_using_namespace( StrC name );

CodeVar def_variable( CodeType type, StrC name, Code value = NoCode
	, CodeSpecifiers specifiers = NoCode, CodeAttributes attributes = NoCode
	, ModuleFlag     mflags     = ModuleFlag::None );

// Constructs an empty body. Use AST::validate_body() to check if the body is was has valid entries.
CodeBody def_body( CodeT type );

// There are two options for defining a struct body, either varadically provided with the args macro to auto-deduce the arg num,
/// or provide as an array of Code objects.

CodeBody       def_class_body      ( s32 num, ... );
CodeBody       def_class_body      ( s32 num, Code* codes );
CodeBody       def_enum_body       ( s32 num, ... );
CodeBody       def_enum_body       ( s32 num, Code* codes );
CodeBody       def_export_body     ( s32 num, ... );
CodeBody       def_export_body     ( s32 num, Code* codes);
CodeBody       def_extern_link_body( s32 num, ... );
CodeBody       def_extern_link_body( s32 num, Code* codes );
CodeBody       def_function_body   ( s32 num, ... );
CodeBody       def_function_body   ( s32 num, Code* codes );
CodeBody       def_global_body     ( s32 num, ... );
CodeBody       def_global_body     ( s32 num, Code* codes );
CodeBody       def_namespace_body  ( s32 num, ... );
CodeBody       def_namespace_body  ( s32 num, Code* codes );
CodeParam      def_params          ( s32 num, ... );
CodeParam      def_params          ( s32 num, CodeParam* params );
CodeSpecifiers def_specifiers      ( s32 num, ... );
CodeSpecifiers def_specifiers      ( s32 num, SpecifierT* specs );
CodeBody       def_struct_body     ( s32 num, ... );
CodeBody       def_struct_body     ( s32 num, Code* codes );
CodeBody       def_union_body      ( s32 num, ... );
CodeBody       def_union_body      ( s32 num, Code* codes );

#pragma endregion Upfront

#pragma region Parsing

// TODO(Ed) : Implmeent the new parser API design.

#if 0
namespace parser {
	struct StackNode
	{
		StackNode* Prev;

		Token Start;
		Token Name;       // The name of the AST node (if parsed)
		StrC  FailedProc; // The name of the procedure that failed
	};
	// Stack nodes are allocated the error's allocator

	struct Error
	{
		String     message;
		StackNode* context_stack;
	};
}

struct ParseInfo
{
	Arena FileMem;
	Arena TokMem;
	Arena CodeMem;

	FileContents         FileContent;
	Array<parser::Token> Tokens;
	Array<parser::Error> Errors;
	// Errors are allocated to a dedicated general arena.
};

CodeBody parse_file( StrC path );
#endif

CodeClass       parse_class        ( StrC class_def       );
CodeConstructor parse_constructor  ( StrC constructor_def );
CodeDestructor  parse_destructor   ( StrC destructor_def  );
CodeEnum        parse_enum         ( StrC enum_def        );
CodeBody        parse_export_body  ( StrC export_def      );
CodeExtern      parse_extern_link  ( StrC exten_link_def  );
CodeFriend      parse_friend       ( StrC friend_def      );
CodeFn          parse_function     ( StrC fn_def          );
CodeBody        parse_global_body  ( StrC body_def        );
CodeNS          parse_namespace    ( StrC namespace_def   );
CodeOperator    parse_operator     ( StrC operator_def    );
CodeOpCast      parse_operator_cast( StrC operator_def    );
CodeStruct      parse_struct       ( StrC struct_def      );
CodeTemplate    parse_template     ( StrC template_def    );
CodeType        parse_type         ( StrC type_def        );
CodeTypedef     parse_typedef      ( StrC typedef_def     );
CodeUnion       parse_union        ( StrC union_def       );
CodeUsing       parse_using        ( StrC using_def       );
CodeVar         parse_variable     ( StrC var_def         );

#pragma endregion Parsing

#pragma region Untyped text

ssize   token_fmt_va( char* buf, usize buf_size, s32 num_tokens, va_list va );
//! Do not use directly. Use the token_fmt macro instead.
StrC token_fmt_impl( ssize, ... );

Code untyped_str      ( StrC content);
Code untyped_fmt      ( char const* fmt, ... );
Code untyped_token_fmt( char const* fmt, s32 num_tokens, ... );

#pragma endregion Untyped text

#pragma endregion Gen Interface

#pragma region Inlines

inline
void AST::append( AST* other )
{
	if ( other->Parent )
		other = other->duplicate();

	other->Parent = this;

	if ( Front == nullptr )
	{
		Front = other;
		Back  = other;

		NumEntries++;
		return;
	}

	AST*
		Current       = Back;
	Current->Next = other;
	other->Prev   = Current;
	Back          = other;
	NumEntries++;
}

inline
Code& AST::entry( u32 idx )
{
	AST** current = & Front;
	while ( idx >= 0 && current != nullptr )
	{
		if ( idx == 0 )
			return * rcast( Code*, current);

		current = & ( * current )->Next;
		idx--;
	}

	return * rcast( Code*, current);
}

inline
bool AST::has_entries()
{
	return NumEntries > 0;
}

inline
char const* AST::type_str()
{
	return ECode::to_str( Type );
}

inline
AST::operator Code()
{
	return { this };
}

inline
Code& Code::operator ++()
{
	if ( ast )
		ast = ast->Next;

	return *this;
}

inline
void CodeClass::add_interface( CodeType type )
{
	CodeType possible_slot = ast->ParentType;
	if ( possible_slot.ast )
	{
		// Were adding an interface to parent type, so we need to make sure the parent type is public.
		ast->ParentAccess = AccessSpec::Public;
		// If your planning on adding a proper parent,
		// then you'll need to move this over to ParentType->next and update ParentAccess accordingly.
	}

	while ( possible_slot.ast != nullptr )
	{
		possible_slot.ast = (AST_Type*) possible_slot->Next.ast;
	}

	possible_slot.ast = type.ast;
}

inline
void CodeParam::append( CodeParam other )
{
	AST* self  = (AST*) ast;
	AST* entry = (AST*) other.ast;

	if ( entry->Parent )
		entry = entry->duplicate();

	entry->Parent = self;

	if ( self->Last == nullptr )
	{
		self->Last = entry;
		self->Next = entry;
		self->NumEntries++;
		return;
	}

	self->Last->Next = entry;
	self->Last       = entry;
	self->NumEntries++;
}

inline
CodeParam CodeParam::get( s32 idx )
{
	CodeParam param = *this;
	do
	{
		if ( ! ++ param )
			return { nullptr };

		param = { (AST_Param*) param.raw()->Next };
	}
	while ( --idx );

	return param;
}

inline
bool CodeParam::has_entries()
{
	return ast->NumEntries > 0;
}

inline
CodeParam& CodeParam::operator ++()
{
	ast = ast->Next.ast;
	return * this;
}

inline
void CodeStruct::add_interface( CodeType type )
{
	CodeType possible_slot = ast->ParentType;
	if ( possible_slot.ast )
	{
		// Were adding an interface to parent type, so we need to make sure the parent type is public.
		ast->ParentAccess = AccessSpec::Public;
		// If your planning on adding a proper parent,
		// then you'll need to move this over to ParentType->next and update ParentAccess accordingly.
	}

	while ( possible_slot.ast != nullptr )
	{
		possible_slot.ast = (AST_Type*) possible_slot->Next.ast;
	}

	possible_slot.ast = type.ast;
}

inline
CodeBody def_body( CodeT type )
{
	switch ( type )
	{
		using namespace ECode;
		case Class_Body:
		case Enum_Body:
		case Export_Body:
		case Extern_Linkage:
		case Function_Body:
		case Global_Body:
		case Namespace_Body:
		case Struct_Body:
		case Union_Body:
			break;

		default:
			log_failure( "def_body: Invalid type %s", (char const*)ECode::to_str(type) );
			return (CodeBody)Code::Invalid;
	}

	Code
	result       = make_code();
	result->Type = type;
	return (CodeBody)result;
}

inline
StrC token_fmt_impl( ssize num, ... )
{
	local_persist thread_local
	char buf[GEN_PRINTF_MAXLEN] = { 0 };
	mem_set( buf, 0, GEN_PRINTF_MAXLEN );

	va_list va;
	va_start(va, num );
	ssize result = token_fmt_va(buf, GEN_PRINTF_MAXLEN, num, va);
	va_end(va);

	return { result, buf };
}
#pragma region generated code inline implementation

inline char const* Code::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code Code::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool Code::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool Code::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void Code::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline Code& Code::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool Code::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool Code::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline Code::operator bool()
{
	return ast != nullptr;
}

inline char const* CodeBody::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeBody::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeBody::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeBody::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeBody::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeBody& CodeBody::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeBody::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeBody::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeBody::operator bool()
{
	return ast != nullptr;
}

inline char const* CodeAttributes::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeAttributes::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeAttributes::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeAttributes::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeAttributes::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeAttributes& CodeAttributes::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeAttributes::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeAttributes::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeAttributes::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeAttributes::raw()
{
	return rcast( AST*, ast );
}

inline CodeAttributes::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Attributes* CodeAttributes::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeComment::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeComment::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeComment::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeComment::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeComment::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeComment& CodeComment::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeComment::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeComment::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeComment::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeComment::raw()
{
	return rcast( AST*, ast );
}

inline CodeComment::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Comment* CodeComment::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeConstructor::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeConstructor::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeConstructor::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeConstructor::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeConstructor::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeConstructor& CodeConstructor::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeConstructor::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeConstructor::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeConstructor::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeConstructor::raw()
{
	return rcast( AST*, ast );
}

inline CodeConstructor::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Constructor* CodeConstructor::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeClass::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeClass::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeClass::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeClass::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeClass::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeClass& CodeClass::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeClass::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeClass::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeClass::operator bool()
{
	return ast != nullptr;
}

inline char const* CodeDefine::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeDefine::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeDefine::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeDefine::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeDefine::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeDefine& CodeDefine::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeDefine::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeDefine::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeDefine::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeDefine::raw()
{
	return rcast( AST*, ast );
}

inline CodeDefine::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Define* CodeDefine::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeDestructor::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeDestructor::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeDestructor::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeDestructor::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeDestructor::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeDestructor& CodeDestructor::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeDestructor::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeDestructor::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeDestructor::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeDestructor::raw()
{
	return rcast( AST*, ast );
}

inline CodeDestructor::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Destructor* CodeDestructor::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeEnum::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeEnum::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeEnum::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeEnum::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeEnum::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeEnum& CodeEnum::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeEnum::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeEnum::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeEnum::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeEnum::raw()
{
	return rcast( AST*, ast );
}

inline CodeEnum::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Enum* CodeEnum::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeExec::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeExec::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeExec::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeExec::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeExec::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeExec& CodeExec::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeExec::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeExec::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeExec::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeExec::raw()
{
	return rcast( AST*, ast );
}

inline CodeExec::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Exec* CodeExec::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeExtern::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeExtern::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeExtern::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeExtern::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeExtern::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeExtern& CodeExtern::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeExtern::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeExtern::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeExtern::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeExtern::raw()
{
	return rcast( AST*, ast );
}

inline CodeExtern::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Extern* CodeExtern::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeFriend::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeFriend::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeFriend::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeFriend::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeFriend::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeFriend& CodeFriend::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeFriend::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeFriend::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeFriend::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeFriend::raw()
{
	return rcast( AST*, ast );
}

inline CodeFriend::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Friend* CodeFriend::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeFn::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeFn::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeFn::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeFn::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeFn::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeFn& CodeFn::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeFn::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeFn::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeFn::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeFn::raw()
{
	return rcast( AST*, ast );
}

inline CodeFn::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Fn* CodeFn::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeInclude::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeInclude::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeInclude::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeInclude::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeInclude::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeInclude& CodeInclude::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeInclude::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeInclude::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeInclude::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeInclude::raw()
{
	return rcast( AST*, ast );
}

inline CodeInclude::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Include* CodeInclude::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeModule::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeModule::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeModule::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeModule::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeModule::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeModule& CodeModule::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeModule::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeModule::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeModule::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeModule::raw()
{
	return rcast( AST*, ast );
}

inline CodeModule::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Module* CodeModule::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeNS::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeNS::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeNS::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeNS::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeNS::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeNS& CodeNS::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeNS::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeNS::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeNS::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeNS::raw()
{
	return rcast( AST*, ast );
}

inline CodeNS::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_NS* CodeNS::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeOperator::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeOperator::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeOperator::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeOperator::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeOperator::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeOperator& CodeOperator::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeOperator::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeOperator::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeOperator::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeOperator::raw()
{
	return rcast( AST*, ast );
}

inline CodeOperator::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Operator* CodeOperator::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeOpCast::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeOpCast::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeOpCast::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeOpCast::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeOpCast::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeOpCast& CodeOpCast::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeOpCast::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeOpCast::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeOpCast::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeOpCast::raw()
{
	return rcast( AST*, ast );
}

inline CodeOpCast::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_OpCast* CodeOpCast::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeParam::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeParam::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeParam::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeParam::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeParam::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeParam& CodeParam::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeParam::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeParam::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeParam::operator bool()
{
	return ast != nullptr;
}

inline char const* CodePragma::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodePragma::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodePragma::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodePragma::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodePragma::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodePragma& CodePragma::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodePragma::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodePragma::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodePragma::operator bool()
{
	return ast != nullptr;
}

inline AST* CodePragma::raw()
{
	return rcast( AST*, ast );
}

inline CodePragma::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Pragma* CodePragma::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodePreprocessCond::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodePreprocessCond::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodePreprocessCond::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodePreprocessCond::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodePreprocessCond::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodePreprocessCond& CodePreprocessCond::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodePreprocessCond::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodePreprocessCond::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodePreprocessCond::operator bool()
{
	return ast != nullptr;
}

inline AST* CodePreprocessCond::raw()
{
	return rcast( AST*, ast );
}

inline CodePreprocessCond::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_PreprocessCond* CodePreprocessCond::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeSpecifiers::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeSpecifiers::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeSpecifiers::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeSpecifiers::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeSpecifiers::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeSpecifiers& CodeSpecifiers::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeSpecifiers::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeSpecifiers::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeSpecifiers::operator bool()
{
	return ast != nullptr;
}

inline char const* CodeStruct::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeStruct::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeStruct::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeStruct::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeStruct::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeStruct& CodeStruct::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeStruct::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeStruct::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeStruct::operator bool()
{
	return ast != nullptr;
}

inline char const* CodeTemplate::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeTemplate::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeTemplate::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeTemplate::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeTemplate::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeTemplate& CodeTemplate::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeTemplate::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeTemplate::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeTemplate::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeTemplate::raw()
{
	return rcast( AST*, ast );
}

inline CodeTemplate::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Template* CodeTemplate::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeType::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeType::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeType::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeType::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeType::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeType& CodeType::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeType::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeType::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeType::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeType::raw()
{
	return rcast( AST*, ast );
}

inline CodeType::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Type* CodeType::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeTypedef::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeTypedef::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeTypedef::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeTypedef::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeTypedef::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeTypedef& CodeTypedef::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeTypedef::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeTypedef::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeTypedef::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeTypedef::raw()
{
	return rcast( AST*, ast );
}

inline CodeTypedef::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Typedef* CodeTypedef::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeUnion::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeUnion::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeUnion::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeUnion::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeUnion::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeUnion& CodeUnion::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeUnion::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeUnion::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeUnion::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeUnion::raw()
{
	return rcast( AST*, ast );
}

inline CodeUnion::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Union* CodeUnion::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeUsing::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeUsing::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeUsing::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeUsing::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeUsing::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeUsing& CodeUsing::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeUsing::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeUsing::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeUsing::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeUsing::raw()
{
	return rcast( AST*, ast );
}

inline CodeUsing::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Using* CodeUsing::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

inline char const* CodeVar::debug_str()
{
	if ( ast == nullptr )
		return "Code::debug_str: AST is null!";
	return rcast( AST*, ast )->debug_str();
}

inline Code CodeVar::duplicate()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::duplicate: Cannot duplicate code, AST is null!" );
		return Code::Invalid;
	}
	return { rcast( AST*, ast )->duplicate() };
}

inline bool CodeVar::is_equal( Code other )
{
	if ( ast == nullptr || other.ast == nullptr )
	{
		return ast == nullptr && other.ast == nullptr;
	}
	return rcast( AST*, ast )->is_equal( other.ast );
}

inline bool CodeVar::is_valid()
{
	return (AST*)ast != nullptr && rcast( AST*, ast )->Type != CodeT::Invalid;
}

inline void CodeVar::set_global()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::set_global: Cannot set code as global, AST is null!" );
		return;
	}
	rcast( AST*, ast )->Parent = Code::Global.ast;
}

inline CodeVar& CodeVar::operator=( Code other )
{
	if ( other.ast && other->Parent )
	{
		ast                        = rcast( decltype( ast ), other.ast->duplicate() );
		rcast( AST*, ast )->Parent = nullptr;
	}
	ast = rcast( decltype( ast ), other.ast );
	return *this;
}

inline bool CodeVar::operator==( Code other )
{
	return (AST*)ast == other.ast;
}

inline bool CodeVar::operator!=( Code other )
{
	return (AST*)ast != other.ast;
}

inline CodeVar::operator bool()
{
	return ast != nullptr;
}

inline AST* CodeVar::raw()
{
	return rcast( AST*, ast );
}

inline CodeVar::operator Code()
{
	return *rcast( Code*, this );
}

inline AST_Var* CodeVar::operator->()
{
	if ( ast == nullptr )
	{
		log_failure( "Attempt to dereference a nullptr!" );
		return nullptr;
	}
	return ast;
}

#pragma endregion generated code inline implementation

#pragma region generated AST/Code cast implementation

inline AST::operator CodeBody()
{
	return { rcast( AST_Body*, this ) };
}

inline Code::operator CodeBody() const
{
	return { (AST_Body*)ast };
}

inline AST::operator CodeAttributes()
{
	return { rcast( AST_Attributes*, this ) };
}

inline Code::operator CodeAttributes() const
{
	return { (AST_Attributes*)ast };
}

inline AST::operator CodeComment()
{
	return { rcast( AST_Comment*, this ) };
}

inline Code::operator CodeComment() const
{
	return { (AST_Comment*)ast };
}

inline AST::operator CodeConstructor()
{
	return { rcast( AST_Constructor*, this ) };
}

inline Code::operator CodeConstructor() const
{
	return { (AST_Constructor*)ast };
}

inline AST::operator CodeClass()
{
	return { rcast( AST_Class*, this ) };
}

inline Code::operator CodeClass() const
{
	return { (AST_Class*)ast };
}

inline AST::operator CodeDefine()
{
	return { rcast( AST_Define*, this ) };
}

inline Code::operator CodeDefine() const
{
	return { (AST_Define*)ast };
}

inline AST::operator CodeDestructor()
{
	return { rcast( AST_Destructor*, this ) };
}

inline Code::operator CodeDestructor() const
{
	return { (AST_Destructor*)ast };
}

inline AST::operator CodeEnum()
{
	return { rcast( AST_Enum*, this ) };
}

inline Code::operator CodeEnum() const
{
	return { (AST_Enum*)ast };
}

inline AST::operator CodeExec()
{
	return { rcast( AST_Exec*, this ) };
}

inline Code::operator CodeExec() const
{
	return { (AST_Exec*)ast };
}

inline AST::operator CodeExtern()
{
	return { rcast( AST_Extern*, this ) };
}

inline Code::operator CodeExtern() const
{
	return { (AST_Extern*)ast };
}

inline AST::operator CodeFriend()
{
	return { rcast( AST_Friend*, this ) };
}

inline Code::operator CodeFriend() const
{
	return { (AST_Friend*)ast };
}

inline AST::operator CodeFn()
{
	return { rcast( AST_Fn*, this ) };
}

inline Code::operator CodeFn() const
{
	return { (AST_Fn*)ast };
}

inline AST::operator CodeInclude()
{
	return { rcast( AST_Include*, this ) };
}

inline Code::operator CodeInclude() const
{
	return { (AST_Include*)ast };
}

inline AST::operator CodeModule()
{
	return { rcast( AST_Module*, this ) };
}

inline Code::operator CodeModule() const
{
	return { (AST_Module*)ast };
}

inline AST::operator CodeNS()
{
	return { rcast( AST_NS*, this ) };
}

inline Code::operator CodeNS() const
{
	return { (AST_NS*)ast };
}

inline AST::operator CodeOperator()
{
	return { rcast( AST_Operator*, this ) };
}

inline Code::operator CodeOperator() const
{
	return { (AST_Operator*)ast };
}

inline AST::operator CodeOpCast()
{
	return { rcast( AST_OpCast*, this ) };
}

inline Code::operator CodeOpCast() const
{
	return { (AST_OpCast*)ast };
}

inline AST::operator CodeParam()
{
	return { rcast( AST_Param*, this ) };
}

inline Code::operator CodeParam() const
{
	return { (AST_Param*)ast };
}

inline AST::operator CodePragma()
{
	return { rcast( AST_Pragma*, this ) };
}

inline Code::operator CodePragma() const
{
	return { (AST_Pragma*)ast };
}

inline AST::operator CodePreprocessCond()
{
	return { rcast( AST_PreprocessCond*, this ) };
}

inline Code::operator CodePreprocessCond() const
{
	return { (AST_PreprocessCond*)ast };
}

inline AST::operator CodeSpecifiers()
{
	return { rcast( AST_Specifiers*, this ) };
}

inline Code::operator CodeSpecifiers() const
{
	return { (AST_Specifiers*)ast };
}

inline AST::operator CodeStruct()
{
	return { rcast( AST_Struct*, this ) };
}

inline Code::operator CodeStruct() const
{
	return { (AST_Struct*)ast };
}

inline AST::operator CodeTemplate()
{
	return { rcast( AST_Template*, this ) };
}

inline Code::operator CodeTemplate() const
{
	return { (AST_Template*)ast };
}

inline AST::operator CodeType()
{
	return { rcast( AST_Type*, this ) };
}

inline Code::operator CodeType() const
{
	return { (AST_Type*)ast };
}

inline AST::operator CodeTypedef()
{
	return { rcast( AST_Typedef*, this ) };
}

inline Code::operator CodeTypedef() const
{
	return { (AST_Typedef*)ast };
}

inline AST::operator CodeUnion()
{
	return { rcast( AST_Union*, this ) };
}

inline Code::operator CodeUnion() const
{
	return { (AST_Union*)ast };
}

inline AST::operator CodeUsing()
{
	return { rcast( AST_Using*, this ) };
}

inline Code::operator CodeUsing() const
{
	return { (AST_Using*)ast };
}

inline AST::operator CodeVar()
{
	return { rcast( AST_Var*, this ) };
}

inline Code::operator CodeVar() const
{
	return { (AST_Var*)ast };
}

#pragma endregion generated AST / Code cast implementation

#pragma endregion Inlines

#pragma region Constants

#ifndef GEN_GLOBAL_BUCKET_SIZE
#	define GEN_GLOBAL_BUCKET_SIZE megabytes(8)
#endif
#ifndef GEN_CODEPOOL_NUM_BLOCKS
#	define GEN_CODEPOOL_NUM_BLOCKS kilobytes(16)
#endif
#ifndef GEN_SIZE_PER_STRING_ARENA
#	define GEN_SIZE_PER_STRING_ARENA megabytes(1)
#endif
#ifndef GEN_MAX_COMMENT_LINE_LENGTH
#	define GEN_MAX_COMMENT_LINE_LENGTH 1024
#endif
#ifndef GEN_MAX_NAME_LENGTH
#	define GEN_MAX_NAME_LENGTH 128
#endif
#ifndef GEN_MAX_UNTYPED_STR_LENGTH
#	define GEN_MAX_UNTYPED_STR_LENGTH megabytes(1)
#endif
#ifndef GEN_TOKEN_FMT_TOKEN_MAP_MEM_SIZE
#	define GEN_TOKEN_FMT_TOKEN_MAP_MEM_SIZE kilobytes(4)
#endif
#ifndef GEN_LEX_ALLOCATOR_SIZE
#	define GEN_LEX_ALLOCATOR_SIZE megabytes(4)
#endif
#ifndef GEN_BUILDER_STR_BUFFER_RESERVE
#	define GEN_BUILDER_STR_BUFFER_RESERVE megabytes(2)
#endif

// These constexprs are used for allocation behavior of data structures
// or string handling while constructing or serializing.
// Change them to suit your needs.

constexpr s32 InitSize_DataArrays = 16;

// NOTE: This limits the maximum size of an allocation
// If you are generating a string larger than this, increase the size of the bucket here.
constexpr usize  Global_BucketSize         = GEN_GLOBAL_BUCKET_SIZE;
constexpr s32 CodePool_NumBlocks        = GEN_CODEPOOL_NUM_BLOCKS;
constexpr s32 SizePer_StringArena       = GEN_SIZE_PER_STRING_ARENA;

constexpr s32 MaxCommentLineLength      = GEN_MAX_COMMENT_LINE_LENGTH;
constexpr s32 MaxNameLength             = GEN_MAX_NAME_LENGTH;
constexpr s32 MaxUntypedStrLength       = GEN_MAX_UNTYPED_STR_LENGTH;
constexpr s32 TokenFmt_TokenMap_MemSize	= GEN_TOKEN_FMT_TOKEN_MAP_MEM_SIZE;
constexpr s32 LexAllocator_Size         = GEN_LEX_ALLOCATOR_SIZE;
constexpr s32 Builder_StrBufferReserve  = GEN_BUILDER_STR_BUFFER_RESERVE;

extern Code access_public;
extern Code access_protected;
extern Code access_private;

extern CodeAttributes attrib_api_export;
extern CodeAttributes attrib_api_import;

extern Code module_global_fragment;
extern Code module_private_fragment;

extern Code fmt_newline;

extern CodePragma pragma_once;

extern CodeParam param_varadic;

extern CodePreprocessCond preprocess_else;
extern CodePreprocessCond preprocess_endif;

extern CodeSpecifiers spec_const;
extern CodeSpecifiers spec_consteval;
extern CodeSpecifiers spec_constexpr;
extern CodeSpecifiers spec_constinit;
extern CodeSpecifiers spec_extern_linkage;
extern CodeSpecifiers spec_final;
extern CodeSpecifiers spec_forceinline;
extern CodeSpecifiers spec_global;
extern CodeSpecifiers spec_inline;
extern CodeSpecifiers spec_internal_linkage;
extern CodeSpecifiers spec_local_persist;
extern CodeSpecifiers spec_mutable;
extern CodeSpecifiers spec_neverinline;
extern CodeSpecifiers spec_noexcept;
extern CodeSpecifiers spec_override;
extern CodeSpecifiers spec_ptr;
extern CodeSpecifiers spec_pure;
extern CodeSpecifiers spec_ref;
extern CodeSpecifiers spec_register;
extern CodeSpecifiers spec_rvalue;
extern CodeSpecifiers spec_static_member;
extern CodeSpecifiers spec_thread_local;
extern CodeSpecifiers spec_virtual;
extern CodeSpecifiers spec_volatile;

extern CodeType t_empty; // Used with varaidc parameters. (Exposing just in case its useful for another circumstance)
extern CodeType t_auto;
extern CodeType t_void;
extern CodeType t_int;
extern CodeType t_bool;
extern CodeType t_char;
extern CodeType t_wchar_t;
extern CodeType t_class;
extern CodeType t_typename;

#ifdef GEN_DEFINE_LIBRARY_CODE_CONSTANTS
	// Predefined typename codes. Are set to readonly and are setup during gen::init()

	extern CodeType t_b32;

	extern CodeType t_s8;
	extern CodeType t_s16;
	extern CodeType t_s32;
	extern CodeType t_s64;

	extern CodeType t_u8;
	extern CodeType t_u16;
	extern CodeType t_u32;
	extern CodeType t_u64;

	extern CodeType t_ssize;
	extern CodeType t_usize;

	extern CodeType t_f32;
	extern CodeType t_f64;
#endif

#pragma endregion Constants

#pragma region Macros

#	define gen_main main

#	define __ NoCode

	//	Convienence for defining any name used with the gen api.
	//  Lets you provide the length and string literal to the functions without the need for the DSL.
#	define name( Id_ )   { sizeof(stringize( Id_ )) - 1, stringize(Id_) }

	//  Same as name just used to indicate intention of literal for code instead of names.
#	define code( ... ) { sizeof(stringize(__VA_ARGS__)) - 1, stringize( __VA_ARGS__ ) }

#	define args( ... ) num_args( __VA_ARGS__ ), __VA_ARGS__

#	define code_str( ... ) GEN_NS untyped_str( code( __VA_ARGS__ ) )
#	define code_fmt( ... ) GEN_NS untyped_str( token_fmt( __VA_ARGS__ ) )

	// Takes a format string (char const*) and a list of tokens (StrC) and returns a StrC of the formatted string.
#	define token_fmt( ... ) GEN_NS token_fmt_impl( (num_args( __VA_ARGS__ ) + 1) / 2, __VA_ARGS__ )

#pragma endregion Macros

// Used by the lexer to persistently treat all these identifiers as preprocessor defines.
// Populate with strings via gen::get_cached_string.
// Functional defines must have format: id( ;at minimum to indicate that the define is only valid with arguments.
extern Array< StringCached > PreprocessorDefines;

#ifdef GEN_EXPOSE_BACKEND

	// Global allocator used for data with process lifetime.
	extern AllocatorInfo  GlobalAllocator;
	extern Array< Arena > Global_AllocatorBuckets;

	extern Array< Pool >  CodePools;
	extern Array< Arena > StringArenas;

	extern StringTable StringCache;

	extern Arena LexArena;

	extern AllocatorInfo Allocator_DataArrays;
	extern AllocatorInfo Allocator_CodePool;
	extern AllocatorInfo Allocator_Lexer;
	extern AllocatorInfo Allocator_StringArena;
	extern AllocatorInfo Allocator_StringTable;
	extern AllocatorInfo Allocator_TypeTable;

#endif

#pragma region Builder

struct Builder
{
	FileInfo File;
	String   Buffer;

	static Builder open( char const* path );

	void pad_lines( s32 num );

	void print( Code );
	void print_fmt( char const* fmt, ... );

	void write();
};

#pragma endregion Builder
GEN_NS_END

#pragma region GENCPP IMPLEMENTATION GUARD
#if defined(GEN_IMPLEMENTATION) && ! defined(GEN_IMPLEMENTED)
#	define GEN_IMPLEMENTED


//! If its desired to roll your own dependencies, define GEN_ROLL_OWN_DEPENDENCIES before including this file.
// Dependencies are derived from the c-zpl library: https://github.com/zpl-c/zpl
#ifndef GEN_ROLL_OWN_DEPENDENCIES
GEN_NS_BEGIN


#pragma region Macros and Includes

#	include <stdio.h>
// NOTE: Ensure we use standard methods for these calls if we use GEN_PICO
#	if ! defined( GEN_PICO_CUSTOM_ROUTINES )
#		if ! defined( GEN_MODULE_CORE )
#			define _strlen                   strlen
#			define _printf_err( fmt, ... )   fprintf( stderr, fmt, __VA_ARGS__ )
#			define _printf_err_va( fmt, va ) vfprintf( stderr, fmt, va )
#		else
#			define _strlen                   str_len
#			define _printf_err( fmt, ... )   str_fmt_out_err( fmt, __VA_ARGS__ )
#			define _printf_err_va( fmt, va ) str_fmt_out_err_va( fmt, va )
#		endif
#	endif
#
#	include <errno.h>
#
#	if defined( GEN_SYSTEM_UNIX ) || defined( GEN_SYSTEM_MACOS )
#		include <unistd.h>
#	elif defined( GEN_SYSTEM_WINDOWS )
#		if ! defined( GEN_NO_WINDOWS_H )
#			ifndef WIN32_LEAN_AND_MEAN
#				ifndef NOMINMAX
#					define NOMINMAX
#				endif
#
#				define WIN32_LEAN_AND_MEAN
#				define WIN32_MEAN_AND_LEAN
#				define VC_EXTRALEAN
#			endif
#			include <windows.h>
#			undef NOMINMAX
#			undef WIN32_LEAN_AND_MEAN
#			undef WIN32_MEAN_AND_LEAN
#			undef VC_EXTRALEAN
#		endif
#	endif

#include <sys/stat.h>

#ifdef GEN_SYSTEM_MACOS
#	include <copyfile.h>
#endif

#ifdef GEN_SYSTEM_CYGWIN
#	include <windows.h>
#endif

#if defined( GEN_SYSTEM_WINDOWS ) && ! defined( GEN_COMPILER_GCC )
#	include <io.h>
#endif

#if defined( GEN_SYSTEM_LINUX )
#	include <sys/types.h>
#endif

#ifdef GEN_BENCHMARK
// Timing includes
#if defined( GEN_SYSTEM_MACOS ) || GEN_SYSTEM_UNIX
#	include <time.h>
#	include <sys/time.h>
#endif

#if defined( GEN_SYSTEM_MACOS )
#	include <mach/mach.h>
#	include <mach/mach_time.h>
#	include <mach/clock.h>
#endif

#if defined( GEN_SYSTEM_EMSCRIPTEN )
#	include <emscripten.h>
#endif

#if defined( GEN_SYSTEM_WINDOWS )
#	include <timezoneapi.h>
#endif
#endif

#pragma endregion Macros and Includes

#pragma region Debug

void assert_handler( char const* condition, char const* file, s32 line, char const* msg, ... )
{
	_printf_err( "%s:(%d): Assert Failure: ", file, line );

	if ( condition )
		_printf_err( "`%s` \n", condition );

	if ( msg )
	{
		va_list va;
		va_start( va, msg );
		_printf_err_va( msg, va );
		va_end( va );
	}

	_printf_err( "%s", "\n" );
}

s32 assert_crash( char const* condition )
{
	GEN_PANIC( condition );
	return 0;
}

#if defined( GEN_SYSTEM_WINDOWS )
	void process_exit( u32 code )
	{
		ExitProcess( code );
	}
#else
#	include <stdlib.h>

	void process_exit( u32 code )
	{
		exit( code );
	}
#endif

#pragma endregion Debug

#pragma region String Ops

internal
ssize _scan_zpl_i64( const char* text, s32 base, s64* value )
{
	const char* text_begin = text;
	s64         result     = 0;
	b32         negative   = false;

	if ( *text == '-' )
	{
		negative = true;
		text++;
	}

	if ( base == 16 && str_compare( text, "0x", 2 ) == 0 )
		text += 2;

	for ( ;; )
	{
		s64 v;
		if ( char_is_digit( *text ) )
			v = *text - '0';
		else if ( base == 16 && char_is_hex_digit( *text ) )
			v = hex_digit_to_int( *text );
		else
			break;

		result *= base;
		result += v;
		text++;
	}

	if ( value )
	{
		if ( negative )
			result = -result;
		*value = result;
	}

	return ( text - text_begin );
}

// TODO : Are these good enough for characters?
global const char _num_to_char_table[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"@$";

s64 str_to_i64( const char* str, char** end_ptr, s32 base )
{
	ssize  len;
	s64 value;

	if ( ! base )
	{
		if ( ( str_len( str ) > 2 ) && ( str_compare( str, "0x", 2 ) == 0 ) )
			base = 16;
		else
			base = 10;
	}

	len = _scan_zpl_i64( str, base, &value );
	if ( end_ptr )
		*end_ptr = ( char* )str + len;
	return value;
}

void i64_to_str( s64 value, char* string, s32 base )
{
	char* buf      = string;
	b32   negative = false;
	u64   v;

	if ( value < 0 )
	{
		negative = true;
		value    = -value;
	}

	v = scast( u64, value);
	if ( v != 0 )
	{
		while ( v > 0 )
		{
			*buf++  = _num_to_char_table[ v % base ];
			v      /= base;
		}
	}
	else
	{
		*buf++ = '0';
	}
	if ( negative )
		*buf++ = '-';
	*buf = '\0';
	str_reverse( string );
}

void u64_to_str( u64 value, char* string, s32 base )
{
	char* buf = string;

	if ( value )
	{
		while ( value > 0 )
		{
			*buf++  = _num_to_char_table[ value % base ];
			value  /= base;
		}
	}
	else
	{
		*buf++ = '0';
	}
	*buf = '\0';

	str_reverse( string );
}

f64 str_to_f64( const char* str, char** end_ptr )
{
	f64 result, value, sign, scale;
	s32 frac;

	while ( char_is_space( *str ) )
	{
		str++;
	}

	sign = 1.0;
	if ( *str == '-' )
	{
		sign = -1.0;
		str++;
	}
	else if ( *str == '+' )
	{
		str++;
	}

	for ( value = 0.0; char_is_digit( *str ); str++ )
	{
		value = value * 10.0 + ( *str - '0' );
	}

	if ( *str == '.' )
	{
		f64 pow10 = 10.0;
		str++;
		while ( char_is_digit( *str ) )
		{
			value += ( *str - '0' ) / pow10;
			pow10 *= 10.0;
			str++;
		}
	}

	frac  = 0;
	scale = 1.0;
	if ( ( *str == 'e' ) || ( *str == 'E' ) )
	{
		u32 exp;

		str++;
		if ( *str == '-' )
		{
			frac = 1;
			str++;
		}
		else if ( *str == '+' )
		{
			str++;
		}

		for ( exp = 0; char_is_digit( *str ); str++ )
		{
			exp = exp * 10 + ( *str - '0' );
		}
		if ( exp > 308 )
			exp = 308;

		while ( exp >= 50 )
		{
			scale *= 1e50;
			exp   -= 50;
		}
		while ( exp >= 8 )
		{
			scale *= 1e8;
			exp   -= 8;
		}
		while ( exp > 0 )
		{
			scale *= 10.0;
			exp   -= 1;
		}
	}

	result = sign * ( frac ? ( value / scale ) : ( value * scale ) );

	if ( end_ptr )
		* end_ptr = rcast( char*, ccast(char*, str) );

	return result;
}

#pragma endregion String Ops

#pragma region Printing

enum
{
	GEN_FMT_MINUS = bit( 0 ),
	GEN_FMT_PLUS  = bit( 1 ),
	GEN_FMT_ALT   = bit( 2 ),
	GEN_FMT_SPACE = bit( 3 ),
	GEN_FMT_ZERO  = bit( 4 ),

	GEN_FMT_CHAR   = bit( 5 ),
	GEN_FMT_SHORT  = bit( 6 ),
	GEN_FMT_INT    = bit( 7 ),
	GEN_FMT_LONG   = bit( 8 ),
	GEN_FMT_LLONG  = bit( 9 ),
	GEN_FMT_SIZE   = bit( 10 ),
	GEN_FMT_INTPTR = bit( 11 ),

	GEN_FMT_UNSIGNED = bit( 12 ),
	GEN_FMT_LOWER    = bit( 13 ),
	GEN_FMT_UPPER    = bit( 14 ),
	GEN_FMT_WIDTH    = bit( 15 ),

	GEN_FMT_DONE = bit( 30 ),

	GEN_FMT_INTS = GEN_FMT_CHAR | GEN_FMT_SHORT | GEN_FMT_INT | GEN_FMT_LONG | GEN_FMT_LLONG | GEN_FMT_SIZE | GEN_FMT_INTPTR
};

struct _format_info
{
	s32 base;
	s32 flags;
	s32 width;
	s32 precision;
};

internal ssize _print_string( char* text, ssize max_len, _format_info* info, char const* str )
{
	ssize    res = 0, len = 0;
	ssize    remaining = max_len;
	char* begin     = text;

	if ( str == NULL && max_len >= 6 )
	{
		res += str_copy_nulpad( text, "(null)", 6 );
		return res;
	}

	if ( info && info->precision >= 0 )
		// Made the design decision for this library that precision is the length of the string.
		len = info->precision;
	else
		len = str_len( str );

	if ( info && ( info->width == 0 && info->flags & GEN_FMT_WIDTH ) )
	{
		return res;
	}

	if ( info && ( info->width == 0 || info->flags & GEN_FMT_MINUS ) )
	{
		if ( info->precision > 0 )
			len = info->precision < len ? info->precision : len;
		if ( res + len > max_len )
			return res;
		res  += str_copy_nulpad( text, str, len );
		text += res;

		if ( info->width > res )
		{
			ssize padding = info->width - len;

			char pad = ( info->flags & GEN_FMT_ZERO ) ? '0' : ' ';
			while ( padding-- > 0 && remaining-- > 0 )
				*text++ = pad, res++;
		}
	}
	else
	{
		if ( info && ( info->width > res ) )
		{
			ssize   padding = info->width - len;
			char pad     = ( info->flags & GEN_FMT_ZERO ) ? '0' : ' ';
			while ( padding-- > 0 && remaining-- > 0 )
				*text++ = pad, res++;
		}

		if ( res + len > max_len )
			return res;
		res += str_copy_nulpad( text, str, len );
	}

	if ( info )
	{
		if ( info->flags & GEN_FMT_UPPER )
			str_to_upper( begin );
		else if ( info->flags & GEN_FMT_LOWER )
			str_to_lower( begin );
	}

	return res;
}

internal ssize _print_char( char* text, ssize max_len, _format_info* info, char arg )
{
	char str[ 2 ] = "";
	str[ 0 ]      = arg;
	return _print_string( text, max_len, info, str );
}

internal ssize _print_repeated_char( char* text, ssize max_len, _format_info* info, char arg )
{
	ssize  res = 0;
	s32 rem = ( info ) ? ( info->width > 0 ) ? info->width : 1 : 1;
	res     = rem;
	while ( rem-- > 0 )
		*text++ = arg;

	return res;
}

internal ssize _print_i64( char* text, ssize max_len, _format_info* info, s64 value )
{
	char num[ 130 ];
	i64_to_str( value, num, info ? info->base : 10 );
	return _print_string( text, max_len, info, num );
}

internal ssize _print_u64( char* text, ssize max_len, _format_info* info, u64 value )
{
	char num[ 130 ];
	u64_to_str( value, num, info ? info->base : 10 );
	return _print_string( text, max_len, info, num );
}

internal ssize _print_f64( char* text, ssize max_len, _format_info* info, b32 is_hexadecimal, f64 arg )
{
	// TODO: Handle exponent notation
	ssize    width, len, remaining = max_len;
	char* text_begin = text;

	if ( arg )
	{
		u64 value;
		if ( arg < 0 )
		{
			if ( remaining > 1 )
				*text = '-', remaining--;
			text++;
			arg = -arg;
		}
		else if ( info->flags & GEN_FMT_MINUS )
		{
			if ( remaining > 1 )
				*text = '+', remaining--;
			text++;
		}

		value  = scast( u64, arg);
		len    = _print_u64( text, remaining, NULL, value );
		text  += len;

		if ( len >= remaining )
			remaining = min( remaining, 1 );
		else
			remaining -= len;
		arg -= value;

		if ( info->precision < 0 )
			info->precision = 6;

		if ( ( info->flags & GEN_FMT_ALT ) || info->precision > 0 )
		{
			s64 mult = 10;
			if ( remaining > 1 )
				*text = '.', remaining--;
			text++;
			while ( info->precision-- > 0 )
			{
				value  = scast( u64, arg * mult );
				len    = _print_u64( text, remaining, NULL, value );
				text  += len;
				if ( len >= remaining )
					remaining = min( remaining, 1 );
				else
					remaining -= len;
				arg  -= scast( f64, value / mult);
				mult *= 10;
			}
		}
	}
	else
	{
		if ( remaining > 1 )
			*text = '0', remaining--;
		text++;
		if ( info->flags & GEN_FMT_ALT )
		{
			if ( remaining > 1 )
				*text = '.', remaining--;
			text++;
		}
	}

	width = info->width - ( text - text_begin );
	if ( width > 0 )
	{
		char  fill = ( info->flags & GEN_FMT_ZERO ) ? '0' : ' ';
		char* end  = text + remaining - 1;
		len        = ( text - text_begin );

		for ( len = ( text - text_begin ); len--; )
		{
			if ( ( text_begin + len + width ) < end )
				*( text_begin + len + width ) = *( text_begin + len );
		}

		len   = width;
		text += len;
		if ( len >= remaining )
			remaining = min( remaining, 1 );
		else
			remaining -= len;

		while ( len-- )
		{
			if ( text_begin + len < end )
				text_begin[ len ] = fill;
		}
	}

	return ( text - text_begin );
}

neverinline ssize str_fmt_va( char* text, ssize max_len, char const* fmt, va_list va )
{
	char const* text_begin = text;
	ssize          remaining  = max_len, res;

	while ( *fmt )
	{
		_format_info info = { 0 };
		ssize           len  = 0;
		info.precision    = -1;

		while ( *fmt && *fmt != '%' && remaining )
			*text++ = *fmt++;

		if ( *fmt == '%' )
		{
			do
			{
				switch ( *++fmt )
				{
					case '-' :
						{
							info.flags |= GEN_FMT_MINUS;
							break;
						}
					case '+' :
						{
							info.flags |= GEN_FMT_PLUS;
							break;
						}
					case '#' :
						{
							info.flags |= GEN_FMT_ALT;
							break;
						}
					case ' ' :
						{
							info.flags |= GEN_FMT_SPACE;
							break;
						}
					case '0' :
						{
							info.flags |= ( GEN_FMT_ZERO | GEN_FMT_WIDTH );
							break;
						}
					default :
						{
							info.flags |= GEN_FMT_DONE;
							break;
						}
				}
			} while ( ! ( info.flags & GEN_FMT_DONE ) );
		}

		// NOTE: Optional Width
		if ( *fmt == '*' )
		{
			int width = va_arg( va, int );
			if ( width < 0 )
			{
				info.flags |= GEN_FMT_MINUS;
				info.width  = -width;
			}
			else
			{
				info.width = width;
			}
			info.flags |= GEN_FMT_WIDTH;
			fmt++;
		}
		else
		{
			info.width = scast( s32, str_to_i64( fmt, ccast( char**, & fmt), 10 ));
			if ( info.width != 0 )
			{
				info.flags |= GEN_FMT_WIDTH;
			}
		}

		// NOTE: Optional Precision
		if ( *fmt == '.' )
		{
			fmt++;
			if ( *fmt == '*' )
			{
				info.precision = va_arg( va, int );
				fmt++;
			}
			else
			{
				info.precision = scast( s32, str_to_i64( fmt, ccast( char**, & fmt), 10 ));
			}
			info.flags &= ~GEN_FMT_ZERO;
		}

		switch ( *fmt++ )
		{
			case 'h' :
				if ( *fmt == 'h' )
				{    // hh => char
					info.flags |= GEN_FMT_CHAR;
					fmt++;
				}
				else
				{    // h => short
					info.flags |= GEN_FMT_SHORT;
				}
				break;

			case 'l' :
				if ( *fmt == 'l' )
				{    // ll => long long
					info.flags |= GEN_FMT_LLONG;
					fmt++;
				}
				else
				{    // l => long
					info.flags |= GEN_FMT_LONG;
				}
				break;

				break;

			case 'z' :    // NOTE: zpl_usize
				info.flags |= GEN_FMT_UNSIGNED;
				// fallthrough
			case 't' :    // NOTE: zpl_isize
				info.flags |= GEN_FMT_SIZE;
				break;

			default :
				fmt--;
				break;
		}

		switch ( *fmt )
		{
			case 'u' :
				info.flags |= GEN_FMT_UNSIGNED;
				// fallthrough
			case 'd' :
			case 'i' :
				info.base = 10;
				break;

			case 'o' :
				info.base = 8;
				break;

			case 'x' :
				info.base   = 16;
				info.flags |= ( GEN_FMT_UNSIGNED | GEN_FMT_LOWER );
				break;

			case 'X' :
				info.base   = 16;
				info.flags |= ( GEN_FMT_UNSIGNED | GEN_FMT_UPPER );
				break;

			case 'f' :
			case 'F' :
			case 'g' :
			case 'G' :
				len = _print_f64( text, remaining, &info, 0, va_arg( va, f64 ) );
				break;

			case 'a' :
			case 'A' :
				len = _print_f64( text, remaining, &info, 1, va_arg( va, f64 ) );
				break;

			case 'c' :
				len = _print_char( text, remaining, &info, scast( char, va_arg( va, int ) ));
				break;

			case 's' :
				len = _print_string( text, remaining, &info, va_arg( va, char* ) );
				break;

			case 'S':
			{
				String gen_str = String { va_arg( va, char*) };

				info.precision = gen_str.length();
				len            = _print_string( text, remaining, &info, gen_str );
			}
			break;

			case 'r' :
				len = _print_repeated_char( text, remaining, &info, va_arg( va, int ) );
				break;

			case 'p' :
				info.base   = 16;
				info.flags |= ( GEN_FMT_LOWER | GEN_FMT_UNSIGNED | GEN_FMT_ALT | GEN_FMT_INTPTR );
				break;

			case '%' :
				len = _print_char( text, remaining, &info, '%' );
				break;

			default :
				fmt--;
				break;
		}

		fmt++;

		if ( info.base != 0 )
		{
			if ( info.flags & GEN_FMT_UNSIGNED )
			{
				u64 value = 0;
				switch ( info.flags & GEN_FMT_INTS )
				{
					case GEN_FMT_CHAR :
						value = scast( u64, scast( u8, va_arg( va, int )));
						break;
					case GEN_FMT_SHORT :
						value = scast( u64, scast( u16, va_arg( va, int )));
						break;
					case GEN_FMT_LONG:
						value = scast( u64, va_arg( va, unsigned long ));
						break;
					case GEN_FMT_LLONG :
						value = scast( u64, va_arg( va, unsigned long long ));
						break;
					case GEN_FMT_SIZE :
						value = scast( u64, va_arg( va, usize ));
						break;
					case GEN_FMT_INTPTR :
						value = scast( u64, va_arg( va, uptr ));
						break;
					default :
						value = scast( u64, va_arg( va, unsigned int ));
						break;
				}

				len = _print_u64( text, remaining, &info, value );
			}
			else
			{
				s64 value = 0;
				switch ( info.flags & GEN_FMT_INTS )
				{
					case GEN_FMT_CHAR :
						value = scast( s64, scast( s8, va_arg( va, int )));
						break;
					case GEN_FMT_SHORT :
						value = scast( s64, scast( s16, va_arg( va, int )));
						break;
					case GEN_FMT_LONG :
						value = scast( s64, va_arg( va, long ));
						break;
					case GEN_FMT_LLONG :
						value = scast( s64, va_arg( va, long long ));
						break;
					case GEN_FMT_SIZE :
						value = scast( s64, va_arg( va, usize ));
						break;
					case GEN_FMT_INTPTR :
						value = scast( s64, va_arg( va, uptr ));
						break;
					default :
						value = scast( s64, va_arg( va, int ));
						break;
				}

				len = _print_i64( text, remaining, &info, value );
			}
		}

		text += len;
		if ( len >= remaining )
			remaining = min( remaining, 1 );
		else
			remaining -= len;
	}

	*text++ = '\0';
	res     = ( text - text_begin );
	return ( res >= max_len || res < 0 ) ? -1 : res;
}

char* str_fmt_buf_va( char const* fmt, va_list va )
{
	local_persist thread_local char buffer[ GEN_PRINTF_MAXLEN ];
	str_fmt_va( buffer, size_of( buffer ), fmt, va );
	return buffer;
}

char* str_fmt_buf( char const* fmt, ... )
{
	va_list va;
	char*   str;
	va_start( va, fmt );
	str = str_fmt_buf_va( fmt, va );
	va_end( va );
	return str;
}

ssize str_fmt_file_va( struct FileInfo* f, char const* fmt, va_list va )
{
	local_persist thread_local char buf[ GEN_PRINTF_MAXLEN ];
	ssize                              len = str_fmt_va( buf, size_of( buf ), fmt, va );
	b32                             res = file_write( f, buf, len - 1 );    // NOTE: prevent extra whitespace
	return res ? len : -1;
}

ssize str_fmt_file( struct FileInfo* f, char const* fmt, ... )
{
	ssize      res;
	va_list va;
	va_start( va, fmt );
	res = str_fmt_file_va( f, fmt, va );
	va_end( va );
	return res;
}

ssize str_fmt( char* str, ssize n, char const* fmt, ... )
{
	ssize      res;
	va_list va;
	va_start( va, fmt );
	res = str_fmt_va( str, n, fmt, va );
	va_end( va );
	return res;
}

ssize str_fmt_out_va( char const* fmt, va_list va )
{
	return str_fmt_file_va( file_get_standard( EFileStandard_OUTPUT ), fmt, va );
}

ssize str_fmt_out_err_va( char const* fmt, va_list va )
{
	return str_fmt_file_va( file_get_standard( EFileStandard_ERROR ), fmt, va );
}

ssize str_fmt_out_err( char const* fmt, ... )
{
	ssize      res;
	va_list va;
	va_start( va, fmt );
	res = str_fmt_out_err_va( fmt, va );
	va_end( va );
	return res;
}

#pragma endregion Printing

#pragma region Memory

void* mem_copy( void* dest, void const* source, ssize n )
{
	if ( dest == NULL )
	{
		return NULL;
	}

	return memcpy( dest, source, n );
}

void const* mem_find( void const* data, u8 c, ssize n )
{
	u8 const* s = rcast( u8 const*, data);
	while ( ( rcast( uptr, s) & ( sizeof( usize ) - 1 ) ) && n && *s != c )
	{
		s++;
		n--;
	}
	if ( n && *s != c )
	{
		ssize const* w;
		ssize        k = GEN__ONES * c;
		w           = rcast( ssize const*, s);
		while ( n >= size_of( ssize ) && ! GEN__HAS_ZERO( *w ^ k ) )
		{
			w++;
			n -= size_of( ssize );
		}
		s = rcast( u8 const*, w);
		while ( n && *s != c )
		{
			s++;
			n--;
		}
	}

	return n ? rcast( void const*, s ) : NULL;
}

#define GEN_HEAP_STATS_MAGIC 0xDEADC0DE

struct _heap_stats
{
	u32 magic;
	ssize  used_memory;
	ssize  alloc_count;
};

global _heap_stats _heap_stats_info;

void heap_stats_init( void )
{
	zero_item( &_heap_stats_info );
	_heap_stats_info.magic = GEN_HEAP_STATS_MAGIC;
}

ssize heap_stats_used_memory( void )
{
	GEN_ASSERT_MSG( _heap_stats_info.magic == GEN_HEAP_STATS_MAGIC, "heap_stats is not initialised yet, call heap_stats_init first!" );
	return _heap_stats_info.used_memory;
}

ssize heap_stats_alloc_count( void )
{
	GEN_ASSERT_MSG( _heap_stats_info.magic == GEN_HEAP_STATS_MAGIC, "heap_stats is not initialised yet, call heap_stats_init first!" );
	return _heap_stats_info.alloc_count;
}

void heap_stats_check( void )
{
	GEN_ASSERT_MSG( _heap_stats_info.magic == GEN_HEAP_STATS_MAGIC, "heap_stats is not initialised yet, call heap_stats_init first!" );
	GEN_ASSERT( _heap_stats_info.used_memory == 0 );
	GEN_ASSERT( _heap_stats_info.alloc_count == 0 );
}

struct _heap_alloc_info
{
	ssize    size;
	void* physical_start;
};

void* heap_allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags )
{
	void* ptr = NULL;
	// unused( allocator_data );
	// unused( old_size );
	if ( ! alignment )
		alignment = GEN_DEFAULT_MEMORY_ALIGNMENT;

#ifdef GEN_HEAP_ANALYSIS
	ssize alloc_info_size      = size_of( _heap_alloc_info );
	ssize alloc_info_remainder = ( alloc_info_size % alignment );
	ssize track_size           = max( alloc_info_size, alignment ) + alloc_info_remainder;
	switch ( type )
	{
		case EAllocation_FREE :
			{
				if ( ! old_memory )
					break;
				_heap_alloc_info* alloc_info  = rcast( _heap_alloc_info*, old_memory) - 1;
				_heap_stats_info.used_memory -= alloc_info->size;
				_heap_stats_info.alloc_count--;
				old_memory = alloc_info->physical_start;
			}
			break;
		case EAllocation_ALLOC :
			{
				size += track_size;
			}
			break;
		default :
			break;
	}
#endif

	switch ( type )
	{
#if defined( GEN_COMPILER_MSVC ) || ( defined( GEN_COMPILER_GCC ) && defined( GEN_SYSTEM_WINDOWS ) ) || ( defined( GEN_COMPILER_TINYC ) && defined( GEN_SYSTEM_WINDOWS ) )
		case EAllocation_ALLOC :
			ptr = _aligned_malloc( size, alignment );
			if ( flags & ALLOCATOR_FLAG_CLEAR_TO_ZERO )
				zero_size( ptr, size );
			break;
		case EAllocation_FREE :
			_aligned_free( old_memory );
			break;
		case EAllocation_RESIZE :
			{
				AllocatorInfo a = heap();
				ptr             = default_resize_align( a, old_memory, old_size, size, alignment );
			}
			break;

#elif defined( GEN_SYSTEM_LINUX ) && ! defined( GEN_CPU_ARM ) && ! defined( GEN_COMPILER_TINYC )
		case EAllocation_ALLOC :
			{
				ptr = aligned_alloc( alignment, ( size + alignment - 1 ) & ~( alignment - 1 ) );

				if ( flags & GEN_ALLOCATOR_FLAG_CLEAR_TO_ZERO )
				{
					zero_size( ptr, size );
				}
			}
			break;

		case EAllocation_FREE :
			{
				free( old_memory );
			}
			break;

		case EAllocation_RESIZE :
			{
				AllocatorInfo a = heap();
				ptr             = default_resize_align( a, old_memory, old_size, size, alignment );
			}
			break;
#else
		case EAllocation_ALLOC :
			{
				posix_memalign( &ptr, alignment, size );

				if ( flags & GEN_ALLOCATOR_FLAG_CLEAR_TO_ZERO )
				{
					zero_size( ptr, size );
				}
			}
			break;

		case EAllocation_FREE :
			{
				free( old_memory );
			}
			break;

		case EAllocation_RESIZE :
			{
				AllocatorInfo a = heap();
				ptr             = default_resize_align( a, old_memory, old_size, size, alignment );
			}
			break;
#endif

		case EAllocation_FREE_ALL :
			break;
	}

#ifdef GEN_HEAP_ANALYSIS
	if ( type == EAllocation_ALLOC )
	{
		_heap_alloc_info* alloc_info = rcast( _heap_alloc_info*, rcast( char*, ptr) + alloc_info_remainder );
		zero_item( alloc_info );
		alloc_info->size              = size - track_size;
		alloc_info->physical_start    = ptr;
		ptr                           = rcast( void*, alloc_info + 1 );
		_heap_stats_info.used_memory += alloc_info->size;
		_heap_stats_info.alloc_count++;
	}
#endif

	return ptr;
}

#pragma region VirtualMemory
VirtualMemory vm_from_memory( void* data, ssize size )
{
	VirtualMemory vm;
	vm.data = data;
	vm.size = size;
	return vm;
}

#if defined( GEN_SYSTEM_WINDOWS )
VirtualMemory vm_alloc( void* addr, ssize size )
{
	VirtualMemory vm;
	GEN_ASSERT( size > 0 );
	vm.data = VirtualAlloc( addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	vm.size = size;
	return vm;
}

b32 vm_free( VirtualMemory vm )
{
	MEMORY_BASIC_INFORMATION info;
	while ( vm.size > 0 )
	{
		if ( VirtualQuery( vm.data, &info, size_of( info ) ) == 0 )
			return false;
		if ( info.BaseAddress != vm.data || info.AllocationBase != vm.data || info.State != MEM_COMMIT || info.RegionSize > scast( usize, vm.size) )
		{
			return false;
		}
		if ( VirtualFree( vm.data, 0, MEM_RELEASE ) == 0 )
			return false;
		vm.data  = pointer_add( vm.data, info.RegionSize );
		vm.size -= info.RegionSize;
	}
	return true;
}

VirtualMemory vm_trim( VirtualMemory vm, ssize lead_size, ssize size )
{
	VirtualMemory new_vm = { 0 };
	void*             ptr;
	GEN_ASSERT( vm.size >= lead_size + size );

	ptr = pointer_add( vm.data, lead_size );

	vm_free( vm );
	new_vm = vm_alloc( ptr, size );
	if ( new_vm.data == ptr )
		return new_vm;
	if ( new_vm.data )
		vm_free( new_vm );
	return new_vm;
}

b32 vm_purge( VirtualMemory vm )
{
	VirtualAlloc( vm.data, vm.size, MEM_RESET, PAGE_READWRITE );
	// NOTE: Can this really fail?
	return true;
}

ssize virtual_memory_page_size( ssize* alignment_out )
{
	SYSTEM_INFO info;
	GetSystemInfo( &info );
	if ( alignment_out )
		*alignment_out = info.dwAllocationGranularity;
	return info.dwPageSize;
}

#else
#	include <sys/mman.h>

#	ifndef MAP_ANONYMOUS
#		define MAP_ANONYMOUS MAP_ANON
#	endif
VirtualMemory vm_alloc( void* addr, ssize size )
{
	VirtualMemory vm;
	GEN_ASSERT( size > 0 );
	vm.data = mmap( addr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0 );
	vm.size = size;
	return vm;
}

b32 vm_free( VirtualMemory vm )
{
	munmap( vm.data, vm.size );
	return true;
}

VirtualMemory vm_trim( VirtualMemory vm, ssize lead_size, ssize size )
{
	void*  ptr;
	ssize trail_size;
	GEN_ASSERT( vm.size >= lead_size + size );

	ptr        = pointer_add( vm.data, lead_size );
	trail_size = vm.size - lead_size - size;

	if ( lead_size != 0 )
		vm_free( vm_from_memory(( vm.data, lead_size ) );
	if ( trail_size != 0 )
		vm_free( vm_from_memory( ptr, trail_size ) );
	return vm_from_memory( ptr, size );
}

b32 vm_purge( VirtualMemory vm )
{
	int err = madvise( vm.data, vm.size, MADV_DONTNEED );
	return err != 0;
}

ssize virtual_memory_page_size( ssize* alignment_out )
{
	// TODO: Is this always true?
	ssize result = scast( ssize, sysconf( _SC_PAGE_SIZE ));
	if ( alignment_out )
		*alignment_out = result;
	return result;
}
#endif

#pragma endregion VirtualMemory

void* Arena::allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags )
{
	Arena* arena = rcast(Arena*, allocator_data);
	void*      ptr   = NULL;

	// unused( old_size );

	switch ( type )
	{
		case EAllocation_ALLOC :
			{
				void* end        = pointer_add( arena->PhysicalStart, arena->TotalUsed );
				ssize    total_size = align_forward_i64( size, alignment );

				// NOTE: Out of memory
				if ( arena->TotalUsed + total_size > (ssize) arena->TotalSize )
				{
					// zpl__printf_err("%s", "Arena out of memory\n");
					GEN_FATAL("Arena out of memory! (Possibly could not fit for the largest size Arena!!)");
					return nullptr;
				}

				ptr              = align_forward( end, alignment );
				arena->TotalUsed += total_size;

				if ( flags & ALLOCATOR_FLAG_CLEAR_TO_ZERO )
					zero_size( ptr, size );
			}
			break;

		case EAllocation_FREE :
			// NOTE: Free all at once
			// Use Temp_Arena_Memory if you want to free a block
			break;

		case EAllocation_FREE_ALL :
			arena->TotalUsed = 0;
			break;

		case EAllocation_RESIZE :
			{
				// TODO : Check if ptr is on top of stack and just extend
				AllocatorInfo a = arena->Backing;
				ptr             = default_resize_align( a, old_memory, old_size, size, alignment );
			}
			break;
	}
	return ptr;
}

void* Pool::allocator_proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags )
{
	Pool* pool = rcast( Pool*, allocator_data);
	void* ptr  = NULL;

	// unused( old_size );

	switch ( type )
	{
		case EAllocation_ALLOC :
			{
				uptr next_free;

				GEN_ASSERT( size == pool->BlockSize );
				GEN_ASSERT( alignment == pool->BlockAlign );
				GEN_ASSERT( pool->FreeList != NULL );

				next_free        = * rcast( uptr*, pool->FreeList);
				ptr              = pool->FreeList;
				pool->FreeList   = rcast( void*, next_free);
				pool->TotalSize += pool->BlockSize;

				if ( flags & ALLOCATOR_FLAG_CLEAR_TO_ZERO )
					zero_size( ptr, size );
			}
			break;

		case EAllocation_FREE :
			{
				uptr* next;
				if ( old_memory == NULL )
					return NULL;

				next             = rcast( uptr*, old_memory);
				*next            = rcast( uptr, pool->FreeList);
				pool->FreeList   = old_memory;
				pool->TotalSize -= pool->BlockSize;
			}
			break;

		case EAllocation_FREE_ALL :
			{
				ssize    actual_block_size, block_index;
				void* curr;
				uptr* end;

				actual_block_size = pool->BlockSize + pool->BlockAlign;
				pool->TotalSize   = 0;

				// NOTE: Init intrusive freelist
				curr = pool->PhysicalStart;
				for ( block_index = 0; block_index < pool->NumBlocks - 1; block_index++ )
				{
					uptr* next = rcast( uptr*, curr);
					* next     = rcast( uptr, curr) + actual_block_size;
					curr       = pointer_add( curr, actual_block_size );
				}

				end            = rcast( uptr*, curr);
				* end          = scast( uptr, NULL);
				pool->FreeList = pool->PhysicalStart;
			}
			break;

		case EAllocation_RESIZE :
			// NOTE: Cannot resize
			GEN_PANIC( "You cannot resize something allocated by with a pool." );
			break;
	}

	return ptr;
}

Pool Pool::init_align( AllocatorInfo backing, ssize num_blocks, ssize block_size, ssize block_align )
{
	Pool pool = {};

	ssize    actual_block_size, pool_size, block_index;
	void *data, *curr;
	uptr* end;

	zero_item( &pool );

	pool.Backing     = backing;
	pool.BlockSize   = block_size;
	pool.BlockAlign  = block_align;
	pool.NumBlocks   = num_blocks;

	actual_block_size = block_size + block_align;
	pool_size         = num_blocks * actual_block_size;

	data = alloc_align( backing, pool_size, block_align );

	// NOTE: Init intrusive freelist
	curr = data;
	for ( block_index = 0; block_index < num_blocks - 1; block_index++ )
	{
		uptr* next = ( uptr* ) curr;
		*next      = ( uptr  ) curr + actual_block_size;
		curr       = pointer_add( curr, actual_block_size );
	}

	end  =  ( uptr* ) curr;
	*end =  ( uptr )  NULL;

	pool.PhysicalStart = data;
	pool.FreeList      = data;

	return pool;
}

void Pool::clear()
{
	ssize    actual_block_size, block_index;
	void* curr;
	uptr* end;

	actual_block_size = BlockSize + BlockAlign;

	curr = PhysicalStart;
	for ( block_index = 0; block_index < NumBlocks - 1; block_index++ )
	{
		uptr* next = ( uptr* ) curr;
		*next      = ( uptr  ) curr + actual_block_size;
		curr       = pointer_add( curr, actual_block_size );
	}

	end  =  ( uptr* ) curr;
	*end =  ( uptr )  NULL;

	FreeList = PhysicalStart;
}

#pragma endregion Memory

#pragma region Hashing

global u32 const _crc32_table[ 256 ] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd,
	0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
	0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce,
	0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0,
	0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703,
	0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5,
	0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

u32 crc32( void const* data, ssize len )
{
	ssize        remaining;
	u32       result = ~( scast( u32, 0) );
	u8 const* c      = rcast( u8 const*, data);
	for ( remaining = len; remaining--; c++ )
		result = ( result >> 8 ) ^ ( _crc32_table[ ( result ^ *c ) & 0xff ] );
	return ~result;
}

global u64 const _crc64_table[ 256 ] = {
	0x0000000000000000ull, 0x7ad870c830358979ull, 0xf5b0e190606b12f2ull, 0x8f689158505e9b8bull, 0xc038e5739841b68full, 0xbae095bba8743ff6ull, 0x358804e3f82aa47dull,
	0x4f50742bc81f2d04ull, 0xab28ecb46814fe75ull, 0xd1f09c7c5821770cull, 0x5e980d24087fec87ull, 0x24407dec384a65feull, 0x6b1009c7f05548faull, 0x11c8790fc060c183ull,
	0x9ea0e857903e5a08ull, 0xe478989fa00bd371ull, 0x7d08ff3b88be6f81ull, 0x07d08ff3b88be6f8ull, 0x88b81eabe8d57d73ull, 0xf2606e63d8e0f40aull, 0xbd301a4810ffd90eull,
	0xc7e86a8020ca5077ull, 0x4880fbd87094cbfcull, 0x32588b1040a14285ull, 0xd620138fe0aa91f4ull, 0xacf86347d09f188dull, 0x2390f21f80c18306ull, 0x594882d7b0f40a7full,
	0x1618f6fc78eb277bull, 0x6cc0863448deae02ull, 0xe3a8176c18803589ull, 0x997067a428b5bcf0ull, 0xfa11fe77117cdf02ull, 0x80c98ebf2149567bull, 0x0fa11fe77117cdf0ull,
	0x75796f2f41224489ull, 0x3a291b04893d698dull, 0x40f16bccb908e0f4ull, 0xcf99fa94e9567b7full, 0xb5418a5cd963f206ull, 0x513912c379682177ull, 0x2be1620b495da80eull,
	0xa489f35319033385ull, 0xde51839b2936bafcull, 0x9101f7b0e12997f8ull, 0xebd98778d11c1e81ull, 0x64b116208142850aull, 0x1e6966e8b1770c73ull, 0x8719014c99c2b083ull,
	0xfdc17184a9f739faull, 0x72a9e0dcf9a9a271ull, 0x08719014c99c2b08ull, 0x4721e43f0183060cull, 0x3df994f731b68f75ull, 0xb29105af61e814feull, 0xc849756751dd9d87ull,
	0x2c31edf8f1d64ef6ull, 0x56e99d30c1e3c78full, 0xd9810c6891bd5c04ull, 0xa3597ca0a188d57dull, 0xec09088b6997f879ull, 0x96d1784359a27100ull, 0x19b9e91b09fcea8bull,
	0x636199d339c963f2ull, 0xdf7adabd7a6e2d6full, 0xa5a2aa754a5ba416ull, 0x2aca3b2d1a053f9dull, 0x50124be52a30b6e4ull, 0x1f423fcee22f9be0ull, 0x659a4f06d21a1299ull,
	0xeaf2de5e82448912ull, 0x902aae96b271006bull, 0x74523609127ad31aull, 0x0e8a46c1224f5a63ull, 0x81e2d7997211c1e8ull, 0xfb3aa75142244891ull, 0xb46ad37a8a3b6595ull,
	0xceb2a3b2ba0eececull, 0x41da32eaea507767ull, 0x3b024222da65fe1eull, 0xa2722586f2d042eeull, 0xd8aa554ec2e5cb97ull, 0x57c2c41692bb501cull, 0x2d1ab4dea28ed965ull,
	0x624ac0f56a91f461ull, 0x1892b03d5aa47d18ull, 0x97fa21650afae693ull, 0xed2251ad3acf6feaull, 0x095ac9329ac4bc9bull, 0x7382b9faaaf135e2ull, 0xfcea28a2faafae69ull,
	0x8632586aca9a2710ull, 0xc9622c4102850a14ull, 0xb3ba5c8932b0836dull, 0x3cd2cdd162ee18e6ull, 0x460abd1952db919full, 0x256b24ca6b12f26dull, 0x5fb354025b277b14ull,
	0xd0dbc55a0b79e09full, 0xaa03b5923b4c69e6ull, 0xe553c1b9f35344e2ull, 0x9f8bb171c366cd9bull, 0x10e3202993385610ull, 0x6a3b50e1a30ddf69ull, 0x8e43c87e03060c18ull,
	0xf49bb8b633338561ull, 0x7bf329ee636d1eeaull, 0x012b592653589793ull, 0x4e7b2d0d9b47ba97ull, 0x34a35dc5ab7233eeull, 0xbbcbcc9dfb2ca865ull, 0xc113bc55cb19211cull,
	0x5863dbf1e3ac9decull, 0x22bbab39d3991495ull, 0xadd33a6183c78f1eull, 0xd70b4aa9b3f20667ull, 0x985b3e827bed2b63ull, 0xe2834e4a4bd8a21aull, 0x6debdf121b863991ull,
	0x1733afda2bb3b0e8ull, 0xf34b37458bb86399ull, 0x8993478dbb8deae0ull, 0x06fbd6d5ebd3716bull, 0x7c23a61ddbe6f812ull, 0x3373d23613f9d516ull, 0x49aba2fe23cc5c6full,
	0xc6c333a67392c7e4ull, 0xbc1b436e43a74e9dull, 0x95ac9329ac4bc9b5ull, 0xef74e3e19c7e40ccull, 0x601c72b9cc20db47ull, 0x1ac40271fc15523eull, 0x5594765a340a7f3aull,
	0x2f4c0692043ff643ull, 0xa02497ca54616dc8ull, 0xdafce7026454e4b1ull, 0x3e847f9dc45f37c0ull, 0x445c0f55f46abeb9ull, 0xcb349e0da4342532ull, 0xb1eceec59401ac4bull,
	0xfebc9aee5c1e814full, 0x8464ea266c2b0836ull, 0x0b0c7b7e3c7593bdull, 0x71d40bb60c401ac4ull, 0xe8a46c1224f5a634ull, 0x927c1cda14c02f4dull, 0x1d148d82449eb4c6ull,
	0x67ccfd4a74ab3dbfull, 0x289c8961bcb410bbull, 0x5244f9a98c8199c2ull, 0xdd2c68f1dcdf0249ull, 0xa7f41839ecea8b30ull, 0x438c80a64ce15841ull, 0x3954f06e7cd4d138ull,
	0xb63c61362c8a4ab3ull, 0xcce411fe1cbfc3caull, 0x83b465d5d4a0eeceull, 0xf96c151de49567b7ull, 0x76048445b4cbfc3cull, 0x0cdcf48d84fe7545ull, 0x6fbd6d5ebd3716b7ull,
	0x15651d968d029fceull, 0x9a0d8ccedd5c0445ull, 0xe0d5fc06ed698d3cull, 0xaf85882d2576a038ull, 0xd55df8e515432941ull, 0x5a3569bd451db2caull, 0x20ed197575283bb3ull,
	0xc49581ead523e8c2ull, 0xbe4df122e51661bbull, 0x3125607ab548fa30ull, 0x4bfd10b2857d7349ull, 0x04ad64994d625e4dull, 0x7e7514517d57d734ull, 0xf11d85092d094cbfull,
	0x8bc5f5c11d3cc5c6ull, 0x12b5926535897936ull, 0x686de2ad05bcf04full, 0xe70573f555e26bc4ull, 0x9ddd033d65d7e2bdull, 0xd28d7716adc8cfb9ull, 0xa85507de9dfd46c0ull,
	0x273d9686cda3dd4bull, 0x5de5e64efd965432ull, 0xb99d7ed15d9d8743ull, 0xc3450e196da80e3aull, 0x4c2d9f413df695b1ull, 0x36f5ef890dc31cc8ull, 0x79a59ba2c5dc31ccull,
	0x037deb6af5e9b8b5ull, 0x8c157a32a5b7233eull, 0xf6cd0afa9582aa47ull, 0x4ad64994d625e4daull, 0x300e395ce6106da3ull, 0xbf66a804b64ef628ull, 0xc5bed8cc867b7f51ull,
	0x8aeeace74e645255ull, 0xf036dc2f7e51db2cull, 0x7f5e4d772e0f40a7ull, 0x05863dbf1e3ac9deull, 0xe1fea520be311aafull, 0x9b26d5e88e0493d6ull, 0x144e44b0de5a085dull,
	0x6e963478ee6f8124ull, 0x21c640532670ac20ull, 0x5b1e309b16452559ull, 0xd476a1c3461bbed2ull, 0xaeaed10b762e37abull, 0x37deb6af5e9b8b5bull, 0x4d06c6676eae0222ull,
	0xc26e573f3ef099a9ull, 0xb8b627f70ec510d0ull, 0xf7e653dcc6da3dd4ull, 0x8d3e2314f6efb4adull, 0x0256b24ca6b12f26ull, 0x788ec2849684a65full, 0x9cf65a1b368f752eull,
	0xe62e2ad306bafc57ull, 0x6946bb8b56e467dcull, 0x139ecb4366d1eea5ull, 0x5ccebf68aecec3a1ull, 0x2616cfa09efb4ad8ull, 0xa97e5ef8cea5d153ull, 0xd3a62e30fe90582aull,
	0xb0c7b7e3c7593bd8ull, 0xca1fc72bf76cb2a1ull, 0x45775673a732292aull, 0x3faf26bb9707a053ull, 0x70ff52905f188d57ull, 0x0a2722586f2d042eull, 0x854fb3003f739fa5ull,
	0xff97c3c80f4616dcull, 0x1bef5b57af4dc5adull, 0x61372b9f9f784cd4ull, 0xee5fbac7cf26d75full, 0x9487ca0fff135e26ull, 0xdbd7be24370c7322ull, 0xa10fceec0739fa5bull,
	0x2e675fb4576761d0ull, 0x54bf2f7c6752e8a9ull, 0xcdcf48d84fe75459ull, 0xb71738107fd2dd20ull, 0x387fa9482f8c46abull, 0x42a7d9801fb9cfd2ull, 0x0df7adabd7a6e2d6ull,
	0x772fdd63e7936bafull, 0xf8474c3bb7cdf024ull, 0x829f3cf387f8795dull, 0x66e7a46c27f3aa2cull, 0x1c3fd4a417c62355ull, 0x935745fc4798b8deull, 0xe98f353477ad31a7ull,
	0xa6df411fbfb21ca3ull, 0xdc0731d78f8795daull, 0x536fa08fdfd90e51ull, 0x29b7d047efec8728ull,
};

u64 crc64( void const* data, ssize len )
{
	ssize        remaining;
	u64       result = ( scast( u64, 0) );
	u8 const* c      = rcast( u8 const*, data);
	for ( remaining = len; remaining--; c++ )
		result = ( result >> 8 ) ^ ( _crc64_table[ ( result ^ *c ) & 0xff ] );
	return result;
}

#pragma endregion Hashing

#pragma region String

String String::fmt( AllocatorInfo allocator, char* buf, ssize buf_size, char const* fmt, ... )
{
	va_list va;
	va_start( va, fmt );
	str_fmt_va( buf, buf_size, fmt, va );
	va_end( va );

	return make( allocator, buf );
}

String String::make_length( AllocatorInfo allocator, char const* str, ssize length )
{
	constexpr ssize header_size = sizeof( Header );

	s32   alloc_size = header_size + length + 1;
	void* allocation = alloc( allocator, alloc_size );

	if ( allocation == nullptr )
		return { nullptr };

	Header&
	header = * rcast(Header*, allocation);
	header = { allocator, length, length };

	String  result = { rcast( char*, allocation) + header_size };

	if ( length && str )
		mem_copy( result, str, length );
	else
		mem_set( result, 0, alloc_size - header_size );

	result[ length ] = '\0';

	return result;
}

String String::make_reserve( AllocatorInfo allocator, ssize capacity )
{
	constexpr ssize header_size = sizeof( Header );

	s32   alloc_size = header_size + capacity + 1;
	void* allocation = alloc( allocator, alloc_size );

	if ( allocation == nullptr )
		return { nullptr };

	mem_set( allocation, 0, alloc_size );

	Header*
		header            = rcast(Header*, allocation);
	header->Allocator = allocator;
	header->Capacity  = capacity;
	header->Length    = 0;

	String result = { rcast(char*, allocation) + header_size };
	return result;
}

String String::fmt_buf( AllocatorInfo allocator, char const* fmt, ... )
{
	local_persist thread_local
	char buf[ GEN_PRINTF_MAXLEN ] = { 0 };

	va_list va;
	va_start( va, fmt );
	str_fmt_va( buf, GEN_PRINTF_MAXLEN, fmt, va );
	va_end( va );

	return make( allocator, buf );
}

bool String::append_fmt( char const* fmt, ... )
{
	ssize   res;
	char buf[ GEN_PRINTF_MAXLEN ] = { 0 };

	va_list va;
	va_start( va, fmt );
	res = str_fmt_va( buf, count_of( buf ) - 1, fmt, va ) - 1;
	va_end( va );

	return append( buf, res );
}

bool String::make_space_for( char const* str, ssize add_len )
{
	ssize available = avail_space();

	// NOTE: Return if there is enough space left
	if ( available >= add_len )
	{
		return true;
	}
	else
	{
		ssize new_len, old_size, new_size;

		void* ptr;
		void* new_ptr;

		AllocatorInfo allocator = get_header().Allocator;
		Header*       header	= nullptr;

		new_len  = grow_formula( length() + add_len );
		ptr      = & get_header();
		old_size = size_of( Header ) + length() + 1;
		new_size = size_of( Header ) + new_len + 1;

		new_ptr = resize( allocator, ptr, old_size, new_size );

		if ( new_ptr == nullptr )
			return false;

		header            = rcast( Header*, new_ptr);
		header->Allocator = allocator;
		header->Capacity  = new_len;

		Data = rcast( char*, header + 1 );

		return true;
	}
}
#pragma endregion String

#pragma region File Handling

#if defined( GEN_SYSTEM_WINDOWS ) || defined( GEN_SYSTEM_CYGWIN )

internal
wchar_t* _alloc_utf8_to_ucs2( AllocatorInfo a, char const* text, ssize* w_len_ )
{
	wchar_t* w_text = NULL;
	ssize       len = 0, w_len = 0, w_len1 = 0;
	if ( text == NULL )
	{
		if ( w_len_ )
			*w_len_ = w_len;
		return NULL;
	}
	len = str_len( text );
	if ( len == 0 )
	{
		if ( w_len_ )
			*w_len_ = w_len;
		return NULL;
	}
	w_len = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, text, scast( int, len), NULL, 0 );
	if ( w_len == 0 )
	{
		if ( w_len_ )
			*w_len_ = w_len;
		return NULL;
	}
	w_text = alloc_array( a, wchar_t, w_len + 1 );
	w_len1 = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, text, scast( int, len), w_text, scast( int, w_len) );
	if ( w_len1 == 0 )
	{
		free( a, w_text );
		if ( w_len_ )
			*w_len_ = 0;
		return NULL;
	}
	w_text[ w_len ] = 0;
	if ( w_len_ )
		*w_len_ = w_len;
	return w_text;
}

internal
GEN_FILE_SEEK_PROC( _win32_file_seek )
{
	LARGE_INTEGER li_offset;
	li_offset.QuadPart = offset;
	if ( ! SetFilePointerEx( fd.p, li_offset, &li_offset, whence ) )
	{
		return false;
	}

	if ( new_offset )
		*new_offset = li_offset.QuadPart;
	return true;
}

internal
GEN_FILE_READ_AT_PROC( _win32_file_read )
{
	// unused( stop_at_newline );
	b32 result = false;
	_win32_file_seek( fd, offset, ESeekWhence_BEGIN, NULL );
	DWORD size_ = scast( DWORD, ( size > GEN_I32_MAX ? GEN_I32_MAX : size ));
	DWORD bytes_read_;
	if ( ReadFile( fd.p, buffer, size_, &bytes_read_, NULL ) )
	{
		if ( bytes_read )
			*bytes_read = bytes_read_;
		result = true;
	}

	return result;
}

internal
GEN_FILE_WRITE_AT_PROC( _win32_file_write )
{
	DWORD size_ = scast( DWORD, ( size > GEN_I32_MAX ? GEN_I32_MAX : size ));
	DWORD bytes_written_;
	_win32_file_seek( fd, offset, ESeekWhence_BEGIN, NULL );
	if ( WriteFile( fd.p, buffer, size_, &bytes_written_, NULL ) )
	{
		if ( bytes_written )
			*bytes_written = bytes_written_;
		return true;
	}
	return false;
}

internal
GEN_FILE_CLOSE_PROC( _win32_file_close )
{
	CloseHandle( fd.p );
}

FileOperations const default_file_operations = { _win32_file_read, _win32_file_write, _win32_file_seek, _win32_file_close };

neverinline
GEN_FILE_OPEN_PROC( _win32_file_open )
{
	DWORD    desired_access;
	DWORD    creation_disposition;
	void*    handle;
	wchar_t* w_text;

	switch ( mode & GEN_FILE_MODES )
	{
		case EFileMode_READ :
			desired_access       = GENERIC_READ;
			creation_disposition = OPEN_EXISTING;
			break;
		case EFileMode_WRITE :
			desired_access       = GENERIC_WRITE;
			creation_disposition = CREATE_ALWAYS;
			break;
		case EFileMode_APPEND :
			desired_access       = GENERIC_WRITE;
			creation_disposition = OPEN_ALWAYS;
			break;
		case EFileMode_READ | EFileMode_RW :
			desired_access       = GENERIC_READ | GENERIC_WRITE;
			creation_disposition = OPEN_EXISTING;
			break;
		case EFileMode_WRITE | EFileMode_RW :
			desired_access       = GENERIC_READ | GENERIC_WRITE;
			creation_disposition = CREATE_ALWAYS;
			break;
		case EFileMode_APPEND | EFileMode_RW :
			desired_access       = GENERIC_READ | GENERIC_WRITE;
			creation_disposition = OPEN_ALWAYS;
			break;
		default :
			GEN_PANIC( "Invalid file mode" );
			return EFileError_INVALID;
	}

	w_text = _alloc_utf8_to_ucs2( heap(), filename, NULL );
	handle = CreateFileW( w_text, desired_access, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL, NULL );

	free( heap(), w_text );

	if ( handle == INVALID_HANDLE_VALUE )
	{
		DWORD err = GetLastError();
		switch ( err )
		{
			case ERROR_FILE_NOT_FOUND :
				return EFileError_NOT_EXISTS;
			case ERROR_FILE_EXISTS :
				return EFileError_EXISTS;
			case ERROR_ALREADY_EXISTS :
				return EFileError_EXISTS;
			case ERROR_ACCESS_DENIED :
				return EFileError_PERMISSION;
		}
		return EFileError_INVALID;
	}

	if ( mode & EFileMode_APPEND )
	{
		LARGE_INTEGER offset = { { 0 } };
		if ( ! SetFilePointerEx( handle, offset, NULL, ESeekWhence_END ) )
		{
			CloseHandle( handle );
			return EFileError_INVALID;
		}
	}

	fd->p = handle;
	*ops  = default_file_operations;
	return EFileError_NONE;
}

#else    // POSIX
#	include <fcntl.h>

internal
GEN_FILE_SEEK_PROC( _posix_file_seek )
{
#	if defined( GEN_SYSTEM_OSX )
	s64 res = lseek( fd.i, offset, whence );
#	else    // TODO(ZaKlaus): @fixme lseek64
	s64 res = lseek( fd.i, offset, whence );
#	endif
	if ( res < 0 )
		return false;
	if ( new_offset )
		*new_offset = res;
	return true;
}

internal
GEN_FILE_READ_AT_PROC( _posix_file_read )
{
	unused( stop_at_newline );
	ssize res = pread( fd.i, buffer, size, offset );
	if ( res < 0 )
		return false;
	if ( bytes_read )
		*bytes_read = res;
	return true;
}

internal
GEN_FILE_WRITE_AT_PROC( _posix_file_write )
{
	ssize  res;
	s64 curr_offset = 0;
	_posix_file_seek( fd, 0, ESeekWhence_CURRENT, &curr_offset );
	if ( curr_offset == offset )
	{
		// NOTE: Writing to stdout et al. doesn't like pwrite for numerous reasons
		res = write( scast( int, fd.i), buffer, size );
	}
	else
	{
		res = pwrite( scast( int, fd.i), buffer, size, offset );
	}
	if ( res < 0 )
		return false;
	if ( bytes_written )
		*bytes_written = res;
	return true;
}

internal
GEN_FILE_CLOSE_PROC( _posix_file_close )
{
	close( fd.i );
}

FileOperations const default_file_operations = { _posix_file_read, _posix_file_write, _posix_file_seek, _posix_file_close };

neverinline
GEN_FILE_OPEN_PROC( _posix_file_open )
{
	s32 os_mode;
	switch ( mode & GEN_FILE_MODES )
	{
		case EFileMode_READ :
			os_mode = O_RDONLY;
			break;
		case EFileMode_WRITE :
			os_mode = O_WRONLY | O_CREAT | O_TRUNC;
			break;
		case EFileMode_APPEND :
			os_mode = O_WRONLY | O_APPEND | O_CREAT;
			break;
		case EFileMode_READ | EFileMode_RW :
			os_mode = O_RDWR;
			break;
		case EFileMode_WRITE | EFileMode_RW :
			os_mode = O_RDWR | O_CREAT | O_TRUNC;
			break;
		case EFileMode_APPEND | EFileMode_RW :
			os_mode = O_RDWR | O_APPEND | O_CREAT;
			break;
		default :
			GEN_PANIC( "Invalid file mode" );
			return EFileError_INVALID;
	}

	fd->i = open( filename, os_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
	if ( fd->i < 0 )
	{
		// TODO : More file errors
		return EFileError_INVALID;
	}

	*ops = default_file_operations;
	return EFileError_NONE;
}

// POSIX
#endif

internal void _dirinfo_free_entry( DirEntry* entry );

// TODO : Is this a bad idea?
global b32      _std_file_set                     = false;
global FileInfo _std_files[ EFileStandard_COUNT ] = {
{
	{ nullptr, nullptr, nullptr, nullptr },
	{ nullptr },
	0,
	nullptr,
	0,
	nullptr
} };

#if defined( GEN_SYSTEM_WINDOWS ) || defined( GEN_SYSTEM_CYGWIN )

FileInfo* file_get_standard( FileStandardType std )
{
	if ( ! _std_file_set )
	{
#	define GEN__SET_STD_FILE( type, v ) \
		_std_files[ type ].fd.p = v;    \
		_std_files[ type ].ops  = default_file_operations
		GEN__SET_STD_FILE( EFileStandard_INPUT, GetStdHandle( STD_INPUT_HANDLE ) );
		GEN__SET_STD_FILE( EFileStandard_OUTPUT, GetStdHandle( STD_OUTPUT_HANDLE ) );
		GEN__SET_STD_FILE( EFileStandard_ERROR, GetStdHandle( STD_ERROR_HANDLE ) );
#	undef GEN__SET_STD_FILE
		_std_file_set = true;
	}
	return &_std_files[ std ];
}

#else    // POSIX

FileInfo* file_get_standard( FileStandardType std )
{
	if ( ! _std_file_set )
	{
#	define GEN__SET_STD_FILE( type, v ) \
		_std_files[ type ].fd.i = v;     \
		_std_files[ type ].ops  = default_file_operations
		GEN__SET_STD_FILE( EFileStandard_INPUT, 0 );
		GEN__SET_STD_FILE( EFileStandard_OUTPUT, 1 );
		GEN__SET_STD_FILE( EFileStandard_ERROR, 2 );
#	undef GEN__SET_STD_FILE
		_std_file_set = true;
	}
	return &_std_files[ std ];
}

#endif

FileError file_close( FileInfo* f )
{
	if ( ! f )
		return EFileError_INVALID;

	if ( f->filename )
		free( heap(), ccast( char*, f->filename ));

#if defined( GEN_SYSTEM_WINDOWS )
	if ( f->fd.p == INVALID_HANDLE_VALUE )
		return EFileError_INVALID;
#else
	if ( f->fd.i < 0 )
		return EFileError_INVALID;
#endif

	if ( f->is_temp )
	{
		f->ops.close( f->fd );
		return EFileError_NONE;
	}

	if ( ! f->ops.read_at )
		f->ops = default_file_operations;
	f->ops.close( f->fd );

#if 0
	if ( f->Dir )
	{
		_dirinfo_free_entry( f->Dir );
		mfree( f->Dir );
		f->Dir = NULL;
	}
#endif

	return EFileError_NONE;
}

FileError file_new( FileInfo* f, FileDescriptor fd, FileOperations ops, char const* filename )
{
	FileError err = EFileError_NONE;
	ssize        len = str_len( filename );

	f->ops             = ops;
	f->fd              = fd;
	f->dir             = nullptr;
	f->last_write_time = 0;
	f->filename        = alloc_array( heap(), char, len + 1 );
	mem_copy( ccast( char*, f->filename), ccast( char*, filename), len + 1 );

	return err;
}

FileError file_open( FileInfo* f, char const* filename )
{
	return file_open_mode( f, EFileMode_READ, filename );
}

FileError file_open_mode( FileInfo* f, FileMode mode, char const* filename )
{
	FileInfo file_ =
	{
		{ nullptr, nullptr, nullptr, nullptr },
		{ nullptr },
		0,
		nullptr,
		0,
		nullptr
		};

	*f = file_;
	FileError err;

#if defined( GEN_SYSTEM_WINDOWS ) || defined( GEN_SYSTEM_CYGWIN )
	err = _win32_file_open( &f->fd, &f->ops, mode, filename );
#else
	err = _posix_file_open( &f->fd, &f->ops, mode, filename );
#endif

	if ( err == EFileError_NONE )
		return file_new( f, f->fd, f->ops, filename );

	return err;
}

s64 file_size( FileInfo* f )
{
	s64 size        = 0;
	s64 prev_offset = file_tell( f );

	file_seek_to_end( f );
	size = file_tell( f );

	file_seek( f, prev_offset );

	return size;
}

FileContents file_read_contents( AllocatorInfo a, b32 zero_terminate, char const* filepath )
{
	FileContents result;
	FileInfo     file  ;

	result.allocator = a;

	if ( file_open( &file, filepath ) == EFileError_NONE )
	{
		ssize fsize = scast( ssize , file_size( &file ));
		if ( fsize > 0 )
		{
			result.data = alloc( a, zero_terminate ? fsize + 1 : fsize );
			result.size = fsize;
			file_read_at( &file, result.data, result.size, 0 );
			if ( zero_terminate )
			{
				u8* str      = rcast( u8*, result.data);
				str[ fsize ] = '\0';
			}
		}
		file_close( &file );
	}

	return result;
}

struct _memory_fd
{
	u8            magic;
	u8*           buf;    //< zpl_array OR plain buffer if we can't write
	ssize         cursor;
	AllocatorInfo allocator;

	FileStreamFlags flags;
	ssize           cap;
};

#define GEN__FILE_STREAM_FD_MAGIC 37

FileDescriptor _file_stream_fd_make( _memory_fd* d );
_memory_fd*    _file_stream_from_fd( FileDescriptor fd );

inline
FileDescriptor _file_stream_fd_make( _memory_fd* d )
{
	FileDescriptor fd = { 0 };
	fd.p              = ( void* )d;
	return fd;
}

inline
_memory_fd* _file_stream_from_fd( FileDescriptor fd )
{
	_memory_fd* d = ( _memory_fd* )fd.p;
	GEN_ASSERT( d->magic == GEN__FILE_STREAM_FD_MAGIC );
	return d;
}

b8 file_stream_new( FileInfo* file, AllocatorInfo allocator )
{
	GEN_ASSERT_NOT_NULL( file );

	_memory_fd* d = ( _memory_fd* )alloc( allocator, size_of( _memory_fd ) );

	if ( ! d )
		return false;

	zero_item( file );
	d->magic     = GEN__FILE_STREAM_FD_MAGIC;
	d->allocator = allocator;
	d->flags     = EFileStream_CLONE_WRITABLE;
	d->cap       = 0;
	d->buf       = Array<u8>::init( allocator );

	if ( ! d->buf )
		return false;

	file->ops             = memory_file_operations;
	file->fd              = _file_stream_fd_make( d );
	file->dir             = NULL;
	file->last_write_time = 0;
	file->filename        = NULL;
	file->is_temp         = true;
	return true;
}

b8 file_stream_open( FileInfo* file, AllocatorInfo allocator, u8* buffer, ssize size, FileStreamFlags flags )
{
	GEN_ASSERT_NOT_NULL( file );
	_memory_fd* d = ( _memory_fd* )alloc( allocator, size_of( _memory_fd ) );
	if ( ! d )
		return false;
	zero_item( file );
	d->magic     = GEN__FILE_STREAM_FD_MAGIC;
	d->allocator = allocator;
	d->flags     = flags;
	if ( d->flags & EFileStream_CLONE_WRITABLE )
	{
		Array<u8> arr = Array<u8>::init_reserve( allocator, size );
		d->buf = arr;

		if ( ! d->buf )
			return false;

		mem_copy( d->buf, buffer, size );
		d->cap = size;

		arr.get_header()->Num = size;
	}
	else
	{
		d->buf = buffer;
		d->cap = size;
	}
	file->ops             = memory_file_operations;
	file->fd              = _file_stream_fd_make( d );
	file->dir             = NULL;
	file->last_write_time = 0;
	file->filename        = NULL;
	file->is_temp         = true;
	return true;
}

u8* file_stream_buf( FileInfo* file, ssize* size )
{
	GEN_ASSERT_NOT_NULL( file );
	_memory_fd* d = _file_stream_from_fd( file->fd );
	if ( size )
		*size = d->cap;
	return d->buf;
}

internal
GEN_FILE_SEEK_PROC( _memory_file_seek )
{
	_memory_fd* d      = _file_stream_from_fd( fd );
	ssize          buflen = d->cap;

	if ( whence == ESeekWhence_BEGIN )
		d->cursor = 0;
	else if ( whence == ESeekWhence_END )
		d->cursor = buflen;

	d->cursor = max( 0, clamp( d->cursor + offset, 0, buflen ) );
	if ( new_offset )
		*new_offset = d->cursor;
	return true;
}

internal
GEN_FILE_READ_AT_PROC( _memory_file_read )
{
	// unused( stop_at_newline );
	_memory_fd* d = _file_stream_from_fd( fd );
	mem_copy( buffer, d->buf + offset, size );
	if ( bytes_read )
		*bytes_read = size;
	return true;
}

internal
GEN_FILE_WRITE_AT_PROC( _memory_file_write )
{
	_memory_fd* d = _file_stream_from_fd( fd );

	if ( ! ( d->flags & ( EFileStream_CLONE_WRITABLE | EFileStream_WRITABLE ) ) )
		return false;

	ssize buflen   = d->cap;
	ssize extralen = max( 0, size - ( buflen - offset ) );
	ssize rwlen    = size - extralen;
	ssize new_cap  = buflen + extralen;

	if ( d->flags & EFileStream_CLONE_WRITABLE )
	{
		Array<u8> arr = { d->buf };

		if ( arr.get_header()->Capacity < usize(new_cap) )
		{
			if ( ! arr.grow( ( s64 )( new_cap ) ) )
				return false;
			d->buf = arr;
		}
	}

	mem_copy( d->buf + offset, buffer, rwlen );

	if ( ( d->flags & EFileStream_CLONE_WRITABLE ) && extralen > 0 )
	{
		Array<u8> arr = { d->buf };

		mem_copy( d->buf + offset + rwlen, pointer_add_const( buffer, rwlen ), extralen );
		d->cap = new_cap;
		arr.get_header()->Capacity = new_cap;
	}
	else
	{
		extralen = 0;
	}

	if ( bytes_written )
		*bytes_written = ( rwlen + extralen );
	return true;
}

internal
GEN_FILE_CLOSE_PROC( _memory_file_close )
{
	_memory_fd*   d         = _file_stream_from_fd( fd );
	AllocatorInfo allocator = d->allocator;

	if ( d->flags & EFileStream_CLONE_WRITABLE )
	{
		Array<u8> arr = { d->buf };
		arr.free();
	}

	free( allocator, d );
}

FileOperations const memory_file_operations = { _memory_file_read, _memory_file_write, _memory_file_seek, _memory_file_close };

#pragma endregion File Handling

#pragma region Timing

#ifdef GEN_BENCHMARK
	#if defined( GEN_COMPILER_MSVC ) && ! defined( __clang__ )
	u64 read_cpu_time_stamp_counter( void )
	{
		return __rdtsc();
	}
	#elif defined( __i386__ )
	u64 read_cpu_time_stamp_counter( void )
	{
		u64 x;
		__asm__ volatile( ".byte 0x0f, 0x31" : "=A"( x ) );
		return x;
	}
	#elif defined( __x86_64__ )
	u64 read_cpu_time_stamp_counter( void )
	{
		u32 hi, lo;
		__asm__ __volatile__( "rdtsc" : "=a"( lo ), "=d"( hi ) );
		return scast( u64, lo ) | ( scast( u64, hi ) << 32 );
	}
	#elif defined( __powerpc__ )
	u64 read_cpu_time_stamp_counter( void )
	{
		u64 result = 0;
		u32 upper, lower, tmp;
		__asm__ volatile(
			"0:                   \n"
			"\tmftbu   %0         \n"
			"\tmftb    %1         \n"
			"\tmftbu   %2         \n"
			"\tcmpw    %2,%0      \n"
			"\tbne     0b         \n"
			: "=r"( upper ), "=r"( lower ), "=r"( tmp )
		);
		result = upper;
		result = result << 32;
		result = result | lower;

		return result;
	}
	#elif defined( GEN_SYSTEM_EMSCRIPTEN )
	u64 read_cpu_time_stamp_counter( void )
	{
		return ( u64 )( emscripten_get_now() * 1e+6 );
	}
	#elif defined( GEN_CPU_ARM ) && ! defined( GEN_COMPILER_TINYC )
	u64 read_cpu_time_stamp_counter( void )
	{
	#	if defined( __aarch64__ )
		int64_t r = 0;
		asm volatile( "mrs %0, cntvct_el0" : "=r"( r ) );
	#	elif ( __ARM_ARCH >= 6 )
		uint32_t r = 0;
		uint32_t pmccntr;
		uint32_t pmuseren;
		uint32_t pmcntenset;

		// Read the user mode perf monitor counter access permissions.
		asm volatile( "mrc p15, 0, %0, c9, c14, 0" : "=r"( pmuseren ) );
		if ( pmuseren & 1 )
		{    // Allows reading perfmon counters for user mode code.
			asm volatile( "mrc p15, 0, %0, c9, c12, 1" : "=r"( pmcntenset ) );
			if ( pmcntenset & 0x80000000ul )
			{    // Is it counting?
				asm volatile( "mrc p15, 0, %0, c9, c13, 0" : "=r"( pmccntr ) );
				// The counter is set up to count every 64th cycle
				return ( ( int64_t )pmccntr ) * 64;    // Should optimize to << 6
			}
		}
	#	else
	#		error "No suitable method for read_cpu_time_stamp_counter for this cpu type"
	#	endif

		return r;
	}
	#else
	u64 read_cpu_time_stamp_counter( void )
	{
		GEN_PANIC( "read_cpu_time_stamp_counter is not supported on this particular setup" );
		return -0;
	}
	#endif

	#if defined( GEN_SYSTEM_WINDOWS ) || defined( GEN_SYSTEM_CYGWIN )

	u64 time_rel_ms( void )
	{
		local_persist LARGE_INTEGER win32_perf_count_freq = {};
		u64                         result;
		LARGE_INTEGER               counter;
		local_persist LARGE_INTEGER win32_perf_counter = {};
		if ( ! win32_perf_count_freq.QuadPart )
		{
			QueryPerformanceFrequency( &win32_perf_count_freq );
			GEN_ASSERT( win32_perf_count_freq.QuadPart != 0 );
			QueryPerformanceCounter( &win32_perf_counter );
		}

		QueryPerformanceCounter( &counter );

		result = ( counter.QuadPart - win32_perf_counter.QuadPart ) * 1000 / ( win32_perf_count_freq.QuadPart );
		return result;
	}

	#else

	#	if defined( GEN_SYSTEM_LINUX ) || defined( GEN_SYSTEM_FREEBSD ) || defined( GEN_SYSTEM_OPENBSD ) || defined( GEN_SYSTEM_EMSCRIPTEN )
	u64 _unix_gettime( void )
	{
		struct timespec t;
		u64             result;

		clock_gettime( 1 /*CLOCK_MONOTONIC*/, &t );
		result = 1000 * t.tv_sec + 1.0e-6 * t.tv_nsec;
		return result;
	}
	#	endif

	u64 time_rel_ms( void )
	{
	#	if defined( GEN_SYSTEM_OSX )
		u64 result;

		local_persist u64 timebase  = 0;
		local_persist u64 timestart = 0;

		if ( ! timestart )
		{
			mach_timebase_info_data_t tb = { 0 };
			mach_timebase_info( &tb );
			timebase   = tb.numer;
			timebase  /= tb.denom;
			timestart  = mach_absolute_time();
		}

		// NOTE: mach_absolute_time() returns things in nanoseconds
		result = 1.0e-6 * ( mach_absolute_time() - timestart ) * timebase;
		return result;
	#	else
		local_persist u64 unix_timestart = 0.0;

		if ( ! unix_timestart )
		{
			unix_timestart = _unix_gettime();
		}

		u64 now = _unix_gettime();

		return ( now - unix_timestart );
	#	endif
	}
	#endif

	f64 time_rel( void )
	{
		return ( f64 )( time_rel_ms() * 1e-3 );
	}
#endif

#pragma endregion Timing

#pragma region Parsing

#pragma region ADT

#define _adt_fprintf( s_, fmt_, ... )                      \
	do                                                     \
	{                                                      \
		if ( str_fmt_file( s_, fmt_, ##__VA_ARGS__ ) < 0 ) \
			return EADT_ERROR_OUT_OF_MEMORY;               \
	} while ( 0 )

u8 adt_make_branch( ADT_Node* node, AllocatorInfo backing, char const* name, b32 is_array )
{
	ADT_Type type = EADT_TYPE_OBJECT;
	if ( is_array )
		type = EADT_TYPE_ARRAY;

	ADT_Node* parent = node->parent;
	zero_item( node );

	node->type   = type;
	node->name   = name;
	node->parent = parent;
	node->nodes  = Array<ADT_Node>::init( backing );

	if ( ! node->nodes )
		return EADT_ERROR_OUT_OF_MEMORY;

	return 0;
}

u8 adt_destroy_branch( ADT_Node* node )
{
	GEN_ASSERT_NOT_NULL( node );
	if ( ( node->type == EADT_TYPE_OBJECT || node->type == EADT_TYPE_ARRAY ) && node->nodes )
	{
		for ( ssize i = 0; i < scast(ssize, node->nodes.num()); ++i )
		{
			adt_destroy_branch( node->nodes + i );
		}

		node->nodes.free();
	}
	return 0;
}

u8 adt_make_leaf( ADT_Node* node, char const* name, ADT_Type type )
{
	GEN_ASSERT( type != EADT_TYPE_OBJECT && type != EADT_TYPE_ARRAY );

	ADT_Node* parent = node->parent;
	zero_item( node );

	node->type   = type;
	node->name   = name;
	node->parent = parent;
	return 0;
}

ADT_Node* adt_find( ADT_Node* node, char const* name, b32 deep_search )
{
	if ( node->type != EADT_TYPE_OBJECT )
	{
		return NULL;
	}

	for ( ssize i = 0; i < scast(ssize, node->nodes.num()); i++ )
	{
		if ( ! str_compare( node->nodes[ i ].name, name ) )
		{
			return ( node->nodes + i );
		}
	}

	if ( deep_search )
	{
		for ( ssize i = 0; i < scast(ssize, node->nodes.num()); i++ )
		{
			ADT_Node* res = adt_find( node->nodes + i, name, deep_search );

			if ( res != NULL )
				return res;
		}
	}

	return NULL;
}

internal ADT_Node* _adt_get_value( ADT_Node* node, char const* value )
{
	switch ( node->type )
	{
		case EADT_TYPE_MULTISTRING :
		case EADT_TYPE_STRING :
			{
				if ( node->string && ! str_compare( node->string, value ) )
				{
					return node;
				}
			}
			break;
		case EADT_TYPE_INTEGER :
		case EADT_TYPE_REAL :
			{
				char     back[ 4096 ] = { 0 };
				FileInfo tmp;

				/* allocate a file descriptor for a memory-mapped number to string conversion, input source buffer is not cloned, however. */
				file_stream_open( &tmp, heap(), ( u8* )back, size_of( back ), EFileStream_WRITABLE );
				adt_print_number( &tmp, node );

				ssize  fsize = 0;
				u8* buf   = file_stream_buf( &tmp, &fsize );

				if ( ! str_compare( ( char const* )buf, value ) )
				{
					file_close( &tmp );
					return node;
				}

				file_close( &tmp );
			}
			break;
		default :
			break; /* node doesn't support value based lookup */
	}

	return NULL;
}

internal ADT_Node* _adt_get_field( ADT_Node* node, char* name, char* value )
{
	for ( ssize i = 0; i < scast(ssize, node->nodes.num()); i++ )
	{
		if ( ! str_compare( node->nodes[ i ].name, name ) )
		{
			ADT_Node* child = &node->nodes[ i ];
			if ( _adt_get_value( child, value ) )
			{
				return node; /* this object does contain a field of a specified value! */
			}
		}
	}

	return NULL;
}

ADT_Node* adt_query( ADT_Node* node, char const* uri )
{
	GEN_ASSERT_NOT_NULL( uri );

	if ( *uri == '/' )
	{
		uri++;
	}

	if ( *uri == 0 )
	{
		return node;
	}

	if ( ! node || ( node->type != EADT_TYPE_OBJECT && node->type != EADT_TYPE_ARRAY ) )
	{
		return NULL;
	}

#if defined EADT_URI_DEBUG || 0
	str_fmt_out( "uri: %s\n", uri );
#endif

	char *    p = ( char* )uri, *b = p, *e = p;
	ADT_Node* found_node = NULL;

	b = p;
	p = e     = ( char* )str_skip( p, '/' );
	char* buf = str_fmt_buf( "%.*s", ( int )( e - b ), b );

	/* handle field value lookup */
	if ( *b == '[' )
	{
		char *l_p = buf + 1, *l_b = l_p, *l_e = l_p, *l_b2 = l_p, *l_e2 = l_p;
		l_e  = ( char* )str_skip( l_p, '=' );
		l_e2 = ( char* )str_skip( l_p, ']' );

		if ( ( ! *l_e && node->type != EADT_TYPE_ARRAY ) || ! *l_e2 )
		{
			GEN_ASSERT_MSG( 0, "Invalid field value lookup" );
			return NULL;
		}

		*l_e2 = 0;

		/* [field=value] */
		if ( *l_e )
		{
			*l_e = 0;
			l_b2 = l_e + 1;

			/* run a value comparison against our own fields */
			if ( node->type == EADT_TYPE_OBJECT )
			{
				found_node = _adt_get_field( node, l_b, l_b2 );
			}

			/* run a value comparison against any child that is an object node */
			else if ( node->type == EADT_TYPE_ARRAY )
			{
				for ( ssize i = 0; i < scast(ssize, node->nodes.num()); i++ )
				{
					ADT_Node* child = &node->nodes[ i ];
					if ( child->type != EADT_TYPE_OBJECT )
					{
						continue;
					}

					found_node = _adt_get_field( child, l_b, l_b2 );

					if ( found_node )
						break;
				}
			}
		}
		/* [value] */
		else
		{
			for ( ssize i = 0; i < scast(ssize, node->nodes.num()); i++ )
			{
				ADT_Node* child = &node->nodes[ i ];
				if ( _adt_get_value( child, l_b2 ) )
				{
					found_node = child;
					break; /* we found a matching value in array, ignore the rest of it */
				}
			}
		}

		/* go deeper if uri continues */
		if ( *e )
		{
			return adt_query( found_node, e + 1 );
		}
	}
	/* handle field name lookup */
	else if ( node->type == EADT_TYPE_OBJECT )
	{
		found_node = adt_find( node, buf, false );

		/* go deeper if uri continues */
		if ( *e )
		{
			return adt_query( found_node, e + 1 );
		}
	}
	/* handle array index lookup */
	else
	{
		ssize idx = ( ssize )str_to_i64( buf, NULL, 10 );
		if ( idx >= 0 && idx < scast(ssize, node->nodes.num()) )
		{
			found_node = &node->nodes[ idx ];

			/* go deeper if uri continues */
			if ( *e )
			{
				return adt_query( found_node, e + 1 );
			}
		}
	}

	return found_node;
}

ADT_Node* adt_alloc_at( ADT_Node* parent, ssize index )
{
	if ( ! parent || ( parent->type != EADT_TYPE_OBJECT && parent->type != EADT_TYPE_ARRAY ) )
	{
		return NULL;
	}

	if ( ! parent->nodes )
		return NULL;

	if ( index < 0 || index > scast(ssize, parent->nodes.num()) )
		return NULL;

	ADT_Node o = { 0 };
	o.parent   = parent;
	if ( ! parent->nodes.append_at( o, index ) )
		return NULL;

	return parent->nodes + index;
}

ADT_Node* adt_alloc( ADT_Node* parent )
{
	if ( ! parent || ( parent->type != EADT_TYPE_OBJECT && parent->type != EADT_TYPE_ARRAY ) )
	{
		return NULL;
	}

	if ( ! parent->nodes )
		return NULL;

	return adt_alloc_at( parent, parent->nodes.num() );
}

b8 adt_set_obj( ADT_Node* obj, char const* name, AllocatorInfo backing )
{
	return adt_make_branch( obj, backing, name, 0 );
}

b8 adt_set_arr( ADT_Node* obj, char const* name, AllocatorInfo backing )
{
	return adt_make_branch( obj, backing, name, 1 );
}

b8 adt_set_str( ADT_Node* obj, char const* name, char const* value )
{
	adt_make_leaf( obj, name, EADT_TYPE_STRING );
	obj->string = value;
	return true;
}

b8 adt_set_flt( ADT_Node* obj, char const* name, f64 value )
{
	adt_make_leaf( obj, name, EADT_TYPE_REAL );
	obj->real = value;
	return true;
}

b8 adt_set_int( ADT_Node* obj, char const* name, s64 value )
{
	adt_make_leaf( obj, name, EADT_TYPE_INTEGER );
	obj->integer = value;
	return true;
}

ADT_Node* adt_move_node_at( ADT_Node* node, ADT_Node* new_parent, ssize index )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( new_parent );
	ADT_Node* old_parent = node->parent;
	ADT_Node* new_node   = adt_alloc_at( new_parent, index );
	*new_node            = *node;
	new_node->parent     = new_parent;
	if ( old_parent )
	{
		adt_remove_node( node );
	}
	return new_node;
}

ADT_Node* adt_move_node( ADT_Node* node, ADT_Node* new_parent )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( new_parent );
	GEN_ASSERT( new_parent->type == EADT_TYPE_ARRAY || new_parent->type == EADT_TYPE_OBJECT );
	return adt_move_node_at( node, new_parent, new_parent->nodes.num() );
}

void adt_swap_nodes( ADT_Node* node, ADT_Node* other_node )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( other_node );
	ADT_Node* parent                     = node->parent;
	ADT_Node* other_parent               = other_node->parent;
	ssize        index                      = ( pointer_diff( parent->nodes, node ) / size_of( ADT_Node ) );
	ssize        index2                     = ( pointer_diff( other_parent->nodes, other_node ) / size_of( ADT_Node ) );
	ADT_Node  temp                       = parent->nodes[ index ];
	temp.parent                          = other_parent;
	other_parent->nodes[ index2 ].parent = parent;
	parent->nodes[ index ]               = other_parent->nodes[ index2 ];
	other_parent->nodes[ index2 ]        = temp;
}

void adt_remove_node( ADT_Node* node )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( node->parent );
	ADT_Node* parent = node->parent;
	ssize        index  = ( pointer_diff( parent->nodes, node ) / size_of( ADT_Node ) );
	parent->nodes.remove_at( index );
}

ADT_Node* adt_append_obj( ADT_Node* parent, char const* name )
{
	ADT_Node* o = adt_alloc( parent );
	if ( ! o )
		return NULL;
	if ( adt_set_obj( o, name, parent->nodes.get_header()->Allocator ) )
	{
		adt_remove_node( o );
		return NULL;
	}
	return o;
}

ADT_Node* adt_append_arr( ADT_Node* parent, char const* name )
{
	ADT_Node* o = adt_alloc( parent );
	if ( ! o )
		return NULL;
	if ( adt_set_arr( o, name, parent->nodes.get_header()->Allocator ) )
	{
		adt_remove_node( o );
		return NULL;
	}
	return o;
}

ADT_Node* adt_append_str( ADT_Node* parent, char const* name, char const* value )
{
	ADT_Node* o = adt_alloc( parent );
	if ( ! o )
		return NULL;
	adt_set_str( o, name, value );
	return o;
}

ADT_Node* adt_append_flt( ADT_Node* parent, char const* name, f64 value )
{
	ADT_Node* o = adt_alloc( parent );
	if ( ! o )
		return NULL;
	adt_set_flt( o, name, value );
	return o;
}

ADT_Node* adt_append_int( ADT_Node* parent, char const* name, s64 value )
{
	ADT_Node* o = adt_alloc( parent );
	if ( ! o )
		return NULL;
	adt_set_int( o, name, value );
	return o;
}

/* parser helpers */
char* adt_parse_number_strict( ADT_Node* node, char* base_str )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( base_str );
	char *p = base_str, *e = p;

	while ( *e )
		++e;

	while ( *p && ( str_find( "eE.+-", *p ) || char_is_hex_digit( *p ) ) )
	{
		++p;
	}

	if ( p >= e )
	{
		return adt_parse_number( node, base_str );
	}

	return base_str;
}

char* adt_parse_number( ADT_Node* node, char* base_str )
{
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( base_str );
	char *p = base_str, *e = p;

	s32       base         = 0;
	s32       base2        = 0;
	u8        base2_offset = 0;
	s8        exp = 0, orig_exp = 0;
	u8        neg_zero   = 0;
	u8        lead_digit = 0;
	ADT_Type  node_type  = EADT_TYPE_UNINITIALISED;
	u8        node_props = 0;

	/* skip false positives and special cases */
	if ( ! ! str_find( "eE", *p ) || ( ! ! str_find( ".+-", *p ) && ! char_is_hex_digit( *( p + 1 ) ) && *( p + 1 ) != '.' ) )
	{
		return ++base_str;
	}

	node_type = EADT_TYPE_INTEGER;
	neg_zero  = false;

	ssize   ib        = 0;
	char buf[ 48 ] = { 0 };

	if ( *e == '+' )
		++e;
	else if ( *e == '-' )
	{
		buf[ ib++ ] = *e++;
	}

	if ( *e == '.' )
	{
		node_type   = EADT_TYPE_REAL;
		node_props  = EADT_PROPS_IS_PARSED_REAL;
		lead_digit  = false;
		buf[ ib++ ] = '0';
		do
		{
			buf[ ib++ ] = *e;
		} while ( char_is_digit( *++e ) );
	}
	else
	{
		if ( ! str_compare( e, "0x", 2 ) || ! str_compare( e, "0X", 2 ) )
		{
			node_props = EADT_PROPS_IS_HEX;
		}

		/* bail if ZPL_ADT_PROPS_IS_HEX is unset but we get 'x' on input */
		if ( char_to_lower( *e ) == 'x' && ( node_props != EADT_PROPS_IS_HEX ) )
		{
			return ++base_str;
		}

		while ( char_is_hex_digit( *e ) || char_to_lower( *e ) == 'x' )
		{
			buf[ ib++ ] = *e++;
		}

		if ( *e == '.' )
		{
			node_type  = EADT_TYPE_REAL;
			lead_digit = true;
			u32 step   = 0;

			do
			{
				buf[ ib++ ] = *e;
				++step;
			} while ( char_is_digit( *++e ) );

			if ( step < 2 )
			{
				buf[ ib++ ] = '0';
			}
		}
	}

	/* check if we have a dot here, this is a false positive (IP address, ...) */
	if ( *e == '.' )
	{
		return ++base_str;
	}

	f32  eb          = 10;
	char expbuf[ 6 ] = { 0 };
	ssize   expi        = 0;

	if ( *e && ! ! str_find( "eE", *e ) )
	{
		++e;
		if ( *e == '+' || *e == '-' || char_is_digit( *e ) )
		{
			if ( *e == '-' )
			{
				eb = 0.1f;
			}
			if ( ! char_is_digit( *e ) )
			{
				++e;
			}
			while ( char_is_digit( *e ) )
			{
				expbuf[ expi++ ] = *e++;
			}
		}

		orig_exp = exp = ( u8 )str_to_i64( expbuf, NULL, 10 );
	}

	if ( node_type == EADT_TYPE_INTEGER )
	{
		node->integer = str_to_i64( buf, 0, 0 );
#ifndef GEN_PARSER_DISABLE_ANALYSIS
		/* special case: negative zero */
		if ( node->integer == 0 && buf[ 0 ] == '-' )
		{
			neg_zero = true;
		}
#endif
		while ( orig_exp-- > 0 )
		{
			node->integer *= ( s64 )eb;
		}
	}
	else
	{
		node->real = str_to_f64( buf, 0 );

#ifndef GEN_PARSER_DISABLE_ANALYSIS
		char *q = buf, *base_string = q, *base_string2 = q;
		base_string           = ccast( char*, str_skip( base_string, '.' ));
		*base_string          = '\0';
		base_string2          = base_string + 1;
		char* base_string_off = base_string2;
		while ( *base_string_off++ == '0' )
			base2_offset++;

		base  = ( s32 )str_to_i64( q, 0, 0 );
		base2 = ( s32 )str_to_i64( base_string2, 0, 0 );
		if ( exp )
		{
			exp        = exp * ( ! ( eb == 10.0f ) ? -1 : 1 );
			node_props = EADT_PROPS_IS_EXP;
		}

		/* special case: negative zero */
		if ( base == 0 && buf[ 0 ] == '-' )
		{
			neg_zero = true;
		}
#endif
		while ( orig_exp-- > 0 )
		{
			node->real *= eb;
		}
	}

	node->type  = node_type;
	node->props = node_props;

#ifndef GEN_PARSER_DISABLE_ANALYSIS
	node->base         = base;
	node->base2        = base2;
	node->base2_offset = base2_offset;
	node->exp          = exp;
	node->neg_zero     = neg_zero;
	node->lead_digit   = lead_digit;
#else
	unused( base );
	unused( base2 );
	unused( base2_offset );
	unused( exp );
	unused( neg_zero );
	unused( lead_digit );
#endif
	return e;
}

ADT_Error adt_print_number( FileInfo* file, ADT_Node* node )
{
	GEN_ASSERT_NOT_NULL( file );
	GEN_ASSERT_NOT_NULL( node );
	if ( node->type != EADT_TYPE_INTEGER && node->type != EADT_TYPE_REAL )
	{
		return EADT_ERROR_INVALID_TYPE;
	}

#ifndef GEN_PARSER_DISABLE_ANALYSIS
	if ( node->neg_zero )
	{
		_adt_fprintf( file, "-" );
	}
#endif

	switch ( node->type )
	{
		case EADT_TYPE_INTEGER :
			{
				if ( node->props == EADT_PROPS_IS_HEX )
				{
					_adt_fprintf( file, "0x%llx", ( long long )node->integer );
				}
				else
				{
					_adt_fprintf( file, "%lld", ( long long )node->integer );
				}
			}
			break;

		case EADT_TYPE_REAL :
			{
				if ( node->props == EADT_PROPS_NAN )
				{
					_adt_fprintf( file, "NaN" );
				}
				else if ( node->props == EADT_PROPS_NAN_NEG )
				{
					_adt_fprintf( file, "-NaN" );
				}
				else if ( node->props == EADT_PROPS_INFINITY )
				{
					_adt_fprintf( file, "Infinity" );
				}
				else if ( node->props == EADT_PROPS_INFINITY_NEG )
				{
					_adt_fprintf( file, "-Infinity" );
				}
				else if ( node->props == EADT_PROPS_TRUE )
				{
					_adt_fprintf( file, "true" );
				}
				else if ( node->props == EADT_PROPS_FALSE )
				{
					_adt_fprintf( file, "false" );
				}
				else if ( node->props == EADT_PROPS_NULL )
				{
					_adt_fprintf( file, "null" );
#ifndef GEN_PARSER_DISABLE_ANALYSIS
				}
				else if ( node->props == EADT_PROPS_IS_EXP )
				{
					_adt_fprintf( file, "%lld.%0*d%llde%lld", ( long long )node->base, node->base2_offset, 0, ( long long )node->base2, ( long long )node->exp );
				}
				else if ( node->props == EADT_PROPS_IS_PARSED_REAL )
				{
					if ( ! node->lead_digit )
						_adt_fprintf( file, ".%0*d%lld", node->base2_offset, 0, ( long long )node->base2 );
					else
						_adt_fprintf( file, "%lld.%0*d%lld", ( long long int )node->base2_offset, 0, ( int )node->base, ( long long )node->base2 );
#endif
				}
				else
				{
					_adt_fprintf( file, "%f", node->real );
				}
			}
			break;
	}

	return EADT_ERROR_NONE;
}

ADT_Error adt_print_string( FileInfo* file, ADT_Node* node, char const* escaped_chars, char const* escape_symbol )
{
	GEN_ASSERT_NOT_NULL( file );
	GEN_ASSERT_NOT_NULL( node );
	GEN_ASSERT_NOT_NULL( escaped_chars );
	if ( node->type != EADT_TYPE_STRING && node->type != EADT_TYPE_MULTISTRING )
	{
		return EADT_ERROR_INVALID_TYPE;
	}

	/* escape string */
	char const *p = node->string, *b = p;

	if ( ! p )
		return EADT_ERROR_NONE;

	do
	{
		p = str_skip_any( p, escaped_chars );
		_adt_fprintf( file, "%.*s", pointer_diff( b, p ), b );
		if ( *p && ! ! str_find( escaped_chars, *p ) )
		{
			_adt_fprintf( file, "%s%c", escape_symbol, *p );
			p++;
		}
		b = p;
	} while ( *p );

	return EADT_ERROR_NONE;
}

ADT_Error adt_str_to_number( ADT_Node* node )
{
	GEN_ASSERT( node );

	if ( node->type == EADT_TYPE_REAL || node->type == EADT_TYPE_INTEGER )
		return EADT_ERROR_ALREADY_CONVERTED; /* this is already converted/parsed */
	if ( node->type != EADT_TYPE_STRING && node->type != EADT_TYPE_MULTISTRING )
	{
		return EADT_ERROR_INVALID_TYPE;
	}

	adt_parse_number( node, ( char* )node->string );

	return EADT_ERROR_NONE;
}

ADT_Error adt_str_to_number_strict( ADT_Node* node )
{
	GEN_ASSERT( node );

	if ( node->type == EADT_TYPE_REAL || node->type == EADT_TYPE_INTEGER )
		return EADT_ERROR_ALREADY_CONVERTED; /* this is already converted/parsed */
	if ( node->type != EADT_TYPE_STRING && node->type != EADT_TYPE_MULTISTRING )
	{
		return EADT_ERROR_INVALID_TYPE;
	}

	adt_parse_number_strict( node, ( char* )node->string );

	return EADT_ERROR_NONE;
}

#undef _adt_fprintf

#pragma endregion ADT

#pragma region CSV

#ifdef GEN_CSV_DEBUG
#	define GEN_CSV_ASSERT( msg ) GEN_PANIC( msg )
#else
#	define GEN_CSV_ASSERT( msg )
#endif

u8 csv_parse_delimiter( CSV_Object* root, char* text, AllocatorInfo allocator, b32 has_header, char delim )
{
	CSV_Error error = ECSV_Error__NONE;
	GEN_ASSERT_NOT_NULL( root );
	GEN_ASSERT_NOT_NULL( text );
	zero_item( root );

	adt_make_branch( root, allocator, NULL, has_header ? false : true );

	char* currentChar = text;
	char* beginChar;
	char* endChar;

	ssize columnIndex       = 0;
	ssize totalColumnIndex = 0;

	do
	{
		char delimiter = 0;
		currentChar = ccast( char*, str_trim( currentChar, false ));

		if ( *currentChar == 0 )
			break;

		ADT_Node rowItem = { 0 };
		rowItem.type     = EADT_TYPE_STRING;

	#ifndef GEN_PARSER_DISABLE_ANALYSIS
		rowItem.name_style = EADT_NAME_STYLE_NO_QUOTES;
	#endif

		/* handle string literals */
		if ( *currentChar == '"' )
		{
			currentChar   += 1;
			beginChar      = currentChar;
			endChar        = currentChar;
			rowItem.string = beginChar;
		#ifndef GEN_PARSER_DISABLE_ANALYSIS
			rowItem.name_style = EADT_NAME_STYLE_DOUBLE_QUOTE;
		#endif
			do
			{
				endChar = ccast( char*, str_skip( endChar, '"' ));

				if ( *endChar && *( endChar + 1 ) == '"' )
				{
					endChar += 2;
				}
				else
					break;
			}
			while ( *endChar );

			if ( *endChar == 0 )
			{
				GEN_CSV_ASSERT( "unmatched quoted string" );
				error = ECSV_Error__UNEXPECTED_END_OF_INPUT;
				return error;
			}

			*endChar    = 0;
			currentChar = ccast( char*, str_trim( endChar + 1, true ));
			delimiter   = * currentChar;

			/* unescape escaped quotes (so that unescaped text escapes :) */
			{
				char* escapedChar = beginChar;
				do
				{
					if ( *escapedChar == '"' && *( escapedChar + 1 ) == '"' )
					{
						mem_move( escapedChar, escapedChar + 1, str_len( escapedChar ) );
					}
					escapedChar++;
				}
				while ( *escapedChar );
			}
		}
		else if ( *currentChar == delim )
		{
			delimiter      = * currentChar;
			rowItem.string = "";
		}
		else if ( *currentChar )
		{
			/* regular data */
			beginChar      = currentChar;
			endChar        = currentChar;
			rowItem.string = beginChar;

			do
			{
				endChar++;
			}
			while ( * endChar && * endChar != delim && * endChar != '\n' );

			if ( * endChar )
			{
				currentChar = ccast( char*, str_trim( endChar, true ));

				while ( char_is_space( *( endChar - 1 ) ) )
				{
					endChar--;
				}

				delimiter = * currentChar;
				* endChar = 0;
			}
			else
			{
				delimiter   = 0;
				currentChar = endChar;
			}

			/* check if number and process if so */
			b32   skip_number = false;
			char* num_p       = beginChar;

			// We only consider hexadecimal values if they start with 0x
			if ( str_len(num_p) > 2 && num_p[0] == '0' && (num_p[1] == 'x' || num_p[1] == 'X') )
			{
				num_p += 2; // skip '0x' prefix
				do
				{
					if (!char_is_hex_digit(*num_p))
					{
						skip_number = true;
						break;
					}
				} while (*num_p++);
			}
			else
			{
				skip_number = true;
			}

			if (!skip_number)
			{
				adt_str_to_number(&rowItem);
			}
		}

		if ( columnIndex >= scast(ssize, root->nodes.num()) )
		{
			adt_append_arr( root, NULL );
		}

		root->nodes[ columnIndex ].nodes.append( rowItem );

		if ( delimiter == delim )
		{
			columnIndex++;
			currentChar++;
		}
		else if ( delimiter == '\n' || delimiter == 0 )
		{
			/* check if number of rows is not mismatched */
			if ( totalColumnIndex < columnIndex )
				totalColumnIndex = columnIndex;

			else if ( totalColumnIndex != columnIndex )
			{
				GEN_CSV_ASSERT( "mismatched rows" );
				error = ECSV_Error__MISMATCHED_ROWS;
				return error;
			}

			columnIndex = 0;

			if ( delimiter != 0 )
				currentChar++;
		}
	}
	while ( *currentChar );

	if ( root->nodes.num() == 0 )
	{
		GEN_CSV_ASSERT( "unexpected end of input. stream is empty." );
		error = ECSV_Error__UNEXPECTED_END_OF_INPUT;
		return error;
	}

	/* consider first row as a header. */
	if ( has_header )
	{
		for ( ssize i = 0; i < scast(ssize, root->nodes.num()); i++ )
		{
			CSV_Object* col = root->nodes + i;
			CSV_Object* hdr = col->nodes;
			col->name       = hdr->string;
			col->nodes.remove_at( 0 );
		}
	}

	return error;
}

void csv_free( CSV_Object* obj )
{
	adt_destroy_branch( obj );
}

void _csv_write_record( FileInfo* file, CSV_Object* node )
{
	switch ( node->type )
	{
		case EADT_TYPE_STRING :
			{
#ifndef GEN_PARSER_DISABLE_ANALYSIS
				switch ( node->name_style )
				{
					case EADT_NAME_STYLE_DOUBLE_QUOTE :
						{
							str_fmt_file( file, "\"" );
							adt_print_string( file, node, "\"", "\"" );
							str_fmt_file( file, "\"" );
						}
						break;

					case EADT_NAME_STYLE_NO_QUOTES :
						{
#endif
							str_fmt_file( file, "%s", node->string );
#ifndef GEN_PARSER_DISABLE_ANALYSIS
						}
						break;
				}
#endif
			}
			break;

		case EADT_TYPE_REAL :
		case EADT_TYPE_INTEGER :
			{
				adt_print_number( file, node );
			}
			break;
	}
}

void _csv_write_header( FileInfo* file, CSV_Object* header )
{
	CSV_Object temp = *header;
	temp.string     = temp.name;
	temp.type       = EADT_TYPE_STRING;
	_csv_write_record( file, &temp );
}

void csv_write_delimiter( FileInfo* file, CSV_Object* obj, char delimiter )
{
	GEN_ASSERT_NOT_NULL( file );
	GEN_ASSERT_NOT_NULL( obj );
	GEN_ASSERT( obj->nodes );
	ssize cols = obj->nodes.num();
	if ( cols == 0 )
		return;

	ssize rows = obj->nodes[ 0 ].nodes.num();
	if ( rows == 0 )
		return;

	b32 has_headers = obj->nodes[ 0 ].name != NULL;

	if ( has_headers )
	{
		for ( ssize i = 0; i < cols; i++ )
		{
			_csv_write_header( file, &obj->nodes[ i ] );
			if ( i + 1 != cols )
			{
				str_fmt_file( file, "%c", delimiter );
			}
		}
		str_fmt_file( file, "\n" );
	}

	for ( ssize r = 0; r < rows; r++ )
	{
		for ( ssize i = 0; i < cols; i++ )
		{
			_csv_write_record( file, &obj->nodes[ i ].nodes[ r ] );
			if ( i + 1 != cols )
			{
				str_fmt_file( file, "%c", delimiter );
			}
		}
		str_fmt_file( file, "\n" );
	}
}

String csv_write_string_delimiter( AllocatorInfo a, CSV_Object* obj, char delimiter )
{
	FileInfo tmp;
	file_stream_new( &tmp, a );
	csv_write_delimiter( &tmp, obj, delimiter );
	
	ssize  fsize;
	u8*    buf    = file_stream_buf( &tmp, &fsize );
	String output = String::make_length( a, ( char* )buf, fsize );
	file_close( &tmp );
	return output;
}

#pragma endregion CSV

#pragma endregion Parsing

GEN_NS_END

// GEN_ROLL_OWN_DEPENDENCIES
#endif

GEN_NS_BEGIN

#pragma region StaticData

// TODO : Convert global allocation strategy to use a slab allocation strategy.
global AllocatorInfo  GlobalAllocator;
global Array<Arena>   Global_AllocatorBuckets;

// TODO(Ed) : Make the code pool a dynamic arena
global Array< Pool >  CodePools         = { nullptr };
global Array< Arena > StringArenas      = { nullptr };

global StringTable StringCache;

global Arena LexArena;

global AllocatorInfo Allocator_DataArrays  = heap();
global AllocatorInfo Allocator_CodePool    = heap();
global AllocatorInfo Allocator_Lexer       = heap();
global AllocatorInfo Allocator_StringArena = heap();
global AllocatorInfo Allocator_StringTable = heap();
global AllocatorInfo Allocator_TypeTable   = heap();

#pragma endregion StaticData

#pragma region Constants

global Code access_public;
global Code access_protected;
global Code access_private;

global CodeAttributes attrib_api_export;
global CodeAttributes attrib_api_import;

global Code module_global_fragment;
global Code module_private_fragment;

global Code fmt_newline;

global CodeParam param_varadic;

global CodePragma pragma_once;

global CodePreprocessCond preprocess_else;
global CodePreprocessCond preprocess_endif;

global CodeSpecifiers spec_const;
global CodeSpecifiers spec_consteval;
global CodeSpecifiers spec_constexpr;
global CodeSpecifiers spec_constinit;
global CodeSpecifiers spec_extern_linkage;
global CodeSpecifiers spec_final;
global CodeSpecifiers spec_forceinline;
global CodeSpecifiers spec_global;
global CodeSpecifiers spec_inline;
global CodeSpecifiers spec_internal_linkage;
global CodeSpecifiers spec_local_persist;
global CodeSpecifiers spec_mutable;
global CodeSpecifiers spec_noexcept;
global CodeSpecifiers spec_neverinline;
global CodeSpecifiers spec_override;
global CodeSpecifiers spec_ptr;
global CodeSpecifiers spec_pure;
global CodeSpecifiers spec_ref;
global CodeSpecifiers spec_register;
global CodeSpecifiers spec_rvalue;
global CodeSpecifiers spec_static_member;
global CodeSpecifiers spec_thread_local;
global CodeSpecifiers spec_virtual;
global CodeSpecifiers spec_volatile;

global CodeType t_empty;
global CodeType t_auto;
global CodeType t_void;
global CodeType t_int;
global CodeType t_bool;
global CodeType t_char;
global CodeType t_wchar_t;
global CodeType t_class;
global CodeType t_typename;

global Array< StringCached > PreprocessorDefines;

#ifdef GEN_DEFINE_LIBRARY_CODE_CONSTANTS
global CodeType t_b32;

global CodeType t_s8;
global CodeType t_s16;
global CodeType t_s32;
global CodeType t_s64;

global CodeType t_u8;
global CodeType t_u16;
global CodeType t_u32;
global CodeType t_u64;

global CodeType t_ssize;
global CodeType t_usize;

global CodeType t_f32;
global CodeType t_f64;
#endif

#pragma endregion Constants
#pragma region AST

#	define GEN_AST_BODY_CLASS_UNALLOWED_TYPES \
	case PlatformAttributes:                  \
	case Class_Body:                          \
	case Enum_Body:                           \
	case Extern_Linkage:                      \
	case Function_Body:                       \
	case Function_Fwd:                        \
	case Global_Body:                         \
	case Namespace:                           \
	case Namespace_Body:                      \
	case Operator:                            \
	case Operator_Fwd:                        \
	case Parameters:                          \
	case Specifiers:                          \
	case Struct_Body:                         \
	case Typename:
#	define GEN_AST_BODY_STRUCT_UNALLOWED_TYPES GEN_AST_BODY_CLASS_UNALLOWED_TYPES

#	define GEN_AST_BODY_FUNCTION_UNALLOWED_TYPES \
	case Access_Public:                          \
	case Access_Protected:                       \
	case Access_Private:                         \
	case PlatformAttributes:                     \
	case Class_Body:                             \
	case Enum_Body:                              \
	case Extern_Linkage:                         \
	case Friend:                                 \
	case Function_Body:                          \
	case Function_Fwd:                           \
	case Global_Body:                            \
	case Namespace:                              \
	case Namespace_Body:                         \
	case Operator:                               \
	case Operator_Fwd:                           \
	case Operator_Member:                        \
	case Operator_Member_Fwd:                    \
	case Parameters:                             \
	case Specifiers:                             \
	case Struct_Body:                            \
	case Typename:

#	define GEN_AST_BODY_GLOBAL_UNALLOWED_TYPES \
	case Access_Public: 				       \
	case Access_Protected: 				       \
	case Access_Private: 				       \
	case PlatformAttributes:                   \
	case Class_Body: 					       \
	case Enum_Body: 					       \
	case Execution: 					       \
	case Friend: 						       \
	case Function_Body: 				       \
	case Namespace_Body: 				       \
	case Operator_Member: 				       \
	case Operator_Member_Fwd: 			       \
	case Parameters: 					       \
	case Specifiers: 					       \
	case Struct_Body: 					       \
	case Typename:
#	define GEN_AST_BODY_EXPORT_UNALLOWED_TYPES         GEN_AST_BODY_GLOBAL_UNALLOWED_TYPES
#	define GEN_AST_BODY_EXTERN_LINKAGE_UNALLOWED_TYPES GEN_AST_BODY_GLOBAL_UNALLOWED_TYPES

#	define GEN_AST_BODY_NAMESPACE_UNALLOWED_TYPES \
	case Access_Public: 				          \
	case Access_Protected: 				          \
	case Access_Private: 				          \
	case PlatformAttributes:                      \
	case Class_Body: 					          \
	case Enum_Body: 					          \
	case Execution: 					          \
	case Friend: 						          \
	case Function_Body: 				          \
	case Namespace_Body: 				          \
	case Operator_Member: 				          \
	case Operator_Member_Fwd: 			          \
	case Parameters: 					          \
	case Specifiers: 					          \
	case Struct_Body: 					          \
	case Typename:

Code Code::Global;
Code Code::Invalid;

// This serializes all the data-members in a "debug" format, where each member is printed with its associated value.
char const* AST::debug_str()
{
	String result = String::make_reserve( GlobalAllocator, kilobytes(1) );

	if ( Parent )
		result.append_fmt( "\n\tParent       : %S %S", Parent->type_str(), Name ? Name : "" );
	else
		result.append_fmt( "\n\tParent       : %S", "Null" );

	result.append_fmt( "\n\tName         : %S", Name ? Name : "Null" );
	result.append_fmt( "\n\tType         : %S", type_str() );
	result.append_fmt( "\n\tModule Flags : %S", to_str( ModuleFlags ) );

	switch ( Type )
	{
		using namespace ECode;

		case Invalid:
		case NewLine:
		case Access_Private:
		case Access_Protected:
		case Access_Public:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
		break;

		case Untyped:
		case Execution:
		case Comment:
		case PlatformAttributes:
		case Preprocess_Define:
		case Preprocess_Include:
		case Preprocess_Pragma:
		case Preprocess_If:
		case Preprocess_ElIf:
		case Preprocess_Else:
		case Preprocess_IfDef:
		case Preprocess_IfNotDef:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tContent: %S", Content );
		break;

		case Class:
		case Struct:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmd   : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes  : %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tParentAccess: %s", ParentType ? to_str( ParentAccess )  : "No Parent" );
			result.append_fmt( "\n\tParentType  : %s", ParentType ? ParentType->type_str()  : "Null" );
			result.append_fmt( "\n\tBody        : %S", Body       ? Body->debug_str()       : "Null" );
		break;

		case Class_Fwd:
		case Struct_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmd   : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes  : %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tParentAccess: %s", ParentType ? to_str( ParentAccess )  : "No Parent" );
			result.append_fmt( "\n\tParentType  : %s", ParentType ? ParentType->type_str()  : "Null" );
		break;

		case Constructor:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt      : %S", InlineCmt       ? InlineCmt->Content           : "Null" );
			result.append_fmt( "\n\tSpecs          : %S", Specs           ? Specs->to_string()           : "Null" );
			result.append_fmt( "\n\tInitializerList: %S", InitializerList ? InitializerList->to_string() : "Null" );
			result.append_fmt( "\n\tParams         : %S", Params          ? Params->to_string()          : "Null" );
			result.append_fmt( "\n\tBody           : %S", Body            ? Body->debug_str()            : "Null" );
		break;

		case Constructor_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt      : %S", InlineCmt       ? InlineCmt->Content           : "Null" );
			result.append_fmt( "\n\tSpecs          : %S", Specs           ? Specs->to_string()           : "Null" );
			result.append_fmt( "\n\tInitializerList: %S", InitializerList ? InitializerList->to_string() : "Null" );
			result.append_fmt( "\n\tParams         : %S", Params          ? Params->to_string()          : "Null" );
		break;

		case Destructor:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt      : %S", InlineCmt ? InlineCmt->Content : "Null" );
			result.append_fmt( "\n\tSpecs          : %S", Specs     ? Specs->to_string() : "Null" );
			result.append_fmt( "\n\tBody           : %S", Body      ? Body->debug_str()  : "Null" );
		break;

		case Destructor_Fwd:
		break;

		case Enum:
		case Enum_Class:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt       : %S", InlineCmt      ? InlineCmt->Content          : "Null" );
			result.append_fmt( "\n\tAttributes      : %S", Attributes     ? Attributes->to_string()     : "Null" );
			result.append_fmt( "\n\tUnderlying Type : %S", UnderlyingType ? UnderlyingType->to_string() : "Null" );
			result.append_fmt( "\n\tBody            : %S", Body           ? Body->debug_str()           : "Null" );
		break;

		case Enum_Fwd:
		case Enum_Class_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt       : %S", InlineCmt      ? InlineCmt->Content          : "Null" );
			result.append_fmt( "\n\tAttributes      : %S", Attributes     ? Attributes->to_string()     : "Null" );
			result.append_fmt( "\n\tUnderlying Type : %S", UnderlyingType ? UnderlyingType->to_string() : "Null" );
		break;

		case Extern_Linkage:
		case Namespace:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tBody: %S", Body ? Body->debug_str() : "Null" );
		break;

		case Friend:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt  : %S", InlineCmt   ? InlineCmt->Content       : "Null" );
			result.append_fmt( "\n\tDeclaration: %S", Declaration ? Declaration->to_string() : "Null" );
		break;

		case Function:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes: %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()      : "Null" );
			result.append_fmt( "\n\tReturnType: %S", ReturnType ? ReturnType->to_string() : "Null" );
			result.append_fmt( "\n\tParams    : %S", Params     ? Params->to_string()     : "Null" );
			result.append_fmt( "\n\tBody      : %S", Body       ? Body->debug_str()       : "Null" );
		break;

		case Function_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes: %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()      : "Null" );
			result.append_fmt( "\n\tReturnType: %S", ReturnType ? ReturnType->to_string() : "Null" );
			result.append_fmt( "\n\tParams    : %S", Params     ? Params->to_string()     : "Null" );
		break;

		case Module:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
		break;

		case Operator:
		case Operator_Member:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes: %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()      : "Null" );
			result.append_fmt( "\n\tReturnType: %S", ReturnType ? ReturnType->to_string() : "Null" );
			result.append_fmt( "\n\tParams    : %S", Params     ? Params->to_string()     : "Null" );
			result.append_fmt( "\n\tBody      : %S", Body       ? Body->debug_str()       : "Null" );
			result.append_fmt( "\n\tOp        : %S", to_str( Op ) );
		break;

		case Operator_Fwd:
		case Operator_Member_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content      : "Null" );
			result.append_fmt( "\n\tAttributes: %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()      : "Null" );
			result.append_fmt( "\n\tReturnType: %S", ReturnType ? ReturnType->to_string() : "Null" );
			result.append_fmt( "\n\tParams    : %S", Params     ? Params->to_string()     : "Null" );
			result.append_fmt( "\n\tOp        : %S", to_str( Op ) );
		break;

		case Operator_Cast:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content     : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()     : "Null" );
			result.append_fmt( "\n\tValueType : %S", ValueType  ? ValueType->to_string() : "Null" );
			result.append_fmt( "\n\tBody      : %S", Body       ? Body->debug_str()      : "Null" );
		break;

		case Operator_Cast_Fwd:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt : %S", InlineCmt  ? InlineCmt->Content     : "Null" );
			result.append_fmt( "\n\tSpecs     : %S", Specs      ? Specs->to_string()     : "Null" );
			result.append_fmt( "\n\tValueType : %S", ValueType  ? ValueType->to_string() : "Null" );
		break;

		case Parameters:
			result.append_fmt( "\n\tNumEntries: %d", NumEntries );
			result.append_fmt( "\n\tLast      : %S", Last->Name );
			result.append_fmt( "\n\tNext      : %S", Next->Name );
			result.append_fmt( "\n\tValueType : %S", ValueType ? ValueType->to_string() : "Null" );
			result.append_fmt( "\n\tValue     : %S", Value     ? Value->to_string()     : "Null" );
		break;

		case Specifiers:
		{
			result.append_fmt( "\n\tNumEntries: %d", NumEntries );
			result.append( "\n\tArrSpecs: " );

			s32 idx  = 0;
			s32 left = NumEntries;
			while ( left-- )
			{
				StrC spec = ESpecifier::to_str( ArrSpecs[idx] );
				result.append_fmt( "%.*s, ", spec.Len, spec.Ptr );
				idx++;
			}
			result.append_fmt( "\n\tNextSpecs: %S", NextSpecs ? NextSpecs->debug_str() : "Null" );
		}
		break;

		case Template:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tParams     : %S", Params      ? Params->to_string()      : "Null" );
			result.append_fmt( "\n\tDeclaration: %S", Declaration ? Declaration->to_string() : "Null" );
		break;

		case Typedef:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt     : %S", InlineCmt      ? InlineCmt->Content          : "Null" );
			result.append_fmt( "\n\tUnderlyingType: %S", UnderlyingType ? UnderlyingType->to_string() : "Null" );
		break;

		case Typename:
			result.append_fmt( "\n\tAttributes     : %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tSpecs          : %S", Specs      ? Specs->to_string()      : "Null" );
			result.append_fmt( "\n\tReturnType     : %S", ReturnType ? ReturnType->to_string() : "Null" );
			result.append_fmt( "\n\tParams         : %S", Params     ? Params->to_string()     : "Null" );
			result.append_fmt( "\n\tArrExpr        : %S", ArrExpr    ? ArrExpr->to_string()    : "Null" );
		break;

		case Union:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tAttributes: %S", Attributes ? Attributes->to_string() : "Null" );
			result.append_fmt( "\n\tBody      : %S", Body       ? Body->debug_str()       : "Null" );
		break;

		case Using:
			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt     : %S", InlineCmt      ? InlineCmt->Content          : "Null" );
			result.append_fmt( "\n\tAttributes    : %S", Attributes     ? Attributes->to_string()     : "Null" );
			result.append_fmt( "\n\tUnderlyingType: %S", UnderlyingType ? UnderlyingType->to_string() : "Null" );
		break;

		case Variable:

			if ( Parent && Parent->Type == Variable )
			{
				// Its a NextVar
				result.append_fmt( "\n\tSpecs       : %S", Specs        ? Specs->to_string()        : "Null" );
				result.append_fmt( "\n\tValue       : %S", Value        ? Value->to_string()        : "Null" );
				result.append_fmt( "\n\tBitfieldSize: %S", BitfieldSize ? BitfieldSize->to_string() : "Null" );
				result.append_fmt( "\n\tNextVar     : %S", NextVar      ? NextVar->debug_str()      : "Null" );
				break;
			}

			if ( Prev )
				result.append_fmt( "\n\tPrev: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );
			if ( Next )
				result.append_fmt( "\n\tNext: %S %S", Prev->type_str(), Prev->Name ? Prev->Name : "Null" );

			result.append_fmt( "\n\tInlineCmt   : %S", InlineCmt    ? InlineCmt->Content        : "Null" );
			result.append_fmt( "\n\tAttributes  : %S", Attributes   ? Attributes->to_string()   : "Null" );
			result.append_fmt( "\n\tSpecs       : %S", Specs        ? Specs->to_string()        : "Null" );
			result.append_fmt( "\n\tValueType   : %S", ValueType    ? ValueType->to_string()    : "Null" );
			result.append_fmt( "\n\tBitfieldSize: %S", BitfieldSize ? BitfieldSize->to_string() : "Null" );
			result.append_fmt( "\n\tValue       : %S", Value        ? Value->to_string()        : "Null" );
			result.append_fmt( "\n\tNextVar     : %S", NextVar      ? NextVar->debug_str()      : "Null" );
		break;
	}

	return result;
}

AST* AST::duplicate()
{
	using namespace ECode;

	AST* result = make_code().ast;

	mem_copy( result, this, sizeof( AST ) );

	result->Parent = nullptr;
	return result;
}

String AST::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void AST::to_string( String& result )
{
	local_persist thread_local
	char SerializationLevel = 0;

	switch ( Type )
	{
		using namespace ECode;

		case Invalid:
		#ifdef GEN_DONT_ALLOW_INVALID_CODE
			log_failure("Attempted to serialize invalid code! - %S", Parent ? Parent->debug_str() : Name );
		#else
			result.append_fmt( "Invalid Code!" );
		#endif
		break;

		case NewLine:
			result.append("\n");
		break;

		case Untyped:
		case Execution:
		case Comment:
		case PlatformAttributes:
			result.append( Content );
		break;

		case Access_Private:
		case Access_Protected:
		case Access_Public:
			result.append( Name );
		break;

		case Class:
			cast<CodeClass>().to_string_def( result );
		break;

		case Class_Fwd:
			cast<CodeClass>().to_string_fwd( result );
		break;

		case Constructor:
			cast<CodeConstructor>().to_string_def( result );
		break;

		case Constructor_Fwd:
			cast<CodeConstructor>().to_string_fwd( result );
		break;

		case Destructor:
			cast<CodeDestructor>().to_string_def( result );
		break;

		case Destructor_Fwd:
			cast<CodeDestructor>().to_string_fwd( result );
		break;

		case Enum:
			cast<CodeEnum>().to_string_def( result );
		break;

		case Enum_Fwd:
			cast<CodeEnum>().to_string_fwd( result );
		break;

		case Enum_Class:
			cast<CodeEnum>().to_string_class_def( result );
		break;

		case Enum_Class_Fwd:
			cast<CodeEnum>().to_string_class_fwd( result );
		break;

		case Export_Body:
			cast<CodeBody>().to_string_export( result );
		break;

		case Extern_Linkage:
			cast<CodeExtern>().to_string( result );
		break;

		case Friend:
			cast<CodeFriend>().to_string( result );
		break;

		case Function:
			cast<CodeFn>().to_string_def( result );
		break;

		case Function_Fwd:
			cast<CodeFn>().to_string_fwd( result );
		break;

		case Module:
			cast<CodeModule>().to_string( result );
		break;

		case Namespace:
			cast<CodeNS>().to_string( result );
		break;

		case Operator:
		case Operator_Member:
			cast<CodeOperator>().to_string_def( result );
		break;

		case Operator_Fwd:
		case Operator_Member_Fwd:
			cast<CodeOperator>().to_string_fwd( result );
		break;

		case Operator_Cast:
			cast<CodeOpCast>().to_string_def( result );
		break;

		case Operator_Cast_Fwd:
			cast<CodeOpCast>().to_string_fwd( result );
		break;

		case Parameters:
			cast<CodeParam>().to_string( result );
		break;

		case Preprocess_Define:
			cast<CodeDefine>().to_string( result );
		break;

		case Preprocess_If:
			cast<CodePreprocessCond>().to_string_if( result );
		break;

		case Preprocess_IfDef:
			cast<CodePreprocessCond>().to_string_ifdef( result );
		break;

		case Preprocess_IfNotDef:
			cast<CodePreprocessCond>().to_string_ifndef( result );
		break;

		case Preprocess_Include:
			cast<CodeInclude>().to_string( result );
		break;

		case Preprocess_ElIf:
			cast<CodePreprocessCond>().to_string_elif( result );
		break;

		case Preprocess_Else:
			cast<CodePreprocessCond>().to_string_else( result );
		break;

		case Preprocess_EndIf:
			cast<CodePreprocessCond>().to_string_endif( result );
		break;

		case Preprocess_Pragma:
			cast<CodePragma>().to_string( result );
		break;

		case Specifiers:
			cast<CodeSpecifiers>().to_string( result );
		break;

		case Struct:
			cast<CodeStruct>().to_string_def( result );
		break;

		case Struct_Fwd:
			cast<CodeStruct>().to_string_fwd( result );
		break;

		case Template:
			cast<CodeTemplate>().to_string( result );
		break;

		case Typedef:
			cast<CodeTypedef>().to_string( result );
		break;

		case Typename:
			cast<CodeType>().to_string( result );
		break;

		case Union:
			cast<CodeUnion>().to_string( result );
		break;

		case Using:
			cast<CodeUsing>().to_string( result );
		break;

		case Using_Namespace:
			cast<CodeUsing>().to_string_ns( result );
		break;

		case Variable:
			cast<CodeVar>().to_string( result );
		break;

		case Enum_Body:
		case Class_Body:
		case Extern_Linkage_Body:
		case Function_Body:
		case Global_Body:
		case Namespace_Body:
		case Struct_Body:
		case Union_Body:
			cast<CodeBody>().to_string( result );
		break;
	}
}

bool AST::is_equal( AST* other )
{
/*
	AST values are either some u32 value, a cached string, or a pointer to another AST.

	u32 values are compared by value.
	Cached strings are compared by pointer.
	AST nodes are compared with AST::is_equal.
*/
	if ( other == nullptr )
	{
		log_fmt( "AST::is_equal: other is null\nAST: %S", debug_str() );
		return false;
	}

	if ( Type != other->Type )
	{
		log_fmt("AST::is_equal: Type check failure with other\nAST: %S\nOther: %S"
			, debug_str()
			, other->debug_str()
		);

		return false;
	}

	switch ( Type )
	{
		using namespace ECode;

	#define check_member_val( val )                           \
	if ( val != other->val )                                  \
	{                                                         \
		log_fmt("\nAST::is_equal: Member - " #val " failed\n" \
		        "AST  : %S\n"                                 \
		        "Other: %S\n"                                 \
		    , debug_str()                                     \
		    , other->debug_str()                              \
		);                                                    \
	                                                          \
		return false;                                         \
	}

	#define check_member_str( str )                                 \
	if ( str != other->str )                                        \
	{                                                               \
		log_fmt("\nAST::is_equal: Member string - "#str " failed\n" \
				"AST  : %S\n"                                       \
				"Other: %S\n"                                       \
			, debug_str()                                           \
			, other->debug_str()                                    \
		);                                                          \
	                                                                \
		return false;                                               \
	}

	#define check_member_content( content )                               \
	if ( content != other->content )                                      \
	{                                                                     \
		log_fmt("\nAST::is_equal: Member content - "#content " failed\n"  \
				"AST  : %S\n"                                             \
				"Other: %S\n"                                             \
			, debug_str()                                                 \
			, other->debug_str()                                          \
		);                                                                \
                                                                          \
		log_fmt("Content cannot be trusted to be unique with this check " \
			"so it must be verified by eye for now\n"                     \
			"AST   Content:\n%S\n"                                        \
			"Other Content:\n%S\n"                                        \
			, content.visualize_whitespace()                              \
			, other->content.visualize_whitespace()                       \
		);                                                                \
	}

	#define check_member_ast( ast )                                                                \
	if ( ast )                                                                                     \
	{                                                                                              \
		if ( other->ast == nullptr )                                                               \
		{                                                                                          \
			log_fmt("\nAST::is_equal: Failed for member " #ast " other equivalent param is null\n" \
					"AST  : %s\n"                                                                  \
					"Other: %s\n"                                                                  \
					"For ast member: %s\n"                                                         \
				, debug_str()                                                                      \
				, other->debug_str()                                                               \
				, ast->debug_str()                                                                 \
			);                                                                                     \
                                                                                                   \
			return false;                                                                          \
		}                                                                                          \
                                                                                                   \
		if ( ! ast->is_equal( other->ast ) )                                                       \
		{                                                                                          \
			log_fmt( "\nAST::is_equal: Failed for " #ast"\n"                                       \
			         "AST  : %S\n"                                                                 \
			         "Other: %S\n"                                                                 \
			         "For     ast member: %S\n"                                                    \
			         "other's ast member: %S\n"                                                    \
				, debug_str()                                                                      \
				, other->debug_str()                                                               \
				, ast->debug_str()                                                                 \
				, other->ast->debug_str()                                                          \
			);                                                                                     \
		                                                                                           \
			return false;                                                                          \
		}                                                                                          \
	}

		case NewLine:
		case Access_Public:
		case Access_Protected:
		case Access_Private:
		case Preprocess_Else:
		case Preprocess_EndIf:
			return true;


		// Comments are not validated.
		case Comment:
			return true;

		case Execution:
		case PlatformAttributes:
		case Untyped:
		{
			check_member_content( Content );

			return true;
		}

		case Class_Fwd:
		case Struct_Fwd:
		{
			check_member_str( Name );
			check_member_ast( ParentType );
			check_member_val( ParentAccess );
			check_member_ast( Attributes );

			return true;
		}

		case Class:
		case Struct:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ParentType );
			check_member_val( ParentAccess );
			check_member_ast( Attributes );
			check_member_ast( Body );

			return true;
		}

		case Constructor:
		{
			check_member_ast( InitializerList );
			check_member_ast( Params );
			check_member_ast( Body );

			return true;
		}

		case Constructor_Fwd:
		{
			check_member_ast( InitializerList );
			check_member_ast( Params );

			return true;
		}

		case Destructor:
		{
			check_member_ast( Specs );
			check_member_ast( Body );

			return true;
		}

		case Destructor_Fwd:
		{
			check_member_ast( Specs );

			return true;
		}

		case Enum:
		case Enum_Class:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Attributes );
			check_member_ast( UnderlyingType );
			check_member_ast( Body );

			return true;
		}

		case Enum_Fwd:
		case Enum_Class_Fwd:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Attributes );
			check_member_ast( UnderlyingType );

			return true;
		}

		case Extern_Linkage:
		{
			check_member_str( Name );
			check_member_ast( Body );

			return true;
		}

		case Friend:
		{
			check_member_str( Name );
			check_member_ast( Declaration );

			return true;
		}

		case Function:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ReturnType );
			check_member_ast( Attributes );
			check_member_ast( Specs );
			check_member_ast( Params );
			check_member_ast( Body );

			return true;
		}

		case Function_Fwd:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ReturnType );
			check_member_ast( Attributes );
			check_member_ast( Specs );
			check_member_ast( Params );

			return true;
		}

		case Module:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );

			return true;
		}

		case Namespace:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Body );

			return true;
		}

		case Operator:
		case Operator_Member:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ReturnType );
			check_member_ast( Attributes );
			check_member_ast( Specs );
			check_member_ast( Params );
			check_member_ast( Body );

			return true;
		}

		case Operator_Fwd:
		case Operator_Member_Fwd:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ReturnType );
			check_member_ast( Attributes );
			check_member_ast( Specs );
			check_member_ast( Params );

			return true;
		}

		case Operator_Cast:
		{
			check_member_str( Name );
			check_member_ast( Specs );
			check_member_ast( ValueType );
			check_member_ast( Body );

			return true;
		}

		case Operator_Cast_Fwd:
		{
			check_member_str( Name );
			check_member_ast( Specs );
			check_member_ast( ValueType );

			return true;
		}

		case Parameters:
		{
			if ( NumEntries > 1 )
			{
				AST* curr       = this;
				AST* curr_other = other;
				while ( curr != nullptr  )
				{
					if ( curr )
					{
						if ( curr_other == nullptr )
						{
							log_fmt("\nAST::is_equal: Failed for parameter, other equivalent param is null\n"
							        "AST  : %S\n"
							        "Other: %S\n"
							        "For ast member: %S\n"
							    , curr->debug_str()
							);

							return false;
						}

						if ( curr->Name != curr_other->Name )
						{
							log_fmt( "\nAST::is_equal: Failed for parameter name check\n"
									"AST  : %S\n"
									"Other: %S\n"
									"For     ast member: %S\n"
									"other's ast member: %S\n"
								, debug_str()
								, other->debug_str()
								, curr->debug_str()
								, curr_other->debug_str()
							);
							return false;
						}

						if ( curr->ValueType && ! curr->ValueType->is_equal(curr_other->ValueType) )
						{
							log_fmt( "\nAST::is_equal: Failed for parameter value type check\n"
									"AST  : %S\n"
									"Other: %S\n"
									"For     ast member: %S\n"
									"other's ast member: %S\n"
								, debug_str()
								, other->debug_str()
								, curr->debug_str()
								, curr_other->debug_str()
							);
							return false;
						}

						if ( curr->Value && ! curr->Value->is_equal(curr_other->Value) )
						{
							log_fmt( "\nAST::is_equal: Failed for parameter value check\n"
									"AST  : %S\n"
									"Other: %S\n"
									"For     ast member: %S\n"
									"other's ast member: %S\n"
								, debug_str()
								, other->debug_str()
								, curr->debug_str()
								, curr_other->debug_str()
							);
							return false;
						}
					}

					curr       = curr->Next;
					curr_other = curr_other->Next;
				}

				check_member_val( NumEntries );

				return true;
			}

			check_member_str( Name );
			check_member_ast( ValueType );
			check_member_ast( Value );
			check_member_ast( ArrExpr );

			return true;
		}

		case Preprocess_Define:
		{
			check_member_str( Name );
			check_member_content( Content );

			return true;
		}

		case Preprocess_If:
		case Preprocess_IfDef:
		case Preprocess_IfNotDef:
		case Preprocess_ElIf:
		{
			check_member_content( Content );

			return true;
		}

		case Preprocess_Include:
		case Preprocess_Pragma:
		{
			check_member_content( Content );

			return true;
		}

		case Specifiers:
		{
			check_member_val( NumEntries );
			check_member_str( Name );
			for ( s32 idx = 0; idx < NumEntries; ++idx )
			{
				check_member_val( ArrSpecs[ idx ] );
			}
			return true;
		}

		case Template:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Params );
			check_member_ast( Declaration );

			return true;
		}

		case Typedef:
		{
			check_member_val( IsFunction );
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Specs );
			check_member_ast( UnderlyingType );

			return true;
		}
		case Typename:
		{
			check_member_val( IsParamPack );
			check_member_str( Name );
			check_member_ast( Specs );
			check_member_ast( ArrExpr );

			return true;
		}

		case Union:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( Attributes );
			check_member_ast( Body );

			return true;
		}

		case Using:
		case Using_Namespace:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( UnderlyingType );
			check_member_ast( Attributes );

			return true;
		}

		case Variable:
		{
			check_member_val( ModuleFlags );
			check_member_str( Name );
			check_member_ast( ValueType );
			check_member_ast( BitfieldSize );
			check_member_ast( Value );
			check_member_ast( Attributes );
			check_member_ast( Specs );
			check_member_ast( NextVar );

			return true;
		}

		case Class_Body:
		case Enum_Body:
		case Export_Body:
		case Global_Body:
		case Namespace_Body:
		case Struct_Body:
		case Union_Body:
		{
			check_member_ast( Front );
			check_member_ast( Back );

			AST* curr       = Front;
			AST* curr_other = other->Front;
			while ( curr != nullptr )
			{
				if ( curr_other == nullptr )
				{
					log_fmt("\nAST::is_equal: Failed for body, other equivalent param is null\n"
					        "AST  : %S\n"
					        "Other: %S\n"
					        "For ast member: %S\n"
					    , curr->debug_str()
					);

					return false;
				}

				if ( ! curr->is_equal( curr_other ) )
				{
					log_fmt( "\nAST::is_equal: Failed for body\n"
							"AST  : %S\n"
							"Other: %S\n"
							"For     ast member: %S\n"
							"other's ast member: %S\n"
						, debug_str()
						, other->debug_str()
						, curr->debug_str()
						, curr_other->debug_str()
					);

					return false;
				}

				curr       = curr->Next;
				curr_other = curr_other->Next;
			}

			check_member_val( NumEntries );

			return true;
		}

	#undef check_member_val
	#undef check_member_str
	#undef check_member_ast
	}

	return true;
}

bool AST::validate_body()
{
	using namespace ECode;

#define CheckEntries( Unallowed_Types )                                                               \
	do                                                                                                \
	{                                                                                                 \
		for ( Code entry : cast<CodeBody>() )                                                         \
		{                                                                                             \
			switch ( entry->Type )                                                                    \
			{                                                                                         \
				Unallowed_Types                                                                       \
					log_failure( "AST::validate_body: Invalid entry in body %s", entry.debug_str() ); \
					return false;                                                                     \
			}                                                                                         \
		}                                                                                             \
	}                                                                                                 \
	while (0);

	switch ( Type )
	{
		case Class_Body:
			CheckEntries( GEN_AST_BODY_CLASS_UNALLOWED_TYPES );
		break;
		case Enum_Body:
			for ( Code entry : cast<CodeBody>() )
			{
				if ( entry->Type != Untyped )
				{
					log_failure( "AST::validate_body: Invalid entry in enum body (needs to be untyped or comment) %s", entry.debug_str() );
					return false;
				}
			}
		break;
		case Export_Body:
			CheckEntries( GEN_AST_BODY_CLASS_UNALLOWED_TYPES );
		break;
		case Extern_Linkage:
			CheckEntries( GEN_AST_BODY_EXTERN_LINKAGE_UNALLOWED_TYPES );
		break;
		case Function_Body:
			CheckEntries( GEN_AST_BODY_FUNCTION_UNALLOWED_TYPES );
		break;
		case Global_Body:
			for (Code entry : cast<CodeBody>())
			{
				switch (entry->Type)
				{
					case Access_Public:
					case Access_Protected:
					case Access_Private:
					case PlatformAttributes:
					case Class_Body:
					case Enum_Body:
					case Execution:
					case Friend:
					case Function_Body:
					case Global_Body:
					case Namespace_Body:
					case Operator_Member:
					case Operator_Member_Fwd:
					case Parameters:
					case Specifiers:
					case Struct_Body:
					case Typename:
						log_failure("AST::validate_body: Invalid entry in body %s", entry.debug_str());
					return false;
				}
			}
		break;
		case Namespace_Body:
			CheckEntries( GEN_AST_BODY_NAMESPACE_UNALLOWED_TYPES );
		break;
		case Struct_Body:
			CheckEntries( GEN_AST_BODY_STRUCT_UNALLOWED_TYPES );
		break;
		case Union_Body:
			for ( Code entry : Body->cast<CodeBody>() )
			{
				if ( entry->Type != Untyped )
				{
					log_failure( "AST::validate_body: Invalid entry in union body (needs to be untyped or comment) %s", entry.debug_str() );
					return false;
				}
			}
		break;

		default:
			log_failure( "AST::validate_body: Invalid this AST does not have a body %s", debug_str() );
			return false;
	}

	return false;

#undef CheckEntries
}

String Code::to_string()
{
	if ( ast == nullptr )
	{
		log_failure( "Code::to_string: Cannot convert code to string, AST is null!" );
		return { nullptr };
	}
	return rcast( AST*, ast )->to_string();
}

String CodeAttributes::to_string()
{
	return ast->Content.duplicate( GlobalAllocator );
}

String CodeBody::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Untyped:
		case Execution:
			result.append( raw()->Content );
		break;

		case Enum_Body:
		case Class_Body:
		case Extern_Linkage_Body:
		case Function_Body:
		case Global_Body:
		case Namespace_Body:
		case Struct_Body:
		case Union_Body:
			to_string( result );
		break;

		case Export_Body:
			to_string_export( result );
		break;
	}
	return result;
}

void CodeBody::to_string( String& result )
{
	Code curr = ast->Front;
	s32  left = ast->NumEntries;
	while ( left -- )
	{
		result.append_fmt( "%S", curr.to_string() );
		++curr;
	}
}

void CodeBody::to_string_export( String& result )
{
	result.append_fmt( "export\n{\n" );

	Code curr = *this;
	s32  left = ast->NumEntries;
	while ( left-- )
	{
		result.append_fmt( "%S", curr.to_string() );
		++curr;
	}

	result.append_fmt( "};\n" );
}

String CodeComment::to_string()
{
	return ast->Content.duplicate( GlobalAllocator );
}

String CodeConstructor::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch (ast->Type)
	{
		using namespace ECode;
		case Constructor:
			to_string_def( result );
		break;
		case Constructor_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeConstructor::to_string_def( String& result )
{
	AST* ClassStructParent = ast->Parent->Parent;
	if (ClassStructParent) {
		result.append( ClassStructParent->Name );
	}
	else {
		result.append( ast->Name );
	}

	if ( ast->Params )
		result.append_fmt( "( %S )", ast->Params.to_string() );
	else
		result.append( "()" );

	if ( ast->InitializerList )
		result.append_fmt( " : %S", ast->InitializerList.to_string() );

	if ( ast->InlineCmt )
		result.append_fmt( " // %S", ast->InlineCmt->Content );

	result.append_fmt( "\n{\n%S\n}\n", ast->Body.to_string() );
}

void CodeConstructor::to_string_fwd( String& result )
{
	AST* ClassStructParent = ast->Parent->Parent;
	if (ClassStructParent) {
		result.append( ClassStructParent->Name );
	}
	else {
		result.append( ast->Name );
	}

	if ( ast->Params )
		result.append_fmt( "( %S )", ast->Params.to_string() );
	else
		result.append_fmt("()");

	if (ast->Body)
		result.append_fmt( " = %S", ast->Body.to_string() );

	if ( ast->InlineCmt )
		result.append_fmt( "; // %S\n", ast->InlineCmt->Content );
	else
		result.append( ";\n" );
}

String CodeClass::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Class:
			to_string_def( result );
		break;
		case Class_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeClass::to_string_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append( "class " );

	if ( ast->Attributes )
	{
		result.append_fmt( "%S ", ast->Attributes.to_string() );
	}

	if ( ast->ParentType )
	{
		char const* access_level = to_str( ast->ParentAccess );

		result.append_fmt( "%S : %s %S", ast->Name, access_level, ast->ParentType.to_string() );

		CodeType interface = ast->ParentType->Next->cast< CodeType >();
		if ( interface )
			result.append( "\n" );

		while ( interface )
		{
			result.append_fmt( ", %S", interface.to_string() );
			interface = interface->Next ? interface->Next->cast< CodeType >() : CodeType { nullptr };
		}
	}
	else if ( ast->Name )
	{
		result.append( ast->Name );
	}

	if ( ast->InlineCmt )
	{
		result.append_fmt( " // %S", ast->InlineCmt->Content );
	}

	result.append_fmt( "\n{\n%S\n}", ast->Body.to_string() );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
		result.append(";\n");
}

void CodeClass::to_string_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "class %S %S", ast->Attributes.to_string(), ast->Name );

	else result.append_fmt( "class %S", ast->Name );

	// Check if it can have an end-statement
	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
	{
		if ( ast->InlineCmt )
			result.append_fmt( "; // %S\n", ast->InlineCmt->Content );
		else
			result.append(";\n");
	}
}

String CodeDefine::to_string()
{
	return String::fmt_buf( GlobalAllocator, "#define %S %S\n", ast->Name, ast->Content );
}

void CodeDefine::to_string( String& result )
{
	result.append_fmt( "#define %S %S\n", ast->Name, ast->Content );
}

String CodeDestructor::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Destructor:
			to_string_def( result );
		break;
		case Destructor_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeDestructor::to_string_def( String& result )
{
	if ( ast->Name )
	{
		result.append_fmt( "%S()", ast->Name );
	}
	else if ( ast->Specs )
	{
		if ( ast->Specs.has( ESpecifier::Virtual ) )
			result.append_fmt( "virtual ~%S()", ast->Parent->Name );
		else
			result.append_fmt( "~%S()", ast->Parent->Name );
	}
	else
		result.append_fmt( "~%S()", ast->Parent->Name );

	result.append_fmt( "\n{\n%S\n}\n", ast->Body.to_string() );
}

void CodeDestructor::to_string_fwd( String& result )
{
	if ( ast->Specs )
	{
		if ( ast->Specs.has( ESpecifier::Virtual ) )
			result.append_fmt( "virtual ~%S();\n", ast->Parent->Name );
		else
			result.append_fmt( "~%S()", ast->Parent->Name );

		if ( ast->Specs.has( ESpecifier::Pure ) )
			result.append( " = 0;" );
		else if (ast->Body)
			result.append_fmt( " = %S;", ast->Body.to_string() );
	}
	else
		result.append_fmt( "~%S();", ast->Parent->Name );

	if ( ast->InlineCmt )
		result.append_fmt( "  %S", ast->InlineCmt->Content );
	else
		result.append("\n");
}

String CodeEnum::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Enum:
			to_string_def( result );
		break;
		case Enum_Fwd:
			to_string_fwd( result );
		break;
		case Enum_Class:
			to_string_class_def( result );
		break;
		case Enum_Class_Fwd:
			to_string_class_fwd( result );
		break;
	}
	return result;
}

void CodeEnum::to_string_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes || ast->UnderlyingType )
	{
		result.append( "enum " );

		if ( ast->Attributes )
			result.append_fmt( "%S ", ast->Attributes.to_string() );

		if ( ast->UnderlyingType )
			result.append_fmt( "%S : %S\n{\n%S\n}"
				, ast->Name
				, ast->UnderlyingType.to_string()
				, ast->Body.to_string()
			);

		else result.append_fmt( "%S\n{\n%S\n}", ast->Name, ast->Body.to_string() );
	}
	else result.append_fmt( "enum %S\n{\n%S\n}", ast->Name, ast->Body.to_string() );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
		result.append(";\n");
}

void CodeEnum::to_string_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	result.append_fmt( "enum %S : %S", ast->Name, ast->UnderlyingType.to_string() );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
	{
		if ( ast->InlineCmt )
			result.append_fmt(";  %S", ast->InlineCmt->Content );
		else
			result.append(";\n");
	}
}

void CodeEnum::to_string_class_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes || ast->UnderlyingType )
	{
		result.append( "enum class " );

		if ( ast->Attributes )
		{
			result.append_fmt( "%S ", ast->Attributes.to_string() );
		}

		if ( ast->UnderlyingType )
		{
			result.append_fmt( "%S : %S\n{\n%S\n}", ast->Name, ast->UnderlyingType.to_string(), ast->Body.to_string() );
		}
		else
		{
			result.append_fmt( "%S\n{\n%S\n}", ast->Name, ast->Body.to_string() );
		}
	}
	else
	{
		result.append_fmt( "enum class %S\n{\n%S\n}", ast->Body.to_string() );
	}

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
		result.append(";\n");
}

void CodeEnum::to_string_class_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append( "enum class " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	result.append_fmt( "%S : %S", ast->Name, ast->UnderlyingType.to_string() );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
	{
		if ( ast->InlineCmt )
			result.append_fmt(";  %S", ast->InlineCmt->Content );
		else
			result.append(";\n");
	}
}

String CodeExec::to_string()
{
	return ast->Content.duplicate( GlobalAllocator );
}

void CodeExtern::to_string( String& result )
{
	if ( ast->Body )
		result.append_fmt( "extern \"%S\"\n{\n%S\n}\n", ast->Name, ast->Body.to_string() );
	else
		result.append_fmt( "extern \"%S\"\n{}\n", ast->Name );
}

String CodeInclude::to_string()
{
	return String::fmt_buf( GlobalAllocator, "#include %S\n", ast->Content );
}

void CodeInclude::to_string( String& result )
{
	result.append_fmt( "#include %S\n", ast->Content );
}

String CodeFriend::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeFriend::to_string( String& result )
{
	result.append_fmt( "friend %S", ast->Declaration->to_string() );

	if ( ast->Declaration->Type != ECode::Function && result[ result.length() - 1 ] != ';' )
	{
		result.append( ";" );
	}

	if ( ast->InlineCmt )
		result.append_fmt("  %S", ast->InlineCmt->Content );
	else
		result.append("\n");
}

String CodeFn::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Function:
			to_string_def( result );
		break;
		case Function_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeFn::to_string_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export" );

	if ( ast->Attributes )
		result.append_fmt( " %S ", ast->Attributes.to_string() );

	bool prefix_specs = false;
	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );

				prefix_specs = true;
			}
		}
	}

	if ( ast->Attributes || prefix_specs )
		result.append( "\n" );

	if ( ast->ReturnType )
		result.append_fmt( "%S %S(", ast->ReturnType.to_string(), ast->Name );

	else
		result.append_fmt( "%S(", ast->Name );

	if ( ast->Params )
		result.append_fmt( "%S)", ast->Params.to_string() );

	else
		result.append( ")" );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	result.append_fmt( "\n{\n%S\n}\n", ast->Body.to_string() );
}

void CodeFn::to_string_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	b32 prefix_specs = false;
	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) || ! (spec != ESpecifier::Pure) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );

				prefix_specs = true;
			}
		}
	}

	if ( ast->Attributes || prefix_specs )
	{
		result.append("\n" );
	}

	if ( ast->ReturnType )
		result.append_fmt( "%S %S(", ast->ReturnType.to_string(), ast->Name );

	else
		result.append_fmt( "%S(", ast->Name );

	if ( ast->Params )
		result.append_fmt( "%S)", ast->Params.to_string() );

	else
		result.append( ")" );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	if ( ast->Specs && ast->Specs.has( ESpecifier::Pure ) >= 0 )
		result.append( " = 0;" );
	else if (ast->Body)
		result.append_fmt( " = %S;", ast->Body.to_string() );

	if ( ast->InlineCmt )
		result.append_fmt( ";  %S", ast->InlineCmt->Content );
	else
		result.append( ";\n" );
}

String CodeModule::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeModule::to_string( String& result )
{
	if (((u32(ModuleFlag::Export) & u32(ast->ModuleFlags)) == u32(ModuleFlag::Export)))
		result.append("export ");

	if (((u32(ModuleFlag::Import) & u32(ast->ModuleFlags)) == u32(ModuleFlag::Import)))
		result.append("import ");

	result.append_fmt( "%S;\n", ast->Name );
}

String CodeNS::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeNS::to_string( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append_fmt( "namespace %S\n{\n%S\n}\n", ast->Name , ast->Body.to_string() );
}

String CodeOperator::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Operator:
		case Operator_Member:
			to_string_def( result );
		break;
		case Operator_Fwd:
		case Operator_Member_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeOperator::to_string_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	if ( ast->Attributes || ast->Specs )
	{
		result.append("\n" );
	}

	if ( ast->ReturnType )
		result.append_fmt( "%S %S (", ast->ReturnType.to_string(), ast->Name );

	if ( ast->Params )
		result.append_fmt( "%S)", ast->Params.to_string() );

	else
		result.append( ")" );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	result.append_fmt( "\n{\n%S\n}\n"
		, ast->Body.to_string()
	);
}

void CodeOperator::to_string_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "%S\n", ast->Attributes.to_string() );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	if ( ast->Attributes || ast->Specs )
	{
		result.append("\n" );
	}

	result.append_fmt( "%S %S (", ast->ReturnType.to_string(), ast->Name );

	if ( ast->Params )
		result.append_fmt( "%S)", ast->Params.to_string() );

	else
		result.append_fmt( ")" );

	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}
	}

	if ( ast->InlineCmt )
		result.append_fmt( ";  %S", ast->InlineCmt->Content );
	else
		result.append( ";\n" );
}

String CodeOpCast::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Operator_Cast:
			to_string_def( result );
		break;
		case Operator_Cast_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeOpCast::to_string_def( String& result )
{
	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( "%*s ", spec_str.Len, spec_str.Ptr );
			}
		}

		if ( ast->Name && ast->Name.length() )
			result.append_fmt( "%Soperator %S()", ast->Name, ast->ValueType.to_string() );
		else
			result.append_fmt( "operator %S()", ast->ValueType.to_string() );

		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %.*s", spec_str.Len, spec_str.Ptr );
			}
		}

		result.append_fmt( "\n{\n%S\n}\n", ast->Body.to_string() );
		return;
	}

	if ( ast->Name && ast->Name.length() )
		result.append_fmt("%Soperator %S()\n{\n%S\n}\n", ast->Name, ast->ValueType.to_string(), ast->Body.to_string() );
	else
		result.append_fmt("operator %S()\n{\n%S\n}\n", ast->ValueType.to_string(), ast->Body.to_string() );
}

void CodeOpCast::to_string_fwd( String& result )
{
	if ( ast->Specs )
	{
		for ( SpecifierT spec : ast->Specs )
		{
			if ( ! ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( "%*s ", spec_str.Len, spec_str.Ptr );
			}
		}

		result.append_fmt( "operator %S()", ast->ValueType.to_string() );

		for ( SpecifierT spec : ast->Specs )
		{
			if ( ESpecifier::is_trailing( spec ) )
			{
				StrC spec_str = ESpecifier::to_str( spec );
				result.append_fmt( " %*s", spec_str.Len, spec_str.Ptr );
			}
		}

		if ( ast->InlineCmt )
			result.append_fmt( ";  %S", ast->InlineCmt->Content );
		else
			result.append( ";\n" );
		return;
	}

	if ( ast->InlineCmt )
		result.append_fmt("operator %S();  %S", ast->ValueType.to_string() );
	else
		result.append_fmt("operator %S();\n", ast->ValueType.to_string() );
}

String CodeParam::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeParam::to_string( String& result )
{
	if ( ast->Macro )
	{
		// Related to parsing: ( <macro>, ... )
		result.append( ast->Macro.ast->Content );
		// Could also be: ( <macro> <type <name>, ... )
	}

	if ( ast->Name )
	{
		if ( ast->ValueType.ast == nullptr )
			result.append_fmt( " %S", ast->Name );
		else
			result.append_fmt( " %S %S", ast->ValueType.to_string(), ast->Name );

	}
	else if ( ast->ValueType )
		result.append_fmt( " %S", ast->ValueType.to_string() );

	if ( ast->PostNameMacro )
	{
		result.append_fmt(" %S", ast->PostNameMacro.to_string() );
	}

	if ( ast->Value )
		result.append_fmt( " = %S", ast->Value.to_string() );

	if ( ast->NumEntries - 1 > 0 )
	{
		for ( CodeParam param : ast->Next )
		{
			result.append_fmt( ", %S", param.to_string() );
		}
	}
}

String CodePreprocessCond::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Preprocess_If:
			to_string_if( result );
		break;
		case Preprocess_IfDef:
			to_string_ifdef( result );
		break;
		case Preprocess_IfNotDef:
			to_string_ifndef( result );
		break;
		case Preprocess_ElIf:
			to_string_elif( result );
		break;
		case Preprocess_Else:
			to_string_else( result );
		break;
		case Preprocess_EndIf:
			to_string_endif( result );
		break;
	}
	return result;
}

void CodePreprocessCond::to_string_if( String& result )
{
	result.append_fmt( "#if %S\n", ast->Content );
}

void CodePreprocessCond::to_string_ifdef( String& result )
{
	result.append_fmt( "#ifdef %S\n", ast->Content );
}

void CodePreprocessCond::to_string_ifndef( String& result )
{
	result.append_fmt( "#ifndef %S\n", ast->Content );
}

void CodePreprocessCond::to_string_elif( String& result )
{
	result.append_fmt( "#elif %S\n", ast->Content );
}

void CodePreprocessCond::to_string_else( String& result )
{
	result.append_fmt( "#else\n" );
}

void CodePreprocessCond::to_string_endif( String& result )
{
	result.append_fmt( "#endif\n" );
}

String CodePragma::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodePragma::to_string( String& result )
{
	result.append_fmt( "#pragma %S\n", ast->Content );
}

String CodeSpecifiers::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeSpecifiers::to_string( String& result )
{
	s32 idx  = 0;
	s32 left = ast->NumEntries;
	while ( left-- )
	{
		StrC spec = ESpecifier::to_str( ast->ArrSpecs[idx] );
		result.append_fmt( "%.*s ", spec.Len, spec.Ptr );
		idx++;
	}
}

String CodeStruct::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Struct:
			to_string_def( result );
		break;
		case Struct_Fwd:
			to_string_fwd( result );
		break;
	}
	return result;
}

void CodeStruct::to_string_def( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append( "struct " );

	if ( ast->Attributes )
	{
		result.append_fmt( "%S ", ast->Attributes.to_string() );
	}

	if ( ast->ParentType )
	{
		char const* access_level = to_str( ast->ParentAccess );

		result.append_fmt( "%S : %s %S", ast->Name, access_level, ast->ParentType.to_string() );

		CodeType interface = ast->ParentType->Next->cast< CodeType >();
		if ( interface )
			result.append( "\n" );

		while ( interface )
		{
			result.append_fmt( ", %S", interface.to_string() );
			interface = interface->Next ? interface->Next->cast< CodeType >() : CodeType { nullptr };
		}
	}
	else if ( ast->Name )
	{
		result.append( ast->Name );
	}

	if ( ast->InlineCmt )
	{
		result.append_fmt( " // %S", ast->InlineCmt->Content );
	}

	result.append_fmt( "\n{\n%S\n}", ast->Body.to_string() );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
		result.append(";\n");
}

void CodeStruct::to_string_fwd( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "struct %S %S", ast->Attributes.to_string(), ast->Name );

	else result.append_fmt( "struct %S", ast->Name );

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
	{
		if ( ast->InlineCmt )
			result.append_fmt(";  %S", ast->InlineCmt->Content );
		else
			result.append(";\n");
	}
}

String CodeTemplate::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeTemplate::to_string( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Params )
		result.append_fmt( "template< %S >\n%S", ast->Params.to_string(), ast->Declaration.to_string() );
	else
		result.append_fmt( "template<>\n%S", ast->Declaration.to_string() );
}

String CodeTypedef::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeTypedef::to_string( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append( "typedef ");

	// Determines if the typedef is a function typename
	if ( ast->UnderlyingType->ReturnType )
		result.append( ast->UnderlyingType.to_string() );
	else
		result.append_fmt( "%S %S", ast->UnderlyingType.to_string(), ast->Name );

	if ( ast->UnderlyingType->Type == ECode::Typename && ast->UnderlyingType->ArrExpr )
	{
		result.append_fmt( "[ %S ];", ast->UnderlyingType->ArrExpr->to_string() );

		AST* next_arr_expr = ast->UnderlyingType->ArrExpr->Next;
		while ( next_arr_expr )
		{
			result.append_fmt( "[ %S ];", next_arr_expr->to_string() );
			next_arr_expr = next_arr_expr->Next;
		}
	}
	else
	{
		result.append( ";" );
	}

	if ( ast->InlineCmt )
		result.append_fmt("  %S", ast->InlineCmt->Content);
	else
		result.append("\n");
}

String CodeType::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeType::to_string( String& result )
{
	#if defined(GEN_USE_NEW_TYPENAME_PARSING)
		if ( ast->ReturnType && ast->Params )
		{
			if ( ast->Attributes )
				result.append_fmt( "%S ", ast->Attributes.to_string() );
			else
			{
				if ( ast->Specs )
					result.append_fmt( "%S ( %S ) ( %S ) %S", ast->ReturnType.to_string(), ast->Name, ast->Params.to_string(), ast->Specs.to_string() );
				else
					result.append_fmt( "%S ( %S ) ( %S )", ast->ReturnType.to_string(), ast->Name, ast->Params.to_string() );
			}

			break;
		}
	#else
		if ( ast->ReturnType && ast->Params )
		{
			if ( ast->Attributes )
				result.append_fmt( "%S ", ast->Attributes.to_string() );
			else
			{
				if ( ast->Specs )
					result.append_fmt( "%S %S ( %S ) %S", ast->ReturnType.to_string(), ast->Name, ast->Params.to_string(), ast->Specs.to_string() );
				else
					result.append_fmt( "%S %S ( %S )", ast->ReturnType.to_string(), ast->Name, ast->Params.to_string() );
			}

			return;
		}
	#endif

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	if ( ast->Specs )
		result.append_fmt( "%S %S", ast->Name, ast->Specs.to_string() );
	else
		result.append_fmt( "%S", ast->Name );

	if ( ast->IsParamPack )
		result.append("...");
}

String CodeUnion::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeUnion::to_string( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	result.append( "union " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	if ( ast->Name )
	{
		result.append_fmt( "%S\n{\n%S\n}"
			, ast->Name
			, ast->Body.to_string()
		);
	}
	else
	{
		// Anonymous union
		result.append_fmt( "\n{\n%S\n}"
			, ast->Body.to_string()
		);
	}

	if ( ast->Parent.ast == nullptr || ( ast->Parent->Type != ECode::Typedef && ast->Parent->Type != ECode::Variable ) )
		result.append(";\n");
}

String CodeUsing::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	switch ( ast->Type )
	{
		using namespace ECode;
		case Using:
			to_string( result );
		break;
		case Using_Namespace:
			to_string_ns( result );
		break;
	}
	return result;
}

void CodeUsing::to_string( String& result )
{
	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes )
		result.append_fmt( "%S ", ast->Attributes.to_string() );

	if ( ast->UnderlyingType )
	{
		result.append_fmt( "using %S = %S", ast->Name, ast->UnderlyingType.to_string() );

		if ( ast->UnderlyingType->ArrExpr )
		{
			result.append_fmt( "[ %S ]", ast->UnderlyingType->ArrExpr.to_string() );

			AST* next_arr_expr = ast->UnderlyingType->ArrExpr->Next;
			while ( next_arr_expr )
			{
				result.append_fmt( "[ %S ]", next_arr_expr->to_string() );
				next_arr_expr = next_arr_expr->Next;
			}
		}

		result.append( ";" );
	}
	else
		result.append_fmt( "using %S;", ast->Name );

	if ( ast->InlineCmt )
		result.append_fmt("  %S\n", ast->InlineCmt->Content );
	else
		result.append("\n");
}

void CodeUsing::to_string_ns( String& result )
{
	if ( ast->InlineCmt )
		result.append_fmt( "using namespace $S;  %S", ast->Name, ast->InlineCmt->Content );
	else
		result.append_fmt( "using namespace %s;\n", ast->Name );
}

String CodeVar::to_string()
{
	String result = String::make( GlobalAllocator, "" );
	to_string( result );
	return result;
}

void CodeVar::to_string( String& result )
{
	if ( ast->Parent && ast->Parent->Type == ECode::Variable )
	{
		// Its a comma-separated variable ( a NextVar )

		if ( ast->Specs )
			result.append_fmt( "%S ", ast->Specs.to_string() );

		result.append( ast->Name );

		if ( ast->ValueType->ArrExpr )
		{
			result.append_fmt( "[ %S ]", ast->ValueType->ArrExpr.to_string() );

			AST* next_arr_expr = ast->ValueType->ArrExpr->Next;
			while ( next_arr_expr )
			{
				result.append_fmt( "[ %S ]", next_arr_expr->to_string() );
				next_arr_expr = next_arr_expr->Next;
			}
		}

		if ( ast->Value )
		{
			if ( ast->VarConstructorInit )
				result.append_fmt( "( %S ", ast->Value.to_string() );
			else
				result.append_fmt( " = %S", ast->Value.to_string() );
		}

		// Keep the chain going...
		if ( ast->NextVar )
			result.append_fmt( ", %S", ast->NextVar.to_string() );

		if ( ast->VarConstructorInit )
			result.append( " )");

		return;
	}

	if ( bitfield_is_equal( u32, ast->ModuleFlags, ModuleFlag::Export ))
		result.append( "export " );

	if ( ast->Attributes || ast->Specs )
	{
		if ( ast->Attributes )
			result.append_fmt( "%S ", ast->Specs.to_string() );

		if ( ast->Specs )
			result.append_fmt( "%S\n", ast->Specs.to_string() );

		result.append_fmt( "%S %S", ast->ValueType.to_string(), ast->Name );

		if ( ast->ValueType->ArrExpr )
		{
			result.append_fmt( "[ %S ]", ast->ValueType->ArrExpr.to_string() );

			AST* next_arr_expr = ast->ValueType->ArrExpr->Next;
			while ( next_arr_expr )
			{
				result.append_fmt( "[ %S ]", next_arr_expr->to_string() );
				next_arr_expr = next_arr_expr->Next;
			}
		}

		if ( ast->BitfieldSize )
			result.append_fmt( " : %S", ast->BitfieldSize.to_string() );

		if ( ast->Value )
		{
			if ( ast->VarConstructorInit )
				result.append_fmt( "( %S ", ast->Value.to_string() );
			else
				result.append_fmt( " = %S", ast->Value.to_string() );
		}

		if ( ast->NextVar )
			result.append_fmt( ", %S", ast->NextVar.to_string() );

		if ( ast->VarConstructorInit )
			result.append( " )");

		if ( ast->InlineCmt )
			result.append_fmt(";  %S", ast->InlineCmt->Content);
		else
			result.append( ";\n" );

		return;
	}

	if ( ast->BitfieldSize )
		result.append_fmt( "%S %S : %S", ast->ValueType.to_string(), ast->Name, ast->BitfieldSize.to_string() );

	else if ( ast->ValueType->ArrExpr )
	{
		result.append_fmt( "%S %S[ %S ]", ast->ValueType.to_string(), ast->Name, ast->ValueType->ArrExpr.to_string() );

		AST* next_arr_expr = ast->ValueType->ArrExpr->Next;
		while ( next_arr_expr )
		{
			result.append_fmt( "[ %S ]", next_arr_expr->to_string() );
			next_arr_expr = next_arr_expr->Next;
		}
	}

	else
		result.append_fmt( "%S %S", ast->ValueType.to_string(), ast->Name );

	if ( ast->Value )
	{
		if ( ast->VarConstructorInit )
			result.append_fmt( "( %S ", ast->Value.to_string() );
		else
			result.append_fmt( " = %S", ast->Value.to_string() );
	}

	if ( ast->NextVar )
		result.append_fmt( ", %S", ast->NextVar.to_string() );

	if ( ast->VarConstructorInit )
		result.append( " )");

	result.append( ";" );

	if ( ast->InlineCmt )
		result.append_fmt("  %S", ast->InlineCmt->Content);
	else
		result.append("\n");
}
#pragma endregion AST

#pragma region Interface

namespace parser {
internal void init();
internal void deinit();
}

internal
void* Global_Allocator_Proc( void* allocator_data, AllocType type, ssize size, ssize alignment, void* old_memory, ssize old_size, u64 flags )
{
	Arena* last = & Global_AllocatorBuckets.back();

	switch ( type )
	{
		case EAllocation_ALLOC:
		{
			if ( ( last->TotalUsed + size ) > last->TotalSize )
			{
				Arena bucket = Arena::init_from_allocator( heap(), Global_BucketSize );

				if ( bucket.PhysicalStart == nullptr )
					GEN_FATAL( "Failed to create bucket for Global_AllocatorBuckets");

				if ( ! Global_AllocatorBuckets.append( bucket ) )
					GEN_FATAL( "Failed to append bucket to Global_AllocatorBuckets");

				last = & Global_AllocatorBuckets.back();
			}

			return alloc_align( * last, size, alignment );
		}
		case EAllocation_FREE:
		{
			// Doesn't recycle.
		}
		break;
		case EAllocation_FREE_ALL:
		{
			// Memory::cleanup instead.
		}
		break;
		case EAllocation_RESIZE:
		{
			if ( last->TotalUsed + size > last->TotalSize )
			{
				Arena bucket = Arena::init_from_allocator( heap(), Global_BucketSize );

				if ( bucket.PhysicalStart == nullptr )
					GEN_FATAL( "Failed to create bucket for Global_AllocatorBuckets");

				if ( ! Global_AllocatorBuckets.append( bucket ) )
					GEN_FATAL( "Failed to append bucket to Global_AllocatorBuckets");

				last = & Global_AllocatorBuckets.back();
			}

			void* result = alloc_align( last->Backing, size, alignment );

			if ( result != nullptr && old_memory != nullptr )
			{
				mem_copy( result, old_memory, old_size );
			}

			return result;
		}
	}

	return nullptr;
}

internal
void define_constants()
{
	Code::Global          = make_code();
	Code::Global->Name    = get_cached_string( txt("Global Code") );
	Code::Global->Content = Code::Global->Name;

	Code::Invalid = make_code();
	Code::Invalid.set_global();

	t_empty          = (CodeType) make_code();
	t_empty->Type    = ECode::Typename;
	t_empty->Name    = get_cached_string( txt("") );
	t_empty.set_global();

	access_private       = make_code();
	access_private->Type = ECode::Access_Private;
	access_private->Name = get_cached_string( txt("private:\n") );
	access_private.set_global();

	access_protected       = make_code();
	access_protected->Type = ECode::Access_Protected;
	access_protected->Name = get_cached_string( txt("protected:\n") );
	access_protected.set_global();

	access_public       = make_code();
	access_public->Type = ECode::Access_Public;
	access_public->Name = get_cached_string( txt("public:\n") );
	access_public.set_global();

	attrib_api_export = def_attributes( code(GEN_API_Export_Code));
	attrib_api_export.set_global();

	attrib_api_import = def_attributes( code(GEN_API_Import_Code));
	attrib_api_import.set_global();

	module_global_fragment          = make_code();
	module_global_fragment->Type    = ECode::Untyped;
	module_global_fragment->Name    = get_cached_string( txt("module;") );
	module_global_fragment->Content = module_global_fragment->Name;
	module_global_fragment.set_global();

	module_private_fragment          = make_code();
	module_private_fragment->Type    = ECode::Untyped;
	module_private_fragment->Name    = get_cached_string( txt("module : private;") );
	module_private_fragment->Content = module_private_fragment->Name;
	module_private_fragment.set_global();

	fmt_newline = make_code();
	fmt_newline->Type = ECode::NewLine;
	fmt_newline.set_global();

	pragma_once          = (CodePragma) make_code();
	pragma_once->Type    = ECode::Preprocess_Pragma;
	pragma_once->Name    = get_cached_string( txt("once") );
	pragma_once->Content = pragma_once->Name;
	pragma_once.set_global();

	param_varadic            = (CodeType) make_code();
	param_varadic->Type      = ECode::Parameters;
	param_varadic->Name      = get_cached_string( txt("...") );
	param_varadic->ValueType = t_empty;
	param_varadic.set_global();

	preprocess_else = (CodePreprocessCond) make_code();
	preprocess_else->Type = ECode::Preprocess_Else;
	preprocess_else.set_global();

	preprocess_endif = (CodePreprocessCond) make_code();
	preprocess_endif->Type = ECode::Preprocess_EndIf;
	preprocess_endif.set_global();

#	define def_constant_code_type( Type_ )   \
		t_##Type_ = def_type( name(Type_) ); \
		t_##Type_.set_global();

	def_constant_code_type( auto );
	def_constant_code_type( void );
	def_constant_code_type( int );
	def_constant_code_type( bool );
	def_constant_code_type( char );
	def_constant_code_type( wchar_t );
	def_constant_code_type( class );
	def_constant_code_type( typename );

#ifdef GEN_DEFINE_LIBRARY_CODE_CONSTANTS
	t_b32 = def_type( name(b32) );

	def_constant_code_type( s8 );
	def_constant_code_type( s16 );
	def_constant_code_type( s32 );
	def_constant_code_type( s64 );

	def_constant_code_type( u8 );
	def_constant_code_type( u16 );
	def_constant_code_type( u32 );
	def_constant_code_type( u64 );

	def_constant_code_type( ssize );
	def_constant_code_type( usize );

	def_constant_code_type( f32 );
	def_constant_code_type( f64 );
#endif
#	undef def_constant_code_type


#	define def_constant_spec( Type_, ... )                                  \
		spec_##Type_ = def_specifiers( num_args(__VA_ARGS__), __VA_ARGS__); \
		spec_##Type_.set_global();

#	pragma push_macro("forceinline")
#	pragma push_macro("global")
#	pragma push_macro("internal")
#	pragma push_macro("local_persist")
#	pragma push_macro("neverinline")
#	undef forceinline
#	undef global
#	undef internal
#	undef local_persist
#	undef neverinline
	def_constant_spec( const,            ESpecifier::Const );
	def_constant_spec( consteval,        ESpecifier::Consteval );
	def_constant_spec( constexpr,        ESpecifier::Constexpr );
	def_constant_spec( constinit,        ESpecifier::Constinit );
	def_constant_spec( extern_linkage,   ESpecifier::External_Linkage );
	def_constant_spec( final, 		     ESpecifier::Final );
	def_constant_spec( forceinline,      ESpecifier::ForceInline );
	def_constant_spec( global,           ESpecifier::Global );
	def_constant_spec( inline,           ESpecifier::Inline );
	def_constant_spec( internal_linkage, ESpecifier::Internal_Linkage );
	def_constant_spec( local_persist,    ESpecifier::Local_Persist );
	def_constant_spec( mutable,          ESpecifier::Mutable );
	def_constant_spec( neverinline,      ESpecifier::NeverInline );
	def_constant_spec( noexcept,         ESpecifier::NoExceptions );
	def_constant_spec( override,         ESpecifier::Override );
	def_constant_spec( ptr,              ESpecifier::Ptr );
	def_constant_spec( pure,             ESpecifier::Pure )
	def_constant_spec( ref,              ESpecifier::Ref );
	def_constant_spec( register,         ESpecifier::Register );
	def_constant_spec( rvalue,           ESpecifier::RValue );
	def_constant_spec( static_member,    ESpecifier::Static );
	def_constant_spec( thread_local,     ESpecifier::Thread_Local );
	def_constant_spec( virtual, 		 ESpecifier::Virtual );
	def_constant_spec( volatile, 	     ESpecifier::Volatile)

	spec_local_persist = def_specifiers( 1, ESpecifier::Local_Persist );
	spec_local_persist.set_global();

#	pragma pop_macro("forceinline")
#	pragma pop_macro("global")
#	pragma pop_macro("internal")
#	pragma pop_macro("local_persist")
#	pragma pop_macro("neverinline")

#	undef def_constant_spec
}

void init()
{
	// Setup global allocator
	{
		GlobalAllocator = AllocatorInfo { & Global_Allocator_Proc, nullptr };

		Global_AllocatorBuckets = Array<Arena>::init_reserve( heap(), 128 );

		if ( Global_AllocatorBuckets == nullptr )
			GEN_FATAL( "Failed to reserve memory for Global_AllocatorBuckets");

		Arena bucket = Arena::init_from_allocator( heap(), Global_BucketSize );

		if ( bucket.PhysicalStart == nullptr )
			GEN_FATAL( "Failed to create first bucket for Global_AllocatorBuckets");

		Global_AllocatorBuckets.append( bucket );

	}

	// Setup the arrays
	{
		CodePools = Array<Pool>::init_reserve( Allocator_DataArrays, InitSize_DataArrays );

		if ( CodePools == nullptr )
			GEN_FATAL( "gen::init: Failed to initialize the CodePools array" );

		StringArenas = Array<Arena>::init_reserve( Allocator_DataArrays, InitSize_DataArrays );

		if ( StringArenas == nullptr )
			GEN_FATAL( "gen::init: Failed to initialize the StringArenas array" );
	}

	// Setup the code pool and code entries arena.
	{
		Pool code_pool = Pool::init( Allocator_CodePool, CodePool_NumBlocks, sizeof(AST) );

		if ( code_pool.PhysicalStart == nullptr )
			GEN_FATAL( "gen::init: Failed to initialize the code pool" );

		CodePools.append( code_pool );

		LexArena = Arena::init_from_allocator( Allocator_Lexer, LexAllocator_Size );

		Arena string_arena = Arena::init_from_allocator( Allocator_StringArena, SizePer_StringArena );

		if ( string_arena.PhysicalStart == nullptr )
			GEN_FATAL( "gen::init: Failed to initialize the string arena" );

		StringArenas.append( string_arena );
	}

	// Setup the hash tables
	{
		StringCache = StringTable::init( Allocator_StringTable );

		if ( StringCache.Entries == nullptr )
			GEN_FATAL( "gen::init: Failed to initialize the StringCache");
	}

	// Preprocessor Defines
	PreprocessorDefines = Array<StringCached>::init_reserve( GlobalAllocator, kilobytes(1) );

	define_constants();
	parser::init();
}

void deinit()
{
	usize index = 0;
	usize left  = CodePools.num();
	do
	{
		Pool* code_pool = & CodePools[index];
		code_pool->free();
		index++;
	}
	while ( left--, left );

	index = 0;
	left  = StringArenas.num();
	do
	{
		Arena* string_arena = & StringArenas[index];
		string_arena->free();
		index++;
	}
	while ( left--, left );

	StringCache.destroy();

	CodePools.free();
	StringArenas.free();

	LexArena.free();

	PreprocessorDefines.free();

	index = 0;
	left  = Global_AllocatorBuckets.num();
	do
	{
		Arena* bucket = & Global_AllocatorBuckets[ index ];
		bucket->free();
		index++;
	}
	while ( left--, left );

	Global_AllocatorBuckets.free();
	parser::deinit();
}

void reset()
{
	s32 index = 0;
	s32 left  = CodePools.num();
	do
	{
		Pool* code_pool = & CodePools[index];
		code_pool->clear();
		index++;
	}
	while ( left--, left );

	index = 0;
	left  = StringArenas.num();
	do
	{
		Arena* string_arena = & StringArenas[index];
		string_arena->TotalUsed = 0;;
		index++;
	}
	while ( left--, left );

	StringCache.clear();

	define_constants();
}

AllocatorInfo get_string_allocator( s32 str_length )
{
	Arena* last = & StringArenas.back();

	usize size_req = str_length + sizeof(String::Header) + sizeof(char*);

	if ( last->TotalUsed + ssize(size_req) > last->TotalSize )
	{
		Arena new_arena = Arena::init_from_allocator( Allocator_StringArena, SizePer_StringArena );

		if ( ! StringArenas.append( new_arena ) )
			GEN_FATAL( "gen::get_string_allocator: Failed to allocate a new string arena" );

		last = & StringArenas.back();
	}

	return * last;
}

// Will either make or retrive a code string.
StringCached get_cached_string( StrC str )
{
	s32 hash_length = str.Len > kilobytes(1) ? kilobytes(1) : str.Len;
	u64 key         = crc32( str.Ptr, hash_length );
	{
		StringCached* result = StringCache.get( key );

		if ( result )
			return * result;
	}

	String result = String::make( get_string_allocator( str.Len ), str );
	StringCache.set( key, result );

	return result;
}

// Used internally to retireve a Code object form the CodePool.
Code make_code()
{
	Pool* allocator = & CodePools.back();
	if ( allocator->FreeList == nullptr )
	{
		Pool code_pool = Pool::init( Allocator_CodePool, CodePool_NumBlocks, sizeof(AST) );

		if ( code_pool.PhysicalStart == nullptr )
			GEN_FATAL( "gen::make_code: Failed to allocate a new code pool - CodePool allcoator returned nullptr." );

		if ( ! CodePools.append( code_pool ) )
			GEN_FATAL( "gen::make_code: Failed to allocate a new code pool - CodePools failed to append new pool." );

		allocator = & CodePools.back();
	}

	Code result { rcast( AST*, alloc( * allocator, sizeof(AST) )) };
	mem_set( result.ast, 0, sizeof(AST) );
	// result->Type = ECode::Invalid;

	// result->Content     = { nullptr };
	// result->Prev        = { nullptr };
	// result->Next        = { nullptr };
	// result->Token		= nullptr;
	// result->Parent      = { nullptr };
	// result->Name        = { nullptr };
	// result->Type        = ECode::Invalid;
	// result->ModuleFlags = ModuleFlag::Invalid;
	// result->NumEntries  = 0;

	return result;
}

void set_allocator_data_arrays( AllocatorInfo allocator )
{
	Allocator_DataArrays = allocator;
}

void set_allocator_code_pool( AllocatorInfo allocator )
{
	Allocator_CodePool = allocator;
}

void set_allocator_lexer( AllocatorInfo allocator )
{
	Allocator_Lexer = allocator;
}

void set_allocator_string_arena( AllocatorInfo allocator )
{
	Allocator_StringArena = allocator;
}

void set_allocator_string_table( AllocatorInfo allocator )
{
	Allocator_StringArena = allocator;
}

#pragma region Upfront

enum class OpValidateResult : u32
{
	Fail,
	Global,
	Member
};

OpValidateResult operator__validate( OperatorT op, CodeParam params_code, CodeType ret_type, CodeSpecifiers specifier )
{
	using namespace EOperator;

	if ( op == EOperator::Invalid )
	{
		log_failure("gen::def_operator: op cannot be invalid");
		return OpValidateResult::Fail;
	}

#pragma region Helper Macros
#	define check_params()                                                                                 \
	if ( ! params_code )                                                                                  \
	{                                                                                                     \
		log_failure("gen::def_operator: params is null and operator%s requires it", to_str(op));          \
		return OpValidateResult::Fail;                                                                    \
	}                                                                                                     \
	if ( params_code->Type != ECode::Parameters )                                                         \
	{                                                                                                     \
		log_failure("gen::def_operator: params is not of Parameters type - %s", params_code.debug_str()); \
		return OpValidateResult::Fail;                                                                    \
	}

#	define check_param_eq_ret()                                                                     \
	if ( ! is_member_symbol && ! params_code->ValueType.is_equal( ret_type) )                       \
	{                                                                                               \
		log_failure("gen::def_operator: operator%s requires first parameter to equal return type\n" \
			"param types: %s\n"                                                                     \
			"return type: %s",                                                                      \
			to_str(op).Ptr,                                                                         \
			params_code.debug_str(),                                                                \
			ret_type.debug_str()                                                                    \
		);                                                                                          \
		return OpValidateResult::Fail;                                                              \
	}
#pragma endregion Helper Macros

	if ( ! ret_type )
	{
		log_failure("gen::def_operator: ret_type is null but is required by operator%s", to_str(op));
	}

	if ( ret_type->Type != ECode::Typename )
	{
		log_failure("gen::def_operator: ret_type is not of typename type - %s", ret_type.debug_str());
		return OpValidateResult::Fail;
	}

	bool is_member_symbol = false;

	switch ( op )
	{
#	define specs( ... ) num_args( __VA_ARGS__ ), __VA_ARGS__
		case Assign:
			check_params();

			if ( params_code->NumEntries > 1 )
			{
				log_failure("gen::def_operator: "
					"operator%s does not support non-member definition (more than one parameter provided) - %s",
					to_str(op),
					params_code.debug_str()
				);
				return OpValidateResult::Fail;
			}

			is_member_symbol = true;
			break;

		case Assign_Add:
		case Assign_Subtract:
		case Assign_Multiply:
		case Assign_Divide:
		case Assign_Modulo:
		case Assign_BAnd:
		case Assign_BOr:
		case Assign_BXOr:
		case Assign_LShift:
		case Assign_RShift:
			check_params();

			if ( params_code->NumEntries == 1 )
				is_member_symbol = true;

			else
				check_param_eq_ret();

			if (params_code->NumEntries > 2 )
			{
				log_failure("gen::def_operator: operator%s may not be defined with more than two parametes - param count; %d\n%s"
					, to_str(op)
					, params_code->NumEntries
					, params_code.debug_str()
				);
				return OpValidateResult::Fail;
			}
			break;

		case Increment:
		case Decrement:
			// If its not set, it just means its a prefix member op.
			if ( params_code )
			{
				if ( params_code->Type != ECode::Parameters )
				{
					log_failure("gen::def_operator: operator%s params code provided is not of Parameters type - %s"
						, to_str(op)
						, params_code.debug_str()
					);
					return OpValidateResult::Fail;
				}

				switch ( params_code->NumEntries )
				{
					case 1:
						if ( params_code->ValueType.is_equal( t_int ) )
							is_member_symbol = true;

						else
							check_param_eq_ret();
						break;

					case 2:
						check_param_eq_ret();

						if ( ! params_code.get(1).is_equal( t_int ) )
						{
							log_failure("gen::def_operator: "
								"operator%s requires second parameter of non-member definition to be int for post-decrement",
								to_str(op)
							);
							return OpValidateResult::Fail;
						}
						break;

					default:
						log_failure("gen::def_operator: operator%s recieved unexpected number of parameters recived %d instead of 0-2"
							, to_str(op)
							, params_code->NumEntries
						);
						return OpValidateResult::Fail;
				}
			}
			break;

		case Unary_Plus:
		case Unary_Minus:
			if ( ! params_code )
				is_member_symbol = true;

			else
			{
				if ( params_code->Type != ECode::Parameters )
				{
					log_failure("gen::def_operator: params is not of Parameters type - %s", params_code.debug_str());
					return OpValidateResult::Fail;
				}

				if ( params_code->ValueType.is_equal( ret_type ) )
				{
					log_failure("gen::def_operator: "
						"operator%s is non-member symbol yet first paramter does not equal return type\n"
						"param type: %s\n"
						"return type: %s\n"
						, params_code.debug_str()
						, ret_type.debug_str()
					);
					return OpValidateResult::Fail;
				}

				if ( params_code->NumEntries > 1 )
				{
					log_failure("gen::def_operator: operator%s may not have more than one parameter - param count: %d"
						, to_str(op)
						, params_code->NumEntries
					);
					return OpValidateResult::Fail;
				}
			}
			break;

		case BNot:
		{
			// Some compilers let you do this...
		#if 0
			if ( ! ret_type.is_equal( t_bool) )
			{
				log_failure( "gen::def_operator: return type is not a boolean - %s", params_code.debug_str() );
				return OpValidateResult::Fail;
			}
		#endif

			if ( ! params_code )
				is_member_symbol = true;

			else
			{
				if ( params_code->Type != ECode::Parameters )
				{
					log_failure( "gen::def_operator: params is not of Parameters type - %s", params_code.debug_str() );
					return OpValidateResult::Fail;
				}

				if ( params_code->NumEntries > 1 )
				{
					log_failure(
					    "gen::def_operator: operator%s may not have more than one parameter - param count: %d",
					    to_str( op ),
					    params_code->NumEntries
					);
					return OpValidateResult::Fail;
				}
			}
			break;
		}

		case Add:
		case Subtract:
		case Multiply:
		case Divide:
		case Modulo:
		case BAnd:
		case BOr:
		case BXOr:
		case LShift:
		case RShift:
			check_params();

			switch ( params_code->NumEntries )
			{
				case 1:
					is_member_symbol = true;
					break;

				case 2:
					if ( ! params_code->ValueType.is_equal( ret_type ) )
					{
						log_failure("gen::def_operator: "
							"operator%s is non-member symbol yet first paramter does not equal return type\n"
							"param type: %s\n"
							"return type: %s\n"
							, params_code.debug_str()
							, ret_type.debug_str()
						);
						return OpValidateResult::Fail;
					}
					break;

				default:
					log_failure("gen::def_operator: operator%s recieved unexpected number of paramters recived %d instead of 0-2"
						, to_str(op)
						, params_code->NumEntries
					);
					return OpValidateResult::Fail;
			}
			break;

		case UnaryNot:
			if ( ! params_code )
				is_member_symbol = true;

			else
			{
				if ( params_code->Type != ECode::Parameters )
				{
					log_failure("gen::def_operator: params is not of Parameters type - %s", params_code.debug_str());
					return OpValidateResult::Fail;
				}

				if ( params_code->NumEntries != 1 )
				{
					log_failure("gen::def_operator: operator%s recieved unexpected number of paramters recived %d instead of 0-1"
						, to_str(op)
						, params_code->NumEntries
					);
					return OpValidateResult::Fail;
				}
			}

			if ( ! ret_type.is_equal( t_bool ))
			{
				log_failure("gen::def_operator: operator%s return type must be of type bool - %s"
					, to_str(op)
					, ret_type.debug_str()
				);
				return OpValidateResult::Fail;
			}
			break;

		case LAnd:
		case LOr:
		case LEqual:
		case LNot:
		case Lesser:
		case Greater:
		case LesserEqual:
		case GreaterEqual:
			check_params();

			switch ( params_code->NumEntries )
			{
				case 1:
					is_member_symbol = true;
					break;

				case 2:
					break;

				default:
					log_failure("gen::def_operator: operator%s recieved unexpected number of paramters recived %d instead of 1-2"
						, to_str(op)
						, params_code->NumEntries
					);
					return OpValidateResult::Fail;
			}
			break;

		case Indirection:
		case AddressOf:
		case MemberOfPointer:
			if ( params_code && params_code->NumEntries > 1)
			{
				log_failure("gen::def_operator: operator%s recieved unexpected number of paramters recived %d instead of 0-1"
					, to_str(op)
					, params_code->NumEntries
				);
				return OpValidateResult::Fail;
			}
			else
			{
				is_member_symbol = true;
			}
			break;

		case PtrToMemOfPtr:
			if ( params_code )
			{
				log_failure("gen::def_operator: operator%s expects no paramters - %s", to_str(op), params_code.debug_str());
				return OpValidateResult::Fail;
			}
			break;

		case Subscript:
		case FunctionCall:
		case Comma:
			check_params();
			break;

		case New:
		case Delete:
			// This library doesn't support validating new and delete yet.
			break;
#	undef specs
	}

	return is_member_symbol ? OpValidateResult::Member : OpValidateResult::Global;
#	undef check_params
#	undef check_ret_type
#	undef check_param_eq_ret
}


#pragma region Helper Marcos
// This snippet is used in nearly all the functions.
#define name_check( Context_, Name_ )                                                                 \
{                                                                                                     \
	if ( Name_.Len <= 0 )                                                                             \
	{                                                                                                 \
		log_failure( "gen::" stringize(Context_) ": Invalid name length provided - %d",  Name_.Len ); \
		return CodeInvalid;                                                                           \
	}                                                                                                 \
																									  \
	if ( Name_.Ptr == nullptr )                                                                       \
	{                                                                                                 \
		log_failure( "gen::" stringize(Context_) ": name is null" );                                  \
		return CodeInvalid;                                                                           \
	}                                                                                                 \
}

#define null_check( Context_, Code_ )                                                         \
	if ( ! Code_ )                                                                            \
	{                                                                                         \
		log_failure( "gen::" stringize(Context_) ": " stringize(Code_) " provided is null" ); \
		return CodeInvalid;                                                                   \
	}

#define null_or_invalid_check( Context_, Code_ )                                                \
{                                                                                               \
	if ( ! Code_ )                                                                              \
	{                                                                                           \
		log_failure( "gen::" stringize(Context_) ": " stringize(Code_) " provided is null" );   \
		return CodeInvalid;                                                                     \
	}                                                                                           \
																								\
	if ( Code_->is_invalid() )                                                                  \
	{                                                                                           \
		log_failure("gen::" stringize(Context_) ": " stringize(Code_) " provided is invalid" ); \
		return CodeInvalid;                                                                     \
	}                                                                                           \
}

#define not_implemented( Context_ )                             \
	log_failure( "gen::%s: This function is not implemented" ); \
	return CodeInvalid;
#pragma endregion Helper Marcos


/*
The implementaiton of the upfront constructors involves doing three things:
* Validate the arguments given to construct the intended type of AST is valid.
* Construct said AST type.
* Lock the AST (set to readonly) and return the valid object.

If any of the validation fails, it triggers a call to log_failure with as much info the give the user so that they can hopefully
identify the issue without having to debug too much (at least they can debug though...)

The largest of the functions is related to operator overload definitions.
The library validates a good protion of their form and thus the argument processing for is quite a bit.
*/
CodeAttributes def_attributes( StrC content )
{
	if ( content.Len <= 0 || content.Ptr == nullptr )
	{
		log_failure( "gen::def_attributes: Invalid attributes provided" );
		return CodeInvalid;
	}

	Code
	result          = make_code();
	result->Type    = ECode::PlatformAttributes;
	result->Name    = get_cached_string( content );
	result->Content = result->Name;

	return (CodeAttributes) result;
}

CodeComment def_comment( StrC content )
{
	if ( content.Len <= 0 || content.Ptr == nullptr )
	{
		log_failure( "gen::def_comment: Invalid comment provided:" );
		return CodeInvalid;
	}

	static char line[ MaxCommentLineLength ];

	String      cmt_formatted = String::make_reserve( GlobalAllocator, kilobytes(1) );
	char const* end           = content.Ptr + content.Len;
	char const* scanner       = content.Ptr;
	s32         curr          = 0;
	do
	{
		char const* next   = scanner;
		s32         length = 0;
		while ( next != end && scanner[ length ] != '\n' )
		{
			next = scanner + length;
			length++;
		}
		length++;

		str_copy( line, scanner, length );
		cmt_formatted.append_fmt( "//%.*s", length, line );
		mem_set( line, 0, MaxCommentLineLength );

		scanner += length;
	}
	while ( scanner <= end );

	if ( cmt_formatted.back() != '\n' )
		cmt_formatted.append( "\n" );

	Code
	result          = make_code();
	result->Type    = ECode::Comment;
	result->Name    = get_cached_string( cmt_formatted );
	result->Content = result->Name;

	cmt_formatted.free();

	return (CodeComment) result;
}

CodeConstructor def_constructor( CodeParam params, Code initializer_list, Code body )
{
	using namespace ECode;

	if ( params && params->Type != Parameters )
	{
		log_failure("gen::def_constructor: params must be of Parameters type - %s", params.debug_str());
		return CodeInvalid;
	}

	CodeConstructor
	result = (CodeConstructor) make_code();

	if ( params )
	{
		result->Params = params;
	}

	if ( initializer_list )
	{
		result->InitializerList = initializer_list;
	}

	if ( body )
	{
		switch ( body->Type )
		{
			case Function_Body:
			case Untyped:
			break;

			default:
				log_failure("gen::def_constructor: body must be either of Function_Body or Untyped type - %s", body.debug_str());
				return CodeInvalid;
		}

		result->Type = Constructor;
		result->Body = body;
	}
	else
	{
		result->Type = Constructor_Fwd;
	}

	return result;
}

CodeClass def_class( StrC name
	, Code           body
	, CodeType       parent, AccessSpec parent_access
	, CodeAttributes attributes
	, ModuleFlag     mflags
	, CodeType*      interfaces, s32 num_interfaces	)
{
	using namespace ECode;

	name_check( def_class, name );

	if ( attributes && attributes->Type != PlatformAttributes )
	{
		log_failure( "gen::def_class: attributes was not a 'PlatformAttributes' type: %s", attributes.debug_str() );
		return CodeInvalid;
	}

	if ( parent && ( parent->Type != Class && parent->Type != Struct && parent->Type != Typename && parent->Type != Untyped ) )
	{
		log_failure( "gen::def_class: parent provided is not type 'Class', 'Struct', 'Typeanme', or 'Untyped': %s", parent.debug_str() );
		return CodeInvalid;
	}

	CodeClass
	result              = (CodeClass) make_code();
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;

	if ( body )
	{
		switch ( body->Type )
		{
			case Class_Body:
			case Untyped:
			break;

			default:
				log_failure("gen::def_class: body must be either of Class_Body or Untyped type - %s", body.debug_str());
				return CodeInvalid;
		}

		result->Type = Class;
		result->Body = body;
		result->Body->Parent = result; // TODO(Ed): Review this?
	}
	else
	{
		result->Type = Class_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( parent )
	{
		result->ParentAccess = parent_access;
		result->ParentType   = parent;
	}

	if ( interfaces )
	{
		for (s32 idx = 0; idx < num_interfaces; idx++ )
		{
			result.add_interface( interfaces[idx] );
		}
	}

	return result;
}

CodeDefine def_define( StrC name, StrC content )
{
	using namespace ECode;

	name_check( def_define, name );

	// Defines can be empty definitions
#if 0
	if ( content.Len <= 0 || content.Ptr == nullptr )
	{
		log_failure( "gen::def_define: Invalid value provided" );
		return CodeInvalid;
	}
#endif

	CodeDefine
	result          = (CodeDefine) make_code();
	result->Type    = Preprocess_Define;
	result->Name    = get_cached_string( name );
	if ( content.Len <= 0 || content.Ptr == nullptr )
	{
		result->Content = get_cached_string( txt("") );
	}
	else
		result->Content = get_cached_string( content );

	return result;
}

CodeDestructor def_destructor( Code body, CodeSpecifiers specifiers )
{
	using namespace ECode;

	if ( specifiers && specifiers->Type != Specifiers )
	{
		log_failure( "gen::def_destructor: specifiers was not a 'Specifiers' type: %s", specifiers.debug_str() );
		return CodeInvalid;
	}

	CodeDestructor result = (CodeDestructor) make_code();

	if ( specifiers )
		result->Specs = specifiers;

	if ( body )
	{
		switch ( body->Type )
		{
			case Function_Body:
			case Untyped:
			break;

			default:
				log_failure("gen::def_destructor: body must be either of Function_Body or Untyped type - %s", body.debug_str());
				return CodeInvalid;
		}

		result->Type = Destructor;
		result->Body = body;
	}
	else
	{
		result->Type = Destructor_Fwd;
	}

	return result;
}

CodeEnum def_enum( StrC name
	, Code       body,      CodeType       type
	, EnumT      specifier, CodeAttributes attributes
	, ModuleFlag mflags )
{
	using namespace ECode;

	name_check( def_enum, name );

	if ( type && type->Type != Typename )
	{
		log_failure( "gen::def_enum: enum underlying type provided was not of type Typename: %s", type.debug_str() );
		return CodeInvalid;
	}

	if ( attributes && attributes->Type != PlatformAttributes )
	{
		log_failure( "gen::def_enum: attributes was not a 'PlatformAttributes' type: %s", attributes.debug_str() );
		return CodeInvalid;
	}

	CodeEnum
	result              = (CodeEnum) make_code();
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;

	if ( body )
	{
		switch ( body->Type )
		{
			case Enum_Body:
			case Untyped:
			break;

			default:
				log_failure( "gen::def_enum: body must be of Enum_Body or Untyped type %s", body.debug_str());
				return CodeInvalid;
		}

		result->Type = specifier == EnumClass ?
			Enum_Class : Enum;

		result->Body = body;
	}
	else
	{
		result->Type = specifier == EnumClass ?
			Enum_Class_Fwd : Enum_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( type )
	{
		result->UnderlyingType = type;
	}
	else if ( result->Type != Enum_Class_Fwd && result->Type != Enum_Fwd )
	{
		log_failure( "gen::def_enum: enum forward declaration must have an underlying type" );
		return CodeInvalid;
	}

	return result;
}

CodeExec def_execution( StrC content )
{
	if ( content.Len <= 0 || content.Ptr == nullptr )
	{
		log_failure( "gen::def_execution: Invalid execution provided" );
		return CodeInvalid;
	}

	Code
	result          = make_code();
	result->Type    = ECode::Execution;
	result->Name    = get_cached_string( content );
	result->Content = result->Name;

	return (CodeExec) result;
}

CodeExtern def_extern_link( StrC name, Code body )
{
	using namespace ECode;

	name_check( def_extern_linkage, name );
	null_check( def_extern_linkage, body );

	if ( body->Type != Extern_Linkage_Body && body->Type != Untyped )
	{
		log_failure("gen::def_extern_linkage: body is not of extern_linkage or untyped type %s", body->debug_str());
		return CodeInvalid;
	}

	CodeExtern
	result        = (CodeExtern)make_code();
	result->Type  = Extern_Linkage;
	result->Name  = get_cached_string( name );
	result->Body  = body;

	return (CodeExtern) result;
}

CodeFriend def_friend( Code declaration )
{
	using namespace ECode;

	null_check( def_friend, declaration );

	switch ( declaration->Type )
	{
		case Class_Fwd:
		case Function_Fwd:
		case Operator_Fwd:
		case Struct_Fwd:
		case Class:
		case Function:
		case Operator:
		case Struct:
		break;

		default:
			log_failure("gen::def_friend: requires declartion to have class, function, operator, or struct - %s", declaration->debug_str());
			return CodeInvalid;
	}

	CodeFriend
	result       = (CodeFriend) make_code();
	result->Type = Friend;

	result->Declaration = declaration;

	return result;
}

CodeFn def_function( StrC name
	, CodeParam      params ,    CodeType       ret_type, Code body
	, CodeSpecifiers specifiers, CodeAttributes attributes
	, ModuleFlag     mflags )
{
	using namespace ECode;

	name_check( def_function, name );

	if ( params && params->Type != Parameters )
	{
		log_failure( "gen::def_function: params was not a `Parameters` type: %s", params.debug_str() );
		return CodeInvalid;
	}

	if ( ret_type && ret_type->Type != Typename )
	{
		log_failure( "gen::def_function: ret_type was not a Typename: %s", ret_type.debug_str() );
		return CodeInvalid;
	}

	if ( specifiers && specifiers->Type != Specifiers )
	{
		log_failure( "gen::def_function: specifiers was not a `Specifiers` type: %s", specifiers.debug_str() );
		return CodeInvalid;
	}

	if ( attributes && attributes->Type != PlatformAttributes )
	{
		log_failure( "gen::def_function: attributes was not a `PlatformAttributes` type: %s", attributes.debug_str() );
		return CodeInvalid;
	}

	CodeFn
	result              = (CodeFn) make_code();
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;

	if ( body )
	{
		switch ( body->Type )
		{
			case Function_Body:
			case Execution:
			case Untyped:
				break;

			default:
			{
				log_failure("gen::def_function: body must be either of Function_Body, Execution, or Untyped type. %s", body->debug_str());
				return CodeInvalid;
			}
		}

		result->Type = Function;
		result->Body = body;
	}
	else
	{
		result->Type = Function_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	if ( ret_type )
	{
		result->ReturnType = ret_type;
	}
	else
	{
		result->ReturnType = t_void;
	}

	if ( params )
		result->Params = params;

	return result;
}

CodeInclude def_include( StrC path, bool foreign )
{
	if ( path.Len <= 0 || path.Ptr == nullptr )
	{
		log_failure( "gen::def_include: Invalid path provided - %d" );
		return CodeInvalid;
	}

	StrC content = foreign ?
			to_str( str_fmt_buf( "<%.*s>", path.Len, path.Ptr ))
		:	to_str( str_fmt_buf( "\"%.*s\"", path.Len, path.Ptr ));

	Code
	result          = make_code();
	result->Type    = ECode::Preprocess_Include;
	result->Name    = get_cached_string( content );
	result->Content = result->Name;

	return (CodeInclude) result;
}

CodeModule def_module( StrC name, ModuleFlag mflags )
{
	name_check( def_module, name );

	Code
	result              = make_code();
	result->Type        = ECode::Module;
	result->Name        = get_cached_string( name );
	result->Content     = result->Name;
	result->ModuleFlags = mflags;

	return (CodeModule) result;
}

CodeNS def_namespace( StrC name, Code body, ModuleFlag mflags )
{
	using namespace ECode;

	name_check( def_namespace, name );
	null_check( def_namespace, body );

	if ( body->Type != Namespace_Body && body->Type != Untyped )
	{
		log_failure("gen::def_namespace: body is not of namespace or untyped type %s", body.debug_str());
		return CodeInvalid;
	}

	CodeNS
	result              = (CodeNS) make_code();
	result->Type        = Namespace;
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;
	result->Body        = body;

	return result;
}

CodeOperator def_operator( OperatorT op, StrC nspace
	, CodeParam      params_code, CodeType       ret_type, Code body
	, CodeSpecifiers specifiers,  CodeAttributes attributes
	, ModuleFlag     mflags )
{
	using namespace ECode;

	if ( attributes && attributes->Type != PlatformAttributes )
	{
		log_failure( "gen::def_operator: PlatformAttributes was provided but its not of attributes type: %s", attributes.debug_str() );
		return CodeInvalid;
	}

	if ( specifiers && specifiers->Type != Specifiers )
	{
		log_failure( "gen::def_operator: Specifiers was provided but its not of specifiers type: %s", specifiers.debug_str() );
		return CodeInvalid;
	}

	OpValidateResult check_result = operator__validate( op, params_code, ret_type, specifiers );

	if ( check_result == OpValidateResult::Fail )
	{
		return CodeInvalid;
	}

	char const* name = nullptr;

	StrC op_str = to_str( op );
	if ( nspace.Len > 0 )
		name = str_fmt_buf( "%.*soperator %.*s", nspace.Len, nspace.Ptr, op_str.Len, op_str.Ptr );
	else
		name = str_fmt_buf( "operator %.*s", op_str.Len, op_str.Ptr );
	CodeOperator
	result              = (CodeOperator) make_code();
	result->Name        = get_cached_string( { str_len(name), name } );
	result->ModuleFlags = mflags;
	result->Op          = op;

	if ( body )
	{
		switch ( body->Type )
		{
			case Function_Body:
			case Execution:
			case Untyped:
				break;

			default:
			{
				log_failure("gen::def_operator: body must be either of Function_Body, Execution, or Untyped type. %s", body->debug_str());
				return CodeInvalid;
			}
		}

		result->Type = check_result == OpValidateResult::Global ?
			Operator : Operator_Member;

		result->Body = body;
	}
	else
	{
		result->Type = check_result == OpValidateResult::Global ?
			Operator_Fwd : Operator_Member_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	result->ReturnType = ret_type;

	if (params_code)
		result->Params = params_code;

	return result;
}

CodeOpCast def_operator_cast( CodeType type, Code body, CodeSpecifiers const_spec )
{
	using namespace ECode;
	null_check( def_operator_cast, type );

	if ( type->Type != Typename )
	{
		log_failure( "gen::def_operator_cast: type is not a typename - %s", type.debug_str() );
		return CodeInvalid;
	}

	CodeOpCast result = (CodeOpCast) make_code();

	if (body)
	{
		result->Type = Operator_Cast;

		if ( body->Type != Function_Body && body->Type != Execution )
		{
			log_failure( "gen::def_operator_cast: body is not of function body or execution type - %s", body.debug_str() );
			return CodeInvalid;
		}

		result->Body = body;
	}
	else
	{
		result->Type = Operator_Cast_Fwd;
	}

	if ( const_spec )
	{
		result->Specs = const_spec;
	}

	result->ValueType = type;
	return result;
}

CodeParam def_param( CodeType type, StrC name, Code value )
{
	using namespace ECode;

	name_check( def_param, name );
	null_check( def_param, type );

	if ( type->Type != Typename )
	{
		log_failure( "gen::def_param: type is not a typename - %s", type.debug_str() );
		return CodeInvalid;
	}

	if ( value && value->Type != Untyped )
	{
		log_failure( "gen::def_param: value is not untyped - %s", value.debug_str() );
		return CodeInvalid;
	}

	CodeParam
	result       = (CodeParam) make_code();
	result->Type = Parameters;
	result->Name = get_cached_string( name );

	result->ValueType = type;

	if ( value )
		result->Value = value;

	result->NumEntries++;

	return result;
}

CodePragma def_pragma( StrC directive )
{
	using namespace ECode;

	if ( directive.Len <= 0 || directive.Ptr == nullptr )
	{
		log_failure( "gen::def_comment: Invalid comment provided:" );
		return CodeInvalid;
	}

	CodePragma
	result          = (CodePragma) make_code();
	result->Type    = Preprocess_Pragma;
	result->Content = get_cached_string( directive );

	return result;
}

CodePreprocessCond def_preprocess_cond( EPreprocessCond type, StrC expr )
{
	using namespace ECode;

	if ( expr.Len <= 0 || expr.Ptr == nullptr )
	{
		log_failure( "gen::def_comment: Invalid comment provided:" );
		return CodeInvalid;
	}

	CodePreprocessCond
	result          = (CodePreprocessCond) make_code();
	result->Content = get_cached_string( expr );

	switch (type)
	{
		case EPreprocessCond::If:
			result->Type = Preprocess_If;
		break;
		case EPreprocessCond::IfDef:
			result->Type = Preprocess_IfDef;
		break;
		case EPreprocessCond::IfNotDef:
			result->Type = Preprocess_IfNotDef;
		break;
		case EPreprocessCond::ElIf:
			result->Type = Preprocess_ElIf;
		break;
	}

	return result;
}

CodeSpecifiers def_specifier( SpecifierT spec )
{
	CodeSpecifiers
	result       = (CodeSpecifiers) make_code();
	result->Type = ECode::Specifiers;
	result.append( spec );

	return result;
}

CodeStruct def_struct( StrC name
	, Code           body
	, CodeType       parent, AccessSpec parent_access
	, CodeAttributes attributes
	, ModuleFlag     mflags
	, CodeType*      interfaces, s32 num_interfaces )
{
	using namespace ECode;

	if ( attributes && attributes->Type != PlatformAttributes )
	{
		log_failure( "gen::def_struct: attributes was not a `PlatformAttributes` type - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	if ( parent && parent->Type != Typename )
	{
		log_failure( "gen::def_struct: parent was not a `Struct` type - %s", parent.debug_str() );
		return CodeInvalid;
	}

	if ( body && body->Type != Struct_Body )
	{
		log_failure( "gen::def_struct: body was not a Struct_Body type - %s", body.debug_str() );
		return CodeInvalid;
	}

	CodeStruct
	result              = (CodeStruct) make_code();
	result->ModuleFlags = mflags;

	if ( name )
		result->Name = get_cached_string( name );

	if ( body )
	{
		result->Type = Struct;
		result->Body = body;
	}
	else
	{
		result->Type = Struct_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( parent )
	{
		result->ParentAccess = parent_access;
		result->ParentType   = parent;
	}

	if ( interfaces )
	{
		for (s32 idx = 0; idx < num_interfaces; idx++ )
		{
			result.add_interface( interfaces[idx] );
		}
	}

	return result;
}

CodeTemplate def_template( CodeParam params, Code declaration, ModuleFlag mflags )
{
	null_check( def_template, declaration );

	if ( params && params->Type != ECode::Parameters )
	{
		log_failure( "gen::def_template: params is not of parameters type - %s", params.debug_str() );
		return CodeInvalid;
	}

	switch (declaration->Type )
	{
		case ECode::Class:
		case ECode::Function:
		case ECode::Struct:
		case ECode::Variable:
		case ECode::Using:
		break;

		default:
			log_failure( "gen::def_template: declaration is not of class, function, struct, variable, or using type - %s", declaration.debug_str() );
	}

	CodeTemplate
	result              = (CodeTemplate) make_code();
	result->Type        = ECode::Template;
	result->ModuleFlags = mflags;
	result->Params      = params;
	result->Declaration = declaration;

	return result;
}

CodeType def_type( StrC name, Code arrayexpr, CodeSpecifiers specifiers, CodeAttributes attributes )
{
	name_check( def_type, name );

	if ( attributes && attributes->Type != ECode::PlatformAttributes )
	{
		log_failure( "gen::def_type: attributes is not of attributes type - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	if ( specifiers && specifiers->Type != ECode::Specifiers )
	{
		log_failure( "gen::def_type: specifiers is not of specifiers type - %s", specifiers.debug_str() );
		return CodeInvalid;
	}

	if ( arrayexpr && arrayexpr->Type != ECode::Untyped )
	{
		log_failure( "gen::def_type: arrayexpr is not of untyped type - %s", arrayexpr->debug_str() );
		return CodeInvalid;
	}

	CodeType
	result       = (CodeType) make_code();
	result->Name = get_cached_string( name );
	result->Type = ECode::Typename;

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	if ( arrayexpr )
		result->ArrExpr = arrayexpr;

	return result;
}

CodeTypedef def_typedef( StrC name, Code type, CodeAttributes attributes, ModuleFlag mflags )
{
	using namespace ECode;

	null_check( def_typedef, type );

	switch ( type->Type )
	{
		case Class:
		case Class_Fwd:
		case Enum:
		case Enum_Fwd:
		case Enum_Class:
		case Enum_Class_Fwd:
		case Function_Fwd:
		case Struct:
		case Struct_Fwd:
		case Union:
		case Typename:
			break;
		default:
			log_failure( "gen::def_typedef: type was not a Class, Enum, Function Forward, Struct, Typename, or Union - %s", type.debug_str() );
			return CodeInvalid;
	}

	if ( attributes && attributes->Type != ECode::PlatformAttributes )
	{
		log_failure( "gen::def_typedef: attributes was not a PlatformAttributes - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	// Registering the type.
	Code registered_type = def_type( name );

	if ( ! registered_type )
	{
		log_failure( "gen::def_typedef: failed to register type" );
		return CodeInvalid;
	}

	CodeTypedef
	result              = (CodeTypedef) make_code();
	result->Type        = ECode::Typedef;
	result->ModuleFlags = mflags;

	result->UnderlyingType = type;

	if ( name.Len <= 0  )
	{
		if (type->Type != Untyped)
		{
			log_failure( "gen::def_typedef: name was empty and type was not untyped (indicating its a function typedef) - %s", type.debug_str() );
			return CodeInvalid;
		}

		result->Name       = get_cached_string( type->Name );
		result->IsFunction = true;
	}
	else
	{
		result->Name       = get_cached_string( name );
		result->IsFunction = false;
	}

	return result;
}

CodeUnion def_union( StrC name, Code body, CodeAttributes attributes, ModuleFlag mflags )
{
	null_check( def_union, body );

	if ( body->Type != ECode::Union_Body )
	{
		log_failure( "gen::def_union: body was not a Union_Body type - %s", body.debug_str() );
		return CodeInvalid;
	}

	if ( attributes && attributes->Type != ECode::PlatformAttributes )
	{
		log_failure( "gen::def_union: attributes was not a PlatformAttributes type - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	CodeUnion
	result              = (CodeUnion) make_code();
	result->ModuleFlags = mflags;
	result->Type        = ECode::Union;

	if ( name.Ptr )
		result->Name = get_cached_string( name );

	result->Body = body;

	if ( attributes )
		result->Attributes = attributes;

	return result;
}

CodeUsing def_using( StrC name, CodeType type
	, CodeAttributes attributes
	, ModuleFlag     mflags )
{
	name_check( def_using, name );
	null_check( def_using, type );

	Code register_type = def_type( name );

	if ( ! register_type )
	{
		log_failure( "gen::def_using: failed to register type" );
		return CodeInvalid;
	}

	if ( attributes && attributes->Type != ECode::PlatformAttributes )
	{
		log_failure( "gen::def_using: attributes was not a PlatformAttributes type - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	CodeUsing
	result              = (CodeUsing) make_code();
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;
	result->Type = ECode::Using;

	result->UnderlyingType = type;

	if ( attributes )
		result->Attributes = attributes;

	return result;
}

CodeUsing def_using_namespace( StrC name )
{
	name_check( def_using_namespace, name );

	Code
	result          = make_code();
	result->Name    = get_cached_string( name );
	result->Content = result->Name;
	result->Type    = ECode::Using_Namespace;

	return (CodeUsing) result;
}

CodeVar def_variable( CodeType type, StrC name, Code value
	, CodeSpecifiers specifiers, CodeAttributes attributes
	, ModuleFlag     mflags )
{
	name_check( def_variable, name );
	null_check( def_variable, type );

	if ( attributes && attributes->Type != ECode::PlatformAttributes )
	{
		log_failure( "gen::def_variable: attributes was not a `PlatformAttributes` type - %s", attributes.debug_str() );
		return CodeInvalid;
	}

	if ( specifiers && specifiers->Type != ECode::Specifiers )
	{
		log_failure( "gen::def_variable: specifiers was not a `Specifiers` type - %s", specifiers.debug_str() );
		return CodeInvalid;
	}

	if ( type->Type != ECode::Typename )
	{
		log_failure( "gen::def_variable: type was not a Typename - %s", type.debug_str() );
		return CodeInvalid;
	}

	if ( value && value->Type != ECode::Untyped )
	{
		log_failure( "gen::def_variable: value was not a `Untyped` type - %s", value.debug_str() );
		return CodeInvalid;
	}

	CodeVar
	result              = (CodeVar) make_code();
	result->Name        = get_cached_string( name );
	result->Type        = ECode::Variable;
	result->ModuleFlags = mflags;

	result->ValueType = type;

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	if ( value )
		result->Value = value;

	return result;
}

#pragma region Helper Macros for def_**_body functions
#define def_body_start( Name_ )                                               \
using namespace ECode;                                                        \
																			  \
if ( num <= 0 )                                                               \
{                                                                             \
	log_failure("gen::" stringize(Name_) ": num cannot be zero or negative"); \
	return CodeInvalid;                                                       \
}

#define def_body_code_array_start( Name_ )                                     \
using namespace ECode;                                                         \
																			   \
if ( num <= 0 )                                                                \
{                                                                              \
	log_failure("gen::" stringize(Name_) ": num cannot be zero or negative");  \
	return CodeInvalid;                                                        \
}                                                                              \
																			   \
if ( codes == nullptr )                                                        \
{                                                                              \
	log_failure("gen::" stringize(Name_)" : Provided a null array of codes");  \
	return CodeInvalid;                                                        \
}

#pragma endregion Helper Macros for def_**_body functions

CodeBody def_class_body( s32 num, ... )
{
	def_body_start( def_class_body );

	CodeBody result = ( CodeBody )make_code();
	result->Type    = Class_Body;

	va_list va;
	va_start( va, num );
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::"
						"def_class_body"
						": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_CLASS_UNALLOWED_TYPES
				log_failure("gen::" "def_class_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_class_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_class_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Function_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_class_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_CLASS_UNALLOWED_TYPES
				log_failure("gen::" "def_class_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeBody def_enum_body( s32 num, ... )
{
	def_body_start( def_enum_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Enum_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if ( ! entry )
		{
			log_failure("gen::def_enum_body: Provided a null entry");
			return CodeInvalid;
		}

		if ( entry->Type != Untyped && entry->Type != Comment )
		{
			log_failure("gen::def_enum_body: Entry type is not allowed - %s. Must be of untyped or comment type.", entry.debug_str() );
			return CodeInvalid;
		}

		result.append( entry );
	}
	while ( num--, num > 0 );
	va_end(va);

	return (CodeBody) result;
}

CodeBody def_enum_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_enum_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Enum_Body;

	do
	{
		Code entry = *codes;

		if ( ! entry )
		{
			log_failure("gen::def_enum_body: Provided a null entry");
			return CodeInvalid;
		}

		if ( entry->Type != Untyped && entry->Type != Comment )
		{
			log_failure("gen::def_enum_body: Entry type is not allowed: %s", entry.debug_str() );
			return CodeInvalid;
		}

		result.append( entry );
	}
	while ( codes++, num--, num > 0 );

	return result;
}

CodeBody def_export_body( s32 num, ... )
{
	def_body_start( def_export_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Export_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" "def_export_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_EXPORT_UNALLOWED_TYPES
				log_failure("gen::" "def_export_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_export_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_export_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Export_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_export_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_EXPORT_UNALLOWED_TYPES
				log_failure("gen::" "def_export_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeBody def_extern_link_body( s32 num, ... )
{
	def_body_start( def_extern_linkage_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Extern_Linkage_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod = va_arg(va, Code_POD);
		Code entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" "def_extern_linkage_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_EXTERN_LINKAGE_UNALLOWED_TYPES
				log_failure("gen::" "def_extern_linkage_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_extern_link_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_extern_linkage_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Extern_Linkage_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_extern_linkage_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_EXTERN_LINKAGE_UNALLOWED_TYPES
				log_failure("gen::" "def_extern_linkage_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);

	}
	while (num--, num > 0);

	return result;
}

CodeBody def_function_body( s32 num, ... )
{
	def_body_start( def_function_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Function_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" stringize(def_function_body) ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{

			GEN_AST_BODY_FUNCTION_UNALLOWED_TYPES
				log_failure("gen::" stringize(def_function_body) ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_function_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_function_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Function_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_function_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_FUNCTION_UNALLOWED_TYPES
				log_failure("gen::" "def_function_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}
		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeBody def_global_body( s32 num, ... )
{
	def_body_start( def_global_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Global_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" "def_global_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			case Global_Body:
				result.append( entry.cast<CodeBody>() ) ;
				continue;

			GEN_AST_BODY_GLOBAL_UNALLOWED_TYPES
				log_failure("gen::" "def_global_body" ": Entry type is not allowed: %s", entry.debug_str());
				return (*Code::Invalid.ast);

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_global_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_global_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Global_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_global_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			case Global_Body:
				result.append( entry.cast<CodeBody>() ) ;
				continue;

			GEN_AST_BODY_GLOBAL_UNALLOWED_TYPES
				log_failure("gen::" "def_global_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeBody def_namespace_body( s32 num, ... )
{
	def_body_start( def_namespace_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Namespace_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" "def_namespace_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_NAMESPACE_UNALLOWED_TYPES
				log_failure("gen::" "def_namespace_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_namespace_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_namespace_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Global_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_namespace_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_NAMESPACE_UNALLOWED_TYPES
				log_failure("gen::" "def_namespace_body" ": Entry type is not allowed: %s", entry.debug_str() );
				return CodeInvalid;

			default: break;
		}

		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeParam def_params( s32 num, ... )
{
	def_body_start( def_params );

	va_list va;
	va_start(va, num);

	Code_POD  pod   = va_arg(va, Code_POD);
	CodeParam param = pcast( CodeParam, pod );

	null_check( def_params, param );

	if ( param->Type != Parameters )
	{
		log_failure( "gen::def_params: param %d is not a Parameters", num - num + 1 );
		return CodeInvalid;
	}

	CodeParam result = (CodeParam) param.duplicate();

	while ( -- num )
	{
		pod   = va_arg(va, Code_POD);
		param = pcast( CodeParam, pod );

		if ( param->Type != Parameters )
		{
			log_failure( "gen::def_params: param %d is not a Parameters", num - num + 1 );
			return CodeInvalid;
		}

		result.append( param );
	}
	va_end(va);

	return result;
}

CodeParam def_params( s32 num, CodeParam* codes )
{
	def_body_code_array_start( def_params );

#	define check_current()                                                                                      \
	if ( current.ast == nullptr )                                                                               \
	{                                                                                                           \
		log_failure("gen::def_params: Provide a null code in codes array");                                     \
		return CodeInvalid;                                                                                     \
	}                                                                                                           \
																												\
	if (current->Type != Parameters )                                                                           \
	{                                                                                                           \
		log_failure("gen::def_params: Code in coes array is not of paramter type - %s", current.debug_str() );  \
		return CodeInvalid;                                                                                     \
	}

	CodeParam current = (CodeParam) codes->duplicate();
	check_current();

	CodeParam
	result            = (CodeParam) make_code();
	result->Name      = current->Name;
	result->Type      = current->Type;
	result->ValueType = current->ValueType;

	while( codes++, current = * codes, num--, num > 0 )
	{
		check_current();
		result.append( current );
	}
#	undef check_current

	return result;
}

CodeSpecifiers def_specifiers( s32 num, ... )
{
	if ( num <= 0 )
	{
		log_failure("gen::def_specifiers: num cannot be zero or less");
		return CodeInvalid;
	}

	if ( num > AST::ArrSpecs_Cap )
	{
		log_failure("gen::def_specifiers: num of speciifers to define AST larger than AST specicifier capacity - %d", num);
		return CodeInvalid;
	}

	CodeSpecifiers
	result       = (CodeSpecifiers) make_code();
	result->Type = ECode::Specifiers;

	va_list va;
	va_start(va, num);
	do
	{
		SpecifierT type = (SpecifierT)va_arg(va, int);

		result.append( type );
	}
	while ( --num, num );
	va_end(va);

	return result;
}

CodeSpecifiers def_specifiers( s32 num, SpecifierT* specs )
{
	if ( num <= 0 )
	{
		log_failure("gen::def_specifiers: num cannot be zero or less");
		return CodeInvalid;
	}

	if ( num > AST::ArrSpecs_Cap )
	{
		log_failure("gen::def_specifiers: num of speciifers to define AST larger than AST specicifier capacity - %d", num);
		return CodeInvalid;
	}

	CodeSpecifiers
	result       = (CodeSpecifiers) make_code();
	result->Type = ECode::Specifiers;

	s32 idx = 0;
	do
	{
		result.append( specs[idx] );
		idx++;
	}
	while ( --num, num );

	return result;
}

CodeBody def_struct_body( s32 num, ... )
{
	def_body_start( def_struct_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Struct_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast(Code, pod);

		if (!entry)
		{
			log_failure("gen::" "def_struct_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_STRUCT_UNALLOWED_TYPES
				log_failure("gen::" "def_struct_body" ": Entry type is not allowed: %s", entry.debug_str());
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);
	va_end(va);

	return result;
}

CodeBody def_struct_body( s32 num, Code* codes )
{
	def_body_code_array_start( def_struct_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Struct_Body;

	do
	{
		Code entry = *codes;
		codes++;

		if (!entry)
		{
			log_failure("gen::" "def_struct_body" ": Provided an null entry");
			return CodeInvalid;
		}

		switch (entry->Type)
		{
			GEN_AST_BODY_STRUCT_UNALLOWED_TYPES
				log_failure("gen::" "def_struct_body" ": Entry type is not allowed: %s", entry.debug_str() );
				return CodeInvalid;

			default:
			break;
		}

		result.append(entry);
	}
	while (num--, num > 0);

	return result;
}

CodeBody def_union_body( s32 num, ... )
{
	def_body_start( def_union_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Union_Body;

	va_list va;
	va_start(va, num);
	do
	{
		Code_POD pod   = va_arg(va, Code_POD);
		Code     entry = pcast( Code, pod );

		if ( ! entry )
		{
			log_failure("gen::def_union_body: Provided a null entry");
			return CodeInvalid;
		}

		if ( entry->Type != Untyped && entry->Type != Comment )
		{
			log_failure("gen::def_union_body: Entry type is not allowed - %s. Must be of untyped or comment type.", entry.debug_str() );
			return CodeInvalid;
		}

		result.append( entry );
	}
	while ( num--, num > 0 );
	va_end(va);

	return result;
}

CodeBody def_union_body( s32 num, CodeUnion* codes )
{
	def_body_code_array_start( def_union_body );

	CodeBody
	result       = (CodeBody) make_code();
	result->Type = Union_Body;

	do
	{
		Code entry = *codes;

		if ( ! entry )
		{
			log_failure("gen::def_union_body: Provided a null entry");
			return CodeInvalid;
		}

		if ( entry->Type != Untyped && entry->Type != Comment )
		{
			log_failure("gen::def_union_body: Entry type is not allowed: %s", entry.debug_str() );
			return CodeInvalid;
		}

		result.append( entry );
	}
	while ( codes++, num--, num > 0 );

	return (CodeBody) result;
}

#	undef name_check
#	undef null_check
#	undef null_or_invalid_check
#	undef def_body_start
#	undef def_body_code_array_start

#pragma endregion Upfront

#pragma region Parsing

namespace parser
{
	namespace ETokType
	{
#define GEN_DEFINE_ATTRIBUTE_TOKENS Entry( Attribute_API_Export, "GEN_API_Export_Code" ) Entry( Attribute_API_Import, "GEN_API_Import_Code" )

		enum Type : u32
		{
			Invalid,
			Access_Private,
			Access_Protected,
			Access_Public,
			Access_MemberSymbol,
			Access_StaticSymbol,
			Ampersand,
			Ampersand_DBL,
			Assign_Classifer,
			Attribute_Open,
			Attribute_Close,
			BraceCurly_Open,
			BraceCurly_Close,
			BraceSquare_Open,
			BraceSquare_Close,
			Capture_Start,
			Capture_End,
			Comment,
			Comment_End,
			Comment_Start,
			Char,
			Comma,
			Decl_Class,
			Decl_GNU_Attribute,
			Decl_MSVC_Attribute,
			Decl_Enum,
			Decl_Extern_Linkage,
			Decl_Friend,
			Decl_Module,
			Decl_Namespace,
			Decl_Operator,
			Decl_Struct,
			Decl_Template,
			Decl_Typedef,
			Decl_Using,
			Decl_Union,
			Identifier,
			Module_Import,
			Module_Export,
			NewLine,
			Number,
			Operator,
			Preprocess_Hash,
			Preprocess_Define,
			Preprocess_If,
			Preprocess_IfDef,
			Preprocess_IfNotDef,
			Preprocess_ElIf,
			Preprocess_Else,
			Preprocess_EndIf,
			Preprocess_Include,
			Preprocess_Pragma,
			Preprocess_Content,
			Preprocess_Macro,
			Preprocess_Unsupported,
			Spec_Alignas,
			Spec_Const,
			Spec_Consteval,
			Spec_Constexpr,
			Spec_Constinit,
			Spec_Explicit,
			Spec_Extern,
			Spec_Final,
			Spec_ForceInline,
			Spec_Global,
			Spec_Inline,
			Spec_Internal_Linkage,
			Spec_LocalPersist,
			Spec_Mutable,
			Spec_NeverInline,
			Spec_Override,
			Spec_Static,
			Spec_ThreadLocal,
			Spec_Volatile,
			Spec_Virtual,
			Star,
			Statement_End,
			StaticAssert,
			String,
			Type_Typename,
			Type_Unsigned,
			Type_Signed,
			Type_Short,
			Type_Long,
			Type_bool,
			Type_char,
			Type_int,
			Type_double,
			Type_MS_int8,
			Type_MS_int16,
			Type_MS_int32,
			Type_MS_int64,
			Type_MS_W64,
			Varadic_Argument,
			__Attributes_Start,
			Attribute_API_Export,
			Attribute_API_Import,
			NumTokens
		};

		inline StrC to_str( Type type )
		{
			local_persist StrC lookup[] {
				{ sizeof( "__invalid__" ),         "__invalid__"         },
				{ sizeof( "private" ),             "private"             },
				{ sizeof( "protected" ),           "protected"           },
				{ sizeof( "public" ),              "public"              },
				{ sizeof( "." ),                   "."                   },
				{ sizeof( "::" ),                  "::"                  },
				{ sizeof( "&" ),                   "&"                   },
				{ sizeof( "&&" ),                  "&&"                  },
				{ sizeof( ":" ),                   ":"                   },
				{ sizeof( "[[" ),                  "[["                  },
				{ sizeof( "]]" ),                  "]]"                  },
				{ sizeof( "{" ),                   "{"                   },
				{ sizeof( "}" ),                   "}"                   },
				{ sizeof( "[" ),                   "["                   },
				{ sizeof( "]" ),                   "]"                   },
				{ sizeof( "(" ),                   "("                   },
				{ sizeof( ")" ),                   ")"                   },
				{ sizeof( "__comment__" ),         "__comment__"         },
				{ sizeof( "__comment_end__" ),     "__comment_end__"     },
				{ sizeof( "__comment_start__" ),   "__comment_start__"   },
				{ sizeof( "__character__" ),       "__character__"       },
				{ sizeof( "," ),                   ","                   },
				{ sizeof( "class" ),               "class"               },
				{ sizeof( "__attribute__" ),       "__attribute__"       },
				{ sizeof( "__declspec" ),          "__declspec"          },
				{ sizeof( "enum" ),                "enum"                },
				{ sizeof( "extern" ),              "extern"              },
				{ sizeof( "friend" ),              "friend"              },
				{ sizeof( "module" ),              "module"              },
				{ sizeof( "namespace" ),           "namespace"           },
				{ sizeof( "operator" ),            "operator"            },
				{ sizeof( "struct" ),              "struct"              },
				{ sizeof( "template" ),            "template"            },
				{ sizeof( "typedef" ),             "typedef"             },
				{ sizeof( "using" ),               "using"               },
				{ sizeof( "union" ),               "union"               },
				{ sizeof( "__identifier__" ),      "__identifier__"      },
				{ sizeof( "import" ),              "import"              },
				{ sizeof( "export" ),              "export"              },
				{ sizeof( "__new_line__" ),        "__new_line__"        },
				{ sizeof( "__number__" ),          "__number__"          },
				{ sizeof( "__operator__" ),        "__operator__"        },
				{ sizeof( "#" ),                   "#"                   },
				{ sizeof( "define" ),              "define"              },
				{ sizeof( "if" ),                  "if"                  },
				{ sizeof( "ifdef" ),               "ifdef"               },
				{ sizeof( "ifndef" ),              "ifndef"              },
				{ sizeof( "elif" ),                "elif"                },
				{ sizeof( "else" ),                "else"                },
				{ sizeof( "endif" ),               "endif"               },
				{ sizeof( "include" ),             "include"             },
				{ sizeof( "pragma" ),              "pragma"              },
				{ sizeof( "__macro_content__" ),   "__macro_content__"   },
				{ sizeof( "__macro__" ),           "__macro__"           },
				{ sizeof( "__unsupported__" ),     "__unsupported__"     },
				{ sizeof( "alignas" ),             "alignas"             },
				{ sizeof( "const" ),               "const"               },
				{ sizeof( "consteval" ),           "consteval"           },
				{ sizeof( "constexpr" ),           "constexpr"           },
				{ sizeof( "constinit" ),           "constinit"           },
				{ sizeof( "explicit" ),            "explicit"            },
				{ sizeof( "extern" ),              "extern"              },
				{ sizeof( "final" ),               "final"               },
				{ sizeof( "forceinline" ),         "forceinline"         },
				{ sizeof( "global" ),              "global"              },
				{ sizeof( "inline" ),              "inline"              },
				{ sizeof( "internal" ),            "internal"            },
				{ sizeof( "local_persist" ),       "local_persist"       },
				{ sizeof( "mutable" ),             "mutable"             },
				{ sizeof( "neverinline" ),         "neverinline"         },
				{ sizeof( "override" ),            "override"            },
				{ sizeof( "static" ),              "static"              },
				{ sizeof( "thread_local" ),        "thread_local"        },
				{ sizeof( "volatile" ),            "volatile"            },
				{ sizeof( "virtual" ),             "virtual"             },
				{ sizeof( "*" ),                   "*"                   },
				{ sizeof( ";" ),                   ";"                   },
				{ sizeof( "static_assert" ),       "static_assert"       },
				{ sizeof( "__string__" ),          "__string__"          },
				{ sizeof( "typename" ),            "typename"            },
				{ sizeof( "unsigned" ),            "unsigned"            },
				{ sizeof( "signed" ),              "signed"              },
				{ sizeof( "short" ),               "short"               },
				{ sizeof( "long" ),                "long"                },
				{ sizeof( "bool" ),                "bool"                },
				{ sizeof( "char" ),                "char"                },
				{ sizeof( "int" ),                 "int"                 },
				{ sizeof( "double" ),              "double"              },
				{ sizeof( "__int8" ),              "__int8"              },
				{ sizeof( "__int16" ),             "__int16"             },
				{ sizeof( "__int32" ),             "__int32"             },
				{ sizeof( "__int64" ),             "__int64"             },
				{ sizeof( "_W64" ),                "_W64"                },
				{ sizeof( "..." ),                 "..."                 },
				{ sizeof( "__attrib_start__" ),    "__attrib_start__"    },
				{ sizeof( "GEN_API_Export_Code" ), "GEN_API_Export_Code" },
				{ sizeof( "GEN_API_Import_Code" ), "GEN_API_Import_Code" },
			};
			return lookup[type];
		}

		inline Type to_type( StrC str )
		{
			local_persist u32 keymap[NumTokens];
			do_once_start for ( u32 index = 0; index < NumTokens; index++ )
			{
				StrC enum_str = to_str( (Type)index );
				keymap[index] = crc32( enum_str.Ptr, enum_str.Len - 1 );
			}
			do_once_end u32 hash = crc32( str.Ptr, str.Len );
			for ( u32 index = 0; index < NumTokens; index++ )
			{
				if ( keymap[index] == hash )
					return (Type)index;
			}
			return Invalid;
		}

	}    // namespace ETokType

	using TokType = ETokType::Type;

}    // namespace parser

namespace parser {

enum TokFlags : u32
{
	TF_Operator		   = bit(0),
	TF_Assign          = bit(1),
	TF_Preprocess      = bit(2),
	TF_Preprocess_Cond = bit(3),
	TF_Attribute       = bit(6),
	TF_AccessOperator  = bit( 7 ),
	TF_AccessSpecifier = bit( 8 ),
	TF_Specifier       = bit( 9 ),
	TF_EndDefinition   = bit( 10 ),    // Either ; or }
	TF_Formatting      = bit( 11 ),
	TF_Literal         = bit( 12 ),

	TF_Null = 0,
};

struct Token
{
	char const* Text;
	sptr        Length;
	TokType     Type;
	s32         Line;
	s32         Column;
	u32         Flags;

	operator bool()
	{
		return Text && Length && Type != TokType::Invalid;
	}

	operator StrC()
	{
		return { Length, Text };
	}

	bool is_access_operator()
	{
		return bitfield_is_equal( u32, Flags, TF_AccessOperator );
	}

	bool is_access_specifier()
	{
		return bitfield_is_equal( u32, Flags, TF_AccessSpecifier );
	}

	bool is_attribute()
	{
		return bitfield_is_equal( u32, Flags, TF_Attribute );
	}

	bool is_operator()
	{
		return bitfield_is_equal( u32, Flags, TF_Operator );
	}

	bool is_preprocessor()
	{
		return bitfield_is_equal( u32, Flags, TF_Preprocess );
	}

	bool is_preprocess_cond()
	{
		return bitfield_is_equal( u32, Flags, TF_Preprocess_Cond );
	}

	bool is_specifier()
	{
		return bitfield_is_equal( u32, Flags, TF_Specifier );
	}

	bool is_end_definition()
	{
		return bitfield_is_equal( u32, Flags, TF_EndDefinition );
	}

	AccessSpec to_access_specifier()
	{
		return scast(AccessSpec, Type);
	}

	String to_string()
	{
		String result = String::make_reserve( GlobalAllocator, kilobytes(4) );

		StrC type_str = ETokType::to_str( Type );

		result.append_fmt( "Line: %d Column: %d, Type: %.*s Content: %.*s"
			, Line, Column
			, type_str.Len, type_str.Ptr
			, Length, Text
		);

		return result;
	}
};

constexpr Token NullToken { nullptr, 0, TokType::Invalid, false, 0, TF_Null };

struct TokArray
{
	Array<Token> Arr;
	s32          Idx;

	bool __eat( TokType type );

	Token& current( bool skip_formatting = true )
	{
		if ( skip_formatting )
		{
			while ( Arr[Idx].Type == TokType::NewLine || Arr[Idx].Type == TokType::Comment  )
				Idx++;
		}

		return Arr[Idx];
	}

	Token& previous( bool skip_formatting = false )
	{
		s32 idx = this->Idx;

		if ( skip_formatting )
		{
			while ( Arr[idx].Type == TokType::NewLine )
				idx--;

			return Arr[idx];
		}

		return Arr[idx - 1];
	}

	Token& next( bool skip_formatting = false )
	{
		s32 idx = this->Idx;

		if ( skip_formatting )
		{
			while ( Arr[idx].Type == TokType::NewLine )
				idx++;

			return Arr[idx + 1];
		}

		return Arr[idx + 1];
	}

	Token& operator []( s32 idx )
	{
		return Arr[idx];
	}
};

global Arena_256KB     defines_map_arena;
global HashTable<StrC> defines;
global Array<Token>    Tokens;

#define current ( * scanner )

#define move_forward()          \
	{                           \
		if ( current == '\n' )  \
		{                       \
			line++;             \
			column = 1;         \
		}                       \
		else                    \
		{                       \
			column++;           \
		}                       \
		left--;                 \
		scanner++;              \
	}

#define SkipWhitespace()                        \
	while ( left && char_is_space( current ) )  \
	{                                           \
		move_forward();                         \
	}

#define end_line()                          \
	do                                      \
	{                                       \
		while ( left && current == ' ' )    \
		{                                   \
			move_forward();                 \
		}                                   \
		if ( left && current == '\r' )      \
		{                                   \
			move_forward();                 \
			move_forward();                 \
		}                                   \
		else if ( left && current == '\n' ) \
		{                                   \
			move_forward();                 \
		}                                   \
	}                                       \
	while (0)

enum
{
	Lex_Continue,
	Lex_ReturnNull,
};

forceinline
s32 lex_preprocessor_directive(
	  StrC&            content
	, s32&             left
	, char const*&     scanner
	, s32&             line
	, s32&             column
	, HashTable<StrC>& defines
	, Token&           token )
{
	char const* hash = scanner;
	Tokens.append( { hash, 1, TokType::Preprocess_Hash, line, column, TF_Preprocess } );

	move_forward();
	SkipWhitespace();

	token.Text = scanner;
	while (left && ! char_is_space(current) )
	{
		move_forward();
		token.Length++;
	}

	token.Type = ETokType::to_type( token );

	bool   is_preprocessor = token.Type >= TokType::Preprocess_Define && token.Type <= TokType::Preprocess_Pragma;
	if ( ! is_preprocessor )
	{
		token.Type  = TokType::Preprocess_Unsupported;

		// Its an unsupported directive, skip it
		s32 within_string = false;
		s32 within_char   = false;
		while ( left )
		{
			if ( current == '"' && ! within_char )
				within_string ^= true;

			if ( current == '\'' && ! within_string )
				within_char ^= true;

			if ( current == '\\' && ! within_string && ! within_char )
			{
				move_forward();
				token.Length++;

				if ( current == '\r' )
				{
					move_forward();
					token.Length++;
				}

				if ( current == '\n' )
				{
					move_forward();
					token.Length++;
					continue;
				}
				else
				{
					log_failure( "gen::Parser::lex: Invalid escape sequence '\\%c' (%d, %d)"
								" in preprocessor directive (%d, %d)\n%.100s"
						, current, line, column
						, token.Line, token.Column, token.Text );
					break;
				}
			}

			if ( current == '\r' )
			{
				move_forward();
				token.Length++;
			}

			if ( current == '\n' )
			{
				move_forward();
				token.Length++;
				break;
			}

			move_forward();
			token.Length++;
		}

		token.Length = token.Length + token.Text - hash;
		token.Text   = hash;
		Tokens.append( token );
		return Lex_Continue; // Skip found token, its all handled here.
	}

	if ( token.Type == TokType::Preprocess_Else || token.Type == TokType::Preprocess_EndIf )
	{
		token.Flags |= TF_Preprocess_Cond;
		Tokens.append( token );
		end_line();
		return Lex_Continue;
	}
	else if ( token.Type >= TokType::Preprocess_If && token.Type <= TokType::Preprocess_ElIf  )
	{
		token.Flags |= TF_Preprocess_Cond;
	}

	Tokens.append( token );

	SkipWhitespace();

	if ( token.Type == TokType::Preprocess_Define )
	{
		Token name = { scanner, 0, TokType::Identifier, line, column, TF_Preprocess };

		name.Text   = scanner;
		name.Length = 1;
		move_forward();

		while ( left && ( char_is_alphanumeric(current) || current == '_' ) )
		{
			move_forward();
			name.Length++;
		}

		if ( left && current == '(' )
		{
			move_forward();
			name.Length++;
		}

		Tokens.append( name );

		u64 key = crc32( name.Text, name.Length );
		defines.set( key, name );
	}

	Token preprocess_content = { scanner, 0, TokType::Preprocess_Content, line, column, TF_Preprocess };

	if ( token.Type == TokType::Preprocess_Include )
	{
		preprocess_content.Type = TokType::String;

		if ( current != '"' && current != '<' )
		{
			String directive_str = String::fmt_buf( GlobalAllocator, "%.*s", min( 80, left + preprocess_content.Length ), token.Text );

			log_failure( "gen::Parser::lex: Expected '\"' or '<' after #include, not '%c' (%d, %d)\n%s"
				, current
				, preprocess_content.Line
				, preprocess_content.Column
				, directive_str.Data
			);
			return Lex_ReturnNull;
		}
		move_forward();
		preprocess_content.Length++;

		while ( left && current != '"' && current != '>' )
		{
			move_forward();
			preprocess_content.Length++;
		}

		move_forward();
		preprocess_content.Length++;

		if ( current == '\r' && scanner[1] == '\n' )
		{
			move_forward();
			move_forward();
		}
		else if ( current == '\n' )
		{
			move_forward();
		}

		Tokens.append( preprocess_content );
		return Lex_Continue; // Skip found token, its all handled here.
	}

	s32 within_string = false;
	s32 within_char   = false;

	// SkipWhitespace();
	while ( left )
	{
		if ( current == '"' && ! within_char )
			within_string ^= true;

		if ( current == '\'' && ! within_string )
			within_char ^= true;

		if ( current == '\\' && ! within_string && ! within_char )
		{
			move_forward();
			preprocess_content.Length++;

			if ( current == '\r' )
			{
				move_forward();
				preprocess_content.Length++;
			}

			if ( current == '\n' )
			{
				move_forward();
				preprocess_content.Length++;
				continue;
			}
			else
			{
				String directive_str = String::make_length( GlobalAllocator, token.Text, token.Length );
				String content_str   = String::fmt_buf( GlobalAllocator, "%.*s", min( 400, left + preprocess_content.Length ), preprocess_content.Text );

				log_failure( "gen::Parser::lex: Invalid escape sequence '\\%c' (%d, %d)"
							" in preprocessor directive '%s' (%d, %d)\n%s"
					, current, line, column
					, directive_str, preprocess_content.Line, preprocess_content.Column
					, content_str );
				break;
			}
		}

		if ( current == '\r' )
		{
			move_forward();
		}

		if ( current == '\n' )
		{
			move_forward();
			break;
		}

		move_forward();
		preprocess_content.Length++;
	}

	Tokens.append( preprocess_content );
	return Lex_Continue; // Skip found token, its all handled here.
}

forceinline
void lex_found_token( StrC& content
	, s32&             left
	, char const*&     scanner
	, s32&             line
	, s32&             column
	, HashTable<StrC>& defines
	, Token&           token )
{
	if ( token.Type != TokType::Invalid )
	{
		Tokens.append( token );
		return;
	}

	TokType type = ETokType::to_type( token );

	if (type <= TokType::Access_Public && type >= TokType::Access_Private )
	{
		token.Flags |= TF_AccessSpecifier;
	}

	if ( type > TokType::__Attributes_Start )
	{
		token.Flags |= TF_Attribute;
	}

	if ( type == ETokType::Decl_Extern_Linkage )
	{
		SkipWhitespace();

		if ( current != '"' )
		{
			type         = ETokType::Spec_Extern;
			token.Flags |= TF_Specifier;
		}

		token.Type = type;
		Tokens.append( token );
		return;
	}

	if ( ( type <= TokType::Star && type >= TokType::Spec_Alignas)
			|| type == TokType::Ampersand
			|| type == TokType::Ampersand_DBL )
	{
		token.Type   = type;
		token.Flags |= TF_Specifier;
		Tokens.append( token );
		return;
	}


	if ( type != TokType::Invalid )
	{
		token.Type = type;
		Tokens.append( token );
		return;
	}

	u64 key = 0;
	if ( current == '(')
		key = crc32( token.Text, token.Length + 1 );
	else
		key = crc32( token.Text, token.Length );

	StrC* define = defines.get( key );
	if ( define )
	{
		token.Type = TokType::Preprocess_Macro;

		// Want to ignore any arguments the define may have as they can be execution expressions.
		if ( left && current == '(' )
		{
			move_forward();
			token.Length++;

			s32 level = 0;
			while ( left && (current != ')' || level > 0) )
			{
				if ( current == '(' )
					level++;

				else if ( current == ')' && level > 0 )
					level--;

				move_forward();
				token.Length++;
			}

			move_forward();
			token.Length++;
		}

		if ( current == '\r' && scanner[1] == '\n' )
		{
			move_forward();
		}
		else if ( current == '\n' )
		{
			move_forward();
		}
	}
	else
	{
		token.Type = TokType::Identifier;
	}

	Tokens.append( token );
}


neverinline
// TokArray lex( Array<Token> tokens, StrC content )
TokArray lex( StrC content )
{
	s32         left    = content.Len;
	char const* scanner = content.Ptr;

	char const* word        = scanner;
	s32         word_length = 0;

	s32 line   = 1;
	s32 column = 1;

	SkipWhitespace();
	if ( left <= 0 )
	{
		log_failure( "gen::lex: no tokens found (only whitespace provided)" );
		return { { nullptr }, 0 };
	}

	for ( StringCached entry : PreprocessorDefines )
	{
		s32         length  = 0;
		char const* scanner = entry.Data;
		while ( entry.length() > length && (char_is_alphanumeric( *scanner ) || *scanner == '_') )
		{
			scanner++;
			length ++;
		}
		if ( scanner[0] == '(' )
		{
			length++;
		}

		u64 key = crc32( entry.Data, length );
		defines.set( key, entry );
	}

	Tokens.clear();

	while (left )
	{
		#if 0
		if (Tokens.num())
		{
			log_fmt("\nLastTok: %S", Tokens.back().to_string());
		}
		#endif

		Token token = { scanner, 0, TokType::Invalid, line, column, TF_Null };

		bool is_define = false;

		if ( column == 1 )
		{
			if ( current == '\r')
			{
				move_forward();
				token.Length = 1;
			}

			if ( current == '\n' )
			{
				move_forward();

				token.Type = TokType::NewLine;
				token.Length++;

				Tokens.append( token );
				continue;
			}
		}

		token.Length = 0;

		SkipWhitespace();
		if ( left <= 0 )
			break;

		switch ( current )
		{
			case '#':
			{
				s32 result = lex_preprocessor_directive( content, left, scanner, line, column, defines, token );
				switch ( result )
				{
					case Lex_Continue:
						continue;

					case Lex_ReturnNull:
						return { { nullptr }, 0 };
				}
			}
			case '.':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Access_MemberSymbol;
				token.Flags  = TF_AccessOperator;

				if (left) {
					move_forward();
				}

				if ( current == '.' )
				{
					move_forward();
					if( current == '.' )
					{
						token.Length = 3;
						token.Type   = TokType::Varadic_Argument;
						token.Flags  = TF_Null;
						move_forward();
					}
					else
					{
						String context_str = String::fmt_buf( GlobalAllocator, "%s", scanner, min( 100, left ) );

						log_failure( "gen::lex: invalid varadic argument, expected '...' got '..%c' (%d, %d)\n%s", current, line, column, context_str );
					}
				}

				goto FoundToken;
			}
			case '&' :
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Ampersand;
				token.Flags |= TF_Operator;
				token.Flags |= TF_Specifier;

				if (left)
					move_forward();

				if ( current == '&' )	// &&
				{
					token.Length  = 2;
					token.Type    = TokType::Ampersand_DBL;

					if (left)
						move_forward();
				}

				goto FoundToken;
			}
			case ':':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Assign_Classifer;
				// Can be either a classifier (ParentType, Bitfield width), or ternary else
				// token.Type   = TokType::Colon;

				if (left)
					move_forward();

				if ( current == ':' )
				{
					move_forward();
					token.Type  = TokType::Access_StaticSymbol;
					token.Length++;
				}
				goto FoundToken;
			}
			case '{':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::BraceCurly_Open;

				if (left)
					move_forward();
				goto FoundToken;
			}
			case '}':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::BraceCurly_Close;
				token.Flags  = TF_EndDefinition;

				if (left)
					move_forward();

				end_line();
				goto FoundToken;
			}
			case '[':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::BraceSquare_Open;
				if ( left )
				{
					move_forward();

					if ( current == ']' )
					{
						token.Length = 2;
						token.Type   = TokType::Operator;
						move_forward();
					}
				}
				goto FoundToken;
			}
			case ']':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::BraceSquare_Close;

				if (left)
					move_forward();
				goto FoundToken;
			}
			case '(':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Capture_Start;

				if (left)
					move_forward();
				goto FoundToken;
			}
			case ')':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Capture_End;

				if (left)
					move_forward();
				goto FoundToken;
			}
			case '\'':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Char;
				token.Flags  = TF_Literal;

				move_forward();

				if ( left && current == '\\' )
				{
					move_forward();
					token.Length++;

					if ( current == '\'' )
					{
						move_forward();
						token.Length++;
					}
				}

				while ( left && current != '\'' )
				{
					move_forward();
					token.Length++;
				}

				if ( left )
				{
					move_forward();
					token.Length++;
				}
				goto FoundToken;
			}
			case ',':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Comma;
				token.Flags  = TF_Operator;

				if (left)
					move_forward();
				goto FoundToken;
			}
			case '*':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Star;
				token.Flags |= TF_Specifier;
				token.Flags |= TF_Operator;

				if (left)
					move_forward();

				if ( current == '=' )
				{
					token.Length++;
					token.Flags |= TF_Assign;
					// token.Type = TokType::Assign_Multiply;

					if ( left )
						move_forward();
				}

				goto FoundToken;
			}
			case ';':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Statement_End;
				token.Flags  = TF_EndDefinition;

				if (left)
					move_forward();

				end_line();
				goto FoundToken;
			}
			case '"':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::String;
				token.Flags |= TF_Literal;

				move_forward();
				while ( left )
				{
					if ( current == '"' )
					{
						move_forward();
						break;
					}

					if ( current == '\\' )
					{
						move_forward();
						token.Length++;

						if ( left )
						{
							move_forward();
							token.Length++;
						}
						continue;
					}

					move_forward();
					token.Length++;
				}
				goto FoundToken;
			}
			case '?':
			{
				token.Text     = scanner;
				token.Length   = 1;
				token.Type     = TokType::Operator;
				// token.Type     = TokType::Ternary;
				token.Flags    = TF_Operator;

				if (left)
					move_forward();

				goto FoundToken;
			}
			case '=':
			{
				token.Text     = scanner;
				token.Length   = 1;
				token.Type     = TokType::Operator;
				// token.Type     = TokType::Assign;
				token.Flags    = TF_Operator;
				token.Flags   |= TF_Assign;

				if (left)
					move_forward();

				if ( current == '=' )
				{
					token.Length++;
					token.Flags = TF_Operator;

					if (left)
						move_forward();
				}

				goto FoundToken;
			}
			case '+':
			{
				// token.Type = TokType::Add

			}
			case '%':
			{
				// token.Type = TokType::Modulo;

			}
			case '^':
			{
				// token.Type = TokType::B_XOr;
			}
			case '~':
			{
				// token.Type = TokType::Unary_Not;

			}
			case '!':
			{
				// token.Type = TokType::L_Not;
			}
			case '<':
			{
				// token.Type = TokType::Lesser;

			}
			case '>':
			{
				// token.Type = TokType::Greater;

			}
			case '|':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Operator;
				token.Flags  = TF_Operator;
				// token.Type   = TokType::L_Or;

				if (left)
					move_forward();

				if ( current == '=' )
				{
					token.Length++;
					token.Flags |= TF_Assign;
					// token.Flags |= TokFlags::Assignment;
					// token.Type = TokType::Assign_L_Or;

					if (left)
						move_forward();
				}
				else while ( left && current == *(scanner - 1) && token.Length < 3 )
				{
					token.Length++;

					if (left)
						move_forward();
				}
				goto FoundToken;
			}

			// Dash is unfortunatlly a bit more complicated...
			case '-':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Operator;
				// token.Type = TokType::Subtract;
				token.Flags  = TF_Operator;
				if ( left )
				{
					move_forward();

					if ( current == '>'  )
					{
						token.Length++;
//						token.Type = TokType::Access_PointerToMemberSymbol;
						token.Flags |= TF_AccessOperator;
						move_forward();

						if ( current == '*' )
						{
//							token.Type = TokType::Access_PointerToMemberOfPointerSymbol;
							token.Length++;
							move_forward();
						}
					}
					else if ( current == '=' )
					{
						token.Length++;
						// token.Type = TokType::Assign_Subtract;
						token.Flags |= TF_Assign;

						if (left)
							move_forward();
					}
					else while ( left && current == *(scanner - 1) && token.Length < 3 )
					{
						token.Length++;

						if (left)
							move_forward();
					}
				}
				goto FoundToken;
			}
			case '/':
			{
				token.Text   = scanner;
				token.Length = 1;
				token.Type   = TokType::Operator;
				// token.Type   = TokType::Divide;
				token.Flags  = TF_Operator;
				move_forward();

				if ( left )
				{
					if ( current == '=' )
					{
						// token.Type = TokeType::Assign_Divide;
						move_forward();
						token.Length++;
						token.Flags = TF_Assign;
					}
					else if ( current == '/' )
					{
						token.Type   = TokType::Comment;
						token.Length = 2;
						token.Flags  = TF_Null;
						move_forward();

						while ( left && current != '\n' && current != '\r' )
						{
							move_forward();
							token.Length++;
						}

						if ( current == '\r' )
						{
							move_forward();
							token.Length++;
						}
						if ( current == '\n' )
						{
							move_forward();
							token.Length++;
						}
						Tokens.append( token );
						continue;
					}
					else if ( current == '*' )
					{
						token.Type   = TokType::Comment;
						token.Length = 2;
						token.Flags  = TF_Null;
						move_forward();

						bool star   = current    == '*';
						bool slash  = scanner[1] == '/';
						bool at_end = star && slash;
						while ( left && ! at_end  )
						{
							move_forward();
							token.Length++;

							star   = current    == '*';
							slash  = scanner[1] == '/';
							at_end = star && slash;
						}
						token.Length += 2;
						move_forward();
						move_forward();

						if ( current == '\r' )
						{
							move_forward();
							token.Length++;
						}
						if ( current == '\n' )
						{
							move_forward();
							token.Length++;
						}
						Tokens.append( token );
						// end_line();
						continue;
					}
				}
				goto FoundToken;
			}
		}

		if ( char_is_alpha( current ) || current == '_' )
		{
			token.Text   = scanner;
			token.Length = 1;
			move_forward();

			while ( left && ( char_is_alphanumeric(current) || current == '_' ) )
			{
				move_forward();
				token.Length++;
			}

			goto FoundToken;
		}
		else if ( char_is_digit(current) )
		{
			// This is a very brute force lex, no checks are done for validity of literal.

			token.Text   = scanner;
			token.Length = 1;
			token.Type   = TokType::Number;
			token.Flags  = TF_Literal;
			move_forward();

			if (left
			&& (	current == 'x' || current == 'X'
				||	current == 'b' || current == 'B'
				||  current == 'o' || current == 'O' )
			)
			{
				move_forward();
				token.Length++;

				while ( left && char_is_hex_digit(current) )
				{
					move_forward();
					token.Length++;
				}

				goto FoundToken;
			}

			while ( left && char_is_digit(current) )
			{
				move_forward();
				token.Length++;
			}

			if ( left && current == '.' )
			{
				move_forward();
				token.Length++;

				while ( left && char_is_digit(current) )
				{
					move_forward();
					token.Length++;
				}

				// Handle number literal suffixes in a botched way
				if (left && (
					current == 'l' || current == 'L' ||  // long/long long
					current == 'u' || current == 'U' ||  // unsigned
					current == 'f' || current == 'F' ||  // float
					current == 'i' || current == 'I' ||  // imaginary
					current == 'z' || current == 'Z'))   // complex
				{
					char prev = current;
					move_forward();
					token.Length++;

					// Handle 'll'/'LL' as a special case when we just processed an 'l'/'L'
					if (left && (prev == 'l' || prev == 'L') && (current == 'l' || current == 'L'))
					{
						move_forward();
						token.Length++;
					}
				}
			}

			goto FoundToken;
		}
		else
		{
			s32 start = max( 0, Tokens.num() - 100 );
			log_fmt("\n%d\n", start);
			for ( s32 idx = start; idx < Tokens.num(); idx++ )
			{
				log_fmt( "Token %d Type: %s : %.*s\n"
					, idx
					, ETokType::to_str( Tokens[ idx ].Type ).Ptr
					, Tokens[ idx ].Length, Tokens[ idx ].Text
				);
			}

			String context_str = String::fmt_buf( GlobalAllocator, "%.*s", min( 100, left ), scanner );
			log_failure( "Failed to lex token '%c' (%d, %d)\n%s", current, line, column, context_str );

			// Skip to next whitespace since we can't know if anything else is valid until then.
			while ( left && ! char_is_space( current ) )
			{
				move_forward();
			}
		}

	FoundToken:
		lex_found_token( content, left, scanner, line, column, defines, token );
	}

	if ( Tokens.num() == 0 )
	{
		log_failure( "Failed to lex any tokens" );
		return { { nullptr }, 0 };
	}

	defines.clear();
	// defines_map_arena.free();
	return { Tokens, 0 };
}
#undef current
#undef move_forward
#undef SkipWhitespace

// namespace parser
}

namespace parser {

// TODO(Ed) : Rename ETokType::Capture_Start, ETokType::Capture_End to Open_Parenthesis adn Close_Parenthesis

constexpr bool dont_skip_formatting = false;

struct StackNode
{
	StackNode* Prev;

	Token Start;
	Token Name;        // The name of the AST node (if parsed)
	StrC  ProcName;    // The name of the procedure
};

struct ParseContext
{
	TokArray   Tokens;
	StackNode* Scope;

	void push( StackNode* node )
	{
		node->Prev = Scope;
		Scope      = node;

	#if 0 && Build_Debug
		log_fmt("\tEntering Context: %.*s\n", Scope->ProcName.Len, Scope->ProcName.Ptr );
	#endif
	}

	void pop()
	{
	#if 0 && Build_Debug
		log_fmt("\tPopping  Context: %.*s\n", Scope->ProcName.Len, Scope->ProcName.Ptr );
	#endif
		Scope = Scope->Prev;
	}

	String to_string()
	{
		String result = String::make_reserve( GlobalAllocator, kilobytes(4) );

		Token scope_start = Scope->Start;
		Token last_valid  = Tokens.Idx >= Tokens.Arr.num() ? Tokens.Arr[Tokens.Arr.num() -1] : Tokens.current();

		sptr        length  = scope_start.Length;
		char const* current = scope_start.Text + length;
		while ( current <= Tokens.Arr.back().Text && *current != '\n' && length < 74 )
		{
			current++;
			length++;
		}

		String line = String::make( GlobalAllocator, { length, scope_start.Text } );
		result.append_fmt("\tScope    : %s\n", line );
		line.free();

		sptr   dist            = (sptr)last_valid.Text - (sptr)scope_start.Text + 2;
		sptr   length_from_err = dist;
		String line_from_err   = String::make( GlobalAllocator, { length_from_err, last_valid.Text } );

		if ( length_from_err < 100 )
			result.append_fmt("\t(%d, %d):%*c\n", last_valid.Line, last_valid.Column, length_from_err, '^' );
		else
			result.append_fmt("\t(%d, %d)\n", last_valid.Line, last_valid.Column );

		StackNode* curr_scope = Scope;
		s32 level = 0;
		do
		{
			if ( curr_scope->Name )
			{
				result.append_fmt("\t%d: %s, AST Name: %.*s\n", level, curr_scope->ProcName.Ptr, curr_scope->Name.Length, curr_scope->Name.Text );
			}
			else
			{
				result.append_fmt("\t%d: %s\n", level, curr_scope->ProcName.Ptr );
			}

			curr_scope = curr_scope->Prev;
			level++;
		}
		while ( curr_scope );
		return result;
	}
};

global ParseContext Context;

bool TokArray::__eat( TokType type )
{
	if ( Arr.num() - Idx <= 0 )
	{
		log_failure( "No tokens left.\n%s", Context.to_string() );
		return false;
	}

	if ( ( Arr[ Idx ].Type == TokType::NewLine && type != TokType::NewLine )
	||   ( Arr[ Idx ].Type == TokType::Comment && type != TokType::Comment ) )
	{
		Idx++;
	}

	if ( Arr[Idx].Type != type )
	{
		log_failure( "Parse Error, TokArray::eat, Expected: ' %s ' not ' %.*s ' (%d, %d)`\n%s"
			, ETokType::to_str(type).Ptr
			, Arr[Idx].Length, Arr[Idx].Text
			, current().Line
			, current().Column
			, Context.to_string()
		);

		return false;
	}

#if 0 && Build_Debug
	log_fmt("Ate: %S\n", Arr[Idx].to_string() );
#endif

	Idx++;
	return true;
}

internal
void init()
{
	Tokens = Array<Token>::init_reserve( LexArena
		, ( LexAllocator_Size - sizeof( Array<Token>::Header ) ) / sizeof(Token)
	);

	defines_map_arena = Arena_256KB::init();
	defines           = HashTable<StrC>::init_reserve( defines_map_arena, 256 );
}

internal
void deinit()
{
	parser::Tokens = { nullptr };
}

#pragma region Helper Macros

#	define check_parse_args( def )                                             \
if ( def.Len <= 0 )                                                            \
{                                                                              \
	log_failure( "gen::" stringize(__func__) ": length must greater than 0" ); \
	parser::Context.pop();                                                     \
	return CodeInvalid;                                                        \
}                                                                              \
if ( def.Ptr == nullptr )                                                      \
{                                                                              \
	log_failure( "gen::" stringize(__func__) ": def was null" );               \
	parser::Context.pop();                                                     \
	return CodeInvalid;                                                        \
}

#	define currtok_noskip Context.Tokens.current( dont_skip_formatting )
#	define currtok        Context.Tokens.current()
#	define prevtok        Context.Tokens.previous()
#	define nexttok		  Context.Tokens.next()
#	define eat( Type_ )   Context.Tokens.__eat( Type_ )
#	define left           ( Context.Tokens.Arr.num() - Context.Tokens.Idx )

#ifdef check
#define CHECK_WAS_DEFINED
#pragma push_macro("check")
#undef check
#endif

#	define check_noskip( Type_ ) ( left && currtok_noskip.Type == Type_ )
#	define check( Type_ )        ( left && currtok.Type == Type_ )

#	define push_scope()                                               \
	StackNode scope { nullptr, currtok_noskip, NullToken, txt( __func__ ) }; \
	Context.push( & scope )

#pragma endregion Helper Macros

// Procedure Forwards ( Entire parser internal parser interface )

internal Code               parse_array_decl                   ();
internal CodeAttributes     parse_attributes                   ();
internal CodeComment        parse_comment                      ();
internal Code               parse_complicated_definition       ( TokType which );
internal CodeBody           parse_class_struct_body            ( TokType which, Token name = NullToken );
internal Code               parse_class_struct                 ( TokType which, bool inplace_def );
internal CodeDefine         parse_define                       ();
internal Code               parse_expression                   ();
internal Code               parse_forward_or_definition        ( TokType which, bool is_inplace );
internal CodeFn             parse_function_after_name          ( ModuleFlag mflags, CodeAttributes attributes, CodeSpecifiers specifiers, CodeType ret_type, Token name );
internal Code               parse_function_body                ();
internal Code               parse_global_nspace                ();
internal Code               parse_global_nspace_constructor_destructor( CodeSpecifiers specifiers );
internal Token              parse_identifier                   ( bool* possible_member_function = nullptr );
internal CodeInclude        parse_include                      ();
internal CodeOperator       parse_operator_after_ret_type      ( ModuleFlag mflags, CodeAttributes attributes, CodeSpecifiers specifiers, CodeType ret_type );
internal Code               parse_operator_function_or_variable( bool expects_function, CodeAttributes attributes, CodeSpecifiers specifiers );
internal CodePragma         parse_pragma                       ();
internal CodeParam          parse_params                       ( bool use_template_capture = false );
internal CodePreprocessCond parse_preprocess_cond              ();
internal Code               parse_simple_preprocess            ( TokType which );
internal Code               parse_static_assert                ();
internal void               parse_template_args                ( Token& token );
internal CodeVar            parse_variable_after_name          ( ModuleFlag mflags, CodeAttributes attributes, CodeSpecifiers specifiers, CodeType type, StrC name );
internal CodeVar            parse_variable_declaration_list    ();

internal CodeClass       parse_class           ( bool inplace_def = false );
internal CodeConstructor parse_constructor     ( CodeSpecifiers specifiers );
internal CodeDestructor  parse_destructor      ( CodeSpecifiers specifiers = NoCode );
internal CodeEnum        parse_enum            ( bool inplace_def = false );
internal CodeBody        parse_export_body     ();
internal CodeBody        parse_extern_link_body();
internal CodeExtern      parse_extern_link     ();
internal CodeFriend      parse_friend          ();
internal CodeFn          parse_function        ();
internal CodeNS          parse_namespace       ();
internal CodeOpCast      parse_operator_cast   ( CodeSpecifiers specifiers = NoCode );
internal CodeStruct      parse_struct          ( bool inplace_def = false );
internal CodeVar         parse_variable        ();
internal CodeTemplate    parse_template        ();
internal CodeType        parse_type            ( bool from_template = false, bool* is_function = nullptr );
internal CodeTypedef     parse_typedef         ();
internal CodeUnion       parse_union           ( bool inplace_def = false );
internal CodeUsing       parse_using           ();

constexpr bool inplace_def = true;

// Internal parsing functions

constexpr bool strip_formatting_dont_preserve_newlines = false;
/*
	This function was an attempt at stripping formatting from any c++ code.
	It has edge case failures that prevent it from being used in function bodies.
*/
internal
String strip_formatting( StrC raw_text, bool preserve_newlines = true )
{
	String content = String::make_reserve( GlobalAllocator, raw_text.Len );

	if ( raw_text.Len == 0 )
		return content;

#define cut_length ( scanner - raw_text.Ptr - last_cut )
#define cut_ptr    ( raw_text.Ptr   + last_cut )
#define pos        ( sptr( scanner ) - sptr( raw_text.Ptr ) )
#define move_fwd() do { scanner++; tokleft--; } while(0)

	s32         tokleft  = raw_text.Len;
	sptr        last_cut = 0;
	char const* scanner  = raw_text.Ptr;

	if ( scanner[0] == ' ' )
	{
		move_fwd();
		last_cut = 1;
	}

	bool within_string     = false;
	bool within_char       = false;
	bool must_keep_newline = false;
	while ( tokleft )
	{
		// Skip over the content of string literals
		if ( scanner[0] == '"' )
		{
			move_fwd();

			while ( tokleft && ( scanner[0] != '"' || *( scanner - 1 ) == '\\' ) )
			{
				if ( scanner[0] == '\\' && tokleft > 1 )
				{
					scanner += 2;
					tokleft -= 2;
				}
				else
				{
					move_fwd();
				}
			}

			// Skip the closing "
			if ( tokleft )
				move_fwd();

			content.append( cut_ptr, cut_length );
			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Skip over the content of character literals
		if ( scanner[0] == '\'' )
		{
			move_fwd();

			while ( tokleft
			&& ( scanner[0] != '\''
				|| ( *(scanner -1 ) == '\\' )
			) )
			{
				move_fwd();
			}

			// Skip the closing '
			if ( tokleft )
				move_fwd();

			content.append( cut_ptr, cut_length );
			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Block comments
		if ( tokleft > 1 && scanner[0] == '/' && scanner[1] == '*' )
		{
			while ( tokleft > 1 && !(scanner[0] == '*' && scanner[1] == '/') )
				move_fwd();

			scanner += 2;
			tokleft -= 2;

			content.append( cut_ptr, cut_length );
			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Line comments
		if ( tokleft > 1 && scanner[0] == '/' && scanner[1] == '/' )
		{
			must_keep_newline = true;

			scanner += 2;
			tokleft -= 2;

			while ( tokleft && scanner[ 0 ] != '\n' )
				move_fwd();

			if (tokleft)
				move_fwd();

			content.append( cut_ptr, cut_length );
			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Tabs
		if (scanner[0] == '\t')
		{
			if (pos > last_cut)
				content.append(cut_ptr, cut_length);

			if ( content.back() != ' ' )
				content.append(' ');

			move_fwd();
			last_cut = sptr(scanner) - sptr(raw_text.Ptr);
			continue;
		}

		if ( tokleft > 1 && scanner[0] == '\r' && scanner[1] == '\n' )
		{
			if ( must_keep_newline || preserve_newlines )
			{
				must_keep_newline = false;

				scanner += 2;
				tokleft -= 2;

				content.append( cut_ptr, cut_length );
				last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
				continue;
			}

			if ( pos > last_cut )
				content.append( cut_ptr, cut_length );

			// Replace with a space
			if ( content.back() != ' ' )
				content.append( ' ' );

			scanner += 2;
			tokleft -= 2;

			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		if ( scanner[0] == '\n' )
		{
			if ( must_keep_newline || preserve_newlines )
			{
				must_keep_newline = false;

				move_fwd();

				content.append( cut_ptr, cut_length );
				last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
				continue;
			}

			if ( pos > last_cut )
				content.append( cut_ptr, cut_length );

			// Replace with a space
			if ( content.back() != ' ' )
				content.append( ' ' );

			move_fwd();

			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Escaped newlines
		if ( scanner[0] == '\\' )
		{
			content.append( cut_ptr, cut_length );

			s32 amount_to_skip = 1;
			if ( tokleft > 1 && scanner[1] == '\n' )
			{
				amount_to_skip = 2;
			}
			else if ( tokleft > 2 && scanner[1] == '\r' && scanner[2] == '\n' )
			{
				amount_to_skip = 3;
			}

			if ( amount_to_skip > 1 && pos == last_cut )
			{
				scanner += amount_to_skip;
				tokleft -= amount_to_skip;
			}
			else
				move_fwd();

			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );
			continue;
		}

		// Consectuive spaces
		if ( tokleft > 1 && char_is_space( scanner[0] ) && char_is_space( scanner[ 1 ] ) )
		{
			content.append( cut_ptr, cut_length );
			do
			{
				move_fwd();
			}
			while ( tokleft && char_is_space( scanner[0] ) );

			last_cut = sptr( scanner ) - sptr( raw_text.Ptr );

			// Preserve only 1 space of formattting
			if ( content.back() != ' ' )
				content.append( ' ' );

			continue;
		}

		move_fwd();
	}

	if ( last_cut < raw_text.Len )
	{
		content.append( cut_ptr, raw_text.Len - last_cut );
	}

#undef cut_ptr
#undef cut_length
#undef pos
#undef move_fwd

	return content;
}

internal
Code parse_array_decl()
{
	push_scope();

	if ( check( TokType::Operator ) && currtok.Text[0] == '[' && currtok.Text[1] == ']' )
	{
		Code array_expr = untyped_str( currtok );
		eat( TokType::Operator );
		// []

		Context.pop();
		return array_expr;
	}

	if ( check( TokType::BraceSquare_Open ) )
	{
		eat( TokType::BraceSquare_Open );
		// [

		if ( left == 0 )
		{
			log_failure( "Error, unexpected end of array declaration ( '[]' scope started )\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		if ( currtok.Type == TokType::BraceSquare_Close )
		{
			log_failure( "Error, empty array expression in definition\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		Token untyped_tok = currtok;

		while ( left && currtok.Type != TokType::BraceSquare_Close )
		{
			eat( currtok.Type );
		}

		untyped_tok.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)untyped_tok.Text;

		Code array_expr = untyped_str( untyped_tok );
		// [ <Content>

		if ( left == 0 )
		{
			log_failure( "Error, unexpected end of array declaration, expected ]\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		if ( currtok.Type != TokType::BraceSquare_Close )
		{
			log_failure( "%s: Error, expected ] in array declaration, not %s\n%s", ETokType::to_str( currtok.Type ), Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		eat( TokType::BraceSquare_Close );
		// [ <Content> ]

		// Its a multi-dimensional array
		if ( check( TokType::BraceSquare_Open ))
		{
			Code adjacent_arr_expr = parse_array_decl();
			// [ <Content> ][ <Content> ]...

			array_expr->Next = adjacent_arr_expr.ast;
		}

		Context.pop();
		return array_expr;
	}

	Context.pop();
	return { nullptr };
}

internal inline
CodeAttributes parse_attributes()
{
	push_scope();

	Token start = currtok;
	s32   len   = 0;

	// There can be more than one attribute. If there is flatten them to a single string.
	// TODO(Ed): Support keeping an linked list of attributes similar to parameters
	while ( left && currtok.is_attribute() )
	{
		if ( check( TokType::Attribute_Open ) )
		{
			eat( TokType::Attribute_Open );
			// [[

			while ( left && currtok.Type != TokType::Attribute_Close )
			{
				eat( currtok.Type );
			}
			// [[ <Content>

			eat( TokType::Attribute_Close );
			// [[ <Content> ]]

			len = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )start.Text;
		}
		else if ( check( TokType::Decl_GNU_Attribute ) )
		{
			eat( TokType::Decl_GNU_Attribute );
			eat( TokType::Capture_Start );
			eat( TokType::Capture_Start );
			// __attribute__((

			while ( left && currtok.Type != TokType::Capture_End )
			{
				eat( currtok.Type );
			}
			// __attribute__(( <Content>

			eat( TokType::Capture_End );
			eat( TokType::Capture_End );
			// __attribute__(( <Content> ))

			len = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )start.Text;
		}
		else if ( check( TokType::Decl_MSVC_Attribute ) )
		{
			eat( TokType::Decl_MSVC_Attribute );
			eat( TokType::Capture_Start );
			// __declspec(

			while ( left && currtok.Type != TokType::Capture_End )
			{
				eat( currtok.Type );
			}
			// __declspec( <Content>

			eat( TokType::Capture_End );
			// __declspec( <Content> )

			len = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )start.Text;
		}
		else if ( currtok.is_attribute() )
		{
			eat( currtok.Type );
			// <Attribute>

			// If its a macro based attribute, this could be a functional macro such as Unreal's UE_DEPRECATED(...)
			if ( check( TokType::Capture_Start))
			{
				eat( TokType::Capture_Start );

				s32 level = 0;
				while (left && currtok.Type != TokType::Capture_End && level == 0)
				{
					if (currtok.Type == TokType::Capture_Start)
						++ level;
					if (currtok.Type == TokType::Capture_End)
						--level;
					eat(currtok.Type);
				}
				eat(TokType::Capture_End);
			}

			len = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )start.Text;
			// <Attribute> ( ... )
		}
	}

	if ( len > 0 )
	{
		StrC attribute_txt = { len, start.Text };
		Context.pop();

		String name_stripped = strip_formatting( attribute_txt, strip_formatting_dont_preserve_newlines );

		Code result     = make_code();
		result->Type    = ECode::PlatformAttributes;
		result->Name    = get_cached_string( name_stripped );
		result->Content = result->Name;
		// result->Token   =

		return ( CodeAttributes )result;
	}

	Context.pop();
	return { nullptr };
}

internal
Code parse_class_struct( TokType which, bool inplace_def = false )
{
	if ( which != TokType::Decl_Class && which != TokType::Decl_Struct )
	{
		log_failure( "Error, expected class or struct, not %s\n%s", ETokType::to_str( which ), Context.to_string() );
		return CodeInvalid;
	}

	Token name { nullptr, 0, TokType::Invalid };

	AccessSpec     access     = AccessSpec::Default;
	CodeType       parent     = { nullptr };
	CodeBody       body       = { nullptr };
	CodeAttributes attributes = { nullptr };
	ModuleFlag     mflags     = ModuleFlag::None;

	CodeClass result = CodeInvalid;

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <ModuleFlags>

	eat( which );
	// <ModuleFlags> <class/struct>

	attributes = parse_attributes();
	// <ModuleFlags> <class/struct> <Attributes>

	if ( check( TokType::Identifier ) )
	{
		name = parse_identifier();
		Context.Scope->Name = name;
	}
	// <ModuleFlags> <class/struct> <Attributes> <Name>

	local_persist
	char interface_arr_mem[ kilobytes(4) ] {0};
	Array<CodeType> interfaces = Array<CodeType>::init_reserve( Arena::init_from_memory(interface_arr_mem, kilobytes(4) ), 4 );

	// TODO(Ed) : Make an AST_DerivedType, we'll store any arbitary derived type into there as a linear linked list of them.
	if ( check( TokType::Assign_Classifer ) )
	{
		eat( TokType::Assign_Classifer );
		// <ModuleFlags> <class/struct> <Attributes> <Name> :

		if ( currtok.is_access_specifier() )
		{
			access = currtok.to_access_specifier();
			// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier>
			eat( currtok.Type );
		}

		Token parent_tok = parse_identifier();
		parent = def_type( parent_tok );
		// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Parent/Interface Name>

		while ( check(TokType::Comma) )
		{
			eat( TokType::Comma );
			// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Name>,

			if ( currtok.is_access_specifier() )
			{
				eat(currtok.Type);
			}
			Token interface_tok = parse_identifier();

			interfaces.append( def_type( interface_tok ) );
			// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Name>, ...
		}
	}

	if ( check( TokType::BraceCurly_Open ) )
	{
		body = parse_class_struct_body( which, name );
	}
	// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Name>, ... { <Body> }

	CodeComment inline_cmt = NoCode;
	if ( ! inplace_def )
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Name>, ... { <Body> };

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
			// <ModuleFlags> <class/struct> <Attributes> <Name> : <Access Specifier> <Name>, ... { <Body> }; <InlineCmt>
	}

	if ( which == TokType::Decl_Class )
		result = def_class( name, body, parent, access, attributes, mflags );

	else
		result = def_struct( name, body, (CodeType)parent, access, attributes, mflags );

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	interfaces.free();
	return result;
}

internal neverinline
CodeBody parse_class_struct_body( TokType which, Token name )
{
	using namespace ECode;
	push_scope();

	eat( TokType::BraceCurly_Open );
	// {

	CodeBody
	result = (CodeBody) make_code();

	if ( which == TokType::Decl_Class )
		result->Type = Class_Body;

	else
		result->Type = Struct_Body;

	while ( left && currtok_noskip.Type != TokType::BraceCurly_Close )
	{
		Code           member     = Code::Invalid;
		CodeAttributes attributes = { nullptr };
		CodeSpecifiers specifiers = { nullptr };

		bool expects_function = false;

		// Context.Scope->Start = currtok_noskip;

		if ( currtok_noskip.Type == TokType::Preprocess_Hash )
			eat( TokType::Preprocess_Hash );

		switch ( currtok_noskip.Type )
		{
			case TokType::Statement_End:
			{
				// TODO(Ed): Convert this to a general warning procedure
				log_fmt("Dangling end statement found %S\n", currtok_noskip.to_string());
				eat( TokType::Statement_End );
				continue;
			}
			case TokType::NewLine:
				member = fmt_newline;
				eat( TokType::NewLine );
			break;

			case TokType::Comment:
				member = parse_comment();
			break;

			case TokType::Access_Public:
				member = access_public;
				eat( TokType::Access_Public );
				eat( TokType::Assign_Classifer );
				// public:
			break;

			case TokType::Access_Protected:
				member = access_protected;
				eat( TokType::Access_Protected );
				eat( TokType::Assign_Classifer );
				// protected:
			break;

			case TokType::Access_Private:
				member = access_private;
				eat( TokType::Access_Private );
				eat( TokType::Assign_Classifer );
				// private:
			break;

			case TokType::Decl_Class:
				member = parse_complicated_definition( TokType::Decl_Class );
				// class
			break;

			case TokType::Decl_Enum:
				member = parse_complicated_definition( TokType::Decl_Enum );
				// enum
			break;

			case TokType::Decl_Friend:
				member = parse_friend();
				// friend
			break;

			case TokType::Decl_Operator:
				member = parse_operator_cast();
				// operator <Type>()
			break;

			case TokType::Decl_Struct:
				member = parse_complicated_definition( TokType::Decl_Struct );
				// struct
			break;

			case TokType::Decl_Template:
				member = parse_template();
				// template< ... >
			break;

			case TokType::Decl_Typedef:
				member = parse_typedef();
				// typedef
			break;

			case TokType::Decl_Union:
				member = parse_complicated_definition( TokType::Decl_Union );
				// union
			break;

			case TokType::Decl_Using:
				member = parse_using();
				// using
			break;

			case TokType::Operator:
				if ( currtok.Text[0] != '~' )
				{
					log_failure( "Operator token found in global body but not destructor unary negation\n%s", Context.to_string() );
					return CodeInvalid;
				}

				member = parse_destructor();
				// ~<Name>()
			break;

			case TokType::Preprocess_Define:
				member = parse_define();
				// #define
			break;

			case TokType::Preprocess_Include:
				member = parse_include();
				// #include
			break;

			case TokType::Preprocess_If:
			case TokType::Preprocess_IfDef:
			case TokType::Preprocess_IfNotDef:
			case TokType::Preprocess_ElIf:
				member = parse_preprocess_cond();
				// #<Condition>
			break;

			case TokType::Preprocess_Else:
				member = preprocess_else;
				eat( TokType::Preprocess_Else );
				// #else
			break;

			case TokType::Preprocess_EndIf:
				member = preprocess_endif;
				eat( TokType::Preprocess_EndIf );
				// #endif
			break;

			case TokType::Preprocess_Macro:
				member = parse_simple_preprocess( TokType::Preprocess_Macro );
				// <Macro>
			break;

			case TokType::Preprocess_Pragma:
				member = parse_pragma();
				// #pragma
			break;

			case TokType::Preprocess_Unsupported:
				member = parse_simple_preprocess( TokType::Preprocess_Unsupported );
				// #<UNKNOWN>
			break;

			case TokType::StaticAssert:
				member = parse_static_assert();
				// static_assert
			break;

			case TokType::Attribute_Open:
			case TokType::Decl_GNU_Attribute:
			case TokType::Decl_MSVC_Attribute:
		#define Entry( attribute, str ) case TokType::attribute:
			GEN_DEFINE_ATTRIBUTE_TOKENS
		#undef Entry
			{
				attributes = parse_attributes();
				// <Attributes>
			}
			//! Fallthrough intended
			case TokType::Spec_Consteval:
			case TokType::Spec_Constexpr:
			case TokType::Spec_Constinit:
			case TokType::Spec_Explicit:
			case TokType::Spec_ForceInline:
			case TokType::Spec_Inline:
			case TokType::Spec_Mutable:
			case TokType::Spec_NeverInline:
			case TokType::Spec_Static:
			case TokType::Spec_Volatile:
			case TokType::Spec_Virtual:
			{
				SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
				s32        NumSpecifiers = 0;

				while ( left && currtok.is_specifier() )
				{
					SpecifierT spec = ESpecifier::to_type( currtok );

					b32 ignore_spec = false;

					switch ( spec )
					{
						case ESpecifier::Constexpr:
						case ESpecifier::Constinit:
						case ESpecifier::Explicit:
						case ESpecifier::Inline:
						case ESpecifier::ForceInline:
						case ESpecifier::Mutable:
						case ESpecifier::NeverInline:
						case ESpecifier::Static:
						case ESpecifier::Volatile:
						case ESpecifier::Virtual:
						break;

						case ESpecifier::Consteval:
							expects_function = true;
						break;

						case ESpecifier::Const :
							ignore_spec = true;
						break;

						default:
							log_failure( "Invalid specifier %s for variable\n%s", ESpecifier::to_str(spec), Context.to_string() );
							Context.pop();
							return CodeInvalid;
					}

					// Every specifier after would be considered part of the type type signature
					if (ignore_spec)
						break;

					specs_found[NumSpecifiers] = spec;
					NumSpecifiers++;
					eat( currtok.Type );
				}

				if ( NumSpecifiers )
				{
					specifiers = def_specifiers( NumSpecifiers, specs_found );
				}
				// <Attributes> <Specifiers>

				if ( currtok.is_attribute() )
				{
					// Unfortuantely Unreal has code where there is attirbutes before specifiers
					CodeAttributes more_attributes = parse_attributes();

					if ( attributes )
					{
						String fused = String::make_reserve( GlobalAllocator, attributes->Content.length() + more_attributes->Content.length() );
						fused.append_fmt( "%S %S", attributes->Content, more_attributes->Content );

						attributes->Name    = get_cached_string(fused);
						attributes->Content = attributes->Name;
						// <Attributes> <Specifiers> <Attributes>
					}

					attributes = more_attributes;
				}

				if ( currtok.Type == TokType::Operator && currtok.Text[0] == '~' )
				{
					member = parse_destructor( specifiers );
					// <Attribute> <Specifiers> ~<Name>()
					break;
				}

				if ( currtok.Type == TokType::Decl_Operator )
				{
					member = parse_operator_cast( specifiers );
					// <Attributes> <Specifiers> operator <Type>()
					break;
				}
			}
			//! Fallthrough intentional
			case TokType::Identifier:
			case TokType::Spec_Const:
			case TokType::Type_Unsigned:
			case TokType::Type_Signed:
			case TokType::Type_Short:
			case TokType::Type_Long:
			case TokType::Type_bool:
			case TokType::Type_char:
			case TokType::Type_int:
			case TokType::Type_double:
			{
				if ( nexttok.Type == TokType::Capture_Start && name.Length && currtok.Type == TokType::Identifier )
				{
					if ( str_compare( name.Text, currtok.Text, name.Length ) == 0 )
					{
						member = parse_constructor( specifiers );
						// <Attributes> <Specifiers> <Name>()
						break;
					}
				}

				member = parse_operator_function_or_variable( expects_function, attributes, specifiers );
				// <Attributes> <Specifiers> operator <Op> ...
				// or
				// <Attributes> <Specifiers> <Name> ...
			}
			break;

			default:
				Token untyped_tok = currtok;

				while ( left && currtok.Type != TokType::BraceCurly_Close )
				{
					untyped_tok.Length = ( (sptr)currtok.Text + currtok.Length ) - (sptr)untyped_tok.Text;
					eat( currtok.Type );
				}

				member = untyped_str( untyped_tok );
				// Something unknown
			break;
		}

		if ( member == Code::Invalid )
		{
			log_failure( "Failed to parse member\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		result.append( member );
	}

	eat( TokType::BraceCurly_Close );
	// { <Members> }
	Context.pop();
	return result;
}

internal
CodeComment parse_comment()
{
	StackNode scope { nullptr, currtok_noskip, NullToken, txt( __func__ ) };
	Context.push( & scope );

	CodeComment
	result          = (CodeComment) make_code();
	result->Type    = ECode::Comment;
	result->Content = get_cached_string( currtok_noskip );
	result->Name    = result->Content;
	// result->Token   = currtok_noskip;
	eat( TokType::Comment );

	Context.pop();
	return result;
}

internal
Code parse_complicated_definition( TokType which )
{
	push_scope();

	bool is_inplace = false;

	TokArray tokens = Context.Tokens;

	s32 idx         = tokens.Idx;
	s32 level       = 0;
	for ( ; idx < tokens.Arr.num(); idx++ )
	{
		if ( tokens[ idx ].Type == TokType::BraceCurly_Open )
			level++;

		if ( tokens[ idx ].Type == TokType::BraceCurly_Close )
			level--;

		if ( level == 0 && tokens[ idx ].Type == TokType::Statement_End )
			break;
	}

	if ( ( idx - 2 ) == tokens.Idx )
	{
		// Its a forward declaration only
		Code result = parse_forward_or_definition( which, is_inplace );
		// <class, enum, struct, or union> <Name>;
		Context.pop();
		return result;
	}

	Token tok = tokens[ idx - 1 ];
	if ( tok.is_specifier() && is_trailing( ESpecifier::to_type(tok)) )
	{
		// <which> <type_identifier>(...) <specifier> ...;

		s32   spec_idx = idx - 1;
		Token spec     = tokens[spec_idx];
		while ( spec.is_specifier() && is_trailing( ESpecifier::to_type(spec)) )
		{
			-- spec_idx;
			spec = tokens[spec_idx];
		}

		if ( tokens[spec_idx].Type == TokType::Capture_End )
		{
			// Forward declaration with trailing specifiers for a procedure
			tok = tokens[spec_idx];

			Code result = parse_operator_function_or_variable( false, { nullptr }, { nullptr } );
			// <Attributes> <Specifiers> <ReturnType/ValueType> <operator <Op>, or Name> ...
			Context.pop();
			return result;
		}

		log_failure( "Unsupported or bad member definition after %s declaration\n%s", to_str(which), Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}
	if ( tok.Type == TokType::Identifier )
	{
		tok = tokens[ idx - 2 ];
		bool is_indirection = tok.Type == TokType::Ampersand || tok.Type == TokType::Star;
		bool ok_to_parse    = false;

		if ( tok.Type == TokType::BraceCurly_Close )
		{
			// Its an inplace definition
			// <which> <type_identifier> { ... } <identifier>;
			ok_to_parse = true;
			is_inplace  = true;
		}
		else if ( tok.Type == TokType::Identifier && tokens[ idx - 3 ].Type == which )
		{
			// Its a variable with type ID using <which> namespace.
			// <which> <type_identifier> <identifier>;
			ok_to_parse = true;
		}
		else if ( tok.Type == TokType::Assign_Classifer
		&& (	( tokens[idx - 5].Type == which && tokens[idx - 4].Type == TokType::Decl_Class )
			||	( tokens[idx - 4].Type == which))
		)
		{
			// Its a forward declaration of an enum
			// <enum>         <type_identifier> : <identifier>;
			// <enum> <class> <type_identifier> : <identifier>;
			ok_to_parse = true;
			Code result = parse_enum();
			Context.pop();
			return result;
		}
		else if ( is_indirection )
		{
			// Its a indirection type with type ID using struct namespace.
			// <which> <type_identifier>* <identifier>;
			ok_to_parse = true;
		}

		if ( ! ok_to_parse )
		{
			log_failure( "Unsupported or bad member definition after %s declaration\n%s", to_str(which), Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		Code result = parse_operator_function_or_variable( false, { nullptr }, { nullptr } );
		// <Attributes> <Specifiers> <ReturnType/ValueType> <operator <Op>, or Name> ...
		Context.pop();
		return result;
	}
	else if ( tok.Type >= TokType::Type_Unsigned && tok.Type <= TokType::Type_MS_W64 )
	{
		tok = tokens[ idx - 2 ];

		if ( tok.Type != TokType::Assign_Classifer
		|| (	( tokens[idx - 5].Type != which && tokens[idx - 4].Type != TokType::Decl_Class )
			&&	( tokens[idx - 4].Type != which))
		)
		{
			log_failure( "Unsupported or bad member definition after %s declaration\n%s", to_str(which), Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		// Its a forward declaration of an enum class
		// <enum>         <type_identifier> : <identifier>;
		// <enum> <class> <type_identifier> : <identifier>;
		Code result = parse_enum();
		Context.pop();
		return result;
	}
	else if ( tok.Type == TokType::BraceCurly_Close )
	{
		// Its a definition
		Code result = parse_forward_or_definition( which, is_inplace );
		// <which> { ... };
		Context.pop();
		return result;
	}
	else if ( tok.Type == TokType::BraceSquare_Close )
	{
		// Its an array definition
		Code result = parse_operator_function_or_variable( false, { nullptr }, { nullptr } );
		// <which> <type_identifier> <identifier> [ ... ];
		Context.pop();
		return result;
	}
	else
	{
		log_failure( "Unsupported or bad member definition after %s declaration\n%S", to_str(which).Ptr, Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}
}

internal inline
CodeDefine parse_define()
{
	push_scope();
	eat( TokType::Preprocess_Define );
	// #define

	CodeDefine
	define = (CodeDefine) make_code();
	define->Type = ECode::Preprocess_Define;

	if ( ! check( TokType::Identifier ) )
	{
		log_failure( "Error, expected identifier after #define\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	Context.Scope->Name = currtok;
	define->Name = get_cached_string( currtok );
	eat( TokType::Identifier );
	// #define <Name>

	if ( ! check( TokType::Preprocess_Content ))
	{
		log_failure( "Error, expected content after #define %s\n%s", define->Name, Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	if ( currtok.Length == 0 )
	{
		define->Content = get_cached_string( currtok );
		eat( TokType::Preprocess_Content );
		// #define <Name> <Content>

		Context.pop();
		return define;
	}

	define->Content = get_cached_string( strip_formatting( currtok, strip_formatting_dont_preserve_newlines ) );
	eat( TokType::Preprocess_Content );
	// #define <Name> <Content>

	Context.pop();
	return define;
}

internal inline
Code parse_assignment_expression()
{
	Code expr = { nullptr };

	eat( TokType::Operator );
	// <Attributes> <Specifiers> <ValueType> <Name> =

	Token expr_tok = currtok;

	if ( currtok.Type == TokType::Statement_End && currtok.Type != TokType::Comma )
	{
		log_failure( "Expected expression after assignment operator\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	s32 level = 0;
	while ( left && currtok.Type != TokType::Statement_End && (currtok.Type != TokType::Comma || level > 0) )
	{
		if (currtok.Type == TokType::BraceCurly_Open )
			level++;
		if (currtok.Type == TokType::BraceCurly_Close )
			level--;
		if (currtok.Type == TokType::Capture_Start)
			level++;
		else if (currtok.Type == TokType::Capture_End)
			level--;

		eat( currtok.Type );
	}

	expr_tok.Length = ( ( sptr )currtok.Text + currtok.Length ) - ( sptr )expr_tok.Text - 1;
	expr            = untyped_str( expr_tok );
	// = <Expression>
	return expr;
}

internal inline
Code parse_forward_or_definition( TokType which, bool is_inplace )
{
	Code result = CodeInvalid;

	switch ( which )
	{
		case TokType::Decl_Class:
			result = parse_class( is_inplace );
			return result;

		case TokType::Decl_Enum:
			result = parse_enum( is_inplace );
			return result;

		case TokType::Decl_Struct:
			result = parse_struct( is_inplace );
			return result;

		case TokType::Decl_Union:
			result = parse_union( is_inplace );
			return result;

		default:
			log_failure( "Error, wrong token type given to parse_complicated_definition "
				"(only supports class, enum, struct, union) \n%s"
				, Context.to_string() );

			return CodeInvalid;
	}
}

// Function parsing is handled in multiple places because its initial signature is shared with variable parsing
internal inline
CodeFn parse_function_after_name(
	  ModuleFlag     mflags
	, CodeAttributes attributes
	, CodeSpecifiers specifiers
	, CodeType       ret_type
	, Token          name
)
{
	push_scope();
	CodeParam params = parse_params();
	// <Attributes> <Specifiers> <ReturnType> <Name> ( <Parameters> )

	// TODO(Ed), Review old comment : These have to be kept separate from the return type's specifiers. 
	while ( left && currtok.is_specifier() )
	{
		if ( specifiers.ast == nullptr )
		{
			specifiers = def_specifier( ESpecifier::to_type(currtok) );
			eat( currtok.Type );
			continue;
		}

		specifiers.append( ESpecifier::to_type(currtok) );
		eat( currtok.Type );
	}
	// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers>

	CodeBody    body       = NoCode;
	CodeComment inline_cmt = NoCode;
	if ( check( TokType::BraceCurly_Open ) )
	{
		body = parse_function_body();
		if ( body == Code::Invalid )
		{
			Context.pop();
			return CodeInvalid;
		}
		// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers> { <Body> }
	}
	else if ( check(TokType::Operator) && currtok.Text[0] == '=' )
	{
		eat(TokType::Operator);
		specifiers.append( ESpecifier::Pure );

		eat( TokType::Number);
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers> = 0;

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
		// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers>; <InlineCmt>
	}
	else
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers>;

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
			// <Attributes> <Specifiers> <ReturnType> <Name> ( <Paraemters> ) <Specifiers>; <InlineCmt>
	}

	using namespace ECode;

	String
	name_stripped = String::make( GlobalAllocator, name );
	name_stripped.strip_space();

	CodeFn
	result              = (CodeFn) make_code();
	result->Name        = get_cached_string( name_stripped );
	result->ModuleFlags = mflags;

	if ( body )
	{
		switch ( body->Type )
		{
			case Function_Body:
			case Untyped:
				break;

			default:
			{
				log_failure("Body must be either of Function_Body or Untyped type, %s\n%s", body.debug_str(), Context.to_string());
				Context.pop();
				return CodeInvalid;
			}
		}

		result->Type = Function;
		result->Body = body;
	}
	else
	{
		result->Type = Function_Fwd;
	}

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	result->ReturnType = ret_type;

	if ( params )
		result->Params = params;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal
Code parse_function_body()
{
	using namespace ECode;
	push_scope();

	eat( TokType::BraceCurly_Open );

	CodeBody
	result = (CodeBody) make_code();
	result->Type = Function_Body;

	// TODO : Support actual parsing of function body
	Token start = currtok_noskip;

	s32 level = 0;
	while ( left && ( currtok_noskip.Type != TokType::BraceCurly_Close || level > 0 ) )
	{
		if ( currtok_noskip.Type == TokType::BraceCurly_Open )
			level++;

		else if ( currtok_noskip.Type == TokType::BraceCurly_Close && level > 0 )
			level--;

		eat( currtok_noskip.Type );
	}

	Token previous = prevtok;

	s32 len = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)start.Text;

	if ( len > 0 )
	{
		result.append( def_execution( { len, start.Text } ) );
	}

	eat( TokType::BraceCurly_Close );

	Context.pop();
	return result;
}

internal neverinline
CodeBody parse_global_nspace( CodeT which )
{
	using namespace ECode;

	push_scope();

	if ( which != Namespace_Body && which != Global_Body && which != Export_Body && which != Extern_Linkage_Body )
		return CodeInvalid;

	if ( which != Global_Body )
		eat( TokType::BraceCurly_Open );
		// {

	CodeBody
	result = (CodeBody) make_code();
	result->Type = which;

	while ( left && currtok_noskip.Type != TokType::BraceCurly_Close )
	{
		Code           member     = Code::Invalid;
		CodeAttributes attributes = { nullptr };
		CodeSpecifiers specifiers = { nullptr };

		bool expects_function = false;

		// Context.Scope->Start = currtok_noskip;

		if ( currtok_noskip.Type == TokType::Preprocess_Hash )
			eat( TokType::Preprocess_Hash );

		switch ( currtok_noskip.Type )
		{
			case TokType::Statement_End:
			{
				// TODO(Ed): Convert this to a general warning procedure
				log_fmt("Dangling end statement found %S\n", currtok_noskip.to_string());
				eat( TokType::Statement_End );
				continue;
			}
			case TokType::NewLine:
				// Empty lines are auto skipped by Tokens.current()
				member = fmt_newline;
				eat( TokType::NewLine );
			break;

			case TokType::Comment:
				member = parse_comment();
			break;

			case TokType::Decl_Class:
				member = parse_complicated_definition( TokType::Decl_Class );
				// class
			break;

			case TokType::Decl_Enum:
				member = parse_complicated_definition( TokType::Decl_Enum );
				// enum
			break;

			case TokType::Decl_Extern_Linkage:
				if ( which == Extern_Linkage_Body )
					log_failure( "Nested extern linkage\n%s", Context.to_string() );

				member = parse_extern_link();
				// extern "..." { ... }
			break;

			case TokType::Decl_Namespace:
				member = parse_namespace();
				// namespace <Name> { ... }
			break;

			case TokType::Decl_Struct:
				member = parse_complicated_definition( TokType::Decl_Struct );
				// struct ...
			break;

			case TokType::Decl_Template:
				member = parse_template();
				// template<...> ...
			break;

			case TokType::Decl_Typedef:
				member = parse_typedef();
				// typedef ...
			break;

			case TokType::Decl_Union:
				member = parse_complicated_definition( TokType::Decl_Union );
				// union ...
			break;

			case TokType::Decl_Using:
				member = parse_using();
				// using ...
			break;

			case TokType::Preprocess_Define:
				member = parse_define();
				// #define ...
			break;

			case TokType::Preprocess_Include:
				member = parse_include();
				// #include ...
			break;

			case TokType::Preprocess_If:
			case TokType::Preprocess_IfDef:
			case TokType::Preprocess_IfNotDef:
			case TokType::Preprocess_ElIf:
				member = parse_preprocess_cond();
				// #<Conditional> ...
			break;

			case TokType::Preprocess_Else:
				member = preprocess_else;
				eat( TokType::Preprocess_Else );
				// #else
			break;

			case TokType::Preprocess_EndIf:
				member = preprocess_endif;
				eat( TokType::Preprocess_EndIf );
				// #endif
			break;

			case TokType::Preprocess_Macro:
				member = parse_simple_preprocess( TokType::Preprocess_Macro );
				// <Macro>
			break;

			case TokType::Preprocess_Pragma:
				member = parse_pragma();
				// #pragma ...
			break;

			case TokType::Preprocess_Unsupported:
				member = parse_simple_preprocess( TokType::Preprocess_Unsupported );
				// #<UNSUPPORTED> ...
			break;

			case TokType::StaticAssert:
				member = parse_static_assert();
				// static_assert( <Conditional Expression>, ... );
			break;

			case TokType::Module_Export:
				if ( which == Export_Body )
					log_failure( "Nested export declaration\n%s", Context.to_string() );

				member = parse_export_body();
				// export { ... }
			break;

			case TokType::Module_Import:
			{
				not_implemented( context );
				// import ...
			}
			//! Fallthrough intentional
			case TokType::Attribute_Open:
			case TokType::Decl_GNU_Attribute:
			case TokType::Decl_MSVC_Attribute:
		#define Entry( attribute, str ) case TokType::attribute:
			GEN_DEFINE_ATTRIBUTE_TOKENS
		#undef Entry
			{
				attributes = parse_attributes();
				// <Attributes>
			}
			//! Fallthrough intentional
			case TokType::Spec_Consteval:
			case TokType::Spec_Constexpr:
			case TokType::Spec_Constinit:
			case TokType::Spec_Extern:
			case TokType::Spec_ForceInline:
			case TokType::Spec_Global:
			case TokType::Spec_Inline:
			case TokType::Spec_Internal_Linkage:
			case TokType::Spec_NeverInline:
			case TokType::Spec_Static:
			{
				SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
				s32        NumSpecifiers = 0;

				while ( left && currtok.is_specifier() )
				{
					SpecifierT spec = ESpecifier::to_type( currtok );

					bool ignore_spec = false;

					switch ( spec )
					{
						case ESpecifier::Constexpr:
						case ESpecifier::Constinit:
						case ESpecifier::ForceInline:
						case ESpecifier::Global:
						case ESpecifier::External_Linkage:
						case ESpecifier::Internal_Linkage:
						case ESpecifier::Inline:
						case ESpecifier::Mutable:
						case ESpecifier::NeverInline:
						case ESpecifier::Static:
						case ESpecifier::Volatile:
						break;

						case ESpecifier::Consteval:
							expects_function = true;
						break;

						case ESpecifier::Const:
							ignore_spec = true;
						break;

						default:
							StrC spec_str = ESpecifier::to_str(spec);

							log_failure( "Invalid specifier %.*s for variable\n%s", spec_str.Len, spec_str, Context.to_string() );
							Context.pop();
							return CodeInvalid;
					}

					if (ignore_spec)
						break;

					specs_found[NumSpecifiers] = spec;
					NumSpecifiers++;
					eat( currtok.Type );
				}

				if ( NumSpecifiers )
				{
					specifiers = def_specifiers( NumSpecifiers, specs_found );
				}
				// <Attributes> <Specifiers>
			}
			//! Fallthrough intentional
			case TokType::Identifier:
			case TokType::Spec_Const:
			case TokType::Type_Long:
			case TokType::Type_Short:
			case TokType::Type_Signed:
			case TokType::Type_Unsigned:
			case TokType::Type_bool:
			case TokType::Type_char:
			case TokType::Type_double:
			case TokType::Type_int:
			{
				Code constructor_destructor = parse_global_nspace_constructor_destructor( specifiers );
				// Possible constructor implemented at global file scope.
				if ( constructor_destructor )
				{
					member = constructor_destructor;
					break;
				}

				bool found_operator_cast_outside_class_implmentation = false;
				s32  idx = Context.Tokens.Idx;

				for ( ; idx < Context.Tokens.Arr.num(); idx++ )
				{
					Token tok = Context.Tokens[ idx ];

					if ( tok.Type == TokType::Identifier )
					{
						idx++;
						tok = Context.Tokens[ idx ];
						if ( tok.Type == TokType::Access_StaticSymbol )
							continue;

						break;
					}

					if ( tok.Type == TokType::Decl_Operator )
						found_operator_cast_outside_class_implmentation = true;

					break;
				}

				if ( found_operator_cast_outside_class_implmentation )
				{
					member = parse_operator_cast( specifiers );
					// <Attributes> <Specifiers> <Name>::operator <Type>() { ... }
					break;
				}

				member = parse_operator_function_or_variable( expects_function, attributes, specifiers );
				// <Attributes> <Specifiers> ...
			}
		}

		if ( member == Code::Invalid )
		{
			log_failure( "Failed to parse member\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		// log_fmt("Global Body Member: %s", member->debug_str());
		result.append( member );
	}

	if ( which != Global_Body )
		eat( TokType::BraceCurly_Close );
		// { <Body> }

	Context.pop();
	return result;
}

internal inline
Code parse_global_nspace_constructor_destructor( CodeSpecifiers specifiers )
{
	Code result = { nullptr };

	/*
		To check if a definition is for a constructor we can go straight to the opening parenthesis for its parameters
		From There we work backwards to see if we come across two identifiers with the same name between an member access
		:: operator, there can be template parameters on the left of the :: so we ignore those.
		Whats important is that	its back to back.

		This has multiple possible faults. What we parse using this method may not filter out if something has a "return type"
		This is bad since technically you could have a namespace nested into another namespace with the same name.
		If this awful pattern is done the only way to distiguish with this coarse parse is to know there is no return type defined.

		TODO(Ed): We could fix this by attempting to parse a type, but we would have to have a way to have it soft fail and rollback.
	*/
	TokArray tokens = Context.Tokens;

	s32   idx = tokens.Idx;
	Token nav = tokens[ idx ];
	for ( ; idx < tokens.Arr.num(); idx++, nav = tokens[ idx ] )
	{
		if ( nav.Text[0] == '<' )
		{
			// Skip templated expressions as they mey have expressions with the () operators
			s32 capture_level  = 0;
			s32 template_level = 0;
			for ( ; idx < tokens.Arr.num(); idx++, nav = tokens[idx] )
			{
				if (nav.Text[ 0 ] == '<')
					++ template_level;

				if (nav.Text[ 0 ] == '>')
					-- template_level;
				if (nav.Type == TokType::Operator && nav.Text[1] == '>')
					-- template_level;

				if ( nav.Type == ETokType::Capture_Start)
				{
					if (template_level != 0 )
						++ capture_level;
					else
						break;
				}

				if ( template_level != 0 && nav.Type == ETokType::Capture_End)
					-- capture_level;
			}
		}

		if ( nav.Type == TokType::Capture_Start )
			break;
	}

	-- idx;
	Token tok_right = tokens[idx];
	Token tok_left  = NullToken;

	if (tok_right.Type != TokType::Identifier)
	{
		// We're not dealing with a constructor if there is no identifier right before the opening of a parameter's scope.
		return result;
	}

	-- idx;
	tok_left = tokens[idx];
	// <Attributes> <Specifiers> ... <Identifier>

	bool possible_destructor = false;
	if ( tok_left.Type == TokType::Operator && tok_left.Text[0] == '~')
	{
		possible_destructor = true;
		-- idx;
		tok_left = tokens[idx];
	}

	if ( tok_left.Type != TokType::Access_StaticSymbol )
		return result;

	-- idx;
	tok_left = tokens[idx];
	// <Attributes> <Specifiers> ... :: <Identifier>

	// We search toward the left until we find the next valid identifier
	s32 capture_level  = 0;
	s32 template_level = 0;
	while ( idx != tokens.Idx )
	{
		if (tok_left.Text[ 0 ] == '<')
			++ template_level;

		if (tok_left.Text[ 0 ] == '>')
			-- template_level;
		if (tok_left.Type == TokType::Operator && tok_left.Text[1] == '>')
			-- template_level;

		if ( template_level != 0 && tok_left.Type == ETokType::Capture_Start)
			++ capture_level;

		if ( template_level != 0 && tok_left.Type == ETokType::Capture_End)
			-- capture_level;

		if ( capture_level == 0 && template_level == 0  && tok_left.Type == TokType::Identifier )
			break;

		-- idx;
		tok_left = tokens[idx];
	}

	bool is_same = str_compare( tok_right.Text, tok_left.Text, tok_right.Length ) == 0;
	if (tok_left.Type == TokType::Identifier && is_same)
	{
		// We have found the pattern we desired
		if (possible_destructor)
		{
			// <Name> :: ~<Name> (
			result = parse_destructor( specifiers );
		}
		else {
			// <Name> :: <Name> (
			result = parse_constructor( specifiers );
		}
	}

	return result;
}

// TODO(Ed): I want to eventually change the identifier to its own AST type.
// This would allow distinction of the qualifier for a symbol <qualifier>::<nested symboL>
// This would also allow 
internal
Token parse_identifier( bool* possible_member_function )
{
	push_scope();

	Token name = currtok;
	Context.Scope->Name = name;
	eat( TokType::Identifier );
	// <Name>

	parse_template_args( name );
	// <Name><Template Args>

	while ( check( TokType::Access_StaticSymbol ) )
	{
		eat( TokType::Access_StaticSymbol );
		// <Qualifier Name> <Template Args> ::

		if ( left == 0 )
		{
			log_failure( "Error, unexpected end of static symbol identifier\n%s", Context.to_string() );
			Context.pop();
			return { nullptr, 0, TokType::Invalid };
		}

		if ( currtok.Type == TokType::Operator && currtok.Text[0] == '~' )
		{
			bool is_destructor = str_compare( Context.Scope->Prev->ProcName, "parse_destructor" ) == 0;
			if (is_destructor)
			{
				name.Length = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )name.Text;
				Context.pop();
				return name;
			}

			log_failure( "Error, had a ~ operator after %S but not a destructor\n%s", ETokType::to_str( prevtok.Type ), Context.to_string() );
			Context.pop();
			return { nullptr, 0, TokType::Invalid };
		}

		if ( currtok.Type == TokType::Operator && currtok.Text[0] == '*' && currtok.Length == 1 )
		{
			if ( possible_member_function )
				*possible_member_function = true;

			else
			{
				log_failure( "Found a member function pointer identifier but the parsing context did not expect it\n%s", Context.to_string() );
				Context.pop();
				return { nullptr, 0, TokType::Invalid };
			}
		}

		if ( currtok.Type != TokType::Identifier )
		{
			log_failure( "Error, expected static symbol identifier, not %s\n%s", ETokType::to_str( currtok.Type ), Context.to_string() );
			Context.pop();
			return { nullptr, 0, TokType::Invalid };
		}

		name.Length = ( (sptr)currtok.Text + currtok.Length ) - (sptr)name.Text;
		eat( TokType::Identifier );
		// <Qualifier Name> <Template Args> :: <Name>

		parse_template_args( name );
		// <Qualifier Name> <Template Args> :: <Name> <Template Args>
	}
	// <Qualifier Name> <Template Args> :: <Name> <Template Args> ...

	Context.pop();
	return name;
}

internal
CodeInclude parse_include()
{
	push_scope();

	CodeInclude
	include       = (CodeInclude) make_code();
	include->Type = ECode::Preprocess_Include;
	eat( TokType::Preprocess_Include );
	// #include

	if ( ! check( TokType::String ))
	{
		log_failure( "Error, expected include string after #include\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	Context.Scope->Name = currtok;
	include->Content = get_cached_string( currtok );
	eat( TokType::String );
	// #include <Path> or "Path"

	Context.pop();
	return include;
}

internal
CodeOperator parse_operator_after_ret_type(
	  ModuleFlag     mflags
	, CodeAttributes attributes
	, CodeSpecifiers specifiers
	, CodeType       ret_type
)
{
	using namespace EOperator;
	push_scope();

	Token nspace = NullToken;
	if ( check( TokType::Identifier ) )
	{
		nspace = currtok;
		while ( left && currtok.Type == TokType::Identifier )
		{
			eat( TokType::Identifier );

			if ( currtok.Type == TokType::Access_StaticSymbol )
				eat( TokType::Access_StaticSymbol );
		}

		nspace.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)nspace.Text;
	}
	// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...>

	eat( TokType::Decl_Operator );
	// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator

	if ( ! left && currtok.Type != TokType::Operator
		&& currtok.Type != TokType::Star
		&& currtok.Type != TokType::Ampersand
		&& currtok.Type != TokType::Ampersand_DBL )
	{
		log_failure( "Expected operator after 'operator' keyword\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	Context.Scope->Name = currtok;

	bool was_new_or_delete = false;

	OperatorT op = Invalid;
	switch ( currtok.Text[0] )
	{
		case '+':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_Add;

			else if ( currtok.Text[1] == '+' )
				op = Increment;

			else
				op = Add;
		}
		break;
		case '-':
		{
			if ( currtok.Text[1] == '>' )
			{
				if ( currtok.Text[2] == '*' )
					op = MemberOfPointer;

				else
					op = MemberOfPointer;

				break;
			}

			else if ( currtok.Text[1] == '=' )
				op = Assign_Subtract;

			else
				op = Subtract;
		}
		break;
		case '*':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_Multiply;

			else
			{
				Token& finder = prevtok;
				while ( finder.Type != TokType::Decl_Operator )
				{
					if ( finder.Type == TokType::Identifier)
					{
						op = Indirection;
						break;
					}
				}

				if ( op == Invalid)
					op = Multiply;
			}
		}
		break;
		case '/':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_Divide;

			else
				op = Divide;
		}
		break;
		case '%':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_Modulo;

			else
				op = Modulo;
		}
		break;
		case '&':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_BAnd;

			else if ( currtok.Text[1] == '&' )
				op = LAnd;

			else
			{


				if ( op == Invalid )
				op = BAnd;
			}
		}
		break;
		case '|':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_BOr;

			else if ( currtok.Text[1] == '|' )
				op = LOr;

			else
				op = BOr;
		}
		break;
		case '^':
		{
			if ( currtok.Text[1] == '=' )
				op = Assign_BXOr;

			else
				op = BXOr;
		}
		break;
		case '~':
		{
			op = BNot;
		}
		break;
		case '!':
		{
			if ( currtok.Text[1] == '=' )
				op = LNot;

			else
				op = UnaryNot;
		}
		break;
		case '=':
		{
			if ( currtok.Text[1] == '=' )
				op = LEqual;

			else
				op = Assign;
		}
		break;
		case '<':
		{
			if ( currtok.Text[1] == '=' )
				op = LEqual;

			else if ( currtok.Text[1] == '<' )
			{
				if ( currtok.Text[2] == '=' )
					op = Assign_LShift;

				else
					op = LShift;
			}
			else
				op = Lesser;
		}
		break;
		case '>':
		{
			if ( currtok.Text[1] == '=' )
				op = GreaterEqual;

			else if ( currtok.Text[1] == '>' )
			{
				if ( currtok.Text[2] == '=' )
					op = Assign_RShift;

				else
					op = RShift;
			}
			else
				op = Greater;
		}
		break;
		case '(':
		{
			if ( currtok.Text[1] == ')' )
				op = FunctionCall;

			else
				op = Invalid;
		}
		break;
		case '[':
		{
			if ( currtok.Text[1] == ']' )
				op = Subscript;

			else
				op = Invalid;
		}
		break;
		default:
		{
			StrC str_new    = to_str(OperatorT::New);
			StrC str_delete = to_str(OperatorT::Delete);
			if ( str_compare( currtok.Text, str_new.Ptr, max(str_new.Len - 1, currtok.Length)) == 0)
			{
				op = OperatorT::New;
				eat( ETokType::Identifier );
				was_new_or_delete = true;

				s32 idx = Context.Tokens.Idx + 1;
				{
					while ( Context.Tokens[ idx ].Type == TokType::NewLine )
						idx++;
				}
				Token next = Context.Tokens[idx];
				if ( currtok.Type == TokType::Operator && str_compare(currtok.Text, "[]", 2) == 0)
				{
					eat(ETokType::Operator);
					op = OperatorT::NewArray;
				}
				else if ( currtok.Type == TokType::BraceSquare_Open && next.Type == TokType::BraceSquare_Close)
				{
					eat(ETokType::BraceSquare_Open);
					eat(ETokType::BraceSquare_Close);
					op = OperatorT::NewArray;
				}
			}
			else if ( str_compare( currtok.Text, str_delete.Ptr, max(str_delete.Len - 1, currtok.Length )) == 0)
			{
				op = OperatorT::Delete;
				eat(ETokType::Identifier);
				was_new_or_delete = true;

				s32 idx = Context.Tokens.Idx + 1;
				{
					while ( Context.Tokens[ idx ].Type == TokType::NewLine )
						idx++;
				}
				Token next = Context.Tokens[idx];
				if ( currtok.Type == TokType::Operator && str_compare(currtok.Text, "[]", 2) == 0)
				{
					eat(ETokType::Operator);
					op = OperatorT::DeleteArray;
				}
				else if ( currtok.Type == TokType::BraceSquare_Open && next.Type == TokType::BraceSquare_Close)
				{
					eat(ETokType::BraceSquare_Open);
					eat(ETokType::BraceSquare_Close);
					op = OperatorT::DeleteArray;
				}
			}
			else
			{
				if ( op == Invalid )
				{
					log_failure( "Invalid operator '%s'\n%s", prevtok.Text, Context.to_string() );
					Context.pop();
					return CodeInvalid;
				}
			}
		}
	}

	if ( op == Invalid )
	{
		log_failure( "Invalid operator '%s'\n%s", currtok.Text, Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	if ( ! was_new_or_delete)
		eat( currtok.Type );
	// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op>

	// Parse Params
	CodeParam params = parse_params();
	// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op> ( <Parameters> )

	if ( params.ast == nullptr && op == EOperator::Multiply )
		op = MemberOfPointer;

	while ( left && currtok.is_specifier() )
	{
		if ( specifiers.ast == nullptr )
		{
			specifiers = def_specifier( ESpecifier::to_type(currtok) );
			eat( currtok.Type );
			continue;
		}

		specifiers.append( ESpecifier::to_type(currtok) );
		eat( currtok.Type );
	}
	// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op> ( <Parameters> ) <Specifiers>

	// Parse Body
	CodeBody    body       = { nullptr };
	CodeComment inline_cmt = NoCode;
	if ( check( TokType::BraceCurly_Open ) )
	{
		body = parse_function_body();
		if ( body == Code::Invalid )
		{
			Context.pop();
			return CodeInvalid;
		}
		// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op> ( <Parameters> ) <Specifiers> { ... }
	}
	else
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op> ( <Parameters> ) <Specifiers>;

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
			// <ExportFlag> <Attributes> <Specifiers> <ReturnType> <Qualifier::...> operator <Op> ( <Parameters> ) <Specifiers>; <InlineCmt>
	}

	// OpValidateResult check_result = operator__validate( op, params, ret_type, specifiers );
	CodeOperator result = def_operator( op, nspace, params, ret_type, body, specifiers, attributes, mflags );

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal
Code parse_operator_function_or_variable( bool expects_function, CodeAttributes attributes, CodeSpecifiers specifiers )
{
	push_scope();

	Code result = CodeInvalid;

#ifndef GEN_PARSER_DISABLE_MACRO_FUNCTION_SIGNATURES
	if ( currtok.Type == TokType::Preprocess_Macro )
	{
		// Were dealing with a macro after attributes/specifiers.
		result = parse_simple_preprocess( TokType::Preprocess_Macro );
		Context.pop();
		return result;
		// <Attributes> <Specifiers> <Macro>
	}
#endif

	CodeType type = parse_type();
	// <Attributes> <Specifiers> <ReturnType/ValueType>

	if ( type == CodeInvalid )
	{
		Context.pop();
		return CodeInvalid;
	}

	bool found_operator = false;
	s32  idx            = Context.Tokens.Idx;

	for ( ; idx < Context.Tokens.Arr.num(); idx++ )
	{
		Token tok = Context.Tokens[ idx ];

		if ( tok.Type == TokType::Identifier )
		{
			idx++;
			tok = Context.Tokens[ idx ];
			if ( tok.Type == TokType::Access_StaticSymbol )
				continue;

			break;
		}

		if ( tok.Type == TokType::Decl_Operator )
			found_operator = true;

		break;
	}

	if ( found_operator )
	{
		// Dealing with an operator overload
		result = parse_operator_after_ret_type( ModuleFlag::None, attributes, specifiers, type );
		// <Attributes> <Specifiers> <ReturnType> operator ...
	}
	else
	{
		Token name = parse_identifier();
		Context.Scope->Name = name;

		bool detected_capture = check( TokType::Capture_Start );

		// Check three tokens ahead to make sure that were not dealing with a constructor initialization...
		//                  (         350.0f    ,         <---  Could be the scenario
		// Example : <Capture_Start> <Value> <Comma>
		//                 idx         +1      +2
		bool detected_comma = Context.Tokens.Arr[ Context.Tokens.Idx + 2 ].Type == TokType::Comma;
		if ( detected_capture && ! detected_comma )
		{
			// Dealing with a function
			result = parse_function_after_name( ModuleFlag::None, attributes, specifiers, type, name );
			// <Attributes> <Specifiers> <ReturnType> <Name> ( ...
		}
		else
		{
			if ( expects_function )
			{
				log_failure( "Expected function declaration (consteval was used)\n%s", Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}

			// Dealing with a variable
			result = parse_variable_after_name( ModuleFlag::None, attributes, specifiers, type, name );
			// <Attributes> <Specifiers> <ValueType> <Name> ...
		}
	}

	Context.pop();
	return result;
}

internal
CodePragma parse_pragma()
{
	push_scope();

	CodePragma
	pragma       = (CodePragma) make_code();
	pragma->Type = ECode::Preprocess_Pragma;
	eat( TokType::Preprocess_Pragma );
	// #pragma

	if ( ! check( TokType::Preprocess_Content ))
	{
		log_failure( "Error, expected content after #pragma\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	Context.Scope->Name = currtok;

	pragma->Content = get_cached_string( currtok );
	eat( TokType::Preprocess_Content );
	// #pragma <Content>

	Context.pop();
	return pragma;
}

internal inline
CodeParam parse_params( bool use_template_capture )
{
	using namespace ECode;
	push_scope();

	if ( ! use_template_capture )
		eat( TokType::Capture_Start );
	// (

	else
	{
		if ( check( TokType::Operator ) && currtok.Text[ 0 ] == '<' )
			eat( TokType::Operator );
		// <
	}

	if ( ! use_template_capture && check( TokType::Capture_End ) )
	{
		eat( TokType::Capture_End );
		// )
		Context.pop();
		return { nullptr };
	}
	else if ( check( TokType::Operator ) && currtok.Text[ 0 ] == '>' )
	{
		eat( TokType::Operator );
		// >
		Context.pop();
		return { nullptr };
	}

	Code     macro           = { nullptr };
	CodeType type            = { nullptr };
	Code     value           = { nullptr };
	Token    name            = NullToken;
	Code     post_name_macro = { nullptr };

	if ( check( TokType::Varadic_Argument ) )
	{
		eat( TokType::Varadic_Argument );
		// ( or <  ...

		Context.pop();
		return param_varadic;
		// ( ... )
		// or < ... >
	}

	#define CheckEndParams() \
		(use_template_capture ? (currtok.Text[ 0 ] != '>') : (currtok.Type != TokType::Capture_End))

	// Ex: Unreal has this type of macro:                 vvvvvvvvv
	// COREUOBJECT_API void CallFunction( FFrame& Stack, RESULT_DECL, UFunction* Function );
	// and:                 vvvv
	// AddComponentByClass(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UActorComponent> Class, bool bManualAttachment, ...
	if ( check(TokType::Preprocess_Macro))
	{
		macro = parse_simple_preprocess(ETokType::Preprocess_Macro);
		// ( <Macro>
	}
	if ( currtok.Type != TokType::Comma )
	{
		type = parse_type( use_template_capture );
		if ( type == Code::Invalid )
		{
			Context.pop();
			return CodeInvalid;
		}
		// ( <Macro> <ValueType>

		if ( check( TokType::Identifier ) )
		{
			name = currtok;
			eat( TokType::Identifier );
			// ( <Macro> <ValueType> <Name>
		}

		// Unreal has yet another type of macro:
		// template<class T UE_REQUIRES(TPointerIsConvertibleFromTo<T, UInterface>::Value)>
		// class T ... and then ^this^ UE_REQUIRES shows up
		// So we need to consume that.
		if ( check( TokType::Preprocess_Macro ))
		{
			post_name_macro = parse_simple_preprocess( ETokType::Preprocess_Macro );
		}

		// In template captures you can have a typename have direct assignment without a name
		// typename = typename ...
		// Which would result in a static value type from a struct expansion (traditionally)
		if ( ( name.Text || use_template_capture ) && bitfield_is_equal( u32, currtok.Flags, TF_Assign ) )
		{
			eat( TokType::Operator );
			// ( <Macro> <ValueType> <Name> =

			Token value_tok = currtok;

			if ( currtok.Type == TokType::Comma )
			{
				log_failure( "Expected value after assignment operator\n%s.", Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}

			s32 capture_level  = 0;
			s32 template_level = 0;
			while ( (left && ( currtok.Type != TokType::Comma ) && template_level >= 0 && CheckEndParams()) || (capture_level > 0 || template_level > 0) )
			{
				if (currtok.Text[ 0 ] == '<')
					++ template_level;

				if (currtok.Text[ 0 ] == '>')
					-- template_level;
				if (currtok.Type == TokType::Operator && currtok.Text[1] == '>')
					-- template_level;

				if ( currtok.Type == ETokType::Capture_Start)
					++ capture_level;

				if ( currtok.Type == ETokType::Capture_End)
					-- capture_level;

				value_tok.Length = ( ( sptr )currtok.Text + currtok.Length ) - ( sptr )value_tok.Text;
				eat( currtok.Type );
			}

			value = untyped_str( strip_formatting( value_tok, strip_formatting_dont_preserve_newlines ) );
			// ( <Macro> <ValueType> <Name> = <Expression>
		}
	}

	CodeParam result = ( CodeParam )make_code();
	result->Type     = Parameters;

	result->Macro = macro;

	if ( name.Length > 0 )
		result->Name = get_cached_string( name );

	result->ValueType = type;

	if ( value )
		result->Value = value;

	result->NumEntries++;

	while ( check(TokType::Comma) )
	{
		eat( TokType::Comma );
		// ( <Macro> <ValueType> <Name> = <Expression>,

		Code type  = { nullptr };
		Code value = { nullptr };

		if ( check( TokType::Varadic_Argument ) )
		{
			eat( TokType::Varadic_Argument );
			result.append( param_varadic );
			continue;
			// ( <Macro> <ValueType> <Name> = <Expression>, ...
		}

		// Ex: Unreal has this type of macro:                 vvvvvvvvv
		// COREUOBJECT_API void CallFunction( FFrame& Stack, RESULT_DECL, UFunction* Function );
		// and:                 vvvv
		// AddComponentByClass(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UActorComponent> Class, bool bManualAttachment, ...
		if ( check(TokType::Preprocess_Macro))
		{
			macro = parse_simple_preprocess(ETokType::Preprocess_Macro);
			// ( <Macro>
		}
		if ( currtok.Type != TokType::Comma )
		{
			type = parse_type( use_template_capture );
			if ( type == Code::Invalid )
			{
				Context.pop();
				return CodeInvalid;
			}
			// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType>

			name = { nullptr, 0, TokType::Invalid, false };

			if ( check( TokType::Identifier ) )
			{
				name = currtok;
				eat( TokType::Identifier );
				// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name>
			}

			// Unreal has yet another type of macro:
			// template<class T UE_REQUIRES(TPointerIsConvertibleFromTo<T, UInterface>::Value)>
			// class T ... and then ^this^ UE_REQUIRES shows up
			// So we need to consume that.
			if ( check( TokType::Preprocess_Macro ))
			{
				post_name_macro = parse_simple_preprocess( ETokType::Preprocess_Macro );
			}

			// In template captures you can have a typename have direct assignment without a name
			// typename = typename ...
			// Which would result in a static value type from a struct expansion (traditionally)
			if ( ( name.Text || use_template_capture ) && bitfield_is_equal( u32, currtok.Flags, TF_Assign ) )
			{
				eat( TokType::Operator );
				// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name> =

				Token value_tok = currtok;

				if ( currtok.Type == TokType::Comma )
				{
					log_failure( "Expected value after assignment operator\n%s", Context.to_string() );
					Context.pop();
					return CodeInvalid;
				}

				s32 capture_level  = 0;
				s32 template_level = 0;
				while ( (left
				&& currtok.Type != TokType::Comma
				&& template_level >= 0
				&& CheckEndParams()) || (capture_level > 0 || template_level > 0) )
				{
					if (currtok.Text[ 0 ] == '<')
						++ template_level;

					if (currtok.Text[ 0 ] == '>')
						-- template_level;
					if (currtok.Type == TokType::Operator && currtok.Text[1] == '>')
						-- template_level;

					if ( currtok.Type == ETokType::Capture_Start)
						++ capture_level;

					if ( currtok.Type == ETokType::Capture_End)
						-- capture_level;

					value_tok.Length = ( ( sptr )currtok.Text + currtok.Length ) - ( sptr )value_tok.Text;
					eat( currtok.Type );
				}

				value = untyped_str( strip_formatting( value_tok, strip_formatting_dont_preserve_newlines ) );
				// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name> = <Expression>
			}
			// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name> = <Expression>, ..
		}

		CodeParam param = ( CodeParam )make_code();
		param->Type     = Parameters;

		param->Macro = macro;

		if ( name.Length > 0 )
			param->Name = get_cached_string( name );

		param->PostNameMacro = post_name_macro;
		param->ValueType     = type;

		if ( value )
			param->Value = value;

		result.append( param );
	}

	if ( ! use_template_capture )
		eat( TokType::Capture_End );
	// ( <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name> = <Expression>, .. )

	else
	{
		if ( ! check( TokType::Operator ) || currtok.Text[ 0 ] != '>' )
		{
			log_failure( "Expected '<' after 'template' keyword\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}
		eat( TokType::Operator );
		// < <Macro> <ValueType> <Name> = <Expression>, <Macro> <ValueType> <Name> = <Expression>, .. >
	}

	Context.pop();
	return result;
#undef context
}

internal
CodePreprocessCond parse_preprocess_cond()
{
	push_scope();

	if ( ! currtok.is_preprocess_cond() )
	{
		log_failure( "Error, expected preprocess conditional\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	CodePreprocessCond
	cond       = (CodePreprocessCond) make_code();
	cond->Type = scast(CodeT, currtok.Type - ( TokType::Preprocess_If - ECode::Preprocess_If ) );
	eat( currtok.Type );
	// #<Conditional>

	if ( ! check( TokType::Preprocess_Content ))
	{
		log_failure( "Error, expected content after #define\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	Context.Scope->Name = currtok;
	cond->Content = get_cached_string( currtok );
	eat( TokType::Preprocess_Content );
	// #<Conditiona> <Content>

	Context.pop();
	return cond;
}

internal inline
Code parse_simple_preprocess( TokType which )
{
	// TODO(Ed): We can handle a macro a bit better than this. It's AST can be made more robust..
	// Make an AST_Macro, it should have an Name be the macro itself, with the function body being an optional function body node.
	// If we want it to terminate or have an inline comment we can possbily use its parent typedef for that info...
	push_scope();

	Token tok = currtok;
	eat( which );
	// <Macro>

	if ( currtok.Type == TokType::BraceCurly_Open )
	{
		// Eat the block scope right after the macro. Were assuming the macro defines a function definition's signature
		eat( TokType::BraceCurly_Open );
		// <Macro> {

		// TODO(Ed) : Parse this properly later (expression and statement support)
		s32 level = 0;
		while ( left && ( currtok.Type != TokType::BraceCurly_Close || level > 0 ) )
		{
			if ( currtok.Type == TokType::BraceCurly_Open )
				level++;

			else if ( currtok.Type == TokType::BraceCurly_Close && level > 0 )
				level--;

			eat( currtok.Type );
		}
		eat( TokType::BraceCurly_Close );
		// <Macro> { <Body> }

		StrC prev_proc = Context.Scope->Prev->ProcName;
		if ( str_compare( prev_proc.Ptr, "parse_typedef", prev_proc.Len ) != 0 )
		{
			if ( check( TokType::Statement_End ))
			{
				Token stmt_end = currtok;
				eat( TokType::Statement_End );
				// <Macro> { <Content> };

				if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
					eat( TokType::Comment );
					// <Macro> { <Content> }; <InlineCmt>
			}
		}

		tok.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)tok.Text;
	}
	else
	{
		if ( str_compare( Context.Scope->Prev->ProcName.Ptr, "parse_typedef", Context.Scope->Prev->ProcName.Len ) != 0 )
		{
			if ( check( TokType::Statement_End ))
			{
				Token stmt_end = currtok;
				eat( TokType::Statement_End );
				// <Macro>;

				if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
					eat( TokType::Comment );
					// <Macro>; <InlineCmt>
			}
		}

		tok.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)tok.Text;
	}

	char const* content = str_fmt_buf( "%.*s ", tok.Length, tok.Text );

	Code result = untyped_str( to_str( content ) );
	Context.Scope->Name = tok;

	Context.pop();
	return result;
}

internal
Code parse_static_assert()
{
	push_scope();

	Code
	assert       = make_code();
	assert->Type = ECode::Untyped;

	Token content = currtok;

	Context.Scope->Name = content;

	eat( TokType::StaticAssert );
	eat( TokType::Capture_Start );
	// static_assert(

	// TODO(Ed) : Parse this properly.
	s32 level = 0;
	while ( left && ( currtok.Type != TokType::Capture_End || level > 0 ) )
	{
		if ( currtok.Type == TokType::Capture_Start )
			level++;
		else if ( currtok.Type == TokType::Capture_End )
			level--;

		eat( currtok.Type );
	}
	eat( TokType::Capture_End );
	eat( TokType::Statement_End );
	// static_assert( <Content> );

	content.Length  = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)content.Text;

	char const* str = str_fmt_buf( "%.*s\n", content.Length, content.Text );
	assert->Content = get_cached_string( { content.Length + 1, str } );
	assert->Name	= assert->Content;

	Context.pop();
	return assert;
}

/*
	This a brute-froce make all the arguments part of the token provided.
	Can have in-place function signatures, regular identifiers, in-place typenames, compile-time expressions, parameter-pack expansion, etc.
	This means that validation can only go so far, and so if there is any different in formatting
	passed the basic stripping supported it report a soft failure.
*/
internal inline
void parse_template_args( Token& token )
{
	if ( currtok.Type == TokType::Operator && currtok.Text[ 0 ] == '<' && currtok.Length == 1 )
	{
		eat( TokType::Operator );
		// <

		s32 level = 0;
		while ( left && level >= 0 && ( currtok.Text[ 0 ] != '>' || level > 0 ) )
		{
			if ( currtok.Text[ 0 ] == '<' )
				level++;

			if ( currtok.Text[ 0 ] == '>' )
				level--;
			if ( currtok.Type == TokType::Operator && currtok.Text[1] == '>')
				level--;

			eat( currtok.Type );
		}
		// < <Content>

		// Due to the >> token, this could have been eaten early...
		if (level == 0)
			eat( TokType::Operator );
		// < <Content> >

		// Extend length of name to last token
		token.Length = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )token.Text;
	}
}

// Variable parsing is handled in multiple places because its initial signature is shared with function parsing
internal
CodeVar parse_variable_after_name(
	  ModuleFlag        mflags
	, CodeAttributes    attributes
	, CodeSpecifiers    specifiers
	, CodeType          type
	, StrC              name
)
{
	push_scope();

	Code array_expr    = parse_array_decl();
	Code expr          = { nullptr };
	Code bitfield_expr = { nullptr };

	b32 using_constructor_initializer = false;

	if ( bitfield_is_equal( u32, currtok.Flags, TF_Assign ) )
	{
		// <Attributes> <Specifiers> <ValueType> <Name> = <Expression>
		expr = parse_assignment_expression();
	}

	if ( currtok.Type == TokType::BraceCurly_Open )
	{
		Token expr_tok = currtok;

		eat( TokType::BraceCurly_Open );
		// <Attributes> <Specifiers> <ValueType> <Name> {

		s32 level = 0;
		while ( left && ( currtok.Type != TokType::BraceCurly_Close || level > 0 ) )
		{
			if ( currtok.Type == TokType::BraceCurly_Open )
				level++;

			else if ( currtok.Type == TokType::BraceCurly_Close && level > 0 )
				level--;

			eat( currtok.Type );
		}
		eat( TokType::BraceCurly_Close );

		expr_tok.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)expr_tok.Text;
		expr            = untyped_str( expr_tok );
		// <Attributes> <Specifiers> <ValueType> <Name> = { <Expression> }
	}

	if ( currtok.Type == TokType::Capture_Start )
	{
		eat( TokType:: Capture_Start);
		// <Attributes> <Specifiers> <ValueType> <Name> (

		Token expr_token = currtok;

		using_constructor_initializer = true;

		s32 level = 0;
		while ( left && ( currtok.Type != TokType::Capture_End || level > 0 ) )
		{
			if ( currtok.Type == TokType::Capture_Start )
				level++;

			else if ( currtok.Type == TokType::Capture_End && level > 0 )
				level--;

			eat( currtok.Type );
		}

		expr_token.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)expr_token.Text;
		expr              = untyped_str( expr_token );
		eat( TokType::Capture_End );
		// <Attributes> <Specifiers> <ValueType> <Name> ( <Expression> )
	}

	if ( currtok.Type == TokType::Assign_Classifer )
	{
		eat( TokType::Assign_Classifer );
		// <Attributes> <Specifiers> <ValueType> <Name> :

		Token expr_tok = currtok;

		if ( currtok.Type == TokType::Statement_End )
		{
			log_failure( "Expected expression after bitfield \n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		while ( left && currtok.Type != TokType::Statement_End )
		{
			eat( currtok.Type );
		}

		expr_tok.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)expr_tok.Text;
		bitfield_expr   = untyped_str( expr_tok );
		// <Attributes> <Specifiers> <ValueType> <Name> : <Expression>
	}

	CodeVar     next_var   = NoCode;
	Token       stmt_end   = NullToken;
	CodeComment inline_cmt = NoCode;
	if ( type )
	{
		if ( currtok.Type == TokType::Comma )
		{
			// Were dealing with a statement with more than one declaration
			// This is only handled this way if its the first declaration
			// Otherwise its looped through in parse_variable_declaration_list
			next_var = parse_variable_declaration_list();
			// <Attributes> <Specifiers> <ValueType> <Name> : <Expression>, ...
			// <Attributes> <Specifiers> <ValueType> <Name> = <Expression>, ...
			// <Attributes> <Specifiers> <ValueType> <Name> { <Expression> }, ...
		}

		// If we're dealing with a "comma-procedding then we cannot expect a statement end or inline comment
		// Any comma procedding variable will not have a type provided so it can act as a indicator to skip this
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Attributes> <Specifiers> <ValueType> <Name> : <Expression>, ...;
		// <Attributes> <Specifiers> <ValueType> <Name> = <Expression>, ...;
		// <Attributes> <Specifiers> <ValueType> <Name> { <Expression> }, ...;

		// Check for inline comment : <type> <identifier> = <expression>; // <inline comment>
		if ( left && ( currtok_noskip.Type == TokType::Comment ) && currtok_noskip.Line == stmt_end.Line )
		{
			inline_cmt = parse_comment();
			// <Attributes> <Specifiers> <ValueType> <Name> : <Expression>, ...; <InlineCmt>
			// <Attributes> <Specifiers> <ValueType> <Name> = <Expression>, ...; <InlineCmt>
			// <Attributes> <Specifiers> <ValueType> <Name> { <Expression> }, ...; <InlineCmt>
		}
	}

	using namespace ECode;

	CodeVar
	result              = (CodeVar) make_code();
	result->Type        = Variable;
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;

	// Type can be null if we're dealing with a declaration from a variable declaration-list
	if ( type )
		result->ValueType = type;

	if (array_expr )
		type->ArrExpr = array_expr;

	if ( bitfield_expr )
		result->BitfieldSize = bitfield_expr;

	if ( attributes )
		result->Attributes = attributes;

	if ( specifiers )
		result->Specs = specifiers;

	if ( expr )
		result->Value = expr;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	if ( next_var )
	{
		result->NextVar         = next_var;
		result->NextVar->Parent = result;
	}

	result->VarConstructorInit = using_constructor_initializer;

	Context.pop();
	return result;
}

/*
	Note(Ed): This does not support the following:
	* Function Pointers
*/
internal
CodeVar parse_variable_declaration_list()
{
	push_scope();

	CodeVar result   = NoCode;
	CodeVar last_var = NoCode;
	while ( check( TokType::Comma ) )
	{
		eat( TokType::Comma );
		// ,

		CodeSpecifiers specifiers = NoCode;

		while ( left && currtok.is_specifier() )
		{
			SpecifierT spec = ESpecifier::to_type( currtok );

			switch ( spec )
			{
				case ESpecifier::Const:
					if ( specifiers->NumEntries && specifiers->ArrSpecs[ specifiers->NumEntries - 1 ] != ESpecifier::Ptr )
					{
						log_failure( "Error, const specifier must come after pointer specifier for variable declaration proceeding comma\n"
						"(Parser will add and continue to specifiers, but will most likely fail to compile)\n%s"
						, Context.to_string() );

						specifiers.append( spec );
					}
				break;

				case ESpecifier::Ptr:
				case ESpecifier::Ref:
				case ESpecifier::RValue:
				break;

				default:
				{
					log_failure( "Error, invalid specifier '%s' proceeding comma\n"
					"(Parser will add and continue to specifiers, but will most likely fail to compile)\n%s"
					, currtok.Text, Context.to_string() );
					continue;
				}
				break;
			}

			// eat(currtok.Type);

			if ( specifiers )
				specifiers.append( spec );
			else
				specifiers = def_specifier( spec );
		}
		// , <Specifiers>

		StrC name = currtok;
		eat( TokType::Identifier );
		// , <Specifiers> <Name>

		CodeVar var = parse_variable_after_name( ModuleFlag::None, NoCode, specifiers, NoCode, name );
		// , <Specifiers> <Name> ...

		if ( ! result )
		{
			result.ast   = var.ast;
			last_var.ast = var.ast;
		}
		else
		{
			last_var->NextVar.ast         = var.ast;
			last_var->NextVar->Parent.ast = rcast(AST*, var.ast);
			last_var.ast                  = var.ast;
		}
	}

	Context.pop();
	return result;
}

internal
CodeClass parse_class( bool inplace_def )
{
	push_scope();
	CodeClass result = (CodeClass) parse_class_struct( TokType::Decl_Class, inplace_def );
	Context.pop();
	return result;
}

internal
CodeConstructor parse_constructor( CodeSpecifiers specifiers )
{
	push_scope();

	Token     identifier = parse_identifier();
	CodeParam params     = parse_params();
	// <Name> ( <Parameters> )

	Code        initializer_list = NoCode;
	CodeBody    body             = NoCode;
	CodeComment inline_cmt       = NoCode;

	// TODO(Ed) : Need to support postfix specifiers

	if ( check( TokType::Assign_Classifer ) )
	{
		eat( TokType::Assign_Classifer );
		// <Name> ( <Parameters> ) :

		Token initializer_list_tok = currtok;

		s32 level                  = 0;
		while ( left && ( currtok.Type != TokType::BraceCurly_Open || level > 0 ) )
		{
			if (currtok.Type == TokType::Capture_Start)
				level++;
			else if ( currtok.Type == TokType::Capture_End )
				level--;

			eat( currtok.Type );
		}

		initializer_list_tok.Length = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )initializer_list_tok.Text;
		// <Name> ( <Parameters> ) : <InitializerList>

		initializer_list = untyped_str( initializer_list_tok );

		// TODO(Ed): Constructors can have post-fix specifiers

		body = parse_function_body();
		// <Name> ( <Parameters> ) : <InitializerList> { <Body> }
	}
	else if ( check( TokType::BraceCurly_Open ) )
	{
		body = parse_function_body();
		// <Name> ( <Parameters> ) { <Body> }
	}
	else if ( check( TokType::Operator) && currtok.Text[ 0 ] == '=' )
	{
		body = parse_assignment_expression();
	}
	else
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Name> ( <Parameters> );

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
		// <Name> ( <Parameters> ); <InlineCmt>
	}

	CodeConstructor result = ( CodeConstructor )make_code();

	result->Name = get_cached_string(identifier);

	result->Specs = specifiers;

	if ( params )
		result->Params = params;

	if ( initializer_list )
		result->InitializerList = initializer_list;

	if ( body && body->Type == ECode::Function_Body )
	{
		result->Body = body;
		result->Type = ECode::Constructor;
	}
	else
		result->Type = ECode::Constructor_Fwd;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal
CodeDestructor parse_destructor( CodeSpecifiers specifiers )
{
	push_scope();

	bool has_context         = Context.Scope && Context.Scope->Prev;
	bool is_in_global_nspace = has_context && str_compare( Context.Scope->Prev->ProcName, "parse_global_nspace" ) == 0;

	if ( check( TokType::Spec_Virtual ) )
	{
		if ( specifiers )
			specifiers.append( ESpecifier::Virtual );
		else
			specifiers = def_specifier( ESpecifier::Virtual );
		eat( TokType::Spec_Virtual );
	}
	// <Virtual Specifier>

	Token prefix_identifier = NullToken;
	if (is_in_global_nspace)
		prefix_identifier = parse_identifier();

	if ( left && currtok.Text[ 0 ] == '~' )
		eat( TokType::Operator );
	else
	{
		log_failure( "Expected destructor '~' token\n%s", Context.to_string() );
		return CodeInvalid;
	}
	// <Virtual Specifier> ~

	Token       identifier = parse_identifier();
	CodeBody    body       = { nullptr };
	CodeComment inline_cmt = NoCode;
	// <Virtual Specifier> ~<Name>

	eat( TokType::Capture_Start );
	eat( TokType::Capture_End );
	// <Virtual Specifier> ~<Name>()

	bool pure_virtual = false;

	if ( check( TokType::Operator ) && currtok.Text[ 0 ] == '=' )
	{
		// <Virtual Specifier> ~<Name>() =

		bool skip_formatting = true;
		Token next = Context.Tokens.next(skip_formatting);
		if ( left && next.Text[ 0 ] == '0' )
		{
			eat( TokType::Operator );
			eat( TokType::Number );
			// <Virtual Specifier> ~<Name>() = 0

			specifiers.append( ESpecifier::Pure );
		}
		else if ( left && str_compare( next.Text, "default", sizeof("default") - 1 ) == 0)
		{
			body = parse_assignment_expression();
			// <Virtual Specifier> ~<
		}
		else
		{
			log_failure( "Pure or default specifier expected due to '=' token\n%s", Context.to_string() );
			return CodeInvalid;
		}

		pure_virtual = true;
	}

	if ( ! pure_virtual && check( TokType::BraceCurly_Open ) )
		body = parse_function_body();
	// <Virtual Specifier> ~<Name>() { ... }
	else
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Virtual Specifier> ~<Name>() <Pure Specifier>;

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
		// <Virtual Specifier> ~<Name>() <Pure Specifier>; <InlineCmt>
	}

	CodeDestructor result = ( CodeDestructor )make_code();

	if ( prefix_identifier )
	{
		prefix_identifier.Length += 1 + identifier.Length;
		result->Name = get_cached_string( prefix_identifier );
	}

	if ( specifiers )
		result->Specs = specifiers;

	if ( body && body->Type == ECode::Function_Body )
	{
		result->Body = body;
		result->Type = ECode::Destructor;
	}
	else
		result->Type = ECode::Destructor_Fwd;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal
CodeEnum parse_enum( bool inplace_def )
{
	using namespace ECode;
	push_scope();

	SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
	s32        NumSpecifiers = 0;

	CodeAttributes attributes = { nullptr };

	Token    name       = { nullptr, 0, TokType::Invalid };
	Code     array_expr = { nullptr };
	CodeType type       = { nullptr };

	char  entries_code[ kilobytes(128) ] { 0 };
	s32   entries_length = 0;

	bool is_enum_class = false;

	eat( TokType::Decl_Enum );
	// enum

	if ( currtok.Type == TokType::Decl_Class )
	{
		eat( TokType::Decl_Class);
		is_enum_class = true;
		// enum class
	}

	attributes = parse_attributes();
	// enum <class> <Attributes>

	if ( check( TokType::Identifier ) )
	{
		name = currtok;
		Context.Scope->Name = currtok;
		eat( TokType::Identifier );
	}
	// enum <class> <Attributes> <Name>

	if ( currtok.Type == TokType::Assign_Classifer )
	{
		eat( TokType::Assign_Classifer );
		// enum <class> <Attributes> <Name> :

		type = parse_type();
		if ( type == Code::Invalid )
		{
			log_failure( "Failed to parse enum classifier\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}
		// enum <class> <Attributes> <Name> : <UnderlyingType>
	}

	CodeBody body = { nullptr };

	if ( currtok.Type == TokType::BraceCurly_Open )
	{
		body       = (CodeBody) make_code();
		body->Type = ECode::Enum_Body;

		eat( TokType::BraceCurly_Open );
		// enum <class> <Attributes> <Name> : <UnderlyingType> {

		Code member = CodeInvalid;

		bool expects_entry = true;
		while ( left && currtok_noskip.Type != TokType::BraceCurly_Close )
		{
			if ( ! expects_entry )
			{
				log_failure( "Did not expect an entry after last member of enum body.\n%s", Context.to_string() );
				Context.pop();
				break;
			}

			if ( currtok_noskip.Type == TokType::Preprocess_Hash )
				eat( TokType::Preprocess_Hash );

			switch ( currtok_noskip.Type )
			{
				case TokType::NewLine:
					member = untyped_str( currtok_noskip );
					eat( TokType::NewLine );
				break;

				case TokType::Comment:
					member = parse_comment();
				break;

				case TokType::Preprocess_Define:
					member = parse_define();
					// #define
				break;

				case TokType::Preprocess_If:
				case TokType::Preprocess_IfDef:
				case TokType::Preprocess_IfNotDef:
				case TokType::Preprocess_ElIf:
					member = parse_preprocess_cond();
					// #<if, ifdef, ifndef, elif> ...
				break;

				case TokType::Preprocess_Else:
					member = preprocess_else;
					eat( TokType::Preprocess_Else );
				break;

				case TokType::Preprocess_EndIf:
					member = preprocess_endif;
					eat( TokType::Preprocess_EndIf );
				break;

				case TokType::Preprocess_Macro:
					member = parse_simple_preprocess( TokType::Preprocess_Macro );
					// <Macro>
				break;

				case TokType::Preprocess_Pragma:
					member = parse_pragma();
					// #pragma
				break;

				case TokType::Preprocess_Unsupported:
					member = parse_simple_preprocess( TokType::Preprocess_Unsupported );
					// #<UNSUPPORTED>
				break;

				default:
					Token entry = currtok;

					eat( TokType::Identifier);
					// <Name>

					if ( currtok.Type == TokType::Operator && currtok.Text[0] == '=' )
					{
						eat( TokType::Operator );
						// <Name> =

						while ( currtok_noskip.Type != TokType::Comma && currtok_noskip.Type != TokType::BraceCurly_Close )
						{
							eat( currtok_noskip.Type );
						}
					}
					// <Name> = <Expression>

					// Unreal UMETA macro support
					if ( currtok.Type == TokType::Preprocess_Macro )
					{
						eat( TokType::Preprocess_Macro );
						// <Name> = <Expression> <Macro>
					}

					if ( currtok.Type == TokType::Comma )
					{
						eat( TokType::Comma );
						// <Name> = <Expression> <Macro>,
					}

					// Consume inline comments
					// if ( currtok.Type == TokType::Comment && prevtok.Line == currtok.Line )
					// {
						// eat( TokType::Comment );
						// <Name> = <Expression> <Macro>, // <Inline Comment>
					// }

					entry.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)entry.Text;

					member = untyped_str( entry );
				break;
			}

			if ( member == Code::Invalid )
			{
				log_failure( "Failed to parse member\n%s", Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}

			body.append( member );
		}

		eat( TokType::BraceCurly_Close );
		// enum <class> <Attributes> <Name> : <UnderlyingType> { <Body> }
	}

	CodeComment inline_cmt = NoCode;

	if ( ! inplace_def )
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// enum <class> <Attributes> <Name> : <UnderlyingType> { <Body> };

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
			// enum <class> <Attributes> <Name> : <UnderlyingType> { <Body> }; <InlineCmt>
	}

	using namespace ECode;

	CodeEnum
	result = (CodeEnum) make_code();

	if ( body.ast )
	{
		result->Type = is_enum_class ? Enum_Class : Enum;
		result->Body = body;
	}
	else
	{
		result->Type = is_enum_class ? Enum_Class_Fwd : Enum_Fwd;
	}

	result->Name = get_cached_string( name );

	if ( attributes )
		result->Attributes = attributes;

	if ( type )
		result->UnderlyingType = type;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal inline
CodeBody parse_export_body()
{
	push_scope();
	CodeBody result = parse_global_nspace( ECode::Export_Body );
	Context.pop();
	return result;
}

internal inline
CodeBody parse_extern_link_body()
{
	push_scope();
	CodeBody result = parse_global_nspace( ECode::Extern_Linkage_Body );
	Context.pop();
	return result;
}

internal
CodeExtern parse_extern_link()
{
	push_scope();

	eat( TokType::Decl_Extern_Linkage );
	// extern

	Token name = currtok;
	eat( TokType::String );
	// extern "<Name>"

	name.Text   += 1;
	name.Length -= 1;

	CodeExtern
	result       = (CodeExtern) make_code();
	result->Type = ECode::Extern_Linkage;
	result->Name = get_cached_string( name );

	Code entry = parse_extern_link_body();
	if ( entry == Code::Invalid )
	{
		log_failure( "Failed to parse body\n%s", Context.to_string() );
		Context.pop();
		return result;
	}
	// extern "<Name>" { <Body> }

	result->Body = entry;

	Context.pop();
	return result;
}

internal
CodeFriend parse_friend()
{
	using namespace ECode;
	push_scope();

	eat( TokType::Decl_Friend );
	// friend

	CodeFn function = { nullptr };

	// Type declaration or return type
	CodeType type = parse_type();
	if ( type == Code::Invalid )
	{
		Context.pop();
		return CodeInvalid;
	}
	// friend <Type>

	// Funciton declaration
	if ( currtok.Type == TokType::Identifier )
	{
		// Name
		Token name          = parse_identifier();
		Context.Scope->Name = name;
		// friend <ReturnType> <Name>

		function = parse_function_after_name( ModuleFlag::None, NoCode, NoCode, type, name );

		// Parameter list
		// CodeParam params = parse_params();
		// friend <ReturnType> <Name> ( <Parameters> )

		// function             = make_code();
		// function->Type       = Function_Fwd;
		// function->Name       = get_cached_string( name );
		// function->ReturnType = type;

		// if ( params )
			// function->Params = params;
	}

	CodeComment inline_cmt = NoCode;
	if ( function && function->Type == ECode::Function_Fwd )
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// friend <Type>;
		// friend <ReturnType> <Name> ( <Parameters> );

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
		// friend <Type>; <InlineCmt>
		// friend <ReturnType> <Name> ( <Parameters> ); <InlineCmt>
	}

	CodeFriend result = ( CodeFriend )make_code();
	result->Type      = Friend;

	if ( function )
		result->Declaration = function;
	else
		result->Declaration = type;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal
CodeFn parse_function()
{
	push_scope();

	SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
	s32        NumSpecifiers = 0;

	CodeAttributes attributes = { nullptr };
	CodeSpecifiers specifiers = { nullptr };
	ModuleFlag     mflags     = ModuleFlag::None;

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <export>

	attributes = parse_attributes();
	// <export> <Attributes>

	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		switch ( spec )
		{
			case ESpecifier::Const:
			case ESpecifier::Consteval:
			case ESpecifier::Constexpr:
			case ESpecifier::External_Linkage:
			case ESpecifier::ForceInline:
			case ESpecifier::Inline:
			case ESpecifier::NeverInline:
			case ESpecifier::Static:
			break;

			default:
				log_failure( "Invalid specifier %s for functon\n%s", ESpecifier::to_str(spec), Context.to_string() );
				Context.pop();
				return CodeInvalid;
		}

		if ( spec == ESpecifier::Const )
			continue;

		specs_found[NumSpecifiers] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}

	if ( NumSpecifiers )
	{
		specifiers = def_specifiers( NumSpecifiers, specs_found );
	}
	// <export> <Attributes> <Specifiers>

	CodeType ret_type = parse_type();
	if ( ret_type == Code::Invalid )
	{
		Context.pop();
		return CodeInvalid;
	}
	// <export> <Attributes> <Specifiers> <ReturnType>

	Token name = parse_identifier();
	Context.Scope->Name = name;
	if ( ! name )
	{
		Context.pop();
		return CodeInvalid;
	}
	// <export> <Attributes> <Specifiers> <ReturnType> <Name>

	CodeFn result = parse_function_after_name( mflags, attributes, specifiers, ret_type, name );
	// <export> <Attributes> <Specifiers> <ReturnType> <Name> ...

	Context.pop();
	return result;
}

internal
CodeNS parse_namespace()
{
	push_scope();

	eat( TokType::Decl_Namespace );
	// namespace

	Token name = parse_identifier();
	Context.Scope->Name = name;
	// namespace <Name>

	CodeBody body = parse_global_nspace( ECode::Namespace_Body );
	if ( body == Code::Invalid )
	{
		Context.pop();
		return CodeInvalid;
	}
	// namespace <Name> { <Body> }

	CodeNS
	result       = (CodeNS) make_code();
	result->Type = ECode::Namespace;
	result->Name = get_cached_string( name );

	result->Body = body;

	Context.pop();
	return result;
}

internal
CodeOperator parse_operator()
{
	push_scope();

	CodeAttributes attributes = { nullptr };
	CodeSpecifiers specifiers = { nullptr };
	ModuleFlag     mflags     = ModuleFlag::None;

	SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
	s32        NumSpecifiers = 0;

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <export>

	attributes = parse_attributes();
	// <export> <Attributes>

	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		switch ( spec )
		{
			case ESpecifier::Const:
			case ESpecifier::Constexpr:
			case ESpecifier::ForceInline:
			case ESpecifier::Inline:
			case ESpecifier::NeverInline:
			case ESpecifier::Static:
			break;

			default:
				log_failure( "Invalid specifier " "%s" " for operator\n%s", ESpecifier::to_str(spec), Context.to_string() );
				Context.pop();
				return CodeInvalid;
		}

		if ( spec == ESpecifier::Const )
			continue;

		specs_found[NumSpecifiers] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}

	if ( NumSpecifiers )
	{
		specifiers = def_specifiers( NumSpecifiers, specs_found );
	}
	// <export> <Attributes> <Specifiers>

	// Parse Return Type
	CodeType ret_type = parse_type();
	// <export> <Attributes> <Specifiers> <ReturnType>

	CodeOperator result = parse_operator_after_ret_type( mflags, attributes, specifiers, ret_type );
	// <export> <Attributes> <Specifiers> <ReturnType> ...

	Context.pop();
	return result;
}

internal
CodeOpCast parse_operator_cast( CodeSpecifiers specifiers )
{
	push_scope();

	// Operator's namespace if not within same class.
	Token name = NullToken;
	if ( check( TokType::Identifier ) )
	{
		name = currtok;
		while ( left && currtok.Type == TokType::Identifier )
		{
			eat( TokType::Identifier );
			// <Specifiers> <Qualifier>

			if ( currtok.Type == TokType::Access_StaticSymbol )
				eat( TokType::Access_StaticSymbol );
				// <Specifiers> <Qualifier> ::
		}
		// <Specifiers> <Qualifier> :: ...

		name.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)name.Text;
	}

	eat( TokType::Decl_Operator );
	// <Specifiers> <Qualifier> :: ... operator

	Code type = parse_type();
	// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>

	Context.Scope->Name = { type->Name.Data, type->Name.length() };

	eat( TokType::Capture_Start );
	eat( TokType::Capture_End );
	// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>()

	// TODO(Ed) : operator cast can have const, volatile, l-value, r-value noexecept qualifying specifiers.
	if ( check(TokType::Spec_Const))
	{
		if ( specifiers.ast == nullptr )
			specifiers = def_specifier( ESpecifier::Const );

		else
			specifiers.append( ESpecifier::Const );

		eat( TokType::Spec_Const );
	}
	// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>() <const>

	Code        body       = NoCode;
	CodeComment inline_cmt = NoCode;

	if ( check( TokType::BraceCurly_Open) )
	{
		eat( TokType::BraceCurly_Open );
		// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>() <const> {

		Token body_str = currtok;

		s32 level = 0;
		while ( left && ( currtok.Type != TokType::BraceCurly_Close || level > 0 ) )
		{
			if ( currtok.Type == TokType::BraceCurly_Open )
				level++;

			else if ( currtok.Type == TokType::BraceCurly_Close )
				level--;

			eat( currtok.Type );
		}
		body_str.Length = ( (sptr)prevtok.Text + prevtok.Length ) - (sptr)body_str.Text;

		eat( TokType::BraceCurly_Close );
		// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>() <const> { <Body> }

		body = untyped_str( body_str );
	}
	else
	{
		Token stmt_end = currtok;
		eat( TokType::Statement_End );
		// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>() <const>;

		if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
			inline_cmt = parse_comment();
			// <Specifiers> <Qualifier> :: ... operator <UnderlyingType>() <const>; <InlineCmt>
	}

	CodeOpCast result = (CodeOpCast) make_code();

	if ( name )
		result->Name = get_cached_string( name );

	if (body)
	{
		result->Type = ECode::Operator_Cast;
		result->Body = body;
	}
	else
	{
		result->Type = ECode::Operator_Cast_Fwd;
	}

	if ( specifiers )
		result->Specs = specifiers;

	result->ValueType = type;

	Context.pop();
	return result;
}

internal inline
CodeStruct parse_struct( bool inplace_def )
{
	push_scope();
	CodeStruct result = (CodeStruct) parse_class_struct( TokType::Decl_Struct, inplace_def );
	Context.pop();
	return result;
}

internal
CodeTemplate parse_template()
{
#define UseTemplateCapture true

	push_scope();

	ModuleFlag mflags = ModuleFlag::None;

	if ( check( TokType::Module_Export ) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <export> template

	eat( TokType::Decl_Template );
	// <export> template

	Code params = parse_params( UseTemplateCapture );
	if ( params == Code::Invalid )
	{
		Context.pop();
		return CodeInvalid;
	}
	// <export> template< <Parameters> >

	Code definition = { nullptr };

	while ( left )
	{
		if ( check( TokType::Decl_Class ) )
		{
			definition = parse_class();
			// <export> template< <Parameters> > class ...
			break;
		}

		if ( check( TokType::Decl_Struct ) )
		{
			definition = parse_struct();
			// <export> template< <Parameters> > struct ...
			break;
		}

		if ( check( TokType::Decl_Union ) )
		{
			definition = parse_union();
			// <export> template< <Parameters> > union ...
			break;
		}

		if ( check( TokType::Decl_Using ) )
		{
			definition = parse_using();
			// <export> template< <Parameters> > using ...
			break;
		}

		// Its either a function or a variable
		Token name                = { nullptr, 0, TokType::Invalid };

		CodeAttributes attributes = { nullptr };
		CodeSpecifiers specifiers = { nullptr };

		bool expects_function     = false;

		SpecifierT specs_found[ 16 ] { ESpecifier::NumSpecifiers };
		s32        NumSpecifiers = 0;

		attributes = parse_attributes();
		// <export> template< <Parameters> > <Attributes>

		// Specifiers Parsing
		{
			while ( left && currtok.is_specifier() )
			{
				SpecifierT spec = ESpecifier::to_type( currtok );

				switch ( spec )
				{
					case ESpecifier::Const :
					case ESpecifier::Constexpr :
					case ESpecifier::Constinit :
					case ESpecifier::External_Linkage :
					case ESpecifier::Global :
					case ESpecifier::Inline :
					case ESpecifier::ForceInline :
					case ESpecifier::Local_Persist :
					case ESpecifier::Mutable :
					case ESpecifier::Static :
					case ESpecifier::Thread_Local :
					case ESpecifier::Volatile :
						break;

					case ESpecifier::Consteval :
						expects_function = true;
						break;

					default :
						log_failure( "Invalid specifier %s for variable or function\n%s", ESpecifier::to_str( spec ), Context.to_string() );
						Context.pop();
						return CodeInvalid;
				}

				// Ignore const it will be handled by the type
				if ( spec == ESpecifier::Const )
					break;

				specs_found[ NumSpecifiers ] = spec;
				NumSpecifiers++;
				eat( currtok.Type );
			}

			if ( NumSpecifiers )
			{
				specifiers = def_specifiers( NumSpecifiers, specs_found );
			}
			// <export> template< <Parameters> > <Attributes> <Specifiers>
		}


		bool has_context         = Context.Scope && Context.Scope->Prev;
		bool is_in_global_nspace = has_context && str_compare( Context.Scope->Prev->ProcName, "parse_global_nspace" ) == 0;

		// Possible constructor implemented at global file scope.
		if (is_in_global_nspace)
		{
			Code constructor_destructor = parse_global_nspace_constructor_destructor( specifiers );
			if ( constructor_destructor )
			{
				definition = constructor_destructor;
				// <Attributes> <Specifiers> <Name> :: <Name> <Type> () { ... }
				break;
			}
		}

		// Possible user Defined operator casts
		if (is_in_global_nspace)
		{
			bool found_operator_cast_outside_class_implmentation = false;
			s32  idx = Context.Tokens.Idx;

			for ( ; idx < Context.Tokens.Arr.num(); idx++ )
			{
				Token tok = Context.Tokens[ idx ];

				if ( tok.Type == TokType::Identifier )
				{
					idx++;
					tok = Context.Tokens[ idx ];
					if ( tok.Type == TokType::Access_StaticSymbol )
						continue;

					break;
				}

				if ( tok.Type == TokType::Decl_Operator )
					found_operator_cast_outside_class_implmentation = true;

				break;
			}

			if ( found_operator_cast_outside_class_implmentation )
			{
				definition = parse_operator_cast( specifiers );
				// <Attributes> <Specifiers> <Name> :: operator <Type> () { ... }
				break;
			}
		}

		definition = parse_operator_function_or_variable( expects_function, attributes, specifiers );
		// <export> template< <Parameters> > <Attributes> <Specifiers> ...
		break;
	}

	CodeTemplate result = ( CodeTemplate )make_code();
	result->Type        = ECode::Template;
	result->Params      = params;
	result->Declaration = definition;
	result->ModuleFlags = mflags;

	Context.pop();
	return result;
#undef UseTemplateCapture
}

/*
	This is a mess, but it works
	Parsing typename is arguably one of the worst aspects of C/C++.
	This is an effort to parse it without a full blown or half-blown compliant parser.

	Recursive function typenames are not supported, if they are used expect it to serailize just fine, but validation with AST::is_equal
	will not be possible if two ASTs share the same definiton but the formatting is slightly different:
	AST_1->Name: (* A    ( int   (*)    (short a,unsigned b,long c) ) )
	AST_2->Name: (* A       ( int(*)(short a, unsigned b, long c) ) )

	The excess whitespace cannot be stripped however, because there is no semantic awareness within the first capture group.
*/
internal
CodeType parse_type( bool from_template, bool* typedef_is_function )
{
	push_scope();

	Token context_tok = prevtok;

	SpecifierT specs_found[ 16 ] { ESpecifier::NumSpecifiers };
	s32        NumSpecifiers = 0;

	Token name               = { nullptr, 0, TokType::Invalid };

	// Attributes are assumed to be before the type signature
	CodeAttributes attributes = parse_attributes();
	// <Attributes>

	// Prefix specifiers
	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		if ( spec != ESpecifier::Const )
		{
			log_failure( "Error, invalid specifier used in type definition: %s\n%s", currtok.Text, Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		specs_found[ NumSpecifiers ] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}
	// <Attributes> <Specifiers>

	if ( left == 0 )
	{
		log_failure( "Error, unexpected end of type definition\n%s", Context.to_string() );
		Context.pop();
		return CodeInvalid;
	}

	if ( from_template && currtok.Type == TokType::Decl_Class )
	{
		// If a value's type is being parsed from a template, class can be used instead of typename.
		name = currtok;
		eat(TokType::Decl_Class);
		// <class>
	}

	// All kinds of nonsense can makeup a type signature, first we check for a in-place definition of a class, enum, struct, or union
	else if ( currtok.Type == TokType::Decl_Class || currtok.Type == TokType::Decl_Enum || currtok.Type == TokType::Decl_Struct
			|| currtok.Type == TokType::Decl_Union )
	{
		eat( currtok.Type );
		// <Attributes> <Specifiers> <class, enum, struct, union>

		name = parse_identifier();

		// name.Length = ( ( sptr )currtok.Text + currtok.Length ) - ( sptr )name.Text;
		// eat( TokType::Identifier );
		Context.Scope->Name = name;
		// <Attributes> <Specifiers> <class, enum, struct, union> <Name>
	}

// Decltype draft implementaiton
#if 0
else if ( currtok.Type == TokType::DeclType )
{
	// Will have a capture and its own parsing rules, were going to just shove everything in a string (for now).
	name = currtok;
	eat( TokType::DeclType );
	// <Attributes> <Specifiers> decltype

	eat( TokType::Capture_Start );
	while ( left && currtok.Type != TokType::Capture_End )
	{
		if ( currtok.Type == TokType::Capture_Start )
			level++;

		if ( currtok.Type == TokType::Capture_End )
			level--;

		eat( currtok.Type );
	}
	eat( TokType::Capture_End );

	name.Length = ( (sptr)currtok.Text + currtok.Length ) - (sptr)name.Text;
	Context.Scope->Name = name;
	// <Attributes> <Specifiers> decltype( <Expression > )
}
#endif

	// Check if native type keywords are used, eat them for the signature.
	// <attributes> <specifiers> <native types ...> ...
	else if ( currtok.Type >= TokType::Type_Unsigned && currtok.Type <= TokType::Type_MS_W64 )
	{
		// TODO(Ed) : Review this... Its necessary for parsing however the algo's path to this is lost...
		name = currtok;
		eat( currtok.Type );

		while ( left && currtok.Type >= TokType::Type_Unsigned && currtok.Type <= TokType::Type_MS_W64 )
		{
			eat( currtok.Type );
		}

		name.Length = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )name.Text;
		// <Attributes> <Specifiers> <Compound type expression>
	}
	else if ( currtok.Type == TokType::Type_Typename )
	{
		name = currtok;
		eat(TokType::Type_Typename);
		// <typename>

		if ( ! from_template )
		{
			name                = parse_identifier();
			Context.Scope->Name = name;
			if ( ! name )
			{
				log_failure( "Error, failed to type signature\n%s", Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}
		}
	}

	// The usual Identifier type signature that may have namespace qualifiers
	else
	{
		name                = parse_identifier();
		Context.Scope->Name = name;
		if ( ! name )
		{
			log_failure( "Error, failed to type signature\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}
		// <Attributes> <Specifiers> <Qualifier ::> <Identifier>
		// <Attributes> <Specifiers> <Identifier>
	}

	// Suffix specifiers for typename.
	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		if ( spec != ESpecifier::Const && spec != ESpecifier::Ptr && spec != ESpecifier::Ref && spec != ESpecifier::RValue )
		{
			log_failure( "Error, invalid specifier used in type definition: %s\n%s", currtok.Text, Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		specs_found[ NumSpecifiers ] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}

#ifdef GEN_USE_NEW_TYPENAME_PARSING
	if ( NumSpecifiers )
	{
		specifiers    = def_specifiers( NumSpecifiers, specs_found );
		NumSpecifiers = 0;
	}
#endif
	// <Attributes> <Specifiers> <Identifier> <Specifiers>

	// For function type signatures
	CodeType  return_type = NoCode;
	CodeParam params      = NoCode;

#ifdef GEN_USE_NEW_TYPENAME_PARSING
	CodeParam params_nested = NoCode;
#endif

	bool   is_function_typename = false;
	Token* last_capture         = nullptr;
	{
		Token* scanner = Context.Tokens.Arr + Context.Tokens.Idx;

		// An identifier being within a typename's signature only occurs if were parsing a typename for a typedef.
		if ( typedef_is_function && scanner->Type == TokType::Identifier )
		{
			is_function_typename = true;
			++scanner;
		}
		is_function_typename = scanner->Type == TokType::Capture_Start;

		Token* first_capture = scanner;
		if ( is_function_typename )
		{
			// Go to the end of the signature
			while ( scanner->Type != TokType::Statement_End && scanner->Type != TokType::BraceCurly_Open )
				++scanner;

			// Go back to the first capture start found
			while ( scanner->Type != TokType::Capture_Start )
				--scanner;

			last_capture = scanner;
		}

		bool has_context   = Context.Scope && Context.Scope->Prev;
		bool is_for_opcast = has_context && str_compare( Context.Scope->Prev->ProcName, "parse_operator_cast" ) == 0;
		if ( is_for_opcast && is_function_typename && last_capture )
		{
			// If we're parsing for an operator cast, having one capture start is not enough
			// we need to make sure that the capture is not for the cast definition.
			is_function_typename = false;

			if ( last_capture == first_capture )
			{
				// The capture start in question is the first capture start, this is not a function typename.
				is_function_typename = false;
			}
		}
	}

	if ( is_function_typename )
	{
		// We're dealing with a function typename.
		// By this point, decltype should have been taken care of for return type, along with any all its specifiers

		// The previous information with exception to attributes will be considered the return type.
		return_type       = ( CodeType )make_code();
		return_type->Type = ECode::Typename;

		// String
		// name_stripped = String::make( GlobalAllocator, name );
		// name_stripped.strip_space();
		return_type->Name = get_cached_string( name );

#ifdef GEN_USE_NEW_TYPENAME_PARSING
		if ( specifiers )
		{
			return_type->Specs = specifiers;
			specifiers         = nullptr;
		}

#else
		if ( NumSpecifiers )
			return_type->Specs = def_specifiers( NumSpecifiers, ( SpecifierT* )specs_found );

		// Reset specifiers, the function itself will have its own suffix specifiers possibly.
		NumSpecifiers = 0;
#endif
		// <Attributes> <ReturnType>

		name = { nullptr, 0, TokType::Invalid };

		// The next token can either be a capture for the identifier or it could be the identifier exposed.
		if ( ! check( TokType::Capture_Start ) )
		{
			// Started with an identifier immeidately, which means its of the format: <ReturnType> <identifier> <capture>;
			name = parse_identifier();
		}
		// <Attributes> <ReturnType> <Identifier>

		// If the next token is a capture start and is not the last capture, then we're dealing with function typename whoose identifier is within the
		// capture.
		else if ( ( Context.Tokens.Arr + Context.Tokens.Idx ) != last_capture )
		{
			// WIP : Possible alternative without much pain...
			// If this were to be parsed properly...
			// Eat Capture Start
			// Deal with possible binding specifiers (*, &, &&) and modifiers on those bindings (const, volatile)
			// Parse specifiers for the typename with an optional identifier,
			// we can shove these specific specifiers into a specs, and then leave the suffix ones for a separate member of the AST.
			// Parse immeidate capture which would be with parse_params()
			// Eat Capture End
#ifdef GEN_USE_NEW_TYPENAME_PARSING
			eat( TokType::Capture_Start );
			// <Attributes> <ReturnType> (

			// Binding specifiers
			while ( left && currtok.is_specifier() )
			{
				SpecifierT spec = ESpecifier::to_type( currtok );

				if ( spec != ESpecifier::Ptr && spec != ESpecifier::Ref && spec != ESpecifier::RValue )
				{
					log_failure( "Error, invalid specifier used in type definition: %s\n%s", currtok.Text, Context.to_string() );
					Context.pop();
					return CodeInvalid;
				}

				specs_found[ NumSpecifiers ] = spec;
				NumSpecifiers++;
				eat( currtok.Type );
			}

			if ( NumSpecifiers )
			{
				specifiers = def_specifiers( NumSpecifiers, specs_found );
			}
			NumSpecifiers = 0;
			// <Attributes> <ReturnType> ( <Specifiers>

			if ( check( TokType::Identifier ) )
				name = parse_identifier();
			// <Attributes> <ReturnType> ( <Specifiers> <Identifier>

			// Immeidate parameters

			if ( check( TokType::Capture_Start ) )
				params_nested = parse_params();
			// <Attributes> <ReturnType> ( <Specifiers> <Identifier> ( <Parameters> )

			eat( TokType::Capture_End );
			// <Attributes> <ReturnType> ( <Specifiers> <Identifier> ( <Parameters> ) )

#else
			// Starting immediatley with a capture, most likely declaring a typename for a member function pointer.
			// Everything within this capture will just be shoved into the name field including the capture tokens themselves.
			name = currtok;

			eat( TokType::Capture_Start );
			// <Attributes> <ReturnType> (

			s32 level = 0;
			while ( left && ( currtok.Type != TokType::Capture_End || level > 0 ) )
			{
				if ( currtok.Type == TokType::Capture_Start )
					level++;

				if ( currtok.Type == TokType::Capture_End )
					level--;

				eat( currtok.Type );
			}
			eat( TokType::Capture_End );
			// <Attributes> <ReturnType> ( <Expression> )

			name.Length = ( ( sptr )prevtok.Text + prevtok.Length ) - ( sptr )name.Text;
#endif
		}

		// Were now dealing with the parameters of the function
		params = parse_params();
		// <Attributes> <ReturnType> <All Kinds of nonsense> ( <Parameters> )

		// Look for suffix specifiers for the function
		while ( left && currtok.is_specifier() )
		{
			SpecifierT spec = ESpecifier::to_type( currtok );

			if ( spec != ESpecifier::Const
					// TODO : Add support for NoExcept, l-value, volatile, l-value, etc
					// && spec != ESpecifier::NoExcept
					&& spec != ESpecifier::RValue )
			{
				log_failure( "Error, invalid specifier used in type definition: %s\n%s", currtok.Text, Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}

			specs_found[ NumSpecifiers ] = spec;
			NumSpecifiers++;
			eat( currtok.Type );
		}

#ifdef GEN_USE_NEW_TYPENAME_PARSING
		if ( NumSpecifiers )
		{
			func_suffix_specs = def_specifiers( NumSpecifiers, specs_found );
			NumSpecifiers     = 0;
		}
#endif
		// <Attributes> <ReturnType> <All Kinds of nonsense> ( <Parameters> ) <Specifiers>
	}
	// <Attributes> <All Kinds of nonsense>

	bool is_param_pack = false;
	if ( check( TokType::Varadic_Argument ) )
	{
		is_param_pack = true;
		eat( TokType::Varadic_Argument );
		// <Attributes> <All kinds of nonsense> ...
	}

	using namespace ECode;

	CodeType result = ( CodeType )make_code();
	result->Type    = Typename;
	// result->Token = Context.Scope->Start;

	// Need to wait until were using the new parsing method to do this.
	String name_stripped = strip_formatting( name, strip_formatting_dont_preserve_newlines );

	// name_stripped.strip_space();

#ifdef GEN_USE_NEW_TYPENAME_PARSING
	if ( params_nested )
	{
		name_stripped.append( params_nested->to_string() );
	}
#endif

	result->Name = get_cached_string( name_stripped );

	if ( attributes )
		result->Attributes = attributes;

#ifdef GEN_USE_NEW_TYPENAME_PARSING
	if ( specifiers )
	{
		result->Specs = specifiers;
	}

	if ( func_suffix_specs )
	{
		result->FuncSuffixSpecs = func_suffix_specs;
	}
#else
	if ( NumSpecifiers )
	{
		Code specifiers = def_specifiers( NumSpecifiers, ( SpecifierT* )specs_found );
		result->Specs   = specifiers;
	}
#endif

	if ( is_param_pack )
		result->IsParamPack = true;

	// These following are only populated if its a function typename
	if ( return_type )
	{
		result->ReturnType = return_type;

		if ( typedef_is_function )
			*typedef_is_function = true;
	}

	if ( params )
		result->Params = params;

	Context.pop();
	return result;
}

internal
CodeTypedef parse_typedef()
{
	push_scope();

	bool  is_function = false;
	Token name        = { nullptr, 0, TokType::Invalid };
	Code  array_expr  = { nullptr };
	Code  type        = { nullptr };

	ModuleFlag mflags = ModuleFlag::None;

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <ModuleFlags>

	eat( TokType::Decl_Typedef );
	// <ModuleFlags> typedef

	constexpr bool from_typedef = true;

#if GEN_PARSER_DISABLE_MACRO_TYPEDEF
	if ( false )
#else
	if ( check( TokType::Preprocess_Macro ))
#endif
	{
		type = t_empty;
		name = currtok;
		Context.Scope->Name = name;
		eat( TokType::Preprocess_Macro );
		// <ModuleFalgs> typedef <Preprocessed_Macro>
	}
	else
	{
		bool is_complicated =
				currtok.Type == TokType::Decl_Enum
			||	currtok.Type == TokType::Decl_Class
			||	currtok.Type == TokType::Decl_Struct
			||	currtok.Type == TokType::Decl_Union;

		// This code is highly correlated with parse_complicated_definition
		if ( is_complicated )
		{
			TokArray tokens = Context.Tokens;

			s32 idx = tokens.Idx;
			s32 level = 0;
			for ( ; idx < tokens.Arr.num(); idx ++ )
			{
				if ( tokens[idx].Type == TokType::BraceCurly_Open )
					level++;

				if ( tokens[idx].Type == TokType::BraceCurly_Close )
					level--;

				if ( level == 0 && tokens[idx].Type == TokType::Statement_End )
					break;
			}

			if ( (idx - 2 ) == tokens.Idx )
			{
				// Its a forward declaration only
				type = parse_forward_or_definition( currtok.Type, from_typedef );
				// <ModuleFalgs> typedef <UnderlyingType: Forward Decl>
			}

			Token tok = tokens[ idx - 1 ];
			if ( tok.Type == TokType::Identifier )
			{
				tok = tokens[ idx - 2 ];

				bool is_indirection = tok.Type == TokType::Ampersand
				||                    tok.Type == TokType::Star;

				bool ok_to_parse = false;

				if ( tok.Type == TokType::BraceCurly_Close )
				{
					// Its an inplace definition
					// typdef <which> <type_identifier> { ... } <identifier>;
					ok_to_parse = true;
				}
				else if ( tok.Type == TokType::Identifier && tokens[ idx - 3 ].Type == TokType::Decl_Struct )
				{
					// Its a variable with type ID using struct namespace.
					// <which> <type_identifier> <identifier>;
					ok_to_parse = true;
				}
				else if ( is_indirection )
				{
					// Its a indirection type with type ID using struct namespace.
					// <which> <type_identifier>* <identifier>;
					ok_to_parse = true;
				}

				if ( ! ok_to_parse )
				{
					log_failure( "Unsupported or bad member definition after struct declaration\n%s", Context.to_string() );
					Context.pop();
					return CodeInvalid;
				}

				// TODO(Ed) : I'm not sure if I have to use parse_type here, I'd rather not as that would complicate parse_type.
				// type = parse_type();
				type = parse_forward_or_definition( currtok.Type, from_typedef );
				// <ModuleFalgs> typedef <UnderlyingType>
			}
			else if ( tok.Type == TokType::BraceCurly_Close )
			{
				// Its a definition
				// <which> { ... };
				type = parse_forward_or_definition( currtok.Type, from_typedef );
				// <ModuleFalgs> typedef <UnderlyingType>
			}
			else if ( tok.Type == TokType::BraceSquare_Close)
			{
				// Its an array definition
				// <which> <type_identifier> <identifier> [ ... ];
				type = parse_type();
				// <ModuleFalgs> typedef <UnderlyingType>
			}
			else
			{
				log_failure( "Unsupported or bad member definition after struct declaration\n%s", Context.to_string() );
				Context.pop();
				return CodeInvalid;
			}
		}
		else
		{
			bool from_template = false;
			type = parse_type( from_template, &is_function );
			// <ModuleFalgs> typedef <UnderlyingType>
		}

		if ( check( TokType::Identifier ) )
		{
			name = currtok;
			eat( TokType::Identifier );
			// <ModuleFalgs> typedef <UnderlyingType> <Name>
		}
		else if ( ! is_function )
		{
			log_failure( "Error, expected identifier for typedef\n%s", Context.to_string() );
			Context.pop();
			return CodeInvalid;
		}

		array_expr = parse_array_decl();
		// <UnderlyingType> + <ArrayExpr>
	}

	Token stmt_end = currtok;
	eat( TokType::Statement_End );
	// <ModuleFalgs> typedef <UnderlyingType> <Name>;

	CodeComment inline_cmt = NoCode;
	if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
		inline_cmt = parse_comment();
		// <ModuleFalgs> typedef <UnderlyingType> <Name> <ArrayExpr>; <InlineCmt>

	using namespace ECode;

	CodeTypedef
	result              = (CodeTypedef) make_code();
	result->Type        = Typedef;
	result->ModuleFlags = mflags;

	if ( is_function )
	{
		result->Name       = type->Name;
		result->IsFunction = true;
	}
	else
	{
		result->Name       = get_cached_string( name );
		result->IsFunction = false;
	}

	if ( type )
	{
		result->UnderlyingType         = type;
		result->UnderlyingType->Parent = rcast(AST*, result.ast);
	}
	// Type needs to be aware of its parent so that it can be serialized properly.

	if ( type->Type == Typename && array_expr && array_expr->Type != Invalid )
		type.cast<CodeType>()->ArrExpr = array_expr;

	if ( inline_cmt )
		result->InlineCmt = inline_cmt;

	Context.pop();
	return result;
}

internal neverinline
CodeUnion parse_union( bool inplace_def )
{
	push_scope();

	ModuleFlag mflags = ModuleFlag::None;

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <ModuleFlags>

	eat( TokType::Decl_Union );
	// <ModuleFlags> union

	CodeAttributes attributes = parse_attributes();
	// <ModuleFlags> union <Attributes>

	StrC name = { 0, nullptr };
	if ( check( TokType::Identifier ) )
	{
		name = currtok;
		Context.Scope->Name = currtok;
		eat( TokType::Identifier );
	}
	// <ModuleFlags> union <Attributes> <Name>

	CodeBody body = { nullptr };

	eat( TokType::BraceCurly_Open );
	// <ModuleFlags> union <Attributes> <Name> {

	body = make_code();
	body->Type = ECode::Union_Body;

	while ( ! check_noskip( TokType::BraceCurly_Close ) )
	{
		if ( currtok_noskip.Type == TokType::Preprocess_Hash )
			eat( TokType::Preprocess_Hash );

		Code member = { nullptr };
		switch ( currtok_noskip.Type )
		{
			case TokType::NewLine:
				member = fmt_newline;
				eat( TokType::NewLine );
			break;

			case TokType::Comment:
				member = parse_comment();
			break;

			// TODO(Ed) : Unions can have constructors and destructors

			case TokType::Decl_Class:
				member = parse_complicated_definition( TokType::Decl_Class );
			break;

			case TokType::Decl_Enum:
				member = parse_complicated_definition( TokType::Decl_Enum );
			break;

			case TokType::Decl_Struct:
				member = parse_complicated_definition( TokType::Decl_Struct );
			break;

			case TokType::Decl_Union:
				member = parse_complicated_definition( TokType::Decl_Union );
			break;

			case TokType::Preprocess_Define:
				member = parse_define();
			break;

			case TokType::Preprocess_If:
			case TokType::Preprocess_IfDef:
			case TokType::Preprocess_IfNotDef:
			case TokType::Preprocess_ElIf:
				member = parse_preprocess_cond();
			break;

			case TokType::Preprocess_Else:
				member = preprocess_else;
				eat( TokType::Preprocess_Else );
			break;

			case TokType::Preprocess_EndIf:
				member = preprocess_endif;
				eat( TokType::Preprocess_EndIf );
			break;

			case TokType::Preprocess_Macro:
				member = parse_simple_preprocess( TokType::Preprocess_Macro );
			break;

			case TokType::Preprocess_Pragma:
				member = parse_pragma();
			break;

			case TokType::Preprocess_Unsupported:
				member = parse_simple_preprocess( TokType::Preprocess_Unsupported );
			break;

			default:
				member = parse_variable();
			break;
		}

		if ( member )
			body.append( member );
	}
	// <ModuleFlags> union <Attributes> <Name> { <Body>

	eat( TokType::BraceCurly_Close );
	// <ModuleFlags> union <Attributes> <Name> { <Body> }

	if ( ! inplace_def )
		eat( TokType::Statement_End );
		// <ModuleFlags> union <Attributes> <Name> { <Body> };

	CodeUnion
	result = (CodeUnion) make_code();
	result->Type        = ECode::Union;
	result->ModuleFlags = mflags;

	if ( name )
		result->Name = get_cached_string( name );

	if ( body )
		result->Body = body;

	if ( attributes )
		result->Attributes = attributes;

	Context.pop();
	return result;
}

internal
CodeUsing parse_using()
{
	push_scope();

	SpecifierT specs_found[16] { ESpecifier::Invalid };
	s32        NumSpecifiers = 0;

	Token    name       = { nullptr, 0, TokType::Invalid };
	Code     array_expr = { nullptr };
	CodeType type       = { nullptr };

	bool is_namespace = false;

	ModuleFlag     mflags     = ModuleFlag::None;
	CodeAttributes attributes = { nullptr };

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <ModuleFlags>

	eat( TokType::Decl_Using );
	// <ModuleFlags> using

	if ( currtok.Type == TokType::Decl_Namespace )
	{
		is_namespace = true;
		eat( TokType::Decl_Namespace );
		// <ModuleFlags> using namespace
	}

	name = currtok;
	Context.Scope->Name = name;
	eat( TokType::Identifier );
	// <ModuleFlags> using <namespace> <Name>

	if ( ! is_namespace )
	{
		if ( bitfield_is_equal( u32, currtok.Flags, TF_Assign ) )
		{
			attributes = parse_attributes();
			// <ModuleFlags> using <Name> <Attributes>

			eat( TokType::Operator );
			// <ModuleFlags> using <Name> <Attributes> =

			type = parse_type();
			// <ModuleFlags> using <Name> <Attributes> = <UnderlyingType>

			array_expr = parse_array_decl();
			// <UnderlyingType> + <ArrExpr>
		}
	}

	Token stmt_end = currtok;
	eat( TokType::Statement_End );
	// <ModuleFlags> using <namespace> <Attributes> <Name> = <UnderlyingType>;

	CodeComment inline_cmt = NoCode;
	if ( currtok_noskip.Type == TokType::Comment && currtok_noskip.Line == stmt_end.Line )
	{
		inline_cmt = parse_comment();
	}
	// <ModuleFlags> using <namespace> <Attributes> <Name> = <UnderlyingType>; <InlineCmt>

	using namespace ECode;

	CodeUsing
	result              = (CodeUsing) make_code();
	result->Name        = get_cached_string( name );
	result->ModuleFlags = mflags;

	if ( is_namespace)
	{
		result->Type = Using_Namespace;
	}
	else
	{
		result->Type = Using;

		if ( type )
			result->UnderlyingType = type;

		if ( array_expr )
			type->ArrExpr = array_expr;

		if ( attributes )
			result->Attributes = attributes;

		if ( inline_cmt )
			result->InlineCmt = inline_cmt;
	}

	Context.pop();
	return result;
}

internal
CodeVar parse_variable()
{
	push_scope();

	SpecifierT specs_found[16] { ESpecifier::NumSpecifiers };
	s32        NumSpecifiers = 0;

	ModuleFlag	   mflags     = ModuleFlag::None;
	CodeAttributes attributes = { nullptr };
	CodeSpecifiers specifiers = { nullptr };

	if ( check(TokType::Module_Export) )
	{
		mflags = ModuleFlag::Export;
		eat( TokType::Module_Export );
	}
	// <ModuleFlags>

	attributes = parse_attributes();
	// <ModuleFlags> <Attributes>

	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		switch ( spec )
		{
			case ESpecifier::Const:
			case ESpecifier::Constexpr:
			case ESpecifier::Constinit:
			case ESpecifier::External_Linkage:
			case ESpecifier::Global:
			case ESpecifier::Inline:
			case ESpecifier::Local_Persist:
			case ESpecifier::Mutable:
			case ESpecifier::Static:
			case ESpecifier::Thread_Local:
			case ESpecifier::Volatile:
			break;

			default:
				log_failure( "Invalid specifier %s for variable\n%s", ESpecifier::to_str( spec ), Context.to_string() );
				Context.pop();
				return CodeInvalid;
		}

		// Ignore const specifiers, they're handled by the type
		if ( spec == ESpecifier::Const )
			break;

		specs_found[NumSpecifiers] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}

	if ( NumSpecifiers )
	{
		specifiers = def_specifiers( NumSpecifiers, specs_found );
	}
	// <ModuleFlags> <Attributes> <Specifiers>

	CodeType type = parse_type();
	// <ModuleFlags> <Attributes> <Specifiers> <ValueType>

	if ( type == Code::Invalid )
		return CodeInvalid;

	Context.Scope->Name = parse_identifier();
	// <ModuleFlags> <Attributes> <Specifiers> <ValueType> <Name>

	CodeVar result = parse_variable_after_name( mflags, attributes, specifiers, type, Context.Scope->Name );
	// Regular  : <ModuleFlags> <Attributes> <Specifiers> <ValueType> <Name>                  = <Value>; <InlineCmt>
	// Bitfield : <ModuleFlags> <Attributes> <Specifiers> <ValueType> <Name> : <BitfieldSize> = <Value>; <InlineCmt>

	Context.pop();
	return result;
}

// namespace parser
}

#ifdef CHECK_WAS_DEFINED
#pragma pop_macro("check")
#endif

// Publically Exposed Interface

CodeClass parse_class( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	push_scope();
	CodeClass result = (CodeClass) parse_class_struct( TokType::Decl_Class );
	Context.pop();
	return result;
}

CodeConstructor parse_constructor( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	// TODO(Ed): Constructors can have prefix attributes

	CodeSpecifiers specifiers;
	SpecifierT     specs_found[ 16 ] { ESpecifier::NumSpecifiers };
	s32            NumSpecifiers = 0;

	while ( left && currtok.is_specifier() )
	{
		SpecifierT spec = ESpecifier::to_type( currtok );

		b32 ignore_spec = false;

		switch ( spec )
		{
			case ESpecifier::Constexpr :
			case ESpecifier::Explicit:
			case ESpecifier::Inline :
			case ESpecifier::ForceInline :
			case ESpecifier::NeverInline :
				break;

			case ESpecifier::Const :
				ignore_spec = true;
				break;

			default :
				log_failure( "Invalid specifier %s for variable\n%s", ESpecifier::to_str( spec ), Context.to_string() );
				Context.pop();
				return CodeInvalid;
		}

		// Every specifier after would be considered part of the type type signature
		if (ignore_spec)
			break;

		specs_found[ NumSpecifiers ] = spec;
		NumSpecifiers++;
		eat( currtok.Type );
	}

	if ( NumSpecifiers )
	{
		specifiers = def_specifiers( NumSpecifiers, specs_found );
		// <specifiers> ...
	}

	Context.Tokens         = toks;
	CodeConstructor result = parse_constructor( specifiers );
	return result;
}

CodeDestructor parse_destructor( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	// TODO(Ed): Destructors can have prefix attributes
	// TODO(Ed): Destructors can have virtual

	Context.Tokens        = toks;
	CodeDestructor result = parse_destructor();
	return result;
}

CodeEnum parse_enum( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
	{
		Context.pop();
		return CodeInvalid;
	}

	Context.Tokens = toks;
	return parse_enum();
}

CodeBody parse_export_body( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_export_body();
}

CodeExtern parse_extern_link( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_extern_link();
}

CodeFriend parse_friend( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_friend();
}

CodeFn parse_function( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return (CodeFn) parse_function();
}

CodeBody parse_global_body( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	push_scope();
	CodeBody result = parse_global_nspace( ECode::Global_Body );
	Context.pop();
	return result;
}

CodeNS parse_namespace( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_namespace();
}

CodeOperator parse_operator( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return (CodeOperator) parse_operator();
}

CodeOpCast parse_operator_cast( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_operator_cast();
}

CodeStruct parse_struct( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	push_scope();
	CodeStruct result = (CodeStruct) parse_class_struct( TokType::Decl_Struct );
	Context.pop();
	return result;
}

CodeTemplate parse_template( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_template();
}

CodeType parse_type( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_type();
}

CodeTypedef parse_typedef( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_typedef();
}

CodeUnion parse_union( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_union();
}

CodeUsing parse_using( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_using();
}

CodeVar parse_variable( StrC def )
{
	check_parse_args( def );
	using namespace parser;

	TokArray toks = lex( def );
	if ( toks.Arr == nullptr )
		return CodeInvalid;

	Context.Tokens = toks;
	return parse_variable();
}

// Undef helper macros
#	undef check_parse_args
#	undef currtok
#	undef prevtok
#   undef nexttok
#	undef eat
#	undef left
#	undef check
#	undef push_scope

#pragma endregion Parsing

ssize token_fmt_va( char* buf, usize buf_size, s32 num_tokens, va_list va )
{
	char const* buf_begin = buf;
	ssize          remaining = buf_size;

	local_persist
	Arena tok_map_arena;

	HashTable<StrC> tok_map;
	{
		local_persist
		char tok_map_mem[ TokenFmt_TokenMap_MemSize ];

		tok_map_arena = Arena::init_from_memory( tok_map_mem, sizeof(tok_map_mem) );
		tok_map       = HashTable<StrC>::init( tok_map_arena );

		s32 left = num_tokens - 1;

		while ( left-- )
		{
			char const* token = va_arg( va, char const* );
			StrC        value = va_arg( va, StrC );

			u32 key = crc32( token, str_len(token) );

			tok_map.set( key, value );
		}
	}

	char const* fmt     = va_arg( va, char const* );
	char        current = *fmt;

	while ( current )
	{
		ssize len = 0;

		while ( current && current != '<' && remaining )
		{
			* buf = * fmt;
			buf++;
			fmt++;
			remaining--;

			current = * fmt;
		}

		if ( current == '<' )
		{
			char const* scanner = fmt + 1;

			s32 tok_len = 0;

			while ( *scanner != '>' )
			{
				tok_len++;
				scanner++;
			}

			char const* token = fmt + 1;

			u32       key   = crc32( token, tok_len );
			StrC*     value = tok_map.get( key );

			if ( value )
			{
				ssize          left = value->Len;
				char const* str  = value->Ptr;

				while ( left-- )
				{
					* buf = * str;
					buf++;
					str++;
					remaining--;
				}

				scanner++;
				fmt     = scanner;
				current = * fmt;
				continue;
			}

			* buf = * fmt;
			buf++;
			fmt++;
			remaining--;

			current = * fmt;
		}
	}

	tok_map.clear();
	tok_map_arena.free();

	ssize result = buf_size - remaining;

	return result;
}

Code untyped_str( StrC content )
{
	if ( content.Len == 0 )
	{
		log_failure( "untyped_str: empty string" );
		return CodeInvalid;
	}

	Code
	result          = make_code();
	result->Name    = get_cached_string( content );
	result->Type    = ECode::Untyped;
	result->Content = result->Name;

	if ( result->Name == nullptr )
	{
		log_failure( "untyped_str: could not cache string" );
		return CodeInvalid;
	}

	return result;
}

Code untyped_fmt( char const* fmt, ...)
{
	if ( fmt == nullptr )
	{
		log_failure( "untyped_fmt: null format string" );
		return CodeInvalid;
	}

	local_persist thread_local
	char buf[GEN_PRINTF_MAXLEN] = { 0 };

	va_list va;
	va_start(va, fmt);
	ssize length = str_fmt_va(buf, GEN_PRINTF_MAXLEN, fmt, va);
	va_end(va);

	Code
	result          = make_code();
	result->Name    = get_cached_string( { str_len(fmt, MaxNameLength), fmt } );
	result->Type    = ECode::Untyped;
	result->Content = get_cached_string( { length, buf } );

	if ( result->Name == nullptr )
	{
		log_failure( "untyped_fmt: could not cache string" );
		return CodeInvalid;
	}

	return result;
}

Code untyped_token_fmt( s32 num_tokens, ... )
{
	if ( num_tokens == 0 )
	{
		log_failure( "untyped_token_fmt: zero tokens" );
		return CodeInvalid;
	}

	local_persist thread_local
	char buf[GEN_PRINTF_MAXLEN] = { 0 };

	va_list va;
	va_start(va, num_tokens);
	ssize length = token_fmt_va(buf, GEN_PRINTF_MAXLEN, num_tokens, va);
	va_end(va);

	Code
	result          = make_code();
	result->Name    = get_cached_string( { length, buf } );
	result->Type    = ECode::Untyped;
	result->Content = result->Name;

	if ( result->Name == nullptr )
	{
		log_failure( "untyped_fmt: could not cache string" );
		return CodeInvalid;
	}

	return result;
}

#pragma endregion Interface

#pragma region Builder

Builder Builder::open( char const* path )
{
	Builder result;

	FileError error = file_open_mode( & result.File, EFileMode_WRITE, path );
	if ( error != EFileError_NONE )
	{
		log_failure( "gen::File::open - Could not open file: %s", path);
		return result;
	}

	result.Buffer = String::make_reserve( GlobalAllocator, Builder_StrBufferReserve );

	// log_fmt("$Builder - Opened file: %s\n", result.File.filename );
	return result;
}

void Builder::pad_lines( s32 num )
{
	Buffer.append( "\n" );
}

void Builder::print( Code code )
{
	String   str = code->to_string();
	// const ssize len = str.length();
	// log_fmt( "%s - print: %.*s\n", File.filename, len > 80 ? 80 : len, str.Data );
	Buffer.append( str );
}

void Builder::print_fmt( char const* fmt, ... )
{
	ssize   res;
	char buf[ GEN_PRINTF_MAXLEN ] = { 0 };

	va_list va;
	va_start( va, fmt );
	res = str_fmt_va( buf, count_of( buf ) - 1, fmt, va ) - 1;
	va_end( va );

	// log_fmt( "$%s - print_fmt: %.*s\n", File.filename, res > 80 ? 80 : res, buf );
	Buffer.append( buf, res );
}

void Builder::write()
{
	b32 result = file_write( & File, Buffer, Buffer.length() );

	if ( result == false )
		log_failure("gen::File::write - Failed to write to file: %s\n", file_name( & File ) );

	log_fmt( "Generated: %s\n", File.filename );
	file_close( & File );
	Buffer.free();
}

#pragma endregion Builder


#pragma region Scanner

// This is a simple file reader that reads the entire file into memory.
// It has an extra option to skip the first few lines for undesired includes.
// This is done so that includes can be kept in dependency and component files so that intellisense works.
inline
Code scan_file( char const* path )
{
	FileInfo file;

	FileError error = file_open_mode( & file, EFileMode_READ, path );
	if ( error != EFileError_NONE )
	{
		GEN_FATAL( "scan_file: Could not open: %s", path );
	}

	ssize fsize = file_size( & file );
	if ( fsize <= 0 )
	{
		GEN_FATAL("scan_file: %s is empty", path );
	}

	String str = String::make_reserve( GlobalAllocator, fsize );
		file_read( & file, str, fsize );
		str.get_header().Length = fsize;

	// Skip GEN_INTELLISENSE_DIRECTIVES preprocessor blocks
	// Its designed so that the directive should be the first thing in the file.
	// Anything that comes before it will also be omitted.
	{
	#define current (*scanner)
	#define matched    0
	#define move_fwd() do { ++ scanner; -- left; } while (0)
		const StrC directive_start = txt( "ifdef" );
		const StrC directive_end   = txt( "endif" );
		const StrC def_intellisense = txt("GEN_INTELLISENSE_DIRECTIVES" );

		bool        found_directive = false;
		char const* scanner         = str.Data;
		s32         left            = fsize;
		while ( left )
		{
			// Processing directive.
			if ( current == '#' )
			{
				move_fwd();
				while ( left && char_is_space( current ) )
					move_fwd();

				if ( ! found_directive )
				{
					if ( left && str_compare( scanner, directive_start.Ptr, directive_start.Len ) == matched )
					{
						scanner += directive_start.Len;
						left    -= directive_start.Len;

						while ( left && char_is_space( current ) )
							move_fwd();

						if ( left && str_compare( scanner, def_intellisense.Ptr, def_intellisense.Len ) == matched )
						{
							scanner += def_intellisense.Len;
							left    -= def_intellisense.Len;

							found_directive = true;
						}
					}

					// Skip to end of line
					while ( left && current != '\r' && current != '\n' )
						move_fwd();
					move_fwd();

					if ( left && current == '\n' )
						move_fwd();

					continue;
				}

				if ( left && str_compare( scanner, directive_end.Ptr, directive_end.Len ) == matched )
				{
					scanner += directive_end.Len;
					left    -= directive_end.Len;

					// Skip to end of line
					while ( left && current != '\r' && current != '\n' )
						move_fwd();
					move_fwd();

					if ( left && current == '\n' )
						move_fwd();

					// sptr skip_size = fsize - left;
					if ( (scanner + 2) >= ( str.Data + fsize ) )
					{
						mem_move( str, scanner, left );
						str.get_header().Length = left;
						break;
					}

					mem_move( str, scanner, left );
					str.get_header().Length = left;

					break;
				}

			}

			move_fwd();
		}
	#undef move_fwd
	#undef matched
	#undef current
	}

	file_close( & file );
	return untyped_str( str );
}

#if 0
struct CodeFile
{
	using namespace Parser;

	String              FilePath;
	TokArray            Tokens;
	Array<ParseFailure> ParseFailures;
	Code                CodeRoot;
};

namespace Parser
{
	struct ParseFailure
	{
		String Reason;
		Code   Node;
	};
}

CodeFile scan_file( char const* path )
{
	using namespace Parser;

	CodeFile
	result = {};
	result.FilePath = String::make( GlobalAllocator, path );

	Code code = scan_file( path );
	result.CodeRoot = code;

	ParseContext context = parser_get_last_context();
	result.Tokens        = context.Tokens;
	result.ParseFailures = context.Failures;

	return result;
}
#endif
#pragma endregion Scanner

GEN_NS_END

#endif
#pragma endregion GENCPP IMPLEMENTATION GUARD

#ifdef __clang__
#	pragma clang diagnostic pop
#endif

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif
