# paralell
for SIZE in SMALLER_MEDIUM SMALL_MEDIUM
do
	make -C ../ mmult-sym-omp 1=$SIZE
	./run_driver.py ../mmult-sym-omp-$SIZE.out 20 1
done

./store.sh mmult-sym-omp

# naive 
for SIZE in SMALLER_MEDIUM SMALL_MEDIUM
do
	make -C ../ mmult-seq 1=$SIZE
	./run_driver.py ../mmult-seq-$SIZE.out 20 4
done

./store.sh mmult-seq

echo done 
