Jack Ellis
psyje5@nottingham.ac.uk
4262333

## Specification

Create a MATLAB program that takes an image of a plant, and returns a binary image in which
the white pixels correspond to the leaves of the plant.

Personal Requirements:
Minimal false positives: we do not want to waste time processing parts of the image that aren't
food, so the smallest number of false positives are a must.
Speed: the largest image we were given as a test is 5 million pixels in total. This should be
processed quickly, so that we may use the data quickly and not have the image processing step be
a bottleneck.
Total automation: this is a process that should be able to be run overnight, say, without any human
intervention, and as such should be totally automatic.

## Design

To begin with, the image was split into as many constituent parts as possible, including converting
to HSV and splitting the H, S, and V, as well as taking each channel of the RGB spectrum. [SCREENSHOTS FOR EACH]

The RGB constituents were then taken and the average of the other two subtracted, to give only the actual
value of that channel, say `imageG - (imageR + imageB)/2`. This is a more accurate representation of
the individual colour channels in the image.
![Step 1 applied to 001](Screenshots/001Step1.png)
![Step 1 applied to 017](Screenshots/017Step1.png)
![Step 1 applied to 223](Screenshots/223Step1.png)


Now with an accurate representation of the individual RGB channels, MATLAB's `imbinarize` function was used
to convert the images into binary; a 'helper' function was created to assist this, largely in terms of
then using erosion/dilation to reduce noise.
![Step 2 applied to 001](Screenshots/001Step2.png)
![Step 2 applied to 017](Screenshots/017Step2.png)
![Step 2 applied to 223](Screenshots/223Step2.png)

Looking at these binary images, in all three instances, it appeared that the Greenness binary image (bottom
middle) subtract the Blueness (bottom right) would give something close to a representation of just the leaves. The next step,
therefore, was to take Blueness away from Greenness. It turns out however that in MATLAB, a pixel
set to `-1`, i.e. a black pixel subtract a white one, is also white. Another helper function was therefore
required, this time taking two images, subtracting one from the other, then setting all pixels with
value less than zero to zero. This was done, and the Blueness subtracted from Greenness.
![Step 3 applied to 001](Screenshots/001Step3.png)
![Step 3 applied to 017](Screenshots/017Step3.png)
![Step 3 applied to 223](Screenshots/223Step3.png)

In the second and third examples, a great deal of noise has been reduced around the leaves. Importantly,
the leaves are now the largest objects (by pixel area) in all three. So next, the MATLAB function
`bwconncomp` can be used. This function returns information about the binary image specified, including the number of
connected components, as well as their area in pixels. The next step therefore is to use this to take the
largest connected component (the leaves), and remove the rest of the image. This has to be done in a slightly
convoluted way:
  1. Make a copy of the image to be modified
  2. 'Delete' the largest component
  3. Subtract this image from the original
![Step 4 applied to 001](Screenshots/001Step4.png)
![Step 4 applied to 017](Screenshots/017Step4.png)
![Step 4 applied to 223](Screenshots/223Step4.png)

Finally, dilate this image slightly, to smooth out the edges and make sure as much of the leaves as
possible are recognised. .
![Step 5 applied to 001](Screenshots/001Step5.png)
![Step 5 applied to 017](Screenshots/017Step5.png)
![Step 5 applied to 223](Screenshots/223Step5.png)

To sum, step-by-step:
  1. Take only the green and blue channels, subtracting from them the average of the other two channels
  2. Binarize these images
  3. Erode/dilate them for noise reduction
  4. Subtract the 'blue' image from the 'green' one
  5. Ensure that all negative pixels are set to zero
  6. Identify the largest connected component in the image
  7. Remove all other parts of the image

![Step 6 applied to 001](Screenshots/001Step6.png)
![Step 6 applied to 017](Screenshots/017Step6.png)
![Step 6 applied to 223](Screenshots/223Step6.png)

## Key Features

The program is totally autonomous, and gives very little in the way of false positives.
On the largest image, it takes ~4.5 seconds to return the binary image that corresponds to the leaves.

## Testing

### Accuracy

#### Plant 001
![Plant 001 as identified by my program](Screenshots/001PROGRAM.png)
![Plant 001 as identified by hand](Screenshots/001LABELED.png)

As we can see, the stem at the 10 o'clock position is not identified, nor are parts of stems at 9 and 4 o'clock. The rest however, is very close.

#### Plant 017
![Plant 017 as identified by my program](Screenshots/017PROGRAM.png)
![Plant 017 as identified by hand](Screenshots/017LABELED.png)

This is almost perfect; maybe some overspill, but minimal false positives. Very happy with this one

#### Plant 223
![Plant 223 as identified by my program](Screenshots/223PROGRAM.png)
![Plant 223 as identified by hand](Screenshots/223LABELED.png)

Large chunks of leaves unidentified here, however the outline is largely there bar a fairly hefty chunk at the top left.

### Time

#### Plant 001
<1 second running, near-instantaneous. Can't really ask for more than that.

#### Plant 017
Again, near enough instant processing and return of the image.

#### Plant 223
~4.5 second running time, largely to do with the amount of erosion and dilation involved. Without the erosion/dilation steps when binarizing the image, the runtime
drops to ~3 seconds, however a huge amount of the image is lost. In this instance, too much of the image is lost to make the improved running time worth it, and as
such the erosion/dilation steps will remain

## Critical Evaluation
Overall I'm happy with the result; no false positives and a very fast running time on a 5-megapixel image.
There are however, a couple of things that could be done better. On `plant223`, there is a leaf at the bottom
left of the image that isn't picked up. This is due to the connected components part of the code making it so
that only one object will be selected, but it does then also mean that if there are multiple plants in
an image, only the largest will be selected.

Further, not all of the leaves are marked.
This is not to say that there is an entire unmarked leaf, but that the entire area of some leaves are unmarked.
I feel that enough of the leaves are identified, however I'd still prefer it that the whole things were marked.
It seems that the way to do this is to increase the value passed into the `erodeDilate` function, the structural
element.
Doing this however causes the program to take an awful lot longer to run, which I don't think is worth it.
This is a personal thing, but I'd rather the program be able to take a batch of 10 images and spit out 10 binary images
on which 70% of the leaves are marked than only one image where 90% is marked in the same time.

## Conclusion

The result is a good balance between speed and accuracy, with a small amount of false positivity ensuring more of the leaf edge is captured.
The program is very autonomous, in that it takes user input only once. In summary, it fulfils my personal requirements, as well as those specified externally.
