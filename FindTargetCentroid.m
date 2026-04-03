function [centroidRow, centroidCol, modImage] = FindTargetCentroid(RGBImage, colorKey)
 testImage = RGBImage;
% redLayer = testImage(:,:,1);
% greenLayer = testImage(:,:,2);
% blueLayer = testImage(:,:,3);

remainder = rem(colorKey(1), 2);

switch remainder
    case 0
     logArray3D = rem(RGBImage,2) == 0;
    case 1
    logArray3D = rem(RGBImage,2) == 1;
end

logSum = sum(logArray3D, 3);

logArray = logSum == 2;


[matchRows, matchCols] = find(logArray == 1);
firstMatchRow = matchRows(1);
firstMatchCol = matchCols(1);
[rows, cols, colors] = size(testImage);
for c = firstMatchCol:cols
   if logArray(firstMatchRow, c+1) == 0
       break
   end
end

lastMatchCol = c;

for r = firstMatchRow:rows
   if logArray(r+1, firstMatchCol) == 0
       break
   end
end
lastMatchRow = r;

centroidRow = (firstMatchRow + lastMatchRow)/2;
centroidCol = (firstMatchCol + lastMatchCol)/2;

modImage = testImage;
modImage(firstMatchRow:lastMatchRow,firstMatchCol:lastMatchCol,:) = 99;

end