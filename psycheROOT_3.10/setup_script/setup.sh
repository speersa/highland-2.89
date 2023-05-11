#!/bin/bash
export ROOT_VERSION_MAJOR=5
echo "executing ROOT setup.sh"
echo "ROOTROOT =  $ROOTROOT"
echo "ROOTCONFIG = $ROOTCONFIG"
if [ -f ${ROOTROOT}/${ROOTCONFIG}/bin/thisroot.sh ] ; then
. ${ROOTROOT}/${ROOTCONFIG}/bin/thisroot.sh
fi
echo "ROOTSYS set to $ROOTSYS"

