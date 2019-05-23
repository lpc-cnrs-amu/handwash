# -*- coding: utf-8 -*-
"""
Created on Wed May 22 13:52:56 2019

@author: Marjorie
"""
import re
import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf
import pandas as pd
 

column_in = []
column_out = []
column_inout = []
column_not_in = []
column_not_out = []
column_not_inout = []
puce_list = []


def has_numbers(str_input):
    return bool(re.search(r'\d', str_input))

with open("../Docs/output_persons_2018.txt", "r") as file:
    for line in file:
        line = line.rstrip('\n')
        
        if not line or line.isspace() or line[0] == '%'\
            or not has_numbers(line):
            continue
         
        line = line.split()
        puce = line[0]
        
        taken_sure_in = float(line[2])
        taken_sure_out = float(line[4])
        taken_sure_inout = float(line[6])
        
        not_taken_in = float(line[14])
        not_taken_out = float(line[16])
        not_taken_inout = float(line[18])
          
        
        puce_list.append(puce)
        column_in.append(taken_sure_in)
        column_out.append(taken_sure_out)
        column_inout.append(taken_sure_inout)
        
        column_not_in.append(not_taken_in)
        column_not_out.append(not_taken_out)
        column_not_inout.append(not_taken_inout)


df = pd.DataFrame( {'in': column_in,\
    'not in': column_not_in,\
    'out': column_out,\
    'not out': column_not_out,\
    'inout': column_inout,\
    'not inout': column_not_inout,\
    },\
    columns=['in', 'not in', 'out', 'not out', 'inout', 'not inout'],\
    index = ['puce '+p for p in puce_list])
    

def make_autopct(values):
    def my_autopct(pct):
        if pct != 0:
            return '{p:.2f}%'.format(p=pct)
    return my_autopct

colors = ['yellowgreen', 'lightcoral']
labels = ['SHA taken', 'SHA not taken']
pdf = matplotlib.backends.backend_pdf.PdfPages("SHA_pie.pdf")

for ind in df.index:
    fig = plt.figure(figsize=(8,5.3))
    print_in = False
    print_out = False
    
    if df.loc[ind,'in'] != -1 and df.loc[ind,'not in'] != -1:   
        ax1 = plt.subplot2grid((1,3),(0,0))
        df.loc[ind, ['in', 'not in']].plot(kind='pie', ax=ax1, autopct=make_autopct(df.loc[ind, ['in', 'not in']]), colors=colors, labels=None)
        ax1.axis('equal')
        ax1.legend(labels=labels, loc='center left', bbox_to_anchor=(0.5, 0., 0.5, 0.5))
        ax1.set_title('in', pad=0.1)
        print_in = True
    
    if df.loc[ind,'out'] != -1 and df.loc[ind,'not out'] != -1:
        ax2 = plt.subplot2grid((1,3),(0,1))
        
        # if the num of the puce and the legends have already been printed
        # we don't print them again
        if print_in:
            ax2.pie(df.loc[ind, ['out', 'not out']], autopct=make_autopct(df.loc[ind, ['out', 'not out']]), colors=colors, labels=None)
        # the num of the puce and the legends have not been printed (only inout activities)
        else:
            df.loc[ind, ['out', 'not out']].plot(kind='pie', ax=ax2, autopct=make_autopct(df.loc[ind, ['out', 'not out']]), colors=colors, labels=None)
            ax2.legend(labels=labels, loc='center left', bbox_to_anchor=(0.5, 0., 0.5, 0.5))
        ax2.axis('equal')
        ax2.set_title('out', pad=0.1)
        print_out = True
    
    if df.loc[ind,'inout'] != -1 and df.loc[ind,'not inout'] != -1:
        ax3 = plt.subplot2grid((1,3),(0,2))
        
        # if the num of the puce and the legends have already been printed
        # we don't print them again
        if print_in or print_out:
            ax3.pie(df.loc[ind, ['inout', 'not inout']], autopct=make_autopct(df.loc[ind, ['inout', 'not inout']]), colors=colors, labels=None)
            
        # the num of the puce and the legends have not been printed (only inout activities)
        else:
            df.loc[ind, ['inout', 'not inout']].plot(kind='pie', ax=ax3, autopct=make_autopct(df.loc[ind, ['inout', 'not inout']]), colors=colors, labels=None)
            ax3.legend(labels=labels, loc='center left', bbox_to_anchor=(0.5, 0., 0.5, 0.5))
        ax3.axis('equal')
        ax3.set_title('inout', pad=0.1)     
        

    pdf.savefig( fig )
    plt.clf()

pdf.close() 