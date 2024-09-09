# Regras para compilar os executáveis
all: par_impar islands imagens

par_impar: par_impar.c queue.c
	gcc -o par_impar par_impar.c queue.c

islands: islands.c pqueue.c
	gcc -o islands islands.c pqueue.c

imagens: imagens.c pqueue.c
	gcc -o imagens imagens.c pqueue.c

# Regra para limpar os arquivos gerados
clean:
	rm -f par_impar islands imagens