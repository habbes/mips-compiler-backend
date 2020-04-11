rm -rf build
mkdir build
cd src && make main && cp main ../ir2mips
