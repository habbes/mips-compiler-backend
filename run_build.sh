./run_clean.sh
rm -rf build
mkdir build
cd src && make main && cp main ../ir2mips
