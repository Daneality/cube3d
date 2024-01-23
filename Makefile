# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsas <dsas@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 18:35:42 by dsas              #+#    #+#              #
#    Updated: 2024/01/23 18:47:56 by dsas             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		=	main.c exit.c \
				fill_map.c init_map.c keys.c \
				keys2.c map_errors.c map.c\
				move.c pic_utils.c \
				raycasting.c raycasting2.c split_utils.c \
				textures.c utils.c color_trgb.c


MLX_FLAGS		= 	-lmlx -framework OpenGL -framework AppKit
CC_FLAGS		=	-Wall -Wextra -Werror -g
CC				=	cc
SRCS_F			= srcs/
OBJS_F			= obj/


LIBFT = inc/libft/
MLX = mlx/

OBJS		=	$(SRCS:.c=.o)
OBJS_P		=	$(addprefix $(OBJS_F), $(OBJS))
NAME		= 	cub3D

all:$(NAME)

$(OBJS_F)%.o: $(SRCS_F)%.c
	@mkdir -p $(OBJS_F)
	@echo "Working on: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS_P)
	@$(MAKE) -C $(MLX) 
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CC_FLAGS) -O3 -L$(MLX) $(MLX_FLAGS)  $(LIBFT)/libft.a -o $(NAME) $(OBJS_P)
	@echo "OK"


clean:
	@rm -rf $(OBJS_F)
	@$(MAKE) clean -C $(MLX) 
	@$(MAKE) fclean -C $(LIBFT) 

fclean:	clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re