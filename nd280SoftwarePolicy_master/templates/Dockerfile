# DOCKERFILE for cosmicTriggerGeant4Sim generated from Dockerfile.Template
#
ARG  ND280SOFTWAREMASTER_IMAGE_VERSION
FROM git.t2k.org:8088/nd280/framework/nd280softwaremaster:${ND280SOFTWAREMASTER_IMAGE_VERSION} AS precursor

ENV BUILD_PATH $COMMON_BUILD_PREFIX/build

########################################

FROM precursor as intermediate

ARG GIT_T2K_USERNAME
ARG GIT_T2K_TOKEN

COPY . ${BUILD_PATH}

RUN source $COMMON_BUILD_PREFIX/setup.sh 

RUN mkdir ${BUILD_PATH}/${LINUX_INSTALL_FOLDER} || true
WORKDIR ${BUILD_PATH}/${LINUX_INSTALL_FOLDER}
ENV ND280_NJOBS 3

########################################

FROM intermediate

RUN source $COMMON_BUILD_PREFIX/setup.sh &&\
    cmake ../cmake &&\
    . ../bin/setup.sh &&\
    make &&\
    make test
       

