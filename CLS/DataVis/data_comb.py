#Python script to put all same treatments into one csv file!
import pandas as pd

####FUNCTION TO LOAD DATA INTO A COMPRESSED MATRIX#######
def mat(START, END, DIR, FILE, NAME):
    POP_BEST = "POP_BEST"
    POP_AVG = "POP_AVG"
    POP_SOL = "SOL_CNT"
    DATA_STORE = "../DATA/POLISHED_DATA/"
    TIME = [i for i in range(0,10000)]
    BEST_MAT = []
    AVG_MAT = []
    SOL_MAT = []
    BEST_MAT.append(TIME)
    AVG_MAT.append(TIME)
    SOL_MAT.append(TIME)

    for i in range(START, END+1):
        path = DIR + str(i) + FILE
        df = pd.read_csv(path)
        BEST_MAT.append(df[POP_BEST].tolist())
        AVG_MAT.append(df[POP_AVG].tolist())
        SOL_MAT.append(df[POP_SOL].tolist())
        
    AVG = pd.DataFrame(AVG_MAT)
    AVG = AVG.transpose()
    DIR = DATA_STORE + 'AVG/' + NAME + 'AVG.csv'
    AVG.to_csv(DIR, index=False, header=False)
    
    MED = pd.DataFrame(BEST_MAT)
    MED = MED.transpose()
    DIR = DATA_STORE + 'BEST/' + NAME + 'BEST.csv'
    MED.to_csv(DIR, index=False, header=False)
    
    SOL = pd.DataFrame(SOL_MAT)
    SOL = SOL.transpose()
    DIR = DATA_STORE + 'SOL/' + NAME + 'SOL.csv'
    SOL.to_csv(DIR, index=False, header=False)
    
    
def sol_cnt(START, END, DIR, FILE, NAME):
    POP_SOL = 'SOL_CNT'
    cnt = 0.0
    
    for i in range(START, END+1):
        path = DIR + str(i) + FILE
        df = pd.read_csv(path)
        SOL_MAT = (df[POP_SOL].tolist())
        
        for x in SOL_MAT:
            if x > 0:
                cnt += 1.0
                break
            
    return [NAME, cnt]


def main():
    
    ################# MEDIAN #################
    SOL_CNT = []
    START = 1
    END = 100
    OFFSET = 100
    
    ### MEDIAN | CHO[0] 
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT0_SEED'
    fname = '/Median-20-50.csv'
    coh = 'C:20-50'
    mat(START,END,path,fname,'MED_COH0_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ### MEDIAN | CHO[1] 
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT1_SEED'
    fname = '/Median-10-100.csv'
    coh = 'C:10-100'
    mat(START,END,path,fname,'MED_COH1_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ### MEDIAN | CHO[2] 
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT2_SEED'
    fname = '/Median-5-200.csv'
    coh = 'C:5-200'
    mat(START,END,path,fname,'MED_COH2_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ### MEDIAN | CHO[3] 
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT3_SEED'
    fname = '/Median-4-250.csv'
    coh = 'C:4-250'
    mat(START,END,path,fname,'MED_COH3_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ### MEDIAN | CHO[4] 
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT4_SEED'
    fname = '/Median-2-500.csv'
    coh = 'C:2-500'
    mat(START,END,path,fname,'MED_COH4_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ### MEDIAN | CHO[5] 
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE0_SELECTION0_COHORT5_SEED'
    fname = '/Median-1-1000.csv'
    coh = 'C:1-1000'
    mat(START,END,path,fname,'MED_COH5_')
    SOL_CNT.append(sol_cnt(START, END, path, fname, coh))
    
    ################# STORE ALL THE DATA INTO A CSV #################
    SOL = pd.DataFrame(SOL_CNT)
    DIR = '../DATA/POLISHED_DATA/SOL_CNT/MED_SOL_CNT.csv'
    SOL.to_csv(DIR, index=False, header=False)
    
    ################# NUM-IO #################
    SOL_CNT = []
    
    ### NUMIO | CHO[0]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT0_SEED'
    fname = '/NumIO-20-50.csv'
    coh = 'C:20-50'
    mat(START,END,path,fname,'NUM_COH0_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))    
    
    ### NUMIO | CHO[1]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT1_SEED'
    fname = '/NumIO-10-100.csv'
    coh = 'C:10-100'
    mat(START,END,path,fname,'NUM_COH1_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### NUMIO | CHO[2]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT2_SEED'
    fname = '/NumIO-5-200.csv'
    coh = 'C:5-200'
    mat(START,END,path,fname,'NUM_COH2_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### NUMIO | CHO[3]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT3_SEED'
    fname = '/NumIO-4-250.csv'
    coh = 'C:4-250'
    mat(START,END,path,fname,'NUM_COH3_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### NUMIO | CHO[4]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT4_SEED'
    fname = '/NumIO-2-500.csv'
    coh = 'C:2-500'
    mat(START,END,path,fname,'NUM_COH4_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### NUMIO | CHO[5]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE1_SELECTION0_COHORT5_SEED'
    fname = '/NumIO-1-1000.csv'
    coh = 'C:1-1000'
    mat(START,END,path,fname,'NUM_COH5_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ################# STORE ALL THE DATA INTO A CSV #################
    SOL = pd.DataFrame(SOL_CNT)
    DIR = '../DATA/POLISHED_DATA/SOL_CNT/NUM_SOL_CNT.csv'
    SOL.to_csv(DIR, index=False, header=False)
    
    ################# SOS #################
    
    SOL_CNT = []
  
    ### SOS | CHO[0]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT0_SEED'
    fname = '/SOS-20-50.csv'
    coh = 'C:20-50'
    mat(START,END,path,fname,'SOS_COH0_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### SOS | CHO[1]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT1_SEED'
    fname = '/SOS-10-100.csv'
    coh = 'C:10-100'
    mat(START,END,path,fname,'SOS_COH1_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### SOS | CHO[2]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT2_SEED'
    fname = '/SOS-5-200.csv'
    coh = 'C:5-200'
    mat(START,END,path,fname,'SOS_COH2_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### SOS | CHO[3]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT3_SEED'
    fname = '/SOS-4-250.csv'
    coh = 'C:4-250'
    mat(START,END,path,fname,'SOS_COH3_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### SOS | CHO[4]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT4_SEED'
    fname = '/SOS-2-500.csv'
    coh = 'C:2-500'
    mat(START,END,path,fname,'SOS_COH4_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ### SOS | CHO[5]
    START += OFFSET
    END += OFFSET
    path = '../DATA/RAW_DATA/CASE2_SELECTION0_COHORT5_SEED'
    fname = '/SOS-1-1000.csv'
    coh = 'C:1-1000'
    mat(START,END,path,fname,'SOS_COH5_')
    SOL_CNT.append(sol_cnt(START,END, path, fname, coh))
    
    ################# STORE ALL THE DATA INTO A CSV #################
    SOL = pd.DataFrame(SOL_CNT)
    DIR = '../DATA/POLISHED_DATA/SOL_CNT/SOS_SOL_CNT.csv'
    SOL.to_csv(DIR, index=False, header=False)
    


if __name__ == '__main__':
    main()