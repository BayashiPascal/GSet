# GSet
GSet library is a C library to manipulate sets of data.

Elements of the GSet are void pointers toward any kind of data. These data must be allocated and freed separately. The GSet only provides a mean to manipulate sets of pointers toward these data.

The GSet offers functions to add elements (at first position, last position, given position, or sorting based on a float value), to access elements (at first position, last position, given position), to get index of first/last element pointing to a given data, to remove elements (at first position, last position, given position, or first/last/all pointing toward a given data), to search for data in elements (first one or last one), to print the set on a stream, to split, merge and sort the set.

The library provides also GSetVecFloat, GSetVecShort, GSetBCurve, GSetSCurve structure with same interface as a GSet but whose contents is restrained to, respectively, VecFloat, VecShort, BCurve, SCurve structures.

The library also provides two iterator structures to run through a GSet forward or backward, and apply a user defined function on each element.

## How to install this repository
1) Create a directory which will contains this repository and all the repositories it is depending on. Lets call it "Repos"
2) Download the master branch of this repository into "Repos". Unzip it if necessary.
3) The folder's name for the repository should be followed by "-master", rename the folder by removing "-master".
4) cd to the repository's folder
5) If wget is not installed: ```sudo apt-get update && sudo apt-get install wget``` on Ubuntu 16.04, or ```brew install wget``` on Mac OSx
6) If gawk is not installed: ```sudo apt-get update && sudo apt-get install gawk```  on Ubuntu 16.04, ```brew install gawk``` on Mac OSx
7) If this repository is the first one you are installing in "Repos", run the command ```make -k pbmake_wget```
8) Run the command ```make``` to compile the repository. 
9) Eventually, run the command ```main``` to run the unit tests and check everything is ok.
10) Refer to the documentation to learn how to use this repository.

The dependancies to other repositories should be resolved automatically and needed repositories should be installed in the "Repos" folder. However this process is not completely functional and some repositories may need to be installed manually. In this case, you will see a message from the compiler saying it cannot find some headers. Then install the missing repository with the following command, e.g. if "pbmath.h" is missing: ```make pbmath_wget```. The repositories should compile fine on Ubuntu 16.04. On Mac OSx, there is currently a problem with the linker.
If you need assistance feel free to contact me with my gmail address: at bayashipascal.
