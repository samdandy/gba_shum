
@{{BLOCK(zig_bn_gfx)

@=======================================================================
@
@	zig_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-01-31, 16:32:52
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global zig_bn_gfxTiles		@ 128 unsigned chars
	.hidden zig_bn_gfxTiles
zig_bn_gfxTiles:
	.word 0x20022222,0x20022222,0x20025552,0x20025552,0x20025552,0x20025552,0x22222222,0x22505222
	.word 0x00002222,0x00002222,0x00002555,0x00002555,0x00002555,0x00002555,0x22222222,0x22222505
	.word 0x22000222,0x22505222,0x22222222,0x00022222,0x02022222,0x00022222,0x20022222,0x00022222
	.word 0x22222000,0x22222505,0x22222222,0x00000000,0x02020202,0x00000000,0x00202020,0x00000000

	.section .rodata
	.align	2
	.global zig_bn_gfxPal		@ 32 unsigned chars
	.hidden zig_bn_gfxPal
zig_bn_gfxPal:
	.hword 0x0000,0x6E87,0x7FFF,0x18DB,0x7FFF,0x725F,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(zig_bn_gfx)
