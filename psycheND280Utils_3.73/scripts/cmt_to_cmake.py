#!/usr/bin/python

import os, sys, re
import shutil

from optparse import OptionParser


def compare( pattern, string ):
    """ find patterns in string """
    match = re.search(pattern, string )
    if not match:
        return False
    return True

def do_the_job(foldername):
    fprevious = os.getcwd()

    os.chdir(str(foldername))
   
    if not os.path.isdir(os.getcwd() + "/cmake"):
        os.mkdir("cmake")

    if not os.path.isdir(os.getcwd() + "/inc"):
        os.mkdir("inc")
        
 
    
    os.chdir("cmt")
    
    #move setup scripts
    for root, dirs, files in os.walk(os.getcwd()):
        for name in files:
            if compare("rootmap", name) or compare("geometry_setup", name):
                if not os.path.isdir(os.getcwd() + "/setup_script"):
                    os.mkdir("../setup_script")
                shutil.copyfile(os.getcwd() + "/" + name, os.getcwd() + "/../setup_script/" + name)
                #replace src with inc
                #and add CMTCONFIG/lib for libraries
                roofile = open(os.getcwd() + "/../setup_script/" + name,"r")
                filedata = roofile.read()
                filedata = filedata.replace("/src/", "/inc/")
                filedata = filedata.replace("CONFIG", "CONFIG/lib")
                
                roofile = open(os.getcwd() + "/../setup_script/" + name,"w")
                roofile.write(filedata)
                
    #move *.h* to inc
    os.chdir(str(foldername))
    if os.path.isdir(os.getcwd() + "/src"):
        os.chdir("src")

        tree = list(os.walk(os.getcwd()))

        ##folders in src
        for folder in tree[0][1]:
            for root, dirs, files in os.walk(os.getcwd() + "/" + folder):
                for name in files:
                    if compare("\.h", name):
                        if not os.path.isdir(os.getcwd() + "/../inc/" + folder):
                            os.mkdir(os.getcwd() + "/../inc/" + folder)
                        shutil.move(os.getcwd() + "/" + folder + "/" + name, os.getcwd() + "/../inc/" + folder + "/" + name)

        ##files in src
        for header in tree[0][2]:
            if compare("\.h", header):
                shutil.move(os.getcwd() + "/" + header, os.getcwd() + "/../inc/" + header)

    #create cmake files
    #CMakeFiles
    os.chdir(str(foldername))
    os.chdir("cmake")

    params = foldername.split("/")
    package = str(params[len(params)-1])

    uselist = []

    version = ""

    parlist = [
            "# CMakeLists.txt for " + package + " package. It creates a library with dictionary and a main program\n",
            "\n",
            "cmake_minimum_required(VERSION 3.9 FATAL_ERROR)\n",
            "find_package(nd280SoftwarePolicy 3.1)\n",
            "if( NOT nd280SoftwarePolicy_FOUND)\n",
            "   message(FATAL_ERROR \" nd280SoftwarePolicy not found - abort \")\n",
            "endif()\n",
            "\n",
            "include(" + package + "PackageVersion.cmake)\n",
            "ND280_PROJECT(" + package + " ${PACKAGE_VERSION} NOVERSION)\n",
            "include(" + package + "ND280_USE.cmake)\n",
            "\n"]
    parlist.append("\n")
    parlist.append("ND280_STANDARD_LIBRARY()\n")
    parlist.append("\n")

    #open requirements
    requirements = open(foldername + "/cmt/requirements","r")

    line = requirements.readline()

    while line:

        if compare("application", line) and not compare("#", line):
            pars = line.split()
            apps = pars[2].split("/")
            apps[len(apps)-1] = apps[len(apps)-1].replace("*", "")
            parlist.append("ND280_EXECUTABLE(" + pars[1] + " " + apps[len(apps)-1] + ")\n")

        if compare("use ", line) and not compare("#", line):
            pars = line.split()
            if len(pars) == 4 or len(pars) == 2 or len(pars) == 3:
                uselist.append("ND280_USE(" + pars[1] + ")\n")

        if compare("version ", line) and not compare("#", line):
            pars = line.split()
            version = pars[1]

        line = requirements.readline()


    parlist.append("\n")
    parlist.append("ND280_END_PROJECT()\n")

    finalfile = open("CMakeLists.txt", "w+")
    finalfile.writelines(parlist)
    finalfile.close()

    # config
    parlist = [
            "include(${" + package + "_DIR}/" + package + "ND280_USE.cmake)"]

    finalfile = open(package+"Config.cmake", "w+")
    finalfile.writelines(parlist)
    finalfile.close()

    # config version
    parlist = [
            "# This is a basic version file for the Config-mode of find_package().\n",
            "# It is used by write_basic_package_version_file() as input file for configure_file()\n",
            "# to create a version-file which can be installed along a config.cmake file.\n",
            "#\n",
            "# The created file sets PACKAGE_VERSION_EXACT if the current version string and\n",
            "# the requested version string are exactly the same and it sets\n",
            "# PACKAGE_VERSION_COMPATIBLE if the current version is >= requested version.\n",
            "# The variable CVF_VERSION must be set before calling configure_file().\n",
            "\n",
            "include(${CMAKE_CURRENT_LIST_DIR}/" + package + "PackageVersion.cmake)\n",
            "\n",
            "if(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)\n",
            "   set(PACKAGE_VERSION_COMPATIBLE FALSE)\n",
            "else()\n",
            "   set(PACKAGE_VERSION_COMPATIBLE TRUE)\n",
            "   if(PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)\n",
            "       set(PACKAGE_VERSION_EXACT TRUE)\n",
            "   endif()\n",
            "endif()\n",
            "\n",
            "# if the installed or the using project don't have CMAKE_SIZEOF_VOID_P set, ignore it:\n",
            "if(\"${CMAKE_SIZEOF_VOID_P}\" STREQUAL \"\" OR \"8\" STREQUAL \"\")\n",
            "   return()\n",
            "endif()\n",
            "\n",
            "# check that the installed version has the same 32/64bit-ness as the one which is currently searching:\n",
            "if(NOT CMAKE_SIZEOF_VOID_P STREQUAL \"8\")\n",
            "   math(EXPR installedBits \"8 * 8\")\n",
            "   set(PACKAGE_VERSION \"${PACKAGE_VERSION} (${installedBits}bit)\")\n",
            "   set(PACKAGE_VERSION_UNSUITABLE TRUE)\n",
            "endif()"]

    finalfile = open(package+"ConfigVersion.cmake", "w+")
    finalfile.writelines(parlist)
    finalfile.close()

    # nd280 use
    finalfile = open(package+"ND280_USE.cmake", "w+")
    finalfile.writelines(uselist)
    finalfile.close()

    # package version
    version = version.replace("v", "")
    version = version.replace("r", ".")
    version = version.replace("p", ".")
    listtmp = ["set(PACKAGE_VERSION \"" + version + "\")\n"]
    finalfile = open(package+"PackageVersion.cmake", "w+")
    finalfile.writelines(listtmp)
    finalfile.close()

# ============================================= #
if __name__ == "__main__":

    parser = OptionParser()
    usage = "usage: %prog [options] FILE"
    parser = OptionParser(usage=usage)


    (options, args) = parser.parse_args()

    if len(args) < 1:
        print("Needs one input arg")
        parser.print_help()
        exit(1)
        
    do_the_job(args[0])






