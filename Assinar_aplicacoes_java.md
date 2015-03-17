# Assinar aplicações Java #


---


## CONSIDERAÇÔES ##

Sistema Operacional: Ubuntu Server 12.04


---


## PROCEDIMENTOS ##

Dependendo da aplicação desenvolvida em Java Applet, serão necessários permissões especiais para acesso a recursos externos da sandbox da JVM (Java Virtual Machine). Assim, devemos assinar digitalmente nossos arquivos Java implementados no weblabdeusto, para que estes sejam reconhecidos pelos usuários como uma aplicação confiável.

A plataforma JDK fornece as ferramentas necessárias para assinar digitalmente nossas aplicações, e uma vez criado o arquivo de assinatura certificado, podemos utilizá-lo até que expire seu tempo de validade, assim uma mesma assinatura será utilizada para diferentes aplicações. Devemos seguir os seguintes passos para criarmos aplicações confiáveis para distribuição:


Criando o arquivo de assinatura
Selecionar de preferência o diretório _home_ do usuário o qual irá criar o arquivo de assinatura

```
_keytool -genkey -alias MyPlugins -keyalg RSA -keystore mykeystore.ks  -validity 10000_¹

-genkey: gerar uma chave
-alias: referencia à chave
-keyalg: algoritmo para gerar a chave
-keystore: criar arquivo da chave
-validity: tempo para expirar
```

Adicionar um ceritificado ao seu arquivo de assinatura

```
_keytool -selfcert -keystore mykeystore.ks -alias MyPlugins_
```

Assinando as aplicações
Para finalmente assinar os arquivos _.jar_ execute o comando abaixo:

```
jarsigner -keystore mykeystore.ks WeblabJavaSample.jar MyPlugins
```


REFERÊNCIAS

¹Man page _keytool_: http://manpages.ubuntu.com/manpages/precise/man1/gkeytool.1.html