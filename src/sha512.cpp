//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#include "sha512_internal.h"

alignas(64) const uint64_t sha512_consts[80] = {
	UINT64_C(0x428a2f98d728ae22),
	UINT64_C(0x7137449123ef65cd),
	UINT64_C(0xb5c0fbcfec4d3b2f),
	UINT64_C(0xe9b5dba58189dbbc),
	UINT64_C(0x3956c25bf348b538),
	UINT64_C(0x59f111f1b605d019),
	UINT64_C(0x923f82a4af194f9b),
	UINT64_C(0xab1c5ed5da6d8118),
	UINT64_C(0xd807aa98a3030242),
	UINT64_C(0x12835b0145706fbe),
	UINT64_C(0x243185be4ee4b28c),
	UINT64_C(0x550c7dc3d5ffb4e2),
	UINT64_C(0x72be5d74f27b896f),
	UINT64_C(0x80deb1fe3b1696b1),
	UINT64_C(0x9bdc06a725c71235),
	UINT64_C(0xc19bf174cf692694),
	UINT64_C(0xe49b69c19ef14ad2),
	UINT64_C(0xefbe4786384f25e3),
	UINT64_C(0xfc19dc68b8cd5b5),
	UINT64_C(0x240ca1cc77ac9c65),
	UINT64_C(0x2de92c6f592b0275),
	UINT64_C(0x4a7484aa6ea6e483),
	UINT64_C(0x5cb0a9dcbd41fbd4),
	UINT64_C(0x76f988da831153b5),
	UINT64_C(0x983e5152ee66dfab),
	UINT64_C(0xa831c66d2db43210),
	UINT64_C(0xb00327c898fb213f),
	UINT64_C(0xbf597fc7beef0ee4),
	UINT64_C(0xc6e00bf33da88fc2),
	UINT64_C(0xd5a79147930aa725),
	UINT64_C(0x6ca6351e003826f),
	UINT64_C(0x142929670a0e6e70),
	UINT64_C(0x27b70a8546d22ffc),
	UINT64_C(0x2e1b21385c26c926),
	UINT64_C(0x4d2c6dfc5ac42aed),
	UINT64_C(0x53380d139d95b3df),
	UINT64_C(0x650a73548baf63de),
	UINT64_C(0x766a0abb3c77b2a8),
	UINT64_C(0x81c2c92e47edaee6),
	UINT64_C(0x92722c851482353b),
	UINT64_C(0xa2bfe8a14cf10364),
	UINT64_C(0xa81a664bbc423001),
	UINT64_C(0xc24b8b70d0f89791),
	UINT64_C(0xc76c51a30654be30),
	UINT64_C(0xd192e819d6ef5218),
	UINT64_C(0xd69906245565a910),
	UINT64_C(0xf40e35855771202a),
	UINT64_C(0x106aa07032bbd1b8),
	UINT64_C(0x19a4c116b8d2d0c8),
	UINT64_C(0x1e376c085141ab53),
	UINT64_C(0x2748774cdf8eeb99),
	UINT64_C(0x34b0bcb5e19b48a8),
	UINT64_C(0x391c0cb3c5c95a63),
	UINT64_C(0x4ed8aa4ae3418acb),
	UINT64_C(0x5b9cca4f7763e373),
	UINT64_C(0x682e6ff3d6b2b8a3),
	UINT64_C(0x748f82ee5defb2fc),
	UINT64_C(0x78a5636f43172f60),
	UINT64_C(0x84c87814a1f0ab72),
	UINT64_C(0x8cc702081a6439ec),
	UINT64_C(0x90befffa23631e28),
	UINT64_C(0xa4506cebde82bde9),
	UINT64_C(0xbef9a3f7b2c67915),
	UINT64_C(0xc67178f2e372532b),
	UINT64_C(0xca273eceea26619c),
	UINT64_C(0xd186b8c721c0c207),
	UINT64_C(0xeada7dd6cde0eb1e),
	UINT64_C(0xf57d4f7fee6ed178),
	UINT64_C(0x6f067aa72176fba),
	UINT64_C(0xa637dc5a2c898a6),
	UINT64_C(0x113f9804bef90dae),
	UINT64_C(0x1b710b35131c471b),
	UINT64_C(0x28db77f523047d84),
	UINT64_C(0x32caab7b40c72493),
	UINT64_C(0x3c9ebe0a15c9bebc),
	UINT64_C(0x431d67c49c100d4c),
	UINT64_C(0x4cc5d4becb3e42b6),
	UINT64_C(0x597f299cfc657e2a),
	UINT64_C(0x5fcb6fab3ad6faec),
	UINT64_C(0x6c44198c4a475817),
};
alignas(64) const uint64_t sha512_consts_vec128[160] = {
	UINT64_C(0x428a2f98d728ae22), UINT64_C(0x428a2f98d728ae22), 
	UINT64_C(0x7137449123ef65cd), UINT64_C(0x7137449123ef65cd), 
	UINT64_C(0xb5c0fbcfec4d3b2f), UINT64_C(0xb5c0fbcfec4d3b2f), 
	UINT64_C(0xe9b5dba58189dbbc), UINT64_C(0xe9b5dba58189dbbc), 
	UINT64_C(0x3956c25bf348b538), UINT64_C(0x3956c25bf348b538), 
	UINT64_C(0x59f111f1b605d019), UINT64_C(0x59f111f1b605d019), 
	UINT64_C(0x923f82a4af194f9b), UINT64_C(0x923f82a4af194f9b), 
	UINT64_C(0xab1c5ed5da6d8118), UINT64_C(0xab1c5ed5da6d8118), 
	UINT64_C(0xd807aa98a3030242), UINT64_C(0xd807aa98a3030242), 
	UINT64_C(0x12835b0145706fbe), UINT64_C(0x12835b0145706fbe), 
	UINT64_C(0x243185be4ee4b28c), UINT64_C(0x243185be4ee4b28c), 
	UINT64_C(0x550c7dc3d5ffb4e2), UINT64_C(0x550c7dc3d5ffb4e2), 
	UINT64_C(0x72be5d74f27b896f), UINT64_C(0x72be5d74f27b896f), 
	UINT64_C(0x80deb1fe3b1696b1), UINT64_C(0x80deb1fe3b1696b1), 
	UINT64_C(0x9bdc06a725c71235), UINT64_C(0x9bdc06a725c71235), 
	UINT64_C(0xc19bf174cf692694), UINT64_C(0xc19bf174cf692694), 
	UINT64_C(0xe49b69c19ef14ad2), UINT64_C(0xe49b69c19ef14ad2), 
	UINT64_C(0xefbe4786384f25e3), UINT64_C(0xefbe4786384f25e3), 
	UINT64_C(0xfc19dc68b8cd5b5), UINT64_C(0xfc19dc68b8cd5b5), 
	UINT64_C(0x240ca1cc77ac9c65), UINT64_C(0x240ca1cc77ac9c65), 
	UINT64_C(0x2de92c6f592b0275), UINT64_C(0x2de92c6f592b0275), 
	UINT64_C(0x4a7484aa6ea6e483), UINT64_C(0x4a7484aa6ea6e483), 
	UINT64_C(0x5cb0a9dcbd41fbd4), UINT64_C(0x5cb0a9dcbd41fbd4), 
	UINT64_C(0x76f988da831153b5), UINT64_C(0x76f988da831153b5), 
	UINT64_C(0x983e5152ee66dfab), UINT64_C(0x983e5152ee66dfab), 
	UINT64_C(0xa831c66d2db43210), UINT64_C(0xa831c66d2db43210), 
	UINT64_C(0xb00327c898fb213f), UINT64_C(0xb00327c898fb213f), 
	UINT64_C(0xbf597fc7beef0ee4), UINT64_C(0xbf597fc7beef0ee4), 
	UINT64_C(0xc6e00bf33da88fc2), UINT64_C(0xc6e00bf33da88fc2), 
	UINT64_C(0xd5a79147930aa725), UINT64_C(0xd5a79147930aa725), 
	UINT64_C(0x6ca6351e003826f), UINT64_C(0x6ca6351e003826f), 
	UINT64_C(0x142929670a0e6e70), UINT64_C(0x142929670a0e6e70), 
	UINT64_C(0x27b70a8546d22ffc), UINT64_C(0x27b70a8546d22ffc), 
	UINT64_C(0x2e1b21385c26c926), UINT64_C(0x2e1b21385c26c926), 
	UINT64_C(0x4d2c6dfc5ac42aed), UINT64_C(0x4d2c6dfc5ac42aed), 
	UINT64_C(0x53380d139d95b3df), UINT64_C(0x53380d139d95b3df), 
	UINT64_C(0x650a73548baf63de), UINT64_C(0x650a73548baf63de), 
	UINT64_C(0x766a0abb3c77b2a8), UINT64_C(0x766a0abb3c77b2a8), 
	UINT64_C(0x81c2c92e47edaee6), UINT64_C(0x81c2c92e47edaee6), 
	UINT64_C(0x92722c851482353b), UINT64_C(0x92722c851482353b), 
	UINT64_C(0xa2bfe8a14cf10364), UINT64_C(0xa2bfe8a14cf10364), 
	UINT64_C(0xa81a664bbc423001), UINT64_C(0xa81a664bbc423001), 
	UINT64_C(0xc24b8b70d0f89791), UINT64_C(0xc24b8b70d0f89791), 
	UINT64_C(0xc76c51a30654be30), UINT64_C(0xc76c51a30654be30), 
	UINT64_C(0xd192e819d6ef5218), UINT64_C(0xd192e819d6ef5218), 
	UINT64_C(0xd69906245565a910), UINT64_C(0xd69906245565a910), 
	UINT64_C(0xf40e35855771202a), UINT64_C(0xf40e35855771202a), 
	UINT64_C(0x106aa07032bbd1b8), UINT64_C(0x106aa07032bbd1b8), 
	UINT64_C(0x19a4c116b8d2d0c8), UINT64_C(0x19a4c116b8d2d0c8), 
	UINT64_C(0x1e376c085141ab53), UINT64_C(0x1e376c085141ab53), 
	UINT64_C(0x2748774cdf8eeb99), UINT64_C(0x2748774cdf8eeb99), 
	UINT64_C(0x34b0bcb5e19b48a8), UINT64_C(0x34b0bcb5e19b48a8), 
	UINT64_C(0x391c0cb3c5c95a63), UINT64_C(0x391c0cb3c5c95a63), 
	UINT64_C(0x4ed8aa4ae3418acb), UINT64_C(0x4ed8aa4ae3418acb), 
	UINT64_C(0x5b9cca4f7763e373), UINT64_C(0x5b9cca4f7763e373), 
	UINT64_C(0x682e6ff3d6b2b8a3), UINT64_C(0x682e6ff3d6b2b8a3), 
	UINT64_C(0x748f82ee5defb2fc), UINT64_C(0x748f82ee5defb2fc), 
	UINT64_C(0x78a5636f43172f60), UINT64_C(0x78a5636f43172f60), 
	UINT64_C(0x84c87814a1f0ab72), UINT64_C(0x84c87814a1f0ab72), 
	UINT64_C(0x8cc702081a6439ec), UINT64_C(0x8cc702081a6439ec), 
	UINT64_C(0x90befffa23631e28), UINT64_C(0x90befffa23631e28), 
	UINT64_C(0xa4506cebde82bde9), UINT64_C(0xa4506cebde82bde9), 
	UINT64_C(0xbef9a3f7b2c67915), UINT64_C(0xbef9a3f7b2c67915), 
	UINT64_C(0xc67178f2e372532b), UINT64_C(0xc67178f2e372532b), 
	UINT64_C(0xca273eceea26619c), UINT64_C(0xca273eceea26619c), 
	UINT64_C(0xd186b8c721c0c207), UINT64_C(0xd186b8c721c0c207), 
	UINT64_C(0xeada7dd6cde0eb1e), UINT64_C(0xeada7dd6cde0eb1e), 
	UINT64_C(0xf57d4f7fee6ed178), UINT64_C(0xf57d4f7fee6ed178), 
	UINT64_C(0x6f067aa72176fba), UINT64_C(0x6f067aa72176fba), 
	UINT64_C(0xa637dc5a2c898a6), UINT64_C(0xa637dc5a2c898a6), 
	UINT64_C(0x113f9804bef90dae), UINT64_C(0x113f9804bef90dae), 
	UINT64_C(0x1b710b35131c471b), UINT64_C(0x1b710b35131c471b), 
	UINT64_C(0x28db77f523047d84), UINT64_C(0x28db77f523047d84), 
	UINT64_C(0x32caab7b40c72493), UINT64_C(0x32caab7b40c72493), 
	UINT64_C(0x3c9ebe0a15c9bebc), UINT64_C(0x3c9ebe0a15c9bebc), 
	UINT64_C(0x431d67c49c100d4c), UINT64_C(0x431d67c49c100d4c), 
	UINT64_C(0x4cc5d4becb3e42b6), UINT64_C(0x4cc5d4becb3e42b6), 
	UINT64_C(0x597f299cfc657e2a), UINT64_C(0x597f299cfc657e2a), 
	UINT64_C(0x5fcb6fab3ad6faec), UINT64_C(0x5fcb6fab3ad6faec), 
	UINT64_C(0x6c44198c4a475817), UINT64_C(0x6c44198c4a475817), 
};

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha512_block_plain_c(uint64_t state[8], const uint64_t W[16]) noexcept
{
	uint64_t H, E, F, G, D, A, B, C, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15;
	const uint64_t* consts = sha512_consts;

	// Load state
	H = state[7]; E = state[4]; F = state[5]; G = state[6];
	D = state[3]; A = state[0]; B = state[1]; C = state[2];
	W0  = W[ 0];	W1  = W[ 1];	W2  = W[ 2];	W3  = W[ 3];
	W4  = W[ 4];	W5  = W[ 5];	W6  = W[ 6];	W7  = W[ 7];
	W8  = W[ 8];	W9  = W[ 9];	W10 = W[10];	W11 = W[11];
	W12 = W[12];	W13 = W[13];	W14 = W[14];	W15 = W[15];

	// Round 1
	H += (rotl(E, 50) ^ rotl(E, 46) ^ rotl(E, 23)) + (G ^ (E & (F ^ G))) + consts[ 0] + W0 ;	D += H;	H += (rotl(A, 36) ^ rotl(A, 30) ^ rotl(A, 25)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl(D, 50) ^ rotl(D, 46) ^ rotl(D, 23)) + (F ^ (D & (E ^ F))) + consts[ 1] + W1 ;	C += G;	G += (rotl(H, 36) ^ rotl(H, 30) ^ rotl(H, 25)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl(C, 50) ^ rotl(C, 46) ^ rotl(C, 23)) + (E ^ (C & (D ^ E))) + consts[ 2] + W2 ;	B += F;	F += (rotl(G, 36) ^ rotl(G, 30) ^ rotl(G, 25)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl(B, 50) ^ rotl(B, 46) ^ rotl(B, 23)) + (D ^ (B & (C ^ D))) + consts[ 3] + W3 ;	A += E;	E += (rotl(F, 36) ^ rotl(F, 30) ^ rotl(F, 25)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl(A, 50) ^ rotl(A, 46) ^ rotl(A, 23)) + (C ^ (A & (B ^ C))) + consts[ 4] + W4 ;	H += D;	D += (rotl(E, 36) ^ rotl(E, 30) ^ rotl(E, 25)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl(H, 50) ^ rotl(H, 46) ^ rotl(H, 23)) + (B ^ (H & (A ^ B))) + consts[ 5] + W5 ;	G += C;	C += (rotl(D, 36) ^ rotl(D, 30) ^ rotl(D, 25)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl(G, 50) ^ rotl(G, 46) ^ rotl(G, 23)) + (A ^ (G & (H ^ A))) + consts[ 6] + W6 ;	F += B;	B += (rotl(C, 36) ^ rotl(C, 30) ^ rotl(C, 25)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl(F, 50) ^ rotl(F, 46) ^ rotl(F, 23)) + (H ^ (F & (G ^ H))) + consts[ 7] + W7 ;	E += A;	A += (rotl(B, 36) ^ rotl(B, 30) ^ rotl(B, 25)) + ((D & C) ^ (B & (D ^ C)));
	H += (rotl(E, 50) ^ rotl(E, 46) ^ rotl(E, 23)) + (G ^ (E & (F ^ G))) + consts[ 8] + W8 ;	D += H;	H += (rotl(A, 36) ^ rotl(A, 30) ^ rotl(A, 25)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl(D, 50) ^ rotl(D, 46) ^ rotl(D, 23)) + (F ^ (D & (E ^ F))) + consts[ 9] + W9 ;	C += G;	G += (rotl(H, 36) ^ rotl(H, 30) ^ rotl(H, 25)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl(C, 50) ^ rotl(C, 46) ^ rotl(C, 23)) + (E ^ (C & (D ^ E))) + consts[10] + W10;	B += F;	F += (rotl(G, 36) ^ rotl(G, 30) ^ rotl(G, 25)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl(B, 50) ^ rotl(B, 46) ^ rotl(B, 23)) + (D ^ (B & (C ^ D))) + consts[11] + W11;	A += E;	E += (rotl(F, 36) ^ rotl(F, 30) ^ rotl(F, 25)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl(A, 50) ^ rotl(A, 46) ^ rotl(A, 23)) + (C ^ (A & (B ^ C))) + consts[12] + W12;	H += D;	D += (rotl(E, 36) ^ rotl(E, 30) ^ rotl(E, 25)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl(H, 50) ^ rotl(H, 46) ^ rotl(H, 23)) + (B ^ (H & (A ^ B))) + consts[13] + W13;	G += C;	C += (rotl(D, 36) ^ rotl(D, 30) ^ rotl(D, 25)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl(G, 50) ^ rotl(G, 46) ^ rotl(G, 23)) + (A ^ (G & (H ^ A))) + consts[14] + W14;	F += B;	B += (rotl(C, 36) ^ rotl(C, 30) ^ rotl(C, 25)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl(F, 50) ^ rotl(F, 46) ^ rotl(F, 23)) + (H ^ (F & (G ^ H))) + consts[15] + W15;	E += A;	A += (rotl(B, 36) ^ rotl(B, 30) ^ rotl(B, 25)) + ((D & C) ^ (B & (D ^ C)));
	consts += 16;

	// Round 2-5
	for (int i = 0; i < 4; i++) {
		W0  += (rotl(W14, 45) ^ rotl(W14,  3) ^ (W14 >>  6)) + W9  + (rotl(W1 , 63) ^ rotl(W1 , 56) ^ (W1  >>  7));		H += (rotl(E, 50) ^ rotl(E, 46) ^ rotl(E, 23)) + (G ^ (E & (F ^ G))) + consts[ 0] + W0 ;		D += H;		H += (rotl(A, 36) ^ rotl(A, 30) ^ rotl(A, 25)) + ((C & B) ^ (A & (C ^ B)));
		W1  += (rotl(W15, 45) ^ rotl(W15,  3) ^ (W15 >>  6)) + W10 + (rotl(W2 , 63) ^ rotl(W2 , 56) ^ (W2  >>  7));		G += (rotl(D, 50) ^ rotl(D, 46) ^ rotl(D, 23)) + (F ^ (D & (E ^ F))) + consts[ 1] + W1 ;		C += G;		G += (rotl(H, 36) ^ rotl(H, 30) ^ rotl(H, 25)) + ((B & A) ^ (H & (B ^ A)));
		W2  += (rotl(W0 , 45) ^ rotl(W0 ,  3) ^ (W0  >>  6)) + W11 + (rotl(W3 , 63) ^ rotl(W3 , 56) ^ (W3  >>  7));		F += (rotl(C, 50) ^ rotl(C, 46) ^ rotl(C, 23)) + (E ^ (C & (D ^ E))) + consts[ 2] + W2 ;		B += F;		F += (rotl(G, 36) ^ rotl(G, 30) ^ rotl(G, 25)) + ((A & H) ^ (G & (A ^ H)));
		W3  += (rotl(W1 , 45) ^ rotl(W1 ,  3) ^ (W1  >>  6)) + W12 + (rotl(W4 , 63) ^ rotl(W4 , 56) ^ (W4  >>  7));		E += (rotl(B, 50) ^ rotl(B, 46) ^ rotl(B, 23)) + (D ^ (B & (C ^ D))) + consts[ 3] + W3 ;		A += E;		E += (rotl(F, 36) ^ rotl(F, 30) ^ rotl(F, 25)) + ((H & G) ^ (F & (H ^ G)));
		W4  += (rotl(W2 , 45) ^ rotl(W2 ,  3) ^ (W2  >>  6)) + W13 + (rotl(W5 , 63) ^ rotl(W5 , 56) ^ (W5  >>  7));		D += (rotl(A, 50) ^ rotl(A, 46) ^ rotl(A, 23)) + (C ^ (A & (B ^ C))) + consts[ 4] + W4 ;		H += D;		D += (rotl(E, 36) ^ rotl(E, 30) ^ rotl(E, 25)) + ((G & F) ^ (E & (G ^ F)));
		W5  += (rotl(W3 , 45) ^ rotl(W3 ,  3) ^ (W3  >>  6)) + W14 + (rotl(W6 , 63) ^ rotl(W6 , 56) ^ (W6  >>  7));		C += (rotl(H, 50) ^ rotl(H, 46) ^ rotl(H, 23)) + (B ^ (H & (A ^ B))) + consts[ 5] + W5 ;		G += C;		C += (rotl(D, 36) ^ rotl(D, 30) ^ rotl(D, 25)) + ((F & E) ^ (D & (F ^ E)));
		W6  += (rotl(W4 , 45) ^ rotl(W4 ,  3) ^ (W4  >>  6)) + W15 + (rotl(W7 , 63) ^ rotl(W7 , 56) ^ (W7  >>  7));		B += (rotl(G, 50) ^ rotl(G, 46) ^ rotl(G, 23)) + (A ^ (G & (H ^ A))) + consts[ 6] + W6 ;		F += B;		B += (rotl(C, 36) ^ rotl(C, 30) ^ rotl(C, 25)) + ((E & D) ^ (C & (E ^ D)));
		W7  += (rotl(W5 , 45) ^ rotl(W5 ,  3) ^ (W5  >>  6)) + W0  + (rotl(W8 , 63) ^ rotl(W8 , 56) ^ (W8  >>  7));		A += (rotl(F, 50) ^ rotl(F, 46) ^ rotl(F, 23)) + (H ^ (F & (G ^ H))) + consts[ 7] + W7 ;		E += A;		A += (rotl(B, 36) ^ rotl(B, 30) ^ rotl(B, 25)) + ((D & C) ^ (B & (D ^ C)));
		W8  += (rotl(W6 , 45) ^ rotl(W6 ,  3) ^ (W6  >>  6)) + W1  + (rotl(W9 , 63) ^ rotl(W9 , 56) ^ (W9  >>  7));		H += (rotl(E, 50) ^ rotl(E, 46) ^ rotl(E, 23)) + (G ^ (E & (F ^ G))) + consts[ 8] + W8 ;		D += H;		H += (rotl(A, 36) ^ rotl(A, 30) ^ rotl(A, 25)) + ((C & B) ^ (A & (C ^ B)));
		W9  += (rotl(W7 , 45) ^ rotl(W7 ,  3) ^ (W7  >>  6)) + W2  + (rotl(W10, 63) ^ rotl(W10, 56) ^ (W10 >>  7));		G += (rotl(D, 50) ^ rotl(D, 46) ^ rotl(D, 23)) + (F ^ (D & (E ^ F))) + consts[ 9] + W9 ;		C += G;		G += (rotl(H, 36) ^ rotl(H, 30) ^ rotl(H, 25)) + ((B & A) ^ (H & (B ^ A)));
		W10 += (rotl(W8 , 45) ^ rotl(W8 ,  3) ^ (W8  >>  6)) + W3  + (rotl(W11, 63) ^ rotl(W11, 56) ^ (W11 >>  7));		F += (rotl(C, 50) ^ rotl(C, 46) ^ rotl(C, 23)) + (E ^ (C & (D ^ E))) + consts[10] + W10;		B += F;		F += (rotl(G, 36) ^ rotl(G, 30) ^ rotl(G, 25)) + ((A & H) ^ (G & (A ^ H)));
		W11 += (rotl(W9 , 45) ^ rotl(W9 ,  3) ^ (W9  >>  6)) + W4  + (rotl(W12, 63) ^ rotl(W12, 56) ^ (W12 >>  7));		E += (rotl(B, 50) ^ rotl(B, 46) ^ rotl(B, 23)) + (D ^ (B & (C ^ D))) + consts[11] + W11;		A += E;		E += (rotl(F, 36) ^ rotl(F, 30) ^ rotl(F, 25)) + ((H & G) ^ (F & (H ^ G)));
		W12 += (rotl(W10, 45) ^ rotl(W10,  3) ^ (W10 >>  6)) + W5  + (rotl(W13, 63) ^ rotl(W13, 56) ^ (W13 >>  7));		D += (rotl(A, 50) ^ rotl(A, 46) ^ rotl(A, 23)) + (C ^ (A & (B ^ C))) + consts[12] + W12;		H += D;		D += (rotl(E, 36) ^ rotl(E, 30) ^ rotl(E, 25)) + ((G & F) ^ (E & (G ^ F)));
		W13 += (rotl(W11, 45) ^ rotl(W11,  3) ^ (W11 >>  6)) + W6  + (rotl(W14, 63) ^ rotl(W14, 56) ^ (W14 >>  7));		C += (rotl(H, 50) ^ rotl(H, 46) ^ rotl(H, 23)) + (B ^ (H & (A ^ B))) + consts[13] + W13;		G += C;		C += (rotl(D, 36) ^ rotl(D, 30) ^ rotl(D, 25)) + ((F & E) ^ (D & (F ^ E)));
		W14 += (rotl(W12, 45) ^ rotl(W12,  3) ^ (W12 >>  6)) + W7  + (rotl(W15, 63) ^ rotl(W15, 56) ^ (W15 >>  7));		B += (rotl(G, 50) ^ rotl(G, 46) ^ rotl(G, 23)) + (A ^ (G & (H ^ A))) + consts[14] + W14;		F += B;		B += (rotl(C, 36) ^ rotl(C, 30) ^ rotl(C, 25)) + ((E & D) ^ (C & (E ^ D)));
		W15 += (rotl(W13, 45) ^ rotl(W13,  3) ^ (W13 >>  6)) + W8  + (rotl(W0 , 63) ^ rotl(W0 , 56) ^ (W0  >>  7));		A += (rotl(F, 50) ^ rotl(F, 46) ^ rotl(F, 23)) + (H ^ (F & (G ^ H))) + consts[15] + W15;		E += A;		A += (rotl(B, 36) ^ rotl(B, 30) ^ rotl(B, 25)) + ((D & C) ^ (B & (D ^ C)));
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
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha512_block_sse2(simd::Vec128u64 state[8], const simd::Vec128u64 W[16]) noexcept
{
	simd::Vec128u64 H, E, F, G, D, A, B, C, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15;
	const simd::Vec128u64* consts = reinterpret_cast<const simd::Vec128u64*>(sha512_consts_vec128);

	// Load state
	H = load(state + 7); E = load(state + 4); F = load(state + 5); G = load(state + 6);
	D = load(state + 3); A = load(state + 0); B = load(state + 1); C = load(state + 2);
	W0  = load(W +  0);	W1  = load(W +  1);	W2  = load(W +  2);	W3  = load(W +  3);
	W4  = load(W +  4);	W5  = load(W +  5);	W6  = load(W +  6);	W7  = load(W +  7);
	W8  = load(W +  8);	W9  = load(W +  9);	W10 = load(W + 10);	W11 = load(W + 11);
	W12 = load(W + 12);	W13 = load(W + 13);	W14 = load(W + 14);	W15 = load(W + 15);

	// Round 1
	H += (rotl<uint64_t, 50>(E, 50) ^ rotl<uint64_t, 46>(E, 46) ^ rotl<uint64_t, 23>(E, 23)) + (G ^ (E & (F ^ G))) + load(consts +  0) + W0 ;	D += H;	H += (rotl<uint64_t, 36>(A, 36) ^ rotl<uint64_t, 30>(A, 30) ^ rotl<uint64_t, 25>(A, 25)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl<uint64_t, 50>(D, 50) ^ rotl<uint64_t, 46>(D, 46) ^ rotl<uint64_t, 23>(D, 23)) + (F ^ (D & (E ^ F))) + load(consts +  1) + W1 ;	C += G;	G += (rotl<uint64_t, 36>(H, 36) ^ rotl<uint64_t, 30>(H, 30) ^ rotl<uint64_t, 25>(H, 25)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl<uint64_t, 50>(C, 50) ^ rotl<uint64_t, 46>(C, 46) ^ rotl<uint64_t, 23>(C, 23)) + (E ^ (C & (D ^ E))) + load(consts +  2) + W2 ;	B += F;	F += (rotl<uint64_t, 36>(G, 36) ^ rotl<uint64_t, 30>(G, 30) ^ rotl<uint64_t, 25>(G, 25)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl<uint64_t, 50>(B, 50) ^ rotl<uint64_t, 46>(B, 46) ^ rotl<uint64_t, 23>(B, 23)) + (D ^ (B & (C ^ D))) + load(consts +  3) + W3 ;	A += E;	E += (rotl<uint64_t, 36>(F, 36) ^ rotl<uint64_t, 30>(F, 30) ^ rotl<uint64_t, 25>(F, 25)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl<uint64_t, 50>(A, 50) ^ rotl<uint64_t, 46>(A, 46) ^ rotl<uint64_t, 23>(A, 23)) + (C ^ (A & (B ^ C))) + load(consts +  4) + W4 ;	H += D;	D += (rotl<uint64_t, 36>(E, 36) ^ rotl<uint64_t, 30>(E, 30) ^ rotl<uint64_t, 25>(E, 25)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl<uint64_t, 50>(H, 50) ^ rotl<uint64_t, 46>(H, 46) ^ rotl<uint64_t, 23>(H, 23)) + (B ^ (H & (A ^ B))) + load(consts +  5) + W5 ;	G += C;	C += (rotl<uint64_t, 36>(D, 36) ^ rotl<uint64_t, 30>(D, 30) ^ rotl<uint64_t, 25>(D, 25)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl<uint64_t, 50>(G, 50) ^ rotl<uint64_t, 46>(G, 46) ^ rotl<uint64_t, 23>(G, 23)) + (A ^ (G & (H ^ A))) + load(consts +  6) + W6 ;	F += B;	B += (rotl<uint64_t, 36>(C, 36) ^ rotl<uint64_t, 30>(C, 30) ^ rotl<uint64_t, 25>(C, 25)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl<uint64_t, 50>(F, 50) ^ rotl<uint64_t, 46>(F, 46) ^ rotl<uint64_t, 23>(F, 23)) + (H ^ (F & (G ^ H))) + load(consts +  7) + W7 ;	E += A;	A += (rotl<uint64_t, 36>(B, 36) ^ rotl<uint64_t, 30>(B, 30) ^ rotl<uint64_t, 25>(B, 25)) + ((D & C) ^ (B & (D ^ C)));
	H += (rotl<uint64_t, 50>(E, 50) ^ rotl<uint64_t, 46>(E, 46) ^ rotl<uint64_t, 23>(E, 23)) + (G ^ (E & (F ^ G))) + load(consts +  8) + W8 ;	D += H;	H += (rotl<uint64_t, 36>(A, 36) ^ rotl<uint64_t, 30>(A, 30) ^ rotl<uint64_t, 25>(A, 25)) + ((C & B) ^ (A & (C ^ B)));
	G += (rotl<uint64_t, 50>(D, 50) ^ rotl<uint64_t, 46>(D, 46) ^ rotl<uint64_t, 23>(D, 23)) + (F ^ (D & (E ^ F))) + load(consts +  9) + W9 ;	C += G;	G += (rotl<uint64_t, 36>(H, 36) ^ rotl<uint64_t, 30>(H, 30) ^ rotl<uint64_t, 25>(H, 25)) + ((B & A) ^ (H & (B ^ A)));
	F += (rotl<uint64_t, 50>(C, 50) ^ rotl<uint64_t, 46>(C, 46) ^ rotl<uint64_t, 23>(C, 23)) + (E ^ (C & (D ^ E))) + load(consts + 10) + W10;	B += F;	F += (rotl<uint64_t, 36>(G, 36) ^ rotl<uint64_t, 30>(G, 30) ^ rotl<uint64_t, 25>(G, 25)) + ((A & H) ^ (G & (A ^ H)));
	E += (rotl<uint64_t, 50>(B, 50) ^ rotl<uint64_t, 46>(B, 46) ^ rotl<uint64_t, 23>(B, 23)) + (D ^ (B & (C ^ D))) + load(consts + 11) + W11;	A += E;	E += (rotl<uint64_t, 36>(F, 36) ^ rotl<uint64_t, 30>(F, 30) ^ rotl<uint64_t, 25>(F, 25)) + ((H & G) ^ (F & (H ^ G)));
	D += (rotl<uint64_t, 50>(A, 50) ^ rotl<uint64_t, 46>(A, 46) ^ rotl<uint64_t, 23>(A, 23)) + (C ^ (A & (B ^ C))) + load(consts + 12) + W12;	H += D;	D += (rotl<uint64_t, 36>(E, 36) ^ rotl<uint64_t, 30>(E, 30) ^ rotl<uint64_t, 25>(E, 25)) + ((G & F) ^ (E & (G ^ F)));
	C += (rotl<uint64_t, 50>(H, 50) ^ rotl<uint64_t, 46>(H, 46) ^ rotl<uint64_t, 23>(H, 23)) + (B ^ (H & (A ^ B))) + load(consts + 13) + W13;	G += C;	C += (rotl<uint64_t, 36>(D, 36) ^ rotl<uint64_t, 30>(D, 30) ^ rotl<uint64_t, 25>(D, 25)) + ((F & E) ^ (D & (F ^ E)));
	B += (rotl<uint64_t, 50>(G, 50) ^ rotl<uint64_t, 46>(G, 46) ^ rotl<uint64_t, 23>(G, 23)) + (A ^ (G & (H ^ A))) + load(consts + 14) + W14;	F += B;	B += (rotl<uint64_t, 36>(C, 36) ^ rotl<uint64_t, 30>(C, 30) ^ rotl<uint64_t, 25>(C, 25)) + ((E & D) ^ (C & (E ^ D)));
	A += (rotl<uint64_t, 50>(F, 50) ^ rotl<uint64_t, 46>(F, 46) ^ rotl<uint64_t, 23>(F, 23)) + (H ^ (F & (G ^ H))) + load(consts + 15) + W15;	E += A;	A += (rotl<uint64_t, 36>(B, 36) ^ rotl<uint64_t, 30>(B, 30) ^ rotl<uint64_t, 25>(B, 25)) + ((D & C) ^ (B & (D ^ C)));
	consts += 16;

	// Round 2-5
	for (int i = 0; i < 4; i++) {
		W0  += (rotl<uint64_t, 45>(W14, 45) ^ rotl<uint64_t,  3>(W14,  3) ^ (W14 >>  6)) + W9  + (rotl<uint64_t, 63>(W1 , 63) ^ rotl<uint64_t, 56>(W1 , 56) ^ (W1  >>  7));		H += (rotl<uint64_t, 50>(E, 50) ^ rotl<uint64_t, 46>(E, 46) ^ rotl<uint64_t, 23>(E, 23)) + (G ^ (E & (F ^ G))) + load(consts +  0) + W0 ;		D += H;		H += (rotl<uint64_t, 36>(A, 36) ^ rotl<uint64_t, 30>(A, 30) ^ rotl<uint64_t, 25>(A, 25)) + ((C & B) ^ (A & (C ^ B)));
		W1  += (rotl<uint64_t, 45>(W15, 45) ^ rotl<uint64_t,  3>(W15,  3) ^ (W15 >>  6)) + W10 + (rotl<uint64_t, 63>(W2 , 63) ^ rotl<uint64_t, 56>(W2 , 56) ^ (W2  >>  7));		G += (rotl<uint64_t, 50>(D, 50) ^ rotl<uint64_t, 46>(D, 46) ^ rotl<uint64_t, 23>(D, 23)) + (F ^ (D & (E ^ F))) + load(consts +  1) + W1 ;		C += G;		G += (rotl<uint64_t, 36>(H, 36) ^ rotl<uint64_t, 30>(H, 30) ^ rotl<uint64_t, 25>(H, 25)) + ((B & A) ^ (H & (B ^ A)));
		W2  += (rotl<uint64_t, 45>(W0 , 45) ^ rotl<uint64_t,  3>(W0 ,  3) ^ (W0  >>  6)) + W11 + (rotl<uint64_t, 63>(W3 , 63) ^ rotl<uint64_t, 56>(W3 , 56) ^ (W3  >>  7));		F += (rotl<uint64_t, 50>(C, 50) ^ rotl<uint64_t, 46>(C, 46) ^ rotl<uint64_t, 23>(C, 23)) + (E ^ (C & (D ^ E))) + load(consts +  2) + W2 ;		B += F;		F += (rotl<uint64_t, 36>(G, 36) ^ rotl<uint64_t, 30>(G, 30) ^ rotl<uint64_t, 25>(G, 25)) + ((A & H) ^ (G & (A ^ H)));
		W3  += (rotl<uint64_t, 45>(W1 , 45) ^ rotl<uint64_t,  3>(W1 ,  3) ^ (W1  >>  6)) + W12 + (rotl<uint64_t, 63>(W4 , 63) ^ rotl<uint64_t, 56>(W4 , 56) ^ (W4  >>  7));		E += (rotl<uint64_t, 50>(B, 50) ^ rotl<uint64_t, 46>(B, 46) ^ rotl<uint64_t, 23>(B, 23)) + (D ^ (B & (C ^ D))) + load(consts +  3) + W3 ;		A += E;		E += (rotl<uint64_t, 36>(F, 36) ^ rotl<uint64_t, 30>(F, 30) ^ rotl<uint64_t, 25>(F, 25)) + ((H & G) ^ (F & (H ^ G)));
		W4  += (rotl<uint64_t, 45>(W2 , 45) ^ rotl<uint64_t,  3>(W2 ,  3) ^ (W2  >>  6)) + W13 + (rotl<uint64_t, 63>(W5 , 63) ^ rotl<uint64_t, 56>(W5 , 56) ^ (W5  >>  7));		D += (rotl<uint64_t, 50>(A, 50) ^ rotl<uint64_t, 46>(A, 46) ^ rotl<uint64_t, 23>(A, 23)) + (C ^ (A & (B ^ C))) + load(consts +  4) + W4 ;		H += D;		D += (rotl<uint64_t, 36>(E, 36) ^ rotl<uint64_t, 30>(E, 30) ^ rotl<uint64_t, 25>(E, 25)) + ((G & F) ^ (E & (G ^ F)));
		W5  += (rotl<uint64_t, 45>(W3 , 45) ^ rotl<uint64_t,  3>(W3 ,  3) ^ (W3  >>  6)) + W14 + (rotl<uint64_t, 63>(W6 , 63) ^ rotl<uint64_t, 56>(W6 , 56) ^ (W6  >>  7));		C += (rotl<uint64_t, 50>(H, 50) ^ rotl<uint64_t, 46>(H, 46) ^ rotl<uint64_t, 23>(H, 23)) + (B ^ (H & (A ^ B))) + load(consts +  5) + W5 ;		G += C;		C += (rotl<uint64_t, 36>(D, 36) ^ rotl<uint64_t, 30>(D, 30) ^ rotl<uint64_t, 25>(D, 25)) + ((F & E) ^ (D & (F ^ E)));
		W6  += (rotl<uint64_t, 45>(W4 , 45) ^ rotl<uint64_t,  3>(W4 ,  3) ^ (W4  >>  6)) + W15 + (rotl<uint64_t, 63>(W7 , 63) ^ rotl<uint64_t, 56>(W7 , 56) ^ (W7  >>  7));		B += (rotl<uint64_t, 50>(G, 50) ^ rotl<uint64_t, 46>(G, 46) ^ rotl<uint64_t, 23>(G, 23)) + (A ^ (G & (H ^ A))) + load(consts +  6) + W6 ;		F += B;		B += (rotl<uint64_t, 36>(C, 36) ^ rotl<uint64_t, 30>(C, 30) ^ rotl<uint64_t, 25>(C, 25)) + ((E & D) ^ (C & (E ^ D)));
		W7  += (rotl<uint64_t, 45>(W5 , 45) ^ rotl<uint64_t,  3>(W5 ,  3) ^ (W5  >>  6)) + W0  + (rotl<uint64_t, 63>(W8 , 63) ^ rotl<uint64_t, 56>(W8 , 56) ^ (W8  >>  7));		A += (rotl<uint64_t, 50>(F, 50) ^ rotl<uint64_t, 46>(F, 46) ^ rotl<uint64_t, 23>(F, 23)) + (H ^ (F & (G ^ H))) + load(consts +  7) + W7 ;		E += A;		A += (rotl<uint64_t, 36>(B, 36) ^ rotl<uint64_t, 30>(B, 30) ^ rotl<uint64_t, 25>(B, 25)) + ((D & C) ^ (B & (D ^ C)));
		W8  += (rotl<uint64_t, 45>(W6 , 45) ^ rotl<uint64_t,  3>(W6 ,  3) ^ (W6  >>  6)) + W1  + (rotl<uint64_t, 63>(W9 , 63) ^ rotl<uint64_t, 56>(W9 , 56) ^ (W9  >>  7));		H += (rotl<uint64_t, 50>(E, 50) ^ rotl<uint64_t, 46>(E, 46) ^ rotl<uint64_t, 23>(E, 23)) + (G ^ (E & (F ^ G))) + load(consts +  8) + W8 ;		D += H;		H += (rotl<uint64_t, 36>(A, 36) ^ rotl<uint64_t, 30>(A, 30) ^ rotl<uint64_t, 25>(A, 25)) + ((C & B) ^ (A & (C ^ B)));
		W9  += (rotl<uint64_t, 45>(W7 , 45) ^ rotl<uint64_t,  3>(W7 ,  3) ^ (W7  >>  6)) + W2  + (rotl<uint64_t, 63>(W10, 63) ^ rotl<uint64_t, 56>(W10, 56) ^ (W10 >>  7));		G += (rotl<uint64_t, 50>(D, 50) ^ rotl<uint64_t, 46>(D, 46) ^ rotl<uint64_t, 23>(D, 23)) + (F ^ (D & (E ^ F))) + load(consts +  9) + W9 ;		C += G;		G += (rotl<uint64_t, 36>(H, 36) ^ rotl<uint64_t, 30>(H, 30) ^ rotl<uint64_t, 25>(H, 25)) + ((B & A) ^ (H & (B ^ A)));
		W10 += (rotl<uint64_t, 45>(W8 , 45) ^ rotl<uint64_t,  3>(W8 ,  3) ^ (W8  >>  6)) + W3  + (rotl<uint64_t, 63>(W11, 63) ^ rotl<uint64_t, 56>(W11, 56) ^ (W11 >>  7));		F += (rotl<uint64_t, 50>(C, 50) ^ rotl<uint64_t, 46>(C, 46) ^ rotl<uint64_t, 23>(C, 23)) + (E ^ (C & (D ^ E))) + load(consts + 10) + W10;		B += F;		F += (rotl<uint64_t, 36>(G, 36) ^ rotl<uint64_t, 30>(G, 30) ^ rotl<uint64_t, 25>(G, 25)) + ((A & H) ^ (G & (A ^ H)));
		W11 += (rotl<uint64_t, 45>(W9 , 45) ^ rotl<uint64_t,  3>(W9 ,  3) ^ (W9  >>  6)) + W4  + (rotl<uint64_t, 63>(W12, 63) ^ rotl<uint64_t, 56>(W12, 56) ^ (W12 >>  7));		E += (rotl<uint64_t, 50>(B, 50) ^ rotl<uint64_t, 46>(B, 46) ^ rotl<uint64_t, 23>(B, 23)) + (D ^ (B & (C ^ D))) + load(consts + 11) + W11;		A += E;		E += (rotl<uint64_t, 36>(F, 36) ^ rotl<uint64_t, 30>(F, 30) ^ rotl<uint64_t, 25>(F, 25)) + ((H & G) ^ (F & (H ^ G)));
		W12 += (rotl<uint64_t, 45>(W10, 45) ^ rotl<uint64_t,  3>(W10,  3) ^ (W10 >>  6)) + W5  + (rotl<uint64_t, 63>(W13, 63) ^ rotl<uint64_t, 56>(W13, 56) ^ (W13 >>  7));		D += (rotl<uint64_t, 50>(A, 50) ^ rotl<uint64_t, 46>(A, 46) ^ rotl<uint64_t, 23>(A, 23)) + (C ^ (A & (B ^ C))) + load(consts + 12) + W12;		H += D;		D += (rotl<uint64_t, 36>(E, 36) ^ rotl<uint64_t, 30>(E, 30) ^ rotl<uint64_t, 25>(E, 25)) + ((G & F) ^ (E & (G ^ F)));
		W13 += (rotl<uint64_t, 45>(W11, 45) ^ rotl<uint64_t,  3>(W11,  3) ^ (W11 >>  6)) + W6  + (rotl<uint64_t, 63>(W14, 63) ^ rotl<uint64_t, 56>(W14, 56) ^ (W14 >>  7));		C += (rotl<uint64_t, 50>(H, 50) ^ rotl<uint64_t, 46>(H, 46) ^ rotl<uint64_t, 23>(H, 23)) + (B ^ (H & (A ^ B))) + load(consts + 13) + W13;		G += C;		C += (rotl<uint64_t, 36>(D, 36) ^ rotl<uint64_t, 30>(D, 30) ^ rotl<uint64_t, 25>(D, 25)) + ((F & E) ^ (D & (F ^ E)));
		W14 += (rotl<uint64_t, 45>(W12, 45) ^ rotl<uint64_t,  3>(W12,  3) ^ (W12 >>  6)) + W7  + (rotl<uint64_t, 63>(W15, 63) ^ rotl<uint64_t, 56>(W15, 56) ^ (W15 >>  7));		B += (rotl<uint64_t, 50>(G, 50) ^ rotl<uint64_t, 46>(G, 46) ^ rotl<uint64_t, 23>(G, 23)) + (A ^ (G & (H ^ A))) + load(consts + 14) + W14;		F += B;		B += (rotl<uint64_t, 36>(C, 36) ^ rotl<uint64_t, 30>(C, 30) ^ rotl<uint64_t, 25>(C, 25)) + ((E & D) ^ (C & (E ^ D)));
		W15 += (rotl<uint64_t, 45>(W13, 45) ^ rotl<uint64_t,  3>(W13,  3) ^ (W13 >>  6)) + W8  + (rotl<uint64_t, 63>(W0 , 63) ^ rotl<uint64_t, 56>(W0 , 56) ^ (W0  >>  7));		A += (rotl<uint64_t, 50>(F, 50) ^ rotl<uint64_t, 46>(F, 46) ^ rotl<uint64_t, 23>(F, 23)) + (H ^ (F & (G ^ H))) + load(consts + 15) + W15;		E += A;		A += (rotl<uint64_t, 36>(B, 36) ^ rotl<uint64_t, 30>(B, 30) ^ rotl<uint64_t, 25>(B, 25)) + ((D & C) ^ (B & (D ^ C)));
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

