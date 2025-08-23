# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: secros <secros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:10:22 by yabokhar          #+#    #+#              #
#    Updated: 2025/08/23 20:28:02 by yabokhar         ###   ########.fr        #
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

INCDIR = inc/

LIBDIR = libs/

OBJDIR = .Obj/

#///////////SUBDIR////////////#

PARSDIR 	= $(SRCDIR)parsing/
UTILSDIR	= $(SRCDIR)utils/
LISTSDIR	= $(SRCDIR)linked_lists/
ERRDIR 		= $(SRCDIR)errors/
RAYDIR		= $(SRCDIR)ray/
SPECDIR		= $(SRCDIR)spectator_mode/
MLXDIR		= $(SRCDIR)mlx/
IMGDIR		= $(SRCDIR)image/

# -----------FILES-----------#

MAIN 	=	main.c

MLX		=	mlx.c

IMAGE	=	get_camera.c

RT		=	raytracing.c

RAY		=	background_shade.c ray_create.c ray_at.c lightning.c ray_color.c \
			hit_plane.c	cylinder_normal.c hit_sphere.c hit_cylinder.c 

SPEC	=	move_camera.c

PARSING =	parse_arguments.c	parse_parameters.c	\
			parse_ambient_lightning.c	parse_camera.c	parse_lights.c	\
			process_characters.c	parse_objects.c	get_values.c	debug.c
UTILS	=	print.c vect3_convert.c ft_bzero_vect3.c swap_doubles.c

LISTS	=	add_element.c

THREADS	=	multithreading.c

ERRORS 	=	parsing_error_reporting.c parsing_error_reporting_bis.c \
			multithreading_error_malloc.c mlx_error_reporting.c

INC		=	miniRT.h

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
		$(addprefix $(RAYDIR), $(RAY))

# -----------LIBS------------#

LIB =	vect3 libft libmlx

LIBA = $(foreach l,$(LIB),$(LIBDIR)$(l)/$(l).a)

LIBS = $(addprefix $(LIBDIR), $(LIB))

# LIBINCDIR = $(addprefix -I , $(addsuffix $(INCDIR), $(addsuffix /, $(LIBS))))
LIBINCDIR = $(foreach l, $(LIBS), $(if $(findstring mlx, $(l)), -I $(l), -I $(l)/$(INCDIR)))

# -----------OTHER-----------#

OBJS =	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

DEPS =	$(OBJS:.o=.d)

HEADER = $(addprefix $(INCDIR), $(INC))

NAME =	miniRT

# -----------RULES-----------#

all: $(NAME)

$(NAME): $(LIBA) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAG) $(LIBA) -o $(NAME) 

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) $(LIBINCDIR) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(dir $(OBJS))

# $(LIBA): FORCE
$(LIBA): libs
libs:
	@for dir in $(LIBS); do \
		echo "$(YELLOW)Compiling library $$dir$(RESET)" && $(MAKE) -C $$dir --no-print-directory --silent; \
	done

# -----------UTILS-----------#

clean:
	@echo "$(RED)Removing object files...$(RESET)" && rm -rf $(OBJDIR)
	@for dir in $(LIBS); do \
		if [ "$$dir" != "libs/libmlx" ]; then \
			echo "$(RED)Removing $$dir .Obj/ ...$(RESET)" && $(MAKE) $@ -C $$dir --no-print-directory --silent; \
		fi; \
	done

fclean: clean
	@echo "$(RED)Removing executable or library...$(RESET)" && rm -f $(NAME)
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

-include $(DEPS)

.PHONY: clean fclean re all bonus libs
