from pandas import Series, DataFrame
import pandas as pd
from tabulate import tabulate

#Series
ser_1 = Series([1, 1, 2, -3, -5, 8, 13])
print(ser_1)
print(ser_1.values)
print(ser_1.index)

ser_2 = Series([1, 1, 2, -3, -5], index = ['a', 'b', 'c', 'd', 'e'])
#print(ser_2)
#print(ser_2['d'])
#print(ser_2[ser_2 > 0])
#print(ser_2 * 2)

dict_1 = {'matemáticas':80, "quimica":100, "logica":90}
#print(dict_1)
ser_3 = Series(dict_1)
#print(ser_3)

#DataFrames

data_1 = {
    "Estado": ["JA","CO","MX","JA","MI"],
    "Año": [2012, 2013, 2014, 2014, 2015],
    "Version": [5.0, 5.1, 5.2, 4.0, 4.1]
}
#print(data_1)
df_1 = DataFrame(data_1)
#print(df_1)

df_2 = DataFrame(data_1, columns = ["Año", "Version", "Estado"])
#print(df_2)

df_3 = DataFrame(data_1, columns = ["Año", "Version", "Estado", "NewColumn"])
#print(df_3)

df_4 = df_3.rename(columns = {"NewColumn":"Rank"})
#print(df_4)

ranks_df4 = [1,1,2,3,4]
df_4["Rank"] = ranks_df4

#print(df_4["Estado"])
#print(df_4.iloc[0])
#print(df_4["Estado"].iloc[1])

ser_nombre = Series(["maria", "lupe", "omar", "antonio", "checo"])
ser_edad = Series([21,20,22,19,20])
ser_estado = Series(["jalisco", "michoacan", "puebla", "guanajuato", "tabasco"])

frame = {"Nombre":ser_nombre, "Edad":ser_edad, "Estado":ser_estado}
estudiantes_df = pd.DataFrame(frame)
#print(estudiantes_df)

calificacion = [70,85,100,90,60]
estudiantes_df["calificacion"] = calificacion
#print(estudiantes_df)

#print(estudiantes_df[["Nombre", "calificacion"]])

for index, row in estudiantes_df.iterrows():
    for column_name, value in estudiantes_df.items():
        print(column_name)
        print(value)
        print()

print(tabulate(estudiantes_df, headers="keys", tablefmt="psql"))