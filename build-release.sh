
mkdir build
cd build
cmake ..
cd modules/kernel
make
cd ../patch
make
cd ../usbdevice
make
cd ../user
make
cd ../..
make release
