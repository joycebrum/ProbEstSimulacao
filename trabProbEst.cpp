
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
	double abc = log(U);
	/*printf("U = %lf, lambida = %lf, log(U) = %lf\n",U ,lambda, abc);
	printf("%lf\n", x);*/

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
void letraA() {
	double entrada = 1 / 10.0;
	double atendimento = 1 / 5.0;

	while (hora<480)
	{
		double tempoPassado = simularExpLambda(entrada);
		hora = hora + tempoPassado;

		atualizaFila();

		if (hora <= 480)
		{
			cliente novoCliente = geraCliente(atendimento);
		}
		else
		{
			hora = hora - tempoPassado;
			break;
		}
	}
	cout << fila.size() << endl;
	if (fila.size()>0)
	{
		for (unsigned int i = 0; i<fila.size(); i++)
		{
			result.push_back(fila.front());
			fila.pop_front();
		}
	}
	double media = 0;
	int quant = 0;
	cout << endl << endl << endl;
	for (unsigned int i = 0; i<result.size(); i++)
	{
		cout << "cliente" << i << endl;
		cout << "Hora de chegada: " << result[i].horaDeEntrada << endl;
		cout << "Tempo de Espera: " << result[i].tempoDeEspera << endl;
		cout << "Tempo de Atendimento: " << result[i].tempoDeAtendimento << endl << endl;

		media = media + result[i].tempoDeEspera;
	}
	quant = result.size();
	media = media / quant;
	cout << "Quant: " << quant << endl;
	cout << "Média: " << media << endl;
}

double amostra(double entrada, double atendimento) {
	cout << "quantidade no inicio " << result.size() << endl;
	int temporario = 0;
	while (hora<480)
	{
		temporario++;
		double tempoPassado = simularExpLambda(entrada);
		hora = hora + tempoPassado;
		cout << hora << endl;
		atualizaFila();

		if (hora <= 480)
		{
			cliente novoCliente = geraCliente(atendimento);
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
	}
	quant = result.size();
	cout << media << " quantidade = " << quant << " quando na verdade é " << result.size()
		<< " e foram " << temporario << " loops" << endl << endl;
	media = media / quant;

	return media;
}

void letraC(double entrada, double atendimento, double z) {
	double amostras[100];
	double sumAmostras = 0;
	for (int i = 0; i < 100; i++) {
		limpaVariaveis();
		amostras[i] = amostra(entrada, atendimento);
		cout << amostras[i] << endl << endl;
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

int main() {
	srand(time(NULL));
	letraC(1 / 10.0, 1 / 5.0, 0.3159);
	cout << "entrada = 5 minutos e atendimento = 10 minutos" << endl << endl;
	limpaVariaveis();
	letraC(1 / 5.0, 1 / 10.0, 0.3159);

	return 0;
}


