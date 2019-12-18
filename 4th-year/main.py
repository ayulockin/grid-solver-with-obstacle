from breadth_first_search import MoveGen

present_state = list(map(int, input('The bot is at (x,y): ').split(',')))
N = int(input('Length of the grid (N): '))

print(MoveGen(present_state, N))