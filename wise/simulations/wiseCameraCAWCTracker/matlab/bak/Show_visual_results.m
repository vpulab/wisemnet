clc
clear all
close all
% 
addpath('./utils');
% 
% %% load camera results
dataDir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/res_S_t09_5s_r50_f4';
[cams.track,ids,cids]=load_cams_data(dataDir);

%% load camera videos
scenario='pets2009';
configuration;

for i=config.selCams    
    v{i} = VideoReader([config.datasetDir config.vidFile{i}]);
end

%% load frame to visualize
frame_to_view = 21;
gtruth = [380 178 20 73;...
         -1 -1 -1 -1;...
         -1 -1 -1 -1;...
         430 260 24 75;...
         290 160 40 165;...
         155 100 30 140;...
         430 115 40 140;...
         485 110 45 195];

for i=config.selCams    
    f(i)=0;
    while hasFrame(v{i}) && f(i)<=frame_to_view
        frame{i} = readFrame(v{i});
        f(i)=f(i)+1;
    end
end

%load example results
sel_runs=[1 150 250 ]; %selected runs for 5, 15 & 25fps
fps(1)=5;
fps(150)=15;
fps(250)=25;

%% plot frame to visualize
CamID = [cams.track{1,1}.camID cams.track{2,1}.camID cams.track{3,1}.camID cams.track{4,1}.camID cams.track{5,1}.camID cams.track{6,1}.camID];
config.selCams = [1    4     5     6     7     8];
% config.selCams = [1    6     7     8];
for r=sel_runs
    %figure('Name',cams.track{1,r}.filename, 'Position',[100 100 500 750]);
    %fig1=figure('Name',cams.track{1,r}.filename, 'Position',[100 100 225 1100]);
%     fig1=figure('Name',cams.track{1,r}.filename, 'Position',[100 100 225 750]);
    fig1=figure('Name',cams.track{1,r}.filename, 'Position',[100 100 1200 150]);

    k=1;
    
    d=0.00; %distance between images
    for i=config.selCams    
        id = find(i==CamID);        
        
        %subplot_tight(ceil(numel(config.selCams)/2), 2, k);    
        %subplot_tight(numel(config.selCams), 1, k);    
        subplot_tight(1, numel(config.selCams), k);    
        imshow(imresize(frame{i}, [576 720]));
        rectangle('Position',gtruth(i,:),'EdgeColor','b');

                
        hold on;  
        ind =[];
        frame_to_view_ = frame_to_view;
        while isempty(ind)
            ind = find(cams.track{id,r}.frID == frame_to_view_);
            frame_to_view_ = frame_to_view_ + 1;
        end
        x = cams.track{id,r}.X0i(ind);
        y = cams.track{id,r}.Y0i(ind);
        w = cams.track{id,r}.Wi(ind);
        h = cams.track{id,r}.Hi(ind);
        pos = [x-w/2 y-h/2 w h];
        
        %rectangle('Position',pos,'EdgeColor','b');
        rectangle('Position',pos,'EdgeColor','g','LineStyle','-');
        
        %hnd1=text(5,25,sprintf('Cam%d',i));
        %set(hnd1,'FontSize',12,'Color',[1 0 0]);%blue
        hnd1=text(5,25,sprintf('Cam%d',k));
        set(hnd1,'FontSize',12,'Color',[1 0 0]);%green    
        k=k+1;
    end
    
    epsfig = hgexport('factorystyle');
    epsfig.Format = 'eps';
    hgexport(gcf,sprintf('figs/Visuals_%d.eps',fps(r)),epsfig,'Format','eps')
%     print(gcf,'-depsc', sprintf('figs/Visuals_%d.eps',fps(r)));
%     saveas(fig1, sprintf('figs/Visuals_%d.eps',fps(r)),'epsc'); 
    saveas(fig1, sprintf('figs/Visuals_%d.fig',fps(r)));
end