#include "src/tipo.h"
#include <stdio.h>
#include <string.h>
#include "src/pokemon.h"
#include "src/ataque.h"
#include "pa2m.h"

#define ARCHIVO_INEXISTENTE \
	"ejemplos/asdaskjhdsjfhgasjkdhfgaksjldhfgsdjkfhgdsfjkhg"
#define ARCHIVO_OK "ejemplos/correcto.txt"
#define ARCHIVO_LARGO "ejemplos/largo.csv"
#define ARCHIVO_UNO "ejemplos/uno_solo.png"
#define ARCHIVO_ERR "ejemplos/incorrecto.txt"

#define CANTIDAD_ARCHIVO_OK 6
#define CANTIDAD_ARCHIVO_LARGO 600

#define UN_POKEMON "Pikachu"
#define UN_POKEMON_TIPO ELECTRICO

struct datos_pokemon {
	char *nombre;
	enum TIPO tipo;
};

const struct ataque UN_POKEMON_ATAQUES[] = {
	{ .nombre = "Rayo", .tipo = ELECTRICO, .poder = 5 },
	{ .nombre = "Latigo", .tipo = NORMAL, .poder = 1 },
	{ .nombre = "Chispa", .tipo = ELECTRICO, .poder = 1 },
};

const struct datos_pokemon POKEMON_ESPERADO[] = {
	{ .nombre = "Cacnea", .tipo = PLANTA },
	{ .nombre = "Charmander", .tipo = FUEGO },
	{ .nombre = "Floatzel", .tipo = AGUA },
	{ .nombre = "Larvitar", .tipo = ROCA },
	{ .nombre = "Pikachu", .tipo = ELECTRICO },
	{ .nombre = "Togepi", .tipo = NORMAL }
};

int ataque_es_igual(const struct ataque *a1, const struct ataque *a2)
{
	return strcmp(a1->nombre, a2->nombre) == 0 && a1->tipo == a2->tipo &&
	       a1->poder == a2->poder;
}

void verificar_pokemon_n(pokemon_t *p, void *i)
{
	int *n = i;
	pa2m_afirmar(
		strcmp(pokemon_nombre(p), POKEMON_ESPERADO[*n].nombre) == 0,
		"El nombre del pokemon es el esperado por orden alfabetico");
	(*n)++;
}

void contar_pokemon_n(pokemon_t *p, void *i)
{
	int *n = i;
	(*n)++;
}

void verificar_ataque_n(const struct ataque *a, void *i)
{
	int *n = i;
	pa2m_afirmar(ataque_es_igual(a, UN_POKEMON_ATAQUES + *n),
		     "El ataque es correcto");
	(*n)++;
}

void no_puedo_cargar_archivos_null()
{
	pa2m_afirmar(pokemon_cargar_archivo(NULL) == NULL,
		     "No se puede cargar un archivo con nombre NULL");
}

void no_puedo_cargar_archivos_inexistentes()
{
	pa2m_afirmar(pokemon_cargar_archivo(ARCHIVO_INEXISTENTE) == NULL,
		     "No se puede cargar un archivo inexistente");
}

void cargar_archivo_deja_de_leer_al_encontrar_datos_invalidos()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_UNO)) != NULL,
		     "Puedo cargar un archivo parcialmente correcto");
	pa2m_afirmar(pokemon_cantidad(info) == 1,
		     "Se pudo leer un solo pokemon");
	pokemon_destruir_todo(info);
}

void cargar_archivo_devuelve_NULL_si_no_hay_al_menos_un_pokemon_valido()
{
	pa2m_afirmar(pokemon_cargar_archivo(ARCHIVO_ERR) == NULL,
		     "No se puede cargar un archivo sin pokemon validos");
}

void cargar_archivo_carga_todos_los_pokemon_disponibles()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_OK)) != NULL,
		     "Puedo cargar un archivo correcto");
	pa2m_afirmar(pokemon_cantidad(info) == CANTIDAD_ARCHIVO_OK,
		     "Se cargo la cantidad correcta de pokemon");

	pokemon_destruir_todo(info);
}

void cargar_archivo_carga_todos_los_pokemon_disponibles_en_un_archivo_largo()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_LARGO)) != NULL,
		     "Puedo cargar un archivo largo correctamente");
	pa2m_afirmar(pokemon_cantidad(info) == CANTIDAD_ARCHIVO_LARGO,
		     "Se cargo la cantidad correcta de pokemon");

	pokemon_destruir_todo(info);
}

void cargar_archivo_carga_datos_correctos()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_UNO)) != NULL,
		     "Cargo un pokemon");

	pokemon_t *p;
	pa2m_afirmar((p = pokemon_buscar(info, UN_POKEMON)) != NULL,
		     "Puedo buscar (y encuentro) el unico pokemon");

	pa2m_afirmar(strcmp(pokemon_nombre(p), UN_POKEMON) == 0,
		     "El nombre del pokemon obtenido es correcto");
	pa2m_afirmar(pokemon_tipo(p) == UN_POKEMON_TIPO,
		     "El tipo del pokemon obtenido es correcto");

	for (int i = 0; i < 3; i++) {
		const struct ataque *a;
		pa2m_afirmar(
			(a = pokemon_buscar_ataque(
				 p, UN_POKEMON_ATAQUES[i].nombre)) != NULL,
			"Busco uno de los ataques del pokemon y lo encuentro");
		if (!a)
			continue;
		pa2m_afirmar(ataque_es_igual(a, UN_POKEMON_ATAQUES + i),
			     "La información del ataque es correcta");
	}

	pokemon_destruir_todo(info);
}

void cargar_archivo_carga_datos_correctos_de_todos_los_pokemon()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_OK)) != NULL,
		     "Cargo varios pokemon");

	for (int i = 0;
	     i < sizeof(POKEMON_ESPERADO) / sizeof(struct datos_pokemon); i++) {
		pokemon_t *p;
		const struct datos_pokemon *d = POKEMON_ESPERADO + i;

		pa2m_afirmar(
			(p = pokemon_buscar(info, d->nombre)) != NULL,
			"Puedo buscar (y encuentro) el pokemon que corresponde segun orden alfabetico");

		if (!p)
			continue;

		pa2m_afirmar(strcmp(pokemon_nombre(p), d->nombre) == 0,
			     "El nombre del pokemon obtenido es correcto");
		pa2m_afirmar(pokemon_tipo(p) == d->tipo,
			     "El tipo del pokemon obtenido es correcto");
	}

	pokemon_destruir_todo(info);
}

void iterar_pokemon_recorre_por_orden_alfabetico()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_OK)) != NULL,
		     "Cargo varios pokemon");

	int n = 0;
	pa2m_afirmar(
		con_cada_pokemon(info, verificar_pokemon_n, &n) ==
			CANTIDAD_ARCHIVO_OK,
		"La funcion con_cada_pokemon devuelve la cantidad de pokemon");
	pokemon_destruir_todo(info);
}

void iterar_pokemon_recorre_todos_los_pokemon()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_LARGO)) != NULL,
		     "Cargo muchos pokemon");
	int n = 0;

	pa2m_afirmar(
		con_cada_pokemon(info, contar_pokemon_n, &n) ==
			CANTIDAD_ARCHIVO_LARGO,
		"La funcion con_cada_pokemon devuelve la cantidad de pokemon");
	pa2m_afirmar(n == CANTIDAD_ARCHIVO_LARGO,
		     "La función se invocó la cantidad de veces esperada");
	pokemon_destruir_todo(info);
}

void iterar_pokemon_con_funcion_null_no_hace_nada()
{
	informacion_pokemon_t *info;
	info = pokemon_cargar_archivo(ARCHIVO_OK);

	int n = 0;
	pa2m_afirmar(
		con_cada_pokemon(info, NULL, &n) == 0,
		"Iterar pokemon con una funcion inválida recorre 0 pokemon");
	pokemon_destruir_todo(info);
}

void iterar_ataques_recorre_todos_los_ataques()
{
	informacion_pokemon_t *info;
	pa2m_afirmar((info = pokemon_cargar_archivo(ARCHIVO_UNO)) != NULL,
		     "Cargo un pokemon");
	pokemon_t *p = pokemon_buscar(info, UN_POKEMON);

	int n = 0;
	pa2m_afirmar(
		con_cada_ataque(p, verificar_ataque_n, &n) == 3,
		"Iterar ataques con una funcion válida recorre todos los ataques");

	pokemon_destruir_todo(info);
}

void iterar_ataques_con_funcion_null_no_hace_nada()
{
	informacion_pokemon_t *info;
	info = pokemon_cargar_archivo(ARCHIVO_UNO);
	pokemon_t *p = pokemon_buscar(info, UN_POKEMON);

	int n = 0;
	pa2m_afirmar(
		con_cada_ataque(p, NULL, &n) == 0,
		"Iterar ataques con una funcion inválida recorre 0 ataques");
	pokemon_destruir_todo(info);
}

void pruebas_null()
{
	int i = 0;
	void *nullnt = &i; //no debería hacer esto, pero me dio fiaca

	pa2m_afirmar(pokemon_buscar(NULL, NULL) == NULL,
		     "No puedo buscar pokemon con info NULL");
	pa2m_afirmar(pokemon_buscar(nullnt, NULL) == NULL,
		     "No puedo buscar pokemon con nombre NULL");
	pa2m_afirmar(pokemon_cantidad(NULL) == 0,
		     "Pokemon cantidad da 0 si la info es NULL");
	pa2m_afirmar(pokemon_nombre(NULL) == NULL,
		     "Pokemon nombre da NULL si la info es NULL");
	pa2m_afirmar(pokemon_tipo(NULL) == NORMAL,
		     "Pokemon tipo da NORMAL si la info es NULL");
	pa2m_afirmar(con_cada_pokemon(NULL, verificar_pokemon_n, nullnt) == 0,
		     "No debería iterar pokemon si no tengo info");
	pa2m_afirmar(con_cada_ataque(NULL, verificar_ataque_n, nullnt) == 0,
		     "No debería iterar ataques si no tengo pokemon");
	pokemon_destruir_todo(NULL);
}

int main()
{
	pa2m_nuevo_grupo("------------ PRUEBAS DEL TP1 ------------");

	pa2m_nuevo_grupo("PRUEBAS DE CARGAR ARCHIVOS");
	no_puedo_cargar_archivos_null();
	no_puedo_cargar_archivos_inexistentes();
	cargar_archivo_deja_de_leer_al_encontrar_datos_invalidos();
	cargar_archivo_devuelve_NULL_si_no_hay_al_menos_un_pokemon_valido();
	cargar_archivo_carga_todos_los_pokemon_disponibles();
	cargar_archivo_carga_todos_los_pokemon_disponibles_en_un_archivo_largo();

	pa2m_nuevo_grupo("PRUEBAS CON LOS DATOS CARGADOS");
	cargar_archivo_carga_datos_correctos();
	cargar_archivo_carga_datos_correctos_de_todos_los_pokemon();

	pa2m_nuevo_grupo("PRUEBAS CON EL ITERADOR DE POKEMON");
	iterar_pokemon_recorre_por_orden_alfabetico();
	iterar_pokemon_recorre_todos_los_pokemon();
	iterar_pokemon_con_funcion_null_no_hace_nada();

	pa2m_nuevo_grupo("PRUEBAS CON EL ITERADOR DE ATAQUES");
	iterar_ataques_recorre_todos_los_ataques();
	iterar_ataques_con_funcion_null_no_hace_nada();

	pa2m_nuevo_grupo("PRUEBAS NULL");
	pruebas_null();

	return pa2m_mostrar_reporte();
}
