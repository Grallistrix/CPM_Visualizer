class Zdarzenie:
    def __init__(self, Nazwa, Czas, Poprzednicy=[]):
        self.Nazwa = Nazwa
        self.Czas = Czas
        self.Poprzednicy = Poprzednicy
        self.Nastepcy = []
        self.EarlyStart = 0
        self.EarlyFinish = Czas
        self.LastStart = 0
        self.LastFinish = 0
        self.Rezerwa = 0
        
    def __str__(self):
        return f"Zdarzenie {self.Nazwa} Czas: {self.Czas}\nES: {self.EarlyStart} EF: {self.EarlyFinish}\nLS: {self.LastStart} LF: {self.LastFinish}\nRezerwa: {self.Rezerwa}\nPoprzednicy: {self.Poprzednicy}\nNastepcy: {self.Nastepcy}\n"


tablicaZdarzen = []
keys = []
mapaZdarzen = {}

def LogikaForward():
    for xx in mapaZdarzen.values():
        currZdarzenie = xx
        if not currZdarzenie.Poprzednicy:
            currZdarzenie.EarlyStart = 0
            currZdarzenie.EarlyFinish = currZdarzenie.Czas
            continue
        tempEF = -1
        for i in range(len(currZdarzenie.Poprzednicy)):
            klucz = currZdarzenie.Poprzednicy[i]
            it = mapaZdarzen[klucz]
            if it.EarlyFinish > tempEF:
                tempEF = it.EarlyFinish
        currZdarzenie.EarlyStart = tempEF
        currZdarzenie.EarlyFinish = tempEF + currZdarzenie.Czas

def FindNastepcy():
    for xx in mapaZdarzen.values():
        currZdarzenie = xx
        if currZdarzenie.Poprzednicy:
            for i in range(len(currZdarzenie.Poprzednicy)):
                klucz = currZdarzenie.Poprzednicy[i]
                it = mapaZdarzen[klucz]
                it.Nastepcy.append(currZdarzenie.Nazwa)

def LogikaBackwards():
    totalTime = 0
    for xx in mapaZdarzen.values():
        keys.append(xx.Nazwa)
        if xx.EarlyFinish > totalTime:
            totalTime = xx.EarlyFinish
    keys.reverse()
    for Zdarz in keys:
        it = mapaZdarzen[Zdarz]
        if not it.Nastepcy:
            it.LastFinish = totalTime
        else:
            tempLF = totalTime
            for klucz in it.Nastepcy:
                itTemp = mapaZdarzen[klucz]
                if tempLF > itTemp.LastStart:
                    tempLF = itTemp.LastStart
            it.LastFinish = tempLF
        it.LastStart = it.LastFinish - it.Czas
        it.Rezerwa = it.LastFinish - it.EarlyFinish

def WyznaczCPM():
    CPM_Path = ""
    keys.reverse()
    for Zdarzenie in keys:
        it = mapaZdarzen[Zdarzenie]
        if it.Rezerwa == 0:
            appendChar = it.Nazwa
            CPM_Path += appendChar
    return CPM_Path

A = Zdarzenie('A', 7)
B = Zdarzenie('B', 9)
C = Zdarzenie('C', 12, ['A'])
D = Zdarzenie('D', 8, ['A', 'B'])
E = Zdarzenie('E', 9, ['D'])
F = Zdarzenie('F', 6, ['C', 'E'])
G = Zdarzenie('G', 5, ['E'])
tablicaZdarzen = [A, B, C, D, E, F, G]

i = 0
for x in tablicaZdarzen:
    mapaZdarzen[chr(65+i)] = x
    i += 1

LogikaForward()
FindNastepcy()
LogikaBackwards()
for xx in mapaZdarzen.values():
    print(xx)

print("Path to CPM:", WyznaczCPM())


