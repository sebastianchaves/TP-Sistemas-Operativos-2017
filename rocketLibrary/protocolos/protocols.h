#ifndef PROTOCOLOS_PROTOCOLS_H_
#define PROTOCOLOS_PROTOCOLS_H_

//define los TIPOS de mensaje que envia cada proceso (el primer int para identificar que esta pidiendo)
typedef enum PROTOCOLO_CONSOLA_A_KERNEL {

	HANDSHAKE_CONECTAR_CONSOLA_A_KERNEL,
	ENVIO_TEXTO_CONSOLA,
	CONSOLA_PIDE_INICIAR_PROCESO, //[tamanio del path] [path]
	CONSOLA_PIDE_FINALIZAR_PROCESO,
	IMPRESION_EXITOSA,
	IMPRESION_FALLIDA,

} PROTOCOLO_CONSOLA_A_KERNEL;

typedef enum PROTOCOLO_CPU_A_KERNEL {

	HANDSHAKE_CONECTAR_CPU_A_KERNEL,
	PEDIDO_BLOQUE_MEMORIA, //[pid][cantidad de bytes]
	LIBERAR_BLOQUE,
	TERMINE_SENTENCIA,
	WAIT,
	SIGNAL,
	ASIGNAR_VALOR_COMPARTIDA,
	OBTENER_VALOR_COMPARTIDA,
	PROGRAMA_TERMINADO,
	PRIMITIVA_ABRIR_ARCHIVO,
	PRIMITIVA_BORRAR_ARCHIVO,
	PRIMITIVA_CERRAR_ARCHIVO,
	PRIMITIVA_MOVER_CURSOR_ARCHIVO,
	PRIMITIVA_ESCRIBIR_ARCHIVO,
	PRIMITIVA_LEER_ARCHIVO,
	ABORTAR_PROGRAMA,
	ME_DESCONECTO

} PROTOCOLO_CPU_A_KERNEL;

typedef enum PROTOCOLO_KERNEL_A_CPU {

	HANDSHAKE_CONEXION_DE_CPU_A_KERNEL_ACEPTADA,
	ENVIO_TAMANIO_PAGINA,
	ENVIO_TEXTO_A_CPU,
	EJECUTAR_PROGRAMA, //[tamanio PCB][PCB]
	PEDIDO_MEMORIA_RECHAZADO,
	COMPARTIDA_INEXISTENTE,
	ENVIADO_VALOR_COMPARTIDA,
	VALOR_COMPARTIDA_ASIGNADO,
	SEGUI_EJECUTANDO,
	DIRECCION_ENVIADA,
	RESERVA_INVALIDA,
	LIBERACION_EXITOSA,
	LIBERACION_INVALIDA,
	ENVIO_PCB,
	SEMAFORO_OPERADO_CORRECTAMENTE,
	SEMAFORO_INEXISTENTE,


	/*
	 * Cuando reciba este mensaje, la cpu debe enviar el pcb actual, y luego recibira otro pcb previamente recibiendo el mensaje "EJECUTAR_PROGRAMA"
	 */
	CAMBIAR_PROCESO,

	PROCESO_FINALIZADO_CORRECTAMENTE,

	ARCHIVO_INVALIDO,
	APERTURA_EXITOSA,
	BORRADO_EXITOSO,
	BORRADO_ERRONEO,
	CERRADO_EXITOSO,
	MOVER_CURSOR_EXITOSO,
	ESCRITURA_EXITOSA,
	LECTURA_EXITOSA,
	PERMISO_ARCHIVO_INVALIDO, //enviado cuando se hace una operacion sobre un archivo con permisos faltantes

	ESPACIO_INSUFICIENTE_EN_FS

} PROTOCOLO_KERNEL_A_CPU;

typedef enum PROTOCOLO_KERNEL_A_CONSOLA {

	HANDSHAKE_CONEXION_DE_CONSOLA_A_KERNEL_ACEPTADA = -1,

	/*
	 * Proceso aceptado en el sistema, recibe:
	 *[PID]
	 */
	PROCESO_INICIADO = -9,

	/*
	 * El proceso queda en espera por nivel de multiprog, recibe [PID]
	 */
	PROCESO_EN_ESPERA = -10,

	/*
	 * Proceso rechazado recibe:
	 *	1-[Motivo Rechazo] del tipo EXIT_CODE
	 */
	PROCESO_RECHAZADO = -11,

	/*
	 * Informo a la consola que el proceso recibio sus primeras paginas iniciales
	 * el proceso pudo haberse iniciado y devuelto el PID a la consola pero quizas no se le pudo asignar paginas
	 */
	PROCESO_RECIBIO_PAGINAS_INICIALES = -12,

	/*
	 * Nueva impresion
	 */
	NUEVA_IMPRESION = -13,

	/*
	 * Mensaje enviado cuando se termina un proceso seguido del EC
	 */
	PROCESO_TERMINADO = -14,

	/*
	 * Le aviso a la consola que el proceso paso de New a Ready porque quiero que me mande el codigo del programa
	 */
	PROCESO_PASO_DE_NEW_A_READY = -15,

} PROTOCOLO_KERNEL_A_CONSOLA;

typedef enum PROTOCOLO_KERNEL_Y_CPU_A_MEMORIA {

	INICIALIZAR_PROGRAMA, //[PID] [Cantidad de paginas codigo + cantidad paginas de stack]
	PEDIDO_ASIGNAR_PAGINAS, // [PID][Cantidad de paginas de heap]
	ENVIO_TEXTO_A_MEMORIA, // no usar, solo para entrega 1
	ESCRIBIR_A_MEMORIA, // [PID][pagina][offset][tamanio][contenido]
	LEER_DE_MEMORIA, // [PID][PAGINA][OFFSET][TAMANIO]
	FINALIZAR_PROGRAMA, // [PID]
	LIBERAR_PAGINA // [PID] [paginaId]

} PROTOCOLO_KERNEL_Y_CPU_A_MEMORIA;

//usado porque kernel y cpu se conectan al mismo puerto y necesito saber de cual se trata
typedef enum PROTOCOLO_CONECTAR_A_MEMORIA {
	HANDSHAKE_CONECTAR_KERNEL_A_MEMORIA,
	HANDSHAKE_CONECTAR_CPU_A_MEMORIA,
	HANDSHAKE_CONEXION_A_MEMORIA_ACEPTADA
} PROTOCOLO_CONECTAR_A_MEMORIA;

typedef enum PROTOCOLO_CONECTAR_A_KERNEL {
	HANDSHAKE_SOY_CPU, HANDSHAKE_SOY_CONSOLA
} PROTOCOLO_CONECTAR_A_KERNEL;

typedef enum PROTOCOLO_MEMORIA_A_KERNEL_Y_CPU {

	HANDSHAKE_KERNEL_CONECTADO, //[ Parte del handshake, se envia cuanto ocupa una pagina]
	HANDSHAKE_CPU_CONECTADO,
	MEMORIA_INSUFICIENTE, // [Cuando pide paginas de heap, codigo o stack y no hay disponibles]
	PROCESO_INICIADO_EN_MEMORIA, // [Asigne codigo y stack]
	PAGINAS_ASIGNADAS, // Informa que las paginas pedidas fueron asignadas
	LECTURA_SATISFACTORIA, // Informa que se envio el dato correctamente
	ERROR_EN_LECTURA, // Informa de algun error de lectura
	ESCRITURA_SATISFACTORIA, // Informa que se escribio el dato correctamente
	ERROR_EN_ESCRITURA, // Informa de algun error de escritura
	ELIMINACION_DE_PROCESO_SATISFACTORIO,
	ENVIO_TEXTO_A_FS,
	PAGINA_LIBERADA,
	PAGINA_NO_LIBERADA

} PROTOCOLO_MEMORIA_A_KERNEL_Y_CPU;

typedef enum PROTOCOLO_KERNEL_A_FS {

	HANDSHAKE_CONECTAR_A_FS,

	//* Pregunta al FS si existe el archivo, envia tamanio del path y ath
	VALIDAR_ARCHIVO,
	CREAR_ARCHIVO,
	BORRAR_ARCHIVO,
	OBTENER_DATOS,
	GUARDAR_DATOS,
	MOVER_CURSOR
} PROTOCOLO_KERNEL_A_FS;

typedef enum PROTOCOLO_FS_A_KERNEL {

	HANDSHAKE_CONEXION_ACEPTADA_AL_KERNEL,
	EXISTE_ARCHIVO,
	NO_EXISTE_ARCHIVO,
	ARCHIVO_CREADO_CON_EXITO,
	FALLO_EN_LA_CREACION_DE_ARCHIVO,
	ENVIO_DATOS,
	FALLO_DATOS,
	ESCRIBIR_OK,
	ESCRIBIR_FALLO,
	ARCHIVO_BORRADO_OK,
	ARCHIVO_BORRADO_ERROR,
	MOVER_CURSOR_OK,
	MOVER_CURSOR_FAIL

} PROTOCOLO_FS_A_KERNEL;

/*
 typedef enum PROTOCOLO_KERNEL_FILE_SYSTEM {

 HANDSHAKE_CONEXION_DE_KERNEL_A_FILE_SYSTEM_ACEPTADA,
 VALIDAR_ARCHIVO,
 CREAR_ARCHIVO,
 BORRAR,
 OBTENER_DATOS,
 GUARDAR_DATOS,

 } PROTOCOLO_KERNEL_FILE_SYSTEM;
 */
#endif
