# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: secros <secros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:10:22 by yabokhar          #+#    #+#              #
#    Updated: 2025/10/08 16:08:44 by secros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------COLOR-----------#

GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RED    = \033[31m
RESET  = \033[0m

# -----------RULES-----------#

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
MLXFLAG = libs/vect3/vect3.a libs/libft/libft.a libs/libmlx/libmlx.a -lbsd -lX11 -lXext -lm
CC = cc
AR = ar
ARFLAG = -rcs

# -----------PATHS-----------#

SRCDIR = src/

SRCDIR_BONUS = src_bonus/

INCDIR = inc/

LIBDIR = libs/

OBJDIR = .Obj/

OBJDIR_BONUS = .Obj_bonus/

#///////////SUBDIR////////////#

PARSDIR 	= $(SRCDIR)parsing/
UTILSDIR	= $(SRCDIR)utils/
LISTSDIR	= $(SRCDIR)linked_lists/
ERRDIR 		= $(SRCDIR)errors/
RAYDIR		= $(SRCDIR)ray/
SPECDIR		= $(SRCDIR)spectator_mode/
MLXDIR		= $(SRCDIR)mlx/
IMGDIR		= $(SRCDIR)image/
OBJEDIR		= $(SRCDIR)object/
BUMPDIR		= $(RAYDIR)bumpmapping/

PARSDIR_BONUS 	= $(SRCDIR_BONUS)parsing/
UTILSDIR_BONUS	= $(SRCDIR_BONUS)utils/
LISTSDIR_BONUS	= $(SRCDIR_BONUS)linked_lists/
ERRDIR_BONUS	= $(SRCDIR_BONUS)errors/
RAYDIR_BONUS	= $(SRCDIR_BONUS)ray/
SPECDIR_BONUS	= $(SRCDIR_BONUS)spectator_mode/
MLXDIR_BONUS	= $(SRCDIR_BONUS)mlx/
IMGDIR_BONUS	= $(SRCDIR_BONUS)image/
OBJEDIR_BONUS	= $(SRCDIR_BONUS)object/
BUMPDIR_BONUS	= $(RAYDIR_BONUS)bumpmapping/

# -----------FILES-----------#

MAIN 	=	main.c

MLX		=	mlx_event.c mlx_display.c mlx_helpers.c mlx_clear.c

IMAGE	=	get_camera.c

RT		=	raytracing.c

RAY		=	checkerboard.c background_shade.c ray_create.c ray_at.c lightning.c\
			lightning_helpers.c ray_color.c

	BUMP =	cone_mapping.c cylinder_mapping.c plane_mapping.c sphere_mapping.c mapping.c 

OBJECT	=	hit_cylinder.c hit_sphere.c hit_plane.c cylinder_normal.c hit_cone.c\
			object.c


SPEC	=	move_camera.c

PARSING =	parse_arguments.c	parse_parameters.c	\
			parse_ambient_lightning.c	parse_camera.c	parse_lights.c	\
			process_characters.c	parse_objects.c	get_values.c \
			 parse_texture.c parse_cone.c parse_cylinder.c

UTILS	=	print.c vect3_convert.c ft_bzero_vect3.c swap_doubles.c	\
			free_and_return_null.c 

LISTS	=	add_element.c

THREADS	=	multithreading.c

ERRORS 	=	parsing_error_reporting.c parsing_error_reporting_bis.c \
			multithreading_error_malloc.c

INC		=	miniRT.h bumpmapping.h

# -----------SRCS-----------#

SRCS =	$(addprefix $(SRCDIR), $(MAIN))\
		$(addprefix $(PARSDIR), $(PARSING))\
		$(addprefix $(SRCDIR), $(THREADS))\
		$(addprefix $(SRCDIR), $(RT))\
		$(addprefix $(ERRDIR), $(ERRORS))\
		$(addprefix $(UTILSDIR), $(UTILS))\
		$(addprefix $(LISTSDIR), $(LISTS))\
		$(addprefix $(MLXDIR), $(MLX))\
		$(addprefix $(SPECDIR), $(SPEC))\
		$(addprefix $(IMGDIR), $(IMAGE))\
		$(addprefix $(RAYDIR), $(RAY))\
		$(addprefix $(OBJEDIR), $(OBJECT))\
		$(addprefix $(BUMPDIR), $(BUMP))\

SRCS_BONUS =	$(addprefix $(SRCDIR_BONUS), $(MAIN))\
				$(addprefix $(PARSDIR_BONUS), $(PARSING))\
				$(addprefix $(SRCDIR_BONUS), $(THREADS))\
				$(addprefix $(SRCDIR_BONUS), $(RT))\
				$(addprefix $(ERRDIR_BONUS), $(ERRORS))\
				$(addprefix $(UTILSDIR_BONUS), $(UTILS))\
				$(addprefix $(LISTSDIR_BONUS), $(LISTS))\
				$(addprefix $(MLXDIR_BONUS), $(MLX))\
				$(addprefix $(SPECDIR_BONUS), $(SPEC))\
				$(addprefix $(IMGDIR_BONUS), $(IMAGE))\
				$(addprefix $(RAYDIR_BONUS), $(RAY))\
				$(addprefix $(OBJEDIR_BONUS), $(OBJECT))\
				$(addprefix $(BUMPDIR_BONUS), $(BUMP))\

# -----------LIBS------------#

LIB =	libft vect3 libmlx

LIBA = $(foreach l,$(LIB),$(LIBDIR)$(l)/$(l).a)

LIBS = $(addprefix $(LIBDIR), $(LIB))

# LIBINCDIR = $(addprefix -I , $(addsuffix $(INCDIR), $(addsuffix /, $(LIBS))))
LIBINCDIR = $(foreach l, $(LIBS), $(if $(findstring mlx, $(l)), -I $(l), -I $(l)/$(INCDIR)))

# -----------OTHER-----------#

OBJS =	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

OBJS_BONUS = $(patsubst $(SRCDIR_BONUS)%.c, $(OBJDIR_BONUS)%.o, $(SRCS_BONUS))

DEPS =	$(OBJS:.o=.d)

DEPS_BONUS = $(OBJS_BONUS:.o=.d)

HEADER = $(addprefix $(INCDIR), $(INC))

NAME =	miniRT

NAME_BONUS = miniRT_bonus

# -----------RULES-----------#

all: libs $(NAME)

bonus: libs $(NAME_BONUS)

$(NAME): $(LIBA) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAG) $(LIBA) -o $(NAME) 

$(NAME_BONUS): $(LIBA) $(OBJS_BONUS) 
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLXFLAG) $(LIBA) -o $(NAME_BONUS) 

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) $(LIBINCDIR) -c $< -o $@ 

$(OBJDIR_BONUS)%.o: $(SRCDIR_BONUS)%.c | $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) -I $(INCDIR) $(LIBINCDIR) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(addprefix $(OBJDIR), $(dir $(patsubst $(SRCDIR)%,%,$(SRCS))))

$(OBJDIR_BONUS):
	@mkdir -p $(OBJDIR_BONUS) $(addprefix $(OBJDIR_BONUS), $(dir $(patsubst $(SRCDIR_BONUS)%,%,$(SRCS_BONUS))))

# $(LIBA): FORCE
libs:
	@for dir in $(LIBS); do \
		echo "$(YELLOW)Compiling library $$dir$(RESET)" && $(MAKE) -C $$dir --no-print-directory --silent; \
	done

# -----------UTILS-----------#

clean:
	@echo "$(RED)Removing object files...$(RESET)" && rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@for dir in $(LIBS); do \
		if [ "$$dir" != "libs/libmlx" ]; then \
			echo "$(RED)Removing $$dir .Obj/ ...$(RESET)" && $(MAKE) $@ -C $$dir --no-print-directory --silent; \
		fi; \
	done

fclean: clean
	@echo "$(RED)Removing executable or library...$(RESET)" && rm -f $(NAME) $(NAME_BONUS)
	@for dir in $(LIBS); do \
		if [ "$$dir" = "libs/libmlx" ]; then \
			echo "$(RED)Removing $$dir lib.a ...$(RESET)" && $(MAKE) clean -C $$dir ; \
		else \
			echo "$(RED)Removing $$dir lib.a ...$(RESET)" && $(MAKE) $@ -C $$dir --no-print-directory --silent; \
		fi; \
	done

re: fclean all

print-%:
	@echo $($(patsubst print-%,%,$@))

-include $(DEPS) $(DEPS_BONUS)

.PHONY: clean fclean re all bonus libs
