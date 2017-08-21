%get distinguishable colors
colors = distinguishable_colors(11);

%Style for consumption: sensing, processing & comms
moduleStyle={'-';'--';':';'.-'};
% moduleColor={[0 0 0];... %black
%            [0 0 1];... %blue           
%            [1 0 1];...  %pink
%            [178/255 1 100/255]}; %gray (collaborative processing)
moduleColor={colors(1,:);... 
            colors(2,:);... 
            colors(3,:);... 
            colors(4,:)}; 
moduleMark={'o';'*';'x';'^'};


%define color for cameras
% camColor(1,:) = [0 1 1];%cyan
% camColor(2,:) = [1 0.5 0];%orange
% camColor(3,:) = [0 1 0];%green
% camColor(4,:) = [1 0 0];%red
% camColor(5,:) = [1 1 0];%yellow
% camColor(6,:) = [75/255,0,130/255];%purple
% % camColor(7,:) = [1,1,1];%black
camColor = colors(5:11,:);


