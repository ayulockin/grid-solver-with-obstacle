def MoveGen(present_state,N):
    '''
    This method is the Generator of Neighbouring States
    It generates the next moves possible
    Upon giving the present state, the function returns the
    other probable states the device can go in.

    Params: Present State, N
        datatype: set, integer
        data: coordinates, the length of the square
        example:(x,y) , 4
    Output: The probable States that the device can go to from its
            present state.
        datatype: list of sets
        data: list of coordinates
        example: [(x1,y1),(x2,y2)]
    '''
    # This portion of the code checks for `Vertial` edges
    if present_state[0] == 0:
        # This means that the bot is on the `Left` edge
        if present_state[1] == 0:
            # This means that the bot is on the `Bottom Left` corner
            future_states = [(present_state[0]+1,present_state[1]), # move right
                             (present_state[0],present_state[1]+1)] # move up
        elif present_state[1] == N-1:
            # This means that the bot is on the `Top Left` corner
            future_states = [(present_state[0]+1,present_state[1]), # move right
                             (present_state[0],present_state[1]-1)] # move down
    elif present_state[0] == N-1:
        # This means that the bot is on the `Right` edge
        if present_state[1] == 0:
            # This means that the bot is on the `Bottom Right` corner
            future_states = [(present_state[0]-1,present_state[1]), # move left
                             (present_state[0],present_state[1]+1)] # move up
        elif present_state[1] == N-1:
            # This means that the bot is on the `Top Right` corner
            future_states = [(present_state[0]-1,present_state[1]), # move left
                             (present_state[0],present_state[1]-1)] # move down

    # This portion of the code checks for `Horizontal` edges
    elif present_state[1] == 0:
        # This means that the bot is on the `Bottom` edge
        future_states = [(present_state[0]-1,present_state[1]), # move left
                         (present_state[0]+1,present_state[1]), # move right
                         (present_state[0],present_state[1]+1)] # move up
    elif present_state[1] == N-1:
        # This means that the bot is on the `Top` edge
        future_states = [(present_state[0]-1,present_state[1]), # move left
                         (present_state[0]+1,present_state[1]), # move right
                         (present_state[0],present_state[1]-1)] # move down
    
    # THis portion takes care of anything in the middle
    elif present_state[0] < N and present_state[1] < N:
        future_states = [(present_state[0]-1,present_state[1]), # move left
                         (present_state[0]+1,present_state[1]), # move right
                         (present_state[0],present_state[1]+1), # move up
                         (present_state[0],present_state[1]-1)] # move down
    else:
        future_states = [('Out','Out')]
    return future_states
