

ofxGiantImage is an addon for openframeworks used to draw giant, large, huge images.


Created by Tim Knapen on 15/03/13.
Updated example to work with with OF 0.8.1 on 14/07/14

www.timknapen.be

 
 This loads and displays huge images.
 To do this it creates a grid of tiles of ofTextures and draws them only when they are necessary.
 
 It has been tested to work very smoothly on 
 Macbook (13-inch, Aluminum, Late 2008) / 2 GHz Intel Core 2 Duo / 8 GB 1333 MHz DDR3 / NVIDIA GeForce 9400M 256 MB
 Mac Mini (2013) / 2,5-GHz dual-core Intel Core i5 / 4 GB (2x 2 GB) 1600-MHz DDR3/ Intel HD Graphics 4000
 on a 2560 x 1400 pixels display
 
 The image used to test is 20.000 × 15.000 pixels ( = 300.000.000 pixels :-)
 Tests were done with OF0062, OF007 and OF 0.8.1
 
 NOTES:
 1. Loading an image of this size will take a while, but don't worry, once it is loaded, the app runs smoothly.
 2. For now, this only works with RGB images.
 3. Draw( x, y, width, height) works a bit different than expected:
 it will not draw the image translated to x,y at the size width,height but it will draw whatever part of the image is contained within the rectangle defined by x, y, width, height.