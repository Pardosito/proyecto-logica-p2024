import pandas as pd
from pandas import Series, DataFrame
from tabulate import tabulate

#Pedimos al usuario la cantidad de proposiciones con las que trabajará
totalPropositions = int(input("¿Cuántas proposiciones quiere evaluar?: "))

Serie1 = Series([])
totalRows = int(2**totalPropositions)
totalColumns = Series(Series for i in range(totalPropositions))

for i in totalColumns:
    for j in range(totalRows):
        y = " "
        Serie1[i]._append(Series([y]))

frame = {}

for i in totalColumns:
    frame[i] = Serie1[i]

truthTable_DF = pd.DataFrame(frame)

print(tabulate(truthTable_DF, headers = "keys", tablefmt = "psql"))