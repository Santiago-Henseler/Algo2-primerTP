#include "src/pokemon.h"
#include "src/ataque.h"
#include <stdio.h>

void mostrar_pokemon(pokemon_t *p, void *aux)
{
	int *n = aux;
	printf("(%i): %s\n", *n, pokemon_nombre(p));
	(*n)++;
}

void mostrar_ataque(const struct ataque *a, void *aux)
{
	printf("%s: %i\n", a->nombre, a->poder);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("%s <nombre archivo> [pokemon] [ataque]\n", argv[0]);
		return -1;
	}

	char *archivo = argv[1];
	char *nombre_a_buscar = argc > 2 ? argv[2] : "Pikachu";
	char *ataque_a_buscar = argc > 3 ? argv[3] : "Latigo";

	informacion_pokemon_t *info = pokemon_cargar_archivo(archivo);
	if (!info) {
		printf("No se pudo leer el archivo\n");
		return -1;
	}

	int n = 0;
	con_cada_pokemon(info, mostrar_pokemon, &n);

	printf("\nVoy a buscar a %s...\n", nombre_a_buscar);

	pokemon_t *p = pokemon_buscar(info, nombre_a_buscar);
	if (!p)
		printf("No encontré ese pokemon\n");
	else {
		printf("Pokemon encontrado: %s\n", pokemon_nombre(p));
		con_cada_ataque(p, mostrar_ataque, NULL);

		printf("Ataque %s encontrado: %s\n", ataque_a_buscar,
		       pokemon_buscar_ataque(p, ataque_a_buscar) ? "SI" : "NO");
	}

	pokemon_destruir_todo(info);

	return 0;
}
