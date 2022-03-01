rm wordlist.txt wrongspell.txt dict.txt dictionaryWordle.txt
touch wordlist.txt wrongspell.txt dict.txt dictionaryWordle.txt

alpha="a b c d e f g h i j k l m n o p q r s t u v w x y z"
for i in $alpha
do
	for k in $alpha
	do
		for x in $alpha
		do
			for y in $alpha
			do
				for z in $alpha
				do
					echo $i$k$x$y$z >> wordlist.txt
				done
			done
		done
	done
done

spell wordlist.txt >> wrongspell.txt

diff wrongspell.txt wordlist.txt | grep ">" >> dict.txt

cut -d ' ' -f 2 dict.txt >> dictionaryWordle.txt