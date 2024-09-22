> site ofc > https://dsw-wheel.rf.gd/
> 
> discord  > https://discord.gg/8cFE527m9p
# DSW-painel-arduino-lib
A biblioteca oficial para se fazer um Painel personalizado para jogos de corrida com software DSW painel pro 
obtido em  > https://dsw-wheel.rf.gd/baxada.html?i=1

baixe o arquivo ZIP e coloque sua ide arduino de preferência 1.8.x na nova atualização está funcionando corretamente no IDE V2.x.x

nossa biblioteca é oficial no gerenciador de bibliotecas do IDE veja
![image](https://github.com/user-attachments/assets/358ba4a6-18a7-4e3c-966d-f5ad565d83a2)

pode instalar por aí normal!
Espere... espere... detenham a contagem ! caso você não conseguiu conectar a placa no sofware novo void setup coloque o comando '''c++ Serial.begin(115200);'''
![image](https://github.com/user-attachments/assets/a9f79b36-7019-405e-a8b1-46be5ae3db82)


ela é simples apenas 3  funções

".vai()" deve ser chamada só uma vez para iniciar ela

".atualizar()" vai procurar por atualizações lá no aplicativo

".puxa( valor de 0 a 19)" para você puxar os valores dos slots configurados no aplicativo mas lembre que no arduino slots começam de 0 a 19 e no software de 1 a 20 
ou seja se você configurou o slot 14 aqui no arduíno você vai ter que colocar o número 13 para puxar ele


veja um exemplo para fazer um shift light

<pre>
<font color="#5e6d03">#include</font> <font color="#434f54">&lt;</font><font color="#000000">dswpainelpro</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>

<font color="#000000">DSWPainelPro</font> <font color="#000000">dsw</font><font color="#000000">;</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>

 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">vai</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">13</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47; Configura o pino como saída</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">atualizar</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47; Atualiza os valores Com o que tiver disponível </font>
 &nbsp;&nbsp;&nbsp;
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Obtém o valor do slot 0 e imprime</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">String</font> <font color="#000000">value</font> <font color="#434f54">=</font> <font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">puxa</font><font color="#000000">(</font><font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#00979c">int</font> <font color="#000000">intensity</font> <font color="#434f54">=</font> <font color="#000000">value</font><font color="#434f54">.</font><font color="#d35400">toInt</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#00979c">int</font> <font color="#000000">libata</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">intensity</font> <font color="#434f54">&gt;=</font> <font color="#000000">1244</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">libata</font> <font color="#434f54">=</font> <font color="#000000">255</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">libata</font> <font color="#434f54">=</font> <font color="#000000">0</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#000000">}</font>
 &nbsp;&nbsp;&nbsp;
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Ajusta a intensidade do LED</font>
 &nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">13</font><font color="#434f54">,</font> <font color="#000000">libata</font><font color="#000000">)</font><font color="#000000">;</font>

 &nbsp;&nbsp;&nbsp;<font color="#d35400">delay</font><font color="#000000">(</font><font color="#000000">1</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47; Aguarde um tanto </font>
<font color="#000000">}</font>

</pre>

você deverá colocar o  slot 1 para ser RPM e isso vai funcionar quando o giro passar 1244 ele vai acender aquele LED que fica na porta 13 do arduino 

# novas atualizações novas funções ! V 1.2.4 
> cmd < um sistema de envio de comandos foi adicionado percebemos a gente precisava mudar variaveis toda hora e ficar enviando o código novamente então desenvolvemos esse sistema bem simples
 novas funções foram adicionadas observe.
> OBS . Ainda é necessário chamar a função " dsw.atualizar(); " para que o sistema se atualize !
> 
> para iniciar o sistema de CMD é bem simples chame essa funçao no setup "   dsw.cmd_vai(comandos, numComandos);" passando uma listagem de comandos o número de comandos existentes lembrando que obrigatoriamente todo o comando deve começar com uma " / " se não ele não vai funcionar!
> 
> para você poder puxar o valor de um comando atual você pode utilizar "dsw.cmd_puxada("/led")" como nesse exemplo passando o nome do comando que ele vai retornar um float
> 
> outro problema surgiu como vamos saber quando o comando for validado ? então fizemos um sistema de chamadas defina "dsw.cmd_chamarisco()"  passando uma função que você vai criar no código que ela vai ser chamada toda vez que um comando for validado !
ela vai passar 2 variáveis uma de "comando" string e um int do "valor" o que você pode fazer para saber qual comando foi enviado observe o exemplo abaixo que também está nos exemplos da biblioteca
<pre>
<font color="#5e6d03">#include</font> <font color="#005c5f">&#34;dswpainelpro.h&#34;</font>

<font color="#000000">DSWPainelPro</font> <font color="#000000">dsw</font><font color="#000000">;</font>

<font color="#434f54">&#47;&#47; Função de callback que será chamada quando um comando for recebido</font>
<font color="#00979c">void</font> <font color="#000000">meuCallback</font><font color="#000000">(</font><font color="#00979c">String</font> <font color="#000000">command</font><font color="#434f54">,</font> <font color="#00979c">int</font> <font color="#000000">valuer</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#95a5a6">&#47;*</font>
<font color="#95a5a6"> &nbsp;essa disponibiliza de 2 variáveis uma do comando que foi validado e um valor inteiro do valor</font>
<font color="#95a5a6"> &nbsp;pode ver que logo abaixo a gente verificou se o comando é &#34;&#47;led&#34; e depois foi dado outro exemplo de como usar o comando</font>
<font color="#95a5a6"> &nbsp;&#34;&#34;cmd_puxada&#34;&#34; &nbsp;que retorna um valor float do comando selecionado dentro dele por uma string </font>
<font color="#95a5a6"> &nbsp;Apenas para exemplificar mas como a gente já precisa do valor como inteiro a gente podia apenas usar</font>
<font color="#95a5a6"> &nbsp;&#34;&#34;valuer&#34;&#34; aqui no caso que foi definido com a variável de retorno de valor do callback</font>
<font color="#95a5a6"> &nbsp;&gt;PLUS esse CMD nao necessita realmente do proprietário dentro do aplicativo o do próprio Arduino IDE ele já funcionará</font>
<font color="#95a5a6"> &nbsp;*&#47;</font>

 &nbsp;&nbsp;<font color="#5e6d03">if</font> <font color="#000000">(</font><font color="#000000">command</font> <font color="#434f54">==</font> <font color="#005c5f">&#34;&#47;led&#34;</font><font color="#000000">)</font><font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#d35400">analogWrite</font><font color="#000000">(</font><font color="#000000">13</font><font color="#434f54">,</font> <font color="#000000">(</font><font color="#00979c">int</font><font color="#000000">)</font><font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">cmd_puxada</font><font color="#000000">(</font><font color="#005c5f">&#34;&#47;led&#34;</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#000000">eepromManager</font><font color="#434f54">.</font><font color="#000000">eeprom_salvar</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#95a5a6">&#47;*</font>
<font color="#95a5a6">aproveitando o embalo vamos apresentar a função &#34;&#34;slynky&#34;&#34; que serve para você fazer um retorno personalizado para o prompt de comando</font>
<font color="#95a5a6">você pode enviar qualquer string de apenas &nbsp;strings</font>
<font color="#95a5a6"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*&#47;</font>
 &nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">slynky</font><font color="#000000">(</font><font color="#005c5f">&#34; o valor do LED foi atualizado com sucesso!! &gt; exemplo de uso da função slynky !!&lt;&#34;</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;
 &nbsp;&nbsp;<font color="#000000">}</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;
 &nbsp;&nbsp;&nbsp;<font color="#d35400">pinMode</font><font color="#000000">(</font><font color="#000000">13</font><font color="#434f54">,</font> <font color="#00979c">OUTPUT</font><font color="#000000">)</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47; Configura o pino 13 como saída (Esse pino Além de ser o pino digital 13 também é conectado a um LED que tem a letra &#34;L&#34; na placa )</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">String</font> <font color="#000000">comandos</font><font color="#000000">[</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#000000">{</font><font color="#005c5f">&#34;&#47;start&#34;</font><font color="#434f54">,</font> <font color="#005c5f">&#34;&#47;stop&#34;</font><font color="#434f54">,</font> <font color="#005c5f">&#34;&#47;reset&#34;</font><font color="#434f54">,</font><font color="#005c5f">&#34;&#47;led&#34;</font><font color="#000000">}</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">int</font> <font color="#000000">numComandos</font> <font color="#434f54">=</font> <font color="#000000">4</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; inicia a funcionalidade do prompt de comando !</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; definindo os comandos numa lista e o número de comandos</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">cmd_vai</font><font color="#000000">(</font><font color="#000000">comandos</font><font color="#434f54">,</font> <font color="#000000">numComandos</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;&#47;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Registra a função de callback</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; esse &#34;callback&#34; é uma função que você pode declarar que quando um comando for validado ou seja o software</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; enviou um comando que existe ele irá chamar uma função se você quiser claro você pode ver abaixo que foi definido uma função</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47;&#34;&#34;meuCallback&#34;&#34; que nesse código foi criado no início</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">cmd_chamarisco</font><font color="#000000">(</font><font color="#000000">meuCallback</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;<font color="#434f54">&#47;&#47; atualiza os valores mais recentes enviados do Software</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">atualizar</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#000000">}</font>

</pre>
outro problema surgiu e nós resolvemos após enviar um comando  processaria vai tudo funcionar até você desligar placa ! Quando ligar novamente todas as configurações feitas vão ser perdidas então como resolver esse problema adicionamos um sistema de manejamento de EEPROM !

Observe é fácil de utilizar

basta iniciar dsw_eeprom "dsw_eeprom eepromManager(variaveis, tipos, 2);" passando uma listagem para ele das variáveis uma listagem dos tipos e o número de variáveis que você colocou
a listagem de tipos na mesma ordem da listagem das variáveis você vai colocar uma string "i" ou "f" para dizer a tipologia inteiro ou float
depois tem 2 funções que vão fazer o sistema salvar ou carregar ao salvar e carregar ele faz o salvamento e o carregamento de todas as variáveis ao mesmo tempo

salvar   > eepromManager.eeprom_salvar();

carregar > eepromManager.eeprom_puxar();

veja um pequeno exemplo completo!
<pre>
<font color="#5e6d03">#include</font> <font color="#005c5f">&#34;dswpainelpro.h&#34;</font>

<font color="#434f54">&#47;&#47; Variáveis globais para serem armazenadas na EEPROM ( as variáveis que vamos utilizar no nosso exemplo )</font>
<font color="#00979c">int</font> <font color="#000000">contador</font> <font color="#434f54">=</font> <font color="#000000">1234</font><font color="#000000">;</font> &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Exemplo de um inteiro</font>
<font color="#00979c">float</font> <font color="#000000">temperatura</font> <font color="#434f54">=</font> <font color="#000000">23.5</font><font color="#000000">;</font> <font color="#434f54">&#47;&#47; Exemplo de um float</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Array de variáveis que serão salvas ( aqui vamos colocar o nome das variáveis que nós vamos querer trabalhar)</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">void</font><font color="#434f54">*</font> <font color="#000000">variaveis</font><font color="#000000">[</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#000000">{</font> <font color="#434f54">&amp;</font><font color="#000000">contador</font><font color="#434f54">,</font> <font color="#434f54">&amp;</font><font color="#000000">temperatura</font> <font color="#000000">}</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Array com os tipos dessas variáveis (&#39;i&#39; para int, &#39;f&#39; para float) | ( faça com respectividade ou seja a definição deve estar na mesma ordem que você definiu o nome das variáveis)</font>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">char</font> <font color="#000000">tipos</font><font color="#000000">[</font><font color="#000000">]</font> <font color="#434f54">=</font> <font color="#000000">{</font> <font color="#00979c">&#39;i&#39;</font><font color="#434f54">,</font> <font color="#00979c">&#39;f&#39;</font> <font color="#000000">}</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Instancia o objeto para manipular a EEPROM( agora basta chamar a biblioteca com os dados que nós temos definindo nessa ordem a lista de variáveis lista de tipos e também coloque o valor da quantidade de variáveis que você definiu como pode observar nós temos 2 um número 2 foi colocado)</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">dsw_eeprom</font> <font color="#000000">eepromManager</font><font color="#000000">(</font><font color="#000000">variaveis</font><font color="#434f54">,</font> <font color="#000000">tipos</font><font color="#434f54">,</font> <font color="#000000">2</font><font color="#000000">)</font><font color="#000000">;</font>
<font color="#434f54">&#47;&#47;=========================================================================================================================================</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Salva os valores na EEPROM</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">eepromManager</font><font color="#434f54">.</font><font color="#000000">eeprom_salvar</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; toda vez que ela for chamada ela vai pegar o valor das variáveis e salvar na eeprom mesmo que o Arduino for desligado os valores não são perdidos</font>
<font color="#434f54">&#47;&#47;=========================================================================================================================================</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Puxa os valores da EEPROM para as variáveis</font>
 &nbsp;&nbsp;&nbsp;<font color="#000000">eepromManager</font><font color="#434f54">.</font><font color="#000000">eeprom_puxar</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; toda vez que acionada ela vai pegar aqueles valores que estão salvo na eeprom e redefinir eles nas variáveis respectivas, aquelas que foram definidas no início do código obvio</font>
<font color="#434f54">&#47;&#47;=========================================================================================================================================</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#95a5a6">&#47;*</font>
<font color="#95a5a6">sugestão de uso&lt;</font>
<font color="#95a5a6">você pode usar em conjunto do CMD inclusive foi feito para isso no caso !</font>
<font color="#95a5a6">Ao receber um novo comando e processado utilize essa biblioteca para salvar</font>
<font color="#95a5a6">os comandos após processar os comandos chame a função</font>
<font color="#95a5a6"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{.eeprom_salvar();}</font>
<font color="#95a5a6">que ela vai fazer o salvamento e &nbsp;na função &#34;setup&#34; chame</font>
<font color="#95a5a6"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{.eeprom_puxar();}</font>
<font color="#95a5a6">Que toda vez que o arduino religar ele vai puxar o valor das variáveis na última salvação!</font>
<font color="#95a5a6"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*&#47;</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> <font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;<font color="#434f54">&#47;&#47; Não é necessário fazer nada no loop para este exemplo</font>
<font color="#000000">}</font>

</pre>

essas foram as novas funcionalidades adicionais colocamos também mais exemplos você pode ir no menu de exemplos do seu arduínoIDE e verá vários exemplos utilizando o comando e a EEPROM ao mesmo tempo
utilizando o SERVOS também ! 

obs > tem uma função que pode ser muito útil nos testes "dsw.slynky("oi");" slynky pode ser chamada junto a uma string ela vai fazer um log, se você estiver com "cmd" ou "serial view" do arduino IDE aberto na hora que ela for acionada poderá ser visto o que ela enviou!
