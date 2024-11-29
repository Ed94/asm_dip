#ifdef INTELLISENSE_DIRECTIVES
#	pragma once
#	include "debug.h"
#endif

#pragma region Memory

#define kilobytes( x ) (          ( x ) * ( s64 )( 1024 ) )
#define megabytes( x ) ( kilobytes( x ) * ( s64 )( 1024 ) )
#define gigabytes( x ) ( megabytes( x ) * ( s64 )( 1024 ) )
#define terabytes( x ) ( gigabytes( x ) * ( s64 )( 1024 ) )

#define _ONES          ( cast( usize, - 1) / U8_MAX )
#define _HIGHS         ( GEN__ONES * ( U8_MAX / 2 + 1 ) )
#define _HAS_ZERO( x ) ( ( ( x ) - _ONES ) & ~( x ) & _HIGHS )

#define swap( a, b ) \
do {                 \
	typeof(a)          \
	temp = (a);        \
	(a)  = (b);        \
	(b)  = temp;       \
} while(0)

#pragma endregion Memory
