% SHA DATA from Cpp algorithm

clear all
close all
clc

% Set environment variable to UTF8
feature('DefaultCharacterSet','UTF-8');


%% Read tables

%%%%%%%%%%
% raw data 
%%%%%%%%%%

filename = "MHT_2018.csv"
fullfilename = ".." + filesep + "rawdata" + filesep + "Files" + filesep + filename;

opts = delimitedTextImportOptions("NumVariables", 11);

% Specify range and delimiter
opts.DataLines = [2, Inf];
opts.Delimiter = ";";

% Specify column names and types
opts.VariableNames = ["ID", "numTag", "TypeEvenementId", "temps", "AppareilId", "NumAppareil", "CodeEvenement", "NumSHA", "NumAntenne", "Personnel_ID", "tempsImport"];
opts.VariableTypes = ["double", "double", "double", "datetime", "double", "double", "double", "double", "double", "double", "datetime"];

% Specify file level properties
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Specify variable properties
opts = setvaropts(opts, "temps", "InputFormat", "yyyy-MM-dd HH:mm:ss.SSS");
opts = setvaropts(opts, "tempsImport", "InputFormat", "yyyy-MM-dd HH:mm:ss.SSS");

opts.Encoding = "UTF-8";

% Import the data
MHT2018 = readtable("/Users/stephane/Documents/GITHUB/handwash/rawdata/MHT_2018.csv", opts);
clear opts


%%%%%%%%%%%%%%
% activity csv
%%%%%%%%%%%%%%

filename = "activities_2018.csv"
fullfilename = ".." + filesep + "marjorie" + filesep + "Files" + filesep + filename;

opts = delimitedTextImportOptions("NumVariables", 14);

% Specify range and delimiter
opts.DataLines = [2, Inf];
opts.Delimiter = ";";

% Specify column names and types
opts.VariableNames = ["uniqueID", "puceID", "roomID", "activityID", "abort", "statut", "starttime", "endtime", "duration", "alarm", "SHA", "SHAduringalarm", "SHAwithin30sec", "label"];
opts.VariableTypes = ["double", "double", "double", "double", "categorical", "categorical", "datetime", "datetime", "double", "double", "double", "double", "double", "categorical"];

% Specify file level properties
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Specify variable properties
opts = setvaropts(opts, ["abort", "statut", "label"], "EmptyFieldRule", "auto");
opts = setvaropts(opts, "starttime", "InputFormat", "yyyy-MM-dd HH:mm:ss.SSS");
opts = setvaropts(opts, "endtime", "InputFormat", "yyyy-MM-dd HH:mm:ss.SSS");

opts.Encoding = "UTF-8";

% Import the data
activities2018 = readtable(fullfilename, opts);
clear opts

%% FIGURES FOR METHOD
clc
close all

% figure nb event / nb activity by room
t1 = tabulate(MHT2018.NumAppareil);
t2 = tabulate(activities2018.roomID);

ind_in = t1(:,2) | t2(:,2);

figure;
subplot(1,2,1);
bar([t1(ind_in,2), t2(ind_in,2)]);
xlabel('Room');
ylabel('Count');
title('Nb event 2018');
legend({'MHT'; 'Activity'})

subplot(1,2,2);
bar([t1(ind_in,3), t2(ind_in,3)]);
xlabel('Room');
ylabel('Percent');
title('% event 2018')
legend({'MHT'; 'Activity'})



% figure nb event / nb activity by person

x = MHT2018.numTag;
x(x < 9 | x > 1000) = [];
xtab = tabulate(x);

y = activities2018.puceID;
y(y < 9 | y > 1000) = [];
ytab = tabulate(y);
ind_in = xtab(:,2) | ytab(:,2);

[R,P,RL,RU] = corrcoef(xtab(ind_in,3), ytab(ind_in,3))

figure;
subplot(1,2,1);
plot(xtab(ind_in,2), ytab(ind_in,2), 'r*');
xlabel('Nb event');
ylabel('Nb activity');
title('Correspondance per person');

subplot(1,2,2);
plot(xtab(ind_in,3), ytab(ind_in,3), 'b*');
hold on;
%plot([min(xtab(ind_in,3)) max(xtab(ind_in,3))], [min(ytab(ind_in,3)) max(ytab(ind_in,3))])
plot([0 8], [0 8]);
xlabel('% event');
ylabel('% activity');
title(['Correspondance per person, R=' num2str(R(1,2), 4)]);


% figure nb of event per person
caty = categorical(y);
figure;
histogram(caty);
title(['Nb of activity per person']);
ylabel('Count');

ind_in_person = find(ytab(:,2) > 200); % 200 activity IN & OUT
ID200 = ytab(ind_in_person,1);
caty = categorical(y(ismember(y, ID200)));
figure;
histogram(caty);
title(['Nb of activity per person >200 (N=58)']);
ylabel('Count');



% question: y'a t il des comportement qui ne sont pas conanoique et sont
% plus exclu que d'autre? --> representativit� de l'echantillon
% analyse des abandons par personne, par piece dans activites

% pourcentage d'abandon par personne
t = activities2018(:,{'puceID', 'abort','statut','starttime', 'endtime','activityID', 'SHA', 'SHAwithin30sec'});

t = t(~contains(string(t.statut), 'inout'),:); % take only IN and OUT (not INOUT)
t = t(ismember(t.puceID, ID200), :); % take only ID with more than 200 activity
t.valid = double(t.abort == "valide");

valid_per_person = grpstats(t, {'puceID'}, 'mean', 'DataVars',{'valid'})

figure;
subplot(1,2,1);
boxplot(valid_per_person.mean_valid);
title('Percent of valid activities, N=58');

subplot(1,2,2);
plot(valid_per_person.GroupCount, valid_per_person.mean_valid, 'r*');
xlabel('Nb activity');
ylabel('Percent valid');
title('Valid activities');



% pourcentage d'abandon par piece
tr = activities2018(:,{'roomID', 'abort','statut'});

yr = activities2018.roomID;
yr(yr > 20) = [];
yrtab = tabulate(yr);


tr = tr(~contains(string(tr.statut), 'inout'),:); % take only IN and OUT (not INOUT)
tr = tr(tr.roomID<=20, :); % take only roomID with more than 200 activity
tr.valid = double(tr.abort == "valide");

valid_per_room = grpstats(tr, {'roomID'}, 'mean', 'DataVars',{'valid'})

figure;
subplot(1,2,1);
boxplot(valid_per_room.mean_valid);
title('Percent of valid activities, N=20 (room)');

subplot(1,2,2);
plot(valid_per_room.GroupCount, valid_per_room.mean_valid, 'r*');
xlabel('Nb activity');
ylabel('Percent valid');
title('Valid activities');



% question: un out est-il vraiment un out?
% --> pourcentage d'activit� tagu�e IN et OUT, mais entrecoup� d'une
% pr�sence dans une autre pi�ce.
% deja cod� dans raison d'abandon (activite entremelee)
t.entrem = double(t.abort == "activite entremelee");
entrem_per_person = grpstats(t, {'puceID'}, 'mean', 'DataVars',{'entrem'})

figure;
subplot(1,2,1);
boxplot(entrem_per_person.mean_entrem);
title('Percent of interlock activities, N=58');

subplot(1,2,2);
plot(entrem_per_person.GroupCount, entrem_per_person.mean_entrem, 'r*');
xlabel('Nb activity');
ylabel('Percent interlock');
title('Interlock activities');



% histogramme des dur�e + regarder les gigantesque a quoi elles
% correspondent

t_in = t(t.statut == "in",:);
t_out = t(t.statut == "out",:);
ind_out = t_in.abort ~= "valide" | t_out.abort ~= "valide";
t_in(ind_out,:) = [];
t_out(ind_out,:) = [];
isequal(t_in.activityID , t_out.activityID)

t_in.duration = t_out.endtime - t_in.starttime;


figure;
subplot(1,2,1);
histogram(t_in.duration);
xlabel('Duration in HMS');
title('Duree activite IN + OUT');
subplot(1,2,2);
histogram(seconds(t_in.duration(seconds(t_in.duration) < 200 )))
xlabel('Duration in seconds');

% verifier les 2 types de soins (cour: infirmier), long aide-soignat:
% analyse des dur�e par tag


figure;
boxplot(seconds(t_in.duration), t_in.puceID, 'PlotStyle', 'compact')
title('Boxplot duree par personne');
xlabel('in seconds');

%% FIGURES FOR SCIENCE

mIN_SHA = grpstats(t_in, {'puceID'}, 'mean', 'DataVars', {'SHA'});
mOUT_SHA = grpstats(t_out, {'puceID'}, 'mean', 'DataVars', {'SHA'});

isequal(mIN_SHA.puceID, mOUT_SHA.puceID )

figure;
plot(mIN_SHA.mean_SHA, mOUT_SHA.mean_SHA, 'r*');
hold on;
plot([0 1], [0 1]);
xlabel('% SHA IN');
ylabel('% SHA OUT');
title(['SHA IN Vs. SHA OUT']);


























