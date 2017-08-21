function [res,ids,cids]=load_cams_consumption(fileDir)

%% READ DATA
h = waitbar(0,'Loading camera consumption data');

Ncams=0;
for c=0:10
    if size(getfilenames(fileDir,sprintf('*.res%03d',c)),2) > 0
        Ncams = Ncams + 1;
    end
end

for c=0:Ncams-1
    
    filenames = getfilenames(fileDir,sprintf('*.res%03d',c));
    NFiles = size(filenames,2);
    for f=1:NFiles 
        fprintf('Processing file %s...\n',char (filenames(f)));
        [PATHSTR,NAME,EXT] = fileparts(char (filenames(f)));
        data.path = [PATHSTR];
        data.filename = [NAME EXT];

        %open file
        fileID = fopen( char (filenames(f)),'r');
        
        %read system data            
        fgets(fileID);fgets(fileID); tline = fgets(fileID); %move to the line of the file with data to read
        A = sscanf(tline(2:end),'%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f');    
        data.run=A(1);
        data.nodeID=A(2);
        data.camID=A(3);
        data.PRO.clockfreq=A(4); 
        data.PRO.clockfreqHost=A(5); 
        data.PRO.Voltage=A(6);
        data.SEN.FPSrea=A(7); %real FPS 
        data.SEN.FPSreq=A(8); 
        data.SEN.frameH=A(9); 
        data.SEN.frameW=A(10); 
        data.SEN.frame_resize=A(11);
        data.SEN.clockfreq=A(12); 
        data.SEN.Tframe=A(13); 
        data.PRO.optF=A(14); 
        data.SEN.Tact=A(15); data.SEN.Tidl=A(16); 
        data.SEN.Pact=A(17); data.SEN.Pidl=A(18); 
        data.PRO.Pact=A(19); data.PRO.Plea=A(20); data.PRO.Pidl=A(21); 
        data.COM.Pacttx=A(22); data.COM.Pactrx=A(23); data.COM.Pidl=A(24);

        %read tabular data
        [data.t_sim,data.frID,...
            data.SEN.eAct,data.SEN.eIdl,...
            data.COM.DrpD,data.COM.TXraw,data.COM.TXreq, data.COM.TXdone,data.COM.RXdone...
            data.COM.eActTX,data.COM.eActRX,data.COM.eIdl,...
            data.PRO.DrpP,data.PRO.TimeR,data.PRO.TimeS,data.PRO.TimeO, data.PRO.TimeC...
            data.PRO.eAct,data.PRO.eLea, data.PRO.eCol, data.PRO.eIdl] ...
            = textread(char (filenames(f)),'%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f','commentstyle','shell');    
        
        res{c+1,f} = data;
        clear data;
        fclose(fileID);
    end
    h=waitbar((c+1)/Ncams);            
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