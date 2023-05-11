#!/bin/sh
#
if [[ ! -z "${COMPUTE_GUEST_SETUP}" ]] ; then return 0 2>/dev/null || exit 0 ; fi
#
#set -x
# if ND280_DO_NOT_CHOOSE_COMPILER is set to a non zero length string, do nothing
if [[ ! -z "${ND280_DO_NOT_CHOOSE_COMPILER}" ]]; then
 return
fi
if [ ! -x ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG} ]; then
	mkdir ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}
fi

if [ "x${ND280_CPP_COMPILER}" != "x" ]; then
	echo User selected C++ compiler: $(which ${ND280_CPP_COMPILER})
	if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++ ]; then
		rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++
	fi
	ln -sf $(which $ND280_CPP_COMPILER) \
	${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++
else
	# Set the default c++ compiler for this installation.  This should be
	# changed to reflect the preferred compilers.
	for vers in bogus g++-4.9 g++-4.8 g++-5 g++-4.7 g++; do
		if which ${vers} >> /dev/null  2>&1; then
	    if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++ ]; then
	    	rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++
	    fi
	    ln -sf $(which ${vers}) \
	    ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++
	    echo Choosing default C++ compiler: $(readlink -f ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++)
	    break;
	  fi
	done
fi

if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/c++ ]; then
    rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/c++
fi
ln -sf ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/g++ \
   ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/c++

if [ "x${ND280_CC_COMPILER}" != "x" ]; then
	echo User selected C compiler: $(which ${ND280_CC_COMPILER})
	if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc ]; then
	    	rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc
	fi
	ln -sf $(which $ND280_CC_COMPILER) \
	${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc
else
	# Set the default cc compiler for this installation.  This should be
	# changed to reflect the preferred compilers.
	for vers in gcc-4.9 gcc-4.8 gcc-5 gcc-4.7 gcc; do
		if which ${vers}  >> /dev/null  2>&1; then
	    if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc ]; then
	    	rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc
	    fi
	    ln -sf $(which ${vers}) \
	    ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc
	    echo Choosing default C compiler: $(readlink -f ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc)
	    break;
	  fi
	done
fi

if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/cc ]; then
    rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/cc
fi
ln -sf ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gcc \
   ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/cc

if [ "x${ND280_FORTRAN_COMPILER}" != "x" ]; then
	echo User selected fortran compiler: $(which ${ND280_FORTRAN_COMPILER})
	if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran ]; then
		rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran	    	
	fi
	ln -sf $(which $ND280_FORTRAN_COMPILER) \
	${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran
else
	# Set the default fortran compiler for this installation.  This should be
	# changed to reflect the preferred compilers.
	for vers in gfortran-4.9 gfortran-4.8 gfortran-5 gfortran-4.7 gfortran; do
		if which ${vers}  >> /dev/null  2>&1; then
	    if [ -L ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran ]; then
	    	rm ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran	    	
	    fi
	    ln -sf $(which ${vers}) \
	    ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran
	    echo Choosing default fortran compiler: $(readlink -f ${ND280SOFTWAREPOLICYROOT}/${ND280SOFTWAREPOLICYCONFIG}/gfortran)
	    
	    break;
	  fi
	done
fi
