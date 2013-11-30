for VAR in SMALL MEDIUM LARGE
do
	make -C ../ bsort-global-$VAR
	./run_driver.py ../bsort-global-$VAR.out 100 
done
	
	
