#ifdef INTELLISENSE_DIRECTIVES
#	pragma once
#	include "basic_types.hpp"
#endif

#pragma region Debug

#if defined( _MSC_VER )
#	if _MSC_VER < 1300
#		define DEBUG_TRAP() __asm int 3 /* Trap to debugger! */
#	else
#		define debug_trap() __debugbreak()
#	endif
#elif defined( GEN_COMPILER_TINYC )
#	define DEBUG_TRAP() process_exit( 1 )
#else
#	define DEBUG_TRAP() __builtin_trap()
#endif

#define ASSERT( cond ) ASSERT( cond, NULL )

#define ASSERT_MSG( cond, msg, ... )                                                 \
	do                                                                                 \
	{                                                                                  \
		if ( ! ( cond ) )                                                                \
		{                                                                                \
			assert_handler( #cond, __FILE__, scast( s64, __LINE__ ), msg, ##__VA_ARGS__ ); \
			GEN_DEBUG_TRAP();                                                              \
		}                                                                                \
	} while ( 0 )

#define ASSERT_NOT_NULL( ptr ) ASSERT_MSG( ( ptr ) != NULL, #ptr " must not be NULL" )

// NOTE: Things that shouldn't happen with a message!
#define PANIC( msg, ... ) ASSERT_MSG( 0, msg, ##__VA_ARGS__ )

#if Build_Debug
	#define FATAL( ... )                        \
	do                                          \
	{                                           \
		local_persist thread_local                \
		char buf[GEN_PRINTF_MAXLEN] = { 0 };      \
		                                          \
		str_fmt(buf, PRINTF_MAXLEN, __VA_ARGS__); \
		PANIC(buf);                               \
	}                                           \
	while (0)
#else

#	define FATAL( ... )               \
	do                                \
	{                                 \
		str_fmt_out_err( __VA_ARGS__ ); \
		process_exit(1);                \
	}                                 \
	while (0)
#endif

void assert_handler( char const* condition, char const* file, s32 line, char const* msg, ... );
s32  assert_crash( char const* condition );
void process_exit( u32 code );

#pragma endregion Debug
