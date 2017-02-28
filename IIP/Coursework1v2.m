%im1 = imread(uigetfile('*.png'));
%im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
im1 = imread('plant223_rgb.png');

im1green = im1(:,:,2) - (im1(:,:,1) + im1(:,:,3))/2;

[counts,x] = imhist(im1green,16);
%stem(x,counts);

T = otsuthresh(counts);

BW = imbinarize(im1green,T);
BWsizeacross = size(BW);
BWsizeacross = BWsizeacross(1);
threshvalue = round(BWsize(1)/50, -1);
BW2 = bwareaopen(BW, threshvalue);

strelcalc = round(sqrt(BWsizeacross)/8);

se = strel('sphere',strelcalc);

BW3 = imerode(BW2, se);
BW4 = imdilate(BW3, se);
%figure
%imshowpair(im1, BW3, 'montage')

% Showing all images in one figure
subplot(2,2,1), imshow(im1);
subplot(2,2,2), imshow(BW);
subplot(2,2,3), imshow(BW3);
subplot(2,2,4), imshow(BW4);

% imdilate, imerode, open, close
