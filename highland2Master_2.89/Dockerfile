ARG HIGHLANDPILOT_IMAGE_VERSION
FROM git.t2k.org:8088/nd280/highland2software/highland2softwarepilot:${HIGHLANDPILOT_IMAGE_VERSION} as pre_master

ARG VERSION_ARG=2.81
ENV SOFTWARE_MASTER_VERSION=${VERSION_ARG}
ARG ANALYSIS_READER_VERSION=prod6T
ENV ANALYSIS_READER_VERSION=${ANALYSIS_READER_VERSION}

FROM pre_master as install_Master

ARG GIT_T2K_USERNAME
ARG GIT_T2K_TOKEN

WORKDIR ${COMMON_BUILD_PREFIX}

RUN pwd && ls && source ./setup.sh &&\
    export ND280_GIT="https://${GIT_T2K_USERNAME}:${GIT_T2K_TOKEN}@git.t2k.org/nd280/" &&\
    highland-install -j3 -r -R -p ${ANALYSIS_READER_VERSION} ${SOFTWARE_MASTER_VERSION} &&\
    true

RUN echo "# Extra files for from the highland2Master" >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo ". ${COMMON_BUILD_PREFIX}/highland2Master_${SOFTWARE_MASTER_VERSION}/bin/setup.sh"  >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo "if [[ -e ${COMMON_BUILD_PREFIX}/highlandRecPack_*/bin/setup.sh ]]; then . ${COMMON_BUILD_PREFIX}/highlandRecPack_*/bin/setup.sh; fi"  >> $COMMON_BUILD_PREFIX/setup.sh

RUN du -d1 -h $COMMON_BUILD_PREFIX
