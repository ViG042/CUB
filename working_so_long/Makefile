NAME	= so_long
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I../inc/minilibx-linux -g3
LFLAGS	= -L../inc/minilibx-linux -lmlx -lXext -lX11 -lm -lz
SRCS	= main.c parsing.c ft_split.c errors.c ft_itoa.c\
 		initialisations.c flood_fill.c destroy.c move.c\
		init_images.c show_map.c parsing_2.c
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(MLX) :
	cd ../inc/minilibx-linux
	make -C

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : fclean re all clean
