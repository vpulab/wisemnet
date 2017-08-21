function [ly lx lz]=plot_labels_axis(str,zlab,PROclk,SENfps_req)
rx = 0;
ry = 0;
if ~isempty(str)
    title(str);
end
set(gca,'YTick',PROclk, 'YTickLabel',PROclk/1e9,'XTick',SENfps_req, 'XTickLabel',SENfps_req)  % This automatically sets the XTickMode to manual.
%     set(gca,'YTick',1:numel(PROclk), 'YTickLabel',PROclk/1e9,'XTick',1:numel(SENfps_req), 'XTickLabel',SENfps_req);
lz=zlabel(zlab);
ly=ylabel('Processor Clock (GHz)');
set(ly,'Rotation',ry);
lx=xlabel('Sensing framerate (fps)');
set(lx,'Rotation',rx);

rx = 11;
ry = -18;
fntsize = 20;

ly=ylabel('Processor Clock (GHz)','FontSize', fntsize);
set(ly,'Rotation',ry);
lx=xlabel('Sensing framerate (fps)','FontSize', fntsize);
set(lx,'Rotation',rx);    
set(gca,'FontSize', fntsize);
end