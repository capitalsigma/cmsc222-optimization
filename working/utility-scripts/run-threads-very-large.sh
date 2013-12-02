for T_COUNT in 2 4 8 16 32
do
	for VAR in XLARGE XXLARGE
	do
		./comp-and-run.sh $1 $VAR 1 $T_COUNT
	done
done

