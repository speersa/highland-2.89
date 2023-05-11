
# This script sets up a .rootmap file in the directory that includes the highlandTools library.
# The .rootmap file means that ROOT will automatically load the required libraries, so calls like
# gSystem->Load("libhighlandTools.so") are not required in analysis macros.
#
# There is a slight caveat that OSX generates a .dylib file, rather that a .so file. The rlibmap
# utility assumes a .so file, so we must make a symlink between the two.
set base=$HIGHLANDTOOLSROOT/$HIGHLANDTOOLSCONFIG
set base2=$PSYCHECOREROOT/$PSYCHECORECONFIG

if ( -d $base ) then
  set output=$base/libhighlandTools.rootmap
  set hl_lib=$base/libhighlandTools.so
  set root_libs="$base2/libpsycheCore.so libRIO.so libHistPainter.so libMatrix.so libPhysics.so libTree.so libGeom.so libEG.so" 
  set includes=$HIGHLANDTOOLSROOT/src/*_LinkDef.h

  rlibmap -f -o $output -l $hl_lib -d $root_libs -c $includes

  if ( $HIGHLANDTOOLSCONFIG =~ "Darwin*" ) then
    ln -fs $base/libhighlandTools.dylib $base/libhighlandTools.so
    ln -fs $base2/libpsycheCore.dylib $base2/libpsycheCore.so
  endif
endif
