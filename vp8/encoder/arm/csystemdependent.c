/*
 *  Copyright (c) 2010 The VP8 project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license and patent
 *  grant that can be found in the LICENSE file in the root of the source
 *  tree. All contributing project authors may be found in the AUTHORS
 *  file in the root of the source tree.
 */


#include "vpx_ports/config.h"
#include "variance.h"
#include "onyx_int.h"

void (*vp8_yv12_copy_partial_frame_ptr)(YV12_BUFFER_CONFIG *src_ybc, YV12_BUFFER_CONFIG *dst_ybc, int Fraction);
extern void vp8_yv12_copy_partial_frame(YV12_BUFFER_CONFIG *src_ybc, YV12_BUFFER_CONFIG *dst_ybc, int Fraction);
extern void vpxyv12_copy_partial_frame_neon(YV12_BUFFER_CONFIG *src_ybc, YV12_BUFFER_CONFIG *dst_ybc, int Fraction);

void vp8_cmachine_specific_config(VP8_COMP *cpi)
{
#if CONFIG_RUNTIME_CPU_DETECT
    cpi->rtcd.common                         = &cpi->common.rtcd;

#if HAVE_ARMV7
    cpi->rtcd.variance.sad16x16              = vp8_sad16x16_neon;
    cpi->rtcd.variance.sad16x8               = vp8_sad16x8_neon;
    cpi->rtcd.variance.sad8x16               = vp8_sad8x16_neon;
    cpi->rtcd.variance.sad8x8                = vp8_sad8x8_neon;
    cpi->rtcd.variance.sad4x4                = vp8_sad4x4_neon;

    cpi->rtcd.variance.var4x4                = vp8_variance4x4_c;
    cpi->rtcd.variance.var8x8                = vp8_variance8x8_neon;
    cpi->rtcd.variance.var8x16               = vp8_variance8x16_neon;
    cpi->rtcd.variance.var16x8               = vp8_variance16x8_neon;
    cpi->rtcd.variance.var16x16              = vp8_variance16x16_neon;

    cpi->rtcd.variance.subpixvar4x4          = vp8_sub_pixel_variance4x4_c;
    cpi->rtcd.variance.subpixvar8x8          = vp8_sub_pixel_variance8x8_neon;
    cpi->rtcd.variance.subpixvar8x16         = vp8_sub_pixel_variance8x16_c;
    cpi->rtcd.variance.subpixvar16x8         = vp8_sub_pixel_variance16x8_c;
    cpi->rtcd.variance.subpixvar16x16        = vp8_sub_pixel_variance16x16_neon;

    cpi->rtcd.variance.mse16x16              = vp8_mse16x16_neon;
    cpi->rtcd.variance.getmbss               = vp8_get_mb_ss_c;

    cpi->rtcd.variance.get16x16prederror     = vp8_get16x16pred_error_neon;
    cpi->rtcd.variance.get8x8var             = vp8_get8x8var_c;
    cpi->rtcd.variance.get16x16var           = vp8_get16x16var_c;;
    cpi->rtcd.variance.get4x4sse_cs          = vp8_get4x4sse_cs_neon;

    cpi->rtcd.fdct.short4x4                  = vp8_short_fdct4x4_neon;
    cpi->rtcd.fdct.short8x4                  = vp8_short_fdct8x4_neon;
    cpi->rtcd.fdct.fast4x4                   = vp8_fast_fdct4x4_neon;
    cpi->rtcd.fdct.fast8x4                   = vp8_fast_fdct8x4_neon;
    cpi->rtcd.fdct.walsh_short4x4            = vp8_short_walsh4x4_neon;

    cpi->rtcd.encodemb.berr                  = vp8_block_error_c;
    cpi->rtcd.encodemb.mberr                 = vp8_mbblock_error_c;
    cpi->rtcd.encodemb.mbuverr               = vp8_mbuverror_c;
    cpi->rtcd.encodemb.subb                  = vp8_subtract_b_neon;
    cpi->rtcd.encodemb.submby                = vp8_subtract_mby_neon;
    cpi->rtcd.encodemb.submbuv               = vp8_subtract_mbuv_neon;

    cpi->rtcd.quantize.quantb                = vp8_regular_quantize_b;
    cpi->rtcd.quantize.fastquantb            = vp8_fast_quantize_b_neon;
#elif HAVE_ARMV6
    cpi->rtcd.variance.sad16x16              = vp8_sad16x16_c;
    cpi->rtcd.variance.sad16x8               = vp8_sad16x8_c;
    cpi->rtcd.variance.sad8x16               = vp8_sad8x16_c;
    cpi->rtcd.variance.sad8x8                = vp8_sad8x8_c;
    cpi->rtcd.variance.sad4x4                = vp8_sad4x4_c;

    cpi->rtcd.variance.var4x4                = vp8_variance4x4_c;
    cpi->rtcd.variance.var8x8                = vp8_variance8x8_c;
    cpi->rtcd.variance.var8x16               = vp8_variance8x16_c;
    cpi->rtcd.variance.var16x8               = vp8_variance16x8_c;
    cpi->rtcd.variance.var16x16              = vp8_variance16x16_c;

    cpi->rtcd.variance.subpixvar4x4          = vp8_sub_pixel_variance4x4_c;
    cpi->rtcd.variance.subpixvar8x8          = vp8_sub_pixel_variance8x8_c;
    cpi->rtcd.variance.subpixvar8x16         = vp8_sub_pixel_variance8x16_c;
    cpi->rtcd.variance.subpixvar16x8         = vp8_sub_pixel_variance16x8_c;
    cpi->rtcd.variance.subpixvar16x16        = vp8_sub_pixel_variance16x16_c;

    cpi->rtcd.variance.mse16x16              = vp8_mse16x16_c;
    cpi->rtcd.variance.getmbss               = vp8_get_mb_ss_c;

    cpi->rtcd.variance.get16x16prederror     = vp8_get16x16pred_error_c;
    cpi->rtcd.variance.get8x8var             = vp8_get8x8var_c;
    cpi->rtcd.variance.get16x16var           = vp8_get16x16var_c;;
    cpi->rtcd.variance.get4x4sse_cs          = vp8_get4x4sse_cs_c;

    cpi->rtcd.fdct.short4x4                  = vp8_short_fdct4x4_c;
    cpi->rtcd.fdct.short8x4                  = vp8_short_fdct8x4_c;
    cpi->rtcd.fdct.fast4x4                   = vp8_fast_fdct4x4_c;
    cpi->rtcd.fdct.fast8x4                   = vp8_fast_fdct8x4_c;
    cpi->rtcd.fdct.walsh_short4x4            = vp8_short_walsh4x4_armv6;

    cpi->rtcd.encodemb.berr                  = vp8_block_error_c;
    cpi->rtcd.encodemb.mberr                 = vp8_mbblock_error_c;
    cpi->rtcd.encodemb.mbuverr               = vp8_mbuverror_c;
    cpi->rtcd.encodemb.subb                  = vp8_subtract_b_c;
    cpi->rtcd.encodemb.submby                = vp8_subtract_mby_c;
    cpi->rtcd.encodemb.submbuv               = vp8_subtract_mbuv_c;

    cpi->rtcd.quantize.quantb                = vp8_regular_quantize_b;
    cpi->rtcd.quantize.fastquantb            = vp8_fast_quantize_b_c;
#else
    //pure c
    cpi->rtcd.variance.sad16x16              = vp8_sad16x16_c;
    cpi->rtcd.variance.sad16x8               = vp8_sad16x8_c;
    cpi->rtcd.variance.sad8x16               = vp8_sad8x16_c;
    cpi->rtcd.variance.sad8x8                = vp8_sad8x8_c;
    cpi->rtcd.variance.sad4x4                = vp8_sad4x4_c;

    cpi->rtcd.variance.var4x4                = vp8_variance4x4_c;
    cpi->rtcd.variance.var8x8                = vp8_variance8x8_c;
    cpi->rtcd.variance.var8x16               = vp8_variance8x16_c;
    cpi->rtcd.variance.var16x8               = vp8_variance16x8_c;
    cpi->rtcd.variance.var16x16              = vp8_variance16x16_c;

    cpi->rtcd.variance.subpixvar4x4          = vp8_sub_pixel_variance4x4_c;
    cpi->rtcd.variance.subpixvar8x8          = vp8_sub_pixel_variance8x8_c;
    cpi->rtcd.variance.subpixvar8x16         = vp8_sub_pixel_variance8x16_c;
    cpi->rtcd.variance.subpixvar16x8         = vp8_sub_pixel_variance16x8_c;
    cpi->rtcd.variance.subpixvar16x16        = vp8_sub_pixel_variance16x16_c;

    cpi->rtcd.variance.mse16x16              = vp8_mse16x16_c;
    cpi->rtcd.variance.getmbss               = vp8_get_mb_ss_c;

    cpi->rtcd.variance.get16x16prederror     = vp8_get16x16pred_error_c;
    cpi->rtcd.variance.get8x8var             = vp8_get8x8var_c;
    cpi->rtcd.variance.get16x16var           = vp8_get16x16var_c;;
    cpi->rtcd.variance.get4x4sse_cs          = vp8_get4x4sse_cs_c;

    cpi->rtcd.fdct.short4x4                  = vp8_short_fdct4x4_c;
    cpi->rtcd.fdct.short8x4                  = vp8_short_fdct8x4_c;
    cpi->rtcd.fdct.fast4x4                   = vp8_fast_fdct4x4_c;
    cpi->rtcd.fdct.fast8x4                   = vp8_fast_fdct8x4_c;
    cpi->rtcd.fdct.walsh_short4x4            = vp8_short_walsh4x4_c;

    cpi->rtcd.encodemb.berr                  = vp8_block_error_c;
    cpi->rtcd.encodemb.mberr                 = vp8_mbblock_error_c;
    cpi->rtcd.encodemb.mbuverr               = vp8_mbuverror_c;
    cpi->rtcd.encodemb.subb                  = vp8_subtract_b_c;
    cpi->rtcd.encodemb.submby                = vp8_subtract_mby_c;
    cpi->rtcd.encodemb.submbuv               = vp8_subtract_mbuv_c;

    cpi->rtcd.quantize.quantb                = vp8_regular_quantize_b;
    cpi->rtcd.quantize.fastquantb            = vp8_fast_quantize_b_c;
#endif
#endif

#if HAVE_ARMV7
    vp8_yv12_copy_partial_frame_ptr = vpxyv12_copy_partial_frame_neon;
#else
    vp8_yv12_copy_partial_frame_ptr = vp8_yv12_copy_partial_frame;
#endif
}
