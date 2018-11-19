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
double hora=0;

void atualizaFila(){
	if(fila.size()>0)
	{
		int tam = fila.size();
		for(int i=0;i<tam;i++)
		{
			/*printf("hora de entrada: %lf\n",fila.front().horaDeEntrada);
			printf("tempo de espera: %lf\n",fila.front().tempoDeEspera);
			printf("tempo de atendimento: %lf\n",fila.front().tempoDeAtendimento);
			printf("hora: %lf\n", hora);
			printf("result soma = %lf\n",fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento);
		*/
			if(fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento <= hora  )
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

double simularExpLambda( double lambda){
	double U = ((rand()%100)+1)/101.0;
	double x= -(1/lambda) * log(U);
	double abc=log(U);
	/*printf("U = %lf, lambida = %lf, log(U) = %lf\n",U ,lambda, abc);
	printf("%lf\n", x);*/
	
	return x;
}

cliente geraCliente(double atendimento){
	cliente novoCliente;
	novoCliente.tempoDeAtendimento=simularExpLambda(atendimento);
	novoCliente.horaDeEntrada=hora;
	if(fila.size()>0)
	{
		
		/*printf("hora de entrada: %lf\n",fila.front().horaDeEntrada);
		printf("tempo de espera: %lf\n",fila.front().tempoDeEspera);
		printf("tempo de atendimento: %lf\n",fila.front().tempoDeAtendimento);
		printf("result soma = %lf",fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento);
		printf("hora: %lf\n", hora);*/
		novoCliente.tempoDeEspera=fila.front().horaDeEntrada+fila.front().tempoDeEspera+fila.front().tempoDeAtendimento-hora;
		for(int i=1;i<fila.size();i++)
		{
			novoCliente.tempoDeEspera=novoCliente.tempoDeEspera+fila[i].tempoDeAtendimento;
		}
	}
	else
	{
		novoCliente.tempoDeEspera=0;
	}
	fila.push_back(novoCliente);
	return novoCliente;
	
}

void letraA(){
	srand (time(NULL));
	int X = simularExpLambda(1/10.0);
	int Y = simularExpLambda(1/5.0);
	double entrada = 1/10.0;
	double atendimento = 1/5.0;
	
	while(hora<480)
	{
		double tempoPassado = simularExpLambda(entrada);
		hora=hora+tempoPassado;
		
		atualizaFila();
		
		if(hora<=480)
		{
			cliente novoCliente = geraCliente(atendimento);
		} 
		else
		{
			hora=hora-tempoPassado;
			break;
		}
	}
	cout<<fila.size()<<endl;
	if(fila.size()>0)
	{
		for(int i=0;i<fila.size();i++)
		{
			result.push_back(fila.front());
			fila.pop_front();
		}
	}
	double media=0;
	int quant=0;
	cout<<endl<<endl<<endl;
	for(int i=0; i<result.size(); i++)
	{
		cout<<"cliente"<<i<<endl;
		cout<<"Hora de chegada: "<<result[i].horaDeEntrada<<endl;
		cout<<"Tempo de Espera: "<<result[i].tempoDeEspera<<endl;
		cout<<"Tempo de Atendimento: "<<result[i].tempoDeAtendimento<<endl<<endl;
		
		media=media+result[i].tempoDeEspera;
	}
	quant = result.size();
	media=media/quant;
	cout<<"Quant: "<<quant<<endl;
	cout<<"Média: "<<media<<endl;
}

int main(){
	
	letraA();
	
	return 0;
}
