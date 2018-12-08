import matplotlib.pyplot as plt

cohort = [('50', '20'), ('100', '10'), ('200', '5')]
task = ['Median']
data = []

for t in task:
    for size,grp in cohort:
        fname ='../CSV/' + t + '-' + grp + '-' + size + '.csv'
        file = open(fname, 'r')
        best = []
        avg = []
        time = []
        i = 0
        for line in file:
            line = line.split(',')
            best.append(float(line[0]))
            avg.append(float(line[1]))
            time.append(i)
            i += 1

        data.append([best, avg, time])

#data generation for best fitness
plt.plot(data[0][2], data[0][1], 'r--', data[1][2], data[1][1], 'g--', data[2][2], data[2][1], 'b--')
plt.legend(['C: 20', 'C: 10', 'C: 5'])
plt.title('Pop Avg Fitness Per Gen')
plt.show()