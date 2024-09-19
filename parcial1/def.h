#define SLEEP_CAJA_MS 500
#define SLEEP_DERIVADOR_MS 1000

#define SEM_AMOUNT 1
#define SEM_NUMBER 0

#define NOMBRE_ARCHIVO "compras.dat"

#define DERIVADOR_EXIT 0

typedef struct {
    int id;
    char* descripcion;
    int importe;
} Producto;

Producto productos[10] = {
    {1, "CocaParaElFernet", 1500},
    {2, "Agua", 250},
    {3, "Fanta", 200},
    {4, "Sprite", 1750},
    {5, "PS5Trucha", 15000},
    {6, "Tamagochi", 50000},
    {7, "Leche1Ltr", 2000},
    {8, "CafeParaElExamen", 3500},
    {9, "AutoJuguete", 5600},
    {10, "MeQuedeSinIdeas", 7500}};
    
typedef struct {
    int id;
    int cantidad;
} Compra;