# CP-template

This is a collection of quality implementations of common and hard to implement algorithms.
Algorithms are implemented in C++ and in `algos` folder. Tests are mostly downloaded from cses.fi

## Running tests

```shell
python test.py [algo names...] [--verbose]
```

Tests are downloaded from https://cses-tests.pages.dev on first use (into `tests/cses`).

## Generating pdfs

On unix just run

```shell
./all.sh
```
or

```shell
python gen_latex.py
make
```

pdf/output.pdf is ready to print (for ICPC contest) already without running any scripts.
