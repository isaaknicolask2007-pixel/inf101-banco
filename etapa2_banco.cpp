// INF101 - Programacao de Computadores I
// Trabalho: Sistema de Registro e Gestao de Contas Bancarias - ETAPA 2
// Varias contas e historico de movimentacoes em memoria (arrays).
// Tudo implementado diretamente no main(), sem funcoes.

#include <iostream>
#include <string>
using namespace std;

int main() {
    // ---------- Dados das contas ----------
    const int MAX_CONTAS = 100;

    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];      // 1 = Corrente; 2 = Poupanca
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int quantidadeContas = 0;

    // ---------- Historico de movimentacoes ----------
    const int MAX_MOVIMENTACOES = 500;

    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];   // D = Deposito, S = Saque
    double valorMovimentacao[MAX_MOVIMENTACOES];

    int quantidadeMovimentacoes = 0;

    int opcao;

    do {
        // ---------- Menu ----------
        cout << "\n********************************" << endl;
        cout << "**        BANCO INF101        **" << endl;
        cout << "********************************" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Exibir extrato" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

        // ================= 1 - CADASTRAR CONTA =================
        case 1: {
            if (quantidadeContas >= MAX_CONTAS) {
                cout << "Erro: limite maximo de contas atingido!" << endl;
            } else {
                int novoNumero;

                // Numero deve ser maior que zero
                do {
                    cout << "Numero da conta: ";
                    cin >> novoNumero;
                    if (novoNumero <= 0) {
                        cout << "Erro: o numero deve ser maior que zero!" << endl;
                    }
                } while (novoNumero <= 0);

                // Verifica se o numero ja existe
                bool jaExiste = false;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == novoNumero) {
                        jaExiste = true;
                    }
                }

                if (jaExiste) {
                    cout << "Erro: ja existe uma conta com esse numero!" << endl;
                } else {
                    // A nova conta ocupa a primeira posicao livre
                    int p = quantidadeContas;
                    numeroConta[p] = novoNumero;

                    cin.ignore(); // limpa o \n antes do getline
                    cout << "Nome do titular: ";
                    getline(cin, nomeCliente[p]);

                    cout << "CPF do titular: ";
                    getline(cin, cpf[p]);

                    // Tipo da conta deve ser 1 ou 2
                    do {
                        cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
                        cin >> tipoConta[p];
                        if (tipoConta[p] != 1 && tipoConta[p] != 2) {
                            cout << "Erro: tipo invalido! Digite 1 ou 2." << endl;
                        }
                    } while (tipoConta[p] != 1 && tipoConta[p] != 2);

                    // Saldo inicial nao pode ser negativo
                    do {
                        cout << "Saldo inicial: R$ ";
                        cin >> saldo[p];
                        if (saldo[p] < 0) {
                            cout << "Erro: o saldo inicial nao pode ser negativo!" << endl;
                        }
                    } while (saldo[p] < 0);

                    contaAtiva[p] = true;
                    quantidadeContas++;
                    cout << "Conta cadastrada com sucesso!" << endl;
                }
            }
            break;
        }

        // ================= 2 - LISTAR CONTAS =================
        case 2: {
            if (quantidadeContas == 0) {
                cout << "Nenhuma conta cadastrada." << endl;
            } else {
                cout << "\n--- CONTAS CADASTRADAS ---" << endl;
                for (int i = 0; i < quantidadeContas; i++) {
                    cout << "Conta " << numeroConta[i]
                         << " | " << nomeCliente[i]
                         << " | CPF: " << cpf[i];
                    if (tipoConta[i] == 1) {
                        cout << " | Corrente";
                    } else {
                        cout << " | Poupanca";
                    }
                    cout << " | Saldo: R$ " << saldo[i];
                    if (contaAtiva[i]) {
                        cout << " | Ativa" << endl;
                    } else {
                        cout << " | Inativa" << endl;
                    }
                }
            }
            break;
        }

        // ================= 3 - CONSULTAR CONTA =================
        case 3: {
            int numBusca, indice = -1;
            cout << "Numero da conta: ";
            cin >> numBusca;

            // Busca sequencial pelo numero informado
            for (int i = 0; i < quantidadeContas && indice == -1; i++) {
                if (numeroConta[i] == numBusca) {
                    indice = i;
                }
            }

            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else {
                cout << "\n--- DADOS DA CONTA ---" << endl;
                cout << "Numero: " << numeroConta[indice] << endl;
                cout << "Titular: " << nomeCliente[indice] << endl;
                cout << "CPF: " << cpf[indice] << endl;
                if (tipoConta[indice] == 1) {
                    cout << "Tipo: Corrente" << endl;
                } else {
                    cout << "Tipo: Poupanca" << endl;
                }
                cout << "Saldo: R$ " << saldo[indice] << endl;
                if (contaAtiva[indice]) {
                    cout << "Situacao: Ativa" << endl;
                } else {
                    cout << "Situacao: Inativa" << endl;
                }
            }
            break;
        }

        // ================= 4 - DEPOSITAR =================
        case 4: {
            int numBusca, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> numBusca;

            for (int i = 0; i < quantidadeContas && indice == -1; i++) {
                if (numeroConta[i] == numBusca) {
                    indice = i;
                }
            }

            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else if (!contaAtiva[indice]) {
                cout << "Operacao negada: a conta esta inativa." << endl;
            } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "Erro: historico de movimentacoes cheio!" << endl;
            } else {
                cout << "Valor do deposito: R$ ";
                cin >> valor;

                if (valor <= 0) {
                    cout << "Erro: o valor deve ser positivo!" << endl;
                } else {
                    saldo[indice] = saldo[indice] + valor;

                    // Registra a movimentacao
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "Deposito realizado! Novo saldo: R$ " << saldo[indice] << endl;
                }
            }
            break;
        }

        // ================= 5 - SACAR =================
        case 5: {
            int numBusca, indice = -1;
            double valor;
            cout << "Numero da conta: ";
            cin >> numBusca;

            for (int i = 0; i < quantidadeContas && indice == -1; i++) {
                if (numeroConta[i] == numBusca) {
                    indice = i;
                }
            }

            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else if (!contaAtiva[indice]) {
                cout << "Operacao negada: a conta esta inativa." << endl;
            } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                cout << "Erro: historico de movimentacoes cheio!" << endl;
            } else {
                cout << "Valor do saque: R$ ";
                cin >> valor;

                if (valor <= 0) {
                    cout << "Erro: o valor deve ser positivo!" << endl;
                } else if (valor > saldo[indice]) {
                    cout << "Erro: saldo insuficiente! Saldo atual: R$ "
                         << saldo[indice] << endl;
                } else {
                    saldo[indice] = saldo[indice] - valor;

                    // Registra a movimentacao
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "Saque realizado! Novo saldo: R$ " << saldo[indice] << endl;
                }
            }
            break;
        }

        // ================= 6 - TRANSFERIR =================
        case 6: {
            int numOrigem, numDestino;
            int indiceOrigem = -1, indiceDestino = -1;
            double valor;

            cout << "Numero da conta de origem: ";
            cin >> numOrigem;
            cout << "Numero da conta de destino: ";
            cin >> numDestino;

            // Localiza as duas contas
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numOrigem) {
                    indiceOrigem = i;
                }
                if (numeroConta[i] == numDestino) {
                    indiceDestino = i;
                }
            }

            if (indiceOrigem == -1 || indiceDestino == -1) {
                cout << "Erro: uma das contas nao foi encontrada." << endl;
            } else if (indiceOrigem == indiceDestino) {
                cout << "Erro: as contas de origem e destino devem ser diferentes." << endl;
            } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                cout << "Operacao negada: ambas as contas devem estar ativas." << endl;
            } else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                // Precisa de espaco para DOIS registros
                cout << "Erro: sem espaco no historico para registrar a transferencia!" << endl;
            } else {
                cout << "Valor da transferencia: R$ ";
                cin >> valor;

                if (valor <= 0) {
                    cout << "Erro: o valor deve ser positivo!" << endl;
                } else if (valor > saldo[indiceOrigem]) {
                    cout << "Erro: saldo insuficiente na conta de origem! Saldo: R$ "
                         << saldo[indiceOrigem] << endl;
                } else {
                    saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                    saldo[indiceDestino] = saldo[indiceDestino] + valor;

                    // Registro 1: saida na conta de origem (S)
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    // Registro 2: entrada na conta de destino (D)
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;

                    cout << "Transferencia realizada com sucesso!" << endl;
                    cout << "Saldo conta " << numeroConta[indiceOrigem] << ": R$ "
                         << saldo[indiceOrigem] << endl;
                    cout << "Saldo conta " << numeroConta[indiceDestino] << ": R$ "
                         << saldo[indiceDestino] << endl;
                }
            }
            break;
        }

        // ================= 7 - EXTRATO =================
        case 7: {
            int numBusca, indice = -1;
            cout << "Numero da conta: ";
            cin >> numBusca;

            for (int i = 0; i < quantidadeContas && indice == -1; i++) {
                if (numeroConta[i] == numBusca) {
                    indice = i;
                }
            }

            if (indice == -1) {
                cout << "Conta nao encontrada." << endl;
            } else {
                int encontradas = 0;
                cout << "\n--- EXTRATO DA CONTA " << numeroConta[indice]
                     << " (" << nomeCliente[indice] << ") ---" << endl;

                // Percorre o historico e mostra so as movimentacoes desta conta
                for (int i = 0; i < quantidadeMovimentacoes; i++) {
                    if (contaMovimentacao[i] == numeroConta[indice]) {
                        if (tipoMovimentacao[i] == 'D') {
                            cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                        } else if (tipoMovimentacao[i] == 'S') {
                            cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                        }
                        encontradas++;
                    }
                }

                if (encontradas == 0) {
                    cout << "Nenhuma movimentacao registrada." << endl;
                }
                cout << "Saldo atual: R$ " << saldo[indice] << endl;
            }
            break;
        }

        // ================= 0 - SAIR =================
        case 0:
            cout << "Encerrando o sistema. Ate logo!" << endl;
            break;

        default:
            cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0);

    return 0;
}
