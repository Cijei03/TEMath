cd ./..

clear

CYAN='\033[0;34m'
BUILD_DIR="./buildCache"

echo -e ${CYAN} "Clean build started."

if [-e ${BUILD_DIR}]
then
    rm -r ${BUILD_DIR} -f
fi

cd buildCache

echo -e ${CYAN} "Starting Debug build..."

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja


echo -e ${CYAN} "Starting Release build..."
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
