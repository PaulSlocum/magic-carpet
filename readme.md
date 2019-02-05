# Magic Carpet

A generative audiovisual artwork that produces imagery using rapidly spinning photos of rugs and quilts.  Video documentation is [here](https://www.youtube.com/watch?v=vnxtZg9wPo4).  The projects runs and is mostly complete except for some of the audio effects.

![menu screenshot](media/screenshots/screen_menu_480x320.jpg)

Magic Carpet is written in cross-platform C++ using [SDL](https://www.libsdl.org/) with minimal dependencies.  It currently builds for Raspberry Pi and iOS, and it should be possible to add builds for Android and Windows.  This code was ported from my original Magic Carpet iOS Objective C app. 

In addition to making the Magic Carpet carpet app more portable, I intended the project to be a skeleton for creating other lightweight cross-platform audiovisual C++ applications.  It includes a very simple sprite system that can load images from JPEGs, an audio engine that can load Ogg files into buffers and play samples from them, plus it has examples of cross platform touch and keyboard input.

Use the Xcode project to build for iOS and the makefile to build for Raspberry Pi.

(c) 2011-2019 Paul Slocum all rights reserved.  For personal use only, but I plan to soon release this code under MIT license.  Contact me if you'd like to use it.  

![menu screenshot](media/screenshots/screen_1_480x320.jpg)
