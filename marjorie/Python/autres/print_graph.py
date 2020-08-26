# -*- coding: utf-8 -*-
"""
Created on Mon Sep 30 15:18:35 2019

@author: Marjorie
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy.random as random
import numpy as np

if len( sys.argv ) != 3:
    print('Usage: {} {} {}'.format(sys.argv[0], "MHT_csv", "persons_csv"))
    sys.exit()
    
df_MHT = pd.read_csv(sys.argv[1], sep=';')
df_persons = pd.read_csv(sys.argv[2], sep=';')

# number of activities per person
val = 0
nb_activities = []
for index, row in df_persons.iterrows():
    if row['total activity in'] > row['total activity out']:
        val = row['total activity in']
    else:
        val = row['total activity out']
    val += row['total activity inout']
    nb_activities.append(val)

# number of lines per person
df_MHT = df_MHT.groupby(['numTag']).size().reset_index(name='line counts')
df_MHT.drop( df_MHT[ df_MHT['numTag']==0 ].index, inplace=True )
df_MHT = df_MHT.reset_index(drop=True)

# add the number of activities per person to our dataframe
new_col = pd.Series(nb_activities)
df_MHT['total activities'] = new_col.values

"""
# scatter plot without fit line
fig = plt.figure(figsize=(16,15))
ax = df_MHT.plot.scatter(x='line counts', y='total activities')
#ax.legend(["soignants"])
plt.show()
plt.clf()
"""

# scatter plot with fit line
fig = plt.figure(figsize=(10,6))
ax = sns.regplot(df_MHT['line counts'], df_MHT['total activities'], ci=None)
plt.ylim(0, 8000)
plt.xlim(0, 160000)
plt.show()
plt.clf()

# residual
fig = plt.figure(figsize=(10,6))
ax = sns.residplot(df_MHT['line counts'], df_MHT['total activities'], scatter_kws={"s": 80})
plt.show()
plt.clf()


"""
# boxplot
fig = plt.figure(figsize=(5,6))
ax = sns.boxplot(df_MHT["line counts"], orient="v", palette="Set3")
plt.show()
plt.clf()

fig = plt.figure(figsize=(5,6))
ax = sns.boxplot(df_MHT["total activities"], orient="v", palette="Set3")
plt.show()
plt.clf()
"""
"""

# qq plot
df_MHT = df_MHT['total activities'].values.flatten()
df_MHT.sort()
norm=random.normal(0,2,len(df_MHT))
norm.sort()
plt.figure(figsize=(12,8),facecolor='1.0') 
plt.plot(norm,df_MHT,"o")
#generate a trend line
z = np.polyfit(norm,df_MHT, 1)
p = np.poly1d(z)
plt.plot(norm,p(norm),"k--", linewidth=2)
plt.title("Normal Q-Q plot")
plt.xlabel("Theoretical quantiles")
plt.ylabel("Expreimental quantiles")
plt.tick_params()
plt.show()




percs = np.linspace(0,100,21)
qn_a = np.percentile(df_MHT['total activities'], percs)
qn_b = np.percentile(df_MHT['line counts'], percs)
plt.plot(qn_a,qn_b, ls="", marker="o")
x = np.linspace(np.min((qn_a.min(),qn_b.min())), np.max((qn_a.max(),qn_b.max())))
plt.plot(x,x, color="k", ls="--")
plt.show()
"""

import statsmodels.api as sm
df_MHT_list = df_MHT['total activities'].to_numpy()
df_MHT_list.sort()
print(df_MHT_list)
sm.qqplot(df_MHT_list)




