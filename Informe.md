# Cambios
1. comentar variables no usadas, la mas imp es y porque se calculaba un monton de veces
2. size_t size_to_alloc = YDIM*sizeof(double); en lugar de calcularlo cada vez que llamaba malloc
3. comente la linea de srand time para usar siempre missma seed
4. define xdim ydim en lugar de int 
5. cambie %d por %i en los prints
6. hice loop unrolling de for de la primera l desp de for de k en compute
7. ver analysis 1-8
8. saque la multiplicacion por 4 en los for y la pase directamente a c/ valor de kern
9. saque todos los + 1 en tmp_sum (9) e inicie accum en 9 (analysis 9)
10. memset analysis 10
11. elimine las mult que daban 0 y por consiguiente la suma de esos resultados (analysis 11)
12. hasta nalysis 14 no hay mas cambios que los hasta aca hechos
13. los nuevos cambios estan descritos en los analysis.txt

# ver -> LISTO
arr[9999][x] = 9.539862 siempre -- esta
arr[x][9998] = arr[x][9999] siempre -- esta
arr[0][x] = 0 siempre -- esta
arr[x][9999] = arr[x+1][0] siempre => arr[x][9998] = arr[x][9999] = arr[x+1][0]  -- esta