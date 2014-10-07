/*!
 * \file endblk.h
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF end of block marker entity (\c ENDBLK).
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


#ifndef ENDBLK_H
#define ENDBLK_H


#include "global.h"
#include "util.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD end block entity.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_endblk
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
} DxfEndblk, * DxfEndblkPtr;


DxfEndblk *dxf_endblk_new ();
DxfEndblk *dxf_endblk_init
(
        DxfEndblk *dxf_endblk
);
DxfEndblk *dxf_endblk_read
(
        DxfFile *fp,
        DxfEndblk *dxf_endblk
);
int dxf_endblk_write
(
        DxfFile *fp,
        DxfEndblk *dxf_endblk
);
int dxf_endblk_free
(
        DxfEndblk *dxf_endblk
);


#endif /* ENDBLK_H */


/* EOF */
