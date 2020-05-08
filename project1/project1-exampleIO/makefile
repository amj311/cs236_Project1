NUM?=1
numbers=10 11 12 13 14 15 16 17 18 19 20 61 62
tests=project$(NUM)-exampleIO

run:
	for number in $(numbers); \
	do \
		./lab$(NUM) $(tests)/in$$number.txt > $(tests)/out.txt ; \
		diff $(tests)/out.txt $(tests)/out$$number.txt || (echo "diff failed on test $$number") \
	done
	rm $(tests)/out.txt

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp -o lab$(NUM)
