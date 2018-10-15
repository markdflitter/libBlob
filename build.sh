printUsage ()
{
  echo "./build.sh [-c | --clean] [-d | --debug] [-D | --deep-clean] [-t | --test] [-T | --test-only] [-F | -test-filter <test to run>] [-h | --help]"
}

clean=
debug=
deepClean=
test=
testOnly=
testFilter=

while [ "$1" != "" ]; do 
	case $1 in
		-c|--clean)		clean=1	;;
		-d|--debug)		debug=1 ;;
		-D|--deep-clean)	deepClean=1 ;;
		-t|--test)		test=1	;;
		-T|--test-only)		testOnly=1 ;;
		-F|--test-filter)
			shift
			testFilter=$1
			;;
		-h|--help)
			printUsage
			exit
			;;
		*)	printUsage
			exit
			;;
	esac
	shift
done

targetFolder=release
if [ "$debug" = "1" ]; then
	targetFolder=debug
fi

if [ "deepClean" = "1" ]; then
  rm -rf ../../../bld/libraries/libBlob/$targetFolder
fi

if [ ! -d ../../../bld ]; then
  mkdir ../../../bld
fi

if [ ! -d ../../../bld/libraries ]; then
  mkdir ../../../bld/libraries
fi

if [ ! -d ../../../bld/libraries/libBlob ]; then
  mkdir ../../../bld/libraries/libBlob
fi

if [ ! -d ../../../bld/libraries/libBlob/$targetFolder ]; then
  mkdir ../../../bld/libraries/libBlob/$targetFolder
fi


pushd ../../../bld/libraries/libBlob/$targetFolder

if [ "$testOnly" != "1" ]; then
	if [ "$debug" = "1" ]; then
		cmake ../../../../src/libraries/libBlob -DCMAKE_BUILD_TYPE=Debug
	else
		cmake ../../../../src/libraries/libBlob
	fi

	if [ "$clean" = "1" ]; then
		make clean
	fi

	make
fi

if [ "$test" = "1" ] || [ "$testOnly" = "1" ]; then
	if [ $? -eq 0 ]; then
  		if [ "$testFilter" != "" ]; then
			ctest .. -R "$testFilter" 
		else
			ctest .. 
		fi
	fi
fi

popd
