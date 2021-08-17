#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define CIMA_W 87
#define CIMA_W_M 119

#define BAIXO_S 83
#define BAIXO_S_M 115

#define DIREITA_D 68
#define DIREITA_D_M 100

#define ESQUERDA_A 65
#define ESQUERDA_A_M 97

#define PREMIO 5
#define VALOR 5
#define DATA 10
#define TAM_CLI 100
#define TAM_L 10
#define TAM_C 10
#define L_NUM 2
#define C_NUM 100
#define TAM_RIFA 100
#define G_C 3
#define L_CLI 4

void TelaMenu();
void Navegacao();
void TelaCompra();
void Comprando();
void TelaCadastroCliente();
int ProcessaLogin(char cpf[], char senha[]);
void Passaid(char cpf[]);
void TelaLoginCliente();
void LoginInvalido();
void LoginAdmInvalido();
void CamposVaziosNome();
void CamposVaziosRua();
void CamposVaziosSenha();
void CadastroConfirmado();
void CadastroCancelado();
void ComprarReservar();
void SorteiaNumero(int opcao1, int opcao2);
void SorteiaGanhador();
void TotalAPagar(int total);
void JaComprado();
void JaReservado();
int DesejaComprar(int coluna);
void TelaAdmin();
void EditarRifa();
void EditaPremio(int qualp);
void TelaConfirmaPremio(char produto[], int qual);
void EditaData();
void TelaConfirmaData(char dia[]);
void TelaConfirmarValor(float preco);
void EditaValor();
void Sorteio(int qtd, int comprar, int reservar);
int validaADM(char nome[], char senha[]);
void TelaLoginAdmin();
void TelaRifa();
void EscolherPremio();
void ListarCompradores();
void ordena();
void CamposCheiosCpf();
void CamposVaziosCpf();
void ValidaLimite();
void MaximoComprado();
void PodeComprarApenas(int qtd);
int VerificaLimite(int qtd);
void TodasGlobaisZeradas();
void GanhadoresJaSorteados();
void ListarGanhadores();
void VerificaDados();
void CPFjaCadastrado();
void DesejaSair();

int sorteados[G_C];
int matrizrifa[TAM_L][TAM_C];
int matriznumeros[L_NUM][C_NUM];
int numerosreservados[L_NUM][C_NUM];
int idlogado = 0;
int ID = 0;
int compra = 0;
int ordenanome = 1;
char data[DATA];
float valor = 0.0;
char premio1[PREMIO];
char premio2[PREMIO];
char premio3[PREMIO];
char ganhador1[20];
char ganhador2[20];
char ganhador3[20];

struct Usuario{
	int sorteado[3];
	int id;
	char nome[24];
	char cpf[50];
	char senha[50];
};

struct Usuario adm;
struct Usuario pessoa;
struct Usuario cliente_logado[TAM_CLI];
struct Usuario cliente_nome[TAM_CLI];

void gotoxy(int x, int y){
	
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TelaMenu(){
	int opcao = 0;
	
	system("cls");                                                       
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                                       %c",179,179);
	printf("\n%c                          %c%c%c%c%c%c%c%c%c Garagem 79 %c%c%c%c%c%c%c%c%c                        %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                       RIFA-Chevete                      %c",179,179,179);
	printf("\n%c  1-Cadastrar-se      %c                       %c%c%c%c%c%c%c%c%c%c%c%c                      %c",179,179,196,196,196,196,196,196,196,196,196,196,196,196,179);
	printf("\n%c  2-Login Cliente     %c   Pr%cmio1:         %cPr%cmio2:        %cPr%cmio3:           %c",179,179,136,179,136,179,136,179);
	printf("\n%c  3-Login admin       %c   Disponiveis||    %cReservados()    %cComprados[]        %c",179,179,179,179,179);
	printf("\n%c                      %c   Valor:$          %cSorteio:        %c                   %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,135,198,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);	
	TelaRifa();
	
	gotoxy(34, 10);
	printf("%.2f", valor);
	
	gotoxy(35, 8);
	puts(premio1);
	
	gotoxy(53, 8);
	puts(premio2);
	
	gotoxy(70, 8);
	puts(premio3);
	
	gotoxy(53, 10);
	puts(data);
		
	do{
		gotoxy(20,11);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 27) && (opcao < 49) || (opcao > 51));
	if(opcao == 49){
		TelaCadastroCliente();
	}
	if(opcao == 50){
		TelaLoginCliente();
	}
	if(opcao == 51){
		TelaLoginAdmin();
	}
	if(opcao == 27){
		DesejaSair();
	}
}

void Navegacao(){
	int opcao, x, y, i, j, linha, col, comprado, coluna, identifica, resultado, valida;
	x = 29;
	y = 12;
	i = 0;
	j = 1;
	linha = 0;
	col = 0;
	coluna = 0;
	comprado = 1;
	do{
		Comprando();
		do{
			gotoxy(x, y);
			fflush(stdin);
			opcao = getch();
			if((opcao == CIMA_W) || (opcao == CIMA_W_M)){
				y--;
				i = i-10;
				linha--;
				comprado = comprado-10;
				if(y < 12){
					linha++;
					y++;
					i = i+10;
					comprado = 0;
				}
			}
			if((opcao == BAIXO_S) || (opcao == BAIXO_S_M)){
				y++;
				linha++;
				i = i+10;
				comprado = comprado+10;
				if(y > 21){
					linha--;
					y--;
					i = i-10;
					comprado = comprado-10;
				}
			}
			if((opcao == DIREITA_D) || (opcao == DIREITA_D_M)){
				x = x+5;
				j++;
				col++;
				comprado = comprado+1;
				if(x > 75){
					x = x-5;
					j--;
					col--;
					comprado = comprado-1;
				}
			}
			if((opcao == ESQUERDA_A) || (opcao == ESQUERDA_A_M)){
				x = x-5;
				j--;
				col--;
				comprado = comprado-1;
				if(x < 29){
					comprado = comprado+1;
					x = x+5;
					j++;
					col++;
				}
			}
		}while((opcao != 114) && (opcao != 99) && (opcao != 27) && (opcao != 120));	
		coluna = i+j;
		if(opcao == 114){
			if((matrizrifa[linha][col] == 2) && (ID == numerosreservados[1][coluna])){
				resultado = DesejaComprar(coluna);
				if(resultado == 1){
					matrizrifa[linha][col] = 1;					
					matriznumeros[0][coluna] = compra;
					matriznumeros[1][coluna] = ID;
				}
			}else if(matrizrifa[linha][col] == 2){
				JaReservado();
			}else if(matrizrifa[linha][col] == 1){
				JaComprado();
			}else{
				ValidaLimite();
				matrizrifa[linha][col] = 2;
				numerosreservados[0][coluna] = comprado;	
				numerosreservados[1][coluna] = ID;			
			}	
		}
		if(opcao == 99){
			if((matrizrifa[linha][col] == 2) && (ID == numerosreservados[1][coluna])){
				resultado = DesejaComprar(coluna);
				if(resultado == 1){
					matrizrifa[linha][col] = 1;
					matriznumeros[0][coluna] = comprado;
					matriznumeros[1][coluna] = ID;
				}
			}else if(matrizrifa[linha][col] == 2){
				JaReservado();
			}else if(matrizrifa[linha][col] == 1){
				JaComprado();
			}else{
				ValidaLimite();
				matriznumeros[0][coluna] = comprado;
				matriznumeros[1][coluna] = ID;
				matrizrifa[linha][col] = 1;
			}
		}
		if(opcao == 120){
			if((matrizrifa[linha][col] == 2) && (ID == numerosreservados[1][coluna])){
				resultado = DesejaCancelar(coluna);
				if(resultado == 1){
					matrizrifa[linha][col] = 0;
					numerosreservados[0][coluna] = -2;
					numerosreservados[1][coluna] = 0;
				}
			}else if(matrizrifa[linha][col] == 2){
				JaReservado();
			}else if(matrizrifa[linha][col] == 1){
				JaComprado();
			}
		}				
	}while(opcao != 27);
	
	TelaCompra();
}

void DesejaSair(){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                      %c%c%c%c%c%c%c%c%c FINALIZA PROGRAMA %c%c%c%c%c%c%c%c%c                     %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          Deseja finalizar o programa ?                         %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1- Confirmar | 2- Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	do{
		gotoxy(54, 10);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50));
	if(opcao == 49){
		system("cls");
		system("pause");
		system("pause");
	}else{
		TelaMenu();
	}
}

void TelaCompra(){
	int opcao, i;
	int id = 0;
	system("cls");	                                                   
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                                ID:    %c",179,179);
	printf("\n%c                          %c%c%c%c%c%c%c%c%c Garagem 79 %c%c%c%c%c%c%c%c%c                        %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                       RIFA-Chevete                      %c",179,179,179);
	printf("\n%c 1-Gerar um n%cmero    %c                       %c%c%c%c%c%c%c%c%c%c%c%c                      %c",179,163,179,196,196,196,196,196,196,196,196,196,196,196,196,179);
	printf("\n%c 2-Escolher n%cmeros   %c   Pr%cmio1:         %cPr%cmio2:        %cPr%cmio3:           %c",179,163,179,136,179,136,179,136,179);
	printf("\n%c Escolha uma op%c%co:   %c   Disponiveis||    %cReservados()    %cComprados[]        %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c   Valor:$          %cSorteio:        %c                   %c",179,179,179,179,179);
	printf("\n%c                      %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c                      %c    C: Comprar    R: Reservar    X: Cancelar reserva     %c",179,179,179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);	
	
	gotoxy(34, 10);
	printf("%.2f", valor);
	
	gotoxy(35, 8);
	puts(premio1);
	
	gotoxy(53, 8);
	puts(premio2);
	
	gotoxy(70, 8);
	puts(premio3);
	
	gotoxy(53, 10);
	puts(data);
		
	TelaRifa();	
	gotoxy(77, 2);
	printf("%i", ID);
	do{	
		gotoxy(20, 9);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 27) && (opcao < 49) || (opcao > 50));
	if(opcao == 27){
		TelaMenu();
	}else if(opcao == 49){
		ComprarReservar();
	}else if(opcao == 50){
		Navegacao();
	}
}

void Comprando(){
	int opcao, i;
	int id = 0;
	system("cls");	                                                   
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                                ID:    %c",179,179);
	printf("\n%c                          %c%c%c%c%c%c%c%c%c Garagem 79 %c%c%c%c%c%c%c%c%c                        %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                       RIFA-Chevete                      %c",179,179,179);
	printf("\n%c 1-Gerar um n%cmero    %c                       %c%c%c%c%c%c%c%c%c%c%c%c                      %c",179,163,179,196,196,196,196,196,196,196,196,196,196,196,196,179);
	printf("\n%c 2-Escolher n%cmeros   %c   Pr%cmio1:         %cPr%cmio2:        %cPr%cmio3:           %c",179,163,179,136,179,136,179,136,179);
	printf("\n%c Escolha uma op%c%co:   %c   Disponiveis||    %cReservados()    %cComprados[]        %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c   Valor:$          %cSorteio:        %c                   %c",179,179,179,179,179);
	printf("\n%c                      %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c                                                     %c %c",179,179,179,179,179);
	printf("\n%c                      %c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c                      %c    C: Comprar    R: Reservar    X: Cancelar reserva     %c",179,179,179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);	
	
	gotoxy(34, 10);
	printf("%.2f", valor);
	
	gotoxy(35, 8);
	puts(premio1);
	
	gotoxy(53, 8);
	puts(premio2);
	
	gotoxy(70, 8);
	puts(premio3);
	
	gotoxy(53, 10);
	puts(data);
		
	TelaRifa();	
	
	gotoxy(77, 2);
	printf("%i", ID);	
}

void TelaCadastroCliente(){
	int opcao, x, y, i, cont,letra, voltar, nome, rua;
	int valida = -1;
	char palavra[24];
	voltar = 0;
	nome = 0; 
	rua = 0;
	
	strcpy(pessoa.nome, "");
   	strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c Cadastro de Cliente %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c  Primeiro nome:                   CPF:                 Telefone:               %c",179,179,179);
	printf("\n%c  Endere%co:                        Senha:                                       %c",179,135,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1-Confirmar | 2- Cancelar:                            %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	x=17;
	y=7;
	cont = 0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 93;
			}else if(letra == 8){
				letra = 91;
			}else if(letra == 32){
				letra = 95;
			}	
		}while((letra < 65) || (letra > 122));
			if(letra == 93){
				letra = 13;
			}else if(letra == 91){
				letra = 8;				
			}else if(letra == 95){
				letra = 32;
			}
		nome++;
		printf("%c", letra);
		pessoa.nome[cont] = letra;
		cont++;
		if(cont > 18){
			letra = 13;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 17){
				x = 17;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}
			nome--;
			if(nome < 0){
				nome = 0;
			}	
		}
	}while(letra != 13);

	x=40;
	y=7;
	cont=0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 58;
			}else if(letra == 8){
				letra = 59;
			}
				
		}while((letra < 45) || (letra > 60));
			if(letra == 58){
				letra = 13;
			}else if(letra == 59){
				letra = 8;				
			}
			if(cont == 14 && letra != 13 && letra != 8){
				do{
					gotoxy(x, y);
					fflush(stdin);
					letra = getch();
				}while(letra != 13 && letra != 8);
			}
		printf("%c", letra);
		if(letra != 13 && letra != 8){
			pessoa.cpf[cont] = letra;
			cont++;
		}
				
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 40){
				x = 40;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			cont++;
			if(cont < 0){
				cont = 0;
			}	
		}

	}while(letra != 13);
	
	x=66;
	y=7;
	cont = 0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 47;
			}else if(letra == 8){
				letra = 58;
			}		
		}while((letra < 40) || (letra > 59));
			if(letra == 47){
				letra = 13;
			}else if(letra == 58){
				letra = 8;				
			}
		printf("%c", letra);
		palavra[cont] = letra;
		cont++;
		if(cont > 13){
			letra = 13;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 66){
				x = 66;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}	
		}
	}while(letra != 13);
		
	x=12;
	y=8;
	cont = 0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 93;
			}else if(letra == 8){
				letra = 91;
			}else if(letra == 32){
				letra = 95;
			}	
		}while((letra < 65) || (letra > 122));
			if(letra == 93){
				letra = 13;
			}else if(letra == 91){
				letra = 8;				
			}else if(letra == 95){
				letra = 32;
			}
		rua++;
		printf("%c", letra);
		palavra[cont] = letra;
		cont++;
		if(cont > 20){
			letra = 13;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 12){
				x = 12;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}
			rua--;
			if(rua < 0){
				rua = 0;
			}	
		}
	}while(letra != 13);

	x=42;
	y=8;
	cont=0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 93;
			}else if(letra == 8){
				letra = 91;
			}else if(letra == 32){
				letra = 95;
			}	
		}while((letra < 45) || (letra > 122));
			if(letra == 93){
				letra = 13;
			}else if(letra == 91){
				letra = 8;				
			}else if(letra == 95){
				letra = 32;
			}
		printf("%c", letra);
		if(cont > 14){
			letra = 13;
		}
		if(letra != 13){
			pessoa.senha[cont] = letra;
			cont++;
		}
		if(cont > 20){
			letra = 13;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 42){
				x = 42;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}	
		}
	}while(letra != 13);
		
	do{
		gotoxy(53, 13);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50));
					
	if(opcao == 49){
		if(nome >= 3){
			valida = -1;
		}else{
			valida = 0;
		}
		if(valida == 0){
			CamposVaziosNome();
		}
		if(rua > 5){
			valida = -1;
		}else{
			valida = 0;
		}
		if(strlen(pessoa.cpf) < 14){
			CamposVaziosCpf();
		}else if(strlen(pessoa.cpf) > 14){
			CamposCheiosCpf();
		}
		if(strlen(pessoa.senha) < 5){
			CamposVaziosSenha();
		}
		if(valida == 0){
			CamposVaziosRua();
		}
		CadastroConfirmado();	
	}else{
		strcpy(pessoa.nome, "");
    	strcpy(pessoa.cpf, "");
		strcpy(pessoa.senha, "");
		CadastroCancelado();	
	}	
}

int ProcessaLogin(char cpf[], char senha[]){
	int confirmado = -1;
	int i, j;
	for(i = 0; i < TAM_CLI; i=i+2){
		confirmado = strcmp(cliente_logado[i].cpf, cpf);
		if(confirmado == 0){
			confirmado = -1;
			confirmado = strcmp(cliente_logado[i+1].senha, senha);			
			if(confirmado == 0){
				confirmado = 1;
			}
			break;
		}
	}		
	return confirmado;			
}

void Passaid(char cpf[]){
	int i, id, verifica;
	verifica = 1;
	id = 0;
	for(i = 0; i < TAM_CLI; i++){
		verifica = strcmp(cliente_logado[i].cpf, cpf);
		if(verifica == 0){
			ID = cliente_logado[i].id;
			break;
		}
	}
}

void TelaLoginCliente(){
	char cpf[15];
	char senha[15];
	int opcao, x, y;
	int i = 0;
	int confirmado = 0;
	int id = 0;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Login Cliente %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                         CPF:                      Senha:                       %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1- Confirmar | 2- Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
				
	gotoxy(30, 8);
	gets(cpf);
	
	gotoxy(58, 8);
	gets(senha);
	
	do{
		gotoxy(54, 10);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50));

	if(opcao == 49){
		confirmado = ProcessaLogin(cpf, senha);
		Passaid(cpf);
		if(confirmado == 1){	
			TelaCompra();
		}else{
			LoginInvalido();
		}	
	}else{
		TelaMenu();
	}
		
}

void LoginInvalido(){

	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR LOGIN %c%c%c%c%c%c%c%c%c                  %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               Dados inv%cliados !!!                             %c",179,160,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	sleep(2);
	TelaLoginCliente();
}

void LoginAdmInvalido(){

	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR LOGIN %c%c%c%c%c%c%c%c%c                  %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               Dados inv%cliados !!!                             %c",179,160,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	sleep(2);
	TelaLoginAdmin();
}

void CamposVaziosNome(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                    Nome muito curto, preencha novamente !!!                    %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(2);
	TelaCadastroCliente();
}

void CamposVaziosRua(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                   Endere%co muito curto, preencha novamente !!!                 %c",179,135,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(2);
	TelaCadastroCliente();
}

void CamposCheiosCpf(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                      CPF muito longo, preencha novamente !!!                   %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(2);
	TelaCadastroCliente();
}

void CamposVaziosCpf(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                      CPF muito curto, preencha novamente !!!                   %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(2);
	TelaCadastroCliente();
}

void CamposVaziosSenha(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                     Senha muito curta, preencha novamente !!!                  %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(2);
	TelaCadastroCliente();
}

void CPFjaCadastrado(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                   %c%c%c%c%c%c%c%c%c ERRO AO EFETUAR CADASTRO %c%c%c%c%c%c%c%c%c                 %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                         CPF digitado j%c est%c cadastrado                        %c",179,160,160,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	
	sleep(3);
	TelaCadastroCliente();
}

void VerificaDados(){
	int i;
	
	for(i = 0; i<TAM_CLI; i++){
		if(strcmp(pessoa.cpf, cliente_logado[i].cpf) == 0){
			CPFjaCadastrado();
		}	
	}
}

void CadastroConfirmado(){
		
	VerificaDados();	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c Cadastro de Cliente %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                       CADASTRO LEALIZADO COM SUCESSO !!!                       %c",179,179,179);
	printf("\n%c                           Agora, realize seu login                             %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	if(cliente_logado[idlogado].id == 0){
		cliente_logado[idlogado].id = ordenanome;
		strcpy(cliente_nome[ordenanome].nome, pessoa.nome);
		strcpy(cliente_logado[idlogado].cpf, pessoa.cpf);
		strcpy(cliente_logado[idlogado+1].senha, pessoa.senha);
	}
	
	idlogado = idlogado+2;
	ordenanome++;
	sleep(3);
	TelaMenu();
		
}

void CadastroCancelado(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c Cadastro de Cliente %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               CADASTRO CANCELADO                               %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	strcpy(pessoa.nome, "");
    strcpy(pessoa.cpf, "");
	strcpy(pessoa.senha, "");
	sleep(1);
	TelaMenu();	
}

void MaximoComprado(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c ERRO AO GERAR N%cMEROS %c%c%c%c%c%c%c%c%c                  %c",179,219,219,219,219,219,219,219,219,219,233,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                        LIMITE DE 10 N%cMEROS EXCEDIDO !!!                       %c",179,233,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	sleep(2);
	TelaCompra();
}

void PodeComprarApenas(int qtd){
	int total = 0;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c ERRO AO GERAR N%cMEROS %c%c%c%c%c%c%c%c%c                  %c",179,219,219,219,219,219,219,219,219,219,233,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                        LIMITE DE 10 N%cMEROS EXCEDIDO !!!                       %c",179,233,179,179);
	printf("\n%c                        Voc%c pode gerar apenas                                  %c",179,136,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	total = 10-qtd;
	gotoxy(48, 9);
	if(total > 1){
		printf("%i n%cmeros", total, 163);
	}else{
		printf("%i n%cmero", total, 163);
	}
		
	sleep(4);
	ComprarReservar();
}

void ValidaLimite(){
	int i, comprados;
	comprados = 0;
	
	for(i = 0; i < C_NUM; i++){
		
		if(matriznumeros[1][i] == ID || numerosreservados[1][i] == ID){
			comprados++;
			if(comprados >= 10){
				MaximoComprado();
			}
		}
	}
}

int VerificaLimite(int qtd){
	int i, comprados, total, valida;
	comprados = 0;
	valida = 1;
	
	for(i = 0; i < C_NUM; i++){
		if(matriznumeros[1][i] == ID || numerosreservados[1][i] == ID){
			comprados++;
		}
	}
	total = comprados+qtd;
	if(total > 10){
		PodeComprarApenas(comprados);
	}else{
		valida = 0;
	}
	return valida;
}

void ComprarReservar(){
	int opcao;
	int comprar, reservar;
	comprar = 0;
	reservar = 0;
	
	
	ValidaLimite();
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                       %c%c%c%c%c%c%c%c%c COMPRA E RESERVA %c%c%c%c%c%c%c%c%c                     %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                            1- Comprar | 2- Reservar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
		
	do{
		gotoxy(54, 8);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50) && (opcao != 27));
	
	if(opcao == 27){
		TelaCompra();
	}
	if(opcao == 49){
		comprar = 1;
	}else{
		reservar = 2;
	}
	SorteiaNumero(comprar, reservar);
}

void SorteiaNumero(int opcao1, int opcao2){
	int comprar, reservar, valida;
	int qtd = 0;
	comprar = opcao1;
	reservar = opcao2;

	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c  Sortear N%cmeros  %c%c%c%c%c%c%c%c%c                   %c",179,219,219,219,219,219,219,219,219,219,163,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                            Quantos n%cmeros deseja ? [  ]                       %c",179,163,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	do{	
		gotoxy(55, 7);
		fflush(stdin);
		scanf("%i", &qtd);
		valida = VerificaLimite(qtd);
		
	}while(qtd > 10 && valida != 0);
	if(comprar == 1){
		TotalAPagar(qtd);
	}
	Sorteio(qtd, comprar, reservar);
}

void SorteiaGanhador(){
	int i, j, x, y, opcao, libera;
	int sorteado;
	int retorno = -1;
	int ganhador = 0;
	int nome = 0;
	libera = 0;

	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c                GANHADORES                 %c      %c",179,179,179,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c                                           %c      %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
		
	if(sorteados[0] == -1){
		do{
			for(i = 0; i < 3; i++){
				if(i == 0){
					x = 49;
					y = 9;
					gotoxy(x-2, y);
					printf("                   ");
				}
				gotoxy(x, y);
				printf("%c", 250);
				x = x+2;
				sleep(1);
			}
			sorteado = 1+(rand() % 100);
			for(i = 0; i < TAM_CLI; i++){
				if(sorteado == matriznumeros[0][i]){
					libera = 1;
				}
			}
		}while(libera != 1);
		libera = 0;
		for(i = 0; i < C_NUM; i++){
			if(sorteado == matriznumeros[0][i]){
				if(matriznumeros[1][i] != 0){
					ganhador = matriznumeros[1][i];	
				}
				break;
			}
		}
	
		for(i = 0; i < C_NUM; i++){
			if((ganhador != 0) && (ganhador == cliente_logado[i].id)){
				nome = cliente_logado[i].id;
				break;
			}else{
				nome = -1;
			}
		}
		gotoxy(38, 10);
		printf("O ganhador do %s foi: %i", premio1, sorteado);
		gotoxy(42, 11);
		strcpy(ganhador1, cliente_nome[nome].nome);
		printf("PARABENS!!! %s", ganhador1);
		sorteados[0] = sorteado;
		opcao = 0;
	}else{
		opcao = 49;
	}
		if(opcao != 49){
			sleep(2);
			gotoxy(34, 12);
			printf("Deseja sortear o segundo ganhador ?");
			gotoxy(38, 13);
			printf("1- Confirmar | 2- Cancelar:");
		}else{
			gotoxy(38, 10);
			printf("O ganhador do %s foi: %i", premio1, sorteados[0]);
			gotoxy(42, 11);
			printf("PARABENS!!! %s", ganhador1);			
		}
		
		while((opcao < 49) || (opcao > 50)){
			gotoxy(65, 13);
			fflush(stdin);
			opcao = getch();
		}
		
		if(opcao == 50){
			TelaAdmin();
		}
		nome = 0;
	if(sorteados[1] == -1){
		gotoxy(32, 12);
		printf("                                     ");
		gotoxy(36, 13);
		printf("                                  ");
		x = 49;
		y = 12;
		if(opcao == 49){
			do{
				for(i = 0; i < 3; i++){
					if(i == 0){
						x = 49;
						y = 12;
						gotoxy(x-2, y);
						printf("                   ");
					}
					gotoxy(x, y);
					printf("%c", 250);
					x = x+2;
					sleep(1);
				}
				sorteado = 1+(rand() % 100);
				for(i = 0; i < TAM_CLI; i++){
					if(sorteado == matriznumeros[0][i]){
						libera = 1;
					}
				}
			}while(libera != 1);
			libera = 0;
		}
		for(i = 0; i < C_NUM; i++){
			if(sorteado == matriznumeros[0][i]){
				if(matriznumeros[1][i] != 0){
					ganhador = matriznumeros[1][i];	
				}
				break;
			}
		}
	
		for(i = 0; i < C_NUM; i++){
			if((ganhador != 0) && (ganhador == cliente_logado[i].id)){
				nome = cliente_logado[i].id;
				break;
			}else{
				nome = -1;
			}
		}
		gotoxy(38, 13);
		printf("O ganhador do %s foi: %i", premio2, sorteado);
		gotoxy(42, 14);
		strcpy(ganhador2, cliente_nome[nome].nome);
		printf("PARABENS!!! %s", ganhador2);
		sorteados[1] = sorteado;
		opcao = 0;		
	}else{
		opcao = 49;
	}
		if(opcao != 49){
			sleep(2);
			gotoxy(34, 15);
			printf("Deseja sortear o terceiro ganhador ?");
			gotoxy(38, 16);
			printf("1- Confirmar | 2- Cancelar:");
		}else{	
			gotoxy(38, 13);
			printf("O ganhador do %s foi: %i", premio2, sorteados[1]);
			gotoxy(42, 14);
			printf("PARABENS!!! %s", ganhador2);				
		}
		
		while((opcao < 49) || (opcao > 50)){
			gotoxy(65, 16);
			fflush(stdin);
			opcao = getch();
		}
		
		if(opcao == 50){
			TelaAdmin();
		}
		nome = 0;
	if(sorteados[2] == -1){
		gotoxy(32, 15);
		printf("                                        ");
		gotoxy(36, 16);
		printf("                                     ");
		x = 49;
		y = 15;
		if(opcao == 49){
			do{
				for(i = 0; i < 3; i++){
					if(i == 0){
						x = 49;
						y = 15;
						gotoxy(x-2, y);
						printf("                   ");
					}
					gotoxy(x, y);
					printf("%c", 250);
					x = x+2;
					sleep(1);
				}
				sorteado = 1+(rand() % 100);
				for(i = 0; i < TAM_CLI; i++){
					if(sorteado == matriznumeros[0][i]){
						libera = 1;
					}
				}
			}while(libera != 1);
			libera = 0;
		}
		for(i = 0; i < C_NUM; i++){
			if(sorteado == matriznumeros[0][i]){
				if(matriznumeros[1][i] != 0){
					ganhador = matriznumeros[1][i];	
				}
				break;
			}
		}
	
		for(i = 0; i < C_NUM; i++){
			if((ganhador != 0) && (ganhador == cliente_logado[i].id)){
				nome = cliente_logado[i].id;
				break;
			}else{
				nome = -1;
			}
		}
		gotoxy(38, 16);
		printf("O ganhador do %s foi: %i", premio3, sorteado);
		gotoxy(42, 17);
		strcpy(ganhador3, cliente_nome[nome].nome);
		printf("PARABENS!!! %s", ganhador3);
		sorteados[2] = sorteado;
			opcao = 0;
	}else{
		GanhadoresJaSorteados();
	}
	
	do{
		gotoxy(2,2);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 27);
	TelaAdmin();	
}

void GanhadoresJaSorteados(){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                             %c%c%c%c%c%c%c%c%c ERRO %c%c%c%c%c%c%c%c%c                           %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                    Todos os ganhadores j%c foram sorteados                      %c",179,160,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
		
	sleep(3);
	TelaAdmin();
}

void TotalAPagar(int total){
	int opcao;
	int i =0;
	float num = 0.0;
	num = total*valor;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c  TOTAL A PAGAR  %c%c%c%c%c%c%c%c%c                     %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               TOTAL A PAGAR: $                                 %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                            1 Confirmar | 2 Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	gotoxy(48, 7);
	printf("%.2f", num);
	do{	
		gotoxy(54, 9);
		fflush(stdin);
		opcao = getch();	
	}while((opcao != 49) && (opcao != 50));
	
	if(opcao == 50){
		TelaCompra();
	}
			
}

void JaComprado(){
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                             %c%c%c%c%c%c%c%c%c ERRO %c%c%c%c%c%c%c%c%c                           %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               J%c est%c comprado !!!                             %c",179,160,160,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	sleep(2);
	Comprando();
}

void JaReservado(){

	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                             %c%c%c%c%c%c%c%c%c ERRO %c%c%c%c%c%c%c%c%c                           %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                               J%c est%c reservado !!!                            %c",179,160,160,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	sleep(2);
	Comprando();
}

int DesejaComprar(int coluna){
	int opcao = 0;
	int retorno = 0;
	int num;
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                      %c%c%c%c%c%c%c%c%c J%c EST%c RESERVADO %c%c%c%c%c%c%c%c%c                     %c",179,219,219,219,219,219,219,219,219,219,181,181,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                         Deseja comprar o n%cmero [  ] ?                         %c",179,163,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                           1 Confirmar | 2 Cancelar:                            %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	num = numerosreservados[0][coluna];
	compra = num;
	gotoxy(51, 8);
	if(num < 10){
		printf("0%i", num);
	}else if (num > 99){
		printf("%i]", num);
	}else{
		printf("%i", num);
	}
	
	do{
		gotoxy(53, 10);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50));
	if(opcao == 49){
		retorno = 1;
	}else{
		Comprando();
	}
	
	return retorno;
}

int DesejaCancelar(int coluna){
	int opcao = 0;
	int retorno = 0;
	int num;
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                       %c%c%c%c%c%c%c%c%c CANCELAR RESERVA %c%c%c%c%c%c%c%c%c                     %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                   Deseja cancelar a reserva do n%cmero [  ] ?                   %c",179,163,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                           1 Confirmar | 2 Cancelar:                            %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	num = numerosreservados[0][coluna];
	gotoxy(57, 8);
	if(num < 10){
		printf("0%i", num);
	}else if (num > 99){
		printf("%i]", num);
	}else{
		printf("%i", num);
	}
	
	do{
		gotoxy(53, 10);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50));
	if(opcao == 49){
		retorno = 1;
	}else{
		Comprando();
	}
	
	return retorno;
}

void ordena(){
	int i, aux, aux2, j;
	
	for(i = 1; i < C_NUM; i++){
		aux = matriznumeros[0][i];
		aux2 = matriznumeros[1][i];
		j=i-1;
		while(j > -1 && matriznumeros[0][j] < aux){
			matriznumeros[0][j+1] = matriznumeros[0][j];
			matriznumeros[1][j+1] = matriznumeros[1][j];
			j--;
		}
		matriznumeros[0][j+1] = aux;
		matriznumeros[1][j+1] = aux2;
	}
}

void ListarCompradores(){
	int i, x, y, cont, stop, opcao;
	stop = 0;
			
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c LISTA DE COMPRADORES %c%c%c%c%c%c%c%c%c                   %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%C%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c Nome      Num %c Nome      Num %c Nome      Num %c Nome      Num %c Nome      Num  %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c               %c               %c               %c               %c                %c",179,179,179,179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	ordena();
	x=1;
	y=7;
	cont=0;
	i=-1;
	
	do{
		i++;
		gotoxy(x, y);
		if(matriznumeros[0][i] != 0){
			printf("%s", cliente_nome[matriznumeros[1][i]].nome);
		}
		gotoxy(x+11, y);
		if(matriznumeros[0][i] != 0){
			printf("%i", matriznumeros[0][i]);
		}
		printf("\n");
		y++;
		cont++;
		if(cont == 14){
			x = x+16;
			y=7;
			cont=0;
			stop++;
		}
	}while(matriznumeros[0][i] != 0 && stop != 5);
	
	do{
		gotoxy(2,2);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 27);
	TelaAdmin();	
}

void TelaAdmin(){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c                                                         %c",179,179,179);
	printf("\n%c  2-Editar rifa       %c                                                         %c",179,179,179);
	printf("\n%c  3-Listar compradores%c                                                         %c",179,179,179);
	printf("\n%c  4-Listar ganhadores %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c                                                         %c",179,135,198,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	do{
		gotoxy(20, 12);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50) && (opcao != 51) && (opcao != 52) && (opcao != 27));
	
	if(opcao == 27){
		TelaMenu();
	}
	if(opcao == 49){
		SorteiaGanhador();
	}
	if(opcao == 50){
		EditarRifa();
	}
	if(opcao == 51){
		ListarCompradores();
	}
	if(opcao == 52){
		ListarGanhadores();
	}
	
}

void ListarGanhadores(){
	int opcao;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c    Pr%cmio       Ganhador       N%cmero     %c      %c",179,179,179,136,163,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c                                           %c      %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	gotoxy(35, 9);
	puts(premio1);
	if(sorteados[0] != -1){
		gotoxy(49, 9);
		puts(ganhador1);
		gotoxy(64, 9);
		printf("%i", sorteados[0]);
	}
	
	
	gotoxy(35, 10);
	puts(premio2);
	if(sorteados[1] != -1){
		gotoxy(49, 10);
		puts(ganhador2);
		gotoxy(64, 10);
		printf("%i", sorteados[1]);
	}
	
	gotoxy(35, 11);
	puts(premio3);
	if(sorteados[2] != -1){
		gotoxy(49, 11);
		puts(ganhador3);
		gotoxy(64, 11);
		printf("%i", sorteados[2]);
	}

	do{
		gotoxy(2,2);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 27);
	TelaAdmin();
}

void EditarRifa(){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c                                                         %c",179,179,179);
	printf("\n%c  2-Editar rifa       %c                                                         %c",179,179,179);
	printf("\n%c  3-Listar compradores%c                                                         %c",179,179,179);
	printf("\n%c  4-Listar ganhadores %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c                                                         %c",179,135,198,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

	gotoxy(25, 6);
	printf("1- Editar valor da rifa");
	gotoxy(25, 7);
	printf("2- Editar data do sorteio");
	gotoxy(25, 8);
	printf("3- Editar pr%cmio", 136);
	gotoxy(25, 10);
	printf("Escolha um op%c%co:", 135,198);
	gotoxy(25, 10);
	do{
		gotoxy(42, 10);
		fflush(stdin);
		opcao = getch();
	}while((opcao != 49) && (opcao != 50) && (opcao != 51) && (opcao != 27));
	
	if(opcao == 27){
		TelaAdmin();
	}
	if(opcao == 49){
		EditaValor();
	}
	if(opcao == 50){
		EditaData();
	}
	if(opcao == 51){
		EscolherPremio();
	}
}

void EscolherPremio(){
	int opcao;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c           EDITAR PR%cMIO DA RIFA           %c      %c",179,179,179,210,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c  1- Editar primeiro pr%cmio                %c      %c",179,179,179,136,179,179);
	printf("\n%c                      %c      %c  2- Editar segundo pr%cmio                 %c      %c",179,179,179,136,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c  3- Editar terceiro pr%cmio                %c      %c",179,135,198,179,179,136,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c  Qual deseja editar:                      %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

	do{
		gotoxy(52, 14);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50 && opcao != 51 && opcao != 27);
	
	switch(opcao){
		case 49:
			EditaPremio(opcao);
			break;
		case 50:
			EditaPremio(opcao);
			break;
		case 51:
			EditaPremio(opcao);
			break;
		case 27:
			EditarRifa();
			break;
	}
	
}

void EditaPremio(int qualp){
	int opcao, letra;
	char produto[PREMIO];
	int qual = qualp;
	int cont, x, y;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c           EDITAR PR%cMIO DA RIFA           %c      %c",179,179,179,210,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c            Novo pr%cmio :                  %c      %c",179,179,179,136,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c                                           %c      %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c      %c        1- Confirmar | 2- Cancelar:        %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	if(qualp == 49){
		gotoxy(54, 10);
		printf("%c", 251);
	}else if(qualp == 50){
		gotoxy(54, 10);
		printf("%c", 253);
	}else{
		gotoxy(54, 10);
		printf("%c", 252);
	}
			
	x=56;
	y=10;
	cont=0;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 47;
			}else if(letra == 8){
				letra = 58;
			}else if(letra == 32){
				letra = 59;
			}		
		}while((letra < 45) || (letra > 122));
			if(letra == 47){
				letra = 13;
			}else if(letra == 58){
				letra = 8;				
			}else if(letra == 59){
				letra = 32;
			}
		printf("%c", letra);
		if(letra != 13 && letra != 8 && cont < 8){
			produto[cont] = letra;
		}
		cont++;
		if(cont == 8){
			cont--;
			gotoxy(x, y);
			printf(" ");
			x--;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 57){
				x = 56;
				gotoxy(x, y);
				printf(" ");
			}
			gotoxy(x+1, y);
			printf("  ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}	
		}
	}while(letra != 13);
		
	do{
		gotoxy(66, 13);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);	
	if(opcao == 49){
		TelaConfirmaPremio(produto, qual);
	}else{
		EditarRifa();
	}
}

void TelaConfirmaPremio(char produto[], int qual){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c CONFIRMAR ALTERA%c%cO %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,128,199,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                    Deseja alterar o pr%cmio da rifa para:                       %c",179,136,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1- Confirmar | 2- Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	gotoxy(58, 7);
	printf("%s", produto);
	
	do{
		gotoxy(54, 9);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);
	if(opcao == 49 && qual == 49){
		strcpy(premio1, produto);
		EditarRifa();
	}else if(opcao == 49 && qual == 50){
		strcpy(premio2, produto);
		EditarRifa();
	}else if(opcao == 49 && qual == 51){
		strcpy(premio3, produto);
		EditarRifa();
	}else{
		EditaPremio(qual);
	}
}

void EditaData(){
	int opcao, x, y, cont, letra;
	char dia[DATA];
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c            EDITAR DATA DA RIFA            %c      %c",179,179,179,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c            Nova data:                     %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c                                           %c      %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c      %c        1- Confirmar | 2- Cancelar:        %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	x=53;
	y=10;
	cont=-1;
	do{
		do{
			gotoxy(x, y);
			fflush(stdin);
			letra = getch();
			if(letra == 13){
				letra = 40;
			}else if(letra == 8){
				letra = 58;
			}else if(letra == 32){
				letra = 59;
			}		
		}while((letra < 40) || (letra > 59));
			if(letra == 40){
				letra = 13;
			}else if(letra == 58){
				letra = 8;				
			}else if(letra == 59){
				letra = 32;
			}
		printf("%c", letra);
		if(letra != 13){
			cont++;
		}
		if(cont <= 9 && letra != 13){
			dia[cont] = letra;
		}
		if(cont > 9){
			letra = 13;
		}
		x++;
		if(letra == 8){
			x = x-2;
			if(x < 53){
				x = 53;
			}
			gotoxy(x, y);
			printf(" ");
			cont = cont-2;
			if(cont < 0){
				cont = 0;
			}	
		}
	}while(letra != 13);
	
	
	
	do{
		gotoxy(66, 13);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);	
	if(opcao == 49){
		TelaConfirmaData(dia);
	}else{
		EditarRifa();
	}
}

void TelaConfirmaData(char dia[]){
	int opcao;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c CONFIRMAR ALTERA%c%cO %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,128,199,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                     Deseja alterar a data da rifa para:                        %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1- Confirmar | 2- Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	gotoxy(57, 7);
	printf("%s", dia);
	do{
		gotoxy(54, 9);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);
	if(opcao == 49){
		strcpy(data, dia);
		EditarRifa();
	}else{
		EditaData();
	}
}

void TelaConfirmarValor(float preco){
	int opcao,i;
	
	system("cls");	
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                     %c%c%c%c%c%c%c%c%c CONFIRMAR ALTERA%c%cO %c%c%c%c%c%c%c%c%c                    %c",179,219,219,219,219,219,219,219,219,219,128,199,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                     Deseja alterar o valor da rifa para:$                      %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                          1- Confirmar | 2- Cancelar:                           %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	gotoxy(59, 7);
	printf("%.2f", preco);
	
	do{
		gotoxy(54, 9);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);
	if(opcao == 49){
		valor = preco;
		EditarRifa();
	}else{
		EditaValor();
	}
	
}

void EditaValor(){
	int opcao, x, y, cont, letra, i;
	float preco;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c ESC-Sair                                                              ID:ADMIN %c",179,179);
	printf("\n%c                        %c%c%c%c%c%c%c%c%c Administrador %c%c%c%c%c%c%c%c%c                       %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c  1-Sortear ganhador  %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191,179);
	printf("\n%c  2-Editar rifa       %c      %c           EDITAR VALOR DA RIFA            %c      %c",179,179,179,179,179);
	printf("\n%c  3-Listar compradores%c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c  4-Listar ganhadores %c      %c            Novo valor:$                   %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c Escolha uma op%c%co:   %c      %c                                           %c      %c",179,135,198,179,179,179,179);
	printf("\n%c                      %c      %c        1- Confirmar | 2- Cancelar:        %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c                                           %c      %c",179,179,179,179,179);
	printf("\n%c                      %c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c      %c",179,179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c                      %c                                                         %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);

	gotoxy(55,10);
	fflush(stdin);
	scanf("%f", &preco);

	do{
		gotoxy(66, 13);
		fflush(stdin);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);
	
	if(opcao == 49){
		TelaConfirmarValor(preco);
	}else{
		EditarRifa();
	}
}

void Sorteio(int qtd, int comprar, int reservar){
	int numeros[qtd];
	int s, c, cont;
	int i, j;
	cont = 0;
	
	for(s = 0; s < qtd; s++){
		numeros[s] = 0;
	}
	
	for(s = 0; s < qtd; s++){
		numeros[s] = 1+(rand() % 100);
		if(comprar == 1){
			for(i = 0; i < TAM_L; i++){
				for(j = 0; j < TAM_C; j++){
					
					if(numeros[s] == cont){
						if(matrizrifa[i][j-1] == 1){
							s = s-1;
						}else if(matrizrifa[i][j-1] == 2){
							s = s-1;
						}else{						
							matrizrifa[i][j-1] = 1;
							matriznumeros[0][numeros[s]] = numeros[s];
							matriznumeros[1][numeros[s]] = ID;
						}	
					}	
					cont++;
				}
			}	
		}else if(reservar == 2){
			for(i = 0; i < TAM_L; i++){
				for(j = 0; j < TAM_C; j++){
					if(numeros[s] == cont){
						if(matrizrifa[i][j-1] == 1){
							s = s-1;
						}else if(matrizrifa[i][j-1] == 2){	
							s = s-1;
						}else{	
							matrizrifa[i][j-1] = 2;
							numerosreservados[0][numeros[s]] = numeros[s];	
							numerosreservados[1][numeros[s]] = ID;
						}	
					}
					cont++;
				}
			}
		}
	
		cont = 0;	 
	}
	
	TelaCompra();
}

int validaADM(char nome[], char senha[]){
	int retorno = -1;

	retorno = strcmp(adm.nome, nome);
	if(retorno == 0){
		retorno = strcmp(adm.senha, senha);
	}
	return retorno;	
}

void TelaLoginAdmin(){
	int opcao;
	char nome[10];
	char senha[10];
	int retorno = -1;
	
	system("cls");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c                      %c%c%c%c%c%c%c%c%c Login Administrador %c%c%c%c%c%c%c%c%c                   %c",179,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,179);
	printf("\n%c                                                                                %c",179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",195,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,180);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                         Login:                    Senha:                       %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c                           1- Confirmar | 2- Cancelar:                          %c",179,179,179);
	printf("\n%c                                                                                %c",179,179,179);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	
	gotoxy(32, 8);
	fflush(stdin);
	gets(nome);
	gotoxy(58, 8);
	fflush(stdin);
	gets(senha);
	do{
		gotoxy(55, 10);
		opcao = getch();
	}while(opcao != 49 && opcao != 50);
		if(opcao == 49){
			retorno = validaADM(nome, senha);
			if(retorno == 0){
				TelaAdmin();
			}else{
				LoginAdmInvalido();
			}
		}else{
			TelaMenu();
		}	
}

void TelaRifa(){
	int i, j, linha, coluna, cont;
	linha = 28;
	coluna =12;		
	cont = 1;
	for(i = 0; i < TAM_L; i++){
		gotoxy(linha,coluna);
		for(j = 0; j < TAM_C; j++){
			if(matrizrifa[i][j] == 0){
				if(cont < 10){
					printf("|0%i| ", cont++);
				}else{
					printf("|%i| ", cont++);
				}				
			}else if(matrizrifa[i][j] == 2){
				if(cont < 10){
					printf("(0%i) ", cont++);
				}else{
					printf("(%i) ", cont++);
				}				
			}else if(matrizrifa[i][j] == 1){
				if(cont < 10){
					printf("[0%i] ", cont++);
				}else{
					printf("[%i] ", cont++);
				}
			}		
		}
		printf("\n");
		coluna++;
	}	
}

void TodasGlobaisZeradas(){
	int i, j;
	
	strcpy(adm.nome, "admin");
	strcpy(adm.senha, "admin");
	
	for(j = 0; j < TAM_CLI; j++){
		cliente_logado[j].id = 0;
		strcpy(cliente_logado[j].cpf, " ");
		strcpy(cliente_logado[j].senha, " ");
		strcpy(cliente_logado[j].nome, " ");
	}
	for(i = 0; i < TAM_L; i++){
		for(j = 0; j < TAM_C; j++){
			matrizrifa[i][j] = 0;
			matriznumeros[i][j] = 0;
		}
	}
	for(i = 0; i < L_NUM; i++){
		for(j = 0; j < C_NUM; j++){
			matriznumeros[i][j] = 0;
		}
	}
	strcpy(ganhador1, " ");
	strcpy(ganhador2, " ");
	strcpy(ganhador3, " ");
	strcpy(premio1, " ");
	strcpy(premio2, " ");
	strcpy(premio3, " ");
	strcpy(data, " ");
	for(i = 0; i < G_C; i++){
		sorteados[i] = -1;	
	}
	
	for(i = 0; i < L_NUM; i++){
		for(j = 0; j < C_NUM; j++){
			numerosreservados[i][j] = -1;
		}
	}
}

main(){
	TodasGlobaisZeradas();		
	TelaMenu();
}
