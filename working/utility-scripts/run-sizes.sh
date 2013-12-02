for VAR in SMALL MEDIUM LARGE
do
	./comp-and-run.sh $1 $VAR 30
done
	
	
./comp-and-run.sh $1 XLARGE 10
