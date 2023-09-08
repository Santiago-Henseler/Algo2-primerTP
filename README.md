<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1

## Repositorio de Santiago Henseler - 110732 - shenseler@fi.uba.ar

- Para compilar:

```bash
gcc *.c -o entrega -std=c99 -Wall -Wconversion -Werror -lm
```

- Para ejecutar:

```bash
./entrega
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./entrega
```
---
##  Funcionamiento

En este TP voy a explicar como implemente la funcion `pokemon_cargar_archivo()` porque considero que fue la más dificil de implementar.

Al llamar a la funcion, se debe pasar por parametro un archivo. Si el archivo es NULL o si no se puede abrir la funcion termina y devuelve NULL.

Si no termina, se reserva memoria dinamica en el puntero `info_pokemones` con `malloc()` para almacenar todos los pokemones validos que esten en el archivo. Si no se puede reservar esa memoria la funcion termina y devuelve NULL.

Si se reserva memoria correctamente se llama a la funcion `leer_pokemones()`. Luego de leer todos los pokemones si la cantidad de pokemones validos es mayor a 0 se devuelve el puntero donde se almacenaron `(info_pokemones)`. Si no hay pokemones validos devuelve NULL.

*Aclaración:* La funcion `pokemon_cargar_archivo()` la subdividi en varios modulos para que sea mas lejible el codigo y ademas encontrar errores en el codigo sea mucho más sencillo.
	
<div align="center">
<img width="70%" src="img/flujo1.jpg">
</div>

---

## Respuestas a las preguntas teóricas

-  *Explicación de cómo se logra que los pokemon queden ordenados alfabéticamente:*
<br/>

La implementación para que los pokemons queden ordenados alfabeticamente la hice en el archivo `src/pokemon.c` en la función `ordenar_pokemones()`. La funcion recibe por parametro todos los pokemones validos y con un `for` itera pokemon a pokemon comparandolos afabeticamente con el resto almacenando en la variable `min` la posición del menor elemento. Luego intercambia   
<br/>
-  *Analisis de la complejidad de la funcion que ordena alfabéticamente los pokemons:*
  
```c
void ordenar_pokemones(struct info_pokemon *ip)
{
	for(int i = 0; i < ip->cantidad_pokemones; i++){ // ---> N
		int min = i;    // ---> 1

		for(int j = i; j < ip->cantidad_pokemones; j++){ // ---> N
			if(strcmp(ip->pokemones[min]->nombre, ip->pokemones[j]->nombre) > 0){
				min = j; // ---> 1
			}
		}

		struct pokemon *aux = ip->pokemones[min]; // ---> 1
		ip->pokemones[min] = ip->pokemones[i]; // ---> 1 
		ip->pokemones[i] = aux; // ---> 1

	}
}
```

Contando todas las instruciónes llegamos a la siguiente ecuación: `T(n) = (1+1+1+1)*n*n` . Entonces el algoritmo de ordenar_pokemones tiene una complejidad de *O(n²)* porque: `4n² < N * n² , ∀ N > 4`

<br/>
- *Disposición de la memoria en el programa:*
<br/>
	Cuando finaliza la funcion `pokemon_cargar_archivo()` la memoria queda distribuida de la siguiente manera:

<div align="center">
<img width="70%" src="img/memoria1.png">
</div>

	Cuando se usa la funcion `pokemon_destruir_todo()` se iteran todos los campos de la memoria como esta distribuida en la imagen de arriba y se los va borrando desde adentro hacia afuera para no perder los punteros. 
