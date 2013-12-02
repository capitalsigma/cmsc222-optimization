for T_COUNT in 2 4 8 16 32
do
	for VAR in SMALL MEDIUM LARGE XLARGE XXLARGE
	do
		for RANGE in 4096 1048576 16777216
		do
			./comp-and-run.sh csort-new-par $VAR 1 $T_COUNT $RANGE
		done
	done
done

for VAR in SMALL MEDIUM LARGE XLARGE XXLARGE
do
	for RANGE in 4096 1048576 16777216
	do
	./comp-and-run.sh csort-new-par $VAR 1 $T_COUNT $RANGE
	done
done
