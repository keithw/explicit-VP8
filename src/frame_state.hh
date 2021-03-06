#ifndef FRAME_STATE_HH_
#define FRAME_STATE_HH_

#include "dixie.hh"

struct vp8_raster_ref_ids {
  unsigned int lf_number;    /* Raster number of last_ref */
  unsigned int gf_number;    /* Raster number of golden */
  unsigned int ar_number;    /* Raster number of altref */
};

struct vp8_mb_dependencies {
  bool depends_lf;   /* Does any mb in current operator depend on last raster ? */
  bool depends_gf;   /* Does any mb in current operator depend on golden raster ? */
  bool depends_ar;   /* Does any mb in current operator depend on altref raster ? */
  const struct vp8_mb_dependencies compute_union(const struct vp8_mb_dependencies & other) {
    return {depends_lf or other.depends_lf,
            depends_gf or other.depends_gf,
            depends_ar or other.depends_ar};
  }
};

class FrameState {
 public:
  /* Constructor */
  FrameState(struct vp8_frame_hdr         t_frame_hdr,
             struct vp8_segment_hdr       t_segment_hdr,
             struct vp8_loopfilter_hdr    t_loopfilter_hdr,
             struct vp8_token_hdr         t_token_hdr,
             struct vp8_quant_hdr         t_quant_hdr,
             struct vp8_reference_hdr     t_reference_hdr,
             struct vp8_entropy_hdr       t_entropy_hdr,
             struct vp8_raster_ref_ids    t_raster_ids,
             struct vp8_mb_dependencies   t_raster_deps,
             unsigned int                 t_raster_num,
             unsigned int                 t_prob_update_len)
      : frame_hdr(t_frame_hdr),
        segment_hdr(t_segment_hdr),
        loopfilter_hdr(t_loopfilter_hdr),
        token_hdr(t_token_hdr),
        quant_hdr(t_quant_hdr),
        reference_hdr(t_reference_hdr),
        entropy_hdr(t_entropy_hdr),
        raster_ids(t_raster_ids),
        raster_deps(t_raster_deps),
        raster_num(t_raster_num),
        prob_update_len(t_prob_update_len) {}

  /* Print all state (per frame and intra frame) */
  void pretty_print_everything(void) const;

  /* Print only inter frame state (probability tables) */
  void pretty_print_inter_frame_state(void) const;

  /* Compact Pretty print (raster deps with probability update  length) */
  void pretty_print_compact(void) const;

 private:
  /* Pretty printing */
  void pretty_print_frame_hdr(void)      const;
  void pretty_print_segment_hdr(void)    const;
  void pretty_print_loopfilter_hdr(void) const;
  void pretty_print_token_hdr(void)      const;
  void pretty_print_quant_hdr(void)      const;
  void pretty_print_reference_hdr(void)  const;
  void pretty_print_raster_numbers(void) const;
  void pretty_print_frame_deps(void)     const;
  void pretty_print_entropy_hdr(void)    const;

  /* Frame state */
  const struct vp8_frame_hdr      frame_hdr;     /* Frame scaling */
  const struct vp8_segment_hdr    segment_hdr;   /* Segmentation state */
  const struct vp8_loopfilter_hdr loopfilter_hdr;/* Loop filter state */
  const struct vp8_token_hdr      token_hdr;     /* # partitions & sizes */
  const struct vp8_quant_hdr      quant_hdr;     /* Quant. coeffs */
  const struct vp8_reference_hdr  reference_hdr; /* ref. frame */
  const struct vp8_entropy_hdr    entropy_hdr;   /* Probabilities */
  const struct vp8_raster_ref_ids raster_ids;    /* ids of last, golden, altref rasters */
  const struct vp8_mb_dependencies raster_deps;  /* Does the operator depend on the last, golden and altref rasters */
  unsigned int raster_num;                       /* Raster number of current frame */
  unsigned int prob_update_len;                  /* Length of probability table update */
};

#endif  // FRAME_STATE_HH_
