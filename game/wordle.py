import random as rd
from typing import List
def selRandWord():
    f = open("5lw.txt")
    retVal = rd.choice(f.readlines())
    f.close()
    return retVal

def checkWord(w: str ,input: str):
    
    w = w.strip()
    print(w)
    print("piano")
    if w.__len__() != input.__len__():
        return []
    retVal = []
    for index in range(0,input.__len__()):
        if input[index] not in w:
            retVal.append(0)
        elif input[index] == w[index]:
            retVal.append(2)
        else:
            retVal.append(1)
    return retVal

print(checkWord(selRandWord(),"piano"))
