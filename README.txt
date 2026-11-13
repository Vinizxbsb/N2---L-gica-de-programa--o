================================================================================
PETCONTROL - SISTEMA DE GESTAO DE PET SHOP E CLINICA VETERINARIA
Disciplina: Logica de Programacao em C (UCB)
================================================================================

1. DESCRICAO DO PROJETO
Software de terminal desenvolvido em linguagem C padrao para apoiar a operacao
de um pet shop e clinica veterinaria. Permite o cadastro e consulta de tutores
e animais, registro de atendimentos com calculo automatico de valores,
alteracao cadastral via ponteiros e geracao de relatorio gerencial da sessao.

2. INTEGRANTES DO GRUPO
- Ana Luíza Neres Wagner - UC26200253
- Daniel Vieira de Oliveira - UC26200124
- Yan Paulo de Menezes Silva - UC26200367
- Vinícius e Silva Lopes - UC26200366


3. REQUISITOS DE AMBIENTE
- Compilador C padrao (GCC, MinGW ou Clang)
- Terminal / Prompt de Comando (Windows, Linux ou macOS)

4. INSTRUCOES DE COMPILACAO E EXECUCAO
Abra o terminal na pasta onde se encontra o arquivo "main.c" e execute:

- No Linux / macOS:
  gcc main.c -o petcontrol -Wall
  ./petcontrol

- No Windows (CMD / PowerShell com MinGW):
  gcc main.c -o petcontrol.exe -Wall
  petcontrol.exe

5. FUNCIONALIDADES DISPONIVEIS NO MENU
[1] Cadastrar tutor (gera codigo sequencial, valida CPF unico de 11 digitos)
[2] Cadastrar animal (vincula a um tutor existente, valida especie e idade)
[3] Listar tutores
[4] Listar animais
[5] Listar animais por tutor (filtro relacional pelo codigo do tutor)
[6] Buscar tutor por codigo
[7] Alterar dados do tutor (atualiza nome e telefone via ponteiro para struct)
[8] Buscar animal por codigo
[9] Registrar atendimento (catalogo de 4 servicos, calculo por quantidade)
[10] Exibir relatorio da sessao (total de atendimentos, faturamento e servicos)
[0] Sair do sistema

6. OBSERVACOES TECNICAS
- Os dados sao mantidos em memoria RAM durante a execucao (vetores estaticos).
- Limites configurados: 50 tutores, 50 animais e 100 atendimentos.
- Todas as entradas passam por funcoes seguras (fgets + strtol) para evitar
  falhas de buffer ou encerramento inesperado por digitacao invalida.
================================================================================