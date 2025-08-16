INICIAR ventana ChrisEngine de tamaño 800x600 con título "ChrisEngine Test"

CREAR lista personajes :
"princesa.png"
"sonic.png"
"virdo.png"
"wario.png"

CARGAR textura pista : "pista de carreras.png"
CREAR sprite pista con la textura
COLOCAR sprite pista en posición(0, 0)

PARA cada personaje en lista personajes :
CARGAR textura del personaje
CREAR sprite con la textura
COLOCAR sprite en posición(100, y)  // separar verticalmente
AUMENTAR y en 100

MIENTRAS ventana esté abierta :
LEER eventos de la ventana
SI evento es CerrarVentana :
CERRAR ventana

LIMPIAR ventana con color negro
DIBUJAR sprite de pista
DIBUJAR todos los sprites de personajes
MOSTRAR ventana
FIN MIETRAS
