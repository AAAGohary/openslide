/*
 *  OpenSlide, a library for reading whole slide image files
 *
 *  Copyright (c) 2007-2013 Carnegie Mellon University
 *  All rights reserved.
 *
 *  OpenSlide is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, version 2.1.
 *
 *  OpenSlide is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with OpenSlide. If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OPENSLIDE_OPENSLIDE_DECODE_TIFFLIKE_H_
#define OPENSLIDE_OPENSLIDE_DECODE_TIFFLIKE_H_

#include "openslide-private.h"
#include "openslide-hash.h"

#include <stdio.h>
#include <stdint.h>
#include <glib.h>

/* TIFF container support (for formats violating the TIFF spec) */

struct _openslide_tifflike *_openslide_tifflike_create(FILE *f, GError **err);

void _openslide_tifflike_destroy(struct _openslide_tifflike *tl);

bool _openslide_tifflike_init_properties_and_hash(openslide_t *osr,
                                                  const char *filename,
                                                  struct _openslide_tifflike *tl,
                                                  struct _openslide_hash *quickhash1,
                                                  int32_t lowest_resolution_level,
                                                  int32_t property_dir,
                                                  GError **err);

// helpful printout?
void _openslide_tifflike_print(struct _openslide_tifflike *tl);

int64_t _openslide_tifflike_get_directory_count(struct _openslide_tifflike *tl);

int64_t _openslide_tifflike_get_value_count(struct _openslide_tifflike *tl,
                                            int64_t dir, int32_t tag);

// accessors only set *ok on failure

// TIFF_BYTE, TIFF_SHORT, TIFF_LONG, TIFF_IFD
uint64_t _openslide_tifflike_get_uint(struct _openslide_tifflike *tl,
                                      int64_t dir, int32_t tag, int64_t i,
                                      bool *ok);

// TIFF_SBYTE, TIFF_SSHORT, TIFF_SLONG
int64_t _openslide_tifflike_get_sint(struct _openslide_tifflike *tl,
                                     int64_t dir, int32_t tag, int64_t i,
                                     bool *ok);

// TIFF_FLOAT, TIFF_DOUBLE, TIFF_RATIONAL, TIFF_SRATIONAL
double _openslide_tifflike_get_float(struct _openslide_tifflike *tl,
                                     int64_t dir, int32_t tag, int64_t i,
                                     bool *ok);

// TIFF_ASCII, TIFF_UNDEFINED
const void *_openslide_tifflike_get_buffer(struct _openslide_tifflike *tl,
                                           int64_t dir, int32_t tag);

#endif