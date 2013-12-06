/*
    Programa- Proveedores.h
    Autor- Equipo SysteMy
    Fecha- 17/11/12
    Objetivo- Archivo o clase, que contiene la estructura y las funciones de los proveedores.
*/

//CONSTANTES
#define PEDIDOS 50

//TIPOS
typedef FILE *fArchivoProve; //ARCHIVO

typedef struct //FECHA
{
    int eMes;
    int eDia;
    int eAnio;
} TrFecha;
typedef TrFecha TaFecha[PEDIDOS];

//PROVEEDOR
typedef struct proveedor
{
    char cNombreProv[30];
    char cRepartidor[30];
    char cVendedor[30];
    char cDomicilio[50];
    char cTelefono[10];
    char cRfc[30];
    TaFecha aFecha_de_pedido;
    TaFecha aFecha_de_entrega;
    TrFecha rFecha_de_alta;
    struct proveedor *pSig;
    int eTotal_aFecha_pedido;
    int eTotal_aFecha_entrega;
} TrProveedor;
typedef TrProveedor *TpProveedor;

//PROTOTIPOS
void crearArchivoProveedor(fArchivoProve  *, TpProveedor *);
void indexarProveedor(fArchivoProve *, TpProveedor *);

void proveedores(TpProveedor *);
void altaProveedor(TpProveedor *);
void bajaProveedor(TpProveedor *);
void consultarProveedor(TpProveedor);
void modificarProveedor(TpProveedor *);

int listaVacia(TpProveedor);
int listaLlena(TpProveedor *);
void insertarProveedor(TpProveedor *);
TpProveedor buscarProveedor(TpProveedor pProveedor, char *);
void imprimirProveedor(TpProveedor);
void eliminarProveedor(TpProveedor * , char *);
void modificar_Dato_Proveedor(TpProveedor * , char *);
void imprimirFecha(TaFecha , int);

void LiberarMemoriaProveedor(TpProveedor);
void guardarProveedoresEnArchivo( fArchivoProve *, TpProveedor);

//FUNCIONES
/*
Nombre: proveedores
Objetivo: Submenu que contiene las funciones de altas, bajas, modificaciones y consulta 
    de un prooveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- Donde se llevaran acabo las funciones 
    antes mencionadas en el objetivo.
*/
void proveedores(TpProveedor *pProveedor){
//Variables    
    char cOpc;
    
//Inicio
    do
    {
        printf("------------------\nProveedores\n------------------\n");
        printf("A- Altas\n");
        printf("B- Bajas\n");
        printf("C- Consultas\n");
        printf("M- Modificar\n");
        printf("R- Regresar Menu Principal\n");
        printf("\n\t\t\t\t\t\tSeleccione una opcion: ");
        scanf("%c",&cOpc);
        fflush(stdin);
        switch(toupper(cOpc))
        {
        case 'A':
            system("cls");
            altaProveedor( &(*pProveedor) );
            break;
        case 'B':
            system("cls");
            bajaProveedor( &(*pProveedor) );
            break;
        case 'C':
            system("cls");
            consultarProveedor( *pProveedor );
            break;
        case 'M':
            system("cls");
            modificarProveedor( &(*pProveedor) );
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
}//FIN proveedores

/*
Nombre: altaProveedor
Objetivo: Menu que permite realizar la alta de un proveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- donde se guardara el proveedor dado de alta
*/
void altaProveedor(TpProveedor *pProveedor){
//Variables
    char cDecision;

//Inicio
    do
    {
        printf("------------------\nAltas\n------------------\n");
        insertarProveedor( & (*pProveedor) );
        do
        {
            printf("\nDesea dar de alta otro proveedor[S/N]: ");
            scanf("%c",&cDecision);
            fflush(stdin);
        }
        while(toupper(cDecision) != 'S' &&  toupper(cDecision) != 'N' );
        system("cls");
    }
    while(toupper(cDecision) != 'N');
    printf("\n\t\t\t\t\tPresione Enter para regresar al menu");
    getch();
    system("cls");
}//FIN altaProveedor

/*
Nombre: bajaProveedor
Objetivo: Menu que permite realizar la baja de un proveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- donde se guardara el proveedor dado de baja.
*/
void bajaProveedor(TpProveedor *pProveedor){
//Variables
    char cProveedor[20];
    char cDecision;

//Inicio
    do
    {
        printf("------------------\nBajas\n------------------\n");
        printf("Ingresa el proveedor: ");
        gets(cProveedor);
        eliminarProveedor( &(*pProveedor) , cProveedor);

        do
        {
            printf("\nDesea dar de baja otro proveedor[S/N]: ");
            scanf("%c",&cDecision);
            fflush(stdin);
        }
        while(toupper(cDecision) != 'S' &&  toupper(cDecision) != 'N' );
        system("cls");
    }
    while(toupper(cDecision) != 'N');
    printf("\n\t\t\t\t\tPresione Enter para regresar al menu");
    getch();
    system("cls");
}//FIN bajaProveedor

/*
Nombre: consultarProveedor
Objetivo: Menu que permite realizar la consulta de la informacion de un proveedor.
Parametros de Entrada(E) y Salida(S): (E)pProveedor- contiene la informacion del proveedor que se
    consultara. 
*/
void consultarProveedor(TpProveedor pProveedor){
//Variables
    char cProveedor[20];
    char cDecision;

//Inicio
    do
    {
        imprimirProveedor( pProveedor);
        do
        {
            printf("\nDesea consultar otro vez[S/N]: ");
            scanf("%c",&cDecision);
            fflush(stdin);
        }
        while(toupper(cDecision) != 'S' &&  toupper(cDecision) != 'N' );
        system("cls");
    }
    while(toupper(cDecision) != 'N');
    printf("\n\t\t\t\t\tPresione Enter para regresar al menu");
    getch();
    system("cls");
}//FIN consultarProveedor

/*
Nombre: modificarProveedor
Objetivo: Menu que permite realizar la modificacion de un proveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- contiene la informacion que se modificara
    del proveedor.  
*/
void modificarProveedor(TpProveedor *pProveedor){
//Variables
    char cProveedor[20];
    char cDecision;

//Inicio
    do
    {
        printf("------------------\nModificar\n------------------\n");
        printf("Ingresa el proveedor: ");
        gets(cProveedor);
        modificar_Dato_Proveedor( &(*pProveedor) , cProveedor);

        do
        {
            printf("\nDesea modificar otro proveedor[S/N]: ");
            scanf("%c",&cDecision);
            fflush(stdin);
        }
        while(toupper(cDecision) != 'S' &&  toupper(cDecision) != 'N' );
        system("cls");
    }
    while(toupper(cDecision) != 'N');
    printf("\n\t\t\t\t\tPresione Enter para regresar al menu");
    getch();
    system("cls");
}//FIN modificarProveedor

/*
Nombre: LiberarMemoriaProveedor
Objetivo: Liberar la memoria de la lista de proveedores.
Parametros de Entrada(E) y Salida(S): (E)pProveedor- donde se llevara acabo la liberación de
    memoria.
*/
void LiberarMemoriaProveedor(TpProveedor pProveedor){
//Variables
    TpProveedor pBorrar;

//Inicio
    if (pProveedor != NULL)
    {

        while (pProveedor != pProveedor->pSig)
        {

            pBorrar = pProveedor->pSig;
            pProveedor->pSig = pBorrar->pSig;
            free(pBorrar);

        }
    }

} //LiberarMemoria

/*
Nombre: listaVacia
Objetivo: Si la lista se encuentra vacia
Parametros de Entrada(E) y Salida(S): (E)pPrimero- Contiene el primer elemento de la lista
*/
int listaVacia(TpProveedor pPrimero){
//Inicio
    return pPrimero == NULL;
}//FIN listaVacia


/*
Nombre: listaLlena
Objetivo: Si la lista se encuentra llena
Parametros de Entrada(E) y Salida(S): (S)pNuevo- Se utiliza para verificar si la lista esta llena
*/
int listaLlena(TpProveedor *pNuevo){
//Inicio    
    *pNuevo = (TpProveedor) malloc(sizeof(TrProveedor));
    return *pNuevo == NULL;
}//FIN listaLlena

/*
Nombre: registrarProveedor.
Objetivo: Registrar los datos de un proveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- donde se registran los datos del proveedor.
*/
void insertarProveedor(TpProveedor *pProveedor){
//Variables
    TpProveedor pNuevo , pPos;

//Inicio
    if( listaLlena (&pNuevo) )
    {

        printf("\n\n\n\t\tOverflow");
        getch();

    }
    else
    {
        
        pNuevo->eTotal_aFecha_pedido = -1; 
        pNuevo->eTotal_aFecha_entrega = -1;
        
        printf("ALTA DE PROVEEDORES\n");
        printf("Nombre del proveedor: ");
        gets( pNuevo->cNombreProv );
        printf("Lugar de residencia: ");
        gets( pNuevo->cDomicilio);
        printf("Numero de comunicacion: ");
        gets( pNuevo->cTelefono);
        printf("Ingrese RFC: ");
        gets( pNuevo->cRfc);
        printf("Nombre del encargado de repartir el pedido: ");
        gets( pNuevo->cRepartidor);
        printf("Nombre del encargado de levantar el pedido: ");
        gets( pNuevo->cVendedor);
        
        pNuevo->eTotal_aFecha_pedido =  pNuevo->eTotal_aFecha_pedido + 1;
        printf("Fecha de pedido [dd/mm/aaaa]: ");
        scanf("%d/%d/%d" , &pNuevo->aFecha_de_pedido[ pNuevo->eTotal_aFecha_pedido].eDia,
        &pNuevo->aFecha_de_pedido[ pNuevo->eTotal_aFecha_pedido].eMes,
        &pNuevo->aFecha_de_pedido[ pNuevo->eTotal_aFecha_pedido].eAnio);
        fflush(stdin);
         
        pNuevo->eTotal_aFecha_entrega = pNuevo->eTotal_aFecha_entrega + 1;
        printf("Fecha de visita [dd/mm/aaaa]: ");
        scanf("%d/%d/%d" , &pNuevo->aFecha_de_entrega[pNuevo->eTotal_aFecha_entrega].eDia,
        &pNuevo->aFecha_de_entrega[pNuevo->eTotal_aFecha_entrega].eMes,
        &pNuevo->aFecha_de_entrega[pNuevo->eTotal_aFecha_entrega].eAnio);
        fflush(stdin);
        
        printf("Fecha de alta [dd/mm/aaaa]: ");
        scanf("%d/%d/%d" , &pNuevo->rFecha_de_alta.eDia,&pNuevo->rFecha_de_alta.eMes,&pNuevo->rFecha_de_alta.eAnio);
        fflush(stdin);
        
        
        if( listaVacia( (*pProveedor) ) )
        {

            *pProveedor  = pNuevo;
            (*pProveedor)->pSig = pNuevo;

        }
        else
        {

            pPos = buscarProveedor( *pProveedor, pNuevo->cNombreProv);

            if( pPos != NULL)
            {

                printf("---El proveedor %s ya existe---\n" , pNuevo->cNombreProv);
                getch();

            }
            else
            {

                if( strcmp ( pNuevo->cNombreProv , (*pProveedor)->cNombreProv) > 0 )
                {

                    pNuevo->pSig = (*pProveedor)->pSig;
                    (*pProveedor)->pSig = pNuevo;
                    *pProveedor = pNuevo;

                }
                else
                {

                    if( strcmp ( pNuevo->cNombreProv, (*pProveedor)->pSig->cNombreProv) < 0 )
                    {

                        pNuevo->pSig = (*pProveedor)->pSig;
                        (*pProveedor)->pSig = pNuevo;
                    }
                    else
                    {

                        pPos = (*pProveedor)->pSig;

                        while ( strcmp ( pPos->pSig->cNombreProv , pNuevo->cNombreProv) < 0)
                        {
                            pPos = pPos->pSig;
                        }
                        pNuevo->pSig = pPos->pSig;
                        pPos->pSig = pNuevo;

                    }
                }
            }
        }
    }
    system("cls");
}//FIN insertarProveedor

/*
Nombre: buscarProveedor
Objetivo: Buscar en la lisda un proveedor.
Parametros de Entrada(E) y Salida(S): (E)pProveedor- donde se realizara la busqueda del proveedor.
    (E)Nombre- Nombre del proveedor que se desea buscar en la lista.
Tipo de retorno: TpProveedor- contiene la ubicacion dentro de la lista donde se encuentra
    el proveedor.
*/  
TpProveedor buscarProveedor(TpProveedor pProveedor, char *Nombre){
//Variables
    TpProveedor pPos;

//Inicio
    if ( listaVacia(pProveedor) )
    {

        printf("\n\n\n\t\tUnderflow");
        getch();
        return NULL;

    }
    else
    {

        pPos = pProveedor->pSig;

        while( ( pPos != pProveedor ) &&	( strcmp (pPos->cNombreProv , Nombre) < 0 ) )
        {
            pPos = pPos->pSig;
        }


        if ( strcmp (pPos->cNombreProv , Nombre) == 0)
        {
            return pPos;
        }

        else
        {
            return NULL;
        }
    }
    system("cls");
}//BuscarElemento

/*
Nombre: imprimirProveedor
Objetivo: Listar los proveedores actuales.
Parametros de Entrada(E) y Salida(S): (E)pProveedor- contiene la informacion de los proveedores.
*/
void imprimirProveedor(TpProveedor pProveedor){
//Variables
    TpProveedor pPos;

//Inicio         
    if(pProveedor == NULL){
        
        printf("\n\n\n\t\tUnderflow");     
    }
    else{
        
        pPos = pProveedor->pSig;
        
        system("cls");
        printf("\n-----------*****Proveedores*****------------\n");    
        while(pPos != pProveedor){
            
            printf("Nombre: %s\n",pPos->cNombreProv);
            printf("Lugar de residencia: %s\n",pPos->cDomicilio);
            printf("Numero de comunicacion: %s\n",pPos->cTelefono);
            printf("Ingrese RFC: %s\n",pPos->cRfc);
            printf("Nombre del encargado de repartir el pedido: %s\n",pPos->cRepartidor);
            printf("Nombre del encargado de levantar el pedido: %s\n",pPos->cVendedor);
            printf("Fecha de pedidos\n");
            imprimirFecha( pPos->aFecha_de_pedido , pPos->eTotal_aFecha_pedido);  
            printf("\nFecha de visitas\n");
            imprimirFecha( pPos->aFecha_de_entrega , pPos->eTotal_aFecha_entrega); 
            printf("\nFecha de alta\n%i/%i/%i",pPos->rFecha_de_alta.eDia, pPos->rFecha_de_alta.eMes, pPos->rFecha_de_alta.eAnio);
            printf("\n----------------------------------------------\n");
            getch();   
            system("cls");
            
            pPos = pPos->pSig;        
        }
        
        printf("----------------------------------------------\n");
        printf("Nombre: %s\n",pPos->cNombreProv);
        printf("Lugar de residencia: %s\n",pPos->cDomicilio);
        printf("Numero de comunicacion: %s\n",pPos->cTelefono);
        printf("Ingrese RFC: %s\n",pPos->cRfc);
        printf("Nombre del encargado de repartir el pedido: %s\n",pPos->cRepartidor);
        printf("Nombre del encargado de levantar el pedido: %s\n",pPos->cVendedor);
        printf("Fecha de pedidos\n");
        imprimirFecha( pPos->aFecha_de_pedido , pPos->eTotal_aFecha_pedido);  
        printf("\nFecha de visitas\n");
        imprimirFecha( pPos->aFecha_de_entrega , pPos->eTotal_aFecha_entrega);
        printf("\nFecha de alta\n%i/%i/%i",pPos->rFecha_de_alta.eDia, pPos->rFecha_de_alta.eMes, pPos->rFecha_de_alta.eAnio);
        printf("\n----------------------------------------------");     
    }
    getch();
    system("cls");
}//FIN imprimirProveedor

/*
Nombre: eliminarProveedor
Objetivo: Eliminar un proveedor de la lista.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- donde se llevara acabo la eliminacion
    del proveedor.
    (E)cNombre- nombre del proveedor a eliminar.
*/
void eliminarProveedor(TpProveedor *pProveedor,char *cNombre)
{

    TpProveedor pPos , pBorrar;

    if(listaVacia( *pProveedor ) )
    {

        printf("\n\n\n\t\tUnderflow");
        getch();

    }
    else
    {

        pPos = buscarProveedor( *pProveedor , cNombre);

        if( pPos == NULL)
        {

            printf("\n---El proveedor %s no existe---\n",cNombre);
            getch();
        }
        else
        {

            pBorrar = pPos;

            if ( *pProveedor == (*pProveedor)->pSig)
            {

                *pProveedor = NULL;

            }
            else
            {

                if (pPos == (*pProveedor)->pSig)
                {

                    (*pProveedor)->pSig = pPos->pSig;

                }
                else
                {

                    pPos = (*pProveedor)->pSig;

                    while (pBorrar != pPos->pSig)
                    {

                        pPos = pPos->pSig;
                    }


                    pPos->pSig = pBorrar->pSig;

                    if (pBorrar == *pProveedor)
                    {
                        *pProveedor = pPos;
                    }

                }
            }
            free(pBorrar);
            printf("---El proveedor %s ha sido borrado de la lista---", cNombre);
            getch();
        }
    }
    system("cls");
}//FIN eliminarProveedor

/*
Nombre: modificar_Dato_Proveedor
Objetivo: Modificar informacion de un proveedor.
Parametros de Entrada(E) y Salida(S): (S)pProveedor- contiene la informacion del proveedor
    a modifcar.
    (E)cNombre- Nombre del proveedor a modificar.
*/
void modificar_Dato_Proveedor(TpProveedor *pProveedor , char *cNombre){
//Variables
    TpProveedor pPos;
    int eOpc;

//Inicio
    if(listaVacia (*pProveedor) )
    {

        printf("\n\n\n\t\tUnderflow");
        getch();

    }
    else
    {

        pPos = buscarProveedor( *pProveedor , cNombre);

        if( pPos == NULL)
        {

            printf("\n\t\t---El proveedor %s no existe---\n",cNombre);
            getch();

        }
        else
        {

            printf("Dato que desea modificar: \n1- Repartidor\n2- Vendedor\n3- Domicilio\n4- Telefono\n");
            printf("5- RFC\n6- Fecha de visita\n7- Fecha de alta\nElija una opcion: ");
            scanf("%i",&eOpc);
            fflush(stdin);

            switch(eOpc)
            {
            case 1:
                printf("Nuevo repartidor: ");
                gets(pPos->cRepartidor);
                break;
            case 2:
                printf("Nuevo vendedor: ");
                gets(pPos->cVendedor);
                break;
            case 3:
                printf("Nuevo domicilio: ");
                gets(pPos->cDomicilio);
                break;
            case 4:
                printf("Nuevo telefono: ");
                gets(pPos->cTelefono);
                break;
            case 5:
                printf("Nuevo RFC: ");
                gets(pPos->cRfc);
                break;
            case 6:
                printf("Nueva fecha de pedido [dd/mm/aaaa]: ");
                scanf("%d/%d/%d" , &pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eDia,
                &pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eMes,
                &pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eAnio);
                fflush(stdin);
                break;
            case 7:
                break;
            }
        }
    }
    system("cls");
}//FIN modificar_Dato_Proveedor

/*
Nombre; imprimirFecha
Objetivo: Imprimir en pantalla la fecha.
Parametros de Entrada(E) y Salida(S): (E)aFecha- contiene el arreglo de las fechas a mostrar.
    (E)eTotal- Total de fechas registradas en el arreglo.
*/
void imprimirFecha(TaFecha aFecha,int eTotal){
//Variables    
    int eRecorre;

//Inicio
    for(eRecorre = 0; eRecorre <= eTotal; eRecorre++){ 
        printf("%i/%i/%i\n" , aFecha[eRecorre].eDia ,aFecha[eRecorre].eMes , 
        aFecha[eRecorre].eAnio);       
    }        
}//FIN imprimirFecha

/*
Nombre: crearArchivoProveedor
Objetivo: Crear un archivo binario y extraer datos él.
Parametros de Entrada(E) y Salida(S): (S)ArchivoProve- Archivo que se va crear.
    (S)pProveedor- Donde se van a guardar los datos extraidos del archivo.
*/
void crearArchivoProveedor(fArchivoProve *ArchivoProve, TpProveedor *pProveedor){
//Inicio
    if( (*ArchivoProve = fopen("Proveedores.dat" , "ab+")) == NULL ) //Abre el fichero para lecturay y escritura. La escritura comenzará al final del fichero, respetando el contenido.
    {
        printf("No se puede abrir el archivo\n");
    }
    else
    {
        indexarProveedor( &(*ArchivoProve) , &(*pProveedor) ); //indexa
        
        //Abre el fichero para lectura y escritura. Crea el fichero si no existe y borra el contenido si existe.
        *ArchivoProve = fopen("Proveedores.dat" , "wb+"); 
    }
}//FIN crearArchivoProducto

/*
Nombre: indexarProveedor
Objetivo: Extraer los datos del archivo(ArchivoProve) a la lista(pProveedor).
Parametros de Entrada(E) y Salida(S): (S)ArchivoProve- Contiene los datos a extraer.
    (S)pProveedor- Lista donde se guardaran los datos extraídos.
*/
void indexarProveedor(fArchivoProve *ArchivoProve, TpProveedor *pProveedor){
//Variables    
    TrProveedor rRegistro;
    TpProveedor pRegistro;
    int eRecorre;
    
//Inicio
    rewind(*ArchivoProve); //Posiciona al inicio del archivo

    do
    {
        //Devuelve el numero de elementos leidos del archivo
        fread(&rRegistro, sizeof(rRegistro) , 1, *ArchivoProve);

        if( !feof(*ArchivoProve) )
        {
            if( listaLlena(&pRegistro) )
            {
                printf("OverFlow\n");
            }
            
            strcpy(pRegistro->cNombreProv , rRegistro.cNombreProv);
            strcpy(pRegistro->cDomicilio , rRegistro.cDomicilio);
            strcpy(pRegistro->cTelefono , rRegistro.cTelefono);
            strcpy(pRegistro->cRfc , rRegistro.cRfc);
            strcpy(pRegistro->cRepartidor , rRegistro.cRepartidor);
            strcpy(pRegistro->cVendedor , rRegistro.cVendedor);
            
            pRegistro->eTotal_aFecha_pedido = rRegistro.eTotal_aFecha_pedido;
            for(eRecorre = 0; eRecorre <= rRegistro.eTotal_aFecha_pedido; eRecorre++){
                
                pRegistro->aFecha_de_pedido[ eRecorre ].eDia =  rRegistro.aFecha_de_pedido[ eRecorre ].eDia;     
                pRegistro->aFecha_de_pedido[ eRecorre ].eMes =  rRegistro.aFecha_de_pedido[ eRecorre ].eMes;
                pRegistro->aFecha_de_pedido[ eRecorre ].eAnio =  rRegistro.aFecha_de_pedido[ eRecorre ].eAnio;
            }
            
            pRegistro->eTotal_aFecha_entrega = rRegistro.eTotal_aFecha_entrega;
            for(eRecorre = 0; eRecorre <= rRegistro.eTotal_aFecha_entrega; eRecorre++){
                
                pRegistro->aFecha_de_entrega[ eRecorre ].eDia =  rRegistro.aFecha_de_entrega[ eRecorre ].eDia;     
                pRegistro->aFecha_de_entrega[ eRecorre ].eMes =  rRegistro.aFecha_de_entrega[ eRecorre ].eMes;
                pRegistro->aFecha_de_entrega[ eRecorre ].eAnio = rRegistro.aFecha_de_entrega[ eRecorre ].eAnio;
            }
            
            pRegistro->rFecha_de_alta.eDia = rRegistro.rFecha_de_alta.eDia;
            pRegistro->rFecha_de_alta.eMes = rRegistro.rFecha_de_alta.eMes;
            pRegistro->rFecha_de_alta.eAnio = rRegistro.rFecha_de_alta.eAnio;
            
            if( listaVacia( *pProveedor ) )
            {
                
                *pProveedor  = pRegistro;
                (*pProveedor)->pSig = pRegistro;
            }
            else
            {
                  
                pRegistro->pSig = (*pProveedor)->pSig;
                (*pProveedor)->pSig = pRegistro;
                *pProveedor = pRegistro;
            }     
        }
    }
    while(!feof(*ArchivoProve));
}//FIN indexarProveedor

/*
Nombre: guardarProveedoresEnArchivo
Objetivo: Guardar en el archivo(ArchivoProve), los proveedores actuales que se encuentran en la lista(pProveedor).
Parametros de Entrada(E) y Salida(S): (S)ArchivoProve- Archivo donde se guardaran los proveedores.
    (E)pProveedor- contiene los proveedores a guardar.
*/
void guardarProveedoresEnArchivo( fArchivoProve *ArchivoProve, TpProveedor pProveedor){
//Variables
    TrProveedor rProveedor;
    TpProveedor pPos;
//Inicio
    if(pProveedor != NULL){
            pPos = pProveedor->pSig;
        
            while( pPos != pProveedor){
                
                strcpy(rProveedor.cNombreProv , pPos->cNombreProv);
                strcpy(rProveedor.cDomicilio , pPos->cDomicilio);
                strcpy(rProveedor.cTelefono , pPos->cTelefono);
                strcpy(rProveedor.cRfc , pPos->cRfc);
                strcpy(rProveedor.cRepartidor , pPos->cRepartidor);
                strcpy(rProveedor.cVendedor , pPos->cVendedor);
                
                rProveedor.eTotal_aFecha_pedido =  pPos->eTotal_aFecha_pedido;
                rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eDia = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eDia;
                rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eMes = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eMes;
                rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eAnio = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eAnio;
                
                rProveedor.eTotal_aFecha_entrega =  pPos->eTotal_aFecha_entrega;
                rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eDia = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eDia;
                rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eMes = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eMes;
                rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eAnio = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eAnio;
                
                rProveedor.rFecha_de_alta.eDia = pPos->rFecha_de_alta.eDia;
                rProveedor.rFecha_de_alta.eMes = pPos->rFecha_de_alta.eMes;
                rProveedor.rFecha_de_alta.eAnio = pPos->rFecha_de_alta.eAnio;
                
                fwrite(& rProveedor , sizeof( rProveedor ), 1, *ArchivoProve); //Escribe en el archivo
                
                pPos = pPos->pSig;    
            }
        
            strcpy(rProveedor.cNombreProv , pPos->cNombreProv);
            strcpy(rProveedor.cDomicilio , pPos->cDomicilio);
            strcpy(rProveedor.cTelefono , pPos->cTelefono);
            strcpy(rProveedor.cRfc , pPos->cRfc);
            strcpy(rProveedor.cRepartidor , pPos->cRepartidor);
            strcpy(rProveedor.cVendedor , pPos->cVendedor);
            
            rProveedor.eTotal_aFecha_pedido =  pPos->eTotal_aFecha_pedido;
            rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eDia = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eDia;
            rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eMes = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eMes;
            rProveedor.aFecha_de_pedido[ rProveedor.eTotal_aFecha_pedido].eAnio = pPos->aFecha_de_pedido[ pPos->eTotal_aFecha_pedido].eAnio;
            
            rProveedor.eTotal_aFecha_entrega =  pPos->eTotal_aFecha_entrega;
            rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eDia = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eDia;
            rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eMes = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eMes;
            rProveedor.aFecha_de_entrega[ rProveedor.eTotal_aFecha_entrega].eAnio = pPos->aFecha_de_entrega[ pPos->eTotal_aFecha_entrega].eAnio;
            
            rProveedor.rFecha_de_alta.eDia = pPos->rFecha_de_alta.eDia;
            rProveedor.rFecha_de_alta.eMes = pPos->rFecha_de_alta.eMes;
            rProveedor.rFecha_de_alta.eAnio = pPos->rFecha_de_alta.eAnio;
                
            fwrite(& rProveedor , sizeof( rProveedor ), 1, *ArchivoProve); //Escribe en el archivo  
            
            fclose(*ArchivoProve);               
    }
    
}//FIN guardarProveedoresEnArchivo
