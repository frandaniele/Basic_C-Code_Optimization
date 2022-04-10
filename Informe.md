# Cambios
1. comentar variables no usadas, la mas imp es y porque se calculaba un monton de veces
2. size_t size_to_alloc = YDIM*sizeof(double); en lugar de calcularlo cada vez que llamaba malloc
3. comente la linea de srand time para usar siempre missma seed
4. define xdim ydim en lugar de int 
5. cambie %d por %i en los prints
6. hice loop unrolling de for de la primera l desp de for de k en compute