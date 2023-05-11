#! /bin/bash

cd $ND280_ROOT
source $COMMON_BUILD_PREFIX/setup.sh
echo "-> Exporting needed variables ND280_VER, ND280_GIT and GIT_T2K_TOKEN"
export ND280_VER=master
export ND280_GIT="https://${1}:${2}@git.t2k.org/nd280/"
export GIT_T2K_TOKEN=${2}

echo "-> Test cleaning feature of fetch-package with -c "
nd280-fetch-package externals ROOT ROOT master || exit 1

# This will use the default behavior sincee job token don't have API access
echo "-> Test recursive fetching script on externalsMaster"
nd280-fetch-package master-packages externalsMaster externalsMaster master || exit 1
nd280-find-recursive-dependencies externalsMaster master || exit 1
echo "-> Check all the packages are here"
ls -altrh $COMMON_BUILD_PREFIX

echo "-> Testing to pull oaCalibTables and its dependencies"
nd280-fetch-package base oaCalibTables oaCalibTables master || exit 1
nd280-find-dependencies -r base oaCalibTables master || exit 1

