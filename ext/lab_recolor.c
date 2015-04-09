// A ruby wrapper around lab_recolor

#include <stdlib.h>
#include <stdio.h>
#include <ruby.h>

#define TMPFILE_NAME_FMT "lab_recolor_XXXXXX.tif"

VALUE LabRecolor = Qnil;
VALUE FailedRecolor = Qnil;

static FILE* mk_img_tempfile(const char*) {
  FILE* file;
  char* name = mktemp(TMPFILE_NAME_FMT);

  return fopen(name, "rw");
}

VALUE recolor_lab(VALUE image, VALUE in_colors, VALUE out_colors) {
  if(TYPE(image) != T_FILE) {
    rb_raise(rb_eTypeError, "Input image must be a file!"
  } else if(TYPE(in_colors) != T_ARRAY) {
    rb_raise(rb_eTypeError, "Source color list must be an array!")
  } else if (TYPE(out_colors) != T_ARRAY) {
    rb_raise(rb_eTypeError, "Dest color list must be an array!")
  }

  
  FILE* output_file = mk_img_tempfile();
  long int colors_len = RARRY_LEN(in_colors);
  int result = wu_lab_recolor(input_file, output_file, in_colors, out_colors,
                              number_colors, &err);
  
  if(result != 0) {
    char* errstr = wu_get_last_error();
    rb_raise(FAILED_RECOLOR, errstr);
    free(errstr);
  }
}

typedef struct {
  int len; 
  double* colors;
} color_set;

void InitLabRecolor() {
  LabRecolor = rb_define_module("LabRecolor");
  FailedRecolor = rb_define_class_under(
    LabRecolor, "FailedRecolor", rb_const_get("Exception"))
  rb_define_singleton_method(LabRecolor, "process", recolor_lab, 2);
}
