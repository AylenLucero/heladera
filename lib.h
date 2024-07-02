#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
typedef struct DatosCuentaAdmin { //Estructura datos de cuenta de administradores y cajeros
    int dni;
    char contrasena[20];
} TDatosCuentaAdminYCajero;
typedef struct Productos {
    int tortas_heladas;
    float precio_tortas_heladas;
    int postres_helados;
    float precio_postres_helados;
    float saboresKGramos[5];
    float preciosPorCantidad[6];
}TProductos;
typedef struct HistorialVentas {
    int id;
    int idTotal;
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
int existe_dni(char *ValoresCuentasAdmin,int dni_input);
void login_admin(char *ValoresCuentasAdmin,int dni_admin);
void guardar_admin(char *nomArchivo, int dni_input, char *texto);
void eliminar_admin_O_Cajero(char *nomArchivo,int dni_input);
void listar_admins();

void cargar_stock_inicio();
void eleccion_sabor(double peso_a_restar);
void cargar_stock_inicio();
void mostrar_mensaje_intermitente(const char *mensaje, int duracion);

#endif // LIB_H_INCLUDED
