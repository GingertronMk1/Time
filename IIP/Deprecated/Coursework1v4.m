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
threshvalue = round(BWsizeacross(1)/50, -1);
BW2 = bwareaopen(BW, threshvalue);

strelcalc = round(sqrt(BWsizeacross)/8);

se = strel('sphere',strelcalc);

BW3 = imerode(BW2, se);
BW4 = imdilate(BW3, se);
%figure
%imshowpair(im1, BW3, 'montage')

HSV = rgb2hsv(im1);

H=HSV(:,:,1);
level = graythresh(H);
BW = im2bw(H, 0.3);
BW = imcomplement(BW);
range = (0.3 < H & H < 0.35);
H(range) = 255;
H(~range) = 0;

% Showing all images in one figure
imshowpair(H, BW4, 'montage')

% imdilate, imerode, open, close
