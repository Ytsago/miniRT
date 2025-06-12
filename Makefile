# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: secros <secros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:10:22 by yabokhar          #+#    #+#              #
#    Updated: 2025/06/12 14:04:05 by yabokhar         ###   ########.fr        #
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
MLXFLAG = -lbsd -lX11 -lm -lXext 
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
ERRDIR 		= $(SRCDIR)errors/

# -----------FILES-----------#

MAIN 	=	main.c	initialize_scene_variables.c

PARSING =	parse_arguments_then_get_fd.c	parse_and_load_parameters.c	\
			parse_ambient_lightning.c	parse_camera.c	parse_light.c	\
			jump_characters.c	parse_object.c	parsing_utils.c	debug.c

ERRORS 	=	parsing_error_reporting.c

INC		=	miniRT.h

# -----------SRCS-----------#

SRCS =	$(addprefix $(SRCDIR), $(MAIN))\
		$(addprefix $(PARSDIR), $(PARSING))\
		$(addprefix $(ERRDIR), $(ERRORS))

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

all: libs $(NAME)

$(NAME): $(LIBA) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAG) $(LIBA) -o $(NAME) 

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) $(LIBINCDIR) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(dir $(OBJS))

# $(LIBA): FORCE
libs:
	@for dir in $(LIBS); do \
		echo "$(YELLOW)Compiling library $$dir$(RESET)" && $(MAKE) -C $$dir --no-print-directory; \
	done

# -----------UTILS-----------#

clean:
	@echo "$(RED)Removing object files...$(RESET)" && rm -rf $(OBJDIR)
	@for dir in $(LIBS); do \
		echo "$(RED)Removing $$dir .Obj/ ...$(RESET)" && $(MAKE) $@ -C $$dir --no-print-directory; \
	done

fclean: clean
	@echo "$(RED)Removing executable or library...$(RESET)" && rm -f $(NAME)
	@for dir in $(LIBS); do \
		if [ "$$dir" = "libs/libmlx" ]; then \
			echo "$(RED)Removing $$dir lib.a ...$(RESET)"; \
		else \
			echo "$(RED)Removing $$dir lib.a ...$(RESET)" && $(MAKE) $@ -C $$dir --no-print-directory; \
		fi; \
	done

re: fclean all

print-%:
	@echo $($(patsubst print-%,%,$@))

-include $(DEPS)

.PHONY: clean fclean re all bonus libs
