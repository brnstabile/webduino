# Webcams para os experimentos #


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

As imagens que são visualizadas nos experimentos e no site do projeto são todas centralizadas em nosso servidor principal, desta maneira criamos um diretório específico que contem todas as imagens enviadas pelas _webcams_ . Para implementar uma arquitetura semelhante, será necessário que as câmeras possuam conexão Ethernet (poderíamos utilizar câmeras com conexão Wi-Fi, porém neste método devemos respeitar o número limite de usuários dispositivos conectados num mesmo access point), e protocolo de transporte de arquivos FTP. Já para a recepção das imagens devemos no servidor principal, necessitamos configurar alguma aplicação para servidor FTP, como o _vsftpd\_¹._

### Configuração no servidor ###
Préviamente, configuramos o serviço _vsftpd_ para aceitar o upload das imagens enviadas pelas câmeras. Criamos um usuário _webcam_ em nosso sistema operacional e utilizamos este para conexão à partir das câmeras, sendo que, também atribuímos o diretório  _/home/webcam/_, com permissão de escrita de dados para este mesmo usuário.

Para o weblabdeusto acessar estas imagens, devemos criar um link na seguinte pasta onde podemos encontrar os arquivos que os clientes irão acessar:

```
/usr/local/lib/python2.7/dist-packages/weblabdeusto-5.0-py2.7.egg/weblabdeusto_data/war/weblabclientlab/img/
```
Com o comando:

```
ln {/home/webcam/nome_da_foto.jpg} {espectro.jpg}
```


### Configuração nas câmeras ###
As informações básicas que necessitamos definir nas configurações nas webcams são as seguintes:

  * Endereço IP do servidor
  * Usuário de conexão que em nosso caso é o _webcam_

Com isso podemos realizar um teste de enviado cliando no botão de envio de teste na mesma página de configuração do serviço FTP.

Assim que constatarmos que a imagem foi recebida em nosso servidor com sucesso, alteramos as propriedades de acesso à este arquivo normalmente _.jpg_ com o seguinte comando:

```
chmod 777 nome_da_foto.jpg
```

Com o comando acima, definimos que este arquivo de imagem poderá ser visualizado por qualquer usuário em nosso sistema.

Uma configuração interessante é o envio autmático das imagens, pois as imagens deverão ser estar prontas para visualização independentemente do horário.


### Publicação das imagens ###
Para a configurar o [Java Applet Client](https://github.com/weblabdeusto/weblabdeusto/blob/master/experiments/managed/libs/client/java/src/es/deusto/weblab/client/experiment/plugins/es/deusto/weblab/javadummy/JavaDummyApplet.java) fornecido pela equipe do weblabdeusto para encontrar estas imagens, na classe _JavaDummyApplet_, devemos colocar qual será a imagem à exibir, adicionando o diretório e arquivo no parâmetro abaixo:

```
 _public static final String DEFAULT_WEBCAM_IMAGE_URL       = "/img/webcam/images/nome_da_foto.jpg";_ . 
```

Devemos tomar precaução com a defeinição deste parâmetro de localização das imagens, pois a aplicação inialmente somente encontrará imagens que estão ou no mesmo diretório que o arquivo _.jar_, ou diretório que estão abaixo deste, assim não é possível buscar imagens em locais anteriores ao diretório raiz do aplicativo.

Já para publicação em sites ou outras plataformas, podemos criar quantos links forem necessários, definindo como origem o respectivo _.jpg_.



---


## REFERÊNCIAS ##

¹ Site da aplicação _vsftpd_: https://security.appspot.com/vsftpd.html