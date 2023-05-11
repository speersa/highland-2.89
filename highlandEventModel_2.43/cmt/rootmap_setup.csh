
# This script sets up a .rootmap file in the directory that includes the highlandEventModel library.
# The .rootmap file means that ROOT will automatically load the required libraries, so calls like
# gSystem->Load("libhighlandEventModel.so") are not required in analysis macros.
#
# There is a slight caveat that OSX generates a .dylib file, rather that a .so file. The rlibmap
# utility assumes a .so file, so we must make a symlink between the two.
set base=$HIGHLANDEVENTMODELROOT/$HIGHLANDEVENTMODELCONFIG 
set base1=$PSYCHECOREROOT/$PSYCHECORECONFIG 
set base2=$PSYCHEEVENTMODELROOT/$PSYCHEEVENTMODELCONFIG 


if ( -d $base ) then
  set output=$base/libhighlandEventModel.rootmap
  set hl_lib=$base/libhighlandEventModel.so
  set root_libs="$base2/libpsycheEventModel.so $base1/libpsycheCore.so   libRIO.so libHistPainter.so libMatrix.so libPhysics.so libTree.so libGeom.so libEG.so" 
  set includes=$HIGHLANDEVENTMODELROOT/src/*_LinkDef.h

  rlibmap -f -o $output -l $hl_lib -d $root_libs -c $includes

  if ( $HIGHLANDEVENTMODELCONFIG =~ "Darwin"* ) then
    ln -fs $base/libhighlandEventModel.dylib $base/libhighlandEventModel.so
    ln -fs $base1/libpsycheCore.dylib        $base1/libpsycheCore.so
    ln -fs $base2/libpsycheEventModel.dylib  $base2/libpsycheEventModel.so
  endif
endif
