# This document will serve me as a documentation to inner workings of the program




## Jump instruction handelling
The jumb instruction will be handaled as such:

1. Before the execution of the code, check that all the brackets have a match.
    1.1 Count them
    1.2 Check that every open bracket corresponds to a closing bracket and vice-versa

2.
    Make A structure(Just a list at first) that will hold pairs of uint type positions of brackets.
    The format will be: key = value i.e. [ { a pair }, { one_pos = other_pos }, { another pair }]
    Positions will be duplicated to be able to access them other way around
