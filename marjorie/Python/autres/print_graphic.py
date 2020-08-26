# -*- coding: utf-8 -*-
"""
Created on Wed May 22 13:52:56 2019

@author: Marjorie
"""
import re
import sys
import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf
import pandas as pd
"""
if len(sys.argv) != 3 :
    print("Usage : {} {} {}".format( sys.argv[0], "file_generated_by_cpp.csv", "output_filename.pdf" ))
    sys.exit()
"""

filename = sys.argv[1]
df = pd.read_csv(filename, sep=";")




def has_numbers(str_input):
    return bool(re.search(r'\d', str_input))
    

def make_autopct(values):
    def my_autopct(pct):
        if pct != 0.00:
            return '{p:.2f}%'.format(p=pct)
    return my_autopct
"""
colors = ['yellowgreen', 'lightcoral', 'gold']
labels = ['SHA taken', 'SHA not taken', 'SHA possibly taken']
pdf = matplotlib.backends.backend_pdf.PdfPages(sys.argv[2])
"""

"""
for tuple_row in df.itertuples(index=False):
    #print(tuple_row)
    print(type(tuple_row[0])

"""
for ind in df.index:
    fig = plt.figure(figsize=(8,6))
    print_in = False
    print_out = False
    
    if df.loc[ind,'taken in sure total'] != 0 or df.loc[ind,'taken in possible number'] != 0:
        ax1 = plt.subplot2grid((1,3),(0,0))
        df.loc[ind, ['taken in sure percent', 'not taken in percent', 'taken in possible percent']].plot\
            (kind='pie', ax=ax1, autopct=make_autopct(df.loc[ind, ['taken in sure percent', 'not taken in percent', 'taken in possible percent']]),\
            colors=colors, labels=None)
        ax1.legend(labels=labels, loc='upper center', bbox_to_anchor=(0.5, -0.05))
        ax1.set_title('in :\ntotal sure = '+\
            str(df.loc[ind, 'taken in sure total'])+\
            '\ntotal possible = '+\
            str(df.loc[ind, 'taken in possible number'])+\
            '\ntotal = '+\
            str( int(df.loc[ind, 'taken in sure total'] + df.loc[ind, 'taken in possible number']))\
            , pad=0)       
        print_in = True
    
    if df.loc[ind,'taken out sure total'] != 0 or df.loc[ind,'taken out possible number'] != 0:
        ax2 = plt.subplot2grid((1,3),(0,1))
    
        # if the num of the puce and the legends have already been printed
        # we don't print them again
        if print_in:
            ax2.pie(df.loc[ind, ['taken out sure percent', 'not taken out percent',\
                'taken out possible percent']],\
                autopct=make_autopct(df.loc[ind, ['taken out sure percent', 'not taken out percent', 'taken out possible percent']]),\
                colors=colors, labels=None)
        # the num of the puce and the legends have not been printed (only inout activities)
        else:
            df.loc[ind, ['taken out sure percent', 'not taken out percent','taken out possible percent']].\
            plot(kind='pie', ax=ax2,\
            autopct=make_autopct(df.loc[ind, ['taken out sure percent',\
            'not taken out percent','taken out possible percent']]), colors=colors, labels=None)
            ax2.legend(labels=labels, loc='upper center', bbox_to_anchor=(0.5, -0.05))
        
        ax2.set_title('out :\ntotal sure = '+\
            str(df.loc[ind, 'taken out sure total'])+\
            '\ntotal possible = '+\
            str(df.loc[ind, 'taken out possible number'])+\
            '\ntotal = '+\
            str( int(df.loc[ind, 'taken out sure total'] + df.loc[ind, 'taken out possible number']))\
            , pad=0)   
        print_out = True
    
    if df.loc[ind,'taken inout sure total'] != 0 or df.loc[ind,'taken inout possible number'] != 0:
        ax3 = plt.subplot2grid((1,3),(0,2))
        
        # if the num of the puce and the legends have already been printed
        # we don't print them again
        if print_in or print_out:
            ax3.pie(df.loc[ind, ['taken inout sure percent',\
                'not taken inout percent', 'taken inout possible percent']],\
                autopct=make_autopct(df.loc[ind, ['taken inout sure percent',\
                'not taken inout percent', 'taken inout possible percent']]),\
                colors=colors, labels=None)
            
        # the num of the puce and the legends have not been printed (only inout activities)
        else:
            df.loc[ind, ['taken inout sure percent', 'not taken inout percent',\
            'taken inout possible percent']].plot(kind='pie', ax=ax3,\
            autopct=make_autopct(df.loc[ind, ['taken inout sure percent', 'not taken inout percent',\
            'taken inout possible percent']]), colors=colors, labels=None)
            ax3.legend(labels=labels, loc='upper center', bbox_to_anchor=(0.5, -0.05))
            
        ax3.set_title('inout :\ntotal sure = '+\
            str(df.loc[ind, 'taken inout sure total'])+\
            '\ntotal possible = '+\
            str(df.loc[ind, 'taken inout possible number'])+\
            '\ntotal = '+\
            str( int(df.loc[ind, 'taken inout sure total'] + df.loc[ind, 'taken inout possible number']) )\
            , pad=0)     
        
    pdf.savefig( fig )
    plt.clf()

pdf.close() 
