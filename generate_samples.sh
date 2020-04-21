samples=("arithmetic" "array" "for-to" "function" "if-else" "logical" "long-blocks" "sum-to-n" "web" "while")
allocators=("naive" "block" "briggs")
srcDir="samples/ir"
outDir="samples/asm"
resDir="samples/res"

rm -rf $outDir
rm -rf $resDir
mkdir $outDir
mkdir $resDir


for sample in ${samples[@]}; do
    for allocator in ${allocators[@]}; do
        srcPath=$srcDir/$sample.ir
        outPath=$outDir/$sample-$allocator.s
        resPath=$resDir/$sample-$allocator.txt

        echo "compiling $srcPath to $outPath using $allocator allocator..."
        ./ir2mips $srcPath $outPath $allocator
        spim -keepstats -f $outPath > $resPath
        echo "saved execution results to $resPath"
    done
done