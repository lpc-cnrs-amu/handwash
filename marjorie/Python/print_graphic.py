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
 
if len(sys.argv) != 2 :
    print("Usage : {} {}".format( sys.argv[0], "file_generated_by_cpp" ))
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
        taken_sure_in_percent = float(line[2]) #
        taken_sure_in_nb = int(line[4])
        taken_sure_in_total = int(line[6])
         
        taken_sure_out_percent = float(line[8]) #
        taken_sure_out_nb = int(line[10])
        taken_sure_out_total = int(line[12])    
        
        taken_sure_inout_percent = float(line[14]) #
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
          
        # puce
        puce_list.append(puce)
        
        
        
        """ APPEND faire les not taken"""
        #percent
        column_taken_sure_in_percent.append(taken_sure_in_percent)
        column_taken_sure_out_percent.append(taken_sure_out_percent)
        column_taken_sure_inout_percent.append(taken_sure_inout_percent)
        
        # number
        column_taken_sure_in_nb.append(taken_sure_in_nb)
        column_taken_sure_out_nb.append(taken_sure_out_nb)
        column_taken_sure_inout_nb.append(taken_sure_inout_nb)
        
        # total
        column_taken_sure_in_total.append(taken_sure_in_total)
        column_taken_sure_out_total.append(taken_sure_out_total)
        column_taken_sure_inout_total.append(taken_sure_inout_total)
        

# si ya toutes les colonnes du tableau alors c ok
df = pd.DataFrame( {'taken in sure percent': column_taken_sure_in_percent,\
    'taken in sure number': column_taken_sure_in_nb,\
    'taken in sure total': column_taken_sure_in_total,\
    'taken in possible percent': ,\
    'taken in possible number': ,\
    
    'taken out sure percent': ,\
    'taken out sure number': ,\
    'taken out sure total': ,\
    'taken out possible percent': ,\
    'taken out possible number': ,\    
    
    'taken inout sure percent': ,\
    'taken inout sure number': ,\
    'taken inout sure total': ,\
    'taken inout possible percent': ,\
    'taken inout possible number': ,\     
    
  
    'not taken in percent': ,\
    'not taken in number': ,\
    'not taken in total': ,\  
    
    'not taken out percent': ,\
    'not taken out number': ,\
    'not taken out total': ,\     
    
    'not taken inout percent': ,\
    'not taken inout number': ,\
    'not taken inout total': ,\    
    },\
    columns=['taken in sure percent', 'not in', 'out', 'not out', 'inout', 'not inout'],\
    index = ['puce '+p for p in puce_list])
    

def make_autopct(values):
    def my_autopct(pct):
        if pct != 0:
            return '{p:.2f}%'.format(p=pct)
    return my_autopct

colors = ['yellowgreen', 'lightcoral', 'gold']
labels = ['SHA taken', 'SHA not taken', 'SHA possibly taken']
pdf = matplotlib.backends.backend_pdf.PdfPages(sys.argv[2])

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