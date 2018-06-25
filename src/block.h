/*!
 * \file block.h
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2014, 2015, 2016, 2017,
 * 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Header file for a DXF block entity (\c BLOCK).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#ifndef LIBDXF_SRC_BLOCK_H
#define LIBDXF_SRC_BLOCK_H


#include "global.h"
#include "util.h"
#include "endblk.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD block entity.
 *
 * The Blocks section of the DXF file contains all the Block Definitions.\n
 * This section contains the entities that make up the Blocks used in the
 * drawing, including anonymous Blocks generated by the HATCH command and by
 * associative dimensioning.\n
 * The format of the entities in this section is identical to those in the
 * Entities section described later, so see that section for details.\n
 * All entities in the Blocks section appear between Block and Endblk
 * entities.\n
 * Block and Endblk entities appear only in the Blocks section.\n
 * Block definitions are never nested (that is, no Block or Endblk entity
 * ever appears within another Block-Endblk pair), although a Block
 * definition can contain an INSERT entity.\n
 * \n
 * External References are written in the DXF file as any Block Definition,
 * except they also include a text string (group code 1) of the path and
 * filename of the External Reference.\n
 */
typedef struct
dxf_block_struct
{
        char *xref_name;
                /*!< Xref path name.\n
                 * Group code = 1. */
        char *block_name;
                /*!< Block name.\n
                 * Group code = 2. */
        char *block_name_additional;
                /*!< Additional block name.\n
                 * Group code = 3. */
        char *description;
                /*!< Block description (optional).\n
                 * Group code = 4. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        int block_type;
                /*!< Bit coded:\n
                 * <ol>
                 * <li value = "1"> this is an anonymous Block generated
                 * by hatching, associative dimensioning, other internal
                 * operations, or an application.</li>
                 * <li value = "2"> this Block has Attributes.</li>
                 * <li value = "4"> this Block is an external reference (Xref).</li>
                 * <li value = "8"> not used.</li>
                 * <li value = "16"> this Block is externally dependent.</li>
                 * <li value = "32"> this is a resolved external
                 * reference, or dependent of an external reference.</li>
                 * <li value = "64"> this definition is referenced.</li>
                 * </ol>
                 * Group code = 70. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle to owner object.\n
                 * Group code = 330. */
        struct DxfEndblk *endblk;
                /*!< pointer to the end of block marker. */
        struct DxfBlock *next;
                /*!< pointer to the next DxfBlock.\n
                 * \c NULL in the last DxfBlock. */
        
} DxfBlock;


DxfBlock *dxf_block_new ();
DxfBlock *dxf_block_init (DxfBlock *block);
DxfBlock *dxf_block_read (DxfFile *fp, DxfBlock *block);
int dxf_block_write (DxfFile *fp, DxfBlock *block);
int dxf_block_write_endblk (DxfFile *fp);
int dxf_block_write_table (DxfFile *fp, DxfBlock *blocks_list);
int dxf_block_free (DxfBlock *block);
void dxf_block_free_chain (DxfBlock *blocks);
char *dxf_block_get_xref_name (DxfBlock *block);
DxfBlock *dxf_block_set_xref_name (DxfBlock *block, char *xref_name);
char *dxf_block_get_block_name (DxfBlock *block);
DxfBlock *dxf_block_set_block_name (DxfBlock *block, char *block_name);
char *dxf_block_get_block_name_additional (DxfBlock *block);
DxfBlock *dxf_block_set_block_name_additional (DxfBlock *block, char *block_name_additional);
char *dxf_block_get_description (DxfBlock *block);
DxfBlock *dxf_block_set_description (DxfBlock *block, char *description);
int dxf_block_get_id_code (DxfBlock *block);
DxfBlock *dxf_block_set_id_code (DxfBlock *block, int id_code);
char *dxf_block_get_layer (DxfBlock *block);
DxfBlock *dxf_block_set_layer (DxfBlock *block, char *layer);
DxfPoint *dxf_block_get_p0 (DxfBlock *block);
DxfBlock *dxf_block_set_p0 (DxfBlock *block, DxfPoint *p0);
double dxf_block_get_x0 (DxfBlock *block);
DxfBlock *dxf_block_set_x0 (DxfBlock *block, double x0);
double dxf_block_get_y0 (DxfBlock *block);
DxfBlock *dxf_block_set_y0 (DxfBlock *block, double y0);
double dxf_block_get_z0 (DxfBlock *block);
DxfBlock *dxf_block_set_z0 (DxfBlock *block, double z0);
int dxf_block_get_block_type (DxfBlock *block);
DxfBlock *dxf_block_set_block_type (DxfBlock *block, int block_type);
int dxf_block_is_anonymous (DxfBlock *block);
int dxf_block_has_attributes (DxfBlock *block);
int dxf_block_is_xreferenced (DxfBlock *block);
int dxf_block_is_xdependent (DxfBlock *block);
int dxf_block_is_xresolved (DxfBlock *block);
int dxf_block_is_referenced (DxfBlock *block);
double dxf_block_get_extr_x0 (DxfBlock *block);
DxfBlock *dxf_block_set_extr_x0 (DxfBlock *block, double extr_x0);
double dxf_block_get_extr_y0 (DxfBlock *block);
DxfBlock *dxf_block_set_extr_y0 (DxfBlock *block, double extr_y0);
double dxf_block_get_extr_z0 (DxfBlock *block);
DxfBlock *dxf_block_set_extr_z0 (DxfBlock *block, double extr_z0);
DxfPoint *dxf_block_get_extrusion_vector_as_point (DxfBlock *block);
DxfBlock *dxf_block_set_extrusion_vector (DxfBlock *block, double extr_x0, double extr_y0, double extr_z0);
char *dxf_block_get_object_owner_soft (DxfBlock *block);
DxfBlock *dxf_block_set_object_owner_soft (DxfBlock *block, char *object_owner_soft);
struct DxfEndblk *dxf_block_get_endblk (DxfBlock *block);
DxfBlock *dxf_block_set_endblk (DxfBlock *block, struct DxfEndblk *endblk);
DxfBlock *dxf_block_get_next (DxfBlock *block);
DxfBlock *dxf_block_set_next (DxfBlock *block, DxfBlock *next);
DxfBlock *dxf_block_get_last (DxfBlock *block);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_BLOCK_H */


/* EOF */
