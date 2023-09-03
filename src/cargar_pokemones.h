#ifndef CARGAR_POKEMONES_H_
#define CARGAR_POKEMONES_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokemon.h"
#include "ataque.h"

//Defino constantes
#define MAX_LINEA 200
#define MAX_NOMBRE 70

struct ataque *cargar_ataque_pokemon(char linea[MAX_LINEA]);

enum TIPO definir_tipo(char texto);


#endif // CARGAR_POKEMONES_H_