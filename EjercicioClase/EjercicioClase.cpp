#include <iostream>

using namespace std;

const int FILAS = 7;
const int COLUMNAS = 7;

// Definición del nodo para la lista enlazada
struct Nodo {
    int x, y;
    Nodo* siguiente;
};

// Definición de la clase Lista
class Lista {
private:
    Nodo* cabeza;
    Nodo* cola;
public:
    Lista() : cabeza(nullptr), cola(nullptr) {}

    void agregarFrente(int x, int y) {
        Nodo* nuevo = new Nodo();
        nuevo->x = x;
        nuevo->y = y;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        if (cola == nullptr) {
            cola = nuevo;
        }
    }

    void agregarFinal(int x, int y) {
        Nodo* nuevo = new Nodo();
        nuevo->x = x;
        nuevo->y = y;
        nuevo->siguiente = nullptr;
        if (cola != nullptr) {
            cola->siguiente = nuevo;
        }
        cola = nuevo;
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
    }

    bool eliminarFrente(int& x, int& y) {
        if (cabeza == nullptr) return false;
        Nodo* temp = cabeza;
        x = cabeza->x;
        y = cabeza->y;
        cabeza = cabeza->siguiente;
        if (cabeza == nullptr) {
            cola = nullptr;
        }
        delete temp;
        return true;
    }

    void eliminar() {
        if (cabeza != nullptr) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    bool estaVacia() {
        return cabeza == nullptr;
    }

    void imprimirCamino() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << "(" << actual->x << "," << actual->y << ") ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

bool esSeguro(int laberinto[FILAS][COLUMNAS], int visitado[FILAS][COLUMNAS], int x, int y) {
    return (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && laberinto[x][y] == 1 && visitado[x][y] == 0);
}

bool encontrarCaminoRecursivoConLista(int laberinto[FILAS][COLUMNAS], int visitado[FILAS][COLUMNAS], int x, int y, int destX, int destY, Lista& camino) {
    cout << "Visitando: (" << x << "," << y << ")" << endl; // Depuración: Imprimir coordenadas actuales

    // Verificar si se ha alcanzado el destino
    if (x == destX && y == destY) {
        camino.agregarFrente(x, y);
        cout << "Destino alcanzado: (" << x << "," << y << ")" << endl; // Depuración: Imprimir cuando se alcanza el destino
        camino.imprimirCamino();
        return true;
    }

    // Marcar la celda actual como visitada
    visitado[x][y] = 1;

    // Definir los posibles movimientos (Derecha, Izquierda, Abajo, Arriba)
    int moverX[] = { 0, 0, 1, -1 };
    int moverY[] = { 1, -1, 0, 0 };

    // Intentar moverse en las cuatro direcciones
    for (int i = 0; i < 4; i++) {
        int nuevoX = x + moverX[i];
        int nuevoY = y + moverY[i];

        if (esSeguro(laberinto, visitado, nuevoX, nuevoY)) {
            camino.agregarFrente(x, y);
            if (encontrarCaminoRecursivoConLista(laberinto, visitado, nuevoX, nuevoY, destX, destY, camino)) {
                return true;
            }
            camino.eliminar(); // Retroceder si no se encuentra el camino
        }
    }

    // Desmarcar la celda si no se encontró un camino
    visitado[x][y] = 0;
    cout << "Retrocediendo desde: (" << x << "," << y << ")" << endl; // Depuración: Imprimir cuando se retrocede

    return false;
}

bool encontrarCaminoIterativoConLista(int laberinto[FILAS][COLUMNAS], int visitado[FILAS][COLUMNAS], int inicioX, int inicioY, int destX, int destY) {
    Lista lista;
    lista.agregarFinal(inicioX, inicioY);
    visitado[inicioX][inicioY] = 1;

    int moverX[] = { 1, -1, 0, 0 };
    int moverY[] = { 0, 0, 1, -1 };

    while (!lista.estaVacia()) {
        int x, y;
        lista.eliminarFrente(x, y);

        cout << "Visitando: (" << x << "," << y << ")" << endl; // Depuración: Imprimir coordenadas actuales

        // Verificar si se ha alcanzado el destino
        if (x == destX && y == destY) {
            lista.agregarFinal(x, y); // Agregar el destino antes de imprimir el camino
            cout << "Destino alcanzado: (" << x << "," << y << ")" << endl; // Depuración: Imprimir cuando se alcanza el destino
            lista.imprimirCamino();
            return true;
        }

        // Intentar moverse en las cuatro direcciones
        for (int i = 0; i < 4; i++) {
            int nuevoX = x + moverX[i];
            int nuevoY = y + moverY[i];

            if (esSeguro(laberinto, visitado, nuevoX, nuevoY)) {
                lista.agregarFinal(nuevoX, nuevoY);
                visitado[nuevoX][nuevoY] = 1;
            }
        }
    }

    return false;
}

int main() {
    int laberinto[FILAS][COLUMNAS] = {
        {1, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 0, 1}
    };

    int visitado[FILAS][COLUMNAS] = { 0 };  // Inicializar todas las celdas como no visitadas

    int inicioX = 0, inicioY = 0;
    int destX = 2, destY = 5;

    cout << "Busqueda Recursiva:" << endl;
    Lista caminoRecursivo;
    if (encontrarCaminoRecursivoConLista(laberinto, visitado, inicioX, inicioY, destX, destY, caminoRecursivo)) {
        cout << "Se encontro un camino valido (recursivo)." << endl;
    }
    else {
        cout << "No se encontro un camino valido (recursivo)." << endl;
    }

    // Reiniciar la matriz de visitados para la prueba iterativa
    fill(&visitado[0][0], &visitado[0][0] + FILAS * COLUMNAS, 0);

    cout << "Busqueda Iterativa:" << endl;
    if (encontrarCaminoIterativoConLista(laberinto, visitado, inicioX, inicioY, destX, destY)) {
        cout << "Se encontro un camino valido (iterativo)." << endl;
    }
    else {
        cout << "No se encontro un camino valido (iterativo)." << endl;
    }

    return 0;
}
