CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCS    = -I. -I./Libft -I./mlx_linux
NAME    = cub3D
LIBFT   = ./Libft/libft.a
MLX_DIR = ./mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a
LDLIBS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS = \
	srcs/init/init_game.c \
	srcs/init/init_img.c \
	srcs/init/init_keys.c \
	srcs/init/init_mlx.c \
	srcs/init/init_texture.c \
	srcs/init/init_player.c \
	srcs/init/init_map.c \
	srcs/main/cub3d.c \
	srcs/raycasting/raycasting.c \
	srcs/raycasting/color_utils.c \
	srcs/raycasting/calculate_ray.c \
	srcs/raycasting/calculate_wall.c \
	srcs/raycasting/dda.c \
	srcs/raycasting/draw.c \
	srcs/raycasting/draw_utils.c \
	srcs/raycasting/draw_crosshair.c \
	srcs/raycasting/put_px_alpha.c \
	srcs/setup/control.c \
	srcs/setup/hook.c \
	srcs/setup/key.c \
	srcs/setup/mouse.c \
	srcs/minimap/minimap.c \
	srcs/minimap/minimap_utils.c \
	srcs/minimap/draw_rect.c \
	srcs/minimap/draw_tile.c \
	srcs/minimap/draw_border.c \
	srcs/minimap/draw_line.c \
	srcs/minimap/calculate_size.c \
	srcs/parser/parser_utils.c \
	srcs/selfie_stick/selfie_system.c \
	srcs/selfie_stick/selfie_utils.c \
# 	srcs/parser/parser.c \
	srcs/init/init_ray.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_LIB) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	make -C ./Libft

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make -C ./Libft clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	make -C ./Libft fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
