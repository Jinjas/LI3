BUILDDIR := objects/
SRCFILES = $(wildcard src/*.c)
OBJFILES = $(SRCFILES:src/%.c=$(BUILDDIR)%.o)

INPUTFILE  = input.txt
OUTPUTFILE = /home/rodrigo/Documents/uni/LI3/backupOfProject/large-outputs

program: $(OBJFILES) Resultados# só compila o programa (o que for necessário)
	gcc $(SRCFILES) -lncurses -o programa-principal -O3 -g -lncurses
	gcc test/main.c src/drivers.c src/interactive.c src/query1.c src/query2.c src/query3.c src/query4.c src/rides.c src/users.c src/query5.c src/query6.c src/query7.c src/utilities.c src/query_handler.c -lncurses -o programa-testes -O3

run: program Resultados
	./programa-principal

run_with_files: program Resultados # correr o programa e compila o que for necessário
	./programa-principal "." $(INPUTFILE)

test: Resultados #cria um executavel para verificar testes
	gcc test/main.c src/drivers.c src/interactive.c src/query1.c src/query2.c src/query3.c src/query4.c src/rides.c src/users.c src/query5.c src/query6.c src/query7.c src/utilities.c src/query_handler.c -lncurses -o programa-testes -O3

runTests: test
	./programa-testes "." ./test_output/input.txt

Resultados:
	mkdir -p $@

objects: # constroi a diretoria com os objects
	mkdir -p $@

print: $(SRCFILES) #caga nisto (make print)
	ls -la  $?

print2: $(OBJFILES) #caga nisto
	ls -la  $?

clean: #apaga td o que foi criado
	rm -rf $(BUILDDIR) programa-principal programa-testes Resultados

verify: verify.c run_with_files #compara os Resultados obtidos com um output dado (trocar o nome aqui por agora)
	gcc verify.c 
	./a.out 500 Resultados $(OUTPUTFILE)
	rm -rf a.out

$(BUILDDIR)%.o: src/%.c | objects # cria os objetos
	$(CC) -o "$@" -c "$<"

time: program Resultados# o time
	time ./programa-principal "." input.txt


 