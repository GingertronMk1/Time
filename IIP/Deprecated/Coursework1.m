%im1 = imread(uigetfile('*.png'));
%im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
im1 = imread('plant223_rgb.png');

im1(im1>200) = 0;

% Getting the size of the original image
im1size = size(im1);

im1RedChannel = im1(:,:,1);
im1GreenChannel = im1(:,:,2);
im1BlueChannel = im1(:,:,3);

% Separating the greenness of the image
im1Red = im1RedChannel - (im1GreenChannel + im1BlueChannel)/2;
im1Green = im1GreenChannel - (im1RedChannel + im1BlueChannel)/2;
im1Blue = im1BlueChannel - (im1RedChannel + im1GreenChannel)/2;

% Applying a Gaussian filter to deal with noise
im1GreenGauss = imgaussfilt(im1Green, 7);

% Thresholding the result; getting rid of any random green dots
im1GreenGaussThresh = im1GreenGauss;
im1GreenGaussThresh(im1GreenGaussThresh<127)=0;

level = graythresh(im1GreenGaussThresh);
im1Bin = imbinarize(im1GreenGaussThresh, level);

% Showing all images in one figure
subplot(2,2,1), imshow(im1);
subplot(2,2,2), imshow(im1Green);
subplot(2,2,3), imshow(im1GreenGauss);
subplot(2,2,4), imshow(im1Bin);

% Need to do:
% Take a colour image, and if the red, green, and blue channels are within `n` of
% one another, set all three channels to zero.
