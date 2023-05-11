FROM git.t2k.org:8088/nd280/framework/nd280softwarepolicy:v3.0 as intermediate_MYSQL

ENV MYSQL_VERSION 5.6.20.01
ENV MYSQL_PATH /usr/local/t2k/current/MYSQL_${MYSQL_VERSION}

##################################################

FROM intermediate_MYSQL as built_MYSQL

COPY bin $MYSQL_PATH/bin
COPY build $MYSQL_PATH/build
COPY cmake $MYSQL_PATH/cmake
COPY tar $MYSQL_PATH/tar

RUN mkdir $MYSQL_PATH/$LINUX_INSTALL_FOLDER

WORKDIR $MYSQL_PATH/build
ENV ND280_NJOBS 3

# MYSQL
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

FROM intermediate_MYSQL

COPY --from=built_MYSQL \
        $MYSQL_PATH \
        $MYSQL_PATH/
