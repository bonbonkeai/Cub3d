NAME		=	cub3D
BONUS		=	cub3D_bonus
LIBFT		=	libft/libft.a
INC			=	includes/
INC_B		=	bonus/includes/
SRC_DIR		=	srcs/
SRC_DIR_B	=	bonus/srcs/
OBJ_DIR		=	obj/
OBJ_DIR_B	=	bonus/obj/
MLX_DIR		=	mlx_linux/
MLX_LIB		=	$(MLX_DIR)libmlx.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iincludes -I/usr/include -Imlx -I./libft
INCLUDES_B	=	-Ibonus/includes -I/usr/include -Imlx -I./libft
FLAGS		=	-Lmlx_linux -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
RM			=	rm -f

# source files
SRCS		=	$(SRC_DIR)cub3d.c \
			

SRCS_B		=	$(SRC_DIR_B)cub3d_bonus.c \
				

OBJS		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJS_B		=	$(patsubst $(SRC_DIR_B)%.c,$(OBJ_DIR_B)%.o,$(SRCS_B))

all:		$(NAME)
bonus:		$(BONUS)

$(LIBFT):
		@make -sC ./libft
		@echo "Libft compilation success!"

$(MLX_LIB):
		@make -sC $(MLX_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(FLAGS) $(INCLUDES) \
		$(LIBFT) $(MLX_LIB) -o $(NAME)
		@echo "Compilation success!"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -Iinclude -Imlx -c $< -o $@

$(BONUS):	$(OBJS_B) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(OBJS_B) $(FLAGS) $(INCLUDES_B) \
		$(LIBFT) $(MLX_LIB) -o $(BONUS)
		@echo "Bonus Compilation success!"

$(OBJ_DIR_B)%.o:	$(SRC_DIR_B)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INCLUDES_B) -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR) $(OBJ_DIR_B)
		@make clean -C ./libft
		@make clean -C $(MLX_DIR)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(BONUS)
		@$(RM) $(LIBFT)
		@make clean -C $(MLX_DIR)

re:		fclean all

.PHONY:		all clean fclean re bonus