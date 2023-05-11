<!--View this file in the GitLab GUI for better readability-->
# nd280SoftwarePilot

This repository has the capability of creating scripts to source the required variables to install and run the ND280 Software, and contains all the tools necessary to recursively clone all the software packages from GitLab and build them with CMake. The top level scripts are written in bash with the lower level scripts in Python to allow more functionality with the GitLab interface. 

## Contents

<!-- - [nd280SoftwarePilot](#nd280softwarepilot) -->
<!-- - [Contents](#contents) -->
- [Dependencies](#dependencies)
- [Setting Up Credentials for Remote Connections](#setting-up-credentials-for-remote-connections)
  - [Cloning Over HTTPS](#cloning-over-https)
  - [Cloning Over SSH](#cloning-over-ssh)
- [Quick Start](#quick-start)
- [MacOS Users](#macos-users)
- [Sourcing the Profile Scripts](#sourcing-the-profile-scripts)
- [Configuring CMake](#configuring-cmake)
- [Installing the ND280 Software](#installing-the-nd280-software)
- [Switching to a Different Software Version](#switching-to-a-different-software-version)
- [Building a Single Software Package and its Dependencies](#building-a-single-software-package-and-its-dependencies)
- [Docker Environment](#docker-environment)
- [Developing nd280SoftwarePilot](#developing-nd280softwarepilot)

## Dependencies

The are several required packages/libraries to install and run the ND280 Software. Most are included as standard with Linux, but the proceeding list gives examples of packages that may need updating to a newer/different version:
- CMake 3.12.2 or newer (optional; see ["Configuring CMake"](#configuring-cmake) section)
- gcc-4.x where x>=8. Older gcc will fail because they are not c++11 complete. gcc-5 and above fail for other reasons. gcc-9 or above may cause problems installing NEUT
- git 1.8 or newer
- python 2.7 below python 2.7.15 . We are in the process of moving to python 3. Version 3.6 or higher is recommended.

Here is a list of the commands to install all the (known) required dependencies using **yum (CentOS)**: 
```
sudo yum group install -y "Development Tools"
sudo yum install -y epel-release
sudo yum install -y cmake3 python-devel python3-devel wget ncurses-devel libX11-devel libxml2-devel \
 libXpm-devel libXft-devel libXext-devel libcurl-devel mesa-dri-drivers ed imake \
 krb5-devel tcsh krb5-devel openssl-devel graphviz-devel libXt-devel motif-devel \
 freetype-devel gmp-devel gsl-devel glut-devel which man-db lz4-devel libAfterImage-devel \
 glew-devel cfitsio-devel ftgl-devel davix-devel gl2ps-devel
```
**dnf (fedora):**
```
sudo dnf group install -y "Development Tools"
sudo dnf install -y cmake3 python-devel python3-devel wget ncurses-devel libX11-devel libxml2-devel \
 libXpm-devel libXft-devel libXext-devel libcurl-devel mesa-dri-drivers ed imake krb5-devel \
 tcsh krb5-devel openssl-devel graphviz-devel libXt-devel motif-devel freetype-devel \
 gmp-devel gsl-devel glut-devel which man-db lz4-devel libAfterImage-devel glew-devel \
 cfitsio-devel ftgl-devel davix-devel gl2ps-devel
```
or **apt (Ubuntu):**
```
sudo apt-get install -y build-essential python-dev python3-dev wget libncurses5-dev libncursesw5-dev \
 git make gcc doxygen libx11-dev libxpm-dev libxml2-dev libncurses5-dev libncursesw5-dev \
 libx11-dev libxpm-dev libxft-dev libxext-dev libglu1-mesa-dev libkrb5-dev libssl-dev \
 libpcre3-dev libglu1-mesa-dev libglew-dev libftgl-dev libfftw3-dev csh tcsh cmake \
 liblzma-dev xutils-dev gfortran libgsl-dev davix-dev libgl2ps-dev libxt-dev libmotif-dev 
```
NB: lz4-devel, libAfterImage-devel, glew-devel, cfitsio-devel, ftgl-devel, davix-devel and gl2ps-devel (and their equivalents on Ubuntu) are only required when using Root 6.

**Mac users** cannot install an official release of the software as yet. If you must install on a mac now, you can try the development build of the mac installation by cloning the latest version of the ND280 Software, then checking out the master branches for the nd280SoftwarePilot and nd280SoftwarePolicy packages. On a MacBook 2013, the following packages had to be installed with **homebrew** before installation of ND280:
```
brew install cmake pkg-config vips gsl coreutils
```
but this may not be an exhaustive list. Please email w.shorrock17@imperial.ac.uk, or create a new issue for the project, if you find any further dependencies.

Mac users also have to place the path to the new gnu tools into the PATH variable:
```
export PATH="/usr/local/opt/coreutils/libexec/gnubin:$PATH"
```

## Setting Up Credentials for Remote Connections

Before you can start cloning ("cloning" is the action of copying something on GitLab to your machine) the software packages, you will need to set up some credentials that allow your machine to establish a connection with GitLab.

First, you must decide whether you want to clone through an ssh connection or an https connection. We recommend using an https connection, as ssh connections can be blocked by firewalls and proxies, but we will go through how to use both here.

### Cloning Over HTTPS

You will need to create a **Personal Access Token** to avoid having to input your username and password everytime you clone a package. Instructions to do so are here: https://docs.gitlab.com/ee/user/profile/personal_access_tokens.html#creating-a-personal-access-token

When asked to choose a scope, choose "api", as this will give you push and pull rights.

Now you will be able to clone packages with the command<br/>
```
git clone https://oauth2:<MYTOKEN>@git.t2k.org/<PATH_TO_PACKAGE>
```
where "\<MYTOKEN\>" is the Personal Access Token code.

### Cloning Over SSH

An **ssh-key pair** is needed to establish an ssh connection with GitLab. You will need to generate a keypair (if you don't have one) and add the public key to your GitLab account. You can do this be following the instructions here: https://docs.gitlab.com/ee/ssh/

Follow the instructions for an ED25519 ssh-key.

Once this is done, packages can be cloned with<br/>
```
git clone git@git.t2k.org:<PATH_TO_PACKAGE>
```

## Quick Start

Here are the basic commands and the order to use them in to install all the ND280 Software packages. If you have all the required dependencies and have gone through the section ["Setting up credentials for remote connections"](#setting-up-credentials-for-remote-connections), this should work with no issue, but we recommend reading the other sections to understand all the options available.<br/>
```
cd folder/to/install/software
git clone https://oauth2:<MYTOKEN>@git.t2k.org/nd280/pilot/nd280SoftwarePilot.git  
cd nd280SoftwarePilot
./configure.sh
. nd280SoftwarePilot.profile
nd280-install -jN <version>  ## N=number of parallel jobs; <version>=the software version to install
```

If you want to use an ssh connection instead of https to clone packages, replace the second command with:<br/>
```
git clone git@git.t2k.org:nd280/pilot/nd280SoftwarePilot.git
```

## MacOS Users

The ND280 Software is mainly used on Linux systems, but with a few tweaks it has been made compatible with MacOS systems. For installation on MacOS, no special set up is required other than those listed in the ["Dependencies"](#dependencies) section. Otherwise, the standard installation instructions can be followed.

## Sourcing the Profile Scripts

Running `./configure.sh` will produce a .profile script that, when sourced, will add the directory containing the pilot repository's executable scripts to your PATH variable. Other variables, such as ND280_ROOT, will also be set. This script should always be sourced before installing or using the ND280 Software. It is recommended to add an alias into your .bashrc file to source this file with a simple command.

## Configuring CMake

There are three different ways to configure/install CMake. These options are described below.

### 1. Use the native version of CMake on your machine.
If this is too old (the minimum required version is 3.12.4), update it (see ["Dependencies"](#dependencies) section), but you will need superuser permissions. To use the native CMake, you do not need to specify any special options during the install. You can check your cmake version with:
```
cmake --version
```
or perhaps
```
cmake3 --version
```

### 2. Download a binary
If you cannot update your native CMake (maybe you don't have superuser permissions), you can instead get a CMake binary that you can just download from the internet and unpack, no install required. They are available on the [CMake website](https://cmake.org/download/). There are different binaries for different OSs, so be sure to get the right one. Once you have unpacked the binary, you need to specify the path to the "cmake" or "cmake3" command in the unpacked directory when executing `configure.sh` with the option **-c**. e.g. `./configure -c /path/to/binary/bin/cmake`.
Eg:
```
cd ~/opt
wget https://github.com/Kitware/CMake/releases/download/v3.12.4/cmake-3.12.4-Linux-x86_64.tar.gz
tar xf cmake-3.12.4-Linux-x86_64.tar.gz
cd ~/nd280Software
git clone git@git.t2k.org:nd280/pilot/nd280SoftwarePilot.git
cd nd280SoftwarePilot
./configure.sh -c  ~/opt/cmake-3.12.4-Linux-x86_64/bin/cmake
. nd280SoftwarePilot.profile
nd280-install 13.1
```
### 3. From git.t2k.org
For those that do not want to install CMake themselves, there is an option to use a pre-packaged version of CMake for Linux x86_64 platforms from the GitLab repository. You will have to specify to use this CMake version by using the **-i** option with `configure.sh`. Then, when executing `nd280-install`, you will need to use the **-i** option to download the CMAKE repository from GitLab and unpack the binary.
Eg.
```
git clone git@git.t2k.org:nd280/pilot/nd280SoftwarePilot.git
cd nd280SoftwarePilot
./configure.sh -i
. nd280SoftwarePilot.profile
nd280-install -i 13.1
```

## Installing the ND280 Software

To install the software, first, clone this repository (through an https or ssh connection) to the directory on your machine where you want to install the software. Then, run the `configure.sh` script within the main nd280SoftwarePilot directory. There is an option (-g) to change the address of the git repository where the software packages are cloned (only change this if you want to change between ssh and https connections). You can also use an option (**-c**) to set the path to a user-installed binary version of CMake, which will be helpful to users that do not have permissions to install a source version of CMake on their machine, but the current version is too old (the minimum required version is 3.9.6). If you don't want the hassle of installing CMake, there is a pre-packaged version included with the software, which you can specify to use with option **-i**. Run `./configure -h` for more information on how to set these options.

The next step is to source the `nd280SoftwarePilot.profile` script created after running configure.sh. This will set variables like `ND280_ROOT` (the directory where the software will be installed) and ammend the `PATH` variable so the commands needed to install the software can be found.

Finally, run the `nd280-install` command and specify the software version you want to install, in the format \<major\>.\<minor\>. If you want to retrieve the master branch of the software, which you can develop and push back to the repository, write "master" instead of the software version (in this case it may also be useful to use the option **-c** to skip the compile step to avoid non-source files being created). There is also an option (**-j**) that allow you to specify the number of parallel jobs that can be run, which will help speed up the process. With 9 parallel jobs set, the total install should take around two hours. Execute `nd280-install -h` for details on more options. 

`nd280-install` checks for clones of each package in your `ND280_ROOT` directory before cloning them. If the requested version is already cloned it will skip the clone command for that package, so there's no need to delete cloned packages on your machine if you need to restart the install for some reason. The exception to this is if there was an error while cloning a package, in which case a message should appear recommending you delete that package and retry the install.

## Switching to a Different Software Version

It is recommended to install new software versions in separate directories to old versions. If `nd280-install <version>` is run in the same directory as another version of nd280, the packages for the new version will be cloned into that directory along with the old packages, which may be confusing when it comes to editing files. Building and using the software will be just the same, though.

If `nd280-install <version>` is executed and attempts to clone packages that already exist in that directory, the cloning of those packages will be skipped, so software cloning can be stopped and restarted without having to delete or re-clone packages.

## Building a Single Software Package and its Dependencies

It is possible to only install a single nd280 software package and its dependencies. Follow the steps laid out in ["Quick Start"](#quick-start) but for the last command include the option **-c** so that the packages are only cloned and not installed. Then, cd to the build directory of the package you want to install and execute:
```
cmake ../cmake
../bin/makeAll.sh ## build the software
. ../bin/setup.sh ## setup the environment for running the software
```

This will only work if you have sourced nd280SoftwarePilot.profile, which you should have done to download the packages.

Of course, if a package has no dependencies, you can avoid downloading all the packages and just clone the single package using the `git clone` command (you will also need to clone nd280SoftwarePilot to set up your environment). Then, run the above commands in the build directory of the package to be installed after executing `./configure` and `. nd280SoftwarePiot.sh` in nd280SoftwarePilot. Note that the package to be installed must be in the same directory as nd280SoftwarePilot.

## Docker Environment

You can produce a docker image that contains all the software stack installation.
To do so, make sure you have docker installed, then clone nd280SoftwarePilot using https and an access token and then run 

```bash
docker build -t nd280 .
```
from the top directory of nd280SoftwarePilot.

Upon completion, you can then generate and enter a container with the software installed and play with it by using:

```bash
docker run --rm -it nd280 
```

Remember, you can source the environment for the whole software by sourcing nd280SoftwareMaster_<version>/bin/setup.sh or you can just source the environment variables for the package you're interested in, and its dependencies, by sourcing <your_package>_<version>/bin/setup.sh.

## Developing nd280SoftwarePilot

The nd280SoftwarePilot package is used for installing the entire nd280 software. It should be the only package users have to download manually. As such, we have tried to make it as simple as possible for users to acquire, so we have refrained from using a workflow for this package that results in multiple versions. Instead, we have a single branch called "stable" in which a stable version of the code is kept. The master branch is used for development, and whenever the master branch is in a state that it can be used for a release of the package, then the master branch should be merged in to the stable branch.

Using this development model, users just have to clone the stable branch of the pilot package and they should always get a working version of the package. The stable branch has been made the default branch to make this process even easier, as this means the stable branch is automatically checked out when the package is cloned. Just be sure to remember this when making merge requests, as the branch to be merged in to will automatically be set to "stable", but can be changed to "master". Both the stable branch and the master branch are protected and cannot be pushed to directly, so merge requests are required to alter the code there. Hence, it is best to develop code on feature branches, use merge requests to add the feature to the master branch, then, when you are sure the code works on the master branch, use another merge request to merge the master into the stable branch.

---

For a more complete explanation of how the CMake build works, see the [ND280 workbook](http://nd280.lancs.ac.uk/devel/invariant/nd280Doc/workbook/SoftwareUserCMAKEandGIT.html).
