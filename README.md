<div align="center">
	<img src="http://notredamebus.com/wp-content/uploads/2012/01/Purdue_Boilermakers.jpg" height="350" alt="Purdue" title="Purdue">
</div>

Thesis
=====

#### To simulte the protocol 
Single step compilation
```
cd thesis
gcc main.c ../src/util.c
./a.out
```

Multiple step compilation
```
cd thesis
gcc -c src/util.c
gcc -c thesis/main.c
gcc main.o util.o -o main
./main
```
#### Current

* To generate commitment tree from given aggregation tree.
* To simulate ACK, NACK trees from given commitment trees & run verification algorithm.
* To create all possible commitment trees from given aggregation tree.
* Try implementing printTree without recurssion

#### Development

* Development is done on kavitdev branch and after manual testing it is merged to master branch. Checkout kavitdev branch for latest version.

#### Notes

* Tree generation algorithm generates more nodes than you feed in, but that is fine as far as you have a random tree.