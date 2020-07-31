# Magic Carpet

Magic Carpet is a generative audiovisual artwork that produces unique imagery using rapidly spinning photos of rugs and quilts that are accompanied by generative music.  It was originally released as an iOS app in 2010, but later when Apple's changes to iOS broke the app, I decided to port it to cross-platform C++ using SDL.  This new version is mostly complete except for some of the original generative audio effects that still need to be included.

Video documentation is [here](http://qotile.net/files/MAGIC_CARPET_wsound.mp4).

![menu screenshot](media/screenshots/screen_menu_480x320.jpg)

This new version of Magic Carpet is written in C++ using [SDL](https://www.libsdl.org/) without any additional external dependecies.  The OGG and image decoding are handled by MIT licensed [single file libraries](https://github.com/nothings/single_file_libs) that are included with the project.  It currently builds for Raspberry Pi and iOS, and it should be relatively easy to add builds for Android, Windows, and [Emscripten](https://en.wikipedia.org/wiki/Emscripten).

In addition to making the Magic Carpet carpet app more portable, I intended this project to be a skeleton for creating other lightweight cross-platform audiovisual C++ applications.  It includes a very simple sprite system that can load images from JPEGs, an audio engine that can load OGG files into buffers and play samples from them, plus it has examples of cross platform touch and keyboard input.

Use the included Xcode project to build for iOS and the makefile to build for Raspberry Pi.

&copy; 2010-2020 Paul Slocum all rights reserved.  This project is provided for personal use only, but I plan to soon release this code under MIT license.  Contact me if you'd like to use it for something.

![menu screenshot](media/screenshots/screen_1_480x320.jpg)
