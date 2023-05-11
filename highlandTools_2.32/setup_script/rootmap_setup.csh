
# This script sets up a .rootmap file in the directory that includes the highlandTools library.
# The .rootmap file means that ROOT will automatically load the required libraries, so calls like
# gSystem->Load("libhighlandTools.so") are not required in analysis macros.
#
# There is a slight caveat that OSX generates a .dylib file, rather that a .so file. The rlibmap
# utility assumes a .so file, so we must make a symlink between the two.
set base=$HIGHLANDTOOLSROOT/$HIGHLANDTOOLSCONFIG/lib 
set base1=$PSYCHECOREROOT/$PSYCHECORECONFIG/lib 
set base2=$HIGHLANDCOREROOT/$HIGHLANDCORECONFIG/lib 
set base3=$PSYCHEND280UTILSROOT/$PSYCHEND280UTILSCONFIG/lib 
set base4=$PSYCHEEVENTMODELROOT/$PSYCHEEVENTMODELCONFIG/lib 
set base5=$PSYCHEUTILSROOT/$PSYCHEUTILSCONFIG/lib 

if ( -d $base ) then
  set output=$base/libhighlandTools.rootmap
  set hl_lib=$base/libhighlandTools.so
  set root_libs="$base2/libhighlandCore.so $base3/libpsycheND280Utils.so $base5/libpsycheUtils.so $base4/libpsycheEvenModel.so $base1/libpsycheCore.so libRIO.so libHistPainter.so libMatrix.so libPhysics.so libTree.so libGeom.so libEG.so" 
  set includes="$HIGHLANDTOOLSROOT/inc/*_LinkDef.h"

  rlibmap -f -o $output -l $hl_lib -d $root_libs -c $includes

  if ( $HIGHLANDTOOLSCONFIG =~ "Darwin"* ) then
    ln -fs $base/libhighlandTools.dylib     $base/libhighlandTools.so
    ln -fs $base1/libpsycheCore.dylib       $base1/libpsycheCore.so
    ln -fs $base3/libpsycheND280Utils.dylib $base3/libpsycheND280Utils.so
    ln -fs $base4/libpsycheEventModel.dylib $base4/libpsycheEvenModel.so
    ln -fs $base5/libpsycheUtils.dylib      $base5/libpsycheUtils.so
    ln -fs $base2/libhighlandCore.dylib     $base2/libhighlandCore.so
  endif
endif
