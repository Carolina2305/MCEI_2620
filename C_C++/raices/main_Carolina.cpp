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

double df(double x, void *params)
{
  // Calcula la derivada: 3x^2 - 5
  return 3 * std::pow(x, 2) - 5;
}

// Evalúa la función y su derivada de forma simultánea.
void fdf(double x, void *params, double *y, double *dy)
{
  *y = f(x, params);
  *dy = df(x, params); // Ahora sí reconocerá a df
}
// Punto de inicio de la ejecución del programa.
int main()
{
  // Puntero al tipo de método numérico que se utilizará.
  const gsl_root_fdfsolver_type *T;
  // Puntero al solucionador de raíces reservado por GSL.
  gsl_root_fdfsolver *s;
  // Estructura de GSL que contiene la función, su derivada y sus parámetros.
  gsl_function_fdf F;
  // Asocia la función, su derivada y la función conjunta con la estructura.
  F.f = &f;
  F.df = &df;
  F.fdf = &fdf;
  F.params = nullptr;
  // Define el extremo inferior del intervalo inicial.
  // Valor inicial (semilla) para el método de secante.
  double x = 2.0;
  double x_prev;
  // Selecciona el método de secante.
  T = gsl_root_fdfsolver_secant;
  // Reserva memoria para el solucionador usando el método seleccionado.
  s = gsl_root_fdfsolver_alloc(T);
  // Configura el solucionador con la función y la aproximación inicial.
  gsl_root_fdfsolver_set(s, &F, x);
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
    x_prev = x;
    // Realiza una iteración del método de secante.
    status = gsl_root_fdfsolver_iterate(s);
    // Obtiene la aproximación actual de la raíz.
    x = gsl_root_fdfsolver_root(s);

    // Muestra la iteración y la raíz aproximada.
    std::cout << iter << "\t" << x << "\n";

    // Evalúa si el cambio entre la aproximación actual y la anterior cumple la tolerancia.
    // 0.0 es la tolerancia absoluta y 1e-8 la tolerancia relativa.
    status = gsl_root_test_delta(x, x_prev, 0.0, 1e-8);
    // Continúa mientras GSL pida más iteraciones y no se alcance el máximo.
  } while (status == GSL_CONTINUE && iter < max_iter);

  // Muestra la última aproximación calculada.
  std::cout << "\nRaiz encontrada = " << x << std::endl;
  // Libera la memoria reservada para el solucionador.
  gsl_root_fdfsolver_free(s);
  // Indica que el programa terminó correctamente.
  return 0;
}