import MoveGen as M

start = tuple(map(int,input("Enter the starting coordinate eg. x,y : ").split(',')))

end = tuple(map(int,input("Enter the ending coordinate eg. x,y : ").split(',')))

N = int(input("ENter the length of one side of the square: "))

num_obstacles = int(input("Enter the number of obstacles: "))

obstacles = []

for i in range(num_obstacles):
    obstacles.append(tuple(map(int,input("Enter the obstacle coordinate eg. x,y : ").split(','))))  

openStates = [start]
closedStates = []

while(len(openStates) != 0):
    if openStates[0] == end:
        break
    else:
        temp = M.MoveGen(openStates[0],N)
        closedStates.append(openStates[0])
        for i in temp:
            if (not(i in openStates or i in closedStates or i in obstacles)):
                openStates.append(i)
        openStates.remove(openStates[0])
print(closedStates)