---------------------------------------------
Resultados 
---------------------------------------------
   Método      | raíz    | iteraciones | Observaciones |
---------------------------------------------
bisección      |0.20164  |  29         | Dependiendo de en donde se ajusten los limites van a dar raices diferentes en un limite de [0,1] dio el que puse pero en un limite de [1,3] da  2.12842 con 27 iteraciones lo que nos muestra que solo se pueden tomar intervalos pequeños para analizar si hay solo 1 raíz
---------------------------------------------
Falsa posición |0.20164  |  9          |Es un método mucho mas rápido que el anterior reduciendo su numero de iteraciones hasta un poco mas de 3 veces con diferentes intervalos de tiempo,tampoco requiere un paso de codigo adicional ademas de solo cambiar la linea que define mi root_fsolver
Falsa posición | 2.12842 |  10         |
----------------------------------------------
  Brent        | 0.20164 |  6          | Con este metodo aumento la rapidez para encontrar las raices a comparacion de los otros dos en la deteccion de los dos intervalos que he estado evaluando
  Brent        | 2.12842 |  7          |
----------------------------------------------
  Newton       | 0.20164 |  4          | Este metodo redujo el numero de iteraciones pero su implementacion requirio cambiar muchos detalles del codigo base tanto añadir cosas a lo que ya etaba como añadir la funcion derivada por lo que es mas rapido pero no considero que sea el mas eficiente si lo comparamos por ejemplo con el anterior.
  Newton       | 2.12842 |  5          |
----------------------------------------------




