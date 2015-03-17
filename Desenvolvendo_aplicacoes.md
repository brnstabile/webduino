# Desenvolvendo as aplicações para o experimento #


---


## CONSIDERAÇÔES ##

Sistema Operacional: Ubuntu Server 12.04

  * Definimos aqui apenas as configurações básicas para uma implementação semelhante ao laboratório do projeto webduino;
  * Considere que utilizamos o seguinte diretório de instalação do weblabdeusto: _/opt/weblabdeusto_;
  * Todas nossas instâncias são dispostas no diretório  _/opt/weblabdeusto/labs_;
  * As informações mais detalhadas dos procedimentos estão disponíveis em: https://weblabdeusto.readthedocs.org/en/latest/
  * Para instalação inicial da plataforma weblabdeusto utilize os documentos fornecidos pelos desenvolvedores em: https://weblabdeusto.readthedocs.org/en/latest/installation.html
  * Por ser uma plataforma recente, o weblabdeusto possui atualizações constantes o que poderá diferenciar em alguns procedimentos abaixo;

---


## PROCEDIMENTOS ##

A plataforma weblabdeusto possibilita a integração de várias tecnologias para o controle dos experimentos, entretanto iniciamos nossos desenvolvimentos com os Java Applets que possui linguagem de programação em Java e pode ser reutilizada em outras aplicações. Contudo não será possível acessar os experimentos através de dispositivos móveis, assim iremos migrar para HTML5 e JavaScript.

Para uma primeira implementação, os procedimentos abaixo evidenciam claramente a relação da aplicação no cliente com o sistema dos laboratório, assim é interessante utilizar este método ao menos como primeira abordagem. Por conseguinte, a equipe desenvolvedora nos fornece um projeto básico para implementação e testes.

Antes de tudo, necessitamos de uma _IDE_ como o [Eclipse](http://www.eclipse.org/downloads/) ou o [NetBeans](https://netbeans.org/downloads/) e o JDK, para facilitar o desenvolvimento do projeto de aplicação exemplo em Java Applet. Se estiver em dúvida nas versões das IDE’s, para o Eclipse as versões _Eclipse IDE for Java EE Developers_, _Eclipse IDE for Java Developers_,  _Eclipse Standard 4.3.1_ e para o NetBeans as versões _Java EE_ e _Tudo_ fornecem o que precisamos. Poderíamos até mesmo utilizar o notepad incluindo a biblioteca para aplicações Java fornecido pelo weblabdeusto, entretanto este procedimento requer um melhor aperfeiçoamento no conhecimento em programação Java e compilação. O Java EE é relacionado as aplicações Web, entretanto as versões básicas suprem nossa necessidade.

Após instalar a IDE, e realizar o download ou instalação do weblabdeusto, podemos encontrar no diretório _/weblabdeusto-master/weblabdeusto-master/experiments/managed/libs/client/java_ o projeto que será incluido em nossa IDE. Para que os arquivos originais mantenham-se instactos, devemos selecionar a opção que irá copiar os arquivos para a nossa _workspace_ que se localiza em _C:\Users\Usuario\workspace_ no windows ou _/home/usuario/workspace_ em sistemas Linux.

## IMPORTAÇÃO ##

### Eclipse ###

Com a IDE em execução devemos importar o projeto para a nossa _workspace_  através do menu _File_ e _import_.

![http://weblabduino.googlecode.com/files/open_project.png](http://weblabduino.googlecode.com/files/open_project.png)

Selecione na categoria _General_ a opção _Existing Projects into Workspace_
![http://weblabduino.googlecode.com/files/folder_project.png](http://weblabduino.googlecode.com/files/folder_project.png)


Na próxima janela selecione o diretório do projeto original que está em _/weblabdeusto-master/weblabdeusto-master/experiments/managed/libs/client/java_ e ainda marque a opção _Copy projects into workspace_.


![http://weblabduino.googlecode.com/files/create_project.png](http://weblabduino.googlecode.com/files/create_project.png)

Clicando em _Finish_ podemos navegar pelo projeto até a classe _JavaDummyApplet_ a qual será modificada de acordo com a necessidade.

![http://weblabduino.googlecode.com/files/browse_project.png](http://weblabduino.googlecode.com/files/browse_project.png)

Para o servidor de experimentos são necessários os mesmos procedimentos, entretanto o diretório do projeto original é o _/weblabdeusto-master/weblabdeusto-master/experiments/managed/libs/server/java_.


## EXPORTAÇÃO ##
Os procedimentos de exportação são diferentes para o cliente e para o servidor, pois o primeiro irá será executado à partir do browser e o segundo será executado diretamente no computador servidor de experimentos.

Primeiramente selecione no diretório do projeto da aplicação cliente _javadummy_, clique com o botão direito e selecione a opção _Export_.

**Cliente e Servidor**

![http://weblabduino.googlecode.com/files/export_project.png](http://weblabduino.googlecode.com/files/export_project.png)

Agora selecione o tipo que será importado sendo para o cliente _Jar File_ e para o servidor _Runnable Jar File_.

**Cliente**

![http://weblabduino.googlecode.com/files/export_type_project.png](http://weblabduino.googlecode.com/files/export_type_project.png)

**Servidor**

![http://weblabduino.googlecode.com/files/export_type_server_project.png](http://weblabduino.googlecode.com/files/export_type_server_project.png)


Com os modos selecionados, devemos definir o local de exportação para ambos e para o servidor, em especial devemos selecionar a classe de execução préviamente utilizada nos testes.

**Cliente**

![http://weblabduino.googlecode.com/files/finish_export_project.png](http://weblabduino.googlecode.com/files/finish_export_project.png)


**Servidor**

![http://weblabduino.googlecode.com/files/finish_export_server_project.png](http://weblabduino.googlecode.com/files/finish_export_server_project.png)

Estes arquivos serão utilizados para incluir no nosso sistema.


---


## OBSERVAÇÔES ##
  1. Preste atenção se a biblioteca _plugin.jar_ é referenciada no arquivo _build.xml_, a qual é utilizado pela aplicação;