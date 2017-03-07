im1 = imread(uigetfile('*.png'));
%im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
%im1 = imread('plant223_rgb.png');

imageSize=size(im1);
imageAvgDim=round((imageSize(1)+imageSize(2))/2);
seValue=round(sqrt(imageAvgDim/500));
SE=strel('sphere',seValue);
%bwThresh=round(imageAvgDim/5);

im1Greenness=im1(:,:,2)-(im1(:,:,1)+im1(:,:,3))/2;

im1GreenBin=binarizeAndProcess(im1Greenness, SE);

CC=bwconncomp(im1GreenBin);
im1GreenBinSub=im1GreenBin;
numPixels = cellfun(@numel,CC.PixelIdxList);
[biggest,idx] = max(numPixels);
im1GreenBinSub(CC.PixelIdxList{idx}) = 0;
im1Fin=subtractImages(im1GreenBin,im1GreenBinSub);
imdilate(im1Fin, SE);
imshowpair(im1, im1Fin, 'blend');

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
