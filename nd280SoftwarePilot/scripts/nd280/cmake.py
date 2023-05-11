#######################################################################
# This package is automatically available to python scripts in the
# nd280SoftwarePilot/scripts directory.
#
# This provide the functions:
#
#  nd280.cmake.GetPackages(dir) -- Return a list of the packages
#            in the given directory.  The actual command run
#            is "os.listdir(<dir>)"
#
#  nd280.cmake.GetUses(dir) -- Return a list of packages kept in
#            "<package>ND280_USE.cmake".  The actual command that is 
#            run is "()"
#
#  nd280.cmake.GetMissing(dir=".") -- Return a list of the missing
#            packages.  This is parsed from the error output of the
#            "(cd <dir>; cmt show uses)" command.
#
#  nd280.cmake.GetMissingPackages(dir=".") -- Return a list of the missing
#            packages.  This is parsed from the error output of the
#            "(cd <dir>; cmt show packages)" command.
#
# This provides the class:
#
#  nd280.cmake.Package -- A pure data class with fields for
#    name -- The name of the package.
#    version -- The version string for the package.
#    rootpath -- The root of the path that would be set inside the package.
#    uses -- A list of packages used by this package.

import re
import nd280.shell
import xml.parsers.expat
import shell

class Package:
    """A container for a package description.  The fields are:

    name -- The name of the package.

    version -- The version string for the package.  This is derived
          from the subdirectory containing the package.

    rootpath -- The root of the path that would be set inside the package.

    uses -- A list of packages used by this package.
    
"""
    def __init__(self):
        self.name = None
        self.version = None
        self.rootpath = None
        self.uses = None

    def __repr__(self):
        rep = "<package"
        if self.name != None: rep += " n: " + str(self.name)
        else: rep += " n: None"
        if self.version != None: rep += " v: " + str(self.version)
        else: rep += " v: None"
        if self.rootpath != None: rep += " P: " + str(self.rootpath)
        else: rep += " P: None"
        if self.uses != None: rep += " u: " + str(self.uses)
        else: rep += " u: None"
        rep += ">"
        return rep

def GetUses(dir):
    """Get a list of CMake packages used by the present one"""

    filename=shell.CaptureShell("ls "+dir+"/cmake/*ND280_USE.cmake")[0]
    print filename
    nfile = file(filename)
    packages = []
    for line in nfile:
        if ND280_USE in line:
            package = Package()
            namever = line[line.find("(")+1:s.find(")")]
            package.name = namever[0:namever.find(" ")]
            package.ver = namever[namever.find(" ")+1:-1]
            packages.append(package)
    return packages

#def GetPackages(dir):
#    """Get a list of the CMake packages accessible from dir"""
#
#    packagelist = [o for o in os.listdir(dir)
#                if os.path.isdir(os.path.join(dir, o)) & os.exists(dir+"/cmake/CMakeLists.txt")]
#    return packagelist

def GetMissingPackages(dir):
    """Get a list of the missing packages used by the present one"""

    packages = GetUses(dir)

    missingList = []
    for package in packages:
        if os.exists(os.environ["ND280_ROOT"]+"/"+package.name+"/"+package.version): continue
        missingList.append(package)

    return missingList

def CheckCMake():
    """ Check if CMake is available"""

    foundVersion = False
    try:
        cmakeVersion = nd280.shell.CaptureShell("cmake --version | grep version | cut -d. -f3")
        for line in cmakeVersion[0].splitlines():
            if (re.compile(r'(\d+).(\d+).(\d+)').match(line)):
                foundVersion = True
    except:
        foundVersion = False

    if not foundVersion:
        print "WARNING: CMake not available"
        
    return foundVersion
