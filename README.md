# CP-template

This is a collection of quality implementations of common and hard to implement algorithms.
Algorithms are implemented in C++ and in `algos` folder. Tests are mostly downloaded from cses.fi

## Running tests

```shell
python3 test.py [algo names...] [--verbose]
```

`--report` updates `perf_report.txt` with the timings of the tests that were run.

Tests are downloaded from https://cses-tests.pages.dev on first use (into `tests/cses`).

## Generating pdfs

```shell
python3 pdf.py
```

This builds `output.pdf` (needs `pygments` and LaTeX), which is ready to print (for ICPC contest). Intermediate files go to the gitignored `pdf` folder.
