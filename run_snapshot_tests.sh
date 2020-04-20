
allocators=("naive" "block" "briggs")

for allocator in ${allocators[@]}; do
    echo "Testing $allocator allocator snapshots"
    ./run_quickcheck.sh $allocator > snapshots_temp.txt
    diff snapshots-$allocator.txt snapshots_temp.txt
    rm snapshots_temp.txt
done