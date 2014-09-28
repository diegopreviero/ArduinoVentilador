ArduinoVentilador
=================

Projeto de automação Residencial.
Nesse projeto utilizo um módulo rele com quatro reles de 12 volts e um display de LCD de 16x2 para exibir as informações de controle.
O módulo rele é utilizado para ligar e desligar o ventilador e determinar o sentido de rotação das pás alternando entre três velocidades para cada sentido.
A velocidade de giro das pás é determinada pela ativação dos capacitores, sendo 4uf velocidade mínima, 6uf velocidade média e 4uf + 6uf velocidade máxima.
O controle do módulo se dá através de infra vermelho utilizando um controle de DVD player no qual foi realizado o mapeamento das teclas para obtençao dos códigos, os quais foram inseridos no código fonte do projeto para que o arduino possa fazer a leitura.
