# -*- coding: utf-8 -*-
"""
Created on Wed Oct  2 12:34:06 2019

@author: Marjorie
"""

import pandas as pd
import sys

if len(sys.argv) != 2 :
    print("Usage : {} {}".format( sys.argv[0], "activites_csv_file_sorted" ))
    sys.exit()
    
df = pd.read_csv(sys.argv[1], sep=';')
cpt_line = -1
id_act = 0
id_prec_act = 0
statut = ''
prec_statut = ''
error = 0

ok = True
id_supp = []
with open("log.txt", 'w', newline='') as output:
    for index, row in df.iterrows():
        cpt_line += 1
        id_act = row['activity ID']
        statut = row['statut']
        
        if statut != "inout" and statut != "in" and statut != "out":
            print("WARNING pas de in, out, inout (statut =", statut,") ligne ", cpt_line)
    
        if id_prec_act not in id_supp and id_prec_act != 0 and id_prec_act != id_act:
            if prec_statut=="in" or (prec_statut=="out" and statut=="out"):
                output.write("ERROR ligne "+ str(cpt_line)+ " statut prec act ["+ str(id_prec_act)+"] = "+\
                             prec_statut+ " statut actual act ["+ str(id_act)+"] = "+ statut+"\n")
                error += 1
                id_supp.append(id_prec_act)
            
        id_prec_act = id_act
        prec_statut = statut
    
    
    df_abandon = df[ df['activity ID'].isin(id_supp)]
    print("nb in abandon = ", len(df_abandon[  (df_abandon['statut']=="in") & (df_abandon["abandon"]!="valide")  ]))
    print("nb in = ", len(df_abandon[  (df_abandon['statut']=="in") & (df_abandon["abandon"]=="valide")  ]))
    print("nb out abandon = ", len(df_abandon[  (df_abandon['statut']=="out") & (df_abandon["abandon"]!="valide")  ]))
    print("nb out = ", len(df_abandon[  (df_abandon['statut']=="out") & (df_abandon["abandon"]=="valide")  ]))
    
    df.loc[ df['activity ID'].isin(id_supp), "abandon" ] = "activité entremêlée"
    output.write("nb errors: "+ str(error) +"\n\n")
    print("nb errors: ", error)
    print("len df = ", len(df))


print(len(df.loc[ df["abandon"] == "valide" ]))
df.to_csv("sorted_activities_2018_ok.csv", sep=";")