# -*- coding: utf-8 -*-
"""
Created on Fri May 10 09:13:36 2019

@author: Marjorie
"""

import csv
import pandas as pd
import numpy as np
import seaborn as sns
from matplotlib import pyplot as plt
import sys

""" DESCR:
    ID :
        Id of the entry
        
    numTag :
        Id of a puce (on the shoes) detecting different event 
        (enter a chamber, etc)
         
    TypeEvenementId :
        Id of an event (enter a chamber, exit a chamber, wash hands, etc)
        
    temps :
        Date of the saving
        
    AppareilId :
        Id of a chamber
        
    NumAppareil :
        ?
        
    CodeEvenement :
        Interpretation of the event
        
    NumSHA :
        Num of the hydroalcoolique 'box'
        SHA = Solution HydroAlcoolique
        
    NumAntenne :
        ?
        
    Personnel_ID :
        Idendify a person
        
    tempsImport :
        Date of the saving in the database
"""


if len(sys.argv) != 2 :
    print("Usage : {} {}".format( sys.argv[0], "data_csv_file" ))
    sys.exit()


df = pd.read_csv(sys.argv[1], sep=';')
df = df.sort_values(by=['AppareilId', 'temps'])
df.to_csv('sorting_MHT_Janvier_Octobre_2018.csv', index=False, header=False)

"""
# Split temps into date and heure 
dfSplit = pd.DataFrame(df['temps'].str.split(' ',1).tolist(),\
    columns = ['date','heure'])
df = pd.concat([df, dfSplit], axis=1)


# Just to print
df = df[ (df['date'] == '2018-04-14') & (df['AppareilId'] == 37) ]
df.drop(['temps','ID','NumSHA','NumAntenne'], axis=1, inplace=True)


df.to_csv('14_avril_per_chamber.csv', index=False, header=True)
"""