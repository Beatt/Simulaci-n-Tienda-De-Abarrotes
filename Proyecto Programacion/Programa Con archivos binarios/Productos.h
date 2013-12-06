/*
    Programa- Productos.h
    Autor- Equipo SysteMy
    Fecha- 17/11/12
    Objetivo- Archivo o clase, que contiene la estructura y las funciones de los productos.
*/

//TIPOS
typedef FILE *fArchivoProd; //ARCHIVO

typedef struct producto{
    int eCodigoProd;
    char cProducto[30];
    float fCosto;
    float fPrecio;
    char cProveedor[30];
    int eExistencia;
    int eExistenciaMinima;
    struct producto *pSig; 
}TrProducto;
typedef TrProducto *TpProducto; //PRODUCTO


//PROTOTIPOS
void crearArchivoProducto(fArchivoProd  *, TpProducto *);
void indexarProducto(fArchivoProd *, TpProducto *);

void productos(TpProducto *);
void altaProducto(TpProducto *);
void bajaProducto(TpProducto *);
void modificarProducto(TpProducto *);
int listaLlenaProducto(TpProducto *);
int listaVaciaProducto(TpProducto);

void insertarProducto(TpProducto *);
void eliminarProducto(TpProducto * , int);
TpProducto buscarProducto(TpProducto , int );
void modificar_Dato_Producto(TpProducto * , int );
void imprimirInventario(TpProducto);

void LiberarMemoriaProducto(TpProducto);
void guardarProductosEnArchivo( fArchivoProd *, TpProducto);

//FUNCIONES
/*
Nombre: productos
Objetivo: Submenú que contiene las funciones de altas, bajas, modificaciones de un producto, 
    así como una impresión en pantalla del inventario de los productos que se encuentran en la lista.
Parámetros de Entrada(E) y Salida(S): (S)pProducto - Donde se llevaran acabo las funciones 
    antes mencionadas en el objetivo.
*/
void productos(TpProducto *pProducto){
//Variables
    char cOpc;
    
//Inicio
    do
    {
        printf("------------------\nProductos\n------------------\n");
        printf("A- Altas\n");
        printf("B- Bajas\n");
        printf("M- Modificar\n");
        printf("I- Inventario\n");
        printf("R- Regresar Menu Principal\n");
        printf("\n\t\t\t\t\t\tSeleccione una opcion: ");
        scanf("%c",&cOpc);
        fflush(stdin);
        switch(toupper(cOpc))
        {
        case 'A':
            system("cls");
            altaProducto( &(*pProducto) );
            break;
        case 'B':
            system("cls");
            bajaProducto( &(*pProducto) );
            break;
        case 'M':
            system("cls");
            modificarProducto( &(*pProducto) );
            break;
        case 'I':
            system("cls");
            imprimirInventario( *pProducto );
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

/*
Nombre: altaProducto
Objetivo: Menú que permite realizar la alta de un producto.
Parámetros de Entrada(E) y Salida(S): (S)pProducto- donde se guardará el producto que se de
    de alta.  
*/
void altaProducto(TpProducto *pProducto){
//Variables
    char cDecision;
    
//Inicio
    do
    {
        printf("------------------\nAltas\n------------------\n");
        insertarProducto( &(*pProducto) );
        do
        {
            printf("\nDesea dar de alta otro producto[S/N]: ");
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
}//FIN altaProducto

/*
Nombre: bajaProducto
Objetivo: Menú que permite realizar la baja de un producto.
Parámetros de Entrada(E) y Salida(S): (S)pProducto - donde se guardará el producto que se 
    de de baja.  
*/
void bajaProducto(TpProducto *pProducto){
//Variables
    int eCodigoProd;
    char cDecision;

//Inicio
    do
    {
        printf("------------------\nBajas\n------------------\n");
        printf("Ingresa el codigo del producto: ");
        scanf("%d" , &eCodigoProd);
        fflush(stdin);
        eliminarProducto( &(*pProducto) , eCodigoProd );

        do
        {
            printf("\nDesea dar de baja otro producto[S/N]: ");
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
}//FIN bajaProducto

/*
Nombre: modificarProducto
Objetivo: Menú que permite realizar la modificación de un producto.
Parámetros de Entrada(E) y Salida(S): (S)pProducto - contiene la información que se modificará
    del producto.  
*/
void modificarProducto(TpProducto *pProducto){
//Variables
    int eCodigoProd;
    char cDecision;
    
//Inicio
    do
    {
        printf("------------------\nModificar\n------------------\n");
        printf("Ingresa el ID del producto: ");
        scanf("%d", &eCodigoProd);
        fflush(stdin);
        modificar_Dato_Producto( &(*pProducto) , eCodigoProd);

        do
        {
            printf("\nDesea modificar otro producto[S/N]: ");
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
}//FIN modificarProducto
 

//FUNCIONES

/*
Nombre: listaLlenaProducto
Objetivo: Si la lista se encuentra llena
Parametros de Entrada(E) y Salida(S): (S)pNuevo- Se utiliza para verificar si la lista esta llena
*/
int listaLlenaProducto(TpProducto *pNuevo){
//Inicio  
    *pNuevo = (TpProducto) malloc(sizeof(TrProducto));
    return *pNuevo == NULL;
}//FIN listaLlenaProducto

/*
Nombre: listaVaciaProducto
Objetivo: Si la lista se encuentra vacia
Parametros de Entrada(E) y Salida(S): (E)pPrimero- Contiene el primer elemento de la lista
*/
int listaVaciaProducto(TpProducto pPrimero){
//Inicio   
    return pPrimero == NULL;
}//FIN listaVaciaProducto

/*
Nombre: insertarProducto.
Objetivo: Registrar los datos de un producto.
Parametros de Entrada(E) y Salida(S): (S)pProducto- donde se guardaran los datos del producto.
*/
void insertarProducto(TpProducto *pProducto){
//Variables
    TpProducto pNuevo , pPos;
    TrProducto rProducto;

//Inicio
    if( listaLlenaProducto (&pNuevo) )
    {

        printf("\n\n\n\t\tOverflow");
        getch();

    }
    else{
        
        printf("ALTA DE PRODUCTOS\n");
        printf("Nombre del articulo: ");
        gets( (*pNuevo).cProducto);
        printf("Precio de compra: ");
        scanf("%f", &(*pNuevo).fCosto);
        fflush(stdin);
        printf("Precio al publico: ");
        scanf("%f", &(*pNuevo).fPrecio);
        fflush(stdin);
        printf("Nombre del proveedor: ");
        gets( (*pNuevo).cProveedor);
        printf("Existencia del producto actual: ");
        scanf("%d", &(*pNuevo).eExistencia);
        fflush(stdin);
        printf("Existencias minimas del producto: ");
        scanf("%d", &(*pNuevo).eExistenciaMinima);
        fflush(stdin);
        printf("Numero de identificacion del producto[ID]: ");
        scanf("%d" , &(*pNuevo).eCodigoProd);
        fflush(stdin);   
        
        if( listaVaciaProducto( (*pProducto) ) )
        {

            *pProducto  = pNuevo;
            (*pProducto)->pSig = pNuevo;
        }
        else{

            pPos = buscarProducto( *pProducto, pNuevo->eCodigoProd);

            if( pPos != NULL)
            {

                printf("---Este proveedor ya existe---\n");
                getch();

            }
            else{

                if( pNuevo->eCodigoProd > (*pProducto)->eCodigoProd  )
                {

                    pNuevo->pSig = (*pProducto)->pSig;
                    (*pProducto)->pSig = pNuevo;
                    *pProducto = pNuevo;

                }
                else{

                    if( pNuevo->eCodigoProd < (*pProducto)->pSig->eCodigoProd )
                    {

                        pNuevo->pSig = (*pProducto)->pSig;
                        (*pProducto)->pSig = pNuevo;
                    }
                    else{

                        pPos = (*pProducto)->pSig;

                        while ( pPos->pSig->eCodigoProd < pNuevo->eCodigoProd )
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
}//FIN insertarProducto

/*
Nombre: buscarProducto
Objetivo: Buscar en la lisda un producto.
Parametros de Entrada(E) y Salida(S): (E)pProducto- donde se realizara la busqueda del producto.
    (E)eCodigoProd- Producto que se buscara en la lista, la busqueda se realiza por el 
    codigo del preoducto(ID) del producto.
Tipo de retorno: TpProducto- contiene la ubicacion dentro de la lista donde se encuentra
    el producto.
*/            
TpProducto buscarProducto(TpProducto pProducto, int eCodigoProd){
//Variables
    TpProducto pPos;

//Inicio
    if ( listaVaciaProducto(pProducto) )
    {

        printf("\n\n\n\t\tUnderflow");
        getch();
        return NULL;

    }
    else
    {

        pPos = pProducto->pSig;

        while( ( pPos != pProducto ) &&	( pPos->eCodigoProd < eCodigoProd) )
        {
            pPos = pPos->pSig;
        }


        if ( pPos->eCodigoProd == eCodigoProd )
        {
            return pPos;
        }

        else
        {
            return NULL;
        }
    }
    system("cls");
}//FIN buscarProducto

/*
Nombre: eliminarProducto
Objetivo: Eliminar un producto de la lista.
Parametros de Entrada(E) y Salida(S): (S)pProducto- donde se llevara acabo la eliminacion del producto.
    (E)eCodigoProd- producto a buscar dentro de la lista.
*/
void eliminarProducto(TpProducto *pProducto,int eCodigoProd){
//Variables    
    TpProducto pPos , pBorrar;

//Inicio    
    if(listaVaciaProducto( *pProducto ) ){
        
        printf("\n\n\n\t\tUnderflow");
        getch(); 
           
    }else{
     
        pPos = buscarProducto( *pProducto , eCodigoProd);
        
        if( pPos == NULL){
            
            printf("No existe producto con este codigo %i\n",eCodigoProd);
            getch();    
        }else{
            
            pBorrar = pPos;
            
            if ( *pProducto == (*pProducto)->pSig) {

				*pProducto = NULL;

			} else {

				if (pPos == (*pProducto)->pSig) {

					(*pProducto)->pSig = pPos->pSig;

				} else {

					pPos = (*pProducto)->pSig;
					
                    while (pBorrar != pPos->pSig){
                        
                        pPos = pPos->pSig;
                    }      
                    
					pPos->pSig = pBorrar->pSig;

					if (pBorrar == *pProducto){
                        *pProducto = pPos;
                    }
						
				}
			}
			free(pBorrar);
			printf("El producto %i ha sido borrado de la lista", eCodigoProd);
			getch();    
        }       
    }
    system("cls");        
}//FIN eliminarProducto

/*
Nombre: modificar_Dato_Producto
Objetivo: Modificar informacion de un producto.
Parametros de Entrada(E) y Salida(S): (S)pProducto- contiene la informacion del 
    producto a modificar.
    (E)eCodigoProd- codigo del producto(ID) del producto a modificar.
*/
void modificar_Dato_Producto(TpProducto *pProducto , int eCodigoProd){
    
    TpProducto pPos;
    int eOpc;
    
    if(listaVaciaProducto (*pProducto) ){
        
        printf("\n\n\n\t\tUnderflow");
        getch();    
            
    }else{

        pPos = buscarProducto( *pProducto , eCodigoProd);
        
         if( pPos == NULL){
            
            printf("\n\t\t---No existe producto con la %i---\n" , eCodigoProd);
            getch();
                
        }else{
            
            printf("Dato que desea modificar: \n1- Costo\n2- Precio\n3- Proveedor\n4- Existencia Actual\n");
            printf("5- Existencia Mimina\n6- Nombre\nElija una opcion: ");
            scanf("%i",&eOpc);
            fflush(stdin);

            switch(eOpc){
                case 1: printf("Nuevo precio de compra: ");
                        scanf("%f" , &pPos->fCosto);
                        fflush(stdin);
                        break;
                case 2: printf("Nuevo precio al publico: ");
                        scanf("%f" , &pPos->fPrecio);
                        fflush(stdin);
                        break;
                case 3: printf("Nuevo proveedor: ");
                        gets(pPos->cProveedor);
                        break;
                case 4: printf("Nueva existencia actual: ");
                        scanf("%d" , &pPos->eExistencia);
                        fflush(stdin);
                        break;
                case 5: printf("Nueva existencia minima: ");
                        scanf("%d" , &pPos->eExistenciaMinima);
                        fflush(stdin);
                        break;
                case 6: printf("Nuevo nombre: ");
                        gets(pPos->cProducto);
                        break;    
            }          
        }            
    }
    system("cls");       
}//FIN modificar_Dato_Producto

/*
Nombre: imprimirInventario
Objetivo: Mostrar el inventario de dos en dos.
Parametros de Entrada(E) y Salida(S): (E)pProducto- contiene los productos que se mostraran
    en pantalla.
*/
void imprimirInventario(TpProducto pProducto){
//Variables
    TpProducto pPos;
    int ePausa = 0;

//Inicio
	if (listaVaciaProducto(pProducto))
		printf("\n\n\n\t\tUnderflow");
	else {

		printf("\n------*****Invetario*****-----");
		pPos = pProducto->pSig;

		while (pPos != pProducto) {
            
            printf("\n\n----------------------------------------------\n");
            ePausa++;
			printf("Nombre del articulo: %s\nPrecio de compra: %f\n",pPos->cProducto , pPos->fCosto);
			printf("Precio al publico: %f\nNombre del proveedor: %s\n",pPos->fPrecio , pPos->cProveedor);
            printf("Existencia del producto actual: %i\n",pPos->eExistencia);
            printf("Existencias minimas del producto: %i\n",pPos->eExistenciaMinima);
            printf("Numero de identificacion del producto: %i\n",pPos->eCodigoProd);
            printf("----------------------------------------------\n");
			pPos = pPos->pSig;
			
			if( ePausa%2 == 0){ //Permite pausar, para mostrar de dos en dos productos.
                
                getch();
                system("cls");    
            }
		}
        printf("\n\n----------------------------------------------\n");
		printf("Nombre del articulo: %s\nPrecio de compra: %f\n",pPos->cProducto , pPos->fCosto);
		printf("Precio al publico: %f\nNombre del proveedor: %s\n",pPos->fPrecio , pPos->cProveedor);
        printf("Existencia del producto actual: %i\n",pPos->eExistencia);
        printf("Existencias minimas del producto: %i\n",pPos->eExistenciaMinima);
        printf("Numero de identificacion del producto: %i\n",pPos->eCodigoProd);
        printf("----------------------------------------------\n");

	}

	getch();
    system("cls");       
}// imprimirInventario

/*
Nombre: LiberarMemoriaProducto
Objetivo: Liberar la memoria de la lista de productos.
Parametros de Entrada(E) y Salida(S): (E)pProducto- donde se llevara acabo la liberación de
    memoria.
*/
void LiberarMemoriaProducto(TpProducto pProducto){
//Variables
    TpProducto pBorrar;

//Inicio
    if (pProducto != NULL)
    {

        while (pProducto != pProducto->pSig)
        {

            pBorrar = pProducto->pSig;
            pProducto->pSig = pBorrar->pSig;
            free(pBorrar);

        }
    }

}//LiberarMemoriaProducto

/*
Nombre: crearArchivoProducto
Objetivo: Crear un archivo binario y extraer datos de él.
Parametros de Entrada(E) y Salida(S): (S)ArchivoProd- Archivo que se va crear.
    (S)pProductos- Donde se van a guardar los datos extraidos del archivo.
*/
void crearArchivoProducto(fArchivoProd *ArchivoProd, TpProducto *pProducto){
//Inicio
    if( (*ArchivoProd = fopen("Productos.dat" , "ab+")) == NULL ) //Abre el fichero para lecturay y escritura. La escritura comenzará al final del fichero, respetando el contenido.
    {
        printf("No se puede abrir el archivo\n");
    }
    else
    {
        indexarProducto( &(*ArchivoProd) , &(*pProducto) ); //indexa
        
        //Abre el fichero para lectura y escritura. Crea el fichero si no existe y borra el contenido si existe.
        *ArchivoProd = fopen("Productos.dat" , "wb+"); 
    }
}//FIN crearArchivoProducto


/*
Nombre: indexarProducto
Objetivo: Extraer los datos del archivo(ArchivoProd) a la lista(pProducto).
Parametros de Entrada(E) y Salida(S): (S)ArchivoProd- Contiene los datos a extraer.
    (S)pProducto- Lista donde se guardaran los datos extraídos.
*/
void indexarProducto(fArchivoProd *ArchivoProd, TpProducto *pProducto){
//Variables    
    TrProducto rRegistro;
    TpProducto pRegistro;
    
//Inicio
    rewind(*ArchivoProd); //Posiciona al inicio del archivo

    do
    {
        //Devuelve el numero de elementos leidos del archivo
        fread(&rRegistro, sizeof(TrProducto) , 1, *ArchivoProd);

        if( !feof(*ArchivoProd) )
        {
            if( listaLlenaProducto(&pRegistro) )
            {
                printf("OverFlow\n");
            }
            //Asigna
            strcpy(pRegistro->cProducto , rRegistro.cProducto );
            pRegistro->fCosto = rRegistro.fCosto;
            pRegistro->fPrecio = rRegistro.fPrecio;
            strcpy(pRegistro->cProveedor , rRegistro.cProveedor );
            pRegistro->eExistencia = rRegistro.eExistencia;
            pRegistro->eExistenciaMinima = rRegistro.eExistenciaMinima;
            pRegistro->eCodigoProd = rRegistro.eCodigoProd;

            if( listaVaciaProducto( *pProducto ) )
            {
                
                *pProducto  = pRegistro;
                (*pProducto)->pSig = pRegistro;
            }
            else
            {
                  
                pRegistro->pSig = (*pProducto)->pSig;
                (*pProducto)->pSig = pRegistro;
                *pProducto = pRegistro;
            }     
        }
    }
    while(!feof(*ArchivoProd));
}//FIN indexarProducto

/*
Nombre: guardarProductosEnArchivo
Objetivo: Guardar en el archivo(ArchivoProd), los productos actuales que se encuentran en la lista(pProducto).
Parametros de Entrada(E) y Salida(S): (S)ArchivoProd- Archivo donde se guardaran los productos.
    (E)pProducto- contiene los productos a guardar.
*/
void guardarProductosEnArchivo( fArchivoProd *ArchivoProd, TpProducto pProducto){
//Variables
    TrProducto rProducto;
    TpProducto pPos;
//Inicio
    if(pProducto != NULL)
    {
        pPos = pProducto->pSig;

        while( pPos != pProducto)
        {

            strcpy(rProducto.cProducto , pPos->cProducto);
            rProducto.fCosto = pPos->fCosto;
            rProducto.fPrecio = pPos->fPrecio;
            strcpy( rProducto.cProveedor , pPos->cProveedor );
            rProducto.eExistencia = pPos->eExistencia;
            rProducto.eExistenciaMinima = pPos->eExistenciaMinima;
            rProducto.eCodigoProd = pPos->eCodigoProd;

            fwrite(& rProducto , sizeof( rProducto ), 1, *ArchivoProd); //Escribe en el archivo

            pPos = pPos->pSig;
        }

        strcpy(rProducto.cProducto , pPos->cProducto);
        rProducto.fCosto = pPos->fCosto;
        rProducto.fPrecio = pPos->fPrecio;
        strcpy( rProducto.cProveedor , pPos->cProveedor );
        rProducto.eExistencia = pPos->eExistencia;
        rProducto.eExistenciaMinima = pPos->eExistenciaMinima;
        rProducto.eCodigoProd = pPos->eCodigoProd;

        fwrite(& rProducto , sizeof( rProducto ), 1, *ArchivoProd); //Escribe en el archivo

        fclose(*ArchivoProd); //Cierra archivo
    }

}//FIN guardarProductosEnArchivo

