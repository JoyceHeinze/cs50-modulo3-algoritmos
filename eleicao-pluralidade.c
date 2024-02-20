#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char nome[100];
    int votos;
} candidato;

int definirQuantEleitores(void);
int validarQuantCandidatos(int quantCandidatos);
void candidatosDisponiveis(int quantCandidatos, char *argv[], candidato candidatos[10]);
void realizarVotacao(int quantCandidatos, candidato candidatos[10], int quantEleitores);
void computarVoto(char *candidatoEscolhido, candidato candidatos[10], int quantCandidatos);
void resultadoFinalVotacao(candidato candidatos[10], int quantCandidatos);
void exibirResultadoVotacao(char maisVotado[100], int maxVotos, int contador);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");

    int quantCandidatos = argc - 1;
    int validacaoQuantCandidatos = validarQuantCandidatos(quantCandidatos);
    if (validacaoQuantCandidatos == 1)
    {
        return 1;
    }

    candidato candidatos[10];
    candidatosDisponiveis(quantCandidatos, argv, candidatos);

    int quantEleitores = definirQuantEleitores();

    realizarVotacao(quantCandidatos, candidatos, quantEleitores);
    resultadoFinalVotacao(candidatos, quantCandidatos);
}

int validarQuantCandidatos(int quantCandidatos)
{
    if (quantCandidatos > 9)
    {
        printf("\nVota��o anulada, pois o n�mero m�ximo de candidatos � 9.\n\n");
        return 1;
    }
    else if (quantCandidatos == 0)
    {
        printf("\nVota��o anulada, pois n�o h� candidatos inscritos.\n\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void candidatosDisponiveis(int quantCandidatos, char *argv[], candidato candidatos[10])
{

    for (int i = 0; i < quantCandidatos; i++)
    {
        strcpy(candidatos[i].nome, argv[i + 1]);
        candidatos[i].votos = 0;

        for (int j = 0; j < strlen(candidatos[i].nome); j++)
        {
            candidatos[i].nome[j] = toupper(candidatos[i].nome[j]);
        }
    }
}

int definirQuantEleitores(void)
{
    int quantEleitores;
    int numeroMinEleitores = 1;
    int numeroMaxEleitores = 100;
    int leituraValida;

    do
    {
        printf("Defina o n�mero de eleitores (entre %d e %d): ", numeroMinEleitores, numeroMaxEleitores);
        leituraValida = scanf("%d", &quantEleitores);
        
        if (leituraValida != 1 || quantEleitores < numeroMinEleitores || quantEleitores > numeroMaxEleitores)
        {
            printf("Entrada inv�lida. Por favor, digite um n�mero inteiro.\n");
            while (getchar() != '\n');
        }
    } while (quantEleitores < numeroMinEleitores || quantEleitores > numeroMaxEleitores);

    return quantEleitores;
}

void realizarVotacao(int quantCandidatos, candidato candidatos[10], int quantEleitores)
{
    for (int i = 0; i < quantEleitores; i++)
    {
        char candidatoEscolhido[100];
        printf("\nVoto %d: ", i + 1);
        scanf("%s", candidatoEscolhido);

        for (int j = 0; j < strlen(candidatoEscolhido); j++)
        {
            candidatoEscolhido[j] = toupper(candidatoEscolhido[j]);
        }
        computarVoto(candidatoEscolhido, candidatos, quantCandidatos);
    }
}

void computarVoto(char *candidatoEscolhido, candidato candidatos[10], int quantCandidatos)
{
    for (int i = 0; i < quantCandidatos; i++)
    {
        if (strcmp(candidatoEscolhido, candidatos[i].nome) == 0)
        {
            candidatos[i].votos++;
            return;
        }
    }
    printf("Voto inv�lido.\n");
}

void resultadoFinalVotacao(candidato candidatos[10], int quantCandidatos)
{
    char maisVotado[100];
    int maxVotos = 0;
    int contador = 0;

    for (int i = 0; i < quantCandidatos; i++)
    {
        if (candidatos[i].votos > maxVotos)
        {
            maxVotos = candidatos[i].votos;
            strcpy(maisVotado, candidatos[i].nome);
            contador = 0;
        }
        else if (candidatos[i].votos == maxVotos && candidatos[i].votos != 0)
        {
            strcat(maisVotado, ", ");
            strcat(maisVotado, candidatos[i].nome);
            contador++;
        }
    }

    exibirResultadoVotacao(maisVotado, maxVotos, contador);
}

void exibirResultadoVotacao(char maisVotado[100], int maxVotos, int contador)
{
    char *mensagem = contador >= 1 ? "Vencedores" : "Vencedor:";
    printf("\n\n%s %s (%d votos).\n\n", mensagem, maisVotado, maxVotos);
}
