% SHA DATA from Cpp algorithm

clear all
close all
clc

% Set environment variable to UTF8
feature('DefaultCharacterSet','UTF-8');


%% Read table

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

%%

T = activities2018;

