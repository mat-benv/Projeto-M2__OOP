#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Representante{
    public:
        int id;
        int itens=0;
        double valor=0.0;
        double com = 0.0;
        double comVal=0.1;

        Representante(int i) : id(i) {}

        void registrarVenda(int numItens, double valorVenda){
            itens += numItens;
            valor += valorVenda;
            if (itens >= 20 && com != 0.25){
                atualizarComissao();
            }
            com = valor * comVal; // calcula comissão
        }

        void atualizarComissao(){
            if (itens < 50){
                comVal = 0.15;
            } else if (itens < 75){
                comVal = 0.2;
            } else {
                comVal = 0.25;
            }
        }
};


vector<Representante> reps = {
    Representante(1),
    Representante(2),
    Representante(3),
    Representante(4)
};



double totalVendas() {
    double totalValor = 0.0;
    for (const Representante& r : reps){
        totalValor += r.valor;
    }
    return totalValor;
}

void opcao3(){
    cout << "O total de comissões por representante é: " << endl;
                
    for (const Representante& r : reps){
        cout << "Representante " << r.id << ": R$" << r.com << endl;
    }
}

void opcao4(){
    double totalCom = 0.0;
    for (const Representante& r : reps){
        totalCom += r.com;
    }
    cout << "O total geral de comissões a serem pagas é: R$" << totalCom << endl;
}

bool nenhumaVenda(){
    for (const Representante& r : reps){
        if (r.valor != 0.0){
            return false;
        }
    }
    return true;
}

bool alguemNaoVendeu(){
    for (const Representante& r : reps){
        if (r.itens == 0){
            return true;
        }
    }
    return false;
}

void maiorValor(){
    Representante champ(0);
    for (const Representante& r : reps){
        if (r.valor > champ.valor){
            champ = r;
        }
    }
    cout << "O representante com o maior valor em vendas é o representante " << champ.id << endl;
    cout << "Ele vendeu, no total: R$" << champ.valor << endl;
}

void menosItens(){
    Representante loser(0);
    for (const Representante& r : reps){
        if (r.itens <= loser.itens){
            loser = r;
        }
    }
    cout << "O representante que vendeu menos itens foi o representante " << loser.id << endl;
    cout << "Ele vendeu apenas " << loser.itens << endl;
}

int main(){
    setlocale(LC_ALL, "portuguese");
    cout << fixed << setprecision(2);

        int rep, o=0, numItens=0, vendasProcessadas=0;
        double valor;
        char p;

    do{
        do{
            cout << endl << "==== MENU - SISTEMA DE COMISSÕES ====" << endl;
            cout << "1 - Registar nova venda" << endl;
            cout << "2 - Exibir total de vendas processadas" << endl;
            cout << "3 - Exibir total de comissões por representante" << endl;
            cout << "4 - Exibir total de comissões pagas pela empresa" << endl;
            cout << "5 - Vendedor com o maior valor de vendas" << endl;
            cout << "6 - Vendedor com a menor quantidade de itens vendidos" << endl;
            cout << "7 - Sair" << endl;
            cin >> o;
        }while(o < 1 || o > 7); // até valor válido de opção do menu

        switch (o){ // valores do menu
            case 1:
                do{
                    do{
                        cout << "Digite o código do representante: " << endl;
                        cin >> rep;

                    }while(rep < 1 || rep > 4);

                    do{
                        cout << "Digite o número de itens vendidos: " << endl;
                        cin >> numItens;
                    }while(numItens < 1);

                    do{
                        cout << "Digite o valor total da venda: " << endl;
                        cin >> valor;
                    }while(valor <= 0.0);

                    for (Representante& r : reps){
                        if (r.id == rep){
                            r.registrarVenda(numItens, valor);
                        }
                    }

                    vendasProcessadas++; // atualiza quantidade total de vendas
                    
                    cin.ignore();
                    do{

                        cout << "Deseja informar mais uma venda? (S/N) " << endl;
                        cin >> p;

                    }while(toupper(p) != 'S' && toupper(p) != 'N');

                }while(toupper(p) != 'N');

                break; // quebra switch de opção

            case 2:
                cout << "O total acumulado de vendas processdas é " << vendasProcessadas << endl << "Para um valor de R$" << totalVendas() << endl;
                break;

            case 3: opcao3();
                break;
            
            case 4: opcao4();
                break;

            case 5:
                if(nenhumaVenda()){
                    cout << "Ninguém vendeu nada." << endl;
                }else{
                    maiorValor();
                }
                break;

            case 6:
                if(alguemNaoVendeu()){ // verifica se teve vendedor que não fez nenhuma venda
                    for (Representante r : reps){
                        if(r.itens == 0){
                            cout << "O representante " << r.id << " não vendeu nenhum item." << endl;
                        }
                    }
                }else{
                    menosItens();
                }
        }
    }while (o != 7);
    
return 0;
}