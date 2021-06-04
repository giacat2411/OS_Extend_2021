import matplotlib.pyplot as plt
from random import randint
import csv
from datetime import datetime # To measure running time of the algorithm


# Time measurement starts here
startTime = datetime.now()


pts = []
with open("10000.csv") as f:
    csv_reader = csv.reader(f, delimiter=",")
    for row in csv_reader:
        pts = pts + [[float(row[0]), float(row[1])]]




#def create_points(ct,min=0,max=10):
#    return [[randint(min,max),randint(min,max)] \
#            for _ in range(ct)]
            
def scatter_plot(coords, hull=None):
    xs,ys=zip(*coords) # unzip into x and y coord lists
    plt.scatter(xs,ys) # plot the data points

    if hull!=None:
        # plot the convex hull boundary, extra iteration at
        # the end so that the bounding line wraps around
        hull.append(hull[0])
        S = [] 
        n = len(hull)
        #print("number points to plot: ", n)
        for i in range(0, n-1):
            if hull[i+1][0] > hull[i][0] and hull[i+1][1] > hull[i][1]:
                p3 = [hull[i][0], hull[i+1][1]]
                S.append([i+1, p3]) 

            elif hull[i+1][0] > hull[i][0] and hull[i+1][1] < hull[i][1]:
                p3 = [hull[i+1][0], hull[i][1]]
                S.append([i+1, p3])
            elif hull[i+1][0] < hull[i][0] and hull[i+1][1] < hull[i][1]:
                p3 = [hull[i][0], hull[i+1][1]]
                S.append([i+1, p3])
            elif hull[i+1][0] < hull[i][0] and hull[i+1][1] > hull[i][1]:
                p3 = [hull[i+1][0], hull[i][1]]
                S.append([i+1, p3])        
        

        for i in range(len(S)):
            hull.insert(S[i][0]+i, S[i][1])
    

        xz, yz = zip(*hull)
        plt.plot(xz, yz, 'go-', label='line 1', linewidth=2)
        plt.show()

####################################
def orthogonal_sort(L):
    minimum_x_coordinate = min(L) 
    list_of_minx = []
    i = 0
    n2 = len(L)
    while i < n2:
        temp = []
        if L[i][0] == minimum_x_coordinate[0]:
            for elem in L[i]:
                temp.append(elem)
            list_of_minx.append(temp)
            del L[i] 
            n2 = n2 - 1
        else:
            i = i + 1
    I2= sorted(list_of_minx, key =lambda k: k[1], \
        reverse = True)

    leftmost_highest = I2[0]
    leftmost_lowest = I2[-1]
    L = L + list_of_minx
###################

    maximum_x_coordinate = max(L) 
    list_of_maxx = []
    i = 0
    n3 = len(L)
    while i < n3:
        temp = []
        if L[i][0] == maximum_x_coordinate[0]:
            for elem in L[i]:
                temp.append(elem)
            list_of_maxx.append(temp)
            del L[i] 
            n3 = n3 - 1
        else:
            i = i + 1
    I3= sorted(list_of_maxx, key =lambda k: k[1], \
        reverse = True)

    rightmost_lowest = I3[-1]
    rightmost_highest = I3[0]
    L = L + list_of_maxx
###################
    maximum_y_coordinate = max(L, key = lambda x: x[1]) 

    list_of_maxy = []
    i = 0
    n = len(L)
    while i < n:
        temp = []
        if L[i][1] == maximum_y_coordinate[1]:
            for elem in L[i]:
                temp.append(elem)
            list_of_maxy.append(temp)
            del L[i]
            n = n - 1
        else:
            i = i + 1
    I = sorted(list_of_maxy)

    highest_leftmost = I[0]
    highest_rightmost = I[-1]
    L = L+ list_of_maxy
###############
    minimum_y_coordinate = min(L, key = lambda x: x[1]) 
    list_of_miny = []
    i = 0
    n1 = len(L)
    while i < n1:
        temp = []
        if L[i][1] == minimum_y_coordinate[1]:
            for elem in L[i]:
                temp.append(elem)
            list_of_miny.append(temp)
            del L[i]
            n1 = n1 - 1
        else:
            i = i + 1
    I1= sorted(list_of_miny)

    lowest_leftmost = I1[0]
    lowest_rightmost = I1[-1]
    L = L + list_of_miny
############################################
# divide the set of points into two subsets 
    L1 = []
    i = 0
    n4 = len(L)
    while i < n4:
        temp = []
        if leftmost_highest[0] < L[i][0] and L[i][0] <   highest_leftmost[0] \
            and leftmost_highest[1] < L[i][1] and L[i][1] < highest_leftmost[1]:
            for elem in L[i]:
                temp.append(elem)
            L1.append(temp)
            del L[i]
            n4 = n4 - 1
        else:
            i = i + 1

    L = L + L1
##################
    L2 = []
    i = 0
    n5 = len(L)
    while i < n5:
        temp = []
        if leftmost_lowest[0] < L[i][0] and L[i][0] < lowest_leftmost[0] \
            and lowest_leftmost[1] < L[i][1] and L[i][1] < leftmost_lowest[1]:
            for elem in L[i]:
                temp.append(elem)
            L2.append(temp)
            del L[i]
            n5 = n5 - 1
        else:
            i = i + 1
        

    L = L+ L2
#####################
    L3 = []
    i = 0
    n6 = len(L)
    while i < n6:
        temp = []
        if rightmost_highest[0] > L[i][0] and L[i][0] > highest_rightmost[0] \
            and rightmost_highest[1] < L[i][1] and L[i][1] < highest_rightmost[1]:
            for elem in L[i]:
                temp.append(elem)
            L3.append(temp)
            del L[i]
            n6 = n6 - 1
        else:
            i = i + 1


#print("list of  top right hull points are\n", L3)
    L = L+ L3
########################
    L4 = []
    i = 0
    n7 = len(L)
    while i < n7:
        temp = []
        if rightmost_lowest[0] > L[i][0] and L[i][0] > lowest_rightmost[0] \
            and lowest_rightmost[1] < L[i][1] and L[i][1] < rightmost_lowest[1]:
            for elem in L[i]:
                temp.append(elem)
            L4.append(temp)
            del L[i]
            n7 = n7 - 1
        else:
            i = i + 1

############### delete same y-coordinate points 
    L1 = sorted(L1) 
    L1 = sorted(L1, key =lambda k: k[1], \
        reverse = True) 
    index = []
    for i in range(len(L1)-1):
        if L1[i][1] == L1[i+1][1]:
            index.append(i+1)
    L1[:] = [ item for i,item in enumerate(L1) if i not in index ]
    L2 = sorted(L2) 
    L2 = sorted(L2, key =lambda k: k[1], \
         reverse = True) 
    index = []
    for i in range(len(L2)-1):
        if L2[i][1] == L2[i+1][1]:
            index.append(i+1)
    L2[:] = [ item for i,item in enumerate(L2) if i not in index ]
    L3 = sorted(L3) 
    L3 = sorted(L3, key =lambda k: k[1], \
        reverse = True) 
    index = []
    for i in range(len(L3)-1):
        if L3[i][1] == L3[i+1][1]:
            index.append(i)
    L3[:] = [ item for i,item in enumerate(L3) if i not in index ]
    L4 = sorted(L4) 
    L4 = sorted(L4, key =lambda k: k[1], \
        reverse = True) 
    index = []
    for i in range(len(L4)-1):
        if L4[i][1] == L4[i+1][1]:
            index.append(i)
    L4[:] = [ item for i,item in enumerate(L4) if i not in index ]

    L4.reverse()
    L3.reverse()
    L1.insert(0, highest_leftmost)
    L1.append(leftmost_highest)
    L1.append(leftmost_lowest)
    L1 = L1 + L2
    L1.append(lowest_leftmost)
    L4.insert(0, lowest_rightmost)
    L4.append(rightmost_lowest)
    L4.append(rightmost_highest)
    L4 = L4+ L3
    if highest_leftmost[0] != highest_rightmost[0]:
        L4.append(highest_rightmost)


    M = L1 + L4

###########################################
    index = []
    for i in range(len(M)-1):
        if M[i][0] == M[i+1][0] and M[i][1] == M[i+1][1]:
            index.append(i)
    M[:] = [ item for i,item in enumerate(M) if i not in index ]
    

    return leftmost_highest, highest_leftmost, M
###############################################
# Returns the determinant of the 3x3 matrix...
#     [p1(x) p1(y) 1]
#    [p2(x) p2(y) 1]
#     [p3(x) p3(y) 1]
# If >0 then counter-clockwise
# If <0 then clockwise
# If =0 then collinear
def det(p1,p2,p3):
    return   (p2[0]-p1[0])*(p3[1]-p1[1]) \
            -(p2[1]-p1[1])*(p3[0]-p1[0])


def left(p1, p2, p3):
    if det(p1, p2, p3) > 0:
        return True
    else:
        return False
# Returns True of False if a point p1 is to the left of an O-line 
def lefttooline(p1, p2, p3, p4):
    if left(p1, p2, p3) or left(p1, p3, p4):
        return True
    else:
        return False



# Returns True or Fasle if a point is to the left of an O-line through two points
def oleft(p1, p2, p4):

    if p4[0] > p2[0] and p4[1] > p2[1]:

        p3 = [p2[0], p4[1]]

    elif p4[0] > p2[0] and p4[1] < p2[1]:
        p3 = [p4[0], p2[1]]

    elif p4[0] < p2[0] and p4[1] < p2[1]:
        p3 = [p2[0], p4[1]]

    elif p4[0] < p2[0] and p4[1] > p2[1]:
        p3 = [p4[0], p2[1]]

    else:
        p3 = p4 

    return lefttooline(p1, p2, p3, p4)
####################################################
# function linear return True if the considered point is on O-line, false if not
def linear(p1, p2, p4):
    if p4[0] > p2[0] and p4[1] > p2[1]:
        if p2[0] <= p1[0] and p1[0] < p4[0] and p1[1] == p4[1]:

            return True
 
    elif p4[0] > p2[0] and p4[1] < p2[1]:
        if p2[0] < p1[0] and p1[0] <= p4[0] and p1[1] == p2[1]:

            return True

    elif p4[0] < p2[0] and p4[1] < p2[1]:
        if p4[0] < p1[0] and p1[0] <= p2[0] and p1[1] == p4[1]:

            return True

    elif p4[0] < p2[0] and p4[1] > p2[1]:
        if p4[0] <= p1[0] and p1[0] < p2[0] and p1[1] == p2[1]:

            return True

    elif p4[0] == p2[0]:
        if p2[0] == p1[0] and p2[0] < p1[0] and p1[0] < p4[0]:

            return True

    elif p2[1] == p4[1]:
        if p1[1] == p2[1] and p2[0] < p1[0] and p1[0] < p4[0]:

            return True

    elif p2[0] == p4[0]:
        if p1[0] == p2[0] and p4[1] < p1[1]  and p1[1] < p2[1]:

            return True

    elif p2[1] == p4[1]:
        if p1[1] == p2[1] and p4[0] < p1[0] and p1[0] < p2[0]: 

            return True
######################################################




def orthogonal_graham_scan(points, show_progress = False):
    leftmost_highest, highest_leftmost, M = orthogonal_sort(points)    
    if M[0][0] >= M[1][0]:
#    print("scanning counter-clockwise order.......")
#      print("we're going to scan this list\n", M)
#  else:
#      print("scanning from M[-1] counter-clockwise order.......")
        M.insert(0,M[-1]) 
        del M[-1] 
    
    hull = [M[0], M[1]]
    n = len(M)
#print("number points will be scanned ", n)
    for i in range(2, n):
        while not(oleft(M[i], hull[-2], hull[-1]) or linear(M[i], hull[-2], hull[-1])):

            #print("Deleting ", hull[-1], "...")
            del hull[-1]
            #if len(hull) < 2: break
        hull.append(M[i])
        #print("Adding ", M[i], "...")    
        if show_progress: scatter_plot(points,hull)
    if leftmost_highest == highest_leftmost:
        del hull[0]
    return hull
    
#pts = create_points(10)
#print("Points =", pts)
hull = orthogonal_graham_scan(pts, False)


#print("Hull =", hull)
scatter_plot(pts,hull)


# Time measurement ends here

endTime = datetime.now()
timeInterval = endTime - startTime
timeInSecond = timeInterval.total_seconds()
print(f"Algorithm running time: {timeInSecond} seconds.")


