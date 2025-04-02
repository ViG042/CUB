# **************************************************************************** #
#		General variables													   #
# **************************************************************************** #

NAME		= cub

DIR_SRC		= src
DIR_DISP	= display
DIR_ERR		= error
DIR_INPU	= input
DIR_PARS	= parsing
DIR_PAIN	= paint
DIR_GAME	= game
DIR_RAY		= raycasting

DIR_OBJ		= obj
DIR_OBJS	= $(DIR_OBJ) $(DIR_OBJ)/$(DIR_INPU) $(DIR_OBJ)/$(DIR_PARS) \
				$(DIR_OBJ)/$(DIR_ERR) $(DIR_OBJ)/$(DIR_RAY) \
				$(DIR_OBJ)/$(DIR_DISP) $(DIR_OBJ)/$(DIR_PAIN) \
				$(DIR_OBJ)/$(DIR_GAME)

DIR_INC		= inc
DIR_LIB		= $(DIR_INC)/libft \
				$(DIR_INC)/minilibx-linux

HEADER		= $(DIR_INC)/cub.h

FUNC_GAME	=	loop.c \
				time.c \
				move.c

FUNC_PARS	=	do_parsing.c \
				check_syntax.c \
				elem_errors.c \
				elem_extract.c \
				elem_init.c \
				elem_color.c \
				map_check.c \
				map_clean.c \
				prints.c

FUNC_DISP	=	render.c \
				window.c \

FUNC_ERR	=	clean.c \
				errors.c

FUNC_INPU	=	input.c \
				player.c \
				collision.c

FUNC_PAIN	=	color.c \
				minimap.c \
				rasterize.c \
				shape.c \
				blend.c \
				shading.c \
				project.c

FUNC_RAY 	=	dda.c \
				texture.c \
				block.c \
				side.c

FUNC		=	$(addprefix $(DIR_DISP)/, $(FUNC_DISP)) \
				$(addprefix $(DIR_ERR)/, $(FUNC_ERR)) \
				$(addprefix $(DIR_INPU)/, $(FUNC_INPU)) \
				$(addprefix $(DIR_PARS)/, $(FUNC_PARS)) \
				$(addprefix $(DIR_TRANS)/, $(FUNC_TRANS)) \
				$(addprefix $(DIR_PAIN)/, $(FUNC_PAIN)) \
				$(addprefix $(DIR_GAME)/, $(FUNC_GAME)) \
				$(addprefix $(DIR_RAY)/, $(FUNC_RAY))

MAIN		= main.c

SRC			= 	$(addprefix $(DIR_SRC)/, $(FUNC)) \
				$(addprefix $(DIR_SRC)/, $(MAIN))

OBJ			= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB			= inc/libft/libft.a \
			inc/minilibx-linux/libmlx.a \
			-L/usr/lib -lX11 -lXext -lm -lz

DEP			= $(DIR_OBJS) $(HEADER)

INC			= -I$(DIR_INC)

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

V_FLAG		= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --track-fds=yes

# **************************************************************************** #
#																			   #
#			COMPILATION														   #
#																			   #
# **************************************************************************** #

all:				$(NAME)

$(NAME):			$(DEP) $(OBJ)
					$(MAKE) -C inc/libft
					$(MAKE) -C inc/minilibx-linux
					$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o  $@

$(DIR_OBJS):
					mkdir -p $@

# **************************************************************************** #
#																			   #
#			TEST AND DEBUG													   #
#																			   #
# **************************************************************************** #

debug:				$(DEP) $(OBJ)
					$(MAKE) -C inc/libft
					$(MAKE) -C inc/minilibx-linux
					@echo "Compiling with debug flag"
					$(CC) $(CFLAGS) -g $(INC) -o $(NAME) $(SRC) $(LIB)

valgrind:			debug
					@echo "Running with valgrind :"
					$(V_FLAG) ./$(NAME)

opti:
					$(CC) $(CFLAGS) -O3 $(INC) -o $(NAME) $(SRC) $(LIB)

# **************************************************************************** #
#																			   #
#			CLEAN UP														   #
#																			   #
# **************************************************************************** #

clean:
					rm -rf $(DIR_OBJ)
					make -C inc/libft clean
					make -C inc/minilibx-linux clean

fclean:
					rm -rf $(DIR_OBJ)
					rm -rf $(NAME)
					make -C inc/libft fclean

re:					fclean all

.PHONY:				all clean fclean re debug test compile
