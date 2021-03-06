# compile_lamscript.sh
#
# This script is used to configure and compile lamscript.

ROOT_DIR="$(git rev-parse --show-toplevel)"
pushd $ROOT_DIR > /dev/null

# ----------------------------- LAMBDA-SH & ARGS ------------------------------
source lambda-sh/lambda.sh

LAMBDA_PARSE_ARG build Release "The type of build to produce."
LAMBDA_PARSE_ARG cpp-compiler g++ "The compiler to use for C++ code."
LAMBDA_PARSE_ARG cores 6 "The number of cores used for compilation."

LAMBDA_COMPILE_ARGS $@

export CXX=$LAMBDA_cpp_compiler

LAMBDA_INFO "Attempting to Compile a $LAMBDA_build for lamscript."

# ----------------------------------- CMAKE ------------------------------------

if [ $LAMBDA_build = "Release" ] || [ $LAMBDA_build = "Debug" ]; then
    cmake \
        -DCMAKE_BUILD_TYPE="$LAMBDA_build" \
        -DDISTRIBUTION_BUILD=False .
elif [ $LAMBDA_build = "Dist" ]; then
    cmake \
        -DCMAKE_BUILD_TYPE="Release" \
        -DDISTRIBUTION_BUILD=True .
else
    LAMBDA_FATAL \
        "You need to pass a valid build type in order to compile lamscript."
fi

LAMBDA_ASSERT_LAST_COMMAND_OK \
    "Couldn't generate the cmake file necessary for compiling lamscript."

# ----------------------------------- BUILD ------------------------------------

make -j $LAMBDA_cores
LAMBDA_ASSERT_LAST_COMMAND_OK "Couldn't successfully compile lamscript."

LAMBDA_INFO "Successfully compiled lamscript."

$popd  # ROOT_DIR
