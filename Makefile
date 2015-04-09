CFLAGS+=-Wall -I./src --std=c99
CC?=clang # or GCC if you're into that.
VERSION=0.0.1

# Set up image magick paths.  When building you'll need to 
# supply IMAGEMAGICK_PREFIX if its not in /usr
IMAGEMAGICK_PREFIX?=/usr
IMAGEMAGICK_INC=$(IMAGEMAGICK_PREFIX)/include/ImageMagick/
IMAGEMAGICK_LIB=$(IMAGEMAGICK_PREFIX)/lib/
CFLAGS+=-I$(IMAGEMAGICK_INC) -L$(IMAGEMAGICK_LIB)

LDFLAGS=-lMagickWand -lm

PREFIX?=/usr/local
INSTALL=cp -pf

ifeq ($(DEBUG), true)
	CLFAGS += -DDEBUG -g
endif

cc-command = $(CC) $(CFLAGS) $1 $(LDFLAGS)

wu-lab-recolor: lib/wu-lab-recolor.o
	$(call cc-command,-o bin/wu-lab-recolor lib/wu-lab-recolor.o src/main.c)

lib/wu-lab-recolor.o:
	$(call cc-command,-c -o lib/wu-lab-recolor.o src/lab_recolor.c)

bin/test: lib/wu-lab-recolor.o
	$(call cc-command,-o bin/test lib/wu-lab-recolor.o test/test.c)

clean: ; rm -f lib/wu-lab_recolor.o bin/wu-lab-recolor bin/test
.PHONY: clean

test: bin/test
	bin/test
.PHONY: test
