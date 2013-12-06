/*
    Programa- Ventas.h
    Autor- Equipo SysteMy
    Fecha- 17/11/12
    Objetivo- Archivo o clase, que contiene la estructura y las funciones de ventas.
*/

//TIPOS
typedef FILE *fArchivoVenta; //ARCHIVO

typedef struct venta
{
    int eFolio;
    int eCodigoProd;
    char cProducto[30];
    int eCantProd;
    float fPrecio;
    float fImporte;
    char Fecha_y_hora_de_venta[35];
    struct venta *pSig;
} TrVenta;
typedef TrVenta *TpVenta;

//PROTOTIPOS
void ventas(TpVenta * , TpVenta* , TpProducto *);
void realizarVenta(TpVenta * , TpVenta * , TpProducto *);
int listaLlenaVenta(TpVenta *);
int listaVaciaVenta(TpVenta);

void crearArchivoVentas(fArchivoVenta *, TpVenta * , TpVenta *);
void indexarVentas(fArchivoVenta *, TpVenta * , TpVenta *);
void guardarVentasEnArchivo( fArchivoVenta *, TpVenta);
void liberarMemoriaVenta(TpVenta);

//FUNCIONES
/*
Nombre: ventas
Objetivo: Permite llevar acabo una venta de un producto.
Parámetros de Entrada(E) y Salida(S): (S)pPrimero - contiene la posición de la primera venta
    que se realizó.
    (S)pUltimo - contiene la posición de la ultima venta realizada.
    (S)pProducto - pProducto - contiene los productos que seran vendidos.     
*/
void ventas(TpVenta *pPrimero ,TpVenta *pUltimo , TpProducto *pProducto){
//Variables
    char cDecision;
    
//Inicio
    printf("------------------\nRegistro de Ventas\n------------------\n");
    do
    {
        realizarVenta( &(*pPrimero) , &(*pUltimo), &(*pProducto) );
        do
        {
            printf("\nDesea realizar otra venta[S/N]: ");
            scanf("%c",&cDecision);
            fflush(stdin);
        }
        while(toupper(cDecision) != 'S' &&  toupper(cDecision) != 'N' );
        system("cls");
    }
    while(toupper(cDecision) != 'N');
    printf("\n\t\t\t\tPresione Enter para regresar al menu principal");
    getch();
    system("cls");
}//FIN ventas

/*
Nombre: listaLlenaVenta
Objetivo: Si la lista se encuentra llena
Parámetros de Entrada(E) y Salida(S): (S)pNuevo - Se utiliza para verificar si la lista esta llena
*/
int listaLlenaVenta(TpVenta *pNuevo){
//Inicio    
    *pNuevo = (TpVenta) malloc(sizeof(TrVenta));
    return *pNuevo == NULL;    
}//FIN listaLlenaVenta

/*
Nombre: listaVaciaVenta
Objetivo: Si la lista se encuentra vacáa
Parámetros de Entrada(E) y Salida(S): (E)pPrimero - Contiene el primer elemento de la lista
*/
int listaVaciaVenta(TpVenta pPrimero){
//Inicio    
    return pPrimero == NULL;    
}//FIN listaVaciaVenta

/*
Nombre realizarVenta
Objetivo: Registrar una venda.
Parámetros de Entrada(E) y Salida(S): (S)pPrimero - contiene la posición de la primera venta
    que se realizo.
    (S)pUltimo - contiene la posición de la ultima venta realizada.
    (S)pProducto - contiene la información del producto que se vera afectado por 
        la venta.  
*/
void realizarVenta(TpVenta *pPrimero, TpVenta *pUltimo, TpProducto *pProducto){
//Variables    
    int eCantidad,eIdProducto;
    TpProducto pPos;
    float fImporte;
    TpVenta pNuevo;
    char cDecision = 'n';
    
    //Determina la hora y fecha, respecto a la computadora donde es ejecutado el programa.
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[35];
    strftime(output,35,"Fecha: %d/%m/%y Hora: %H:%M:%S\n",tlocal);

//Inicio
    printf("Ingrese id del producto: ");
    scanf("%d" , &eIdProducto);
    fflush(stdin);

    pPos = buscarProducto( *pProducto , eIdProducto ); //Busqueda del producto a vender

    if( pPos == 0)
    {
        printf("\n  ---No existe producto con la id %i---" , eIdProducto );
        getch();
    }
    else
    { 
        if (listaLlenaVenta(&pNuevo))
        {

            printf("\n\n\n\n\t\t\tOverflow");
            getch();
        }
        else
        {       
            printf("Ingresa la cantidada a vender: ");
            scanf("%d" , &eCantidad);
            fflush(stdin);
            
            if (eCantidad <= pPos->eExistencia) //Existen cantidad suficiente en el almacen de tal producto
            {
                cDecision = 'S';
                pNuevo->eCantProd = eCantidad; //Asigna cantidad vendida
                pNuevo->fImporte = (pPos->fPrecio * eCantidad); //Asigna el total del producto vendido
            }
            else{
                if( pPos->eExistencia <=0) //Es menor o igual a 0 la cantidad que se tiene en el almacen.
                {
                    printf("No existe mercancia del producto %i en el almacen\n",pPos->eCodigoProd);
                    printf("Contacte a su distribuidor\n");
                    getch();
                }
                else{
                    
                    printf("No existe la cantidad que usted desea en el almacen\n");
                    printf("Desea comprar la cantidad de %i que existe en el almacen[S/N]: " , pPos->eExistencia);
                    scanf("%c",&cDecision);
                    fflush(stdin);
                    
                    if( toupper(cDecision) == 'S' ){ //Decide comprar lo que hay en el almacen
                        
                        //Asigna la cantidad existente del producto que se encuentra en el almacen
                        pNuevo->eCantProd = pPos->eExistencia; 
                    
                        //Asigna el total del producto vendido
                        pNuevo->fImporte = (pPos->fPrecio * pPos->eExistencia); 
                    
                        eCantidad = pPos->eExistencia; /* Asigna cantidad existente del producto,
                        para mostrar en pantalla */ 
                    }
                    
                }
            }
            if( toupper(cDecision) == 'S' )
            {
                           
                pNuevo->fPrecio = pPos->fPrecio; //Asigna el precio del producto que se va vender 
                  
                //Asigna la fecha y hora que se realizo la venta          
                strcpy( pNuevo->Fecha_y_hora_de_venta , output); 
                
                strcpy( pNuevo->cProducto , pPos->cProducto); //Asigna nombre del producto vendido
                
                pNuevo->pSig = NULL;
                
                //Guarda en la lista de ventas
                if(listaVaciaVenta( *pPrimero) ) //Si esta vacia
                {
                    *pPrimero = pNuevo; 
                    *pUltimo = pNuevo;
                }
                else 
                {
                    (*pUltimo)->pSig = pNuevo;
                    *pUltimo = pNuevo;
                }
                
                //Afecta su cantidad existente del producto que se vendio.
                pPos->eExistencia  = pPos->eExistencia - eCantidad;
                
                //Muestra datos del producto vendido
                printf("\nID    \tProducto    \tPrecio    \tCantidad\t    Importe\n\n");
                printf("%i  \t%s    \t\t%4.2f     \t%i\t\t\t%4.2f\n",pPos->eCodigoProd ,pPos->cProducto, pPos->fPrecio , eCantidad , (*pUltimo)->fImporte);
                printf("\n\t\t\t\t\t\t%s\n\t\t\t\t\t\tFolio: %i",output, (*pUltimo)->eFolio );
                getch();
            }
        }
    }
    system("cls");
}//realizarVenta

/*
Nombre: liberarMemoriaVenta
Objetivo: Liberar la memoria de la lista de productos.
Parámetros de Entrada(E) y Salida(S): (E)pPrimero - donde se llevara acabo la liberación de
    memoria.
*/
void liberarMemoriaVenta(TpVenta pPrimero) {
//Variables
	TpVenta pBorrar, pPos;

//Inicio
	pPos = pPrimero;

	while (pPos != NULL) {
		pBorrar = pPos;
		pPos = pPos->pSig;
		free(pBorrar);
	}

}//liberarMemoriaVenta

/*
Nombre: crearArchivoVentas
Objetivo: Crear un archivo binario y extraer datos de él.
Parámetros de Entrada(E) y Salida(S): (S)ArchivoVenta- Archivo que se va crear.
    (S)pPrimero- Donde se van a guardar los datos extraidos del archivo.
    (S)pUltimo- Donde se van a guardar los datos extraidos del archivo.
*/
void crearArchivoVentas(fArchivoVenta *ArchivoVenta, TpVenta *pPrimero , TpVenta *pUltimo){
//Inicio
    if( (*ArchivoVenta = fopen("Ventas.dat" , "ab+")) == NULL ) //Abre el fichero para lecturay y escritura. La escritura comenzará al final del fichero, respetando el contenido.
    {
        printf("No se puede abrir el archivo\n");
    }
    else
    {
        indexarVentas( &(*ArchivoVenta) , &(*pPrimero) , &(*pUltimo)); //indexa
        
        //Abre el fichero para lectura y escritura. Crea el fichero si no existe y borra el contenido si existe.
        *ArchivoVenta = fopen("Ventas.dat" , "wb+"); 
    }
}//FIN crearArchivoVentas

/*
Nombre: indexarVentas
Objetivo: Extraer los datos del archivo(ArchivoVenta) a la lista(pPrimero).
Parámetros de Entrada(E) y Salida(S): (S)ArchivoVenta- Contiene los datos a extraer.
    (S)pPrimero- Lista donde se guardaran los datos extraídos.
    (S)pUltimo- Lista donde se guardaran los datos extraídos.
*/
void indexarVentas(fArchivoVenta *ArchivoVenta, TpVenta *pPrimero , TpVenta *pUltimo){
//Variables    
    TrVenta rRegistro;
    TpVenta pRegistro;
    
//Inicio
    rewind(*ArchivoVenta); //Posiciona al inicio del archivo

    do
    {
        //Devuelve el numero de elementos leidos del archivo
        fread(&rRegistro, sizeof(TrVenta) , 1, *ArchivoVenta);

        if( !feof(*ArchivoVenta) )
        {
            if( listaLlenaVenta(&pRegistro) )
            {
                printf("OverFlow\n");
            }
            //Asigna
            pRegistro->eCodigoProd = rRegistro.eCodigoProd;
            pRegistro->fPrecio = rRegistro.fPrecio;
            pRegistro->fImporte = rRegistro.fImporte;
            strcpy(pRegistro->Fecha_y_hora_de_venta , rRegistro.Fecha_y_hora_de_venta );
            pRegistro->eCantProd = rRegistro.eCantProd;
            pRegistro->eFolio = rRegistro.eFolio;
            pRegistro->pSig = NULL;
            
            if( listaVaciaVenta( *pPrimero ) )
            {
                
                *pPrimero  = pRegistro;
                *pUltimo = pRegistro;
            }
            else
            {
                
               (*pUltimo)->pSig = pRegistro;
                *pUltimo = pRegistro;  
            }     
        }
    }
    while(!feof(*ArchivoVenta));
}//FIN indexarVentas

/*
Nombre: guardarVentasEnArchivo
Objetivo: Guardar en el archivo(ArchivoVenta), las compras actuales que se encuentran en la lista(pPrimero).
Parámetros de Entrada(E) y Salida(S): (S)ArchivoVenta- Archivo donde se guardaran las ventas.
    (E)pPrimero- contiene las ventas realizadas.
*/
void guardarVentasEnArchivo( fArchivoVenta *ArchivoVenta, TpVenta pPrimero){
//Variables
    TrVenta rVenta;
    TpVenta pPos;
//Inicio
    if(pPrimero != NULL)
    {
        pPos = pPrimero;

        while( pPos != NULL)
        {
            
            rVenta.eCodigoProd = pPos->eCodigoProd;
            rVenta.fPrecio = pPos->fPrecio;
            strcpy( rVenta.Fecha_y_hora_de_venta , pPos->Fecha_y_hora_de_venta );
            rVenta.fImporte = pPos->fImporte;
            rVenta.eFolio = pPos->eFolio;
            rVenta.eCodigoProd = pPos->eCodigoProd;
            strcpy( rVenta.cProducto , pPos->cProducto );
 
            fwrite(& rVenta , sizeof( rVenta ), 1, *ArchivoVenta); //Escribe en el archivo

            pPos = pPos->pSig;
        }    
    }
    fclose(*ArchivoVenta); //Cierra archivo
}//FIN guardarVentasEnArchivo
