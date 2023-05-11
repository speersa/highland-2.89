ARG SOFTPILOT_IMAGE_VERSION
FROM git.t2k.org:8088/nd280/pilot/nd280softwarepilot:${SOFTPILOT_IMAGE_VERSION} as pre_master

ARG VERSION_ARG=1.75
ENV EXTERNALSMASTER_VERSION=${VERSION_ARG}
ENV ND280_VER $EXTERNALSMASTER_VERSION
ENV EXTERNALSMASTER_PATH /usr/local/t2k/current/externalsMaster_${EXTERNALSMASTER_VERSION}

FROM pre_master as installed_master

ARG GIT_T2K_USERNAME
ARG GIT_T2K_TOKEN

COPY build $EXTERNALSMASTER_PATH/build
COPY cmake $EXTERNALSMASTER_PATH/cmake

ENV ND280_NJOBS 5

RUN source $COMMON_BUILD_PREFIX/setup.sh &&\
    ND280_GIT="https://${GIT_T2K_USERNAME}:${GIT_T2K_TOKEN}@git.t2k.org/nd280/" &&\
    nd280-find-dependencies externals externalsMaster ${EXTERNALSMASTER_VERSION} &&\
    ls -altrh $COMMON_BUILD_PREFIX

RUN mkdir $EXTERNALSMASTER_PATH/$LINUX_INSTALL_FOLDER

WORKDIR $EXTERNALSMASTER_PATH/$LINUX_INSTALL_FOLDER

# EXTERNALMASTER
RUN source $COMMON_BUILD_PREFIX/setup.sh &&\
    cmake -D ND280_DEBUG_MODE=DEBUG ../cmake &&\
    ./../bin/makeAll.sh &&\
    # ls -r \
    #     -I "*Policy.sh" \
    #     -I "*All.sh" \
    #     -I "setup.sh" \
    #     ../bin | xargs -I NAME -P 1 /bin/bash -c "ND280_NJOBS=3 /bin/bash ../bin/NAME $1" &&\
    cd ${COMMON_BUILD_PREFIX} &&\
    rm -rf CERNLIB_*/$LINUX_INSTALL_FOLDER/src/200*/build &&\
    rm -rf GSL_*/src &&\
    rm -rf ROOT_*/$LINUX_INSTALL_FOLDER/tmp_build ROOT_*/.git ROOT_*/src &&\
    rm -rf Geant4_*/downloads Geant4_*/tar Geant4_*/geant4_source Geant4_*/$LINUX_INSTALL_FOLDER/src &&\  
    rm -rf MYSQL_*/src MYSQL_*/$LINUX_INSTALL_FOLDER/tmp_build &&\
    # rm -rf NEUT_*/.git NEUT_*/${LINUX_INSTALL_FOLDER}/src/neut_*/src &&\ if we remove this folder, some files will be missing later on (like necardev.h); need to move needed files elsewhere...
    rm -rf CLHEP_*/tmp_build CLHEP_*/downloads CLHEP_*/src 

RUN du -d1 -h $COMMON_BUILD_PREFIX

FROM pre_master

COPY --from=installed_master ${COMMON_BUILD_PREFIX} ${COMMON_BUILD_PREFIX}

