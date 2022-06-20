#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int main()
{
    int arrPaciente[100];
    FILE *archi = fopen("Masculinos", "ab");
    FILE *archi2= fopen("Femeninos","ab");
    carga(arrPaciente,100);

    return 0;
}

int carga(Paciente paciente[30], int validos)
{
    char continuar = 's';
    while(continuar == 's')
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
