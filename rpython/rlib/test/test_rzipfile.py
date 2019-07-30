import py

from rpython.rlib.rzipfile import RZipFile
from rpython.tool.udir import udir
from zipfile import ZIP_STORED, ZIP_DEFLATED, ZipInfo, ZipFile
from rpython.rtyper.test.tool import BaseRtypingTest
from rpython.rlib import clibffi # for side effect of testing lib_c_name on win32
import os
import time

try:
    from rpython.rlib import rzlib
except CompilationError as e:
    py.test.skip("zlib not installed: %s " % (e, ))

class BaseTestRZipFile(BaseRtypingTest):

    def setup_class(cls):
        tmpdir = udir.ensure('zipimport_%s' % cls.__name__, dir=1)
        zipname = str(tmpdir.join("somezip.zip"))
        cls.zipname = zipname
        zipfile = ZipFile(zipname, "w", compression=cls.compression)
        cls.year = time.localtime(time.time())[0]
        zipfile.writestr("one", "stuff\n")
        zipfile.writestr("dir" + os.path.sep + "two", "otherstuff")
        # Value selected to produce a CRC32 which is negative if
        # interpreted as a signed 32 bit integer.  This exercises the
        # masking behavior necessary on 64 bit platforms.
        zipfile.writestr("three", "hello, world")
        zipfile.close()

    def test_rzipfile(self):
        zipname = self.zipname
        year = self.year
        compression = self.compression
        def one():
            rzip = RZipFile(zipname, "r", compression)
            info = rzip.getinfo('one')
            return (info.date_time[0] == year and
                    rzip.read('one') == 'stuff\n' and
                    rzip.read('three') == 'hello, world')

        assert one()
        assert self.interpret(one, [])

    def test_rzipfile_bytes(self):
        data = 'PK\x03\x04\n\x00\x00\x00\x00\x00/S#N\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x1c\x00mssun.pyUT\t\x00\x03\x9aS.\\\xb4S.\\ux\x0b\x00\x01\x04\xe9\x03\x00\x00\x04\xe9\x03\x00\x00PK\x01\x02\x1e\x03\n\x00\x00\x00\x00\x00/S#N\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00\x18\x00\x00\x00\x00\x00\x00\x00\x00\x00\xb4\x81\x00\x00\x00\x00mssun.pyUT\x05\x00\x03\x9aS.\\ux\x0b\x00\x01\x04\xe9\x03\x00\x00\x04\xe9\x03\x00\x00PK\x05\x06\x00\x00\x00\x00\x01\x00\x01\x00N\x00\x00\x00B\x00\x00\x00\x00\x00'
        rzip = RZipFile(zipname="example.zip", data=data)

class TestRZipFile(BaseTestRZipFile):
    compression = ZIP_STORED

class TestRZipFileCompressed(BaseTestRZipFile):
    compression = ZIP_DEFLATED
