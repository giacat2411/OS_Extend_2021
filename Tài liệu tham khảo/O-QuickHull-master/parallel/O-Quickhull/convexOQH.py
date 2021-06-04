'''
    p[0]: x- coordinate of P
    p[1]: y- coodinate of p
    def insnide(p, p1, p2): All points in the right of L(p1, p2)
    that is, all points that whose x-coordinate in (min(p1[0], p2[0]), max(p1[0], p2[0])) and y-codinate in min(p1[1], p2[1]), max(p1[1], p2[1])
'''

def inside(p, p1, p2):
    if p == p1 or p == p2:
        return False
    return min(p1[0], p2[0]) <= p[0] <= max(p1[0], p2[0]) and \
           min(p1[1], p2[1]) <= p[1] <= max(p1[1], p2[1])

#####################################################
'''
    finite extreme point.
'''

#####################################################
def find_o_hull1(set1, q1, qq1):
    if len(set1) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []
    
    
    '''
        Sắp xếp tập set1 theo thứ tự giảm dần của tung độ, nếu có hai điểm có tung độ trùng nhau thì xếp theo thứ tự tăng dần của x (điểm có tung độ cao nhất với hành độ nhỏ nhất nằm ở đầu dãy)
    '''
    sort_set1y = sorted(set1, key=lambda p: (-p[1], p[0]))
    new_point11 = sort_set1y[0]
    '''
        Sắp xếp tập set1 theo thứ tự tăng dần của hoành, nếu có hai điểm có hoành độ trùng nhau thì xếp theo thứ tự giảm dần của y (điểm có hoảnh độ nhỏ nhất với tung độ lớn nhất nằm ở đầu dãy)
    '''
    sort_set1x = sorted(set1, key=lambda p: (p[0], -p[1]))
    new_point12 = sort_set1x[0]
    '''
        The set of points on the right of L(new_point11, new_point12)
    '''
    new_set1 = [p for p in set1 if inside(p, new_point11, new_point12)]
    '''
        Return two new points in order
    '''
    
    return [new_point11] + find_o_hull1(new_set1, new_point11, new_point12) + [new_point12]

#####################################################
def find_o_hull2(set2, q2, qq2):
    if len(set2) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []

    '''
        Sắp xếp tập set2 theo thứ tự tăng dần của x, nếu có hai điểm có x trùng nhau thì xếp theo thứ tự tăng dần của y (điểm có x nhỏ nhất với y nhỏ nhất nằm ở đầu dãy)
    '''
    sort_set2x = sorted(set2, key=lambda p: (p[0], p[1]))
    new_point21 = sort_set2x[0]
    '''
        Sắp xếp tập set2 theo thứ tự tăng dần của y, nếu có hai điểm có y trùng nhau thì xếp theo thứ tự tăng dần của x (điểm có y nhỏ nhất với x nhỏ nhất nằm ở đầu dãy)
    '''
    sort_set2y = sorted(set2, key=lambda p: (p[1], p[0]))
    new_point22 = sort_set2y[0]
    '''
        The set of points on the right of L(new_point1, new_point2)
    '''
    new_set2 = [p for p in set2 if inside(p, new_point21, new_point22)]
    '''
        Return two new points in order
    '''
    return [new_point21] + find_o_hull2(new_set2, new_point21, new_point22) + [new_point22]

#####################################################
def find_o_hull3(set3, q3, qq3):
    if len(set3) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []
 
    
    '''
        Sắp xếp tập set3 theo thứ tự tăng dần của y, nếu có hai điểm có y trùng nhau thì xếp theo thứ tự giảm dần của x (điểm có y nhỏ nhất với x lớn nhất nằm ở đầu dãy)
    '''
    sort_set3y = sorted(set3, key=lambda p: (p[1], -p[0]))
    new_point31 = sort_set3y[0]
    '''
        Sắp xếp tập set3 theo thứ tự giảm dần của x, nếu có hai điểm có x trùng nhau thì xếp theo thứ tự tăng dần của y (điểm có x lớn nhất với y nhỏ nhất nằm ở đầu dãy)
    '''
    sort_set3x = sorted(set3, key=lambda p: (-p[0], p[1]))
    new_point32 = sort_set3x[0]
    '''
        The set of points on the right of L(new_point1, new_point2)
    '''
    new_set3 = [p for p in set3 if inside(p, new_point31, new_point32)]
    '''
        Return two new points in order
    '''
    return [new_point31] + find_o_hull3(new_set3, new_point31, new_point32) + [new_point32]

#####################################################

def find_o_hull4(set4, q4, qq4):
    if len(set4) == 0:
        #po = ortho(pf, pt, xInc, yInc) # SUPPORT POINTS
        return []

    
    '''
        Sắp xếp tập set4 theo thứ tự giảm dần của x, nếu có hai điểm có x trùng nhau thì xếp theo thứ tự giảm dần của y (điểm có x lớn nhất với y lớn nhất nằm ở đầu dãy)
    '''
    sort_set4x = sorted(set4, key=lambda p: (-p[0], -p[1]))
    new_point41 = sort_set4x[0]
    '''
        Sắp xếp tập set4 theo thứ tự giảm dần của y, nếu có hai điểm có y trùng nhau thì xếp theo thứ tự giảm dần của x (điểm có y lớn nhất với x lớn nhất nằm ở đầu dãy)
    '''
    sort_set4y = sorted(set4, key=lambda p: (-p[1], -p[0]))
    new_point42 = sort_set4y[0]
    '''
        The set of points on the right of L(new_point1, new_point2)
    '''
    new_set4 = [p for p in set4 if inside(p, new_point41, new_point42)]
    '''
        Return two new points in order
    '''
    return [new_point41] + find_o_hull4(new_set4, new_point41, new_point42) + [new_point42]
 
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
    set1 = [a for a in points if inside(a, q1, qq1)]
    set2 = [a for a in points if inside(a, q2, qq2)]
    set3 = [a for a in points if inside(a, q3, qq3)]
    set4 = [a for a in points if inside(a, q4, qq4)]

    arranged_points = []
    arranged_points = arranged_points + [q1] + find_o_hull1(set1, q1, qq1) + [qq1]
    arranged_points = arranged_points + [q2] + find_o_hull2(set2, q2, qq2) + [qq2]
    arranged_points = arranged_points + [q3] + find_o_hull3(set3, q3, qq3) + [qq3]
    arranged_points = arranged_points + [q4] + find_o_hull4(set4, q4, qq4) + [qq4]

    print(len(arranged_points))
    return arranged_points

