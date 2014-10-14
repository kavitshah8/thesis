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
* To control the way back works, and make sure you do not generate more than N children.
* printDataStr second last row shows error

#### Future

* To simulate ACK, NACK trees from given commitment trees & run verification algorithm.
* To create all possible commitment trees from given aggregation tree.

#### Misc
* Change N, NN to global constant NODES

#### Development

* Development is done on kavitdev branch and after manual testing it is merged to master branch. Checkout kavitdev branch for latest version.

#### Notes

* Tree generation algorithm generates more nodes than you feed in, but that is fine as far as you have a random tree.