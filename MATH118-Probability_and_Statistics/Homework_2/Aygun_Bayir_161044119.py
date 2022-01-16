# import csv library for reading text file
import csv
with open('manufacturing_defects.txt', 'r') as file:
    reader = csv.reader(file, delimiter='\t') # all values are seperated with tab
    data = list(reader)

# import matplotlib library for drawing barplot
import matplotlib.pyplot as plt

# Function to calculate factorial of number n
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

# Part A
# Calculation
a_counts = [0 for x in range(5)]
for x in range(20):
    for y in range(2,16):
        if int(data[x][y]) == 0:
            a_counts[0] = a_counts[0] + 1
        elif int(data[x][y]) == 1:
            a_counts[1] = a_counts[1] + 1
        elif int(data[x][y]) == 2:
            a_counts[2] = a_counts[2] + 1
        elif int(data[x][y]) == 3:
            a_counts[3] = a_counts[3] + 1
        elif int(data[x][y]) == 4:
            a_counts[4] = a_counts[4] + 1

# Printing result
print()
print("********** Part A **********")
print("# of Defects\t# of defects in all")
print("\t\tcompanies between the years")
print("------------------------------------------")
for x in range(5):
    print(x, "\t\t", a_counts[x])

total = 0.0
for x in range(5):
    total = total + float(a_counts[x])
    
# Part B & C
# Calculating mean
mean = 0.0
for x in range(20):
    for y in range(2,16):
        mean = mean + float(data[x][y])
mean = mean / total

euler = 2.7182818

# Calculating poisson predicted cases
poisson_counts = [0.0 for x in range(5)]
for x in range(5):
    poisson_counts[x] = (mean**x)*(1/(euler**mean)) / float(factorial(x)) * total

# Printing results
print()
print("********** Part B **********")
print("Lambda = ", mean)
print()
print("********** Part C **********")
print("# of Defects\t# of defects in all\tPredicted # of defects")
print("\t\tcompanies between \tin all companies")
print("\t\tthe years\t\tbetween the years")
print("---------------------------------------------------------------")
for x in range(5):
    print(x, "\t\t", a_counts[x], "\t\t\t", float('%.2f' % (poisson_counts[x])))

# Part D
print()
print("********** Part D **********")
print("Barplot drawing(s) will be shown in new window(s).")
# Common in both figure
langs = [0,1,2,3,4]

# Barplot: Number of Defects
plt.bar(langs,a_counts)
plt.show()

# Barplot: Predicted number of Defects
plt.bar(langs,poisson_counts)
plt.show()

