#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
using namespace std;

string parse(string json){
	for(int i=0;i<json.size()-1;){
		if(json[i]=='{')
			json.erase(i,1);
		else if(json[i]=='}'){
			json[i] = '\n';
			json.erase(i+1,1);
		} else i++;
	}
	return json;
}

int main (){
	try{
		ClientSocket client_socket ( "localhost", PORTA );
		string reply,a;
		string orderID,rowID;
		int comando;

		
		cout << "Menu" << endl << "[0] - Salvar e Encerrar" << endl << "[1] - Buscar" << endl << "[2] - Inserir" << endl << "[3] - Remover" << endl << endl << "Comando: ";
		cin >> comando;
		
		while(comando != 0){
			string info, stringRegistros = "";
			string operacaoDisponivel;
						
			switch (comando){
				
				case 1:
				
					/** BUSCA **/
					
					cout << "Order ID para busca: ";
					cin >> orderID;
					rowID = "-1";
					
					client_socket << "f" + orderID + "," + rowID;
					client_socket >> reply;
					
					switch(reply[0]){
						case '4':
							cout << "Nenhuma ID correspondente" << endl << endl;
							break;
						case 'R':
							cout << "Existe mais de um registro com essa ID. Informe a Row ID: ";
							cin >> rowID;
							client_socket << "f" + orderID + "," + rowID;
							client_socket >> reply;
							if(reply == "404"){
								cout << "Nenhuma ID correspondente" << endl << endl;
								break;
							}
						case 'S':
							reply.erase(0,1);
							cout << parse(reply) << endl; 
							break; 
					}
					break;
				
				case 2:
				
					/** INSERÇÃO **/
					
					cout << "Dados para inserir" << endl;
					
					cout << "Row ID: ";  				cin >> info;	stringRegistros += info + ";";
					cout << "Order ID: ";				cin >> info;	stringRegistros += info + ";";
					cout << "Order Date: ";				cin >> info;	stringRegistros += info + ";";
					cout << "Order Priority: ";			cin >> info;	stringRegistros += info + ";";
					cout << "Order Quantity: ";			cin >> info;	stringRegistros += info + ";";
					cout << "Sales: ";					cin >> info;	stringRegistros += info + ";";
					cout << "Discount: ";				cin >> info;	stringRegistros += info + ";";
					cout << "Ship Mode: "; 				cin >> info;	stringRegistros += info + ";";
					cout << "Profit: ";					cin >> info;	stringRegistros += info + ";";
					cout << "Unit Price: ";				cin >> info;	stringRegistros += info + ";";
					cout << "Shipping Cost: ";			cin >> info;	stringRegistros += info + ";";
					cout << "Customer Name: ";			cin >> info;	stringRegistros += info + ";";
					cout << "Province: ";				cin >> info;	stringRegistros += info + ";";
					cout << "Region: ";					cin >> info;	stringRegistros += info + ";";
					cout << "Customer Segment: "; 		cin >> info;	stringRegistros += info + ";";
					cout << "Product Category: ";		cin >> info;	stringRegistros += info + ";";
					cout << "Product Sub-Category: ";	cin >> info;	stringRegistros += info + ";";
					cout << "Product Name: ";			cin >> info;	stringRegistros += info + ";";
					cout << "Product Container: ";		cin >> info;	stringRegistros += info + ";";
					cout << "Product Base Margin: ";	cin >> info;	stringRegistros += info + ";";
					cout << "Ship Date: ";				cin >> info;	stringRegistros += info + ";";
					
					client_socket << "i" + stringRegistros;
					client_socket >> reply;
					cout << reply << endl;
					break;
			
				case 3:
				
					/** REMOÇÃO **/
					
					cout << "Order ID para remover: ";
					cin >> orderID;
					rowID = "-1";
														
					client_socket << "r" + orderID + "," + rowID;
					client_socket >> reply;
					
					switch(reply[0]){
						case '4':
							cout << "Nenhuma ID correspondente" << endl << endl;
							break;
						case 'R':
							cout << "Existe mais de um registro com essa ID. Informe a Row ID: ";
							cin >> rowID;
							client_socket << "r" + orderID + "," + rowID;
							client_socket >> reply;
							if(reply == "404"){
								cout << "Nenhuma ID correspondente" << endl << endl;
								break;
							}
						case 'S':
							cout << "Removido com sucesso!" << endl;
							break; 
					}
					break;
				}
			
			cout << endl;
			cout << "Menu" << endl << "[0] - Salvar e Encerrar" << endl << "[1] - Buscar" << endl << "[2] - Inserir" << endl << "[3] - Remover" << endl << endl << "Comando: ";
			cin >> comando;
			
		}	
		client_socket << "s";
		client_socket >> reply;
		cout << reply << endl;

	}
	catch ( SocketException& e ){
		cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}
