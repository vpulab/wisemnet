function [Ncams,Nruns,PROclk,SENclk,optFactor,SENfps_req,SENfps_rea,comparedFrames] = preprocess_data(cams)

%Number of cameras & runs
Ncams = size(cams.usage,1);
Nruns = size(cams.usage,2);

%get the test variables (frequencies)
PROclk=[]; SENclk = []; SENfps_rea = []; SENfps_req = [];simTime=0;
optFactor=[];
for c=1:size(cams.usage,1)
    for r=1:size(cams.usage,2)
        simTime = max([simTime cams.usage{c,r}.t_sim']);
        PROclk = [PROclk cams.usage{c,r}.PRO.clockfreq];
        SENclk = [SENclk cams.usage{c,r}.SEN.clockfreq];
        SENfps_rea = [SENfps_rea cams.usage{c,r}.SEN.FPSrea];
        SENfps_req = [SENfps_req cams.usage{c,r}.SEN.FPSreq];
        ind =find (cams.usage{c,r}.PRO.TimeS > 0);
        %val = round(median(cams.usage{c,r}.PRO.TimeS(ind)./cams.usage{c,r}.PRO.TimeO(ind)),3);
        optFactor = [optFactor cams.usage{c,r}.PRO.optF];        
    end
end

PROclk = sort(unique(PROclk), 'ascend');
optFactor = sort(unique(optFactor), 'ascend');
SENclk = sort(unique(SENclk), 'ascend');
SENfps_req = sort(unique(SENfps_req), 'ascend');
SENfps_rea = sort(unique(SENfps_rea), 'ascend');

%select the frames where performance is compared
count_comparedFrames=zeros(1,round(simTime)*25);
%(frames available in all configurations)
if any(strcmp('track',fieldnames(cams))) == 1    
    for c=1:Ncams
        for r=1:Nruns
            for f=1:numel(cams.track{c,r}.frID)
                ind = cams.track{c,r}.frID(f);
                count_comparedFrames(ind) = count_comparedFrames(ind) + 1;
            end
        end
    end
end

th=0.70*Ncams*Nruns;
ind=find(count_comparedFrames>th);
comparedFrames = ind;