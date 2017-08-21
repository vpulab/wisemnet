function [res,ids,cids]=load_cams_data(fileDir)

%% READ data
h = waitbar(0,'Loading camera tracking data');

Ncams=0;
for c=0:10
    if size(getfilenames(fileDir,sprintf('*.dat%03d',c)),2) > 0
        Ncams = Ncams + 1;
    end
end

for c=0:Ncams-1    
    filenames = getfilenames(fileDir,sprintf('*.dat%03d',c));
    NFiles = size(filenames,2);
    for f=1:NFiles 
        fprintf('Processing file %s...\n',char (filenames(f)));
        [PATHSTR,NAME,EXT] = fileparts(char (filenames(f)));
        data.path = [PATHSTR];
        data.filename = [NAME EXT];

        %open file
         fID = fopen( char (filenames(f)),'r');
         
        %read system data        
         tline = fgets(fID); data.run = sscanf(tline,'#run=%d');   
         tline = fgets(fID); data.nodeID = sscanf(tline,'#nodeID=%d');   
         tline = fgets(fID); data.camID = sscanf(tline,'#camID=%d');   
         tline = fgets(fID); data.targetID = sscanf(tline,'#targetID=%d');
         tline = fgets(fID); data.sRows = sscanf(tline,'#scaleFactorRows=%f');
         tline = fgets(fID); data.sCols = sscanf(tline,'#scaleFactorCols=%f');

        %read tabular data
        [data.t_sim,data.frID,data.u,data.l,data.b,...
         data.Xi,data.Yi,data.Wi,data.Hi,data.X0i,data.Y0i,data.X0w,data.Y0w] ...
            = textread(char (filenames(f)),'%f %f %f %f %f %f %f %f %f %f %f %f %f','commentstyle','shell');    
        
        res{c+1,f} = data;
        clear data;
        fclose(fID);
    end
    waitbar((c+1)/Ncams);        
end
close(h);

%extract the IDs using only the first run (r=1)
ids = [];
for c=1:Ncams
    ids = [ids res{c,1}.nodeID];
end

cids = [];
for c=1:Ncams
    cids = [cids res{c,1}.camID];
end
