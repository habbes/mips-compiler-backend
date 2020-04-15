tests=("arithmetic" "for-to" "long-blocks" "sort" "sum-to-n")
outputPath="./output"
testsPath="./test-cases-mar19"

for test in ${tests[@]}; do
    echo "-- TEST CASE $test --"
    echo "compiling..."
    ./ir2mips $testsPath/ir/$test.ir $outputPath/$test.s
    echo "executing..."
    echo
    spim -keepstats -f $outputPath/$test.s
    echo
    echo "done"
done
