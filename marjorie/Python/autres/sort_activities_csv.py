# -*- coding: utf-8 -*-
"""
Created on Tue Oct  1 16:35:01 2019

@author: Marjorie
"""

import pandas as pd
import sys

if len(sys.argv) != 2 :
    print("Usage : {} {}".format( sys.argv[0], "data_csv_file" ))
    sys.exit()

if '/' in sys.argv[1]:
    filename = sys.argv[1].split('/')
    name = filename[-1]
else:
    name = sys.argv[1]

output_filename = 'sort_'+name
df = pd.read_csv(sys.argv[1], sep=';')
print("reading ", name, "...")
df = df.sort_values(by=['puce ID', 'start time'])
df.to_csv(output_filename, index=False, header=True, sep=";")
print(output_filename, " finish")