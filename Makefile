# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 04:41:59 by pharbst           #+#    #+#              #
#    Updated: 2023/03/30 16:03:54 by pharbst          ###   ########.fr        #
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
CFLAGS		+=	-g
# CFLAGS		+=	-fsanitize=address
ifeq ($(UNAME), Darwin)
CFLAGSS      = -I$(shell brew --prefix readline)/include # -fsanitize=address -fsanitize=undefined #-Wno-gnu-include-next -I LeakSanitizer/include
LDFLAGS     = -L$(shell brew --prefix readline)/lib/ #-LLeakSanitizer  -llsan -lc++
endif


# **************************************************************************** #
# Project
# **************************************************************************** #
PRONAME		=	Minishell
NAME		=	minishell


# **************************************************************************** #
# srcs
# **************************************************************************** #
SRC_FILES	=	main.c \
				shell.c \

# parsing
SRC_FILES	+=	parsing_main.c \
				parsing_helper.c \
				quote_expand.c \
				string_con.c \
				join_arg.c \
				validate_fd.c \
				redirect_condition.c \
				redirect_helper.c \
				str_cat.c \
				check_open.c \
				token_helper_tokencheck_quote.c \
				token_helper_tokencheck.c \
				token_helper.c \
				here_doc_condition.c \
				here_doc_delimiter.c \
				ft_syntax_error.c \
				shell_readline.c \
				shell_readline_helper.c \
				here_doc_interpret.c \

# execution
SRC_FILES	+=	execute.c \
				prepare.c \
				piping.c \
				builtin_exec.c \
				child_handle_fds.c \
				piping_dup_open.c \

# Buildins
SRC_FILES	+=	cd.c \
				echo.c \
				env.c \
				export.c \
				export_args.c \
				exit.c \
				pwd.c \
				unset.c \

# tools
SRC_FILES	+=	grap.c \
				last_word.c \
				print_pipex.c \
				shell_g.c \
				find_var.c \
				arraysize.c \
				error_code.c \
				split_free.c \
				signal_helper.c \
				shell_free.c \

# **************************************************************************** #
# directories
# **************************************************************************** #
INC_DIR		=	./includes
SRC_DIR		=	./src/*/
OBJ_DIR		=	./obj
LIBFTIO_DIR	=	./libftio


# **************************************************************************** #
# libraries
# **************************************************************************** #
LIBFTIO		=	$(LIBFTIO_DIR)/libftio.a


# **************************************************************************** #
# Includes
# **************************************************************************** #
INC			=	-I $(INC_DIR)
INC_LIBFTIO	=	-I $(LIBFTIO_DIR)/includes


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
	@./spinner.sh make -s proname_header fclean $(NAME)

# $(NAME):	proname_header libftio_header $(LIBFTIO) obj_header $(OBJ) linking_header
# 	@$(CC) $(CFLAGS) $(OBJ) -L/usr/local/lib -I/usr/local/include -lreadline $(LIBFTIO) -o $(NAME)
# 	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

$(NAME):	proname_header libftio_update_header libftio_update libftio_header $(LIBFTIO) obj_header $(OBJ) linking_header
	@$(CC) $(CFLAGS) $(OBJ) $(CFLAGSS) $(LDFLAGS) -lreadline $(LIBFTIO) -o $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	
$(OBJ_DIR)/%.o:	$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) $(INC_LIBFTIO) $(CFLAGSS) -c $< -o $@

libftio_update:
	@git submodule update --init >/dev/null 2>&1

$(LIBFTIO):
	@make -C $(LIBFTIO_DIR) > /dev/null

# **************************************************************************** #
# Cleaning Rules
# **************************************************************************** #
fclean:	proname_header
	@./spinner.sh make hard_cleanall

clean:	proname_header
	@./spinner.sh make clean_simple

clean_simple:
	@printf "$(FRed)Cleaning$(RESET)		 			 						      "
	@rm -rf $(OBJ_DIR)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

hard_cleanall:
	@printf "$(FRed)FCleaning$(RESET)										  	      "
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@make -C $(LIBFTIO_DIR) fclean > /dev/null
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
	@printf " $(FGreen)[$(TICK)]\n$(FBlue)Compiling Libftio$(Reset)										     "

libftio_update_header:
	@printf "$(FBlue)Updating Libftio$(Reset)										     "

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
