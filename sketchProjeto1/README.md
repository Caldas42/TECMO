# T.E.C.M.O. - Treinamento em Educação Computacional com o Módulo de Orientação

## Índice

1. [Descrição]
2. [Configuração]
3. [Circuito]
4. [Código]
5. [Como usar]

## 1. Descrição

O TECMO é um dispositivo físico voltado para a inserção de pessoas no mercado de tecnologia através da gamificação da montagem de uma placa mãe. Onde o jogador responde perguntas em formatos de quiz encaixando as peças correspondentes a descrição na tela até o TECMO ser montado por completo.

## 2. Configuração

Passo a passo de instalação e configuração:

1. Instale o Arduino IDE para abrir o código: (https://www.arduino.cc/en/software).
2. Instale o Driver Serial: (https://www.blogdarobotica.com/2021/03/12/instalando-o-driver-serial-para-arduino/).
3. Plugue o cabo USB em seu computador e compile o código no Arduino.
4. Mantenha conectado ao computador ou fornece uma bateria ao Arduino para funcionar.

## 3. Circuito

Certifique-se que tenha o circuito do TECMO em pleno funcionamento, cheque todos os componentes (LED's, LDR's, botões e tela). Para aprender a montá-lo siga o link a seguir: (https://docs.google.com/document/d/1DzoTNUN6WK5v0u0mfZcjHKdOyG05aTmQ2v2y2HCyb1s/edit?usp=sharing)

## 4. Código

O código tem três seções principais, primeiro a seleção de dificuldade que retorna um inteiro, segundo esse inteiro será checado para mostrar a pergunta correspondente a dificuldade e depois um "while (true)" que checa os sensores de luz e acende a luz correspondente a resposta (verde correto e vermelho incorreto) quando a peça certa for encaixada o LED verde acende e a próxima pergunta é printada na tela até todo o TECMO estar montado.

## 5. Como usar

Para usar o TECMO é simples, selecione a dificuldade entre os botões e encaixe a peça correspondente a descrição que aparece na tela. Não encaixe duas peças ao mesmo tempo e quando encaixar a peça correta deixe-a encaixada até o TECMO ser montado completamente. Quando o jogo terminar, retire todas as peças antes de jogar novamente.