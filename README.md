# sudokuBBB_T3
**Projeto desenvolvido por alunos de Tecnologia da Informação da UFRN para a disciplina de Sistemas Operacionais**

####PROFESSOR
Ivanovitch Medeiros Dantas da Silva 

####AUTORES: 
Francleide Simão e José Victor Andrade

####O PROJETO
O projeto irá utilizar funções de processos (fork), sinal (signal), alarme (alarm) e uma BeagleBone com led RGB.
####OBJETIVO
O objetivo do projeto é gerar um jogo de Sudoku utilizando processos onde o processo filho é responsável por executar o jogo, o processo pai é responsável pelo gerenciamento do alarme, sinal e o componente led RGB conectado a BeagleBone. O led RGB é responsável por indicar visualmente o tempo que resta para desvendar o sudoku. O tempo é controlado pela função alarme. O sinal serve para finalizar o filho caso o alarme chegue ao limite.

####IMPLEMENTAÇÃO
<p>A implementação foi feita utilizando a linguagem C++, a biblioteca BlackGPIO e na BeagleBone com o sistema operacional linux.<br>
<a href="https://github.com/francleide/sudokuBBB_T3/blob/master/sudoku.cpp">Código do Projeto</a>

######EXECUÇÃO
Para executar baixe os arquivos e depois abra o terminal do linux. Navegue até a pasta em que está o arquivo sudoku.cpp e execute o código:<br>
<code>g++ sudoku.cpp - o [um nome]</code><br>
pressione ENTER e depois execute:<br>
<code>./[um nome]</code> <br>
pressione ENTER e o programa será executado.<br>
Para pará-lo antes do tempo pressione:<br>
<code>Ctrl + z</code><br>
ou digite em outro terminal: <br>
<code>kill -9 [numero do processo que deseja "matar"]</code>

####VÍDEO
