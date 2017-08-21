function filenames = getfilenames(root,refiles)
%---Returns a cell array of all files matching the wildcard expression
%---"refiles" beginning in the root folder "root". Includes subdirectories
%---Example: mfiles = getfilenames('c:\','*.m') will return all .m files
%---on the c drive to the cell array "mfiles". 

%---Note: Never tested on a Unix Box. 

%---Joe Burgel, General Motors, 8/2002

MyPwd = cd; %---We will come back here when we're done
filesep = '/'; %---Set up for windows. Change this for Unix
filenames = {};

try, 
    cd(root);
catch,
    return;
end

% AllFiles = dir('*.*'); %--Everything in this folder
% if strcmp(computer, 'GLNXA64') == 1
%     AllFiles = ls;
%     eval (sprintf('MyFiles = ls(''%s'')',refiles)); %--The files we need in this fol
% else
    AllFiles = dir;
    MyFiles = dir(refiles); %--The files we need in this folder
% end

%---Build a list of all the files matching the regular expression in this folder
for k=1:length(MyFiles)
    filenames{k} = [cd filesep MyFiles(k).name];
end


%---Do a recursive call of this function for every sub directory of this folder
SkipFolder1 = [cd filesep '.'];
SkipFolder2 = [cd filesep '..'];
for k=1:length(AllFiles)
    if AllFiles(k).isdir
        ThisFolder = [cd filesep AllFiles(k).name];
        if ~(strcmp(ThisFolder,SkipFolder1)|strcmp(ThisFolder,SkipFolder2))
            cd(MyPwd);%go to the initial folder for calling the 'getfilenames' function
            filenames = [filenames  ...
                    getfilenames(ThisFolder,refiles)];
            cd(root);%go to the root folder for reading the files
        end
    end
    
end

%---Return to the present directory
cd(MyPwd);
