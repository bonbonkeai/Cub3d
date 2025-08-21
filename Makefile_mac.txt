NAME        = cub3D

LIBFT_DIR   = Libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = mlx_mac
MLX_DIR2 	= mlx_mac2
MLX_LIB     = $(MLX_DIR)/libmlx.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I. -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR2)
FRAMEWORKS  = -framework OpenGL -framework AppKit
RM          = rm -f

SRCS = \
	srcs/init/init_game.c \
	srcs/init/init_img.c \
	srcs/init/init_keys.c \
	srcs/init/init_mlx.c \
	srcs/init/init_ray.c \
	srcs/init/init_texture.c \
	srcs/main/cub3d.c \
	srcs/parser/check_init_map.c \
	srcs/parser/check_init_player.c \
	srcs/parser/handle_line1.c \
	srcs/parser/check_map.c \
	srcs/parser/parser_color.c \
	srcs/parser/parser_tex.c \
	srcs/parser/parser_split.c \
	srcs/parser/parser_utils.c \
	srcs/parser/parser.c \
	srcs/raycasting/raycasting.c \
	srcs/raycasting/utils.c \
	srcs/setup/control.c \
	srcs/setup/hook.c \
	srcs/setup/key.c \
	srcs/setup/minimap.c \
	srcs/setup/mouse.c

SRCS_BONUS = \
	# srcs_bonus/xxx_bonus.c

OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR2)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(FRAMEWORKS) -o $(NAME)

bonus: CFLAGS += -DBONUS
bonus: $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR2)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(LIBFT) $(MLX_LIB) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(MLX_DIR2) clean
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
