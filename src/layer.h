/*!
 * \file layer.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF layer table.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_LAYER_H
#define LIBDXF_SRC_LAYER_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD layer entity.
 *
 * Xref-dependent layers are to be written to an output file during DXFOUT.
 */
typedef struct
dxf_layer
{
        char *layer_name;
                /*!< group code = 2. */
        char *linetype;
                /*!< group code = 6\n
                 * For these layers, the associated linetype name in the DXF
                 * file is always CONTINUOUS. */
        int color;
                /*!< group code = 62\n
                 * if negative, layer is off. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 0 = on and thawed\n
                 * 1 = if set, layer is frozen\n
                 * 2 = if set, layer is frozen by default in new viewports\n
                 * 4 = if set, layer is locked\n
                 * 8 = unused\n
                 * 128 = unused. */
        int plotting_flag;
                /*!< group code = 290\n
                 * Boolean, if set to 0, do not plot this layer. */
        char *material;
                /*!< group code = 347\n
                 * Hard-pointer ID / handle to Material object */
        int16_t lineweight;
                /*!< group code = 370\n
                 * Lineweight enum value. */
        char *plot_style_name;
                /*!< group code = 390\n
                 * Hard pointer ID / handle of PlotStyleName object. */
        struct DxfLayer *next;
                /*!< pointer to the next DxfLayer.\n
                 * \c NULL in the last DxfLayer. */
} DxfLayer, * DxfLayerPtr;


DxfLayer *
dxf_layer_new ();
DxfLayer *
dxf_layer_init
(
        DxfLayer *dxf_layer
);
DxfLayer *
dxf_layer_read
(
        DxfFile *fp,
        DxfLayer *dxf_layer
);
int
dxf_layer_write
(
        DxfFile *fp,
        DxfLayer *dxf_layer
);
int
dxf_layer_free
(
        DxfLayer *dxf_layer
);


#endif /* LIBDXF_SRC_LAYER_H */


/* EOF */
