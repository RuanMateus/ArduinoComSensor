import serial                   # importe da biblioteca Pyserial
from datetime import datetime   # importe do módulo datetime


porta = "COM3"                      # Definindo a variável porta no qual o arduino está conectado. Obs.: COM3 e a porta USB do PC mostrado pela IDE do arduino
baud = 9600                         # Definindo a taxa de dados chamada de "baud rate" com o valor armazenado em bits por segundo
arquivo = "BPM-EsforcoFisico.csv"   # Definindo o arquivo csv que irá receber os dados

ser = serial.Serial(porta,baud)     # Inicializando o objeto serial com parâmetros
ser.flushInput()                    # Limpando dados da serial
print("Abrindo Serial")             # Imprime a mensagem em parâmetro

amostra = 100                                           # Definindo o valor de amostras que se deseja obter na variável amostra
linha = 0                                               # Definindo o controle de linha com a variável linha

while linha <= amostra:                                 # loop para ler os dados

    data = str(ser.readline().decode("utf-8"))          # Lendo os dados (Batimentos) enviados do arduino e transformando para string
    file = open(arquivo,"a")                            # Abrindo o arquivo csv com parâmetro de criação
    now = datetime.now()                                # Mostra a data e hora atual em tempo de execução 
    dataHora = now.strftime("%d/%m/%Y,%H:%M:%S")        # Armazenando a data e hora atual na variável dataHora formatado dessa forma, exemplo: 01/01/2000,01:01:01
    print(data)                                         # Imprime no terminal o dado do Batimento Cardíaco enviado pelo arduino
    file.write(dataHora + "," + data)                   # Adiciona os dados ao arquivo csv
    linha = linha+1                                     # Iteração da variável linha

print("Fim da Leitura!")                                # Imprime a mensagem em parâmetro
file.close()                                            # Fecha o arquivo csv
ser.close()                                             # Fecha a serial