# This script sets up a .rootmap file in the directory that includes the psycheND280Utils library.
# The .rootmap file means that ROOT will automatically load the required libraries, so calls like
# gSystem->Load("libpsycheND280Utils.so") are not required in analysis macros.
#
# There is a slight caveat that OSX generates a .dylib file, rather that a .so file. The rlibmap
# utility assumes a .so file, so we must make a symlink between the two.
base=$PSYCHEND280UTILSROOT/$PSYCHEND280UTILSCONFIG/lib 
base1=$PSYCHECOREROOT/$PSYCHECORECONFIG/lib 
base2=$PSYCHEEVENTMODELROOT/$PSYCHEEVENTMODELCONFIG/lib
base3=$PSYCHEUTILSROOT/$PSYCHEUTILSCONFIG/lib 


if [[ -d $base ]]; then
  output=$base/libpsycheND280Utils.rootmap
  hl_lib=$base/libpsycheND280Utils.so
  root_libs="$base3/libpsycheUtils.so $base2/libpsycheEventModel.so $base1/libpsycheCore.so libRIO.so libHistPainter.so libMatrix.so libPhysics.so libTree.so libGeom.so libEG.so" 

  if command -v rlibmap >/dev/null 2>&1; then
    rlibmap -f -o $output -l $hl_lib -d $root_libs -c $PSYCHEND280UTILSROOT/inc/*_LinkDef.h
  fi
  
  if [[ $PSYCHEND280UTILSCONFIG == "Darwin"* ]]; then
    ln -fs $base/libpsycheND280Utils.dylib     $base/libpsycheND280Utils.so
    ln -fs $base1/libpsycheCore.dylib          $base1/libpsycheCore.so
    ln -fs $base2/libpsycheEventModel.dylib    $base2/libpsycheEventModel.so
    ln -fs $base3/libpsycheUtils.dylib         $base3/libpsycheUtils.so
  fi
fi
