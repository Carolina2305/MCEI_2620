// Permite mostrar información en la pantalla mediante std::cout.
#include <iostream>
// Incluye herramientas para controlar la precisión y el formato de salida.
#include <iomanip>
// Incluye funciones matemáticas de la biblioteca estándar.
#include <cmath>
// Incluye el método de GSL para encontrar raíces de funciones.
#include <gsl/gsl_roots.h>
// Incluye constantes y códigos de estado utilizados por GSL.
#include <gsl/gsl_errno.h>

// Define la función de la que se busca una raíz, es decir, un valor x tal que f(x)=x^3-5x+1.
double f(double x, void *params)
{
  // Calcula x^3 - 5x + 1.
  return std::pow(x, 3) - 5 * x + 1;
}

// Punto de inicio de la ejecución del programa.
int main()
{
  // Puntero al tipo de método numérico que se utilizará.
  const gsl_root_fsolver_type *T;
  // Puntero al solucionador de raíces reservado por GSL.
  gsl_root_fsolver *s;
  // Estructura de GSL que contiene la función y sus parámetros.
  gsl_function F;
  // Asocia la función f con la estructura que utilizará GSL.
  F.function = &f;
  // Indica que no se necesitan parámetros adicionales para f.
  F.params = nullptr;
  // Define el extremo inferior del intervalo inicial.
  double x_lo = 2.0;
  // Define el extremo superior del intervalo inicial.
  double x_hi = 3.0;
  // Selecciona el método de posición falsa.
  T = gsl_root_fsolver_falsepos;
  // Reserva memoria para el solucionador usando el método seleccionado.
  s = gsl_root_fsolver_alloc(T);
  // Configura el solucionador con la función y el intervalo inicial.
  gsl_root_fsolver_set(s, &F, x_lo, x_hi);
  // Imprime los encabezados de las columnas de resultados.
  std::cout << "iter\t" << "inf\t" << "sup\t" << "raíz\n";

  // Almacena el estado de cada operación realizada por GSL.
  int status;
  // Inicializa en cero el contador de iteraciones.
  int iter = 0;
  // Establece el número máximo de iteraciones permitidas.
  int max_iter = 100;
  // Almacena la aproximación actual de la raíz.
  double r;

  // Ejecuta el bloque al menos una vez antes de evaluar la condición.
  do
  {
    // Aumenta en uno el número de iteración.
    iter++;
    // Realiza una iteración del método de posición falsa.
    status = gsl_root_fsolver_iterate(s);
    // Obtiene la aproximación actual de la raíz.
    r = gsl_root_fsolver_root(s);
    // Obtiene el límite inferior del intervalo actualizado.
    x_lo = gsl_root_fsolver_x_lower(s);
    // Obtiene el límite superior del intervalo actualizado.
    x_hi = gsl_root_fsolver_x_upper(s);
    // Muestra la iteración, los límites y la raíz aproximada.
    std::cout << iter << "\t" << x_lo << "\t" << x_hi << "\t" << r << "\n";
    // Termina cuando el intervalo es suficientemente pequeño.
    // 0.0 es la tolerancia absoluta y 1e-8 la tolerancia relativa.
    status = gsl_root_test_interval(x_lo, x_hi, 0.0, 1e-8);
    // Continúa mientras GSL pida más iteraciones y no se alcance el máximo.
  } while (status == GSL_CONTINUE && iter < max_iter);

  // Muestra la última aproximación calculada.
  std::cout << "\nRaiz encontrada = " << r << std::endl;
  // Libera la memoria reservada para el solucionador.
  gsl_root_fsolver_free(s);
  // Indica que el programa terminó correctamente.
  return 0;
}
