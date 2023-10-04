## LilTracer

> And on the first day, God said, let there be light!

A cruddy little raytracer written by me, Abdullah Khurram.

Heavily based off the guide [*Raytracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html), which has been an invaluable source of information for this project.

### Dependencies
Requires clang++, version 16. I think g++ should work too, but I haven't tested it. YMMV.
Runs just fine on Arch Linux and macOS, should be fine on other *nix-based operating systems.

As far as Windows goes, I don't know! Let me know if it works for you :)=
#
### How to compile/run
```bash
git clone https://github.com/abkhur/liltracer.git && cd liltracer
clang++ -o liltracer -Wall -Wextra main.cc
./liltracer > whatever_you_want.ppm
```
From there, the program will spit out a *.ppm file in the folder where the program is located. You can view the image in the image viewer of your choice.
However, I recommend [nomacs](https://github.com/nomacs/nomacs).

##
### Default Output
I still haven't implemented much here. This is baby's first raytracer, and it's *slow*. Keep that in mind.
This is the default output for the program. You can mess around with it, though. It's pretty easy, just read the code!

![default output](https://i.ibb.co/kQkV7MZ/image.png)

By default, this program will spit out a 1280x780 image. Keep that in mind. This thing's like a graphics slowcooker, basically. You can lower the resolution by fiddling around with variables in ```main.cc```.
#
### Contact info

If you have any questions or comments, feel free to shoot me a message either via email or thru Discord!

email: [abkhur@vt.edu](mailto:abkhur@vt.edu)
discord: @joechillw0rld

