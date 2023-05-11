FROM git.t2k.org:8088/nd280/framework/nd280softwarepolicy:v3.0 as intermediate_ROOT

ENV ROOT_VERSION 5.34.34.00
ENV ROOT_PATH /usr/local/t2k/current/ROOT_${ROOT_VERSION}

COPY --from=git.t2k.org:8088/nd280/externals/mysql:5.6.20.01 /usr/local/t2k/current/MYSQL_5.6.20.01 /usr/local/t2k/current/MYSQL_5.6.20.01
COPY --from=git.t2k.org:8088/nd280/externals/gsl:1.15.0.00 /usr/local/t2k/current/GSL_1.15.0.00 /usr/local/t2k/current/GSL_1.15.0.00

##################################################

FROM intermediate_ROOT as built_ROOT

COPY build $ROOT_PATH/build
COPY cmake $ROOT_PATH/cmake
COPY setup_script $ROOT_PATH/setup_script
COPY tar $ROOT_PATH/tar

RUN mkdir $ROOT_PATH/$LINUX_INSTALL_FOLDER

WORKDIR $ROOT_PATH/build
ENV ND280_NJOBS 3

# ROOT
RUN source $COMMON_BUILD_PREFIX/setup.sh &&\
    cmake ../cmake &&\
    make -j${ND280_NJOBS} &&\
    cd .. &&\
    rm -rf \
        build \
        tmp_build \
        src \
        tar 

##################################################

FROM intermediate_ROOT

COPY --from=built_ROOT \
        $ROOT_PATH \
        $ROOT_PATH/
