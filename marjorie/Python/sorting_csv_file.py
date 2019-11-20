# -*- coding: utf-8 -*-
"""
Created on Fri May 10 09:13:36 2019

@author: Marjorie
"""

import pandas as pd
import sys

if len(sys.argv) > 3 :
    print("Usage : {} {} {}".format( sys.argv[0], "data_csv_file", "[year to include]" ))
    sys.exit()

year_include = 0 
if len(sys.argv) == 3:
    year_include = sys.argv[2]

if '/' in sys.argv[1]:
    filename = sys.argv[1].split('/')
    name = filename[-1]
else:
    name = sys.argv[1]

name = name.replace(".csv","")

output_filename = name+'_sorted.csv'
df = pd.read_csv(sys.argv[1], sep=';')

if year_include != 0:
    print('year to include: ', year_include)
    df = df[df['temps'].str.contains(year_include)]

print("reading ", name, "...")

length2=len(df) 
df = df.sort_values(by=['NumAppareil', 'temps']).drop_duplicates(subset=['numTag', 
                   'TypeEvenementId', 'temps', 'NumAppareil', 'CodeEvenement'])
length3=len(df) 
df.to_csv(output_filename, index=False, header=True, sep=";")
print(length2, length3) 
print(output_filename, " finish")