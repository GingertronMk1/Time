%im1 = imread(uigetfile('*.png'));
im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
%im1 = imread('plant223_rgb.png');

imageSize=size(im1);
imageAvgDim=(imageSize(1)+imageSize(2))/2;
seValue=round(sqrt(imageAvgDim/500));
SE=strel('sphere',seValue);

im1Redness=im1(:,:,1)-(im1(:,:,3)+im1(:,:,2))/2;
im1Greenness=im1(:,:,2)-(im1(:,:,1)+im1(:,:,3))/2;
im1Blueness=im1(:,:,3)-(im1(:,:,2)+im1(:,:,1))/2;

im1GreenBin=binarizeandprocess(im1Greenness, SE);
im1GreenCircles=bwareaopen(im1Fin,2*imageAvgDim);

im1RedBin=binarizeandprocess(im1Redness, SE);

im1GreenSubRed=im1GreenBin-im1RedBin;

subplot(2,2,1), imshow(im1Greenness);
subplot(2,2,2), imshow(im1RedBin);
subplot(2,2,3), imshow(im1Blueness);
subplot(2,2,4), imshow(im1GreenSubRed);

function imb = binarizeandprocess(image, value)
  imb=imbinarize(image);      % binarize and
  imb=imerode(imb,value);     % noise reduce via
  imb=imdilate(imb,value);    % erosion and dilation
end
