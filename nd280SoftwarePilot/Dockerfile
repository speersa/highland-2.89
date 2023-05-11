ARG DOCKERBASE_VERSION
ARG DOCKERBASE_FLAVOR
FROM git.t2k.org:8088/nd280/docker/base:${DOCKERBASE_FLAVOR}-${DOCKERBASE_VERSION}

COPY . $COMMON_BUILD_PREFIX/nd280SoftwarePilot

ENV ND280_PILOT $COMMON_BUILD_PREFIX/nd280SoftwarePilot

RUN . $COMMON_BUILD_PREFIX/setup.sh &&\
    cd $ND280_PILOT &&\
    ./configure.sh

RUN echo "# Extra files for from the nd280SoftwarePilot" >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo "export ND280_PILOT=$ND280_PILOT" >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo ". ${ND280_PILOT}/nd280SoftwarePilot.profile"  >> $COMMON_BUILD_PREFIX/setup.sh

# Allow testing upon entry
WORKDIR $ND280_PILOT
