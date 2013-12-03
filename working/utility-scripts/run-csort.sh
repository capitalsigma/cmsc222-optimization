# # seq
# for SIZE in MEDIUM LARGE XLARGE XXLARGE XXXLARGE
# do
# 	make -C ../ csort-seq 1=$SIZE
# 	./run_driver.py ../csort-seq-$SIZE.out 20 1
# done

# ./store.sh csort-seq

# par
# for SIZE in MEDIUM LARGE XLARGE 
# do
# 	for TH in 4 6 8 10
# 	do
# 		make -C ../ csort-par 1=$SIZE 2=$TH
# 		./run_driver.py ../csort-par-$SIZE-$TH.out 20 1
# 	done
# done
# ./store.sh csort-par

for TH in 12 10 8
do
	make -C ../ csort-new-par 1=XXXLARGE 2=$TH
	./run_driver.py ../csort-new-par-XXXLARGE-$TH.out 10 1
done


./store.sh csort-par


make -C ../ clean

echo done 
