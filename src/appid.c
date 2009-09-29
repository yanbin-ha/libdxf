/*!
 * \file appid.c
 * \author Copyright (C) 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF application identity entity (\c APPID).
 *
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
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

#include "global.h"
#include "appid.h"

/*!
 * \brief Write DXF output for an \c APPID entity.
 */
static int
dxf_write_appid
(
        FILE *fp,
                /*!< File pointer to output file (or device). */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_appid () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");

        if (strcmp (application_name, "") == 0)
        {
                fprintf (stderr, "[File: %s: line: %d] Warning: empty application_name string for the %s entity with id-code: %x.\n", __FILE__, __LINE__, dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to default layer.\n", dxf_entity_name);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        fprintf (fp, "  2\n%s\n", application_name);
        fprintf (fp, " 70\n%d\n", standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_appid () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/*!
 * \brief Write DXF output to a file for an \c APPID entity.
 */
int
dxf_write_appid_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfAppid dxf_appid
                /*!< DXF appid entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_appid_struct () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");
        if (dxf_appid.application_name == "")
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_appid.id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n", dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_appid.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_appid.id_code);
        }
        fprintf (fp, "  2\n%s\n", dxf_appid.application_name);
        fprintf (fp, " 70\n%d\n", dxf_appid.standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_appid_struct () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF*/
