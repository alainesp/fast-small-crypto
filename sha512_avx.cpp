//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#include "sha512_internal.h"

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha512_block_avx(simd::Vec128u64 state[8], const simd::Vec128u64 W[16]) noexcept
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

