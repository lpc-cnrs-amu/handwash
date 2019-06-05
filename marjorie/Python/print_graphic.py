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
 
if len(sys.argv) != 3 :
    print("Usage : {} {} {}".format( sys.argv[0], "file_generated_by_cpp", "output_filename.pdf" ))
    sys.exit()



# percent
column_taken_sure_in_percent = []
column_taken_sure_out_percent = []
column_taken_sure_inout_percent = []
column_taken_possible_in_percent = []
column_taken_possible_out_percent = []
column_taken_possible_inout_percent = []
column_not_taken_in_percent = []
column_not_taken_out_percent = []
column_not_taken_inout_percent = []

# number
column_taken_sure_in_nb = []
column_taken_sure_out_nb = []
column_taken_sure_inout_nb = []
column_taken_possible_in_nb = []
column_taken_possible_out_nb = []
column_taken_possible_inout_nb = []
column_not_taken_in_nb = []
column_not_taken_out_nb = []
column_not_taken_inout_nb = []

# total
column_taken_sure_in_total = []
column_taken_sure_out_total = []
column_taken_sure_inout_total = []
column_not_taken_in_total = []
column_not_taken_out_total = []
column_not_taken_inout_total = []

puce_list = []


def has_numbers(str_input):
    return bool(re.search(r'\d', str_input))

with open(sys.argv[1], "r") as file:
    for line in file:
        line = line.rstrip('\n')
        
        if not line or line.isspace() or line[0] == '%'\
            or not has_numbers(line):
            continue
         
        line = line.split()
        puce = line[0]
        
        # SHA SURE
        taken_sure_in_percent = float(line[2])
        taken_sure_in_nb = int(line[4])
        taken_sure_in_total = int(line[6])
         
        taken_sure_out_percent = float(line[8])
        taken_sure_out_nb = int(line[10])
        taken_sure_out_total = int(line[12])    
        
        taken_sure_inout_percent = float(line[14])
        taken_sure_inout_nb = int(line[16])
        taken_sure_inout_total = int(line[18])
        
        # SHA POSSIBLE
        taken_possible_in_percent = float(line[20])
        taken_possible_in_nb = int(line[22])
        
        taken_possible_out_percent = float(line[24])
        taken_possible_out_nb = int(line[26])
        
        taken_possible_inout_percent = float(line[28])
        taken_possible_inout_nb = int(line[30])      
        
        # SHA NOT TAKEN
        not_taken_in_percent = float(line[32])
        not_taken_in_nb = int(line[34])
        not_taken_in_total = int(line[36])
         
        not_taken_out_percent = float(line[38])
        not_taken_out_nb = int(line[40])
        not_taken_out_total = int(line[42])    
        
        not_taken_inout_percent = float(line[44])
        not_taken_inout_nb = int(line[46])
        not_taken_inout_total = int(line[48])
          

        
        """ APPEND """
        # puce
        puce_list.append(puce)
        
        #percent
        column_taken_sure_in_percent.append(taken_sure_in_percent)
        column_taken_sure_out_percent.append(taken_sure_out_percent)
        column_taken_sure_inout_percent.append(taken_sure_inout_percent)
        column_taken_possible_in_percent.append(taken_possible_in_percent)
        column_taken_possible_out_percent.append(taken_possible_out_percent)
        column_taken_possible_inout_percent.append(taken_possible_inout_percent)
        column_not_taken_in_percent.append(not_taken_in_percent)
        column_not_taken_out_percent.append(not_taken_out_percent)
        column_not_taken_inout_percent.append(not_taken_inout_percent)       
        
        # number
        column_taken_sure_in_nb.append(taken_sure_in_nb)
        column_taken_sure_out_nb.append(taken_sure_out_nb)
        column_taken_sure_inout_nb.append(taken_sure_inout_nb)
        column_taken_possible_in_nb.append(taken_possible_in_nb)
        column_taken_possible_out_nb.append(taken_possible_out_nb)
        column_taken_possible_inout_nb.append(taken_possible_inout_nb)
        column_not_taken_in_nb.append(not_taken_in_nb)
        column_not_taken_out_nb.append(not_taken_out_nb)
        column_not_taken_inout_nb.append(not_taken_inout_nb)        
        
        # total
        column_taken_sure_in_total.append(taken_sure_in_total)
        column_taken_sure_out_total.append(taken_sure_out_total)
        column_taken_sure_inout_total.append(taken_sure_inout_total)
        column_not_taken_in_total.append(not_taken_in_total)
        column_not_taken_out_total.append(not_taken_out_total)
        column_not_taken_inout_total.append(not_taken_inout_total)       


df = pd.DataFrame( {'taken in sure percent': column_taken_sure_in_percent,\
    'taken in sure number': column_taken_sure_in_nb,\
    'taken in sure total': column_taken_sure_in_total,\
    'taken in possible percent': column_taken_possible_in_percent,\
    'taken in possible number': column_taken_possible_in_nb,\
    'taken out sure percent': column_taken_sure_out_percent,\
    'taken out sure number': column_taken_sure_out_nb,\
    'taken out sure total': column_taken_sure_out_total,\
    'taken out possible percent': column_taken_possible_out_percent,\
    'taken out possible number': column_taken_possible_out_nb,\
    'taken inout sure percent': column_taken_sure_inout_percent,\
    'taken inout sure number': column_taken_sure_inout_nb,\
    'taken inout sure total': column_taken_sure_inout_total,\
    'taken inout possible percent': column_taken_possible_inout_percent,\
    'taken inout possible number': column_taken_possible_inout_nb,\
    'not taken in percent': column_not_taken_in_percent,\
    'not taken in number': column_not_taken_in_nb,\
    'not taken in total': column_not_taken_in_total,\
    'not taken out percent': column_not_taken_out_percent,\
    'not taken out number': column_not_taken_out_nb,\
    'not taken out total': column_not_taken_out_total,\
    'not taken inout percent': column_not_taken_inout_percent,\
    'not taken inout number': column_not_taken_inout_nb,\
    'not taken inout total': column_not_taken_inout_total,\
    },\
    columns=[\
    'taken in sure percent',\
    'taken in sure number',\
    'taken in sure total',\
    'taken in possible percent',\
    'taken in possible number',\
    'taken out sure percent',\
    'taken out sure number',\
    'taken out sure total',\
    'taken out possible percent',\
    'taken out possible number',\
    'taken inout sure percent',\
    'taken inout sure number',\
    'taken inout sure total',\
    'taken inout possible percent',\
    'taken inout possible number',\
    'not taken in percent',\
    'not taken in number',\
    'not taken in total',\
    'not taken out percent',\
    'not taken out number',\
    'not taken out total',\
    'not taken inout percent',\
    'not taken inout number',\
    'not taken inout total',\
    ],\
    index = ['puce '+p for p in puce_list])
    

def make_autopct(values):
    def my_autopct(pct):
        if pct != 0.00:
            return '{p:.2f}%'.format(p=pct)
    return my_autopct

colors = ['yellowgreen', 'lightcoral', 'gold']
labels = ['SHA taken', 'SHA not taken', 'SHA possibly taken']
pdf = matplotlib.backends.backend_pdf.PdfPages(sys.argv[2])

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