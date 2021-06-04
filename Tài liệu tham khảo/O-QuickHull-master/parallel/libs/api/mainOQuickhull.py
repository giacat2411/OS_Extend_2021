import matplotlib.pyplot as plt
import wrapper
import convexOQH
import csv
from datetime import datetime # To measure running time of the algorithm


# Read input points.36
input_points = []
dataset = []

fname = "100000.csv"

with open(fname) as f:
    csv_reader = csv.reader(f, delimiter=",")
    for row in csv_reader:
        input_points = input_points + [[float(row[0]), float(row[1])]]


# Time measurement starts here
startTime = datetime.now()
# Find orthogonal points sequence (arranged to order)
points = wrapper.findOrthogonalConvexHull_runable(fname, "temp.csv")
#points = convex.findOrthogonalConvexHull(input_points)
points2 = convexOQH.findOrthogonalConvexHull(input_points)

from functools import *
print(reduce(lambda x, y: x and y in points2, points, True))
for i in points2:
    if i not in points:
        print(points2.index(i), i)



############################################################
# plot the orthogonal hull
# adding points (angle 270)
S = []
n = len(points)
#print("number points to plot: ", n)
for i in range(0, n-1):
    
    if points[i+1][0] > points[i][0] and points[i+1][1] > points[i][1]:
        
        p3 = [points[i][0], points[i+1][1]]
        
        S.append([i+1, p3])

    elif points[i+1][0] > points[i][0] and points[i+1][1] < points[i][1]:
        
        p3 = [points[i+1][0], points[i][1]]
        
        S.append([i+1, p3])

    elif points[i+1][0] < points[i][0] and points[i+1][1] < points[i][1]:
    
        p3 = [points[i][0], points[i+1][1]]
    
        S.append([i+1, p3])

    elif points[i+1][0] < points[i][0] and points[i+1][1] > points[i][1]:
        
        p3 = [points[i+1][0], points[i][1]]
        
        S.append([i+1, p3])

#print("list index and points to be adding: ", S)

for i in range(len(S)):
    points.insert(S[i][0]+i, S[i][1])
points.append(points[0])
############################################################
# Draw lines
fig, ax = plt.subplots()

# Input points in blue
ax.plot([x[0] for x in input_points], [x[1] for x in input_points], 'r.')

# Orthogonal convex hull points in red
ax.plot([x[0] for x in points], [x[1] for x in points], 'b-')
#ax.plot([list(points[0])[0], list(points[-1])[0]], [list(points[0])[1], list(points[-1])[1]],'r-')

plt.ylabel('Y')
plt.xlabel('X')
plt.show()

# Time measurement ends here
endTime = datetime.now()
timeInterval = endTime - startTime
timeInSecond = timeInterval.total_seconds()
print(f"Algorithm running time: {timeInSecond} seconds.")


