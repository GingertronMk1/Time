im1 = imread(uigetfile('*.png'));
%im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
%im1 = imread('plant223_rgb.png');

imageSize=size(im1);
imageAvgDim=round((imageSize(1)+imageSize(2))/2);
seValue=round(sqrt(imageAvgDim/500));
SE=strel('sphere',seValue);
%bwThresh=round(imageAvgDim/5);

im1HSV=rgb2hsv(im1);
im1H=im1HSV(:,:,1);
im1H=binarizeAndProcess(im1H,SE);
im1S=im1HSV(:,:,2);
im1S=binarizeAndProcess(im1S,SE);
im1V=im1HSV(:,:,3);
im1V=binarizeAndProcess(im1V,SE);

im1R=im1(:,:,1);
im1G=im1(:,:,2);
im1B=im1(:,:,3);

im1ROnly=im1R-(im1G+im1B)/2;
im1GOnly=im1G-(im1B+im1R)/2;
im1BOnly=im1B-(im1R+im1G)/2;

im1ROnly=binarizeAndProcess(im1ROnly, SE);
im1GOnly=binarizeAndProcess(im1GOnly, SE);
im1BOnly=binarizeAndProcess(im1BOnly, SE);

im1GSubB=subtractImages(im1GOnly, im1BOnly);


figure;
%{
subplot(2,3,1), imshow(im1H);
subplot(2,3,2), imshow(im1S);
subplot(2,3,3), imshow(im1V);
subplot(2,3,4), imshow(im1ROnly);
subplot(2,3,5), imshow(im1GOnly);
subplot(2,3,6), imshow(im1BOnly);
%}
subplot(1,3,1), imshow(im1GOnly);
subplot(1,3,2), imshow(im1BOnly);
subplot(1,3,3), imshow(im1GSubB);

function ed = erodeDilate(image, value)       % Noise reduction
ed=imerode(image,value);
ed=imdilate(ed,value);
end

function imb = binarizeAndProcess(image, value)
imb=imbinarize(image);      % binarize and
imb=erodeDilate(imb, value);
end

function si = subtractImages(image1, image2)
si=image1-image2;
si(si<0)=0;
end
