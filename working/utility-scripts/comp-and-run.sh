make -C ../ $1 1=$2
./run_driver.py ../$1-$2.out 100 
