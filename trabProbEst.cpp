
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <cmath>
#include <deque>


using namespace std;
typedef struct _CLIENTE {
	double tempoDeEspera;
	double tempoDeAtendimento;
	double horaDeEntrada;
} cliente;

deque<cliente> fila;
deque<cliente> result;
double hora = 0;

void atualizaFila() {
	if (fila.size()>0)
	{
		int tam = fila.size();
		for (int i = 0; i<tam; i++)
		{
			/*printf("hora de entrada: %lf\n",fila.front().horaDeEntrada);
			printf("tempo de espera: %lf\n",fila.front().tempoDeEspera);
			printf("tempo de atendimento: %lf\n",fila.front().tempoDeAtendimento);
			printf("hora: %lf\n", hora);
			printf("result soma = %lf\n",fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento);
			*/
			if (fila.front().horaDeEntrada + fila.front().tempoDeEspera + fila.front().tempoDeAtendimento <= hora)
			{
				result.push_back(fila.front());
				fila.pop_front();
			}
			else
			{
				break;
			}
		}
	}
}

double simularExpLambda(double lambda) {
	double U = ((rand() % 100) + 1) / 101.0;
	double x = -(1 / lambda) * log(U);

	return x;
}

cliente geraCliente(double atendimento) {
	cliente novoCliente;
	novoCliente.tempoDeAtendimento = simularExpLambda(atendimento);
	novoCliente.horaDeEntrada = hora;
	if (fila.size()>0)
	{

		/*printf("hora de entrada: %lf\n",fila.front().horaDeEntrada);
		printf("tempo de espera: %lf\n",fila.front().tempoDeEspera);
		printf("tempo de atendimento: %lf\n",fila.front().tempoDeAtendimento);
		printf("result soma = %lf",fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento);
		printf("hora: %lf\n", hora);*/
		novoCliente.tempoDeEspera = fila.front().horaDeEntrada + fila.front().tempoDeEspera + fila.front().tempoDeAtendimento - hora;
		for (unsigned int i = 1; i<fila.size(); i++)
		{
			novoCliente.tempoDeEspera = novoCliente.tempoDeEspera + fila[i].tempoDeAtendimento;
		}
	}
	else
	{
		novoCliente.tempoDeEspera = 0;
	}
	fila.push_back(novoCliente);
	return novoCliente;

}

void esvaziaFila() {

	while (!fila.empty())
	{
		result.push_back(fila.front());
		fila.pop_front();
	}
}
void limpaVariaveis() {
	while (!fila.empty())
	{
		fila.pop_front();
	}
	while (!result.empty())
	{
		result.pop_front();
	}
	hora = 0;
}

double amostra(double entrada, double atendimento) {
	while (hora<480)
	{
		double tempoPassado = simularExpLambda(entrada);
		hora = hora + tempoPassado;
		atualizaFila();

		if (hora <= 480)
		{
			geraCliente(atendimento);
		}
		else
		{
			hora = hora - tempoPassado;
			break;
		}
	}
	esvaziaFila();
	double media = 0;
	int quant = 0;
	for (unsigned int i = 0; i<result.size(); i++)
	{
		media = media + result[i].tempoDeEspera;
		// cout << "cliente" << i << endl;
		// cout << "Hora de chegada: " << result[i].horaDeEntrada << endl;
		// cout << "Tempo de Espera: " << result[i].tempoDeEspera << endl;
		// cout << "Tempo de Atendimento: " << result[i].tempoDeAtendimento << endl << endl;
	}
	quant = result.size();
	media = media / quant;

	return media;
}

void letraA() {
	double entrada = 1 / 10.0;
	double atendimento = 1 / 5.0;
	double media = amostra(entrada, atendimento);
	cout << "Quant: " << result.size() << endl;
	cout << "Média: " << media << endl;
}


void letraC(double entrada, double atendimento, double z) {
	double amostras[100];
	double sumAmostras = 0;
	for (int i = 0; i < 100; i++) {
		limpaVariaveis();
		amostras[i] = amostra(entrada, atendimento);
		sumAmostras += amostras[i];
	}
	double mediaAmostral = sumAmostras / 100;
	double tau = 1 / 101;
	for (int i = 0; i < 100; i++) {
		tau += pow(amostras[i] - mediaAmostral, 2);
	}
	tau = sqrt(tau);
	double temp = z * tau / 10;
	cout << "intervalo de confiança = [" << mediaAmostral - temp << ", " << mediaAmostral + temp << "]" << endl;
}


void letraD () {
	letraC(1 / 5.0, 1 / 10.0, 0.3159);
}

int main() {
	srand(time(NULL));
	char letra;
	cout << "Digite a letra da questão dentre as opções  [a,c,d]" << endl;
	cin >> letra;
	switch(letra) {
		case 'a':
			cout << "Simula um dia de serviço" << endl;
			letraA();
			break;
		case 'c':
			cout << "Intervalo de confiança da média amostral" << endl;
			letraC(1 / 10.0, 1 / 5.0, 0.3159);
			break;
		case 'd':
			cout << "Intervalo de confiança da média amostral para parâmetros invertidos" << endl;
			letraD();
			break;
		default:
			cout << "Opção Inválida" << endl;
			break;
	}
	return 0;
}

