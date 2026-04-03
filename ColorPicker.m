function [RGBVector] = ColorPicker(imageArray)
%   Returns a vector containing the R, G, and B values of a pixel selected
%   by the user.
%   ImageArray = RGB image array.
%   RGBVector = Vector containing the R, G, and B values of the selected
%   pixel.
%%%

%   Call image to display the image
image(imageArray);
%   Call ginput to allow the user to select the pixel of interest
[y,x] = ginput(1);
%   Call round to round the resulting x (column) and y (row) values 
%   to the nearest integer so that you can use them to index the image array
xRound = round(x);
yRound = round(y);
%   Index out the R, G and B values of the selected pixel and assign them to the output vector
RGBVector(1) = imageArray(xRound, yRound, 1);
RGBVector(2) = imageArray(xRound, yRound, 2);
RGBVector(3) = imageArray(xRound, yRound, 3);




end
