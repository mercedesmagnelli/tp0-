#include "client.h"
#include<readline/readline.h>
int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	log_trace(logger, "Hola, soy un log!");

	config = iniciar_config();

	 ip = config_get_string_value(config, "IP");
	 log_trace(logger, "Obtuve: %s", ip);
	 puerto = config_get_string_value(config, "PUERTO");
	 log_trace(logger, "Obtuve: %s", puerto);
	 valor = config_get_string_value(config, "VALOR");
	 log_trace(logger, "Obtuve: %s", valor);



	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);



}

t_log* iniciar_logger(void)
{

	return  log_create("logTP0.log", "tp0log", 1, LOG_LEVEL_TRACE);
}

t_config* iniciar_config(void)
{
	return config_create("/home/utnso/tp0-2C/client/src/tp0.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");
	while(strcmp(leido, "") != 0)
	{
		log_info(logger, leido);
		free(leido);
		leido = readline(">");
	}
	free(leido);

}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;
	int tamanio;

	paquete = crear_super_paquete();

	leido = readline(">");
	while(strcmp("", leido) != 0){
		tamanio = strlen(leido) + 1;
		agregar_a_paquete(paquete, leido, tamanio);
		free(leido);
		leido = readline(">");
	}
	free(leido);

	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);


}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
