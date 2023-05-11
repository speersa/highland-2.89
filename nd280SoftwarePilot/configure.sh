#! /bin/sh
#
# Create the login script (nd280SoftwarePilot.profile). This
# rewrites input templates with installation specific values.
#

echo ""

usage () {
  cat <<EOF

Setup the ND280 Software.  This creates the files that can be sourced by users 
to access the software.  Mostly they just define paths.  This script must be 
executed from the main "nd280SoftwarePilot" directory. After it has been run, 
the nd280SoftwarePilot.profile file will exist. This can be directly sourced 
by the user, or an alias can be added to the profile.

-- Usage:
  ./configure.sh

-- Options:
  -h : Print this documentation.
  -g : Manually set the git server to clone packages from
       (default is git@git.t2k.org/nd280/)
  -c : Manually set the path to the desired cmake command.
       e.g. /path/to/cmake-3.0/bin/cmake
       This is useful for binary installations of CMake on
       systems where you do not have permission to install
       a source version of CMake.
       If not specified your machine's native CMake package
       will be used. 
  -i : Use the CMake 3.14.0 binary packaged with the software 
       to compile the software. Use this if your native
       CMake is too old and you don't want the hassle of 
       installing a new version yourself. You must specify
       that the CMake package be installed when running
       nd280-install.
       If not specified your machine's native CMake package
       will be used.

EOF
}

######################################################################

#set the install location
ND280PILOT_ROOT=$(dirname ${PWD})
ND280_ROOT=$ND280PILOT_ROOT

#set the download location for external tarballs
ND280_DOWNLOADS=http://nd280.lancs.ac.uk/downloads

#set the default for the ND280 GitLab server. Will be used as ${ND280_GIT}repositoryname"
ND280_GIT=`git config remote.origin.url | sed s:pilot/nd280SoftwarePilot.git:: | sed s:pilot/nd280SoftwarePilot::`

#set the default option for using the package CMake binary
#CMAKE_BINARY=false

#check this file is being run from top "nd280SoftwarePilot" repository. Exit if not
configurescriptdir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
if [ "${configurescriptdir}" != $(pwd) ]; then
  usage
  echo ERROR: Must be run from top level "nd280SoftwarePilot" directory
  exit 1;
fi

while getopts "hig:c:" option; do
  case $option in
    h) usage; exit 0;;
    g) ND280_GIT=$OPTARG;;
    c) CMAKE_PATH=$OPTARG;;
    i) CMAKE_PATH=${ND280_ROOT}/CMAKE_3.14.0/cmake-3.14.0-Linux-x86_64/bin/cmake;
       CMAKE_TAR=true;;
    *) usage; exit 1;;
  esac
done
shift "$((OPTIND-1))"

######################################################################

# Find the base directory and other "setables" for this installation,
# and set it in the login scripts.  The login scripts have this
# parameterized as "@@ND280ROOT@@", &c.

for input in inputs/*.in; do
  output=`basename ${input} .in`
  echo "-- Write $output from $input"
  cat $input | sed "s^@@ND280GIT@@^${ND280_GIT}^g"  | sed "s^@@ND280PILOTROOT@@^${ND280PILOT_ROOT}^g" | sed "s^@@ND280ROOT@@^${ND280_ROOT}^g"  | sed "s^@@ND280DOWNLOADS@@^${ND280_DOWNLOADS}^g"> $output
done
echo

if [ "x${ND280_CPP_COMPILER}" != "x" ]; then
  echo -- User selected C++ compiler: $(which ${ND280_CPP_COMPILER})
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/g++ > /dev/null 2>&1
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/c++ > /dev/null 2>&1
  ln -sf $(which $ND280_CPP_COMPILER) ${ND280_ROOT}/nd280SoftwarePilot/scripts/g++
  ln -sf $(which $ND280_CPP_COMPILER) ${ND280_ROOT}/nd280SoftwarePilot/scripts/c++
else
  # Set the default c++ compiler for this installation. This should be
  # changed to reflect the preferred compilers.
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/g++ > /dev/null 2>&1
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/c++ > /dev/null 2>&1
  for vers in g++-4.9 g++49 g++-4.8 g++48 g++ c++; do
	  if which $vers > /dev/null 2>&1; then
	    echo -- Choosing default C++ compiler: $(which $vers)
	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/g++
	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/c++
	    break;
	  fi
  done
fi
echo

if [ "x${ND280_CC_COMPILER}" != "x" ]; then
  echo -- User selected CC compiler: $(which ${ND280_CC_COMPILER})
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/gcc > /dev/null 2>&1
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/cc > /dev/null 2>&1
  ln -sf $(which $ND280_CC_COMPILER) ${ND280_ROOT}/nd280SoftwarePilot/scripts/gcc
  ln -sf $(which $ND280_CC_COMPILER) ${ND280_ROOT}/nd280SoftwarePilot/scripts/cc
else
  # Set the default C compiler for this installation. This should be
  # changed to reflect the preferred compilers.
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/gcc > /dev/null 2>&1
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/cc > /dev/null 2>&1
  for vers in gcc-4.9 gcc49 gcc-4.8 gcc48 gcc cc; do
	  if which $vers > /dev/null 2>&1; then
	    echo -- Choosing default CC compiler: $(which $vers)
	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/gcc
	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/cc
	    break;
	  fi
  done
fi
echo

if [ "x${ND280_FORTRAN_COMPILER}" != "x" ]; then
  echo -- User selected Fortran compiler: $(which ${ND280_FORTRAN_COMPILER})
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/gfortran > /dev/null 2>&1
  ln -sf $(which $ND280_FORTRAN_COMPILER) ${ND280_ROOT}/nd280SoftwarePilot/scripts/gfortran
else
  # Set the default fortran compiler for this installation. This should be
  # changed to reflect the preferred compilers.
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/gfortran > /dev/null 2>&1
  for vers in gfortran-4.9 gfortran49 gfortran-4.8 gfortran48 gfortran; do
	  if which $vers > /dev/null 2>&1; then
	    echo -- Choosing default Fortran compiler: $(which $vers)
	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/gfortran
	    break;
	  fi
  done
fi
echo

if [ "x${ND280_MAKE_COMMAND}" != "x" ]; then
  echo -- User selected make version: $(which ${ND280_MAKE_COMMAND})
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/make > /dev/null 2>&1
  ln -sf $(which $ND280_MAKE_COMMAND) ${ND280_ROOT}/nd280SoftwarePilot/scripts/make
else
  # Set the default make command for this installation. This should be
  # changed to reflect the preferred versions.
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/make > /dev/null 2>&1
  for vers in make; do
      if which $vers > /dev/null 2>&1; then
	  echo -- Choosing default make command: $(which $vers)
	  ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/make
	  # Add a gmake link (for any really out of date software).
	  ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/gmake
	  break;
      fi
  done
fi
echo

if [ "x${CMAKE_PATH}" != "x" ]; then
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/cmake > /dev/null 2>&1
  if [ ${CMAKE_TAR} ]; then
    echo "-- Using pre-packaged CMake 3.14.0"
    ln -sf $CMAKE_PATH ${ND280_ROOT}/nd280SoftwarePilot/scripts/cmake
  else
    echo -- User selected CMake: $(which $CMAKE_PATH)
    ln -sf $(which $CMAKE_PATH) ${ND280_ROOT}/nd280SoftwarePilot/scripts/cmake
  fi    
else
  # Set the defauls CMake command for the installation. This should be 
  # changed to reflect the preferred command
  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/cmake > /dev/null 2>&1
  for commands in cmake3 cmake; do
    if which $commands > /dev/null 2>&1; then
      echo -- Choosing default CMake: $(which $commands)
      ln -sf $(which $commands) ${ND280_ROOT}/nd280SoftwarePilot/scripts/cmake
      break;
    fi
  done
fi
echo

#if [ "x${PYTHON_PATH}" != "x" ]; then
#  echo -- User selected python version: $(which ${PYTHON_PATH})
#  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/python > /dev/null 2>&1
#  ln -sf $(which $PYTHON_PATH) ${ND280_ROOT}/nd280SoftwarePilot/scripts/python
#else
#  # Set the default C compiler for this installation. This should be
#  # changed to reflect the preferred compilers.
#  rm -f ${ND280_ROOT}/nd280SoftwarePilot/scripts/python > /dev/null 2>&1
#  for vers in python2.7 python; do
#	  if which $vers > /dev/null 2>&1; then
#	    echo -- Choosing python2 version: $(which $vers)
#	    ln -sf $(which $vers) ${ND280_ROOT}/nd280SoftwarePilot/scripts/python
#	    break;
#	  fi
#  done
#fi

cat <<EOF
Setup file named
  ${ND280_ROOT}/nd280SoftwarePilot/nd280SoftwarePilot.profile
has been created.  You can source these files directly, or add the
following alias to the login scripts to simplify ND280 setup:
  alias nd280-setup=". ${ND280_ROOT}/nd280SoftwarePilot/nd280SoftwarePilot.profile"
This script makes sure the nd280-setup command is defined, and the
environment will then be setup by running "nd280-setup". 

To install the software, source the relevant setup file and run
  nd280-install 'version'
where 'version' is the desired ND280 Software version.

Useful options can be used when running the install command. Execute
  nd280-install -h
for more information.

EOF
