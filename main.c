#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

typedef struct {
int dni;
char nombre [30];
char sexo; // ‘m’ o ‘f’
int edad;
int cantidadDeAtenciones;
char ultimaPatologia [50]; //Gripe A, Gripe B, Covid, Fractura, etc
} Paciente;

int carga(Paciente paciente[30], int validos);
Paciente cargaIndividual();
int validacionSexo(char sexo);
void MuestraArreglo(Paciente paciente[30], int validos);
void muestraArregloIndividual(Paciente paciente);
void pasarArchivo(Paciente paciente[30], int validos);
void busquedaPaciente();
int buscarArchivo(int dni, char NombreArchivo);
void muestraArchivoMyF();
void Mostrar(FILE*ARCH, char ultimaPatologia[]);
void mostrar(Paciente aux);
int cantidadPacientesPatologia(Paciente paci[], int validos, char patologia);
float SumarEdadPatologia(Paciente paci[], int validos, char patologia);


int main()
{
    Paciente arrPaciente[30];
    FILE *archi = fopen("Masculinos","ab");
    FILE *archi2 = fopen("Femeninos","ab");
    carga(arrPaciente,30);
    fflush(stdin);

    MuestraArreglo(arrPaciente,30);

    return 0;
}

int carga(Paciente paciente[30], int validos)
{
    char continuar ='s';
    while(continuar =='s')
    {
        paciente[validos] = cargaIndividual();
        printf("Desea continuar? (S|N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        validos++;
        system("cls");
    }

    return validos;
}

Paciente cargaIndividual()
{
    int flag=0;
    Paciente paciente;
    printf("Ingrese el nombre del paciente: ");
    fflush(stdin);
    gets(paciente.nombre);
    printf("Ingrese el DNI: ");
    scanf("%i", &paciente.dni);
    printf("Ingrese la edad: ");
    scanf("%i", &paciente.edad);
    //VALIDAR
    do
    {
      printf("Ingrese el sexo(m|f): ");
      fflush(stdin);
      scanf("%c",&paciente.sexo);
      flag=validacionSexo(paciente.sexo);
    }
    while(flag==0);
    printf("Ingrese la cantidad de atenciones: ");
    scanf("%i", &paciente.cantidadDeAtenciones);
    printf("Ingrese la ultima patologia (fiebre - gripe - fractura - covid - ninguna) : ");
    fflush(stdin);
    gets(paciente.ultimaPatologia);

    return paciente;
}

int validacionSexo(char sexo)
{
    int flag=0;

    if(sexo=='m' || sexo=='f')
    {
        flag=1;
    }

    return flag;
}

//EJERCICIO 2

void MuestraArreglo(Paciente paciente[30], int validos)
{
    int i;

    for(i=0;i<validos;i++)
    {
        muestraArregloIndividual(paciente[i]);
    }

}

void muestraArregloIndividual(Paciente paciente)
{
    printf("| Nombre: %-60s  | \n", paciente.nombre);
    printf("| Dni:  %-63i | \n", paciente.dni);
    printf("|Edad: %-62i | \n", paciente.edad);

    if(paciente.sexo =='m')
    {
        printf("| Sexo: Masculino");
    }
    else
    {
        printf("| Sexo: Femenino");
    }

    printf("| Cantidad de atenciones: %-44i | \n",paciente.cantidadDeAtenciones);
    printf("| Ultima patologia: %-50s | \n\n", paciente.ultimaPatologia);
}


//EJERCICIO 3

void pasarArchivo(Paciente paciente[30], int validos)
{
    int i;
    FILE *archivoMasculino=fopen("Masculinos", "ab");
    FILE *archivoFemenino=fopen("Femeninos", "ab");

    if(archivoFemenino && archivoMasculino)
    {
        for(i=0; i<validos;i++)
        {
            if(paciente[i].sexo=='m')
            {
                fwrite(&paciente,sizeof(Paciente),1,archivoMasculino);
            }
            else
            {
                fwrite(&paciente,sizeof(Paciente),1,archivoFemenino);
            }
        }
        fclose(archivoFemenino);
        fclose(archivoMasculino);
    }
}

//EJERCICIO 4

void busquedaPaciente()
{
    int dni;
    int flagM=0;
    int flagF=0;
    printf("Ingrese el dni de la persona que desea buscar: ");
    scanf("%i", &dni);
    flagM= buscarArchivo(dni,"Masculino");
    if(flagM==1)
    {
        printf("\nEl usuario existe y tiene por lo menos 5 atenciones.\n\n");

    }
    else if(flagM==0)
    {
      flagM=buscarArchivo(dni, "Femenino");
      if(flagF==1)
      {
          printf("\nEl usuario no existe o no tiene por lo menos 5 atenciones.\n\n");
      }
    }
}

int buscarArchivo(int dni, char NombreArchivo)
{
    Paciente aux;
    int flag=0;
    FILE *archivo=fopen(NombreArchivo, "rb");
    if(archivo!=NULL)
    {
        while(fread(&aux,sizeof(Paciente),1,archivo>0 && flag==0))
        {
            if(aux.dni==dni && aux.cantidadDeAtenciones>=5)
            {
                flag=1;
            }
        }
        fclose(archivo);
    }

    return flag;
}

//EJERCICIO 5

void muestraArchivoMyF()
{
    Paciente aux;
    char ultimaPatologia[50];

    printf("Ingrese la ultima patologia de los pacientes que desea mostrar: ");
    fflush(stdin);
    gets(ultimaPatologia);

    FILE *archivoM = fopen("Masculinos", "rb");
    FILE *archivoF= fopen("Femeninos", "rb");

    if(archivoM !=NULL && archivoF!=NULL)
    {
        Mostrar(archivoM, ultimaPatologia);
        Mostrar(archivoF,ultimaPatologia);

        fcloseall;
    }
}

void Mostrar(FILE * ARCH, char ultimaPatologia[])
{
    Paciente aux;

    while(fread(&aux,sizeof(Paciente),1,ARCH>0))
    {
        if(strcmp(aux.ultimaPatologia,ultimaPatologia)==0)
        {
            mostrar(aux);
        }
    }
}

void mostrar(Paciente aux)
{
    printf("| Nombre: %-60s  | \n",aux.nombre);
    printf("| DNI: %-63i |\n",aux.dni);
    printf("| Edad: %-62i |\n",aux.edad);
    if(aux.sexo=='m')
    {
        printf("| Sexo: Masculino");
    }
    else
    {
        printf("| Sexo: Femenino");
    }

    printf("| Cantidad de atenciones: %-44i | \n", aux.cantidadDeAtenciones);
    printf("| Ultima patologia: %-50s | \n", aux.ultimaPatologia);
}


//EJERCICIO 6

int cantidadPacientesPatologia(Paciente paci[], int validos, char patologia)
{
    int i=0;
    while(i<validos)
    {
        if(strcmp(patologia,paci[i].ultimaPatologia)==0)
        {
            i++;
        }
    }
    return i;
}

float SumarEdadPatologia(Paciente paci[], int validos, char patologia)
{
    int i;
    int suma =0;

    for(i=0; i<validos;i++)
    {
        if(strcmp(patologia,paci[i].ultimaPatologia)==0)
        {
            suma = suma + paci[i].edad;
        }
    }
    return suma;
}


