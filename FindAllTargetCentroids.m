function [centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray, colorKey)

for i = 1:6
   [centroidRowVec(i), centroidColVec(i), imageArray] = FindTargetCentroid(imageArray, colorKey);
end

end 