# DSW-painel-arduino-lib
A biblioteca oficial para se fazer um Painel personalizado com software DSW painel pro

baixe o arquivo ZIP e coloque sua ide arduino de preferência 1.8.x
caso arduino IDE não consiga reconhecer

![image](https://github.com/user-attachments/assets/97f435ac-160c-4b6a-a895-68f197ff94ef)

pegue essa biblioteca e arraste os seus documentos > arduino > libraries | 

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

você deverá colocar o  slot zero para ser RPM e isso vai funcionar quando o giro passar 1244 ele vai acender aquele LED que fica na porta 13 do arduino 
