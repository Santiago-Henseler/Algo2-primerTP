#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokemon.h"
#include "tipo.h"
#include "ataque.h"


//Defino constantes
#define MAX_LINEA 200
#define COMA ';'

struct pokemon {
	struct ataque **ataques;
	int cantidad_ataques;
	char *nombre;
};

struct info_pokemon {
	struct pokemon **pokemones;
	int cantidad_pokemones;
};


struct pokemon *cargar_pokemones(linea)
{

	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));

	



	
	return NULL;
}

informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{

	FILE *archivo = fopen(*path, "r");

	if(archivo == NULL){
		return NULL;
	}

	char linea[MAX_LINEA];

	struct info_pokemon *info_pokemones = malloc(sizeof(struct info_pokemon));

	info_pokemones->cantidad_pokemones = 0;

	do{
		info_pokemones->pokemones[info_pokemones->cantidad_pokemones] = cargar_pokemones(linea);

		if(info_pokemones->pokemones[info_pokemones->cantidad_pokemones])
		{
			info_pokemones->cantidad_pokemones++;
		}

	}while(fgets(linea, 200, archivo) != NULL  && info_pokemones->pokemones[info_pokemones->cantidad_pokemones]);

	if(info_pokemones->pokemones[info_pokemones->cantidad_pokemones]){
		return info_pokemones;
	}else{
		return NULL;
	}
	
}

pokemon_t *pokemon_buscar(informacion_pokemon_t *ip, const char *nombre)
{
	return NULL;
}

int pokemon_cantidad(informacion_pokemon_t *ip)
{
	return 0;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	return NULL;
}

enum TIPO pokemon_tipo(pokemon_t *pokemon)
{
	return FUEGO;
}

const struct ataque *pokemon_buscar_ataque(pokemon_t *pokemon,const char *nombre)
{
	return NULL;
}

int con_cada_pokemon(informacion_pokemon_t *ip, void (*f)(pokemon_t *, void *),	void *aux)
{
	int i = 0;

	for(i; i < ip->cantidad_pokemones; i++){
		f(ip->pokemones[i], aux);
	}


	return i;
}

int con_cada_ataque(pokemon_t *pokemon, void (*f)(const struct ataque *, void *), void *aux)
{
	int i = 0;

	for(i; i < pokemon->cantidad_ataques; i++){
		f(pokemon->ataques[i], aux);
	}


	return i;
}

void pokemon_destruir_todo(informacion_pokemon_t *ip)
{
}
