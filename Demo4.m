% header
clear, clc, close all

%% image processing

imgArray = imread('F25_CP_B1.bmp');

disp("Click on the baby metroid to get color information.");

babyRGB = ColorPicker(imgArray);
[centroidRow, centroidCol, newImage] = FindTargetCentroid(imgArray, babyRGB);
%centroidRow;
%centroidCol;
image(newImage);

[centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imgArray, babyRGB);
centroidRowVec;
centroidColVec;
figure(3)
image(imageArray);
hold on;
plot(centroidColVec, centroidRowVec, "wx");
drawnow
stripeNum = centroidRowVec / 10;
[stripeNum, index] = sort(stripeNum, "descend")
xTargetM = (450 + centroidColVec) / 1000;
xTargetM = circshift(xTargetM(index),1);
stripeNum = circshift(stripeNum, 1);









%% serial communication setup
RomeoCOM = serialport('COM5',115200);
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
    % must have these functions in same folder as script:
        % CloseKeyListener.p
        % GetLastKey.p
        % OnClose.p
        % OnKeyPress.p
        % StartKeyListener.p
StartKeyListener;

while(1)
    % key press detection
    key = GetLastKey;
    pause(1/6000) % seconds
    if key == 'q'
        break
    elseif key ~= char(0)
        disp('MATLAB: Sending letter to Arduino')
        write(RomeoCOM,key,"char")
        
    end

%     % serial communication
    if RomeoCOM.NumBytesAvailable > 0
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        % if Arduino sends special done message, break out of the scanning
        % loop
        if strcmp(message, endCheck)
            break
            % if Arduino sends special ready for data message, send data
            % and receive messages back.
        elseif strcmp(message,dataCheck)
            disp("MATLAB: Sending data to Romeo");
            for target = 1:6
            out1 = sprintf("%d", stripeNum(target));
            writeline(RomeoCOM, out1);
            out2 = sprintf('%.3f', xTargetM(target));
            writeline(RomeoCOM, out2);
            message = readline(RomeoCOM);
            message = erase(message,sprintf('\r'));
            disp(message);
            end
                   
        else
            disp(message);

        end
    end
end
    
CloseKeyListener;
clear RomeoCOM
