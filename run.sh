########################################
# This is shell script that can perform build operations.
########################################

COMMAND=$1
ROOT_DIR=$(pwd)

BUILD_DIR=$ROOT_DIR/build
TESTS_DIR=$ROOT_DIR/build/tests

########################################
# Help message
########################################
print_help () {
	echo 
	echo "Usage: ./run.sh [build|run-tests|clean|wipe|help]"
	echo "	build 		-- build application from source code"
	echo "	run-tests 	-- build rpm package"
	echo "	clean 		-- clean build directory"
	echo "	wipe	 	-- remove all build files and packages"
	echo
}



########################################
# Build source code
########################################
build_source () {
	if ! [ -d $BUILD_DIR ] ; then
		mkdir $BUILD_DIR
	fi

	cd $BUILD_DIR	
	cmake ../ && make
	cd $ROOT_DIR
}



########################################
# Perform make clean 
########################################
clean () {
	cd $BUILD_DIR	
	make clean
	cd $ROOT_DIR
	
}



########################################
# Wipe build files
########################################
full_clean () {
	rm -rf $BUILD_DIR/*
}


########################################
# Run tets
########################################
run_tests () {
	if ! [ -x $TESTS_DIR/test-megachat-networklib ]; then
		exit 1
	fi
	$TESTS_DIR/test-megachat-networklib
}


########################################
# Parse command
########################################
case "${COMMAND}" in
	"help" )
		print_help
	;;
	"build" )
		echo "Building..."
		build_source
	;;
	"run-tests" )
		echo "Testing..."
		run_tests
	;;
	"clean" )
		echo "Cleaning build dir..."
		clean
	;;
	"wipe" )
		echo "Wiping build dir..."
		full_clean
	;;
	* )
		print_help
	;;
esac
