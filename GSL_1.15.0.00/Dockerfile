FROM git.t2k.org:8088/nd280/framework/nd280softwarepolicy:v3.0 as intermediate_GSL

ENV GSL_VERSION 1.15.0.00
ENV GSL_PATH /usr/local/t2k/current/GSL_${GSL_VERSION}

##################################################

FROM intermediate_GSL as built_GSL

COPY bin $GSL_PATH/bin
COPY build $GSL_PATH/build
COPY cmake $GSL_PATH/cmake
COPY tar $GSL_PATH/tar

RUN mkdir $GSL_PATH/$LINUX_INSTALL_FOLDER

WORKDIR $GSL_PATH/build
ENV ND280_NJOBS 3

# GSL
RUN source $COMMON_BUILD_PREFIX/setup.sh &&\
    cmake ../cmake &&\
    make -j${ND280_NJOBS} &&\
    cd .. &&\
    rm -rf \
        build \
        src 
##################################################

FROM intermediate_GSL

COPY --from=built_GSL \
        $GSL_PATH \
        $GSL_PATH/
