im1 = imread(uigetfile('*.png'));

imageSize=size(im1);
imageAvgDim=round((imageSize(1)+imageSize(2))/2);
seValue=round(sqrt(imageAvgDim/500));
SE=strel('sphere',seValue);

im1Greenness=im1(:,:,2)-(im1(:,:,1)+im1(:,:,3))/2;
im1Blueness=im1(:,:,3)-(im1(:,:,2)+im1(:,:,1))/2;

im1GreenBin=binarizeAndProcess(im1Greenness, SE);
im1BlueBin=binarizeAndProcess(im1Blueness, SE);
im1BlueBin=imdilate(im1BlueBin, SE);

im1GSB=subtractImages(im1GreenBin, im1BlueBin);
im1GSB=erodeDilate(im1GSB, SE);

CC=bwconncomp(im1GSB);
im1GreenBinSub=im1GSB;
numPixels = cellfun(@numel,CC.PixelIdxList);
[biggest,idx] = max(numPixels);
im1GreenBinSub(CC.PixelIdxList{idx}) = 0;

im1Fin=subtractImages(im1GSB,im1GreenBinSub);
im1Fin=imdilate(im1Fin, SE);

figure;

imwrite(im1Fin, 'Screenshots/im1Fin.png');
imshow(im1Fin);

function ed = erodeDilate(image, value)       % Noise reduction
  ed=imerode(image,value);
  ed=imdilate(ed,value);
end

function imb = binarizeAndProcess(image, value)
  imb=imbinarize(image);        % binarize and
  imb=erodeDilate(imb, value);  % noise reduce
end

function si = subtractImages(image1, image2)
  si=image1-image2;
  si(si<0)=0;
end
