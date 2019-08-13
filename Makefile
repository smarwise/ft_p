client = client

server = server

FLAGS = gcc -Wall -Wextra -Werror

client_obj = client_obj/main.o\
     
server_obj = server_obj/main.o\

$(client) : $(client_obj)
	make -C libft
	$(FLAGS) -o $(client) $(client_obj) libft/libft.a

$(server) : $(server_obj)
	make -C libft
	$(FLAGS) -o $(server) $(server_obj) libft/libft.a

all : $(client) $(server)

$(client_obj): client_obj/%.o: client_src/%.c
	$(FLAGS) -c client_src/$*.c -o $@

$(server_obj): server_obj/%.o: server_src/%.c
	$(FLAGS) -c server_src/$*.c -o $@

clean:
	make clean -C libft/
	rm -f $(client_obj)
	rm -f $(server_obj)

fclean: clean
	make fclean -C libft/
	rm -f $(CLIENT)
	rm -rf $(SERVER)

re: fclean all