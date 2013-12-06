/*
    Programa- Compras.h
    Autor- Equipo SysteMy
    Fecha- 17/11/12
    Objetivo- Archivo o clase, que contiene la estructura y las funciones de compras.
*/

//TIPOS
typedef FILE *fArchivoCompra; //ARCHIVO

typedef struct compra
{
    int eCodigoProd;
    int eCantProd;
    float fCosto;
    float fImporte;
    char cFecha_de_compra[35];
    struct compra *pSig;
    struct compra *pAnt;
} TrCompra;
typedef TrCompra *TpCompra;

//PROTOTIPOS
int listaVaciaCompra(TpCompra);
int listaLlenaCompra(TpCompra *);
void compras(TpCompra *, TpCompra * , TpProducto *);
void ordenCompra(TpCompra *, TpCompra * , TpProducto *);
void registrarCompra(TpCompra * , TpCompra * , TpProducto * , int);
void consultarCompras(TpCompra);

void crearArchivoCompras( fArchivoCompra * , TpCompra * , TpCompra *);
void indexarCompras(fArchivoCompra *, TpCompra *, TpCompra *);
void guardarComprasEnArchivo( fArchivoCompra *, TpCompra);
void liberarMemoriaCompra(TpCompra);

//FUNCIONES
void compras(TpCompra *pPrimeroC , TpCompra *pUltimoC , TpProducto *pProducto){
//Variables
    char cOpc;
    
//Inicio
    do
    {
        printf("------------------\nCompras\n------------------\n");
        printf("O- Orden de compra\n");
        printf("C- Consultar\n");
        printf("R- Regresar Menu Principal\n");
        printf("\n\t\t\t\t\t\tSeleccione una opcion: ");
        scanf("%c",&cOpc);
        fflush(stdin);
        switch(toupper(cOpc))
        {
        case 'O':
            system("cls");
            ordenCompra( &(*pPrimeroC) , &(*pUltimoC) , &(*pProducto) );
            break;
        case 'C':
            system("cls");
            consultarCompras( *pPrimeroC );
            break;
        case 'R':
            break;
        default:
            printf("Opcion incorrecta\n");
        }
    }
    while(toupper(cOpc)!= 'R');
    printf("\n\t\t\t\tPresione Enter para regresar al menu principal");
    getch();
    system("cls");
}//FIN productos

void ordenCompra(TpCompra *pPrimeroC , TpCompra *pUltimoC , TpProducto *pProducto){
//Variables
    char cDecision;
    int eIdProducto;

//Inicio
    printf("------------------\nRegistro de Compras\n------------------\n");
    do
    {
        printf("Ingrese ID del producto que desee comprar: ");
        scanf("%d" , &eIdProducto);
        fflush(stdin);
        registrarCompra( &(*pPrimeroC) , &(*pUltimoC), &(*pProducto) , eIdProducto );
        do
        {
            printf("\nDesea realizar otra compra[S/N]: ");
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
}//FIN ordenCompra

/*
Nombre: listaLlenaCompra
Objetivo: Si la lista se encuentra llena
Parametros de Entrada(E) y Salida(S): (S)pNuevo- Se utiliza para verificar si la lista esta llena
*/
int listaLlenaCompra(TpCompra *pNuevo){
//Inicio
    *pNuevo = (TpCompra) malloc(sizeof(TrCompra));
    return *pNuevo == NULL;
}//FIN listaLlenaCompra

/*
Nombre: listaVaciaCompra
Objetivo: Si la lista se encuentra vacia
Parametros de Entrada(E) y Salida(S): (E)pPrimeroC- Contiene el primer elemento de la lista
*/
int listaVaciaCompra(TpCompra pPrimeroC){
//Inicio
    return pPrimeroC == NULL;
}//FIN listaVaciaCompra

/*
Nombre: registrarCompra
Objetivo: Realizar la compra de mercancia.
Parametros de Entrada(E) y Salida(S): (S)pPrimeroC- Contiene el primer elemento de la lista(compras).
    (S)pUltimoC- Contiene el ultimo elemento de la lista(compras).
    (S)pProducto- Contiene la lista de productos donde se afectara si se lleva acabo una compra.
    (E)eIdProducto- Producto a buscar dentro de la lista(pProducto).
*/
void registrarCompra(TpCompra *pPrimeroC , TpCompra *pUltimoC , TpProducto *pProducto , int eIdProducto){
//Variables
    TpCompra pNuevo;
    TpProducto pPos;
    char eDecision;
    
    //Se encarga de obtener la fecha y hora.
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[35];
    strftime(output,35,"Fecha: %d/%m/%y Hora: %H:%M:%S\n",tlocal);

//Inicio     
    if( listaLlenaCompra( &pNuevo) ) 
    {
        printf("\n\n\n\t\tUnderflow");
        getch();
    }
    else
    {

        pPos = buscarProducto( *pProducto , eIdProducto);

        if ( pPos == NULL)
        {

            printf("\n\t---No existe producto con la id %i---" , eIdProducto);
            getch();
        }
        else
        {
            
            //Asignan datos al nodo creado
            pNuevo->pSig = NULL;
            pNuevo->pAnt = NULL;
            pNuevo->eCodigoProd = eIdProducto; //Id de producto
            
            printf("Ingrese la cantidad a comprar del producto %i: " , eIdProducto);
            scanf("%d" , &pNuevo->eCantProd);
            fflush(stdin);
            
            pNuevo->fCosto = (*pProducto)->fCosto; //Asigna costo de producto
            pNuevo->fImporte = (*pProducto)->fCosto * pNuevo->eCantProd; //Asigna Importe
            strcpy(pNuevo->cFecha_de_compra , output); //Asigna Fecha
            
            //Muestra en pantalla datos del producto a comprar
            printf("\nProducto(ID)    \t\tCantidad      \t\tCosto\t\t Importe\n\n");
            printf("%s    \t\t\t%i    \t\t%4.2f\t\t%4.2f", pPos->cProducto, pNuevo->eCantProd , pPos->fCosto , pNuevo->fImporte );
            printf("\n\n\t\t\t\t\t\t%s\n",output);
            
            //Se pregunta
            printf("Desea realizar esta compra[S/N]: ");
            scanf("%c" , &eDecision);
            fflush(stdin);

            if( toupper(eDecision) == 'S') //Si se acepta la compra, guarda en la lista de compras
            {

                if( listaVaciaCompra ( *pPrimeroC) )
                {

                    *pPrimeroC = pNuevo;
                    *pUltimoC = pNuevo;
                }
                else
                {

                    (*pUltimoC)->pSig = pNuevo;
                    pNuevo->pAnt = *pUltimoC;
                    *pUltimoC = pNuevo;
                }
                        
                pPos->eExistencia = pPos->eExistencia + (*pUltimoC)->eCantProd; //AFECTA EXISTENCIA DEL PRODUCTO
                printf("Compra satisfactoria\n");
                
            }
             
            getch();
        }
    }
    system("cls");
}//FIN registrarCompra

/*
Nombre: consultarCompras
Objetivo: Mostrar un listado de las compras realizadas.
Parametros de Entrada(E) y Salida(S): (E)pPrimeroC- Contiene las compras realizadas.
*/
void consultarCompras(TpCompra pPrimeroC){
//Variables
    TpCompra pPos;
    int ePausa = 0;

//Inicio
    if(listaVaciaCompra( pPrimeroC )){
    
        printf("\n\n\n\t\tUnderflow");
    }
    else{
        
        pPos = pPrimeroC;
        printf("\n-----------*****Compras*****------------");
        while( pPos != NULL){
        
            printf("\nProducto: %i\nCantidad: %i\nCosto: %4.2f\nImporte: %4.2f\n%s", pPos->eCodigoProd, pPos->eCantProd , pPos->fCosto , 
            pPos->fImporte , pPos->cFecha_de_compra);
            ePausa++;
            printf("----------------------------------------------\n");
            
            if( ePausa%2 == 0){ //Permite pausar, para mostrar de dos en dos productos.
                
                getch();
                system("cls");    
            }
            
            pPos = pPos->pSig;        
        }   
    }
    getch();
    system("cls");    
}//FIN consultarCompras

/*
Nombre: LiberarMemoriaProveedor
Objetivo: Liberar la memoria de la lista de compras.
Parametros de Entrada(E) y Salida(S): (E)pPrimero- donde se llevara acabo la liberación de
    memoria.
*/
void liberarMemoriaCompra(TpCompra pPrimero){
//Variables
    TpCompra pBorrar, pPos;

//Inicio
    pPos = pPrimero;

    while (pPos != NULL)
    {
        pBorrar = pPos;
        pPos = pPos->pSig;
        free(pBorrar);
    }

}//LiberarMemoria

/*
Nombre: crearArchivoCompras
Objetivo: Crear un archivo binario y extraer datos de él.
Parametros de Entrada(E) y Salida(S): (S)ArchivoCompra- Archivo que se va crear.
    (S)pPrimeroC- Donde se van a guardar los datos extraidos del archivo.
    (S)pUltimoC- Donde se van a guardar los datos extraidos del archivo.
*/
void crearArchivoCompras(fArchivoCompra *ArchivoCompra, TpCompra *pPrimeroC , TpCompra *pUltimoC){
//Inicio
    if( (*ArchivoCompra = fopen("Compras.dat" , "ab+")) == NULL ) //Abre el fichero para lecturay y escritura. La escritura comenzará al final del fichero, respetando el contenido.
    {
        printf("No se puede abrir el archivo\n");
    }
    else
    {
        indexarCompras( &(*ArchivoCompra) , &(*pPrimeroC) , &(*pUltimoC) ); //indexa
        
        //Abre el fichero para lectura y escritura. Crea el fichero si no existe y borra el contenido si existe.
        *ArchivoCompra = fopen("Compras.dat" , "wb+"); 
    }
}//FIN crearArchivoCompras

/*
Nombre: indexarCompras
Objetivo: Extraer los datos del archivo(ArchivoCompra) a la lista(pPrimeroC).
Parametros de Entrada(E) y Salida(S): (S)ArchivoCompra- Contiene los datos a extraer.
    (S)pPrimeroC- Lista donde se guardaran los datos extraídos.
    (S)pUltimoC- Lista donde se guardaran los datos extraídos.
*/
void indexarCompras(fArchivoCompra *ArchivoCompra, TpCompra *pPrimeroC , TpCompra *pUltimoC){
//Variables    
    TrCompra rRegistro;
    TpCompra pRegistro;
    
//Inicio
    rewind(*ArchivoCompra); //Posiciona al inicio del archivo

    do
    {
        //Devuelve el numero de elementos leidos del archivo
        fread(&rRegistro, sizeof(TrCompra) , 1, *ArchivoCompra);

        if( !feof(*ArchivoCompra) )
        {
            if( listaLlenaCompra(&pRegistro) )
            {
                printf("OverFlow\n");
            }
            //Asigna
            pRegistro->eCodigoProd = rRegistro.eCodigoProd;
            pRegistro->fCosto = rRegistro.fCosto;
            pRegistro->fImporte = rRegistro.fImporte;
            strcpy(pRegistro->cFecha_de_compra , rRegistro.cFecha_de_compra );
            pRegistro->eCantProd = rRegistro.eCantProd;
            pRegistro->pSig = NULL;
            pRegistro->pAnt = NULL;
            
            if( listaVaciaCompra( *pPrimeroC ) )
            {
                
                *pPrimeroC  = pRegistro;
                *pUltimoC = pRegistro;
            }
            else
            {
                
               (*pUltimoC)->pSig = pRegistro;
                pRegistro->pAnt = *pUltimoC;
                *pUltimoC = pRegistro;  
            }     
        }
    }
    while(!feof(*ArchivoCompra));
}//FIN indexarCompras

/*
Nombre: guardarComprasEnArchivo
Objetivo: Guardar en el archivo(ArchivoCompra), las compras actuales que se encuentran en la lista(pPrimeroC).
Parametros de Entrada(E) y Salida(S): (S)ArchivoCompra- Archivo donde se guardaran las compras.
    (E)pPrimeroC- contiene las compras realizadas.
*/
void guardarComprasEnArchivo( fArchivoCompra *ArchivoCompra, TpCompra pPrimeroC){
//Variables
    TrCompra rCompra;
    TpCompra pPos;
//Inicio
    if(pPrimeroC != NULL)
    {
        pPos = pPrimeroC;

        while( pPos != NULL)
        {

            rCompra.fCosto = pPos->fCosto;
            rCompra.eCantProd = pPos->eCantProd;
            strcpy( rCompra.cFecha_de_compra , pPos->cFecha_de_compra );
            rCompra.fImporte = pPos->fImporte;
            rCompra.eCodigoProd = pPos->eCodigoProd;

            fwrite(& rCompra , sizeof( rCompra ), 1, *ArchivoCompra); //Escribe en el archivo

            pPos = pPos->pSig;
        }    
    }
    fclose(*ArchivoCompra); //Cierra archivo
}//FIN guardarComprasEnArchivo
