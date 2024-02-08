//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA256 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#include "sha256_internal.h"

alignas(64) const uint32_t sha256_consts[64] = {
	UINT32_C(0x428a2f98),
	UINT32_C(0x71374491),
	UINT32_C(0xb5c0fbcf),
	UINT32_C(0xe9b5dba5),
	UINT32_C(0x3956c25b),
	UINT32_C(0x59f111f1),
	UINT32_C(0x923f82a4),
	UINT32_C(0xab1c5ed5),
	UINT32_C(0xd807aa98),
	UINT32_C(0x12835b01),
	UINT32_C(0x243185be),
	UINT32_C(0x550c7dc3),
	UINT32_C(0x72be5d74),
	UINT32_C(0x80deb1fe),
	UINT32_C(0x9bdc06a7),
	UINT32_C(0xc19bf174),
	UINT32_C(0xe49b69c1),
	UINT32_C(0xefbe4786),
	UINT32_C(0x0fc19dc6),
	UINT32_C(0x240ca1cc),
	UINT32_C(0x2de92c6f),
	UINT32_C(0x4a7484aa),
	UINT32_C(0x5cb0a9dc),
	UINT32_C(0x76f988da),
	UINT32_C(0x983e5152),
	UINT32_C(0xa831c66d),
	UINT32_C(0xb00327c8),
	UINT32_C(0xbf597fc7),
	UINT32_C(0xc6e00bf3),
	UINT32_C(0xd5a79147),
	UINT32_C(0x06ca6351),
	UINT32_C(0x14292967),
	UINT32_C(0x27b70a85),
	UINT32_C(0x2e1b2138),
	UINT32_C(0x4d2c6dfc),
	UINT32_C(0x53380d13),
	UINT32_C(0x650a7354),
	UINT32_C(0x766a0abb),
	UINT32_C(0x81c2c92e),
	UINT32_C(0x92722c85),
	UINT32_C(0xa2bfe8a1),
	UINT32_C(0xa81a664b),
	UINT32_C(0xc24b8b70),
	UINT32_C(0xc76c51a3),
	UINT32_C(0xd192e819),
	UINT32_C(0xd6990624),
	UINT32_C(0xf40e3585),
	UINT32_C(0x106aa070),
	UINT32_C(0x19a4c116),
	UINT32_C(0x1e376c08),
	UINT32_C(0x2748774c),
	UINT32_C(0x34b0bcb5),
	UINT32_C(0x391c0cb3),
	UINT32_C(0x4ed8aa4a),
	UINT32_C(0x5b9cca4f),
	UINT32_C(0x682e6ff3),
	UINT32_C(0x748f82ee),
	UINT32_C(0x78a5636f),
	UINT32_C(0x84c87814),
	UINT32_C(0x8cc70208),
	UINT32_C(0x90befffa),
	UINT32_C(0xa4506ceb),
	UINT32_C(0xbef9a3f7),
	UINT32_C(0xc67178f2),
};
alignas(64) const uint32_t sha256_consts_vec128[256] = {
	UINT32_C(0x428a2f98), UINT32_C(0x428a2f98), UINT32_C(0x428a2f98), UINT32_C(0x428a2f98), 
	UINT32_C(0x71374491), UINT32_C(0x71374491), UINT32_C(0x71374491), UINT32_C(0x71374491), 
	UINT32_C(0xb5c0fbcf), UINT32_C(0xb5c0fbcf), UINT32_C(0xb5c0fbcf), UINT32_C(0xb5c0fbcf), 
	UINT32_C(0xe9b5dba5), UINT32_C(0xe9b5dba5), UINT32_C(0xe9b5dba5), UINT32_C(0xe9b5dba5), 
	UINT32_C(0x3956c25b), UINT32_C(0x3956c25b), UINT32_C(0x3956c25b), UINT32_C(0x3956c25b), 
	UINT32_C(0x59f111f1), UINT32_C(0x59f111f1), UINT32_C(0x59f111f1), UINT32_C(0x59f111f1), 
	UINT32_C(0x923f82a4), UINT32_C(0x923f82a4), UINT32_C(0x923f82a4), UINT32_C(0x923f82a4), 
	UINT32_C(0xab1c5ed5), UINT32_C(0xab1c5ed5), UINT32_C(0xab1c5ed5), UINT32_C(0xab1c5ed5), 
	UINT32_C(0xd807aa98), UINT32_C(0xd807aa98), UINT32_C(0xd807aa98), UINT32_C(0xd807aa98), 
	UINT32_C(0x12835b01), UINT32_C(0x12835b01), UINT32_C(0x12835b01), UINT32_C(0x12835b01), 
	UINT32_C(0x243185be), UINT32_C(0x243185be), UINT32_C(0x243185be), UINT32_C(0x243185be), 
	UINT32_C(0x550c7dc3), UINT32_C(0x550c7dc3), UINT32_C(0x550c7dc3), UINT32_C(0x550c7dc3), 
	UINT32_C(0x72be5d74), UINT32_C(0x72be5d74), UINT32_C(0x72be5d74), UINT32_C(0x72be5d74), 
	UINT32_C(0x80deb1fe), UINT32_C(0x80deb1fe), UINT32_C(0x80deb1fe), UINT32_C(0x80deb1fe), 
	UINT32_C(0x9bdc06a7), UINT32_C(0x9bdc06a7), UINT32_C(0x9bdc06a7), UINT32_C(0x9bdc06a7), 
	UINT32_C(0xc19bf174), UINT32_C(0xc19bf174), UINT32_C(0xc19bf174), UINT32_C(0xc19bf174), 
	UINT32_C(0xe49b69c1), UINT32_C(0xe49b69c1), UINT32_C(0xe49b69c1), UINT32_C(0xe49b69c1), 
	UINT32_C(0xefbe4786), UINT32_C(0xefbe4786), UINT32_C(0xefbe4786), UINT32_C(0xefbe4786), 
	UINT32_C(0x0fc19dc6), UINT32_C(0x0fc19dc6), UINT32_C(0x0fc19dc6), UINT32_C(0x0fc19dc6), 
	UINT32_C(0x240ca1cc), UINT32_C(0x240ca1cc), UINT32_C(0x240ca1cc), UINT32_C(0x240ca1cc), 
	UINT32_C(0x2de92c6f), UINT32_C(0x2de92c6f), UINT32_C(0x2de92c6f), UINT32_C(0x2de92c6f), 
	UINT32_C(0x4a7484aa), UINT32_C(0x4a7484aa), UINT32_C(0x4a7484aa), UINT32_C(0x4a7484aa), 
	UINT32_C(0x5cb0a9dc), UINT32_C(0x5cb0a9dc), UINT32_C(0x5cb0a9dc), UINT32_C(0x5cb0a9dc), 
	UINT32_C(0x76f988da), UINT32_C(0x76f988da), UINT32_C(0x76f988da), UINT32_C(0x76f988da), 
	UINT32_C(0x983e5152), UINT32_C(0x983e5152), UINT32_C(0x983e5152), UINT32_C(0x983e5152), 
	UINT32_C(0xa831c66d), UINT32_C(0xa831c66d), UINT32_C(0xa831c66d), UINT32_C(0xa831c66d), 
	UINT32_C(0xb00327c8), UINT32_C(0xb00327c8), UINT32_C(0xb00327c8), UINT32_C(0xb00327c8), 
	UINT32_C(0xbf597fc7), UINT32_C(0xbf597fc7), UINT32_C(0xbf597fc7), UINT32_C(0xbf597fc7), 
	UINT32_C(0xc6e00bf3), UINT32_C(0xc6e00bf3), UINT32_C(0xc6e00bf3), UINT32_C(0xc6e00bf3), 
	UINT32_C(0xd5a79147), UINT32_C(0xd5a79147), UINT32_C(0xd5a79147), UINT32_C(0xd5a79147), 
	UINT32_C(0x06ca6351), UINT32_C(0x06ca6351), UINT32_C(0x06ca6351), UINT32_C(0x06ca6351), 
	UINT32_C(0x14292967), UINT32_C(0x14292967), UINT32_C(0x14292967), UINT32_C(0x14292967), 
	UINT32_C(0x27b70a85), UINT32_C(0x27b70a85), UINT32_C(0x27b70a85), UINT32_C(0x27b70a85), 
	UINT32_C(0x2e1b2138), UINT32_C(0x2e1b2138), UINT32_C(0x2e1b2138), UINT32_C(0x2e1b2138), 
	UINT32_C(0x4d2c6dfc), UINT32_C(0x4d2c6dfc), UINT32_C(0x4d2c6dfc), UINT32_C(0x4d2c6dfc), 
	UINT32_C(0x53380d13), UINT32_C(0x53380d13), UINT32_C(0x53380d13), UINT32_C(0x53380d13), 
	UINT32_C(0x650a7354), UINT32_C(0x650a7354), UINT32_C(0x650a7354), UINT32_C(0x650a7354), 
	UINT32_C(0x766a0abb), UINT32_C(0x766a0abb), UINT32_C(0x766a0abb), UINT32_C(0x766a0abb), 
	UINT32_C(0x81c2c92e), UINT32_C(0x81c2c92e), UINT32_C(0x81c2c92e), UINT32_C(0x81c2c92e), 
	UINT32_C(0x92722c85), UINT32_C(0x92722c85), UINT32_C(0x92722c85), UINT32_C(0x92722c85), 
	UINT32_C(0xa2bfe8a1), UINT32_C(0xa2bfe8a1), UINT32_C(0xa2bfe8a1), UINT32_C(0xa2bfe8a1), 
	UINT32_C(0xa81a664b), UINT32_C(0xa81a664b), UINT32_C(0xa81a664b), UINT32_C(0xa81a664b), 
	UINT32_C(0xc24b8b70), UINT32_C(0xc24b8b70), UINT32_C(0xc24b8b70), UINT32_C(0xc24b8b70), 
	UINT32_C(0xc76c51a3), UINT32_C(0xc76c51a3), UINT32_C(0xc76c51a3), UINT32_C(0xc76c51a3), 
	UINT32_C(0xd192e819), UINT32_C(0xd192e819), UINT32_C(0xd192e819), UINT32_C(0xd192e819), 
	UINT32_C(0xd6990624), UINT32_C(0xd6990624), UINT32_C(0xd6990624), UINT32_C(0xd6990624), 
	UINT32_C(0xf40e3585), UINT32_C(0xf40e3585), UINT32_C(0xf40e3585), UINT32_C(0xf40e3585), 
	UINT32_C(0x106aa070), UINT32_C(0x106aa070), UINT32_C(0x106aa070), UINT32_C(0x106aa070), 
	UINT32_C(0x19a4c116), UINT32_C(0x19a4c116), UINT32_C(0x19a4c116), UINT32_C(0x19a4c116), 
	UINT32_C(0x1e376c08), UINT32_C(0x1e376c08), UINT32_C(0x1e376c08), UINT32_C(0x1e376c08), 
	UINT32_C(0x2748774c), UINT32_C(0x2748774c), UINT32_C(0x2748774c), UINT32_C(0x2748774c), 
	UINT32_C(0x34b0bcb5), UINT32_C(0x34b0bcb5), UINT32_C(0x34b0bcb5), UINT32_C(0x34b0bcb5), 
	UINT32_C(0x391c0cb3), UINT32_C(0x391c0cb3), UINT32_C(0x391c0cb3), UINT32_C(0x391c0cb3), 
	UINT32_C(0x4ed8aa4a), UINT32_C(0x4ed8aa4a), UINT32_C(0x4ed8aa4a), UINT32_C(0x4ed8aa4a), 
	UINT32_C(0x5b9cca4f), UINT32_C(0x5b9cca4f), UINT32_C(0x5b9cca4f), UINT32_C(0x5b9cca4f), 
	UINT32_C(0x682e6ff3), UINT32_C(0x682e6ff3), UINT32_C(0x682e6ff3), UINT32_C(0x682e6ff3), 
	UINT32_C(0x748f82ee), UINT32_C(0x748f82ee), UINT32_C(0x748f82ee), UINT32_C(0x748f82ee), 
	UINT32_C(0x78a5636f), UINT32_C(0x78a5636f), UINT32_C(0x78a5636f), UINT32_C(0x78a5636f), 
	UINT32_C(0x84c87814), UINT32_C(0x84c87814), UINT32_C(0x84c87814), UINT32_C(0x84c87814), 
	UINT32_C(0x8cc70208), UINT32_C(0x8cc70208), UINT32_C(0x8cc70208), UINT32_C(0x8cc70208), 
	UINT32_C(0x90befffa), UINT32_C(0x90befffa), UINT32_C(0x90befffa), UINT32_C(0x90befffa), 
	UINT32_C(0xa4506ceb), UINT32_C(0xa4506ceb), UINT32_C(0xa4506ceb), UINT32_C(0xa4506ceb), 
	UINT32_C(0xbef9a3f7), UINT32_C(0xbef9a3f7), UINT32_C(0xbef9a3f7), UINT32_C(0xbef9a3f7), 
	UINT32_C(0xc67178f2), UINT32_C(0xc67178f2), UINT32_C(0xc67178f2), UINT32_C(0xc67178f2), 
};

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha256_block_plain_c(uint32_t state[8], const uint32_t W[16]) noexcept
{
	uint32_t H, E, F, G, D, A, B, C, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15;
	const uint32_t* consts = sha256_consts;

	// Load state
	H = state[7]; E = state[4]; F = state[5]; G = state[6];
	D = state[3]; A = state[0]; B = state[1]; C = state[2];
	W0  = W[ 0];	W1  = W[ 1];	W2  = W[ 2];	W3  = W[ 3];
	W4  = W[ 4];	W5  = W[ 5];	W6  = W[ 6];	W7  = W[ 7];
	W8  = W[ 8];	W9  = W[ 9];	W10 = W[10];	W11 = W[11];
	W12 = W[12];	W13 = W[13];	W14 = W[14];	W15 = W[15];

	// Round 1
	H += ((rotl(E, 26) ^ rotl(E, 21) ^ rotl(E,  7)) + (G ^ (E & (F ^ G)))) + consts[ 0] + W0 ;	D += H;	H += (rotl(A, 30) ^ rotl(A, 19) ^ rotl(A, 10)) + ((C & B) ^ (A & (C ^ B)));
	G += ((rotl(D, 26) ^ rotl(D, 21) ^ rotl(D,  7)) + (F ^ (D & (E ^ F)))) + consts[ 1] + W1 ;	C += G;	G += (rotl(H, 30) ^ rotl(H, 19) ^ rotl(H, 10)) + ((B & A) ^ (H & (B ^ A)));
	F += ((rotl(C, 26) ^ rotl(C, 21) ^ rotl(C,  7)) + (E ^ (C & (D ^ E)))) + consts[ 2] + W2 ;	B += F;	F += (rotl(G, 30) ^ rotl(G, 19) ^ rotl(G, 10)) + ((A & H) ^ (G & (A ^ H)));
	E += ((rotl(B, 26) ^ rotl(B, 21) ^ rotl(B,  7)) + (D ^ (B & (C ^ D)))) + consts[ 3] + W3 ;	A += E;	E += (rotl(F, 30) ^ rotl(F, 19) ^ rotl(F, 10)) + ((H & G) ^ (F & (H ^ G)));
	D += ((rotl(A, 26) ^ rotl(A, 21) ^ rotl(A,  7)) + (C ^ (A & (B ^ C)))) + consts[ 4] + W4 ;	H += D;	D += (rotl(E, 30) ^ rotl(E, 19) ^ rotl(E, 10)) + ((G & F) ^ (E & (G ^ F)));
	C += ((rotl(H, 26) ^ rotl(H, 21) ^ rotl(H,  7)) + (B ^ (H & (A ^ B)))) + consts[ 5] + W5 ;	G += C;	C += (rotl(D, 30) ^ rotl(D, 19) ^ rotl(D, 10)) + ((F & E) ^ (D & (F ^ E)));
	B += ((rotl(G, 26) ^ rotl(G, 21) ^ rotl(G,  7)) + (A ^ (G & (H ^ A)))) + consts[ 6] + W6 ;	F += B;	B += (rotl(C, 30) ^ rotl(C, 19) ^ rotl(C, 10)) + ((E & D) ^ (C & (E ^ D)));
	A += ((rotl(F, 26) ^ rotl(F, 21) ^ rotl(F,  7)) + (H ^ (F & (G ^ H)))) + consts[ 7] + W7 ;	E += A;	A += (rotl(B, 30) ^ rotl(B, 19) ^ rotl(B, 10)) + ((D & C) ^ (B & (D ^ C)));
	H += ((rotl(E, 26) ^ rotl(E, 21) ^ rotl(E,  7)) + (G ^ (E & (F ^ G)))) + consts[ 8] + W8 ;	D += H;	H += (rotl(A, 30) ^ rotl(A, 19) ^ rotl(A, 10)) + ((C & B) ^ (A & (C ^ B)));
	G += ((rotl(D, 26) ^ rotl(D, 21) ^ rotl(D,  7)) + (F ^ (D & (E ^ F)))) + consts[ 9] + W9 ;	C += G;	G += (rotl(H, 30) ^ rotl(H, 19) ^ rotl(H, 10)) + ((B & A) ^ (H & (B ^ A)));
	F += ((rotl(C, 26) ^ rotl(C, 21) ^ rotl(C,  7)) + (E ^ (C & (D ^ E)))) + consts[10] + W10;	B += F;	F += (rotl(G, 30) ^ rotl(G, 19) ^ rotl(G, 10)) + ((A & H) ^ (G & (A ^ H)));
	E += ((rotl(B, 26) ^ rotl(B, 21) ^ rotl(B,  7)) + (D ^ (B & (C ^ D)))) + consts[11] + W11;	A += E;	E += (rotl(F, 30) ^ rotl(F, 19) ^ rotl(F, 10)) + ((H & G) ^ (F & (H ^ G)));
	D += ((rotl(A, 26) ^ rotl(A, 21) ^ rotl(A,  7)) + (C ^ (A & (B ^ C)))) + consts[12] + W12;	H += D;	D += (rotl(E, 30) ^ rotl(E, 19) ^ rotl(E, 10)) + ((G & F) ^ (E & (G ^ F)));
	C += ((rotl(H, 26) ^ rotl(H, 21) ^ rotl(H,  7)) + (B ^ (H & (A ^ B)))) + consts[13] + W13;	G += C;	C += (rotl(D, 30) ^ rotl(D, 19) ^ rotl(D, 10)) + ((F & E) ^ (D & (F ^ E)));
	B += ((rotl(G, 26) ^ rotl(G, 21) ^ rotl(G,  7)) + (A ^ (G & (H ^ A)))) + consts[14] + W14;	F += B;	B += (rotl(C, 30) ^ rotl(C, 19) ^ rotl(C, 10)) + ((E & D) ^ (C & (E ^ D)));
	A += ((rotl(F, 26) ^ rotl(F, 21) ^ rotl(F,  7)) + (H ^ (F & (G ^ H)))) + consts[15] + W15;	E += A;	A += (rotl(B, 30) ^ rotl(B, 19) ^ rotl(B, 10)) + ((D & C) ^ (B & (D ^ C)));
	consts += 16;

	// Round 2-4
	for (int i = 0; i < 3; i++) {
		W0  += (rotl(W14, 15) ^ rotl(W14, 13) ^ (W14 >> 10)) + W9  + (rotl(W1 , 25) ^ rotl(W1 , 14) ^ (W1  >>  3));		H += (rotl(E, 26) ^ rotl(E, 21) ^ rotl(E,  7)) + (G ^ (E & (F ^ G))) + consts[ 0] + W0 ;		D += H;		H += (rotl(A, 30) ^ rotl(A, 19) ^ rotl(A, 10)) + ((C & B) ^ (A & (C ^ B)));
		W1  += (rotl(W15, 15) ^ rotl(W15, 13) ^ (W15 >> 10)) + W10 + (rotl(W2 , 25) ^ rotl(W2 , 14) ^ (W2  >>  3));		G += (rotl(D, 26) ^ rotl(D, 21) ^ rotl(D,  7)) + (F ^ (D & (E ^ F))) + consts[ 1] + W1 ;		C += G;		G += (rotl(H, 30) ^ rotl(H, 19) ^ rotl(H, 10)) + ((B & A) ^ (H & (B ^ A)));
		W2  += (rotl(W0 , 15) ^ rotl(W0 , 13) ^ (W0  >> 10)) + W11 + (rotl(W3 , 25) ^ rotl(W3 , 14) ^ (W3  >>  3));		F += (rotl(C, 26) ^ rotl(C, 21) ^ rotl(C,  7)) + (E ^ (C & (D ^ E))) + consts[ 2] + W2 ;		B += F;		F += (rotl(G, 30) ^ rotl(G, 19) ^ rotl(G, 10)) + ((A & H) ^ (G & (A ^ H)));
		W3  += (rotl(W1 , 15) ^ rotl(W1 , 13) ^ (W1  >> 10)) + W12 + (rotl(W4 , 25) ^ rotl(W4 , 14) ^ (W4  >>  3));		E += (rotl(B, 26) ^ rotl(B, 21) ^ rotl(B,  7)) + (D ^ (B & (C ^ D))) + consts[ 3] + W3 ;		A += E;		E += (rotl(F, 30) ^ rotl(F, 19) ^ rotl(F, 10)) + ((H & G) ^ (F & (H ^ G)));
		W4  += (rotl(W2 , 15) ^ rotl(W2 , 13) ^ (W2  >> 10)) + W13 + (rotl(W5 , 25) ^ rotl(W5 , 14) ^ (W5  >>  3));		D += (rotl(A, 26) ^ rotl(A, 21) ^ rotl(A,  7)) + (C ^ (A & (B ^ C))) + consts[ 4] + W4 ;		H += D;		D += (rotl(E, 30) ^ rotl(E, 19) ^ rotl(E, 10)) + ((G & F) ^ (E & (G ^ F)));
		W5  += (rotl(W3 , 15) ^ rotl(W3 , 13) ^ (W3  >> 10)) + W14 + (rotl(W6 , 25) ^ rotl(W6 , 14) ^ (W6  >>  3));		C += (rotl(H, 26) ^ rotl(H, 21) ^ rotl(H,  7)) + (B ^ (H & (A ^ B))) + consts[ 5] + W5 ;		G += C;		C += (rotl(D, 30) ^ rotl(D, 19) ^ rotl(D, 10)) + ((F & E) ^ (D & (F ^ E)));
		W6  += (rotl(W4 , 15) ^ rotl(W4 , 13) ^ (W4  >> 10)) + W15 + (rotl(W7 , 25) ^ rotl(W7 , 14) ^ (W7  >>  3));		B += (rotl(G, 26) ^ rotl(G, 21) ^ rotl(G,  7)) + (A ^ (G & (H ^ A))) + consts[ 6] + W6 ;		F += B;		B += (rotl(C, 30) ^ rotl(C, 19) ^ rotl(C, 10)) + ((E & D) ^ (C & (E ^ D)));
		W7  += (rotl(W5 , 15) ^ rotl(W5 , 13) ^ (W5  >> 10)) + W0  + (rotl(W8 , 25) ^ rotl(W8 , 14) ^ (W8  >>  3));		A += (rotl(F, 26) ^ rotl(F, 21) ^ rotl(F,  7)) + (H ^ (F & (G ^ H))) + consts[ 7] + W7 ;		E += A;		A += (rotl(B, 30) ^ rotl(B, 19) ^ rotl(B, 10)) + ((D & C) ^ (B & (D ^ C)));
		W8  += (rotl(W6 , 15) ^ rotl(W6 , 13) ^ (W6  >> 10)) + W1  + (rotl(W9 , 25) ^ rotl(W9 , 14) ^ (W9  >>  3));		H += (rotl(E, 26) ^ rotl(E, 21) ^ rotl(E,  7)) + (G ^ (E & (F ^ G))) + consts[ 8] + W8 ;		D += H;		H += (rotl(A, 30) ^ rotl(A, 19) ^ rotl(A, 10)) + ((C & B) ^ (A & (C ^ B)));
		W9  += (rotl(W7 , 15) ^ rotl(W7 , 13) ^ (W7  >> 10)) + W2  + (rotl(W10, 25) ^ rotl(W10, 14) ^ (W10 >>  3));		G += (rotl(D, 26) ^ rotl(D, 21) ^ rotl(D,  7)) + (F ^ (D & (E ^ F))) + consts[ 9] + W9 ;		C += G;		G += (rotl(H, 30) ^ rotl(H, 19) ^ rotl(H, 10)) + ((B & A) ^ (H & (B ^ A)));
		W10 += (rotl(W8 , 15) ^ rotl(W8 , 13) ^ (W8  >> 10)) + W3  + (rotl(W11, 25) ^ rotl(W11, 14) ^ (W11 >>  3));		F += (rotl(C, 26) ^ rotl(C, 21) ^ rotl(C,  7)) + (E ^ (C & (D ^ E))) + consts[10] + W10;		B += F;		F += (rotl(G, 30) ^ rotl(G, 19) ^ rotl(G, 10)) + ((A & H) ^ (G & (A ^ H)));
		W11 += (rotl(W9 , 15) ^ rotl(W9 , 13) ^ (W9  >> 10)) + W4  + (rotl(W12, 25) ^ rotl(W12, 14) ^ (W12 >>  3));		E += (rotl(B, 26) ^ rotl(B, 21) ^ rotl(B,  7)) + (D ^ (B & (C ^ D))) + consts[11] + W11;		A += E;		E += (rotl(F, 30) ^ rotl(F, 19) ^ rotl(F, 10)) + ((H & G) ^ (F & (H ^ G)));
		W12 += (rotl(W10, 15) ^ rotl(W10, 13) ^ (W10 >> 10)) + W5  + (rotl(W13, 25) ^ rotl(W13, 14) ^ (W13 >>  3));		D += (rotl(A, 26) ^ rotl(A, 21) ^ rotl(A,  7)) + (C ^ (A & (B ^ C))) + consts[12] + W12;		H += D;		D += (rotl(E, 30) ^ rotl(E, 19) ^ rotl(E, 10)) + ((G & F) ^ (E & (G ^ F)));
		W13 += (rotl(W11, 15) ^ rotl(W11, 13) ^ (W11 >> 10)) + W6  + (rotl(W14, 25) ^ rotl(W14, 14) ^ (W14 >>  3));		C += (rotl(H, 26) ^ rotl(H, 21) ^ rotl(H,  7)) + (B ^ (H & (A ^ B))) + consts[13] + W13;		G += C;		C += (rotl(D, 30) ^ rotl(D, 19) ^ rotl(D, 10)) + ((F & E) ^ (D & (F ^ E)));
		W14 += (rotl(W12, 15) ^ rotl(W12, 13) ^ (W12 >> 10)) + W7  + (rotl(W15, 25) ^ rotl(W15, 14) ^ (W15 >>  3));		B += (rotl(G, 26) ^ rotl(G, 21) ^ rotl(G,  7)) + (A ^ (G & (H ^ A))) + consts[14] + W14;		F += B;		B += (rotl(C, 30) ^ rotl(C, 19) ^ rotl(C, 10)) + ((E & D) ^ (C & (E ^ D)));
		W15 += (rotl(W13, 15) ^ rotl(W13, 13) ^ (W13 >> 10)) + W8  + (rotl(W0 , 25) ^ rotl(W0 , 14) ^ (W0  >>  3));		A += (rotl(F, 26) ^ rotl(F, 21) ^ rotl(F,  7)) + (H ^ (F & (G ^ H))) + consts[15] + W15;		E += A;		A += (rotl(B, 30) ^ rotl(B, 19) ^ rotl(B, 10)) + ((D & C) ^ (B & (D ^ C)));
		consts += 16;
	}

	// Save state  
	state[7] += H;
	state[3] += D;
	state[6] += G;
	state[2] += C;
	state[5] += F;
	state[1] += B;
	state[4] += E;
	state[0] += A;
}

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha256_block_sse2(simd::Vec128u32 state[8], const simd::Vec128u32 W[16]) noexcept
{
	simd::Vec128u32 H, E, F, G, D, A, B, C, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15;
	const simd::Vec128u32* consts = reinterpret_cast<const simd::Vec128u32*>(sha256_consts_vec128);

	// Load state
	H = load(state + 7); E = load(state + 4); F = load(state + 5);	G = load(state + 6);
	D = load(state + 3); A = load(state + 0); B = load(state + 1);	C = load(state + 2);
	W0  = load(W +  0);	W1  = load(W +  1);	W2  = load(W +  2);	W3  = load(W +  3);
	W4  = load(W +  4);	W5  = load(W +  5);	W6  = load(W +  6);	W7  = load(W +  7);
	W8  = load(W +  8);	W9  = load(W +  9);	W10 = load(W + 10);	W11 = load(W + 11);
	W12 = load(W + 12);	W13 = load(W + 13);	W14 = load(W + 14);	W15 = load(W + 15);

	// Round 1
	H += (rotl<uint32_t, 26>(E, 26) ^ rotl<uint32_t, 21>(E, 21) ^ rotl<uint32_t,  7>(E,  7)) + (G ^ (E & (F ^ G))) + load(consts +  0) + W0 ;	D += H;	H += (rotl<uint32_t, 30>(A, 30) ^ rotl<uint32_t, 19>(A, 19) ^ rotl<uint32_t, 10>(A, 10)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl<uint32_t, 26>(D, 26) ^ rotl<uint32_t, 21>(D, 21) ^ rotl<uint32_t,  7>(D,  7)) + (F ^ (D & (E ^ F))) + load(consts +  1) + W1 ;	C += G;	G += (rotl<uint32_t, 30>(H, 30) ^ rotl<uint32_t, 19>(H, 19) ^ rotl<uint32_t, 10>(H, 10)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl<uint32_t, 26>(C, 26) ^ rotl<uint32_t, 21>(C, 21) ^ rotl<uint32_t,  7>(C,  7)) + (E ^ (C & (D ^ E))) + load(consts +  2) + W2 ;	B += F;	F += (rotl<uint32_t, 30>(G, 30) ^ rotl<uint32_t, 19>(G, 19) ^ rotl<uint32_t, 10>(G, 10)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl<uint32_t, 26>(B, 26) ^ rotl<uint32_t, 21>(B, 21) ^ rotl<uint32_t,  7>(B,  7)) + (D ^ (B & (C ^ D))) + load(consts +  3) + W3 ;	A += E;	E += (rotl<uint32_t, 30>(F, 30) ^ rotl<uint32_t, 19>(F, 19) ^ rotl<uint32_t, 10>(F, 10)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl<uint32_t, 26>(A, 26) ^ rotl<uint32_t, 21>(A, 21) ^ rotl<uint32_t,  7>(A,  7)) + (C ^ (A & (B ^ C))) + load(consts +  4) + W4 ;	H += D;	D += (rotl<uint32_t, 30>(E, 30) ^ rotl<uint32_t, 19>(E, 19) ^ rotl<uint32_t, 10>(E, 10)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl<uint32_t, 26>(H, 26) ^ rotl<uint32_t, 21>(H, 21) ^ rotl<uint32_t,  7>(H,  7)) + (B ^ (H & (A ^ B))) + load(consts +  5) + W5 ;	G += C;	C += (rotl<uint32_t, 30>(D, 30) ^ rotl<uint32_t, 19>(D, 19) ^ rotl<uint32_t, 10>(D, 10)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl<uint32_t, 26>(G, 26) ^ rotl<uint32_t, 21>(G, 21) ^ rotl<uint32_t,  7>(G,  7)) + (A ^ (G & (H ^ A))) + load(consts +  6) + W6 ;	F += B;	B += (rotl<uint32_t, 30>(C, 30) ^ rotl<uint32_t, 19>(C, 19) ^ rotl<uint32_t, 10>(C, 10)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl<uint32_t, 26>(F, 26) ^ rotl<uint32_t, 21>(F, 21) ^ rotl<uint32_t,  7>(F,  7)) + (H ^ (F & (G ^ H))) + load(consts +  7) + W7 ;	E += A;	A += (rotl<uint32_t, 30>(B, 30) ^ rotl<uint32_t, 19>(B, 19) ^ rotl<uint32_t, 10>(B, 10)) + ((D & C) ^ (B & (D ^ C)));
	H += (rotl<uint32_t, 26>(E, 26) ^ rotl<uint32_t, 21>(E, 21) ^ rotl<uint32_t,  7>(E,  7)) + (G ^ (E & (F ^ G))) + load(consts +  8) + W8 ;	D += H;	H += (rotl<uint32_t, 30>(A, 30) ^ rotl<uint32_t, 19>(A, 19) ^ rotl<uint32_t, 10>(A, 10)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl<uint32_t, 26>(D, 26) ^ rotl<uint32_t, 21>(D, 21) ^ rotl<uint32_t,  7>(D,  7)) + (F ^ (D & (E ^ F))) + load(consts +  9) + W9 ;	C += G;	G += (rotl<uint32_t, 30>(H, 30) ^ rotl<uint32_t, 19>(H, 19) ^ rotl<uint32_t, 10>(H, 10)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl<uint32_t, 26>(C, 26) ^ rotl<uint32_t, 21>(C, 21) ^ rotl<uint32_t,  7>(C,  7)) + (E ^ (C & (D ^ E))) + load(consts + 10) + W10;	B += F;	F += (rotl<uint32_t, 30>(G, 30) ^ rotl<uint32_t, 19>(G, 19) ^ rotl<uint32_t, 10>(G, 10)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl<uint32_t, 26>(B, 26) ^ rotl<uint32_t, 21>(B, 21) ^ rotl<uint32_t,  7>(B,  7)) + (D ^ (B & (C ^ D))) + load(consts + 11) + W11;	A += E;	E += (rotl<uint32_t, 30>(F, 30) ^ rotl<uint32_t, 19>(F, 19) ^ rotl<uint32_t, 10>(F, 10)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl<uint32_t, 26>(A, 26) ^ rotl<uint32_t, 21>(A, 21) ^ rotl<uint32_t,  7>(A,  7)) + (C ^ (A & (B ^ C))) + load(consts + 12) + W12;	H += D;	D += (rotl<uint32_t, 30>(E, 30) ^ rotl<uint32_t, 19>(E, 19) ^ rotl<uint32_t, 10>(E, 10)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl<uint32_t, 26>(H, 26) ^ rotl<uint32_t, 21>(H, 21) ^ rotl<uint32_t,  7>(H,  7)) + (B ^ (H & (A ^ B))) + load(consts + 13) + W13;	G += C;	C += (rotl<uint32_t, 30>(D, 30) ^ rotl<uint32_t, 19>(D, 19) ^ rotl<uint32_t, 10>(D, 10)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl<uint32_t, 26>(G, 26) ^ rotl<uint32_t, 21>(G, 21) ^ rotl<uint32_t,  7>(G,  7)) + (A ^ (G & (H ^ A))) + load(consts + 14) + W14;	F += B;	B += (rotl<uint32_t, 30>(C, 30) ^ rotl<uint32_t, 19>(C, 19) ^ rotl<uint32_t, 10>(C, 10)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl<uint32_t, 26>(F, 26) ^ rotl<uint32_t, 21>(F, 21) ^ rotl<uint32_t,  7>(F,  7)) + (H ^ (F & (G ^ H))) + load(consts + 15) + W15;	E += A;	A += (rotl<uint32_t, 30>(B, 30) ^ rotl<uint32_t, 19>(B, 19) ^ rotl<uint32_t, 10>(B, 10)) + ((D & C) ^ (B & (D ^ C)));
	consts += 16;

	// Round 2-4
	for (int i = 0; i < 3; i++) {
		W0  += (rotl<uint32_t, 15>(W14, 15) ^ rotl<uint32_t, 13>(W14, 13) ^ (W14 >> 10)) + W9  + (rotl<uint32_t, 25>(W1 , 25) ^ rotl<uint32_t, 14>(W1 , 14) ^ (W1  >>  3));		H += (rotl<uint32_t, 26>(E, 26) ^ rotl<uint32_t, 21>(E, 21) ^ rotl<uint32_t,  7>(E,  7)) + (G ^ (E & (F ^ G))) + load(consts +  0) + W0 ;		D += H;		H += (rotl<uint32_t, 30>(A, 30) ^ rotl<uint32_t, 19>(A, 19) ^ rotl<uint32_t, 10>(A, 10)) + ((C & B) ^ (A & (C ^ B)));
		W1  += (rotl<uint32_t, 15>(W15, 15) ^ rotl<uint32_t, 13>(W15, 13) ^ (W15 >> 10)) + W10 + (rotl<uint32_t, 25>(W2 , 25) ^ rotl<uint32_t, 14>(W2 , 14) ^ (W2  >>  3));		G += (rotl<uint32_t, 26>(D, 26) ^ rotl<uint32_t, 21>(D, 21) ^ rotl<uint32_t,  7>(D,  7)) + (F ^ (D & (E ^ F))) + load(consts +  1) + W1 ;		C += G;		G += (rotl<uint32_t, 30>(H, 30) ^ rotl<uint32_t, 19>(H, 19) ^ rotl<uint32_t, 10>(H, 10)) + ((B & A) ^ (H & (B ^ A)));
		W2  += (rotl<uint32_t, 15>(W0 , 15) ^ rotl<uint32_t, 13>(W0 , 13) ^ (W0  >> 10)) + W11 + (rotl<uint32_t, 25>(W3 , 25) ^ rotl<uint32_t, 14>(W3 , 14) ^ (W3  >>  3));		F += (rotl<uint32_t, 26>(C, 26) ^ rotl<uint32_t, 21>(C, 21) ^ rotl<uint32_t,  7>(C,  7)) + (E ^ (C & (D ^ E))) + load(consts +  2) + W2 ;		B += F;		F += (rotl<uint32_t, 30>(G, 30) ^ rotl<uint32_t, 19>(G, 19) ^ rotl<uint32_t, 10>(G, 10)) + ((A & H) ^ (G & (A ^ H)));
		W3  += (rotl<uint32_t, 15>(W1 , 15) ^ rotl<uint32_t, 13>(W1 , 13) ^ (W1  >> 10)) + W12 + (rotl<uint32_t, 25>(W4 , 25) ^ rotl<uint32_t, 14>(W4 , 14) ^ (W4  >>  3));		E += (rotl<uint32_t, 26>(B, 26) ^ rotl<uint32_t, 21>(B, 21) ^ rotl<uint32_t,  7>(B,  7)) + (D ^ (B & (C ^ D))) + load(consts +  3) + W3 ;		A += E;		E += (rotl<uint32_t, 30>(F, 30) ^ rotl<uint32_t, 19>(F, 19) ^ rotl<uint32_t, 10>(F, 10)) + ((H & G) ^ (F & (H ^ G)));
		W4  += (rotl<uint32_t, 15>(W2 , 15) ^ rotl<uint32_t, 13>(W2 , 13) ^ (W2  >> 10)) + W13 + (rotl<uint32_t, 25>(W5 , 25) ^ rotl<uint32_t, 14>(W5 , 14) ^ (W5  >>  3));		D += (rotl<uint32_t, 26>(A, 26) ^ rotl<uint32_t, 21>(A, 21) ^ rotl<uint32_t,  7>(A,  7)) + (C ^ (A & (B ^ C))) + load(consts +  4) + W4 ;		H += D;		D += (rotl<uint32_t, 30>(E, 30) ^ rotl<uint32_t, 19>(E, 19) ^ rotl<uint32_t, 10>(E, 10)) + ((G & F) ^ (E & (G ^ F)));
		W5  += (rotl<uint32_t, 15>(W3 , 15) ^ rotl<uint32_t, 13>(W3 , 13) ^ (W3  >> 10)) + W14 + (rotl<uint32_t, 25>(W6 , 25) ^ rotl<uint32_t, 14>(W6 , 14) ^ (W6  >>  3));		C += (rotl<uint32_t, 26>(H, 26) ^ rotl<uint32_t, 21>(H, 21) ^ rotl<uint32_t,  7>(H,  7)) + (B ^ (H & (A ^ B))) + load(consts +  5) + W5 ;		G += C;		C += (rotl<uint32_t, 30>(D, 30) ^ rotl<uint32_t, 19>(D, 19) ^ rotl<uint32_t, 10>(D, 10)) + ((F & E) ^ (D & (F ^ E)));
		W6  += (rotl<uint32_t, 15>(W4 , 15) ^ rotl<uint32_t, 13>(W4 , 13) ^ (W4  >> 10)) + W15 + (rotl<uint32_t, 25>(W7 , 25) ^ rotl<uint32_t, 14>(W7 , 14) ^ (W7  >>  3));		B += (rotl<uint32_t, 26>(G, 26) ^ rotl<uint32_t, 21>(G, 21) ^ rotl<uint32_t,  7>(G,  7)) + (A ^ (G & (H ^ A))) + load(consts +  6) + W6 ;		F += B;		B += (rotl<uint32_t, 30>(C, 30) ^ rotl<uint32_t, 19>(C, 19) ^ rotl<uint32_t, 10>(C, 10)) + ((E & D) ^ (C & (E ^ D)));
		W7  += (rotl<uint32_t, 15>(W5 , 15) ^ rotl<uint32_t, 13>(W5 , 13) ^ (W5  >> 10)) + W0  + (rotl<uint32_t, 25>(W8 , 25) ^ rotl<uint32_t, 14>(W8 , 14) ^ (W8  >>  3));		A += (rotl<uint32_t, 26>(F, 26) ^ rotl<uint32_t, 21>(F, 21) ^ rotl<uint32_t,  7>(F,  7)) + (H ^ (F & (G ^ H))) + load(consts +  7) + W7 ;		E += A;		A += (rotl<uint32_t, 30>(B, 30) ^ rotl<uint32_t, 19>(B, 19) ^ rotl<uint32_t, 10>(B, 10)) + ((D & C) ^ (B & (D ^ C)));
		W8  += (rotl<uint32_t, 15>(W6 , 15) ^ rotl<uint32_t, 13>(W6 , 13) ^ (W6  >> 10)) + W1  + (rotl<uint32_t, 25>(W9 , 25) ^ rotl<uint32_t, 14>(W9 , 14) ^ (W9  >>  3));		H += (rotl<uint32_t, 26>(E, 26) ^ rotl<uint32_t, 21>(E, 21) ^ rotl<uint32_t,  7>(E,  7)) + (G ^ (E & (F ^ G))) + load(consts +  8) + W8 ;		D += H;		H += (rotl<uint32_t, 30>(A, 30) ^ rotl<uint32_t, 19>(A, 19) ^ rotl<uint32_t, 10>(A, 10)) + ((C & B) ^ (A & (C ^ B)));
		W9  += (rotl<uint32_t, 15>(W7 , 15) ^ rotl<uint32_t, 13>(W7 , 13) ^ (W7  >> 10)) + W2  + (rotl<uint32_t, 25>(W10, 25) ^ rotl<uint32_t, 14>(W10, 14) ^ (W10 >>  3));		G += (rotl<uint32_t, 26>(D, 26) ^ rotl<uint32_t, 21>(D, 21) ^ rotl<uint32_t,  7>(D,  7)) + (F ^ (D & (E ^ F))) + load(consts +  9) + W9 ;		C += G;		G += (rotl<uint32_t, 30>(H, 30) ^ rotl<uint32_t, 19>(H, 19) ^ rotl<uint32_t, 10>(H, 10)) + ((B & A) ^ (H & (B ^ A)));
		W10 += (rotl<uint32_t, 15>(W8 , 15) ^ rotl<uint32_t, 13>(W8 , 13) ^ (W8  >> 10)) + W3  + (rotl<uint32_t, 25>(W11, 25) ^ rotl<uint32_t, 14>(W11, 14) ^ (W11 >>  3));		F += (rotl<uint32_t, 26>(C, 26) ^ rotl<uint32_t, 21>(C, 21) ^ rotl<uint32_t,  7>(C,  7)) + (E ^ (C & (D ^ E))) + load(consts + 10) + W10;		B += F;		F += (rotl<uint32_t, 30>(G, 30) ^ rotl<uint32_t, 19>(G, 19) ^ rotl<uint32_t, 10>(G, 10)) + ((A & H) ^ (G & (A ^ H)));
		W11 += (rotl<uint32_t, 15>(W9 , 15) ^ rotl<uint32_t, 13>(W9 , 13) ^ (W9  >> 10)) + W4  + (rotl<uint32_t, 25>(W12, 25) ^ rotl<uint32_t, 14>(W12, 14) ^ (W12 >>  3));		E += (rotl<uint32_t, 26>(B, 26) ^ rotl<uint32_t, 21>(B, 21) ^ rotl<uint32_t,  7>(B,  7)) + (D ^ (B & (C ^ D))) + load(consts + 11) + W11;		A += E;		E += (rotl<uint32_t, 30>(F, 30) ^ rotl<uint32_t, 19>(F, 19) ^ rotl<uint32_t, 10>(F, 10)) + ((H & G) ^ (F & (H ^ G)));
		W12 += (rotl<uint32_t, 15>(W10, 15) ^ rotl<uint32_t, 13>(W10, 13) ^ (W10 >> 10)) + W5  + (rotl<uint32_t, 25>(W13, 25) ^ rotl<uint32_t, 14>(W13, 14) ^ (W13 >>  3));		D += (rotl<uint32_t, 26>(A, 26) ^ rotl<uint32_t, 21>(A, 21) ^ rotl<uint32_t,  7>(A,  7)) + (C ^ (A & (B ^ C))) + load(consts + 12) + W12;		H += D;		D += (rotl<uint32_t, 30>(E, 30) ^ rotl<uint32_t, 19>(E, 19) ^ rotl<uint32_t, 10>(E, 10)) + ((G & F) ^ (E & (G ^ F)));
		W13 += (rotl<uint32_t, 15>(W11, 15) ^ rotl<uint32_t, 13>(W11, 13) ^ (W11 >> 10)) + W6  + (rotl<uint32_t, 25>(W14, 25) ^ rotl<uint32_t, 14>(W14, 14) ^ (W14 >>  3));		C += (rotl<uint32_t, 26>(H, 26) ^ rotl<uint32_t, 21>(H, 21) ^ rotl<uint32_t,  7>(H,  7)) + (B ^ (H & (A ^ B))) + load(consts + 13) + W13;		G += C;		C += (rotl<uint32_t, 30>(D, 30) ^ rotl<uint32_t, 19>(D, 19) ^ rotl<uint32_t, 10>(D, 10)) + ((F & E) ^ (D & (F ^ E)));
		W14 += (rotl<uint32_t, 15>(W12, 15) ^ rotl<uint32_t, 13>(W12, 13) ^ (W12 >> 10)) + W7  + (rotl<uint32_t, 25>(W15, 25) ^ rotl<uint32_t, 14>(W15, 14) ^ (W15 >>  3));		B += (rotl<uint32_t, 26>(G, 26) ^ rotl<uint32_t, 21>(G, 21) ^ rotl<uint32_t,  7>(G,  7)) + (A ^ (G & (H ^ A))) + load(consts + 14) + W14;		F += B;		B += (rotl<uint32_t, 30>(C, 30) ^ rotl<uint32_t, 19>(C, 19) ^ rotl<uint32_t, 10>(C, 10)) + ((E & D) ^ (C & (E ^ D)));
		W15 += (rotl<uint32_t, 15>(W13, 15) ^ rotl<uint32_t, 13>(W13, 13) ^ (W13 >> 10)) + W8  + (rotl<uint32_t, 25>(W0 , 25) ^ rotl<uint32_t, 14>(W0 , 14) ^ (W0  >>  3));		A += (rotl<uint32_t, 26>(F, 26) ^ rotl<uint32_t, 21>(F, 21) ^ rotl<uint32_t,  7>(F,  7)) + (H ^ (F & (G ^ H))) + load(consts + 15) + W15;		E += A;		A += (rotl<uint32_t, 30>(B, 30) ^ rotl<uint32_t, 19>(B, 19) ^ rotl<uint32_t, 10>(B, 10)) + ((D & C) ^ (B & (D ^ C)));
		consts += 16;
	}

	// Save state  
	store(state +  7, load(state +  7) + H);
	store(state +  3, load(state +  3) + D);
	store(state +  6, load(state +  6) + G);
	store(state +  2, load(state +  2) + C);
	store(state +  5, load(state +  5) + F);
	store(state +  1, load(state +  1) + B);
	store(state +  4, load(state +  4) + E);
	store(state +  0, load(state +  0) + A);
}

