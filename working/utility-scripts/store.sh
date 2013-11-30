DIR="./runs/$1"
if [ ! -d $DIR ]; then
	mkdir $DIR
fi
mv *.log $DIR/.

