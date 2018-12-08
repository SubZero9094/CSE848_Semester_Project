#Python script to put all same treatments into one csv file!
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def main():
    
    #Name for x axis labels in graph
    name = ['C#: 20 \n CS: 50', 'C#: 10 \n CS: 100', 'C#: 5 \n CS: 200', 'C#: 4 \n CS: 250', 'C#: 2 \n CS: 500', 'C#: 1 \n CS: 1000']
    
#    #Creating a bar graph for the median solution counts
#    med = pd.read_csv('../POLISHED_DATA/SOL_CNT/MED_SOL_CNT.csv', header=None)
#    sols_cnt = med[1].tolist()
#    y_pos = np.arange(len(name))
#
#    plt.bar(y_pos, sols_cnt, align='center', alpha=1.0)
#    plt.xticks(y_pos, name)
#    plt.ylabel('Solutions Count')
#    plt.title('Solution Count - Median')
#    plt.savefig('Median_SOL_CNT.png')
    
#    #Creating a bar graph for the median solution counts
#    med = pd.read_csv('../POLISHED_DATA/SOL_CNT/NUM_SOL_CNT.csv', header=None)
#    sols_cnt = med[1].tolist()
#    y_pos = np.arange(len(name))
#
#    plt.bar(y_pos, sols_cnt, align='center', alpha=1.0)
#    plt.xticks(y_pos, name)
#    plt.ylabel('Solutions Count')
#    plt.title('Solution Count - Number IO')
#    plt.savefig('Num_SOL_CNT.png')
    
    #Creating a bar graph for the median solution counts
    med = pd.read_csv('../POLISHED_DATA/SOL_CNT/SOS_SOL_CNT.csv', header=None)
    sols_cnt = med[1].tolist()
    print(sols_cnt)
    y_pos = np.arange(len(name))

    plt.bar(y_pos, sols_cnt, align='center', alpha=1.0)
    axes = plt.gca()
    axes.set_ylim([0,100])
    plt.xticks(y_pos, name)
    plt.ylabel('Solutions Count')
    plt.title('Solution Count - Sum of Squares')
    plt.savefig('Sos_SOL_CNT.png')

if __name__ == '__main__':
    main()