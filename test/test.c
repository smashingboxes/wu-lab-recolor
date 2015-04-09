#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "lab_recolor.h"

#define run_test(fn_name) \
  printf("%s\n", #fn_name); \
  fn_name()

void test_lab_recolor() {
  FILE *input_file;
  FILE *output_file;
  WU_LABRECOLORERR err;

  int number_colors = 2;
  double input_colors[6] = { 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double output_colors[6] = { 50.0, 100.0, -100.0, 75.0, -75.1, 75.0 };

  input_file = fopen("test/fixtures/labtiff.tif", "r");
  assert(input_file);

  output_file = fopen("test.tif", "w");

  int result = wu_lab_recolor(input_file, output_file, input_colors, output_colors,
                              number_colors, &err);
  assert(result);

  fseek(output_file, 0L, SEEK_END);
  int size = ftell(output_file);
  fseek(output_file, 0L, SEEK_SET);
  assert(size);

  fclose(input_file);
  fclose(output_file);
}

void test_lab_recolor_with_null_image() {
  FILE* input_file = NULL;
  FILE* output_file = NULL;
  int number_colors = 2;
  double input_colors[6] = { 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double output_colors[6] = { 50.0, 100.0, -100.0, 75.0, -75.1, 75.0 };
  WU_LABRECOLORERR err;

  int result = wu_lab_recolor(input_file, output_file, input_colors, output_colors,
                              number_colors, &err);
  assert(!result);

  assert(err == WU_NULL_IMAGE);
}

void test_lab_recolor_with_invalid_image_type() {
  FILE *input_file;
  FILE *output_file;
  int number_colors = 2;
  double input_colors[6] = { 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double output_colors[6] = { 50.0, 100.0, -100.0, 75.0, -75.1, 75.0 };
  WU_LABRECOLORERR err;

  input_file = fopen("test/fixtures/no_image.txt", "r");
  assert(input_file);

  output_file = tmpfile();

  int result = wu_lab_recolor(input_file, output_file, input_colors, output_colors,
                              number_colors, &err);
  assert(!result);
  assert(err == WU_MAGICK_WAND_ERR);
}

void test_lab_from_string() {
  signed char lab_ints[3];
  char normalized_color_string[80];
  strcpy(normalized_color_string, "1,1,0");

  _wu_lab_from_string(lab_ints, normalized_color_string);
  assert(lab_ints[0] == 100);
  assert(lab_ints[1] == -1);
  assert(lab_ints[2] == 0);

  strcpy(normalized_color_string, "0,0.555959,0.2512344");

  _wu_lab_from_string(lab_ints, normalized_color_string);
  assert(lab_ints[0] == 0);
  assert(lab_ints[1] == -114);
  assert(lab_ints[2] == 64);
}

void test_closest_color_map() {
  int number_colors = 2;
  double input_colors[6] = { 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  double output_colors[6] = { 50.0, 100.0, -100.0, 75.0, -75.1, 75.0 };
  char input_string[80];
  char output_string[80];

  strcpy(input_string, "1,0.01111,1");

  _wu_get_mapped_color_with_in_out(input_string, output_string, input_colors, output_colors, number_colors);
  _wu_teardown();
  assert(strcmp(output_string,"#80649C") == 0);

  strcpy(input_string, "0.25,0.444444444444,0.0011111111");

  _wu_get_mapped_color_with_in_out(input_string, output_string, input_colors, output_colors, number_colors);
  _wu_teardown();
  assert(strcmp(output_string,"#BFB54B") == 0);
}

int main(int argc, char** argv) {
  run_test(test_lab_recolor);
  run_test(test_lab_recolor_with_null_image);
  run_test(test_lab_recolor_with_invalid_image_type);
  run_test(test_lab_from_string);
  run_test(test_closest_color_map);
  printf("\nOK\n");
  return 0;
}
