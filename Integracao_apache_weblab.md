# Integrando o laboratório ao servidor Web Apache #


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

Para configurar uma instância de laboratório no servidor Web Apache, devemos configurá-lo com as referências para as páginas do laboratório remoto recém criado. Por exemplo, após criarmos um laboratório denominado _teste_, existirão arquivos que referenciam as páginas de acesso a este nova instância dentro do diretório _../teste/http_, assim devemos dizer ao servidor Apache que estas páginas deverão ser gerenciadas por ele, e fazemos isto adicionando ao diretório _/opt/weblabdeusto/labs/_, um arquivo comum utilizando qualquer editor de texto como o _vim_ ou o _gedit_, no diretório _/etc/apache2/conf.d/_ com o seguinte conteúdo:

```
Include “/opt/weblab/labs/teste/http/apache_weblab_generic.conf”
```

E caso existam outras instâncias de laboratórios implementadas, podemos incluir suas referências neste mesmo arquivo utilizando a função _Include_ e o local de configuração do Apache. Podemos ainda alterar os redirecionamentos de requisição de páginas nos arquivos do diretório _/opt/weblab/labs/teste/http_