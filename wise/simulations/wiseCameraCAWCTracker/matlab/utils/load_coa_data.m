function [runs coaData]=load_coa_data(fileDir)

%% READ DATA
filenames = getfilenames(fileDir,'*.coa');
NFiles = size(filenames,2);

 h = waitbar(0,'Loading coalition data');
 
for f=1:NFiles      
    fprintf('Processing file %s...\n',char (filenames(f)));
    fID = fopen( char (filenames(f)),'r');    

    t = 1;    
    tline = fgets(fID); run = sscanf(tline,'run=%d');
    tline = fgets(fID); 
    while ischar(tline)
        
         frameID = sscanf(tline,'frameID=%d');        
         tline = fgets(fID); man = sscanf(tline,'manager=%d');    
             
         %negotiation set
         tline = fgets(fID); C = strsplit(tline(7:end-2),', ');
         nego = str2double(C); 

         %coalition set
         tline = fgets(fID); C = strsplit(tline(6:end-2),', ');     
         cam = str2double(C); 

         %utilities
         tline = fgets(fID); C = strsplit(tline(4:end-2),',');     
         u = str2double(C); 

         %utility coalition
         tline = fgets(fID); C = strsplit(tline(6:end),',');     
         ucoa = str2double(C); 

         %batery
         tline = fgets(fID); C = strsplit(tline(4:end-2),',');     
         b = str2double(C); 

         %load
         tline = fgets(fID); C = strsplit(tline(4:end-2),',');     
         l = str2double(C); 

         %tx/rx
         tline = fgets(fID); C = strsplit(tline(5:end-2),',');     
         tx = str2double(C);     
         tline = fgets(fID); C = strsplit(tline(5:end-2),',');     
         rx = str2double(C);

         %x/P
         tline = fgets(fID); C = strsplit(tline(4:end-2),',');     
         x = str2double(C);
         tline = fgets(fID); C = strsplit(tline(4:end-2),',');     
         P = str2double(C);

         data(t).frameID = frameID;
         data(t).man = man;
         data(t).nego = {nego};
         data(t).cam = {cam};
         data(t).b = {b};
         data(t).l = {l};
         data(t).u = {u};
         data(t).ucoa = ucoa;
         data(t).tx = {tx};
         data(t).rx = {rx};
         data(t).x = {x};
         data(t).P = {P};

         t = t + 1;
         tline = fgets(fID); 
    end
    
    [PATHSTR,NAME,EXT] = fileparts(char (filenames(f)));    
    coaData(f)=struct('run',run,'path',PATHSTR,'file',[NAME EXT],'data',data);
    clear data;
    runs(f) = run;
    fclose(fID);
    waitbar(f/NFiles);
end
close(h);