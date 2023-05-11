ARG SOFTPILOT_IMAGE_VERSION
FROM git.t2k.org:8088/nd280/pilot/nd280softwarepilot:${SOFTPILOT_IMAGE_VERSION}

COPY . $COMMON_BUILD_PREFIX/highland2SoftwarePilot

ENV HIGHLAND2_PILOT $COMMON_BUILD_PREFIX/highland2SoftwarePilot

RUN echo "# Extra files for from the highland2SoftwarePilot" >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo "export HIGHLAND2_PILOT=$HIGHLAND2_PILOT" >> $COMMON_BUILD_PREFIX/setup.sh &&\
    echo ". ${HIGHLAND2_PILOT}/highland2SoftwarePilot.profile"  >> $COMMON_BUILD_PREFIX/setup.sh

WORKDIR $COMMON_BUILD_PREFIX
