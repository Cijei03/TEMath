BASIC='\033[0;0m'
CYAN='\033[0;34m'
BUILD_DIR="./buildCache"

cd ../..

clear
echo -e ${CYAN} "Build started."
echo -n -e ${BASIC}

cd ${BUILD_DIR}

echo -e ${CYAN} "Starting Debug build..."
echo -n -e ${BASIC}
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja
