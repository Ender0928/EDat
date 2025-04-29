# Reflexiones sobre el TAD BST

*Al ejecutar el programa p4_e1.c se puede comprobar que los tiempos de creación y búsqueda varían mucho según si el programa se ejecuta en modo normal o en modo ordenado.*

•¿Por qué es así?

Cuando se ejecuta en modo ordenado los elementos entran previamente organizados esto provoca que  se aproveche mejor el espacio, rellenándose así los nodos de la derecha e izquierda, es por ello que podemos ver que su profundidad es considerablemente menor ya que se tratan de potencias de dos(50k ~ 2¹⁶ o 10k ~ 2¹⁴).

•¿Hay alguna propiedad del árbol que permita explicar este comportamiento?

Debido a que los árboles están jerarquizados, es decir que los elemntos están en distintos niveles, encontrar un elemento o donde insertarlo es más fácil si está previamente ordenado, porque como ya hemos dicho antes su profundidad es menor.

# Reflexiones sobre el TAD SQ

•¿Qué diferencias y similitudes hay entre el TAD SQ y el TAD Cola de la práctica anterior?

En primer lugar, debido a que las SQ están formadas por un árbol están ordenadas a diferencia de las colas, además gracias a esto funciones primitivas típicas de colas como push_front o push_back no tienen sentido, ya que cuando se inserta un elemento este se ordena, en segundo lugar, estas no tienen variables que apuntan al front o rear, porque estas pueden ser optenidas con funciones como find_min o find_max, por otro lado, el pop funciona también distinto al de una cola, ya que aunque si que extrae el primer elemento, como la SQ está ordenada no es siempre el primer elemento añadido, por último, las SQ a diferencia de las colas no pueden ser circulares.

• ¿Qué coste (aproximado) tiene la operación de extraer un elemento en el TAD SQ? ¿Sería posible hacer que esta operación fuera 𝒪(1)?

El coste vendrá determinado por la profundidad que tenga el arbol ya que se tiene que recorrer todo el subárbol izquierdo para encontrar el mínimo y luego hacer el proceso necesario para eliminar el elemento. Por lo que aproximadamente su coste sería de 𝒪(2n).
En el caso de que el árbol solo tuviese un elemento, el coste sería 𝒪(1) ya que únicamente tendría que visitar este para saber que es el mínimo. En un caso general, no se podría, pero podríamos reducir el coste con un doble puntero al elemento mínimo, de esta forma eleminar el elemento sería de coste 𝒪(1), pero luego tendríamos que buscar el nuevo elemento mínimo, pasando a 𝒪(n).
