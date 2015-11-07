/*!
 * \file dictionaryvar.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dictionaryvar object (\c DICTIONARYVAR).
 *
 * \version The \c DICTIONARYVAR object was introduced in DXF R14.
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


#include "dictionaryvar.h"


/*!
 * \brief Allocate memory for a DXF \c DICTIONARYVAR object.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionaryvar_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDictionaryVar *dictionaryvar = NULL;
        size_t size;

        size = sizeof (DxfDictionaryVar);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dictionaryvar = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionaryVar struct.\n")),
                  __FUNCTION__);
                dictionaryvar = NULL;
        }
        else
        {
                memset (dictionaryvar, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DICTIONARYVAR
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionaryvar_init
(
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionaryvar = dxf_dictionaryvar_new ();
        }
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionaryVar struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionaryvar->id_code = 0;
        dictionaryvar->value = strdup ("");
        dictionaryvar->object_schema_number = strdup ("");
        dictionaryvar->dictionary_owner_soft = strdup ("");
        dictionaryvar->dictionary_owner_hard = strdup ("");
        dictionaryvar->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DICTIONARYVAR object.
 *
 * The last line read from file contained the string "DICTIONARYVAR". \n
 * Now follows some data for the \c DICTIONARYVAR object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c dictionaryvar. \n
 *
 * \return \c a pointer to \c dictionaryvar.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionaryvar_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionaryvar = dxf_dictionaryvar_new ();
                dictionaryvar = dxf_dictionaryvar_init (dictionaryvar);
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionaryvar->value);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dictionaryvar->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "DictionaryVariables") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a handle to ae
                         * entry object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionaryvar->object_schema_number);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionaryvar->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionaryvar->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Write DXF output to a file for a DXF \c DICTIONARYVAR object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_dictionaryvar_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DICTIONARYVAR");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dictionaryvar->value, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty value string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dictionaryvar->id_code);
        }
        if (strcmp (dictionaryvar->object_schema_number, "0") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty object schema number string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dictionaryvar->id_code);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dictionaryvar->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dictionaryvar->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dictionaryvar->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (dictionaryvar->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dictionaryvar->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dictionaryvar->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dictionaryvar->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nDictionaryVariables\n");
        }
        fprintf (fp->fp, "280\n%s\n", dictionaryvar->object_schema_number);
        fprintf (fp->fp, "  1\n%s\n", dictionaryvar->value);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DICTIONARYVAR and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_dictionaryvar_free
(
        DxfDictionaryVar *dictionaryvar
                /*!< Pointer to the memory occupied by the DXF
                 * \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDictionaryVar was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dictionaryvar->dictionary_owner_soft);
        free (dictionaryvar->dictionary_owner_hard);
        free (dictionaryvar->value);
        free (dictionaryvar->object_schema_number);
        free (dictionaryvar);
        dictionaryvar = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c DICTIONARYVAR
 * objects and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_dictionaryvar_free_chain
(
        DxfDictionaryVar *dictionaryvars
                /*!< pointer to the chain of DXF \c DICTIONARYVAR objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dictionaryvars == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (dictionaryvars != NULL)
        {
                struct DxfDictionaryVar *iter = dictionaryvars->next;
                dxf_dictionary_free (dictionaryvars);
                dictionaryvars = (DxfDictionaryVar *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c DICTIONARYVAR object.
 *
 * \return ID code.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_dictionaryvar_get_id_code
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dictionaryvar->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dictionaryvar->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c DICTIONARYVAR object.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_id_code
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        int id_code
                /*!< Identification number for the object.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionaryvar->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c DICTIONARYVAR object.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
char *
dxf_dictionaryvar_get_dictionary_owner_soft
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dictionaryvar->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF*/
