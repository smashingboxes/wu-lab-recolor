#ifndef LABRECOLOR_H
#define LABRECOLOR_H

typedef enum {
  WU_NULL_IMAGE,
  WU_MAGICK_WAND_ERR
} WU_LABRECOLORERR;

/**
 * @param {FILE} input file descriptor
 * @param {FILE} output file descriptor
 * @param {WU_LABRECOLORERR} a pointer to a LABRECOLORERR
 * @return {INT} 1 if successful 0 if failure
 */

int wu_lab_recolor(FILE* input_file, FILE* output_file, WU_LABRECOLORERR* err);

// Private methods
void _wu_lab_from_string(signed char* lab_ints, char* pixel_norm_color);
// Helper Method These Input and Output Maps will be set by the wu_lab_recolor
// function
void _wu_get_mapped_color_with_in_out(
    char* input_string,
    char* output_string,
    double* input_colors,
    double* output_colors,
    unsigned int count);
void _wu_teardown();
#endif
