#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Prueba si se puede crear una lista correctamente. 
*/
void prueba_crear_lista()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(!lista_iterador_elemento_actual(iterador) &&
			     lista_iterador_tiene_siguiente(iterador) ==
				     false &&
			     lista,
		     "Se puede crear una lista (chequeá iterador si no va).");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

/**
 * Prueba la función lista_insertar.
*/
void prueba_insertar(lista_t *lista)
{
	int num1 = 1, num2 = 2, num3 = 3;
	lista_insertar(lista, &num1);
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 0) == 1,
		     "Se puede insertar en una lista vacía.");
	lista_insertar(lista, &num3);
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 1) == 3,
		     "Se puede insertar en una lista no vacía.");
	pa2m_afirmar(!lista_insertar(NULL, &num2),
		     "No hay errores al intentar insertar en una lista NULL.");
}

/**
 * Prueba las funciones lista_insertar_en_posicion, lista_tamanio
 * y lista_elemento_en_posicion.
*/
void prueba_insertar_en_posicion_tamanio_y_busqueda(lista_t *lista)
{
	int num0 = 0, num2 = 2, num4 = 4;
	lista_insertar_en_posicion(lista, &num0, 0);
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 0) == 0,
		     "Se puede insertar al principio.");
	lista_insertar_en_posicion(lista, &num2, 2);
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 2) == 2,
		     "Se puede insertar en el medio.");
	lista_insertar_en_posicion(lista, &num4, 24);
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 4) == 4,
		     "Se puede insertar en la posición final.");
	pa2m_afirmar(
		!lista_insertar_en_posicion(NULL, &num4, 7),
		"No hay errores al insertar en una posición de una lista NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "El tamaño es correcto.");
	pa2m_afirmar(!lista_elemento_en_posicion(lista, 34),
		     "No hay errores al buscar elemento fuera de la lista.");
}

/**
 * Prueba la función lista_quitar.
*/
void prueba_quitar()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	pa2m_afirmar(*(int *)lista_quitar(lista) == 1 &&
			     lista_tamanio(lista) == 1,
		     "Se puede quitar del final de una lista con elementos.");
	pa2m_afirmar(*(int *)lista_quitar(lista) == 0 &&
			     lista_tamanio(lista) == 0,
		     "Se puede quitar el único elemento.");
	pa2m_afirmar(lista_quitar(lista) == NULL && lista_tamanio(lista) == 0,
		     "No hay errores al quitar elementos de una lista vacía.");
	lista_destruir(lista);
}

/**
 * Prueba la función lista_quitar_de_posicion.
*/
void prueba_quitar_de_posicion()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1, num2 = 2, num3 = 3;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	lista_insertar(lista, &num2);
	lista_insertar(lista, &num3);
	pa2m_afirmar(*(int *)lista_quitar_de_posicion(lista, 0) == 0 &&
			     lista_tamanio(lista) == 3,
		     "Se puede quitar del principio.");
	pa2m_afirmar(*(int *)lista_quitar_de_posicion(lista, 1) == 2 &&
			     lista_tamanio(lista) == 2,
		     "Se puede quitar del medio.");
	pa2m_afirmar(*(int *)lista_quitar_de_posicion(lista, 32) == 3 &&
			     lista_tamanio(lista) == 1,
		     "Se puede quitar de la posición final.");
	pa2m_afirmar(*(int *)lista_quitar_de_posicion(lista, 12) == 1 &&
			     lista_tamanio(lista) == 0,
		     "Se puede quitar del principio de una lista con un elm.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 12) == NULL &&
			     lista_tamanio(lista) == 0,
		     "Se puede quitar elm. de una posición en lista vacía.");
	lista_destruir(lista);
}

/**
 * Recibe dos int pointer, los compara y devuelve cero si son iguales o -1 si no.
*/
int es_numero(void *elemento, void *contexto)
{
	if (elemento != NULL && *(int *)elemento == *(int *)contexto)
		return 0;
	return -1;
}

/**
 * Prueba la función lista_buscar_elemento.
*/
void prueba_buscar_elemento()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1, c = 1;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	pa2m_afirmar(*(int *)lista_buscar_elemento(lista, es_numero, &c) == 1,
		     "Se puede buscar un elemento con función comparador.");
	int contexto1 = 4;
	void *ptrc1 = &contexto1;
	pa2m_afirmar(lista_buscar_elemento(lista, es_numero, ptrc1) == NULL,
		     "Se devuelve NULL si no hay elemento que coincida.");
	lista_destruir(lista);
}

/**
 * Prueba las funciones lista_primero, lista_ultimo y lista_destruir_todo.
*/
void prueba_primero_ultimo_y_destruir_todo()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1, num2 = 2;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	lista_insertar(lista, &num2);
	pa2m_afirmar(*(int *)lista_primero(lista) == 0,
		     "Se puede obtener el primer elemento.");
	pa2m_afirmar(*(int *)lista_ultimo(lista) == 2,
		     "Se puede obtener el último elemento.");
	lista_destruir(lista);
}

/**
 * Prueba las funciones lista_iterador_crear, lista_iterador_elemento_actual
 * lista_iterador_tiene_siguiente y lista_iterador_avanzar.
*/
void prueba_iterador_actual_siguiente_avanzar()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1, num2 = 2;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	lista_insertar(lista, &num2);
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(*(int *)lista_iterador_elemento_actual(iterador) == 0,
		     "Iterador devuelve elemento actual.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true,
		     "Iterador devuelve true si tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == true &&
			     *(int *)lista_iterador_elemento_actual(iterador) ==
				     1,
		     "Iterador puede avanzar.");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

/**
 * Recibe dos int pointer, donde elemento es un int y contexto una lista 
 * de enteros.
 * Si el elemento se encuentra en la lista contexto, se convierte en 0.
 * Devuelve true si ninguno de los parámetros es NULL.
*/
bool convertir_en_cero_si_coincide(void *elemento, void *contexto)
{
	if (!elemento || !contexto)
		return false;
	if (*(int *)elemento == *(int *)contexto)
		*(int *)elemento = 0;
	return true;
}

/**
 * Prueba el iterador interno de la lista. (Función lista_con_cada_elemento).
*/
void prueba_iterador_interno()
{
	lista_t *lista = lista_crear();
	int num0 = 0, num1 = 1, num2 = 2, contexto = 1;
	lista_insertar(lista, &num0);
	lista_insertar(lista, &num1);
	lista_insertar(lista, NULL);
	lista_insertar(lista, &num2);
	pa2m_afirmar(lista_con_cada_elemento(lista,
					     convertir_en_cero_si_coincide,
					     &contexto) == 3,
		     "Iterador interno devuelve cantidad correcta.");
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	bool elementos_de_lista_correctos = true;
	int i = 0;
	while (i < 2) {
		if (*(int *)lista_iterador_elemento_actual(iterador) != 0)
			elementos_de_lista_correctos = false;
		lista_iterador_avanzar(iterador);
		i++;
	}
	if (lista_iterador_elemento_actual(iterador))
		elementos_de_lista_correctos = false;
	lista_iterador_avanzar(iterador);
	if (*(int *)lista_iterador_elemento_actual(iterador) != 2)
		elementos_de_lista_correctos = false;
	pa2m_afirmar(elementos_de_lista_correctos == true,
		     "Iterador interno funciona bien.");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

/**
 * Prueba las funciones cola_crear, cola_frente (con colas vacías),
 * cola_tamanio (con colas vacías) y cola_vacia (con colas vacías)
*/
void prueba_crear_cola_frente_y_vacia()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola && cola_frente(cola) == NULL &&
			     cola_tamanio(cola) == 0,
		     "Se puede crear una cola.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el tamaño de una cola vacía.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el frente de una cola vacía.");
	pa2m_afirmar(cola_vacia(cola) == true,
		     "cola_vacia devuelve true si está vacía.");
	cola_destruir(cola);
}

/**
 * Prueba las funciones cola_encolar, cola_vacia (con colas no vacías), 
 * cola_frente (con colas no vacías), cola_tamanio (con colas no vacías) 
 * y cola_desencolar.
*/
void prueba_encolar_y_desencolar()
{
	cola_t *cola = cola_crear();
	int num0 = 0;
	cola_encolar(cola, &num0);
	pa2m_afirmar(cola_vacia(cola) == false,
		     "cola_vacia devuelve false si no está vacía.");
	pa2m_afirmar(cola_tamanio(cola) == 1, "Se pueden encolar elementos.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el tamaño de una cola no vacía.");
	pa2m_afirmar(!cola_encolar(NULL, &num0),
		     "No pasa nada si quiero encolar en una cola NULL.");
	pa2m_afirmar(*(int *)cola_frente(cola) == 0,
		     "Se puede obtener el frente de una cola no vacía.");
	pa2m_afirmar(*(int *)cola_desencolar(cola) == 0 &&
			     cola_tamanio(cola) == 0,
		     "Se pueden desencolar elementos.");
	pa2m_afirmar(!cola_desencolar(cola),
		     "No pasa nada si quiero desencolar de una cola vacía.");
	pa2m_afirmar(!cola_desencolar(NULL),
		     "No pasa nada si quiero desencolar de una cola NULL.");
	cola_destruir(cola);
}

/**
 * Prueba las funciones pila_crear, pila_tope (con pilas vacías),
 * pila_tamanio (con pilas vacías) y pila_vacia (con pilas vacías)
*/
void prueba_crear_pila_tope_y_vacia()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila && pila_tope(pila) == NULL && pila_tamanio(pila) == 0,
		     "Se puede crear una pila.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el tamaño de una pila vacía.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el tope de una pila vacía.");
	pa2m_afirmar(pila_vacia(pila) == true,
		     "pila_vacia devuelve true si está vacía.");
	pila_destruir(pila);
}

/**
 * Prueba las funciones pila_apilar, pila_vacia (con pilas no vacías), 
 * pila_tope (con pilas no vacías), pila_tamanio (con pilas no vacías) 
 * y pila_desapilar.
*/
void prueba_apilar_y_desapilar()
{
	pila_t *pila = pila_crear();
	int num0 = 0;
	pila_apilar(pila, &num0);
	pa2m_afirmar(*(int *)pila_tope(pila) == 0,
		     "Se puede obtener el tope de una pila no vacía.");
	pa2m_afirmar(pila_vacia(pila) == false,
		     "pila_vacia devuelve false si no está vacía.");
	pa2m_afirmar(pila_tamanio(pila) == 1, "Se pueden apilar elementos.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede obtener el tamaño de una pila no vacía.");
	pa2m_afirmar(!pila_apilar(NULL, &num0),
		     "No pasa nada si quiero apilar en una pila NULL.");
	pa2m_afirmar(*(int *)pila_desapilar(pila) == 0 &&
			     pila_tamanio(pila) == 0,
		     "Se pueden desapilar elementos.");
	pa2m_afirmar(!pila_desapilar(pila),
		     "No pasa nada si quiero desapilar de una pila vacía.");
	pa2m_afirmar(!pila_desapilar(NULL),
		     "No pasa nada si quiero desapilar de una pila NULL.");
	pila_destruir(pila);
}

int main()
{
	pa2m_nuevo_grupo("\n================= LISTA =================");
	prueba_crear_lista();
	lista_t *lista = lista_crear();
	prueba_insertar(lista);
	prueba_insertar_en_posicion_tamanio_y_busqueda(lista);
	lista_destruir(lista);
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede buscar elemento en cierta posición.");
	prueba_quitar();
	prueba_quitar_de_posicion();
	prueba_buscar_elemento();
	prueba_primero_ultimo_y_destruir_todo();
	pa2m_nuevo_grupo(
		"\n================= ITERADOR LISTA =================");
	// Las 3 pruebas siguientes ya fueron hechas en prueba_crear_lista.
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede crear iterador.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Iterador muestra elemento actual si es NULL.");
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Iterador devuelve false si no hay elemento siguiente.");
	prueba_iterador_actual_siguiente_avanzar();
	prueba_iterador_interno();
	pa2m_nuevo_grupo("\n================= COLA =================");
	prueba_crear_cola_frente_y_vacia();
	pa2m_afirmar(__pa2m_cantidad_de_pruebas_fallidas == 0,
		     "Se puede ver el frente de una cola vacía.");
	prueba_encolar_y_desencolar();
	pa2m_nuevo_grupo("\n================= PILA =================");
	prueba_crear_pila_tope_y_vacia();
	prueba_apilar_y_desapilar();
	return pa2m_mostrar_reporte();
}