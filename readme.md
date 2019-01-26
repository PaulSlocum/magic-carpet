# Magic Carpet

A generative audiovisual artwork that produces imagery with rapidly spinning photos of rugs and quilts.

Magic Carpet is written in cross-platform C++ using SDL with minimal dependencies.  It currently builds for Raspberry Pi and iOS, and I'm planning to add builds for other platforms.  This code was ported from the original Magic Carpet iOS app, which was written in Objective C and OpenGL. 

I partly intended the project to be an example for creating other lightweight cross-platform audiovisual C++ applications.  SDL comes with examples that build on various platforms, but it's not trivial to combine those into a single fully working project on diverse platforms like Raspberry Pi and iOS.

Magic Carpet includes a very simple sprite system that can load images from JPEGs, an audio engine that can load OGG files into buffers and play samples from them, plus it includes examples of reading touch and keyboard input.  It's most of what's needed to get started with a simple SDL application except for a text display library, which can be easily integrated.

(c) 2012-2018 Paul Slocum all rights reserved.  I plan to soon release this code soon under MIT license, contact me if you want to use it.  
