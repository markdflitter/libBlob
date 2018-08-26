if [ ! -d ../../../bld ]; then
  mkdir ../../../bld
fi

if [ ! -d ../../../bld/libraries ]; then
  mkdir ../../../bld/libraries
fi

if [ ! -d ../../../bld/libraries/libBlob ]; then
  mkdir ../../../bld/libraries/libBlob
fi

pushd ../../../bld/libraries/libBlob

cmake ../../../src/libraries/libBlob
make clean
make

ctest .. 

popd
