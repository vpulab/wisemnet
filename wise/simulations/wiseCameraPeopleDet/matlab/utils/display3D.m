function display3D(c1,c2,c3, N,M,data,xticks,yticks,factorx,factory,title_str,zlabel_str,xlabel_str,ylabel_str)
rot_angle1 = 15;
rot_angle2 = 25;

subplot(c1,c2,c3);
mesh(N,M,data); axis tight;
set(gca,'XTick',xticks, 'XTickLabel',xticks/factorx,'YTick',yticks, 'YTickLabel',yticks/factory)  % This automatically sets the XTickMode to manual.
% title(title_str); zlabel(zlabel_str); xlabel(xlabel_str,'Rotation',15); ylabel(ylabel_str);
title(title_str); zlabel(zlabel_str); xlabel(xlabel_str,'Rotation',rot_angle1); ylabel(ylabel_str,'Rotation',-rot_angle2);
