# -*- coding: utf-8 -*-
"""
Created on Fri Oct  4 16:45:13 2019

@author: Marjorie
"""

import pandas as pd
import sys


outputDatasetName = sys.argv[2]

df = pd.read_csv(sys.argv[1], sep=';')
print(df.columns)
df = df.drop(['Unnamed: 60'], axis=1)
print(df.columns)

df.to_excel(outputDatasetName, index=False, na_rep='')