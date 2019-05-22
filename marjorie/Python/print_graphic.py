# -*- coding: utf-8 -*-
"""
Created on Wed May 22 13:52:56 2019

@author: Marjorie
"""
import re
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec
from matplotlib.backends.backend_pdf import PdfPages
import pandas as pd

""" idée : tout mettre dans une dataframe puis afficher toutes les pies
https://stackoverflow.com/questions/34035427/conditional-removal-of-labels-in-matplotlib-pie-chart/34035864
    
import matplotlib.pyplot as plt
import numpy as np
np.random.seed(123456)
import pandas as pd


plt.style.use('ggplot')
colors = plt.rcParams['axes.color_cycle']

fig, axes = plt.subplots(nrows=2, ncols=3)
for ax in axes.flat:
    ax.axis('off')

for ax, col in zip(axes.flat, df.columns):
    ax.pie(df[col], labels=df.index, autopct='%.2f', colors=colors)
    ax.set(ylabel='', title=col, aspect='equal')

axes[0, 0].legend(bbox_to_anchor=(0, 0.5))

fig.savefig('your_file.png') # Or whichever format you'd like
plt.show()    
"""



column_in = []
column_out = []
column_inout = []
column_not_in = []
column_not_out = []
column_not_inout = []

pp = PdfPages('multipage.pdf')

def has_numbers(str_input):
    return bool(re.search(r'\d', str_input))


colors = ['yellowgreen', 'lightcoral']
labels = ['SHA taken', 'SHA not taken']
nb_puces = 0

with open("../Docs/output_persons_2018.txt", "r") as file:
    for line in file:
        line = line.rstrip('\n')
        
        if not line or line.isspace() or line[0] == '%'\
            or not has_numbers(line):
            continue

        nb_puces += 1
         
        #line="    0 |  67.63 |  69.74 |  43.92  |  -1.00 |  -1.00 |  -1.00  |    32.37   |    30.26   |    56.08  |"       
        line = line.split()
        puce = line[0]
        
        taken_sure_in = float(line[2])
        taken_sure_out = float(line[4])
        taken_sure_inout = float(line[6])
        
        not_taken_in = float(line[14])
        not_taken_out = float(line[16])
        not_taken_inout = float(line[18])
          
        """
        column_in.append(taken_sure_in)
        column_out.append(taken_sure_out)
        column_inout.append(taken_sure_inout)
        
        column_not_in.append(not_taken_in)
        column_not_out.append(not_taken_out)
        column_not_inout.append(not_taken_inout)
        """
        
        the_grid = GridSpec(1, 3)
        
        if taken_sure_in != -1:
            plt.subplot(the_grid[0, 0], aspect=1)
            plt.pie([taken_sure_in, not_taken_in], labels=labels, colors=colors,\
                   autopct='%1.2f%%', shadow=False, startangle=90)
            plt.title('Puce ' + puce + ' : in')
        
        if taken_sure_out != -1:
            plt.subplot(the_grid[0, 1], aspect=1)
            plt.pie([taken_sure_out, not_taken_out], labels=labels, colors=colors,\
                   autopct='%1.2f%%', shadow=False, startangle=90)
            plt.title('Puce ' + puce + ' : out')
        
        if taken_sure_inout != -1:
            plt.subplot(the_grid[0, 2], aspect=1)
            plt.pie([taken_sure_inout, not_taken_inout], labels=labels, colors=colors,\
                   autopct='%1.2f%%', shadow=False, startangle=90)
            plt.title('Puce ' + puce + ' : inout')
        
        
        plt.subplots_adjust(left=0.1, bottom=8, right=1.8, top=10, wspace=1.2, hspace=0.2)
        plt.show()
        #plt.savefig(pp, format='pdf')
        #pp.close()
plt.savefig(pp, format='pdf')
        
        
"""    
        
df = pd.DataFrame( {'in': column_in,\
    'out': column_out,\
    'inout': column_inout,\
    'not_in': column_not_in,\
    'not_out': column_not_out,\
    'not_inout': column_not_inout,\
    },\
    columns=['in', 'out','inout', 'not_in', 'not_out', 'not_inout'])


plt.style.use('ggplot')
colors = plt.rcParams['axes.color_cycle']

fig, axes = plt.subplots(nrows=nb_puces, ncols=3)
for ax in axes.flat:
    ax.axis('off')

for ax, col in zip(axes.flat, df.columns):
    ax.pie(df[col], labels=df.index, autopct='%.2f', colors=colors)
    ax.set(ylabel='', title=col, aspect='equal')

axes[0, 0].legend(bbox_to_anchor=(0, 0.5))

fig.savefig('all_puces.png')
plt.show() 
"""