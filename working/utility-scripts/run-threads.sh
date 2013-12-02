for T_COUNT in 16 18 20 22 24 26
do
	for VAR in LARGE XLARGE
	do
		./comp-and-run.sh $1 $VAR 1 $T_COUNT
	done
done

