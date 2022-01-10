Servidor.c
Linea 65-148 Crea la matriz de juego
Linea 150-161 Abre la tuberia
Linea 165-181 Crea los semaforos segun cantidad de jugadores
Linea 184-186 Se conecta a la tuberia

Linea 188-228 (Comentada) Se intenta hacer la conexion de la tuberia FIFO con los diferentes hijos de servidor

Cliente.c
Linea 16-19 Abre la tuberia
Linea 21-23 Escribe en la tuberia

Makefile
La creacion de la tuberia FIFO se crea en el Makefile debido que da errores al crearse en el servidor ya que se creaba con permisos erroneos, creandolo con el Makefile se logra que la tuberia tenga los permisos correctos