# libinput

This is a library for handling controller inputs on the Wii U.

## Dependencies

This library uses features from [dynamic_libs](https://github.com/Maschell/dynamic_libs/tree/lib) and [libutils](https://github.com/Maschell/libutils), so make sure these are both installed before trying to use libinput.

## Usage
Compile using
```
make && make install
```
to install to your Portlibs folder, then make sure your Makefile has the include path
```
$(PORTLIBS)/include/libutils
```

for example by adding
```
export INCLUDE	:= [...]  -I$(PORTLIBS)/include/libutils
```

Finally, make sure you link all libraries necessary for libinput to work
```
-lutils -ldynamic_libs -linput
```

## Credits

[Maschell](https://github.com/Maschell/) and any other contributors for libutils, dynamic_libs, from which I stole my Makefile
Nintendo for making the Wii U gamepad so horrible I could use it to motivate myself to do this
