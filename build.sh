printUsage ()
{
  echo "./build.sh [-C | --CMAKE] [-c | --clean] [-d | --debug] [-t | --test] [-T | --test-only] [-F | -test-filter <test to run>] [-h | --help]"
}

cmake=
clean=
debug=
test=
testOnly=
testFilter=

while [ "$1" != "" ]; do 
	case $1 in
		-C|--CMAKE)  	cmake=1 ;;
		-c|--clean)	clean=1	;;
		-d|--debug)	debug=1 ;;
		-t|--test)	test=1	;;
		-T|--test-only)
			testOnly=1 ;;
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

if [ ! -d ../../../bld ]; then
  mkdir ../../../bld
fi

if [ ! -d ../../../bld/libraries ]; then
  mkdir ../../../bld/libraries
fi

if [ ! -d ../../../bld/libraries/libBlob ]; then
  mkdir ../../../bld/libraries/libBlob
fi

targetFolder=release
if [ "$debug" = "1" ]; then
	targetFolder=debug
fi

if [ ! -d ../../../bld/libraries/libBlob/$targetFolder ]; then
  mkdir ../../../bld/libraries/libBlob/$targetFolder
fi


pushd ../../../bld/libraries/libBlob/$targetFolder

if [ "$testOnly" != "1" ]; then
	if [ "$cmake" = "1" ]; then
		if [ "$debug" = "1" ]; then
			cmake ../../../../src/libraries/libBlob -DCMAKE_BUILD_TYPE=Debug
		else
			cmake ../../../../src/libraries/libBlob
		fi
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
