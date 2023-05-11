> <!--View this file in the GitLab GUI for better readability-->
# highland2SoftwarePilot
This repository extends _nd280SoftwarePilot_ scripts to source the required variables, to install and run the _highland2Software_, and contains all the tools necessary to recursively clone all the _highland_ related packages from GitLab and build them with CMake. For the general information on the ND280 git/CMake usage see [_highland2SoftwarePilot_ documentation](https://git.t2k.org/nd280/pilot/nd280SoftwarePilot#nd280softwarepilot).

## Contents
- [Dependencies](#dependencies)
- [highland2Software Projects Organisation](#highland2software-projects-organisation)
- [Sourcing the Profile Script](#sourcing-the-profile-script)
- [Installing the HighLAND2 Software](#installing-the-highland2-software)
- [Installing Only the PSYCHE Software](#installing-only-the-psyche-software)
- [Switching to a Different Software Version](#switching-to-a-different-software-version)
- [Using ROOT Installation Outside ND280 Software Suite](#using-root-installation-outside-nd280-software-suite)
- [Additional information](#additional-information)


## Dependencies
In order to use _highland2SoftwarePilot_ scripts one has to clone _nd280SoftwarePilot_ project. Additional dependency is _nd280SoftwarePolicy_ which takes care of CMake business and if not present will be installed with _highland2SoftwarePilot_ scripts.  

## highland2Software Projects Organisation
All _HighLAND2_ projects live inside _nd280/highland2Software_ subgroup. E.g. a _highland2_ main package can be found inside _nd280/highland2Software/highland2_ subgroup. Inside _nd280/highland2Software_ one can find:
* _psycheMaster_: an umbrella project that provides versions of _psyche_ projects (as cvs/CMT _nd280Psyche_)
* _highland2Master_: an umbrella project that provides versions of _psyche_ (via _psycheMaster_) and _highland2_ main projects (as cvs/CMT _nd280Highland2_)
* _highland2_: a subgroup where _highland2_ main projects are located
* _psyche_: a subgroup where _psyche_ projects are located
* _highland2UserAnalyses_: a subgroup where projects not included into _highland2_ are located; a user should store their analysis project inside this subgroup
* _highland2ControlSamples_: a subgroup to store projects used to select different control samples later utilised e.g. in systematics and corrections evaluation
* _highland2Systematics_: a subgroup to store projects used to evaluate various systematics
* _highlandDoc, highlandND280Doc_: documentation packages

To get which versions of the projects can be used one should refer to [HighLAND2 Software Release History](https://git.t2k.org/nd280/highland2Software/highlandDoc/-/wikis/HighLAND2-Software-Release-History).

## Sourcing the Profile Script
Sourcing `highland2SoftwarePilot.profile` script will add the directory containing the pilot repository's executable scripts to your PATH variable. This script should always be sourced before installing or using the _HighLAND2_ software. It is recommended to add an alias into your .bashrc (.bash_profile) file to source this file with a simple command. There is something to note here: sourcing `highland2SoftwarePilot.profile` script sets `CMAKE_PREFIX_PATH` variable that is later used by ND280 CMake routines and by default this is the same as `ND280_ROOT`. The variable is not changed if is already set, hence it may be required to unset `CMAKE_PREFIX_PATH` prior to running the script if the current `CMAKE_PREFIX_PATH` variable is set and points outside the _ND280/HighLAND2_ software suite location.

## Installing the HighLAND2 Software
To install the software, first, clone _nd280SoftwarePilot_ repository (through an https or ssh connection) to the directory on your machine where you want to install the software. Then clone this repository _highland2SoftwarePilot_. Follow _nd280SoftwarePilot_ setup isnstructions to run `./configure` and source `nd280SoftwarePilot.profile`, this will set variables like ND280_ROOT (the directory where the software will be installed) and ammend the PATH variable so the commands needed to install the software can be found. Source `highland2SoftwarePilot.profile` to ammend the PATH variable to find commands needed to install the _highland2_ software. 

Finally, run the `highland-install` command and specify the software version you want to install, in the format `<major>.<minor>[.<patch>]` If you want to retrieve the master branch of the software, which you can develop and push back to the repository, write "master" instead of the software version (in this case it may also be useful to use the option `-c` to skip the compile step to avoid non-source files being created).  There is also an option `-j` that allow you to specify the number of parallel jobs that can be run, which will help speed up the process. Execute `highland-install -h` for details on more options. Some useful options are:
* `-d` : Install only psyche, psyche version should be provided in this case 
* `-r` : Install a ROOT version from nd280Software. ROOT5 at the moment. Will install ROOT and its dependencies (MYSQL and GSL)
* `-p` : Set the production version to oaAnalysisReader: e.g. `-p prod6T` (default option as for November 2020)

`highland-install` checks for clones of each package in your ND280_ROOT directory before cloning them. If the requested version is already cloned it will skip the clone command for that package, so there's no need to delete cloned packages on your machine if you need to restart the install for some reason. The exception to this is if there was an error while cloning a package, in which case a message should appear recommending you delete that package and retry the install.

It is expected that a user will often want to built only a particular analysis package and its dependencies. In this case one can use `-c` option of `highland-install` so to only clone (and not build) the software. Then the following instructions should be followed: [Building a Single Software Package and its Dependencies](https://git.t2k.org/nd280/pilot/nd280SoftwarePilot#building-a-single-software-package-and-its-dependencies). Note! when referring to the build directory, it assumes the one created with 
> mkdir \`nd280-system\`.

## Installing Only the PSYCHE software
In oder to get and build only _psyche_ projects one can run `psyche-install <major>.<minor>[.<patch>] (master)` script, which is equivalent to running `highland-install -d <major>.<minor>[.<patch>] (master)`.  

## Switching to a Different Software Version
This basicaly follows recommendations from _nd280SoftwarePolicy_. It is recommended to install new software versions in separate directories to old versions. If `highland-install` <version> is run in the same directory as another version of nthe software, the packages for the new version will be cloned into that directory along with the old packages, which may be confusing when it comes to editing files. Building and using the software will be just the same, though.
If `highland-install` <version> is executed and attempts to clone packages that already exist in that directory, the cloning of those packages will be skipped, so software cloning can be stopped and restarted without having to delete or re-clone packages.

## Using ROOT Installation Outside ND280 Software Suite
Similar to CVS/CMT era there is a possibility to use local ROOT installation, i.e. the one outside ND280 software suite. This is done with _psycheROOT_ package which provides all the necessary settings for CMake to build _highland2_ software packages with ROOT dependencies. _psycheROOT_ checks internally whether `$ROOTSYS` environment variable is set, so one bascially has to run `thisroot.sh` setup script before building the software with _psycheROOT_ dependency. In oder to switch between ROOT (ND280 software veresion of ROOT) and _psycheROOT_ one has to run `highland_set_use_psycheROOT -r/--root {ROOT, psycheROOT}` script that will do all the necessary changes to _highland2_ packages. The script has to be run before building the software. E.g. running `highland_set_use_psycheROOT -r psycheROOT` will do mofications to _pscycheROOT_, _psycheCore_, _oaAnalysisReader_ and _highlandUtils_.  Running `highland_set_use_psycheROOT -r ROOT` will revert the changes. Note! by default ROOT is used. Note also that for the moment (as for Nov 2020) _highland2_ software is supported only for ROOT5. 

## Additional information
For additional information please refer to [_nd280SoftwarePilot_  documentation](https://git.t2k.org/nd280/pilot/nd280SoftwarePilot#nd280softwarepilot). 




