# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 04:41:59 by pharbst           #+#    #+#              #
#    Updated: 2023/02/08 22:00:13 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)


# ****************************************************************************  #
# Colors and Printing stuff
# ****************************************************************************  #
Black			=	$(shell echo "\033[0;30m")
FBlack			=	$(shell echo "\033[1;30m")
Red				=	$(shell echo "\033[0;31m")
FRed			=	$(shell echo "\033[1;31m")
BRed			=	$(shell echo "\033[1;41m")
Green			=	$(shell echo "\033[0;32m")
FGreen			=	$(shell echo "\033[1;32m")
Brown/Orange	=	$(shell echo "\033[0;33m")
FBrown/Orange	=	$(shell echo "\033[1;33m")
FYellow			=	$(shell echo "\033[1;33m")
Yellow			=	$(shell echo "\033[0;33m")
Blue			=	$(shell echo "\033[0;34m")
FBlue			=	$(shell echo "\033[1;34m")
Purple			=	$(shell echo "\033[0;35m")
FPurple			=	$(shell echo "\033[1;35m")
Cyan			=	$(shell echo "\033[0;36m")
FCyan			=	$(shell echo "\033[1;36m")
FWhite			=	$(shell echo "\033[1;37m")
White			=	$(shell echo "\033[0;37m")
RESET			=	$(shell echo "\033[0m")
TICK			=	$(shell echo "\xE2\x9C\x94")


# **************************************************************************** #
# Compiler
# **************************************************************************** #
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		+=	-L/usr/local/lib -I/usr/local/include -lreadline
CFLAGS		+=	-g
# CFLAGS		+=	-fsanitize=address


# **************************************************************************** #
# Project
# **************************************************************************** #
PRONAME		=	Minishell
NAME		=	minishell


# **************************************************************************** #
# srcs
# **************************************************************************** #
SRC_FILES	=	main.c \
				prompt_line.c \
				grap.c \
				last_word.c \
				shell.c \
				split.c \


# **************************************************************************** #
# directories
# **************************************************************************** #
INC_DIR		=	./includes
SRC_DIR		=	./src/*
OBJ_DIR		=	./obj
LIBFTIO_DIR	=	./libftio
PIPEX_DIR	=	./pipex


# **************************************************************************** #
# libraries
# **************************************************************************** #
LIBFTIO		=	$(LIBFTIO_DIR)/libftio.a
PIPEX		=	$(PIPEX_DIR)/pipex.a


# **************************************************************************** #
# Includes
# **************************************************************************** #
INC			=	-I $(INC_DIR)
INC_LIBFTIO	=	-I $(LIBFTIO_DIR)/includes
INC_PIPEX	=	-I $(PIPEX_DIR)/includes


# **************************************************************************** #
# objs
# **************************************************************************** #
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

all:
	@./spinner.sh make -s $(NAME)

re:
	@./spinner.sh make proname_header fclean $(NAME)

hard_re:
	@./spinner.sh make proname_header hard_clean $(NAME)

$(NAME):	proname_header libftio_header $(LIBFTIO) pipex_header $(PIPEX) obj_header $(OBJ) linking_header
	@$(CC) $(CFLAGS) $(OBJ) -L/usr/local/lib -I/usr/local/include -lreadline $(LIBFTIO) $(PIPEX) -o $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) $(INC_LIBFTIO) $(INC_PIPEX) -c $< -o $@

$(LIBFTIO):
	@make -C $(LIBFTIO_DIR) > /dev/null

$(PIPEX):
	@make -C $(PIPEX_DIR) > /dev/null


# **************************************************************************** #
# Cleaning Rules
# **************************************************************************** #
fclean:	proname_header
	@./spinner.sh make cleanall

clean:	proname_header
	@./spinner.sh make clean_simple

hard_clean:	proname_header
	@./spinner.sh make hard_cleanall

cleanall:
	@printf "$(FRed)FCleaning$(RESET)										  	      "
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

clean_simple:
	@printf "$(FRed)Cleaning$(RESET)		 			 						      "
	@rm -rf $(OBJ_DIR)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

hard_cleanall:
	@printf "$(FRed)Hard Cleaning$(RESET)										  	      "
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@make -C $(LIBFTIO_DIR) fclean > /dev/null
	@make -C $(PIPEX_DIR) fclean > /dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

# **************************************************************************** #
# git rules
# **************************************************************************** #
git:	commit push

commit:
	git commit -m "$(msg)"

push:
	git push -u $(branch)

update:
	git pull
	make update -C $(LIBFTIO_DIR)

# **************************************************************************** #
# Header Rules
# **************************************************************************** #
libftio_header:
	@printf "$(FBlue)Compiling Libftio$(Reset)										     "

pipex_header:
	@printf " $(FGreen)[$(TICK)]\n$(FBlue)Compiling Pipex$(Reset)											     "

obj_header:
	@printf " $(FGreen)[$(TICK)]\n$(FBlue)Compiling .o files$(RESET)										     "

linking_header:
	@printf " $(FGreen)[$(TICK)]\n$(Green)Linking $(PRONAME)$(RESET)										      "

proname_header:
	@printf "$(FYellow)╔═══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n\
$(FYellow)║$(FGreen)	 ▄▀▀▄ ▄▀▄$(FYellow)  ▄▀▀█▀▄  $(FPurple)  ▄▀▀▄ ▀▄$(FCyan)  ▄▀▀█▀▄  $(FBlue) ▄▀▀▀▀▄    $(FRed)  ▄▀▀▄ ▄▄   ▄▀▀█▄▄▄▄  ▄▀▀▀▀▄    ▄▀▀▀▀▄     	$(FYellow)║\n\
$(FYellow)║$(FGreen)	█  █ ▀  █$(FYellow) █   █  █ $(FPurple) █  █ █ █$(FCyan) █   █  █ $(FBlue)█ █   ▐    $(FRed) █  █   ▄▀ ▐  ▄▀   ▐ █    █    █    █      	$(FYellow)║\n\
$(FYellow)║$(FGreen)	▐  █    █$(FYellow) ▐   █  ▐ $(FPurple) ▐  █  ▀█$(FCyan) ▐   █  ▐ $(FBlue)   ▀▄      $(FRed) ▐  █▄▄▄█    █▄▄▄▄▄  ▐    █    ▐    █      	$(FYellow)║\n\
$(FYellow)║$(FGreen)	  █    █ $(FYellow)     █    $(FPurple)   █   █ $(FCyan)     █    $(FBlue)▀▄   █     $(FRed)    █   █    █    ▌      █         █       	$(FYellow)║\n\
$(FYellow)║$(FGreen)	▄▀   ▄▀  $(FYellow)  ▄▀▀▀▀▀▄ $(FPurple) ▄▀   █  $(FCyan)  ▄▀▀▀▀▀▄ $(FBlue) █▀▀▀      $(FRed)   ▄▀  ▄▀   ▄▀▄▄▄▄     ▄▀▄▄▄▄▄▄▀ ▄▀▄▄▄▄▄▄▀ 	$(FYellow)║\n\
$(FYellow)║$(FGreen)	█    █   $(FYellow) █       █$(FPurple) █    ▐  $(FCyan) █       █$(FBlue) ▐         $(FRed)  █   █     █    ▐     █         █         	$(FYellow)║\n\
$(FYellow)║$(FGreen)	▐    ▐   $(FYellow) ▐       ▐$(FPurple) ▐       $(FCyan) ▐       ▐$(FBlue)           $(FRed)  ▐   ▐     ▐          ▐         ▐         	$(FYellow)║\n\
$(FYellow)╚═══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n$(RESET)"