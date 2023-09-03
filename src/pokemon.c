#include <stdbool.h>
#include "pokemon.h"
#include "tipo.h"
#include "ataque.h"
#include "cargar_pokemones.h"

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

struct pokemon *cargar_nombre_pokemon(char nombre[MAX_LINEA])
{
	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));

	if(nuevo_pokemon == NULL)
		return NULL;

	char tipo;

	int cantidad = sscanf(nombre, "%[^;];%c", nuevo_pokemon->nombre, &tipo);

	if(cantidad < 2)
		return NULL;

	nuevo_pokemon->tipo = definir_tipo(tipo);

	return nuevo_pokemon;
}

void validar_pokemones_leidos(struct info_pokemon *ip)
{

	for(int i = 0; i < ip->cantidad_pokemones; i++){
		if(ip->pokemones[i]->cantidad_ataques != 3){
			for(int j = 0; j < ip->pokemones[i]->cantidad_ataques; j++){
				free(ip->pokemones[i]->ataques[j]);
			}
			free(ip->pokemones[i]);
			ip->cantidad_pokemones--;
		}
	}

}

void leer_pokemones(FILE* archivo, struct info_pokemon *ip)
{
	char linea[MAX_LINEA];
	bool error = false;
	int linea_recorrida = 0;

	while(fgets(linea, 200, archivo) != NULL && !error){

		if(linea_recorrida < 1){

			ip->pokemones[ip->cantidad_pokemones] = cargar_nombre_pokemon(linea);

			if(ip->pokemones[ip->cantidad_pokemones]){
				ip->pokemones[ip->cantidad_pokemones]->cantidad_ataques = 0;
				ip->pokemones[ip->cantidad_pokemones]->ataques = malloc(sizeof(struct ataque));
				if(ip->pokemones[ip->cantidad_pokemones]->ataques == NULL){
					error = true;
				}
			}else{
				error = true;
			}

		}else{	

			ip->pokemones[ip->cantidad_pokemones]->ataques[ip->pokemones[ip->cantidad_pokemones]->cantidad_ataques] = cargar_ataque_pokemon(linea); 
			
			if(ip->pokemones[ip->cantidad_pokemones]->ataques[ip->pokemones[ip->cantidad_pokemones]->cantidad_ataques] == NULL){
				error = true;
			}else{
				ip->pokemones[ip->cantidad_pokemones]->cantidad_ataques++;
			}	
		}

		if(linea_recorrida == 3){
			ip->cantidad_pokemones++;
			linea_recorrida = 0;
		}else{
			linea_recorrida++;
		}
		
	}

	validar_pokemones_leidos(ip);
}

informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{

	FILE *archivo = fopen(path, "r");

	if(archivo == NULL)
		return NULL;

	struct info_pokemon *info_pokemones = (struct info_pokemon*)malloc(sizeof(struct info_pokemon));

	info_pokemones->pokemones = (struct pokemon**)malloc(sizeof(struct pokemon));

	if(info_pokemones == NULL || info_pokemones->pokemones == NULL){
		free(info_pokemones);
		free(info_pokemones->pokemones);
		return NULL;
	}

	info_pokemones->cantidad_pokemones = 0;

	leer_pokemones(archivo, info_pokemones);

	fclose(archivo);

	if(info_pokemones->cantidad_pokemones == 0)
		return NULL;
	
	return info_pokemones;
}


//hecho sin errores  #desde
pokemon_t *pokemon_buscar(informacion_pokemon_t *ip, const char *nombre)
{

	struct pokemon *aux =  NULL;

	for(int i = 0; ip->cantidad_pokemones; i++){
		if(strcmp(ip->pokemones[i]->nombre, nombre) == 0){
			aux = ip->pokemones[i];
		}
	}

	return aux;
}

int pokemon_cantidad(informacion_pokemon_t *ip)
{

	if(ip == NULL)
		return -1;

	return ip->cantidad_pokemones;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{

	if(pokemon == NULL)
			return NULL;

	return pokemon->nombre;
}

enum TIPO pokemon_tipo(pokemon_t *pokemon)
{
	
	if(pokemon == NULL)
		return NORMAL;
	
	return pokemon->tipo;
}

const struct ataque *pokemon_buscar_ataque(pokemon_t *pokemon,const char *nombre)
{
	
	struct ataque *aux =  NULL;

	for(int i = 0; pokemon->cantidad_ataques; i++){
		if(strcmp(pokemon->ataques[i]->nombre, nombre) == 0){
			aux = pokemon->ataques[i];
		}
	}

	return aux;
}
//hecho sin errores  #hasta

int con_cada_pokemon(informacion_pokemon_t *ip, void (*f)(pokemon_t *, void *),	void *aux)
{

	//ordenar_pokemones();

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

	for(int i = 0; i < ip->cantidad_pokemones; i++){
		for(int j = 0; j < ip->pokemones[i]->cantidad_ataques;  j++){
			free(ip->pokemones[i]->ataques[j]);
		}
		free(ip->pokemones[i]);
	}

	free(ip);

}
