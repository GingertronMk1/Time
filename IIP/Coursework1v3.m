%im1 = imread(uigetfile('*.png'));
%im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
im1 = imread('plant223_rgb.png');

HSV = rgb2hsv(im1);

H=HSV(:,:,1);
S=HSV(:,:,2);
V=HSV(:,:,3);
range = (0.3 < H & H < 0.35);
H(range) = 255;
H(~range) = 0;
S(S < 0.5) = 0;

rangeHHSV = (0.3 < HSV(:,:,1) & H(:,:,1) < 0.35);
HSV(~rangeHHSV) = 0;

rangeSHSV = (HSV(:,:,2) < 0.5);

HSV(rangeHHSV) = 0;

subplot(2,2,1), imshow(im1);
subplot(2,2,2), imshow(H);
subplot(2,2,3), imshow(S);
subplot(2,2,4), imshow(V);