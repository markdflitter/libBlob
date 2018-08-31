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
make

if [ $? -eq 0 ]; then
  ctest .. 
fi

popd
