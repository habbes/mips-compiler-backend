./run_quickcheck.sh naive > snapshots_temp.txt
diff snapshots-naive.txt snapshots_temp.txt
rm snapshots_temp.txt