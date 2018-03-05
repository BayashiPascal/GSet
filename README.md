# GSet
GSet library is a C library to manipulate sets of data.

Elements of the GSet are void pointers toward any kind of data. These data must be allocated and freed separately. The GSet only provides a mean to manipulate sets of pointers toward these data.

The GSet offers functions to add elements (at first position, last position, given position, or sorting based on a float value), to access elements (at first position, last position, given position), to get index of first/last element pointing to a given data, to remove elements (at first position, last position, given position, or first/last/all pointing toward a given data), to search for data in elements (first one or last one), to print the set on a stream, to split, merge and sort the set.

The library provides also GSetVecFloat, GSetVecShort, GSetBCurve, GSetSCurve structure with same interface as a GSet but whose contents is restrained to, respectively, VecFloat, VecShort, BCurve, SCurve structures.

The library also provides two iterator structures to run through a GSet forward or backward, and apply a user defined function on each element.
