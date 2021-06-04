def inside(p, p1, p2):
    if p == p1 or p == p2:
        return False
    return min(p1[0], p2[0]) <= p[0] <= max(p1[0], p2[0]) and \
           min(p1[1], p2[1]) <= p[1] <= max(p1[1], p2[1])


def findOrthogonalConvexHull(points):
    # Find 8 points
    maxY = points[0][1]
    minY = points[0][1]
    maxX = points[0][0]
    minX = points[0][0]

    for point in points:
        if point[0] < minX: minX = point[0]
        if point[0] > maxX: maxX = point[0]
        if point[1] < minY: minY = point[1]
        if point[1] > maxY: maxY = point[1]
    
    leftPoints = []
    rightPoints = []
    topPoints = []
    bottomPoints = []

    for point in points:
        if point[0] == minX:
            leftPoints.append(point) 
        if point[0] == maxX:
            rightPoints.append(point)
        if point[1] == minY:
            bottomPoints.append(point)
        if point[1] == maxY:
            topPoints.append(point)

    # top
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

    topLeft = top[0]
    topRight = top[-1]

    rightmostTop = right[0]
    rightmostBot = right[-1]

    botRight = bottom[0]
    botLeft = bottom[-1]

    leftmostBot = left[0]
    leftmostTop = left[-1]

    # Separate to 4 sets of points
    URPoints = [a for a in points if inside(a, rightmostTop, topRight)]
    ULPoints = [a for a in points if inside(a, topLeft, leftmostTop)]
    BLPoints = [a for a in points if inside(a, leftmostBot, botLeft)]
    BRPoints = [a for a in points if inside(a, botRight, rightmostBot)]

    # Find convex of 4 quarters
    URConvex = []
    ULConvex = []
    BLConvex = []
    BRConvex = []
    
    URPoints = sorted(URPoints, key = lambda x : -x[0]*1000 + x[1]/1000)
    if len(URPoints) > 0: URConvex = [URPoints[0]]
    for point in URPoints:
        current = URConvex[-1]
        if current[0] == point[0] and current[1] == point[1]: continue
        if point[1] >= current[1]: URConvex.append(point)
    URConvex = [rightmostBot, rightmostTop] + URConvex + [topRight]

    ULPoints = sorted(ULPoints, key = lambda x : x[0]*1000 + x[1]/1000)
    if len(ULPoints) > 0: ULConvex = [ULPoints[0]]
    for point in ULPoints:
        current = ULConvex[-1]
        if current[0] == point[0] and current[1] == point[1]: continue
        if point[1] >= current[1]: ULConvex.append(point)
    ULConvex.reverse()
    ULConvex = [topRight, topLeft] + ULConvex + [leftmostTop]

    BLPoints = sorted(BLPoints, key = lambda x : x[0]*1000 - x[1]/1000)
    if len(BLPoints) > 0: BLConvex = [BLPoints[0]]
    for point in BLPoints:
        current = BLConvex[-1]
        if current[0] == point[0] and current[1] == point[1]: continue
        if point[1] <= current[1]: BLConvex.append(point)
    BLConvex = [leftmostTop, leftmostBot] + BLConvex + [botLeft]

    BRPoints = sorted(BRPoints, key = lambda x : -x[0]*1000 - x[1]/1000)
    if len(BRPoints) > 0: BRConvex = [BRPoints[0]]
    for point in BRPoints:
        current = BRConvex[-1]
        if current[0] == point[0] and current[1] == point[1]: continue
        if point[1] <= current[1]: BRConvex.append(point)
    BRConvex.reverse()
    BRConvex = [botLeft, botRight] + BRConvex + [rightmostBot]

    return [URConvex, ULConvex, BLConvex, BRConvex]
