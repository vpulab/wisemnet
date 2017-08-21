function res=load_data(fileDir)

%% READ DATA
filenames = getfilenames(fileDir,'*.res');
NFiles = size(filenames,2);
for f=1:NFiles 
    [PATHSTR,NAME,EXT] = fileparts(char (filenames(f)));
    res(f).path = [PATHSTR];
    res(f).filename = [NAME EXT];
    
    %read system data
    fileID = fopen( char (filenames(f)),'r');
    fgets(fileID);fgets(fileID);tline = fgets(fileID); %move to the line of the file with data to read
    A = sscanf(tline(2:end),'%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f');    
    res(f).nodeID=A(1);
    res(f).PRO.clockfreq=A(2); 
    res(f).PRO.clockfreqHost=A(3); 
    res(f).PRO.Voltage=A(4);
    res(f).SEN.FPSrea=A(5); %real FPS 
    res(f).SEN.FPSreq=A(6); 
    res(f).SEN.frameH=A(7); 
    res(f).SEN.frameW=A(8); 
    res(f).SEN.frame_resize=A(9);
    res(f).SEN.clockfreq=A(10); 
    res(f).SEN.Tframe=A(11); 
    res(f).SEN.Tact=A(12); res(f).SEN.Tidl=A(13); 
    res(f).SEN.Pact=A(14); res(f).SEN.Pidl=A(15); 
    res(f).PRO.Pact=A(16); res(f).PRO.Plea=A(17); res(f).PRO.Pidl=A(18); 
    res(f).COM.Pacttx=A(19); res(f).COM.Pactrx=A(20); res(f).COM.Pidl=A(21);
    
    %read tabular data
    [res(f).t_sim,res(f).frID,...
        res(f).SEN.eAct,res(f).SEN.eIdl,res(f).SEN.eTot,...
        res(f).COM.DrpD,res(f).COM.nDet,res(f).COM.TXraw,res(f).COM.TXreq, res(f).COM.TXdone, res(f).COM.CompRatio,res(f).COM.RXdone...
        res(f).COM.eActTX,res(f).COM.eActRX,res(f).COM.eIdl,res(f).COM.eTot,...
        res(f).PRO.DrpP,res(f).PRO.TimeR,res(f).PRO.TimeS,res(f).PRO.TimeO, res(f).PRO.TimeC...
        res(f).PRO.eAct,res(f).PRO.eLea, res(f).PRO.eCol, res(f).PRO.eIdl, res(f).PRO.eTot] ...
        = textread(char (filenames(f)),'%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f','commentstyle','shell');    
end
