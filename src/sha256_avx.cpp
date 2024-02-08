//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA256 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#include "sha256_internal.h"

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha256_block_avx(simd::Vec128u32 state[8], const simd::Vec128u32 W[16]) noexcept
{
	simd::Vec128u32 H, E, F, G, D, A, B, C, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15;
	const simd::Vec128u32* consts = reinterpret_cast<const simd::Vec128u32*>(sha256_consts_vec128);

	// Load state
	H = load(state + 7); E = load(state + 4); F = load(state + 5); G = load(state + 6);
	D = load(state + 3); A = load(state + 0); B = load(state + 1); C = load(state + 2);
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

