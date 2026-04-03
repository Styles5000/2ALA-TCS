% ME EN 1010, University of Utah
% Sample code for utilizing the Key Listener

clear, clc, close all

StartKeyListener;  % Open the Key Listener window

disp('Press letter keys (a–z) with the figure window active.');
disp('The last key will be shown in the figure and printed to the Command Window.');
disp('Press "q" to quit and close the figure.');
disp('If you close the figure manually, you will need to stop the script by clicking the Stop button or pressing Ctrl+C.')

while true
    pause(0.1);  % polling interval (seconds)
    key = GetLastKey;
    if key == 'q'
        % quit and close the figure window
        fprintf('User entered %c\n',key)
        CloseKeyListener;
        break;
    elseif key ~= char(0)
        % print the letter to the Command Window
        fprintf('User entered %c\n',key)
    end
end

% ME EN 1010, University of Utah



