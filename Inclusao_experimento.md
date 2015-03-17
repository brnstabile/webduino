# Inclusão de um experimento #


---


## CONSIDERAÇÔES ##

Sistema Operacional: Ubuntu Server 12.04

  * Definimos aqui apenas as configurações básicas para uma implementação semelhante ao ao laboratório do projeto webduino;
  * Considere que utilizamos o seguinte diretório de instalação do weblabdeusto: _/opt/weblabdeusto_;
  * Todas nossas instâncias são dispostas no diretório  _/opt/weblabdeusto/labs_;
  * As informações mais detalhadas dos procedimentos estão disponíveis em: https://weblabdeusto.readthedocs.org/en/latest/
  * Para instalação inicial da plataforma weblabdeusto utilize os documentos fornecidos pelos desenvolvedores em: https://weblabdeusto.readthedocs.org/en/latest/installation.html
  * Por ser uma plataforma recente, o weblabdeusto possui atualizações constantes o que poderá diferenciar em alguns procedimentos abaixo;

---


## PROCEDIMENTOS ##

Após a implementação e configuração de uma nova instância no weblabdeusto, necessitamos criar os experimentos para uso, e este processo é definido aqui em três passos básicos iniciando pelo nosso cliente, o qual somente acessará os experimentos que estiverem adicionados no arquivo de configuração _../client/configuration.js_. Após a inclusão das referências para os usuários, devemos criar os arquivos de configuração que o weblabdeusto irá utilizar para definir o experimento, e estes ficam no diretório _../labs/teste/exp\_machine/_, e ainda dizer ao weblabdeusto da existência deste novo experimento incluindo configurações no arquivo _/core\_machine/machine\_config.py_. Por fim, criamos as referências do experimento em nosso banco de dados através da plataforma online de administração.



### Registrar o experimento para o cliente ###
Primeiramente devemos incluir o experimento nos arquivos de cofiguração dos usuários em: _/opt/weblab/labs/teste/client/configuration.js_

Devemos incluir as configurações de acordo com a tecnologia implementada de acesso, assim para Java Applets utilizar o seguinte:

```

 "java": [
   {
    "code": "es.deusto.weblab.client.experiment.plugins.es.deusto.weblab.javadummy.JavaDummyApplet",
    "experiment.info.description": "description",
    "experiment.name": "javadummy",
    "jar.file": "WeblabJavaSample.jar",
    "height": 350,
    "width": 500,
    "experiment.category": "Dummy experiments",
    "experiment.info.link": "http://code.google.com/p/weblabdeusto/wiki/Latest_Exp_Java_Dummy",
    "message": "Note: This is not a real experiment, it's just a demo so as to show that WebLab-Deusto can integrate different web technologies (such as Java Applets in this experiment). This demostrates that developing experiments in WebLab-Deusto is really flexible.",
    "experiment.picture": "/img/experiments/java.jpg"
   },

   {
    "code": "es.deusto.weblab.client.experiment.plugins.es.deusto.weblab.javadummy.JavaDummyApplet",
    "experiment.info.description": "Descrição",
    "experiment.name": "era",
    "jar.file": "WeblabJavaEra.jar",
    "height": 350,
    "width": 500,
    "experiment.category": "Fisica",
    "experiment.info.link": "http://weblabduino.pucsp.br/experimentos/era/",
    "message": "Espectrofotometro Remoto com Arduíno",
    "experiment.picture": "/img/experiments/era.jpg"
   }

 ],

```

Preste atenção que a vírgula após a chave somente é utilizada até o penúltimo experimento, e para “encapsular” a categoria de experimento com tecnologia Java devemos utilizar um colchete e uma vírgula. Qualquer caracter incorreto neste arquivo após os usuários introduzirem seu usuário e senha, uma página em branco aparecerá.

Aqui definimos todos os experimentos disponíveis em nosso laboratório, sendo que as permissões para grupos e usuários serão definidas apenas no banco de dados.

### Registrar o experimento no sistema ###

Todo experimento possui uma pasta de configuração que irá definir sua relação e comunicação com o weblab por completo. Assim, devemos em nosso servidor alocar estas configurações no seguinte diretório:

```
/teste/exp_machine/exp_instance/
```

Este diretório aloca os arquivos de configuração dos nossos experimentos em geral, e cada experimento possui uma pasta específica com os arquivos _configuration.xml_ e _server\_config.py_, sendo que, estes diretórios deverão possuir referência no arquivo _configuration.xml_ que está no mesmo local onde estão os diretórios dos experimentos.

Adotamos como padrão de comunicação entre os experimentos e o weblab, o protocolo XmlRpcServer, com isso nossa arquitetura fica distribuída entre o servidor principal e os servidores de experimento. Assim, para definir o servidor de cada experimento, os quais irão receber os comandos enviados pelos usuários, devemos alterar os endereços IP dos campos _parameter name_ no arquivo _configuration.xml_ e a porta de conexão, veja abaixo:

```

       <protocol name="XMLRPC">
            <coordinations>
                <coordination>
                    <parameter name="address" value="192.168.42.51:40002@NETWORK" />
                </coordination>
            </coordinations>
            <creation>
                <parameter name="address" value="192.168.42.51"     />
                <parameter name="port"    value="40002" />
            </creation>
        </protocol>

```


Neste ponto os arquivos do experimento ja estão prontos, mas ainda necessitamos informar ao weblabdeusto que existem novos experimentos. Assim iremos utilizar os seguintes arquivos de configuração abaixo para incluir as informações deste novo experimento:


Define os diretórios dos experimentos
```
/teste/core_machine/laboratory1/laboratory1/server_config.py
```


Neste arquivo deverão constar os experimentos e seus diretórios.
```
##################################
# Laboratory Server configuration #
##################################

laboratory_assigned_experiments = {
        'exp1:dummy@Dummy experiments' : {
                'coord_address' : 'experiment1:exp_instance@exp_machine',
                'checkers' : ()
            },
        'exp1:era@Fisica' : {
                'coord_address' : 'era:exp_instance@exp_machine',
                'checkers' : ()
            },
        'exp2:cna@Fisica' : {
                'coord_address' : 'cna:exp_instance@exp_machine',
                'checkers' : ()
            },


    }
```



Registra o experimento no sistema e atribui uma fila
```
/core_machine/machine_config.py
```


Este arquivo possui a configuração completa do sistema, desde a referência ao banco de dados como também os experimentos. Sendo que para os experimentos, devemos referenciar os gerenciadores de filas de espera os quais irão alocar os usuários. Estas são criadas dentro do parãmetro _core\_scheduling\_systems_ como segue abaixo:

```
core_scheduling_systems = {
        'dummy'            : ('PRIORITY_QUEUE', {}),
        'robot_external' : weblabdeusto_federation_demo,
        'Fisica'               : ('PRIORITY_QUEUE', {}),
    }

```

Com os gerenciadores de filas criados devemos incluir os experimentos no sistema no parâmetro _core\_coordinator\_laboratory\_servers_ como segue abaixo

```
core_coordinator_laboratory_servers = {
    'laboratory1:laboratory1@core_machine' : {
            'exp1|dummy|Dummy experiments'        : 'dummy1@dummy',
            'exp1|era|Fisica'                     : 'exp1@Fisica',
            'exp2|cna|Fisica'                     : 'exp2@Fisica',
        },

}


```

Reparem que as denominações do experimento são as mesmas que utilizamos no arquivo _server\_config.py_ no diretório _core\_machine/laboratory1/laboratory1/server\_config.py_.

Neste ponto temos o novo experimento integrado ao sistema, faltando somente liberar acesso pelo banco de dados.

### Registrar o experimento no banco de dados ###

O conteúdo abaixo foi extraído e traduzido e readaptado dos documentos fornecidos pelos desenvolvedores do weblabdeusto.

Neste ponto nós temos o servidor de experimento em execução e o cliente configurado, o laboratório está registrado com as filas, e a localização dos experimentos na rede é conhecida. Agora nós necessitamos fazer nosso experimento acessível aos usuários, adiconando as permissões à este experimento para os usuários ou grupos. Isto é realizado acessando a plataforma com o usuário _admin_ e senha _password_, assim no canto superior direito o ícone abaixo irá aparecer no canto superior direito.



Clicando neste você visualizará a página abaixo:

Vá em _Experiments/Experimentos_, depois em _Categories/Categorias_ e _Create/Criar_. Você pode criar uma nova categoria de experimento, caso nenhuma ainda existe, como por exemplo _Eletronics Experiments_, e clique em _Submit/Enviar_:

Agora volte para a guia _Experiments/Experimentos_ e depois em _Create/Criar_. Você poderá adicionar um novo experimento, como _electronics_, utilizando a categoria recentemente criada. A data inicial e final reference-se ao tempo que este será disponível.

Neste momento, o laboratório foi adicionado no banco de dados.Agora você irá forncer as permissões aos usuários. ENtão para realizar isto, clique em _Permissions/Permissões e_Create/Criar_. Selecione quem irá receber a permissão (Type of recipient - Tipo do beneficiário) e_experiment\_allowed_.
Agora o usuário ou grupo o qual recebeu a permissão está habilitado a acessar o novo experimento através da interface principal._






## Observações ##

  1. Quando atribuimos servidores de experimento para recepção dos comandos, devemos iniciá-los antes do weblabdeusto, para que este encontre nosso servidor de experimento. Caso alguma exista alguma falha de comunicação entre o sistema prinpical e este sub servidor, ao reservar o experimento o sistema no informará que este está indisponível.

  1. Em geral, o diretório ao qual será acessível pelos usuários será o _/usr/local/lib/python2.7/dist-packages/weblabdeusto-5.0-py2.7.egg/weblabdeusto\_data/war/weblabclientlab_ , assim quando necessitar atualizar a aplicação cliente, podemos substituir as aplicações neste diretório.