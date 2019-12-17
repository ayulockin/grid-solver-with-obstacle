import MoveGen as M

openStates = []

closedStates = []

start = tuple(map(int,input("Enter the starting coordinate eg. x,y : ").split(',')))

end = tuple(map(int,input("Enter the ending coordinate eg. x,y : ").split(',')))

N = int(input("ENter the length of one side of the square: "))

openStates = M.MoveGen(start,N)
closedStates = [start]

while(len(openStates) != 0):
    if openStates[0] == end:
        break
    else:
        temp = M.MoveGen(openStates[0],N)
        closedStates.append(openStates[0])
        for i in temp:
            if (not(i in openStates or i in closedStates)):
                openStates.append(i)
        openStates.remove(openStates[0])
print(closedStates)