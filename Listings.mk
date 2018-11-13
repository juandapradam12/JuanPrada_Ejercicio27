# compilo con make -f Listings.mk

Listing12.2: Listing12.2.c
	mpicc Listing12.2.c -o Listing12.2
	mpirun -np 2 ./Listing12.2

Listing12.3: Listing12.3.c
	mpicc Listing12.3.c -o Listing12.3
	mpirun -np 2 ./Listing12.3

clean: 
	rm Listing12.2
	rm Listing12.3
