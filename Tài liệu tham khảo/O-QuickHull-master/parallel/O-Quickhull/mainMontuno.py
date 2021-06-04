import matplotlib.pyplot as plt
from convexMontuno import findOrthogonalConvexHull
import csv
from random import randint
from random import uniform
from datetime import datetime # To measure running time of the algorithm



# Time measurement starts here
startTime = datetime.now()



# Read input points
input_points = []
dataset = []

with open("50000.csv") as f:
    csv_reader = csv.reader(f, delimiter=",")
    csv_reader1 = csv.reader(f, delimiter=",")
    for row in csv_reader:
        input_points = input_points + [[float(row[0]), float(row[1])]]




def convexPlot(points, drawRule):
    for i in range(len(points) - 1):
        start = points[i]
        end = points[i + 1]
        buffer = drawRule(start, end)
        plt.plot([start[0], buffer[0]], [start[1], buffer[1]], 'r-')
        plt.plot([buffer[0], end[0]], [buffer[1], end[1]], 'r-')

def drawRule1(start, end):
    return [end[0], start[1]]

def drawRule2(start, end):
    return [start[0], end[1]]


# Draw lines
fig, ax = plt.subplots()
ax.plot([x[0] for x in input_points], [x[1] for x in input_points], 'o')


# Find orthogonal points sequence (arranged to order)
points = findOrthogonalConvexHull(input_points)



#pointsPlot2 = findOrthogonalConvexHull(input_points)
# Orthogonal convex hull in red
convexPlot(points[0], drawRule1)
convexPlot(points[1], drawRule2)
convexPlot(points[2], drawRule1)
convexPlot(points[3], drawRule2)

plt.ylabel('Y')
plt.xlabel('X')
plt.show()

# Time measurement ends here
endTime = datetime.now()
timeInterval = endTime - startTime
timeInSecond = timeInterval.total_seconds()
print(f"Algorithm running time: {timeInSecond} seconds.")



