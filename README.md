# DSW-painel-arduino-lib
A biblioteca oficial para se fazer um Painel personalizado com software DSW painel pro

baixe o arquivo ZIP e coloque sua ide arduino de preferência 1.8.x

ela é simples apenas 3  funções

".vai()" deve ser chamada só uma vez para iniciar ela

".atualizar()" vai procurar por atualizações lá no aplicativo

".puxa( valor de 0 a 19)" para você puxar os valores dos slots configurados no aplicativo

veja um exemplo para fazer um shift light

<pre>
 &nbsp;&nbsp;&nbsp;<font color="#00979c">String</font> <font color="#000000">value</font> <font color="#434f54">=</font> <font color="#000000">dsw</font><font color="#434f54">.</font><font color="#000000">puxa</font><font color="#000000">(</font><font color="#000000">0</font><font color="#000000">)</font><font color="#000000">;</font>

</pre>
