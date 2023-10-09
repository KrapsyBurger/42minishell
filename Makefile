# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:07:37 by rdel-agu          #+#    #+#              #
#    Updated: 2022/08/25 18:56:22 by rdel-agu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm

OBJDR = obj

OBJ = $(SRC:.c=.o)

SRC =	src/main.c\
		src/pwd.c\
		src/env.c\
		src/env2.c\
		src/env3.c\
		src/cd.c\
		src/ft_itoa.c\
		src/echo.c\
		src/libft.c\
		src/libft_helper.c\
		src/libft_helper2.c\
		src/export.c\
		src/export_helper.c\
		src/export_helper2.c\
		src/unset.c\
		src/demallocage.c\
		src/demallocage2.c\
		src/ft_mod_split.c\
		src/lexer.c\
		src/state_machine_utils.c\
		src/state_machine.c\
		src/state_machine2.c\
		src/state_machine3.c\
		src/state_machine4.c\
		src/expander.c\
		src/expander2.c\
		src/expander3.c\
		src/expander4.c\
		src/pipex_parser1.c\
		src/pipex_parser2.c\
		src/pipex_parser3.c\
		src/pipex_parser4.c\
		src/command_access.c\
		src/infile_outfile_checker.c\
		src/pipex_exec.c\
		src/heredoc.c\
		src/heredoc2.c\
		src/heredoc3.c\
		src/child.c\
		src/child_helper.c\
		src/bltn_exec.c\
		src/bltn_exec_helper.c\
		src/empty.c\
		src/init.c\
		src/exit.c\
		src/pipex_parser.c\

all: $(NAME)

bonus: $(NAME)_bonus

src/%.o: src/%.c 
	@$(CC) $(CFLAGS)  -c $<  -I/usr/include -o $@

$(NAME): $(OBJ)
	@echo " \033[0;31mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@echo " \033[0;32mSuccess\033[0m"

clean:
	@$(RM) -f $(OBJ)
	@echo " \033[0;32mCleaning done!\033[0m"
	
fclean: clean
	@$(RM) -f $(NAME)
	@$(RM) -f $(NAME)_bonus

re: fclean all

norme:
	@echo " \033[0;31mChecking sources...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo " \033[0;31mChecking libft...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(LFTSRC)
	@echo " \033[0;31mChecking includes...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(INCL)
	@echo " \033[0;32mDone!\033[0m"

sanit:
	@echo " \033[0;31mCompiling libft...\033[0m"
	@make -C libft/ -s
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling with fsanitize...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -fsanitize=address -g3 -L/usr/lib -o $(NAME) libft/libft.a
	@echo " \033[0;32mSuccess!\033[0m"
	
.PHONY: clean fclean
