# Atualização da plataforma weblabdeusto #


---

## CONSIDERAÇÔES ##

Sistema Operacional: Ubuntu Server 12.04

  * Definimos aqui apenas as configurações básicas para uma implementação semelhante ao ao laboratório do projeto webduino;

  * Colchetes e chaves são utilizadas apenas como caracter de delimitação e são desconsiderados nos códigos;

  * Considere que utilizamos o seguinte diretório de instalação do weblabdeusto: [/opt/weblabdeusto];

  * Todas nossas instâncias são dispostas no diretório  [/opt/weblabdeusto/labs];

  * As informações mais detalhadas dos procedimentos estão disponíveis em: https://weblabdeusto.readthedocs.org/en/latest/

  * Para instalação inicial da plataforma weblabdeusto utilize os documentos fornecidos pelos desenvolvedores em: https://weblabdeusto.readthedocs.org/en/latest/installation.html

  * Por ser uma plataforma recente, o weblabdeusto possui atualizações constantes o que poderá diferenciar em alguns procedimentos abaixo;

---

## PROCEDIMENTOS ##

Para atualizar a aplicação do weblabdeusto, utilizamos o protocolo de versionamento de desenvolvimento de softwares chamado Git, assim é necessário previamente instala-lo em nosso servidor. Quando realizamos o processo de atualização, os arquivos locais do nosso servidor serão modificados de acordo com as alterações realizadas no repositório online do weblabdeusto, localizado na URL https://github.com/weblabdeusto/weblabdeusto/. Entretando, as diferentes versões ocasionalmente possuam discrepâncias relevântes, ocasionando em instabilidade ou não funcionamento do sistema. Por precaução, anteriormente a qualquer alteração, realizar um backup das instâncias dos laboratórios e qualquer outro arquivo modificado pelo usuário dentro dos diretórios do weblabdeusto. Uma situação ideal, requer um “servidor espelho” para um teste prévio da nova versão.

Em suma, são necessários três passos para realizar a atualização completa: Atualizar os arquivos da aplicação, recompilar o sistema e atualizar as instâncias de laboratórios criadas. Com isso, devemos parar a execução de qualquer laboratório ativo no sistema - verificar utilizando o comando _ps -x_ <sup>1</sup> - e executar os seguintes comandos com o usuário que possui direitos de administrador, por exemplo o usuário _root_:

```
sudo git pull --progress
```

Atualização dos arquivos da aplicação
Executar o comando abaixo dentro da diretório onde o weblabdeusto foi instalado. Por exemplo: _/opt/weblabdeusto/_




Recompilar e reinstalar o sistema
Para recompilar e reinstalar a aplicação do weblabdeusto é necessário executar os seguintes arquivos:

```
/{local_de_instalacao}/weblabdeusto/client/gwtc.sh

/opt/weblabdeusto/setup.py
```


Atualizar as instâncias já implementadas
Para instâncias de laboratórios préviamente criados com a versão anterior devemos executar o seguinte comando:

```
weblab-admin upgrade {diretorio_da_instancia}
```


---


## REFERÊNCIAS ##

¹ Man page do comando _ps_ : http://manpages.ubuntu.com/manpages/precise/en/man1/ps.1.html

² Man page do comando _git_ : http://manpages.ubuntu.com/manpages/precise/en/man1/git.1.html