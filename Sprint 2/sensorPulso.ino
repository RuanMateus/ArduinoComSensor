
int pin = A0;               // Definido o pino A0 como "pin"

float valorAnterior = 0;    // Definindo a variável que armazenará o valor da leitura anterior 
float valorMaximo = 0.0;    // Definindo a variável que armazenará 97% do valor máximo obtido
int quantidadeBatidas = 0;  // Definindo a variável que armazenará a quantidade de batimentos

float fatorFiltro = 0.75;   // Coeficiente para o filtro do valor analógico obtido durante a leitura
int minimoEntreBatidas = 300;   // Valor mínimo de tempo entre os batimentos cardíacos

long entreBatidas = millis();   // Definindo a variável local que armazenará o tempo entre os batimentos
long tempoBPM = millis();       // Definindo a variável local "tempo de batimentos por minuto em milissegundos

void setup() {
  Serial.begin(9600);           // Inicializando o monitor serial
  Serial.println("BPM");        // Imprime no monitor serial a mensagem que está sendo passada como parâmetro
}

void loop() {
  int valorLido = analogRead(pin);    // Realizando a leitura do pino denominado A0

  float valorFiltrado = fatorFiltro * valorAnterior + (1 - fatorFiltro) * valorLido;    // Realizando a filtragem do sinal analógico
  float valorDiferenca = valorFiltrado - valorAnterior;         // Calculando a diferença entre a variavel valorFiltrado e valorAnterior

  valorAnterior = valorFiltrado;          // Atualizando a variavel valorAnterior com o valor da variável valorFiltrado

  if ((valorDiferenca >= valorMaximo) &&            // Verificando se a variavel valorDiferenca é maior que a variável valorMaximo
    (millis() > entreBatidas + minimoEntreBatidas)  // E se o tempo atual é maior que a soma do tempo da última batida detectada e o tempo mínimo entre as batidas
  ) {
    valorMaximo = valorDiferenca;                   // Armazena na variável valorMaximo o valor da variável valorDiferenca
    entreBatidas = millis();                        // Armazena o momento atual em milissegundos na variável entreBatidas
    quantidadeBatidas++;                            // Incrementa mais um ao valor armazenado na variável quantidadeBatidas
  }

  valorMaximo = valorMaximo * 0.97;                 // Atualizando o valor da variável valorMaximo com 97% do valor da variavel valorDiferenca

  if (millis() >= tempoBPM + 15000) {               // Verificando se já se passaram 15 segundos para mostrar a quantidade de batimentos por minuto
    Serial.println(quantidadeBatidas * 4);          // Imprime no monitor serial a quantidade de batidas multiplicadas por 4, pis a cada 15 segundos temos 1/4 do minuto
    tempoBPM = millis();                            // Armazena o momento atual em milissegundos na variável tempoBPM
    quantidadeBatidas = 0;                          // Atualizando a variavel quantidadeBatidas com o valor zero para iniciar uma nova contagem 
  }

  delay(50);                                        // Parando a execução do código por 50 milissegundos
}



