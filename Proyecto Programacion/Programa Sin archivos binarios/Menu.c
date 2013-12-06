/*
    Programa- Menu.c
    Autor- Equipo SysteMy
    Fecha- 17/11/12
    Objetivo- Controlar las ventas, así como las compras de productos a proveedores, 
    para generar un inventario que ayude a manetener un control de la tienda.  
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Proveedores.h"
#include "Productos.h"
#include "Ventas.h"
#include "Compras.h"

//FUNCION PRINCIPAL
void main(){
//Variables
    fArchivoProd ArchivoProd; //Archivo producto
    fArchivoProve ArchivoProve; //Archivo proveedores
    fArchivoCompra ArchivoCompra; //Archivo Compras
    fArchivoVenta ArchivoVenta; //Archivo Ventas
   
    TpProveedor pProveedor = NULL; //pProveedor = pUltimo
    
    TpProducto pProducto = NULL; //pProducto = pUltimo
    
    TpVenta pPrimero = NULL; //Lista simple enlazada pPrimero(ventas)
    TpVenta pUltimo = NULL;  //Lista simple enlazada pUltimo(ventas)
    
    TpCompra pPrimeroC = NULL; //Lista doblemente enlazada pPrimero(compras)
    TpCompra pUltimoC = NULL; //Lista doblemente enlazada pultimo(compras)
    
    int eOpc;  

//Inicio
    crearArchivoProducto( &ArchivoProd , &pProducto); 
    crearArchivoProveedor( &ArchivoProve, &pProveedor);
    crearArchivoCompras( &ArchivoCompra, &pPrimeroC , &pUltimoC);
    crearArchivoVentas( &ArchivoVenta, &pPrimero , &pUltimo);
            
    do{
        printf("|---------\nLa Nueva Xicotencatl\n[SISATC](Sistema de Administracion de Tiendas y Comercios)\n---------|\n");
        printf("1- Ventas\n");
        printf("2- Compras\n");
        printf("3- Productos\n");
        printf("4- Proveedores\n");
        printf("5- Apagar Sistema\n");
        printf("\n\t\t\t\t\t\tSeleccione una opcion: ");
        scanf("%i",&eOpc);
        fflush(stdin);
        switch(eOpc){
            case 1: system("cls");
                    ventas(&pPrimero , &pUltimo , &pProducto);
            break;
            case 2: system("cls"); 
                    compras(&pPrimeroC , &pUltimoC , &pProducto);
            break;
            case 3: system("cls");
                    productos(&pProducto);  
            break;
            case 4: system("cls");
                    proveedores(&pProveedor);
            break;
            case 5: guardarComprasEnArchivo( &ArchivoCompra , pPrimeroC);
                    guardarVentasEnArchivo( &ArchivoVenta , pPrimero);
                    guardarProductosEnArchivo( &ArchivoProd , pProducto); 
                    guardarProveedoresEnArchivo( &ArchivoProve, pProveedor);
                     
                    LiberarMemoriaProveedor(pProveedor);    
                    LiberarMemoriaProducto(pProducto);
                    liberarMemoriaVenta(pPrimero);
                    liberarMemoriaCompra(pPrimeroC);
                    
                    printf("Sistema Apagado\nDatos Guardados Correctamente\n");
            break;
            default: printf("Opcion Incorrecta\n");    
        }
    }while(eOpc != 5);
    getch();
}//FIN MAIN
