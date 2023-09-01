#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "pokemon.h"
#include "tipo.h"
#include "ataque.h"


//Defino constantes
#define MAX_LINEA 200
#define MAX_NOMBRE 70

struct pokemon {
	struct ataque **ataques;
	enum TIPO tipo;
	int cantidad_ataques;
	char nombre[MAX_NOMBRE];
};

struct info_pokemon {
	struct pokemon **pokemones;
	int cantidad_pokemones;
};

enum TIPO definir_tipo(char texto)
{
    enum TIPO tipo = -1;

    if(texto == 'N'){
        tipo = NORMAL;
    }else if(texto == 'F'){
        tipo = FUEGO;
    }else if(texto == 'A'){
        tipo = AGUA;
    }else if(texto ==  'P'){
        tipo = PLANTA;
    }else if(texto == 'E'){
        tipo = ELECTRICO;
    }else if(texto == 'R'){
        tipo = ROCA;
    }

    return tipo;
}

struct pokemon *cargar_nombre_pokemon(char linea[MAX_LINEA])
{

	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));

	if(nuevo_pokemon == NULL)
		return NULL;

	char tipo;

	int cantidad = sscanf(linea, "%[^;];%c", nuevo_pokemon->nombre, &tipo);

	if(cantidad < 2)
		return NULL;

	enum TIPO validar_tipo = definir_tipo(tipo);
	
	if(validar_tipo == -1)
		return NULL;

	nuevo_pokemon->tipo = definir_tipo(tipo);

	return nuevo_pokemon;
}

informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{

	FILE *archivo = fopen(path, "r");

	if(archivo == NULL)
		return NULL;

	struct info_pokemon *info_pokemones = malloc(sizeof(struct info_pokemon));

	if(info_pokemones == NULL)
		return NULL;

	info_pokemones->cantidad_pokemones = 0;

	int linea_recorrida = 0;
	char linea[MAX_LINEA];
	bool error = false;
	
	while(fgets(linea, 200, archivo) != NULL && !error){

		if(linea_recorrida < 1){
			info_pokemones->pokemones[info_pokemones->cantidad_pokemones] = cargar_nombre_pokemon(linea);

			if(info_pokemones->pokemones[info_pokemones->cantidad_pokemones]){
				info_pokemones->cantidad_pokemones++;
			}else{
				error = true;
			}

		}else{
			//cargar_ataque_pokemon(linea,);
		}

		if(linea_recorrida == 3){
			linea_recorrida = 0;
		}else{
			linea_recorrida++;
		}
	}

	return info_pokemones;
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
	for(int i = 0; i < ip->cantidad_pokemones; i++){
		f(ip->pokemones[i], aux);
	}

	return  ip->cantidad_pokemones;
}

int con_cada_ataque(pokemon_t *pokemon, void (*f)(const struct ataque *, void *), void *aux)
{
	for(int i = 0; i < pokemon->cantidad_ataques; i++){
		f(pokemon->ataques[i], aux);
	}

	return pokemon->cantidad_ataques;
}

void pokemon_destruir_todo(informacion_pokemon_t *ip)
{
}
