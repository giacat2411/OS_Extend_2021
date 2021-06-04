'''
    p[0]: x- coordinate of P
    p[1]: y- coodinate of p
    def insnide(p, p1, p2): All points in the right of L(p1, p2)
    that is, all points that whose x-coordinate in (min(p1[0], p2[0]), max(p1[0], p2[0])) and y-codinate in min(p1[1], p2[1]), max(p1[1], p2[1])


def inside(p, p1, p2):
    if p == p1 or p == p2:
        return False
    return min(p1[0], p2[0]) <= p[0] <= max(p1[0], p2[0]) and \
           min(p1[1], p2[1]) <= p[1] <= max(p1[1], p2[1])
'''
#####################################################
'''
    finite extreme point.
'''

#####################################################
def find_o_hull1(set1, q1, qq1):
    if len(set1) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []
    
    def add(p):
        return (p[0] - q1[0])*(p[0] - q1[0]) + (p[1] - qq1[1])*(p[1] - qq1[1])
    
    sort_set1_Dist = sorted(set1, key = add, reverse=True) 
    new_point1 = sort_set1_Dist[0]
    
    new_set11 = []
    new_set12 = []
    for p in set1:
        if p[1] > new_point1[1]:
            new_set11.append(p)
        elif p[0] < new_point1[0]:
            new_set12.append(p)
    #new_set1 = [p for p in set1 if inside(p, q1, new_point)]
    #new_set2 = [p for p in set1 if inside(p, new_point, qq1)]
    return find_o_hull1(new_set11, q1, new_point1) + [new_point1] + find_o_hull1(new_set12, new_point1, qq1)

#####################################################
def find_o_hull2(set2, q2, qq2):
    if len(set2) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []

    '''
    Tính bình phương khoảng cách từ điểm p tới đỉnh v(qq2[0], q2[1])
    '''
    def add(p):
        return (p[0] - qq2[0])*(p[0] - qq2[0]) + (p[1] - q2[1])*(p[1] - q2[1])
    '''
    Sắp xếp theo thứ tự giảm dần các khoảng cách từ p với v. New point là điểm đầu tiên trong dãy.    
    '''
    sort_set2_Dist = sorted(set2, key = add, reverse=True) 
    new_point2 = sort_set2_Dist[0]
    
    '''
        The set of points on the right of L
    '''
    new_set21 = []
    new_set22 = []
    for p in set2:
        if p[0] < new_point2[0]:
            new_set21.append(p)
        elif p[1] < new_point2[1]:
            new_set22.append(p)
    
    #new_set1 = [p for p in set2 if inside(p, q2, new_point)]
    #new_set2 = [p for p in set2 if inside(p, new_point, qq2)]
    '''
        Return two new points in order
    '''
    return find_o_hull2(new_set21, q2, new_point2) + [new_point2] + find_o_hull2(new_set22, new_point2, qq2)

#####################################################
def find_o_hull3(set3, q3, qq3):
    if len(set3) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []
 
    
    '''
    Tính bình phương khoảng cách từ điểm p tới đỉnh v(qq2[0], q2[1])
    '''
    def add(p):
        return (p[0] - q3[0])*(p[0] - q3[0]) + (p[1] - qq3[1])*(p[1] - qq3[1])
    '''
    Sắp xếp theo thứ tự giảm dần các khoảng cách từ p với v. New point là điểm đầu tiên trong dãy.    
    '''
    sort_set3_Dist = sorted(set3, key = add, reverse=True) 
    new_point3 = sort_set3_Dist[0]
    
    '''
        The set of points on the right of L
    '''
    new_set31 = []
    new_set32 = []
    for p in set3:
        if p[1] < new_point3[1]:
            new_set31.append(p)
        elif p[0] > new_point3[0]:
            new_set32.append(p)
    #new_set1 = [p for p in set3 if inside(p, q3, new_point)]
    #new_set2 = [p for p in set3 if inside(p, new_point, qq3)]
    '''
        Return two new points in order
    '''
    return find_o_hull3(new_set31, q3, new_point3) + [new_point3] + find_o_hull3(new_set32, new_point3, qq3)

#####################################################

def find_o_hull4(set4, q4, qq4):
    if len(set4) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []

   
    '''
    Tính bình phương khoảng cách từ điểm p tới đỉnh v(qq2[0], q2[1])
    '''
    def add(p):
        return (p[0] - qq4[0])*(p[0] - qq4[0]) + (p[1] - q4[1])*(p[1] - q4[1])
    '''
    Sắp xếp theo thứ tự giảm dần các khoảng cách từ p với v. New point là điểm đầu tiên trong dãy.    
    '''
    sort_set4_Dist = sorted(set4, key = add, reverse=True) 
    new_point4 = sort_set4_Dist[0]
    
    new_set41 = []
    new_set42 = []
    for p in set4:
        if p[0] > new_point4[0]:
            new_set41.append(p)
        elif p[1] > new_point4[1]:
            new_set42.append(p)
    '''
        The set of points on the right of L
    '''
    #new_set1 = [p for p in set4 if inside(p, q4, new_point)]
    #new_set2 = [p for p in set4 if inside(p, new_point, qq4)]
    '''
        Return two new points in order
    '''
    return find_o_hull4(new_set41, q4, new_point4) + [new_point4] + find_o_hull4(new_set42, new_point4, qq4)
 
 #####################################################

def findOrthogonalConvexHull(points):
    # Find 8 points
    # top
    maxY = points[0][1]
    minY = points[0][1]
    maxX = points[0][0]
    minX = points[0][0]
    
    leftPoints = []
    rightPoints = []
    topPoints = []
    bottomPoints = []
    
    for point in points:
        if point[0] < minX: minX = point[0] #leftmost point
        if point[0] > maxX: maxX = point[0] #rightmost point
        if point[1] < minY: minY = point[1] #lowest point
        if point[1] > maxY: maxY = point[1] #hightest point


    for point in points:
        if point[0] == minX: leftPoints.append(point) #add the points having minimal x-coordinate in lefPoints list
        if point[0] == maxX: rightPoints.append(point) #add the points having maxi mal x-coordinate in lefPoints list
        if point[1] == minY: bottomPoints.append(point) #add the points having minimal y-coordinate in lefPoints list
        if point[1] == maxY: topPoints.append(point) #add the points having maximal y-coordinate in lefPoints list

# Sort the elements of the lists: topPoints, bottomPoints, rightPoints, and leftPoints and give the starting and ending points of each list

    if len(topPoints) == 1:
        top = (topPoints[0],)
    else:
        topPoints = sorted(topPoints, key = lambda x : x[0])
        top = (topPoints[0], topPoints[len(topPoints)-1])

    # bottom
    if len(bottomPoints) == 1:
        bottom = (bottomPoints[0],)
    else:
        bottomPoints = sorted(bottomPoints, key = lambda x : -x[0])
        bottom = (bottomPoints[0], bottomPoints[len(bottomPoints)-1])

    # right
    if len(rightPoints) == 1:
        right = (rightPoints[0],)
    else:
        rightPoints = sorted(rightPoints, key = lambda x : -x[1])
        right = (rightPoints[0], rightPoints[len(rightPoints)-1])

    # left
    if len(leftPoints) == 1:
        left = (leftPoints[0],)
    else:
        leftPoints = sorted(leftPoints, key = lambda x : x[1])
        left = (leftPoints[0], leftPoints[len(leftPoints)-1])

    if len(top) == 1:
        q1 = qq4 = top[0]
    else:
        q1 = top[0]
        qq4 = top[1]
    q4 = right[0]
    if len(right) == 1:
        qq3 = right[0]
    else:
        qq3 = right[1]
    q3 = bottom[0]
    if len(bottom) == 1:
        qq2 = bottom[0]
    else:
        qq2 = bottom[1]
    q2 = left[0]
    if len(left) == 1:
        qq1 = left[0]
    else:
        qq1 = left[1]

    # Separate to 4 sets of points
    set1 = []
    set2 = []
    set3 = []
    set4 = []
    '''
    for i in range(len(points)):
        if points[i][0] <= q1[0] and points[i][1] >= qq1[1]:
            set1.append(points[i])
        elif points[i][0] <= qq2[0] and points[i][1] <= q2[1]:
            set2.append(points[i])
        elif points[i][0] >= q3[0] and points[i][1] <= qq3[1]:
            set3.append(points[i])
        elif points[i][0] >= qq4[0] and points[i][1] >= q4[1]:
            set4.append(points[i])
     '''       
    for p in points:
        if p[0] <= q1[0] and p[1] >= qq1[1]:
            set1.append(p)
        elif p[0] <= qq2[0] and p[1] <= q2[1]:
            set2.append(p)
        elif p[0] >= q3[0] and p[1] <= qq3[1]:
            set3.append(p)
        elif p[0] >= qq4[0] and p[1] >= q4[1]:
            set4.append(p) 
    
    #set1 = [a for a in points if inside(a, q1, qq1)]
    #set2 = [a for a in points if inside(a, q2, qq2)]
    #set3 = [a for a in points if inside(a, q3, qq3)]
    #set4 = [a for a in points if inside(a, q4, qq4)]

    arranged_points = []
    arranged_points = arranged_points + [q1] + find_o_hull1(set1, q1, qq1) + [qq1]
    arranged_points = arranged_points + [q2] + find_o_hull2(set2, q2, qq2) + [qq2]
    arranged_points = arranged_points + [q3] + find_o_hull3(set3, q3, qq3) + [qq3]
    arranged_points = arranged_points + [q4] + find_o_hull4(set4, q4, qq4) + [qq4]

    return arranged_points