library(ggplot2)
#library(data.table)
setwd("C:/Users/josex/Desktop/Classes/CSE848/Project/CLS/DATA/RSTUD/")

####################################################AVERAGES####################################################

###MEDIAN AVERAGE
#MED C[0]
M_C0 <- read.csv("../POLISHED_DATA/AVG/MED_COH0_AVG.csv", header=FALSE)
M_C0 <- rbind(mean=rowMeans(M_C0[,-c(1)]), std=apply(M_C0[,-c(1)], 1, sd))
M_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C0))))
#MED C[1]
M_C1 <- read.csv("../POLISHED_DATA/AVG/MED_COH1_AVG.csv", header=FALSE)
M_C1 <- rbind(mean=rowMeans(M_C1[,-c(1)]), std=apply(M_C1[,-c(1)], 1, sd))
M_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C1))))
#MED C[2]
M_C2 <- read.csv("../POLISHED_DATA/AVG/MED_COH2_AVG.csv", header=FALSE)
M_C2 <- rbind(mean=rowMeans(M_C2[,-c(1)]), std=apply(M_C2[,-c(1)], 1, sd))
M_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C2))))
#MED C[3]
M_C3 <- read.csv("../POLISHED_DATA/AVG/MED_COH3_AVG.csv", header=FALSE)
M_C3 <- rbind(mean=rowMeans(M_C3[,-c(1)]), std=apply(M_C3[,-c(1)], 1, sd))
M_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C3))))
#MED C[4]
M_C4 <- read.csv("../POLISHED_DATA/AVG/MED_COH4_AVG.csv", header=FALSE)
M_C4 <- rbind(mean=rowMeans(M_C4[,-c(1)]), std=apply(M_C4[,-c(1)], 1, sd))
M_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C4))))
#MED C[4]
M_C5 <- read.csv("../POLISHED_DATA/AVG/MED_COH5_AVG.csv", header=FALSE)
M_C5 <- rbind(mean=rowMeans(M_C5[,-c(1)]), std=apply(M_C5[,-c(1)], 1, sd))
M_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=M_C0, mapping = aes(x=Generations, y=mean, colour='C:50-20'),size=.1) +
  geom_line(data=M_C1, mapping = aes(x=Generations, y=mean, colour='C:100-10'),size=.1) +
  geom_line(data=M_C2, mapping = aes(x=Generations, y=mean, colour='C:200-5'),size=.1) +
  geom_line(data=M_C3, mapping = aes(x=Generations, y=mean, colour='C:250-4'),size=.1) +
  geom_line(data=M_C4, mapping = aes(x=Generations, y=mean, colour='C:500-2'),size=.1) +
  geom_line(data=M_C5, mapping = aes(x=Generations, y=mean, colour='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,800)) +
  ggtitle('Population Average Fitness - Median') +
  ggsave('Median_Pop_Ave.png')


####NUMIO AVG
#NUM C[0]
N_C0 <- read.csv("../POLISHED_DATA/AVG/NUM_COH0_AVG.csv", header=FALSE)
N_C0 <- rbind(mean=rowMeans(N_C0[,-c(1)]), std=apply(N_C0[,-c(1)], 1, sd))
N_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C0))))
#NUM C[1]
N_C1 <- read.csv("../POLISHED_DATA/AVG/NUM_COH1_AVG.csv", header=FALSE)
N_C1 <- rbind(mean=rowMeans(N_C1[,-c(1)]), std=apply(N_C1[,-c(1)], 1, sd))
N_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C1))))
#NUM C[2]
N_C2 <- read.csv("../POLISHED_DATA/AVG/NUM_COH2_AVG.csv", header=FALSE)
N_C2 <- rbind(mean=rowMeans(N_C2[,-c(1)]), std=apply(N_C2[,-c(1)], 1, sd))
N_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C2))))
#NUM C[3]
N_C3 <- read.csv("../POLISHED_DATA/AVG/NUM_COH3_AVG.csv", header=FALSE)
N_C3 <- rbind(mean=rowMeans(N_C3[,-c(1)]), std=apply(N_C3[,-c(1)], 1, sd))
N_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C3))))
#NUM C[4]
N_C4 <- read.csv("../POLISHED_DATA/AVG/NUM_COH4_AVG.csv", header=FALSE)
N_C4 <- rbind(mean=rowMeans(N_C4[,-c(1)]), std=apply(N_C4[,-c(1)], 1, sd))
N_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C4))))
#NUM C[4]
N_C5 <- read.csv("../POLISHED_DATA/AVG/NUM_COH5_AVG.csv", header=FALSE)
N_C5 <- rbind(mean=rowMeans(N_C5[,-c(1)]), std=apply(N_C5[,-c(1)], 1, sd))
N_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=N_C0, mapping = aes(x=Generations, y=mean, color='C:50-20'),size=.1) +
  geom_line(data=N_C1, mapping = aes(x=Generations, y=mean, color='C:100-10'),size=.1) +
  geom_line(data=N_C2, mapping = aes(x=Generations, y=mean, color='C:200-5'),size=.1) +
  geom_line(data=N_C3, mapping = aes(x=Generations, y=mean, color='C:250-4'),size=.1) +
  geom_line(data=N_C4, mapping = aes(x=Generations, y=mean, color='C:500-2'),size=.1) +
  geom_line(data=N_C5, mapping = aes(x=Generations, y=mean, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,900)) +
  ggtitle('Population Average Fitness - Number IO')+
  ggsave('Num_Pop_Ave.png')

###SOS AVG
#SOS C[0]
S_C0 <- read.csv("../POLISHED_DATA/AVG/SOS_COH0_AVG.csv", header=FALSE)
S_C0 <- rbind(mean=rowMeans(S_C0[,-c(1)]), std=apply(S_C0[,-c(1)], 1, sd))
S_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C0))))
#SOS C[1]
S_C1 <- read.csv("../POLISHED_DATA/AVG/SOS_COH1_AVG.csv", header=FALSE)
S_C1 <- rbind(mean=rowMeans(S_C1[,-c(1)]), std=apply(S_C1[,-c(1)], 1, sd))
S_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C1))))
#SOS C[2]
S_C2 <- read.csv("../POLISHED_DATA/AVG/SOS_COH2_AVG.csv", header=FALSE)
S_C2 <- rbind(mean=rowMeans(S_C2[,-c(1)]), std=apply(S_C2[,-c(1)], 1, sd))
S_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C2))))
#SOS C[3]
S_C3 <- read.csv("../POLISHED_DATA/AVG/SOS_COH3_AVG.csv", header=FALSE)
S_C3 <- rbind(mean=rowMeans(S_C3[,-c(1)]), std=apply(S_C3[,-c(1)], 1, sd))
S_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C3))))
#SOS C[4]
S_C4 <- read.csv("../POLISHED_DATA/AVG/SOS_COH4_AVG.csv", header=FALSE)
S_C4 <- rbind(mean=rowMeans(S_C4[,-c(1)]), std=apply(S_C4[,-c(1)], 1, sd))
S_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C4))))
#SOS C[4]
S_C5 <- read.csv("../POLISHED_DATA/AVG/SOS_COH5_AVG.csv", header=FALSE)
S_C5 <- rbind(mean=rowMeans(S_C5[,-c(1)]), std=apply(S_C5[,-c(1)], 1, sd))
S_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=S_C0, mapping = aes(x=Generations, y=mean, color='C:50-20'),size=.1) +
  geom_line(data=S_C1, mapping = aes(x=Generations, y=mean, color='C:100-10'),size=.1) +
  geom_line(data=S_C2, mapping = aes(x=Generations, y=mean, color='C:200-5'),size=.1) +
  geom_line(data=S_C3, mapping = aes(x=Generations, y=mean, color='C:250-4'),size=.1) +
  geom_line(data=S_C4, mapping = aes(x=Generations, y=mean, color='C:500-2'),size=.1) +
  geom_line(data=S_C5, mapping = aes(x=Generations, y=mean, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,800)) +
  ggtitle('Population Average Fitness - Sum of Squares')+
  ggsave('Sos_Pop_Ave.png')

####################################################BEST####################################################
###MEDIAN BEST
#MED C[0]
M_C0 <- read.csv("../POLISHED_DATA/BEST/MED_COH0_BEST.csv", header=FALSE)
M_C0 <- rbind(best=rowMeans(M_C0[,-c(1)]), std=apply(M_C0[,-c(1)], 1, sd))
M_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C0))))
#MED C[1]
M_C1 <- read.csv("../POLISHED_DATA/BEST/MED_COH1_BEST.csv", header=FALSE)
M_C1 <- rbind(best=rowMeans(M_C1[,-c(1)]), std=apply(M_C1[,-c(1)], 1, sd))
M_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C1))))
#MED C[2]
M_C2 <- read.csv("../POLISHED_DATA/BEST/MED_COH2_BEST.csv", header=FALSE)
M_C2 <- rbind(best=rowMeans(M_C2[,-c(1)]), std=apply(M_C2[,-c(1)], 1, sd))
M_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C2))))
#MED C[3]
M_C3 <- read.csv("../POLISHED_DATA/BEST/MED_COH3_BEST.csv", header=FALSE)
M_C3 <- rbind(best=rowMeans(M_C3[,-c(1)]), std=apply(M_C3[,-c(1)], 1, sd))
M_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C3))))
#MED C[4]
M_C4 <- read.csv("../POLISHED_DATA/BEST/MED_COH4_BEST.csv", header=FALSE)
M_C4 <- rbind(best=rowMeans(M_C4[,-c(1)]), std=apply(M_C4[,-c(1)], 1, sd))
M_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C4))))
#MED C[4]
M_C5 <- read.csv("../POLISHED_DATA/BEST/MED_COH5_BEST.csv", header=FALSE)
M_C5 <- rbind(best=rowMeans(M_C5[,-c(1)]), std=apply(M_C5[,-c(1)], 1, sd))
M_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=M_C0, mapping = aes(x=Generations, y=best, color='C:50-20'),size=.1) +
  geom_line(data=M_C1, mapping = aes(x=Generations, y=best, color='C:100-10'),size=.1) +
  geom_line(data=M_C2, mapping = aes(x=Generations, y=best, color='C:200-5'),size=.1) +
  geom_line(data=M_C3, mapping = aes(x=Generations, y=best, color='C:250-4'),size=.1) +
  geom_line(data=M_C4, mapping = aes(x=Generations, y=best, color='C:500-2'),size=.1) +
  geom_line(data=M_C5, mapping = aes(x=Generations, y=best, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,1000)) +
  ggtitle('Population Best Fitness - Median')+
  ggsave('Median_Pop_Best.png')


####NUMIO BEST
#NUM C[0]
N_C0 <- read.csv("../POLISHED_DATA/BEST/NUM_COH0_BEST.csv", header=FALSE)
N_C0 <- rbind(best=rowMeans(N_C0[,-c(1)]), std=apply(N_C0[,-c(1)], 1, sd))
N_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C0))))
#NUM C[1]
N_C1 <- read.csv("../POLISHED_DATA/BEST/NUM_COH1_BEST.csv", header=FALSE)
N_C1 <- rbind(best=rowMeans(N_C1[,-c(1)]), std=apply(N_C1[,-c(1)], 1, sd))
N_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C1))))
#NUM C[2]
N_C2 <- read.csv("../POLISHED_DATA/BEST/NUM_COH2_BEST.csv", header=FALSE)
N_C2 <- rbind(best=rowMeans(N_C2[,-c(1)]), std=apply(N_C2[,-c(1)], 1, sd))
N_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C2))))
#NUM C[3]
N_C3 <- read.csv("../POLISHED_DATA/BEST/NUM_COH3_BEST.csv", header=FALSE)
N_C3 <- rbind(best=rowMeans(N_C3[,-c(1)]), std=apply(N_C3[,-c(1)], 1, sd))
N_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C3))))
#NUM C[4]
N_C4 <- read.csv("../POLISHED_DATA/BEST/NUM_COH4_BEST.csv", header=FALSE)
N_C4 <- rbind(best=rowMeans(N_C4[,-c(1)]), std=apply(N_C4[,-c(1)], 1, sd))
N_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C4))))
#NUM C[4]
N_C5 <- read.csv("../POLISHED_DATA/BEST/NUM_COH5_BEST.csv", header=FALSE)
N_C5 <- rbind(best=rowMeans(N_C5[,-c(1)]), std=apply(N_C5[,-c(1)], 1, sd))
N_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=N_C0, mapping = aes(x=Generations, y=best, color='C:50-20'),size=.5) +
  geom_line(data=N_C1, mapping = aes(x=Generations, y=best, color='C:100-10'),size=.5) +
  geom_line(data=N_C2, mapping = aes(x=Generations, y=best, color='C:200-5'),size=.5) +
  geom_line(data=N_C3, mapping = aes(x=Generations, y=best, color='C:250-4'),size=.5) +
  geom_line(data=N_C4, mapping = aes(x=Generations, y=best, color='C:500-2'),size=.5) +
  geom_line(data=N_C5, mapping = aes(x=Generations, y=best, color='C:1000-1'),size=.5) +
  scale_y_continuous(limits=c(0,1000)) +
  ggtitle('Population Best Fitness - Number IO')+
  ggsave('Num_Pop_Best.png')

###SOS BEST
#SOS C[0]
S_C0 <- read.csv("../POLISHED_DATA/BEST/SOS_COH0_BEST.csv", header=FALSE)
S_C0 <- rbind(best=rowMeans(S_C0[,-c(1)]), std=apply(S_C0[,-c(1)], 1, sd))
S_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C0))))
#SOS C[1]
S_C1 <- read.csv("../POLISHED_DATA/BEST/SOS_COH1_BEST.csv", header=FALSE)
S_C1 <- rbind(best=rowMeans(S_C1[,-c(1)]), std=apply(S_C1[,-c(1)], 1, sd))
S_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C1))))
#SOS C[2]
S_C2 <- read.csv("../POLISHED_DATA/BEST/SOS_COH2_BEST.csv", header=FALSE)
S_C2 <- rbind(best=rowMeans(S_C2[,-c(1)]), std=apply(S_C2[,-c(1)], 1, sd))
S_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C2))))
#SOS C[3]
S_C3 <- read.csv("../POLISHED_DATA/BEST/SOS_COH3_BEST.csv", header=FALSE)
S_C3 <- rbind(best=rowMeans(S_C3[,-c(1)]), std=apply(S_C3[,-c(1)], 1, sd))
S_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C3))))
#SOS C[4]
S_C4 <- read.csv("../POLISHED_DATA/BEST/SOS_COH4_BEST.csv", header=FALSE)
S_C4 <- rbind(best=rowMeans(S_C4[,-c(1)]), std=apply(S_C4[,-c(1)], 1, sd))
S_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C4))))
#SOS C[4]
S_C5 <- read.csv("../POLISHED_DATA/BEST/SOS_COH5_BEST.csv", header=FALSE)
S_C5 <- rbind(best=rowMeans(S_C5[,-c(1)]), std=apply(S_C5[,-c(1)], 1, sd))
S_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=S_C0, mapping = aes(x=Generations, y=best, color='C:50-20'),size=.1) +
  geom_line(data=S_C1, mapping = aes(x=Generations, y=best, color='C:100-10'),size=.1) +
  geom_line(data=S_C2, mapping = aes(x=Generations, y=best, color='C:200-5'),size=.1) +
  geom_line(data=S_C3, mapping = aes(x=Generations, y=best, color='C:250-4'),size=.1) +
  geom_line(data=S_C4, mapping = aes(x=Generations, y=best, color='C:500-2'),size=.1) +
  geom_line(data=S_C5, mapping = aes(x=Generations, y=best, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,1000)) +
  ggtitle('Population Best Fitness - Sum of Squares')+
  ggsave('Sos_Pop_Best.png')

####################################################SOLUTIONS####################################################
###MEDIAN SOL
#MED C[0]
M_C0 <- read.csv("../POLISHED_DATA/SOL/MED_COH0_SOL.csv", header=FALSE)
M_C0 <- rbind(solutions=rowMeans(M_C0[,-c(1)]), std=apply(M_C0[,-c(1)], 1, sd))
M_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C0))))
#MED C[1]
M_C1 <- read.csv("../POLISHED_DATA/SOL/MED_COH1_SOL.csv", header=FALSE)
M_C1 <- rbind(solutions=rowMeans(M_C1[,-c(1)]), std=apply(M_C1[,-c(1)], 1, sd))
M_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C1))))
#MED C[2]
M_C2 <- read.csv("../POLISHED_DATA/SOL/MED_COH2_SOL.csv", header=FALSE)
M_C2 <- rbind(solutions=rowMeans(M_C2[,-c(1)]), std=apply(M_C2[,-c(1)], 1, sd))
M_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C2))))
#MED C[3]
M_C3 <- read.csv("../POLISHED_DATA/SOL/MED_COH3_SOL.csv", header=FALSE)
M_C3 <- rbind(solutions=rowMeans(M_C3[,-c(1)]), std=apply(M_C3[,-c(1)], 1, sd))
M_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C3))))
#MED C[4]
M_C4 <- read.csv("../POLISHED_DATA/SOL/MED_COH4_SOL.csv", header=FALSE)
M_C4 <- rbind(solutions=rowMeans(M_C4[,-c(1)]), std=apply(M_C4[,-c(1)], 1, sd))
M_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C4))))
#MED C[4]
M_C5 <- read.csv("../POLISHED_DATA/SOL/MED_COH5_SOL.csv", header=FALSE)
M_C5 <- rbind(solutions=rowMeans(M_C5[,-c(1)]), std=apply(M_C5[,-c(1)], 1, sd))
M_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), M_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=M_C0, mapping = aes(x=Generations, y=solutions, color='C:50-20'),size=.1) +
  geom_line(data=M_C1, mapping = aes(x=Generations, y=solutions, color='C:100-10'),size=.1) +
  geom_line(data=M_C2, mapping = aes(x=Generations, y=solutions, color='C:200-5'),size=.1) +
  geom_line(data=M_C3, mapping = aes(x=Generations, y=solutions, color='C:250-4'),size=.1) +
  geom_line(data=M_C4, mapping = aes(x=Generations, y=solutions, color='C:500-2'),size=.1) +
  geom_line(data=M_C5, mapping = aes(x=Generations, y=solutions, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,800)) +
  ggtitle('Number of Solutions - Median')+
  ggsave('Median_Pop_SolAvg.png')


####NUMIO SOL
#NUM C[0]
N_C0 <- read.csv("../POLISHED_DATA/SOL/NUM_COH0_SOL.csv", header=FALSE)
N_C0 <- rbind(solutions=rowMeans(N_C0[,-c(1)]), std=apply(N_C0[,-c(1)], 1, sd))
N_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C0))))
#NUM C[1]
N_C1 <- read.csv("../POLISHED_DATA/SOL/NUM_COH1_SOL.csv", header=FALSE)
N_C1 <- rbind(solutions=rowMeans(N_C1[,-c(1)]), std=apply(N_C1[,-c(1)], 1, sd))
N_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C1))))
#NUM C[2]
N_C2 <- read.csv("../POLISHED_DATA/SOL/NUM_COH2_SOL.csv", header=FALSE)
N_C2 <- rbind(solutions=rowMeans(N_C2[,-c(1)]), std=apply(N_C2[,-c(1)], 1, sd))
N_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C2))))
#NUM C[3]
N_C3 <- read.csv("../POLISHED_DATA/SOL/NUM_COH3_SOL.csv", header=FALSE)
N_C3 <- rbind(solutions=rowMeans(N_C3[,-c(1)]), std=apply(N_C3[,-c(1)], 1, sd))
N_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C3))))
#NUM C[4]
N_C4 <- read.csv("../POLISHED_DATA/SOL/NUM_COH4_SOL.csv", header=FALSE)
N_C4 <- rbind(solutions=rowMeans(N_C4[,-c(1)]), std=apply(N_C4[,-c(1)], 1, sd))
N_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C4))))
#NUM C[4]
N_C5 <- read.csv("../POLISHED_DATA/SOL/NUM_COH5_SOL.csv", header=FALSE)
N_C5 <- rbind(solutions=rowMeans(N_C5[,-c(1)]), std=apply(N_C5[,-c(1)], 1, sd))
N_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), N_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=N_C0, mapping = aes(x=Generations, y=solutions, color='C:50-20'),size=.1) +
  geom_line(data=N_C1, mapping = aes(x=Generations, y=solutions, color='C:100-10'),size=.1) +
  geom_line(data=N_C2, mapping = aes(x=Generations, y=solutions, color='C:200-5'),size=.1) +
  geom_line(data=N_C3, mapping = aes(x=Generations, y=solutions, color='C:250-4'),size=.1) +
  geom_line(data=N_C4, mapping = aes(x=Generations, y=solutions, color='C:500-2'),size=.1) +
  geom_line(data=N_C5, mapping = aes(x=Generations, y=solutions, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,600)) +
  ggtitle('Number of Solutions - Number IO')+
  ggsave('Num_Pop_SolAvg.png')

###SOS SOL
#SOS C[0]
S_C0 <- read.csv("../POLISHED_DATA/SOL/SOS_COH0_SOL.csv", header=FALSE)
S_C0 <- rbind(solutions=rowMeans(S_C0[,-c(1)]), std=apply(S_C0[,-c(1)], 1, sd))
S_C0 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C0))))
#SOS C[1]
S_C1 <- read.csv("../POLISHED_DATA/SOL/SOS_COH1_SOL.csv", header=FALSE)
S_C1 <- rbind(solutions=rowMeans(S_C1[,-c(1)]), std=apply(S_C1[,-c(1)], 1, sd))
S_C1 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C1))))
#SOS C[2]
S_C2 <- read.csv("../POLISHED_DATA/SOL/SOS_COH2_SOL.csv", header=FALSE)
S_C2 <- rbind(solutions=rowMeans(S_C2[,-c(1)]), std=apply(S_C2[,-c(1)], 1, sd))
S_C2 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C2))))
#SOS C[3]
S_C3 <- read.csv("../POLISHED_DATA/SOL/SOS_COH3_SOL.csv", header=FALSE)
S_C3 <- rbind(solutions=rowMeans(S_C3[,-c(1)]), std=apply(S_C3[,-c(1)], 1, sd))
S_C3 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C3))))
#SOS C[4]
S_C4 <- read.csv("../POLISHED_DATA/SOL/SOS_COH4_SOL.csv", header=FALSE)
S_C4 <- rbind(solutions=rowMeans(S_C4[,-c(1)]), std=apply(S_C4[,-c(1)], 1, sd))
S_C4 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C4))))
#SOS C[4]
S_C5 <- read.csv("../POLISHED_DATA/SOL/SOS_COH5_SOL.csv", header=FALSE)
S_C5 <- rbind(solutions=rowMeans(S_C5[,-c(1)]), std=apply(S_C5[,-c(1)], 1, sd))
S_C5 <- data.frame(t(data.frame(rbind(Generations=seq(0,9999), S_C5))))
#Without Error bars
ggplot() +
  scale_color_discrete(name = "Cohort Size- \n # of Cohorts") +
  geom_line(data=S_C0, mapping = aes(x=Generations, y=solutions, color='C:50-20'),size=.1) +
  geom_line(data=S_C1, mapping = aes(x=Generations, y=solutions, color='C:100-10'),size=.1) +
  geom_line(data=S_C2, mapping = aes(x=Generations, y=solutions, color='C:200-5'),size=.1) +
  geom_line(data=S_C3, mapping = aes(x=Generations, y=solutions, color='C:250-4'),size=.1) +
  geom_line(data=S_C4, mapping = aes(x=Generations, y=solutions, color='C:500-2'),size=.1) +
  geom_line(data=S_C5, mapping = aes(x=Generations, y=solutions, color='C:1000-1'),size=.1) +
  scale_y_continuous(limits=c(0,600)) +
  ggtitle('Number of Solutions - Sum of Squares')+
  ggsave('Sos_Pop_SolAvg.png')

#################################################### SOL CNT ####################################################
M_CNT <- read.csv("../POLISHED_DATA/SOL_CNT/MED_SOL_CNT.csv", header=FALSE)
M_CNT <- data.frame(cohort=M_CNT[,c(1)], solutions = as.numeric(M_CNT[,c(2)]))
ggplot(data=M_CNT, aes(x=cohort, y=solutions)) +
  geom_bar(stat="identity", fill="steelblue") +
  theme_minimal() +
  ggtitle("Solution Count - Median")+
  ggsave('Median_Sol_Cnt.png')

N_CNT <- read.csv("../POLISHED_DATA/SOL_CNT/NUM_SOL_CNT.csv", header=FALSE)
N_CNT <- data.frame(cohort = N_CNT[,c(1)], solutions = as.numeric(N_CNT[,c(2)]))
ggplot(data=N_CNT, aes(x=cohort, y=solutions)) +
  geom_bar(stat="identity", fill="steelblue") +
  theme_minimal() +
  ggtitle("Solution Count - Number IO")+
  ggsave('Num_Sol_Cnt.png')

N_CNT <- read.csv("../POLISHED_DATA/SOL_CNT/SOS_SOL_CNT.csv", header=FALSE)
N_CNT <- data.frame(cohort = N_CNT[,c(1)], solutions = as.numeric(N_CNT[,c(2)]))
ggplot(data=N_CNT, aes(x=cohort, y=solutions)) +
  geom_bar(stat="identity", fill="steelblue") +
  theme_minimal() +
  ggtitle("Solution Count - Sum of Squares")+
  ggsave('SOS_Sol_Cnt.png')
       