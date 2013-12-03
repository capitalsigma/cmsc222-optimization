# paralell
# for SIZE in LARGE X
# do
# 	make -C ../ mergesort-seq 1=$SIZE
# 	./run_driver.py ../mergesort-seq-$SIZE.out 20 1
# done

# make -C ../ mergesort-seq 1=LARGE
# ./run_driver.py ../mergesort-seq-LARGE.out 20 10

make -C ../ mergesort-seq 1=XXLARGE
./run_driver.py ../mergesort-seq-XXLARGE.out 5 1


./store.sh mergesort-seq

echo done 
