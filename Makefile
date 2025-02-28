# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 15:34:20 by mkling            #+#    #+#              #
#    Updated: 2025/02/28 15:36:21 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		General variables													   #
# **************************************************************************** #

NAME		= cub

DIR_SRC		= src
DIR_EXEC	= execution
DIR_PARS	= parsing

DIR_OBJ		= obj
DIR_OBJS	= $(DIR_OBJ) $(DIR_OBJ)/$(DIR_EXEC) $(DIR_OBJ)/$(DIR_PARS) \

DIR_INC		= inc

DIR_LIB		= $(DIR_INC)/libft

HEADER		= $(DIR_INC)/cub.h

# FUNC_EXEC	=

# FUNC_PARS	=

FUNC		=	$(addprefix $(DIR_EXEC)/, $(FUNC_EXEC)) \
				$(addprefix $(DIR_PARS)/, $(FUNC_PARS)) \

MAIN		= main.c

SRC			= 	$(addprefix $(DIR_SRC)/, $(FUNC)) \
				$(addprefix $(DIR_SRC)/, $(MAIN))

OBJ			= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB			= -L$(DIR_LIB) -lft -lm

DEP			= $(DIR_OBJS) $(HEADER)

INC			= -I$(DIR_INC) -I$(DIR_LIB)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

V_FLAG		= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --track-fds=yes --trace-children=yes \
				--suppressions=inc/readline.supp

# **************************************************************************** #
#																			   #
#			COMPILATION														   #
#																			   #
# **************************************************************************** #

all:				$(NAME)

$(NAME):			$(DEP) $(OBJ)
					$(MAKE) -C $(DIR_LIB)
					$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o  $@

$(DIR_OBJS):
					mkdir -p $@

$(LIB):
					make -C $(DIR_LIB)

# **************************************************************************** #
#																			   #
#			TEST AND DEBUG													   #
#																			   #
# **************************************************************************** #

debug:		$(DEP) $(OBJ)
			$(MAKE) -C $(DIR_LIB)
			@echo "Compiling with debug flag"
			$(CC) $(CFLAGS) -g $(INC) -o $(NAME) $(SRC) $(LIB)

valgrind:	debug
			@echo "Running with valgrind :"
			$(V_FLAG) ./$(NAME)

# **************************************************************************** #
#																			   #
#			CLEAN UP														   #
#																			   #
# **************************************************************************** #

clean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			make -C $(DIR_LIB) clean

fclean:
			rm -rf $(DIR_OBJ)
			rm -rf $(T_DIR)/$(T_NAME)
			rm -rf $(NAME)
			make -C $(DIR_LIB) fclean

re:			fclean all

.PHONY:		all clean fclean re debug test compile
