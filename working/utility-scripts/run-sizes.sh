for VAR in SMALL MEDIUM LARGE XLARGE
do
	make -C ../ bsort-$VAR
	./run_driver.py ../bsort-$VAR.out 100 
done
	
	
