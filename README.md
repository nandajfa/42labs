<h1 align="center">
	Processo seletivo da 3º Edição do 42 Labs.
 </h1>

 [![NPM](https://img.shields.io/npm/l/react)](https://github.com/nandajfa/42labs/blob/main/LICENSE)


  ## 🗣️ Sobre

> _Aplicação de monitoramento de serviços web._

####

  Projeto desenvolvido em linguagem C, que monitora serviços web utilizando 3 protocolos: HTTP, PING e DNS. Para cada protocolo, existirão configurações que definem como o monitoramento vai acontecer, assim como o endereço do serviço monitorado. As configurações de monitoramento estarão em um arquivo com nome monitoring.db.


As configurações para cada protocolo são:

| Protocolo   | Configurações                                                           |
|-------------|-------------------------------------------------------------------------|
| HTTP        | nome, protocolo, endereço, método HTTP, código HTTP esperado, intervalo |
| PING        | nome, protocolo, endereço, intervalo                                    |
| DNS         | nome, protocolo, endereço, intervalo, servidor DNS                      |

Abaixo, exemplo do arquivo descrito acima:

```txt
# monitoring.db

intra	HTTP	intra.42.fr	GET	200	120
game ping test	PING	game.42sp.org.br	60
workspaces monitoring	PING	workspaces.42sp.org.br	60
```

## Como usar
**Siga os passos abaixo**
```bash
# Clonar o projeto e acessar a pasta
https://github.com/nandajfa/42labs.git && cd 42labs/

# Compilação
make

# Execute o programa
./monitoring

# Remove todos os arquivos (.o)
make clean

# Utiliza (make clean) e também remove suas dependências e arquivo executável
make fclean

# Remove o aquivo monitoring.log
make cfile

# Recompila o programa
make re

# Well done!
```

### :toolbox: Ferramentas utilizadas

:small_orange_diamond: **LIBCURL**

A libcurl é uma biblioteca de transferência de URL do lado do cliente  para aplicações escritas em C gratuita e fácil de usar. Ela foi escolhida pela facilidade de se encontrar informações e tutoriais sobre seu uso para APIs em C. A libcurl permite receber e processar com facilidade o conteúdo do corpo e do header da requisição através da função curl_easy_setopt().

:small_orange_diamond: **GET_NEXT_LINE**

Projeto realizado na 42sp. Usado em algumas funções para leitura de arquivos.

:small_orange_diamond: **LIBFT**

Primeiro projeto da 42, onde recodificamos funções da biblioteca C padrão. Algumas funções dessa biblioteca foram utilizadas.

### 📑 Planejamento e Referências

* ➡️ [Notion](https://grizzled-turtle-393.notion.site/42-Labs-2de8c9e246074f83adb3298dcaf3d000)

 #### Autor

Made by jessica Fernanda 👋 [See my linkedin](https://www.linkedin.com/in/jessica-fernanda-alves-marques-106651205/)
