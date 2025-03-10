#!/usr/bin/env pytest
# -*- coding: utf-8 -*-
###############################################################################
#
# Project:  GDAL/OGR Test Suite
# Purpose:  Test read/write functionality for GXF driver.
# Author:   Even Rouault <even dot rouault at spatialys.com>
#
###############################################################################
# Copyright (c) 2008-2012, Even Rouault <even dot rouault at spatialys.com>
#
# SPDX-License-Identifier: MIT
###############################################################################


import gdaltest
import pytest

from osgeo import gdal

pytestmark = pytest.mark.require_driver("GXF")

###############################################################################
# Test a small GXF sample


def test_gxf_1():

    tst = gdaltest.GDALTest("GXF", "gxf/small.gxf", 1, 90)

    tst.testOpen()


###############################################################################
# Test an other GXF sample (with continuous line)


def test_gxf_2():

    tst = gdaltest.GDALTest("GXF", "gxf/small2.gxf", 1, 65042)
    wkt = """PROJCS["NAD27 / Ohio North",
    GEOGCS["NAD27",
        DATUM["NAD27",
            SPHEROID["NAD27",6378206.4,294.978699815746]],
        PRIMEM["unnamed",0],
        UNIT["degree",0.0174532925199433]],
    PROJECTION["Lambert_Conformal_Conic_2SP"],
    PARAMETER["standard_parallel_1",40.4333333333],
    PARAMETER["standard_parallel_2",41.7],
    PARAMETER["latitude_of_origin",39.6666666667],
    PARAMETER["central_meridian",82.5],
    PARAMETER["false_easting",609601.22],
    UNIT["ftUS",0.3048006096012]]"""

    tst.testOpen(check_prj=wkt)


gxf_list = [
    ("http://download.osgeo.org/gdal/data/gxf", "SAMPLE.GXF", 24068, -1),
    ("http://download.osgeo.org/gdal/data/gxf", "gxf_compressed.gxf", 20120, -1),
    ("http://download.osgeo.org/gdal/data/gxf", "gxf_text.gxf", 20265, -1),
    ("http://download.osgeo.org/gdal/data/gxf", "gxf_ul_r.gxf", 19930, -1),
    ("http://download.osgeo.org/gdal/data/gxf", "latlong.gxf", 12243, -1),
    ("http://download.osgeo.org/gdal/data/gxf", "spif83.gxf", 28752, -1),
]


@pytest.mark.parametrize(
    "downloadURL,fileName,checksum,download_size",
    gxf_list,
    ids=[tup[1] for tup in gxf_list],
)
def test_gxf(downloadURL, fileName, checksum, download_size):
    gdaltest.download_or_skip(downloadURL + "/" + fileName, fileName, download_size)

    ds = gdal.Open("tmp/cache/" + fileName)

    assert (
        ds.GetRasterBand(1).Checksum() == checksum
    ), "Bad checksum. Expected %d, got %d" % (checksum, ds.GetRasterBand(1).Checksum())
