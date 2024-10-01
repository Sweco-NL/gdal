/******************************************************************************
 * $Id$
 *
 * Project:  GML Reader
 * Purpose:  Public Declarations for OGR free GML Reader code.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2002, Frank Warmerdam
 * Copyright (c) 2008-2013, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef GMLREADER_H_INCLUDED
#define GMLREADER_H_INCLUDED

#include "cpl_port.h"
#include "cpl_vsi.h"
#include "cpl_minixml.h"
#include "ogr_core.h"
#include "gmlutils.h"
#include "gmlfeature.h"

#include <map>
#include <vector>

// Special value to map to a NULL field
#define OGR_GML_NULL "___OGR_GML_NULL___"

/************************************************************************/
/*                              IGMLReader                              */
/************************************************************************/
class CPL_DLL IGMLReader
{
  public:
    virtual ~IGMLReader();

    virtual bool IsClassListLocked() const = 0;
    virtual void SetClassListLocked(bool bFlag) = 0;

    virtual void SetSourceFile(const char *pszFilename) = 0;

    virtual void SetFP(CPL_UNUSED VSILFILE *fp)
    {
    }

    virtual const char *GetSourceFileName() = 0;

    virtual int GetClassCount() const = 0;
    virtual GMLFeatureClass *GetClass(int i) const = 0;
    virtual GMLFeatureClass *GetClass(const char *pszName) const = 0;

    virtual int AddClass(GMLFeatureClass *poClass) = 0;
    virtual void ClearClasses() = 0;

    virtual GMLFeature *NextFeature() = 0;
    virtual void ResetReading() = 0;

    virtual bool LoadClasses(const char *pszFile = nullptr) = 0;
    virtual bool SaveClasses(const char *pszFile = nullptr) = 0;

    virtual bool ResolveXlinks(const char *pszFile, bool *pbOutIsTempFile,
                               char **papszSkip = nullptr,
                               const bool bStrict = false) = 0;

    virtual bool HugeFileResolver(const char *pszFile, bool bSqliteIsTempFile,
                                  int iSqliteCacheMB) = 0;

    virtual bool PrescanForSchema(bool bGetExtents = true,
                                  bool bOnlyDetectSRS = false) = 0;
    virtual bool PrescanForTemplate() = 0;

    virtual bool HasStoppedParsing() = 0;

    virtual void SetGlobalSRSName(CPL_UNUSED const char *pszGlobalSRSName)
    {
    }

    virtual const char *GetGlobalSRSName() = 0;
    virtual bool CanUseGlobalSRSName() = 0;

    virtual bool SetFilteredClassName(const char *pszClassName) = 0;
    virtual const char *GetFilteredClassName() = 0;

    virtual bool IsSequentialLayers() const
    {
        return false;
    }
};

IGMLReader *CreateGMLReader(bool bUseExpatParserPreferably,
                            bool bInvertAxisOrderIfLatLong,
                            bool bConsiderEPSGAsURN,
                            GMLSwapCoordinatesEnum eSwapCoordinates,
                            bool bGetSecondaryGeometryOption);

#endif /* GMLREADER_H_INCLUDED */
