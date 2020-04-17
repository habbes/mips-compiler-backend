./run_quickcheck.sh > snapshots_temp.txt
diff snapshots.txt snapshots_temp.txt
rm snapshots_temp.txt