# Wiki

This repo hosts team *É Só Fazer* ICPC wiki, is based on the [KACTL](https://github.com/kth-competitive-programming/kactl)

# Dependencies
The build process uses the following tools:  
- LaTeX (pdflatex together with some common packages such as 'listings')
- Python	
- make
- bc

Downloading latex on ubuntu and debian base linux:
```sh
sudo apt-get install texlive-latex-base texlive-latex-recommended texlive-latex-extra
sudo apt-get install build-essential
sudo apt-get install python3
suto apt-get install bc
```

# Running

```sh
make wiki
```

# Testing

```sh
make test-compiles
make test
```
To run specific test:
```sh
./doc/scripts/run_test.sh ./stress-tests/<test_path>/<test_name>
./doc/scripts/run_test.sh ./stress-tests/data-structures/SegTree.cpp
```

To create a test:
- Add <filename>.cpp to stress-tests
- Use stress-tests/data-structures/LazySeg.cpp as an example
- Add the links to problems using the topic

# Creating

## New section
- Create a new directory
- Create chapter.tex inside it and add it to wiki.tex

## Wiki files
- Include author, description, time and memory complexity
- Include it on chapter.tex

## Wiki code:
### Should be working correctly:
- Tested at challenging problems
- Using intended complexity (and good constant factor)
- Compiling in C++17 and C++20 (if possible)
### Should follow hierarchy:
- Basic data as containers/types
- Basic processes as functions
- Union of processes and/or data as structs
- Outer processes should not worry about inner's details
### Should be as abstract as convenient:
- Use of template types internally
- Easy modification of variable processes
- Support generalization of original functionality
### Should be as short as possible:
- Avoid extra functions and data
- Avoid too many whitespaces and lines
- Use macros and short names

# License
TODO