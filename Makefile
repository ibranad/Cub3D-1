NAME = cub3d

CC = gcc

ADDITIONAL_FLAGS = -g -fsanitize=address

C_FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

FUNCTIONS =	otoufah/map_filling.c\
			otoufah/my_mlx_pixel_put.c\
			otoufah/get_player_position.c\
			otoufah/get_keys.c\
			otoufah/projecting_rays.c\
			otoufah/cast_rays.c\
			otoufah/move_forward.c\
			otoufah/move_left.c\
			otoufah/move_right.c\
			otoufah/move_backword.c\
			otoufah/destroy_window.c\
			orbiay/check_textures_colors.c\
			orbiay/checking_walls.c\
			orbiay/check_map_utils.c\
			orbiay/read_and_add.c\
			orbiay/To_hexa.c\
			orbiay/main.c\
			orbiay/map_cheking.c\
			orbiay/check_Path.c\
			libft/ft_strcmp.c\
			libft/ft_strlen.c\
			libft/ft_strncmp.c \
			libft/ft_strdup.c\
			libft/ft_strjoin.c\
			libft/ft_split.c\
			libft/ft_atoi.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
		
OBJECTS = $(FUNCTIONS:.c=.o)

RM = rm -rf

all		:	$(OBJECTS)
			$(CC) $(C_FLAGS) $(MLX_FLAGS) $(OBJECTS) ./otoufah/cub3d.c -o $(NAME)

clean	:	$(OBJECTS)
			$(RM) $(OBJECTS)

fclean :	clean
	$(RM) $(NAME)

re: fclean all
