#ifndef BN_SPRITE_ITEMS_ZIG_H
#define BN_SPRITE_ITEMS_ZIG_H

#include "bn_sprite_item.h"

//{{BLOCK(zig_bn_gfx)

//======================================================================
//
//	zig_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2026-02-07, 21:23:50
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ZIG_BN_GFX_H
#define GRIT_ZIG_BN_GFX_H

#define zig_bn_gfxTilesLen 128
extern const bn::tile zig_bn_gfxTiles[4];

#define zig_bn_gfxPalLen 32
extern const bn::color zig_bn_gfxPal[16];

#endif // GRIT_ZIG_BN_GFX_H

//}}BLOCK(zig_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item zig(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(zig_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(zig_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

