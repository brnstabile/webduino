# Criando uma instância de laboratório #


---


## CONSIDERAÇÔES ##

Sistema Operacional: Ubuntu Server 12.04

  * Definimos aqui apenas as configurações básicas para uma implementação semelhante ao ao laboratório do projeto webduino;
  * Considere que utilizamos o seguinte diretório de instalação do weblabdeusto: [/opt/weblabdeusto];
  * Todas nossas instâncias são dispostas no diretório  [/opt/weblabdeusto/labs];
  * As informações mais detalhadas dos procedimentos estão disponíveis em: https://weblabdeusto.readthedocs.org/en/latest/
  * Para instalação inicial da plataforma weblabdeusto utilize os documentos fornecidos pelos desenvolvedores em: https://weblabdeusto.readthedocs.org/en/latest/installation.html
  * Por ser uma plataforma recente, o weblabdeusto possui atualizações constantes o que poderá diferenciar em alguns procedimentos abaixo;

---


## PROCEDIMENTOS ##

Este é o primeiro passo que deve ser realizado após a instalação do weblabdeusto, a criação de um laboratório que irá conter nossos experimentos, configurações dos protocolos de comunicação e sistemas de filas e usuários.

Abaixo referenciamos como criar uma instância completa para uso do weblabdeusto da mesma maneira como implementamos o laboratório do webduino. Vamos criar esta instância com comunicação na porta de acesso 20000, ou seja a _URL_ será http://localhost:20000 inicialmente, protocolo HTTPS habilitado, _XMLRPC_ para comunicação entre o servidor principal e o primeiro experimento através da porta 40000, as sessões serão coordenadas com a tecnologia _SQL_, e o banco de dados de usuários e experimentos será implementado em _MySQL_.

Primeiramente devemos criar o banco de dados que armazenará os dados desta nova instância, e posteriormente podemos executar o comando abaixo fornecendo os dados do banco de dados criado:

```
weblab-admin create {nome da instancia} --http-server-port=20000 --enable-https --xmlrpc-experiment --xmlrpc-experiment-port=40000 --session-storage=sql --db-engine=mysql --db-name=weblab --db-user=root --db-passwd={senha}
```

Ainda que utilizamos todos estes parâmetros para implementação de uma nova instância, podemos realizar alterações caso necessário, como por exemplo as portas de conexão dos experimentos, podem ser facilmente alteradas no seguinte diretório:

```
/opt/weblabdeusto/instancia/core_machine/
```

Agora que possuímos nossa instâncias personalizada, podemos executa-la através do comando abaixo:

```
weblab-admin start instancia -m core_machine
```

Podemos perceber que o comando _weblab-admin_ é o principal para executar ações no weblabdeusto, assim para conhecer as demais digite-o sem nenhum parâmetro:

```
weblab-admin
```

O mesmo pode ser feito para o parâmetro create:

```
weblab-admin create
```