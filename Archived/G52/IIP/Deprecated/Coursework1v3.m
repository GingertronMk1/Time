%im1 = imread(uigetfile('*.png'));
im1 = imread('plant001_rgb.png');
%im1 = imread('plant017_rgb.png');
%im1 = imread('plant223_rgb.png');

HSV=rgb2hsv(im1);

H=HSV(:,:,1);
S=HSV(:,:,2);
V=HSV(:,:,3);

imageSize=size(im1);
imageAvgDim=(imageSize(1)+imageSize(2))/2;
seValue=round(sqrt(imageAvgDim/20));

SE=strel('sphere',seValue);

H=imbinarize(H);%,'global');
S=imbinarize(S);%,'global');
V=imbinarize(V);%,'global');

H=erodeDilate(H,se);
S=erodeDilate(S,se);
V=erodeDilate(V,se);

HC=imcomplement(H);     % Inverts the binary image of H
SC=imcomplement(S);     % Inverts the binary image of S
VC=imcomplement(V);     % Inverts the binary image of V

VsubH=V-H;
HsubV=H-V;


subplot(2,3,1), imshow(H);
subplot(2,3,2), imshow(S);
subplot(2,3,3), imshow(V);
subplot(2,3,4), imshow(HC);
subplot(2,3,5), imshow(SC);
subplot(2,3,6), imshow(VC);
%subplot(2,3,4), imshow(VsubH);
%subplot(2,3,5), imshow(HsubV)

function ed = erodeDilate(image, value)       % Noise reduction
  ed=imerode(image,value);
  ed=imdilate(image,value);
end
