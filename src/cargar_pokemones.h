#ifndef CARGAR_POKEMONES_H_
#define CARGAR_POKEMONES_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ataque.h"
#include "pokemon.h"

// Defino constantes
#define MAX_LINEA 200
#define MAX_NOMBRE 70

// Recibe un string no NULL
// Devuelve un pointer a un ataque rellenado con la informacion del string
struct ataque *cargar_ataque_pokemon(char linea[MAX_LINEA]);

// Recibe un char
// Devuelve un tipo si el char es valido, sino devuelve -1
enum TIPO definir_tipo(char texto);

#endif // CARGAR_POKEMONES_H_