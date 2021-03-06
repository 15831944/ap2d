// md5.cpp: implementation of the md5 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "md5.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT32 count_padding_bits ( UINT32 length )
{
	UINT32 div = length * BITS / BLOCK_SIZE;
	UINT32 mod = length * BITS % BLOCK_SIZE;
	UINT32 c_bits;
	if ( mod == 0 )
		c_bits = MOD_SIZE;
	else
		c_bits = ( MOD_SIZE + BLOCK_SIZE - mod ) % BLOCK_SIZE;
	return c_bits / BITS;
}
STRING append_padding_bits ( char * argv )
{
	UINT32 msg_length = strlen ( argv );
	UINT32 bit_length = count_padding_bits ( msg_length );
	UINT64 app_length = msg_length * BITS;
	STRING string;
	string.message = (char *)malloc(msg_length + bit_length + APP_SIZE / BITS);
	// Save message
	strncpy ( string.message, argv, msg_length );
	// Pad out to mod 64.
	memset ( string.message + msg_length, 0, bit_length );
	string.message [ msg_length ] = SINGLE_ONE_BIT;
	// Append length (before padding).
	memmove ( string.message + msg_length + bit_length, (char *)&app_length, sizeof( UINT64 ) );
	string.length = msg_length + bit_length + sizeof( UINT64 );
	return string;
}


void cal_hash_val(STRING r_string,UINT8 *r)
{
		// MD5 initialization.
	UINT32 w[16];
	UINT32 chain[4];
	UINT32 state[4];
//	UINT8 r[16];
	UINT32 ( *auxi[ 4 ])( UINT32, UINT32, UINT32 ) = { F, G, H, I };
	int roundIdx;
	int sIdx;
	int wIdx;
	int i;
	int j;


	chain[0] = A;
	chain[1] = B;
	chain[2] = C;
	chain[3] = D;
	
	for ( j = 0; j < r_string.length; j += BLOCK_SIZE / BITS){
		memmove ( (char *)w, r_string.message + j, BLOCK_SIZE / BITS );
		memmove ( state, chain, sizeof(chain) );
		for ( roundIdx = 0; roundIdx < 4; roundIdx++ )
		{
			wIdx = X[ roundIdx ][ 0 ];
			sIdx = 0;
			for ( i = 0; i < 16; i++ )
			{
				// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
				// Rotation is separate from addition to prevent recomputation.
				state[sIdx] = state [ (sIdx + 1) % 4 ] +
					rotate_left ( state[sIdx] +
							( *auxi[ roundIdx ] )
							( state[(sIdx+1) % 4], state[(sIdx+2) % 4], state[(sIdx+3) % 4]) +
							w[ wIdx ] +
								(UINT32)floor( ((DWORD)(1) << 32) * fabs(sin( roundIdx * 16 + i + 1 )) ),
							S[ roundIdx ][ i % 4 ]);
				sIdx = ( sIdx + 3 ) % 4;
				wIdx = ( wIdx + X[ roundIdx ][ 1 ] ) & 0xF;
			}
		}
		chain[ 0 ] += state[ 0 ];
		chain[ 1 ] += state[ 1 ];
		chain[ 2 ] += state[ 2 ];
		chain[ 3 ] += state[ 3 ];
	}
	memmove ( r + 0, (char *)&chain[0], sizeof(UINT32) );
	memmove ( r + 4, (char *)&chain[1], sizeof(UINT32) );
	memmove ( r + 8, (char *)&chain[2], sizeof(UINT32) );
	memmove ( r + 12, (char *)&chain[3], sizeof(UINT32) );

//	for ( i = 0; i < 16; i++ )
//		printf ( "%02x", r[i] );
//	putchar ( '\n' );

}