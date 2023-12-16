cd ../..

clear

BASIC='\033[0;0m'
CYAN='\033[0;34m'
BUILD_DIR="./buildCache"

echo -e ${CYAN} "Clean build started."

if [ -d ${BUILD_DIR} ];
then
    rm -r ${BUILD_DIR} -f
fi

mkdir buildCache
cd buildCache

echo -e ${CYAN} "Starting Debug build..."
echo -n -e ${BASIC}

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja


echo -e ${CYAN} "Starting Release build..."
echo -n -e ${BASIC}
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
