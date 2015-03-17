# Client Side #

Instalar o GWTC plugin para o Eclipse no link

> Eclipse 3.7 (Indigo)

http://dl.google.com/eclipse/plugin/3.7


## Compilar o GWTC ##

```
Microsoft Windows:

C:\weblab\> cd client
C:\weblab\client\> gwtc
Buildfile: build.xml
(...)
     [java]    Compilation succeeded -- 533.078s

BUILD SUCCESSFUL
Total time: 9 minutes 11 seconds
C:\weblab\client\>
```

> Será criado o arquivo "war" que poderá ser manipulado pelo Eclipse incluindo-o como um novo projeto.

> Após a inclusão do projeto no Eclipse, devemos criar os pacotes do novo experimento como no exemplo abaixo:

> _es.deusto.weblab.client.lab.experiments.plugins.br.pucsp.weblab."nome do experimento com a-z 0-9 minúsculas"_

> Os pacotes devem ser separados nas seguintes categorias:

> _br.pucsp.weblab."ligaled"_
  * Factory
  * Experiment

> _br.pucsp.weblab."ligaledcommands"_
  * Comandos que serão utilizados

> _br.pucsp.weblab."ligaledui"_
  * Interface de comandos com Listenner dos comandos + arquivo XML de configuração da pagina

### Compilar com build.xml ###

No projeto do Eclipse compilar o client com o arquivo build.xml


### Arquivo de configuração do experimento ###
C:\weblab\client\war\WEB-INF\classes\es\deusto\weblab\public