#include <stdio.h>
#include <string.h>
#include <wand/MagickWand.h>
#include <math.h>
#include "lab_recolor.h"
#include <assert.h>

#define return_with_error(err_name) \
  if(err != NULL) { \
    *err = err_name; \
  } \
  return 0

#define return_with_wand_error(wand) \
  description = MagickGetException(wand, &severity); \
  wu_set_last_error(description); \
  fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(),description); \
  description = (char *)MagickRelinquishMemory(description); \
  return_with_error(WU_MAGICK_WAND_ERR);

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

static double* wu_input_colors;
static double* wu_output_colors;
static unsigned int wu_color_count;
static char* wu_last_error = NULL;

// Allocates a string to hold a string with the given number of characters
// (The given strlen should not include the NULL byte)
static char* alloc_str(size_t strlen) {
  return (char*) malloc(sizeof(char) * (char_len + 1));
}

static void wu_clear_last_error() {
  if(wu_last_error != NULL)
    free(wu_last_error);
}

static void wu_set_last_error(const char* msg) {
  size_t msg_len = strlen(msg);

  wu_clear_last_error();

  wu_last_error = alloc_str(msg_len + 1);
  strncpy(wu_last_error, msg, msg_len + 1);
}

// Returns a copy of this unit's static last_error string. The caller
// is responsible for freeing the returned string.
char* wu_get_last_error() {
  size_t errlen = strlen(wu_last_error);
  char* errstr = alloc_str(msg_len + 1);

  strncpy(errstr, wu_last_error, msg_len + 1);
  return errstr;
}

void _wu_setup_color_arrays(double* input_colors, double* output_colors) {
  wu_input_colors = malloc(wu_color_count*3*sizeof(double));
  wu_output_colors = malloc(wu_color_count*3*sizeof(double));
  memcpy(wu_input_colors, input_colors, wu_color_count*3*sizeof(double));
  memcpy(wu_output_colors, output_colors, wu_color_count*3*sizeof(double));
}

void _wu_teardown() {
  wu_color_count = 0;
  if(wu_input_colors != NULL) {
    free(wu_input_colors);
  }
  if(wu_output_colors != NULL) {
    free(wu_output_colors);
  }
}

void _wu_lab_from_string(signed char* lab_ints, char* pixel_norm_color) {
  char* separated_strings[3];

  separated_strings[0] = strtok(pixel_norm_color, ",");
  separated_strings[1] = strtok(NULL, ",");
  separated_strings[2] = strtok(NULL, ",");

  lab_ints[0] = (signed char) (round(strtod(separated_strings[0], NULL) * 100));
  lab_ints[1] = (signed char) (round(strtod(separated_strings[1], NULL) * 255));
  lab_ints[2] = (signed char) (round(strtod(separated_strings[2], NULL) * 255));
}

void _wu_get_mapped_color(char* input_string, char* output_string) {
  int i, shortest_index;
  double shortest_distance = -1.0, current_distance;
  signed char lab_ints[3];

  _wu_lab_from_string(lab_ints, input_string);

  for(i = 0; i < wu_color_count; i++) {
    current_distance = sqrt(
        pow((double)lab_ints[0] - wu_input_colors[i*3], 2) +
        pow((double)lab_ints[1] - wu_input_colors[i*3 + 1], 2) +
        pow((double)lab_ints[2] - wu_input_colors[i*3 + 2], 2));

    if(shortest_distance == -1.0 || current_distance < shortest_distance) {
      shortest_distance = current_distance;
      shortest_index = i;
    }
  }

  sprintf(output_string, "#%02X%02X%02X",
    (unsigned char) (round(wu_output_colors[shortest_index * 3] / 100.0 * 255)),
    (unsigned char) (round(wu_output_colors[shortest_index * 3 + 1])),
    (unsigned char) (round(wu_output_colors[shortest_index * 3 + 2]))
  );
};


void _wu_get_mapped_color_with_in_out(char* input_string, char* output_string,
                                      double* input_colors, double* output_colors,
                                      unsigned int count) {
  wu_color_count = count;
  _wu_setup_color_arrays(input_colors, output_colors);
  _wu_get_mapped_color(input_string, output_string);
}

int wu_lab_recolor(FILE* input_file, FILE* output_file, double* input_colors,
                   double* output_colors, unsigned int count, WU_LABRECOLORERR *err) {
  MagickBooleanType status;
  MagickWand* recolor_wand;
  PixelWand** recolor_pixels;
  PixelIterator* iterator;

  char* pixel_norm_color;
  char final_color[8];
  size_t width;
  ssize_t y, x;

  ExceptionType severity;
  char* description;

  wu_color_count = count;
  _wu_setup_color_arrays(input_colors, output_colors);

  if(input_file == NULL || output_file == NULL) {
    return_with_error(WU_NULL_IMAGE);
  }

  MagickWandGenesis();
  recolor_wand = NewMagickWand();
  status = MagickReadImageFile(recolor_wand, input_file);
  if(status == MagickFalse) {
    return_with_wand_error(recolor_wand);
  }

  iterator = NewPixelIterator(recolor_wand);
  if(iterator == (PixelIterator *) NULL) {
    return_with_wand_error(recolor_wand);
  }

  ssize_t image_height = (ssize_t) MagickGetImageHeight(recolor_wand);
  for(y=0; y < image_height; y++) {
    /* printf("\r                  "); */
    /* printf("Line %zd of %zd", y, image_height); */
    recolor_pixels = PixelGetNextIteratorRow(iterator, &width);
    if(recolor_pixels == (PixelWand **) NULL) {
      break;
    }

    for(x=0; x < (ssize_t) width; x++) {
      pixel_norm_color = PixelGetColorAsNormalizedString(recolor_pixels[x]);
      strcpy(final_color, "");

      _wu_get_mapped_color(pixel_norm_color, final_color);
      PixelSetColor(recolor_pixels[x], final_color);
    }
    PixelSyncIterator(iterator);
  }

  iterator = DestroyPixelIterator(iterator);

  status = MagickWriteImageFile(recolor_wand, output_file);
  if(status == MagickFalse) {
    return_with_wand_error(recolor_wand)
  }

  recolor_wand = DestroyMagickWand(recolor_wand);
  MagickWandTerminus();
  _wu_teardown();
  return 1;
}
