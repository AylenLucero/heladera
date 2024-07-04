#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
typedef struct DatosCuentaAdmin { //Estructura datos de cuenta de administradores y cajeros
    int dni;
    char contrasena[20];
} TDatosCuentaAdminYCajero;
typedef struct Productos {
    int idProductos[6];
    int tortasHeladas;
    float precioTortasHeladas;
    int postresHelados;
    float precioPostresHelados;
    float saboresKGramos[5];
    float preciosPorCantidad[6];
}TProductos;
typedef struct HistorialVentas {
    int id;
    char fecha[11];
    char productosVendidos[100][100];
    int cantProdVendidos[100];
    float preciosProductos[100];
    float totalPrev[100];
    float total;
}THistorialVentas;

void menuPrincipal();
void crearArchivoBinario(char *nombreArchivoBinario);
int archivoEstaVacio(char *nombreArchivo);

void leerArchivoBinarioInicioSesion(char *nombreArchivoBinario, char *puesto);
void menuAdmin(TDatosCuentaAdminYCajero *datos);
void menuCajero();
void guardarDatos();
int existeDni(char *ValoresCuentasAdmin,int dniInput);
void loginAdmin(char *ValoresCuentasAdmin,int dniAdmin);
void guardarAdmin(char *nomArchivo, int dni_input, char *texto);
void eliminarAdminOCajero(char *nomArchivo,int dniInput);
void listarAdmins();

void cargarStockInicio();
void eleccionSabor(double pesoARestar);
void cargarStockInicio();
void mostrarMensajeIntermitente(const char *mensaje, int duracion);

#endif // LIB_H_INCLUDED
