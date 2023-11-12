#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define NUM_DISCIPLINAS 5

// Disciplinas pré-registradas
char disciplinas[NUM_DISCIPLINAS][100] = {
    "Matematica",
    "Portugues",
    "Geografia",
    "Historia",
    "Ciencias"};

// Estrutura para representar as informações de um aluno
typedef struct
{
    char nome[100];
    int matricula;
    float notas[4][NUM_DISCIPLINAS];
} Aluno;

// Função para adicionar um novo aluno
void adicionarAluno(Aluno *alunos, int *numAlunos)
{
    if (*numAlunos < MAX_ALUNOS)
    {
        Aluno novoAluno;
        printf("\nNome completo do aluno: ");
        scanf(" %[^\n]s", novoAluno.nome);
        printf("Matricula: ");
        scanf("%d", &novoAluno.matricula);
        for (int i = 0; i < NUM_DISCIPLINAS; i++)
        {
            printf("%s:\n", disciplinas[i]);
            for (int bimestre = 0; bimestre < 4; bimestre++)
            {
                printf("\nBimestre %d - Nota: ", bimestre + 1);
                scanf("%f", &novoAluno.notas[bimestre][i]);
            }
        }
        alunos[(*numAlunos)++] = novoAluno;
        printf("Aluno adicionado com sucesso!\n");
    }
    else
    {
        printf("O limite de alunos foi atingido.\n");
    }
}

// Função para listar todos os alunos
void listarAlunos(Aluno *alunos, int numAlunos)
{
    if (numAlunos == 0)
    {
        printf("\nNENHUM ALUNO CADASTRADO.\n");
    }
    else
    {
        printf("\nLISTA DE ALUNOS:\n");
        for (int i = 0; i < numAlunos; i++)
        {
            printf("Nome: %s \nMatricula: %d\n", alunos[i].nome, alunos[i].matricula);
        }
    }
}

// Função para imprimir o boletim de um aluno
void imprimirBoletim(Aluno *aluno)
{
    printf("\nBoletim de %s (Matrícula: %d):\n", aluno->nome, aluno->matricula);

    // Impressão dos títulos das disciplinas com os bimestres, média final e status
    printf("\nDisciplinas\t| Bimestre 1\tBimestre 2\tBimestre 3\tBimestre 4\tMédia Final\t[Status]\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < NUM_DISCIPLINAS; i++)
    {
        printf("%s\t| ", disciplinas[i]); // Impressão do nome da disciplina

        double somaNotas = 0.0;
        // Impressão das notas para cada bimestre e cálculo da média final
        for (int bimestre = 0; bimestre < 4; bimestre++)
        {
            printf("%.2f\t\t", aluno->notas[bimestre][i]);
            somaNotas += aluno->notas[bimestre][i];
        }

        double mediaFinal = somaNotas / 4; // Calculando a média final

        // Exibição da média final e status (aprovado/reprovado)
        if (mediaFinal >= 6.0)
        {
            printf("%.2f \t\t[APROVADO]\n", mediaFinal);
        }
        else
        {
            printf("%.2f \t\t[REPROVADO]\n", mediaFinal);
        }
    }
}

// Função para salvar os dados dos alunos em um arquivo CSV
void salvarDados(Aluno *alunos, int numAlunos)
{
    FILE *arquivo = fopen("dados_alunos.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Escrevendo o cabeçalho do arquivo
    fprintf(arquivo, "Nome,Matricula");
    for (int i = 0; i < NUM_DISCIPLINAS; i++)
    {
        for (int bimestre = 1; bimestre <= 4; bimestre++)
        {
            fprintf(arquivo, ",%s B%d", disciplinas[i], bimestre);
        }
    }
    fprintf(arquivo, "\n");

    // Escrevendo os dados dos alunos
    for (int i = 0; i < numAlunos; i++)
    {
        fprintf(arquivo, "%s,%d", alunos[i].nome, alunos[i].matricula);
        for (int bimestre = 0; bimestre < 4; bimestre++)
        {
            for (int j = 0; j < NUM_DISCIPLINAS; j++)
            {
                fprintf(arquivo, ",%.2f", alunos[i].notas[bimestre][j]);
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
    printf("Dados dos alunos foram salvos com sucesso.\n");
}

int main()
{
    Aluno alunos[MAX_ALUNOS];
    int numAlunos = 0;
    int opcao;

    // salvardados dos alunos do arquivo (se existir)
    salvarDados(alunos, numAlunos);

    while (1)
    {
        printf("\nSistema de Gestao Escolar\n");
        printf("1. Adicionar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Imprimir Boletim\n");
        printf("4. Salvar Dados\n");
        printf("5. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            adicionarAluno(alunos, &numAlunos);
            break;
        case 2:
            listarAlunos(alunos, numAlunos);
            break;
        case 3:
            if (numAlunos > 0)
            {
                listarAlunos(alunos, numAlunos);
                int alunoIndex;
                printf("Selecione o aluno (1-%d): ", numAlunos);
                scanf("%d", &alunoIndex);
                if (alunoIndex >= 1 && alunoIndex <= numAlunos)
                {
                    imprimirBoletim(&alunos[alunoIndex - 1]);
                }
                else
                {
                    printf("Opcao invalida.\n");
                }
            }
            else
            {
                printf("Nenhum aluno cadastrado.\n");
            }
            break;
        case 4:
            salvarDados(alunos, numAlunos);
            break;
        case 5:
            printf("Saindo do programa.\n");
            exit(0);
        default:
            printf("Opção invalida. Tente novamente.\n");
        }
    }

    return 0;
}
