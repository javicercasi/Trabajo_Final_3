
                                                      //Defino las funciones a compartir por los archivos

//Configuracion inicial del Modulo:

void inicio ();

void encendido();

void standby();

void Configuracion();


// Funciones Loops a ejecutar indefinidamente:

void teclado();

void oyente();

void comando(String at, int unsigned tiempo);

void ShowSerialData();


// Funciones para Llamar y mandar Mensajes:

void llamado(String posicion);

void timmer(String posicion);

void mensaje(String num, String posicion);


// Funcion para conectarse a la red y realizar el envio de datos a la Nube:

void envio_trama(String posicion, String duracion);
