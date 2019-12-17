def MoveGen(present_state):
    '''
    This method is the Generator of Neighbouring States
    It generates the next moves possible
    Upon giving the present state, the function returns the
    other probable states the device can go in.

    Params: Present State
        datatype: set
        data: coordinates
        example:(x,y)
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
            future_states = [(present_state[0]+1,present_state[1]),
            (present_state[0],present_state[1]+1)]
        elif present_state[1] == N-1:
            # This means that the bot is on the `Top Left` corner
            future_states = [(present_state[0]+1,present_state[1]),
            (present_state[0],present_state[1]-1)]
    if present_state[0] == N-1:
        # This means that the bot is on the `Right` edge
        if present_state[1] == 0:
            # This means that the bot is on the `Bottom Right` corner
            future_states = [(present_state[0]-1,present_state[1]),
            (present_state[0],present_state[1]+1)]
        elif present_state[1] == N-1:
            # This means that the bot is on the `Top Right` corner
            future_states = [(present_state[0]-1,present_state[1]),
            (present_state[0],present_state[1]-1)]

    # This portion of the code checks for vertial edges
    if present_state[0] == 0:
        # This means that the bot is on the `Left` edge
        if present_state[1] == 0:
            # This means that the bot is on the `Bottom` edge
        elif present_state[1] == N-1:
            # This means that the bot is on the `Top` edge
    elif present_state[0] == N-1:
        # This means that the bot is on the `Right` edge

