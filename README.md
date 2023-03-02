# ped_hom
* A __beta__ C++ program for making homozygous haploid ped files.
* Requires the [boost](http://www.boost.org/) C++ libraries

# Usage 
* Tested on Ubuntu 22.04 only

```bash
# Install boost libraries
sudo apt install libboost-all-dev

# Compile
g++ ped_hom_0.1.cpp -o ped_hom

# Run
ped_hom file.ped > file_h.ped
```
