NAME = ft_ls

objs = main.o ft_parse.o ft_listing.o ft_helper.o ft_flagbits.o ft_free_mem.o ft_get_parse.o ft_printing.o ft_parse_helper.o ft_recursive.o ft_setuid.o \
	ft_errors.o

flags = -Wall -Werror -Wextra

libft = libft/libft.a

all : $(NAME)

$(NAME) : $(objs)
	make -C libft/
	gcc $(flags) $(objs) $(libft) -o $(NAME)

%.o : %.c ft_ls.h
	gcc -Wall -Werror -Wextra -c $< -o $@

clean :
	rm -f $(objs)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)
	make fclean -C libft/

re : fclean
	make
