# Configurações para o Servidor de Experimentos #


---


## CONSIDERAÇÔES ##

Sistema Operacional: Raspbian

  * Definimos aqui apenas as configurações básicas para uma implementação semelhante ao ao laboratório do projeto webduino;
  * As informações mais detalhadas dos procedimentos estão disponíveis em: https://weblabdeusto.readthedocs.org/en/latest/
  * Realize a instalação da aplicação _vim_ para auxiliar neste procedimento;


---


## PROCEDIMENTOS ##

Para o servidor de experimento utilizamos um Raspberry Pi com distribuição Linux Debian como sistema operacional. Entretando qualquer outro sistema ou dispositivo que possua a plataforma JRE - Java Runtime Enviroment poderá servir como servidor de experimento. Pois em suma, o servidor de experimento é a aplicação Java XML-RPC desenvolvida e exportada na etapa de desenvolvimento [Desenvolvendo\_aplicacoes](http://code.google.com/p/weblabduino/wiki/Desenvolvendo_aplicacoes).

Assim, após constatar que podemos executar aplicações _.jar_ em nosso servidor de experimentos, podemos incluí-lo junto à inicilização do sistema. Pois com isso, caso ocorrer uma queda de energia e o desligamento instantaneo do sistema, ao religa-lo as aplicações servidoras de experimentos irão inicializar automaticamente.

Para incluir uma aplicação na inicilização de sistemas baseados no Debian, primeiramente necessitamos criar um bash-script com o comando que irá executar o arquivo Java. Fazemos isto criando um arquivo com o seguinte comando no _Terminal/Bash_ do sistema com usuário administrador _root_:

```
vim experimentoServer.sh
```

A extensão _.sh_ representa um arquivo shell script.

Neste arquivo devemos colocar o conteudo referente a execução do servidor _.jar_ e ainda os parâmetros necessários para o sistema reconhecer este script na inicilização do sistema. Apresentamos o conteúdo abaixo como uma exemplo:

```
### BEGIN INIT INFO
# Provides: JavaXmlRpcServer
# Required-Start: $all
# Required-Stop:
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: Start JavaXmlRpcServer
### END INIT INFO


#! /bin/bash

nohup java -jar /home/pi/JavaXmlRpcServer.jar &


exit 0
```

Para introduzir este conteúdo através do vim pressione a tecla _Insert_ e cole o conteúdo com as teclas _Ctrl+Shift+V_. A tecla _Shift_ é neceessária para copiar e colar itens no bash. Certifique-se para que o arquivo _.jar_ esteja no diretório correto, assim como suas informações.

Observe que o comando _java -jar /home/pi/JavaXmlRpcServer.jar_ seria o sufiente para executar a aplicação, entretanto o bash ficaria "preso" à esta aplicação, e se tentarmos "libera-lo" desta, a aplicação se encerraria. Com isso utilizamos o _nohup_ e o parâmetro _&_, que irá criar um processo com PID próprio para nossa aplicação, liberando o bash.

Para salvar este script pelo vim pressione o botão _:_ e digite _wq_ que correspondem à _write/escrever_ e _quit/fechar_. Para que scripts bash possam ser executados no sistema necessitamos ainda altera-los como arquivo executável através do comando abaixo:

```
chmod +x experimentoServer.sh
```

Mova este arquivo para o diretório _/etc/init.d/_.

Agora só precisamos atualizar no sistema operacional as aplicações que irão inicializar através do comando abaixo:

```
update-rc.d experimentoServer.sh defaults
```

Reinicie o computador e verifique se a aplicação _JavaXmlRpcServer.jar_ está em execução no gerenciador de tarefas do sistema, sendo no linux com comando abaixo e usuário administrador:

```
ps -x | grep .jar
```