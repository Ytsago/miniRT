# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 17:28:29 by yabokhar          #+#    #+#              #
#    Updated: 2025/06/21 20:44:27 by yabokhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------RULES-----------#

CFLAGS = -Wall -Wextra -Werror -MMD -MP 
LFLAGS = -lm
CC = cc
AR = ar
ARFLAG = -rcs

# -----------PATHS-----------#

SRCDIR = src/

INCDIR = inc/
OBJDIR = .Obj/

# -----------FILES-----------#

MAIN =		vect3_const.c	vect3_math.c	vect3_operator.c 
INC =		Vect3.h

# -----------SRCS-----------#



SRCS =	$(addprefix $(SRCDIR), $(MAIN)) \

# -----------OTHER-----------#

OBJS =	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

DEPS =	$(OBJS:.o=.d)

HEADER = $(addprefix $(INCDIR), $(INC))

NAME =	vect3.a

# -----------RULES-----------#

all: $(NAME) Makefile

$(NAME):$(OBJS)
	@$(AR) $(ARFLAG) $(NAME) $(OBJS) 

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -I $(INCDIR) $(if $(LIBS),-I $(LIBDIR)$(INCDIR)) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(dir $(OBJS))

# -----------UTILS-----------#

clean:
	@rm -rf $(OBJDIR)
ifneq ($(LIBS),)
	@$(MAKE) $@ -C $(LIBDIR) 
endif

fclean: clean
	@rm -f $(NAME)
ifneq ($(LIBS),)
	@$(MAKE) $@ -C $(LIBDIR) 
endif

re: fclean all

FORCE:

-include $(DEPS)

.PHONY: clean fclean re all bonus
