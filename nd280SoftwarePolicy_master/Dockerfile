ARG SOFTPILOT_IMAGE_VERSION
FROM git.t2k.org:8088/nd280/pilot/nd280softwarepilot:${SOFTPILOT_IMAGE_VERSION}


# Defining default version (for master and Merge Requests); no need to update too often
ARG VERSION_ARG=v3.1.2
ENV POLICY_VERSION=${VERSION_ARG}
ENV POLICY_PATH /usr/local/t2k/current/nd280SoftwarePolicy_${POLICY_VERSION}
ENV LINUX_INSTALL_FOLDER Linux-CentOS_7-gcc_4.8-x86_64

COPY . ${POLICY_PATH}
