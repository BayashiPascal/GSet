# GSet

GSet is a C library providing a set data structure and the functions to interact with it.

A GSet is a collection of element, each containing a pointer to data. These data are of type `void*` for the default `GSet` structure, but typed version of this structure can be defined in one line with a provided macro.

## Table Of Content

1 [Install](https://github.com/BayashiPascal/GSet/tree/master#1-install)

2 [Usage](https://github.com/BayashiPascal/GSet/tree/master#2-usage)

3 [License](https://github.com/BayashiPascal/GSet/tree/master#3-license)

# 1 Install

Download this repository into a folder of your choice, in the examples below I'll call it `Repos`, as follow:
```
cd Repos
wget https://github.com/BayashiPascal/GSet/archive/main.zip
unzip main.zip
mv GSet-main GSet
rm main.zip
cd GSet
make all
sudo make install
```

The [TryCatchC](https://github.com/BayashiPascal/TryCatchC) libraries will automatically be installed during installation. You may be asked for your password during installation.

# 2 Usage

# 2.1 Define a typed GSet

To create a typed `GSet` containing data of type, for example, `struct UserData`, one can use the macro `DefineGSet(UserData, struct UserData)`. Then, all the functions defined for a `GSet` are redefined with an equivalen function for the type `struct UserData`. Below is an example of how it could be used:

```
DefineGSet(UserData, struct UserData)
int main() {
  struct GSetUserData* set = GSetUserDataAlloc();
  struct UserData userData = { ... };
  GSetUserDataPush(set, &userData);
  struct UserData* ptrUserData = GSetUserDataPop(set);
  GSetUserDataFree(&set);
}
```

## 3 License

GSet, a C library providing a set data structure and the functions to interact with it.
Copyright (C) 2021  Pascal Baillehache

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

