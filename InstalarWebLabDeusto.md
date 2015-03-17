# Estrutura dos arquivos #

C:\
-weblab
--server
--client

-xampp

-Python26


# Softwares necessários #

Windows
**XAMPP**Python 2.6 for 32 bits.

# Variáveis de Ambiente #

Colocar as Variáveis de Ambiente para o mysql e python

set PATH=%PATH%;C:\xampp\mysql\bin
set PATH=%PATH%;C:\Python26\

testar com echo%PATH%

# Configurar WebServer #

Copiar C:\weblab\server\server\launch\apache
apache\_weblab\_generic.conf
apache\_weblab\_windows.conf

Para C:\xampp\apache\conf

e incluir as seguintes linha no final do arquivo httpd.conf

Include "conf/apache\_weblab\_windows.conf"
Include "conf/apache\_weblab\_generic.conf"


# Criar Database #

Executar os seguintes arquivos na pasta C:\weblab\server\server\deploy

create\_weblab\_administrator.py
create\_databases.py
weblab\_administrator\_credentials.py
deploy.py


# Executar experimentos #

weblab/server/launch/sample