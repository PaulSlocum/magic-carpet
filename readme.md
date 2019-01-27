# Magic Carpet

A generative audiovisual artwork that produces imagery with rapidly spinning photos of rugs and quilts.  Video documentation is [here](https://www.youtube.com/watch?v=vnxtZg9wPo4).

![menu screenshot](media/screenshots/screen_menu_480x320.jpg)

Magic Carpet is written in cross-platform C++ using SDL with minimal dependencies.  It currently builds for Raspberry Pi and iOS, and I'm planning to add builds for other platforms.  This code was ported from my original Magic Carpet iOS app, which was written in Objective C and OpenGL. 

I partly intended the project to be an example for creating other lightweight cross-platform audiovisual C++ applications.  SDL comes with examples that build on various platforms, but it's not trivial to combine those into a single fully working project on diverse platforms like Raspberry Pi and iOS.

Magic Carpet includes a very simple sprite system that can load images from JPEGs, an audio engine that can load OGG files into buffers and play samples from them, plus it includes examples of reading touch and keyboard input.  It's most of what's needed to get started with a simple SDL application.

(c) 2011-2018 Paul Slocum all rights reserved.  I plan to soon release this code soon under MIT license, contact me if you want to use it.  

![menu screenshot](media/screenshots/screen_1_480x320.jpg)
